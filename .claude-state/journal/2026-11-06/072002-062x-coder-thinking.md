---
ts: 2026-11-06T14:20:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_rSLrsZyJ8IftFd9fJy1P
---
b2 has identical refs/live (i=11/39, dst=11/36) as c1. So the statement reorder didn't change the live ranges — because flow's live_length is based on the RTL insn positions, and the statements produce the same insns in the same positions after expand? Actually the order `src; dst; i=0` vs `i=0; src; dst` — maybe expand/sched put them in a canonical order? No, flow is before sched. Hmm, but the RTL order would follow the C order. Unless the compiler reorders at expand time (it doesn't much).

Wait, maybe the live_length counts insns, and moving i=0 after dst doesn't change i's birth because... the `i=0` is a `(set reg (const 0))` insn; its position moved but the number of insns between birth and death stayed the same? If i=0 moved after src and dst (2 insns), i's birth moves 2 later, so live should be 37. But it's 39. So the reorder didn't take effect in the RTL? Or the live_length is computed differently.

Hmm, maybe expand emits the loads/stores in a different order than the C. Actually for `src = arg0->data; dst = src + n; i = 0;` the RTL order is: load src, add dst, set i=0. i's birth at the set. In c1: set i=0, load src, add dst. So i's birth is 2 insns earlier in c1. live_length should differ by 2. But it's the same 39. So maybe flow's live_length isn't simply death-birth in insns; it counts only insns where the reg is LIVE (live at that point), and maybe the extra 2 insns... Actually, if i is born later, the insns before its birth don't count as live for i. So live should shrink.

Unless the RTL order is not what I think. Maybe gcc's expand reorders independent statements? No.

Wait — maybe the `-dl` dump I'm reading is AFTER sched1 (since the lreg dump is the local-alloc input, which is after sched1). And the live_length printed in the lreg dump is reg_live_length computed by flow BEFORE sched1. So the value 39 is from flow. If sched1 reordered, the printed live_length is still flow's. So b2's flow live should be 37. But it shows 39.

Hmm, maybe the C reorder didn't change the RTL order because the compiler hoists `i=0`? Or maybe I misread: b2's file — let me verify b2 actually has the reorder. The mkvar replaced the block; let me check b2.c.

Actually wait — maybe the loads and the const set are scheduled/ordered differently. Let me look at b2's RTL around the setup. Let me grep for reg 160 set and reg 162 set insn numbers.

Actually, maybe flow's live_length for a reg live across a loop counts the loop body length differently. Let me not chase this.

Let me look at b2's RTL to see the actual order. Actually, the lreg dump is post-sched1. Let me look at the .rtl or .jump dump (pre-sched) — but those are huge.

Hmm, let me instead just check whether the insn order in b2's lreg differs from c1's. Let me grep the first block for reg 160/162 sets.

Actually, the key question: can I change live_length at all via C? Let me test an extreme: move `i = 0;` to inside the loop? That changes code. 

Alternatively, maybe live_length is dominated by the loop: for a reg live across a loop, flow's live_length counts the loop body once plus... The birth/death within the loop don't matter much if the reg is live across the back edge.

Hmm wait: i is live from i=0 (block13) through the loop body (block14) and latch (block17), and the back edge to block14. Since i is live across the back edge, its live range spans the loop. The birth at i=0 is before the loop. Moving i=0 later (still before the loop) shortens the pre-loop part. If i=0 is moved to just before the `if`, the pre-loop live shrinks by ~2 insns. Should matter.

But the dump says 39 for both. Let me verify b2.c content.
