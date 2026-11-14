# REVIEW — Phase 3.45, T2

What ran: PY tools/struct_twins.py --selftest (17/17); --links --propose --report twice (identical); --dispositions --check (0 undisposed); make tools-health (OK, c4 and c5); type_census --check and sig_evidence --compare unchanged after the refactors; all on this machine at 0e82fbac09
Results at: docs/ops/p345-struct-merge-report.md; config/struct_dispositions.tsv; docs/ops/p345-t2-struct-merge-evidence.md; .run/3.45/t2/*.tsv
What the expert saw: every placeholder struct (4,112) carries a proposed disposition from cited merge evidence: fold 202, apart 1,004, no-evidence 2,906

Decisions needed:
- Evidence policy for the folds: typed (30), effective (202), or views (210) — Recommended: effective; views add 8 folds through cast spellings that can be codegen levers (C0507).
- The measured outcome: 3,910 surviving types, not about 50; 2,639 placeholders are cast views of untyped values with no link — Recommended: accept as measured and keep the evidence bar; folding look-alikes would break G62 and R122.
- Batch B4, the 53-type component on Unkstruct_800B5CB8 (the map's known suspect merge) — Recommended: hold it; T7 first counts hub-type partners before hub-slot refusals, re-proposes (its 52 members become apart/hub), and B4 waits for a later per-type judgement.
- Fold batches and stop rules for T7 — Recommended: B1 (90 folds, 65 components: global and body evidence), then B2 (50 folds, 40 components: pointer evidence), then B3 (10 folds, 2 components of 6-20); one batch per commit with R22 run alone; a DIFF is localized, its component goes back to apart with the cite, and the batch continues; stop and report after 2 refused components in one batch or any type_census control move.
- Naming scope for T9 (milestone: every surviving type named) — Recommended: name the 930 survivors with reach 2 or more plus every fold target; leave the 2,980 with reach 0-1 as placeholders with their ledger rows, deferred to Gen 4. This narrows the milestone and is the developer's call; the alternative is guess_ names with basis rows for all 3,910.
- Fields for T10: the top 20 survivors by projected reach (report "Naming scope": 80126B58 121 accessed fields, 800B5CB8 98 if B4 held) — Recommended: keep 20.
- Planned field style: lowerCamelCase, guess_ outermost (guess_posX) with a basis row, the citation or basis in the field's comment beside its /* 0xNN */ offset; types PascalCase — Recommended: confirm.
- Scope boundary: 4,112 placeholders incl. 437 drafter-word types; 14 PsyQ excluded — Recommended: confirm.
- DECL-PARAM: 0 disagreements measured — Recommended: T8 still adds the rule (R179) as a guard at 0; the 20,816 struct-vs-void/scalar pairs stay out of scope (scalar parameter types are 3.44's).
- A `(void *)` cast at a call into a typed parameter counts as pointer evidence — Recommended: accept.

Plan edits proposed:
- PY tools/plan_edit.py append-change "T2 review: T7 folds B1 (90), B2 (50), B3 (10) from config/struct_dispositions.tsv under policy effective; B4 (Unkstruct_800B5CB8, 52) held; stop rules per tasks/T2.md Review"
- PY tools/plan_edit.py append-change "T2 review: T7 first: struct_twins hub-type partners counted before hub-slot refusals, re-propose, then fold; each applied row stamped applied:<commit>"
- PY tools/plan_edit.py append-change "T2 review: T9 names the survivors with reach >= 2 plus every fold target; reach 0-1 survivors stay placeholders, deferred to Gen 4 (if the developer narrows the milestone)"
- PY tools/plan_edit.py append-change "T2 review: T10 names the accessed fields of the top 20 survivors by projected reach (docs/ops/p345-struct-merge-report.md Naming scope)"
