---
ts: 2026-11-06T05:48:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mrH7Wtdfk89mXXyiaUEt
---
The structload body is clean and semantically equivalent:
- `struct S9 { u16 v; }; struct S9 *sq; sq = (struct S9*)&D_800B9A02;` — reading `sq->v` is the same as `*(u16*)&D_800B9A02`.
- All `*q` uses replaced with `sq->v`.

Note: `extern s16 D_800B9A02;` is a block-scope extern; the struct cast reads the same bytes.

Now check all includers for func_80175820. How many? Let me count and run check_all.py (which is in the item1 dir; let me generalize it — it's a shared helper under my shard; fine to reuse by path).

Let me count includers first.
