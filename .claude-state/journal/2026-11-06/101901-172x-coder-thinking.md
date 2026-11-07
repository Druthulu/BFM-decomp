---
ts: 2026-11-06T17:19:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7chlzU1Z4zoA4PG3HmnJ
---
Hmm, i4: the mask used only in the 6 `*ot` statements (m2) and inline elsewhere — still 21 with the mask in t7? Let me check i4's diff to see which register the mask (m2, 6 refs) got.

Actually if it's still 21, the mask is still t7.

Time: 13.4 min. Let me look at i4's diff quickly — maybe the mask register changed but other things broke.
