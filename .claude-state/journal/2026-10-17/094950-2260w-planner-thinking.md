---
ts: 2026-10-17T15:49:50.758Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ae6f058bb8615c3ec
model: claude-opus-5-5[1m]
effort: high
turnId: 8006c97b-6a60-4f7b-9d5b-7accf0cbe0ec
---
I'm confirming the numbers: 2,309 residue sites across 1,436 rows, down from the original 3,528 sites in 2,433 rows. Notably, zero rows name a compiler wall, which matters because the amended milestone requires every row to be re-judged this phase with pass and instrument criteria.

Breaking down the remaining rows, 607 are head-class (spanning 20 uncracked classes), 255 are missing-parameter refusals, 572 are singletons that T11 will handle, and 2 are other. That leaves a scope gap of 862 rows (head-class plus missing-parameter) that don't name walls and aren't covered by T11. I'm thinking the fix is a new wall-naming task that mechanizes from existing logs — propagating one wall judgment per head-class across its 20 classes, and pulling refusal causes per function from T7's "refusals by cause" summary for the missing-parameter rows, with a short oracle probe where the logs lack a named wall.

I'll call this new task T19, alongside T18 for the cast-gate fix, since the walls currently only exist in logs and need to be written into the TSV itself. For the tool rule, I'm designing a strict mode for lever_census that fails with rc 1 if any residue row lacks a usage count or a named wall, using a `wall:<tag>` suffix convention where tags come from a closed vocabulary defined in a config file alongside pass name, description, and an evidence example. I'm sketching the initial tag vocabulary — covering things like constant-address CSE, add-merge CSE, argument-copy hoisting, birth-boost scheduling, callee-saved ordering, unused-result flow, stack-switch, non-C-spellable instructions, hand-written asm, asm data, and missing-parameter causes.

Since the vocabulary itself is built from compiler wall categories and grows as new tags get evidence, the check enforced by the tool is mechanical, but assigning the actual wall tag per row is still a judgment call made by the expert during re-judging. T11 is currently running under its existing done-when criteria, which already tells it every survivor row must name its compiler wall, but T11 doesn't know about the new vocabulary convention yet — so there's a real risk its wall strings won't match the format. That means T18, the tool rule that defines the vocabulary and check, needs to also normalize T11's existing wall strings onto the new vocabulary, and should land before T19 handles the head-class and missing-param wall assignments.

I'm now numbering out the sequence: T18 for the cast-gate fix REPLAN mentioned, T19 for the wall rule tool itself, T20 for assigning walls to the remaining non-singleton survivors. REPLAN only explicitly asked for a small new task, but item 1's tool-applied rule requires implementation infrastructure that doesn't currently exist, so I need to flag that gap — adding the tasks to realize it still falls within the brief's instruction to keep everything approved except what REPLAN specifies, since the rule's existence is implied by that item.

I'm weighing whether the head-class and missing-param survivor rows (862 of them) actually need named walls, or whether class labels are sufficient — this is a scope question I should flag as a DECIDE item, leaning toward requiring walls everywhere since that's consistent with the milestone's residue-tracking goal and the added cost looks manageable since walls can be assigned per class rather than per row.

For the 255 missing-parameter refusal rows specifically, the recorded causes (COMPILE-ERROR, oracle DIFFERS, etc.) don't automatically map to a compiler wall — something like a parameter change affecting register allocation would need actual probing to pin down, so I'm considering letting T20 use a mechanised probe per row to determine the real wall.
