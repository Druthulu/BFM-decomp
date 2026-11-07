---
ts: 2026-11-06T04:44:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_MaoEqLclwXFlzkr7gGRm
---
b3: the do-while makes the pointer p get copied to v1 (move v1,a0) because... the loop creates a new scope where p is used, and maybe p must be in a callee-saved? No, v1. Why does p become v1? Because do-while creates a loop; loop.c might think... Actually the move v1,a0 then uses v1 — p (u8*) got copied into v1. Interesting: the schedule is otherwise perfect (sb v0, then lbu v0,1). Score 6 = 4 register-pair mismatches + 1 extra insn (move).

If we avoid the copy, we'd match. The copy appears because in a loop body, the variable p is a loop-invariant? Actually do{}while(0) at -O2 gcc might treat as a loop for a while and then delete the loop note, but local-alloc may have assigned p to a call-clobbered... Hmm, why copy a0 to v1 at all? Possibly because within the "loop", p is not modified, but the store `p[0]=v0` could modify memory; the compiler might reload p? No.

Maybe because p is used in multiple basic blocks (the loop creates a join at end), so it's not a "local" pseudo and gets global alloc into v1 with a copy from a0. If instead we don't have the do-while around each but something else...

Alternatively, maybe put all three in ONE do-while(0)? Then one copy. Or use a0 directly instead of p (no pointer variable): `*(u8*)a0` etc. Then no copy needed.

Let's try: one do-while(0) wrapping all three, and direct a0 indexing. Also try per-statement do-while with direct a0.

Also, the target uses a0 directly (no copy). Let's write b4: direct a0 with casts, three do-while.

Actually the original orig.c uses p = a0 and with the barrier no copy happened (score 0). So barrier doesn't cause copy. The do-while causes it. Maybe use a `for` loop? Or a `while(0)`? A `while(0)` body is dead and removed.

Hmm, maybe instead of do-while, use `if (1) { ... }`? An if(1) creates a block but no loop; gcc folds it away early (no EBB split). What about `if (v0 >= 0) {} ...` no.

Let me try:
- b4: three do-while, but use a0 directly.
- b5: single do-while around all three, p pointer.
- b6: three do-while, pointer declared inside each.
- b7: `do { ... } while (0)` with `volatile`? no.

Also maybe the copy is from the loop's requirement that p be live across the "loop back edge"; global-alloc gives it a register (v1) and inserts move at entry. If the pointer is not live across the back edge... it is used inside. Hmm.

Alternative: use a0 directly in the do-while body — then a0 is a parameter (already in a register, fixed). The copy would be unnecessary.

Let's test.
