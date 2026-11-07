---
ts: 2026-11-06T12:28:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vZJwhlF13SyYeojc6czE
---
Oops — I put a literal `\t` inside a single-quoted printf format? I used single quotes around the whole string with \t escapes — printf interprets \t in the format string. Yes, the format string is the first argument; printf interprets backslash escapes in the format. But the arguments after that... I used the whole row as the FORMAT (no %s), so \t is interpreted. Good.

But wait — the evidence contains `;` and `$` — `$a2` inside a single-quoted string is fine for the shell, and printf format only interprets % and backslashes. `$a2` is fine. However `%` isn't present. OK.

Let me verify the row has tabs.
