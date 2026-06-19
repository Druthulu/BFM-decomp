# PhaseEnd — Phase 16: Struct-heavy shared core — the loose-typing wall + pivot
**Date:** 2026-06-19 · **Project Version:** 1.15.0 · **Phase Status:** Complete (PIVOT — negative result + strategic redirect, like Phase 3.5) · **Generation:** Gen2 (8th phase)

> Phase 16 set out to crack the ~964 struct-heavy **shared** engine functions via an m2c→sig_unify→
> decomp-permuter→byte-gate pipeline + an unattended multi-day run. It found, through the byte-gate, that
> this approach **cannot** crack them: the original engine is **loosely typed** (no consistent signatures
> exist to recover), so the yield is ~3%, bounded by a fundamental wall, not a fixable bug. The phase
> closes deliberately on that honest finding + a documented new plan. The granular session trail is the
> conversation; the durable artifacts are `docs/struct-core-pivot.md` (findings + new directions) and this file.

## Build Log

**Files created/changed and complete — do not recreate:**

*The pipeline + harness (built; the bug-fixes are REAL and KEPT):*
- `include/common.h` — **m2c-compat prelude (byte-neutral, KEPT):** `s64`/`u64`/`f64` + `M2C_UNK*` typedefs,
  the **byte-faithful** macros `M2C_FIELD`/`M2C_BITWISE`, and `NULL`. Lets m2c `--valid-syntax` output compile
  (`M2C_FIELD(p,t,o)` ≡ `*(t)((s8*)p+o)`). Proven byte-neutral on all binaries (main `143dbb89`, resident
  `8e17e02f`, ov_SC01_077 `d19c9580`). The non-faithful m2c macros are deliberately left undefined = an early
  "not m2c-matchable, defer" signal.
- `tools/p16_permute.py` — decomp-permuter batch driver (nested `M2C_FIELD`→cast expander, scratch setup, run,
  parse). **Three real bug-fixes:** (1) `base.c` KEEPS the canonical callee externs (was stripping them →
  implicit-`int` → wrong context); (2) a true match is **`output-0-*` only** (was counting `output-<score>`
  intermediate bests → the illusory overnight "42%"); (3) `winner_to_draft` strips typedefs by line-filter.
- `tools/sig_unify.py` — **fix (KEPT):** also canonicalizes m2c's **no-`extern`** callee prototypes
  (`M2C_UNK func_X(void *); /* extern */`), which it previously missed → `conflicting types` in the link.
- `tools/p16_known_answer.py` — graduated **known-answer ladder** (revert a matched fn → re-derive → measure;
  `--gate` for the whole-binary ceiling). The methodology that surfaced the real (low) yield.
- `tools/p16_improve.py` — known-answer **improvement-loop** workhorse (categorizes every fail by actionable
  class; tracks the re-derivation ceiling).
- `tools/gen_engine_decls.py` + (regenerable, uncommitted) `src/shared/engine_decls.h` — the **canonical-decls
  header ("lever 1")**. **Documents why it FAILS:** a single global signature per function breaks the existing
  loose-typed matches (`passing arg makes integer from pointer`). Kept as the evidence/record.
- `tools/auto_driver.py` + `tools/auto_supervisor.sh` + `tools/auto_stop.sh` + `tools/auto_status.sh` — the
  **unattended-run driver + pure-bash supervisor + STOP-sentinel safe-exit + heartbeat** (Drew's never-stop +
  message-me-to-exit design). Built + syntax-clean; **NOT deployed** (pending a worthwhile yield).
- `docs/struct-core-pivot.md` — **the key deliverable:** findings, the loose-typing root cause, and the new
  research directions (emulator type-recovery → Ghidra global type propagation; K&R modeling; LLM-gate-loop).
- `docs/matching-cookbook.md` **§15** — m2c-macro/permuter/struct empirical determinations (R16 flywheel).
- `src/ov_SC01_077/ov_SC01_077.c` — a few byte-gated leaf matches (the modest real yield).
- `phase-ends/CURRENT_PHASE.md` → **`phase-ends/logs/Phase16.md`** (R19 archive). `phase-ends/PhaseEnd_Phase16.md` — this file.

**Tools/packages installed:** None (used the existing Phase-4/6/10/11/12/13 toolchain + venv).

