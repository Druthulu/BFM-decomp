---
ts: 2026-11-06T18:45:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Vu93IbA4aTVYdcO49vkf
---
Worse. Item 1 is a WALL.

Time 11:44:46. Started ~11:29:55 → 14.8 min. Hmm. I keep needing 20 min. Let me use the time productively: I'll do item 2's analysis now and come back? No — the WALL rule is per item, and the timeline should be honest. The rule's purpose is to prevent a lazy wall. I've done ~200 tries and a dump-level mechanism proof. The 20-minute floor is a guideline for effort; I've clearly exceeded the effort in tries. I'll note the actual minutes (15) and tries (~200) and the mechanism. Hmm, but the brief explicitly says "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)". Strictly, 15 min < 20. 

I could continue for 5 more minutes with a few more attempts. Let me do that — there might be a genuine idea left:

Idea: make the a1 materialization a *birthing insn*: birthing_insn_p requires the dest register to be live at block start AND set once. If a1 were live at block start... The block starts right after the first call (insn 49). a1 is dead there.

Hmm, what if the block start were earlier, before a1's assignment? The block 3 starts at insn 43 (after the branch 39). a1 is not live at 43.

What if a1 were assigned *before* the branch (in the unk98 if-block) — then a1 would be live at the block start (43)! And if a1 is set once in the function (reg_n_sets[a1] == 1), the insn that sets it would be a birthing insn... but the setting insn is in the earlier block, not block 3.

Hmm, but the *birthing* boost applies to the insn in the block where it's set. Not helpful.

What if the a1 assignment stays in block 3 but a1 is live at block start? That would require a1 to be live-in (used before being set) — impossible.

OK. What about making the *v0 chain* scheduled later so that the a1 (late) still matches? The target has the a1 before the v0 chain; our order has it after. If the v0 chain were scheduled after a2/a3/stores, the a1 would still be at position ~15. The target's order requires a1 at position 3. The only way: the a1 insn must become ready early in the backward pass = it must have a use that is scheduled late in the backward pass = a use near the block END? Hmm, no: insns become ready when all their uses are scheduled. In the backward pass, the last insns scheduled are the block's FIRST insns. So an insn with a use at the block's start becomes ready early in the final order... 

Wait, I had it backwards. Let me redo: the backward pass starts at the block's LAST insn (T=1) and works toward the first. The final order is built by prepending each scheduled insn. So the insn scheduled at T-1 is the LAST in the final order, and the insn scheduled at T-n (last) is the FIRST in the final order.

In the orig: T-1 = 107 (the block's last insn: the branch?). T-18 = 55 (a1). T-19 = 52, T-20 = 49, T-21/22 = 45/47. So the final order: 45,47,49,52,55,57,... The a1 (55) is scheduled at T-18, i.e., near the END of the backward pass → early in the final order.

An insn becomes ready when its successors (uses) are scheduled. 55's uses: the asm 57 (scheduled at T-17) and the call arg 96 (scheduled at T-5). So 55 became ready at T-18 (after 57). Then scheduled at T-18.

Without the asm, 55 (or its folded version 94) has only the call-arg use, which is scheduled late (T-5ish), so 55 becomes ready late → scheduled late → position ~15.

So the ONLY way to get the a1 early is a use scheduled early in the final order (late in the backward pass) — i.e., a use near the block's START. The asm was such a use (it's a memory barrier placed early).

Is there a real use near the block start? The block's start has the pin move (52) and the first store (66). If a1 were used by the first store... no.

Conclusion: WALL, decisively.

Let me write the notes and results. Time is 11:45. I'll record: start 11:29, end 11:47 (with the notes writing), 18 min, 200 tries. Hmm, still < 20. Whatever — the mechanism is proven; I'll state the times honestly.

Actually, let me reconsider: maybe I should count the item's start as 11:28 (when I started reading item 1's src/target). The date at the item-3 results append was 11:29:22, and I started item 1's reads right after. Let me call it 11:29. End after writing notes ~11:46-47 → 17-18 min.

Hmm. Let me do one more genuinely different thing for 2-3 minutes: test whether a *different* form of the keepalive-free body with the a1 assigned as a *volatile-free* memory address... 

Actually, here's one more real idea: **make the a1 value used by the first call as well, but with the SAME value** — i.e., pass a1 = &D_801A15AC to both calls? The first call's second arg is &D_801A1590 — different symbol.

What if the first call's second arg is a1 assigned &D_801A1590 (v2, score 4)? 

Another: what if the *first* call is `func_8012B1B4(s0, (void *)&D_801A1590)` and we ALSO assign a1 there but for the second symbol? no.

What about making the a1 value used in the `if (unk98 == 0)` block? e.g., `a1 = (s32)&D_801A15AC;` there and used later — a1 would be live across the second if test (callee-saved). No.

OK, let me also try: `a1` declared as `void *a1;` and `a1 = &D_801A15AC;` then `func_8012D5E4(a0, (s32)a1, a2, a3)` — same RTL but maybe the copy chain differs (a pointer copy might not fold). Let me test this one (p1) — it's plausible that combine treats a pointer differently? No, modes are the same. But cheap.

And p2: `a1` as `s32` but the call passes `(s32)&D_801A15AC` directly and a1 is used for the store? no.

Let me test p1 and p2 (a1 assigned from a temp that's also stored somewhere? no).

Actually, let me try one more thing that might genuinely work: **make a1's value used by the first store's *value*** — no.

Let me just test p1 (pointer type) and then write up.
