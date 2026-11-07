---
ts: 2026-11-06T07:52:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_s1ryGnvQqmBYEEwtCVm1
---
Wait, body_span returns line numbers relative to the text. But the text lines are absolute. Slicing by line numbers needs line starts. Let me just print the function via a simpler regex extraction. Let me use the extract logic inline: find the def line and brace match. Let me rewrite that part.
