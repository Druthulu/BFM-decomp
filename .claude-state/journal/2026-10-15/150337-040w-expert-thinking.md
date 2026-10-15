---
ts: 2026-10-15T21:03:37.616Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a392f0f264a320d35
model: claude-opus-5-5[1m]
effort: high
turnId: fbd02241-c212-4c6f-9662-f763aed1dbdc
---
I'm puzzling over the TYPE-NO-MEMBER residual types that got pruned because rung S found zero matching bodies — likely because the bodies' base references never resolved back to the defining name, though that cause doesn't seem to show up in the by-cause breakdown.

Checking the by-cause data, I see it's missing TYPE-NO-MEMBER entirely, meaning those sites are still counted as TNC, which matches the "top-75 names still TNC: 6,855" figure almost exactly when I sum the residual counts. This looks like a done-when gap: residual types are permitted by policy, but their residue rows should be rewritten with the new cause rather than left stamped as TNC.

I suspect the restamp only touched the ov_* segment this round, while md/main/shared weren't restamped, and the TYPE-NO-MEMBER rows were added later by c4's pruning before it got killed — so my restamp ran before those causes existed, leaving stale TNC stamps on sites that should now carry the new cause.
