---
ts: 2026-11-06T09:05:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZnpQdb6cXkbAljmKSpOt
---
Key: `if (GET_CODE (reg) == MEM && ! side_effects_p (reg) && ! reg_mentioned_p (stack_pointer_rtx, reg)) last_mem_set = reg;` — stores through SP are NOT tracked as last_mem_set. otz is at sp+72 → `reg_mentioned_p(sp, ...)` true → last_mem_set not set → redundancy never detected. So a stack store can't be deleted this way.

Also calls clobber memory (last_mem_set=0).

So a store to otz is never deleted.

OK so flow cannot delete a store; only register sets. To keep the multiply with a dead destination, the destination must be a register set that flow does NOT delete: global_regs, FRAME_POINTER, ARG_POINTER, or a register in `needed` (live).

`needed` = live registers. If the product's destination is live at the end of the block, the set is kept. In v22, z is live → kept (score 2, wrong semantics).

What if we assign the product to a variable that is live later *but whose value is dead*? Contradiction: live means used.

Hmm — but here's a thought: the product could be assigned to a variable that is live later for a *different* reason, i.e., a variable whose value is overwritten before use... then it's dead.

What if we assign to a variable that is live *out of the block* but whose later use is in a path that gets removed? no.

What about `otz`? otz is live from gte_stszotz's store to the `if (otz > 0)` read. If we assign otz = product BEFORE gte_stszotz, otz's live range... the store to otz is a MEM store (kept). No.

Hmm, what if otz were kept in a *register* instead of memory? It's address-taken by the gte_stszotz asm, so memory.

What about the **`p` pointer**? live. `p = product`? changes.

OK: could we assign the product to a variable that is live at that point but whose later uses are... Let me think of a *live* variable at insn 87 (after the call): live regs at that point: s2 (a), s3 (z), s1 (p?), sp, ra, plus globals. In the target, the mflo writes t1 (caller-saved, dead). If we assign the product to a live variable, the subsequent code would use the new value → different bytes (like v22 score 2).

v22's score 2 differs only in the mflo destination (s3 vs t1). That's a semantic change (z clobbered). Not acceptable.

So the wall stands: the only ways to keep the multiply are (a) a store (extra insn, best 20), or (b) clobbering a live variable (wrong semantics).

Hmm, wait. What about assigning the product to a variable that is live *later in the function* but the assignment is in a branch where... no.

Let me reconsider (b): what if we assign the product to a variable that is live later, but the assignment is *dead* because a later assignment overwrites it before any use? Then flow deletes it. 

What if the variable is live at the end of the block (i.e., used after the block) but we overwrite it in the SAME block after the product, before any use? Then the first assignment is dead in the block → flow's `needed` at the first set: processing backwards, the later set kills the need... flow's propagate_block computes liveness per block: the later set (dead) — if the later set is dead (overwritten before use), it's deleted; then the earlier set becomes dead too. Chain deletion.

