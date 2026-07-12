# PhaseEnd — Phase 25: The structural-family endgame → the giant endgame + the h_seq family reframe
**Date:** 2026-07-11 · **Project Version:** 1.24.0 · **Phase Status:** Complete (milestone confirmed by Drew, gate 2) · **Generation:** Gen2 (17th phase of the arc; Phase 14 public-flip deferred to Gen3+)

> Gen2 phase 17 (8→…→24→**25**). Ran across **many sessions (2026-07-08 → 07-11)** — the longest matching phase.
> The granular per-task/per-session crash-recovery trail (T0–T7 mechanical tiers, the wave rounds, the giant
> campaign, the permuter batch, the reach/family surveys) is preserved on-demand at
> **`phase-ends/logs/Phase25.md`** (R19 — NOT auto-loaded; consult only when researching a mechanism). This file
> is the synthesis. Owner decisions (Drew): exemplar-per-family sweep, cheap-tier-first with Opus/Fable5/permuter
> escalation → giant campaign → on the **h_seq family reframe**, close the phase and hand a **family-endgame
> megaplan** to a fresh plan-mode + Fable5 **Phase 26**.

## Build Log

**Files created/changed and complete — do not recreate** (the durable Phase-25 output; the archived log has the exhaustive per-commit list):

*The mechanical family engine (the phase's economic core, T2–T7):*
- `tools/family_manifest.py` — regroup the unmatched frontier by `h_norm`; per family the ov_SC01_077 drafting exemplar + instances (×N leverage) + byte-weight → `docs/family-manifest.md`.
- `tools/family_remap.py` — crack ONE exemplar → positionally substitute each member's per-overlay reloc symbols → plain `harvest_verify` byte-gate. ~0 agent tokens/member. **The T3 proof that h_norm families are TEMPLATES (reloc-symbol-remap), not free dedup.**
- `tools/family_sweep.py` — two-phase stage-then-gate driver; `--only`, `--reconcile` (per-sibling canon_sig_reconcile, the Q5 law), `--edit-remap` (§42e out-of-body //@EDIT + once-global engine_core.h flips), `--no-preclassify`.
- `tools/canon_sig_reconcile.py` **v3.2** — the def-side loose-typing-wall cracker (strip ambient dups → rewrite def to canonical sig → cast changed params AT USE; uniquify draft type names). The T6 headline tool.
- `tools/t7_bank.py` (M1 driver, reconcile-at-bank-time), `tools/recover_giant.py` (canonical-extern block-scope recovery), `tools/rtu_match.py` (real-TU-faithful parallel-safe match check — closes match_one's isolation blind spot), `tools/progress.py --weighted` (the honest byte/instruction-weighted metrics).

*Config / source (the harvest — fleet 66.02% → ~74.6% fn-count):*
- The 134 overlay `src/ov_*/*.c` files — thousands of member-matches banked via the mechanical family sweeps (T7 M1 37 + M2 4,389 + M3 268; waves 2–4; the matched-free +16,512 / type-lift +1,729 / h_exact stragglers). `src/shared/engine_core.h` + `engine_types.h` (typedef/struct lifts). `config/dedup.us.yaml` (1813 groups, 0 failed).
- **The giant campaign** (Task A, tonight + prior): all matchable region-a giants ×134 — batch 1 (`func_80166994` 369 §43 K&R-s16, `func_80135480` 258, `func_80163EC8` 234) + **the flagship `func_80133CD4` (399 ins) ×134** (§45 Fable5 crack, `commit:0515`). `func_8014FBC0` (22×1996 inline-asm trampoline) + `func_80132144` (27×539) among the wave banks.

*Docs / knowledge base (the mature gcc-2.7.2 + family toolkit):*
- `docs/matching-cookbook.md` **§40–§45**: §40/§40a (structural-family mechanical-remap), §41/§41a–c (canon_sig_reconcile + the ×134 per-sibling re-reconcile law + the object-probe≠gate correction), §42/§42a–e (density-lever catalog, the stale-object gate trap, rtu_match, the wave-4 levers, the `--edit-remap` propagation), §43 (K&R s16-param dissolves the narrow-param wall), §44 (cheap-Opus giant batch, 5 levers + "each giant is its own class"), **§45 (the flagship crack — merged-accumulator-variables + the 1-death local-alloc in-out-asm + offset-0 /s + goto-shared-return; the template for the family-core cracks)**.
- `docs/phase25-t6-curriculum.md` (Fable5-authored crack curriculum), `docs/phase25-frontier-map.md` (rtu-measured endgame buckets), **`docs/family-endgame-megaplan.md`** (the Phase-26 brief — the h_seq family reframe + the finish plan), `docs/decision-log.md` (R31, strategic-pivot rationale), `docs/backlog.md` / `docs/worklist.md`.
- `phase-ends/CURRENT_PHASE.md` → **`phase-ends/logs/Phase25.md`** (R19). `phase-ends/PhaseEnd_Phase25.md` — this file.

**Tools/packages installed:** None — the whole phase used the existing Phase-4/6/…/24 toolchain + venv (decomp-permuter, m2c, rabbitizer, cc1 candidates). Fable5/Opus agents via the Agent tool.

**Verification results (literal):**
- **`make check-all` → 136 passed, 0 failed of 136** — reproduced from a genuinely-clean R22 tree (`make clean` + extract-all-136 + check-all) after every banked batch. The whole-binary byte-gate (`harvest_verify`, G3/P9) was the sole per-bank arbiter and **never accepted a wrong match** across the phase.
- **Fleet: 66.02% → ~74.6% fn-count** (the arc: 66.02 → 70.82 → 71.36 → 72.18 → 73.66 → 73.97 → 74.36 → 74.48 → 74.58 → tonight's flagship). **Weighted (the honest metrics, `progress.py --weighted` introduced this phase): instr-weighted 58.2% (decomp.dev-display), distinct-code 30.3%** (29,322 / 84,996 unique fns). **0 NON_MATCHING** in any default build (G4); `dedup-check` 1813 validated / 0 failed.
- **Flagship `func_80133CD4` (399 ins) byte-identical** (whole-binary gate `d19c9580`), `family_sweep` **133/133** siblings ×134, PIN-FREE — the ~22-phase "unsteerable whole-function register permutation" retired.
- **The reframe (byte-verified tonight, R14):** the "36k unique / 87.3% distinct-code tail" is a **strict-`h_norm` artifact** — re-clustered by `h_seq` (mnemonic skeleton), **90% collapses into ~754 families** (986 substantial nins≥80 / 1.88M ins, top-20 = 52%), all per-location-shaped, templatability confirmed (identical nbytes/ncalls/call-sequence across ~120 members).
- `git status`: only `config/`/`tools/`/`src/`/`docs/`/`phase-ends/` tracked across the phase; zero ROM-derived/generated bulk staged; the `db.*.gbf` churn is R23 restart-noise (never staged); **no Ghidra DB change** (matching used cached Ghidra-C + asm).

**Milestone achieved (confirmed by Drew, gate 2):** The structural-family endgame drove the fleet **66.02% → ~74.6% fn-count (58.2% instr-weighted / 30.3% distinct-code)**, banking the mechanical `h_norm`-family sweep engine (`family_remap`/`family_sweep`, ~20k+ member-matches for ~0 agent tokens), the T6/T7 curriculum + recovery tooling (`canon_sig_reconcile` v3.2, `rtu_match`), and the **complete giant endgame** (every matchable region-a giant ×134, capped by the 399-ins flagship `func_80133CD4` via the §45 Fable5 gdb-on-cc1 crack) — then **closed on the strategic reframe** (R14) that the remaining "unique tail" is really **~986 templatable `h_seq` families**, the discovery that defines the finish plan and is handed forward as `docs/family-endgame-megaplan.md`. 136/136 byte-identical, 0 NON_MATCHING throughout.

**Next:** **Phase 26 — the family-endgame (finish the decomp).** A fresh session, **plan-mode + Fable5** (Tier-1 Phase-Start). Start from **`docs/family-endgame-megaplan.md`**: Step A (cheap `h_seq` family map + templatability validation + exemplar triage — the measured foundation) → Step B (Fable5 hard family CORES + the 2 permanent walls + the 3 walled reach-134 giants) → Step C (`family_remap` immediate-substitution + the mechanical ×120 harvest + the 5.9 MB matched-free propagation) → Step D (the genuine unique residue + the 5 behemoths — last). **Fable5 is gone after ~2026-07-13** — spend it only on the hard family cores + the class-walls (permanent idioms), never the unique behemoths.

## Deviations
| Item | Plan | Actual | Reason |
|---|---|---|---|
| Milestone shape | "close when top-family ROI drops" (open-ended) | closed on the **h_seq reframe** + a giant-endgame checkpoint | the cheap tiers were byte-proven exhausted on the giant/near-miss tail, and the reframe redirects to a distinct approach (a new phase) |
| The "unique tail" | assumed ~36k unique hand-decomps (strict h_norm) | **90% is ~754 h_seq families** (R14 — the grouping was the artifact, not the code) | Drew's intuition + a byte-verified re-cluster; the single most consequential finding of the phase |
| Giant route | permuter/cheap-Opus first, Fable5 on walls | flagship cracked by **Fable5 gdb-on-cc1** (§45); 3 flywheel giants + F-band permuter batch all WALLED → Fable5 | RC-6/S3/allocno-tie intrinsic ties; the free tiers improve *toward* but can't close them (byte-proven) |
| Fable5 usage doctrine | (not pre-specified) | **parallel-isolated agents, distill-between, NOT batched** (context-accumulation is ~N× costlier; the §31 map already amortizes the source-read) | measured this session; the flagship = 125 tool-calls / 506k tokens solo |
| v4 local model | retrain + gate | **FAILED/negative — keep v3** (7B capacity-bound) | corpus-quality>size; the local tier is a $0 ≤15-ins mop-up, off the critical path |
| Phase close | write PhaseEnd + continue | close + hand a **megaplan** to a fresh plan-mode/Fable5 phase | the finish is a distinct plan-mode Phase Start (two-gate model); Drew's call |

## Commit Message
```
(Phase 25 landed across many sessions of checkpoint commits; key closes: commit:0514 giant batch 1,
commit:0515 flagship ×134 + §45, commit:0516 family-endgame megaplan + checkpoint, + this PhaseEnd.)

feat(phase-25): close — structural-family endgame + the giant endgame + the h_seq family reframe (v1.24.0)

- MECHANICAL FAMILY ENGINE: family_manifest/family_remap/family_sweep + canon_sig_reconcile v3.2 +
  rtu_match; ~20k+ member-matches banked for ~0 agent tokens (h_norm families are TEMPLATES, T3).
  Fleet 66.02% -> ~74.6% fn-count (58.2% instr-weighted / 30.3% distinct-code, progress.py --weighted).
- GIANT ENDGAME COMPLETE: every matchable region-a giant ×134 incl. the 399-ins flagship func_80133CD4
  (§45 Fable5 gdb-on-cc1 crack: merged-accumulator-variables + 1-death local-alloc in-out-asm + /s +
  goto-ret; the ~22-phase 'unsteerable' verdict retired). 3 flywheel giants + F-band permuter batch
  WALLED -> Fable5 (recon-done pin-free seeds + gdb specs).
- THE REFRAME (R14, byte-verified): the '36k unique / 87% distinct-code tail' is a strict-h_norm
  artifact; re-clustered by h_seq it collapses 90% into ~754 families (986 substantial / 1.88M ins,
  top-20=52%), templatability confirmed. Endgame = crack ~986 exemplars -> template ×120.
- cookbook §40-§45; docs/{phase25-t6-curriculum,phase25-frontier-map,family-endgame-megaplan}.md.
  136/136 byte-identical (R22), 0 NON_MATCHING (G4), dedup 1813/0. No new governance rules (techniques
  -> cookbook; the reframe -> the megaplan). worklog -> logs/Phase25.md (R19). bumps 1.23.0 -> 1.24.0.
```

## Rules Added This Phase
| Rule | Reason |
|---|---|
| **R31 — Capture the WHY behind strategic pivots in `docs/decision-log.md`, while fresh** (confirmed by Drew 2026-07-08, binding). At each major direction change / dead-end / reversal, log (during the producing session): context+belief → what failed → the pivot → the byte/measurement-grounded why → a hindsight "better path." Extends R30 (technical artifacts) to STRATEGIC/decision rationale — the perishable judgment the terse Deviations table can't hold. Forward-only. The substrate for the eventual retrospective + the public "how to AI-decomp" wiki. | The terse PhaseEnd loses the reasoning; a fresh session reconstructing from compressed summaries would lose it. Exercised all phase (the T3 pivot, the giant campaign, the h_seq reframe). |

*(No OTHER new governance rules — per the Phase-8+ precedent, the phase's lessons are techniques (→ cookbook §40–§45) + findings (→ the megaplan + the `structural-family-mechanical-remap` memory, updated with the h_seq refinement). The **h_seq re-cluster methodology** ("before declaring code unique, regroup by the looser fingerprint — strict h_norm over-fragments per-location families on immediates") is a direct application of **R14** (verify the grouping against the bytes) and is captured in the megaplan + memory. The **Fable5 parallel-isolated / distill-between doctrine** → effort-map + the `breadth-isolated-agents-not-serial` memory. G3/P9/R14/R16/R22/R26/R27/R30 governed the phase.)*

## PhaseEnd Changelog
**v1.23.0 → v1.24.0 — Phase 25 complete (Gen2 phase 17; the structural-family endgame + the giant endgame + the reframe).** The phase built and ran the **mechanical family engine** — `family_remap`/`family_sweep` (crack one exemplar → positionally remap per-overlay symbols → whole-binary byte-gate), banking **~20k+ member-matches for ~0 agent tokens** (proving h_norm families are TEMPLATES, not free dedup) — plus the T6/T7 curriculum and the def-side-wall recovery tooling (`canon_sig_reconcile` v3.2, `rtu_match`, the object-probe≠gate correction). It **completed the giant endgame** (every matchable region-a giant ×134, capped by the 399-ins flagship `func_80133CD4` cracked PIN-FREE via a Fable5 gdb-on-cc1 read of the allocator → cookbook §45), driving the fleet **66.02% → ~74.6% fn-count (58.2% instr-weighted / 30.3% distinct-code)** at 136/136 byte-identical, 0 NON_MATCHING throughout. The mature gcc-2.7.2 toolkit is now §17–§45. **The decisive close (R14):** regrouping the unmatched frontier by the looser **`h_seq`** fingerprint proved the "36k unique / 87% distinct-code tail" is a strict-`h_norm` artifact — **90% is ~754 templatable per-location families** (986 substantial / 1.88M ins; top-20 = 52%; same function at one address × ~120 overlays, differing only in per-location constants). That turns the endgame from "36k hand-decomps" into "crack ~986 exemplars → template ×~120," and it is handed forward as **`docs/family-endgame-megaplan.md`** for a fresh plan-mode + Fable5 **Phase 26**. One rule was added mid-phase (**R31**, capture-the-why); no other governance rules (techniques → cookbook, the reframe → the megaplan). The 3 walled reach-134 giants, the 2 permanent walls, and the F-band residuals are all carried forward in the megaplan §6 (recon-done seeds + specs), so nothing is lost on close.

## Plain-English Recap
This was a huge, multi-day push, and it ended on a discovery that changes the whole finish line. First, we built a "stamp" machine: once we reconstruct one copy of a piece of engine code, the tool automatically produces the matching copy for all ~120 game locations and checks each is bit-perfect — so **tens of thousands of functions got reconstructed for almost no extra effort**. That pushed the game from ~66% to ~75% (by function count). We also finished off the "giant" functions — the biggest, most-reused engine routines — including a 400-instruction monster we'd literally called "impossible" for most of the project; the top AI model, reading the actual 1990s compiler's source code, cracked it cleanly, and we wrote the trick down so cheaper AI can reuse it. But the **biggest win was a course-correction Drew pushed for**: the ~36,000 leftover functions looked like a hopeless one-by-one grind, but that was an illusion caused by how strictly we were grouping them. When we grouped them more loosely — by their *instruction skeleton* instead of exact details — **90% of them turned out to be the same handful of functions repeated once per game location**, just with different numbers filled in. So instead of 36,000 unique puzzles, it's really about **986 puzzles, each of which stamps into ~120 places once solved.** That makes "finish the decomp this weekend" genuinely plausible. We wrote all of this — the data, the plan, and exactly what to point the best AI model at before it goes away in two days — into a single handoff document for the next planning session. Everything still rebuilds perfectly; nothing broke.

## 🛑 Stop Here
PhaseEnd written; `CURRENT_PHASE.md` archived → `phase-ends/logs/Phase25.md` (R19, via `git mv` — left uncommitted). **Drew commits AND pushes** this PhaseEnd + the archived log (R6/R8 — the milestone-close is the human-controlled gate-2 sign-off; tonight's matching/docs commits `commit:0514`..`commit:0516` are already landed). No Ghidra DB change this phase (R23 no-op — the `db.*.gbf` churn is restart-noise; do NOT stage). Gen2 continues — do **NOT** start Phase 26 here. Start a **fresh session** (effort **Max**, **plan mode**, Fable5 for the plan-draft) for **Phase 26 — the family-endgame (finish the decomp)**, opening from `docs/family-endgame-megaplan.md` (Step A cheap map+triage first — the measured foundation). Keep this file forever.
