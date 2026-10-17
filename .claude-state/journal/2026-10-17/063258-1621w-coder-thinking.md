---
ts: 2026-10-17T12:32:58.244Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: aa713f978f6769f98
model: claude-opus-5-5[1m]
effort: medium
turnId: 29f80c87-241a-492d-b40b-c42d868c661f
---
I'm trying to recall whether expand_return always routes the result through a pseudo register, or whether there's an earlier branch in stmt.c that creates a pseudo only when the return value expression has side effects or is complex.

Tracing through global allocation, I'm wondering whether pseudo 82 ends up tied to v0 only if nothing else in its live range grabs v0 first, and trying to figure out what in the target configuration pushes local allocations away from v0. I'm also considering whether this traces back to how TRUTH_ANDIF conditional jumps set the pseudo via store-flag logic, and whether reg_set_last would scan back cleanly through the jump chain without hitting an intervening label.

But I also realize there's a call instruction that interrupts that backward scan, which changes which assignment actually gets picked up. That suggests the pattern collapses differently than I assumed, with 82 taking the comparison result rather than the zero case, and then v0 picking up 82's value at the join label. I want to check how this plays into the d1 case, which apparently gets the right shape but assigns the wrong register, and then see what happens once I add back the goto-ret0 branch and look at the resulting diff for h7.
