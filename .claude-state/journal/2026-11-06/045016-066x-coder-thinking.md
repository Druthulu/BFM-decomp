---
ts: 2026-11-06T11:50:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_l77zV1okoIRBQheGDFOb
---
All score 3. Same residual presumably. The sched1 order is robust.

Let me think about the mechanism: the target computes `srl a2,a1,0x10` at fdc (right after the two loads), mine at fe4 (after two other loads). 

sched1 orders by priority = birth insn number / dependencies. The target's launder is `asm("" : "=r"(wz) : "0"(wz))` — a use of wz that comes after `mny = wy + dy;`. Hmm, that's AFTER the box stores in source. But the launder's presence changes the birth of the srl?

Actually — wait. Maybe it's not the scheduler but the *register allocation* (local-alloc) order: the loads' target registers. In both, a1=zz, v0=xx. Same.

Hmm, so only the position of the srl differs.

Let me look at the sched1 dump. The tools: hdump.sh and cc1_dumps_tu.sh. Let me check what dumps are available for sched. `.run/P40/T10/hdump.sh` is for header pass dumps. `tools/cc1_dumps_tu.sh` + `tools/alloc_table.py` for TU dumps. Let me look at cc1_dumps_tu.sh usage.
