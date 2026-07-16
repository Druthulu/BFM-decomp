# PhaseEnd — Phase 27: The Fable5 Farewell Sprint + the Honest Frontier
**Date:** 2026-07-15 · **Project Version:** 1.26.0 · **Phase Status:** Complete (milestone confirmed by Drew, gate 2) · **Generation:** Gen2 (19th phase of the arc; Phase 14 public-flip deferred to Gen3+)

> Gen2 phase 19 (8→…→26→**27**). First phase off `docs/roadmap-to-100.md` (adopted the day before). The granular per-task crash-recovery trail is preserved on-demand at **`phase-ends/logs/Phase27.md`** (R19 — NOT auto-loaded; consult only when researching a mechanism). This file is the synthesis. Owner decisions (Drew): batch the xHigh cluster while the perishable Fable5 sprint ran, prompt for Max at the deep synthesis; curated `.run/` preservation; full disc audit incl. the type-sweep; Fable5 in 2 waves with distillation between; cap Fable5 at the last running crack (86% context); the 1,670-triage → P29.

## Build Log

**Files created/changed and complete — do not recreate** (the durable Phase-27 output; the archived log has the exhaustive per-commit list):

*The enabling + oracle fixes (T2/T4/T6/T10):*
- `Makefile` — **`.SHELLFLAGS := -ec`** (global fail-closed; `.ONESHELL` swallowed every non-final failure — `make report`'s middle gates were non-gates); `check-env` opts out (`set +e`); `check-all`/`extract-all` assert **`pass == N`** (coverage, not the absence of a marker); the `grep -c` landmine fixed (`|| true`); new **`tools-health`** (regenerates sigs → `audit-corpus` + `audit-cdecl` + `report`, fail-closed); new **`sig-resident`** (sig_image on the resident); **`sig-overlays` derives from `overlays.mk`** (the `0.4.dec` glob dropped the 4 SC07 overlays).
- `tools/cdecl.py` — **the canonical typedef-strip primitive** `typedef_names()` + `strip_provided_typedefs()` (replaced SIX copied scalar-name regexes with complementary holes; per-TU, scalar AND struct, multi-line-aware; built on `tu_statements` not the coverage-asserting `scope`, so it can't crash the byte-gate).
- `tools/harvest_verify.py` — strips per-TU via `cdecl` (unblocks the 39 struct-typedef drafts) + **surfaces cc1 stderr** → classifies a single-draft failure **DIFF / PLUMBING / CC1-FAIL / SKIP** (`.run/harvest_failed.classified.txt`).
- `tools/masked_diff.py` — `strip_scalar_typedefs()` (common.h set derived once, R33); wired into `tools/match_one.py` + `tools/p16_permute.py` (fixes the multi-typedef-line skip that discarded 42 masked-MATCH drafts).
- `tools/difficulty.py` — the 136-entry hand-dict → `cfg_for(alias)` (derived, tree-validated; proven byte-exact for all 136). `tools/exemplar_miner.py` — the `registered_addrs()` proxy → `corpus.stubs` (R33). `tools/new_overlay.sh` — dropped difficulty from its insertion set + the `[ENTRY]` arg.
- `tools/progress.py` — `weighted_metrics` off `src_stubs` onto `corpus.stubs` (**the landmine: `src_stubs("SLUS_007.26")`→0 files→main 100%**; proven 0.000pp on the fleet) + a separate caveated **`MAIN game-code weighted`** line. `tools/corpus.py` — `sig_is_independent` now covers **resident** (the second oracle, R34; probed clean).

*The disc audit + the honest frontier (T7/T8/T9):*
- `tools/new_overlay.sh` `[ENTRY]` → onboarded **`ov_SC07_{006,007,010,011}`** from `1.4.dec` (byte-identical). `config/overlays.mk` + 12 new `config/{splat,check,symbols}.ov_SC07_*` + 4 `src/ov_SC07_*/` stub records. **Fleet 136 → 140.**
- `tools/disc_code_sweep.py` — **new**; the R34 disc-completeness oracle (valid + `jr $ra` density). `tools/worklist.py` — **`--assert-partition`** (R32; caught 5 stale rows). `.run/fuel_manifest.json` refreshed (giants reach-138); `.run/backlog.jsonl` ledger corruption fixed (`func_80178004` close=0 myth → 91).
- `tools/family_remap.py` — **`_carry_macros`** (T5): `extract_unit` carries the body's file-scope `#define` deps → unblocks staging (0x8017BEBC 0→106/112) AND dissolves the §42e pin-crash wall.

*Docs / knowledge base (all distilled IN-SESSION, R30):*
- `docs/disc-completeness.md`, `docs/second-oracle.md`, `docs/calibration.md` — **new** durable records.
- `docs/matching-cookbook.md` **§42e-CORRECTION** (the pin-crash wall refuted) + **§44-Lever-5** reclassification. `docs/gcc-2.7.2-map/regalloc.md` **§H** (the reg_renumber-swap oracle + RC-14/RC-15 + the local-vs-global tie) + `cse_expr.md` **§H** (the CSE address-fold antidote). `docs/decision-log.md` — the Phase-27 R31 entry (3 strategic findings). `docs/SETUP.md` §6.3 (fail-closed, sig-resident, tool inventory). `docs/progress.fleet.md` / `worklist.md` / `backlog.md` regenerated.
- `.gitignore` — the curated `/.run/` allowlist (irreplaceable recon tracked, regenerable bulk ignored). Preserved recon: `.run/giants/*.fable.{c,md}` (4 cracks), `pin_crash_sigabrt.md` + `pincrash/{minimal_repro.c,*.gdb}`, `backlog.jsonl`, `fuel_manifest.json`, `fable_80178004/`.
- `phase-ends/CURRENT_PHASE.md` → **`phase-ends/logs/Phase27.md`** (R19). `phase-ends/PhaseEnd_Phase27.md` — this file.

**Tools/packages installed:** None — the whole phase used the existing toolchain + venv. No Ghidra DB change (R23 no-op).

**Verification results (literal) — the milestone proof:**
- **`make check-all` → 140 passed, 0 failed of 140** BYTE-IDENTICAL from a clean tree (R22), reproduced after every step. **0 NON_MATCHING** in any default build (G4).
- **`make audit-corpus` → 0 PHANTOM + 0 TRUNCATED** (now covers resident, R34). **`make report`** genuinely fail-closed (negative control: an identical broken gate exits 0 under the old `.SHELLFLAGS=-c`, non-zero under `-ec`).
- **`make report` metrics (post-audit, honest):** fn-count **82.16%** (was 84.47%) · instr-weighted **67.0%** (was 68.9%) · distinct-code **47.8%** (was 49.2%) · MAIN game-code **0.7%** (separate, provisional). The drops are the T7 denominator expansion (the SC07 overlays), NOT regressions.
- **T5 probe (R14):** 0x8017BEBC staging 0→106/112; bounded 8-member gate **0/8, all genuine DIFF** → the family is NOT byte-templatable (roadmap B2 refuted). **T8:** `worklist --assert-partition` 223==223 after refresh.
- `git status`: only `config/`/`tools/`/`src/`/`docs/`/`.run/`(allowlisted)/`phase-ends/` tracked; the `db.*.gbf` churn is R23 restart-noise (not staged).

**Milestone achieved (confirmed by Drew, gate 2):** the endgame plan is rebuilt on **measured reality** — the tools that scan the frontier were fixed (fail-closed gates, one typedef-strip primitive, derived scanners, a second oracle extended to resident), the disc was audited honest (**136→140 overlays + 39 un-onboarded type-1 code modules found**), the residue map is partition-validated with measured rates (`calibration.md`), and the completion contract + 3-metric dashboard are adopted on the corrected numbers — all at **140/140 byte-identical, 0 NON_MATCHING**, both audit gates green and *actually* fail-closed. The Fable5 farewell sprint (4 cracks + the SIGABRT) banked nothing directly but **dissolved the pin-crash propagation wall** (P31's route re-opened), reclassified three "intrinsic" walls, and distilled ~9 new pin-free levers.

**Next:** **Phase 28 — The Endgame Engine** (roadmap §3 P28). Open a fresh session (plan mode, Max). **First task: measure the member-adapt close-rate on register-drift members** (the roadmap's swing number, `calibration.md`'s one honest gap) — build `member_adapt.py` and calibrate on a byte-gated sample before P29 scales. Then the parallel gate farm, fleet-wide Ghidra-C prefetch, and the resident 100% flag-plant.

## Deviations
| Item | Plan | Actual | Reason |
|---|---|---|---|
| Roadmap P27 as written | execute the 7 workstreams | **~28 specifics corrected by verification** (P27 gate) | 3 targets dropped (stale/contested), B4 dissolved into T4, 2 false-wall traps caught, 4 invisible overlays found — the roadmap's numbers were red-teamed, its tools were not |
| Effort | Max throughout | **batched xHigh cluster (T2/3/4/6/7/10) while the perishable sprint ran; Max for the distillation + T5/T8/T9/T11** | R27 + Drew's keep-moving signal; the deep synthesis genuinely wants Max, the settled-design execution is xHigh |
| Pin-crash wall | (not in scope) | **REFUTED — a major unplanned finding** (the SIGABRT is the T5 macro-drop, not a compiler limit) | the wave-2 SIGABRT characterization converged exactly with T5; P31's pin route is now OPEN |
| 0x8017BEBC (B2) | "possibly the largest cheap win left" | **byte-refuted (0/8)** — but only after the macro-carry made the probe honest | the fix had to precede the probe; a pre-fix 0% was a tooling artefact |
| T8 1,670-triage | Ultracode breadth | **scoped to P29** (P5d) | labels re-derive at harvest + the pin-crash finding re-buckets them; the gate's residue map is the partition + calibration, delivered |
| T10 main oracle | "add main to the weighted metric" | **separate caveated line + honest deferral** (`second-oracle.md`) | main has only a stale LINKED-excluding Ghidra sig; folding it into the decomp.dev headline would mislead; sig_image-on-main is structurally blocked |
| T3 ordering | after T1 | **pulled ahead** (+ addendum: §45 cited untracked files) | the sprint's inputs were untracked — one `git clean` from gone |

## Commit Message
```
(Phase 27 landed as 14 per-task commits commit:0629..commit:0642 + this PhaseEnd.)

feat(phase-27): the honest frontier — fix the instruments, audit the disc, dissolve a wall (v1.26.0)

- INSTRUMENTS FIXED: Makefile fail-closed (report's gates were swallowed); one cdecl typedef-strip
  primitive (was 6 regexes); scanners derived not hand-listed (difficulty/exemplar_miner); the
  second boundary oracle extended to resident. Each fix CHANGED an answer the old tool hid.
- DISC AUDITED HONEST: 4 hidden SC07 overlays onboarded (136->140, code at PAC entry 1) + 39
  un-onboarded type-1 code modules found (resident-class, load-address RE pending). The byte-gate
  is blind to un-onboarded code (R34); game-code TRUE 100% now spans 140 + ~39. Instr 68.9->67.0%
  (denominator correction, not regression).
- PIN-CRASH WALL DISSOLVED: the §42e "cc1 SIGABRTs the sibling TU" wall is the extract_unit macro-
  drop (sched.c:2725), fixed (T5 _carry_macros); pinned families stage 133/133 clean -> P31 open.
- HONEST FRONTIER: worklist --assert-partition (R32, caught 5 stale rows); ledger corruption fixed;
  calibration.md (the templatability swing: h_exact cores ~xN, h_seq families ~0% -> B2 refuted).
- FABLE5 SPRINT: 4 cracks + the SIGABRT, 0 banks, but 3 wall reclassifications + the wall dissolved
  + ~9 pin-free levers distilled (cookbook §42e/§44 + regalloc/cse_expr §H + decision-log R31).
- 140/140 byte-identical (R22), 0 NON_MATCHING (G4), audit gates green + fail-closed. No tools
  installed. rules R35 (fix the instrument before trusting its measurement). bumps 1.25.0 -> 1.26.0.
```

## Rules Added This Phase
| Rule | Reason |
|---|---|
| **R35 — Fix the measuring instrument before trusting its measurement; a probe from a broken tool is not evidence.** When a scan, metric, closeness score, or probe is about to scope real work (a phase, a "cheap win", a "wall", a completion claim), verify the TOOL that produced it is not the thing being measured — and if it is broken, fix it and RE-measure before acting. A 0% from a broken tool and a 0% from a working one are the same number and opposite facts. Extends R14 (verify the DATA vs the bytes) and R32/R33/R34 (make the tool correct) with the **sequencing**: tool-integrity is a *precondition* of a measurement, not a parallel concern. | The phase's through-line, five times over: `make report` swallowing its own gates (T2), six typedef regexes each half-broken (T4), the `extract_unit` macro-drop wearing a compiler wall's clothes (T5), the disc glob hiding 4 overlays + 39 modules (T7), the `0x8017BEBC` probe that would have read a phantom 0% (T5). In every case the fix CHANGED the answer, and the roadmap had been scoped against the broken readings. R32/R33/R34 (Phase 26) made tools assert their own correctness; R35 is the standing obligation to *act on that first*. Drew to accept/modify/reject. |

*(No OTHER new governance rules — per the Phase-8+ precedent, the phase's techniques → cookbook §42e/§44 + gcc-2.7.2-map §H, and its findings → `docs/decision-log.md` (R31) + `disc-completeness.md` / `second-oracle.md` / `calibration.md`. The **disc-completeness-before-100%** invariant is captured as a completion-contract item in `disc-completeness.md`, governed by the existing R34, not elevated to a separate rule. The **effort-batching** discipline is R26/R27. The existing rules — G3/P9, R14, R16/R30, R19, R20, R22, R23, R26/R27, R32/R33/R34 — governed the phase and it reinforced them.)*

## PhaseEnd Changelog
**v1.25.0 → v1.26.0 — Phase 27 complete (Gen2 phase 19; the first phase off the Road-to-100 roadmap; an infrastructure + honest-findings phase).** Phase 27 rebuilt the endgame plan on **measured reality**. The roadmap adopted the day before had red-teamed its *numbers* but not the *tools under them* — so the phase fixed the instruments and looked again. **The instruments were lying in five places:** `make report` silently swallowed its own gates (`.ONESHELL` with no `-e`); six copied typedef-strip regexes each had complementary holes (one consolidated `cdecl` primitive; a live ×134-family draft went CC1-FAIL→MATCH with the tool change alone); `difficulty`/`exemplar_miner` scanned via hand-lists/proxies (now derived); the second boundary oracle was blind to main + resident (extended to resident, R34); and `extract_unit` dropped file-scope macros. Each fix **changed an answer the roadmap had been scoped against**. The **disc-completeness audit** found the byte-gate blind to un-onboarded code (R34): **4 hidden SC07 overlays** (code at PAC entry 1, invisible for a month) onboarded byte-clean (**136→140**), and **39 more un-onboarded type-1 code modules** discovered (resident-class, pending load-address RE) — so game-code TRUE 100% now spans 140 binaries **plus ~39 modules**, and the honest headline dropped **68.9%→67.0% instr** (a denominator correction). The **Fable5 farewell sprint** (4 cracks + the pin-crash SIGABRT characterization) banked **0** functions directly but **dissolved the §42e "pin-crash wall"** — the SIGABRT (`sched.c:2725`) is the `extract_unit` macro-drop (T5's bug), not a compiler limit, so a whole class of high-reach pinned cracks the roadmap wrote off as ×1 now propagate (**P31's route re-opened**) — reclassified three "intrinsic" walls (RC-6-not-S3 etc.), and distilled **~9 new pin-free levers + the reg_renumber-swap oracle + the CSE address-fold antidote** (cookbook §42e/§44, gcc-2.7.2-map §H). The honest frontier is validated (`worklist --assert-partition` 223==223; the templatability swing measured — h_exact cores ≈×N, h_seq structural families ≈0%, so **B2's cheap-harvest hope is byte-refuted**), the completion contract + 3-metric dashboard adopted on the corrected numbers, and main added to the weighted metric safely (separate, caveated) with the main second oracle honestly deferred. **140/140 byte-identical, 0 NON_MATCHING** throughout; no tools installed. One rule (**R35**, fix-the-instrument-first). All idioms distilled IN-SESSION (R30).

## Plain-English Recap
This was a "fix the instruments, then look" phase — and looking through honest instruments changed the picture three ways. First we repaired the project's own tools: the build's self-checks had been *silently passing when they should fail*, a pile of duplicated helper code was subtly broken, and the honesty-checker was blind to two pieces of the game. Fixing each one **changed the answer it gave** — which is the whole point. Then the discoveries: the game has **more code than we'd been counting** (four hidden levels, now built, plus about 39 more code modules nobody knew were there), so the honest "how done are we" number actually went *down* — to 67% — because we'd been grading against an incomplete game. A **"wall" we'd respected for months turned out to be our own tool quietly dropping a few lines of setup code**; fixing it re-opens a whole batch of high-value work we'd written off as impossible. And a **"cheap win" the plan was counting on doesn't exist** — the leftover functions that look identical aren't, down to the byte. The best AI model spent its last four attempts of the session not *finishing* functions but *understanding* them — and that paid off: it dissolved that wall, corrected three mistaken "impossible" verdicts, and taught us nine new tricks, all written down. Nothing regressed — all 140 pieces of the game still rebuild perfectly. The lasting win isn't a percentage; it's that our instruments no longer lie to us, and we know honestly what's left: not a cheap templating harvest, but careful per-function work — with a freshly re-opened path through the functions we'd given up on.

## Roadmap delta (roadmap §0 — what Phase 27 changed about the road ahead)
- **Binary count: 136 → 140 onboarded + a documented backlog of ~39 type-1 code modules** pending load-address RE (`disc-completeness.md`). The completion contract's denominator and the "100%" bar both move; a disc-completeness audit is now a hard precondition of any 100% claim (R34).
- **Metrics re-baselined: instr-weighted 68.9% → 67.0%** (denominator expansion, honest); main added to the weighted metric as a separate provisional line; the fleet is 140 binaries.
- **B2 (`0x8017BEBC` "largest cheap win") REFUTED** — byte-not-templatable; and the calibration establishes the general rule: **h_seq/h_norm structural families do not mechanically template (≈0%)** — remaining yield is per-member cracking + mechanical ×N for h_exact cores, NOT "template ×120 the 986 families." P29's arithmetic is (cores cracked) × (reach), not (families) × 120.
- **P31 pin-×1 route RE-OPENED** — the pin-crash wall is dissolved; the ~20 PINS-class stubs + the 4 characterized pin families are back on the mechanical-harvest table (un-projected P29 fuel).
- **P28 opens by measuring the member-adapt close-rate** (the one honest calibration gap) before scaling — unchanged from the roadmap, now with the tools + the second-oracle it needs.
- **B4 dissolved** (its remedy was already run 1/7; the residuals are the T4 debts). The `func_80178004` ledger myth is corrected. `worklist --assert-partition` is the standing R32 partition guard.

## 🛑 Stop Here
PhaseEnd written; `CURRENT_PHASE.md` archived → `phase-ends/logs/Phase27.md` (R19, via `git mv` — left uncommitted for Drew's milestone-close commit). The Phase-27 work is committed across the session (`commit:0629`..`commit:0642`); **Drew commits AND pushes** this PhaseEnd + the archived log (R6/R8 — the milestone-close is the human-controlled gate-2 sign-off). No Ghidra DB change this phase (R23 no-op — the `db.*.gbf` churn is restart-noise; do NOT stage). Gen2 continues — do **NOT** start Phase 28 here. Start a **fresh session** (effort **Max**, **plan mode**) for **Phase 28 — The Endgame Engine**, opening by measuring the member-adapt close-rate (`docs/calibration.md`). Keep this file forever.
