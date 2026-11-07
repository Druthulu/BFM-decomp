---
ts: 2026-11-07T00:41:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_fffrUKKbspWO7Ixzf3Cv
---
rank_for_schedule:
1. higher priority first.
2. then class relative to the last scheduled insn: class 3 (independent) preferred over class 2 (anti/output dep) over class 1 (data dep).
3. then LUID.

So after scheduling the call (insn 50), the next candidates: 53, 56, 59, 62, 65 — all have REG_DEP_ANTI 50 (anti-dependence on the call). Hmm, class relative to last_scheduled (50): for 53, link = find_insn_list(53, LOG_LINKS(50)) — LOG_LINKS of the *last scheduled insn* (50) contains the dependents? LOG_LINKS(50) lists the insns that depend on 50? Actually LOG_LINKS(insn) lists dependencies from insn to earlier insns. Hmm, in gcc's scheduler LOG_LINKS(insn) = the list of insns that INSN depends on. So find_insn_list(tmp, LOG_LINKS(last)) looks for tmp among the deps of the last scheduled insn — that's odd.

Anyway, the tie-break at equal priority and equal class is LUID.

Since 53 has a lower LUID than 56, 53 should be preferred... unless the class differs: for 53, its link from the call is REG_DEP_ANTI (a register anti-dependence: the call clobbers the reg the load writes? Actually 53 sets reg 76 (a pseudo) — an anti-dep with the call means the call's clobber list includes the pseudo? no...).

Hmm, both 53 and 56 have REG_DEP_ANTI 50. So class equal.

Wait — the ORDER in the ready list also depends on when they become ready. All become ready after the call. Then the sort puts them by LUID: 53 first.

But the output has 53 after 65. So something else: maybe 53's priority is not 1 at the time... The dump says priority 1 for insn 53.

Hmm, is this .sched dump the *result* of sched1? The dump is printed at the end of sched1 (after scheduling). The order shown is the scheduled order.

Hmm, but wait: the .sched dump also could be the *input* (sched1 prints "before" and "after"?). In gcc 2.7.2 sched.c, the dump is printed after scheduling (dump_insns). Hmm, actually there might be two dumps (before/after). Let me check the .lreg dump (local-alloc output, before sched1) to see the order of 53 vs 56. If .lreg already has 53 after 65, then the reorder happened before sched1 (in local-alloc/global-alloc? they don't reorder) — or in the RTL generation (expand/combine).

Let me check the .lreg dump.
