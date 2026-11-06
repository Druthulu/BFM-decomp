---
ts: 2026-10-22T21:43:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_eHPk33WnItJjDhASABGz
---
The sched dump lists insns in the scheduled order? Not exactly — the .sched dump prints the insns in the *original* order with the scheduled order as a permutation? In gcc, `-dS` (sched) prints "after scheduling" insn list in scheduled order... Actually the .sched dump prints the RTL in scheduled order but keeps uids.

Let me dump the sequence of insns with their uids around the loop, and see whether insn 40 (v1) precedes insn 43 (a0) in the scheduled order.

Better: read the region and print lines with `(insn N` and the set destination.

Let me extract the first ~120 lines of the function in .sched and print each insn's uid and destination.
