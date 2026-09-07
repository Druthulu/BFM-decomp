# Phase 25 · T6 — Fable5 Curriculum-Authoring Brief

> **Read this in a FRESH session running as Fable5Max.** This is the Step-B input package (plan-of-record §"The
> recommended shape"): Step A (the measure wave) is done; your job is to turn the measured frontier + the diagnosed
> wall-classes into the **finish curriculum** for the structural-family endgame. Grounded on byte-verified data, not
> prediction. Prepared 2026-07-09 by the Opus session that ran batches 1–3 + cracked the def-side wall.

## Your task (the deliverable)

Author the **crack curriculum** for the **95 still-stub draftable family exemplars** (10,785 ins). Per stub — or better,
per wall-CLASS — decide: **which tool/idiom cracks it**, whether it's **mechanical** (a deterministic tool) or **discovery**
(a NEW gcc-2.7.2 idiom only you can find), the **dedup-vs-template** question, and the **attack ORDER** (cheapest ×134
ROI first), with a **projected fleet-% / byte-weight per tier**. Flag genuine gcc-intrinsic walls as permanent
INCLUDE_ASM (G4). Validate the top 3–5 before scaling (Phase-15/16 lesson). Output a curriculum doc + a ranked worklist.

**Your edge = compiler-internals reasoning.** The mechanical tools + the measured residuals are below; the value you add
is diagnosing the residual CLASS of each wall and splitting "a deterministic tool already cracks this" from "this needs a
new idiom" — so the T7 execution session (back at Opus-Max + surgical tiers) doesn't waste effort.

## State (byte-verified, committed `20747321c`)

- **Fleet 72.29%**, `check-all` **136/136 byte-identical**, dedup 1813/0, 0 NON_MATCHING (G4).
- **127 draftable family exemplars** (all ov_SC01_077 members; `.run/t5_targets.json`): **32 banked** (each →×134 via
  `family_sweep`), **95 stub** = your worklist.
- **Frontier map: `.run/t5_frontier.jsonl`** — 125/127 measured (closeness + klass + status per exemplar). 2 tiny `_o0`
  stragglers unmeasured (`0x8013bc7c`/24ins, `0x8013bcdc`/22ins).
- Each stub is inst≈134 (a few 3/17/136/268) → **cracking one exemplar propagates ×~134**. The prize is ~95×134 ≈ up
  to ~12k fleet fns, but only for the cleanly-crackable subset — your job is to find how big that subset really is.

## The 95-stub worklist by frontier class ( **⚠ R14: re-verify before trusting** )

`.run/recon_sweep_targets.json` = the 51 "isolation-MATCH-classified" addrs. **CAUTION (learned this session):** the
frontier "match" status includes some **un-R14-verified agent self-reports**. A 5-target spot-check found only **3/5**
were genuine `match_one`-MATCH (1 CC1-FAIL, 1 DIFF-1). **Re-verify each with `match_one` (add `--o0` for `_o0` split
fns) before classifying.** Rough measured breakdown:

| class | ~count | lever |
|---|---|---|
| def-side wall, **clean engine_core.h canonical** | **~19** | `canon_sig_reconcile.py` — PROVEN (banked batch-2's 5 giants byte-identical). Mechanical. |
| def-side wall, **implicit-int fallback** (harder) | ~32 | varied — callee-sig conflicts, non-id types, data symbols. Some mechanical w/ a tool extension, some per-fn. |
| genuine near-miss (regalloc/schedule) | 31 | permuter-ILS (seeds pre-softened) / your idiom discovery. |
| hard wall (non-identical ambient types / macro-local data) | 11 | `reconcile_decls` (§33) / rename / your discovery. |
| unknown / unmeasured | 2 | measure (`_o0` stragglers). |

Plus 4 known-harder inside the 51: `func_80166994` (369, T7-caller-entangled: 5 callers mixed s16/s32) and the 3 `_o0`
giants (`func_8013C414/8013BD74/8013C0F8` — isolation-MATCH at -O0 but in-context byte-diff).

## The wall-classes (diagnosed this session — full detail in cookbook **§41**)

1. **Def-side canonical-sig wall (the dominant one).** Drafters write Ghidra-TYPED sigs (`void f(u32*, s16*)`) that
   conflict with the TU's canonical sig — declared *inside a `DEFINE_func_*` macro* in `engine_core.h`, so `sig_unify`
   (file-scope-extern rewriter) can't reach it. **`canon_sig_reconcile.py`** cracks it BYTE-NEUTRALLY when a clean
   engine_core.h canonical exists: strip ambient-dup typedefs/externs → rewrite def to that canonical → **cast changed
   params AT USE, never intermediate locals** (a local adds a pseudo → regalloc shift → byte-diff; measured
   `70ff4748`≠`d19c9580`). When there's NO engine_core.h decl it falls back to implicit-int `s32 f(s32…)` — LESS
   reliable (that's the ~32).
2. **Callee-sig conflicts.** The draft declares a *callee* (e.g. resident `func_800599B8`) with a Ghidra sig that
   conflicts with its canonical → `conflicting types for func_800599B8`. `canon_sig_reconcile` strips redundant
   func/data/memcpy externs the TU/engine declares, but NOT resident-callee (0x8005xxxx) externs not in engine_core.h
   → a candidate small tool extension (strip/reconcile resident-callee externs too).
3. **Non-identical ambient types.** Draft's `Vec3`/`SVEC`/`ApplyMatrixSV` differ in LAYOUT from `engine_types.h`'s →
   can't strip (not identical), can't keep (conflicts). Needs a rename or a real layout reconcile. (§40a's split-TU
   collision lesson is adjacent.)
4. **Macro-local data symbols.** `D_xxx` declared *inside* `DEFINE_` macros (not file-scope) → stripping the draft's
   extern leaves the body referencing an undeclared symbol; keeping it conflicts. `reconcile_decls.py`/§33 byte-neutral
   access-cast territory.
5. **-O0 in-context byte-diff.** The 3 `_o0` giants are isolation-MATCH at -O0 (`match_one --o0`) but byte-diff in the
   real `_o0` TU. `canon_sig_reconcile`'s void→s32 return is **NOT byte-neutral at -O0** (it changes the epilogue), and
   `gate_stage`'s call-site transforms don't fix it. Likely fix = an -O0-specific reconcile that PRESERVES the void
   return + casts params at use. Worth resolving: 3×134 ≈ 400 fns.
6. **Genuine near-misses.** Regalloc/schedule residuals (the 31) → permuter-ILS or a new C-lever idiom.

## The tools you're orchestrating (all committed, reproducible)

- **`tools/canon_sig_reconcile.py`** — def-side sig reconcile (clean-canonical). `--fn --draft --out --tu <split.c>
  [--sig]`. PROVEN.
- **`tools/reconcile_decls.py`** — data-symbol reconcile (§33 fleet-majority type oracle + byte-neutral access cast).
- **`tools/permuter_ils.py`** + the floor-free masked scorer (§permuter overhaul, Phase 24) — regalloc/schedule search.
- **`tools/family_sweep.py --no-preclassify`** — propagate a banked exemplar ×134 (real-TU byte-gate; §40/§40a).
- **`tools/family_remap.py`** — mechanical per-overlay symbol remap.
- **`tools/harvest_verify.py`** — the whole-binary byte-gate (sole arbiter, G3/P9). `_o0.c` builds -O0 automatically
  (Makefile:445). **`tools/match_one.py --o0`** — -O0 isolation proxy (added this session).
- **Knowledge base:** cookbook §17–§41 (esp. §40 mechanical remap, §40a decl-reconcile, §41 def-side wall);
  `docs/gcc-2.7.2-map/` (§31 codegen map: sched/regalloc/loop/cse).

## Swing questions to resolve FIRST (they size the endgame)

1. **How big is the CLEAN mechanical subset really?** Re-verify the ~19 clean-canonical stubs with `match_one`; how many
   bank via `canon_sig_reconcile` as-is? (Batch-2's 5 did.) That's the cheapest ×134 tier — quantify it.
2. **Does a small tool extension (strip/reconcile resident-callee externs) unlock much of the ~32 fallback tier?**
   `func_8013D9B0` failed on a callee (`func_800599B8`) conflict — is that pattern common? If so it's a mechanical
   multiplier.
3. **Is the -O0 reconcile mechanical** (preserve void, cast-at-use)? If yes → the 3 `_o0` giants + the 2 stragglers ×134.
4. **Which non-identical-type walls are a rename vs a real layout conflict?** (Vec3, SVEC, ApplyMatrixSV.)
5. **dedup-vs-template**: reconciled bodies carry ov_SC01_077-specific casts, so `family_sweep` to siblings byte-matched
   only SOME (`func_8016DC20` = 133 siblings failed → exemplar-only). Does a per-sibling re-reconcile fix the ×134
   rollout, or is it template-per-overlay? This swings the ×134 math (§41 "sweep fragility").

## Reminders for the T6 session

- **Effort:** you're Fable5Max for the curriculum (deep synthesis). Drop back to **Opus-Max + surgical tiers** to
  EXECUTE the curriculum (T7) — Fable5 authors, cheap-Opus/permuter/mechanical-tools execute (R27).
- **R14 throughout** — re-verify every "match" against `match_one` before building on it (it bit this session twice).
- **R22** — clean-fleet 136/136 (`make clean` + extract-all-136 + `check-all`; use `BINS="main resident $(ls -d
  src/ov_*/|xargs -n1 basename)"` — an unexpanded `$(OVERLAY_BINARIES)` gives a false result).
- **G3/P9/G4** — the whole-binary byte-gate is the sole arbiter; genuine intrinsic walls stay INCLUDE_ASM.
- Phase is **OPEN** — do NOT close; the curriculum feeds T7, then Close when top-family ROI drops.
