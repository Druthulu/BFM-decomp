---
ts: 2026-10-16T16:35:45.418Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: adedfdbb8f5ba3d6e
model: claude-opus-5-5[1m]
effort: medium
turnId: 8f3cea4c-1538-4d9e-8595-5d752c92ba07
---
I'm recalculating the stale counts: kept-stale comes out to 3537 and twins-stale to 357, with dup_classes gating at 170. I'm checking whether this is prune-caused -- those 3537 T3 band definitions were dead at T3 verify time but became live again after rung-S cycles in T4/T5 drew them in.

Since my prune only removed bullets for names that are actually dead now, the correct fix is just to drop the Dead-kept bullets for names that are live again -- that's a docs-only change, no need for R22. For the twin stale/dup gating issue, I suspect my prune is the cause since it removed 1764 defs that may overlap with twin classes in canon headers; the fix would be updating twin sections to strip pruned names from the `names:` lines, collapsing classes that drop to a single name, while leaving layout hashes untouched since those are per-layout.

Checking the numbers: 551 total tier-2 dup classes, with 381 still OK as twins, leaving 170 gating classes, and 357 stale sections — likely accounting for classes whose membership shrank or vanished entirely due to the pruned names. Since fixing struct-twins.md is a direct, in-scope consequence of my change, I'll handle both the twin section updates and the Dead-kept bullet removals as mechanical docs-only fixes, then rerun check-structs -- first I need to look at the actual format of a ### section to edit it properly.

Of the 3894, 3537 are stale "Dead kept" bullets for now-live T3 band defs, and the remaining 357 are mismatched twin sections also responsible for the 170 gating dup classes. Before making changes, I'll check how many of those 357 stale twin sections contain pruned names.
