---
ts: 2026-10-15T20:31:42.762Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a31f6db5685e71399
model: claude-opus-5-5[1m]
effort: high
turnId: 9f574573-afe9-457a-95b2-2cdf6fbec095
---
I notice that I/M restamps on global address bases should move to GADDR/GLOBAL — since the actual cause is GADDR, not TNC, restamping those rows is a legitimate cause correction. Since the done-when criteria calls for rewriting residue rows accurately, I'll include these I,M restamps.

The remaining plan: wait for the census child process to finish its refresh, then run per-segment residue checks for P,X,I,M across the redrawn bodies, followed by restamp, census, and verifying zero residue/unbacked casts. After that I need to tackle check-structs — dup_classes=5, dead=7, twins_stale=1 all need to reach zero. Coincident layout twins are policy-exempt if documented in struct-twins.md, so regenerating that doc via the twins script likely resolves the stale count and some duplicates, while the dead=7 canonical names need pruning similar to the six dead T2 defs already removed.

That said, dead names might resolve themselves once the redrawn bodies actually reference those types, since dead-kept canonical types go live once spelled in source — so pruning headers for a third batch may not even be necessary. I'll hold off on doing manual edits until I see the check-structs output after the census completes, so let me wait on that child process with a timeout before proceeding.

Header batch 2's R22 is already complete (218/218), matching the redraw batches' 94–113 s wall times. I'll wait for the orphaned census to finish before checking check-structs and check-casts on a current census.
