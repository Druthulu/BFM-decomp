---
ts: 2026-10-22T20:22:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_CW9Uv1O3DkNBrS32CNwh
---
I misread: r80 here is a movstr temporary (the 3rd load register), not the address. So the alloc table's r80 row in score-0 is the movstr temp (v0). The address pseudo in score-0 must be a different number. The address uses: let me find `(set (reg:SI NN) (plus:SI (reg:SI 30 $fp) (const_int 16)))` in score-0.
