---
ts: 2026-11-06T22:12:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_nFiY4qzdZw7RqIqqar3X
---
The diff only shows 3 positions. Let me get the actual instruction listing around 145-165 for mine and target. The scorer's diff doesn't show matching context. Let me use the .dis approach: --keep and objdump, or extract from the target object. I already have tgt_f.dis and can regenerate cand for i2.

Actually, simpler: the residual is that mine schedules `lui a1,0xff` at 150 and `ori a1,a1,0xffff` at 154; target at 154 and 158 (each one slot later). The insns at 151-153 and 155-157 match (nops?). Let me look at the current cand.dis (v0) around 145-160 — but i2 differs from v0. Let me generate the i2 object via --keep and dump.

Actually, this is a sched1 ordering of the constant mask materialization relative to a branch delay. The mask 0xFFFFFF is used later (at the `and v0,v0,a1` after the otp load). In the target it's materialized later (2 slots).

To fix: the mask materialization timing depends on sched1's ready list. A different statement order or an extra dependency could shift it. Since we're at score 3, a small move might fix it.

Ideas:
- The `do{}while(0)` wrapper around the otp block changed the EBB. Maybe wrapping a slightly different span (e.g., include the `oidx = ...` line, or only the `*otp = ...` line) shifts the schedule.
- Try wrapping the packet store instead (i1 = 23, worse).
- Try wrapping the second store only: `do { *otp = ...; } while(0);`
- Try wrapping the `otp = ...; *otp = ...;` (i2, current).
- Try adding a second do-while around the oidx line.

Let me generate variants:
j1: do-while around only `*otp = ...;`
j2: do-while around `oidx = ...; otp = ...; *otp = ...;`
j3: do-while around the two stores plus the packet store? no.
j4: do-while around the whole tail (oidx..*otp).
j5: two separate do-whiles.

Let me try.
