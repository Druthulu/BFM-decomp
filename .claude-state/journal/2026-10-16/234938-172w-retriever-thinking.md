---
ts: 2026-10-17T05:49:38.226Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a2e95e2384d8f97b8
model: claude-haiku-5-5[1m]
effort: medium
turnId: 4ea45d6c-ae50-4424-b618-7353d307458c
---
I think I have enough to answer, though I should double check whether the logs actually record a --write-residue invocation for lever_census. It seems the logs don't document that flag being used; the rows appear to have been removed by hand edit or via share_body instead, with the only documented write-residue path being the strict/residue check command.

The T6.c1 recipe follows a two-step pattern: first hand-editing callers to pass an empty-parameter intermediate and running check, then applying the rung D fix with --callee, --body, and --label flags pointing at a prepared body file — using --body rather than --signature. The parameter signature seems derived from how the definition itself uses its arguments, treating $a0 as a live pin, though that register pin was later removed once the fake marker was dropped. I also want to note that the question mentioned rung D supporting --body, --with, and --tu flags alongside --apply.

I'm noting that the --all-defs flag likely wasn't used since md_SC07_004 functions each have a single definition, and calibration still needs to run via delever_oracle with snapshot-baseline followed by a calibrate pass for md_SC07_004. There are also missing-parameter pin notes for functions like func_801A1E94, residue rows that were removed, and a discrepancy between T6.md reporting zero lying cases versus T6.c1 showing eleven at a specific commit — worth flagging but not blocking.

Now I'm working out where to write the report: the pending research directory under the retriever-digest agent name, with a filename like retriever-digest-t6-rung-d-recipe.md using a slug under 40 characters, and I should verify the pending directory exists before writing.

Now I'm drafting the report content itself, capped at roughly 40 lines, covering the T6 rung D recipe for missing-parameter pins — explaining that T6 used a two-step per-definition approach (hand-editing callers with a K&R-empty intermediate signature, then applying rung D to the definition with a body file and label) rather than a single rung D pass across callers, noting only two rung D runs occurred and that --with was refused for the def translation unit, then listing the actual commands run for functions func_801A5C44 and func_801A1E94.

I'm fleshing out the findings section: how T6 picked signatures based on what callers already passed, documenting the make-check-verified hand-edit step and the cascade fix needed when restruct's --signature option fails on zero-argument callers, the handling of same-address duplicate functions requiring --all-defs, per-overlay header edits done by hand versus script (noting a script bug that missed two indented headers), the R22 regression-check workflow run per batch and at the end with make check-all, oracle calibration steps, the residue table rows removed by hand with no recorded --write-residue run, and finally noting that only those two specific pins were fixed in T6 — this isn't a broader pattern for the other 270 missing-parameter pins, since those will need caller-walking and cascade handling similar to what was done here.

I'm also noting dead ends: --with being refused on def translation units, --apply refusing dirty source trees, tree-wide return-type changes causing "conflicting types" errors unless done within the same compilation unit via check-all, and one case where changing a return type to u8 broke a shift operation in another overlay while s32 was accepted — plus how the census tool's lying-predicate check doesn't catch return-type mismatches. With everything verified against the logs, I'm ready to write this out to the file now.
