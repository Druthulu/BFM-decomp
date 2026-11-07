---
ts: 2026-11-06T06:07:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_MXkPCmOf2oWJy2KvDlzE
---
pa0 is gone. But the score is still 25 with 67 ins. So the s1 copy persists — maybe it's from something else. Let me look at p1's diff.

Hmm, maybe `s0` itself is copied: the pin removal makes s0 a normal variable, and `move s1,s0` in the prologue suggests gcc copies the argument to a callee-saved reg (s1) because s0 crosses calls. Wait, in n2 the frame had s1 saved and `move s1,s0` — s0 is $16 in the target (pinned); without the pin, gcc uses s1 (its own choice) to hold the argument across calls, and copies a0→s1 in the prologue.

Hmm, but the target also has `move a0,s0`? Let me look at the target asm.

Let me dump the target function.
