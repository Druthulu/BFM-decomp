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
- [ ] T4 — v4 retrain + A/B gate  *(xHigh pipeline; Max to judge A/B)*  ← **NEXT** (T7-mechanical was pulled ahead; now resume planned order)
- [ ] T5 — Cheap-tier soften + measure wave → the complete class/closeness frontier map (Step A) + pre-advanced seeds  *(Ultracode — prompt)*
- [ ] T6 — Step B: Fable5Max curriculum authoring from the measured map  *(Fable5Max — prompt)*
- [~] T7 — Sweep one exemplar per family, curriculum-ordered. **MECHANICAL/free sub-scope DONE** (pulled ahead):
      matched-free harvest (+16,512) + T7.2 type-lift (+1,729) + T7.3 h_exact stragglers (+~200). **REMAINING (the
      real substance):** crack the **127 draftable family exemplars** curriculum-ordered (T6 order), template/propagate ×134.
- [ ] Close — clean-fleet verify · PhaseEnd synthesis · plain-English recap (R25) · Phase-26 backlog  *(NOT yet — phase open)*

## FRESH SESSION — RESUME HERE  (T7-MECHANICAL done & pulled ahead; **NEXT = T4 → T5 → T6 → T7-cracking**; phase OPEN, no PhaseEnd)
**Clarification (Drew, 2026-07-08):** "do NOT start T4 *yet*" meant *finish the pulled-ahead mechanical T7 sweep
first* — **NOT** defer T4 to Phase 26. T4/T5/T6 + T7's exemplar-cracking (the 127 draftable families / 6.7 MB) are
the phase's CORE remaining work. The mechanical sweeps were the cheap prelude.

**Done + committed:** T0–T3 + T7-part-1 (matched-free sweep, `commit:0476`) + **T7.2 decl-reconcile** (`commit:0479`) +
**T7.3 h_exact stragglers** (`commit:0481`) — fleet **66.02% → 70.82% → 71.32% → 71.36%**. T7.2 banked **1,729**
(base 532 + `_after` 1,197) via type-lift + mechanical remap; T7.3 banked **~200** via `dedup_propagate`; **R22
clean-fleet 136/136** every batch, dedup-check 1813/0.

