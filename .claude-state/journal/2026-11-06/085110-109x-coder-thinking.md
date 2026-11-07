---
ts: 2026-11-06T15:51:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZA8A7UIWx30MEzMKvyam
---
Both e1 and e2 score 0! The dead-reset on the address temp `a` invalidates cse's value entry for the computed address, so the second call recomputes `mb + 0x18` as an addiu off the base.

Let me verify e1 as win.c, check no asm launder remains (pins? none here), and the diff.
