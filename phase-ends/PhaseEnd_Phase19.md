# PhaseEnd — Phase 19: Scale the toolkit (wave-harvest at scale + cheap front-loaded levers)
**Date:** 2026-06-20 · **Project Version:** 1.18.0 · **Phase Status:** Complete (milestone confirmed by Drew, gate 2 — Option A: close at a clean checkpoint) · **Generation:** Gen2 (11th phase)

> Gen2 phase 11 of the arc (8→9→10→11→12→13→15→16→17→18→**19**; 14 deferred to Gen3+). Ran across **2 sessions**;
> the granular per-task/per-batch trail (the T1 -O0 split diagnostics, the T2 reproduction logs, the two wave
> result sets, the gate-failure classifications, the propagation-skip breakdowns) is preserved on-demand at
> **`phase-ends/logs/Phase19.md`** (R19 — NOT auto-loaded; consult only when researching a mechanism). This file
> is the synthesis. Owner decisions (Drew): bounded flywheel (T1 + T2 + 2–3 wave batches); T1 re-scoped to "bank
> infra + 6, defer the rest" (R14); Ultracode for the wave batches; **close after 2 batches at a clean checkpoint**
> (Option A) with the propagation type-lift as the Phase-20 opener.

## Build Log

**Files created/changed and complete — do not recreate:**

*New reusable recovery tooling (the phase's durable output — feeds Phase 20 directly):*
- `tools/canon_resident_calls.py` — **(T2)** link-miss recovery: rewrite each `func_<ADDR>` in a draft to the
  **curated** resident symbol name (`0x8004CFEC`→`ratan2`) when that addr has one in the stacked symbol files, so
  the linker resolves it. Pure draft-text (body bytes unchanged); runs FIRST in the recovery pipeline.
- `tools/fix_arity_callers.py` — **(T3)** the no-prototype recovery for the dominant gate-failure class: rewrite a
  banked shared caller's `extern <ret> func_X(void);` → `extern <ret> func_X();` (byte-neutral; `--apply`/`--revert`;
  `--drafts` skips narrow-param defs). Automates the T2-proven hand fix; recovered 8/18 batch-2 failures.
- `tools/gen_harvest_targets.py` — **FIXED** `INLINE_DEF_RE` (was matching an indented `if (func_X(...)) {`
  call-expr as a "definition" → garbled callee hints agents pasted as externs → PARSE fails). Column-0 + type-only
  prefix → **0 garbled of 749**; batch-2 match_one close-rate 88%→92%.

*Config / source (the matches):*
- `src/ov_SC01_077/ov_SC01_077.c` — T2's 3 matches + T3's banked matches (inline defs; the propagated ones spliced
  to `DEFINE_func_*()` macros) + the 4 byte-neutral no-proto caller edits' downstream. ~16 banked matches remain
  inline-LOCAL (typedef/local-type bodies — the propagation cap, Phase-20 lever).
- `src/shared/engine_core.h` — the no-proto caller-extern edits (`(void)`→`()` for func_80147514/80168F40/8014AB7C/
  8014AC10 + the batch-2 arity set) + **+35 new `DEFINE_func_*` macros** (the propagated matches).
- `src/shared/engine_types.h` — **struct-lift** (`build_engine_types.py --strip`): 48 named types (forward decls +
  defs) lifted from `ov_SC01_077.c` so struct-using shared bodies can propagate; byte-neutral.
- `src/ov_*/*.c` (134 overlays) — the ×134 `DEFINE_func_*()` instantiations from `dedup_propagate`.
- `config/dedup.us.yaml` — **1450 → 1485** validated cross-binary groups (0 failed).
- *(T1, committed earlier this phase, prior session)* the per-file `-O0` split (`src/ov_SC01_077_a.c` /
  `…_o0.c` 3-object split + the Makefile `-O0` target-specific `CC1FLAGS`) + 6 matched `-O0` functions.

*Docs / knowledge base (R16 flywheel, R21):*
- `docs/matching-cookbook.md` — **§17a-3 corrected** (the Phase-18 "implicit-int / propagate-first" framing was
  WRONG, R14 — the real classes are resident-callee link-miss + shared-caller arity) + **§18** (T1 -O0 split,
  prior session) + **§19** (T3 wave-at-scale: the canon-first 2-stage gate, `fix_arity_callers`, the garbled-sig
  fix, and **the propagation CAP**).
