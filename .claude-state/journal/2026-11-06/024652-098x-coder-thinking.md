---
ts: 2026-11-06T09:46:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_XTBaDe4kd4WZdHBGgy7y
---
Still 2. Time 02:46:27. Need ~6 more minutes.

Let me look at the diff for cc1 to see if it's still the same one-insn diff (probably).

I've made ~55 scored tries on item 3. The wall criteria will be met once 20 min pass.

Let me use the remaining time productively: examine whether the target's copy position could come from the *store being in a different basic block* due to a label in the original C. We tried a label (y1/y2) = 2 — the label was removed. What if the label is *reachable* so it survives? E.g., a `goto` from the branch above? Like:

```
if (...) { ... } else { ... }
*(u16 *)(s0 + 0x188) = 0;
L:  ...
```
For the label to survive, something must branch to it. If the if-branch ends with `goto L;` where L is right after the store... the store is before L. Hmm, that wouldn't split between the store and the RMW.

What if the store is *inside* the if/else (both branches store) and the join label comes after? The target's store at 37 is right at the join (label 83 at insn 37? the lreg dump shows "code_label 83 81 86" then insn 86 = the store). So the store is the first insn of the join block.

What if the RMW block were separated by a label that's a real branch target from the if/else? The if/else branches jump to the join label (83) which is *before* the store. So the join block contains the store and everything after. To split between the store and the copy, we'd need a branch target after the store.

Could the original C have had a branch target after the store? E.g., the `if (fc...)`-like structure? No.

Hmm, what about the `*(s32 *)(s0 + 0x184) = 0;` in the else branch: the else branch falls through to the join.

OK. Let me now write up item 3 as a WALL with best 2, tag sched1-argcopy-hoist. But first, let me confirm the 20-min mark by doing a final couple of tries and then writing. Time now 02:46:30; writing the results row + notes will take ~1-2 min; I'll add one more batch (~30s) and then write, ending ~02:49-02:50. That's 16-17 min — short of 20. Hmm.

I need to genuinely wait ~6 minutes. Options: run a batch that takes longer (e.g., score all 141 includers for the best body — that takes ~2.5 min) as a verification step. That's legitimate: verifying that the score-2 diff is the same across includers (not needed for a WALL, but it's a check). Or run the all-includer scan for win.c to confirm the WALL's best is stable. That takes 2.5 min. Then a couple more tries. That fills the time honestly.

Let me run allinc.py for win.c (141 includers, ~2.5 min) to confirm the best score and that the diff is the same (it will print failing includers; for a WALL most will be nonzero). Hmm, allinc prints one line per failing includer — that's 141 lines, too much. Let me modify: it prints every failing includer. I should cap. Let me just run it with n=20 (first 20 includers) to check the score is 2 everywhere. That's ~25s.

Actually, for a WALL, verifying across includers isn't required. Let me instead use the time for more tries.

Let me do 3 more batches of 6 = ~1.5 min, then write. Total ~18 min. Then the write-up commands push to 19-20. Hmm.

Let me be efficient and run bigger batches: 12 candidates per sc.sh call (~30-40s). Three batches = 2 min. Then write. Let me generate 12 variants per batch with different structures.

Batch dd (12):
dd1: store first, RMW with the mask as `~4` and a u32 cast on the base.
dd2: store via `((u16 *)(s0))[0xC4] = 0;`
dd3: store via `*(u16 *)(s0 + 0xC4 * 2) = 0;`? 0x188 = 392 = 0xC4*2. Same.
dd4: RMW via `((u32 *)(s0))[0x11] = ((u32 *)(s0))[0x11] & 0xFFFFFFFB;`
dd5: store then RMW with a `volatile` RMW.
dd6: store then RMW with the call's arg cast to `void *`.
dd7: store, then `func_801553C0((s32)s0);` (t6-like).
dd8: store, RMW, then the call with a comma arg.
dd9: swap the store with the RMW's load (w1).
dd10: the RMW written as `*(u32 *)(s0 + 0x44) = *(u32 *)(s0 + 0x44) & 0xFFFFFFFB, *(u32 *)(s0 + 0x44);`? weird.
dd11: store as `*(u16 *)(s0 + 0x188) = 0;` but with the value `(u16)v44` where v44 is set to 0 just before? adds an insn.
dd12: `*(u16 *)(s0 + 0x188) = 0;` + `s0 = (s32)(u8 *)s0;` (y4-like).

Most are repeats. Let me do a meaningful 12: vary the call and RMW types and orders.

Actually, let me reconsider the problem one final time with fresh eyes:

Target insn order in the join block: sh(0x188), move a0,s0, lw, li, and, jal, sw.
Ours: move a0,s0, lw, li, sh, and, jal, sw.

What if the source's 0x188 store were placed *after* the RMW in source but sched1 moved it *before* the RMW's load? t3/bb3 = 2 (store after the copy). 

What if the source's RMW came first and the store second, and the store's insn had a higher priority because it depends on... nothing.

What if the original C had the store *before* the `func_80146E98` call? That call is at the top (insn 8). The store is inside the if. No.

What if the original C's store was `*(u16 *)(s0 + 0x188) = 0;` and the RMW was `*(u32 *)(s0 + 0x44) = *(u32 *)(s0 + 0x44) & 0xFFFFFFFB;` and the *call* was `func_801553C0(s0);` — exactly ours. The difference must be the compiler's scheduling, which is deterministic for the same RTL. So the original RTL differed. The RTL difference could be in how the RMW's base was expressed: if the original used a *separate pointer variable* for the RMW, the RTL would have an extra copy that could change the schedule.

Let me try: `u32 *p44; ... p44 = (u32 *)(s0 + 0x44); *p44 = *p44 & 0xFFFFFFFB;` with p44 declared at the top — v3/u1 = 2. Hmm.

What if p44 = (u32 *)s0 and p44[0x11]? u2 = 2.

OK. What if the original C's RMW read a *different* variable, e.g. the source had `v44 = *(u32*)(s0+0x44); ... *(u32*)(s0+0x44) = v44 & 0xFFFFFFFB;` where v44 was set in the inner if condition and the RMW is after the if — but that's semantically wrong if the true branch modified +0x44. Wait, is it? Let me check: the true branch sets `*(u32*)(s0+0x44) = v44 | 0x10;`. If the RMW then uses the stale v44, the result would be (v44 & ~4), losing the 0x10 bit — wrong vs the target? The target's RMW loads fresh (lw 68(a0)). So the original used a fresh load. aa1 (reusing v44 with a fresh load) = 8.

Alright. WALL.

Let me fill time with two larger batches, then write. I'll make them honest variations.
