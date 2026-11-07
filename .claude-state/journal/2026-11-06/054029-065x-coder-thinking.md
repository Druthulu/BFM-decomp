---
ts: 2026-11-06T12:40:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_3h6jNrGNeaBPmKs5DJhn
---
At T-2: "ready list at T-2: 124 (1) 127 (1), now 127 124" — insns 124 (the v0 store) and 127 (li ret=7) are both ready; the list ends with "127 124" meaning 127 has higher priority in the queue → 127 is emitted first? Then "insn 124 has a greater potential hazard, now 124 127" — hazard logic reorders so 124 goes first! Wait: "now 124 127" means the queue is [124, 127], and the next scheduled is the head = 124? Then at T-3: "ready list at T-3: 127 (1), now 127" → so 124 was scheduled at T-2 and 127 at T-3.

Hold on, but the final asm has `li a0,7` before the store... Let me re-read: at T-2, both 124 and 127 are ready; the code picks... "ready list at T-2: 124 (1) 127 (1), now 127 124" then "insn 124 has a greater potential hazard, now 124 127". The "now X Y" is the queue after the decision, head first. So the queue becomes [124, 127] → 124 scheduled next (at T-2?). Then T-3: [127] → 127 scheduled.

But the final asm shows li a0,7 (127) BEFORE sw v0 (124). Hmm, contradiction. Unless "now 127 124" means 127 is at the head... and the hazard note then swaps.

Wait, the emitted order in the final RTL: from the lreg dump, the stream order was 120 (call), 127 (li), 124 (store), 129 (jump). So 127 came before 124.

But sched says at T-2 it chose... Let me re-read the sched.c code semantics: "ready list at T-2: 124 (1) 127 (1), now 127 124" — the queue printed is after adding the newly-ready insns; "now 127 124" means the head is 127? Then "insn 124 has a greater potential hazard, now 124 127" → after the hazard swap, head = 124. Hmm, then 124 is scheduled first.

Confusing. But the actual output order (from lreg) is 127 before 124. Let me check the .rtl dump (final RTL before sched?) — actually the lreg dump IS post-sched1 (lreg = local-alloc dump, after sched). So the order 127 then 124 is sched1's output.

Hmm OK. So the hazard logic put 127 first? "insn 124 has a greater potential hazard, now 124 127" — if the queue is [127, 124] and the hazard logic says 124 has a greater hazard... maybe it moves 124 to the *back*? No...

Let me look at sched.c's priority/hazard code for "greater potential hazard".

Actually, let me instead consider: the target's order is store(124) then li(127). If sched1's decision depends on hazards (v0 anti-dependency exists only when ret is v0)... In c2, ret is a pseudo → the li's target is a pseudo. Both 124 and 127 have priority 1. The hazard logic uses `insn_cost`/`potential_hazard` which is register-based: 124 writes memory via v0... 

Honestly, the practical approach: find a C change that flips this order. Options:
(a) make the li and the store interdependent: e.g. `ret = 7` where 7 is derived from the store's value? no.
(b) Change the arm's statement order: put `ret = 7;` BEFORE `unkD8 = call(...)`? Then ret is live across the call → saved reg. No.
(c) Put the unkD8 store in a separate statement: `{ s32 r = call(...); unkD8 = r; }` then `ret = 7;` — the temp r might change the schedule/hazard.

Let me try (c) quickly: split the call into a temp.

Actually hold on. Let me reconsider the problem. Maybe I'm going down a rabbit hole. Let me check the time: ~05:40, item started 05:30. 10 min. Budget 30 min. OK.

Alternative plan: maybe a completely different C form makes ret v0. What if we remove the `goto STORE` structure by making the function's return value flow naturally? 

Hmm, what about this: since the conflict is only with the FIRST arm's store ordering... no, all arms.

Let me try (c) and a few other quick variants and see if any flips the order:
c3: split the call result into a temp.
c4: swap the arm statement order: `ret = 7;` after the store but with the store split.
c5: use `do { } while (0)` around the two statements in the arm (C0535 block split) — might affect sched1's region boundaries? The dump shows basic blocks; a do-while(0) may create a NOTE_INSN_BLOCK_BEG, and sched1 splits regions at basic block heads determined by `BLOCK_HEAD/BLOCK_END` (computed by flow?). In 2.7.2 sched1 uses basic block notes from the CFG; a NOTE_INSN_BLOCK_BEG probably doesn't split.

Let me try a batch: c3 (temp), c4 (do-while around the arm statements), c5 (assign ret before the unkD8 store but after the call... no).

Actually here's another thought: what if `ret` is assigned the constant via the *store* first: `unk2` store... no.

Let me try c3 and c4 quickly.
