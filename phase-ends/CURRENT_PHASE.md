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
- [x] T2 — Exemplar target manifest (tools/family_manifest.py: 2,764 multi-member families → 127 draftable / 156 matched-free / 2481 absent)
- [x] T3 — Swing-question PROOF: free `--tier h_norm` REFUTED (0/133); **mechanical symbol-remap lever PROVEN** (tools/family_remap.py)  ← endgame reshaped, see log
- [ ] T4 — v4 retrain + A/B gate (cheap drafter prep; may run parallel to T2/T3)
- [ ] T5 — Cheap-tier soften + measure wave → the complete class/closeness frontier map (Step A) + pre-advanced seeds  *(Ultracode — prompt)*
- [ ] T6 — Step B: Fable5Max curriculum authoring from the measured map  *(Fable5Max — prompt)*
- [ ] T7 — Sweep one exemplar per family, curriculum-ordered (validate top ~3-5 first, then scale)  *(Ultracode harvests / Fable5 discovery — prompt)*
- [ ] Close — clean-fleet verify · PhaseEnd synthesis · plain-English recap (R25) · Phase-26 backlog

## FRESH SESSION — RESUME HERE  (T7 in progress; finish T7 → Close; do NOT start T4 yet, per Drew 2026-07-08)
**Done + committed:** T0–T3 + the **T7 matched-free MECHANICAL sweep** — fleet **66.02% → 70.82%** (+16,512
member-matches; R22 clean-fleet **136/136**; commit `commit:0476`). Tools PROVEN + committed: `tools/family_remap.py`
(the remap lever), `tools/family_sweep.py` (sweep driver), `tools/family_manifest.py` (T2), split-aware `recover_integration`.

