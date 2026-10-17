---
ts: 2026-10-17T16:23:46.358Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac8178896d2313b85
model: claude-opus-5-5[1m]
effort: medium
turnId: 589d16b4-5a62-4ce6-8a45-63d170f3cb6e
---
I'm checking the priority formula against the pb and mine examples to confirm it matches, then working out what priority threshold above 3333 is needed for allocation ordering relative to r162.

With n=8, priority comes out to 3243, just under 3333, but n=9 gives 3552, so I need 5 more refs. This suggests cse might have merged pb2 into pb (since both point to the same address constant), making r77 span across the loop with those extra keepalive references — meaning the live range and ref count aren't independent but tied to how pb2 got unified with pb.

I'm also wondering whether loop-weighted references could explain this: gcc 2.7's flow analysis adds loop_depth to REG_N_REFS for uses inside loops, so if pb (rather than pb2) were used for one of the two per-iteration accesses to D_800AE7BC, that could inflate its ref count naturally without extra keepalive tricks.

I'm checking whether pb2 is just a CSE-generated copy of pb, matching the observed move from a2 into t2, then trying out the four combinations of pb vs pb2 across the loop-body occurrences to see which matches the target reference counts.
