---
ts: 2026-10-22T08:40:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_Zi2o9BH6I3twei1Pum9g
---
There's an alloc_table tool that reads gcc's .greg dump. That's the key tool for understanding the global allocation.

But it needs a dump of the TU. cc1_dumps_tu.sh takes a work dir containing <fn>/t.c or a .c file. I need a copy of the TU with my candidate body. Let me see how the delever tool builds the candidate TU (the --keep path may include the .i/.c). Let me look at the scratch dir .run/P36/engine/score/ov_SC05_018__func_801815AC/p3/.

Careful: that's a shared scratch dir (P36 engine) — reading is fine.

Let me list it.
