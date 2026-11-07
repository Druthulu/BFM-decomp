---
ts: 2026-11-06T11:57:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_laGTRIG82et1jkIgw9DB
---
Wait, there's a bug: in the SH loop, the TAIL already contains the +5 store, and then I add the other sh stores. But the target order after the lbu is: addiu+sb5, sh16, sh12, sh22, sh18, sh14, sh20. My TAIL has the sb5, then V1, V2, then the other sh. Good.

But for y07, SB5 is between the sb6 and the lbu, and TAIL is replaced. OK.

Also, I need to be careful: the `y01.c` I wrote by hand had the intervening store 0x10; my generator starts at y02.

Let me run and score.
