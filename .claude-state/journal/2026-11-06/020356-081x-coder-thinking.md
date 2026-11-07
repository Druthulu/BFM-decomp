---
ts: 2026-11-06T09:03:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_UCXVQ3UkZx7jFwtx8thc
---
The tail of v18's diff shows only the jump address shifts (due to 1 extra insn). The head of the diff (truncated) probably shows the extra store. Let me see the full diff head. dt.sh tail 16 shows the last 16 lines. Let me get more (tail 40) and look at the start.

Actually the diff format shows all differences; the first ones were cut off. Let me run with a bigger tail.
