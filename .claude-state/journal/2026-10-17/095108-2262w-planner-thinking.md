---
ts: 2026-10-17T15:51:08.751Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ae6f058bb8615c3ec
model: claude-opus-5-5[1m]
effort: high
turnId: 8006c97b-6a60-4f7b-9d5b-7accf0cbe0ec
---
I'm checking the relevant line references in lever_census and the Makefile for the interface facts, noting that T11's wall string format isn't settled yet while T19 handles normalization. For the design, I'm deciding that the wall convention should have the TSV cause column keep its class label and append a wall tag suffix.

I'm weighing whether tags should live in a closed vocabulary file seeded from the known wall sources versus adding a new seventh column — appending to the cause column is less invasive since the writer preserves rows verbatim, and new rows without a wall tag would correctly fail validation as unjudged. I'm also sketching the check rule: `lever_census --check --strict` should return failure on strict errors, unused residue, missing or unknown wall tags, or vocabulary tags lacking a pass column, while printing a summary of wall counts by tag — and I'm considering whether this should be gated behind a `--require-walls` flag given potential conflicts with T13.

Deciding that the rule should just always trigger whenever `--strict` and `--residue` are both given, so the milestone command stays simple and only T11 onward is affected, with the vocabulary path defaulting to the walls config file. I'm also simplifying the "re-judged this phase" requirement down to just needing a named wall tag plus some labeled evidence, without enforcing a separate phase tag mechanism — matching the REPLAN tool's existing rule structure. Now I'm thinking through whether to wire the strict residue check into the tools-health Makefile target, since the done-criteria seem to call for it.

Rather than wiring it immediately into T19 — which would make tools-health fail until T20 finishes — I'm deciding to have T20 add the strict/residue flags to the tools-health check only once things are green, keeping the dependency ordering clean and avoiding premature regressions. Then I move to drafting T18, a small cleanup task for leftover cast-gate issues, with done-when criteria requiring zero residue count and zero lying count, while allowing a properly commented K&R-style empty declaration if it's load-bearing.

Next I'm addressing T18's tricky callers: since they pass full arguments through casted pointers rather than zero-arg calls, the real fix is adding a full prototype and dropping the casts at call sites, so I note that fix and assign medium effort with the opus55 coder, depending on T11 since it touches related singleton banking code. Then I start drafting T19, a tool task for adding a lever wall rule to lever_census, also dependent on T11, specifying the relevant files to modify.

Now I'm defining the done-when criteria for T19: the selftest must cover a planted unwalled row, an unknown tag, and residue-unused>0 cases each returning rc 1, plus a properly walled set returning rc 0, and confirming T11's survivor rows carry normalized tags with correct unwalled counts. Then I move to T20, which covers walls for non-singleton survivors depending on T19 — breaking down the head-class rows needing one wall per class from exemplar evidence, and the missing-param rows needing causes traced through T7's SCRATCH refusals.

For the SCRATCH rows specifically, I'm reasoning through the mechanism: these are scratch-register pins where a register variable gets written before being read, and removal changes behavior because register allocation picks a different register. I'm tagging this `alloc-reg-choice`, but applying one tag across 383 rows needs validation, so I'm planning a stratified probe of about 10 rows with oracle diff classification to confirm it's really register-only differences — any rows that don't fit get their own separate tag. I'm also noting that T11's already-parked families get their walls assigned directly within T11 itself.

Beyond that, I'm sorting the remaining families: hand-written asm gets one row, and the ENGINE_SHB asm-macro prelude gets tagged `hand-asm`. For the done-when criteria, I'm specifying that `lever_census --check --strict --residue` must return rc 0 with zero unwalled, unknown, or residue-unused rows, plus counts broken down per tag — and I'm weighing whether wall naming is purely subjective or something the probe can actually arbitrate, landing on "partially, medium effort." I'm also amending T13 to drop the bare `--strict` flag in favor of `--strict --residue`, adding dependencies on T17, T18, and T20, and specifying before/after site and row counts (3,528/2,433 → N/M) broken down by wall tag. For T11, I'm tightening the done-when wording so survivors' rows explicitly name their wall.

I'm now working through whether to update T11's status token during the redraft — since the installed plan has no status (implying queued) but REPLAN item 3 suggests it should run next, I'm leaning toward leaving the token as installed and trusting the merge logic to reconcile the state rather than hardcoding `next` myself.

The verify command's literal strict check will fail against the current residue counts, so I'm adjusting it to point at the residue file instead, replacing the hard gate with a condition that every lever site is either removed or properly excepted.

I'm leaving "re-judged this phase" as stated since the tool itself only verifies wall tags, not phase logic — that's a REPLAN-level note, not something the census tool checks. Now I need to update the context lines with the latest residue figures.

For the 862 non-singleton rows, I think they still need walls under the amended milestone, which I'd put under T20 — I'll recommend walling them and flag this as a developer decision alongside the plan approval note. I also want to add a risk around wall tags becoming a label-laundering mechanism (tags applied without real evidence), guarded by requiring a vocabulary row with pass/evidence examples, plus T20 probes and T11 format checks — then add this under research item R3.40-010.

Interfaces need the lever_census lines and cast-gate lines referenced, plus the config header for lying exceptions. For the changes section I'll leave the approval header reset to blank placeholders, then draft the plan by copying the installed file and editing it in place rather than writing it from scratch.
