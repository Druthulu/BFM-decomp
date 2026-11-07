---
ts: 2026-11-06T11:45:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1fFzG3AzNoCvrS84LljO
---
Line 7110: `else if (do_not_record)` — if the *destination* is volatile, invalidate it and do no further processing. Hmm, that's for the dest.

Let me look at the store-elimination for MEM dest: search around line 7000 for "GET_CODE (dest) == MEM".

Actually, let me look at the code just before 7095 — the part that decides to delete the insn when the source equals the destination's known value.
