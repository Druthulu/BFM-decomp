---
ts: 2026-10-15T04:46:57.368Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7996093418d381a4
model: claude-opus-5-5[1m]
effort: medium
turnId: 709b2f04-d315-4060-ba93-85c3894dd69d
---
So the anomaly is actually a stale cause stamp, not a real mismatch — those 3,457 TNC stamps on 80126B58 predate the 3.39 T3 field additions, and the live cause is really NO-EDIT 3034 / TYPE-NOT-VISIBLE 1343. This is the only type with stale stamps fleet-wide, and the 914 vs 1,650 discrepancy comes from canon_types excluding enums/fields rather than an actual naming issue.

Only 3,457 of the 5,482 entries carry TNC stamps, while the live TNC fleet count is 288,362. I want to run the lever census across the three baseline modes — strict literal, strict with residue, and unmarked — pulling residue counts per cause/kind/instrument from lever_residue.tsv using the planner's existing lever_counts.py script, and since each pass could take a while I'll batch all three into one background job with parallelism.

Confirmed the anomaly is just a stale cause stamp on `Unkstruct_80126B58`, not a name mismatch — its sites re-derive live as NO-EDIT/TYPE-NOT-VISIBLE, putting live TNC at 288,362. Moving on to the lever baselines next.
