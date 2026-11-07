---
ts: 2026-11-06T23:44:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_UmWSa00EVS1cvJb3bb9z
---
Let me look at the item dirs contents (fn, tu files) and the helper scripts.

Note the moves with launder,pin MATCH: several. Relevant ones:
- launder,pin | func_8017F584 | MATCH — field post-decrement per arm
- launder,pin | func_80180E40 | MATCH — pin redundant; u16 var_s4 + (u16)(var_s4 - 0x1000) < 0x11 keeps the andi
- launder,pin | func_80165CA0 | MATCH — s32 t = p[0x16]|1 temp
- launder,pin | func_80186368 | MATCH
- launder,pin | func_8001BBBC | WALL sched1-birth-boost
- launder,pin | func_8017CF48 | WALL cse-const-addr

Let me look at the items.
