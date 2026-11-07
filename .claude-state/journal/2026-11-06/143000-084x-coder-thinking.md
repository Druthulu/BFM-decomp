---
ts: 2026-11-06T21:30:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_IRzz9WpGwMnoZhMMIasG
---
The selection: groups by priority; within a group, it picks the one with the largest `potential_hazard` (function unit conflicts). For MIPS with simple insns, the potential_hazard depends on the insn's function unit (e.g., ALU, memory). The li (58) might use a different unit than the move (55).

`potential_hazard` — for the li (an ALU op with a constant) vs the move (a register copy). Hmm, both ALU. But the store (60) uses the memory unit.

The log: "ready list at T-3: 60 (1) 55 (7f000001) 63 (7f000001), now 63 55 60" — hmm, the priorities: 60 has (1), 55 and 63 have (7f000001). Wait, that's the dump at T-3 *after* selection: "now 63 55 60" is the reordered list. Hmm, the format is "ready list at T-X: <list before>, now <list after>".

Hmm, the priorities 7f000001 vs 1 — those look like the INSN_PRIORITY values printed as %d? 0x7f000001 doesn't look like a normal priority. Hmm.

Let me look at the log line format: `fprintf (file, ";; ready list at T-%d:", ...)` then for each ready insn `fprintf (file, " %d (%d)", INSN_UID, INSN_PRIORITY)`. So 55's priority is 0x7f000001? That's weird but whatever — maybe the priority includes flags in high bits (INSN_PRIORITY is stored with a "scheduled" bit?).

In sched.c, `INSN_PRIORITY(insn)` = XINT(insn, 4). Hmm.

0x7f000001 = 2130706433. Maybe the priority is stored in the high 16 bits: 0x7f00 << 16 | 1? The "1" is the actual priority and 0x7f00 is a flag.

Anyway, the group at T-3: {60 pri 1, 55 pri 7f000001, 63 pri 7f000001} — different priorities! So the group is by priority: the first group is insns with pri = INSN_PRIORITY(ready[0]). The list order is [60(1), 55(7f000001), 63(7f000001)]. So the first group is just {60} (pri 1), and the pick would be 60... but the log says "now 63 55 60" — the best insn moved to the front is 63?

Hmm, the log line is printed in the `if (best_insn != 0)` block, and the "now" list shows the reordered ready list. But the picked insn is ready[0] after reordering = 63. Hmm, so the selection chose 63 even though ready[0]=60 had a different priority?

Wait, maybe the ready list is sorted by priority descending: ready[0] has the highest priority. The log shows "60 (1) 55 (7f000001) 63 (7f000001)" — if 0x7f000001 > 1, then the list isn't sorted... unless the printed priority for 55/63 is not the priority but something else.

Hmm, I'm misreading the format. Let me look at the actual print code for the ready list.
