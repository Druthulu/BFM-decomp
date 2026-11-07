---
ts: 2026-11-06T21:38:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_A36KW2ReXvFYNKgG74DL
---
So function is 4053-4148. Extract into orig.c.

Also check the typedef: `Rec20_8017DF18_8017E050` — where is it defined? Probably file-scope earlier in the TU; but the body uses it. Since we're extracting the body only for delever_search --body, the tool compiles the body in place of the src def presumably, so typedef from TU is available.

Let me create orig.c.