**Verification results (literal):**
- **All binaries still byte-identical** from a clean build (main `143dbb89…`, resident `8e17e02f…`,
  ov_SC01_077 `d19c9580…`) — the byte-locked reference never regressed.
- **The byte-gate guaranteed zero false matches** throughout — it caught the illusory "42%" (intermediate
  permuter scores), the implicit-`int`-context wins, and the declaration-conflict drafts. G3/P9 held perfectly.
- **The wall, byte-checked:** the same function is called with an integer at one site and a pointer at another,
  and with an argument at one site and none at another; a global canonical-decls header breaks existing matches;
  many residual functions are body-byte-correct (`match_one` MATCH) yet have **no C declaration** consistent with
  both the canonical definition and the call site. Gate-verified yield on controlled samples: **~1–2 of 8–16.**

**Milestone achieved (honest, a PIVOT):** Phase 16 **proved by the bytes** that the m2c+permuter brute-force
will not crack the struct-heavy shared core — the root cause is the engine's **loose typing**, which no harness
fix resolves (yield ~3%). It produced a durable findings doc + new research directions, real harness bug-fixes,
and the unattended-run infrastructure (ready if the modest run is ever wanted). A negative-but-decisive result
that redirects the strategy — the Phase-3.5 precedent (a NO-GO that saves the project from a wrong path).

**Next:** **Fresh session for deep-research** (per Drew) on three questions: (1) how PS1/PsyQ matching decomps
use **Ghidra's decompiler + struct/type propagation** to get compilable matching C; (2) how the community handles
**loosely-typed / K&R-style** engine code at scale; (3) whether any **Square PS1 decomp recovered an actor/entity
struct**, and how. Then plan a new phase around **emulator type-recovery → Ghidra global type propagation** (the
root-cause attack). The modest m2c+permuter run remains an optional cheap consolation (not the plan).

## Deviations
| Item | Plan | Actual | Reason |
|---|---|---|---|
| Whole-phase outcome | build the struct→m2c→permuter pipeline + unattended 5-day run to crack the core | **negative finding + pivot** | the byte-gate proved the approach yields ~3%; the loose-typing wall is fundamental |
| S1 struct inference | infer the actor struct as the lever | **vacated** — struct typing is byte-identical to the `M2C_FIELD` cast (readability only) | empirically verified; the wall is signatures/loose-typing, not struct fields |
| "lever 1" canonical-decls header | the planned fix for declaration conflicts | **proven incompatible with loose typing** (breaks existing matches) | the original has no single consistent signature per function |
| The permuter | the yield lever | **only fixes regalloc/scheduling**, not wrong types/symbols/structure (which the residual needs) | confirmed across many functions |
| The overnight "42%" | a strong permuter rate | **a false positive** (intermediate `output-<score>` dirs miscounted as matches) | byte-gate caught it; fixed to `output-0-*` |
| Unattended run | the in-phase payoff (Sun) | **not deployed** | a ~3% consolation isn't worth the unattended risk; pivoting instead |
| Effort | Max planning, then execution | **Max throughout** (deep debugging + the pivot synthesis) | the work was non-obvious root-cause debugging, not breadth |

## Commit Message
```
docs(phase-16): close — m2c+permuter won't crack the loose-typed core; pivot to type-recovery (v1.15.0)

- FINDING (byte-proven): the engine is loosely typed (K&R; same fn called int/ptr, arg/no-arg
  across sites) -> no consistent signature exists -> m2c guesses inconsistently, permuter fixes
  only regalloc, byte-gate (correctly) rejects. Yield ~3%, bounded by a fundamental wall.
- docs/struct-core-pivot.md: findings + new research directions (emulator type-recovery ->
  Ghidra global type propagation; K&R modeling; LLM-gate-loop). cookbook §15 (m2c determinations).
- harness bug-fixes (REAL, kept): p16_permute output-0-only (killed the false 42%), base.c keeps
  externs, winner_to_draft line-strip; sig_unify canonicalizes no-extern prototypes; common.h
  m2c-compat (byte-neutral); gen_engine_decls (documents why a global canonical header fails).
- tools/auto_driver+supervisor+stop+status: unattended-run + safe-exit infra (built, not deployed).
- p16_known_answer / p16_improve: the known-answer ladder + fail-class categorizer.
- a few byte-gated leaf matches; all binaries byte-identical; worklog -> logs/Phase16.md (R19).
- bumps 1.14.0 -> 1.15.0
```

