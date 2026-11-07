---
ts: 2026-11-06T06:39:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6FRZwGby6k35duFkb6vv
---
There are 9 `mp = D_801CC7CC;` sites (3 in case 6, 3 in case 7, 3 at the tail). Each is followed by a call passing `mp`.

The target rematerializes `lui a1; addiu a1` per site (no callee-saved register). Without the launders, gcc hoists into s2.

Let me test:
c1: remove `mp = D_801CC7CC;` lines and pass `D_801CC7CC` directly in the calls.
c2: keep `mp = D_801CC7CC;` and add `mp = 0;` after each call.

Note c1 changes the source semantics? No — passing the same address directly is equivalent.

Let me also consider: maybe `(u8 *)D_801CC7CC` needs a cast. D_801CC7CC is presumably `u8 *` or an array. In the source `mp = D_801CC7CC;` where mp is `u8 *`. So D_801CC7CC is likely declared `u8 D_801CC7CC[]` or similar. Let me check the declaration in the TU. Actually, the body compiles with `extern` from the TU. In the body, D_801CC7CC is used without an extern declaration — so it comes from the TU. Let me just try.

Let me generate c1 and c2 and score.