- `docs/SETUP.md` — tool inventory rows for `canon_resident_calls.py` + `fix_arity_callers.py`.
- `README.md` — Phase-19 status line (136 binaries byte-identical, fleet 58.0%; the narrative body flagged as
  Phase-11/12-era pending a public-flip refresh).
- `docs/{progress,difficulty,duplicates}.*.md` — regenerated.
- `phase-ends/CURRENT_PHASE.md` → **`phase-ends/logs/Phase19.md`** (R19 archive). `phase-ends/PhaseEnd_Phase19.md` — this file.

**Local artifacts (gitignored / regenerable):** `.run/harvest_wave_t3b{1,2}.js` + `.run/gen_wave.py` (wave
generator; recipe = cookbook §17/§19), `.run/t3_gate2.sh` (the canon-first 2-stage gate), `.run/t3_{repro,diag,
dump,postwave}.{py,sh}` (diagnostics), `.run/drafts-t3b*` (wave drafts + recovery stages), `.run/ghidra_c/*` (300
cached Ghidra-C), `.run/t3_b{1,2}_targets.json`, `build/`, `expected/`, `asm/`, `assets/`. The 134 overlay Ghidra
programs are script-reproducible (DB-commit deferred as regenerable).

**Tools/packages installed:** None — the whole phase used the existing Phase-4/6/10/11/12/13 toolchain + venv.

**Verification results (literal) — the milestone proof:**
- **`make check-all` → 136 passed, 0 failed of 136** (main `143dbb89…`, resident `8e17e02f…`, all 134 overlays;
  ov_SC01_077 `d19c9580…`), reproduced after every step (R22).
- **`make report`:** FLEET byte-identical **199,541 / 344,010 = 58.00%** (phase start 56.64% / 194,839 →
  **+1.36%**); REAL 197,894; LINKED 959; **dedup-check 1485 validated, 0 failed**; **0 NON_MATCHING** in any
  default build (G4).
- **Batch 1 (50 targets):** **44/50 match_one MATCH (88%)**; 6 DIFF = genuine gcc-quirk tail (correctly stubbed);
  whole-binary gate **30 banked**; **25 propagated ×134**; **+0.98%**.
- **Batch 2 (38 targets, clean hints):** **35/38 match_one MATCH (92%)**; 3 DIFF (genuine); gate + `fix_arity_callers`
  **25 banked** (ALL 18 stage failures were the shared-caller arity class); **10 propagated ×134**; **+0.31%**.
- **Struct-lift top-up:** +4 propagated; **+0.07%**.
- **The decomp.dev-comparable (instruction/byte-weighted) estimate ≈ 30%** (overlays 29.7%, resident 55.8%, main
  46.4% hand-matched) — the 57.62%→~30% gap is the deferred giants + per-overlay unique code; recorded for honesty
  (P9) and the public-flip expectation.
- `git status`: only `config/`/`tools/`/`src/`/`docs/`/`phase-ends/` tracked; **zero ROM-derived/generated bulk
  staged**. **No Ghidra DB change** this phase (matching used cached Ghidra-C + asm; the `db.*.gbf` churn is
  SessionStart-restart noise — R23 no-op, NOT staged).