**The mechanical family method (the phase's engine — T3):** h_norm families are TEMPLATES, not free dedup. Per
family: crack ONE exemplar → `family_remap` builds each member's C by positionally substituting the per-overlay
symbols (read from each member's image) → **plain `harvest_verify`** byte-gate (NOT gate_stage's transforms — they
perturb a correct remap). ~0 agent tokens/member. `func_` names are UPPERCASE-hex.

**NEXT (finish T7, then Close):**
1. **Re-run surveys first:** `make sig-overlays` (idempotent) → `.venv/bin/python tools/family_manifest.py` — the
   matched set grew 16.5k, so the draftable/matched-free split updates.
2. **Decl-reconcile the 29 `type/decl` deferred** (`.run/sweep_deferred.txt`): exemplars use LOCAL types (e.g.
   `MatEntry`, defined in ov_SC01_077.c not engine_types.h) so the remapped draft won't compile. Fix:
   `tools/build_engine_types.py --source ov_SC01_077 --strip` (lift local types to `src/shared/engine_types.h`,
   byte-neutral — verify ov_SC01_077 still builds `d19c9580`), then `tools/family_sweep.py --only <the 29 addrs>`
   → ~+3,800 banks. Clean-fleet verify (R22) + commit.
3. **8 edge cases** (`.run/sweep_deferred.txt`: 4 diff + 4 remap-fail): `0x8013c360` = -O0 cluster; `0x80165ca0`/
   `0x8012a018` = known Phase-24 stragglers. Brief look or defer.
4. **683 whole-binary-diff simple failures** (~4%: match_one-MATCH but TU-context diff, like the T1 memcpy idiom):
   defer as a small residual or batch-investigate.
5. **The 127 DRAFTABLE families / 6.7 MB** (`docs/family-manifest.md`): their ov077 exemplar is a STUB → must be
   CRACKED first — **this is where T4 (v4) + T5 (the Ultracode wave) come back**: crack the 127 exemplars, then
   `family_sweep` remaps their members ×134 free. **Prompt for `/effort ultracode` before the wave (R27).**
6. **Close:** clean-fleet verify, PhaseEnd (R25 recap). Byte-weighted % (~31%→) rises materially now (big families).

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

### T2 — Exemplar-scoped target manifest ✅ (2026-07-08)
- **Deliverable:** `tools/family_manifest.py` (committed, reusable) → `docs/family-manifest.md` + gitignored
  `.run/family_manifest.json`. Regroups the unmatched frontier by h_norm; per family: the ov_SC01_077 drafting
  exemplar (where present), **instances** (the ×N leverage — NOT h_exact-reach, ~1-3 for byte-shattered families),
  size, byte-weight. 44,101 families; **2,764 multi-member / 11.1 MB**.
- **The endgame's 3 levers (× ov_SC01_077 membership):**
  - **draftable 127 / 6.7 MB** — unmatched ov077 member → draft the exemplar (primary T5/T7; most byte-weight).
  - **matched-free 156 / 2.3 MB** — matched ov077 member + unmatched siblings → FREE `--tier h_norm` propagation
    (draft-free; the T3 proof + a free win).
  - **absent 2481 / 2.1 MB** — no ov077 member → small fns in other overlays, draft elsewhere (low priority).
- **Insight:** h_norm families are reloc-only by construction, so the matched-free bucket is likely bankable NOW by
  re-propagating already-matched ov077 fns via `--tier h_norm` (byte-gated). T3 tests decisively.
- T3 candidates (mid-size draftable): 0x8012c890(149)/0x8016d1d8(148)/0x8013d9b0(141) — all inst=134, ~127 hexcls.

### T3 — Swing-question PROOF ✅ (2026-07-08) — free lever refuted; **mechanical remap PROVEN** (the phase's pivot)
- **Free `--tier h_norm` dedup REFUTED (R14):** propagating ov_SC01_077's matched `0x80141100` across its 133
  h_norm-siblings banked **0/133** (all byte-diverge). h_norm families are byte-shattered *because each member
  references per-overlay symbols* (`D_80187xxx` in ov077 vs `D_8017Fxxx` in ov000) — one C body can't name 134
  overlays' symbols. This also kills the plan's draft-then-propagate fallback (same mechanism).
- **Mechanical symbol-remap lever PROVEN → `tools/family_remap.py`:** two h_norm-identical members have identical
  instruction streams except in the masked reloc fields, so disassemble both overlay images at ADDR, positionally
  pair the resolved reloc targets, substitute the exemplar C's per-overlay symbol NAMES with the sibling's. Verified:
  reloc decoder **22/22** vs .s; `0x80141100`→ov_SC01_000 **whole-binary BYTE-IDENTICAL + harvest_verify banked**
  (9052dc0e); **12/12** siblings SC01-SC07 match_one; **7/9 families × 3 siblings = 21/27** match_one.
- **The 2 failures = decl/type plumbing** (custom `MatEntry` type + conflicting shared `ApplyMatrixSV` decl — a
  COMPILE error, NOT a byte mismatch): the remapped draft must reconcile decls with the target's ambient
  engine_core.h/engine_types.h (strip ambient externs). A known-solved T7 refinement, not a remap failure.
- **Gate path for remapped drafts = plain `harvest_verify`** (gate_stage's canon/cast/sig_unify transforms PERTURB
  an already-correct remap → 0-bank; skip them for remaps).
- **Endgame reshaped:** the 11.1 MB h_norm families are cheaply, MECHANICALLY recoverable — crack ONE exemplar per
  family → remap+gate members (~0 agent tokens/member). Members no longer need drafting; only exemplars do.

### T7 (part 1) — MECHANICAL family sweep: matched-free harvest ✅ (2026-07-08, `commit:0476`)
- Built `tools/family_sweep.py` (two-phase: stage all remaps per overlay, gate each (overlay,split) group ONCE via
  plain `harvest_verify`; a `match_one` pre-classify defers compile-failing type-using families to avoid bisection
  blowup). Driver validated on `func_80141100` (133/133 banked, committed `commit:0475`).
- **BANKED 16,512 member-matches** (131 simple exemplars × ~133 siblings) + the 133 validation; **0 remap-fail**.
  **R22 clean-fleet verify: 136/136 byte-identical** from a fully clean tree (make clean + extract-all + check-all).
  **Fleet 66.02% → 70.82%** (+4.8% in ONE deterministic, ~0-agent-token pass). dedup-check 1813/0.
- Deferred (`.run/sweep_deferred.txt`): 29 type/decl (type-lift recoverable), 4 diff, 4 remap-fail.
- 683 / 17,195 simple drafts failed the whole-binary gate (match_one-MATCH but TU-context diff, ~4%; auto-reverted).
- **Reproduce:** `family_sweep.py --limit 0` (after `make sig-overlays`). The remap is `family_remap.py`.
