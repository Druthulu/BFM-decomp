---
ts: 2026-11-06T15:23:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_rMLDP2oyJPlCDZ4QIqJB
---
Interesting. The main structural differences:
1. First block: `andi v1,s1,0x6000` vs `andi v0,v0,0x6000` — the first launder's purpose: keep raw local ($v0) and flags global ($s1). Removing it merges them into $s1.
2. The second launder's purpose: target has `move v0,s2` in two places (a local copy `fire` of ret/s2) — with it removed, the copies vanish (2 insns: mine 251 vs 253).

So I need:
(a) keep raw and flags as separate pseudos.
(b) keep `fire` as a separate copy from ret.

For (b): `s32 fire = ret; if (fire != 0) ...`. Target: `move v0,s2` — a local copy of ret ($s2) into $v0 used for the test. Without the launder, `fire` is copy-propagated to ret and the branch tests $s2 directly.

Wait, in the current source (with asm), it's:
```
{
    s32 fire = ret;
    __asm__(ret);
    if (fire != 0) { ... }
}
```
So the asm re-ties `ret` (global), forcing ret into a register, and `fire` stays a separate local copy. Hmm, but the target has `move v0,s2` — the copy fires into $v0.

Real-C alternative: make `fire` a real second value: e.g. `s32 fire = ret; if (fire != 0)` where ret is used after? ret isn't used after. Hmm. Since ret isn't used after, `fire` and `ret` are the same value; cse merges them. The asm forces ret to be born at that point as a separate reg, so the copy exists.

What real-C would keep the copy? Maybe declare fire and assign ret through an operation that isn't a plain copy: e.g. `s32 fire = ret & 0xFFFFFFFF;`? folds. `fire = ret;` + use of ret afterwards? There's nothing after.

Alternative: restructure so `ret` is used after the if — no, changes code.

Hmm, what about making the last block not a copy but a comparison of the variable itself, e.g. `if (ret != 0)` — then no move at all (target has a move). Target explicitly has `move v0,s2` twice: one at 215 in a delay slot and one at 235. Interesting: the target's copies are in branch delay slots (reorg duplicates). So target: `move v0,s2; beqz v0,...`. So a real copy is made.

The C0414 dead-reset technique: `ret = 0;` after using it? If I write:
```
if (ret != 0) {
    s32 fire = ret;   // hmm
```

Actually think in terms of gcc: `fire = ret; if (fire)` — copy propagation in cse merges. To stop cse merging, a "real 2nd set" of either variable. For the moves examples, "real 2nd set `c = (u8)c;`" — a sub-word assignment is a real set (different mode conversion). Here `s32 fire = ret;` is same mode. If `fire` were s16: `s16 fire = ret;` then `if (fire != 0)` — that introduces an lh/sll+sra... changes codegen.

Hmm, what about `u32 fire = ret;`? Same mode SImode. No.

Let me think about cse: cse1 processes insns; `(set fire ret)` records equivalence. Later `(set reg fire)`... Actually the merge happens because copy propagation / reg allocation coalesces. Let me look at the actual RTL. But first, let me consider what's cheapest: maybe `do{}while(0)` block (C0535) can help — the brief allows `do{}while(0)` only with `// !FAKE: do-while`. It splits cse1's EBB, which prevents cse from propagating across. For the `fire` case: 

```
{
    s32 fire = ret;
    do { } while (0);  // ?
```
No, the do-while must contain something.

Look at the func_80177F84 crack: "the two pinned copies wrapped in do{}while(0) — the block splits cse1's ebb so sched1 keeps the $3 copy before the $4 copy". And func_800CB2C8: "do-while(0) around raw=t splits the EBB so the lbu qty takes v1 and t v0".

So for (a): 
```
raw = call();
flags = raw;
```
If we wrap `flags = raw;` in a do-while(0) block, cse1's EBB splits — the copy is in a separate block so cse doesn't propagate raw into flags uses? Actually the equivalence recorded in the block still applies... but across block boundary cse deletes equivalences (they're not valid across blocks unless the block is part of an EBB; cse1 does extended basic blocks, and a do-while creates a block boundary that ends the EBB).

Let's test:
```
raw = call();
do { flags = raw; } while (0);  // !FAKE: do-while
```
Hmm, but cse still sees the copy in its own block and might propagate within it — nothing after in that block. Then in the next block flags is used; cse's canon_reg... Within a new EBB, cse starts fresh, but the copy propagation of `flags` could have happened in cse1's block-level pass. Actually the point is that cse's reg_eqv table for the EBB maps flags→raw; splitting the EBB means when the next block starts, the table is cleared. But the copy insn `flags = raw` may still be deleted by cse if... no, it's needed.

Hmm, actually the issue described: "cse canon_reg substitutes one for the other, so the surviving allocno is the GLOBAL". The merge could happen in global-alloc/flow through copy propagation. Let's just try things empirically.

Plan for item 1: try variants:
1. Wrap `flags = raw;` in do-while(0).
2. Wrap `fire = ret;` in do-while(0).
3. Combinations.

Let me write a script that generates candidates. I'll do it by hand with sed/Edit on a copy.

Let me create a generator approach: write files a2.c etc. with specific replacements. Use python script under the item dir (allowed).

Actually simpler: use Edit on a copy. Let me copy orig.c to w.c and edit.

Let me be efficient: write a small python generator that takes orig.c and applies textual substitutions. I'll write gen.py in the item dir.

But first let me understand the tools: delever_search --try TU fn file --body. The file is a bare definition. Good.

Let me create gen.py for item 1 with variants list.

Variant definitions:
- V1: remove both asm (a1) = 14.
- V2: keep removal, wrap flags copy: 
  ```
  raw = ((s32 (*)(s32))func_8012CBA4)(a0);
  do { flags = raw; } while (0);  // !FAKE: do-while
  ```
- V3: wrap fire: 
  ```
  s32 fire;
  do { fire = ret; } while (0);  // !FAKE: do-while
  if (fire != 0) ...
  ```
- V4: both.

Let me build with a python script (no inline python -c; use a file).
