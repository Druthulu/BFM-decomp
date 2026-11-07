---
ts: 2026-11-06T05:44:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FozP4MzssfAWn5AED4eg
---
The relevant part: `invalidate_memory(&everything)` for CALL_INSN. But there are no calls in this function.

Let me find `invalidate_memory` definition (line ~7541 was `note_mem_written`). Let me look at the invalidate_memory function around line 7620.
