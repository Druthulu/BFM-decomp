---
ts: 2026-11-06T05:27:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_x3cLxltoULeLDd60Y5mb
---
`note_mem_written` decides invalidation, not deletion.

Hmm, so where are the stores deleted? Let me check `combine`? Or maybe they're not deleted but **moved**? Mine has 42 insns, target 45.

Let me just dump the candidate object for v1 and count `sh` stores vs the target. Then I'll know exactly which stores are missing.
