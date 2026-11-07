---
ts: 2026-11-06T22:08:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zyhJDuz5rcYGqws5HxBW
---
x1 residual: tmp in a3 ($7) vs target v0 ($2), plus the branch offsets (4-byte shift from the missing li). The pairs: a3->v0 x16, v0->v1 x4. So tmp is a3 instead of v0, and some v0→v1.

The missing `li a3,6` again (insert at 363): target has an extra li because tmp pinned materializes the constant twice.

So removing the tmp pin causes:
1. tmp lands in a3 instead of v0.
2. One insn merged (the double `tmp=6`).

Both stem from tmp's pin. To crack tmp lever-free, we need tmp in v0 AND the double li.

tmp in v0: tmp is a short-lived value; v0 is the natural first scratch. Why does it get a3? Because other qtys in the block take v0,v1,a0,a1,a2 first. In the target, tmp=v0.

This is the same wall class. But maybe a move can help: e.g., make tmp the *result of a call* (calls return in v0) — no.

Or declare tmp as `s16`/`u16`? That changes the shift semantics.

Hmm, what about the constant materialization: `tmp = 6;` then later `tmp = 0x96;` etc. The target's extra `li a3,6` suggests tmp=6 is materialized in two paths. Lever-free merges.

I think these are all walls. Let me record item 4 as WALL best 31 (v33, invalid) — or should I pursue PARTIAL:pin? The PARTIAL:pin requires score 0 keeping the dst pin. x1=38; can moves crack it? Probably same difficulty as the full lever-free.

Let me spend a few tries on x1 with tmp variants (keeping dst pin):
- tmp u32/s16/u16/long/int
- tmp = (s32) casts
- reorder the tmp blocks

Quick test: 7 type variants on x1. If any hits 0, that's PARTIAL:pin and better.

Let me do it.
