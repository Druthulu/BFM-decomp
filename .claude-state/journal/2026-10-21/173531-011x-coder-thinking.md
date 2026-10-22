---
ts: 2026-10-21T23:35:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_ct9N3HEmOnXIjMWJslkk
---
So the prior run created `nopin.c` for every item (a lever-free candidate?) but only scored items 1 and 2.

Now let me look at the actual source. Read src/shared/ov/func_8014C308.h and the nopin.c.

Also I need to understand delever_search.py --try semantics and how the score is computed, plus how header items are handled (tryinc.py for includers).

Let me check the src header first.