## Rules Added This Phase
| Rule | Reason |
|---|---|
| **None (governance).** The lessons are *findings + techniques*, recorded where they belong (Phase-8/11/13/15 precedent): the **loose-typing wall** + **new directions** → `docs/struct-core-pivot.md`; the m2c-macro/permuter mechanics → cookbook §15; the **"an intermediate metric (permuter score, `match_one`) is NOT a match — only the whole-binary byte-gate is, and verify a metric against the gate before trusting it for a decision"** lesson is a direct application of **G3/P9/R14** (I over-claimed "42%" before gating — exactly the R14 failure mode, extended from sub-agent counts to *any* intermediate metric). No new norm of conduct emerged. | A negative-result pivot produces knowledge, not governance. The existing rules (G3 byte-match, P9 honesty, R14 verify-vs-bytes, R22 clean-rebuild) already covered the ground; the phase reinforced them. |

## PhaseEnd Changelog
**v1.14.0 → v1.15.0 — Phase 16 complete (Gen2 phase 8; a PIVOT).** Attempted to crack the ~964 struct-heavy
**shared** engine functions via m2c→sig_unify→decomp-permuter→whole-binary-byte-gate, with an unattended
multi-day driver. **The byte-gate proved the approach won't crack them:** the original engine is **loosely
typed** (the same function is used with contradictory types/arities across call sites), so no consistent set of
signatures exists to recover — m2c guesses inconsistently, the permuter only fixes register allocation, and the
gate (correctly) rejects the subtly-wrong drafts. Real yield ~3%, bounded by this fundamental wall, not a bug.
Along the way the byte-gate caught a string of false positives (a "42%" mirage from miscounted intermediate
permuter scores; implicit-`int` compile contexts; declaration conflicts) — each became a **real, kept harness
fix**. The unattended-run driver + supervisor + safe-exit were built (not deployed). **Decision (Drew): pause
the brute-force, document, and plan a new approach** that attacks the root cause (lost types):
**emulator-recover the actor struct + field/arg types → define in Ghidra → global type propagation → Ghidra-C →
permuter + byte-gate**, grounded first by **deep-research** on how the PS1 decomp community handles loosely-typed
engine code (a fresh session). Findings + directions in `docs/struct-core-pivot.md`; cookbook §15; common.h
m2c-compat is byte-neutral and kept; a few byte-gated leaf matches banked. No new governance rules — the lessons
are findings/techniques, and they reinforce G3/P9/R14/R22. All binaries remain byte-identical.

## Plain-English Recap
We tried to automatically reconstruct the game's hardest remaining code — the shared "engine" functions used by
every level — by having a decompiler write C, a brute-force tool fix the small details, and a strict bit-for-bit
referee check every result. It works, but only for a few percent, and we hit a real wall: the original game was
written in an old, *loose* style of C where the same function is used in contradictory ways in different places
(here it's handed a number, there a pointer; here with an argument, there with none). There is no single
consistent way to describe that in modern C, so no amount of brute-force fixes it. The very good news is that the
bit-for-bit referee never let anything wrong slip through — it actually *caught* us when an earlier result looked
great but was a false alarm — so everything we've built is trustworthy, and we learned *exactly* why this is
hard. So we're deliberately pausing this approach (it's a consolation, not the breakthrough) and planning a
smarter one: recover the game's real data structures by **watching it run in an emulator**, then use the more
powerful analysis tool (**Ghidra**) to apply those real types **consistently** across all the functions — which
is the thing the loose-typing wall denied us. Before committing, we'll research how other similar game
decompilation projects solved this exact problem. Everything we learned and every new idea is written down so the
next session starts fresh with full context. Nothing we already had broke; all the game's reconstructed pieces
still rebuild perfectly.

## 🛑 Stop Here
PhaseEnd written; `CURRENT_PHASE.md` archived → `phase-ends/logs/Phase16.md` (R19). The Phase-16 work is
committed (`commit:0122`..`commit:0127` + this PhaseEnd commit); **Drew pushes** (R6). No Ghidra DB change this phase
(pure tooling/matching — R23 no-op). Gen2 continues — do **NOT** start the next phase here. Start a **fresh
session** (effort **Max**) for the **deep-research** (the 3 questions in `docs/struct-core-pivot.md`), then plan
the new **type-recovery** phase. Keep this file forever.
