---
ts: 2026-11-06T21:29:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_pEJTqz1pBpfWailAEWur
---
At cse1, the order IS: 55 (move a0=s0), 58 (li 3072), 60 (store q), 63 (li 1), 65 (store a), 70 (call) — the TARGET order!

But at sched1 input (.sched dump), the order was 58, 60, 55, 63, 65, 70 — the move moved after the store. So a pass between cse1 and sched1 reordered: that's cse2/loop or combine... Actually the pass order: cse1, jump, loop, cse2, flow, combine, sched. Hmm, the .cse2 dump would show. Let me check .cse2 for this function's order. Actually, the .flow dump (before combine) or .combine would show. But the .sched dump is the sched1 input (after combine).

Hmm, but the .sched dump prints the RTL *before* scheduling. It showed 58, 60, 55, ... So something moved the move down after cse1.

Wait, maybe sched1 DID reorder! The .sched dump prints the RTL after sched1? Let me check: the -ds dump is "sched" — printed after the first scheduler runs. The log in the .sched dump shows the scheduling decisions (priority, ready list), and the RTL printed after the block might be the *result*. Indeed, the .sched dump prints ";; new basic block head = 68" then the RTL of the scheduled block. So the RTL shown IS the post-sched order!

So sched1 DID reorder: it moved 55 after 60 despite all priorities being 1. Hmm, but the comment says with all priorities 1, no scheduling is done... Let me re-read: the .sched dump's RTL order (58, 60, 55, 63, 65, 70) is the scheduled order.

Hmm wait, but the scheduling log shows picks: T-6: 58, T-5: 60, T-4: 55, T-3: 63, T-2: 65, T-1: 70 → final order 58, 60, 55, 63, 65, 70. Yes, sched1 reordered.

Hmm, but the priorities are all 1 and the comment says no scheduling happens... yet it did (the ready-list order isn't the insn order).

Let me look at sched.c's scheduling loop to see the tie-break. `schedule_insn` picks the insn with the highest priority from the ready list; ties → the first in the list. The ready list is built by `add_dependee`/`schedule_insn` and sorted by priority.

The initial ready list is the last insn. As dependents are scheduled, insns become ready and are inserted into the ready list. `ready_add` appends or inserts by priority? Let me look at `ready_add`.

Hmm, this could take a while. Let me check the ready list mechanics quickly.
