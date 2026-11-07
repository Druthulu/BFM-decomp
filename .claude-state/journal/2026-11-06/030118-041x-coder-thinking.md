---
ts: 2026-11-06T10:01:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QE6h9qwa2ay5801VmVxF
---
v3 reorders: loads first (lw v1,76; lw a1,84) then stores later. That's sched1 grouping the loads. Target keeps store between. So direct stores let sched1 hoist both loads. The temps t/tb forced the store after each load (because t is used immediately).

Hmm. So the temp form is needed for ordering. And with temps, t=v1, tb=v0 (swapped from target).

What determines v0 vs v1 for t and tb? Let me get the local-alloc dump to see qty priorities. This is worth it: a 7-score function is close.

Let me splice the TU and dump. I'll write a splice script.

Actually, maybe there's a simpler explanation: t is `s32` and tb is `s32`, but t's qty includes the `addiu` scratch? Hmm.

Let me look at the cc1 -dl dump. I'll create the spliced TU via a script.

Plan:
1. Write splice.py that takes TU, fn, body file, output file: reads TU, replaces body span, writes.
2. Run tools/cc1_dumps_tu.sh with that .c file (it accepts a .c file) and DUMP_ROOT under item dir.
3. Read the .local or .lreg dump around the qty priorities.
4. Delete dumps.

Let me write splice.py using the same body_span logic.
