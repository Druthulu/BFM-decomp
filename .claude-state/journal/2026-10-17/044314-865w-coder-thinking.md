---
ts: 2026-10-17T10:43:14.491Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a55474736c80a3baf
model: claude-opus-5-5[1m]
effort: medium
turnId: e20d419a-4489-4243-b756-85abe7c2d13c
---
I'm tracing through how max_priority gets computed after scheduling an instruction, taking the max between the remaining ready list's top priority and the just-scheduled insn's priority, with ties resolved afterward.

When store 91 is scheduled, the or 82 becomes ready and gets elevated to that max priority, while the dependent chain through 86 may already be sitting ready from when 88 was scheduled earlier. I'm checking whether 86's priority could equal that same max — if so, the tie-breaking cascades through dependence class (since 82 depends on 91, likely class 3 given a cost-1 or→store) and then LUID, where 86 would win since it has a higher LUID than 82.

Working out which has the higher priority: store 91's priority likely depends on output dependencies to a later store (insn 112), while 86's priority flows through its chain to 88 and then to the ori instructions. For 86 to win the tie, its chain needs to be at least as long as 91's output-dependency chain, since priorities are computed backward across all dependents.

I'm also considering whether 82 could be made "not ready" at the moment 91 is scheduled, by giving it a second dependent located further down in the output order — though that would require w to be used twice, which isn't feasible without altering the code.

Another angle: an anti-dependence could force ordering if a later insn writes to a register 82 reads, like c0. If c0 is reassigned in place later in the block (e.g., `c0 |= x2` for the second prim's p[2] write instead of using a fresh temp), that insn would anti-depend on 82 since 82 reads c0 — which could change the scheduling priority.

Whichever dependent resolves last determines when 82 actually launches, so the ordering ends up similar either way. I'm also checking birthing_insn_p's live-register check on the destination, which stays live since 91 is scheduled regardless — so that path doesn't help. I consider whether changing the or's destination pattern (subreg, different mode) or manipulating reg_n_sets could sidestep this, but none of these seem like clean fixes.

Then I think about reusing the variable w in post-loop code for an unrelated value: since local-alloc only handles pseudos confined to a single basic block, having w assigned in both the loop and post-loop blocks forces it into global allocation, which changes how it's scored for register assignment.

I'll test reusing `w` for the second prim's p[2] (`w = c0 | x2`, keeping both sets live) since forcing the c chain to match the store's priority seems too hard, even though similar `g_reusew_*` files suggest this may already have been attempted.
