# PhaseEnd — Phase 24: Permuter overhaul · integration-recovery · the giant endgame (all matched giants ×134) + the structural-family reframe
**Date:** 2026-07-08 · **Project Version:** 1.23.0 · **Phase Status:** Complete (open-ended matching phase, closed at a clean checkpoint — Drew, gate 2) · **Generation:** Gen2 (16th phase of the arc; 14 deferred to Gen3+)

> Gen2 phase 16 (8→…→23→**24**). Ran across **many sessions (2026-07-02 → 07-08)**. The granular per-task/per-session crash-recovery trail (T1–T9, every permuter fix, the §G giant chain, the whale crack, the ×134 propagations, the effort experiments) is preserved on-demand at **`phase-ends/logs/Phase24.md`** (R19 — NOT auto-loaded; consult only when researching a mechanism). This file is the synthesis. Owner decisions (Drew): permuter-first → crack the giants (incl. the whale) → **finish the ×1 giants ×134** → then answer the strategic "what to attack next / which idioms to learn" question → **close here + author the Phase-25 vision (the structural-family / idiom-curriculum endgame).**

## Build Log

**Files created/changed and complete — do not recreate** (the durable Phase-24 output; the archived log has the exhaustive per-commit list):

*The permuter overhaul (T2–T5, §G — all in `tools/`, no decomp-permuter submodule edit):*
- `tools/masked_diff.py` + `tools/masked_scorer.py` + `tools/permuter/run_masked.py` — the **floor-free relocation-masked scorer** (shared `objdump -drz` oracle; masks jal/HI16/LO16). Killed the stock permuter's ~1750–2100 relocation "floor" that made it wander; it now scores TRUE closeness (== `match_one`). Also fixed `match_one.py`'s GTE under-count.
- `tools/permuter_weights.py` (T5) — **§31-class-directed mutation:** `classify(klass, where) → regalloc|schedule|cse` → a `[weight_overrides]` settings.toml table decomp-permuter merges over gcc defaults (biases pass-selection toward each class's §31 levers). Auto-threaded by `p16_permute.setup`/`grinder`.
- `tools/permuter_ils.py` (§G) — **warm-restart iterated-local-search** (the permuter lacked one; drove seeds where cold search plateaus, e.g. 72→38).
- `tools/p16_permute.py` — the pin/typedef/-O0 setup fixes (b64-pragma carrier for register pins + GTE `__asm__`; `-O0` variant; `.include macro.inc` for GTE) + **the §G comment-strip fix** (`make_base_c` didn't strip draft header comments → `cpp` "unterminated comment" → the permuter silently no-op'd `(0s)` on EVERY commented draft; the fix immediately cracked `func_801571C4` 11→0 in 40s).

*Integration-recovery + ×134-propagation tooling (T5c, T6, T7b, T7 close):*
- `tools/lint_symbol_refs.py` (T5c) — comment/string-aware guard that flags any stale `func_/D_<ADDR>` ref after a `symbols.us.txt` rename. **Run after ANY symbols rename.**
- `tools/recover_integration.py` (T6) — batch integration-recovery (no-proto the conflicting caller decl → `gate_stage` → 2-pass snapshot/restore).
- `tools/reconcile_decls.py` (T7b) — the DATA-symbol analog of `cast_call_sites` (fleet-majority canonical-type oracle + byte-neutral access-cast transform); wired into `gate_stage`.
- `tools/recover_giant.py` (Phase 22, exercised) — canonical-extern block-scope recovery for close=0 giants.
- `tools/dedup_propagate.py` — **`find_site` fixes** (indented defs + trailing-comment externs) + **`--recover`** (Part-B straggler caller-extern reconcile / Part-A per-overlay exclude) + **`overlay_files` now scans the whale-split `_o0b`/`_after` files** (this session — post-whale-region fns were invisible to source-def-find AND stub-replacement). `tools/fix_arity_callers.py` extended (`--binary`, `--any-proto`).
- `tools/rollout_whale_o0.py` + `tools/split_whale.py` — the whale's per-overlay -O0 split + ×134 rollout.

*Config / source (the matches — fleet 64.86% → 66.02%):*
- `config/dedup.us.yaml` — **1783 → 1813 validated cross-binary groups** (0 failed).
- `src/shared/engine_core.h` (+giant DEFINE_ macros incl. `func_801770E0`/`func_801372B0`), `src/shared/engine_types.h` (+lifted types incl. `Svec_801372B0`/`Gline_801372B0`), `src/shared/func_80144B9C.h` (the whale's shared -O0 header), the **134 overlay `.c` files** (the ×134 propagations + the whale's `_o0b`/`_after` splits), `config/splat.ov_SC01_077.yaml` (whale o0b carve), `config/symbols.resident.txt` (`memcpy=0x8005C324`), `Makefile` (`WHALE_O0B_OBJS` -O0 wildcard).

*Docs / knowledge base (the mature gcc-2.7.2 toolkit — the compounding asset):*
- `docs/matching-cookbook.md` **§18–§39** — the -O0 split, the wave recovery + propagation cap, the cast tool + DEF-side wall, the coalescing/gate-two-stage findings, the giant recipe, **§32/§34/§35/§36/§37** (the region-a giant idioms + the §G meta-laws), **§38** (the whale -O0 struct-assign memcpy idiom + the -O0 ×134 rollout), **§39** (the native-DEFINE-path-for-O2-giants + the `overlay_files` post-whale gap + the unique-rename typedef-lift + the R14 handoff-staleness).
- `docs/gcc-2.7.2-map/{sched,regalloc,loop,cse_expr}.md` + `t7g-giant-harvest.md` — the codegen map, extended with S11/S12/S13 (sched), RC-6→RC-13 (regalloc), the giant-harvest sibling-isomorphism law. `tools/reference/gcc-2.7.2/` completed (vanilla 2.7.2, R17-corrected from 2.8.1).
- `docs/{worklist,backlog,SETUP,canonical-decl-reconcile-design}.md` updated. `docs/progress.fleet.md` regenerated (66.02%).
- `.run/analyze_frontier.py` + `.run/probe_hnorm.py` (this session — the fleet frontier survey + the **structural-family (h_norm) probe** that reframed the endgame; gitignored scratch, reproducible).
- `phase-ends/CURRENT_PHASE.md` → **`phase-ends/logs/Phase24.md`** (R19). `phase-ends/PhaseEnd_Phase24.md` — this file.

**Tools/packages installed:** None — the whole phase used the existing Phase-4/6/10/11/12/13 toolchain + venv (decomp-permuter, m2c, rabbitizer, the cc1 candidates). Fable5/Opus agents via the Agent tool.

**Verification results (literal):**
- **`make check-all` → 136 passed, 0 failed of 136** (main `143dbb89…`, resident `8e17e02f…`, ov_SC01_077 `d19c9580…`, all 134 overlays) — reproduced from a **genuinely-clean tree** (`make clean` + full extract-all + check-all) after every bank (R22). This session's two giant banks were each clean-fleet-verified.
- **Fleet: 64.86% → 66.02% byte-identical-from-source** (function-count; ~31–32% byte-weighted, decomp.dev-comparable — the byte-weighted gain is larger because giants dominate byte-weight). **0 NON_MATCHING** in any default build (G4); `dedup-check` **1813 validated / 0 failed**.
- **The giant endgame, byte-proven complete:** every matched region-a giant is ×134 — the whale `func_80144B9C` (770), the §G batch (6/8 cracked, 4 propagated ×134 + this close's 2), and this session's `func_801770E0` (152) + `func_801372B0` (207). The **2 remaining reach-134 giants are permanent walls** (`func_801412A8` close=29, `func_80178004` close=7 — gcc-intrinsic, INCLUDE_ASM per G4). **No matched giant remains ×1.**
- **The strategic finding (R14, this session):** regrouping the unmatched frontier by **structure (h_norm)** instead of bytes (h_exact) reveals **2,764 structural families / 11.1 MB** hidden by byte-grouping, and **3,989 of 8,670 large "solo monsters" (46%) are structural family members**, not unique — the reframe that drives Phase 25.
- `git status`: only `config/`/`tools/`/`src/`/`docs/`/`phase-ends/` tracked; zero ROM-derived/generated bulk staged; the `db.*.gbf` churn is R23 restart-noise (do NOT stage). A stray `gccdump.lreg` (gcc RTL scratch) sits untracked at repo root — belongs in `.run/`, harmless, not staged.

**Milestone achieved (Drew's gate 2):** Phase 24 **overhauled the permuter** (floor-free masked scorer + §31-class-directed mutation + warm-restart ILS), built the **integration-recovery / ×134-propagation tooling** (`recover_integration`, `reconcile_decls`, the `dedup_propagate` fixes), **cracked and banked ×134 every matchable region-a giant** — including the 770-ins whale and the 400-ins flagship `func_80132784` that was "irreducible for 22 phases" — driving the fleet **64.86% → 66.02%** at 136/136 byte-identical / 0 NON_MATCHING, and closed by **reframing the endgame** with the structural-family (h_norm) grouping that turns ~half the byte-unique "solo monsters" into idiom-crackable families.

**Next:** **Phase 25 — The structural-family endgame (idiom curriculum).** A fresh session, **plan mode, Max** (Tier-1 Phase-Start). The full vision + the effort/model discipline is the **Phase-25 Backlog** below.

## Deviations
| Item | Plan | Actual | Reason |
|---|---|---|---|
| Permuter "evolve" | §31-class-aware directed mutation as the yield lever | built + validated, but the flagship count-exact seeds were the WORST-case intrinsic walls → the real giant wins came from **Fable5 + the §31 map lookup**, not the permuter | the permuter improves regalloc/sched seeds but doesn't gate the hardest; §31 map lookup + Fable5 discovery is the wall-breaker (Phase-23 lesson held) |
| Giant matching | permuter-first on the seeds | **cheap-Opus applying §31/§32 + a sequential Fable5 idiom-banking chain** for the §G giants; permuter only for the clean regalloc/sched seeds | the ranking law (§35): difficulty = global-array hoisting, not size/$s-count; param/buffer giants one-shot Opus, only global-hoisters need Fable5 |
| The whale | "needs gcc-2.7.2 calls.c + Fable5" | **cheap Opus one-liner** — a struct-assign (not explicit memcpy) for the -O0 block-move; no calls.c, no Fable5 (§38) | reading the -O0 codegen tell (arg-precompute pseudos) named the C shape directly |
| The "3 ×1 giants" handoff | finish func_801770E0 + func_801372B0 + func_8014E048 | **func_8014E048 was ALREADY ×134** (T6 §A) — the handoff was stale (R14); only 2 remained | verified each against the bytes before acting; the stale line cost nothing because the first move was `grep`, not a rebuild |
| ×1→×134 mechanism | the whale's hand-rolled `src/shared/<fn>.h` shared-header lever | the **native `DEFINE_func_X()` macro path** (func_8014E048 proves it handles pin/asm -O2 giants); the shared header is an **-O0-only** necessity | the real blocker was the `overlay_files` post-whale-split gap, not pins (§39) |
| Phase close | grind T8 (the §31 wave) next | **closed at the giant-endgame checkpoint + reframed the endgame** (the structural-family finding) | the giants were the headline lever and are exhausted; the frontier survey + h_norm probe changed the strategy → a fresh plan-mode phase |
| Effort | Max planning, Ultracode/Fable5 execution | Max synthesis + orchestration; **Fable5** (discovery/wall-breaker) for the un-cracked giant classes; cheap Opus for applying banked idioms; **Ultracode** for the breadth waves | R26/R27 (breadth → Ultracode; deep discovery → Fable5; synthesis → Max) |

## Commit Message
```
(Phase 24 landed across many sessions of checkpoint commits 9c8bb5183..f62cd42c3; this close = the
archived log + this PhaseEnd. Key hashes: whale 3b0cc190b/8cfbbf2d4, §G c10677477, this session 8e6658ee8/f62cd42c3.)

feat(phase-24): permuter overhaul + integration-recovery + the giant endgame (all giants ×134); fleet 64.86->66.02% (v1.23.0)

- PERMUTER OVERHAUL (tools/, no submodule edit): masked_diff.py floor-free relocation-masked
  scorer (killed the ~1750-2100 stock floor -> true closeness); permuter_weights.py §31-class-
  directed mutation; permuter_ils.py warm-restart ILS; p16_permute pin/typedef/-O0/comment fixes.
- GIANT ENDGAME COMPLETE: every matched region-a giant banked ×134 — the whale func_80144B9C
  (770, -O0 struct-assign memcpy §38), the flagship func_80132784 (400, "irreducible 22 phases"),
  the §G batch (6/8 cracked), + this close's func_801770E0 (152) + func_801372B0 (207). 2 permanent
  walls remain (func_801412A8, func_80178004 — G4). NO matched giant remains ×1.
- INTEGRATION/PROPAGATION TOOLING: recover_integration.py, reconcile_decls.py, dedup_propagate
  --recover + find_site fixes + overlay_files _o0b/_after (post-whale gap), lint_symbol_refs.py.
  Fixed the Phase-21 latent clean-rebuild breakage (62 stale INCLUDE_ASM refs) -> true clean 136/136.
- TOOLKIT MATURED: cookbook §18-§39 + gcc-2.7.2-map (S11/S12/S13, RC-6..RC-13, giant idioms).
- STRATEGIC REFRAME (R14): the frontier grouped by STRUCTURE (h_norm) reveals 2764 families /
  11.1 MB hidden by byte-grouping; 46% of large "solo monsters" are family members -> the idiom-
  curriculum endgame (Phase 25). Survey scripts .run/analyze_frontier.py + probe_hnorm.py.
- check-all 136/136 BYTE-IDENTICAL (R22), dedup 1783->1813/0, 0 NON_MATCHING (G4). No new rules
  (techniques -> cookbook; the reframe -> Phase-25 backlog). worklog -> logs/Phase24.md (R19).
```

## Rules Added This Phase
| Rule | Reason |
|---|---|
| **None (governance).** Per the Phase-8+ precedent, the phase's lessons are *techniques + findings*, captured where they belong: the matching/propagation toolkit → cookbook **§18–§39** + `docs/gcc-2.7.2-map/`; the **strategic reframe** (structure-grouping / the idiom curriculum) → the **Phase-25 Backlog** below. The existing rules carried the phase — **G3/P9** (byte-gate is the sole arbiter, and it never accepted a wrong match across the whole giant campaign), **R14** (verify vs bytes — caught the stale handoff, the "×134 wall" misdiagnosis, the "S11 intrinsic" over-claim), **R16/R30** (flywheel + capture-during-session — §38/§39 + the map extensions written live), **R22** (clean-fleet verify EVERY batch — caught the Phase-21 latent breakage), **R23** (no db.gbf), **R26/R27** (Ultracode for breadth waves, Fable5 for discovery, Max for synthesis — with the toggle prompts). | A permuter/tooling/giant-harvest/reframe phase yields tools, idioms, and a strategic direction — not a new norm of conduct. |

## PhaseEnd Changelog
**v1.22.0 → v1.23.0 — Phase 24 complete (Gen2 phase 16; the giant-endgame phase + the strategic reframe).** The phase **overhauled the decomp-permuter** entirely in the `tools/` layer (a floor-free relocation-masked scorer that finally scores true closeness, §31-class-directed mutation weights, and a warm-restart ILS the stock permuter lacked), built the **integration-recovery and ×134-propagation machinery** (`recover_integration`, `reconcile_decls`, `dedup_propagate --recover` + the `find_site`/`overlay_files` fixes, `lint_symbol_refs`), and — the headline — **cracked and banked ×134 every matchable region-a giant**, including the 770-instruction whale (`func_80144B9C`, an -O0 struct-assign memcpy idiom, cheap Opus) and the 400-instruction flagship `func_80132784` that had been "irreducible" for 22 phases. Along the way it fixed a **latent Phase-21 clean-rebuild breakage** (62 stale `INCLUDE_ASM` refs a rename never propagated, masked by incremental builds) and restored a genuinely-clean 136/136. The fleet rose **64.86% → 66.02%** at 136/136 byte-identical, 0 NON_MATCHING, dedup 1813/0. The gcc-2.7.2 **codegen map matured** (cookbook §18–§39 + the sched/regalloc/loop/cse map files). The phase **closed at a clean checkpoint** with a strategic reframe (R14): regrouping the unmatched frontier by **structure (h_norm)** instead of bytes exposes **2,764 structural families / 11.1 MB** and shows **46% of the large "solo monsters" are structural family members** — turning the endgame from "match 82k unique functions" into "learn the idiom for each family, then apply the template." That reframe is Phase 25. No new governance rules (techniques → cookbook; the reframe → the Phase-25 vision below).

## Plain-English Recap
This phase finished the "giant" functions — the biggest, most-reused pieces of the game's engine — and stamped every one that can be matched into all 134 levels, bit-for-bit. That includes a 770-instruction monster we'd been dreading and a 400-instruction one we'd literally called "impossible" for most of the project; both fell to a clean trick plus the compiler "cheat-sheet" we built last phase. The game is now ~66% rebuilt exactly, every piece verified. But the most important result was a *change in how we see the remaining work*. Until now we grouped leftover functions by "which levels have the exact same bytes." When we regrouped them by *shape* instead — "which functions are built the same way, just with different numbers filled in" — we discovered that roughly half of the scary-looking one-of-a-kind giant functions are actually the *same function repeated per level* with small changes. That means we don't have to solve 80,000 unique puzzles; we solve one puzzle per *family* and reuse the answer. So the next phase isn't "grind more functions" — it's "figure out the smartest order to learn the handful of remaining tricks, so each one we learn makes the rest fall faster," and we'll bring in the strongest AI model to help lay out that plan.

## Phase-25 Backlog — "The structural-family endgame: an idiom curriculum" (the forward bridge; nothing here is lost on close — Drew emphasized capturing the full vision for the fresh plan-mode session)

> **Phase 25 opens in plan mode, Max (Tier-1 Phase-Start).** The endgame is no longer "match functions by leverage." It is: **learn the remaining idioms in the order that makes the most of the tail fall fastest** (the flywheel, R16). The reframe that makes this possible: group the frontier by **structure (h_norm)**, not bytes (h_exact). The plan-mode session should *design the curriculum* — which family/class to attack first, second, third — and Drew wants a **Fable5Max plan-mode evaluation** as an input to that design.

### The reframe (the ground truth, byte-verified this phase)
- **Byte-grouping (h_exact)** = "reach-134, match once → dedup ×134." That tier is nearly exhausted: 130 reach-134 byte-classes left (66 large/med — the direct T8 continuation — 55 small, and the 2 permanent giant walls). Worth ~4.1 MB.
- **Structure-grouping (h_norm)** = "same code shape, per-level byte-variants → one idiom + one template cracks the family." **2,764 families / 11.1 MB, hidden by byte-grouping.** Example: `func_80133CD4` — a 399-ins function at the SAME address in all 134 overlays, structurally identical, 127 byte-variants. **46% of large solo monsters are family members.**
- The tools that produced this are committed-reproducible: `.run/analyze_frontier.py` (reach×size survey) + `.run/probe_hnorm.py` (structural families). Re-run them first (sigs are stable — they sign the original bytes).

### The curriculum (learning-optimal attack order — validate before scaling, Phase-15/16 lesson)
1. **Finish the h_exact reach-134 tier** (66 large/med + 55 small) — same bytes ×134, KNOWN §31 idioms, cheapest per fleet-%. Two are already leaf-MATCHed (`func_8014F4C0`, `func_80155800` — need only whole-binary integration). This is the old "T8 §31 wave," now the warm-up. *(Breadth → Ultracode.)*
2. **The top structural families** (`func_80133CD4`-class, ~15–20 at 150–399 ins). For each family: draft the exemplar → read its residual class → **if a known §31 idiom, cheap-Opus harvest the whole family; if a NEW class, Fable5 cracks the exemplar → bank the idiom into §31 → Opus applies the template to all ~127 variants.** This is where idiom-learning compounds hardest.
3. **The tiny high-count families** (e.g. `func_80150480`: ~2,000 instances × 22 ins) — one idiom → thousands of small per-level functions.
4. **The truly-unique-shape monsters** (~4,681, incl. the 4,763-ins behemoth) — genuine hand-decomp, worst ROI, LAST.

### THE swing question to resolve FIRST (the data-prep probe)
Each family is byte-*variant* (127 distinct h_exact), so it is **not** an automatic dedup — cracking the idiom makes each variant *fast*, not *free*. **BUT:** if a family's variants differ ONLY in *relocated addresses* (jal/HI16/LO16 targets that resolve to per-overlay symbols), then ONE C source matches all 134 via a **relocation-masked dedup** — a massive free win. If they differ in genuine *immediates*, it's a template (crack once, match each). **Resolve this on `func_80133CD4` before committing the curriculum** — it swings the whole endgame math. (Use `match_one`/`masked_diff.py`: compare two members' relocation-masked bytes.)

### The recommended shape (data-prep → Fable5 plan)
- **Step A (cheap, Opus/Max or an Ultracode wave):** draft-classify the top ~15–20 structural families' exemplars (get their REAL residual classes, not predictions) + run the relocation-vs-immediate probe on `func_80133CD4`. This is the ground-truth input.
- **Step B (Fable5Max, plan mode):** hand Fable5 the structural-family map + the measured residuals + the §31 codegen map + the cookbook. Its task (its true edge — compiler-internals reasoning): per family, diagnose the residual class, split NEW-idiom-needed vs known-§31, verify dedup-vs-template, and **author the finish curriculum** (family attack order, which idioms to chase first/second, projected fleet-% + byte-weight per tier). A plan built on Fable5 *predicting* classes for never-drafted functions is speculation; grounded on Step A's data it is real.

### ⚠️ EFFORT & MODEL DISCIPLINE — STOP AND PROMPT (R26/R27; Claude cannot toggle these itself)
> This is a mixed-mode phase. **At every transition, STOP, prompt Drew, and WAIT for the actual `/effort` command or model confirmation (a system-reminder confirms) before launching — never on a verbal "yes."**
- **Plan mode → Max** for the Phase-25 planning itself (Tier-1). Confirm Max is set before planning.
- **Breadth waves (the reach-134 tier, family harvests) → prompt for `/effort ultracode`** (R26) — the *same analysis across many independent items*. Wait for the toggle before launching the Workflow.
- **Deep discovery (cracking a NEW residual class's exemplar) → prompt Drew to switch to Fable5Max** (`Agent(model: fable)`, the reserved wall-breaker/discovery tier, ~375k tok/giant). Cheap-tier-first: permuter + Opus applying §31 → **Fable5 only when they stall**. A Fable5-cracked lever goes INTO §31 (R16) so Opus applies it thereafter.
- **The Fable5 plan-mode evaluation (Step B) is a heavy, deliberate call** — prompt Drew and confirm before spawning it; feed it Step A's data.
- **Back to Max** for synthesis, PhaseEnd, and any non-obvious debugging (Ultracode/Fable5 cap depth at xHigh).
- **R22 throughout:** clean-fleet verify (`make clean` + extract-all-136 + `check-all` → 136/136) EVERY batch before committing — the incremental gate masks stale asm (bit us twice this phase).

### Carried lower-priority / open items
- The **byte-weighted % reality** (~31–32% vs 66% function-count): only the reach-1 monsters + the big families move it materially. The curriculum (families first) is the efficient path to both metrics.
- The 3 now-propagatable small stragglers (`0x80174650`/`0x8012A018`/`0x80165CA0`) + 17 local-type-blocked ×1s — cheap fodder my `overlay_files` fix unblocked; fold into Tier 1's wave.
- The 2 permanent giant walls (`func_801412A8`, `func_80178004`) stay INCLUDE_ASM (G4) unless a NEW idiom dissolves them.
- Housekeeping: remove the stray `gccdump.lreg` from the repo root (R12 — scratch belongs in `.run/`).
- **Gen2 public-flip release candidates** (Drew, carried from Phase 24): upstream an ILS/warm-restart mode to decomp-permuter; release the gcc-2.7.2 codegen map (§31/§36) + the "shipped cc1 RTL dumps are NOT stripped" method; the `xsig` cross-project dedup tool. Sequence at the public flip (Gen3+).

## 🛑 Stop Here
PhaseEnd written; `CURRENT_PHASE.md` archived → `phase-ends/logs/Phase24.md` (R19, via `git mv` — left uncommitted). The Phase-24 matching work is committed across the session (…`8e6658ee8`, `f62cd42c3`); **Drew commits AND pushes** this PhaseEnd + the archived log (R6/R8 — the milestone-close is the human-controlled gate-2 sign-off). No Ghidra DB change this phase (R23 no-op — the `db.*.gbf` churn is restart-noise; do NOT stage; the untracked `gccdump.lreg` is scratch, do NOT stage). Gen2 continues — do **NOT** start Phase 25 here. Start a **fresh session** (effort **Max**, **plan mode**) for **Phase 25 — The structural-family endgame (idiom curriculum)**, opening from the Backlog above (re-run the surveys → the `func_80133CD4` relocation-vs-immediate probe → Step A data-prep → the Fable5Max plan-mode evaluation → the curriculum). Keep this file forever.
