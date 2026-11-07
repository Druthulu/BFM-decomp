---
ts: 2026-11-06T05:48:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_YPrkLtvgaiIvaDUxYoSB
---
HUGE: `v_structload.c` scores 0 on the first includer! The struct-member load trick cracked the cse wall AND the frame (55 insns matches).

Let me verify: score 0 on the first includer. Now I must check all includers (how many for func_80175820?). Let me count includers and run check_all.

But first, let me look at the v_structload.c body and check semantics:
- `struct S9 { u16 v; }; struct S9 *sq; sq = (struct S9 *)&D_800B9A02;`
- `*q` replaced by `sq->v` everywhere.
- The original `q = (u16 *)&(*(u16 *)&D_800B9A02);` and `u16 *q;` removed.

Semantics: `*q` reads D_800B9A02 as u16. `sq->v` reads the same u16. ✓. And the load is a struct member → in_struct → cse invalidates after the nonscalar store → reload. And the frame becomes 16? Score 0 means byte-identical, so yes!

Let me confirm the full body and then run all includers.

Let me view v_structload.c.
