---
ts: 2026-10-15T03:52:25.829Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7df908b0d85c75d2
model: claude-opus-5-5[1m]
effort: high
turnId: 76dfb9f8-086c-49db-b4bc-a2c84ee77998
---
I'm scanning through the older legacy cookbook entries, noting the relevant ones around allocno class levers, propagation lanes, inert-rider rules, and the dead-end ledger, plus a cluster of gate-related entries where I need to check each gate's predicate before deciding whether to zero it.

The fifth same-address copy that the retriever missed shows up in the Phase37 logs. I'm also tallying the lying_exceptions rows against their declarations across callees.

Applying the P38 lesson about testing milestone counts against their instruments in both directions: for the TNC-by-cause milestone, I trace through how residue_cause stamps TNC at row-write time based on whether a type is canonical, and realize that writing new types into struct_types.h won't actually clear TNC from the by-cause ledger until the affected rows get re-swept and re-written — the ledger cause is frozen at the moment it's recorded, not recalculated live.

But I worry that a bare re-sweep could just relabel the cause to something generic like NO-EDIT without actually respelling the site properly, so the milestone needs to be stricter: TNC should hit zero in by-cause only if every site that left it became a legitimate member access, a KEPT macro, or landed under a real named cause, with counts verified before and after. I also want type_census --check folded into this milestone to catch duplicate type definitions or dead names that writing 13k new types might introduce. There's also an anomaly with Unkstruct_80126B58 showing 5482 TNC sites that I need to flag for the T2 investigation around map type naming versus canonical names.

Now checking the lever_census --check --strict run — it's failing with pins, asm, gte, and per-TU defect counts, though volatile-needed and register-needed aren't counted as strict failures. I'm also weighing whether moving the 13 pure-asm-body routines into separate .s files is honest (since census won't scan those) — if the originals are genuinely hand-written assembly, that split might be the correct decomp representation, provided it's backed by evidence like o0_detect or absence of a gcc frame prologue, which I should flag as a risk. And the asm-macro-def rows spanning 11 macro names raise the question of whether consolidating them into a single header would even register properly under the census's "via-header" counting for GTE.

Removing the asm-macro-def requires removing all usage sites too, since the asm count already includes those macro-based call sites. Given sizing — around 800 crack targets and comparisons to the P36 session (9 sessions, 15-20M tokens) — the T8 delever pass already drained most of the cheap wins from pins, leaving mostly agent-driven or structural C-level fixes. I'm concluding that reaching literal zero in one phase isn't realistic, so I should propose a milestone scoped to classes with mechanical fixes only — missing-parameter signature fixes, asm-macro-def-follows-usage, and gte-clobber issues.

That still leaves the question of whether the generation-3 done-criterion should flex to `--strict --residue` or whether a follow-up residue phase (like 3.40b) gets added separately — I'll flag this tension for the developer rather than silently narrowing scope. I'll keep literal zero as the stated milestone decision per the "do not silently narrow" rule, note that the singleton pilot checkpoint will return a cost projection, and move to deciding the agent allocation next.

Before drafting, I should check an existing plan file like phase-ends/phase-3.39/PHASE_PLAN.md to copy its header formatting so the new draft stays consistent.
