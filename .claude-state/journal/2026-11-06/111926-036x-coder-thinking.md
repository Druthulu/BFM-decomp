---
ts: 2026-11-06T18:19:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_oacJwYlX71odgNp2S00I
---
The preference table for 76 says 4. Since set_preference only fires for a SET with a REG src (or the first element of the src being a REG after 'e' unwrap), the only candidate is `(set (reg 76) (mem (plus (reg 72) 204)))` → unwrap mem → plus → not REG. Hmm.

Unless `expand_preferences` propagates: it merges preferences across allocnos when one is "set from" another: let me read expand_preferences.
