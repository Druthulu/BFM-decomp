---
ts: 2026-11-06T13:19:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1csley4riTeX2w8D2AUX
---
COMPILE-ERROR for the first 11 — probably the `do { ... } while (0)` on a statement with `goto`? No, the error is truncated. Also v01 temp has braces inside the case — should compile. Let me see the actual error for v01.

The error message got cut at 120 chars by sc.sh's cut. Let me run dt.sh on v01 to see the error.
