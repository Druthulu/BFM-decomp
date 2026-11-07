---
ts: 2026-11-06T16:36:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1CJqnDrw7UzAqKe353df
---
I can run mipsel-linux-gnu-objdump. Let me get the object with --keep for f01 and objdump the function.

Actually simpler: use tools/cc1_dumps_tu.sh? That dumps cc1 passes for a TU, not for a candidate.

Let me do --keep and objdump -dr the candidate object, filtered to the function. The --keep output prints the object path.
