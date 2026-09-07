# Archive index

Every document retired from `docs/` at the Phase-33.5 consolidation (2026-09-07, archived at **v1.32.1**), with what it
was, what came of it, and where its information lives now. The files sit under `docs/sunset/`, moved with `git mv` so
their history is intact, for the owner's final review before deletion; nothing links into that folder, and this page
names each file as a path on purpose, so that deleting the folder later breaks no link. The rule for what goes there,
and the referrer census run before every move, are on [Docs and scratch conventions](Docs-and-scratch-conventions.md).
Records that stay — the PhaseEnds, the decision log, the cookbook — keep their citations of these files untouched.

## Plans, roadmaps and frontier reports of closed phases

| File (`docs/sunset/…`) | What it was | What came of it | Where it lives now |
|---|---|---|---|
| `gen2-roadmap.md` | The Gen2 roadmap (Phases 8–15), approved 2026-06-15; its Phase 14 (the public flip) was deferred and later re-planned | Gen2 ran as Phases 8–33 and closes at Phase 34; the two-repo mirror it described was superseded by the in-place history rewrite | `phase-ends/DIGEST.md` §1–§2; [Where the project goes next](Where-the-project-goes-next.md) |
| `roadmap-to-100.md` | The endgame roadmap v2 (Phases 27–32), re-baselined by every PhaseEnd | The goal was met: 0 stubs, 218 of 218 binaries; its P33 text was superseded by the re-charter | `PhaseEnd_Phase31/32/33.md`; `docs/phase34-seed.md` |
| `family-endgame-megaplan.md` | The Phase-26 "finish the decomp this weekend" input package | Its scan-derived thesis was byte-proven spent (three gate probes, 0%); superseded by roadmap v2 | `PhaseEnd_Phase26.md`; the decision log |
| `phase25-frontier-map.md` | Phase-25 endgame buckets, rtu-measured at 73.97% | Consumed by the family campaign | `PhaseEnd_Phase25.md` |
| `phase25-t6-curriculum.md`, `phase25-t6-fable-brief.md` | The frontier-model crack curriculum and its input brief (2026-07-09) | The curriculum ran; its outcome and lessons are recorded | `PhaseEnd_Phase25.md`; cookbook §31 (the codegen map it seeded) |
| `phase26-triage.md` | A 119-family crack triage produced by a workflow; paused before its reconcile task | The reconcile machinery was later built and the whole family frontier finished | `PhaseEnd_Phase26.md`; cookbook §33/§58/§59; [How to AI-decomp ch.10](../how-to-ai-decomp/10-integration-and-propagation.md) |
| `frontier-p30.md`, `frontier-s39.md` | Point-in-time frontier reports (2026-07-30, 2026-08-05), never re-baselined by design | The frontier they described emptied | `PhaseEnd_Phase30/31.md`; `docs/progress.fleet.md` (218 of 218) |
| `frontier-p32.md` | The last 21 functions and the five parked payloads, by blocker (2026-09-05) — the Phase-32 jumping-off document | All 21 banked and all 5 payloads onboarded; PhaseEnd_Phase31 asked that it be kept forever, so it is archived, never deleted | `PhaseEnd_Phase32.md`; the decision log P32 entries |
| `recovery-queue-s65.md` | 69 unbanked wave targets classified into four lanes, "build it, run it next session" | Absorbed by the P31–P32 finish; 0 open near-misses at the P32 close | `docs/backlog.md` (0 open); `PhaseEnd_Phase31.md` |
| `next-session-triage-ladder.md` | The triage-ladder specification and its three corrections | Built and shipped (`tools/triage_ladder.py`); the corrections are cookbook §376/§378 | `docs/wave-playbook.md` §4b; `docs/SETUP.md`'s tool row |

## Studies and syntheses superseded by the wiki

