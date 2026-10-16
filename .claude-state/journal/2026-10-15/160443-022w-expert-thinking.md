---
ts: 2026-10-15T22:04:43.592Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6182af38cb3c98e2
model: claude-opus-5-5[1m]
effort: medium
turnId: 26e5967c-8c53-498a-863d-3266b4d6d04b
---
The new PA 3.0 card doesn't have a Standing decisions section, so binding goes into the summary instead and the loop/curator handles it from there. I should also check the existing p40-t2-type-folds.md doc since it's likely the policy reference, then create a new p40-t3 doc for the T3 ops note. Next I'll draft the approach note and coder brief c1, and briefly verify where selftest lives given the restructuring.

I'm compiling file/line pointers across restruct.py, restruct_cycle.sh, type_census.py, and struct_types.h for the coder to use. For E2, the key detail is that globals get their canonical type from declarations — type_census may already track declared types for globals, so I'll leave the implementation specifics to the coder with retriever-code support rather than specifying the exact lookup mechanism.

For owner address resolution with hash names, I'm figuring out the fallback chain: lowest func_ address among bodies holding the type's sites, else lowest D_ address in globals_at, and if neither exists I need to decide whether that's a new residual category like TYPE-NO-OWNER since it's not currently in policy — bodies usually have a func_ name except for file-scope units or named functions like main or SDK symbols.

Restruct actually computes owner address via `dl.fn_addr(fn, tu)`, so the owner address should be the lowest `dl.fn_addr` across the type's function bodies — this should always resolve since function bodies always have an address.

For where defs and rows get written: they append to type_folds.tsv under a banded-decision comment block, and struct_types.h gets updated between generated markers with definitions ordered by rank per batch.

For each batch, the flow is: decide rows for ranks, write rows and defs, run check-structs (which depends on census dup-gating data), then refresh census, regenerate struct_twins, rerun check-structs, run R22, commit, and move to the next batch — I need to make sure the ordering accounts for census needing a refresh after header changes.

Since R22 takes about 5.5 minutes, well over the 285-second per-tool-call limit, the coder will need to run it in the background via run.sh.

I'm also weighing whether coders c1 and c2 should be split — c1 for tooling and freeze, c2 for batch execution — keeping them separate so I can verify c1's work (selftest plus a sample of dry-run decisions) before batches run. I'm considering adding a `--dry-run` style preview: the decide mode could write a scratch TSV of decisions without applying changes, with a `--write` flag to actually commit the rows and header changes, which also doubles as a way to sample-check the output. Now I want to draft the approach note and then the brief, keeping the change itself short and pushing details into the constraints/interfaces sections.

I've worked out the four-part implementation plan—freezing the 95% band, adding T2's binding logic to restruct.py, batching header defs, and small fixes—along with several non-obvious calibration decisions on band source, type classification, and verdict reuse. I'll hand the tooling to a coder and verify these decisions on a dry run before processing any header batch.
