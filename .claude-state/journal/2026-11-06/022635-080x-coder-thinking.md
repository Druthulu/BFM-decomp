---
ts: 2026-11-06T09:26:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_XXCXSZAFOSXS2roAy64E
---
Def = 3267..3407. Let me extract and make lever-free win.c: remove pin (ob becomes plain `u8 *ob`) and keepalive (mlo's 6-ref asm). Test.

Note the keepalive in item 3 is `__asm__("" :: "r"(mlo) x6)` — that's the "greg-pri-refs" trick to give mlo refs. Removing it may change mlo's allocation. The pin $10 on ob — removing may change ob's allocation. Let's test.