| File (`docs/sunset/…`) | What it was | What came of it | Where it lives now |
|---|---|---|---|
| `hindsight-study.md` | The optimal order for an AI-driven matching decomp, written mid-Phase 29 at ~78%, with seven meta-principles and a commission for a future study pass | Superseded part by part (its banner carries the table); its §7 became `tools/autopsy.py` + `tools/residual_class.py` | [How to AI-decomp ch.03](../how-to-ai-decomp/03-bootstrap-order.md) (the order, the permuter-failures track); `docs/retrospective.md`; `docs/generic-decomp-package.md` |
| `portable-decomp-workflow.md` | The target-agnostic system written during the campaign (§0–§11) — "the seed of the public deliverable" | The thirteen how-to chapters are its finished successor; six residual items were folded (the per-binary gate lock, the portability test, the lane-restart trap) | [How to AI-decomp](How-to-AI-decomp.md), chapters 00, 02, 05 |
| `hand-matching-process.md` | The Phase-17 Ghidra-driven hand-matching guide for the struct-heavy engine core, updated through July | Its durable content — the two-decompile loop, the five signature moves, target selection, running it as a wave — was folded; its progress numbers, pin recipes and session state were not | [The matching workflow](The-matching-workflow.md) "Matching by hand"; [ch.07](../how-to-ai-decomp/07-compiler-source.md) "Levers from the hand-matching era"; [ch.02](../how-to-ai-decomp/02-byte-gate.md) |
| `wave-metrics.md` | One row per crack wave (agents, tokens, wall-clock, banked) with the findings of each | The measurements and lessons were folded; the S37 execution block moved into the playbook | [ch.09](../how-to-ai-decomp/09-economics.md) "A wave, priced" and the sections after it; [ch.05](../how-to-ai-decomp/05-cards-lanes-waves.md); `docs/wave-playbook.md` §5 |
| `fable5-strategy-review-2026-07.md` | An outside-model strategy and scope review at Phase 22–23 | Its conclusions were acted on and recorded | `docs/retrospective.md`; the decision log P23 entries |
| `sister-decomps.md` | Cross-project knowledge-transfer notes (parked) | Realised as the cross-game signature tool and its check | [Tools from this project](Tools-from-this-project.md) (xsig); `docs/outreach/tools-announcement.md` |
| `calibration.md` | Measured close-rates for sizing Phases 28–29 (with a corrected row) | The phases it sized are closed; the economics are in the chapter | [ch.09](../how-to-ai-decomp/09-economics.md); `docs/retrospective.md` |
| `proto-correspondence.md` | The prototype research spike and its go/no-go (2026-06-14) | Verdict: no symbols in the prototypes; kept only as imported programs | `PhaseEnd_Phase3.5.md`; `config/ghidra/ROSTER.md` |
| `resident-dossier.md` | Per-function analysis of the last 14 resident stubs (2026-07-16) | The resident is 145 of 145; every lever it recorded has a cookbook section (§17, §37, §41, §43, §47, §52a/b, §53) | `PhaseEnd_Phase28/31/32.md`; the cookbook sections named |
| `canonical-decl-reconcile-design.md` | The design input for the ×134 giant unlock | Built as `tools/reconcile_decls.py` | cookbook §33; [ch.10](../how-to-ai-decomp/10-integration-and-propagation.md) |
| `automation-runbook.md` | The OpenRouter-era autonomous campaign runbook (retired 2026-08-31) | Its pipeline was replaced by the wave playbook; its rate-limit economics survive in the chapter | `docs/wave-playbook.md`; [ch.09](../how-to-ai-decomp/09-economics.md) |
| `exemplar_curriculum.md` | A residual curriculum/router for one overlay (snapshot 2026-06-19) | The frontier emptied; the atlas superseded it | `PhaseEnd_Phase31.md` (the atlas) |
| `family-manifest.md` | The Phase-25 structural-family target manifest | Superseded by the family surveys and the atlas | `docs/family-hseq.md`; `PhaseEnd_Phase25.md` |

## Distillation ledgers

| File (`docs/sunset/…`) | What it was | What came of it | Where it lives now |
|---|---|---|---|
| `distill/atbhbkbl.md` | 165 candidate idiom notes from waves at/bh/bk/bl, each disposed of with its A/B evidence | Landed as cookbook §265 (the verbatim-asm bank lane), §266 (the inert-rider law) and §267 (the addenda) — §267 cites this ledger as its evidence | `docs/matching-cookbook.md` §265–§267 |
| `distill/axbm.md` | 82 candidate notes from waves ax/bm | Landed as cookbook §268 (the register-pin law on call-clobbered registers) and §269 | `docs/matching-cookbook.md` §268–§269 |

## Session tool designs and analyses (Phase 31, sessions 58–61)

