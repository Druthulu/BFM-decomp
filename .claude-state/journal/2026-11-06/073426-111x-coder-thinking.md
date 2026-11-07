---
ts: 2026-11-06T14:34:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xotvGthFCOKeJILmocsk
---
v2 (a1 before a0) still has the same diff. So sched1 reordered the a0/a1 anyway.

Let me set up a scratch TU to dump c1's sched. I need _tu/shared/engine_prelude.h and _tu/ov_SC04_004/t.c. The include "../shared/engine_prelude.h" resolves from _tu/ov_SC04_004 -> _tu/shared. And "common.h" via -Iinclude. Let me set up and use mk_tu.py (which I deleted; let me rewrite it).

Actually, I can just copy the TU and apply the c1 transformation textually with a Python script (replace the function body). Let me recreate mk_tu.py.

Let me do it and dump c1's sched.
