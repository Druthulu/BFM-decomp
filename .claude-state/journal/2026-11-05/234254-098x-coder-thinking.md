---
ts: 2026-11-06T06:42:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_J0P69WL9lvvzZW96NNcs
---
A (pins removed only) = 260 (bad, 672 ins).
B (launders removed only) = 47, 671 ins (2 short).

Hmm, B is 2 insns short — the launders' removal lost insns. Let me apply the dead resets and see.

w = B + `mp = 0;` after each of the 9 calls + `m18 = 0;` after RotTransSV.

Let me check the m18/RotTransSV line exists.
