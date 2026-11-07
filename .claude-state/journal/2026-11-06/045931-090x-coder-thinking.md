---
ts: 2026-11-06T11:59:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ifSU43OGGIcXRIf0Opzb
---
v_two_s8 = score 4 (ORDER, 44 ins)! Big improvement. `s8 two` changed the allocation such that the register swap is fixed, leaving only the store order (sched-store-sink). Let me look at the diff.

s8 two: `s8 two; two = 2; a0->unk2 = two;`. The QImode value 2 stored to unk2 (a u16 field?). `unk2` is a u16 (from the struct). Assigning s8 two to u16 unk2 → zero/sign extend? Hmm, but it matched better.

Let me see the diff.