**Milestone achieved (confirmed by Drew, gate 2 — Option A):** the bounded-flywheel milestone is met — the **-O0
lever is banked** (T1: infra + 6), **recovery tooling is proven** (T2: `canon_resident_calls` + the no-proto fix;
T3: `fix_arity_callers` + the canon-first 2-stage gate + the struct-lift), the **toolkit scaled across 2 wave
batches** (match_one 88%→92%), the fleet rose **56.64% → 58.00%** with **136/136 byte-identical** and **0
NON_MATCHING**, and the phase closed at a clean checkpoint with a sharp Phase-20 backlog. The **+3–5% target was
not reached (+1.36%)** — gated by the cache-limited target pool (~88 eligible, all run) and **the phase's key
finding: propagation, not matching, now caps the fleet-% yield** (typedef/local-type bodies can't auto-propagate).

**Next:** **Phase 20 — close the propagation cap, then scale.** Open a fresh session (plan mode). First lever:
extend the type-lift to typedefs/local types so the ~16 banked-but-local matches propagate ×134 (~+0.6% for ~0
agent tokens) and every future batch realizes its full yield; then more wave batches (Ghidra-C regen for fresh
reach-134, R23/R29) and the deferred -O0 ×134 rollout. See the Phase-20 Backlog.

## Deviations
| Item | Plan | Actual | Reason |
|---|---|---|---|
| T1 -O0 rollout | full ×134, "an afternoon, free" | **bank infra + 6, defer the 10 %lo-quirk fns + the ×134 rollout** (R14) | the residual -O0 fns hit a `%lo`-folding codegen quirk (gcc-source research); ×134 needs per-overlay -O0 splits (engine_core.h is -O2) — two findings corrected the Phase-18 "free ×134" premise (prior session) |
| T2 framing | "implicit-int / propagate-first helper (3 fns)" | **R14-corrected: NOT implicit-int** — 3 real classes (resident-callee link-miss + shared-caller arity); `canon_resident_calls` + the no-proto fix; func_8012A418 isn't even a stub in ov_SC01_077 | reproduced each through the gate — the Phase-18 backlog's premise was wrong (verify the framing against the bytes) |
| Recovery pipeline | `cast_call_sites.py` (call-site fn-ptr casts) | **not built** — the bytes never demanded it; instead the **canon-first 2-stage gate** + `fix_arity_callers` | the §17a "call-site cast = #1 miss" did not recur; the real recurring failures were sig_unify-regressions + the arity class |
| sig_unify in the pipeline | run unconditionally before the gate | **gate canon-only FIRST, sig_unify FALLBACK** | sig_unify REGRESSES already-canonical agent drafts (re-canonicalization perturbs codegen / mangles a line); canon-first recovered ~+5/batch |
| Fleet target | +3–5% (~56.6%→~60%) | **+1.36% (→58.00%)**, closed at the checkpoint | cache-limited pool (~88 eligible) + the propagation cap (struct/typedef bodies stay local); Drew chose Option A (close) over batch-3/typedef-lift-now |
| T3 batch count | 2–3 batches of 50 | **2 batches (50 + 38)** | the cached reach-134 ≤90-ins pool was exhausted at ~88; a 3rd batch needs a Ghidra-C regen (R23/R29) |
| T4 gcc-research | conditional, on a residual-class plateau | **NOT triggered** | the waves never plateaued on a single gcc-quirk class (88–92% match_one); residuals were the loose-typing wall (Phase-16, genuine) + the propagation gap (tooling) — neither a gcc-research target |
| Effort | Max planning, Ultracode waves | Max/xHigh setup + recovery, **Ultracode waves** (Drew toggled, R27), **xHigh close** (Drew's saved default — PhaseEnd normally Max) | breadth waves under Ultracode; deterministic recovery/synthesis at xHigh |

## Commit Message
```
(Phase 19 landed as commits commit:0158..commit:0164 + this PhaseEnd.)

feat(phase-19): scale the toolkit — 2 waves (88%/92%), fleet 56.64%->58.00%, propagation is the cap (v1.18.0)

- T1 (prior session, commit:0158/commit:0159): per-file -O0 split infra + 6 -O0 matches; deferred the
  10 %lo-folding-quirk fns + the ×134 rollout (R14 corrected "free ×134")
- T2 (commit:0161): recovery tooling. R14: the 3 Phase-18 "implicit-int" near-misses are NOT
  implicit-int -> resident-callee link-miss (NEW canon_resident_calls.py) + shared-caller arity
  (no-proto caller-extern fix). 3 matches; cookbook §17a-3 corrected
- T3 (commit:0162/commit:0163/commit:0164): 2 Ultracode waves over reach-134 tractable residuals. batch-1
  44/50 match_one (30 banked, 25 propagated ×134); batch-2 35/38 (25 banked, 10 propagated).
  NEW fix_arity_callers.py (no-proto, ALL 18 batch-2 failures were the arity class); canon-first
  2-stage gate (sig_unify REGRESSES canonical drafts); gen_harvest_targets garbled-sig fix
  (0/749, 88%->92%); build_engine_types --strip lift (+4 propagated)
- FINDING: propagation (not matching) caps the fleet-% yield — typedef/local-type bodies can't
  auto-propagate (-> Phase-20 type-lift lever). decomp.dev-comparable byte-weighted est ~30%
- check-all 136/136 BYTE-IDENTICAL (R22); dedup 1450->1485/0 failed; 0 NON_MATCHING (G4);
  fleet 56.64% -> 58.00% (+1.36%). worklog -> phase-ends/logs/Phase19.md (R19)
- bumps 1.17.0 -> 1.18.0
```

## Rules Added This Phase
| Rule | Reason |
|---|---|
| **None (governance).** Phase 19's lessons are *techniques + findings*, recorded where the Phase-8/11/13/15/16/17/18 precedent puts them (cookbook, not rules): the **two recovery tools** (`canon_resident_calls`, `fix_arity_callers`) + the **canon-first 2-stage gate** + the **garbled-sig fix** + the **propagation CAP** → cookbook §17a/§19 + SETUP inventory. The **R14 self-correction** (the Phase-18 "implicit-int/propagate-first" framing was wrong — reproduce the failure against the bytes before trusting a prior framing) is a direct application of the existing **R14/G3/P9**. The **bounded-flywheel + probe-before-investing** discipline is already cookbook (Phase 15) + effort-map. No new norm of conduct emerged. | A scale-up + recovery-tooling phase produces knowledge, not governance; the existing rules (R14 verify-vs-bytes, R16 flywheel, R22 clean-rebuild, R26/R27 effort, G3/P9 byte-gate) covered the ground and the phase reinforced them. |

## PhaseEnd Changelog
**v1.17.0 → v1.18.0 — Phase 19 complete (Gen2 phase 11).** The proven §17/§18 toolkit was scaled over the
tractable reach-134 tail as a **bounded flywheel**: two Ultracode parallel-draft/byte-gate waves matched at
**88% then 92% `match_one`**, and after a hardened deterministic recovery pipeline the fleet rose **56.64% →
58.00%** (136/136 byte-identical throughout, 0 NON_MATCHING). The phase's reusable output is **three recovery
mechanisms** — `tools/canon_resident_calls.py` (rewrite `func_<ADDR>` → the curated resident name for the
link-miss class), `tools/fix_arity_callers.py` (the no-prototype caller-extern fix for the shared-caller arity
class, which turned out to be **~100% of the residual gate failures** once the other noise was removed), and the
**canon-first 2-stage gate** (the finding that `sig_unify` *regresses* already-canonical agent drafts) — plus a
root-cause fix to `gen_harvest_targets`' garbled callee hints (88%→92%) and the `engine_types` struct-lift. Two
R14 self-corrections drove the work: the Phase-18 "implicit-int / propagate-first" framing for the 3 carried
near-misses was **wrong** (the real classes are link-miss + arity, found by reproducing each through the gate),
and the giants/per-overlay-unique deferral means the **decomp.dev-comparable byte-weighted progress is ~30%**, not
57.62% (recorded for honesty). **The decisive finding: propagation — not matching — now caps the fleet-% yield.**
match_one is 88–92% and the gate banks 60–71%, but a matched function whose body uses a **typedef'd / anonymous /
sibling local type** can't be lifted into the shared header, so ~16 banked matches stayed `ov_SC01_077`-local
(no ×134). The **+3–5% target was therefore not reached (+1.36%)** — also gated by the cache-limited pool — and
Drew chose to **close at a clean checkpoint** (Option A) with the propagation type-lift as the Phase-20 opener.
No new governance rules (techniques → cookbook §17a/§19). All 136 binaries byte-identical; 0 NON_MATCHING linked.

## Phase-20 Backlog — "Close the propagation cap, then scale" (the forward bridge; nothing here is lost on close)

> Phase 20 opens in **plan mode**. The harvest's bottleneck has moved from *matching* (now 88–92%) to *sharing*.
> Prioritised by ROI:

1. **[HIGHEST ROI — DO FIRST] Extend the type-lift to typedefs/local types (close the propagation cap).** The
   named-struct-only `build_engine_types.py` leaves ~16 banked matches `ov_SC01_077`-LOCAL because their bodies
   use `typedef`'d / anonymous / sibling types `dedup_propagate`'s `compiles_standalone` can't resolve. Extend the
   lifter to also lift `typedef` definitions (and detect collisions — the named-struct case had 0) into
   `engine_types.h`, then re-run `dedup_propagate --auto-from`. Recovers ~16 already-matched fns **×134 for ~0
   agent tokens** (~+0.6%) **and raises every future batch's realized yield**. This is the lever the whole phase
   pointed at.
2. **[COMPOUNDING — automate the recovery further] `fix_arity_callers` generalization.** It currently fixes
   `(void)`→`()`. The harder residual (batch-2's 10) is a **caller sig ≠ def sig** mismatch (e.g. caller declares
   `void f(void*,s32)`, def needs `s32 f(s32,u32)`; or banked siblings use `s32 f(void)` + call-site casts vs def
   `void f(void*)`). A generalized "reconcile the caller decl to `<def-ret> func_X()` (no-proto, def's return),
   byte-gated" pass would recover some — but some are the genuine **Phase-16 loose-typing wall** (no single C type).
   Worth a bounded probe (size the recoverable fraction first).
3. **[THE CORE — more waves] Scale the toolkit over fresh reach-134 targets.** Regen Ghidra-C
   (`DecompileFunctions.java`, headless — MCP stopped, R23/R29 `/mcp` reconnect) for the uncached tractable
   reach-134 stubs (the cache is 300; ~88 ≤90-ins eligible were exhausted in Phase 19), then run the §19 wave
   (canon-first 2-stage gate + `fix_arity_callers` folded in). With the type-lift (item 1) done, each match now
   actually propagates → batches realize ~full yield. Batch size 50; bank a prompt/tooling improvement each batch.
4. **[THE BYTE-WEIGHTED LEVER] The giants (28 reach-134 fns >150 ins).** Highest *bytes* (so the only lever that
   moves the **byte-weighted** ~30% number materially), same headline %, hardest. The §17 toolkit applies, just
   more labor per fn. Do after the cheap levers; ideal for a focused deep session.
5. **[DEFERRED FROM PHASE 19] The -O0 ×134 rollout + the 10 %lo-quirk -O0 fns.** Per-overlay -O0 splits (uniform
   offsets, scriptable) to bank the 6 matched -O0 fns ×134 (~+0.6%); and gcc-source research (R17) on the
   `%lo`-folding quirk blocking the other 10 -O0 fns (cookbook §18).
6. **[CARRIED, lower priority]** per-overlay unique remainder (×1 leverage); comprehension/emulator actor-field
   naming (Gen2 quality, byte-neutral); the public flip (Phase 14, Gen3+) incl. the README narrative refresh + the
   decomp.dev-comparable byte-weighted metric in `progress.py`.

## Plain-English Recap
This phase was about **scaling up** the function-matching machine we built last phase. We pointed an AI agent swarm
at batches of the game's shared engine functions, and they reconstructed them impressively well — **44 of 50, then
35 of 38** — each checked by an automatic bit-for-bit referee so nothing wrong can slip in. That pushed the game
from ~56.6% to **58%** rebuilt exactly, with all 136 pieces still byte-perfect. Along the way I built two small
"fixer" tools that automatically clean up the most common reasons a correct function fails to slot in (a
mismatched name, and a function-declaration quirk), and I fixed two bugs in our own tooling at the source. **The
big lesson:** we're now *great* at reconstructing functions, but a *separate* step — copying one matched function
into all 134 levels at once — chokes when the function uses certain local data-types, and that's what's actually
holding the headline number back now (not the matching). That's a well-understood, cheap fix queued as the very
first thing next phase. I also gave you an honest reality-check on the percentage: measured the way the
public decompilation trackers measure it (by code *size*, where our deferred "giant" functions count heavily),
we're around **30%** — roughly level with the Xenogears project and a bit behind Symphony of the Night — not
"ahead of both" as our internal 58% might suggest. We deliberately stopped at a clean checkpoint rather than
grind for a higher number, with everything we learned written down. Nothing we already had broke.

## 🛑 Stop Here
PhaseEnd written; `CURRENT_PHASE.md` archived → `phase-ends/logs/Phase19.md` (R19). The Phase-19 matching work is
committed (`commit:0158`..`commit:0164`); **Drew commits AND pushes** this PhaseEnd + the archived log (R6/R8). No Ghidra
DB change this phase (R23 no-op — the `db.*.gbf` churn is restart-noise, do NOT stage it). Gen2 continues — do
**NOT** start Phase 20 here. Start a **fresh session** (plan mode) for **Phase 20 — close the propagation cap,
then scale** (the backlog above; the typedef/local-type lift first). Keep this file forever.
