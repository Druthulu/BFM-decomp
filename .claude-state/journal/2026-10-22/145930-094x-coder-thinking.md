---
ts: 2026-10-22T20:59:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_lYrdpPmCvMcrgned7SuF
---
The ready list at T-115: `165 (4) 208 (3) ... 161 (7f000001)` — 161 is launched at T-116 (as a "birth" with priority 7f000001?) Hmm, the 7f000001 entries are insns with a special birth priority (0x7f000001 = the birth boost). So insn 161 (by) is being "born" at T-116 and launched.

Actually the pattern: an insn with priority 0x7f000001 appears at the end of the ready list — those are "ready" insns whose operands just became available (birth). At T-115, 165 (priority 4) is launched; then at T-116, 161 appears with 7f000001 and is launched (the birth boost).

So the birth boost for 161 (by) happens *after* 165 (ax) was launched, because by's operand (bx's load, insn 152) was scheduled later? The REG_DEP_ANTI: 161 depends on 139 and 152 (the bx load). 165 depends on 155 (the ay load).

The loads: 152 = bx load, 155 = ay load. Their order: the source has bx then ay. If the loads are scheduled as 152 then 155, then by (161) is ready earlier than ax (165). But the ready list at T-115 shows 165 ready and 161 with the birth priority — meaning 161's birth came *after* 165 was ready.

Hmm, "launching 152 before 165 at T-117" — insn 152 (bx load) is launched at T-117, AFTER 165 (ax)! That's odd: the source has bx loaded first. The sched1 reordered the loads too: it launched the ay load (155) earlier, then 165 (ax), then 152 (bx load) at T-117, then 161 (by).

So sched1 moved the bx load later, which delayed by's add. In the target, the loads are 14fc (bx) then 1500 (ay) — source order.

Why did sched1 move the bx load later? Because the ay load's use (ax) was prioritized. This is the birth-boost chain.

To change it, I could make the bx load's use higher priority... e.g., by is used by the store (prim.y0), which comes after prim.x0. Hmm.

What if the source order of the stores were y0 before x0? That would change the asm store order (target: x0 first). No.

What if `by` had more uses (higher ref_count)? by is used once (prim.y0). If by were used twice, its priority would rise. But adding a use changes code.

Hmm, what if `bx` is loaded earlier in the source (e.g., before the prim.attr stores)? The loads are in the block after prim.r/g/b. Moving `bx = out.vy;` earlier (before prim.attr) might let sched1 keep it earlier. v1 swapped the loads (6). Let me try moving both loads before the prim.attr stores, and moving just bx earlier.

Try:
y1: `bx = out.vy; ay = out.vx;` moved before `prim.attr = 0;`
y2: `bx = out.vy;` moved before prim.attr, ay stays after.
y3: reorder: `bx = out.vy; by = bx - 0x5D;` before prim.attr.

These change the RTL uid order, which affects sched1's tie-breaks.

Let me try y1-y3.
