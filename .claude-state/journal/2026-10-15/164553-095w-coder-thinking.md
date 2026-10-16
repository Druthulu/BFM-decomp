---
ts: 2026-10-15T22:45:53.474Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a27f5e99cd45ba1f7
model: claude-opus-5-5[1m]
effort: medium
turnId: 93fc0445-54f4-44e8-8ad6-986fd7c917ec
---
I'm sorting out the distinction between tier-1 and tier-2 rows — tier 2 covers all-new dead types, while tier 1 seems to require identical member names and layout to existing types, meaning struct_twins likely only handles tier 2, and tier-1 classes can't be allowlisted at all.

So tier-1 duplicates need to gate unconditionally, which raises a real policy question: should restruct fold a new def to the existing type purely on layout identity, even though the T2 policy says folds should only happen on detected evidence? Options include folding to the existing/earlier name, having struct_twins accept T3 defs by citing the owner address as evidence of distinct objects, or having check-structs exempt T3 dead defs from dup gating until drawn — the owner-address approach feels cleanest since it's a struct_twins change rather than a restruct change. I still need to double check the tier-1 gating predicate in type_census to see if tier-1 is truly never allowlistable.

Found that 14 of 18 gating classes are tier 2 (new dead T3 defs struct_twins skipped) and 4 are tier 1 (new def matching an existing type by name). I'll check how the predicate handles tier 1 cases.