**The mechanical family method (the phase's engine — T3):** h_norm families are TEMPLATES, not free dedup. Per
family: crack ONE exemplar → `family_remap` builds each member's C by positionally substituting the per-overlay
symbols (read from each member's image) → **plain `harvest_verify`** byte-gate (NOT gate_stage's transforms — they
perturb a correct remap). ~0 agent tokens/member. `func_` names are UPPERCASE-hex.

**T7.2 findings (durable — cookbook §40 refinement):** (1) `family_sweep --no-preclassify` — the match_one
pre-classify compiles in ISOLATION (`-Iinclude` only) so it CANNOT see `src/shared/engine_types.h` (pulled by the
real overlay TUs via `../shared/engine_core.h`); it false-negatives every type-lifted family. The flag routes
remappable exemplars straight to the real-TU `harvest_verify` byte-gate (the sole arbiter). (2) The overlay SPLIT
files (`_a`/`_after`/`_o0`) are SEPARATE TUs with conflicting/​shadowing local types → a blind "lift all splits" is
UNSAFE: `Buf` has a DIFFERENT layout in `_a` vs `_after` (fleet-wide lift → `conflicting types` in the other TU),
and `_a` defines `MATRIX`/`VECTOR` = PsyQ SDK names (fleet-wide lift SHADOWS the real types). Safe mechanical ceiling
= base types + `_after` minus `Buf`. New tool knobs: `build_engine_types --file <split.c>` + `--exclude <names>`.

**NEXT — resume the planned order (T7-mechanical was pulled ahead):**
1. ✅ T7.1 surveys · ✅ T7.2 decl-reconcile (1,729; `commit:0479`) · ✅ T7.3 h_exact stragglers (~200; `commit:0481`).
2. **T4 — v4 retrain + A/B gate** *(xHigh pipeline; Max to judge A/B)*. Retrain v4 on the Phase-23/24 banked-idiom
   corpus; A/B vs v3 (`ab_match.js`/`ab_score.py`). Keep v4 in the wave only where it beats v3. $0 to run.
   (`models/bfm-match-7b-v3` is the current; doc `docs/gen2-mips-matching-model.md`.)
3. **T5 — cheap-tier soften + measure wave** → the complete class/closeness frontier map (Step A) + pre-advanced
   seeds. **Prompt `/effort ultracode` (R27)** — this is the breadth wave.
4. **T6 — Fable5Max curriculum authoring** from the measured map. **Prompt for Fable5Max (R27).**
5. **T7-cracking** — execute the top structural families curriculum-ordered: crack each exemplar (127 draftable /
   6.7 MB), template/propagate ×134, byte-gate. Validate top ~3-5 first, then scale (Phase-15/16 lesson).
6. **Close** — only when top-family ROI drops (open-ended, per plan §Milestone). NOT before.

**Residual backlog (revisit after the curriculum; genuine Phase-26 candidates):**
- **T7.2 residual: 16 split-TU-type families / ~2,128 members** — need per-type reconciliation (namespaced/per-TU
  header, rename the cross-TU `Buf`, or verify `_a`'s PsyQ MATRIX/VECTOR are layout-compatible + use real SDK
  headers) — NOT mechanical. `.run/sweep_deferred.preT72.txt` = the 29 addrs.
- **h_exact engine-core straggler class** — more `DEFINE_func` macros likely stub in siblings (`dedup_propagate
  --auto` MISSES them — it only converts INLINE defs). Sweep by `--addr`. Plus inline→macro hygiene of T7.2's
  h_exact-identical inline banks (10 fns; byte-neutral). A small `family_remap.extract_unit` fix to handle macro
  bodies would unblock the 2 h_norm-macro remap-fails (`8012A568`/`80138C30`).
- **683 whole-binary-diff simple failures** (~4%: match_one-MATCH but TU-context diff, like the memcpy idiom).
- `0x8013c360` (-O0 cluster); the 2 permanent giant walls `func_801412A8`/`func_80178004` (G4, INCLUDE_ASM).

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

### T7.2 — decl-reconcile the 29 type/decl families ✅ (2026-07-08, `commit:0479`) — 1,729 banked; split-TU wall found
- **T7.1 refresh:** `make sig-overlays` (134 re-signed) + `family_manifest.py` — levers unchanged (2,764 families;
  127 draftable / 156 matched-free) because they key on ov077 membership, which the 16.5k sibling-banks didn't change.
- **Base type-lift:** `build_engine_types --source ov_SC01_077 --strip` lifted 4 base-local types (`MatEntry`,
  `P_TAG`, `OtBlk`, `packed_word`/`word_bytes`) → `engine_types.h`; byte-neutral (ov077 d19c9580). Banked **532**.
- **The pre-classify false-negative (R14):** after the lift, all 29 STILL pre-classified as `type/decl` (0 simple).
  Root cause: `match_one` isolation compiles with `-Iinclude` + a prepended `common.h` — it does NOT see
  `src/shared/engine_types.h` (the real overlay TU pulls it via `../shared/engine_core.h`). PROVEN false-negative:
  single real-TU gate `func_80142A80`→ov_SC01_000 = `9052dc0e` BYTE-IDENTICAL. FIX: `family_sweep --no-preclassify`.
- **The split-TU wall:** the 25 remaining families need types from the overlay SPLIT files, which are SEPARATE .o TUs
  with conflicting/​shadowing local types. Blind "lift all splits" FAILED: `typedef Buf` has a DIFFERENT layout in
  `_a.c` vs `_after.c` (`conflicting types for Buf` when shared); `_a.c` defines `MATRIX`/`VECTOR` (PsyQ SDK names →
  fleet-wide SHADOW). Safe ceiling = base + `_after` **minus Buf** (`build_engine_types --file … --exclude Buf`):
  byte-neutral, banked **+1,197** (9 of 10 `_after` families/overlay; the 1 miss is the Buf-user).
- **T7.2 TOTAL 1,729** (532 + 1,197). **R22 clean-fleet 136/136** from clean tree; dedup-check 1813/0; fleet **71.32%**.
- **Deferred → Phase 26:** 16 families / ~2,128 members (see backlog above). Old deferred snapshot preserved at
  `.run/sweep_deferred.preT72.txt` (the 29 addrs).
- **Reproduce:** `build_engine_types --source ov_SC01_077 --strip` ; `build_engine_types --file
  src/ov_SC01_077/ov_SC01_077_after.c --exclude Buf --strip` ; `family_sweep --only <29 addrs> --no-preclassify`.

### T7.3 — edge-case triage: 2 h_exact stragglers banked ✅ (2026-07-08, `commit:0481`) — +~200 members
- Triaged the 8 T7-part-1 edge cases (4 diff + 4 remap-fail). **Finding:** the 4 remap-fails are matched in ov077 via
  the `DEFINE_func_<ADDR>()` engine-core MACRO (§11 h_exact source-share), NOT an inline def — so `family_remap`'s
  `extract_unit` (keys on a `func_<ADDR>(` DEFINITION) can't extract them. 2 of them (`func_80128EA8`, `func_80132EC4`)
  are **h_exact-identical** fleet-wide but were **stub in 100 overlays** → banked via the EXISTING `dedup_propagate
  --addr --tier h_exact` (118 overlays byte-identical each). **R22 clean-fleet 136/136; dedup-check 1813/0; fleet
  71.32% → 71.36%.** (byte-% moves little: asm stubs were already byte-identical; the win is 200 fns now C, not asm.)
- **Deferred → Phase 26:** the 2 h_norm-macro remap-fails (`8012A568`/`80138C30` — h_norm AND macro-defined, neither
  h_exact-propagatable nor family_remap-extractable); `8013C360` (-O0 cluster); the 4 "diff" cases mostly already
  banked (stub-in-0 now).

## SESSION PROGRESS (2026-07-08) — T7-mechanical pulled ahead; phase OPEN (T4→T5→T6→T7-cracking remain)
**This session (T7.1–T7.3, all committed, R6 = Drew pushes):** fleet **70.82% → 71.36%**; **+1,929 member-matches**
(T7.2 1,729 via type-lift+remap `commit:0479`/`commit:0480`; T7.3 ~200 via h_exact propagation `commit:0481`/`commit:0482`).
Every batch R22 clean-fleet **136/136**, dedup-check 1813/0. Tools added: `family_sweep --no-preclassify`;
`build_engine_types --file/--exclude`. Cookbook **§40a** written (R30). **NEXT = T4** (see the RESUME section above);
NOT closing — the curriculum + 127-draftable exemplar-cracking is the phase's core, still ahead.

### T4 — v4 LoRA retrain + A/B gate ⏳ IN PROGRESS (2026-07-08)
- **Corpus re-exported** (`export_pairs`, mines the now-fully-built objects): **2,891 → 3,574 pairs** (v3-era snapshot
  saved at `datasets/match_pairs/pairs.v3era.jsonl`). Size dist: ≤5=784, 6-15=1199, **16-40=994, >40=597** — the
  medium/large signal v3 (trained pre-giant-campaign) lacked. `format_finetune` → **3,176 train / 360 test** (99% compile).
- **Training LAUNCHED** (`.run/train_v4.log`, pid 282216 @ 2026-07-08): `train_lora --out models/bfm-match-7b-v4
  --maxlen 2048 --batch 1 --epochs 3 --rank 16` (v3's exact recipe; only the corpus changed → fair A/B). ~2-3h on the
  3080 Ti. Completion-waiter = bg task; models/ + datasets/ are gitignored (R20) so nothing to commit until the A/B decision.
- **NEXT when training ends:** `eval_lora --test datasets/match_pairs/test.jsonl` on BOTH v3 and v4 (same held-out set,
  gate-true) → A/B. **Keep v4 in the wave only where it beats v3** (else fall back to v3). Then T5 (prompt `/effort ultracode`).
- **If context compacts mid-train:** check `.run/train_v4.log` for `train_runtime` (done) or a Traceback (failed);
  if `models/bfm-match-7b-v4/adapter_model.safetensors` exists, training finished — proceed to eval.

## RULES PROPOSED THIS PHASE (ratify at PhaseEnd — P10)
- **R31 — Capture the WHY behind strategic pivots in `docs/decision-log.md`, while fresh.** At each major
  direction change / dead-end / reversal, log (during the producing session): context+belief → what was
  tried that failed → the pivot → the byte/measurement-grounded why → a hindsight "better path" note.
  Extends R30 (which covers TECHNICAL artifacts — cookbook idioms, byte-verified findings, distillations)
  to STRATEGIC / decision rationale — the perishable judgment the terse PhaseEnd Deviations table can't
  hold and a fresh session reconstructing from compressed summaries would lose. Forward-only (no backfill
  from summaries). It is the substrate for the eventual project **retrospective** + the public
  **"how to AI-decomp a new project"** wiki (Drew, 2026-07-08). Doc created + seeded with this session's
  two fresh pivots (the handoff-misread; the split-TU mechanical ceiling).
