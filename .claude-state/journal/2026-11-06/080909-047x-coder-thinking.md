---
ts: 2026-11-06T15:09:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_T5fBMxSZ4DuMT9DTVIZb
---
tu_c1.c DOES contain the function at 3105 with `vol = ((0xA0 - av) * 0x7F) / 0xA0;`. My earlier grep `grep -n "vol ="` tail -5 showed lines 3358/3360 — different function (there are two vol users). And the function at 3098-3105 is there. OK so tu_c1.c is valid but is it c1? Let me check line 3107-3113 for the mask.
