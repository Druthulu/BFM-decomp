---
ts: 2026-11-06T16:45:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZJWl2VqV2jieeJDniDiP
---
Interesting:
- no_ot: score 8 (265 ins) — ot pin alone costs 8.
- no_fp: 47 (268 ins) — fp pin is the big one.
- no_t0c: 5 (264 ins, one insn short).

All three removed: 52.

Let's look at each residual. Start with no_t0c (score 5, 264 vs 265 — one instruction missing). Then no_ot (8). Then fp.

Let's see no_t0c diff.
