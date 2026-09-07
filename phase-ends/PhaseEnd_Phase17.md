# PhaseEnd — Phase 17: Raise the harness ceiling, then gate the compute run
**Date:** 2026-06-20 · **Project Version:** 1.16.0 · **Phase Status:** Complete (go/no-go decided — NO-GO on brute waves at the current ceiling; PIVOT to compiler-quirk research) · **Generation:** Gen2 (9th phase)

> Gen2 phase 9 of the arc (8→9→10→11→12→13→15→16→**17**; 14 deferred to Gen3+). Ran across **4 sessions**;
> the granular per-session trail (the 5-avenue ceiling test, the demo, the calibration wave, the canonical-sig
> layer build, the 4-circular hand-match attempts, the keystone/leverage analysis) is preserved on-demand at
> **`phase-ends/logs/Phase17.md`** (R19 — NOT auto-loaded; consult only when researching a mechanism). This
> file is the synthesis. Owner decisions (Drew, 2026-06-19/20): pursue all 5 ceiling avenues → on their
> failure, PIVOT to guided hand-matching → build the canonical-sig layer → on the finding that the wall is the
> compiler, **defer the wave and open a fresh compiler-quirk research phase** (goal = match-%, not comprehension).

## Build Log

**Files created/changed and complete — do not recreate:**

*The canonical-sig layer (session 4 — this PhaseEnd commit lands these):*
- `tools/census_conflict_callees.py` — **new.** Censuses the shared callees that block a parallel wave. The
  accurate conflict predicate: an undeclared-`stub` callee with `decl_sources = n_callers + is_target >= 2`
  (a `defined`/`declared`/`extern` callee is conflict-free). Writes `.run/conflict_callees.json`.
- `tools/derive_canonical_sigs.py` — **new.** One byte-neutral canonical sig per conflict callee: `s32` return
  (void→s32 byte-neutral) + `s32` params (bodies cast int→ptr), arity from the Ghidra-C cache AND asm
  read-before-write `$a0–$a3` (agreed on all 14 cached; 6 stubs call-site-validated). `.run/canonical_sigs.json`.
- `src/ov_SC01_077/ov_SC01_077.c` — **the 20-extern "Phase-17 canonical-sig layer" block** at file top.
  LOCAL on purpose (engine_core.h is shared by 134 overlays; a reach-1 name like func_801809BC is matched
  differently in ov_SC03_096 → would collide). `gen_harvest_targets` + `sig_unify` already read the overlay
  `.c` → auto-wired, no tool change. **Byte-neutral** (ov_SC01_077 still `d19c9580…`, fleet 136/136).
- `docs/matching-cookbook.md` **§16** (corrected) + `docs/hand-matching-process.md` **§8** (new) — the layer
  is BUILT; the "~2× lever" framing was wrong; the gate pipeline is now **draft → `sig_unify` (MANDATORY) →
  `harvest_verify --chunk 1`**; the finding + the leverage analysis + the deferred-wave handoff.

*Earlier this phase (sessions 1–3, already committed `1431b523a`→`f0dd9351e`):*
- `tools/wall_taxonomy.py` + `docs/wall-taxonomy.md` (T1 census); the T3 K&R sig_unify wins (+0.52%);
  `tools/ram_probe.py` + `docs/actor-struct.md` + `.run/actor_*` (T5 actor struct, recovered + live-verified,
  byte-neutral for matching); the guided-hand-matching demo + idioms; `docs/hand-matching-process.md` (created,
  §1 loop / §2 idioms / §3a the 5-move sig playbook / §7 the calibration wave); `tools/ghidra_scripts/
  DecompileFunctions.java` (headless Ghidra-C pre-pass); the calibration Ultracode wave matches (→ `engine_core.h`
  + `config/dedup.us.yaml` + `ov_SC01_077.c`); `.run/harvest_wave_s3.js`, `.run/harvest_targets_s3.json`.

**Local artifacts (gitignored / regenerable):** `.run/ghidra_c/*` (300 cached Ghidra-C), `.run/drafts-s3*`,
`.run/drafts-s4*` (this session's 4-circular drafts — none gated), `.run/permuter/func_8012B8E4/` (probe
scratch, reusable: header+macro.inc → target.o), `.run/harvest_wave_s4.js` + `.run/probe_targets_s4.json`
(the staged 40-target tractable probe), `.run/conflict_callees.json`, `.run/canonical_sigs.json`.

**Tools/packages installed:** None — used the existing Phase-4/6/10/11/12/13 toolchain + venv throughout.

