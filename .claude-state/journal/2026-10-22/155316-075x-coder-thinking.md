---
ts: 2026-10-22T21:53:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_uSUtxo5VbfW5UmxRmCY9
---
e1 scores 0 with 23 ins! The dead-reset variant works here too.

Let me check the full listing and run all includers.

Note e1 keeps the block and adds `void *q2;` declared inside the block, `q = 0;`, `q2 = &sp18;`.

Hmm, one consideration: is `q = 0; q2 = &sp18;` acceptable as a crack (vs "identity address spelling")? It's the §373 dead-reset (documented MATCH in G15). Good.

Let me verify + all includers.
