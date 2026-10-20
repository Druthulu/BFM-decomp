---
ts: 2026-10-17T18:44:36.552Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6ee12ed7d3da1789
model: claude-opus-5-5[1m]
effort: medium
turnId: c73a5082-25b2-49a4-a028-dd1d5ff9dd77
---
With only that one laundering removed, the score drops to 1, since cse substitutes a0 for cursor when reading the tag — likely because cursor is pinned to a hard register ($18) while param_1 is just a pseudo copied from a0 at entry, making a0 the cheaper substitution.

Since $18 isn't a fixed register, it doesn't qualify as canonical by cse's rules, so param_1 (the pseudo) ends up canonical and the loads go through param_1 instead of cursor. I'm trying to figure out how to break that equivalence without changing the computation — maybe by modifying param_1 somehow, but that wouldn't help since the tag load happens before any modification and the equivalence already holds at that point. I'm also considering whether local register allocation keeps param_1 pinned to a0 in the target, which would explain why the real binary reads through a0 directly rather than through cursor.

Then I'm looking at whether reordering `cursor = param_1` relative to the increment of D_800EC69C could matter, but cse's equivalence likely persists across that fallthrough regardless. I'm also wondering if the duplicated tag load at both the top and bottom of the loop reflects gcc's loop rotation, where a while-loop gets its exit test duplicated at the top as a do-while, which would explain the two separate load instructions seen in the target.

Trying another possibility: if computing `psVar14 = param_1 + 5` happens before the tag load, the instruction order shifts, but the scheduler might still move things around, and cse would substitute the canonical register regardless of liveness. I suspect cse favors cursor because it has a longer live range as a pseudo, so dropping the register pin on $18 might let that happen -- worth testing as another parameter variant.
