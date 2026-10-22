---
ts: 2026-10-22T11:19:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_A1hznxH3gbKgCcv9Pe3t
---
This is `adjust_priority` for sched2 (backwards). But we care about sched1.

Key: `birthing_insn_p` — an insn whose dest is a REG that is live before the insn and `reg_n_sets[i] == 1` → it's a "birthing" insn → gets max_priority.

In our no-asm case: the load insn (coalesced) sets a0 (a hard reg) — is a0 live before the insn? a0 is call-clobbered, so `bb_live_regs` for a0... Hmm.

Let's look at sched1's `rank_for_schedule` and the "launch_priority" for sched1.

Let me find sched1's function. In GCC 2.7, sched.c has `sched1` (forward) and `sched2` (backward). Let me search for "rank_for_schedule" and "dep_cost".
