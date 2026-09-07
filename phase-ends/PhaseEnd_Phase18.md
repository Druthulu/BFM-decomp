# PhaseEnd — Phase 18: Compiler-quirk research → the matching TOOLKIT, taught to waves at scale
**Date:** 2026-06-20 · **Project Version:** 1.17.0 · **Phase Status:** Complete (milestone confirmed by Drew, gate 2) · **Generation:** Gen2 (10th phase)

> Gen2 phase 10 of the arc (8→9→10→11→12→13→15→16→17→**18**; 14 deferred to Gen3+). Ran across **multiple
> sessions**; the granular per-task/per-session trail (T0–T7, the verdict reversal, the 5-avenue ceiling test,
> the Step-3b calibration, the Step-1 wave + recovery diagnostics) is preserved on-demand at
> **`phase-ends/logs/Phase18.md`** (R19 — NOT auto-loaded; consult only when researching a mechanism). This
> file is the synthesis. Owner decisions (Drew): pursue the research → on the "unsteerable" finding, **hand-match
> everything** (verdict reversal) → teach the toolkit to a calibration wave → **bounded ~40 Step-1 wave**
> (full tractable-247 sweep deferred to Phase 19) → close with a full Phase-19 backlog.

## Build Log

**Files created/changed and complete — do not recreate:**

*The research + the matching TOOLKIT (T0–T7 + verdict reversal):*
- `tools/reference/` (gitignored, SETUP §5.6) — cloned **gcc-papermario** (`a6afc2af`, the PSX gcc-2.7.2 lineage
  source) + **xenogears-decomp** (`f27c0768`, Square Oct-1998, our EXACT compiler). The primary-source corpus.
- `tools/wall_taxonomy.py` + `docs/wall-taxonomy.md` — census/size every residual class (carried from P17 T1).
- `tools/ram_probe.py` + `docs/actor-struct.md` — the actor/arg0 struct, recovered + live-verified (R10).
  **Re-confirmed byte-NEUTRAL for matching** (matching reads access width off the asm opcode, not a struct def).
- `tools/ghidra_scripts/DecompileFunctions.java` — headless Ghidra-C batch pre-pass (no /mcp); feeds the
  `.run/ghidra_c/` cache (300 fns) the waves draft from.
- `tools/census_conflict_callees.py` + `tools/derive_canonical_sigs.py` — the **canonical-sig layer** builders
  (one byte-neutral `s32 func_X(s32…)` per conflict callee; arity from Ghidra-C + asm read-before-write $a0–$a3).
  The 20-extern block at the top of `src/ov_SC01_077/ov_SC01_077.c` (LOCAL; reach-1 names differ per overlay).
- `docs/hand-matching-process.md` — §1 loop / §2 idioms / §3a 5-move signature playbook / §7 wave / §8 the
  canonical-sig-layer finding / §8e Phase-18 outcome (corrected to the register-pinning toolkit).