**Verification results (literal):**
- **MILESTONE byte-proof:** `make check-all` → **136 passed, 0 failed of 136** (main `143dbb89…`, resident
  `8e17e02f…`, all 134 overlays); ov_SC01_077 clean-rebuilds `d19c9580…` (R22). The canonical-sig layer is
  byte-neutral fleet-wide.
- **`make report`:** FLEET byte-identical **190,949 / 344,010 = 55.51%** (was 54.48% at phase start; the
  +1.03% banked by the demo + calibration wave across sessions 2–3); 0 NON_MATCHING in any default build (G4);
  `dedup-check` validated, 0 failed.
- **Canonical-sig layer:** census **conflict callees 20→0, blocked targets 24→0** after the layer; `sig_unify`
  rewrites a wrong draft extern to the file-top canonical (verified).
- **The finding (R14/P9):** the conflict wall is **20 callees / 24 targets / 7% of wave reach** (not ~2×). The
  4 reach-134 *circular* conflict callees hand-tried are **all gcc-quirk/regalloc/layout-bound, 0 banked**
  (func_8012B4B8 §10 hoist; func_8012B8E4 75=75 regalloc-swap, permuter probe stalled at base; func_8016A8FC /
  func_80169A4C local-struct-builders). **The high-reach core IS the gcc-quirk tail.**
- `git status`: only `config/`/`tools/`/`src/`/`docs/`/`phase-ends/` tracked; zero ROM-derived/generated bulk
  staged. **No Ghidra DB change this phase** (matching used the cached Ghidra-C + asm; no live MCP writes) —
  R23 no-op; the `ghidra/ db.*.gbf` churn in `git status` is SessionStart-restart rename noise, do NOT commit it.

**Milestone achieved (confirmed by Drew, gate 2):** the phase set out to raise the harness's per-pass yield to
"eureka" and gate an unattended run. **Measured outcome:** the ceiling did NOT rise to eureka — all 5 planned
avenues were byte-neutral/zero except the guided-hand-matching pivot (fleet 54.48%→55.51%); the canonical-sig
layer was built + validated (sig-conflict wall 20→0, byte-neutral 136/136) BUT the byte-proven finding is that
the **real wall is the gcc-quirk tail, not sig conflicts or missing types** — so the **go/no-go is NO-GO on more
brute waves at the current ceiling, and a GO on a fresh compiler-quirk research phase** that attacks the wall
directly (understand gcc-2.7.2 → raise the close-rate → then resume the built, layer-clean wave).

**Next:** **Phase 18 — Compiler-quirk research (understand gcc-2.7.2 to raise the match-% ceiling).** A
Max-effort, **plan-mode** research phase (Tier-1). See "Notes for Future Phases" for the brief. The harvest
infrastructure is BUILT + staged — resume it after the research lands new cookbook idioms.

## Deviations
| Item | Plan | Actual | Reason |
|---|---|---|---|
| The 5 ceiling avenues (T1–T6) | raise per-pass yield to "eureka" | all byte-neutral/zero except T3 (+0.52%) | the premise was wrong — type recovery is byte-neutral; the permuter doesn't transfer (T6) |
| Whole-phase shape | gate an unattended m2c+permuter run | **PIVOT to guided hand-matching** (Drew), then to **compiler research** | hand-matching is the only proven path on struct fns; but its wall is the compiler, redirecting to R17 research |
| The canonical-sig layer | "the ~2× scaling lever; build before the wave" | built + byte-neutral, but the wall is **7%-reach, not ~2×** | the "~2×" was the top-30's in-flight conflicts, since dissolved by banking (R14 sizing correction) |
| Match the 4 reach-134 circular (validate + bank ×134) | bank the highest-value targets | **0 banked — all quirk-bound** | the high-reach core is the gcc-quirk tail; the layer makes them declarable, not matchable |
| The big wave (task 5) | run the Ultracode wave on the 270 | **staged + DEFERRED** to post-research | understanding the compiler raises the wave's ceiling more than running it now (Drew) |
| Emulator struct types | (raised as a possible silver bullet) | **re-confirmed byte-neutral for matching** | matching reads access widths off the asm opcode, not a struct def; types help comprehension only |

