---
ts: 2026-11-06T12:51:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Wc7umRWuii1aEc0lKsyQ
---
Priority = max over deps of (priority(dep) + cost - 1). With all costs 1, every insn has priority 1 unless it has a dependency chain. So the sh has priority 1. The lui/ori: lui → ori (cost 1) → sw (cost 1). The sw feeds nothing (store). So sw priority 1, ori = priority(lui... wait, deps point from insn to its predecessors (LOG_LINKS are predecessors). ori's predecessor is lui: priority(ori) = priority(lui) + cost - 1. Hmm, priority is computed over predecessors, so the chain grows toward the end. For a 3-insn chain: lui priority 1, ori = 1+1-1 = 1, sw = 1. So all 1!

Then why did sched place the lui/ori before the sh? With all priorities equal, the ready list order decides. The scheduler is backward: it starts from the end and picks the highest priority from the ready list; ties are broken by... the list order (insns are added in reverse source order, so later source insns come first?).

Hmm, this is the "sched1-birth-order" class. Since priorities are all 1, the order comes from the ready-list ordering, which is essentially reverse source order.

So: in mine, the ready list when the scheduler reaches that point had lui/ori ready before sh. To make sh come first in final order, sh must be *more ready* (i.e., its dependents already scheduled) earlier.

Since backward scheduling places insns from last to first, the last insn placed gets the earliest position. The scheduler picks from ready[] the highest priority, and when ties, the one that is "first in the list" — the ready list is sorted by priority and then by the order insns were added (which is reverse source order for the initial list).

Hmm. In the target (with barrier), the asm splits the block, so the sh is scheduled in the FIRST region (ending at the asm) and the lui/ori in the second region. Within region 1, the sh is at the end. So the target's order is forced.

Without the barrier, both are in one region and the scheduler's tie-break decides.

How do I change the tie-break in real C? The ready list order depends on insn order (source order) and the dependence structure. Adding a dependence would do it.

Idea: make the lui/ori depend on the sh's address computation? The 0x4 store's address uses `out` (a1 = out+0x12 giv). The sh uses -8(a1). Both use a1. No.

Idea: introduce a temp whose birth is between them and that both use — creating a false dependence chain. E.g., if the constant 0x64808080 were built as `u32 k = 0x64808080;` and used later, its "birth" is a set of a pseudo. If that pseudo were *tied* to y's register (v0) by local-alloc, the anti-dependence would force order: lui v0 must come after sh v0. But target uses v1 for the constant. Hmm. Unless the target's v1 is exactly because... no, target uses v1.

Wait — maybe I should reconsider. What if the sh in target is scheduled in a *different BB*? Let's look at the actual target control flow: is there a branch between the sh and the lui? Let me dump target lines 100-175 with addresses to see where the branches are.

Let me look at the whole target listing around there.
