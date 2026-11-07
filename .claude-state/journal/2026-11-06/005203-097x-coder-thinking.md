---
ts: 2026-11-06T07:52:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZodJ9ES2hZYTZ7v65Zob
---
The script printed the whole TU, not the body, because `dl.recipe_candidates` returns the full TU text (it operates on the TU, not the body). I need to extract the function from the text. Let me modify the script to print only the function's definition from the resulting text (using body_span). Let me update the script to slice the fn span.
