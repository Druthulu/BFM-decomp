---
ts: 2026-11-06T20:28:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_lZ8zOFSm4wYZNSSuyaLc
---
So the printed list is the ready list before the pick, and the scheduler then sorts and picks ready[0] after sorting by rank_for_schedule. So at T-4 the list was [103, 95, 108] and it picked the best = 108 (after sorting). Then the next line at T-5 shows the remaining list "103 95" (plus any newly ready). The dump line at T-4 shows "now 108 103 95"? No wait, the dump at T-5 is "ready list at T-5: 103 (1) 95 (1), now 103 95". Hmm, the printed format has "now" after? Let me look at more context of the dump code. There's likely a "now" print after scheduling.

Whatever. The point: at T-4 it picked 108 (const) over 103 (sh) and 95 (move a0). With last_scheduled = 110 (call): 108 has a data dependence on 110 → class 1; 103 independent → class 3; 95 data dep → class 1. Class 3 should win → pick 103. But it picked 108. So maybe the dependence from the call to the const isn't recorded as class 1 because insn_cost == 1 (the const is a simple set, latency 1)? `if (link == 0 || insn_cost (tmp, link, last_scheduled_insn) == 1) tmp_class = 3;` — so if the cost is 1, class 3. Both 103 and 108 → class 3. Then tie-break by INSN_LUID: `return INSN_LUID(tmp) - INSN_LUID(tmp2)` — with qsort, the comparator returning positive means x after y... The insn with the larger LUID sorts first? The comment says "sort by INSN_LUID (original insn order), so that we make the sort stable". Since scheduling backwards, picking the later LUID first means the original order is preserved... hmm.

The const 108's LUID: it was originally before the li (101) and sh (103). Wait, in nolau the RTL input order is 95(move a0), 101(li), 103(sh), 108(const)? Let me check the .lreg dump (pre-sched2) to see the original order. The C source order is: q decl (move a0), r decl (const), store (li,sh), call. So the RTL should be 95, 100?(const), 101(li), 103(sh), 110(call). But the .dbr shows 108 as the const after 103. The insn numbers in .dbr are post-sched2 (renumbered? no, UIDs are stable; 108 is the const's UID).

Hmm, in nolau's .dbr, the const is insn 108, the li is 101, the sh is 103. The UID 108 > 103 suggests the const insn was created LATER than the li/sh, i.e., at the call's argument setup, not at the source declaration! Because `r` is a local initialized to a constant and used once — gcc's expr.c may emit the constant at the call site (the pseudo is created at the declaration but the move is emitted... hmm).

Actually, from the .sched2 block dump, insn 108 = the const, and in the .dbr RTL it appears in the call's SEQUENCE (delay slot). So the const insn 108 was placed after 103.

Wait, but in the sched2 dump the order was 95,101,103,108,110. So the const was scheduled last.

Let me look at the pre-sched2 RTL order (.lreg dump) to see where the const was. If the const was originally right after the move a0 (source order), then sched2 moved it down. If it was originally at the call (created by the arg setup), then it's a different story.

Let me check the .lreg dump for the block.
