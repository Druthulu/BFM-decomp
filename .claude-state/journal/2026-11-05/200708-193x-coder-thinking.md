---
ts: 2026-11-06T03:07:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_KFYUIO90PI0fjmQV1zNG
---
Score 6, 109 vs 113 ins. The diff: mine has `bgez v0,4bf0` where target has `bltz v0,4bf8`; and target has an extra `beqz v0,4d04; nop; j 4c08; nop` — 4 ins. So the cross-jump merged the two arms' tails, and the branch polarity differs.

This is the classic cross-jump barrier case. The comment says: without the barrier, cross-jump re-merges the two tails (drops 2 ins and swaps which arm is target vs fallthrough).

Wait, the target has 4 more insns than mine. Let me look at the target asm around the two arms to understand.

The barrier is placed in the *else* arm after `if (d > 0x200) goto TAIL;`. The two arms:
```
if (d >= 0) {
    if (d > 0x200) goto TAIL;
} else {
    d = buf1 - unkA;
    if (d > 0x200) goto TAIL;
    /* barrier */
}
```
Both arms end with `if (d > 0x200) goto TAIL;`. The cross-jump merges the identical tails (the slti/beqz to TAIL). The barrier prevents that.

Real-C moves to prevent the merge (from the earlier research):
- Different polarity in the two arms: write the second as `if (d <= 0x200) { } else goto TAIL;`? Hmm.
- The cookbook §162/§5a note: "the fix is polarity, not a barrier" (from the ov_SC03_099 example): write the two arms with different polarity so the tails differ textually.

Let me look at the target asm first.
