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
- [x] T1 — Integration-recovery pass (split-aware recover_integration fix; caller-arity cohort exhausted 0/16 — residuals backlogged)
- [ ] **T2 — Build the exemplar-scoped, class-routed target manifest** (one per h_norm family + reach-1 uniques + reach-134 h_exact tractable)  ← CURRENT
- [ ] T3 — Swing-question PROOF (match one mid-size reloc-only family exemplar → `--tier h_norm --recover` → measure ×134 bank count)
- [ ] T4 — v4 retrain + A/B gate (cheap drafter prep; may run parallel to T2/T3)
- [ ] T5 — Cheap-tier soften + measure wave → the complete class/closeness frontier map (Step A) + pre-advanced seeds  *(Ultracode — prompt)*
- [ ] T6 — Step B: Fable5Max curriculum authoring from the measured map  *(Fable5Max — prompt)*
- [ ] T7 — Sweep one exemplar per family, curriculum-ordered (validate top ~3-5 first, then scale)  *(Ultracode harvests / Fable5 discovery — prompt)*
- [ ] Close — clean-fleet verify · PhaseEnd synthesis · plain-English recap (R25) · Phase-26 backlog

## Current task — T2: Exemplar-scoped, class-routed target manifest
Build the ONE-exemplar-per-family target set from the T0 surveys: extend `.run/probe_hnorm.py` (or a companion)
to emit a ranked manifest of the 2,764 multi-member h_norm families — per family: rep addr, exemplar (an
ov_SC01_077 member if present, else any overlay+addr to draft), n_instances, n_hexcls, maxIns, reach, byteMB,
size bucket. Plus the reach-134 h_exact tractable stubs (warm-up) + reach-1 uniques. NOTE (T0/T3): an h_norm
family is **reloc-only by construction** (norm_stream masks only jal/HI16/LO16, keeps true immediates+regs), so
h_norm-identical ⟹ intra-family diffs are reloc-only; whether ONE C body matches all 134 additionally needs the
reloc targets to be consistently-named-per-overlay symbols — T3 proves that empirically via `--tier h_norm`.
Output: `.run/family_manifest.json` + a committed digest. This scaffolds Step A (the curriculum input).

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

### T1 — Integration-recovery pass ✅ (2026-07-08) — cheap cohort exhausted; deliverable = the split-aware fix
- **Deliverable (committed `commit:0470`):** `recover_integration` made split-aware (§39 gap). It was silently
  skipping the **263-stub `ov_SC01_077_after`** cohort (drift-check hardcoded the main asm subdir; gate_stage
  never got src/asm/src_file). Now `stub_map()` reads each stub's asm subdir from its INCLUDE_ASM line and
  `reconcile_and_gate` gates per split-file group (run_gate self-filters; propagate idempotent). Reusable T5/T7.
- **Finding (R14/P9):** the closeness-0 **caller-arity** cohort is EXHAUSTED — `--auto --limit 20` banked
  **0/16** (Phase 24 already banked the cheap decl-plumbing ones). Residuals (incl. both flagships) are
  **per-function TU-context matching**, not decl-plumbing.
- **The blocker class (matching idiom → cookbook when it recurs, R16):** an 8-byte mem-copy written as a
  **struct-assign** `*(T*)x = *(T*)y` (func_8014F4C0's `Vec4u`) is `match_one`-MATCH in isolation but lowers to a
  **memcpy CALL** in a TU that declares `memcpy` (sibling `extern void *memcpy(...)` disables the builtin) → byte
  mismatch (`9d043345`≠`d19c9580`). Banked sibling convention = **explicit `memcpy(x,y,8)` or field-by-field
  lhu/sh** (the target uses lhu/sh). T5/T7 drafters: avoid struct-assign for small mem-copies in these overlays.
- **Decision (Drew):** conclude T1; closeness-0 residuals stay in the ranked backlog (available later); the 2
  flagship ×134 leaf-matches NOT hand-banked (per-function ROI < the family lever).
