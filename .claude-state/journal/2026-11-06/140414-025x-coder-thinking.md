---
ts: 2026-11-06T21:04:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_3XdsZgIzJvSJVSMeK4ja
---
The rtl dump has the function twice? Lines 24 and 164 — probably two passes concatenated? Actually .rtl dumps at multiple points (the -dr flag prints after each pass?). Hmm, or there are two functions (the TU includes func_80148AFC too? No, min TU has only the one body). Actually -dr prints RTL after each pass to the same file, so the function appears multiple times. Line 46 and 391 might be different passes.

Let me look at the relevant snippet around line 46-80.
