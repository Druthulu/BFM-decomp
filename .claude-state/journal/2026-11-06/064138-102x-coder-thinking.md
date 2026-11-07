---
ts: 2026-11-06T13:41:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_nxPpl8M7bqNrJwlYWooT
---
w_b2 (B2 removed, B1 present): score 19, differences:
1. index 198-199: `move v1,zero` placement — mine has it as the delay slot of the bne, target doesn't (it's later?).
2. index 204-209: store/load ordering (sw v0,28(s0) vs the load).
3. index 278: a missing `move v1,zero`.

The `move v1,zero` relates to `k = 0x1000`? No — v1=0. Hmm, `move v1,zero` is `var = 0`? In the case 3 code: `var = ((((Unkstruct_800B5CB8 *)param_1)->unk1C - 5) << 12) / ...`? No. Let me find where `move v1,zero` appears in the target. Hmm, could be `((Unkstruct_800B5CB8 *)param_1)->unk34 = 0;` in case 3 (line 150).

Actually, the diff at 278 "insert target[279:280] move v1,zero" means the target has an extra move v1,zero that mine lacks. And at 198 mine has it in the bne delay slot while target doesn't.

Let me look at the source around the case 2 B2 block and the case 3 block.

Let me view the source lines 80-160.
