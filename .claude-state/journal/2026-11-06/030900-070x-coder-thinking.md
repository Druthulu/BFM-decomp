---
ts: 2026-11-06T10:09:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mQZ4U785LVRzH2hsQbhS
---
Very informative!

- p1 (pin removed, keepalive kept): score 38 — so removing the pin causes the register swap (big diff).
- p2 (pin kept, keepalive removed): score 2 (ORDER) — just an ordering diff! So the keepalive is only needed for a 2-score ordering issue.

So the register swap is entirely due to the PIN. The keepalive is a separate scheduling fix (score 2).

So the task decomposes:
1. Replace the pin with a real C lever to get d→s0 (hard: local-alloc).
2. Replace the keepalive with a real C lever to fix the ordering (score 2).

Let me first solve the ordering (keepalive replacement) since p2 shows it's just ORDER. Let me see the p2 residual.
