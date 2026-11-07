---
ts: 2026-11-06T11:43:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_uIukSM6PsomomRHl0ttr
---
Interesting! The alloc table shows:
- r72-r75 (the group A temps, 5 refs, live 21) have priority 4761 but NO hard reg assigned — "dies in 2 places; GR_REGS or none". They're the group A temps which are set twice (two groups use the same variables r2..r5!). That's why "5 refs, dies in 2 places".
- r76-r80 (group B) got v0,v1,a0,a1,a2.

Wait, but r72-r75 are the *same* variables used for both groups (r2..r5 declared once, assigned twice). So r2..r5 are ONE pseudo each with 2 defs. That's why in the asm, group A uses t3-t6 and group A2 uses t3-t6 (same regs!) — lines 39-46 reload into t3-t6.

In the target, group A uses v0,v1,a0,a1 and group A2 ALSO uses v0,v1,a0,a1 (same regs). So target also reuses the same regs for both groups. Good.

But in target, r2..r5 got v0,v1,a0,a1 and group B got a2,a3,t0,t1,t2. In mine, r2..r5 got t3-t6 and group B got v0-a2.

The alloc table says r72-r75 conflict with v0..t2 but have no hard reg (they're "GR_REGS or none" — global-alloc didn't assign because they're local to one block and local-alloc should handle). Hmm, "9 pseudo(s) in the .lreg table; .greg order: 72 73 74 75" — so 4 in .greg (r72-75), 5 in .lreg (r76-80)? The table shows all 9.

Wait: r76-r80 are in the .lreg table (local-alloc), assigned v0-v2? No, the table shows r76=v0, r77=v1, r78=a0, r79=a1, r80=a2. And r72-75 are in .greg order but got no hard reg?? That can't be — they must have been assigned by local-alloc.

Hmm, the table might be showing pre-allocation state. Let me not over-interpret.

Key insight: in the target, r2..r5 (the doubled-use temps) got the FIRST regs v0,v1,a0,a1, and r6..r10 got a2,a3,t0,t1,t2. In mine, the opposite.

Why? Priority: r72-75 have pri 4761 (5 refs, live 21); r76-80 have pri 625 (2 refs, live 32). Higher priority (4761) should win the best regs. But they got t3-t6. Hmm, unless the table's "hard" column shows the assignment and r72-75 show "-" meaning no reg (spilled?). But the asm shows them in t3-t6.

Maybe local-alloc assigned them after global-alloc, and local-alloc's order differs.

Wait, "TIE (lower allocno wins, global.c:607)" appears for all. The pri values: 4761 vs 625.

Global-alloc assigns in order of priority. 4761 > 625, so r72-75 should be allocated first, getting the best registers. But they got t3-t6?! Unless the "hard" column is empty because they were assigned by local-alloc (lreg), and the table's hard column only shows greg assignments.

Actually, the .lreg table lists local-alloc pseudos; the .greg order lists global ones. The header says "9 pseudo(s) in the .lreg table; .greg order: 72 73 74 75" — so 9 in lreg and 4 in greg (72-75 are in both?). Confusing.

Let me not go down this path. Instead, empirically: the target gives r2..r5 the best regs. To achieve that, maybe I need to make r2..r5 have a higher priority or avoid the "dies in 2 places" penalty.

"dies in 2 places" — because r2..r5 are defined twice (two defs). The allocno covers both defs. Maybe if I use SEPARATE variables for the two groups, each would be a simple local pseudo and get assigned differently. But target reuses the same registers for both groups (v0,v1,a0,a1), suggesting the same variables.

Hmm wait, in target group A = v0,v1,a0,a1 and group A2 = v0,v1,a0,a1. Could be different variables that happen to get the same regs (since group A dies before group A2 is defined, they can share). So separate variables is plausible!

Let me try: declare 8 separate temps: a2,a3,a4,a5 for group A; b2,b3,b4,b5 for group A2. Then each is a simple 2-ref pseudo. Local-alloc would assign them in order of definition: group A first → v0,v1,a0,a1; group B → a2,a3,t0,t1,t2; group A2 → v0,v1,a0,a1 (reusing dead regs). That matches target!

Let me test this. This is a real-C move (separate temps instead of reuse). Let me write w5.

Also, I need to keep the do-while splits that fixed the schedule.

Let me write w5 with separate temps and do-while splits.

Declarations:
s32 a0_, a1_, a2_, a3_;  (names can't clash with regs? variable names are fine: r2a, r3a...)
Let me use r2,r3,r4,r5 for group A and s2,s3,s4,s5 for group A2.

Order of declarations matters for local-alloc? Possibly. Let me declare group A temps first, then group B, then group A2? Or all s32 first. Let me try.

Actually local-alloc assigns regs based on the order pseudos are *used*, and `block_alloc` iterates over insns in order. So the first-used pseudo gets the first free reg. Group A defined first → v0... Let's test.