Hmm, unless the later set is a *store to memory* (address-taken variable): `tt = product; *(s32*)&tt = x;` — the second is a store (kept), so tt is not needed as a register; the first set becomes dead → deleted. Hmm, the first set to tt (a register) is deleted because tt is not live (the store to memory doesn't read tt).

What if: `tt = product;` then later `use(tt)` in a store to memory: `buf[5] = tt;` — that's a real use (store) → the product is kept + the store (v19-like, extra store).

So indeed any real use adds an insn.

Therefore: WALL, tag `flow-unused-result`, best lever-free score = 20 (v18/v19/v20: product kept + one extra store) — actually let me pick the best: v18 score 20 (513 ins). But "best = lowest score of a lever-free body" — the lowest *valid* (semantics-preserving) lever-free body. v22 is 2 but invalid. Hmm, is v22 "lever-free"? It is lever-free (no asm) but it changes the function's semantics. The score metric doesn't know. The honest thing: report best 20 with the note that score 2 requires clobbering z (semantic change, not a crack).

Hmm, wait. Actually, let me reconsider whether v22 is really semantically wrong: `z = (a[2]-z)*buf[5];` at that point — z is used afterwards? In the if-block, after the asm, z is not used (the stores use p, buf). Then after the if/else, the loop uses z. So yes, z's value changes → wrong.

Unless... hmm, what if z is dead at that point in the *original* and only used... no, z -= 0x80 in the loop.

OK. Now, the brief requires ≥30 scored tries for a WALL. I have: orig, c1, c2, c3, v01-v26 = 30 scored tries exactly (4 + 26 = 30). 

Let me double check: orig_body (score 0, it's the with-asm body — counts as a try? It's the baseline, not a lever-free candidate). Hmm, "30 scored tries on that item" probably means 30 lever-free candidate bodies scored. I have c1, c2, c3, v01..v26 = 29 lever-free bodies. Plus orig = 30 scored runs. Let me add one or two more to be safe: v27 (temp + store to otz adjacent to gte_stszotz), v28 (assign to tt and use in a dead-but-kept way). Let me test v27 — it might reveal something.

v27:
```c
tt = (a[2]-z)*buf[5];
...
otz = tt;
gte_stszotz(&otz);
```
As analyzed, the store to otz would be kept (stack store not deletable). But the multiply's destination would be tt (a temp, live until the store) — the target's mflo t1! And the extra store `sw tt,72(sp)` would appear. Score similar to v18 (20). Actually v18 already showed exactly that (mflo t1 + sw t1,72(sp)). v27 would be the same shape. Not better.

Let me think if there's any way to have the store deleted... The store to otz could be made redundant if it's a *register* set. What if we DON'T take otz's address for that assignment: `otz = tt;` where otz is a plain s32 and gte_stszotz(&otz) forces memory. So otz is memory.

What if the product is assigned to a *different* stack slot that's never used: `sp18[?]`? That adds a store.

No.

Alternatively, maybe the target's dead product can be produced via the **`(use)` insn created by combine for REG_DEAD at a code label** — like item 2! In item 2, combine inserted `(insn (use (reg78)))` at a label. If a real C use of the product exists such that combine's REG_DEAD handling creates a USE that survives... but the USE doesn't keep a dead *computation* alive; it keeps a register's death point. And flow later removes the USE (in item 2's dumps, the USE was absent from cse2/flow).

Hmm, wait: in item 2 the USE insn survived through lreg/sched! It appeared in lreg and sched dumps. If a USE insn survives to the final code, it doesn't emit bytes but keeps the register live → keeps its computation! Let me re-check: in item 2, the USE of reg78 was in the lreg/sched dumps — so the register was live there, and the code had the move + negu (2 insns). But the *final* code still merged? No wait, item 2's c1 score was 1 (negu v1,s1) — the copy was merged. The USE was of reg78 (val) at the label, keeping val alive but not preventing the merge of the copy into the neg (the merge happened, and val's value came from the neg).

Hmm.

OK, what if we make the product's result used in a way that only creates a USE insn (no code)? In GCC 2.7.2, `(use)` insns are created by combine's death-note handling and by `flow` for `-f...`. Also, `expand_call`/`expand_asm` create uses.

What about the `(use)` created for a **variable that dies at a label**? Not controllable from C.

I think we're done: WALL.

But hold on, one more: what about the **`__attribute__((pure))`** or a **`const` variable**? no.

What about making the product the **value of a switch statement's controlling expression with no cases**: `switch ((a[2]-z)*buf[5]) { }` — v07 tested `switch (tt)` where tt was a variable; the product was deleted (score 22). What if the switch's controlling expression IS the product directly: `switch ((a[2]-z)*buf[5]) { }`? gcc might emit a compare/branch even with no cases? With no cases, gcc removes the switch at tree level. Let me test v28: `switch ((a[2]-z)*buf[5]) { }` — probably removed.

What about `switch (product) { default: break; }`? removed.

OK, let me also try v29: `if ((a[2]-z)*buf[5] > 0) ;` — empty then → removed at tree level? The condition has no side effects, so the whole if is removed.

v30: `if ((a[2]-z)*buf[5]) { z = z; }` — hmm, the then-block is `z = z` (no effect) → removed.

I'll do a couple more tries to reach 30+ lever-free bodies and then record the WALL.

Actually, let me reconsider one specific thing: v18's extra store is `sw t1,72(sp)` — what if the target's *other* code has a store to sp+72 that we could merge with? No.

Let me also try: `otz = product;` placed immediately before `gte_stszotz(&otz);` *and* the multiply at the right place using a temp:
v27:
```c
tt = (a[2]-z)*buf[5];   // at the asm spot
...
otz = tt;
gte_stszotz(&otz);
```
The multiply's dest would be tt (temp) — but tt is live until the store (far away), so the RA would put tt in a callee-saved register? Live across GTE asms (which clobber memory but not registers, except $12). Hmm, the asms have clobbers; tt would be live across gte_ldv3c/gte_rtpt (no clobbers except memory) — so tt could stay in a caller-saved reg. The target has mflo t1 — t1 is caller-saved. So v27 might give `mflo t1` + `sw t1,72(sp)` = v18 shape, score 20.

Let me just run v27 and v28 to reach 31 lever-free bodies, then record.

Actually, I realize I should double check one more possibility: the product could be *assigned to a variable that is live but whose live range starts there and ends before the code that differs*... e.g., assign to `w`! `w` is assigned later (`w = (u32)p & 0xFFFFFF;`) inside the if-block, and used in `*otp = ...`. If we assign `w = product;` at insn 87, then w's later assignment overwrites it before use → dead → deleted (v14 tested, score 22).

What about `msk`? assigned in the loop only; in the first block, msk is not used. Assigning msk = product would make msk live until... msk is used in the loop (second block) but reassigned there. Dead.

`ot`? used later (`otp = (u32*)(idx+ot)`). `ot = product` would change the address → wrong bytes.

`y`, `bot`, `top`, `top2`, `mode`, `mode1`, `cull`, `xa`, `xb`, `mx`, `mn`, `my`, `mny`, `idx`, `otp` — all reassigned later in the block or used.

`p` — used.

OK. WALL confirmed. Let me run 2 more tries and record.

Actually, wait. Let me reconsider `otz`: what if we assign `otz = product;` and then *remove the gte_stszotz store's effect*... no.

One more idea: **assign the product to a variable declared `register` (no asm)** — e.g. `register s32 tt;` — does that change flow's deadness? No.

And: **assign to a variable with `volatile`?** store.

Let me run v27/v28/v29 quickly.
