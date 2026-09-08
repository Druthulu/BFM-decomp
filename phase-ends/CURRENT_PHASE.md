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

## Tasks (strict order; one commit per task after this file is updated; harness task list = the same rows, R28 — 16 at gate 1, 17 since the 2026-09-07 amendment)
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
- [x] **11** Kit part 2: the firewall pack, docs/run READMEs, ops-setup, bootstrap, CLAUDE overlay, `pa-overlays.md`, LICENSE/NOTICE/README/CONTRIBUTING skeletons, `.clang-format` + format snippet, `tools/MANIFEST.md`; `tools/kit_lint.py` in tools-health — xHigh — see Log 2026-09-07 Task 11
- [x] **12** Kit part 3: `SETUP.md` (Step 0–Step 10, `answers:`, the PA-2.0 version pin, the honesty section, Path A only) — Max — **then P6 rules check** — see Log 2026-09-07 Task 12
- [x] **13** Dry-run install under D6's guardrails; fix; re-run to green; fixture + expected manifest + logs tracked under `.run/P33.5/kit-dryrun/` — xHigh — see Log 2026-09-07 Task 13
- [x] **13.5** *(added 2026-09-07 by Drew — plan amendment, P5d; AMENDED the same day after the dry-run: the dictionaries, in-tree)* **Tools audit + the derived tool index + the two corpora as dictionaries:** `tools/tool_census.py` — for every file under `tools/` outside submodules/vendored code: the docstring line, its consumers (Makefile/`.mk` targets, CI, the wave playbook, its SETUP row, other tools by import or subprocess), its class (LIVE · REFERENCED · ORPHAN; PORTABLE vs PROJECT-ONLY) and its ladder phase; coverage-asserted against `find` (R32) → the generated `docs/tool-index.md` (KEEP-GEN, `--check` in tools-health, a Reference-index row, linked from The-matching-workflow + Toolchain-setup, one pointer line in how-to ch.04/05/10) whose rows are **dictionary entries keyed by the NEED they answer** (what · when the need shows up · why — the SETUP row's incident · what proved it — its consumer/control · what to adapt — the hard-codes); the kit's `tools/MANIFEST.md` RE-DERIVED from the census (`--manifest`, byte-equality asserted); the hand review of the no-consumer class (91 of 326 at S91) under **Drew's criterion: a tool that served a purpose and was REQUIRED to complete the decomp is judged on its value to a FUTURE decomp — still needed (stays live and/or becomes a port task), superseded by a better tool (retired, the row NAMING the successor), or a one-off (retired, the row naming what it produced)**; retirement = `git mv` → `tools/sunset/` only after the census proves 0 consumers, an archive-index-style row per tool, its SETUP row moved to a retired section; Drew reviews and deletes later. **The dictionaries (Drew, 2026-09-07, confirmed in-tree now):** `tool_census.py --corpus` materialises the tools VERBATIM into `decomp-architect/corpus/tools/<phase>/` (LIVE + REFERENCED portable tools and the project-only shape references; retired one-offs out; superseded ones as a pointer file naming the successor) and the knowledge base VERBATIM into `decomp-architect/corpus/cookbook/` (the cookbook, its symptom index, the codegen map) behind one front page stating what transfers (gcc 2.7.2 family = direct use, re-proven on the new bytes; other compilers = the symptom → the named pass → read the same pass in your compiler → a five-line reproducer → your lever); both copies regenerated by a `make kit-corpus` target and asserted EQUAL to the live files in tools-health (no drift, R51); `kit_lint` exempts `corpus/tools/` and `corpus/cookbook/` from the de-specialisation check (evidence, verbatim) and asserts coverage (every corpus file has an index entry) — the ROM audit covers them like everything else; the new project installs only the index + the front page + an ops-setup row naming the corpus (SETUP Step 6; its row count derived from the manifest header, no typed 325). **Two memory seeds + two registry rules** in the kit: consult-the-tool-dictionary-first (before designing or debugging a tool, look the need up; the proven implementation is the jumping-off point, its incident row the failure mode to avoid) and translate-the-source-idiom (a symptom + a named pass + a lever + a byte proof; translate through the pass, never copy the lever; re-prove on your bytes) — G66/G67 in `registry-E.decomp.md`, cited from the ladder's Phase 7 row and the methodology. **A five-tool layout-contract probe** (the corpus oracle, `match_one`, `rtu_match`, `harvest_verify`, `dedup_propagate`: count the layout assumptions — paths, aliases, config names, make targets) → `decomp-architect/templates/layout-contract.md` (a draft; stamping it at Step 4 is a split-phase decision) — xHigh (the ORPHAN review draft is breadth-shaped: one read-only Explore agent, verified against the consumer list) — verify: rows == `find` count; `tool-index --check` green; every retired tool has 0 consumers AND a named successor or product; MANIFEST regenerated byte-equal; the two corpora equal to their sources; `kit_lint` OK; `doc_links --strict` rc 0; the dry-run's Step 6 re-verified by a resume on the run-3 throwaway; `make tools-health` OK (detached) — see Log 2026-09-07 Task 13.5
- [ ] **14** Wiki `Start-a-new-decomp-project.md` + README/`Tools-from-this-project.md` rows + SETUP rows (R21) + decision-log entry (R31) + accelerators entry if earned — xHigh — **AMENDED S91 (Drew): also implement the types hindsight into the kit per `docs/decision-log.md` "P33.5 S91-b" items (a)–(e): DK-65, the Phase-6 milestone's canonical type layer, G62 extended (or G68), the type tools' need-keys re-pointed at Phase 6, the cookbook front page's width sentence, one paragraph in the methodology; then `make kit-corpus` + `tool_census --check` + `kit_lint`**
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

### 2026-09-07 — Task 11 — Kit part 2: the firewall pack, READMEs, overlays, skeletons, MANIFEST, `kit_lint` (xHigh; S91)
**Written under `decomp-architect/templates/` (18 new files):** `gitignore.decomp` (EXTRACTED by script from the wiki page's
```` ```gitignore ```` fence, 71 lines — `gitignore_template_check` now runs in tools-health and reads OK); `firewall.txt` (the audit's ONE
config: `purge:`/`glob:` rules for the nine classes with `{{TARGET_BINARY}}` as the first purge path, hash sources tagged
`required:` / `pending:` / `fixture:` — the manifest, the medium hash and the contracts are `pending:` with `TODO(phase-1/3)` promotion
notes); `audit_public.template.py` (a de-BFM'd generalisation of `tools/audit_public.py`: sources from the config, four checks incl.
the disassembly-shaped-content run ≥ 64, refuses zero resolvable sources / a missing required source / an unknown rule kind, warns
loudly on a missing pending source, `--paths` for the control; compiles); `firewall-fixture/` (`blob.bin` = the 16 synthetic bytes
`DECOMP-FIXTURE!!`, `blob.sha1` = `d4bc7b5d…`, README: only the `.sha1` is installed into the new repo as `config/firewall-fixture.sha1`;
the control PLANTS the blob under scratch, asserts FAIL by `--paths`, removes it, asserts PASS); `no-rom.template.yml` (the audit job;
compile-only as `TODO(phase-3)`); `docs-README.md` + `run-README.md` (the conventions page's two tables); `ops-setup.decomp.md` (the
decomp rows: pins with `{{TOOLCHAIN_TRIPLE}}`/`{{COMPILER_FAMILY}}`, the game/medium/dump lines, `{{EXTRACT_CMD}}`/`{{FLEET_CHECK_CMD}}`,
the two oracles, the git posture, the tooling rows); `bootstrap.template.sh` (skeleton, every phase-gated step a `TODO(phase-N)`;
`bash -n` clean); `CLAUDE.decomp-overlay.md` (the four fail-safes; the session-start extras: the digest replaces the full PhaseEnd
read, the checkpoint replayed verbatim, the oracle ping only for RE tasks, the flywheel via `{{COOKBOOK_NAME}}`, the effort line);
`pa-overlays.md` (SEVEN fenced blocks, each headed by target + marker + step: the DIGEST template (CREATE), the 🛑 SESSION CHECKPOINT
block for CURRENT_PHASE (APPEND, sections 0–3), the PhaseEnd narrative axis (APPEND), the decomp per-phase effort rows (APPEND), the
cookbook entry shape + the symptom-keyed triage table (APPEND), the wave-playbook skeleton with an empty measurement column (CREATE),
`settings.json` SessionStart slot + `mcp.json` (MERGE/CREATE)); the skeletons `LICENSE.skeleton.md` (replaced by the license's verbatim
text), `NOTICE.src.md` (no license over `src/`; "clean-room" appears nowhere), `README.skeleton.md`, `CONTRIBUTING.skeleton.md` (the
five conduct rules); `.clang-format` (the community style per gen3-standards: 4 spaces, 80 cols, Attach, pointer left, InsertBraces;
provenance comment, not fetched) + `make-format.snippet.mk` (`format` / `format-check`, dotfiles excluded). **`tools/MANIFEST.md`**
(45 KB): 325 tool files by ladder phase from ONE read-only Explore agent's survey (coverage asserted 325/325 of the find; P1 2 · P2 26
· P3 17 · P4 9 · P5 32 · P6 59 · P7 25 · P8 102 · P9 25 · P10 12 · project-only 16), each row = what it does + what it hard-codes,
framed as Phase-N TASKS until the split; the agent's ten "unsure" placements kept as given (the agent could not write the deliverable
file — read-only mode — so its inline result was transcribed; the seven `TODO(platform)` markers now include the manifest's).
**In the repo:** `tools/kit_lint.py` (six checks with denominators: fence-aware LEAK; the PLACEHOLDERS set-diff; SYNTAX by `bash -n` /
an in-memory `compile()` (the first cut used `py_compile`, which wrote a `__pycache__` INTO the kit, then refused `os.devnull`) /
JSON+YAML parse; the gitignore diff delegated; TODO counts; coverage — zero files refuses; `--selftest` = the R39 control, a planted
leak + a planted unlisted placeholder must be caught while a fenced line and a provenance line must not; rc 1/2), wired into
`tools-health` after the gitignore block; `decomp-architect/README.md` added to `doc_links` DEFAULT; the SETUP row (R21). The
PLACEHOLDERS "Used in" cells reconciled against a script listing where each placeholder actually landed (6 cells corrected; no
placeholder added — the 22-set held). **Verify:** `kit_lint --selftest` OK; `kit_lint` OK over 43 files (leak 0; placeholders used 22 ==
listed 22; syntax 0 failures over 3 scripts; gitignore 71 lines identical; `TODO(platform)` 7, `TODO(phase-N)` 31); the audit template
`py_compile`s; the CI template parses; `bash -n` clean; `doc_links --strict` rc 0 (with the kit README in the set); **`make tools-health`
OK** (run DETACHED via `setsid nohup` into `.run/P33.5/tools_health_t11.log`, 5,903 lines — the foreground cap is 10 min and the chain
runs longer — with a background pid waiter; the first full run of the phase: sigs fresh, sdk-dual both legs, corpus/cdecl/binaries/text
audits, report + audit-digest, cookbook/gccmap/roster checks, doc_links, wiki_render, gitignore check, kit_lint selftest + run, xsig 8,
work_evidence, split_indicator 218/218). The report step regenerated `docs/story-timeline.md` (the 2026-09-07 row's commit count
43 → 48; a generated file, committed — R75). **Deviations:** none from the plan's file list; the checkpoint's "audit template +
`config/firewall.txt`" landed as `templates/firewall.txt` + `templates/audit_public.template.py` + `firewall-fixture/` (three files, the
config separate from the code so a project edits the config only).

### 2026-09-07 — Plan amendment (Drew, S91): task 13.5 added
Asked whether `tools/` had been audited the way `docs/`, `.run/` and the memory store were, the measured answer was no: of 326 tool files (submodules/vendored excluded) 224 have a SETUP row, 54 a Makefile consumer, 14 CI, 34 the playbook, 4 the how-to chapters, 58 a wiki page, 210 another tool; **91 have no runtime consumer at all**; `tools/README.md` is 1 KB; the kit's MANIFEST is an agent-transcribed table. Drew: add task 13.5 (the audit + a derived tool index + the MANIFEST re-derived), and retire only on his criterion — a tool that was required to finish the decomp is judged on its value to a future decomp: still needed, superseded (name the successor), or one-off (name what it produced). Inserted after the dry-run and before the wiki page so task 14 can link the index.

### 2026-09-07 — Task 12 — Kit part 3: `decomp-architect/SETUP.md` (Max; S91)
**Written:** `SETUP.md` (25 KB): the human header (the exact instruction; `answers: <path>` for unattended runs); the **honesty
section** near the top (documents, configuration and one script; no gate/splitter/compiler/disassembler/emulator/permuter/context/
harness — those are `docs/tools-manifest.md`'s tasks; the generation-time values as `TODO(phase-N)` lines; the visibility decision is
the developer's); **Step 0** the execution contract (`KIT`/`ROOT`, `git -C "$ROOT"`; plan mode = "execute Steps 1–10"; copy verbatim +
Edit-tool fills, the two placeholder classes with the five generation-time literals; marked sections never edits; per-step ✓;
idempotent via the Phase-0.5 `CURRENT_PHASE.md`; explicit-path commits, no trailers, never push, never `git clean`, no relative
`rm -rf`, **never under the home directory**; the interview once or the answers file — a missing key STOPs, never defaults); **Step 1**
the PA-2.0 pin (twelve assertions incl. `PhaseEnd_Phase0.md` closed and exactly one cookbook), the ladder-in-constitution check with
the two owner options if absent (the constitution is never edited), the §E precondition (record k), Path A only (an existing decomp
repo is a STOP), the Phase-0.5 phase file from PA's template; **Step 2** the interview: 3 read-backs (PROJECT_NAME from CLAUDE.md's
title, COOKBOOK_NAME from the one `docs/*cookbook*.md`, INSTALL_DATE) + the 13 copy-time answers in one round (DUMP_PATH absolute and
outside the repo, never copied) + the `KEY: value` answers-file contract; **Step 3** the firewall (the ignore block APPENDED under a
dated line, never replacing PA's; `config/firewall.txt`, `config/firewall-fixture.sha1`, `tools/audit_public.py`, the CI workflow; **the
negative control** — plant the blob under scratch, the audit MUST exit 1 naming it, remove the one explicit file, the audit MUST exit 0;
eight positive and five negative `check-ignore` probes); **Step 4** layout + the two READMEs; **Step 5** the bootstrap skeleton + **the
checkpoint commit** (PA's own mid-install precedent); **Step 6** the flywheel documents that outlive the package (the wave playbook from
Block 6, `docs/tools-manifest.md`, `docs/decomp-kernels.md`, optionally `docs/decomp-ladder.md`); **Step 7** the registry: the seed body
from its `## §E —` line INSERTED before `## §E′` (PA's heading + pointer stay above), the renumber-by-offset fallback; **Step 8** the
overlays by marker (CLAUDE, DIGEST create, the CURRENT_PHASE template append, the PhaseEnd template INSERT before "PhaseEnd Changelog",
effort map, cookbook, ops-setup), `config/decomp-hooks.snippet.json` + `config/mcp.json.template` (Block 7 — **not** a live merge), the
methodology copy, the skeletons with the present/absent rules (`*.decomp-skeleton.md` beside an existing file; LICENSE flagged for the
verbatim text), `.clang-format`, the Makefile snippet; **Step 9** the memory seed (16 files + the index rows under a marker; the
memory dir asserted to be PA's `.claude-state/memory`; nothing under `~/.claude`); **Step 10** the leftover-placeholder audit (allowed
hits = PA's three), the audit/bash -n/py_compile checks, G-count, gitignore the package, the sorted `CREATED/APPENDED/SKIPPED` manifest
to `.run/decomp-architect-install-manifest.txt`, PhaseEnd_Phase0.5 from the template with the narrative axis, the state sweep, the
`git mv` to `logs/PhaseLog_0.5.md`, the close commit by explicit path, the five-part final message, 🛑; the install manifest;
troubleshooting (seven rows).
**Three supporting changes (X1, each a correctness fix):** (1) **class 7 of the firewall** — ProjectArchitect keeps the agent's
transcripts INSIDE the repository (`.claude-state/transcripts/`, committed while private under its H8) and a decomp's transcripts quote
the target's disassembly (the source project purged ~260,000 lines of `.s` from its session archive): `/.claude-state/transcripts/`
added under class 7 in the wiki page's fence AND the template (re-extracted, 71 → 75 lines, `gitignore_template_check` OK), with
`!/.run/README.md` under the scratch block so Step 4's README is trackable; (2) **Block 7 is no longer a live merge** — a SessionStart
hook running a stub every session and an MCP entry pointing at nothing would only add noise/prompts, and `_comment` keys inside the
hook/MCP objects risk the harness's schema; the block now installs `config/decomp-hooks.snippet.json` + `config/mcp.json.template`,
activated at Phase 2 (the JSON bodies carry no comment keys); (3) `PLACEHOLDERS.md`'s "Filled" wording aligned with the steps (answered
at Step 2, filled at Steps 3–9; generation-time as `TODO(phase-N)` at Step 8).
**Verify:** `kit_lint` OK over 44 files (leak 0; placeholders 22 == 22; syntax 0/3; gitignore 75 identical; `TODO(platform)` 7,
`TODO(phase-N)` 38); `doc_links --strict` rc 0; the structural read-through as a script — 19/19 PA installer mechanisms have a
counterpart (contract, plan-mode line, verbatim copy, per-step ✓, idempotent resume, explicit-path commits, no trailers, never push, one
interview round, the phase file, the placeholder audit, the manifest, troubleshooting, hard stop, the delete note, the fresh session,
the version pin, the write-scope guardrails, the negative control); 12/12 markers SETUP greps for exist verbatim in their templates;
SETUP names all 21 non-PA placeholders and no unlisted one; every `Step N` reference resolves (0–10); PLACEHOLDERS' step refs (2, 8,
10) exist; 0 `§`+digit. **Deviation from the plan's wording:** `§0–§10` → `Step 0 … Step 10` (the lint), `--answers` → the
`answers: <path>` clause of the instruction (a Claude Code prompt has no flags). No build input changed.

### 2026-09-07 — Task 13 — The dry-run install under D6's guardrails (xHigh; S91) — three runs, PASS
**Shape:** a throwaway `git init` under `.run/P33.5/kit-dryrun/repo/` with PA 2.0 (`/mnt/z/…/project-architect-2.0/`) and the committed
kit copied in; ONE general-purpose subagent (Opus) per run under the D6 brief (writes only under the throwaway + three deliverables;
never under `~/.claude`; every git call `git -C "$R"`; no `git clean`, no relative `rm -rf`; every question answered from
`answers.md`, a missing key STOPs; a failed ✓ line is recorded, never patched; deliverables early — `install.log` as it goes,
`manifest.txt`, `verdict.json` last, the final message one JSON line); the judgment mine (`judge.py`, tracked as evidence: the
manifest SET vs `expected-manifest.txt`, the Step-10.1 placeholder audit, 9 + 5 check-ignore probes, G == 65, seeds == 32, MEMORY.md
links, trailer-free commits, the audit in the throwaway, PhaseEnd/log/tree state, and the BEFORE/AFTER guardrails — settings and
statusline sha1s, the 81 real memory files, the 25 `~/.claude` entries, `ghidra/` 4, `dumps/*.bin` 28, the real tree's dirty PATHS).
**Run 1 — FAIL at kit Step 3.7** (PA install clean: two trailer-free commits, the constitution with the eleven-phase ladder, §E the
pointer line). The negative probe for `.run/README.md` succeeded (ignored): **PA's own ignore block writes the directory form
`.run/`; git never descends into an excluded directory, so the kit's `/.run/*` + `!/.run/README.md` beneath it could never
re-include — and Step 3.1 forbade editing above the marker.** The source project's own conventions page documents exactly this trap.
Fix (SETUP): **Step 3.0** rewrites that one line to `/.run/*` (the single named edit above a marker; Step 0.4 names it; idempotent,
runs even when 3.1's marker is present); a troubleshooting row. Also from run 1: PA's placeholder audit is unscoped (it lists the
package folders' own template bodies; only a gitignore-aware `grep` wrapper made it look clean) → **Step 10.1** scoped past BOTH
package folders with `command grep` (a wrapper that honours `.gitignore` silently narrows).
**Run 2 — resumed from Step 3 in the same throwaway (SendMessage; the fixed kit copied in): PASS 10/10**, four commits; the resume
path and Steps 3.1–3.5's idempotence exercised (marker SKIP; templates verified identical). Two more findings → fixes: **Step 10.2**'s
`PYTHONDONTWRITEBYTECODE` branch does nothing (`py_compile` always writes) → an in-memory `compile()` one-liner; **Step 10.1** trips on
prose that QUOTES the token (the agent's own phase file and PhaseEnd did) → the rule "a tracked document never pastes a literal
double-brace; name the placeholder in prose" (SETUP + `templates/docs-README.md`); **Step 10.6** now asks for the Phase-0.5 digest
synopsis (the agent did it unasked, per the digest's own rule). `decomp-architect/README.md` gained **"Findings for ProjectArchitect"**
(the `.run/` form; the unscoped audit; `.claude/settings.local.json` hidden by a host's global git ignore) — carried upstream at the
split. **The judge itself had two false FAILs** (R40/R57 in miniature): its placeholder grep was not scoped past the still-present PA
package (the same gap it was judging), and its dirty-tree COUNT caught my own uncommitted kit fix (the agent had written nothing in
the real tree) → scoped, and the guardrail compares the real tree's dirty PATH LIST before/after. Re-judged run 2: PASS, 46 == 46.
**Run 3 — a fresh throwaway, a fresh agent, the final kit: PASS 10/10, 0 defects**, four commits (`980dabd`, `a751a36`, `cead72f`,
`9f62ccc` in the throwaway); Step 3.0 rewrote PA's line; the control FAILED on the planted blob (`OFFENDER
.run/firewall-control/planted.bin`) then PASSED; 13/13 probes. One judge finding: the manifest had 57 entries against my expected 46
(run 2's agent had produced 46 from the same words) — a SPEC gap, not an install defect: every extra was legitimate (directories, the
manifest itself, the PhaseEnd and archived log, five SKIPPED optional artifacts). **Step 10.5 tightened to an exact rule** (one line
per FILE, sorted; CREATED incl. the manifest/PhaseEnd/log; APPENDED with markers; SKIPPED for the five optional artifacts with reasons;
directories never; a moved file once under its final path — the agent's better reading); the run-3 agent regenerated under it:
**53 == 53**; judge PASS 20/20. **Guardrails:** every BEFORE/AFTER value equal across all runs (the real tree's only dirty paths were my
own kit edits; the agent reported it never wrote there, and the diff agrees). **Cost (R41):** three agent runs ≈ 209k + 300k + 257k
tokens, ≈ 19 + 12.5 + 23 min wall; the coordinator's cost was the fixture, the judge and the four SETUP fixes. **Evidence tracked**
under `.run/P33.5/kit-dryrun/` (the `.gitignore` block, `*.py` added for the judge): `answers.md`, `expected-manifest.txt`,
`before.txt`/`after.txt` (run 3) + `before.run2.txt`/`after.run2.txt`, `install.run1-2.log` + `install.log` (run 3), `manifest.run2.txt`,
`manifest.run3-first.txt`, `manifest.txt`, `verdict.run2.json`, `verdict.json`, `judge.py`; the throwaways `repo/` (run 3) and `repo-run2/`
stay on disk, ignored. `audit_public --paths` over the 14 fixture files: OK. **Deviation from the plan:** run 2 was a RESUME rather than
a fresh re-run (cheaper, and it proved the resume path); the fresh run 3 is the recorded proof. No `KNOWN-DEFECTS.md` needed.
**Findings for the record:** (1) a governance system that keeps transcripts in the repo needs the class-7 line the kit now carries;
(2) the by-contents `/.run/*` form must be the FIRST thing under `.run/` in any ignore file — a later block cannot undo a directory
rule; (3) an unattended installer's manifest must be specified as a derivable SET or two honest agents will produce two honest sizes.

### 2026-09-07 — Task 13.5 — The tools audit, the need-keyed index, the two dictionaries (xHigh; S91)
**The census instrument:** `tools/tool_census.py` — two enumerations of every tool file under `tools/` (`find` vs `git ls-files`, the
submodules/vendored/downloaded dirs excluded; they must agree — it refused once, correctly, while its own file was untracked); per
tool the docstring line, its SETUP row, its CONSUMERS (Makefile/`.mk`, CI, the playbook, other tools by import or by name) and hence
its class; the AUTHORED half in **`config/tool_dictionary.tsv`** (8 columns: path · phase · portability · need · what · adapts · status
· successor_or_product; LF endings — the first write was CRLF from Python's csv default, caught by git's warning; the seed rows parsed
from the transcribed MANIFEST, incl. its two-column project-only table). Coverage both ways (a new tool without a row fails
`--check`). Generates `docs/tool-index.md` (KEEP-GEN, keyed "when you need to…"; Reference-index row; linked from
The-matching-workflow + Toolchain-setup; one pointer line in how-to ch.04/05/10), the kit's `tools/MANIFEST.md` (`--manifest`; header
states live rows, superseded pointer rows AND their total) and the two corpora (`--corpus`): `decomp-architect/corpus/tools/<phase>/`
(302 verbatim copies + 28 `*.superseded.md` pointers + `INDEX.md`) and `corpus/cookbook/` (the cookbook, its symptom index, the
codegen map, behind an authored front page saying what transfers per compiler). `make kit-corpus` regenerates; `tool_census --check`
in tools-health asserts equality by sha1 (it caught my own edit of the census tool once — the copy was stale). `kit_lint` exempts the
two corpus dirs from the leak/placeholder checks (verbatim evidence; 332 files counted) but syntax-checks them (318 scripts).
**The review (Drew's criterion):** one Opus agent drafted the 93 no-consumer verdicts (55 still-needed / 28 superseded / 10 one-off) and
326 need-keys (none leaky); my verification: 0 verdict defects, every successor exists and stays live, 0 retirement candidates with a
live consumer outside the set, 0 basename collisions; I read all 38 and **overturned four one-offs to STILL-NEEDED** — every future
project needs them (the hindsight miner; the decomp.me toolchain replica; the two history-rewrite executables, the package being one
unit). Final: 234 LIVE + 59 STILL-NEEDED (293 live files) + **34 retired** (28 superseded, 6 one-offs) → `git mv` → `tools/sunset/` (R100
renames, history kept); `tools/sunset/README.md` (the ☐ review table); the 4 SETUP rows that named only retired tools moved to a
"Retired tools" section (3 rows shared with a live tool left in place, noted); `docs/wiki/Archive-index.md` gained the tools group
(paths cited, never linked). Census after: 293 live (LIVE 232 · REFERENCED 30 · ORPHAN 31) + 34 retired.
**The kit:** G66 (consult the tool dictionary first) + G67 (translate an inherited idiom through its pass) in `registry-E.decomp.md`
(G1–G67 everywhere; the judge and SETUP counts updated); two memory seeds (18 at install; SETUP Step 9 = 34); SETUP Step 6 installs
`docs/knowledge-corpus.md` and checks the manifest's row count against the manifest's own stated TOTAL; the ops-setup overlay's
"two dictionaries" rows; the intake's Phase 7 cites G66/G67 and **Phase 10 + Part C now name the raw-cast → declared-symbol step
explicitly (Drew's question, S91)**; the methodology's flywheel section names the dictionaries; `templates/layout-contract.md` — the
five-tool probe (the corpus oracle, `match_one`, `rtu_match`, `harvest_verify`, `dedup_propagate`): six assumption classes, no
assumption outside them; a DRAFT for the split. README "Findings for ProjectArchitect" gained the close-step ordering nit.
**Run 4 (a fresh throwaway, a fresh Opus agent, the final kit):** FAIL at kit Step 6 on MY check (`321 != 293` — the whole-file row
count against the header's LIVE figure while the superseded table exists; the file was right) → both sides derived (the header prints
the total; Step 6 compares against it) → resumed from Step 6 → **PASS 10/10**, 4 commits, `321 == 321`; judged: manifest **56 == 56**,
19/20 checks OK; the one guardrail flag was `docs/story-timeline.md`, regenerated by my detached tools-health at its report step
(commit count 48 → 53), not the agent — the dirty-path set difference over the run held exactly that one path. Evidence:
`.run/P33.5/kit-dryrun/{install.run3.log,manifest.run3.txt,verdict.run3.json,before/after.run3.txt}` (run 3 archived) +
`{install.log,manifest.txt,verdict.json,before/after.txt}` (run 4) + `repo-run3/`, `repo/` on disk; `.run/P33.5/tools_audit/`
(`all_tools.txt`, `noconsumer.txt`, `review.tsv`, `need.tsv`, `layout_probe.json`, `judge_run4.txt`) tracked by a dated block.
**Verify:** `tool_census --check` OK; `kit_lint` OK; `doc_links --strict` rc 0; `wiki_render --selftest` 12/12 + 31/0; `audit_public`
OK over 6,842 tracked paths (the corpus included); **`make tools-health` OK** (detached, `.run/P33.5/tools_health_t135.log`, 5,911
lines — kit_lint 332 corpus files exempt; census 302 + 28 checked). **Also this session:** the purge probe **PASS** (every sampled old
hash gone; the live control resolves; `.run/P33.5/probe_github_s91.log`) — Phase 34's gate is OPEN. **Knowledge banked (R30/R31):**
`docs/decision-log.md` "P33.5 S91" (the dictionaries pivot, Drew's criterion, the measured why, the hindsight path);
`docs/accelerators.md` "P33.5 S91" (four entries: the ignore-form wall; a typed figure vs a derived one; the judge as an instrument;
a tool without a dictionary row is invisible). **Cost (R41):** the review agent 187k tokens; run 4 220k + 276k (the resume); the
coordinator's cost was the census tool, the dictionary seed, two derived-check repairs and the retirement review. **Deviations:** four
verdict overrides (recorded); run 4 needed a resume for a check of my own making; the ORPHAN count moved 91 → 94 → 31 as the
instrument replaced the ad-hoc scan and the retirements landed.

## 🛑 SESSION CHECKPOINT — Tasks 0–13 and 13.5 ✓; NEXT = task 14 (the wiki page `Start-a-new-decomp-project.md` + the README/Tools rows + the kit's SETUP rows; **xHigh**; a FRESH SESSION — S91 ended at 85% context)

### 0. How to use this block
You are a FRESH SESSION that has read `PROJECT_CONTEXT.md`, `phase-ends/DIGEST.md`, `PhaseEnd_Phase31/32/33.md` and this file, and
nothing else (R64). Replay this block verbatim, state phase / done / NEXT / effort, list the rules from the digest (R1–R83), then
WAIT for Drew. Rebuild the harness task list (17 rows incl. task 13.5, R28) marking tasks 0–13 and 13.5 completed and task 14 in progress.

### 1. Where we are
**Phase 33.5** (sub-phase; v1.32.0 → v1.32.1), gate 1 approved 2026-09-07 by Drew in plan mode at Max; effort follows the plan's
column (Max for task 15 — prompt at that transition, R27; task 14 is xHigh). Baseline HEAD `80d45b29b`; task 0 = `39d524991`; task 1 =
`a0cf302e5`; task 2 = `d06923a06`; task 3 = `5d10a0d12`; task 4 = `9970f1e62`; task 5 = `a0d4ae836`; task 6 = `6ec4786bd`; task 7 =
`21c98ed5a`; task 8 = `ae71efe56`; task 9 = `caefe9872`; S90 checkpoint = `e1463d430`; task 10 = `83de29c02`; task 11 = `9235800fb`;
amendment 1 (13.5 added) = `6fb2bc7f8`; task 12 = `4c1d5d9f7`; task 13 = `a291c2b47`; amendment 2 (the dictionaries) = `3307775e5`;
task 13.5 = the commit after this block (S91, 2026-09-07). No build input changed; the fleet is 218/218 at the Phase-33 close;
**`make tools-health` OK on this tree at task 13.5** (`.run/P33.5/tools_health_t135.log`). `doc_links --strict` rc 0; pending list
empty; `kit_lint` OK; `tool_census --check` OK; `audit_public` OK (6,842 paths). **The kit is complete, dry-run-proven four times, and
now carries the two dictionaries in-tree** (Drew, confirmed S91): `corpus/tools/` (302 verbatim copies + 28 pointers + INDEX),
`corpus/cookbook/` (cookbook + index + codegen map + front page), G1–G67, 18 memory seeds, `templates/layout-contract.md` (a draft).
**The tools folder is audited:** 293 live tool files + 34 retired under `tools/sunset/` (README = the ☐ review table; deletion is
Drew's), `config/tool_dictionary.tsv` the authored record, `docs/tool-index.md` the generated need-keyed index. **Phase 34's gate is
OPEN:** the purge probe PASSED on 2026-09-07 (`.run/P33.5/probe_github_s91.log`) — the flip can proceed in Phase 34.
**Already banked — task 14 must NOT write these again:** `docs/decision-log.md` entries "P33.5 S90", "P33.5 S91" AND "P33.5 S91-b" (the types hindsight — task 14 IMPLEMENTS its items (a)–(e) in the kit, it does not re-record them); the
`docs/accelerators.md` "P33.5 S91" entry (four accelerators); the SETUP rows for `kit_lint.py`, `tool_census.py`, the retired-tools
section. Nothing runs in the background; the headless Ghidra MCP was never used (no RE work; nothing under `ghidra/` is tracked).
The plan file `~/.claude/plans/max-effort-set-plan-encapsulated-muffin.md` is a copy of the "Approved plan" section below — this file
is the one that counts.

### 2. What NEXT does (task 14, **xHigh**) — exact steps (plan D1 "Start a new decomp project" + the task-14 row)
**Read first:** `docs/wiki/_Sidebar.md`, `docs/wiki/Home.md`, `docs/wiki/Tools-from-this-project.md`, `docs/wiki/Where-the-project-goes-next.md`
(its day-one-kit pointer paragraph), `docs/wiki/Docs-and-scratch-conventions.md` §"Links" (the link policy: a wiki page links `docs/`
only at a Reference-index target; forward links via `docs/doc_links_pending.txt`), `decomp-architect/README.md` (the install steps, what
it installs and does NOT, the corpus findings), `decomp-architect/intake.decomp.md` Part B (the ladder table) and Part C (the six
inversions), `decomp-architect/corpus/cookbook/README.md` (what transfers), `docs/accelerators.md` (the entries → a one-line-per-entry
table), `README.md` ("Tools from this project"), `docs/SETUP.md` (the row shape).
**Write, FIRST (the S91-b amendment — the kit edits, so the wiki page describes the final kit):** (0) per `docs/decision-log.md`
"P33.5 S91-b" items (a)–(e): `corpus/decomp-kernels.md` gains **DK-65** (types are a banking lever and a width lever, not a byte lever; the
Phase-17 measurement 0/10/2 and the 1,232-definition cost in its calibration fence; coverage line 64 → 65); `intake.decomp.md` Part B
row 6's milestone gains the canonical type layer (one definition per shape; widths proven at bank time; a bank refused for a duplicate
definition or a raw address cast) and row 10 notes it is short when row 6 held; `templates/registry-E.decomp.md` G62 extended with the
bank-time refusal (keep G1–G67 — extend G62's text rather than renumber); `config/tool_dictionary.tsv`: the need-keys/phases of
`lift_types.py`, `canon_sig_reconcile.py`, `sync_tu_decls.py`, `decl_prior.py`, `conform_decls.py` say Phase 6 (the multiplier) as well as
P10; `corpus/cookbook/README.md` one sentence naming width/signedness as the one place a type moves bytes; `decomp-architect.md` part 6
one paragraph with the two-sided verdict. Then `make kit-corpus`, `tool_census --check`, `kit_lint`, `doc_links --strict`. Then:
**Write:** (1) `docs/wiki/Start-a-new-decomp-project.md` — the three steps verbatim from the kit README (install ProjectArchitect 2.0
handing it `intake.decomp.md`; copy `decomp-architect/`; "Read decomp-architect/SETUP.md and do it"); what it installs / does NOT
(no tools installed — the two DICTIONARIES instead: the verbatim tool corpus keyed by need, the inherited cookbook + index + codegen map
behind its front page; the memory seed; G1–G67); the hindsight ladder as a compact table (phase · milestone · earned by); the AI-use
rules (the five); the Gen3-at-day-one inversions (six, incl. raw casts → declared symbols); the accelerators as a one-line-per-entry
table; the compiler question (same family = direct use + re-prove; other = translate through the pass); the four dry-runs as the
proof (runs 1–4, what each found); links: wiki pages by relative `<Page>.md`, the kit by backticked path (it is not a `docs/` file —
the kit README is in `doc_links`' DEFAULT set; do NOT link `decomp-architect/` files from a wiki page unless the Reference index lists
them — cite paths). Sidebar row under "Using the project" or a new "Start a new decomp project" entry; a Home.md row. (2) README:
a "Tools from this project" row for the kit (`decomp-architect/` — the day-one kit; the two dictionaries; the tool index) and one for
`tools/tool_census.py` if the section lists tools; `docs/wiki/Tools-from-this-project.md`: rows for the kit and for the tool index
(`docs/tool-index.md` is a Reference-index target — linkable). (3) `docs/SETUP.md`: a row for `decomp-architect/` (the package: what
it is, how it is checked — `kit_lint`, `tool_census --check`, `gitignore_template_check`, the dry-run harness under
`.run/P33.5/kit-dryrun/` with `judge.py`), R21. (4) `docs/wiki/Where-the-project-goes-next.md`: the kit pointer paragraph → a link to
the new page; the Phase-34 paragraph notes the probe PASSED 2026-09-07. (5) `docs/phase34-seed.md`: note the probe PASS and that the
split phase carries `decomp-architect/` whole (the corpus is generated in-tree; `make kit-corpus`). **Verify:** `wiki_render --selftest`
(the new page reachable — 32 pages); `doc_links --strict` rc 0 (register any forward link in the pending file in the same commit;
none expected); `kit_lint` OK; `tool_census --check` OK (if any tool moved). Log + checkpoint; commit by explicit path. Then **task 15
is Max — prompt Drew (R27)**; task 15's checklist is the plan's row 15 + the P7 walk of the milestone's six items + the R18/R25 recap
+ the PhaseEnd's rule candidates (this phase produced: the ignore-form wall; a typed figure vs a derived one; the judge as an
instrument; a tool needs a dictionary row; re-run `doc_links --strict` after any untrack; an unattended installer's manifest is a
derivable SET; the class-7 line for a governance system that keeps transcripts in the repo).

### 3. Standing facts for every task of this phase
- One commit per task, after this file's log line (R8/R42 form); commit by explicit path; no trailers (R5); Drew pushes (R6).
- Forward links from any new wiki page go into `docs/doc_links_pending.txt` as `<path>\t<task N>` in the SAME commit; the render
  refuses dead relative links (exit 1); `tools/doc_links.py` non-strict is in tools-health; `--strict` at task 15 — **and after
  any untrack or archive move** (task 10's finding).
- Nothing moves while a wiki page / how-to chapter / `doc_links` DEFAULT document / tool docstring cites it — the referrer census
  command in the plan's D3 runs before every `git mv`; for TOOLS the census is `tool_census.py --consumers FILE`.
- `purge_set.txt` is never edited in this phase. Never `git clean -x`. The untracked 29 GB of `.run/` is out of scope.
- Effort transitions are prompted and waited for (R27): Max for task 15; xHigh for task 14.
- The kit's vocabulary (task 10): rules by G-id, kernels by DK-id, PA's sections as "step N", the kit's SETUP as "Step N"; source
  numbers only in ```` ```calibration ```` fences; the placeholder set is `PLACEHOLDERS.md`'s 22 and nothing else (`kit_lint` enforces);
  the two corpus directories are verbatim evidence (lint-exempt, syntax-checked, coverage by `tool_census --check`).
- **Any edit to a tool under `tools/` or to the cookbook/codegen map makes its corpus copy stale: run `make kit-corpus` and re-stage
  `decomp-architect/corpus` before committing** (`tool_census --check` in tools-health refuses otherwise).
- **`make tools-health` runs longer than the 10-minute foreground cap:** launch it detached (`setsid nohup make tools-health >
  .run/P33.5/<log> 2>&1 < /dev/null &`), then wait on the pid from a background Bash; never as a harness background task; never
  sleep-poll in the foreground. Its report step regenerates `docs/story-timeline.md` (a generated file — commit it).
- The wiki fence and `templates/gitignore.decomp` are ONE source in two copies: edit the page, re-extract the template by script,
  `gitignore_template_check` must read OK (75 lines since task 12).
- **The dry-run harness is reusable:** `.run/P33.5/kit-dryrun/{answers.md,expected-manifest.txt,judge.py}` + the D6 brief (task-13
  log); a kit change is re-verified by a resume on the run-4 throwaway (`repo/`), a fresh full run only when SETUP's steps change;
  the judge compares the real tree's dirty PATH SETS — attribute every foreign path (a detached tools-health regenerates the
  timeline) before calling it a write by the agent.

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
