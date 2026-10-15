---
ts: 2026-10-15T16:12:28.342Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ad22d9836f4993c3d
model: claude-opus-5-5[1m]
effort: high
turnId: 1d228657-453d-4d09-b934-a6a5b2617275
---
The TNC count dropped from 291,819 to 153,584, a reduction of 138,235, with the top-75 stamped share accounting for 145,999 of the original total. I'm now checking whether the remaining TNC entries line up with the expected long tail of 141,820 plus the residual 29,871 from other bases in swept bodies.

There's also an open issue with 7 unbacked macro sites across 3 bodies, where a nested base expression got re-spelled into a member access, breaking the macro's census key. The cleanest fix would be a tooling change so that when rung S writes a new row, it carries forward KEPT entries for macro sites that survive — otherwise I'd need to revert the edits in those 3 bodies manually, which isn't straightforward per-body.

Actually, there's a simpler path: since a rejudge mode exists (`--redraw`), I could redraw those 3 bodies with their current verdicts and let rung S re-judge the CAST_SIGN macros directly, which should emit fresh KEPT entries without needing a deeper tool fix. I'll suggest the coder try this redraw approach first before resorting to a tooling change.

For the second header batch, I'm looking at the missing fields issue in 1255bbfd — these affect sites across 123 bodies that are now residual with no field data, so adding the fields and re-sweeping those bodies should resolve it. For the dead=7 count, I need to figure out which type names are involved and whether they should be pruned outright or marked residual with the cause the sweep identified, especially since CAST_SIGN macros don't actually name the underlying struct, which complicates attributing cause.

Even if a definition gets pruned, the KEPT macro sites referencing that removed type name are harmless since they don't rely on it directly, but any raw residual sites still typed through the table would lose their target and trigger TNC errors again. So the plan is: for the pruned definitions, mark their table row as residual with a cause reflecting what the sweep found — something like a `TYPE-NO-MEMBER` label indicating the type was defined and swept but no member site ever matched through it, which is cleaner than trying to pick a dominant non-member cause.

For the duplicate classes and stale twins, I should run struct_twins.py to regenerate the twins documentation and check its help output. For the remaining NO-FIELD cases, I'm considering whether to add padding fields to new definitions for offsets that aren't currently fields — this would mainly apply to the specific type with conflicts and any new T2 definitions where the NO-FIELD offsets represent free pad space that could be filled in additively.

Since the automated pad tool only handles head_types, I'd need a more manual approach for T2 definitions and the two target types, adding NO-FIELD offsets that fit wholly inside a pad and then redrawing those struct bodies — bounded in scope to just the T2-section defs, taking maybe a few batches. After redrawing, I'd rerun residue and restamp checks on touched segments, confirm zero residue, run census and cast checks, verify structs pass, and hit the final verification gate — that's the sequential plan for this coder pass, with a final report breaking down remaining TNC by type across the top 75 set.

I'll let the coder actually check the dead names and residual counts rather than computing it myself, and just write up the brief for this pass.
