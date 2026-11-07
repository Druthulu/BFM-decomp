---
ts: 2026-11-06T14:25:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_G9eMyLtlvsZKReVJp6Au
---
In b2's pre-flow RTL: insn 307 = src (161), 313 = dst (162), 316 = i (160). So i=0 IS after src and dst, as the C order. So i's birth is at insn 316 instead of 307. Yet the live_length is still 39!

So flow's live_length for i is 39 in both. That means the live_length computation doesn't simply count from birth. Let me think: maybe i is live at the START of block 13? No, i is not live before i=0.

Hmm, wait: maybe flow's `reg_live_length` counts the number of insns where the reg is live, and for a register that's live across a loop, the counting includes the loop body once per pass. Moving i=0 by 9 insns (307->316) should reduce live by 9. But it's the same. That's bizarre.

Unless the live_length for i is dominated by something else. Let me look at the actual live_length for i in b2 vs c1 — both 39. Hmm.

OH WAIT. Maybe the "across N insns" in the dump is NOT reg_live_length but reg_n_deaths or something else? Let me check the print format at flow.c:2885-2890.
