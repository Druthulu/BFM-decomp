# CURRENT_PHASE — Phase 25: The structural-family endgame (idiom curriculum)

**Status:** In progress — plan approved 2026-07-08 (gate 1 passed). · **Generation:** Gen2 (17th phase of the
arc; Phase 14 public-flip deferred to Gen3+). · **Effort:** Max (planning/synthesis/deep debugging); **prompt +
wait for the toggle** (R27) → Ultracode for breadth waves (T5, T7 harvests), Fable5Max for new-class discovery +
the T6 curriculum authoring. Claude cannot set effort itself.
**Plan of record:** `/home/musashi/.claude/plans/plan-mode-enabled-max-generic-galaxy.md` (approved, verbatim).
This file is the P3 crash-recovery execution log.

## Scope clarification (Drew, 2026-07-08, at gate 1)
The phase's atomic unit of work is **"solve ONE exemplar per structural family"** — swept across the whole family
set (~2,764 `h_norm` families), curriculum-ordered, cheap-tier-first with Opus/Fable5/permuter escalation. One
solved exemplar → the family propagates ×134 (reloc-only families, free via `--tier h_norm`) **or** yields the
idiom to template the variants (immediate families). The AIM is one exemplar per family for every family the
tiers can crack; genuine gcc-intrinsic-wall families (S3 / RC-6 / cse mega-flush / L6 exemplars) stay
INCLUDE_ASM with logged evidence (G4/P9). This unifies plan T5 (cheap exemplar sweep) + T7 (curriculum-ordered
escalation) into one exemplar-per-family endgame.

## Strategy (approved)
Cheap/free tiers exhaustively FIRST → complete measured frontier map + pre-softened seeds → Fable5Max authors the
idiom curriculum → sweep one exemplar per family (curriculum-ordered), each cracked exemplar propagated ×134 via
`dedup_propagate --tier h_norm`, byte-gated. The whole-binary byte-gate (`harvest_verify`) is the sole arbiter
(G3/P9) — no wrong match can bank; 136/136 byte-identical every batch (R22).

## Tasks
- [x] T0 — Refresh + housekeeping
- [ ] **T1 — Integration-recovery pass** (closeness-0 backlog cohort + the 2 leaf-matches func_8014F4C0/func_80155800)  ← CURRENT
- [ ] T2 — Build the exemplar-scoped, class-routed target manifest (one per h_norm family + reach-1 uniques + reach-134 h_exact tractable)
- [ ] T3 — Swing-question PROOF (match one mid-size reloc-only family exemplar → `--tier h_norm --recover` → measure ×134 bank count)
- [ ] T4 — v4 retrain + A/B gate (cheap drafter prep; may run parallel to T2/T3)
- [ ] T5 — Cheap-tier soften + measure wave → the complete class/closeness frontier map (Step A) + pre-advanced seeds  *(Ultracode — prompt)*
- [ ] T6 — Step B: Fable5Max curriculum authoring from the measured map  *(Fable5Max — prompt)*
- [ ] T7 — Sweep one exemplar per family, curriculum-ordered (validate top ~3-5 first, then scale)  *(Ultracode harvests / Fable5 discovery — prompt)*
- [ ] Close — clean-fleet verify · PhaseEnd synthesis · plain-English recap (R25) · Phase-26 backlog

## Current task — T1: Integration-recovery pass
Bank the closeness-0 "MATCH" backlog cohort (already leaf-matched, whole-binary gate-rejected on TU plumbing)
via `tools/recover_integration.py --auto` / `tools/gate_stage.py`. Priority (top-leverage, already MATCH):
`func_80155800` (145 ins, #3 by leverage — TU-context perturbation, needs Max diagnosis) + `func_8014F4C0`
(141 ins, #4 — same-TU fwd-decl conflict `extern s32 …(void)` vs def `(u8*)` + local `Vec4u` typedef).
Drafts in `.run/wave/` + `.run/backlog_drafts/`. Clean-fleet verify each batch (R22); `--tier h_norm` where a
banked fn is a reloc-only family. Bank the already-matched-but-unintegrated drafts before any softening.

## Blockers
None.

## Per-task log

### T0 — Refresh + housekeeping ✅ (2026-07-08)
- Housekeeping: `gccdump.lreg` (repo root) = gcc's DEFAULT RTL dump (dump-base "gccdump", `.lreg` = local-reg
  pass; `toplev.c:1973/2077`), left by a one-off `cc1 -da` RTL-inspection run with CWD=root — **not** any
  committed tool (grep hits only the gcc source under `tools/reference/`). Deleted; root clean; no other stray
  dumps. Practice: RTL-inspection runs use a `.run/` CWD or `-dumpbase .run/gccdump` (R12).
- Regenerated 134 overlay sigs (`make sig-overlays`, exit 0); rebuilt `fuel_manifest` + `worklist --refresh`
  (stale Jun-26 ranking killed → `docs/worklist.md`: 130 live stubs, top = the wall `func_801412A8`).
- Fixed `tools/sig_image.py` docstring (h_norm is the live `norm_stream`, not a "T5 placeholder" — R21/R30).
- **CURRENT FRONTIER (R14 ground truth):** fleet 66.02%.
  - h_exact: 82,744 unmatched classes / 111,815 instances / **27.33 MB**. Reach-134 tier = **130 classes /
    4.11 MB** (7 tiny + 55 small + 50 med + 16 large + 2 giant-walls). x1-unique = 74,742 classes / **19.99 MB**.
  - h_norm: **44,101 families**; **2,764 multi-member families / 11.1 MB** (the hidden lever). Top: same-address-
    ×134 (func_80133CD4/166994/8013C414 … 126-127 h_exact-cls / 134 inst / 199-399 ins) → match 1 → ×134;
    high-count-small (func_80150480: **1,997 inst × 22 ins** → 1 idiom → ~2000 fns); low-variant
    (func_8014E284/80150170: 2 h_exact-cls / 268 inst → match 2 → ×268).
  - **Solo-monster reframe CONFIRMED:** 3,989 / 8,670 large (≥150-ins) h_exact-reach-1 fns have h_norm siblings
    (46% templatable); 4,681 truly-unique-shape (worst ROI → LAST).
  - Cheap first wins queued: T1 leaf-matches `func_80155800` (#3) + `func_8014F4C0` (#4) ≈ 38k gain_ins
    near-free; 2 permanent walls `func_801412A8`/`func_80178004` stay INCLUDE_ASM (G4).
