---
ts: 2026-11-06T15:33:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_SnTfjJwUUBurkdvvZA9F
---
Hmm, orig_tu.c has 4 "launder" and 1 "ret = 0;"? The orig.c has 2 asm launders and the TU has other functions' launders. `ret = 0;` appears once — from the `ret = 0;` at the top of the function (line 3175). OK good.

Now the orig RTL dump should have the asm. Let me find the function in the .rtl dump and look at the prologue.