| File (`docs/sunset/tool-designs/…`) | What it was | What came of it | Where it lives now |
|---|---|---|---|
| `aprop-lane-s59.md` | The A-prop lane decomposition: 64 functions banked for zero tokens from a lane that had banked 0 of 117 | Byte-proven; the lane shipped | `PhaseEnd_Phase31.md`; the cookbook's lane sections |
| `frontier-analysis-s60.md` | The read-only frontier analysis that found ~571 already-correct drafts refused by plumbing | The integration-resolver lane and `decl_from_use.py`; the finding is the decision log's 2026-08-25 entry | `docs/decision-log.md` (P31 S61, "the wall is an integration wall"); [ch.10](../how-to-ai-decomp/10-integration-and-propagation.md) |
| `frontier-analysis-s61.md` | The exhaustive finish-plan ground truth at the S61 close | Consumed by the completion sprint | `PhaseEnd_Phase31.md` |
| `jtbl-automation-s59.md` | The carve → draft → bank jump-table pipeline | Byte-proven; the lane shipped | cookbook §8/§8a/§8b/§8e/§61b–d/§62/§260 |
| `jtbl-island-split.md`, `jtbl-island-split-review.md` | An unverified design study for the leading-island split, and its adversarial review ("go with changes — two of four steps wrong") | The corrected design shipped as `jtbl_carve --island-split` | cookbook §260; `tools/jtbl_carve.py` |
| `main-gate-defects.md` | Two defects in the executable's gate | Fixed | `docs/wiki/The-matching-workflow.md` (the main gate); `PhaseEnd_Phase31.md` |
| `main-lane-fix-s59.md` | Why 737 drafts for the executable banked zero | Diagnosed, fixed, byte-proven | cookbook §236; R40/R42/R43 |
| `o0-cc1-lanes.md` | An unverified lane study for the `-O0` and compiler-crash populations ("the headline claim was half wrong") | Its verified half became the `-O0` path below | `PhaseEnd_Phase31.md` |
| `o0-path-s59.md` | The `-O0` path: per-population bankability and a byte-proven crack | Shipped | cookbook (the `-O0` sections); `PhaseEnd_Phase31.md` |
| `tells-lane-s59.md` | The tells-lane taxonomy and its four failure causes (proposals) | Folded into the card builder's tell counts | `tools/build_wave_atlas.py` (its comment cites this note); [ch.05](../how-to-ai-decomp/05-cards-lanes-waves.md) |

## Generated snapshots of the closed frontier

These were written by tools that are still in the tree. Run at the closed frontier the tools would write empty
documents (0 open stubs), so the last populated snapshot is kept instead of being regenerated — see the conventions page.

| File (`docs/sunset/generated-snapshots/…`) | Generator | Why it is archived rather than regenerated |
|---|---|---|
| `frontier-atlas.md` | `tools/atlas.py` (`make atlas`) | The atlas at 2,520 open instances; a regen renders empty |
| `family-cousins.md` | `tools/family_cousins.py` (`make atlas`) | The cousin-unit survey over the open frontier; empty at 0 stubs |
| `worklist.md` | `tools/worklist.py` (no target) | The July ranked worklist ("79 live stubs"); `make audit-frontier` reports it absent rather than reconciling against a stale copy |
| `autopsy.md` | `tools/autopsy.py report` (no target) | The permuter-failure classification of a P30 corpus that lives in untracked scratch |
| `burndown.jsonl` | `tools/burndown.py` (no target) | Per-session fleet snapshots; superseded by `docs/story-timeline.md` |
| `progress.{ov_SC01_005,ov_SC01_006,ov_SC01_077,ov_SC03_001,resident}.md`, `difficulty.{…same five…}.md`, `duplicates.{ov_SC01_077,resident}.md` | `tools/progress.py`, `tools/difficulty.py`, `tools/dup_report.py` via `make report BINARY=<alias>` | Twelve June/July snapshots of four binaries out of 218 (two carrying figures that are now wrong: the resident at 88.97%, 21 unmatched); regenerable for any binary on demand, so not published as a partial set |

## The provenance archive's raw material

| File (`docs/sunset/history/…`) | What it was | Where it lives now |
|---|---|---|
| `Fable5-ultracode-Full research findings-w42n9cp9t.output` | 216 KB of raw multi-agent research JSON from the first day (the sotn workflow, the Ghidra/PSX stack, WSL) | Everything actionable went into `docs/SETUP.md` and `docs/formats.md` in June 2026 |
| `debug menu link.txt`, `ghidra psx plugin link.txt`, `sotn-decomp wiki link.txt` | The original three reference URLs | `docs/SETUP.md` §2 and the memory map's source index |
