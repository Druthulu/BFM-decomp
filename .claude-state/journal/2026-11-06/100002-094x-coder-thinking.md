---
ts: 2026-11-06T17:00:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6VDNYziVj0BOXCkUHyDM
---
Still 3. So the &m caching is inherent to the struct assignment path. Hmm.

Wait — maybe the issue isn't cse but the *frame*: the target has `addiu s1,68(sp)` saving s1, and uses s1 for p. Mine also saves s1 and uses it for p (dc8 lw s1,32(s0)). Then mine REUSES s1 for &m after p dies. The target doesn't.

Since s1 is already saved (for p), using it for &m is free. The compiler chose to keep &m in s1 across the call. The target recomputes.

Why? In the target (with the asm launder), cse is blocked across the asm. With real C, cse sees &m as a constant and keeps it in a register.

To prevent: make &m not a constant expression. E.g., compute &m via a pointer that the compiler can't fold: `Blk20 *mp = &m;` then use mp for both calls — but then it would use the same register (mp), which is exactly the caching. Hmm.

The target recomputes `addiu a0,sp,32` — so it does NOT keep a pointer variable. That's cse's remat behavior when the address is a simple constant. So how do we get remat? In y01 (hand-expanded copy + s-launder + q dead-reset), we got remat. The s-launder's presence changed cse.

Maybe the q dead-reset in y01 worked because the hand-expanded copy doesn't create the &m register; the q = &m is the only &m register, and the reset kills it. In z01, the struct assignment creates... hmm, the sw instructions use sp-relative addressing (no register).

Wait, maybe the difference is the *order of cse's equivalence table*: with the struct assignment, `&m` (sp+32) appears as the destination address in the copy, and cse records the value of the address computation. Then `q = &m` reuses it (no addiu?). Hmm, but there IS an addiu s1,sp,32 at e74.

Let me try: do the struct copy to a different expression so &m isn't recorded, e.g., copy via a pointer `q`:
```
q = &m;
*q = D_800AE620;
q = 0;
RotMatrixY(ang & 0xFFF, &m);
```
ab01 tried `*mp = D_800AE620; mp = 0;` → 3.

Hmm. What if the struct copy is done as `m = D_800AE620;` and then we add a statement that clobbers the cse table for the address, e.g., a dead reset of a pointer that aliases... 

Actually, C0414's mechanism is about cse equivalences of *registers*. The &m at func_800484EC might be CSEd with the q register from RotMatrixY. If q is dead-reset, cse shouldn't. But maybe the RotMatrixY argument setup creates a register that cse keeps for the next call regardless.

Let me look at the RTL difference by testing y01 vs z01 more directly. In y01, the target bytes appear. Let me objdump y01 to see the &m handling. y01 has the hand-expanded copy + s-launder + q dead-reset. Let me see if it has `addiu a1,sp,32` and `addiu a0,sp,32`.

Actually, y01 scores 0, so it must. So the hand-expanded copy + s-launder + q reset gives remat. The s-launder is a launder that must go.

Idea: keep the hand-expanded copy but replace the s-launder with a real-C equivalent that makes `s` a non-constant register. What if `s` is assigned from a *global pointer variable*? e.g., `Blk20 *s = (Blk20 *)D_800AE620_ADDR;` — still constant.

What if we read the fields via a pointer that's an argument to a no-op? no.

Hmm. What if we use `s = &D_800AE620;` and then force `s` into a register by taking its address? `&s` → s goes to the stack. no.

What if we make the copy a struct assignment but to a *pointer variable's target* and then reset? ab01 gave 3.

OK, the remaining 3 is the &m cache. Let me try to break it with a dead-reset of a variable that aliases &m at the right point. Since the compiler caches &m in s1 (a callee-saved register), we need to make it think s1 is clobbered. A call to a function that clobbers s1? No, s1 is callee-saved.

What if we insert a `volatile` read? changes bytes.

Alternatively, accept score 3 and consider it a PARTIAL? No — PARTIAL requires score 0 keeping some levers. A WALL requires all row kinds gone; best = 3. That's a WALL with best 3 (very close). But let me try a bit more.

Hmm, wait: maybe the &m cache is caused by the struct assignment, and I could avoid it by using the hand-expanded copy with a *different* real-C way to keep the base in a register: read the source through a pointer variable that cse can't rematerialize because it's *assigned from a non-constant*.

What if the base comes from `(Blk20 *)((u8 *)&D_800AE620 + (i - i))`? The compiler folds.

What if the base is `&D_800AE620` but we use a union or a cast that prevents remat? E.g., `Blk20 *s = &D_800AE620;` then `s->w[0]` — cse remats.

Hmm, what if we declare `s` as `volatile Blk20 *`? Then the loads are volatile (different code).

What if we read the whole struct via a struct assignment to a local and then copy to m? `m = D_800AE620;` is exactly that.

OK, let me try one more idea for the &m cache: use a separate variable for the &m passed to func_800484EC and reset it *after* the call, plus a reset before:
```
q = &m;
RotMatrixY(ang & 0xFFF, q);
q = 0;
...
q = &m;
func_800484EC((s32)q, (s32)vec, (s32)vec);
q = 0;
```
aa02 did this (with a block-scoped q) → 3.

Hmm.

What if the target's remat comes from the *q launder asm* blocking cse across it (C0208: cross-jumping after scheduling; cse can't see through asm). The dead-reset is supposed to be equivalent (C0414) but here it isn't fully.

Let me test whether the q dead-reset is even needed in z01: ac01 (no q at all) = 3. So the q reset doesn't matter; the &m cache is from the struct copy.

So the question: how to make the struct copy NOT leave &m in a register? The copy uses sp-relative stores, so no register. Then RotMatrixY(ang, &m) materializes &m into a1 (addiu a1,sp,32). Then func_800484EC(&m,...) — cse reuses... hmm, the value in a1 is clobbered by the call (caller-saved), so cse can't reuse a1; it must recompute (addiu a0,sp,32). But mine keeps it in s1 across the call.

Why does the compiler keep &m in s1? Because it's used twice with a call in between, and s1 is already saved. It's a deliberate cse decision to cache.

In the target (with the asm), cse couldn't cache because the asm blocked it.

To prevent caching in real C: make the two &m uses not CSE-able. E.g., compute &m through a function-like expression that differs:
```
RotMatrixY(ang & 0xFFF, &m);
...
func_800484EC((s32)&m, (s32)vec, (s32)vec);
```
They're identical expressions. If I make one of them `&m.w[0]` or `(Blk20 *)((u8 *)&m)` — a different spelling of the same address — cse might not equate them. But the *bytes* would be the same (addiu sp,32). Let me try:
- ad01: `func_800484EC((s32)((u8 *)&m), ...)` — the target's first arg is `(s32)&m` = addiu a0,sp,32. `(s32)((u8*)&m)` is the same address, but cse might treat it as a different expression → remat.
- ad02: `RotMatrixY(ang & 0xFFF, (Blk20 *)((u8 *)&m));`
- ad03: use `&m.w[0]` for one.

Let me test.
