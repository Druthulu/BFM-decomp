---
ts: 2026-11-06T15:48:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ggxfC76tLaxCgRlTEk4y
---
- Removing only the `arg` launder (keeping the 2-output ones): score 4, 346 ins. Small residual (the prologue position).
- Removing only the 2-output launders: score 39, 344 ins (cross-jump lost).

So both are load-bearing. Let me tackle them separately.

First, the arg launder: score 4. Let me see the diff.
