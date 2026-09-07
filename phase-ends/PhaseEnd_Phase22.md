# PhaseEnd — Phase 22: Hand-grind the giants (×134) — banked the tractable tail; the irreducible giants byte-deferred
**Date:** 2026-06-29 · **Project Version:** 1.21.0 · **Phase Status:** Complete (open-ended phase; closed at Drew's gate after the tractable-giant ROI dropped to the irreducible scheduler/regalloc tail, and the session pivoted to building the offline LLM matching tier → Phase 23) · **Generation:** Gen2 (14th phase of the arc; 14 deferred to Gen3+)

> Gen2 phase 14 (8→…→21→**22**). The granular per-task crash-recovery trail (every giant crack, the type-lift archaeology, the close=0 recovery batch, the grinder ROI audit) is preserved on-demand at **`phase-ends/logs/Phase22.md`** (R19 — NOT auto-loaded; consult only when researching a mechanism). This file is the synthesis. Owner decisions (Drew): calibrate on a mid-giant → hand-grind giants by byte-weight + distill → **close at the checkpoint when giant ROI drops to the irreducible tail**, then **pivot to the free local-model matching tier** (Phase 23, substantially built in the 2026-06-29 session under this still-open phase — its details live in Phase 23's `CURRENT_PHASE.md`, not here).

## Build Log

**Files created/changed and complete — do not recreate:**
- `tools/recover_giant.py` — the canonical-extern recovery lever (rewrite each engine_core.h-callee extern to its canonical def-sig + move ALL externs **block-scope** so the lifted body is "self-contained" for `harvest_verify`/`dedup_propagate`). The missing gate-stage recovery step that banks pure-extern close=0 giants.
- `tools/worklist.py` → `docs/worklist.md` + `.run/worklist.json` — the byte-weighted ranked decision spine (GIANT queue first).
- `src/shared/engine_types.h` extended — the **struct type-lift** lever: lift a giant's local `struct S8`/`B8`/`Blk16`/`Buf32` typedefs to the shared header (byte-neutral, fleet-verified) so the close=0 struct-walled giants bank.
- `src/ov_SC01_077/ov_SC01_077.c` (+ `_a.c`/`_o0.c`) + the 134 overlay `.c` + `config/dedup.us.yaml` — the banked giant matches + ×134 propagations.
- `docs/matching-cookbook.md` **§28** (the 4-way close=0 triage + canonical-extern recovery + the coalescing `$a0` pin) · **§28a** (decomp.wiki gcc PS1-applicable patterns: negative-struct-offset-in-loop, branch-duplication, load-coalescing) · **§28b** (the struct type-lift; serialize all `make` jobs) · **§28c** (close=0 NOT exhausted — R14 corrects §26; the dedup_propagate registry-skip recovery).
- `tools/gate_stage.py` — commit message made **phase-agnostic** (`GATE_PHASE` env, default `decomp`; was hardcoded `phase-21` — the Phase-22 pending-polish note, now cleared for the Phase-23 auto-committing grinder).
- `phase-ends/CURRENT_PHASE.md` → **`phase-ends/logs/Phase22.md`** (R19 archive). `phase-ends/PhaseEnd_Phase22.md` — this file.

**Tools/packages installed:** None for the giants work (existing toolchain). *(Phase 23's LLM tier installed Unsloth/torch in a separate `.venv-train` — recorded in Phase 23's file, not here.)*

**Verification results (literal):**
- **Fleet: 63.18% → 63.66% byte-identical** (+0.48% function-count; byte-weighted gain larger — each giant banks ×134); **136/136 binaries byte-identical maintained throughout**; **0 NON_MATCHING** (G4); `dedup-check` **1633** validated / 0 failed. The whole-binary byte-gate (G3/P9) was the per-bank proof and **never accepted a wrong match**.
- **Banked ×134 this phase (~17 functions):** `func_8015126C` (254, calib — canonical-extern recovery) · `func_80156B74` (214) + `func_80163C2C` (167) (the struct-type-lift trio's tractable two) · the **close=0 recovery batch — 14 functions** (7 `recover_giant`-recovered + 7 inline-matched bonus). Each propagated across all 134 overlays.
- **Byte-DEFERRED (irreducible, logged to backlog with evidence):** `func_80132784` (400 — hoist-vs-remat §10 + register-LIFETIME-reuse the function-scoped `register __asm__` pins can't express) · `func_801372B0` (207 — structurally PERFECT but the giant scheduler/regalloc last-mile, ~173 positional diff, not C-steerable; structural draft banked to backlog as a head-start) · `func_8014F74C` (masked-residual). These are gcc-2.7.2-intrinsic walls, not effort gaps.
- **Grinder ROI audit (the honest accounting):** all-time token-free permuter banks = **7 functions, ALL in Phase 21**; **0 banks in Phase 22** (hard tail exhausted). Two grinder bugs found (fix before reuse): (1) split-file-blind (`.s` lookup misses `_a`/`_o0` subdirs); (2) churn-without-blacklist on permuter-won-but-gate-rejected-for-non-plumbing fns.
- `git status`: only `config/`/`tools/`/`src/`/`docs/`/`phase-ends/` tracked; zero ROM-derived/generated bulk staged; the `db.*.gbf` churn is R23 restart-noise (do NOT stage).

**Milestone achieved (Drew's gate):** the giants that were **hand-crackable** — the canonical-extern close=0 giant, the struct-type-liftable pair, and the 14-function close=0 recovery batch — were **banked ×134** (fleet 63.18 → 63.66%, 136/136 byte-identical throughout), and the **§28 family of idioms** (close=0 triage, canonical-extern recovery, struct type-lift, registry-skip recovery, the decomp.wiki PS1 patterns) + `recover_giant.py` were distilled. The **remaining giants were byte-proven irreducible** (hoist-vs-remat, register-lifetime-reuse, giant-scheduler last-mile) and handed to the backlog — confirming Phase 21's ceiling finding at the giant scale. With the tractable-giant ROI exhausted, the phase closes and the project pivots to its highest-leverage open question: **can a free, local, fine-tuned model grind the small/medium bulk?** (Phase 23.)

**Next:** **Phase 23 — The offline LLM matching tier (free local-model grinder + the data flywheel).** Substantially built already in the 2026-06-29 session (the cheap-tier A/B, the stock-local floor, the LoRA specialist → corpus-v2 → first real banks, the `lora_grind` mass-run driver). See **`phase-ends/CURRENT_PHASE.md`** for the full state, the in-flight calibration run, and the open tasks (the 0/120 broad-rotation banking puzzle, corpus-v3, the scale-to-14B decision).

## Deviations
| Item | Plan | Actual | Reason |
|---|---|---|---|
| Phase scope | hand-grind the full giant queue (func_80144B9C 770 down the list) | banked the **tractable** giants (type-lift + close=0 + canonical-extern); **byte-deferred the irreducible** (func_80132784, func_801372B0, func_8014F74C) | the same gcc-2.7.2 ceiling Phase 21 proved at wave-scale holds at giant-scale: the residuals are intrinsic (hoist-vs-remat, reg-lifetime, scheduler last-mile), not effort gaps |
| Close at | "when giant ROI drops" | closed there **and** the session pivoted to **building the LLM matching tier** — a major unplanned direction | Drew's research question ("offline free model to grind handmatching") opened during this session and proved high-value enough to become Phase 23 |
| CURRENT_PHASE hygiene | kept current per standard | the LLM-tier work ran under an **un-updated** Phase 22 file (caught by Drew) → archived to logs + this PhaseEnd + a fresh Phase-23 file | the session began as "quick research" and snowballed; the phase-tracking discipline was restored at Drew's prompt |
| close=0 giants | "near-free wave" (Phase-21 hypothesis) | **NOT uniform** — 1 pure-extern, 2 struct-walled (needed the type-lift), 1 masked, 1 regressed | R14: per-giant triage, not a blanket lever (cookbook §28) |
| Grinder | a contributing daemon | **0 banks in Phase 22** + 2 bugs found | the permuter's tractable fuel was a Phase-21-era phenomenon; the giant tail is permuter-irreducible |

## Commit Message
```
(Phase 22 landed across the 06-26/27 giant sessions + the 06-29 pivot; checkpoint commits 013806b07..; this close = the archived log + this PhaseEnd.)

feat(phase-22): close — tractable giants banked ×134 (fleet 63.18->63.66%), irreducible tail byte-deferred; pivot to the LLM tier (v1.21.0)

- BANKED ×134 (~17 fns): func_8015126C (canonical-extern recovery) + func_80156B74/func_80163C2C
  (struct type-lift -> engine_types.h) + the 14-fn close=0 recovery batch (recover_giant.py). 136/136
  byte-identical, dedup-check 1633/0, 0 NON_MATCHING throughout.
- IRREDUCIBLE GIANTS byte-deferred w/ evidence: func_80132784 (hoist-vs-remat + reg-lifetime),
  func_801372B0 (scheduler last-mile, structural draft banked), func_8014F74C (masked). gcc-2.7.2
  intrinsic walls -> backlog, not effort gaps. Grinder ROI audit: 7 all-time banks (all Phase 21), 0 since.
- TOOLKIT: recover_giant.py + the engine_types.h type-lift lever; cookbook §28/§28a/§28b/§28c.
  gate_stage commit tag made phase-agnostic (GATE_PHASE).
- PIVOT: Phase 23 = the offline LLM matching tier (built this session; see CURRENT_PHASE.md).
- worklog -> phase-ends/logs/Phase22.md (R19); bumps project version 1.20.0 -> 1.21.0
```

## Rules Added This Phase
| Rule | Reason |
|---|---|
| **None (governance).** Per the Phase-8+ precedent: techniques → cookbook (**§28** family), strategic findings → this synthesis + the archived log. The existing rules covered all the new ground — **G3/P9** (byte-gate is truth), **R14** (verify vs bytes; close=0 not uniform), **R16/R30** (distill + capture-during-session), **R22** (clean-rebuild), **R19** (worklog archive). The Phase-22-spawned LLM-tier discipline (measure-before-investing; the byte-gate makes a weak model a *throughput* risk only; serve on GPU via LM Studio since Unsloth's llama.cpp is CPU-only) is recorded in the `cheap-tier-ab-validated` memory + `docs/gen2-mips-matching-model.md`, and becomes Phase 23's substance. | A hand-grind-then-pivot phase yields techniques + a new R&D direction, not a governance norm. |

## PhaseEnd Changelog
**v1.20.0 → v1.21.0 — Phase 22 complete (Gen2 phase 14; the giant-grinding phase, closed at the irreducible tail + a pivot).** The phase **hand-cracked every *tractable* giant** — the canonical-extern close=0 giant (`func_8015126C`), the struct-type-liftable pair (`func_80156B74`, `func_80163C2C`), and a 14-function close=0 recovery batch — each banked **×134** across the fleet (58.82%→63.18% was Phase 21; this phase **63.18% → 63.66%**, 136/136 byte-identical, dedup-check 1633/0). It distilled the **§28 idiom family** (close=0 4-way triage, the canonical-extern recovery, the struct type-lift to `engine_types.h`, the dedup_propagate registry-skip recovery, the decomp.wiki PS1 patterns) and promoted **`recover_giant.py`**. The decisive finding: the **remaining giants are byte-proven irreducible** — `func_80132784` (hoist-vs-remat + register-lifetime-reuse), `func_801372B0` (structurally perfect but the giant-scheduler last-mile), `func_8014F74C` (masked) — confirming the Phase-21 ceiling at giant scale, with the permuter contributing **0 banks** this phase (its fuel was Phase-21-era). With tractable-giant ROI exhausted, **Drew pivoted the session to the project's biggest open question — a free, local, fine-tuned model for the small/medium bulk** — which became Phase 23 (and was substantially built before this PhaseEnd was written). Phase 22 hands forward: a complete ranked **backlog** of byte-deferred irreducibles, the §28 toolkit, and a validated new direction.

## Plain-English Recap
This phase was the "hand-finish the giant functions" plan from the end of Phase 21. We cracked the giants that *could* be cracked — the ones blocked by fixable plumbing (a struct definition that needed moving to a shared header, or a function signature that needed reconciling) — and each one, once perfect, copied automatically into all 134 levels of the game. That pushed the rebuilt-exactly number from 63.2% to 63.7%, every byte still verified. But the *remaining* giants turned out to be genuinely unbeatable by hand: their last few instructions differ only because the 1997 compiler shuffled them in ways no C rewrite can reproduce — so we documented exactly why, parked them, and stopped throwing effort at a wall. Midway through, you asked the bigger question — *can a free model running on your own machine grind the bulk of the remaining work?* — and that turned out to be valuable enough that we spent the rest of the session building and proving it. So Phase 22 closes having banked the winnable giants and learned the reusable tricks they taught, and we're opening a new phase for the local-AI matching factory we just stood up.

## 🛑 Stop Here
PhaseEnd written; `CURRENT_PHASE.md` archived → `phase-ends/logs/Phase22.md` (R19). Per your standards I normally stop here and a fresh session starts the next phase — but at your explicit direction I am also writing **Phase 23's `CURRENT_PHASE.md` in this session** (setup only — no Phase-23 *execution* work starts here; the calibration run continues on its own). **Drew commits AND pushes** this PhaseEnd + the archived Phase-22 log + the new Phase-23 file + the session's commits (R6/R8 — the milestone-close is the human-controlled gate). No Ghidra DB change (R23 — the `db.*.gbf` churn is restart-noise; do NOT stage). Keep this file forever. Gen2 continues with **Phase 23 — The offline LLM matching tier**.
