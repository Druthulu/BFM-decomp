---
ts: 2026-10-15T21:05:44.267Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a392f0f264a320d35
model: claude-opus-5-5[1m]
effort: high
turnId: fbd02241-c212-4c6f-9662-f763aed1dbdc
---
I'm tracing how this body's arg0 got stamped NO-EDIT: c3's restamp at 09:56 judged it live NO-EDIT because the target was still canonically defined at that moment, but then c4 pruned the definition and left a residual TYPE-NO-MEMBER state, meaning the restamp's verdict no longer matches the current reality.

So either way, the live cause is some real cause—just not TNC—meaning the ledger's NO-EDIT stamp is stale rather than wrong-wrong, but it's still inaccurate against the current TYPE-NO-MEMBER cause. I think this is worth flagging as a finding: roughly 9.6k sites across 7 types carry stale RESIDUAL(NO-EDIT) stamps from before the pruning, and fixing it properly would mean extending the restamp tool to also rewrite stamps whenever the live cause has drifted, not just TNC stamps—a real tooling change with its own cost. I'll note this as an accepted limitation rather than something to fix right now.

Given the cost and that it's a known residue-cause quirk rather than a correctness issue, I'll skip the fix and just log it as a finding for later. While waiting on the fan-out job notification, I'll start tallying the projection numbers: TNC dropped from 291,819 across 13,736 types to 139,520 across 12,742 types, a 52.2% reduction in sites; breaking it down by raw category, P fell from 257,470 to 174,987, I rose slightly, X dropped, and M dropped sharply, while MEMBER plus the rS1-3 batches totals 90,337 and KEPT sits at 15,466.

I'm uncertain whether the rS entries were actually kept, so I want to pull the rS1-3 commit messages to verify. Looking at the post-sweep cause breakdown, the biggest jumps are in TYPE-UNION, NO-EDIT, and NO-FIELD, with GADDR and TYPE-NOT-VISIBLE also growing substantially from their prior tiny counts. I'm also tracking fan-out timing — batch 1 took 115 seconds per the log, batch 2 is still being measured — and computing sweep rates in minutes per thousand entries across ledger, raw sites, and TNC removals.

Elapsed time divided by TNC removed gives roughly 4.07 min/1k, close enough to the logged 4.48 figure that I'll just use the logged value. For the remaining 12,742 types and 139,520 sites, I'm projecting coverage milestones at 50%, 80%, and 95%, but the per-type decision cost is unclear since the 75 types processed so far mixed automated sweeps with manual evidence review, and much of the TNC drop wasn't even attributable to those 75 types directly.

Looking closer, the restamp process converts stale TNC entries and folds them via the latest drawn canonical type, meaning TNC removal per type is front-loaded rather than evenly distributed. At roughly 4.48 min/1k sites, sweeping the remaining 139.5k sites would take about 10.4 hours if every type were canonical, but with 13,708 single-body types cluttering the struct map as noise, the real bottleneck isn't sweep throughput but rather the pace of type decisions and header fan-out.

Fan-out per batch stays manageable at 2-6 minutes, so I'm focused on decision throughput per type instead — targeting roughly an 80% coverage band of about 1,834 types covering 111.6k sites, which would need ~8.3 hours of sweeping, while noting that 51 of 75 type definitions appear mechanical (single-function, no entity evidence) and could be automated through write-types.

Looking at the residual rate across the top 75 types, it's about 21% residual, 7% fold, and 51% define, which seems tool-automatable. But checking the tail end, the last 5% of remaining types (around 6,066 types) mostly consist of single-site types where defining a canonical type wouldn't actually improve legibility — so that phase doesn't fit, meaning I should probably return a blocked status with the numbers and recommend the 95% band instead of pushing through.

I'm weighing whether "blocked" is really the right signal here versus "done" or "question" — since the committed work is finished and the done-when criteria are technically met, but the projection shows this phase doesn't make sense to run fully. I think the plan's intent is that this pilot phase determines the scope for a follow-up task, so flagging it as blocked with the recommended band is the right move, and I should re-examine the time estimates to back that up.

Checking the site counts precisely: 50% lands at 69.8k sites, 80% at 111.6k, 95% at 132.5k, leaving a tail of roughly 7k sites across 6,066 types outside the 95% band. That residual is likely dominated by single-body types, which I should quantify for the projection at the 95% cutoff of 6,676 definitions.

Applying T2's mix of 68% define, 9% fold, 21% residual to this set suggests around 4,540 definitions, with a sweep over 132.5k sites taking roughly 9.9 hours. But the sweep rate also removes TNC indirectly through stale restamping, which complicates the estimate, and I'm unsure whether 80% or 95% is the right band to target — the real concern is decision cost, since mechanizing per-type evidence judgments across 6,676 types will require defaulting rules like define-by-default when no entity evidence exists, mirroring how most of T2's 75 types were handled.

Residual classification can be mechanized from field/conflict counts (union, no-layout, scalar cases), but fold decisions still need real evidence. I'm wary of coining a new tail cause like "TYPE-SINGLE-BODY" since policy requires justifying any new residual cause, and single-body types can't just become local .c defs under the outside_canon gate — so I'll leave this as a recommendation only and move on to checking job status.
