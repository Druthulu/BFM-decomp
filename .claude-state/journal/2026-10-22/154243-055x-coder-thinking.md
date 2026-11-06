---
ts: 2026-10-22T21:42:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_r89uCO56qgmBUZJBOR3A
---
I can use hdump.sh with an includer TU + the body to get pass dumps. The relevant passes: sched1 (sched.c) vs flow/local-alloc.

Time: 15:56. Item 4 budget: started 15:34, 30 min → 16:04. Let me be careful: a dump run + reading might take 3-4 min. It could give the answer. Let me do it for the u8 variant (score 2) to see the RTL order before sched1 and after.

Actually, a faster check: is the order already wrong in the *unoptimized* RTL (i.e., expand order)? If the RTL order has $3 first but the final has $4 first, it's sched1.

Let me run hdump.sh and grep the sched1 dump for the two moves.

Command: bash .run/P40/T10/hdump.sh src/ov_MAIN_012/ov_MAIN_012_jr_801458E0.c func_80177F84.h $d/u8.c /home/musashi/bfm-decomp/.run/P40/T11/G16x/func_80177F84__func_80177F84/dumps u8

Wait, hdump takes <includer TU> <header basename>. The TU is the includer file. Then dumps go to $o/dumps_$5.

Careful: the outdir must be absolute under my shard dir. Let me use the item dir + /dump.

Note: dumps take disk space; delete after reading.

Also note the pipeline uses a different object path. Let's run it.
