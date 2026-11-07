---
ts: 2026-11-06T16:44:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_MxN3tJVVt6n7m96VtaHD
---
Item 3: pin only (`register s32 v0 __asm__("$2")`). The target uses v0 for various things. Let me run the baseline and the no-pin candidate.

The pin is on `v0` used in the body as a temp. Removing it: global/local-alloc picks a different register. Let's see the score.
