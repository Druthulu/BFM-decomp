---
ts: 2026-10-16T11:44:05.551Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a877a45df9e0229a1
model: claude-opus-5-5[1m]
effort: medium
turnId: e31cc4d9-ecf8-46bb-9be1-1631c84ed118
---
These 652 new types and their site counts are just post-freeze cluster names from the hash changes after T4's union-find sweep — the tools don't decide these, and acting on them would require a T3-style change exceeding T4's scope and violating the "never re-freeze the band" rule, pushing this to a plan-level question. I also need to check whether md/main/shared show the same pattern.

After confirming the drawable set shrank correctly and all residue/casts checks pass, I'll write the log and summary, commit, and return the question along with a recommendation: add a `--decide-band --ranks drift` mode that decides post-freeze types by trying E1 lineage back to their parent band types first, then falling back to a header batch and a targeted re-sweep of the affected bodies, applying the rank cutoff rule to classify types as band-level or below-band with drift evidence — and it's probably cleaner to do this after T5 so the md/main drift gets resolved together.

Weighing that against simply naming these residuals TYPE-POST-FREEZE and amending the done-when criteria — cheaper but leaves hundreds of site types undecided — I'll recommend the fuller approach: schedule it as a new task after T5 covering all segments, and amend T4's done-when to state that band types are zero in overflow, overflow tail is TYPE-BELOW-BAND, and post-freeze drift types get pushed to that new task. I still need to verify the exact cutoff site count from the tnc_band row before finalizing.