## Commit Message
```
feat(phase-17): close — canonical-sig layer built; the wall is the compiler, not sigs; pivot to gcc research (v1.16.0)

- canonical-sig layer (session 4): tools/census_conflict_callees.py + derive_canonical_sigs.py
  -> a 20-extern byte-neutral block atop ov_SC01_077.c (LOCAL, not engine_core.h); census
  conflict callees 20->0, blocked targets 24->0; gate pipeline now draft -> sig_unify (MANDATORY)
  -> harvest_verify --chunk 1; fleet 136/136 byte-identical (R22), 55.51% (no regression)
- FINDING (R14/P9): the conflict wall is 7%-reach not ~2x; the 4 reach-134 circular targets are
  ALL gcc-quirk/regalloc/layout-bound (0 banked); the high-reach core IS the quirk tail; struct
  types are byte-neutral for matching (the wall is gcc codegen, not knowledge)
- leverage analysis: fleet % is function-count-weighted (size adds no %); "unblock many" = the
  layer (declaration, not matching); reach is the lever (already reach-sorted); 247 tractable
  reach-134 stubs ~ +3-4% projected
- GO/NO-GO: NO-GO on brute waves at the current ceiling; GO on a compiler-quirk research phase
  (read gcc-2.7.2 source + Xenogears + the §10/regalloc classes, R17) -> then resume the wave
- docs: cookbook §16 corrected + hand-matching-process.md §8 (the layer + the finding + handoff)
- worklog archived -> phase-ends/logs/Phase17.md (R19); bumps 1.15.0 -> 1.16.0
```

## Rules Added This Phase
| Rule | Reason |
|---|---|
| **None (governance).** Phase 17's lessons are *techniques + a strategic finding*, recorded where they belong (the Phase-8/11/13/15/16 precedent): the **canonical-sig layer** (census/derive tools + the local block + sig_unify-before-gate) → cookbook §16 / hand-matching §8; the **finding** (the wall is the gcc-quirk tail, not sigs/types) + the **leverage analysis** (fleet % is function-weighted so size adds no %; reach is the size-independent lever; matching is independent per function) → hand-matching §8c; the **token-economics insight** (for breadth, isolated agents beat serial main-loop because the main loop's accumulating context is re-read every turn → quadratic; the doc-redundancy is secondary) → memory + effort-map. The existing **R17** (web-research compiler internals) is exactly the Phase-18 mandate; **G3/P9/R14/R22/R26/R27** already govern the rest. | A negative-but-decisive result + a tooling layer produces knowledge, not a new norm of conduct. |

## PhaseEnd Changelog
**v1.15.0 → v1.16.0 — Phase 17 complete (Gen2 phase 9; a go/no-go that PIVOTS the strategy).** The phase
tested 5 avenues to raise the harness ceiling to "eureka" (all byte-neutral/zero), then **pivoted to guided
hand-matching** (Drew) — proven on a demo (4/5) and an Ultracode **calibration wave** (+0.47%), driving the
fleet **54.48% → 55.51%** (+1.03% net, 136/136 byte-identical throughout). The calibration exposed a
**canonical-sig wall** (parallel agents declaring shared callees inconsistently → `conflicting types`), and
session 4 **built + validated the canonical-sig layer** (two new tools + a byte-neutral 20-extern block,
sig-conflict surface 20→0). **The decisive finding** (R14/P9): the wall is only **7%-reach, NOT the "~2×
lever"** it first looked like, and the **4 highest-reach targets are all gcc-quirk/regalloc/layout-bound**
(0 banked, even the permuter stalls) — so the **real wall is the compiler's codegen, not signatures or missing
types** (struct types re-confirmed byte-neutral for matching). The leverage analysis settled the "fewest that
unlock the most" question with data (fleet % is function-count-weighted → size adds no %; reach is the
size-independent lever, already maximised; matching is independent per function → no "magic 5"). **Go/no-go
(gate 2, Drew):** NO-GO on more brute waves at the current ceiling; **GO on a fresh compiler-quirk research
phase** (read the gcc-2.7.2 source + Xenogears-decomp + the §10/regalloc quirk classes, R17) to raise the
close-rate — then **resume the built, layer-clean harvest wave** (staged at `.run/harvest_wave_s4.js`). No new
governance rules (techniques → cookbook §16 / hand-matching §8; the strategic finding → the same; token
economics → memory). All 136 binaries byte-identical; 0 NON_MATCHING linked (G4).

## Notes for Future Phases — Phase 18 research brief (the compiler-quirk avenue, match-% goal)

> **Phase 18 = "Understand gcc-2.7.2 to raise the match-% ceiling."** Max-effort, plan-mode (Tier-1). The wall
> is the compiler, so the lever is understanding it. Prioritised (highest match-% leverage first):

