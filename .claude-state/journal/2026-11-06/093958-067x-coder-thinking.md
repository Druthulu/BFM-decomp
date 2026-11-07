---
ts: 2026-11-06T16:39:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_joaurXIsp3geeJF8ZBOa
---
The dead-reset cse-breaker: `p = expr; use; p = 0;` — flow deletes the dead set before sched1, zero bytes. But it invalidates cse equivalence at the second set. Here the issue is local-alloc/global-alloc combining self with the param, not cse. But maybe a dead-reset on the param after the copy? e.g.:

```
self = arg0;
arg0 = 0;   /* dead-reset */
```
flow deletes the dead set of arg0? But arg0 is a parameter; setting it to 0 after its last use is dead → deleted before sched1, zero bytes. But would it affect local-alloc? local-alloc runs after sched1 and after flow, so the dead set is gone. Hmm, no effect then.

The combine_regs decision in local-alloc is based on the copy insn `self = arg0` where ureg=72. It combines if 72's qty... Actually in win.c the param pseudo 72 is defined at insn 4 `(set 72 (reg a0))` and used at insn 11 `(set 73 72)`. local-alloc processes block 0: insn 4 is a copy from hard reg a0 to 72 → ties 72 to a0 suggestion. insn 11 is a copy 72→73, and if 72 dies at insn 11, combines 73 into 72's qty → both get a0. But global-alloc shows 72 in a1, 73 in a0.

Hmm, this is getting deep. Let me just try a bunch of variants and score them. Empiricism wins. Let me create a generator that emits variants of the two arms and the self handling, then sc.sh them all.

Variants for self handling:
S0: `s32 self; self = arg0;` (baseline win.c, score 16)
S1: pointer self `Unkstruct *self = (Unkstruct *)arg0;` (c1, 16)
S2: `s32 self; do { self = arg0; } while (0);`
S3: `s32 self = arg0;` (initializer at decl)
S4: pointer self with initializer: `Unkstruct *self = (Unkstruct *)arg0;`
S5: `u32 self = (u32)arg0;` uses via casts
S6: `s32 self; self = arg0 + 0;`
S7: `s32 self; self = arg0 | 0;`
S8: `s32 self; self = arg0 ^ 0;`
S9: `s32 self; self = arg0 * 1;`
S10: `s32 self; self = arg0 - 0;`
S11: self as `u8 *` with byte offsets (cast at uses)
S12: `s32 self; self = (s32)((u8 *)arg0);`

And arm variants for the p/f and q/g ordering:
T-decls: p,f vs f,p; assignments p,f vs f,p
E-decls: q,g vs g,q; assignments q,g vs g,q

But first, find an S variant that gets self into a1 in both arms (score residual then only the arm allocation).

Note: the current score is 16 and the diff is entirely: insert target's then-arm block (7 lines) and the arms' register assignments. Wait, the diff says "insert mine[7:7] target[7:14]" — 7 lines missing in mine at position 7, and "replace mine[12:20] target[19:20]" — meaning mine's then-arm block is placed after the j? Let me re-read the diff:

```
insert mine[7:7] target[7:14]
   7 -- | lw v1,32(a1)
   ...
  13 -- | sh v1,256(a1)
replace mine[10:11] target[17:18]
  10 and v1,v1,a0 | ori v1,v1,0x80
replace mine[12:20] target[19:20]
  12 j ... | sh v0,260(a1)
  13 sh v0,256(a1) | --
  ...
```

This is a difflib view, confusing. The real differences (from the asm comparison) are:
- target then: p=v1, f=v0; mine: p=v0, f=v1 (and target mask li before loads; mine also).
- target else: base a1, q=v0, g=v1; mine: base a0, q=v1, g=v0.

So two issues: self base and the register order in both arms.

Let me first solve the self base (bigger). Try S2 (do-while) and S3 (initializer).

Let me generate variants programmatically. I'll write gen.py that writes files sN.c and then sc.sh them.

Actually, since each score is ~1s, 20 candidates = 20s. Fine.

Let me write the generator with a template.