- `docs/matching-cookbook.md` **§17** — **the matching TOOLKIT** (the phase's durable deliverable): the
  call-crossing register-ORDER class is **STEERABLE with `register __asm__` PINS + a scheduling barrier**
  (corrected from a wrong mid-phase "unsteerable" verdict); **array-decay** forces rematerialization;
  **for-loop / statement-order** control scheduling; the **`sig_unify`-MANDATORY** gate gotcha; the
  **narrow-param loose-typing** wall (stub). §16 reconciled (§10-vs-§16 tension resolved).
- `docs/matching-cookbook.md` **§17a (THIS SESSION)** — the toolkit **at wave scale** (measured close-rates) +
  the **pipeline-integration recovery** techniques (call-site casts not redeclaration + re-validate; stale
  sibling `M2C_UNK` decl reconcile; the implicit-int caller class) + **two NEW residual classes** (per-file
  `-O0`; gcc loop-guard operand-order).
- `src/shared/engine_core.h` — the worked-example macros `DEFINE_func_8012B8E4` (pins + barrier) and
  `DEFINE_func_801399A8` (for-loop/structural) + **~33 new Phase-18 reach-134 macros** (the wave harvest).
- `config/dedup.us.yaml` — **1450 validated cross-binary groups** (was ~1424 at phase start; +the Phase-18
  propagations). 0 failed.
- `src/ov_SC01_077/ov_SC01_077.c` + the **134 overlay `.c` files** — the harvest source + the ×134
  propagations; 2 recovery reconciles (func_8012A418 stale-sibling-decl; func_8012F68C parse-fix).

*The Step-3b/Step-1 wave harness (gitignored under `.run/`, regenerable; the recipe is cookbook §17/§17a):*
- `.run/harvest_wave_3b.js` (calibration, 16 targets) + `.run/harvest_wave_p18s1.js` (Step-1, 31 targets,
  +embedded canonical callee sigs +call-site-cast/re-validate). `tools/gen_harvest_targets.py` generates the
  per-target callee-sig/data-decl manifest the Step-1 prompt embeds.
- `phase-ends/CURRENT_PHASE.md` → **`phase-ends/logs/Phase18.md`** (R19 archive). `phase-ends/PhaseEnd_Phase18.md` — this file.

**Local artifacts (gitignored / regenerable):** `.run/ghidra_c/*` (300 cached Ghidra-C), `.run/drafts-*`
(wave drafts + gate-staging dirs), `.run/p18/*` (T1/T2-T3 analyses, exemplar scratch), `.run/harvest_*.js`,
`.run/*_targets*.json`, `build/`, `expected/`, `asm/`, `assets/`. `tools/reference/` (the cloned gcc/Xenogears
source). The 134 overlay Ghidra programs are script-reproducible (DB-commit deferred as regenerable).

**Tools/packages installed:** None — the whole phase used the existing Phase-4/6/10/11/12/13 toolchain + venv.
(Wine deliberately NOT installed — W1 ruled build-divergence out by proxy; SETUP §4.8 unchanged.)

**Verification results (literal) — the milestone proof:**
- **`make check-all` → 136 passed, 0 failed of 136** (main `143dbb89…`, resident `8e17e02f…`, all 134 overlays
  byte-identical; ov_SC01_077 `d19c9580…`), reproduced from clean after every step (R22).
- **`make report`:** FLEET byte-identical **194,839 / 344,010 = 56.64%** (phase start 55.51%); **dedup-check
  1450 validated, 0 failed**; **0 NON_MATCHING** in any default build (G4).
- **The TOOLKIT, byte-gated per class:** register-ORDER → `func_8012B8E4` MATCH via pins+barrier (the flagship
  "unsteerable" fn); array-decay → `func_8012B4B8` 88→52, `func_80149544/584` MATCH; structural/for-loop →
  `func_801399A8` MATCH. Honest stubs: narrow-param (`func_80146A6C`), loop-guard order (`func_8012C2D0`),
  §10 sched (`func_8014F2E0`), per-file -O0 (`func_8013C360`+~17).
- **The toolkit at WAVE scale (the bounded demonstration):** Step-3b calibration **9/16 = 56% whole-binary**
  (vs the Phase-17 prompt's 33%); Step-1 (prompt v2: +embedded sigs +call-site-cast) **28/31 = 90% `match_one`,
  22 verified**. **Session fleet arc 55.58% → 56.64% (+1.06%, ~31 reach-134 matches; phase total 55.51→56.64 =
  +1.13%).**
- `git status`: only `config/`/`tools/`/`src/`/`docs/`/`phase-ends/` tracked; **zero ROM-derived/generated bulk
  staged**. **No Ghidra DB change** this phase (matching used cached Ghidra-C + asm; the `db.*.gbf` churn is
  SessionStart-restart noise — R23 no-op, do NOT stage).

**Milestone achieved (confirmed by Drew, gate 2):** the knowledge-gated milestone — a per-class byte-gated
verdict (validated C idiom OR honest "unsteerable" verdict naming the exact gcc pass), §10-vs-§16 reconciled,
≥1 quirk-tail function newly matched, 136 binaries byte-identical throughout — is **met and exceeded**. The
phase's headline reversal: the highest-reach **call-crossing register-ORDER class is STEERABLE** (`register
__asm__` pins + a scheduling barrier), not "unsteerable" as a mid-phase draft wrongly concluded. The toolkit
was then **taught to a parallel Ultracode wave** and demonstrated at scale (close-rate 33% → 56% → 90%
`match_one`), banking ~31 reach-134 matches (fleet +1.13%).

**Next:** **Phase 19 — Scale the toolkit (the wave-harvest at scale) + the cheap front-loaded levers.** A fresh
session, **plan mode** (Tier-1 Phase-Start). See the **Phase-19 Backlog** below for the full prioritized brief
(the -O0 split-file fix first, recovery-tooling, then 50-target waves scaling to 100+, with an optional bounded
gcc-research spike on the last residual classes). The infra is BUILT and staged.

## Deviations
| Item | Plan | Actual | Reason |
|---|---|---|---|
| Register-ORDER verdict | T1–T5 concluded "UNSTEERABLE from C" | **REVERSED — STEERABLE via `register __asm__` pins** | I'd skipped the most direct lever; Drew's "we hand-match everything" pushed it; `func_8012B8E4` byte-gated (P9/R14 self-correction). The "brute waves won't help" point stood; the HAND pin lever does. |
| Phase scope | research + a bounded quirk-tail demo (gate-1) | research **+ a calibration wave + a bounded Step-1 wave** | the reversal made the toolkit teachable to waves; demonstrating it at scale (33%→56%→90%) is the real proof it raises the ceiling |
| Step-1 size | "scale the wave on the tail" | **bounded 31 targets** (Drew chose ~40; full tractable-247 → Phase 19) | gate-1 deferred the full sweep to Phase 19; Step 1 = a bounded demonstration of the taught wave |
| Wave close-rate gap | (not anticipated) | `match_one` MATCH ≫ whole-binary verified (12→9, 28→22) | the gap is **declaration plumbing** (call-site casts the agents skip + `sig_unify` narrowing the extern), NOT codegen — recovered deterministically (cookbook §17a) |
| W1 Wine native-compiler check | bounded Wine run | **ruled out by proxy, Wine dropped** | 700+ matches prove our cc1's regalloc is faithful; the real compiler emits the same bytes → confirms, doesn't crack; heavy install not worth it (plan escape clause) |
| Effort | Max planning, xHigh/Ultracode execution | Max/xHigh research + debugging; **Ultracode for the waves** (Drew toggled); xHigh for this close | breadth-shaped waves under Ultracode (R26/R27); deep synthesis at xHigh (Drew's saved default) |
| New residual classes | (not anticipated) | **per-file -O0** + **gcc loop-guard operand-order** surfaced at scale | the waves exposed classes the single-function research hadn't; the -O0 one is build-infra (high ROI), not a wall |

## Commit Message
```
(Phase 18 landed as 16 commits d20b20c64..151da542a + this PhaseEnd.)

feat(phase-18): compiler-quirk research -> the matching TOOLKIT, taught to waves (v1.17.0)

- RESEARCH (T0-T7): read gcc-2.7.2 source (gcc-papermario) + mined Xenogears (our exact
  compiler) -> per-class byte-gated verdicts. VERDICT REVERSAL (Drew "hand-match everything"):
  the call-crossing register-ORDER class is STEERABLE via `register __asm__` pins + a scheduling
  barrier (func_8012B8E4, the flagship "unsteerable" fn, byte-gated) -- not unsteerable.
- TOOLKIT (cookbook §17): pins+barrier (register swap), array-decay (hoist-vs-remat),
  for-loop/statement-order (structural), sig_unify-mandatory; narrow-param = honest stub.
  §16 reconciled (§10-vs-§16).
- TAUGHT TO WAVES (§17a): calibration 9/16=56% whole-binary (vs 33%); Step-1 (embedded
  canonical callee sigs + call-site-cast/re-validate) 28/31=90% match_one, 22 verified.
  ~31 reach-134 matches banked, each propagated x134. fleet 55.51 -> 56.64% (+1.13%).
- FINDING: the match_one->gate gap is declaration plumbing (call-site casts not redeclaration;
  stale M2C_UNK sibling-decl reconcile; implicit-int caller class) -- recovered deterministically.
- NEW residual classes: per-file -O0 (~18 fns, needs an -O0 split file like src/boot.c -> high
  ROI) + gcc loop-guard operand-order (irreducible). W1: build-divergence ruled out by proxy.
- make check-all 136/136 byte-identical (R22); dedup 1450 validated/0 failed; 0 NON_MATCHING (G4).
- worklog -> phase-ends/logs/Phase18.md (R19); bumps 1.16.0 -> 1.17.0
```

## Rules Added This Phase
| Rule | Reason |
|---|---|
| **None (governance).** Phase 18's lessons are *findings + techniques*, recorded where the Phase-8/11/13/15/16/17 precedent puts them (cookbook, not rules): the **register-pinning toolkit** + the **call-site-cast/re-validate** + the **sibling-decl/implicit-int recovery** + the **per-file -O0 and loop-guard residual classes** → cookbook §17/§17a + hand-matching §8e. The **verdict-reversal lesson** ("never conclude *unsteerable* before trying `register __asm__` pins; an intermediate metric is not the gate") is already governed by **G3/P9/R14** and the `dont-conclude-unsteerable-try-register-pins` memory. The **probe-before-investing / bounded-calibration-before-scale** discipline is already cookbook (Phase 15) + effort-map. No new norm of conduct emerged. | A research→toolkit→demonstrate phase produces knowledge, not governance. Existing rules covered the ground and the phase reinforced them (esp. R14: the "unsteerable" over-claim was an R14 failure mode, self-corrected). |

## PhaseEnd Changelog
**v1.16.0 → v1.17.0 — Phase 18 complete (Gen2 phase 10).** Set out to "understand gcc-2.7.2 to raise the
match-% ceiling," and delivered a **matching TOOLKIT** that does exactly that. Reading the real gcc-2.7.2 source
+ mining Xenogears (our exact compiler) produced per-class byte-gated verdicts — and a **decisive reversal**
(Drew's "hand-match everything"): the highest-reach **call-crossing register-allocation-ORDER class is
STEERABLE** with `register __asm__` pins + a scheduling barrier (the flagship `func_8012B8E4`, byte-gated),
*not* "unsteerable" as a mid-phase draft wrongly concluded (a clean R14 self-correction). The toolkit
(pins+barrier · array-decay · for-loop/statement-order · sig_unify-mandatory; narrow-param = honest stub) was
then **taught to a parallel Ultracode harvest wave** and demonstrated at scale: whole-binary close-rate **33% →
56%** (Step-3b calibration) **→ 90% `match_one`** (Step-1, after embedding each callee's canonical signature
and teaching call-site casts). **~31 reach-134 functions matched** (each propagated ×134), driving the fleet
**55.51% → 56.64%**, all 136 binaries byte-identical, 0 NON_MATCHING. The phase's reusable yield: the toolkit
itself (cookbook §17), and the **pipeline-integration recovery** insight (§17a) — the `match_one`→gate gap is
**declaration plumbing** (call-site casts, stale-sibling-decl reconcile, implicit-int callers), recoverable for
~0 agent tokens, not a codegen wall. Two new residual classes surfaced at scale: the **per-file -O0 class**
(~18 byte-exact-at-O0 functions needing their own -O0 split file — a high-ROI build-infra fix, not a wall) and
the **gcc loop-guard operand-order** residual (irreducible). W1 ruled build-divergence out by proxy (Wine
dropped). No new governance rules (techniques → cookbook). The harvest infra is BUILT and staged for Phase 19's
scale-up.

## Phase-19 Backlog — "Scale the toolkit" (Drew's research + wave recommendations, full context)

> Phase 19 = **scale the proven toolkit over the tractable reach-134 tail**, front-loaded with two cheaper
> levers, run as a flywheel. Detailed plan is a fresh-session Tier-1 Phase-Start task; this is the prioritized
> brief, by ROI. (Decided with Drew at the Phase-18 close.)

1. **[HIGHEST ROI — DO FIRST] The per-file `-O0` split-file fix (build-infra, no research, no agents).** ~18
   functions in ov_SC01_077 were built **-O0** (prologue sig `21F0A003` = `addu $fp,$sp,$zero`; args spilled to
   frame; load-delay nops; redundant `addu rd,rs,$zero`). Their correct C is **byte-exact at -O0** but the
   overlay TU compiles `-O2`, and **gcc-2.7.2 has no per-function optimize pragma** (opt is per-file, Makefile).
   Fix = give them their own `-O0`-compiled split file with a target-specific `CC1FLAGS := -O0 …` (the
   **`src/boot.c` precedent**, Phase 7). ~18 fns × reach-134 for an afternoon of Makefile work. Members:
   func_8013C360 + func_8013B568/B598/B6A0/B7AC/B7F4/B83C/BC7C/BCDC/BD34/BD74, func_8013C08C/C0F8/C414/C938/C964,
   func_80144B9C, func_801457A4. (One agent already produced verified-correct -O0 C for func_8013C360 — see logs.)
2. **[COMPOUNDING — DO SECOND] Recovery-tooling investment between batches.** This session's deterministic
   recoveries (call-site arity/void casts; stale `M2C_UNK` sibling-decl reconcile) banked matches for **~0 agent
   tokens**. Fold them into the gate so the close-rate rises mechanically: teach `sig_unify` (or a post-pass) to
   **auto-apply call-site arity/void casts** when a draft's call disagrees with the canonical extern, and to
   **auto-reconcile stale sibling `M2C_UNK func_X();` decls** to the real sig. Also solve the **implicit-int
   caller class** (3 deferred fns: func_80147514/8017209C/80168F40) — the clean path is **propagate-first**
   (the def lands in `engine_core.h`, included first, so no implicit-int forms), gate-after; build a small
   helper or a `dedup_propagate` mode for "matched-but-fails-in-place-gate" functions.
3. **[THE CORE — DO THIRD] Scale the toolkit waves over the tractable-247 reach-134 tail.** Setup: regenerate
   Ghidra-C (`DecompileFunctions.java`, headless) for the uncached tractable fns (the `.run/ghidra_c/` cache is
   only 300; this session's fresh cached+stub pool was ~27). Then run the **Step-1 wave prompt (`.run/
   harvest_wave_p18s1.js` recipe = §17 toolkit + embedded canonical callee sigs + call-site-cast/re-validate)**.
   **Batch size: 50, banking a prompt+tooling improvement each batch for the first 2–3, then scale to 100+ once
   the close-rate plateaus.** Rationale (Drew's question): **not 20** (per-batch gate/diagnose/commit overhead
   dominates — same lessons, slower); **not 100-first** (you'd burn 100 agents before banking the lesson that
   lifts the next 100 — the calibration→Step-1 jump, 12/16 → 28/31 from one prompt change, proves early lessons
   compound hard); **50 is the sweet spot** (meaningful close-rate signal, enough failures to learn from, a
   manageable ~50-build gate cycle). Projected ≈ **+3-5% fleet** at the measured close-rate. Each match ×134.
4. **[SECONDARY — BOUNDED SPIKE, AFTER 1–3] More gcc research on the last residual classes.** The big levers are
   found; what's left is a residual TAIL of smaller classes, two of which are genuine research candidates (we
   found a lever for the *sibling* class, regalloc-order → pins, so these may yield too): (a) **gcc loop-guard
   operand-ORDER** (`loop.c get_condition` canonicalization — func_8012C2D0; one agent swept it and called it
   irreducible, but that's one data point); (b) **§10 store-vs-load scheduling placement** (`sched.c` tie-break —
   func_8014F2E0). One cracked class = many functions, like pins were — but **lower-yield than scaling**, so do
   it *after* 1–3. Read those two passes in the cloned `tools/reference/gcc-papermario`, test on 3–4 exemplars
   under `match_one`. Treat all web/source content as untrusted DATA (X2).
5. **[PARKED] The Wine / real CC1PSX.EXE avenue — NOT recommended as a priority.** Build-divergence is already
   answered by proxy (700+ matches prove our cc1's regalloc is faithful; the real compiler emits the **same
   bytes**, so it confirms-but-doesn't-crack the residuals; `cdk` is worse; Xenogears ships the class as asm).
   Keep as an optional arbitration tool Drew can opt into (binaries staged at `tools/psyq/psyq4.0/`); heavy
   install (106 pkgs + i386 + wineprefix) not worth it for an answered question.
6. **[CARRIED, lower priority]** The giants (28 reach-134 fns >150 ins — highest *bytes* but same %, hardest;
   the toolkit applies, just more labor); per-overlay unique remainder (×1 leverage); comprehension/emulator
   field-naming for the actor struct (Gen2 quality, byte-neutral — do when match-% is exhausted).

## Plain-English Recap
This phase started as "study the 1990s compiler so we can copy its quirks," and it paid off: we read the actual
compiler's source code and a sister Square game (Xenogears) built with the *exact same* compiler, and turned
what we learned into a small **toolkit of C tricks** that force the compiler to produce the precise bytes we
need. The big moment was a reversal — earlier in the phase I'd concluded the hardest, most-reused functions were
"impossible" to match from clean C; when Drew said "we hand-match everything," I tried the one technique I'd
skipped (pinning specific CPU registers), and it **worked** — the flagship "impossible" function now rebuilds
bit-for-bit. Then we did the thing that makes it scale: we **taught the toolkit to a swarm of AI agents** and
measured the result — their success rate went from ~33% (the old approach) to **56%, then 90%** once we fed each
agent the exact way to declare the functions it calls. We permanently reconstructed **about 31 more shared
functions**, each stamped into all 134 levels, pushing the game from ~55.5% to **~56.6%** rebuilt bit-for-bit.
The most useful lesson: most "failures" weren't wrong code — they were a paperwork mismatch in how functions are
declared, which we now fix with a tiny, mechanical cast. We also found ~18 functions the original team compiled
with optimizations *off*; their code is already correct and just needs its own build setting — a quick job for
next phase that unlocks all 18 at once. Everything still rebuilds perfectly; nothing broke. **Next phase scales
this up:** do the quick -O0 fix, make the gate auto-fix the paperwork, then run the agent waves in batches of 50
(learning between each), with optional deeper compiler research only for the last stubborn cases. The Wine
route stays parked — we already have the answer it would give.

## 🛑 Stop Here
PhaseEnd written; `CURRENT_PHASE.md` archived → `phase-ends/logs/Phase18.md` (R19). **Drew commits AND pushes**
this PhaseEnd + any uncommitted Phase-18 work (R6/R8 — the matching commits `d593ee20f`..`151da542a` are already
landed; this PhaseEnd + the archived log are the close). No Ghidra DB change this phase (R23 no-op — the
`db.*.gbf` churn is restart-noise, do NOT stage it). Gen2 continues — do **NOT** start Phase 19 here. Start a
**fresh session** (plan mode) for **Phase 19 — Scale the toolkit** (the backlog above; -O0 fix first, then
recovery-tooling, then the 50-target waves). Keep this file forever.
