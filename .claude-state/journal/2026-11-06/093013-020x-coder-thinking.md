---
ts: 2026-11-06T16:30:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Kh98ZwQHhcGeJPzH5rrV
---
We need the TU scratch. The --try --keep produces a scratch dir under .run/P36/engine/score/... which may include t.c. Let me check.

Actually maybe simpler: use the dump on the src TU itself (with the asm). We want to know what target's RTL looked like vs mine. But the src currently has the barrier and matches. I need a candidate dump. The --try scratch may contain the spliced TU. Let me look.
