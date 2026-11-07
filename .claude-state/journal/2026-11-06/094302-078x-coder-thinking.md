---
ts: 2026-11-06T16:43:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_TUOfs5tjw2xRUZ6LmA8n
---
e6 has a bug: `self->unkDC = g | 0x80;` with g never modified — that's equivalent to e5 but g unused after... Actually g is used in the store expression. Fine, but let me not worry.

Run: generate with else=e1, score t1..t7.