1. **[THE LEVER] Read the actual gcc-2.7.2 source** (`pmret/gcc-papermario`, the PSX 2.7.2.x lineage) — the
   **reload / CSE / instruction-scheduling / register-allocation** logic — to understand the heuristics behind
   the two classes that block the harvest: the **§10 rematerialize-vs-hoist** (a cheap stack/global address kept
   in a callee-saved reg vs recomputed per use) and the **`$s0/$s1` regalloc-order** swap. Goal: turn "not
   source-steerable" into cookbook idioms (C shapes that *trigger* the wanted codegen). One cracked class lifts
   the close-rate across hundreds of functions — more than another brute wave.
2. **[GOLD REFERENCE] Mine Xenogears-decomp** — Square, Oct 1998, **our exact compiler** (gcc-2.7.2-psx + -cdk),
   `gears.toml` presets. The most directly transferable quirk knowledge that exists. Then decomp.me (our
   compiler's scratches), decomp-wiki, maspsx/m2c issues. **sotn is GCC 2.6.3** (wrong era) — methodology only.
3. **[CHEAP DUE-DILIGENCE] Sweep the PsyQ archive** (archive.org, where the 4.0/4.7 `.LIB`s came from) for the
   **real CC1PSX.EXE / ASPSX.EXE** (byte-exact arbitration of any maspsx-emulation doubt, §4.8 deferred) + Sony
   **sample code** (the C idioms that produce specific asm). Won't crack the quirk tail (the real compiler emits
   the same bytes) but is low-cost and may surface idioms.
4. **X2 — treat ALL web content as untrusted DATA** (a prompt-injection doc was served during this project's
   research). Prefer API endpoints; record sources.
5. **The deliverable:** cookbook-ready gcc-2.7.2 idioms (or honest "this class is unsteerable" verdicts) for the
   quirk classes. **Then resume the harvest wave** — the layer + `.run/harvest_wave_s4.js` (40 tractable
   reach-134) + the sig_unify-before-gate pipeline are BUILT and staged; the research only raises their yield.
6. **Carried, lower priority:** the giants (28, reach-134, >150 ins — highest *bytes* but same %, hardest);
   comprehension/emulator field-naming (Gen2 quality, byte-neutral — do when match-% is exhausted).

## Plain-English Recap

We spent this phase trying to make our automatic game-code-matching dramatically more productive. We tried five
different ideas to "raise the ceiling" — all of them turned out to barely move the needle. So we switched to a
hands-on approach: an AI swarm hand-writes the matching code, checked by an automatic bit-for-bit referee. That
worked and pushed us from ~54.5% to ~55.5% of the game's shared code rebuilt perfectly. Along the way we built a
clever helper (the "canonical-sig layer") that we expected to roughly *double* the swarm's output — and we got
it working flawlessly — but when we measured it, the problem it solves turned out to be much smaller than we
thought (it was already mostly solved). The big, honest discovery: **the thing blocking us is the original
1990s compiler itself.** The most valuable, most-reused engine functions get blocked not by anything we don't
*understand* (we read them fine), but by specific low-level choices that ancient compiler made — which register
it used, how it ordered instructions — that our rebuild can't always reproduce from clean code. We proved that
neither better data-structure knowledge nor sharing context between functions changes that; the wall is the
compiler. We also answered your "is there a magic 5 that unlock the rest?" question with hard data: no — because
matching is independent per function, the score counts functions (not their size, so giants give no edge), and
the real leverage (reusing one match across all 134 levels) we already use. **So the smart next move is to stop
out-muscling the compiler and instead *study* it** — read its actual source code and a sister project
(Xenogears) that used the exact same compiler — to learn the tricks that make it produce the bytes we need.
That becomes its own focused phase. Everything we built — the layer, the swarm wave, the tools — is finished and
waiting; we just resume it later with better compiler knowledge. All 136 pieces of the game still rebuild
bit-for-bit; nothing broke.

## 🛑 Stop Here
PhaseEnd written; `CURRENT_PHASE.md` archived → `phase-ends/logs/Phase17.md` (R19). **Drew commits AND pushes**
this PhaseEnd + the Phase-17 session-4 change set (R6/R8 — the 2 new tools, the ov_SC01_077.c layer block, the
cookbook §16 / hand-matching §8 doc updates, this PhaseEnd, the archived log; the `ghidra/ db.*.gbf` churn is
R23 restart-noise — do NOT stage it). No Ghidra DB change this phase (R23 no-op). Gen2 continues — do **NOT**
start Phase 18 here. Start a **fresh session** (effort **Max**, **plan mode**) for **Phase 18 — Compiler-quirk
research** (the brief above). Keep this file forever.
