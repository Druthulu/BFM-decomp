---
ts: 2026-10-21T23:38:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_ShhgzTPNrs5Qx3uP0ISQ
---
Same as a1. So gcc CSEs sp+24 across the two uses regardless of whether p1 is a variable.

So the CSE is between `sp10+4` (call1 arg) and `sp10+4` (call2 arg) — same expression → one pseudo → kept in s0.

So the fix must break the CSE between these two. The launder does that by making p1 an opaque asm output.

Real-C ways to break CSE between two identical constant-address expressions:
1. Different base objects at the same address — impossible without a union/alias.
2. Use a union! e.g.
```
union { u16 a[6]; u16 b[6]; } sp10;   // b[0] is at the same address as a[0]
```
Then call1 uses sp10.a+4 and call2 uses sp10.b+4 — different MEM_REF offsets on different components? Actually union members at offset 0 → same address, but the rtx would be (plus (symbol_ref) (const 8)) in both cases, since union member b's address is symbol+0. So same. Hmm.

3. Make one of them a *load* from memory: e.g. store the pointer in a stack slot and load it back → `lw` insn. Doesn't match.

4. Use `&sp10[4]` vs `sp10 + 4` — same.

5. Use a pointer variable that is assigned from a *different* expression: e.g.
```
u16 *p1 = sp10 + 4;
u16 *p2 = &sp10[4];
```
both same address.

6. Compute the address via an integer cast: `func_800D23D0((u16 *)((s32)sp10 + 8))` — hmm, the rtx would be (plus (symbol_ref) (const 8)) still? Casting a pointer to s32 and adding 8 gives (plus (reg holding symbol_ref) (const 8))? Actually (s32)sp10 would be a conversion of the address → the rtx is (plus (symbol_ref) (const 8)) after simplification? Hmm, in gcc, a pointer cast to integer keeps the address as (symbol_ref) and the conversion to s32 might produce a MEM or a register copy. The addition then is (plus (cast (symbol_ref)) (const 8)). The rtx trees differ! (plus (symbol_ref) (const 8)) vs (plus (convert (symbol_ref)) (const 8)). But cse would then need to unify them; gcc's cse does handle conversions... but the first one might be in a different mode.

Hmm, this is getting deep. Let's think about the target differently.

ALTERNATIVE IDEA: maybe the target's two addiu's come from a completely different C structure: what if the original game code had a *local pointer variable* `p` that was assigned `sp10+4` and then the second call used `p` after `p` was modified... no.

Hmm, what about: the second call's argument is `sp10 + 4` and the first call's second argument is `p1` where p1 is a pointer that gcc keeps in a REGISTER — and the register happens to be... no, the target has no register holding sp+24.

Wait wait. Let me re-read the target:
```
3 addiu a0,sp,16
4 addiu a1,sp,24
5 li a2,1
```
Both a0 and a1 computed as addiu from sp. Then later
```
14 jal func_800D23D0
15 addiu a0,sp,24
```

Hmm, so the target computes sp+24 twice. Since these are the two uses.

OK so what if the C had the two uses spelled via DIFFERENT base objects: e.g., the array is passed to the first function as `sp10` and `sp10+4`, and to the second as `sp10+4` — but what if the second call takes `p1` where p1 was set to `sp10+4` BEFORE any modification, and gcc's CSE...

I keep going in circles. Let me look at what the launder actually does at the RTL level by dumping. The brief mentions tools/cc1_dumps_tu.sh and tools/alloc_table.py, and .run/P40/T10/hdump.sh. Let me look at those to understand what's available.

Actually, a more productive approach: let me check whether some OTHER shard already cracked this same function. func_80180D54 and func_801815D4 are twins. moves.md has 150 lines; let me search for these function names in moves.md and in other shards' results.

Let me grep moves.md for 80180D54 and 801815D4.
