# CURRENT_PHASE — Phase 33.5: Docs consolidation, the wiki as source of truth, the tracked-`.run/` prune, and the day-one decomp kit

> **Gate 1 approved 2026-09-07 (Drew, plan mode, Max, Fable 5.1).** Rules **R74–R83 ratified at gate 1** (the Phase 33 candidates
> (a)–(j); binding; full text in `phase-ends/DIGEST.md` §3). The approved plan is reproduced VERBATIM at the end of this file
> (§"Approved plan") — its `~/.claude/plans/` copy is not part of the repo. This is a **sub-phase** between Phase 33 (closed at
> v1.32.0) and Phase 34 (the flip, `docs/phase34-seed.md`, untouched); it closes at **v1.32.1**. It changes no build input: the
> fleet's 218/218 is asserted by `make tools-health` (`report BINARY=main` + `audit-digest`), not by an R22 rebuild.
> **Baseline HEAD at open: `80d45b29b`** (Drew's Phase-33 CLOSE commit; tree clean).

## Milestone (gate 2 — what Drew confirms)
1. **The wiki is the source of truth:** every file under `docs/` (outside `wiki/`, `how-to-ai-decomp/`, `sunset/`) is either a row in
   `docs/wiki/Reference-index.md` or README-linked (the ⊆ check in `tools/doc_links.py`); the five new pages exist and are reachable
   from `_Sidebar.md`; no wiki/how-to page links a `docs/` file outside the index; nothing links into `docs/sunset/`;
   `tools/doc_links.py --strict` = 0 broken / 0 pending / 0 untracked-cited; a real `tools/wiki_render.py` run exits 0.
2. **No information lost:** every sunset file is under `docs/sunset/` with history (`git log --follow`), a row in
   `docs/wiki/Archive-index.md` (what · outcome · where it lives now) and a review row in `docs/sunset/README.md` (`comm -3` empty).
3. **Tracked `.run/` is flip-ready:** `git ls-files -ci --exclude-standard .run` = 0; the finished-work groups untracked (the list in
   the task-8 log == `git diff --diff-filter=D`); the two disassembly files untracked and named in
   `tools/public_rewrite/untracked_after_rewrite.txt`; `tools/audit_public.py` OK with its new content check and both R39 controls
   recorded; `purge_set.txt` unchanged so `gate_scan.py --all` stays PASS.
4. **The kit exists and installs:** `decomp-architect/` (README, intake, SETUP, methodology, templates, corpus, memory-seed, MANIFEST)
   passes `tools/kit_lint.py`, and the dry-run install in a throwaway repo produced the expected manifest with the guardrail
   assertions unchanged — or, past the cut line, `KNOWN-DEFECTS.md` says exactly what did not (R66).
5. **Memory reconciled:** the off-project memory moved, the seven stale ones updated, the portable set present as the kit's seed.
6. `make tools-health` OK; `PhaseEnd_Phase33.5.md` + DIGEST §0/§2 append + `CURRENT_PHASE.md` archived; left for Drew's close commit.

## Effort / model (R7/R26/R27 — every transition is PROMPTED, never assumed)
- Per task (the plan's table): **Max** for tasks 0, 3, 10, 12, 15; **xHigh** for the rest. Task 5's three document diffs may fan out
  to read-only agents (breadth); no Ultracode/Workflow otherwise. The dry-run (task 13) is ONE subagent under D6's guardrails.
- **Drew-only (R6):** every `git push`; the gate-2 confirmation; the eventual deletion of `docs/sunset/`.

## Owner decisions (binding — AskUserQuestion, 2026-09-07)
1. Kit in-tree now (`decomp-architect/`), split into its own repository after the flip as xsig was. 2. Phase 33.5, v1.32.1,
(a)–(j) ratified now as R74–R83. 3. Sunset = `git mv` → `docs/sunset/` + `git rm --cached` of finished tracked `.run/`; Drew reviews
and deletes later. 4. The kit's SETUP.md opens with "install ProjectArchitect 2.0 first, then this". 5. BFM's own memories stay in
`~/.claude` (kit seed only; no `.claude-state/` retrofit). 6. The two `fable_cd4` disassembly files: untrack + an audit-only rule + a
content check; **no second history rewrite** (the tracked C + the pinned compiler reproduce those bytes). 7. Link form: relative
in-tree links to `docs/wiki/<Page>.md`. 8. `.run/`: only what git tracks; no scan of the untracked 29 GB. 9. README's `docs/` links stay.

## Tasks (strict order; one commit per task after this file is updated; harness task list = the same 16 rows, R28)
- [x] **0** Gate 1 close-out: this file (ledgers + checkpoint), R74–R83 into DIGEST §3 (+ §0), `phase34-seed.md` amended, TaskCreate ×16 — Max
- [x] **1** Unblock, code side: tool docstrings re-pointed (`decl_from_use.py`, `integration_resolver.py`, `jtbl_carve.py`, `autopsy.py`, `residual_class.py`); CLAUDE.md lines 11 / 61 / the effort-default sentence — xHigh — see Log 2026-09-07 Task 1
- [x] **2** Unblock, doc side: banners (`concurrency-design`, `gen2-mips-matching-model`, `psyq-worklist`, `distill/*`, `hindsight-study` HISTORICAL + supersession table); SETUP §1a rewritten; the pin count re-derived (one dated number + its command, both gen3 docs) — xHigh — see Log 2026-09-07 Task 2
- [x] **3** Wiki — conventions + firewall: `Docs-and-scratch-conventions.md`, `The-ROM-firewall.md` (the gitignore template block); sidebar rows; Repository-layout/Contributing/ch.11 links; forward links in `doc_links_pending.txt` — Max — see Log 2026-09-07 Task 3
- [x] **4** Wiki — reference + direction: `Reference-index.md` (list-driven), `Where-the-project-goes-next.md`, Contributing "AI use — conduct", Home rewritten, sidebar sections — xHigh — see Log 2026-09-07 Task 4 — **P6 rules check done after it**
- [x] **5** Integrate the six (hand-matching-process; wave-metrics + the s37w block → wave-playbook; portable-decomp-workflow vs the 13 chapters; generic-decomp-package attributed; hindsight §2.1/§7 → ch.03 + permuter-ils; the gen3 docs → the direction page); re-point every referrer incl. `retrospective.md:10–11` — xHigh — see Log 2026-09-07 Task 5
- [x] **6** Sunset moves (59 files — `family-hseq.md` stays, see the log) with the referrer census by command; `docs/sunset/README.md`; `Archive-index.md` rows (backticked paths + `v1.32.1`); DIGEST §4 + `docs/history/README.md` refreshed; coverage: 0 `docs/` files outside wiki/how-to/sunset uncovered — xHigh — see Log 2026-09-07 Task 6
- [x] **7** Checkers: `doc_links.py` (sunset refusal, index-derived allowlist, wiki-first warnings, TRACKED/UNTRACKED citation classifier + `--disk`, coverage ⊆); reachability in `wiki_render --selftest`; `timeline.py` regen in `report BINARY=main` + `--check` in `audit-digest`; the 13 dangling cookbook cites; the gitignore-template diff; tools-health wiring; SETUP rows — xHigh — see Log 2026-09-07 Task 7
- [x] **8** Tracked `.run/` prune (218 paths untracked: the 172 inertia files + 44 finished logs + the 2 firewall listings; `untracked_after_rewrite.txt`; `audit_public` check 4 with both controls; runbook §11; the four tool notes) — xHigh — see Log 2026-09-07 Task 8 — **P6 rules check done after it**
- [x] **9** Memory reconciliation (the off-project file parked; the 7 stale updated in place; `bfm-decomp-context-system` refreshed; the seed set — 16 files — under `decomp-architect/memory-seed/` with `upstream: PA` tags) — xHigh — see Log 2026-09-07 Task 9
- [x] **10** Kit part 1: `README.md`, `intake.decomp.md`, `decomp-architect.md`, `templates/registry-E.decomp.md`, `corpus/decomp-kernels.md`, `templates/PLACEHOLDERS.md` — Max — see Log 2026-09-07 Task 10
- [ ] **11** Kit part 2: the firewall pack, docs/run READMEs, ops-setup, bootstrap, CLAUDE overlay, `pa-overlays.md`, LICENSE/NOTICE/README/CONTRIBUTING skeletons, `.clang-format` + format snippet, `tools/MANIFEST.md`; `tools/kit_lint.py` in tools-health — xHigh
- [ ] **12** Kit part 3: `SETUP.md` (§0–§10, `--answers`, the PA-2.0 version pin, the honesty section, Path A only) — Max — **then P6 rules check**
- [ ] **13** Dry-run install under D6's guardrails; fix; re-run to green; fixture + expected manifest + logs tracked under `.run/P33.5/kit-dryrun/` — xHigh
- [ ] **14** Wiki `Start-a-new-decomp-project.md` + README/`Tools-from-this-project.md` rows + SETUP rows (R21) + decision-log entry (R31) + accelerators entry if earned — xHigh
- [ ] **15** Close: real render; tools-health foreground; `doc_links --strict`; `audit_public`; `PhaseEnd_Phase33.5.md` + DIGEST §0/§2 + log archive; left for Drew — Max (Tier 1, WAIT for gate 2)

## Blockers
- None at open. The GitHub Support purge (ticket #4736982) is Phase 34's blocker, not this phase's.

---

## The execution ledgers (from the three gate-1 audits; the audit reports exist only in the planning session — R30)

### L1. The docs/ classification (path → class · note). Classes: KEEP-LIVE · KEEP-GEN · FROZEN→SUNSET · INTEGRATE→SUNSET · SUNSET
| Path (under `docs/`) | Class | Note |
|---|---|---|
| `SETUP.md` | KEEP-LIVE | §1a is false ("never committed") — rewrite (task 2) |
| `accelerators.md` | KEEP-LIVE | README-linked; its substance reaches the wiki via the kit corpus + the new-project page's table |
| `actor-struct.md` | KEEP-LIVE | Gen3 input (`gen3-handoff` §5) |
| `automation-runbook.md` | SUNSET | already bannered HISTORICAL/superseded by `wave-playbook.md`; economics in how-to ch.09 |
| `autopsy.md` | FROZEN→SUNSET | generated by `tools/autopsy.py` from untracked `.run/autopsy/`; a P30 snapshot |
| `backlog.md` | KEEP-GEN | `backlog.py prune` in `make report BINARY=main`; 0 open |
| `badges/*.json` (4) | KEEP-GEN | `progress.py write_badges()`; README shields |
| `burndown.jsonl` | FROZEN→SUNSET | `burndown.py`, no target; superseded by `story-timeline.md` |
| `calibration.md` | SUNSET | P28/P29 close-rate sizing; economics in ch.09 + `retrospective.md` |
| `canonical-decl-reconcile-design.md` | SUNSET | "✅ RESOLVED — built as tools/reconcile_decls.py (cookbook §33)" |
| `commit-map.tsv` | KEEP-GEN | one-shot, `public_rewrite/build_commit_map.py`; README-linked |
| `community-matching-model-plan.md` | KEEP-LIVE | linked by the published `matching-drafter-pipeline.md`; parked (licensing decision) |
| `concurrency-design.md` | KEEP-LIVE | banner "not yet implemented" is FALSE — six tools implement it; fix (task 2) |
| `cookbook-index.md` | KEEP-GEN | `cookbook_index.py --check` in tools-health |
| `debug-menu-list.txt` | KEEP-LIVE | primary data (Drew's transcription, S45) |
| `decision-log.md` | KEEP-LIVE | README-linked; append-only (R31) |
| `decompme-preset.md` | KEEP-LIVE | README-linked; Phase 34 E1 |
| `difficulty.md` | KEEP-GEN | `make report` |
| `difficulty.{ov_SC01_005,ov_SC01_006,ov_SC01_077,ov_SC03_001,resident}.md` (5) | SUNSET | orphaned per-binary snapshots (June/July; resident says "21 unmatched" — wrong now); regenerable by `make report BINARY=<alias>` |
| `disc-completeness.md` | KEEP-LIVE | wiki `Overlays-and-modules` links it |
| `disc-ledger.md` | KEEP-GEN | `make audit-disc` |
| `distill/atbhbkbl.md`, `distill/axbm.md` | SUNSET | banners say "PROPOSED ONLY" but both LANDED as cookbook §265–§269 (verified); kept as the A/B evidence ledger the cookbook cites — banner fix first (task 2) |
| `doc_links_pending.txt` | KEEP-LIVE | the pending-link mechanism |
| `duplicates.md`, `duplicates.cross.md` | KEEP-GEN | `dup_report.py` in `make report BINARY=main` |
| `duplicates.{ov_SC01_077,resident}.md` (2) | SUNSET | orphaned per-binary snapshots |
| `effort-map.md` | KEEP-LIVE | governs effort; how-to 01/08 link it |
| `exemplar_curriculum.md` | SUNSET | `exemplar_miner.py` snapshot of 2026-06-19; frontier empty |
| `fable5-strategy-review-2026-07.md` | SUNSET | dated standpoint; conclusions in `retrospective.md` + decision log |
| `family-cousins.md`, `family-hseq.md` | FROZEN→SUNSET | `make atlas` would rewrite them EMPTY (0 stubs); keep the last populated snapshot |
| `family-endgame-megaplan.md` | SUNSET | bannered SUPERSEDED by `roadmap-to-100.md`; PhaseEnd_Phase26 records the outcome |
| `family-manifest.md` | SUNSET | Phase-25 target manifest; superseded |
| `formats.md` | KEEP-LIVE | wiki Home + Overlays link it |
| `frontier-atlas.md` | FROZEN→SUNSET | `make atlas` (2,520 open at `252dc930c`) → EMPTY at HEAD |
| `frontier-p30.md`, `frontier-s39.md` | SUNSET | point-in-time reports, self-declared not re-baselined |
| `frontier-p32.md` | SUNSET | PhaseEnd_Phase31 says "keep forever" → MOVE, never delete; outcomes in PhaseEnd_Phase32 |
| `gcc-2.7.2-map/*` (7 incl. `cite_overrides.tsv`) | KEEP-LIVE | README-linked; `gccmap_cites --check` |
| `gen2-mips-matching-model.md` | KEEP-LIVE | status line "not started" is stale — it was built; fix (task 2) |
| `gen2-roadmap.md` | SUNSET | Gen2 closes at Phase 34; the record is DIGEST + PhaseEnds |
| `gen3-handoff.md` | KEEP-LIVE (+INTEGRATE) | summarised into `Where-the-project-goes-next.md`; `doc_links` DEFAULT |
| `gen3-parking-lot.md` | KEEP-LIVE | correctly parked; `gen3-handoff` §7 re-adopts it |
| `gen3-standards.md` | KEEP-LIVE (+INTEGRATE §3) | README-linked; §3 → Contributing "AI use — conduct" + the direction page |
| `generic-decomp-package.md` | KEEP-LIVE (+attribute) | how-to 00/06 link it; attribute in ch.03/06 |
| `hand-matching-process.md` | INTEGRATE→SUNSET | → `The-matching-workflow` (+ch.07) |
| `hindsight-study.md` | INTEGRATE→SUNSET | mid-P29 at ~78%; superseded part-by-part (ch.03, `generic-decomp-package`, `retrospective`, `gen3-handoff` §5; §7 realised as `autopsy.py`); referrers: how-to 00/02, `retrospective.md:10–11`, `gen3-handoff` §8, `autopsy.py`/`residual_class.py` docstrings, backticked cites |
| `history/README.md`, `history/claude-bfm-starting-point.md`, `history/project_architect_v1.3.0.md`, `history/cheap-tier-ab-experiment.md` | KEEP-LIVE | archive; story/retrospective cite them |
| `history/Fable5-ultracode-Full research findings-w42n9cp9t.output` | SUNSET | 216 KB raw JSON, one reader (its README); folded into SETUP/formats long ago |
| `history/{debug menu link,ghidra psx plugin link,sotn-decomp wiki link}.txt` (3) | SUNSET | URLs already in SETUP |
| `idxtab-map.md` | KEEP-LIVE | Gen3 lever (`gen3-handoff` §5) |
| `matching-cookbook.md` | KEEP-LIVE | README-linked; grep by § |
| `matching-drafter-pipeline.md` | KEEP-LIVE | README-linked |
| `memory-map.md` | KEEP-LIVE | wiki links it |
| `next-session-triage-ladder.md` | SUNSET | "BUILT AND SHIPPED (P31 S69) — Status: DONE"; corrections = cookbook §376/§378 |
| `outreach/archipelago.md`, `outreach/tools-announcement.md` | KEEP-LIVE | Phase 34 tasks |
| `permuter-ils.md` | KEEP-LIVE | README-linked; receives hindsight §7's pointer |
| `phase25-frontier-map.md`, `phase25-t6-curriculum.md`, `phase25-t6-fable-brief.md`, `phase26-triage.md` | SUNSET | closed phase artifacts; PhaseEnd_Phase25/26 carry the outcomes |
| `phase34-seed.md` | KEEP-LIVE | the live Phase 34 plan |
| `portable-decomp-workflow.md` | INTEGRATE→SUNSET | "the seed of the public deliverable" — the 13 chapters are its successor; diff, fold uniques |
| `progress.md`, `progress.json`, `progress.fleet.md` | KEEP-GEN | `make report BINARY=main`; CI reads `progress.json` |
| `progress.{ov_SC01_005,ov_SC01_006,ov_SC01_077,ov_SC03_001,resident}.md` (5) | SUNSET | orphaned per-binary snapshots (resident says 88.97% — wrong now) |
| `proto-correspondence.md` | SUNSET | verdict in PhaseEnd_Phase3.5 + `config/ghidra/ROSTER.md` |
| `psyq-sample-idioms.md` | KEEP-LIVE | small; SETUP §5.6 cites it |
| `psyq-worklist.md` | KEEP-LIVE | the only per-object record of the 1,256 LINKED functions; add COMPLETE banner (task 2) |
| `public-flip-runbook.md` | KEEP-LIVE | README-linked; §11 gains the residue note (task 8) |
| `recovery-queue-s65.md` | SUNSET | closed by outcome (backlog 0, 218/218) |
| `resident-dossier.md` | SUNSET | resident is 145/145; check each lever has a cookbook § before moving |
| `retrospective.md` | KEEP-LIVE | README-linked; links hindsight at :10–11 → re-point (task 5) |
| `roadmap-to-100.md` | SUNSET | goal met; successors `phase34-seed.md` + `gen3-handoff.md` |
| `second-oracle.md` | KEEP-LIVE | Makefile + four tools read it |
| `sister-decomps.md` | SUNSET | realised as xsig's cross-game check |
| `story.md`, `story-timeline.md`, `story-timeline.svg` | KEEP-LIVE / KEEP-GEN | README-linked; `timeline.py` to be wired (task 7) |
| `struct-core-pivot.md` | KEEP-LIVE | Gen3 input |
| `tool-designs/*` (11: aprop-lane-s59, frontier-analysis-s60, frontier-analysis-s61, jtbl-automation-s59, jtbl-island-split, jtbl-island-split-review, main-gate-defects, main-lane-fix-s59, o0-cc1-lanes, o0-path-s59, tells-lane-s59) | SUNSET | closed P31 session artifacts; outcomes in PhaseEnd_Phase31 + cookbook §8/§8a/§8b/§8e/§61b–d/§62/§154-A/§236/§260; re-point `decl_from_use.py`, `integration_resolver.py`, `jtbl_carve.py` first |
| `tooling-audit.md` | KEEP-LIVE | how-to ch.04's evidence base — cite it there (task 5) |
| `verification.md` | KEEP-LIVE | README-linked; CI header cites it |
| `wall-taxonomy.md` | KEEP-LIVE | Gen3 input |
| `wave-metrics.md` | INTEGRATE→SUNSET | → ch.09/05; its `.run/s37w.js` execution block → `wave-playbook.md` first |
| `wave-playbook.md` | KEEP-LIVE | the procedure |
| `worklist.md` | FROZEN→SUNSET | July snapshot ("79 live stubs"); read by `make audit-frontier` (outside tools-health) — the audit reports absence |
| `wiki/*`, `how-to-ai-decomp/*` | the wiki | the source set of `wiki_render.py` |

### L2. Tracked `.run/` (1,086 files / 15 MB at open)
- **Untrack, self-sealing (172 tracked-but-ignored; verified this session):** `s6h` 38 · `s6f` 25 · `w6` 16 · `s37` 16 · `s6g` 15 ·
  `s6i` 8 · `t4` 6 · `s6b_cracks` 2 · `fable_frontier` 2 · `audit` 1 · 43 loose root files (`alias_defs.py`, `attract_loadmap.jsonl`,
  `disc_code_sweep.txt`, `jr_family_sweep.py`, `maintenance.sh`, `resident_wave_verdicts.json`, `sc03_hunt_loadmap.jsonl`,
  `s3_sc07_whale.py`, `s6f_gate.py`, `s6g_*`, `s6h_*`, `s10*`, `s33–s36_capture.py`, `s36_wave.json`, `s36w.js`, `s37_wave.json`,
  `s37w.js`, `s7_*`, `s8_*`, `s9_*`, `w6*`, `w7_wave*.json`). Prose citations to move first: `wave-metrics.md:62` (`.run/s37w.js`)
  and `:153` (`.run/s6f_gate.py`). Tool defaults/comments to annotate: `wave_judge.py:8` (`WAVE=.run/t4`), `claude_wave_packs.py:16`,
  `jtbl_family_bank.py:380`, `dedup_propagate.py:114`.
- **Untrack with `.gitignore` narrowing (enumerate at task 8):** `.run/P32/t3s3/` session logs (67 tracked: 44 `.log`, 15 `bank_*`)
  and the duplicate `tools_health.log` / `report_close.log` under `t3s3`/`t4b`/`t4d`/`t4e` — keep any copy a doc cites
  (`verification.md` cites `.run/P32/t4e/r22_check.log`).
- **Untrack + audit rule (the firewall pair):** `.run/giants/fable_cd4/mine_full.txt` (398 lines, `0: 27bdffc0 addiu sp,sp,-64`) and
  `target_full.txt` (399 lines, `0: addiu      $sp, $sp, -0x40`) — allowlisted by `!/.run/giants/fable_cd4/*.txt`.
  `purge_set.txt` must NOT change (`gate_scan.py` reads it as the history census); the rule goes in
  `tools/public_rewrite/untracked_after_rewrite.txt`, read by `audit_public.py`.
- **KEEP-TRACKED:** `P33/verify` (15) · `P33/e1` (1) · `P32/**` drafts/notes/banks/reproducers (482 minus the logs above) ·
  `giants` (279, minus the pair) · `S79w` (33) · `s43` (22) · `fable_80178004` (22) · `wave22` (19) + `wave22_targets.json` ·
  `near6` (16) + `near6_measure.{py,json}` + `near6_ils_*.log` · `s45` (12) · `s42` (3) · `probe_jtbl` (3) · `backlog.jsonl` ·
  `fuel_manifest.json`.
- **POST-FLIP (0 tracked files; on disk only):** `.run/decompme/`, `.run/public_rewrite/`, `.run/objdiff/` — Phase 34 tasks 2/7.
- **Doc citations of `.run/`:** 653 backticked (58 tracked / 581 untracked-on-disk / 14 dangling incl. cookbook :36918
  `.run/P32/t3/restored/sweep_func_80039308.py`, `.run/frontier_p32.json`, `.run/backlog_drafts/func_80011380.c`, `.run/banked_func_*.json`,
  `.run/distill_inflight/*.json`, `.run/rtu_shadow/X.jsonl`, `.run/s7/scratch/spliced.c`, `.run/diag_plumbing.py`) — the checker is
  disk-independent (TRACKED/UNTRACKED by `git ls-files`), strict only for wiki/how-to pages.

### L3. The memory store (81 files + MEMORY.md under `~/.claude/projects/-home-musashi-bfm-decomp/memory/`)
- **ALREADY-IN-REPO (52):** autonomous-lane-architecture · breadth-isolated-agents-not-serial† · build-tasklist-after-plan-approval ·
  capture-knowledge-before-fresh-session · carve-state-files-never-blanket-add · check-against-a-known-true-case ·
  checkpoint-current-phase-before-pause · commit-banked-work-immediately · commit-message-from-tool-output · commit-per-task-after-phase-log ·
  cross-project-idiom-discovery · decomp-accelerator-ledger† · decomp-community-ai-standards · derive-from-invariants-not-reparsing ·
  dont-conclude-unsteerable-try-register-pins · effort-prompt-ultracode-on-breadth · exonerate-the-instrument · fable-agents-for-lane-tooling† ·
  fleet-tool-parallelism-defaults · gating-speed-playbook† · journal-notes-are-pack-fuel · lane-blockers-are-harness-not-model ·
  matching-cookbook · matching-is-solved-integration-is-the-bottleneck · mcp-reconnect-after-restart · mcp-renames-dont-persist-use-applysymbols ·
  measure-the-steady-state-not-the-launch · no-commit-co-author · no-tmp-project-local-data · parallel-gate-via-worktrees · pass-j-to-every-build ·
  phase-worklogs-reference-only · pkill-pattern-kills-own-shell · private-repo-backup-policy (partly stale) · quote-the-denominator ·
  report-every-lane-not-the-loud-one · reprobe-exclude-lists-after-tool-fixes · rescan-twins-after-every-bank · session-start-list-rules-in-full ·
  session-summary-plain-english · setup-md-keep-current · silently-narrowed-tool-scope · standalone-match-is-not-bankable ·
  structural-family-mechanical-remap · subagent-model-ladder† · tool-must-refuse-unsupported-input · tools-folder-convention ·
  ultracode-harvest-pattern · verdict-names-its-instrument · verify-blast-radius-not-just-defect · wave-harvest-is-a-pipeline-step ·
  wave-prompt-seed-step0-and-gaps · web-research-compiler-quirks. († carries a portable rider: the quadratic main-loop-context arithmetic;
  the accelerator-ledger habit as a rule; the per-stuck-lane briefing recipe; "a slow gate is a BUG"; what the frontier model is NOT for.)
- **PORTABLE-NOT-IN-REPO (14):** in PA 2.0's seed already — repo-self-contained-claude-state, drew-working-preferences, dont-block-loop-
  with-askuserquestion, justify-new-tools-before-adopting, clarify-misconception-before-costly-action. **New for the kit (9):**
  no-sleep-polling-background-tasks, live-coop-answer-before-grinding, tools-health-foreground-not-background, resume-means-resumefromrunid,
  tool-change-updates-siblings-and-docs, bank-idioms-before-checkpoint, phaseend-verbosity-for-the-retrospective, offline-tooling-first,
  wave-playbook-is-the-procedure — plus the five riders and three decomp seeds (matching-flywheel, byte-gate-is-the-only-claim,
  mcp-reconnect-after-restart). `upstream: PA` tag on the four harness-generic ones.
- **BFM-SPECIFIC (9, keep):** bfm-decomp-context-system · continuous-gater-lane-plan · crack-wave-sweep-map-regen · dedup-backlog-leave-it ·
  disc-dump-location · endgame-budget-unconstrained · gate-main-only-with-gate-main · roadmap-to-100 · wsl-disk-capped-75gb.
- **STALE (7, update in place):** cheap-tier-ab-validated · effort-doctrine-xhigh-default (the memory is right; CLAUDE.md is stale) ·
  private-repo-backup-policy · project-endgame-deliverables · roadmap-to-100 · rom-content-git-policy · bfm-decomp-context-system's status block.
- **OFF-PROJECT (1, move):** vantage-edge-never-leaks → the Vantage project's memory directory under `~/.claude/projects/`.

### L4. The wiki mechanism, the link policy and the kit design — see the Approved plan (§"What exists", D1–D6) below.

---

## Log (newest last; one entry per task; the 🛑 block at the end is rewritten after every task)

### 2026-09-07 — Task 0 — Gate 1 close-out (Max)
Plan approved in plan mode after three exploration audits (docs/ tree, tracked `.run/` + firewall, memory store + ProjectArchitect)
and one adversarial Plan-agent review (12 amendments folded in: forward links via the pending list; referrer census by command;
frozen snapshots instead of empty regens; the audit-only rules file because `purge_set.txt` is the history gate's census; a content
check whose shapes come from the offenders; disk-independent citation checks; the kit as a Phase-0.5 overlay with an intake
document for PA's own interview; dry-run write guardrails; a cut line). Spot-checked the claims the plan leans on (172 tracked-but-
ignored; the two disassembly files; §265–§269 landed; the tools-health chain). R74–R83 written into DIGEST §3 from the Phase-33
candidates' text; DIGEST §0 notes the sub-phase; `phase34-seed.md` amended. Harness task list built (16 rows). Effort for task 1 is
xHigh — the transition is prompted (R27). Commit `39d524991`.

### 2026-09-07 — Task 1 — Unblock, code side (xHigh; Drew set `/effort xhigh`)
Seven docstring/comment cites re-pointed to durable records: `decl_from_use.py` + `integration_resolver.py` → the decision log's
2026-08-25 (P31 S61) "the wall is an integration wall" entry (the S60 frontier analysis's 178/292 = 61% and ~571 finished-draft
measurements live there); `jtbl_carve.py` ×3 → cookbook §260 (the leading-island split; the review's correction #7); `autopsy.py` +
`residual_class.py` → `docs/how-to-ai-decomp/03-bootstrap-order.md` Phase 2b (the permuter track — task 5 adds the "mine the permuter's
failures" paragraph there; "originally hindsight-study §7, archived" kept as provenance). `CLAUDE.md`: R-range R1–R83; the H1 fail-safe
dates the re-tightening to Phase 33 C3 (2026-09-06, the history rewrite) — the flip has not happened; the Reasoning section's "default
working level is Max" replaced by the DIGEST §1 doctrine (xHigh for most tasks, Max for deep tasks, Ultracode for breadth; plan mode
always Max). Verify: `py_compile` on the five tools OK; `git grep -E 'tool-designs|hindsight-study' tools/ Makefile` = 0; `doc_links`
OK. **Deviation from the plan's verify column:** `make tools-health` was NOT run for docstring-only edits (proportionality — nothing it
measures changed); the first tools-health of the phase runs at task 7, where the Makefile and the checkers change. Commit `a0cf302e5`.

### 2026-09-07 — Task 2 — Unblock, doc side (xHigh)
Six banners/status lines corrected in place (H5 — nothing dropped): `concurrency-design.md` "Not yet implemented" → implemented in
`shared_lock.py` + the gate snapshot layer, five citing tools named; `gen2-mips-matching-model.md` "design / not started" → built in
P22–P23, distilled by the published `matching-drafter-pipeline.md`; `psyq-worklist.md` COMPLETE at P31 S79 #5 with the residue named;
`distill/atbhbkbl.md` + `axbm.md` "PROPOSED ONLY" → LANDED as cookbook §265–§267 / §268–§269 (the banners had been false since S59b/c);
`hindsight-study.md` HISTORICAL banner + the seven-row supersession table (its §7 → `autopsy.py`/`residual_class.py`, live pointer in
how-to ch.03). `SETUP.md` §1a rewritten: `.run/` is ignored by contents (`/.run/*`) with 22 dated `!` allowlist blocks; the R20 test
("commit what a rerun cannot reproduce"); what is tracked at the prune; untracked citations are breadcrumbs; the wiki page named in
prose (no link yet — task 3 creates it). **The pin count (R75):** two published numbers came from two greps — the broad
`register\s+[^;]*__asm__` (44,243) also matched ~290 comment lines (two comment sentences repeated across 141 files, plus a `"$N"`
placeholder), the strict `\("\$[0-9a-z]+"\)` form (43,857) missed 68 pins written without `$` (`"a0"`, `"v0"`, `"v1"`, `"6"`…). Canonical
command `grep -rhoE 'register [^;/]*__asm__\("\$?[a-z0-9]+"\)' src --include=*.c --include=*.h | wc -l` = **43,925** (42,985 `.c` +
940 `.h`), written with its command into `gen3-standards.md` §4 and `gen3-handoff.md` §3 (both rows + the command block). Verify:
`doc_links` OK; the command reproduces 43,925. Commit `d06923a06`.

### 2026-09-07 — Task 3 — Wiki: the conventions page + the ROM-firewall page (Max)
Two new pages under "Working conventions" in the sidebar. `Docs-and-scratch-conventions.md`: the kind-of-knowledge → home table
(cookbook/decision-log/accelerators/runbooks/SETUP/memory-map/formats/phase-ends/how-to/wiki; a session note is never a reference),
authored vs generated with the generator table (R75 — a prose number is a dated snapshot with its command; frozen snapshots are not
regenerated), the link policy (wiki page not docs file; wiki→docs only via the Reference index; nothing links into the archive; the
pending list R80; the render refuses dead links; backticked citations classified TRACKED/UNTRACKED by git, strict only in wiki pages),
the archive procedure (git mv, index row, the referrer-census command, deletion is the owner's), and `.run/` (R12; ignored by contents
with the three-line `!` idiom quoted from the P33 verify block; the R20 test; what is tracked at this phase; the per-session layout
from the playbook's S80 addendum; never `git clean -x`; a tracked `.run/` file is published). `The-ROM-firewall.md`: the rule with the
exemption never to grant (the R1 relaxation and its bill; R74), the nine classes with the tracked form each takes instead, the
copyable `.gitignore` template in a `gitignore` fence (generic paths; the class-9 tarball note; the scratch idiom with an example
block — this block is the kit's `templates/gitignore.decomp`, byte for byte, task 11), the three enforcement layers (the audit's
derived hash set, coverage assertions, R43 refusal, the content check "since Phase 33.5", the expected-offenders control; CI) and the
one-list rule with the `untracked_after_rewrite.txt` sibling, the rewrite lessons as R76/R77/R81/R82/R78, the one recorded residue
(the two `fable_cd4` listings; the owner's decision and its reasoning), and the day-one pointer to the kit. Cross-links: Repository-
layout (`docs/` row, `.run/` row, the not-in-repo section, R1…R83), Contributing (the firewall paragraph; "83 numbered rules"), how-to
ch.11 (the day-one section + the proposed-rules heading now says "ratified as R74–R80"). Forward links registered as PENDING:
`Reference-index.md` (task 4), `Archive-index.md` (task 6). Verify: `wiki_render --selftest` OK; `doc_links` 0 broken / 2 pending.
Commit `5d10a0d12`.

### 2026-09-07 — Task 4 — Wiki: the Reference index, the direction page, Contributing's conduct section, Home + sidebar (xHigh)
`Reference-index.md`: 47 rows in seven groups (environment and verification; formats and addresses; the knowledge base; verification
and progress (generated); releases and outreach; the record; Gen3 inputs) + four directory rows (`gcc-2.7.2-map/`, `badges/`,
`outreach/`, `history/`) — each with what it is, how to read it (the 3.5 MB / 560 KB warnings), who writes it; the page states it is the
only sanctioned wiki→`docs/` link site and that the two index pages are exempt. `Where-the-project-goes-next.md`: Phase 34 (the
probe-gated flip, the outward actions in the maintainer's words, aftercare, v2.0.0), Gen3 (the floor, the bar — sotn's guide + the four
rules —, the census table with the ONE pin count and its command, the invariant, the order of work, the levers, the conduct rules,
shiftability scoped, the parked ideas), and the day-one-kit pointer in prose. Contributing gained "AI use — conduct" (the five rules of
gen3-standards §3, linking the direction page). `Home.md` rewritten: the source-of-truth statement + sections Using / Working conventions
/ Reference / How to AI-decomp / Where next / History; `_Sidebar.md` gained Reference, Where-next and History (Archive index, pending).
`gen3-handoff.md` §8: "R1–R73 plus candidates" → R1–R83; the last 44,243 → 43,925. `doc_links_pending.txt`: the Reference-index line
removed (1 entry left: Archive-index, task 6). **Coverage check** (a Python one-liner over `doc_links`' LINK_RE — the task-7 checker's
prototype): 132 `docs/` files outside wiki/how-to; index ∪ README covers 66; the 66 uncovered are EXACTLY the task-6 leavers (33 root
sunset + 4 integrate + 6 frozen + 12 per-binary snapshots + 11 tool-designs + 2 distill + 4 history files with spaces in their names)
plus one KEEP file the first draft omitted — `generic-decomp-package.md`, added as a row (how-to 00/06 link it). Verify:
`wiki_render --selftest` 12/12; `doc_links` 0 broken / 1 pending.

**P6 rules check — re-read complete** (CLAUDE.md's Mandatory Behavior + fail-safes, DIGEST §3 R1–R83): one task at a time, one commit
per task after this log; never overwrite blind (H5 — every banner was added, none replaced); never commit ROM content (the two
`fable_cd4` listings leave at task 8, before any push Drew makes of this phase would matter — they are already in the pushed history);
never `git clean -x`; a match is byte-for-byte (no build input has changed). Continuing with task 5.

### 2026-09-07 — Task 5 — Integrate the six documents; re-point every referrer (xHigh; three read-only diff agents)
Three Explore agents diffed the three big INTEGRATE documents against their successors; I folded, re-pointed and verified.
**`portable-decomp-workflow.md` vs the 13 chapters:** a near-superset — 6 residual items. Folded: the per-binary gate LOCK (ch.02,
the parallel bullet: worktree = isolation, lock = mutual exclusion); the one-sentence portability TEST ("still true for a PS2 game
with a different compiler → transfers"; ch.00 "What transfers"); the three-part lane-restart trap (code / arguments / per-invocation
defaults; ch.05 "Lanes"). Reconciled, not folded: the ≤30-instruction cheap-tier boundary (the chapters' ~50 is corroborated by the
A/B and ch.09 — the ≤30 was the mid-campaign figure); "~780 sections" (measured: 490 `## §` headings over 442 numbers — the chapters'
"some 500" stands). Dropped: the automation-runbook sibling mention (it sunsets), the "any language" scope claim.
**`wave-metrics.md` vs ch.05/ch.09 + playbook §5:** the chapters priced drafting by token but never per wave, never the gate, never
in instructions, and carried two claims later waves refuted. Folded into ch.09: the sourcing rule (derived from logs, the gate is the
arbiter); a "A wave, priced" table (waves 1–6, T/U/V: agents / tokens / wall / parallelism / banked) + the units (170k–300k tokens
per banked head early, ~124k mature; harvest ≈ a quarter of a wave; recovery ≈0; the seed-twin payoff 15% tokens / 64% wall;
outages as casualty counts); "Instruction weight, not head count" (the wave-5/6 table, pool realisation 43% vs 21%, wave T's
11,511); "The gate's cost is paid in wall-clock" (gate groups 5→7→9→3, drafts per rebuild 7.8→24.3, concentration is a draw-time
CHOICE, the slowest-chain floor); Drafting-yield rows (the size curve's denominator caveat — a fleet-wide curve over 37 mostly
pre-tooling waves; the prompt as the lever, mid-70s→100% with its honesty caveat; 98–100% standalone is noise, never a new floor;
claimed-vs-banked per wave, 26 of 27 rejections byte-perfect, the reconcile lane 21/22); free siblings per wave (65·18·21·26·26·25 /
49·34·25·0·1·4; the 299→4,485 case; bimodal sweep, the family owns the rate); "budget recovery against gate drops, near-misses are
permuter fuel". Folded into ch.05: the banked twin beats the open one (0/34 vs 4/4; the card builder discarded it), STEP 0 = the
magic-literal grep, verify each claim separately + the stale prefetch; the dedup numbers (22 of 44 skeletons drawn twice; 19,266
potential = 6,557 drafted + 12,709 staged; 4,954 banked free); draw by open templatable instructions, FACE vs DELIVERED mass (the
"nearly free mass" claim corrected: unknown-lever cards draft at 96–100% but yield zero siblings and a harvest of 4 vs 14), the
UNKNOWN default-flag trap (607 of 1,179); step 5: pipeline vs batched 136→82 min / 2.5×→3.8× / 37–50-min dead gaps, the six
6,500-ins waves, the difficulty knob; step 6 REWRITTEN: "gate the directory, never the verdict list" replaces "read the verdicts"
(the 362-ins NO-DRAFT and the 579-ins silent zero), the coverage assertion, gate-group concentration; NEW step 6b Reconcile before
any rebuild + "when the reconcile lane goes quiet the prompt is doing its job"; step 8: index_hit/index_gap harvest, the yield
series 9/14/14/4/7/5 vs already-covered 61/44/76/41/56/53 — "the knowledge base knew, the agents did not find it"; "Then recover":
the gate number is not the close-rate (5/8 gate vs 8/8 oracle → 8/8 after recovery), the three plumbing levers. `wave-playbook.md`
§5: the S37 execution block (the barrier-free `pipeline()` + the reduction, 46 lines, from `.run/s37w.js` — which is untracked
scratch and stays so; the ladder inside it noted as superseded by the routing line) and the coverage law (the s6f gate script's
assertion — NOT claimed to live in `gate_wave.py`: a grep found no such assertion there; worded as "whichever driver batches must
assert it"). Internal inconsistencies in wave-metrics itself (its Finding-1 series mixes numerators; "405 drafted, 405 banked" is
unsupported by its own table; wave W's draft count 69/70/71; "one more card" is two; ~45% is 47%) were NOT propagated — the table
values were used, as the agent showed the tables are the derivable ones.
**`hand-matching-process.md` vs The-matching-workflow / ch.07 / ch.02:** 48 unique items, 12 classes of STALE guidance excluded (the
55% / 136-binary numbers; pins as the lever and `func_8012B8E4` as their proof — contradicted by R73; the pre-masked-scorer
"permuter refuted" verdicts; `harvest_verify` as THE gate; the deleted signature tools' method; session scratch paths; forward plans;
historical close-rates; the "only genuine stub" narrow-param wall — dissolved by cookbook §43; the private-era NON_MATCHING line;
Ghidra program ids). Folded: a new "Matching by hand" section in `The-matching-workflow.md` (two decompiles + the asm as arbiter,
the MCP/overlay mechanics, the m2c direct invocation; the loop + the two-command red-gate diagnosis; THE FIVE SIGNATURE MOVES with
their byte-neutrality proofs and the surgical-not-blanket warning, the layer's placement, types byte-neutral vs local widths not;
choosing what to hand-match — the ascending-mismatch anti-signal, the tractable shape, the count-weighted metric, no magic five,
callees before callers, the circular callee; running it as a wave — conflicts are manufactured by parallelism (60%→33% = 100%
compile errors), draft → sig_unify → gate, chunk 1, the recovery pass, the headless pre-decompile + the FUN_ rename + opaque ids,
the Workflow args gotcha, scratch filtering, "no draft" as a valid result 12/30, propagation fail-closed + `--auto-from` + the
signature blast radius); a "Levers from the hand-matching era" list in ch.07 (the scaffold ×4 arithmetic tell, branch polarity,
rematerialize-vs-spill, the cross-jump count law, dual bases in first-use order, the mask-local idiom, `goto ret0` clustering,
v0/v1 coalescing's failed steers, the walking pointer, two phantom-frame variants, the permuter's two no-op modes, the triage
routing with the pin branch re-routed to shape per R73); two bullets in ch.02 (parallelism manufactures conflicts → normalise
before the gate, chunk 1, the recovery pass; a red gate is a hash — the two-command diagnosis; propagation as a fail-closed gate
with the blast radius). **The other three:** `generic-decomp-package.md` attributed in ch.03 (the band's numbers 22/352 → 75/352,
rank by work) — ch.06 already cited it; the hindsight §7 track → ch.03 Phase 2b (the autopsy paragraph) and `permuter-ils.md` §5;
the Gen3 pair are the direction page (task 4). ch.04 now cites `tooling-audit.md` as the evidence base.
**Referrers re-pointed (11 sites):** ch.00 :59–60 (both bullets → the archived-synthesis line), ch.02 :16 (→ ch.03), retrospective
:10 (link → archived citation), :96, :130, :143, gen3-handoff :210 (→ ch.03 Phase 1), permuter-ils :118, wave-playbook :708 (+ the
kit pointer), accelerators :7, SETUP :1312 (the S88 record line notes the archive). Census after: 0 LINKS to any of the four
leavers outside records; 6 backticked prose mentions remain, each naming the archive (`docs/sunset/…` or "archived") — the
sanctioned citation form. Verify: `doc_links` OK (1 pending), `wiki_render --selftest` 12/12.

### 2026-09-07 — Task 6 — The sunset moves + the Archive index (xHigh)
The move list was built from ledger L1 (`.run/P33.5_sunset_list.txt`, scratch) and checked against the task-4 coverage one-liner.
**One correction to the plan (R14):** `docs/family-hseq.md` is NOT a frozen snapshot — `tools/verify_contract.sh` step 02 regenerates it
as part of the recorded contract run ("family_hseq regenerated: 217 binaries scanned, 0 open instances" is the contract's own
statement) and `tools/burndown.py` reads it; it stays as KEEP-GENERATED and got a Reference-index row. The other five frozen
snapshots (`frontier-atlas`, `family-cousins`, `worklist`, `autopsy`, `burndown.jsonl`) moved. **The referrer census** (the D3 command
over all 59 basenames, excluding records/self/indexes): every hit was either a substring false positive (`calibration`, `worklist`,
`autopsy` are ordinary words and tool names), an "archived"-style prose mention written in task 5, a provenance label in a tool
comment naming an S60/S61 analysis by its short name (left as provenance — not a path), or a digest/SETUP line, which were refreshed:
DIGEST §4 rewritten around the wiki (the index pages first; `roadmap-to-100` / `frontier-p32` / `automation-runbook` named as archived,
`phase34-seed` + the Gen3 pair added), DIGEST §1's gen2-roadmap line marked archived, `SETUP.md`'s integration_resolver row and
`docs/history/README.md` updated. `resident-dossier.md`'s eight cookbook § cites all resolve to headings (§17, §37, §41, §43, §47,
§52a, §52b, §53) → safe to move. **Moved:** 59 files by `git mv` into `docs/sunset/` — 25 root documents, `distill/` 2, `history/` 4,
`tool-designs/` 11, `generated-snapshots/` 17 (the 5 frozen + the 12 per-binary reports); `docs/tool-designs/` and `docs/distill/` are
gone. **Indexes:** `docs/wiki/Archive-index.md` (six groups; every file as a backticked path + what it was / what came of it / where
it lives now, with wiki-page links only), `docs/sunset/README.md` (the ☐ review table, 59 rows; deletion is the owner's); the last
pending entry cleared. **Verify:** README rows == `git ls-files docs/sunset` (59 = 59, `comm -3` empty); every sunset basename appears
in the Archive index (0 missing); the coverage check: 64 `docs/` files outside wiki/how-to/sunset, **0 uncovered**; `doc_links`: 56
documents, 429 links, 0 pending, 0 broken; render selftest 12/12; `git log --follow` on three samples confirmed AFTER the commit
(a staged rename shows no history until committed).

### 2026-09-07 — Task 7 — The checkers (xHigh)
`tools/doc_links.py` rewritten around six checks, every count with its denominator: (1) links as before + the pending list;
(2) the archive refusal — any link into `docs/sunset/` is BROKEN; (3) wiki-first — a wiki/how-to link into `docs/` must be a target of
`Reference-index.md` or `README.md` (the allow-list is DERIVED from those two pages; the two index pages exempt); (4) coverage —
every tracked `docs/` file outside wiki/how-to/sunset is covered the same way (64 of 64); (5) citations — every backticked `docs/…`
/ `.run/…` path is TRACKED or UNTRACKED by `git ls-files` (disk-independent; `<…>`/globs/ellipses skipped; `path:12-19` forms look
up the file; `` `path` (not kept) `` is declared gone and skipped); a wiki page citing an UNTRACKED path fails; `--disk` adds the
PRIVATE/DANGLING split; (6) wiki-first WARNINGS (exit 0) from a small topic→page map — today 2 (gen3-handoff and story link
`verification.md`; left, they are records/narrative). `tools/wiki_render.py --selftest` gained the reachability assertion (every
wiki page in the sidebar; every chapter in the sidebar AND the how-to index): 31 pages, 0 unlisted. `tools/timeline.py` wired:
regenerated in `report BINARY=main` after `progress.py --json`, `--check` in `audit-digest` — it WAS stale at HEAD (72 → 73 rows: the
Phase-33 close day); the two files regenerated and committed. New `tools/gitignore_template_check.py` (the page's ```gitignore
fence == the kit's template; rc 1 drift, rc 2 no template yet — never a pass; refuses ≠1 fence) behind an existence test in
tools-health that skips loudly until task 11. **What the new checks found immediately:** the conventions page cited two files only
the future kit stamps (`docs/README.md`, `.run/README.md`) → reworded; the classifier's first cut read `path:line` cites as unknown
paths → fixed. **The R39 control on the cookbook** (`--disk docs/matching-cookbook.md`, not in the default set): BEFORE = 13
DANGLING of 276 untracked citations (the audit's "14" — its regex differed by one); of the 13, FIVE were documents this phase
archived (`tool-designs/jtbl-automation-s59.md`, `tells-lane-s59.md`, `distill/atbhbkbl.md`, `distill/axbm.md`, `frontier-p32.md`)
→ re-pointed to their tracked `docs/sunset/…` paths (my first pass had wrongly marked them "(not kept)" — caught by reading the list;
plus 5 more archived-doc cites re-pointed earlier in the task: `hand-matching-process` ×2, `exemplar_curriculum`, `phase25-frontier-map`,
`calibration`); the other EIGHT are `.run/` scratch that exists nowhere (`.run/_bak.c`, `.run/diag_plumbing.py`,
`.run/s7/scratch/spliced.c`, `.run/wave3/func_8018FF98/vA,…c`, `.run/match/func_80187130.246967/`, `.run/harvest_x/vsweep.py|vsweep.json`,
`.run/.../sweep2.py`, `.run/P32/t3/restored/sweep_func_80039308.py`) → annotated `` (not kept) `` in place. AFTER = 0 DANGLING, 263
PRIVATE (breadcrumbs, allowed in a record). `cookbook_index.py --check` OK (1,169 sections; no heading changed). Default set:
56 documents, 429 links, 0 pending, 0 broken, 551 citations (430 tracked / 121 untracked, none in a wiki page), coverage 64/64;
`--strict` OK. `make audit-digest` rc 0 with the timeline check. SETUP rows for `doc_links`, `wiki_render`, `timeline` and the new
tool (R21). The conventions page's description of the checks matches the implementation.

### 2026-09-07 — Task 8 — The tracked-`.run/` prune, the audit-only rules file, the content check (xHigh)
**Removal set = what `.gitignore` says.** After narrowing the re-includes (`!/.run/P32/t3s3/*.log` → the three cited R22 logs by
name; explicit re-excludes for the uncited duplicate close logs under t4b ×2, t4d ×2, t4e ×1; `/.run/giants/fable_cd4/*_full.txt`
after the `*.txt` allow line), `git ls-files .run | git check-ignore --stdin --no-index` yielded **218** paths — the 172 inertia files
(43 loose root files; `s6h` 38, `s6f` 25, `w6` 16, `s37` 16, `s6g` 15, `s6i` 8, `t4` 6, `s6b_cracks` 2, `fable_frontier` 2, `audit` 1) +
39 uncited `t3s3` root logs (the `gate/` verdict ledger and the 3 cited R22 logs stay) + 5 duplicate close logs + the 2 listings — and
that list IS the removal set (`git rm -r --cached`), so the ignore file and the index agree by construction. Kept: everything a
document cites (12 cited logs under `.run/P32/`, found by grepping each tracked `.log` name over docs + phase-ends + README).
**Invariants after:** tracked `.run/` 1,086 → **868**; `git ls-files -ci --exclude-standard .run` = 0; `git status --porcelain .run |
grep '^??'` = 0; all 218 removed paths still on disk; staged deletions == the list (`cmp` YES). **The firewall pair:** untracked;
`tools/public_rewrite/untracked_after_rewrite.txt` created (audit-only; the header says why it is not the purge set); `purge_set.txt`
byte-unchanged; **`gate_scan.py --all --worktree` PASS** (112,518 reachable blobs / 16.25 GB, 0 offenders, 73 s). **`audit_public.py`
check 4 (CONTENT):** longest contiguous run of disassembly-shaped lines per text file, cap 64. **R39 controls, both recorded:** the first
cut of the asm-differ shape required an operand, and `nop` lines broke the target listing's run to **60 < 64** — the control caught
it (only `mine_full.txt` at 398 failed); the shape now accepts operand-less mnemonics and `.L` label operands, and the control by
`--paths` over the pair + the two xsig fixtures reads **398 and 179 → FAIL, 14 and 14 → pass**; the full audit AFTER the untrack:
**OK — 0 offenders among 6,443 tracked paths** (6,661 before), longest runs 14/14/6. `runbook` §11 gained the residue paragraph; the
four tool comments annotate the untracked defaults (`wave_judge.py` `WAVE=.run/t4`, `claude_wave_packs.py`, `jtbl_family_bank.py`,
`dedup_propagate.py`); SETUP row for the audit (R21). **Deviation from the plan's numbers (R41):** the plan said "~50 allowlisted
logs"; the enumerated count was 44 (39 + 5) because the t3s3 `gate/` logs and every rtu/variant log under t4b/t4d/t4e are evidence
and stay — and the audit's "≈860" became 868 for the same reason.

**P6 rules check — re-read complete** (CLAUDE.md's Mandatory Behavior + fail-safes; DIGEST §3 R1–R83): one task per commit; never
overwrite blind (the `.gitignore` edits are additive re-excludes under dated comments — R60's carve-state rule does not apply, no
splat yaml or overlays.mk was touched); never commit ROM-derived content (the pair is out of the index; check 4 now guards the class);
never `git clean -x`; `purge_set.txt` never edited in this phase. Continuing with task 9.

### 2026-09-07 — Task 9 — Memory reconciliation + the kit's memory seed (xHigh)
**The project store** (`~/.claude/projects/-home-musashi-bfm-decomp/memory/`, outside git by Drew's decision): the off-project
`vantage-edge-never-leaks.md` was MOVED to `~/.claude/memory-parked/` (no Vantage project store exists under `~/.claude/projects/` —
only this project's and `-mnt-c-Users-user`, which has no memory directory; never deleted) and its index row removed. The seven
stale memories got a dated **"Updated 2026-09-07 (Phase 33.5)"** block APPENDED (the originals stay as records): the cheap-tier A/B
(→ the record; routing superseded twice), the effort doctrine (CLAUDE.md now agrees), the private-repo backup policy (HISTORICAL;
R78 is the backup), the endgame deliverables (all three shipped), roadmap-to-100 (archived; plan from phase34-seed + gen3-handoff),
the ROM-content policy (INVERTED — H1 in force, R74, the relaxation's bill), the context-system status block (P33.5 open / P34 next /
Gen3 at 35, the R64 load order). Their `MEMORY.md` hooks rewritten; two more index defects fixed while there — `continuous-gater-
lane-plan.md` had NO index row (added) and the model-ladder hook still described the dead Haiku→Sonnet→Opus ladder (now the
2026-09-01 two-tier rule). Index rows == files: 80 == 80. **The kit seed** `decomp-architect/memory-seed/`: 16 files + `MEMORY.md`
(PA 2.0's own sixteen seeds cited by name, not copied) — the three decomp seeds (`the-byte-gate-is-the-only-claim`,
`the-matching-flywheel`, `mcp-reconnect-after-restart`), the nine portable working agreements (`offline-tooling-first`,
`one-runbook-is-the-procedure`, `keep-an-accelerator-ledger`, `checkpoint-means-everything-is-already-in-a-file`,
`phaseend-carries-the-narrative-axis`, `tool-change-ships-with-its-consumers-and-docs`, `no-sleep-polling-background-tasks`,
`long-checks-run-in-the-foreground`, `resume-means-resume-the-run`, `answer-before-grinding-in-live-coop`) and the riders folded
into three more (`a-slow-gate-is-a-bug`, `breadth-is-isolated-agents`, `route-by-measured-difficulty` — the measured cliff, escalate
sooner, the frontier-agent briefing recipe, what the frontier tier is NOT for). Five carry `upstream: PA` (the harness-generic ones:
the four planned + the live co-op one). Every body de-BFM'd: no project name, owner name, paths, sessions, addresses, rule numbers
or section numbers (the kit_lint pattern + `Drew` → 0 hits); numbers appear only as "measured on the source project". **Verify:**
16 files == 16 index rows; frontmatter parses (name == stem, type ∈ the four, optional `upstream: PA`); every seed has **Why** and
**How to apply**; every index link resolves.

### 2026-09-07 — Task 10 — Kit part 1: README, intake, methodology, registry-E, corpus, PLACEHOLDERS (Max; S91)
Six files under `decomp-architect/` (sizes at commit): `README.md` 8.7 KB (the three install steps — PA 2.0 first, handing it
`intake.decomp.md`; copy the folder; "Read decomp-architect/SETUP.md and do it" — what it installs, what it does NOT (no tools;
the MANIFEST is Phase-1 work until the split), the PS1/PsyQ-complete + `TODO(platform)` scope, the PA-2.0 pin, new-projects-only,
the package tree); `intake.decomp.md` 20 KB (Part A: PA Mode-1's twelve items pre-answered with FILL markers; Part B: the
canonical phase ladder, 11 rows (0 governance+firewall → 1 extraction+manifest → 2 oracles+load map+segmentation evidence → 3
the all-assembly baseline → 4 the compiler pinned → 5 the census + the differential harness at 0% → 6 the multipliers → 7 the
codegen map + the permuter → 8 first cracks, the manual wave, the campaign → 9 publish → 10 readability), each with a
machine-checkable milestone, the tools built, the G-rules in force and the DK-kernels that earned its position; Part C: the six
readability inversions; Part D: what to tell PA's generation step about §E and the fail-safes); `decomp-architect.md` 27 KB (the
methodology, 13 sections, copied to `docs/` at install); `templates/registry-E.decomp.md` 31 KB (**G1–G65** in seven groups — the
oracles and the gate, the ROM firewall, instruments, the campaign, compiler walls, publishing and the record, the use of AI —
each with a `provenance:` line); `corpus/decomp-kernels.md` 62 KB (**DK-1…DK-64** in seven groups + the failure museum's 37
exhibits condensed and de-numbered, PA's "growing it" rule at the top, one `calibration` fence per kernel that carries a number);
`templates/PLACEHOLDERS.md` 6 KB (the contract: **22** placeholders — 4 shared with PA incl. `DOMAIN_FAILSAFES` as
referenced-only, 13 copy-time from the game interview, 5 generation-time — plus what is deliberately NOT a placeholder).
**Design decisions that bind tasks 11–13 (X1):** (a) the lint vocabulary — `§`+digit and `R`+digits are banned outside
fences/provenance, so the kit refers to PA's sections as "step N" and **the kit's own SETUP.md (task 12) uses `Step 0 … Step 10`
headings, not the plan's literal `§0–§10`** (same content, a heading form the lint allows); (b) **registry numbering by
construction** — the intake's Part D asks PA's generation step to leave §E empty except a one-line pointer, SETUP Step 7 asserts
that before appending G1–G65 and documents a renumber-by-offset fallback (no `{{N}}` placeholder); (c) **the placeholder
contract** — tasks 11/12 may add a placeholder only by editing `PLACEHOLDERS.md` in the same change; `kit_lint` diffs the set found
by `\{\{[A-Z_0-9]+\}\}` over the package against the backticked set in that file; (d) **the firewall config** carries literal hash
sources tagged `required:`/`pending:` (a missing required source fails; a missing pending one warns loudly; zero resolvable sources
refuse — R32/R43) so the audit runs at Phase 0.5 before a manifest exists; (e) **`kit_lint` must be fence-aware** — the
checkpoint's hand grep `grep -v calibration` only drops lines containing that word, not the fence CONTENTS; the honest check
(used here; the spec for task 11) strips ```` ```calibration ```` blocks and `provenance:` lines, then greps. **Verify:** lint 0 hits
over 23 files (the 6 + the 17 seed files); placeholders used 22 == listed 22; G ids 65 (1..65), DK ids 64, 0 dangling cites of
either anywhere in the kit; ladder rows 11/11 each cite ≥1 resolving DK (row 10 first cited only Part C → DK-64 "readability at
draft and bank time" added, the museum renumbered to part 8); `doc_links --strict` rc 0; `wiki_render --selftest` 12/12,
reachability 31 pages / 0 unlisted; `TODO(platform)` 5, `TODO(phase-N)` 7.
**Finding, fixed here (R58/R56 class):** at HEAD `e1463d430` `tools/doc_links.py` exited **1 in BOTH modes** — one BROKEN:
`docs/wiki/The-ROM-firewall.md` line 163 cited `.run/giants/fable_cd4/mine_full.txt`, UNTRACKED since task 8's `git rm --cached`
(the classifier is git-based by design, so the untrack flipped the verdict) — i.e. `make tools-health` was red on the docs side and
the S90 checkpoint's "`doc_links --strict` green" was stale (task 8's verify list did not include a doc_links run; the claim was
carried from task 7). Fix: the residue paragraph now names the two basenames and cites the tracked
`tools/public_rewrite/untracked_after_rewrite.txt`; strict rc 0. Lesson for task 15's checklist: re-run `doc_links --strict` after
ANY untrack, not only after a docs edit.
**Deviation from the plan's verify column (R41):** the hand grep prescribed in the checkpoint is not fence-aware; the fence-aware
script above was used instead and is what `kit_lint.py` implements. The kit's `docs/` cross-references are by chapter title and
kernel/rule id, never by this repository's paths, so the split can lift the folder unchanged.

## 🛑 SESSION CHECKPOINT — Tasks 0–10 ✓; NEXT = task 11 (kit part 2: the firewall pack, READMEs, overlays, skeletons, MANIFEST, `kit_lint`; **xHigh** — prompt Drew, R27)

### 0. How to use this block
You are a FRESH SESSION that has read `PROJECT_CONTEXT.md`, `phase-ends/DIGEST.md`, `PhaseEnd_Phase31/32/33.md` and this file, and
nothing else (R64). Replay this block verbatim, state phase / done / NEXT / effort, list the rules from the digest (R1–R83), then
WAIT for Drew. Rebuild the harness task list (16 rows, R28) marking tasks 0–10 completed and task 11 in progress.

### 1. Where we are
**Phase 33.5** (sub-phase; v1.32.0 → v1.32.1), gate 1 approved 2026-09-07 by Drew in plan mode at Max; effort follows the plan's
column (Max for tasks 12 and 15 — prompt at each transition, R27; task 11 is xHigh). Baseline HEAD `80d45b29b`; task 0 =
`39d524991`; task 1 = `a0cf302e5`; task 2 = `d06923a06`; task 3 = `5d10a0d12`; task 4 = `9970f1e62`; task 5 = `a0d4ae836`; task 6 =
`6ec4786bd`; task 7 = `21c98ed5a`; task 8 = `ae71efe56`; task 9 = `caefe9872`; S90 checkpoint = `e1463d430`; task 10 = the commit
after this block (session S91, 2026-09-07). No build input changed; the fleet is 218/218 at the Phase-33 close. Tracked `.run/` =
868; `audit_public` OK; `gate_scan` PASS; **`doc_links --strict` rc 0 again** (it was rc 1 at `e1463d430` — see the task-10 log:
the firewall page's residue citation went UNTRACKED at task 8; fixed in task 10); pending list empty. **The kit directory now
holds:** `README.md`, `intake.decomp.md`, `decomp-architect.md`, `templates/registry-E.decomp.md` (G1–G65),
`templates/PLACEHOLDERS.md` (22 placeholders), `corpus/decomp-kernels.md` (DK-1…DK-64 + the museum), `memory-seed/` (16 seeds +
MEMORY.md, task 9). Tasks 11–13 build the rest; 14–15 close. **Already banked for task 14 (R31):** the `docs/decision-log.md`
entry "P33.5 S90" — task 14 must NOT write a second one; it still owes the wiki page `Start-a-new-decomp-project.md`, the
README/`Tools-from-this-project.md` rows, the SETUP rows for the kit and the checkers, and an accelerators entry if the dry-run
earns one. Nothing runs in the background; the SessionStart hook's headless Ghidra MCP was never used (no RE work; nothing under
`ghidra/` is tracked). The plan file `~/.claude/plans/max-effort-set-plan-encapsulated-muffin.md` is a copy of the "Approved
plan" section at the end of this file — this file is the one that counts.

### 2. What NEXT does (task 11, **xHigh**) — exact steps (plan D5, "Kit part 2")
**Read first:** `decomp-architect/templates/PLACEHOLDERS.md` (THE CONTRACT — every template below uses only the 22 placeholders
listed there, and every "Used in" cell must come true or be amended in the same change), `decomp-architect/README.md` ("What it
installs" is the file list), `decomp-architect/intake.decomp.md` Part D (the four fail-safes the CLAUDE overlay states) and Part C,
`docs/wiki/The-ROM-firewall.md` (the ```gitignore fence = `templates/gitignore.decomp` BYTE FOR BYTE — `tools/gitignore_template_check.py`
from task 7 already exists and currently SKIPS LOUDLY in tools-health until the template lands; rc 1 = drift, rc 2 = no template),
`docs/wiki/Docs-and-scratch-conventions.md` (the docs/scratch READMEs' content), `/mnt/z/Storage/git/ProjectArchitect/project-architect-2.0/templates/`
(`CURRENT_PHASE.template.md`, `PhaseEnd.template.md`, `effort-map.template.md`, `cookbook.template.md`, `ops-setup.template.md`,
`CLAUDE.template.md` — the overlays APPEND marked sections to what PA stamped from these; PA's §5.1 marked-section precedent is
`## Pre-existing instructions (merged at PA 2.0 install)`), `tools/audit_public.py` (the template is a de-BFM'd generalisation of
it: sources from `config/firewall.txt`, checks 1–4, the planted-fixture control), `.github/workflows/no-rom.yml`,
`tools/bootstrap.sh`, `docs/gen3-standards.md` §2 (the formatter settings: 4 spaces, 80 columns, braces on the same line, pointer on
the type — author `.clang-format` from these; cite the style guide as provenance, do not fetch it), `LICENSE`, `src/NOTICE.md`,
`THIRD_PARTY.md`, `CONTRIBUTING`-equivalent wiki page (`docs/wiki/Contributing.md` "AI use — conduct"), and `phase-ends/DIGEST.md`'s
shape (for the digest template) + this file's 🛑 block (for the checkpoint template) + `PhaseEnd_Phase33.md`'s "What we believed"
section (for the PhaseEnd narrative axis).
**Write (all under `decomp-architect/`, de-BFM'd; the lint pattern is
`SLUS|Musashi|BFM|Druthulu|func_80|ov_SC|/home/musashi|/mnt/z|172\.17\.|\bR[0-9]{1,2}\b|§[0-9]+` outside ```` ```calibration ```` fences and
`provenance:` lines — remember `§`+digit is banned, so no `§8`-style references to PA's sections; write "step 8"):
1. `templates/gitignore.decomp` — the wiki fence, byte for byte (extract it with a script, do not retype; then run
   `tools/gitignore_template_check.py` — it must exit 0).
2. `templates/audit_public.template.py` — the audit: hash sources from `config/firewall.txt` (lines `required: <path>` /
   `pending: <path>` / `fixture: <path-to-.sha1>`; refuse if zero sources resolve; fail on a missing required; warn loudly on a
   missing pending), the four checks (purged paths, hash set, size threshold, the disassembly-shaped-content run ≥ 64 lines with the
   asm-differ / objdump / splat-comment / label-block shapes from task 8), counts with denominators, `--paths` for the control;
   `templates/firewall.txt` (the config with the fixture line and `pending:` manifest/contract lines tagged `TODO(phase-1)`/
   `TODO(phase-3)`); `templates/firewall-fixture/` (a 16-byte SYNTHETIC blob + its `.sha1`; the SETUP's control plants a copy in the
   tree, asserts the audit FAILS, removes it, asserts PASS).
3. `templates/no-rom.template.yml` — the CI: the audit on push/PR/weekly; a compile-only job left as `TODO(phase-3)`.
4. `templates/docs-README.md`, `templates/run-README.md` — the conventions page's two tables (kind of knowledge → home; the
   `.run/` rules: ignored by contents, the dated three-line `!` idiom, the R20 test "commit what a rerun cannot reproduce", the
   per-session layout, never `git clean -x`, a tracked scratch file is published).
5. `templates/ops-setup.decomp.md` — the rows appended to PA's ops-setup: version pins (`{{TOOLCHAIN_TRIPLE}}` as `TODO(phase-4)`,
   `{{COMPILER_FAMILY}}`), the extract/fleet-check commands (`{{EXTRACT_CMD}}`, `{{FLEET_CHECK_CMD}}`), the oracles
   (`{{DISASSEMBLER_MCP}}`, `{{EMULATOR_BRIDGE}}`), the machine-local dump path (`{{DUMP_PATH}}`), the git posture
   (`{{PUBLIC_OR_PRIVATE}}`), the tooling-inventory rows for the audit and the format target.
6. `templates/bootstrap.template.sh` — the fresh-clone bootstrap skeleton (toolchain fetch + verify by checksum, venv, submodules,
   the fingerprint ladder as a Phase-4 task); `bash -n` clean.
7. `templates/CLAUDE.decomp-overlay.md` — the marked section appended to CLAUDE.md: the four fail-safes (never commit game-derived
   bytes; a match is byte-for-byte AND the whole-binary hash; never `git clean -x` here; the byte gate is the only claim), the
   session-start extras (the oracle ping only when the next task is RE; the cookbook by symptom; the checkpoint replayed
   verbatim), the flywheel line naming `{{COOKBOOK_NAME}}`.
8. `templates/pa-overlays.md` — ONE file of fenced blocks, each headed by the target file and the marker text: the digest
   (synopses-only) template; the 🛑 SESSION CHECKPOINT block for CURRENT_PHASE (sections 0–3 as in this file, de-BFM'd); the
   PhaseEnd narrative axis ("What we believed, what failed and why it looked right, what it cost, what we would do sooner");
   the effort-map rows (Max on the plan, the PhaseEnd, the compiler pin, the segmentation decision, any wall verdict; breadth for
   audits/bulk drafting); the cookbook entry shape (residual · mechanism · lever · byte proof) + the triage-table skeleton keyed by
   symptom; the wave-playbook skeleton (the ten-step spine from `decomp-architect.md` part 3 with an empty "measurement" column per
   guard); `settings.json` (the SessionEnd hook PA already set + a SessionStart hook slot for the disassembler server) and
   `mcp.json` (a loopback SSE server entry with `{{DISASSEMBLER_MCP}}`).
9. The skeletons: `templates/LICENSE.skeleton.md` (`{{LICENSE_CHOICE}}` + the no-license-over-src statement), `templates/NOTICE.src.md`
   (no license asserted over the decompiled source; "clean-room" appears nowhere), `templates/README.skeleton.md`
   (`{{PROJECT_NAME}}`, `{{GAME_TITLE}}`, `{{PLATFORM}}`, `{{GAME_SERIAL}}`, `{{PROJECT_GOALS}}`, `{{COMMUNITY_WORK}}`, `{{AI_DISCLOSURE}}`,
   `{{PUBLIC_OR_PRIVATE}}`, a generated-numbers block marked `TODO(phase-5)`), `templates/CONTRIBUTING.skeleton.md` (bring your own
   dump; the AI-conduct section = G61–G65; the target's own AI policy line).
10. `templates/.clang-format` + `templates/make-format.snippet.mk` (a `format` target over `src/`).
11. `tools/MANIFEST.md` — the portable tools of the source project BY LADDER PHASE (extract/manifest; oracles/load map; baseline;
    pin/probe; census/harness/reports; signatures/twin band/dedup/families/reconcile/carves/draw filter; map/dumps/permuter/
    reproducers; cards/lanes/wave/gates/recovery/harvest; contract/bootstrap/progress/audit; the readability levers) — one row per
    tool: what it does, what it hard-codes (paths, the compiler, the platform), "copy after the split"; written as Phase-1 TASKS.
    Breadth-shaped: survey `tools/` with ONE read-only Explore agent (the SETUP rows in `docs/SETUP.md` are the index) — the
    manifest names tools by their file name (allowed) but never cites this repo's paths.
12. `tools/kit_lint.py` (in the REPO's `tools/`, wired into `make tools-health`): fence-aware leak grep (strip ```` ```calibration ````
    blocks and `provenance:` lines, then the pattern) with `--paths`; the placeholder set-diff against `PLACEHOLDERS.md`; `bash -n`
    on every `.sh`; `py_compile` on every `.py`; the gitignore template diff (delegate to `gitignore_template_check.py`); the
    `TODO(platform)`/`TODO(phase-N)` counts printed with denominators; an R39 control: a planted leak line must FAIL it. Add
    `decomp-architect/README.md` to `doc_links.py`'s DEFAULT set. SETUP rows for `kit_lint` (R21).
**Verify:** `kit_lint` clean; `gitignore_template_check` rc 0; `bash -n`/`py_compile` clean; the planted-leak control fails;
`doc_links --strict` rc 0; `make tools-health` (foreground, ~15-min timeout — the FIRST full run since task 7's wiring; read it).
Log + checkpoint; commit by explicit path. Task 12 is Max — prompt Drew to raise (R27).

### 3. Standing facts for every task of this phase
- One commit per task, after this file's log line (R8/R42 form); commit by explicit path; no trailers (R5); Drew pushes (R6).
- Forward links from any new wiki page go into `docs/doc_links_pending.txt` as `<path>\t<task N>` in the SAME commit; the render
  refuses dead relative links (exit 1); `tools/doc_links.py` non-strict is in tools-health; `--strict` at task 15 — **and after
  any untrack or archive move** (task 10's finding).
- Nothing moves while a wiki page / how-to chapter / `doc_links` DEFAULT document / tool docstring cites it — the referrer census
  command in the plan's D3 runs before every `git mv`.
- `purge_set.txt` is never edited in this phase. Never `git clean -x`. The untracked 29 GB of `.run/` is out of scope.
- Effort transitions are prompted and waited for (R27): Max for tasks 12 and 15; xHigh otherwise.
- The kit's vocabulary (task 10): rules by G-id, kernels by DK-id, PA's sections as "step N", the kit's SETUP as "Step N"; source
  numbers only in ```` ```calibration ```` fences; the placeholder set is `PLACEHOLDERS.md`'s 22 and nothing else.

---

## Approved plan (verbatim, 2026-09-07)

# Phase 33.5 — Docs consolidation, the wiki as source of truth, the tracked-`.run/` prune, and the day-one decomp kit

> **Version:** v1.32.0 → **v1.32.1**. **Gate 1** ratifies the Phase 33 candidates (a)–(j) as **R74–R83** (DIGEST §3).
> **Effort:** planning at Max (set); per-task effort annotated (R7). Phase number 33.5 per ProjectArchitect's sub-phase
> convention (`PhaseEnd_Phase33.5.md` sorts after 33 and before 34 under `sort -V`). Phase 34 (the flip) is untouched and
> follows this phase; `docs/phase34-seed.md` stays live. Reviewed adversarially by a Plan agent (12 amendments folded in).

## Context

Phase 33 closed at v1.32.0 with everything before the public flip done; Phase 34 (flip + Gen2 exit) waits on GitHub Support
(ticket #4736982). Reviewing `docs/` ahead of the flip, Drew found the tree is not publishable as a *documentation set*: ~100
authored files from 33 phases — an out-of-date study (`hindsight-study.md`, written mid-P29 at ~78%), ledgers whose banners say
"never applied" (`docs/distill/`), a 216 KB raw agent-research JSON (`docs/history/…output`), eleven per-session tool designs,
frontier analyses and worklists for sessions long closed — beside the live references. The wiki (13 pages + 13 how-to
chapters) was written in Phase 33 as a *summary layer over* those files and links back into them; it carries no page on how
`docs/` or `.run/` are used, no `.gitignore` template, no AI-conduct rules, nothing on the Gen3 standards, and no "set up a
new decomp project" installer. The tracked `.run/` evidence (1,086 files) is visible on GitHub as-is, and 172 of those files
are tracked only by index inertia. The working knowledge that ran the project — 81 memory files under `~/.claude` — is
two-thirds already written into the repo and one-third (Claude-Code harness and working-agreement wisdom) nowhere in it.

**Drew's charter (2026-09-07):** (1) the wiki is the single source of truth; every `docs/` file is KEEP / INTEGRATE / SUNSET
(`docs/sunset/`, indexed, for Drew's final review; **no information lost**); in-repo docs link wiki pages, not `docs/` files
(README's links may stay). (2) `.run/` public readiness for what git tracks only — finished work leaves tracking, post-flip
inputs stay; no scan of the untracked 29 GB. (3) The wiki documents the `docs/` and `.run/` conventions, a `.gitignore`
template and the rules that keep ROM content out of history forever. (4) A Claude Code installer in the ProjectArchitect style
that says "install ProjectArchitect 2.0 first", then sets up an entire new decomp project for the chosen game from this
project's hindsight — the optimal starting order, the ROM firewall from commit one, the flywheel, the model ladder + effort
doctrine, the strict AI-use rules, and the Gen3 readability items — built **in-tree now**, split out after the flip as xsig
was. (5) The memory store reconciled; the portable memories become the kit's seed.

**Owner decisions at this gate (AskUserQuestion, 2026-09-07):** kit in-tree now (split later) · Phase 33.5 / v1.32.1 /
ratify (a)–(j) now · sunset = `git mv` → `docs/sunset/` + `git rm --cached` of finished tracked `.run/` · the kit's SETUP.md
opens with "install ProjectArchitect 2.0 first, then this" · BFM's own memories stay in `~/.claude` (kit seed only; no
`.claude-state/` retrofit) · the two ROM-disassembly files: untrack + an audit rule + a content check in `audit_public`, **no
second history rewrite** (the tracked C + the pinned compiler already reproduce those bytes) · link form: relative in-tree
links to `docs/wiki/<Page>.md`.

## What exists (the three audits, condensed — the execution ledger; copied into `CURRENT_PHASE.md` at task 0, R30)

### The wiki mechanism (audit A §D)
`tools/wiki_render.py`: source set = `docs/wiki/*.md` + `docs/how-to-ai-decomp/*.md` **only**; how-to chapters render as
`How-to-AI-decomp-NN-name`; wiki→wiki links become page names; any other in-repo relative link becomes
`https://github.com/Druthulu/BFM-decomp/blob/main/<path>` (`tree/` for dirs, `raw.githubusercontent` for images); **a dead
relative link = RenderError, exit 1**. `_Sidebar.md`, `Home.md`'s table and `How-to-AI-decomp.md`'s table are hand-written;
nothing checks a page is reachable from the sidebar. `tools/wiki_sync.sh` deletes every `*.md` in the wiki clone and copies
the render in (`--push` is Drew's; the clone only exists after the flip). `tools/doc_links.py`: 25 `DEFAULT` documents +
globs `docs/wiki/*.md`, `docs/how-to-ai-decomp/*.md`; checks every relative Markdown link; **`docs/doc_links_pending.txt`**
(`<path>\t<task>` → PENDING instead of BROKEN; `--strict` refuses pending; must be empty at a PhaseEnd) is the mechanism for
forward links; backticked `.run/` / `docs/` citations are NOT links and are not checked. `make tools-health` runs `doc_links`
(non-strict) and only the render *selftest* (fixture), not a real render.
**Consequence:** every new page's forward links are registered in `doc_links_pending.txt` in the same commit; nothing moves
while any wiki page / how-to chapter / DEFAULT doc links it — re-point first, move second.

### docs/ classification (audit A — the classes; per-file detail in the audit table, reproduced in CURRENT_PHASE.md)
- **KEEP-LIVE (45):** `SETUP.md`, `accelerators.md`, `actor-struct.md`, `community-matching-model-plan.md`, `concurrency-design.md`
  (banner "not yet implemented" is false — six tools implement it), `debug-menu-list.txt`, `decision-log.md`, `decompme-preset.md`,
  `disc-completeness.md`, `doc_links_pending.txt`, `effort-map.md`, `formats.md`, `gen2-mips-matching-model.md` (status line stale),
  `gen3-handoff.md`, `gen3-parking-lot.md`, `gen3-standards.md`, `generic-decomp-package.md`, `idxtab-map.md`, `matching-cookbook.md`,
  `matching-drafter-pipeline.md`, `memory-map.md`, `permuter-ils.md`, `phase34-seed.md`, `psyq-sample-idioms.md`, `psyq-worklist.md`
  (add "COMPLETE at P31 S79" banner), `public-flip-runbook.md`, `retrospective.md`, `second-oracle.md`, `story.md`,
  `struct-core-pivot.md`, `tooling-audit.md` (how-to ch.04's evidence base — cite it there), `verification.md`, `wall-taxonomy.md`,
  `wave-playbook.md`, `gcc-2.7.2-map/*` (7), `outreach/*` (2), `history/README.md`, `history/claude-bfm-starting-point.md`,
  `history/project_architect_v1.3.0.md`, `history/cheap-tier-ab-experiment.md`.
- **KEEP-GENERATED (12, regenerated by a live target):** `progress.md/.json/.fleet.md`, `difficulty.md`, `duplicates.md/.cross.md`,
  `backlog.md`, `badges/*` (4), `cookbook-index.md`, `commit-map.tsv` (one-shot), `disc-ledger.md`, `story-timeline.md/.svg`
  (`timeline.py`: today wired to nothing and STALE at HEAD — it derives from `git log` dates; regenerate inside `make report
  BINARY=main` and `--check` inside `make audit-digest`, the `progress.py --check` pattern).
- **FROZEN SNAPSHOTS of the closed frontier → SUNSET, never regenerated (6):** `frontier-atlas.md`, `family-hseq.md`,
  `family-cousins.md` (`make atlas` would rewrite them EMPTY — 0 stubs), `worklist.md` (a July snapshot read by
  `make audit-frontier`, itself deliberately outside tools-health), `autopsy.md`, `burndown.jsonl`. Regenerating replaces the last
  populated snapshot with an empty document — information loss. They move to `docs/sunset/generated-snapshots/` with archive rows
  naming the generator, the fact that a regen at HEAD renders empty, and the commit of the last populated run (via
  `docs/commit-map.tsv`). No `worklist.py` wiring.
- **INTEGRATE-INTO-WIKI (6), then sunset the residue:** `gen3-standards.md` §3 (AI conduct) → Contributing + the direction page;
  `gen3-handoff.md` → the direction page; `hand-matching-process.md` → The-matching-workflow (+ch.07); `wave-metrics.md` → how-to
  ch.09/05 (+ the `.run/s37w.js` execution block → `wave-playbook.md`); `portable-decomp-workflow.md` → diff against the 13
  chapters, fold uniques into ch.03/05/09; `hindsight-study.md` → ch.03 (its §2.1 + §7; §7 is realised as `tools/autopsy.py`).
  Known referrers of hindsight: how-to 00/02, `gen3-handoff` §8, **`retrospective.md:10–11` (a DEFAULT doc — real links)**, two
  tool docstrings, backticked cites in SETUP/accelerators/permuter-ils/wave-playbook/decision-log/cookbook. **The hand list is
  not trusted: task 6 runs the referrer-census command per file.**
- **SUNSET (~55 + the 6 snapshots):** the 12 orphaned per-binary snapshots (`progress|difficulty|duplicates.{ov_SC01_005,ov_SC01_006,
  ov_SC01_077,ov_SC03_001,resident}.md`); `tool-designs/*` (11; re-point `decl_from_use.py`, `integration_resolver.py`,
  `jtbl_carve.py` first); `distill/*` (2 — "PROPOSED ONLY" banners are stale: both landed as cookbook §265–§269, verified; keep as
  the A/B evidence ledger the cookbook cites); `history/Fable5-ultracode-…output`, `history/*link.txt` (3); `automation-runbook.md`,
  `calibration.md`, `canonical-decl-reconcile-design.md`, `exemplar_curriculum.md`, `fable5-strategy-review-2026-07.md`,
  `family-endgame-megaplan.md`, `family-manifest.md`, `frontier-p30.md`, `frontier-p32.md` (PhaseEnd_Phase31 says "keep forever" →
  move, never delete), `frontier-s39.md`, `gen2-roadmap.md`, `next-session-triage-ladder.md`, `phase25-frontier-map.md`,
  `phase25-t6-curriculum.md`, `phase25-t6-fable-brief.md`, `phase26-triage.md`, `proto-correspondence.md`, `recovery-queue-s65.md`,
  `resident-dossier.md` (check each lever has a cookbook §), `roadmap-to-100.md`, `sister-decomps.md`.
- **README's own `docs/` links (stay):** verification, matching-cookbook, gcc-2.7.2-map/, decision-log, accelerators, story,
  retrospective, public-flip-runbook, commit-map.tsv, gen3-standards, permuter-ils, decompme-preset, matching-drafter-pipeline,
  how-to-ai-decomp/00-README (+ badges/progress.json).
- **Wiki coverage gaps (audit A §E):** `.run/` = one table cell; `docs/` layout = one prose row; gitignore rules = prose, **no
  template**; accelerators = links only; portable-decomp-workflow / generic-decomp-package = one link each; gen3-standards /
  gen3-handoff / AI conduct = **absent**; no "start a new decomp" document (ch.03's 12-item checklist is the closest). `SETUP.md`
  §1a still says `.run/` is "never committed" — false since P25. `CLAUDE.md` line 11 says "R1–R64", line 61 "since the public flip
  (Phase 33)" (should be "since Phase 33 C3"), and its "default working level is Max" contradicts DIGEST §1's xHigh doctrine.

### Tracked `.run/` (audit B — 1,086 files / 15 MB; spot-checked this session)
- **172 tracked-but-ignored** (verified: `git ls-files .run | git check-ignore --stdin --no-index | wc -l` = 172): `s6h` 38, `s6f`
  25, `w6` 16, `s37` 16, `s6g` 15, `s6i` 8, `t4` 6, `s6b_cracks` 2, `fable_frontier` 2, `audit` 1, **43 loose root files**.
  `git rm --cached` is self-sealing (no `.gitignore` edit). Move first: `wave-metrics.md:62` (`.run/s37w.js` execution block →
  wave-playbook) and `:153` (`.run/s6f_gate.py`). Tool defaults/comments citing pruned paths get a "(untracked since P33.5)"
  note: `wave_judge.py:8`, `claude_wave_packs.py:16`, `jtbl_family_bank.py:380`, `dedup_propagate.py:114`.
- **Allowlisted FINISHED session logs (enumerated at task 8):** `.run/P32/t3s3/` (67 tracked; 44 `.log`, 15 of them `bank_*`);
  the duplicate `tools_health.log` / `report_close.log` copies under `t3s3`/`t4b`/`t4d`/`t4e` — keep any copy a doc cites
  (`verification.md` cites `.run/P32/t4e/r22_check.log`); narrow their `.gitignore` re-includes.
- **KEEP-TRACKED (~860 after the prune):** `P33/verify` (cited by verification.md, two wiki pages, the CI header,
  `verify_contract.sh`'s cleanliness assertion), `P33/e1` (E1 open in Phase 34), `P32/**` drafts/notes/banks (PhaseEnd_Phase32:
  "the only copy"), `giants` (cookbook ×12+), `S79w`, `s42`, `s43`, `s45`, `wave22`, `near6`, `fable_80178004`, `probe_jtbl`
  (a project-built TU, not ROM), 7 allowlisted root files.
- **FIREWALL:** `.run/giants/fable_cd4/{mine_full.txt,target_full.txt}` (verified: 398/399 lines of `0: 27bdffc0 addiu sp,sp,-64` /
  `0: addiu      $sp, $sp, -0x40`), allowlisted by `!*.txt`, invisible to `audit_public` (path/hash/size). **`purge_set.txt` is
  also `gate_scan.py`'s census over reachable HISTORY** — adding a rule there with no rewrite turns the runbook's first-push gate
  red permanently. So: an audit-only sibling file (D4).
- **POST-FLIP-PENDING:** `.run/decompme/`, `.run/public_rewrite/`, `.run/objdiff/` — **0 tracked files**; on-disk only, governed by
  `phase34-seed.md` tasks 2 and 7. Nothing to do.
- **Doc citations of `.run/`:** 653 backticked, 58 tracked / 581 untracked-on-disk / 14 dangling (cookbook :36918 etc.). Any
  disk-dependent check would go red on a fresh clone — the checker must be disk-independent (D2).

### Memory store (audit C — 81 files + MEMORY.md, all outside git)
- **(1) ALREADY-IN-REPO — 52.** Five carry portable riders: the quadratic main-loop-context arithmetic; the accelerator-ledger habit
  as a rule; the per-stuck-lane briefing recipe; "a slow gate is a BUG"; what the frontier model is NOT for.
- **(2) PORTABLE-NOT-IN-REPO — 14:** in PA 2.0's seed already (cite): repo-self-contained-claude-state, drew-working-preferences
  (→ `who-is-dev`), dont-block-loop-with-askuserquestion, justify-new-tools-before-adopting, clarify-misconception-before-costly-action.
  **New for the kit:** no-sleep-polling-background-tasks, live-coop-answer-before-grinding, tools-health-foreground-not-background,
  resume-means-resumefromrunid, tool-change-updates-siblings-and-docs (+ no end-of-session audits), bank-idioms-before-checkpoint,
  phaseend-verbosity-for-the-retrospective, offline-tooling-first, wave-playbook-is-the-procedure; + the five riders; + three decomp
  seeds (matching-flywheel R16, byte-gate-is-the-only-claim, mcp-reconnect-after-restart R29). The four harness-generic ones
  (no-sleep-polling, tools-health-foreground, resume-means, tool-change-updates-siblings) are tagged `upstream: PA` so the split
  phase sends them to ProjectArchitect instead of burying them in a decomp kit.
- **(3) BFM-SPECIFIC — 9** (keep, not seeded). **(4) STALE — 7** (update in place: cheap-tier-ab-validated, effort-doctrine-xhigh-default
  — the memory is right, CLAUDE.md is stale —, private-repo-backup-policy, project-endgame-deliverables, roadmap-to-100,
  rom-content-git-policy, bfm-decomp-context-system's status block). **(5) OFF-PROJECT — 1:** vantage-edge-never-leaks — **move**
  it to the Vantage project's memory directory under `~/.claude/projects/` (find it with `ls`), never delete from a store with no
  history; the kit's `who-is-dev` interview carries a generic "cross-project export policy" line with none of its content.
- **Other defects:** pin count 43,857 (`gen3-standards.md` §4) vs 44,243 (`gen3-handoff.md` §3) — re-derive once, publish one number
  as a dated snapshot WITH its command in both docs and the wiki (the "re-derive, do not trust" form gen3-handoff already uses).

### ProjectArchitect 2.0 (the model for the kit — and the constraint on it)
Package at `/mnt/z/Storage/git/ProjectArchitect/project-architect-2.0/`: `SETUP.md` (§0 execution contract; `✓ Verify` per step;
idempotent via `CURRENT_PHASE.md` checkboxes; commit by explicit path; never push; §8 fills the generation-time placeholders
`{{DOMAIN_FAILSAFES}}`/`{{DOMAIN_SESSION_START_EXTRAS}}`/effort-map/cookbook/ops-setup via the Mode-1 intake, **then §9 hard-stops**;
`PROJECT_CONTEXT.md` is permanent from then on, PA P1). `templates/` (CLAUDE, PROJECT_CONTEXT skeleton, RULES_REGISTRY seed §A–§M
+ §E project rules with provenance tags + §F per-phase, CURRENT_PHASE with a per-task checkpoint log but **no verbatim SESSION
CHECKPOINT block**, PhaseEnd **without** the believed/failed/sooner axis, cookbook, effort-map, ops-setup), `corpus/`, `memory-seed/`
(16 + `MEMORY.md` rows `- [title](file) — line`; §5 verifies the count 16), `statusline/`, `tools/backup-claude-state.sh`.
BFM runs the older PA 1.3.0 layout (no `RULES_REGISTRY.md`); the kit targets **PA 2.0** and is not testable against BFM — it
must therefore **pin the PA version it overlays** and refuse otherwise (R43).

## Design

### D1. Wiki information architecture (the target `_Sidebar.md`; every new page's sidebar row ships in the page's own commit)
- **Home** (rewritten; "records behind the wiki" → the Reference index).
- **Using the project** — the existing 10 pages. Contributing gains "AI use — conduct" (gen3-standards §3 summarised, linking the
  direction page); Repository-layout's `docs/` and `.run/` rows link the conventions page.
- **Working conventions** (NEW) — `Docs-and-scratch-conventions.md`: where each kind of knowledge goes (cookbook / decision-log /
  accelerators / runbook / PhaseEnd / DIGEST); authored vs generated ("numbers are generated, never typed"); the `doc_links`
  contract + pending list; `docs/sunset/` + the archive index; frontier snapshots are frozen at the closed frontier; `.run/`: R12,
  the contents-exclude + `!` allowlist idiom with its dated provenance comment, "commit what a rerun cannot reproduce", the
  per-session `.run/<session>/` layout, untracked-`.run/` citations are private breadcrumbs, the citation checker. ·
  `The-ROM-firewall.md`: H1 with **no private exemption**; the nine classes of ROM-derived content; the **copyable `.gitignore`
  template** (a fenced block that must `diff` clean against the kit's `templates/gitignore.decomp` — one tools-health line);
  `audit_public` + the no-ROM CI + one purge set consumed by audit AND rewrite; the content check; cite-by-date; the post-purge
  realities; the one recorded residue (the two `fable_cd4` files, in history by owner decision).
- **Reference** (NEW) — `Reference-index.md`: one row per KEEP-LIVE / KEEP-GENERATED file, grouped (environment · formats and
  addresses · the knowledge base · verification and progress · releases · Gen3 inputs · history/), each with what it is, how to read
  it, who generates it. **The only sanctioned place for wiki→`docs/` links**; a directory row (`gcc-2.7.2-map/`, `badges/`) is a
  prefix. The two index pages are exempt from the rules they define.
- **How to AI-decomp** — 13 chapters unchanged in number; ch.03 absorbs hindsight §2.1/§7; ch.05/09 absorb wave-metrics; ch.04 cites
  tooling-audit; ch.11 links The-ROM-firewall; ch.03/06 attribute generic-decomp-package.
- **Where the project goes next** (NEW) — `Where-the-project-goes-next.md`: Phase 34 (from phase34-seed) and Gen3 (standards §1–§3
  in summary, the census with one dated pin count + its command, the invariant, the levers, the order of work, parked ideas).
- **Start a new decomp project** (NEW, task 14) — `Start-a-new-decomp-project.md`: (1) install ProjectArchitect 2.0, handing PA's
  interview the kit's `intake.decomp.md`; (2) "Read decomp-architect/SETUP.md and do it"; what it installs and what it does NOT;
  the hindsight phase ladder; the AI-use rules; the Gen3 items at day one; the memory seed; the tools manifest; the accelerators as
  a one-line-per-entry table.
- **History** (NEW section) — story, timeline, retrospective (via the index), `Archive-index.md` (NEW): every sunset file — what it
  was · its outcome · where the information lives now. **Rows cite the file as a backticked path + the `v1.32.1` tag, never as a
  link into `docs/sunset/`** — the index must outlive the folder's deletion without turning `doc_links`/`wiki_render` red.

### D2. Link policy — `tools/doc_links.py` extensions (task 7), wired into tools-health
- Canonical target = the wiki page, as a relative in-tree link to `docs/wiki/<Page>.md`.
- **Refuse** any link into `docs/sunset/` from any document (no permitted referrer — the archive index uses backticked paths).
- **Refuse** a wiki/how-to link into a `docs/` file not listed in `Reference-index.md` (the allowlist is derived from the index page
  with `LINK_RE`, resolved paths, directory rows as prefixes — R33; introduced only after tasks 4/6 exist).
- **Warn** (list, exit 0) on non-README in-repo docs linking a `docs/` file whose topic has a wiki page (a small topic→page map).
- **Backticked citations, disk-independent:** classify every `` `.run/…` `` and `` `docs/…` `` citation in the checked set as TRACKED
  / UNTRACKED (`git ls-files`, never the disk); **fail** only when a wiki/how-to page cites an UNTRACKED path (exempt `<…>`
  placeholders); print counts with denominators for the records (R41); a local-only `--disk` flag adds the PRIVATE/DANGLING split
  for the R39 control (the 14 dangling cookbook lines are fixed once by hand). PhaseEnds and `phase-ends/logs/` are records —
  excluded from the citation rules.
- **Reachability:** `wiki_render.py --selftest` (or `doc_links`) asserts every `docs/wiki/*.md` except `_Sidebar/_Footer/Home` is
  linked from `_Sidebar.md`, and every how-to chapter appears in `_Sidebar.md` and `How-to-AI-decomp.md` (0 unlisted today).
- **Coverage:** from task 7 on, `git ls-files docs ':!docs/sunset' ':!docs/wiki' ':!docs/how-to-ai-decomp'` ⊆ (Reference-index targets ∪
  README targets), computed with `LINK_RE` over both pages (resolved paths; prefixes) — not substring grep.

### D3. Sunset mechanics
Per file, in this order: (1) fold unique content into its wiki page; (2) **referrer census by command** — `git grep -n -F
'<basename>' -- '*.md' '*.py' '*.sh' Makefile ':!phase-ends/PhaseEnd_*' ':!phase-ends/logs' ':!docs/sunset'` must return only
`Archive-index.md` / `docs/sunset/README.md` rows; (3) `git mv docs/<path> docs/sunset/<same path>` (subfolders
`generated-snapshots/`, `tool-designs/`, `distill/`, `history/`); (4) the archive-index row + the `docs/sunset/README.md` review row
(file · class · ☐ reviewed). Set-equality check: `comm -3` of the paths in `Archive-index.md` and `docs/sunset/README.md` vs
`git ls-files docs/sunset ':!docs/sunset/README.md'` is empty. DIGEST §4's doc map and `docs/history/README.md` are refreshed in
the same task. Deletion is Drew's, at Phase 34 or later; nothing in this phase deletes a document.

### D4. Tracked `.run/` prune (task 8)
(1) `git rm -r --cached` the 172 inertia paths (after task 5 moved the two `wave-metrics` citations); (2) the finished session
logs: `git rm --cached` + narrow their `.gitignore` re-includes; (3) the two firewall files: `git rm --cached`, a `.gitignore`
exclusion, and a **new audit-only rules file `tools/public_rewrite/untracked_after_rewrite.txt`** (dated provenance comment:
"remains in history by owner decision 2026-09-07 — the tracked C reproduces the bytes"), read by `audit_public.py` check 1
alongside `purge_set.txt` (refuse if empty, R43); **`purge_set.txt` stays equal to the rewritten set** so `gate_scan.py --all`
stays green; runbook §11 + The-ROM-firewall cite the file; (4) `audit_public.py` check 4 — CONTENT: shapes derived from the
offenders (asm-differ `^\s*\d+:\s+[a-z]{2,8}(\.[a-z]+)?\s+(\$|-?0x|-?\d|[a-z_])`, objdump `^\s*[0-9a-f]+:\s+[0-9a-f]{8}\s+\w+`,
splat `/* ADDR HEX hex */`, `glabel`/`dlabel` blocks); criterion = longest CONTIGUOUS run per file, threshold 64 lines; prints each
file's max run with denominators; **R39 controls recorded in the log: before untracking exactly the 2 files fail; after, 0 —
and `tools/xsig/tests/fixture_{a,b}.txt` (40 lines, the project's own function) pass.** Verify: the removal list is enumerated in
the log entry and `git diff --name-only --diff-filter=D HEAD~1 | sort` equals it; `git ls-files -ci --exclude-standard .run | wc -l`
= 0 (the real invariant); `git status --porcelain .run | grep -c '^??'` = 0; every removed path still exists on disk; the four
tool defaults carry the note; `audit_public.py` OK; CI `no-rom` green on Drew's next push.

### D5. The kit — `decomp-architect/` (in-tree; mirrors PA 2.0's package shape; runs AFTER PA 2.0 as the project's Phase 0.5)
**The slot.** PA's constitution is permanent after PA §9 and PA §8 fills the domain placeholders during the PA install, so the kit
never writes `PROJECT_CONTEXT.md`. Instead it ships **`intake.decomp.md`** — PA Mode 1's 12 intake items pre-answered for a decomp
plus the hindsight phase ladder with machine-checkable milestones — which the developer hands to PA §8 during the PA install.
The kit's own `SETUP.md` then runs as **Phase 0.5** and does marked-section APPENDS (PA §5.1's precedent) to `CLAUDE.md`
(decomp fail-safes + session-start extras), `RULES_REGISTRY.md` §E (G-numbers, each with `provenance: BFM …` per PA's registry
rule — never BFM R-ids), `docs/effort-map.md`, `docs/<project>-cookbook.md`, `docs/ops-setup.md`, and appends rows to
`.claude-state/memory/MEMORY.md` (PA §5's count 16 becomes 16+N). §1 asserts `grep -q '^> \*\*Version:\*\* 2\.0'
docs/project-architect.md` and `RULES_REGISTRY.md` + `phase-ends/` exist, else STOP and send the user to PA (R43); an existing
decomp repository (PA Path B/C) is an explicit STOP — out of scope for this version.
```
decomp-architect/
  README.md                 for humans: (1) install PA 2.0 with intake.decomp.md as the interview input; (2) copy this folder;
                            (3) "Read decomp-architect/SETUP.md and do it"; what it installs; what it does NOT (see below); scope
  intake.decomp.md          PA Mode-1 intake pre-answered + the phase ladder (milestone · tools built · rules ratified · the
                            accelerator/retrospective citation that earned its position)
  SETUP.md                  §0 contract · §1 PREREQUISITES (PA 2.0 pinned; Path A only) · §2 the game interview (title, platform,
                            region/serial, dump path, container layout, SDK/compiler-era evidence, community work, goals, the
                            AI-disclosure + license decisions) · §3 the ROM firewall from commit one (gitignore, audit + its
                            planted-fixture negative control, no-rom CI, config/firewall.txt) · §4 layout + conventions READMEs ·
                            §5 toolchain bootstrap skeleton (bootstrap.template.sh; the fingerprint ladder as a Phase task) · §6 the
                            flywheel SKELETON (cookbook seed, effort map, the MANIFEST as Phase-1 tasks — the tools are NOT installed)
                            · §7 registry §E appends (G-rules, distilled R-rules, AI conduct, Gen3-at-day-one) · §8 CLAUDE/effort/
                            cookbook/ops-setup overlays + LICENSE/NOTICE/README/CONTRIBUTING skeletons · §9 memory seed + corpus ·
                            §10 verify (placeholder diff against PLACEHOLDERS.md), manifest, gitignore the package, delete-the-package
                            note, hard stop. Every step `✓ Verify`; idempotent via CURRENT_PHASE.md; `--answers <file>` unattended
                            mode ("if the file exists every question is answered from it; an unanswered question STOPs, never defaults")
  decomp-architect.md       the methodology: the ladder; the byte gate; lanes/waves; flywheel laws; models/effort as METHOD (BFM
                            numbers only inside ```calibration fences); conduct; Gen3-at-day-one; what stays hard
  templates/                gitignore.decomp · audit_public.template.py (hash sources from config/firewall.txt, R32 refusal when
                            absent) · no-rom.template.yml · firewall-fixture/ (a 16-byte synthetic blob + its sha1) ·
                            docs-README.md · run-README.md · ops-setup.decomp.md · bootstrap.template.sh · CLAUDE.decomp-overlay.md ·
                            registry-E.decomp.md · pa-overlays.md (ONE file of fenced blocks: DIGEST synopses-only template, the
                            🛑 SESSION CHECKPOINT block for CURRENT_PHASE, the PhaseEnd narrative axis, effort-map, cookbook,
                            wave-playbook, settings.json, mcp.json) · LICENSE/NOTICE/README/CONTRIBUTING skeletons · .clang-format
                            (sotn's) + a `make format` snippet · PLACEHOLDERS.md (copy-time vs generation-time; the grep is a diff)
  corpus/decomp-kernels.md  accelerators A1–A9/#12–#20/S77–P32 + the failure museum + retrospective §4, de-BFM'd; PA's "growing it" rule
  memory-seed/              the 9 new + 5 riders + 3 decomp seeds; MEMORY.md rows in PA's format; PA's 7 cited, not duplicated
  tools/MANIFEST.md         portable BFM tools by stage: what each does, BFM hard-codes flagged, "copy after the split" — Phase-1 tasks
```
**Honesty (R41/R43):** the installer verifies skeleton documents and config; it does not install a byte gate, a permuter harness
or an m2c context — those are Phase-1 tasks from the MANIFEST until the split phase de-BFMs the tools. `SETUP.md` says so.
**Leak instrument:** `tools/kit_lint.py` in tools-health — grep `SLUS|Musashi|BFM|Druthulu|func_80|ov_SC|/home/musashi|/mnt/z|172\.17\.|
\bR[0-9]{1,2}\b|§[0-9]+` over `decomp-architect/` outside ```` ```calibration ```` fences and `provenance:` lines; the placeholder-set
diff against `PLACEHOLDERS.md`; `bash -n` / `py_compile`; the gitignore-template `diff` against the wiki's fenced block.
**Platform scope:** generic in structure, PS1/PsyQ-complete in content; other platforms get `TODO(platform)` markers (R43).

### D6. The dry-run (task 13) — write-scope guardrails
A subagent in `.run/P33.5/kit-dryrun/repo/` (a throwaway `git init`), with PA 2.0 copied from `/mnt/z/…/project-architect-2.0/`
and the kit copied in, runs PA's install then the kit's, from `answers.md`: fictional title + serial `SLUS-99999`, a dump path that
does not exist, container/SDK-evidence strings, goals, license + AI-disclosure choices, PA §1 = Path A, PA §5 answers, "effort Max
already set" for PA Gate 2 (logged as a deviation), pinned `INSTALL_DATE`, **"skip PA §6"** (no writes under `~/.claude`), the
synthetic control blob + sha1, positive AND negative `git check-ignore` probes (`disks/x.bin`, `asm/x.s`, `extracted/x` vs
`src/main.c`, `config/x.yaml`), and `expected-manifest.txt` so "manifest present" is a `diff`. The brief forbids `git clean`
anywhere and relative `rm -rf`; every git call is `git -C <abs>`. Before/after assertions by the main session: `sha1sum
~/.claude/settings.json ~/.claude/statusline.sh`, `ls ~/.claude/projects/-home-musashi-bfm-decomp/memory | wc -l`, `git -C
~/bfm-decomp status --porcelain`, `ls ghidra | wc -l`, `ls dumps/*.bin | wc -l` — all unchanged (R57). `.gitignore` gains one
block: `!/.run/P33.5/` `/.run/P33.5/*` `!/.run/P33.5/kit-dryrun/` `/.run/P33.5/kit-dryrun/*` `!…/answers.md`
`!…/expected-manifest.txt` `!…/*.log` (the nested repo stays ignored). **Cut line:** if the dry-run is still red at the end of
session 3, ship `decomp-architect/KNOWN-DEFECTS.md`, make the re-run the split phase's first task, and the PhaseEnd says so (R66).

### D7. Governance for the phase
Gate 1 ratifies (a)–(j) → **R74–R83** (full text from PhaseEnd_Phase33 → DIGEST §3, the gate-1 commit); `phase34-seed.md`'s
"candidates proposed" line amended. One commit per task after the CURRENT_PHASE log line (R8/R42 form). No `src/`/`config/`
build inputs change → no R22 fleet rebuild; `make tools-health` (foreground, ~15-min timeout) is the gate, plus a **real render**
at task 15. P6 rules check after tasks 4, 8, 12. Forward links always via `doc_links_pending.txt`, emptied by task 15.

## Tasks (in order; one commit each; effort per R7)

| # | Task | Effort | Verify |
|---|---|---|---|
| 0 | **Gate 1 close-out:** `phase-ends/CURRENT_PHASE.md` (this plan as the checklist + the ledgers + a 🛑 checkpoint); R74–R83 into DIGEST §3 (+ §0 "Phase 33.5 open"); amend `phase34-seed.md`; TaskCreate one task per row (R28) | Max | DIGEST diff shows R74–R83; TaskList = 16 rows |
| 1 | **Unblock, code side:** re-point tool docstrings (`decl_from_use.py`, `integration_resolver.py`, `jtbl_carve.py` → cookbook §; `autopsy.py`, `residual_class.py` → the ch.03 anchor); CLAUDE.md lines 11 ("R1–R83"), 61 ("since Phase 33 C3"), the effort-default sentence → DIGEST §1's doctrine | xHigh | `git grep -n 'tool-designs\|hindsight-study' tools/` = 0; tools-health OK |
| 2 | **Unblock, doc side:** banners/status lines (`concurrency-design` implemented, `gen2-mips-matching-model` built, `psyq-worklist` COMPLETE, `distill/*` LANDED as §265–§269, `hindsight-study` HISTORICAL + supersession table); SETUP §1a rewritten (the allowlist idiom, what IS tracked); the pin count re-derived (one grep, one dated number + command in both gen3 docs) | xHigh | `doc_links` 0 broken; the pin-count command reproduces the number |
| 3 | **Wiki — conventions + firewall:** `Docs-and-scratch-conventions.md`, `The-ROM-firewall.md` (the gitignore template block); sidebar rows; Repository-layout/Contributing/ch.11 links; forward links registered in `doc_links_pending.txt` | Max | `wiki_render --selftest`; `doc_links` 0 broken (pending allowed) |
| 4 | **Wiki — reference + direction:** `Reference-index.md` (list-driven: every KEEP-ledger path has a row), `Where-the-project-goes-next.md`, Contributing "AI use — conduct", Home rewritten, sidebar sections. **P6 rules check** | xHigh | every KEEP-LIVE/GENERATED ledger path appears (script over LINK_RE); render selftest |
| 5 | **Integrate the six** (hand-matching-process, wave-metrics + the s37w block → wave-playbook, portable-decomp-workflow diffed vs the 13 chapters, generic-decomp-package attributed, hindsight §2.1/§7 → ch.03 + permuter-ils, gen3 docs → the direction page); re-point every referrer incl. `retrospective.md:10–11` | xHigh (the three diffs may fan out to agents — breadth) | `doc_links` 0 broken; a per-file "unique claims folded" checklist in the log |
| 6 | **Sunset moves** per D3 (~61 files incl. the 6 frozen snapshots); referrer census by command per file; `docs/sunset/README.md`; `Archive-index.md` rows (backticked paths + tag); DIGEST §4 + `docs/history/README.md` refreshed | xHigh | `comm -3` empty; `git log --follow` on 3 samples; `doc_links` 0 broken |
| 7 | **Checkers:** `doc_links.py` extensions per D2; reachability in `wiki_render --selftest`; `timeline.py` regen in `report BINARY=main` + `--check` in `audit-digest`; the 14 dangling cookbook cites fixed (+ `cookbook-index` regen); the gitignore-template diff line; tools-health wiring; SETUP rows (R21) | xHigh | `doc_links --strict` 0 broken/0 pending/0 untracked-cited; R39 control with `--disk`: the pre-fix tree fails on exactly the 14; coverage ⊆ check passes |
| 8 | **Tracked `.run/` prune** per D4 (the 172 + the session logs + the 2 firewall files; the audit-only rules file; the content check with both controls; runbook §11; the four tool notes). **P6 rules check** | xHigh | the D4 verify list, all recorded in the log |
| 9 | **Memory reconciliation:** move the off-project file; update the 7 stale in place; refresh `bfm-decomp-context-system`; write the seed set under `decomp-architect/memory-seed/` (+ `upstream: PA` tags) | xHigh | `MEMORY.md` rows == files; frontmatter valid; `kit_lint` grep clean on the seeds |
| 10 | **Kit part 1:** `README.md`, `intake.decomp.md`, `decomp-architect.md`, `templates/registry-E.decomp.md`, `corpus/decomp-kernels.md`, `templates/PLACEHOLDERS.md` | Max | every ladder phase cites an accelerator/retrospective item; `kit_lint` clean |
| 11 | **Kit part 2:** the firewall pack (gitignore, audit template + `config/firewall.txt`, fixture, no-rom yml), docs/run READMEs, ops-setup, bootstrap, CLAUDE overlay, `pa-overlays.md`, LICENSE/NOTICE/README/CONTRIBUTING skeletons, `.clang-format` + format snippet, `tools/MANIFEST.md`; `tools/kit_lint.py` in tools-health | xHigh | `kit_lint` clean (placeholder diff, `bash -n`, `py_compile`, gitignore diff vs the wiki block) |
| 12 | **Kit part 3 — `SETUP.md`** per D5 (§0–§10, `--answers`, the version pin, the honesty section, Path A only). **P6 rules check** | Max | placeholder diff clean; a structural read-through against PA's SETUP.md |
| 13 | **Dry-run install** per D6; fix defects; re-run to green; the answers fixture + expected manifest + logs tracked under `.run/P33.5/kit-dryrun/` | xHigh | manifest `diff` empty; placeholder grep clean; both check-ignore probe sets; trailer-free commits; the before/after assertions unchanged |
| 14 | **Wiki `Start-a-new-decomp-project.md`** + README/`Tools-from-this-project.md` rows + SETUP rows for the kit and the checkers (R21) + `decision-log.md` P33.5 entry (R31) + `accelerators.md` entry if the dry-run taught one | xHigh | render selftest; `doc_links --strict` |
| 15 | **Close:** a real render to `.run/P33.5/wiki-render/`; `make tools-health` foreground; `doc_links --strict`; `audit_public`; `git status` clean; `PhaseEnd_Phase33.5.md` (Build Log, Deviations, believed/failed/sooner, rules, changelog, recap), DIGEST §0/§2 append, `CURRENT_PHASE.md` → `phase-ends/logs/Phase33.5.md`; left uncommitted for Drew (R6) | Max | every checkbox walked (P7); pending list empty; the R18/R25 recap |

**Scale, with its denominator (R41):** 16 tasks. Calibration: Phase 33 was priced at 17–21 sessions and took 4 (59 commits);
this phase is roughly half of P33's writing plus one novel item (the dry-run). Estimate **2–3 sessions**; the kit (tasks 10–13)
is about half the work; the cut line is D6's.

## Verification (end of phase)
- `make tools-health` OK (foreground): the existing chain + `doc_links` (with D2) + render selftest with reachability +
  `timeline --check` + `kit_lint` + the gitignore-template diff.
- A real `wiki_render.py` run exits 0; `doc_links --strict` 0 broken / 0 pending / 0 untracked-cited from wiki pages.
- `tools/audit_public.py` OK incl. check 4; both R39 controls recorded (2 before / 0 after; xsig fixtures pass).
- `git ls-files -ci --exclude-standard .run | wc -l` = 0; `git status --porcelain .run | grep -c '^??'` = 0; the removal list ==
  the diff; `purge_set.txt` unchanged; `gate_scan.py --all --worktree` still PASS.
- `comm -3` archive-index / sunset README / `git ls-files docs/sunset` empty; the coverage ⊆ check passes.
- Kit: the dry-run's manifest `diff` empty and the guardrail assertions unchanged; `kit_lint` clean.
- Memory: `MEMORY.md` rows == files in `~/.claude/…/memory/`; the seed has no BFM literals.
- The fleet untouched: `docs/progress.json` unchanged (218/218, 100/100/100), asserted by `make audit-digest`.

## Handoff rule for the executing session
Task 0 copies the ledgers above into `CURRENT_PHASE.md` — the audit reports exist only in this planning session's context (R30).
The 🛑 checkpoint after every task carries: the task done, the exact commands, the counts, the pending-list state, and the next
single step.
