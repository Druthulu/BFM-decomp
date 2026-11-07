---
ts: 2026-11-06T05:48:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_f6BWaR2UiacsieIxegke
---
This generator has some sketchy bits (idxlocal construction, p_u32 = body). Let me clean it: 'p_u32' is just base; 'ptrstore' is base. Let me not include duplicates. Also the idxlocal logic is convoluted. Let me simplify by writing the variants explicitly per item via targeted replacements.

Actually, let me just run it and see the scores; wrong ones will fail to compile. But the compile failures waste tries. Let me first test on func_80175820.

Also note: the struct-member declaration inside a function: `struct S9 { u16 v; };` then `struct S9 *sq;` — legal in C89? Declaring a struct type inside a function is legal. Fine.

But `sq = (struct S9 *)&D_800B9A02;` — D_800B9A02 is `s16`, taking its address and casting to struct S9* — fine.

Let me run and score for 75820.
