# CURRENT PHASE — Phase 29: The Family Campaign (cores + members)

**Opened:** 2026-07-16 · **Effort:** Max · **Generation:** Gen2 (21st phase of the arc) ·
**Baseline:** PhaseEnd_Phase28 (v1.27.0) · **Roadmap:** `docs/roadmap-to-100.md` §3 P29
**Plan approved (P3 gate 1):** 2026-07-16. Full plan mirror:
`~/.claude/plans/max-effort-plan-mode-mutable-castle.md` (out-of-repo; this file is the in-repo
authority + crash-recovery log).

**Fleet at open:** 68.9% instr-weighted / 49.5% distinct-code / 83.94% fn-count · 140/140
byte-identical · 0 NON_MATCHING · dedup 1840/0.

**Drew's Phase-Start decisions (2026-07-16):**
- Fable5 = reserved for **NEW wall classes only** (default cheap-Opus + permuter). Window ~7/19.
- Scope = a **longer multi-session campaign** (drive both tracks substantially down before
  closing; ROI-gated on per-session yield floors; velocity + 3 metrics reported each session).

---

## The one question this phase must answer first
The **swing number**: does the legacy PURE-non-jr h_seq tier (~95 families / ~7,993 members /
~478k ins, ~3.6 pp) **template mechanically** (⇒ one exemplar crack banks ×137) or not? Phase-28
measured ~3% as-tooled with 274 genuine gate-DIFF members that are byte-PURE (reloc-only) at the
same vram — so either **(a)** the remap is incomplete (fixable; ceiling ≫ 3%) or **(b)** it's a
TU-context regalloc wall (3% real). **Task 1's disambiguating probe decides it before any yield
arithmetic scales (R14/R35).** Every prior "structural wall" (B2, SC07, pin-crash) resolved to (a).

---

## Standing invariants (every task)
- Whole-binary byte-gate is the **sole arbiter** (G3/P9); match_one/closeness/h_seq are candidates.
- **R22 clean-fleet per banked batch:** `make clean && make extract-all && make check-all` → 140/140.
- `make tools-health` green + fail-closed before matching (corpus · cdecl · audit-binaries(R36) ·
  report/lint/dedup-check).
- **§53 carve law:** `has_mid_jr` families → `jtbl_family_bank.py`, never carve-less `family_sweep`.
- Predictions gate-validated on a SAMPLE before scaling; verify the TOOL before trusting its scan.
- Flywheel: idioms → cookbook + tooling in-session (R16/R30); pivots → decision-log (R31).
- Effort/model transitions **prompted, never assumed** (R26/R27) — STOP + WAIT for the toggle.
- One commit per task after this file's update; Drew pushes (R6/R20). R23 no-op on db.*.gbf.

---

## Task checklist (current-task pointer = ▶)

- [x] **Task 1 — T3b disambiguating probe: build `tools/diff_regions.py` + the swing verdict [Max]** ✅
      **VERDICT: (a) TOOLING — an -O0 compile-flag artifact, NOT a regalloc wall.** The two families
      supplying ~272 of the 274 DIFF (`0x8013c964`, `0x8013c938`) are -O0 functions; `family_sweep
      --hseq` compiled them -O2 (member stub files are -O2). Compiled -O0 they masked-MATCH. 106-member
      sample (nins 2..133): O0-FLAG 45 · already-banked 29 · TEMPLATES 17 · type-lift-plumbing 15 ·
      **REGALLOC 0**. Ceiling ≫ 3%; the pool is back on the table. → `calibration.md` + `decision-log.md`.
      (masked-MATCH = candidate; whole-binary bank is Task 2a's gate, §52b.)
> **🛑 SESSION CHECKPOINT (2026-07-17) — safe to open a FRESH session here.**
> Tree clean, **140/140 byte-identical**, `tools-health` green, dedup 1843/0, 0 NON_MATCHING, main
> `143dbb89`. Fleet: **71.4% instr · 53.3% distinct-code · 86.42% fn-count** (opened at 68.9/49.5/83.94).
> **Tasks 1, 2, 3, 6 DONE.** Remaining: **Task 4** (member harvest behind each crack + grinder
> family-warm-start + the 2 Phase-22 grinder bug-fixes), **Task 5** (fleet Ghidra-C prefetch — needs
> `/mcp`, R23/R29), **Task 7** (burn-down tracker + ROI-gated close).
> **THE HIGHEST-VALUE NEXT MOVE:** bank the 12 preserved giants in `.run/giants/p29t3_README.md` — all
> match_one-MATCH or near, each with its exact blocker and a cheapest-first order (`func_8013FAF8` 312 =
> pure def-sig plumbing is the best value). They cost ~2.6M agent tokens; banking is plumbing, not drafting.
> **Also carried:** the 2 local-type-blocked cores (`func_8014E284`, `func_80137DD4`) need the
> `build_engine_types` type-lift to propagate ×137 (~+276 instances, ~0 tokens).
> **READ FIRST:** cookbook **§55b** (the gate-orchestration law) — `--no-propagate` per group → commit the
> banks → THEN one targeted `dedup_propagate --addr` (~233s/core). It is the distilled cost of ~3.5h I
> lost this session.

- [x] **Task 13A — deterministic residual→class classifier + the corpus it reads [Max]** ✅ 2026-07-21
      `residual_class.py` + `autopsy.py` + `corpus.is_o0`; grinder targeting wired (1,303→78). FINDING: only
      **75/972 (7.7%)** of the grinder-admissible backlog is permuter-shaped — the problem was TARGETING, not
      a missing transform. R22 140/140. Cookbook §60 + decision-log + SETUP.
- [x] **Task 13B — directed permuter run + the plateau autopsy [Max]** ✅ 2026-07-21
      Ran the targeted grinder over all 77 permuter-bucket candidates: **24 wins → 21 banked** (27%), 3
      won-but-gate-rejected as PLUMBING. `func_80141B90` propagated **×138**. Then the `length` expansion:
      probe = 20 targets, **1 win** — `tail` 1/6, `partial` **0/12**. **AUTOPSY VERDICT: ZERO
      missing-transforms.** The partial plateaus are WRONG DRAFTS (byte-read: `(u32)(x^1)`→`xori` vs the
      target's `sltiu`=`!x`; a draft storing to `arg0+8` vs a target storing to a global). So the §7
      "extend the mutation set" bucket came back EMPTY for this class, and the permanent win was the
      opposite move — a tighter ADMISSION rule: `_drift_route` now needs `|Δ|≤2` AND `explains=="tail"`
      (length pool 339→**34**, permuter bucket 389→**84**), plus a proportional `SIZE-MISMATCH` test.
      Cookbook **§60a/§60b**. `permuter_weights` needs no extension.
- [~] **Task 14 (stage 1 DONE) — the ARITY pre-pass wired into `gate_stage` [Max]** ✅ 2026-07-21
      **DIAGNOSED, not assumed:** the 12-draft probe reported the SAME label for 10 of 11 failures
      (`conflicting types for built-in function 'memcpy'`) — the §58 red-herring, a WARNING from an
      unrelated TU position. Splicing three top-reach failures and reading real cc1 stderr gave
      `conflicting types for func_XXXX` **3/3** + a second class `redefinition of 'struct V8'`.
      The first is the loose-typing ARITY conflict: a banked shared caller macro in `engine_core.h`
      declares the fn with FEWER params than its byte-true def takes. `fix_arity_callers --any-proto`
      already fixed it and was simply **never wired into the ladder** (only `family_sweep` had §57).
      **MEASURED: 2 of 7** top integration candidates banked (`func_8016EFC8`, `func_80164418`, both
      reach-138) vs the **1/12** old-ladder baseline. R22 **140/140**; tools-health OK (dedup 1848/0).
      **⚠️ INCIDENT — I BROKE 138/140 AND R22 CAUGHT IT.** Pairing `--apply --any-proto` with `--revert`
      for the unbanked drafts corrupted decls fleet-wide: `--revert` only inverts a PLAIN apply
      (`()`→`(void)`), so an unbanked fn whose real decl was `extern void func_801708B0(void *a0)` came
      back as `(void)` — in `engine_core.h` (all 138 overlays) + 6 sites in ov_SC01_077's own sources.
      **`harvest_verify --binary ov_SC01_077` said BYTE-IDENTICAL and was RIGHT about that binary** —
      the other 137 were broken and structurally invisible to it. Diagnosed to the exact lines, repaired
      precisely (both legitimate rewrites kept), **nothing ever committed**. Root cause fixed: the ladder
      now SNAPSHOTS every file the pre-pass touches and undoes by **restore + re-apply-for-banked-only**.
      **NEW HARD CONSTRAINT (cookbook §61):** *any ladder stage mutating SHARED state must be undone by
      snapshot restore, never an inverse transform, and validated FLEET-WIDE (R22), not by the
      per-binary gate that authorised it.* §55b's law one level down. Also fixed: the first wiring passed
      only `--drafts` (the narrow-param FILTER) without the required `--funcs`, so the stage exited
      `no funcs given` as a SILENT NO-OP and the gate reported 0/6 as if diagnosed — `sh()` does not raise
      on non-zero exit; there is now an explicit rc check.
      **▶ STAGE 2 (not started):** the `redefinition of 'struct <T>'` type-lift/uniquify class — 3 of the
      5 remaining failures also carry a `(void)` header decl the arity pass alone does not clear. It edits
      `engine_types.h`, so it INHERITS the shared-state constraint above by default.
- [x] **Task 15 — §61c diagnosis: the blocker is REFUTED; `func_80135A4C` banked ×1 [xHigh]** ✅ 2026-07-22
      Two independent `make clean && extract-all && check-all` runs → **140/140** with the bank applied
      through the single-function automated jtbl path. The path IS reproducible from committed config +
      source; the prior 139/140 was the *batch* `_jtbl_prep` residue (fixed in the same commit that named
      the blocker). jtbl banking is UNFROZEN, one draft per `harvest_verify` invocation. Cookbook §61c
      REFUTED-block + decision-log (R31).
- [ ] ▶ **Task 14 stage 2 / close — type-lift stage (§19/§57a/§59) OR begin the phase close [Max]** — the
      corrected frontier says every remaining lever is ≤~1pp at low measured conversion; Task 7's
      ROI-gated close is the honest alternative. (Superseded spec below.)
- [ ] **(superseded) Task 14 — enrich `gate_stage`'s ladder (§57/§59) so more wins auto-integrate + grinder auto-R22
      [Max]** — the permuter-automation program's final stage (Tasks 12→13→14). Justified as the SHARED
      BANKING SPINE, not as a bucket: today 3 of 24 permuter wins were lost to plumbing (12.5% of work
      already paid for in CPU), the 12-draft probe banked 1/12, and crack-wave-4's 6 -O2 cores ×138 were
      explicitly deferred to this ladder. **Corrected ceiling for the integration bucket alone: 0.84pp**
      (NOT the 3.2pp I first quoted — see the valuation correction below). Start by splicing 6–10 failures
      individually and reading real cc1/ld stderr: the shared `conflicting types for built-in function`
      label is a §58 red-herring, so the causes are UNDIAGNOSED.
- [ ] **Task 2 — Act on the verdict [Max/xHigh]** — **branch = 2a (tooling).** Build the -O0-cluster
      split rollout (adapt `rollout_whale_o0.py` → per-overlay `[0x13410,c,<ov>_o0]` carve, -O0 Makefile
      rule) + teach `family_sweep --hseq` per-member opt-level awareness; WHOLE-BINARY gate one overlay
      (convert the verdict to a banked fact), then fleet + the type-lift sweep. `member_adapt.py` NOT
      needed for this pool. Originally: (2a) extend `family_remap.symbol_map` + re-run
      the legacy-PURE `family_sweep --hseq` (the ~478k-ins mechanical win); OR (2b) build
      `tools/member_adapt.py` (exemplar→member delta engine + per-member delta briefs); OR both.
- [ ] **Task 3 — Core-crack track: fresh exemplar + B3 near-miss cracks [Ultracode/xHigh/Max]** —
      top substantial stub exemplars (non-jr `0x80176734`/`0x80176218`/`0x8013faf8`/`0x8014d820`/
      `0x801670e4`/`0x80140958`; jr via `jtbl_family_bank` `0x8013f350`/`0x80131340`/`0x80159c84`/
      `0x8013c414`) + B3 high-close near-miss cores (`func_8014F4C0` 127, `func_80137DD4` 107,
      `func_8014E284` 83, `func_80177940` 65, `func_801387B8` 50, `func_8014ADE0` 19,
      `func_801325B8` 4). FRESH re-drafts only (0/958 stored are dead). Add a `family_sweep`
      `has_mid_jr` interlock. Fable5 for NEW walls only (prompt Drew).
- [ ] **Task 4 — Member harvest behind each crack + grinder family-warm-start [xHigh/Ultracode]** —
      propagate members per Task-2's mechanism; build the grinder family-warm-start + 2 Phase-22
      bug-fixes (split-file-blind lookup; churn-without-blacklist).
- [~] **Task 5 — Ghidra-C prefetch: SCOPED BY MEASUREMENT, then executed per-overlay [Max]** 2026-07-21
      **The frontier, measured honestly (and it corrected me twice):** remaining = **2,873,658 stub ins =
      22.0pp** (resident+138 overlays; main is outside this denominator). By band: **substantial 80–1000
      ins = 10,934 fns / 12.84pp** · mid 16–79 = 27,952 / 8.60pp · behemoths >1000 = 14 / 0.28pp ·
      small ≤15 = 2,700 / 0.25pp.
      **I first claimed Task 5 "gates 12.84pp". It does not.** The substantial mass is **1,398 distinct
      h_seq families**, and splitting them by whether their exemplar was ever attempted:
      **340 families / 7.72pp are ALREADY-ATTEMPTED or WALLED** (the top-12 by value are exactly our known
      set — `func_8013C414` -O0, `func_8014D820` close-11, `func_801412A8` permanent wall, `func_8013B83C`/
      `func_8015B950` cracked-but-deferred, `func_8013D53C` 14/137, `func_8013BD74` §8e-2 …), i.e. they need
      the DEFERRED TOOLING fixes (-O0 rollout, jtbl §8c/§8e-2, def-side wall), NOT fresh drafting.
      **1,058 families / 5.40pp have a never-attempted exemplar — the true fresh fuel.** Of those:
      **48 families / 0.62pp already have a cached member (draftable NOW, no MCP)** and **877 families /
      3.10pp have none** (median **1 member** → overlay-UNIQUE code, which is exactly why it was never
      cached: the big 138-member families all live in ov_SC01_077 and were cached+drained by waves 1–4).
      **So the prefetch is per-overlay, not fleet-wide.** Greedy cover: importing **ONE overlay
      (`ov_SC06_018`) unlocks 54 fresh families = 1.59pp**; imports 2–8 add only +0.59pp combined
      (ov_SC03_015/ov_SC07_006/ov_SC03_124/ov_SC06_029/ov_SC02_011/ov_SC03_094/ov_SC04_011), leaving a
      632-family long tail. Ranked ready-list: `.run/autopsy/t5_ready.json`.
      **EXECUTED:** MCP stopped (R23, save succeeded) → `ghidra_import_raw.sh …/SC06.CD.dir/FILE_018.dir/
      0.4.dec 0x80128158 ov_SC06_018` → `DefineFunctions` → `DecompileFunctions` over the **101 uncached
      substantial stubs** (`.run/ov_SC06_018_funcs.txt`, 17,723 ins; largest `func_80191C50` 710,
      `func_8019059C` 673, `func_8018F694` 478). **R29: Drew must run `/mcp` after the server restarts.**
- [ ] **Task 6 — Mechanical mass: tiny-IMM mega-pools + permuter backlog sweep [Ultracode/permuter]**
      — `0x80131eec` (2,887×15) + `0x80130d0c` (2,679×15) via `imm_map`; the 550 close-1..4
      backlog drafts via grinder/`permuter_ils`.
- [ ] **Task 7 — Burn-down tracker + velocity/3-metric report + ROI-gated close [Max]** — close
      when per-session yield across both tracks floors out; Roadmap delta; hand P30 an honest frontier.

**OUT of scope:** parallel gate farm (bulk_harvest already is it) · family-adapt fine-tune (bounded,
conditional) · main-EXE/B9 + GLM/B6 + resident's 14 walls (P30) · behemoths B7 + walls B8 (P31).

---

## Blockers
(none — Arm B substantial-band sweep running in background as of 2026-07-16)

## Task 2 progress (in flight)
- **Verdict → branch 2a (tooling).** Sized the fix: **Arm A** (-O0 cluster carve) = 9 families /
  1,233 stub members / ~24k ins (~0.6pp), needs a per-overlay -O0 carve tool (adapt
  `rollout_whale_o0.py`; the -O0 cluster 0x13410..0x14834 is deferred-since-Phase-19). **Arm B**
  (-O2 type-lift sweep, EXISTING `family_sweep --hseq --no-preclassify`) = 398 families / 7,541 stub
  members / **~520k ins (~4pp)** — the ROI winner; unbanked pool concentrates in the 4 newest (SC07)
  overlays.
- **Arm B gate-probe (10 families): BANKED 32/40 = 80%** — gate-validated (R14). Substantial band alone
  = 76 banks (size-dependent: substantial is pin/drift-limited, 1,799 pinned skips). Comprehensive
  **`--band all --allow-pins`** sweep then banked across **~140 overlays (891 src files)** before a
  **SIGTERM (exit 143)** interrupted it mid-gate (during/after ov_SC07_006 346/570). Triage: 3 clean
  single-binary rebuilds all BYTE-IDENTICAL → the incremental banks survive R22.
- **✅ ARM B CHECKPOINT COMMITTED (2026-07-16).** R22 clean-fleet verify = 136 PASS / 1 FAIL; the
  FAIL (ov_SC07_010, the SIGTERM mid-gate partial) reverted → byte-identical. **3,407 member-matches
  banked** across 136 overlays. `make check-all` → **140/140 byte-identical**; dedup-check 1840/0;
  audit-binaries OK; audit-cdecl green. **Fleet: instr-weighted 68.9→70.2% (+1.3pp) · distinct-code
  49.5→51.9% (+2.4pp) · fn-count 83.94→84.73% (+0.79pp)**; 0 NON_MATCHING (G4).
- **⚠️ LESSON:** `--band all` sweeps are too long for one background pass (SIGTERM'd). Future Arm B
  runs go band-bounded + committed-per-batch (resumable). The comprehensive sweep still had residual
  FAILED members (pin/drift/plumbing) not yet re-attacked.
- **✅ ARM B TAIL FINISHED (2026-07-16).** Band-bounded `family_sweep --hseq --allow-pins` in 3 clean
  bounded passes (substantial 53 + mid 372 + tiny 323 = **748 member-matches**), the SIGTERM lesson applied
  (each band completed exit 0). All 748 confined to the 4 undermatched SC07 tail overlays (the `files=1`
  ones): **ov_SC07_010 897→516 (+381) · ov_SC07_011 797→436 (+361) · 006 457→454 (+3) · 007 595→592 (+3)**.
  Verified pure-reduction (0 NEW stubs, 0 dup INCLUDE_ASM). 006/007's residual is jr-families (§53 carve →
  Task 3) + plumbing/DIFF — the plain-sweep tail is drained. **R22 clean-fleet 140/140 byte-identical;
  audit-binaries OK; dedup-check 1840/0; main 143dbb89.** Fleet: **instr 70.2→70.4% · distinct-code
  51.9→52.3% · fn-count 84.73→84.94%**; 0 NON_MATCHING linked (G4).
- **✅ ARM A: swing verdict CONFIRMED as a BANKED FACT (2026-07-16).** Built `tools/rollout_o0_cluster.py`
  (the -O0-cluster carve, adapting `rollout_whale_o0.py`) + the Makefile `O0_CLUSTER_OBJS` -O0 wildcard.
  On **ov_SC07_010 the carve is byte-neutral and `family_sweep --hseq` banked 9/9 of the -O0 exemplar
  families' members whole-binary** (R22 clean-fleet 140/140) — so the -O0 cluster members DO bank at -O0,
  not just masked-MATCH (§52b candidate → fact; Phase-20's "func_8013B7AC overlay-local" also refuted).
  **BUT the fleet-scale carve hits a splat-integration wall:** the same carve on 006/007/011 byte-shifts the
  whole image (+0x20 data-symbol shift, 34% diff) from a CLEAN build — a splat `%lo` re-disassembly
  sensitivity (boundaries verified correct), the Phase-20 "-O0 split infra" wall now characterized. **Full
  -O0 fleet rollout (~1,233 / ~0.6pp) DEFERRED** on ROI: 3/4 sampled overlays walled + 134 overlays have the
  cluster inside the jr_801380E0 carve + bigger levers wait. Details → `docs/decision-log.md`. (c) opt-level
  awareness is moot — the -O0-ness is per-FILE via the Makefile rule; `family_sweep`/`stub_map` already
  route to the carved split. Hindsight fix logged: mirror the whale's shared-header `_o0b` shape.
- **TASK 2 SUBSTANTIVELY COMPLETE.** Arm B tail (748 members) + Arm A (verdict = banked fact). NEXT: **Task 3
  (core-cracks + B3 near-misses)** and/or **Task 6 (tiny-IMM mega-pools ~5,566 members)** — the bigger levers.

---

## Per-task log
*(appended after each task; the crash-recovery trail — becomes `phase-ends/logs/Phase29.md` at close, R19)*

- **2026-07-18 — jtbl 8-align fix OPENED (Fable5 Max, plan approved).** Plan mirror:
  `~/.claude/plans/fable5-max-set-jtbl-ancient-marble.md`. **⚠️ CORRECTION of the session-2 checkpoint's
  half-pin (R35/R14 — do NOT re-trust it): the claim "cc1 AND maspsx both emit the jtbl `.align 2`" is
  INVERTED, and both preserved probes (`.run/probe_jtbl_{cc1,maspsx}.s`) are VACUOUS (empty `j $31` fn, no
  jtbl).** True chain (byte-grounded this session): **(1)** Sony cc1 emits `.align 3` before EACH jump table
  in `.rdata` (clean `jr_8012ACE0.o` has `.rodata` sh_addralign=8 w/ a single 51-entry table); **(2)** maspsx
  passes `.align` through VERBATIM (`maspsx/__init__.py:872-873` output catch-all; the L435-437 `continue` is
  an inventory-only pass — `jtbl_carve.py:132`'s "maspsx drops .align" docstring is FALSE); **(3)** `as` bakes
  the pad SECTION-RELATIVE (intra-object, linker can't remove); **(4)** placement is always tight
  (`SUBALIGN(2)` fleet-wide + ld_interleave `ALIGN(.,4)` — the 0xb07dc 4-mod-8 carve proves it); **(5)**
  original semantics: separate TUs pack TIGHT (078→144 abutment), intra-TU tables 8-align w/ real zero-word
  pads (tail2.data.s 8158/8170/8188/81A0). **THE BUG:** merging originally-separate TUs into one decomp TU
  fires an intra-TU `.align 3` where the original had a tight TU boundary → +4 at rodata 0xCC → image-wide
  %lo shift (build_g2.log SHA1 FAIL). **THE FIX (red-team-hardened, empirically pre-verified):** pad-spec
  filter `tools/jtbl_rodata_pads.py` (post-maspsx, per-object `JTBL_PADS` make var, fail-loud guards) +
  `jtbl_carve` interval-arithmetic specs + merge relaxation (gap 4 must be verifiably zero) + revert/stale-.o
  coverage + `jtbl_family_bank` stub_file uniqueness assert (yesterday's ladder failure spliced into a stale
  `_a.c` duplicate stub — byte-witnessed in bank_func_80131340.log). Isolation is NOT general (as aligns
  section-relative; a 4-mod-8-start multi-table object mis-pads internally) — kept as NON-CONTIGUOUS fallback.
- **✅ 2026-07-18 — jtbl §8e fix BUILT + fleet-neutral (Steps 1-3 of the approved plan).** Honest probes
  persisted (`.run/probe_jtbl/verdict.md` + objdumps; the vacuous pair deleted): cc1 `.align 3` per table
  (2 tables → 2 aligns, byte-listed), maspsx verbatim passthrough in situ, **the +4 pad materialized at object
  rodata 0xCC** (0xE4 verbatim), as-controls (bare rodata → Al=4; +`.align 3` → Al=8). Built: NEW
  `tools/jtbl_rodata_pads.py` (spec-driven align→pad-bytes replacement; guards byte-tested rc=1 ×3; pad=4
  direction synthetically proven), `jtbl_carve.py` (spec-aware merge: gap∈{0,4-zero-checked-in-payload},
  interval-arithmetic pads CARRIED never re-derived, `JTBL_PADS` target-var emission into overlays.mk +
  revert() restore + stale-.o invalidation, honest docstring), Makefile `$(if $(JTBL_PADS),…)` stage +
  env-shield default, `jtbl_family_bank.stub_file` duplicate-stub fail-loud. **Object-layer byte proof:**
  filtered `.rodata` = 0xE0, table 2 TIGHT at 0xCC = the merged carve span exactly. Dry-run build_carve →
  span `0xaff20..0xb0000` spec `[0,0]` as designed. **R22 clean-fleet WITH the fix wired: 140/140
  byte-identical, tools-health green (dedup 1846/0, C1 234205/234205), zero new banks — fleet-neutral.**
  Flywheel captured in-session (R30): cookbook **§8e** + §8a/§8a-pad corrections, decision-log entry,
  SETUP.md row. NEXT: Step 4 — bank func_80131340 ×1.
- **✅ 2026-07-18 — func_80131340 (424) BANKED ×1 — the first 4-mod-8 non-first jtbl bank ever (§8e live).**
  Draft spliced at the L1635 slot (stub 0, def 1); `jtbl_carve --func func_80131340` → merged span
  `0xaff20..0xb0000` + `JTBL_PADS := 0,0` (stale-.o auto-invalidated); `make extract` + whole-binary gate
  → **[ OK ] d19c9580 == check** (build log `.run/bank_80131340_build.log`). Production object proof:
  `.rodata` 0xE0 / Al=4 / table 2 TIGHT at 0xCC — the filter ran in the real pipeline. NEXT: Step 5
  — ×137 family sweep (`jtbl_family_bank --raw`).
- **✅ 2026-07-18 — func_80131340 family COMPLETE ×138 (the §8e mechanism's ×N proof): 137/137 siblings
  BANKED, 0 failed.** 3 bounded chunks (50+50+37, committed per chunk `commit:0680`/`commit:0681`/`commit:0682`),
  every sibling whole-binary gated, per-sibling §8e carve+`JTBL_PADS` auto-derived from each overlay's own
  island addresses. **R22 clean-fleet: 140/140 byte-identical; tools-health green; dedup 1846/0.**
  Fleet **72.1→72.5% instr · 54.0→55.0% distinct-code · 86.61% fn-count** (~+58.5k ins from one family —
  vs the B2 precedent's 102/115 this ran 138/138). NEXT: Step 6 — the 3 remaining giants
  (59C84 → F350 (pad=4 spec case!) → C414 -O0).
- **✅ 2026-07-18 — THE JTBL 8-ALIGN CAMPAIGN COMPLETE (Steps 4-7): 4 giants ×1 + 3 families swept; fleet
  72.1→73.4% instr (+1.3pp — the checkpoint's +1..1.5pp ceiling hit in one session).**
  **Banked:** `func_80131340` (424) **138/138** (0 fail) · `func_80159C84` (337) **134/138** (isolate path +
  the FIRST pad=4 spec; 4 SC07 residuals named) · `func_8013F350` (490) **138/138** (0 fail — the 4-table
  `[0,0,4,0]` span, `tables=` persistence, `--like` structure transfer ×137, §30#2 fleet-widen ×267) ·
  `func_8013C414` (329, -O0) **×1** (family name-deferred: uniform -O2 gate-fail — rides the Arm-A -O0-cluster
  rollout wall, NOT codegen). ≈ **+165k ins** total. **BATCH R22: check-all 140 passed, 0 failed of 140;
  tools-health green; dedup 1846/0; 0 NON_MATCHING.** Fleet **73.4% instr · 56.9% distinct-code · 86.69%
  fn-count** (session opened 72.1/54.0/86.57).
  **Sweep lessons distilled (§8e-2, R30):** the CLEAN-DRAFT law (59C84 went 3/8→100% once the exemplar's
  canonical-form reconciles were mirrored into the --raw draft — diagnosed by ONE failed-sibling re-run, §55b);
  zero-word spec rule + `tables=` persistence + `--like` role-transfer (built after the F350 pre-§8e merged-double
  archaeology); the SC07 `_o2b` composition class (fail-loud, 4 overlays); commit-per-chunk sweeps with
  auto-commit chaining. Tooling: `jtbl_carve` span-structure engine + `jtbl_rodata_pads` filter +
  `jtbl_family_bank --like`/stub-uniqueness (commits `commit:0678`..`commit:0696`).
  **Burn-down residuals (named):** 4× SC07 59C84-members (o2b span composition) · 137× C414 members (-O0
  rollout dependency) · the -O0 cluster rollout itself (Arm-A splat wall). Ghidra-C/Task-5, permuter
  backlog/Task-6-tail, Task-7 ROI-close remain the open phase items.

- **2026-07-16 — Phase opened.** Session Start Protocol complete (all 28 PhaseEnds + roadmap +
  calibration + decision-log read). 3 Explore surveys grounded the plan (tooling state, frontier
  data, idiom bank). Plan approved at Max/plan-mode. Beginning Task 1.
- **2026-07-16 — Task 1 DONE (the swing RESOLVED = (a) tooling).** Built `tools/diff_regions.py`
  (composes `family_remap.remap_hseq` + `match_one` + `masked_diff`; auto-detects the exemplar's -O0
  opt from the Makefile rules). Byte-proof: the 274-DIFF pool is dominated (~272) by two -O0 families
  the sweep compiled -O2; at -O0 they masked-MATCH. 106-member sample across nins 2..133 →
  **0 REGALLOC walls**; all failure modes recoverable tooling (-O0 flag / already-banked / template /
  type-lift plumbing). Verdict + byte evidence → `docs/calibration.md` (swing RESOLVED section) +
  `docs/decision-log.md` (R31). §52b caveat: masked-MATCH is a candidate — Task 2a whole-binary-gates
  the -O0 split rollout. Run artifacts in `.run/probe29/`.
- **2026-07-16 — Task 2 (Arm B tail) DONE.** Resumed the interrupted comprehensive `--band all` sweep as
  3 band-bounded passes (substantial/mid/tiny, `--allow-pins`, each exit 0 — the SIGTERM lesson) →
  **748 member-matches banked** across the 4 `files=1` SC07 tail overlays (010 +381, 011 +361, 006 +3,
  007 +3), each whole-binary-gated by `harvest_verify` (G3/P9). R22 clean-fleet **140/140 byte-identical**;
  fleet instr 70.2→70.4% / distinct 51.9→52.3% / fn-count 84.73→84.94%; audit-binaries OK, dedup 1840/0,
  main 143dbb89, 0 NON_MATCHING (G4). Verified pure-reduction (0 new/dup stubs, R14/H5). Logs
  `.run/armB_tail_{substantial,mid,tiny,checkall}.log`. NEXT: Arm A (-O0 cluster carve) + item (c).
- **✅ 2026-07-16 — Task 6 tiny-IMM mega-pools CRACKED (+4,801 members).** `0x80131eec` (2887) +
  `0x80130d0c` (2679) went from **1/4966 (0.0%)** to **pool1 2331/2470 (94%) + pool2 2470/2496 (99%) =
  4,801 banked**. Root cause (byte-proven after 3 masked-metric mis-reads — R14/R35, see decision-log):
  NOT a symbol-definition gap (my `commit:0665` scout was WRONG) — it's a **def-signature conflict**:
  `engine_core.h` forward-declares the member (`extern void func_8015FAAC(s32 *a0)`, a shared fn calls it)
  while `family_remap` copies the EXEMPLAR's sig (`void *a0`) → `conflicting types` → the member TU never
  compiles (invisible to standalone diff_regions/match_one AND to --reconcile). FIX: **new
  `family_sweep --fix-def-sig`** (`header_sig_map` + `reconcile_def_sig`, 1005 mapped fns) rewrites the
  member draft's def sig to the shared-header canonical — byte-neutral, gate-arbitrated (G3/P9); one member
  hand-verified byte-identical first. **R22 clean-fleet 140/140**; pure-reduction (0 new/dup stubs);
  fleet **instr 70.4→71.0% · distinct 52.3→53.2% · fn-count 84.94→86.30%**; dedup 1840/0; 0 NON_MATCHING.
  §54 cookbook + R31 decision-log. The 4th "reproduce the build step" instance (§53-carve, -O0-flag,
  now the member's canonical DECLARATION). `--fix-def-sig` likely should be default-on for the h_seq path.
- **✅ 2026-07-17 — Task 4 giants #2 (func_8014F4C0) BANKED + PROPAGATED ×134.** func_8014F4C0 (141) banked
  ×1 in ov_SC01_077_after.c (its earlier "gate reject" was pure §55b propagate-damage — it gated clean on the
  healthy tree, no fleet change needed). h_exact family → `dedup_propagate --addr 0x8014F4C0 --recover`
  (ov_SC01_000 straggler; --recover reconciled conflicting caller externs, kept it) = **134 overlays byte-identical
  after propagation**, +1 dedup group registered. R22 clean-fleet **140/140**; ~+19k ins. §55b honored (targeted
  --addr, fail-closed, committed as its own batch). **GIANT TAXONOMY (the session's key finding):** the 12 giants
  split into **NON-jtbl** (func_8013FAF8, func_8014F4C0 — bank clean once the tree is healthy + propagate ×137 via
  macro/h_seq alone) and **jtbl** (func_80131340/func_80159C84/func_8013C414/func_8013F350 — each needs a per-overlay
  jtbl carve ×137 AND hits an 8-align tooling gap). **func_80131340 DEFERRED with a precise root cause:** gcc emits a
  non-first jump table `.align 3` (8-aligned) but the original island packs it 4-aligned → +4B padding → island +4 →
  every downstream data symbol shifts → %lo relocs break image-wide (+5B, 3077 diffs, byte-proven). A jtbl_carve
  8-align/isolation fix would unlock ~4 giants × ~137 members — a real lever, flagged as a distinct tooling task.
- **✅ 2026-07-17 — func_8013FAF8 PROPAGATED x137 (h_seq family sweep) → giant DONE fleet-wide.** h_seq (not
  h_exact, so dedup_propagate refused it: reach<2); path = `family_sweep --hseq --only 0x8013FAF8 --allow-pins`
  (per-overlay symbol remap). First sweep 0/137: family_sweep copies the exemplar's extern block VERBATIM and my
  hand-crafted exemplar had 4 callee externs diverging from the fleet-canonical (func_8005A600 void→s32,
  func_80024054 s32→void*, func_80137D08 s32*→int, func_8013AB54 s32*→s32) → every member `conflicting types`.
  Aligning those 4 in the COMMITTED exemplar .c to the member-consensus form (byte-neutral; ov_SC01_077 stays
  byte-identical) → re-sweep 137/137 banked, 0 failed. +312 ins x137 ≈ +42.7k ins. R22 clean-fleet 140/140.
  Cookbook §56b (exemplar-externs-must-be-canonical for h_seq; contrast dedup_propagate --recover which
  auto-reconciles CALLER externs). Both NON-jtbl giants now fully banked+propagated (func_8013FAF8 x137,
  func_8014F4C0 x134); the 4 jtbl giants stay deferred on the 8-align carve gap.
- **✅ 2026-07-17 — 2-core type-lift + propagate x138 each (func_8014E284 108, func_80137DD4 129).** Both were
  banked x1 in Task 3 but `dedup_propagate` skipped them ("not self-contained: local types"). Lifted `EntSC01077`
  (func_8014E284) + `P_TAG_80137DD4` (func_80137DD4) into `src/shared/engine_types.h` (fleet-included via
  engine_core.h) and **inlined func_80137DD4's file-local `#define OTE`** into the body (byte-neutral macro
  expansion, re-evaluated per use to preserve codegen) → both self-contained → `dedup_propagate --recover` =
  **138 overlays byte-identical, 0 stragglers, 2 new dedup groups**. ~+32.7k ins. R22 clean-fleet 140/140;
  dedup 1846/0; C1 234205. Cheap carried Task-3 win closed (§55c local-type cap lifted for these 2).

> **🛑 SESSION-2 CHECKPOINT (2026-07-17) — supersedes the checkpoint above; safe to open a FRESH session here.**
> Tree clean, **140/140 byte-identical**, `tools-health` green, dedup **1852/0**, 0 NON_MATCHING.
> Fleet **72.1% instr · 54.0% distinct-code · 86.57% fn-count** (session opened 71.4/53.3/86.42 → **+0.7pp instr**).
> **This session banked ~94k ins across 4 fns ×~137 overlays:** func_8013FAF8 (312) ×137 + func_8014F4C0 (141) ×134
> (the 2 NON-jtbl giants, fully done) + func_8014E284 (108) ×138 + func_80137DD4 (129) ×138 (the 2-core type-lift).
> Commits `commit:0673`, `commit:0674`, `commit:0675` + the type-lift commit (Drew pushes). Cookbook **§56/§56b** added.
> **THE TEED-UP NEXT TASK (Drew-directed): the jtbl 8-align tooling fix** — unblocks the 4 remaining giants
> (`func_80131340`/`func_80159C84`/`func_8013C414`/`func_8013F350`), ceiling ≈ **+1 to +1.5pp instr** (biggest lever
> left). Root cause HALF-PINNED (do not re-derive): cc1 AND maspsx both emit the jtbl `.align 2` (correct) — the
> +4B 8-align pad is a downstream `as`/`ld_interleave` artifact. **START from `.run/giants/p29t3_README.md`** (the
> STATUS section — full findings, probes at `.run/probe_jtbl_*.s`) + cookbook §8/§8a. Step 1: pin `as` section-align
> vs interleave; Step 2: fix jtbl_carve to pack the non-first jtbl 4-aligned; Step 3: prove x137 on func_80131340
> before scaling. Also open: Task 6 permuter backlog, Task 5 Ghidra prefetch (needs /mcp), Task 7 ROI-close.
- **2026-07-17 — Task 3 core-crack wave: 13 agents → 7 MATCH → 5 BANKED ×1.** Ultracode `worker_wave`
  (13 xHigh drafters over 6 cores 260–371 ins + 7 B3 near-misses 100–141 ins; all had cached Ghidra-C).
  Wave hit a usage limit at 2/13, **resumed cleanly** (cached agents replay) → **13/13 done: 7 match / 6 near**.
  **BANKED (whole-binary, R22 clean-fleet 140/140):** `func_8014ADE0` (139), `func_8014E284` (108),
  `func_80137DD4` (129), `func_801325B8` (113), `func_801387B8` (100). **Near (2 of the 7):**
  `func_8013FAF8` (312 giant — def-sig s16/s16 vs fleet-canonical s32/s32 plumbing), `func_8014F4C0`
  (byte-verified in-TU; a decl conflict `fix_arity_callers` didn't resolve). Fleet 71.0% instr / 53.3%
  distinct / 86.30% fn-count. **NEW levers to distill (R16/R30):** §49-variant birthing-boost suppression
  via reg_n_sets 1→2 (`func_801325B8`); sched1 birthing/LUID + `cc1 -dL` movable introspection
  (`func_80177940`); switch-tree vs jtbl CASE_VALUES_THRESHOLD (`func_801387B8`).
- **⚠️ 2026-07-17 — THREE tooling traps hit in the T3 gate (all mine; ~3.5h lost, no data lost):**
  (1) **`gate_stage` propagate is FLEET-WIDE** (`dedup_propagate --auto-from`), so running gate_stage
  per-src-group ran it 4× redundantly; 3 hit the 3600s timeout → **partial propagate damage: 90/140
  overlays broken, 887 files, engine_core.h +561**. → **Always `--no-propagate` per group, then ONE
  targeted `dedup_propagate --addr <banked>` at the end.** (2) **A reverted src needs a RE-EXTRACT**
  (R22 corollary): `git checkout -- src` left `asm/` in the banked state (no `.s` for banked fns) →
  `corpus.CorpusError: 5 stub(s) have NO .s on disk` (R34's second oracle caught it — working as designed).
  (3) **`gate_stage`'s default `.run/harvest_verified.txt` ACCUMULATES across runs and its CLI exposes no
  `--verified-out`** → it reported a **phantom `banked:1`** for a function still stubbed in src (stale
  residue of a reverted run). **Trust the SOURCE, not the report** (R32/R35 class — still armed).
  **Sequencing law learned: COMMIT the cheap verified banks BEFORE the expensive propagate**, else every
  propagate failure takes the banks with it.
- **✅ 2026-07-17 — PROPAGATE DONE + a self-correction (R14/R35).** Dry-run plan = 3 of 5 cores
  self-contained (`0x8014ADE0`/`0x801325B8`/`0x801387B8`, 138 members each ≈ **414 instances**); 2 skipped
  (local types → needs the `build_engine_types` type-lift). Straggler `ov_SC03_093` forces `--recover`
  (h_exact share is all-or-nothing). **CORRECTION: my earlier "needs ~2h+" was WRONG** — that timing came
  from propagating into the tree still carrying the killed-`--auto-from` damage (90/140 broken), so every
  member-gate was failing/retrying. **On a healthy tree a targeted `--addr` propagate is ~233s/core**
  (`[ OK ] 138 overlays byte-identical`) — ~20× faster. Only `--auto-from` is genuinely fleet-slow.
  **A timing taken on a broken tree measures the breakage, not the tool** (§55c).
- **✅ 2026-07-17 — TASK 3 COMPLETE (both deliverables) + 12 giant drafts preserved.**
  **(a) The jr cores — 4/4 match_one MATCH, 0/4 banked (integration, not codegen).** A 2nd ultracode wave
  cracked all four giants: `func_8013F350` (490), `func_80131340` (424, verified TWICE — standalone AND
  in-TU cc1 rc=0), `func_80159C84` (337), `func_8013C414` (329, **-O0**). All four gate-rejected on
  *plumbing* (def-sig / rodata-island / decl-conflict), each blocker NAMED. **`func_8013C414` only matched
  because of the new `worker_wave --o0` fix** — against an -O2 self-check a -O0 target can never match
  (the §53/§54 wrong-build-step trap, Task-1's "~3%" artifact). Drafts + exact blockers + a suggested
  cheapest-first bank order → **`.run/giants/p29t3_README.md`** (12 drafts, tracked; ~2.6M agent tokens
  to reproduce — do NOT re-draft, bank them).
  **(b) The §53 `has_mid_jr` INTERLOCK — BUILT + negative-control-proven** (`commit:0670`): `family_sweep`
  now refuses to sweep a `has_mid_jr` family carve-less, names `jtbl_family_bank`, and states that a 0%
  from that path is a TOOL ARTIFACT not a wall. Uses the manifest's `has_mid_jr` (R33 — one oracle, shared
  with `dedup_extend`). Verified: 11 jr families / 163 slots of 1418 sweepable; `--band substantial` skips
  9 families / 155 slots (159→150); `--allow-jr` → 159 (does not skip). **It flags `0x8017bebc` (n=115) =
  B2** — the very family whose missing carve manufactured the Phase-26 "≈0%" doctrine. That class of
  self-inflicted wall is now structurally impossible.
- **2026-07-16 — broad `--fix-def-sig` harvest = TAPPED beyond the mega-pools (+19).** Fleet-wide
  `--band substantial` (17) + `--band tiny` (2) with `--fix-def-sig` (all families, not just the 2 pools) =
  **19 more members** banked (the def-sig conflict was highly concentrated in the 2 tiny-IMM mega-pools;
  8491 tiny members now skip as not-stub). R22 clean-fleet **140/140**; fleet instr 71.0% (steady) /
  distinct 53.2→53.3% / fn-count 86.30%. Task 6 mega-pool track COMPLETE. **Remaining Task 6:** the permuter
  backlog sweep (the 550 close-1..4 drafts via grinder/permuter_ils) — separate track, not yet run.
- **2026-07-16 — Task 2 (Arm A) DONE = swing verdict → banked fact + wall characterized.** New tool
  `tools/rollout_o0_cluster.py` + Makefile `O0_CLUSTER_OBJS` -O0 wildcard. Carved 4 SC07 tail overlays;
  byte-neutrality gate (clean R22): **ov_SC07_010 byte-identical, 006/007/011 FAIL** (+0x20 splat
  data-symbol shift, boundaries verified — the Phase-20 splat "-O0 split infra" wall, not the compiler).
  Kept 010's carve, reverted the 3; `family_sweep --hseq --only <9 -O0 exemplars> --band all` banked
  **9/9 -O0 members in ov_SC07_010** whole-binary → **the -O0 cluster masked-MATCHes ARE real banks
  (§52b fact)**. R22 clean-fleet **140/140 byte-identical**; fleet 70.4% instr / 52.3% distinct / 84.94%
  fn-count; dedup 1840/0; main 143dbb89. Full -O0 fleet rollout DEFERRED (splat wall on 3/4 + jr-embedded
  on 134 + ROI vs Task 3/6). R31 writeup in `docs/decision-log.md`. Logs `.run/armA_*`.
- **✅ 2026-07-17 — Task 4 giant-bank #1: `func_8013FAF8` (312) BANKED ×1 in ov_SC01_077** (whole-binary
  byte-identical; R22 clean-fleet **140/140**). The README billed it "pure def-sig plumbing" but it was a
  **multi-symbol reconciliation** (3 data + 2 fn conflicts, ~5 gate iterations) — distilled to cookbook **§56**.
  Fixes, all byte-neutral + gate-arbitrated: **(1)** def-sig s16/s16 vs canonical s32/s32 → **narrowed the extern
  fleet-wide** (404 decls / 266 files; NOT `--fix-def-sig` — that rewrites the DRAFT to the canon and the s32
  variant diverges at insn 22; verified via `match_one` R35). All callers pass `(s16)`-cast/small-const → neutral.
  **(2)** 3 data-symbol conflicts (`D_80115128` lh, `D_800B9A02` lhu, `D_80187AC0` s32[]) declared BEFORE the
  splice (block-scope §55a-blocked) → the TU's **§18 cast-at-use-site** convention (`*(s16*)&`, `*(u16*)&`,
  `((s32*)&sym)[i]`) — forces the load width regardless of decl signedness, keeps the TU decl untouched,
  propagation-safe. No CSE-hoist across 5 uses. **(3)** 2 fn-extern conflicts (`func_8013FFD8` s16 arg0,
  `func_80141100` int(int)) → reconciled draft decl to the TU def + byte-neutral call-site cast. Still MATCH
  312/312. Stubs 138→137, defs 1, 0 NON_MATCHING (G4). Resolved draft `.run/drafts_faf8/func_8013FAF8.c`.
  **NEXT:** giant #2 `func_80131340` (424, _jr_8012ACE0.c — in-TU-verified twice, earlier "gate reject" was a
  §55b propagate-damage artifact; re-gate on the clean tree). Propagation of all banked giants = batched (§55b).

- **✅ 2026-07-18 — CRACK-WAVE (Ultracode, 7 fresh-core agents, ~2M tokens): 3 MATCH / 4 near; 1 family banked ×138.**
  Fan-out over the top unbanked substantial families (m2c + §31 map + gcc-2.7.2 source + match_one).
  **MATCH:** `func_8013CB84` (249, non-jr) → **banked ×138** (5-lever crack: §32 struct-base-hoist + §18
  address-caching + packed-struct block-move + 1-arg-callee + Rec12 stride array; §8d reconcile D_801DAA78
  Rec9→u8 cast-at-use). `func_8015B950` (271, jr) + `func_8013B83C` (272, jr-O0) — MATCH but DEFERRED on
  real walls (8015b950 = def-side register-threading: canonical (void) vs def-reads-$a0, thin-wrapper caller
  func_8015BEE4 forwards $a0 implicitly, pin perturbs codegen; 8013b83c = Arm-A -O0 sweep-block + -O0 jr-isolation
  gap). Both preserved+characterized (.run/giants/wave_func_*.c, R20). **Near (permuter/Fable5 fuel, rich probes):**
  func_8012956C (15), func_8013D53C (27, CSE address-merge — literal-probe gives structural match, family-wide),
  func_80175DA8 (30), func_80135EB0 (36, jr). **Permuter:** func_8014D820 33→27 (regalloc-order wall → Fable5
  seed, preserved). **CRACK-WAVE SWEEP LESSON (new memory + §-note):** a freshly-cracked exemplar is draft-ov077
  in the stale map → family_sweep finds 0; --reconcile-raw mishandles per-overlay externs (0/137). FIX: bank ×1 →
  `make sig-overlays` + `family_hseq.py` regen (→matched-ov077) → standard `family_sweep --hseq --only` (137/137).
  **BATCH R22: check-all 140/140 byte-identical; tools-health green; dedup 1846/0.** Fleet **73.4→73.7% instr ·
  56.9→57.5% distinct · 86.73% fn-count**. Commit `commit:0699`.

- **✅ 2026-07-18 — CRACK-WAVE 2 + FABLE AGENTS + TYPE-LIFT RECOVERY (Ultracode→xHigh). Fleet 73.4→74.6% instr.**
  **Two Opus crack-waves (15 fresh-core agents) + 3 Fable5 agents (gcc-2.7.2 source-readers) + a permuter track.**
  Wave-1: `func_8013CB84` (249) MATCH → **banked ×138**. Wave-2 (8 non-jr cores 93-209 ins): **6 MATCH**
  (8016cbc0/8015ea3c/8015d738/8015f448/8014ffdc[×276]/801412a8) + 2 near (80175ab8=58, 80178004=39).
  **Fable5 (each read the compiler source): 3 MATCH** — `func_8013D53C` (240, the cse.c cross-statement
  address-CSE wall: `*(S9*)(&D_801DA998+0x20)` never unifies with SYMBOL_REF while gas folds %hi/%lo(sym+k)
  byte-identical — NEW family-portable idiom), `func_801670E4` (279, post-reload scheduler boost-kill re-ties),
  `func_8012956C` (226, 4 stacked mechanisms incl. the reorg j-slot-steal barrier) — plus 2 near driven far
  closer (8014D820 33→**11**, 80175DA8 30→**11**, permuter/Fable seeds preserved).
  **BANKED: 8 exemplars ×1** (all but 801412a8) **+ ~815 members swept**: first sweep 538 (4 clean families:
  8015ea3c 134 / 8015d738 134 / 8015f448 138 / 8014ffdc 135) + type-lift recovery (8012956c **137/137**,
  801670e4 partial 4). **R22 clean-fleet 140/140 byte-identical; tools-health green; dedup 1846/0; 0 NON_MATCHING.**
  Fleet **74.6% instr · 59.4% distinct-code · 86.92% fn-count** (crack-wave arc start 73.4/56.9/86.61;
  **session-total 72.1→74.6 = +2.5pp instr**). Commits `commit:0699`..`commit:0708`.
  **NEW LESSONS (R30):** (a) crack-wave sweep needs a **map-regen** step (freshly-cracked exemplar is draft-ov077
  → family_sweep finds 0; bank ×1 → sig-overlays + family_hseq.py → matched-ov077 → standard sweep). (b) The
  reconcile ladder (cast_call_sites→reconcile_tu→scope_data_externs) handles most, but recurring manual fixups:
  **func_80161208/func_801670E4 all-decls-normalized-to-no-proto** (a reconcile re-adds a file-scope prototyped
  decl that poisons every no-proto call), scalar-typedef strip, §17a-1 fn-ptr casts, local-typedef uniquify vs
  same-file siblings. (c) **Type-lift recovers clean-TYPE families 137/137** (Blk16_956C/Ent_956C, SVec/Fr →
  engine_types.h, byte-neutral) but NOT def-sig/per-sibling-decl-conflict families.
  **CARRIED FOLLOW-UPS (all preserved, R20):** (1) 801670e4/8016cbc0 — type-lifted but the sweep hits a
  per-sibling decl-conflict (see BUILD SPEC below). (2) 8013d53c family — void* def-sig caller-decl thread per
  sibling. (3) 801412a8 — §29 narrow-u16-param def-side wall (caller decl int; matching adds masking). (4)
  permuter/Fable fuel: 8014d820 (11), 80175da8 (11), 80175ab8 (58), 80178004 (39). Drafts in
  .run/giants/{wave2_,fable_,*.close11}*.

- **▶ NEXT-SESSION BUILD SPEC — the sweep DECL-NORMALIZE enhancement (Drew-directed 2026-07-18; effort Max).**
  **The problem, byte-verified:** `family_sweep --hseq` templates the banked function F's DEF into each sibling
  TU, but the sibling's *own already-banked callers* may carry a block-scope decl of F whose signature differs
  from F's canonical — a HARD `conflicting types`. Byte-proof (func_801670E4, sibling ov_SC01_004): the sibling's
  caller has `extern void func_801670E4(struct Entity_80167540 *, s32, s32, s32);` (jr_8015AE2C.c:5076) while F's
  canonical/def is `s32 func_801670E4(s32,s32,s32,s32)` (engine_core.h:19003) → 133/137 fail. **Crucially the
  EXEMPLAR's copy of that same caller used a fn-ptr CAST instead of a decl** (ov_SC01_077 jr_8015AE2C.c:5338:
  `((void(*)(struct Entity_80167540 *,s32,s32,s32))func_801670E4)(...)`) — different overlays' callers were
  matched in different C forms, so the conflict is per-sibling, invisible in the exemplar. Same root as the
  func_80161208 ×1 whack-a-mole (a callee declared inconsistently → a reconcile re-adds a file-scope prototyped
  decl that poisons every no-proto call).
  **THE FIX (a per-sibling decl-normalize pass — the SAME-FUNCTION analog of `tools/cast_call_sites.py`, which
  only does the CALLEE direction):** after templating F into the sibling, scan the sibling TU for EVERY decl of F
  (block- or file-scope) whose sig ≠ F's engine_core canonical; for each, rewrite the decl to canonical (or drop
  it) AND fn-ptr-cast the associated call site(s) so codegen is byte-neutral (§17a-1). Generalize to conflicting
  CALLEE decls too (func_80161208 class: normalize all decls of the callee to the canonical/no-proto form; a
  reconcile that re-adds a file-scope prototyped decl must be suppressed). Whole-binary gate is the sole arbiter
  (G3/P9) — the pass only needs to make it COMPILE; wrong casts fail the gate.
  **WHERE:** a new stage in `tools/family_sweep.py`'s per-sibling ladder (raw→scoped→recovered→reconciled), or
  extend `tools/reconcile_tu.py`/`cast_call_sites.py`. Model it on `cast_call_sites.py` (decl→canonical + cast).
  **VALIDATE on:** re-sweep func_801670E4 (expect ~137; type-lift already committed) then func_8016CBC0 (also
  type-lifted-needed — lift Blk_8016CBC0 + Mtx8_8016CBC0 first, byte-neutral, like 8012956c). 8013D53C is a
  DISTINCT class (void* def-sig where the sibling CALLER declares/calls F(void) — needs the def-sig+caller thread,
  not this pass). Reproduce a failure fast: `family_sweep --hseq --only 0x801670E4`, then manually splice a
  `.run/sweep/<ov>/func_801670E4.c` staged draft into the sibling stub + `make build BINARY=<ov>` to read cc1.
  Est. reward: ~+300-400 members (801670e4 + 8016cbc0 + the residual SC07 tails) ≈ +0.7pp. Cookbook §-note when done.

- **✅ 2026-07-18 — DECL-NORMALIZE ENHANCEMENT BUILT + VALIDATED: func_801670E4 family 4→137/137 (+133 banked, 0 failed).**
  Built `tools/normalize_self_decls.py` — the **third §17a-1 direction** (cast_call_sites = callee decls in the DRAFT;
  reconcile_tu = data decls in the DRAFT; this = **F ITSELF**, declared divergently by the sibling TU's OWN already-banked
  callers). `fix(tu_text, fn, ref_decl)`: drop each decl of F incompatible with F's def (`cdecl.compatible` oracle; skips
  no-proto `void f()` which never conflicts, §51g) + cast its in-scope calls to the dropped sig (scope via `cdecl._mask`ed
  brace-depth). Wired into `family_sweep --hseq` as `--normalize-self-decls` (new per-sibling stage after reconcile_def_sig;
  edits the **sibling TU FILE** = harvest_verify's baseline, like edit_remap_sweep) + a snapshot/**final-SHA-MISMATCH revert
  backstop** (a MISMATCH ⇒ transform bug — a wrong DRAFT is always reverted by harvest_verify, so only a non-neutral TU edit
  can MISMATCH). **Byte-proof before the tool existed:** manually dropped the ov_SC01_004 decl + cast the call + spliced F's
  def → fresh build (output removed first — dodged the §42b STALE-binary false-pass) BYTE-IDENTICAL. Survey: all 133 still-
  stubbed siblings carried the *identical* block-scope `extern void func_801670E4(struct Entity_80167540*,s32,s32,s32)`.
  **R14 CORRECTION (do not re-trust the confound):** my first repro added `--fix-def-sig`, which renamed F's def params to
  `a0..a3` while the body used `arg0..arg3` → `arg0 undeclared` (a DIFFERENT bug — the "rare name mismatch" reconcile_def_sig's
  own docstring warns of). The raw draft def `s32 func_801670E4(s32 arg0,…)` is already type-compatible with canonical (param
  NAMES are irrelevant to a C prototype), so this family needs NO `--fix-def-sig` — the caller-decl conflict is the SOLE
  blocker. Sweep `family_sweep --hseq --only 0x801670E4 --band substantial --allow-pins --no-preclassify --normalize-self-decls`
  → **133/133 banked, 0 failed, 0 backstop fires**; 0 func_801670E4 stubs remain fleet-wide. **R22 clean-fleet 140/140
  byte-identical; tools-health OK (dedup 1846/0, C1 234205/234205); 0 NON_MATCHING linked (G4).** Fleet **74.6→74.9% instr ·
  59.4→60.1% distinct · 86.92→86.96% fn-count** (~+37k ins). Cookbook **§57** (R30). **R14 finding for Task-4/8016CBC0:**
  survey proved its 137 members have NO divergent self-decl — it is TYPE-LIFT-blocked (6-typedef cluster Rec_/Blk_/SVEC_/CLR_/
  Poly_/Mtx8_8016CBC0), a DIFFERENT lever (like 8012956c), NOT this pass. Route by the real cc1 error, not by "stuck 137-family."
  NEXT: the func_8016CBC0 type-lift (separate commit) + the 8013D53C void*-def-sig class + the permuter/Fable backlog.

- **✅ 2026-07-18 — func_8016CBC0 TYPE-LIFT + sweep COMPLETE ×138 (the separate lever the R14 survey predicted).**
  Confirmed the survey: func_8016CBC0's 137 members are NOT self-decl-blocked (§57) — blocked purely on the exemplar's
  **6 local typedefs** (Rec_/Blk_/SVEC_/CLR_/Poly_/Mtx8_8016CBC0). Lifted all 6 VERBATIM into
  `src/shared/engine_types.h` (marked "Phase-29 crack-wave lift (func_8016CBC0 family)" section, fleet-visible via
  engine_core.h) + removed the locals from the exemplar TU (ov_SC01_077_jr_8016AB6C.c). Verified **no fleet
  name-collision** (all 6 exclusive to the exemplar, grep) and **byte-neutral** (exemplar overlay rebuilds
  byte-identical d19c9580). Sweep `family_sweep --hseq --only 0x8016CBC0 --no-preclassify --normalize-self-decls`
  → **137/137 banked, 0 failed** (--normalize-self-decls a correct no-op here — 0 divergent self-decls, as surveyed);
  0 func_8016CBC0 stubs remain fleet-wide. R22 clean-fleet **140/140 byte-identical**; tools-health OK (dedup 1846/0,
  C1 234205/234205); 0 NON_MATCHING linked (G4). Fleet **74.9→75.1% instr · 60.1→60.6% distinct · 86.96→87.00%
  fn-count**. **Session-total (both families): 74.6→75.1% instr (+0.5pp), 59.4→60.6% distinct (+1.2pp), +270 members**
  — the decl-normalize win (§57, +133) and the type-lift win (+137) from the SAME BUILD-SPEC validation set that
  looked like one "stuck 137-family" but needed two different levers. NEXT: 8013D53C (void*-def-sig + caller-thread
  class), the SC07 tails, permuter/Fable backlog.
  **⚠️ COMMIT GOTCHA (caught + fixed by amend):** a family's members do NOT all live in the same-named split
  file — SC07 overlays carve `func_8016CBC0` into `jr_8013F350.c`/`o2b.c`, not `jr_8016AB6C.c`. A filename-glob
  `git add "src/ov_*/*_jr_8016AB6C.c"` silently missed 4 R22-verified banks. **Use `git add -u src/` (all
  modified tracked) for sweep commits**, never a split-name glob — else a pushed tree omits banks the R22 verified.

> **🛑 SESSION-3 CHECKPOINT (2026-07-18) — safe to open a FRESH session here.** Tree clean (only db.*.gbf R23
> churn), **140/140 byte-identical**, tools-health OK (dedup 1846/0, C1 234205/234205), 0 NON_MATCHING (G4).
> Main `commit:0712`. Fleet **75.1% instr · 60.6% distinct-code · 87.00% fn-count** (session opened 74.6/59.4/86.92).
> **This session delivered the DECL-NORMALIZE ENHANCEMENT (Drew's teed-up BUILD SPEC) + banked both its validation
> families:** `func_801670E4` 4→137/137 (+133, the new §17a-1 self-decl pass, `tools/normalize_self_decls.py` +
> `family_sweep --normalize-self-decls`, cookbook §57) and `func_8016CBC0` 1→138/138 (+137, a 6-typedef
> engine_types.h lift — the R14 survey proved it was a DIFFERENT blocker than it looked). **+270 members, +0.5pp
> instr**, commits `commit:0711` + `commit:0712` (Drew pushes). **NEXT levers (BUILD SPEC residue):** `func_8013D53C`
> (the DISTINCT void*-def-sig + per-sibling caller-thread class — NOT the self-decl pass), the SC07 span-composition
> tails (§8e-2), and the permuter/Fable close-1..N backlog (Task 6). The decl-normalize pass is now a standing
> `family_sweep` stage for any future family whose members' own callers declare F divergently.

- **✅ 2026-07-18 — BROAD SWEEP (honest yield +137) + func_8013D53C (14/137) + NSD HARDENED (2 bug-fixes).**
  After the SESSION-3 checkpoint: ran the broad substantial-family sweep, then attacked func_8013D53C. All findings
  → cookbook **§57a**. **(1) The substantial-family frontier is NOT broadly mechanical (R14/R35):** 60 families /
  2,169 stubbed members STAGE but only **137 bank** with --fix-def-sig — staging ≠ banking; I over-projected ~1,500
  from the staged count instead of gate-probing a sample (the phase's own invariant, violated). Banked func_801502EC
  ×134 + func_80131B14 ×3 (commit `commit:0714`). **(2) NSD is SURGICAL-ONLY:** broad `--normalize-self-decls` (esp.
  combined with `--fix-def-sig`, which changes NSD's reference sig) makes byte-neutral-but-wrong TU edits that poison
  whole (overlay,split) groups — the backstop reverts them (0 false banks) but banked **7** / reverted **752**.
  `--fix-def-sig` edits DRAFTS (bisect-safe per member) so it IS broad-safe. Law: NSD per-family, --fix-def-sig broad.
  **(3) NSD HARDENED — 2 real bug-fixes (validated on D53C):** rewrite-to-canonical instead of DROP (dropping broke
  def-AFTER-caller forward visibility → `func undeclared`); and `(void)` is a genuine 0-param conflict, NOT skippable
  like a true no-proto `()` (the bug that filed D53C's arity class as "not this pass"). **(4) func_8013D53C =
  PARTLY-mechanical:** NSD + a byte-neutral `Cmd_8013D53C` type-lift clear its plumbing → **14/137 bank** (the h_seq
  members whose bodies template); **123** carry genuine per-member codegen DIFFs (the hard cse.c-wall crack does not
  fully template → permuter/Fable fuel). Reverted the 123 bankless NSD edits (byte-neutral but churn on matched code
  — §57a NB). R22 clean-fleet **140/140**; tools-health OK (dedup 1846/0, C1 234205/234205); 0 NON_MATCHING (G4).
  Fleet **75.2% instr · 60.6% distinct · 87.04% fn-count**. **SESSION-TOTAL from 74.6/59.4/86.92: +0.6pp instr,
  +1.2pp distinct, ~+421 members** across 4 commits (commit:0711, commit:0712, commit:0714, + this).
  **REFRAME (the session's strategic finding):** the family campaign is **per-family cracking, not one broad sweep** —
  each substantial family carries its own blocker (self-decl / type-lift / def-sig+caller / genuine codegen), and the
  mechanical fraction is small (~137 broad + 14 D53C). Remaining Task-4/6 levers: the permuter backlog (551 close-1..4
  drafts, high-reach) + per-family type-lift/crack of the ~50 remaining substantial families + the tiny/mid bands.

- **✅ 2026-07-18 — CRACK-WAVE (session-4, Ultracode 11-core): 9 MATCH / 2 near → 6 BANKED ×1 in ov_SC01_077.
  PAUSED at Drew's request after the bank (before sweeps).** Regenerated the `family_manifest` frontier FIRST
  (R35 — the Jul-14 digest still listed this phase's already-banked families as draftable): 14 draftable
  (ov077-STUB) families; 11 with 138-fleet reach dispatched to xHigh drafters (cached Ghidra-C + m2c + §31 +
  `match_one`). **9 MATCH / 2 near** (`func_8014D820` close-11 intrinsic-sched wall, `func_8012E364` close-22
  div-block regalloc — both preserved `.run/giants/wave_*`, R20). **Banking = the §55b reality (new cookbook
  §58):** all 9 `match_one` MATCHes gate-failed on INTEGRATION, 0 codegen — `match_one` compiles STANDALONE so
  it is blind to (a) Ghidra symbol names (DAT_/PTR_DAT_ vs splat D_), (b) def-sig conflict vs the fleet
  (draft sig is byte-truth; the engine_core `void` is a stale stub-era guess — canon_sig_reconcile forcing
  `void` DIFFed), (c) callee-decl conflict, (d) -O0-vs-O2. A focused reconcile agent banked **6/9** byte-identical:
  `func_80150170` (95, hexR=138 DEDUP core) + `func_8016D1D8` (148) + `func_8016D688` (60) + `func_80164E40` (25)
  + `func_80165240` (63) + `func_801457A4` (79, -O0 → relocated into `_o0b`). Levers: 3 `engine_core.h` decls
  narrowed void→s32 (byte-neutral fleet-wide, callers ignore the return), `normalize_self_decls`, `cast_call_sites`,
  + a `D_801D9C20/60` **u8** symbols mirror (fixed my `type:data`→`type:u8` splat-format bug that failed
  ov_SC01_077 extract). **3 NOT banked (`func_801549F8`/`func_8013BD74`/`func_8013C0F8`) — ALL match standalone,
  blocked ONLY by the §8 jtbl-rodata carve** (NOT codegen; 8013C0F8 was NOT a real DIFF — corrected). Drafts
  preserved. **R22 clean-fleet 140/140 byte-identical; tools-health OK (dedup 1846/0, C1 234205/234205); 0
  NON_MATCHING (G4).** Fleet 75.2/60.6/87.04 (FLAT — these are ×1 banks; the **×138 sweep is the deferred
  fleet-mover**). Commit `<this>`. **NEXT (paused, not started):** map-regen + `family_sweep --hseq --only
  --normalize-self-decls` the 4 -O2 cores (8016D1D8/80165240/8016D688/80164E40) + `dedup_propagate 0x80150170`
  (hexR=138 → ~138 free) + jtbl-carve the 3 (Task 6). §58 flywheel captured (R30).

- **✅ 2026-07-18 — SESSION-4 FLEET-MULTIPLIER PASS (Ultracode auto, resumed): +275 members / 2 commits.**
  Propagated the 6-core bank fleet-wide: **`func_80150170` ×138** (`dedup_propagate --addr`, hexR=138 group
  registered — commit `commit:0717`; first run SIGTERM'd mid-gate at the 2-min timeout → reverted the half-gated
  state, re-ran clean fail-closed) + **`func_80164E40` ×137** (`family_sweep --hseq --only --normalize-self-decls`;
  the fleet-wide engine_core void→s32 narrow made it clean — commit `commit:0718`). Map-regen (sig-overlays +
  family_hseq) done first (crack-wave-map-regen rule). **R22 clean-fleet checkpoint: 140/140 byte-identical,
  extract-all 139/0.** Fleet ~75.3% instr (`make report` will confirm; the ×137/×138 propagations register now).
  **3 sweep-residuals (delegated):** `func_80165240` (63, byte-DIFF/reconcile — compiles standalone),
  `func_8016D1D8` (148) + `func_8016D688` (60) reference the carve-boundary data-label `D_801D9C20`/`D_801D9C60`
  only in ov077's symbols; siblings need it propagated (per-sibling symbols + re-extract). Plus the 3 §8
  jtbl-carve cores (Task 6). NEXT: reconcile the residuals (ROI-triaged), then the next crack-wave / permuter backlog.

- **✅ 2026-07-19 — SESSION-4 RESIDUALS BANKED + VERIFIED (delegated agent): +412 more members, 3 commits.**
  A focused agent ROI-triaged the 3 residual classes (byte-gate arbitrated): **`func_80165240` 137/137**
  (`commit:0720` — the sweep dropped the exemplar's LOCAL `struct W4` type → per-member memcpy DIFF; carried the
  decl into each member draft, §59#1), **`func_8016D1D8`+`func_8016D688` 274/274** (`commit:0721` — my "fixed
  0x801D9C20 data" premise was WRONG: h_seq data is per-overlay RELOCATED, no fleet-fixed address; derived each
  overlay's base `= symbol_map[offset]−offset`, declared `D_<base>` per sibling + re-extract, §59#2), and
  **`func_8013C0F8` ×1** (`commit:0722` — jtbl_801D82FC carve, def-sig reconcile). **BLOCKED (genuine tooling
  walls, §59#3):** `func_801549F8` ×137 (jtbl §8c isolation — `trim` can't partition the Phase-17 canonical-sig
  layer TU) + `func_8013BD74` ×1 (§8e-2 table-count drift). **R22 clean-fleet: 140/140 byte-identical,
  extract-all 139/0; tools-health OK (dedup 1847/0, C1 234343/234343); 0 NON_MATCHING linked (G4).**
  **SESSION-4 TOTAL (from the 74.6→ session open, this conversation): fleet 75.2→75.7% instr · 60.6→61.3%
  distinct · 87.04→87.24% fn-count** — 6 cores cracked + propagated ≈ **687 member-banks** across
  `commit:0716`/`commit:0717`/`commit:0718`/`commit:0720`/`commit:0721`/`commit:0722` (+ `commit:0719` checkpoint). Cookbook §58/§59
  captured (R30). 2 near cores preserved (`func_8014D820` close-11, `func_8012E364` close-22 — permuter fuel).
  NEXT: next Ultracode crack-wave over a freshly-regenerated frontier + the permuter backlog (Task 7).

> **🛑 SESSION-4 CHECKPOINT (2026-07-19) — safe to open a FRESH session here.** Tree clean (only db.*.gbf R23
> churn + 2 preserved near-drafts + progress.fleet.md digest), **140/140 byte-identical**, tools-health OK
> (dedup 1847/0, C1 234343/234343), 0 NON_MATCHING (G4). Main `commit:0734`.
> **Fleet 76.3% instr · 62.8% distinct-code · 87.47% fn-count** (session opened 75.2/60.6/87.04 → **+1.1pp instr,
> +2.2pp distinct** — ~1,500 member-banks across TWO crack-waves).
- **✅ 2026-07-19 — CRACK-WAVE 2 (absent-from-ov077 pool) + propagation: +819 members, HEAD `commit:0734`.**
  Broad substantial sweep first = **0 banked / 858 failed** (the mechanical frontier is DRAINED — §57a confirmed).
  So cracked the FRESH absent-from-ov077 substantial pool instead: 9 families drafted from **ov_SC01_000** (cached
  Ghidra-C, NON-MCP) → **7 MATCH / 2 near**. Banked ×1 (4 clean via the §58 ladder, 2 residuals via §18 cast-at-use
  + K&R self-decl reconcile) then propagated: **func_8013EF88 ×136, func_801418F8 ×136, func_8013D8FC ×136,
  func_80141A60 ×136, func_8013D9B0 ×136, func_8016DC20 ×135** (1 wall). **2 walls (reported, not forced):**
  func_8016DC20 in ov_SC07_010_o2b (-O2 recon TU trips `as --fatal-warnings $at`), func_80156044 (byte-match needs a
  `void` def but fleet-canonical is `int(int,int)` via a 138-overlay DEFINE macro — a disproportionate fleet-wide decl
  flip for 74 ins). **R22 clean-fleet 140/140 byte-identical; tools-health OK; 0 NON_MATCHING.**
  **⚠️ TOOLING FINDING (R35, fix next):** `family_sweep --hseq --source <ov>` is IGNORED — it templates from the
  MANIFEST exemplar (`pick_exemplar` hard-prefers ov_SC01_077), so a non-ov077 source silently used ov077's
  heavy-local-struct spelling → 0 banks until the manifest exemplar was redirected. The `--source` flag lies; the
  agent worked around it by editing the manifest. **§57a NSD-hazard re-confirmed** (NSD mis-parses `else func(N);`
  call statements as decls → wrong `void(*)(void)` cast; use K&R self-decl reconcile, not NSD, for these).
  **FRONTIER STATE (honest):** the cheap NON-MCP substantial-family pool (ov077-draftable + absent-cached) is now
  WORKED OUT (broad sweep 0; ~14 absent-substantial → 10 cracked/6 banked-families, 2 walls, 2 uncached needing MCP).
  Remaining levers: (a) **fresh cracks need a Ghidra-C prefetch → /mcp** (mid/tiny bands, resident's 14, main-EXE);
  (b) the **permuter backlog** (4 preserved nears: 8014D820/8012E364/8017B490/80143D28 + the 551 close-1..4 — uncertain
  yield, §26 exhausted-lever caution); (c) **tooling fixes** (family_sweep --source; the §8c/§8e-2 jtbl walls unlock
  func_801549F8 ×137 + func_8013BD74). This is the ROI-floor signal for non-MCP cracking (Task 7).

- **✅ 2026-07-20 — CRACK-WAVE 3 (16 fresh cached ov077 substantial families) + propagation: ~1,378 instances,
  23 commits (`commit:0736..commit:0759`).** The h_seq frontier revealed ~95 cached substantial families still crackable
  NON-MCP (the h_norm view had undercounted); 16 fresh (non-attempted) cracked → **12 MATCH / 4 near** (100% on the
  first 8; wave hit + recovered from a session-limit mid-run via resume). Banked ×1 + propagated (delegated agent,
  §58/§59 ladder, K&R self-decl reconcile NOT NSD per §57a): **9 cores fully 138/138** (func_80160534/8016C998/
  8016B234 non-jtbl + func_8015C32C/80154C24/801588CC/801594E8/80140608/801555F4 jtbl via jtbl_family_bank),
  **func_80169BBC 134/138** (4 SC07 special-split residuals), **func_8014032C + func_8017AE2C exemplar-only** (§59(3)
  jtbl span-fit carve walls — cracks are true MATCHes, recoverable if jtbl_family_bank learns span-fit auto-isolate).
  **4 near preserved** (permuter seeds: 80175AB8/80177B5C/8015D1B8/80179B74). **R22 clean-fleet 140/140 byte-identical,
  extract-all 139/0.** **Fleet 76.3→77.8% instr · 87.47→88.1% fn-count.** New idiom (cookbook-worthy): a jtbl core that
  isolate-fails early can succeed after sibling jtbl cores bank (the overlay's jr-structure evolves) — func_80140608
  went isolate-fail → 138/138. **⚠️ WEEKLY usage limit hit (resets 5am MT 2026-07-20) — session winding down here.**

- **✅ 2026-07-20 — TASK 8 (2 tooling fixes) DONE + immediate payoff: func_8017AE2C ×137 recovered.**
  **(1) `family_sweep --hseq --source` no longer a no-op** (commit): it templated from the manifest exemplar
  (pick_exemplar hard-prefers ov077), silently ignoring --source; now overrides to the --source overlay's MATCHED
  member per family (self-correcting via the gate; ov077-default path unchanged). **(2) `jtbl_family_bank`
  auto-isolates on the span-fit wall too** (commit): was NON-CONTIGUOUS-only; now also fires on "do not fit the
  span" (jr_isolate unblocks it — byte-proven). The distinct table-count-drift error ("more rodata .align than pad
  specs") stays excluded (not isolate-fixable). **PAYOFF: `func_8017AE2C` (174 ins) recovered ×137** (was
  exemplar-only from wave-3's jtbl wall) — the fixed tool banked all 137 members whole-binary; **R22 clean-fleet
  140/140 byte-identical, extract-all 139/0.** **`func_8014032C` STAYS blocked** (its wall IS the excluded
  table-count-drift, confirmed rc=1/0-banked — a separate future fix). ~+24k ins. NEXT: Tasks 9 (crack remaining
  cached fuel), 10 (permuter backlog), 11 (burn-down tracker).

- **✅ 2026-07-20 — CRACK-WAVE 4 (cached-fuel tail) + the crack-track FLOOR.** 10 fresh cached targets from
  ov_SC01_000 → **10/10 MATCH**, but the tail is thin: **6 -O2 cores banked ×1** (`commit:0766`, reconciled: func_80142C84
  cast + func_80143994 s32-cast; R22 clean-fleet 140/140), the 6 -O2 **×138 propagation banked 0** (per-family §59
  reconcile bottleneck — deferred to Task-14 gate_stage-ladder enrichment), and the **4 -O0 cores didn't bank** (the
  ov_SC01_000 -O0-build wall; drafts in .run/drafts_wave4/). **The non-MCP cached substantial crack-fuel is now
  DRAINED** (waves 1-4). Remaining crack levers are all gated: -O0-cluster rollout, jr (jtbl path), or uncached/absent
  (need a Ghidra-C prefetch → overlay import → /mcp). **→ PIVOT to the permuter-automation program (Tasks 12-14,
  Drew-directed): make the offline permuter+ILS pipeline self-improving so it drains the backlog + the deferred
  propagations without an LLM in the loop except for genuine humps.**
  **⚠️ GRINDER CONCURRENCY LESSON (this session):** running the grinder concurrently with a crack-wave + killing it
  mid-flight left an 872-file mid-gate_stage state AND lost 3 permuter wins' C (not durably saved before banking) →
  reverted clean. The grinder needs (a) a fast/clean STOP between functions, (b) durable winner-C saving BEFORE
  gate_stage banks, (c) clear commit boundaries — folded into Tasks 12/14.

- **✅ 2026-07-20 — TASK 12 (permuter-autopsy prerequisite) DONE + committed commit:0768.** Structured failure
  telemetry now FLOWS: `masked_diff.structured_diff()` (per-instruction masked residual) + `match_one --json`
  ({status,closeness,nins,residual}) + `backlog` fields `residual`/`passes_tried` + `gate_stage` logs the
  residual on every near/fail (verified end-to-end: a near-miss's [idx,mine,tgt] residual lands in
  backlog.jsonl) + grinder durably saves the winning C to `.run/permuter-winners/` BEFORE banking (the lost-3-wins
  lesson). **NEXT (fresh session): Task 13 (A+B — deterministic residual→class classifier + LLM-batch autopsy that
  routes each plateau to missing-transform/mis-classified/seed-structural/wall + extends `permuter_weights`), then
  Task 14 (C+D — enrich `gate_stage`'s ladder with §57/§59 so more wins auto-integrate + grinder auto-R22 every N
  wins). Then run the closed loop: improved permuter over the whole backlog → collect telemetry → extend ILS →
  re-run → track the LLM-free fraction (burndown.py). Design substrate: docs/hindsight-study.md §7.**

- **✅ 2026-07-21 — TASK 13A DONE: the deterministic residual classifier + the corpus it reads; the
  permuter's problem is TARGETING, not a missing transform.** Built `tools/residual_class.py` (decode each
  mismatching MIPS word → `(op-skeleton, register-fields, immediate)`; drift FIRST, then consistent-injective
  register map → `REGALLOC-PERM`, same-multiset-different-order → `SCHEDULE-REORDER`, `DELAY-SLOT`,
  `WIDTH`/`BRANCH-POLARITY`/`STRENGTH`/`ADDRESSING`/`IMM-OFFSET`/`IMM-VALUE`; every class routes to a BUCKET =
  which tool the failure wants; uncovered opcode → `UNKNOWN`, counted; 16 unit tests) + `tools/autopsy.py`
  (`collect` recompiles every open draft through the EXISTING `match_one` path, deriving the asm subdir and the
  **-O0 flag** via the new coverage-asserted `corpus.o0_sources()/is_o0()`; `report` → `docs/autopsy.md`).
  **Why a collect step at all (R35):** Task-12's telemetry only fills records written after it landed — 1 of
  6,169 had a `residual`, 0 had `passes_tried` — but 1,752 open near-misses had draft+`.s` on disk, i.e. ~1 s
  of CPU each. Full corpus in **21 s at -j12**; closeness cross-checked against `masked_diff.structured_diff`
  on **1,673/1,673** rows (R34), 0 classifier errors.
  **THE MEASUREMENT (byte-grounded, whole open backlog):** `redraft` 699 · `structural` 578 · `integration` 306
  · **`permuter` 75** · unknown 2. Of the **972** records the grinder's own filter admits, only **75 (7.7%)**
  are permuter-shaped — 547 structural, 348 drafts that are not the function at all. **~92% of the grinder's
  CPU has been going where a search-closer provably cannot win**, which is the byte-grounded explanation of the
  Phase-22 audit's "7 banks all-time, all Phase 21, 0 since." Fixed free: `grinder.candidates()` now filters on
  the measured bucket (**1,303 → 78**) and takes its directed `permuter_weights` profile from the measured
  class instead of the logged label (91% of records carry none → the "directed" search was silently running on
  gcc defaults). Degrades to undirected if the corpus is absent, says which mode it is in, `--no-targeting` A/Bs it.
  **Two corollaries (R14, both measured not projected):** (1) `closeness` conflates "one instruction off" with
  "this draft is a different function" — 699 records rank as near-misses at closeness up to 278 from a pure
  length artefact; they are **un-attempted work misfiled as a backlog of hard functions** (fresh crack fuel),
  so `docs/backlog.md`'s closeness ranking overstates how nearly-done the frontier is. (2) A **12-draft gate
  probe** of the `integration` bucket (reach-134, ov_SC01_077) banked **1/12**, 11 PLUMBING — so the 306
  **prices Task 14's reconcile ladder**, it is not 306 free banks. One real bank landed: **`func_80167714`
  (104 ins, reach-134) ×1**, un-propagated by design (§55b: propagate is its own batch).
  **Two defects fixed forward:** `masked_diff._common_typedefs()` used ONE shared probe path
  `src/.masked_diff_probe.c`, so N parallel `match_one`/permuter processes clobbered each other — **14 of 1,752
  drafts lost in a single 12-way run (0.8%)**, silently, in every parallel wave ever run (a drafter that
  crashes on its self-check is indistinguishable from one that failed); now per-PID. And `gate_stage`'s
  `match_one_closeness` never passed `--o0`, so every -O0 function it scored produced a phantom residual
  written straight into the backlog this autopsy reads.
  **R22 clean-fleet: `make clean && extract-all && check-all` → 140 passed, 0 failed of 140**; `make
  tools-health` OK (dedup **1847/0**, C1 234343/234343); 0 NON_MATCHING (G4). Flywheel captured in-session
  (R30/R31): cookbook **§60**, `docs/decision-log.md` entry, SETUP.md 3 inventory rows + the grinder row.
  **▶ TASK 13B RE-SCOPED BY THE DATA (the pivot):** do **NOT** run an LLM batch autopsy over the backlog — the
  deterministic classifier resolves 96% of it into three non-LLM routes, and the 75 permuter-bucket functions
  **have not yet been permuted under correct targeting**, so calling any of them a "plateau" today would be
  diagnosing a search that never properly ran (R35). Correct order: **run the directed permuter over the 75 →
  collect genuine plateaus with real `passes_tried` → only then spend the LLM on what survives.**

- **✅ 2026-07-21 — TASK 13B (first run): the directed permuter WINS on its first target; two gate
  defects fixed at the root.** Ran the newly-targeted grinder bounded (`--once --batch 8 --permute-secs 90
  --max-closeness 12`). Log: `targeting: ON — 1665 classified; only bucket=permuter is admitted` /
  `targeting skipped 1601 non-permuter candidates {redraft 707, structural 583, integration 305, unclassified
  4, unknown 2}` → **`permuter WON func_80181F78 @ ov_SC03_014 (close was 1)`** in ~6 min. **Banked 2**
  (both byte-gated): `func_80181F78` (8 ins, DELAY-SLOT/schedule) + `func_80141B90` (29 ins, IMM-VALUE/cse).
  **Both were classified `bucket=permuter` by the Task-13A classifier before the run** — it predicted a
  search-closer could reach them and one did; the first end-to-end validation of the targeting thesis.
  **THREE defects found + fixed at the root (all pre-existing, all surfaced by the grinder finally winning):**
  (1) **`gate_stage` commit path crashed** — `git add src …` with `src` deliberately never defaulted (the
  Phase 26-A audit), so EVERY caller that omits it (grinder/orchestrator/idiom_hunt) crashes the moment it
  banks. Unreachable while the grinder banked nothing since Phase 21; the targeting fix made it win and it
  crashed instantly. Now `git add -u src/` (also kills the §-lesson filename-glob hole that once omitted 4
  R22-verified banks from a commit). (2) **`_xform` ladder dirs ACCUMULATE across runs** — `-cn/-cast/-rc/-uni`
  held 34 stale drafts from earlier sessions, so the gate processed 34 when the grinder submitted **1**, and
  banked one function it was never asked to try (which would then have been committed under a message naming a
  different one). Now cleared per run. Nothing wrong entered the tree — G3/P9 held throughout, the gate banks
  only byte-identical output — but the report and the work had diverged (the R32 defect class, inverted:
  a stage silently WIDENING its input set). (3) **grinder was calling `gate_stage` with the default
  `propagate=True`** = `dedup_propagate --auto-from`, the fleet-wide path that timed out at 3600s and left
  90/140 overlays broken (§55b) — unacceptable for the unattended caller; now `propagate=False`, banks
  committed cheap, propagation left as its own targeted `--addr` batch per the §55b law.
  **R22 clean-fleet: 140/140 byte-identical.** Cookbook §60 extended; SETUP.md updated.

- **✅ 2026-07-21 — TASK 13B (full directed run): 21 fns banked, 27% conversion — and the REACH
  measurement that reprices the whole permuter track.** Ran the targeted grinder over all **77**
  permuter-bucket candidates (`--once --batch 80 --permute-secs 120 -j14 --max-closeness 30`, ~2h CPU,
  **zero tokens**). **24 permuter WINS → 21 distinct functions banked** whole-binary (3 won-but-gate-rejected
  → blacklisted WITH the reason, all PLUMBING not codegen: `func_8016EC0C`, `func_8017D880`,
  `func_800D0214`@resident). **Conversion 21/77 = 27%**, vs the ≥10% bar Drew and I set as the go/no-go.
  **The classifier's pre-run verdicts held exactly** — every bank came from the admitted bucket, by class:
  REGALLOC-PERM 7 · IMM-VALUE 6 · SCHEDULE-REORDER 6 · DELAY-SLOT 2. All four permuter classes converted.
  Landed as **20 gate auto-commits** `commit:0774`..`commit:0793` (generic `grinder gate — +N fns` messages; the
  per-commit "+N" counts are bank EVENTS — a shared fn re-banks in every binary that stubs it, so the
  running "42" is events, **21** is distinct, taken from the SOURCE not the report).
  **R22 clean-fleet: 140 passed, 0 failed of 140**; tools-health OK (dedup 1847/0, C1 234343/234343).
  **⚠️ THE REPRICING (R14 — measure the VALUE of a bucket, not just its conversion rate):** fleet moved
  **~0.03pp** (78.0% instr / 66.5% distinct, essentially flat) because the fuel is small per-overlay
  functions. h_exact reach of the 21: **only `func_80141B90` is reach-138**; TEN are reach-1 (nothing to
  propagate at all); the rest are reach 2–10. Total 178 member-instances, 138 of them from that one function.
  Instruction-weighted, **the entire permuter bucket is worth ~0.36pp at 100% conversion.** The 27% was real
  and the mechanism is validated — but I should have priced the bucket BEFORE spending 2h on it, not after.
  **THE PRICED FRONTIER (ins-weighted member-instances / 13.08M fleet denominator):**
  `LENGTH-DRIFT |Δ|≤2` **472,178 ≈ 3.6pp** (339 fns) · `integration` **419,162 ≈ 3.2pp** (305 fns) ·
  `WIDTH` 71,593 ≈ 0.55pp (45) · **permuter bucket (current) 46,571 ≈ 0.36pp** (74) · `BRANCH-POLARITY`
  9,462 ≈ 0.07pp (22). So the two real levers are LENGTH-DRIFT and the Task-14 integration ladder;
  WIDTH/BRANCH-POLARITY are NOT worth prioritizing (my earlier "~200 candidates" framing undersold
  LENGTH-DRIFT by 10× and oversold WIDTH).
  **BUILT (Drew-approved next step):** the `length` permuter profile (`permuter_weights._LENGTH` —
  `perm_temp_for_expr`/`perm_expand_expr` are the only passes that change instruction COUNT; the
  reorder/decl-order levers that dominate regalloc/schedule cannot, so they are down-weighted) +
  a magnitude-dependent route in `residual_class._drift_route` (|Δ|≤2 → permuter/`length`; larger stays
  structural) + `permuter_weights.classify()` now accepts a PROFILE NAME directly (the measured profile
  beats re-parsing a free-text label). 17 unit tests green.
  **`func_80141B90` propagated ×138** as its own targeted `--addr` batch (§55b) — 117 stubs remained after
  the gate had already banked it in ~21 binaries.

- **✅ 2026-07-21 — TASK-5 CRACK WAVE (Ultracode, 12 agents, ~2M tokens): 11/12 MATCH, 0 BANKED —
  three distinct integration walls, each now NAMED.** Fanned out over freshly-prefetched `ov_SC06_018`
  exemplars (verified-fresh: 60 candidates, known-blocked set excluded by hand after the automated
  freshness check missed `func_80135EB0` and `func_8014032C` — it matches backlog+draft-filenames only).
  **Result: 11 MATCH / 1 near**, including ALL THREE giants (`func_80191C50` 710, `func_8019059C` 673,
  `func_8018F694` 478). The near (`func_80191C50` close=9) has a precise verdict: gcc schedules the
  `D_80126B62` lui 2nd because its extra `addiu -0x38` gives that chain +1 list-scheduler priority.
  **THE WHOLE-BINARY GATE BANKED ZERO** — §58's law at its sharpest. Splicing each class individually
  (the gate label is the §58 `memcpy` red-herring, useless here) gave **THREE DIFFERENT blockers**:
  **(1) §8e-2 jtbl table-count drift — 10 of 12 drafts** (`jtbl_rodata_pads: more rodata .align
  directives than pad specs (2)`): the draft adds a switch table to a TU whose carve has a FIXED pad
  spec. **Structural finding: fresh crack fuel in a well-matched overlay CONCENTRATES in jtbl-carved TUs**
  (the non-carved ones were harvested first), so §8e-2 is not a straggler — it GATES the next tranche of
  substantial cracking. **(2) §57 self-decl conflict — the 2 plain-TU drafts** (`argument 'arg2' doesn't
  match prototype`, def vs the TU's own decl): `normalize_self_decls` exists, is wired into
  `family_sweep`, and is **NOT in `gate_stage`** — the same gap the arity pre-pass had.
  **(3) local-type redefinition** (from the Task-14 set). **So the ladder needs THREE stages; today only
  the arity pre-pass landed.** Ranked by what they unblock here: jtbl-drift (10/12) > self-decl (2/12) >
  type-lift. **All 12 drafts PRESERVED at `.run/giants/t5wave_*` (R20) — genuine cracks with per-function
  lever notes; do NOT re-draft.** Cookbook **§61a**. **Method note:** `make build | grep -i error` MISSED
  the real failure TWICE (the `jtbl_rodata_pads` line contains no "error" token; and the build failed at a
  later stage than the warnings I was reading) — **check `rc`, read the tail unfiltered.**
  Tree reverted to clean; nothing banked, nothing committed to src.

- **✅ 2026-07-21 — TASK-14 STAGE 4 (jtbl isolate+carve) BUILT + the ORDERING LAW that blocks it.**
  Diagnosed the wave's 10/12 blocker properly: **NOT "§8e-2 table-count drift"** (the symptom the filter
  reports) but a **NON-CONTIGUOUS .rodata carve** — the new function's table is separated from the TU's
  existing carve by an UNMATCHED function's table, and one object can't straddle that gap. `jtbl_carve`
  names its own remedy in the refusal. **RECIPE BYTE-PROVEN on `func_80135A4C`** (181 ins, 138 members):
  `jr_isolate_all --only <fn>` → `make extract` → splice → `jtbl_carve --func <fn>` → `make extract`
  → **BYTE-IDENTICAL** (isolation is byte-neutral by construction; verified separately).
  **BUILT:** `gate_stage._jtbl_prepare` — per-draft carve + auto-isolate on the §8b walls, logic LIFTED
  from `jtbl_family_bank` (R33), `GATE_NO_ARITY` A/B guard, snapshot-restore undo. Ladder is now
  canon → cast → reconcile_tu → **jtbl** → **arity** → gate → sig_unify → gate.
  **⚠️ IT DOES NOT YET BANK, and the reason is the finding: THE CARVE MUST FOLLOW THE SPLICE.** The
  non-contiguity is only DETECTABLE once the body is in the object; while still `INCLUDE_ASM`,
  `jtbl_carve` reports SUCCESS and yields a spec that fails once the body lands. Byte-witnessed both
  ways (spliced → `NON-CONTIGUOUS 0xaa810/0xaa920`; unspliced → `prepared 1/1` then byte-DIFF).
  A/B'd out the innocent suspects: draft transforms leave the body **IDENTICAL** through canon/cast/
  reconcile_tu, and `GATE_NO_ARITY=1` changes nothing. **FIX (next increment): per-draft prep INSIDE
  `harvest_verify`'s splice loop**, not a batch pre-pass in `gate_stage` — harvest_verify owns the
  splice. The carve/isolate/undo machinery is correct and reusable as-is.
  **Two sub-findings paid for:** (a) a wholesale `git checkout -- config/` undo (jfb.revert) is WRONG in
  a batch gate — it discarded a previously-banked-but-UNCOMMITTED carve, leaving that bank's source with
  no subseg (`undefined reference to func_80136C90`); now snapshot-restore + drop only this run's region
  files (§61's own constraint, which I had ignored). (b) being in a `_jr_*` TU ≠ having a table — only
  4 of 8 wave drafts actually reference a `jtbl_`. Cookbook **§61a corrected + §61b**.
  **Tree restored byte-identical; nothing banked this round; `func_80135A4C`'s manual bank was reverted
  with it** (its draft is preserved at `.run/giants/t5wave_*`, re-bankable by the recipe in minutes).

- **✅ 2026-07-21 — jtbl prep MOVED INTO `harvest_verify` — it BANKS automatically; new blocker named.**
  Implemented the carve-must-follow-splice law where the splice actually happens: `_jtbl_prep()`
  splices each table-bearing draft TEMPORARILY, asks `jtbl_carve`, isolates on the §8b walls,
  un-splices, re-extracts, and **re-derives the stub map + baseline** (isolation MOVES a stub's TU).
  **BYTE-PROVEN AUTOMATED:** `func_80135A4C` (181 ins, 138 members) → `[jtbl] carved 1/1` →
  `+ chunk(1)` → **verified 1 / failed 0, BYTE-IDENTICAL**, no manual steps.
  **⚠️ NEW BLOCKER (precise, byte-proven both ways): banking a jtbl core makes its own carve UNOWNED
  to `jr_inventory`, which then refuses EVERY subsequent isolation in that overlay** —
  `committed .rodata carve ownership is not 1:1 (R32/R33) … [('UNOWNED','0x801d288c')]`. On the
  COMMITTED tree `jr_isolate_all --only func_80135260 --dry-run` succeeds; with `func_80135A4C`
  banked it fails. The assertion is RIGHT (a banked fn's stub `.s` is pruned → owner lookup finds
  nobody) but its conclusion is wrong — the carve IS owned, by C rather than a stub. **So jtbl cores
  currently bank ONE PER OVERLAY.** 10-draft batch: 6 table-bearing → 1 carved, **4 isolate-FAILED**,
  1 stale-asm carve fail. **▶ NEXT INCREMENT (one precise change): resolve `jr_inventory`'s carve
  owners from `corpus.matched ∪ stubs`, not stubs alone (R33 — the same derive-don't-reparse move
  that fixed the corpus oracle). That unblocks batch jtbl banking + the 9 preserved cracks.**
  **BANK NOT KEPT:** R22 clean-fleet showed **139/140** (ov_SC06_018 fails from a CLEAN tree) though
  the INCREMENTAL build read byte-identical — the §42b stale-incremental false pass R22 exists to
  catch. Reverted; **clean-fleet re-verified 140/140**, tools-health OK (dedup 1848/0). Also cleared
  my ladder scratch dirs, which were tripping `audit-cdecl` (it scans draft dirs; agent drafts carry
  `\`-continuations it can't parse — NOT a corpus defect).
  **All 12 wave cracks preserved at `.run/giants/t5wave_*`.** Commits `commit:0800`, `commit:0801`.

- **✅ 2026-07-21 — jr_inventory ownership INVESTIGATED (the tool was RIGHT) + the CLEAN-REBUILD
  BLOCKER that stops all jtbl banking.** Drew asked to fix `jr_inventory` and bank the 9. Root-caused
  instead: **`jr_inventory`'s 1:1 ownership assertion is CORRECT and was catching MY defect.** The
  UNOWNED carve `0x801d288c` is **func_801299C8's table** — `_jtbl_prep` carved it, the gate REJECTED
  the draft, and the carve stayed with no owner (fn still `INCLUDE_ASM`), poisoning every later
  isolation in that overlay (the 4 downstream isolate-FAILs). R32/R33 working exactly as designed.
  **FIXED in `harvest_verify`:** per-function carve + exact snapshot-restore (config text + only that
  attempt's region files) on gate rejection. **SECOND FAULT FOUND:** per-function undo is UNSOUND in a
  BATCH — isolation REPARTITIONS shared source, so restoring one draft's snapshot deletes region files
  now hosting OTHER pending drafts and their stubs vanish (`KeyError` in render). jtbl drafts must run
  **one per `harvest_verify` invocation** (or the undo must be region-aware).
  **⛔ THE BLOCKER (cookbook §61c) — why the 9 are NOT banked:** the carve+isolation path yields a state
  that is **INCREMENTALLY valid and CLEAN-INVALID**. `func_80135A4C` banks every time through the
  automated path (`[jtbl] carved` → `+ chunk(1)` → BYTE-IDENTICAL at the gate) and **fails
  `make clean && extract-all && check-all` TWICE, identically (139/140, [FAIL] ov_SC06_018)**. The bank
  is therefore NOT reproducible from committed config+source, and **the gate that authorises it cannot
  see the defect because the gate IS the incremental build** (§42b in its most expensive form).
  **=> NO jtbl core can be banked until that divergence is diagnosed.** ▶ **NEXT: diff the incremental
  vs clean `build/ov_SC06_018/**` object set + the generated `.ld`/asm for the carved subseg — do NOT
  bank more until it reproduces.**
  **MEASURED (do not re-derive):** of 11 preserved cracks exactly **ONE** (`func_80135A4C`) reaches
  byte-identical through the carve path; the other 4 table-bearing ones fail **one-at-a-time too**, on
  PLUMBING (§57 self-decl et al), not the carve. **Tree reverted; clean-fleet 140/140; nothing banked.**
  All 12 cracks preserved at `.run/giants/t5wave_*`. Commit `commit:0803`.

> **🛑 SESSION-6 CHECKPOINT (2026-07-21, superseded by SESSION-7 below) — Task 13A/13B.**
> The classifier + the targeting finding: of the **972** grinder-admissible records only **75 (7.7%)**
> are permuter-shaped, so ~92% of its CPU was unreachable work. Directed run: 24 wins → **21 banked**
> (27%); `func_80141B90` propagated **×138**. Plateau autopsy: **ZERO missing-transforms** — the
> plateaus are wrong drafts, so the win was NARROWING admission (permuter bucket 389→84), not widening
> the mutation set. Commits `commit:0771`, `commit:0772`, `commit:0796`, `commit:0794`.

> **🛑 SESSION-7 CHECKPOINT (2026-07-22) — THE CURRENT ONE; safe to open a FRESH session here.**
> Tree clean (only R23 `db.*.gbf` churn + preserved drafts). **R22 clean-fleet 140/140 byte-identical**;
> `make tools-health` OK (dedup 1848/0, C1 234481/234481); 0 NON_MATCHING (G4). HEAD `commit:0804`.
> **Fleet 78.0% instr · 66.5% distinct-code · 87.9% fn-count** (flat this session — see "banked: 0").
> **Drew pushes** all commits (R6/R20).
>
> **THIS SESSION (after 13A/13B): Task-14 stage 1, Task 5, a 12-agent wave, and the jtbl campaign.**
> * **Task 14 stage 1 — the ARITY pre-pass** (`commit:0797`): diagnosed from REAL cc1 stderr (the gate's
>   own `memcpy` label is the §58 red-herring, 10/11 identical). Banks **2 of 7** vs a **1/12**
>   baseline. **NEW HARD CONSTRAINT (§61):** any ladder stage mutating SHARED state must undo by
>   SNAPSHOT-RESTORE, never an inverse transform, and be verified FLEET-WIDE — it broke 138/140 once.
> * **Task 5 — Ghidra-C prefetch** (`commit:0798`): `ov_SC06_018` imported, **101 stubs decompiled**
>   (cache 882→983). Scoping corrected my own claim: the substantial mass is **1,398 h_seq families**;
>   **340 (7.72pp) are already-attempted/walled**, **1,058 (5.40pp) fresh**, and the 877 needing a
>   prefetch have **median 1 member** (overlay-unique) → prefetch is PER-OVERLAY, one import ≈ 1.59pp.
> * **The wave** (`commit:0799`): 12 agents, ~2M tokens → **11 MATCH / 1 near**, incl. all 3 giants
>   (710/673/478). **Gate banked ZERO.** All 12 preserved at `.run/giants/t5wave_*` — **DO NOT re-draft.**
> * **jtbl campaign** (`commit:0800`, `commit:0801`, `commit:0803`): the carve-must-follow-splice law
>   implemented in `harvest_verify` (temporary splice → carve → isolate → un-splice → re-extract →
>   re-derive stub map). `jr_inventory`'s ownership assertion was **RIGHT** — it caught MY stranded
>   carve. Fixed per-function snapshot-restore; found per-function undo is unsound in a batch
>   (isolation repartitions shared source).
>
> **⛔ THE ONE BLOCKER, AND THE SINGLE NEXT TASK (cookbook §61c):** the jtbl carve+isolation path is
> **INCREMENTALLY VALID AND CLEAN-INVALID.** `func_80135A4C` banks every time at the gate
> (BYTE-IDENTICAL) and **fails `make clean && extract-all && check-all` TWICE, identically**
> (139/140, `[FAIL] ov_SC06_018`). The gate cannot see it **because the gate IS the incremental
> build** (§42b, worst form). **NEXT: diff the incremental vs clean `build/ov_SC06_018/**` object set
> + the generated `.ld`/asm for the carved subseg. Do NOT bank any jtbl core until it reproduces.**
>
> **BANKED THIS SESSION: 0.** 21 came from 13B earlier; everything after is tooling + findings.
> Reported as zero, not rounded up.
>
> **MEASURED, do not re-derive:** of 11 preserved cracks exactly ONE reaches byte-identical via the
> carve path; the other 4 table-bearing ones fail **one-at-a-time too**, on §57 plumbing, not the carve.
> The remaining wave drafts' blockers are §57 self-decl + local-type redefinition → **Task 14 stages
> 2–3** (`normalize_self_decls` and the type-lift are wired into `family_sweep` but NOT `gate_stage`).
>
> **PHASE STATE:** remaining frontier **22.0pp** (substantial 80–1000 ins = 12.84pp · mid 16–79 =
> 8.60pp · behemoths 0.28pp · small 0.25pp). Remaining tasks: **§61c diagnosis (gates all jtbl)** ·
> Task 14 stages 2–3 · Task 4 remainder · Task 7 ROI-close · ~11 un-propagated small banks · the
> −O0 rollout (splat wall) · 2 permanent giant walls.
> **Effort:** xHigh is fine for the §61c diagnosis (settled shape); prompt **Max** if it turns into
> non-obvious debugging. **3 stuck self-matching `pgrep` waiters** may still be sleeping (harmless;
> kill by PID if seen).

- **✅ 2026-07-22 — §61c REFUTED: the "clean-invalid jtbl bank" blocker does not exist; `func_80135A4C`
  (181 ins) BANKED ×1 and clean-fleet-verified TWICE.** The session-7 checkpoint gated the whole jtbl
  track behind a single finding: the carve+isolation path yields a bank that is incrementally valid and
  clean-invalid (139/140, `[FAIL] ov_SC06_018`, "twice, identically"). **The diagnosis never reached the
  prescribed object diff, because the failure does not reproduce.** Applying the bank through the
  single-function automated path (`harvest_verify --binary ov_SC06_018 --chunk 1` → `[jtbl] carved
  func_80135A4C` → `+ chunk(1)` → BYTE-IDENTICAL) and then measuring:
  **per-binary clean** (rm asm+build for the overlay → extract → build) → BYTE-IDENTICAL `cbbc4f44…`;
  **`make clean && extract-all && check-all` run 1 → 140 passed, 0 failed of 140**; **run 2 (independent)
  → 140 passed, 0 failed of 140.** So the state the incremental gate blesses IS what a clean pipeline
  reconstructs — no extraction-order effect, no mid-flow asm.
  **Attribution (best-supported, not byte-proof — the failing tree is gone):** the 139/140 runs were taken
  on the tree left by the *batch* `_jtbl_prep` (`6 table-bearing → 1 carved, 4 isolate-FAILED, 1 stale-asm
  carve fail`), i.e. five failed preps' residue of stranded carves + half-applied isolations. The
  per-function snapshot-restore that removes exactly that residue landed **after** those runs, in
  `commit:0803` — the same commit that named the blocker.
  **THE LESSON (R35 turned on ourselves, → decision-log):** "twice, identically" was not a replication —
  it was two reads of the SAME contaminated state, which is one observation. A replication must RE-CREATE
  the state, not re-run the check. Standing guard, one command: **before writing a fault down as a property
  of a mechanism, re-apply it from a known-clean tree.** This is the sixth "structural wall" to resolve to
  our own tree/tooling (B2 · SC07 · pin-crash · the ~3% -O0 artifact · grinder targeting · this) — the base
  rate now justifies making "our own state or instrument" the FIRST hypothesis for any new wall.
  **Faults 1-2 of §61c stand** (a stranded carve poisons the overlay; per-function undo is unsound in a
  batch because isolation repartitions shared source) → the standing constraint is **one jtbl draft per
  `harvest_verify` invocation** until the undo is region-aware. `jr_inventory`'s 1:1 ownership assertion
  was RIGHT (already settled in `commit:0804`) and needs no change.
  **BANKED:** `func_80135A4C` ×1 in ov_SC06_018 (isolated into the new `ov_SC06_018_jr_80135A4C` code
  subseg + its own `.rodata` carve; single-table, so no `JTBL_PADS` var; `tail3..tail18` renumbered).
  **R22 clean-fleet 140/140 byte-identical ×2; `make tools-health` OK** (corpus 0 PHANTOM/0 TRUNCATED,
  cdecl ALL ORACLES GREEN 53189/53189, audit-binaries 140 citizens, **dedup 1848/0, C1 234481/234481**);
  **0 NON_MATCHING (G4)**. Fleet **78.0% instr · 66.5% distinct-code · 87.95% fn-count** (a ×1 bank; the
  fleet mover is the sweep below).
  **▶ THE UNFROZEN WORK, ranked:** (1) `func_80135A4C`'s family is **138 members / PURE / 24,978 ins ≈
  +0.19pp** — sweep it via `jtbl_family_bank` (§53 carve law; `has_mid_jr: true`). (2) The **9 remaining
  preserved t5wave cracks** (`.run/giants/t5wave_*`, ~2M agent tokens — do NOT re-draft): of the 11, one
  (this one) banks via the carve path and 4 table-bearing ones fail one-at-a-time on §57 self-decl /
  local-type plumbing = **Task 14 stages 2-3**, not the carve.
  **Housekeeping:** killed an orphaned `cc1` from the Jul-21 session that had been burning a full core for
  **13h23m** (pid 104350, dead pipe); committed the 4 wave-4 `.o0` drafts left untracked (R20).

- **✅ 2026-07-22 — THE FAMILY SWEEP (138/138) + THE RE-PROBE: a giant recovered, TWO tree-eating tool
  defects found and fixed, and `gate_stage`'s jtbl pre-pass DELETED.**
  **(a) `func_80135A4C` family COMPLETE ×138** (probe 1 → chunks 45+45+46, commit per chunk, `git add -A`).
  **137/137 siblings banked, 0 failed** — 100% conversion, exactly as its PURE/`n_templatable:137`
  classification predicted. **R22 clean-fleet 140/140.** Fleet **78.0→78.2% instr · 66.5→67.0% distinct ·
  87.95→87.98% fn-count** (+25,329 ins; predicted +24,797 — the measurement matched the prediction).
  **(b) THE UNDO WAS EATING THE TREE (the §61c mechanism, byte-witnessed).** `jr_isolate_all` repartitions
  a code object by writing region 0 back over the ORIGINAL `src/<ov>/<nm>.c` **truncated**, emitting the
  rest as new `_jr_*.c`. `harvest_verify._jtbl_restore` undid only `config/` + the new region files → every
  gate-REJECTED draft permanently ate that TU's stubs, and **nothing regenerates them** (splat does not
  rewrite a committed overlay `.c`). Measured live across the first re-probe: live stubs **419 → 414 → 406
  → 395**, ending in `undefined reference to func_80191C50`. **Invisible to the gate that causes it** — the
  incremental build keeps linking stale objects (§42b) so `make build` stays green while a CLEAN rebuild
  fails. That is precisely the "139/140, twice" signature, so the §61c attribution is now a **demonstrated
  defect, not an inference**. FIXED: `_jtbl_snapshot` captures every `src/<binary>/*.c`; `_jtbl_restore`
  restores them + deletes exactly the files the attempt created (derived from the snapshot's file set, R33).
  Negative-control-validated: the same failing draft now leaves the tree byte-identical and `git status` clean.
  **(c) THE GATE LABEL WAS A CONSTANT.** `classify_fail` searched the whole stderr, so the benign
  `warning: conflicting types for built-in function 'memcpy'` won on **8 of 8** failures across four
  different real causes — the §58 red-herring the cookbook had been working around by hand. Now classifies
  on NON-warning lines and falls through to `CC1-FAIL:<last error>`. Same failure immediately became
  `ov_SC06_018.c:447: prototype declaration`.
  **(d) THE RE-PROBE (11 preserved t5wave cracks, one `harvest_verify` invocation each).**
  **BANKED: `func_8018F694` (478 ins)** — one of the wave's three giants, previously inside "the gate banked
  ZERO". The other 10 gave **ten DISTINCT** diagnoses: **4 data-decl** (`D_80193B64`×2, `D_8011D030`,
  `D_80126B5C`) · **3 callee-decl** (`func_80135480`×2, `func_8012F14C`) · **3 self-decl/own-sig** (§57).
  **ZERO jtbl-drift · ZERO local-type redefinition · ZERO codegen DIFF** — so **§61a's "§8e-2 jtbl
  table-count drift blocks 10 of 12" does NOT survive** the carve-follows-splice prep: the carve now
  succeeds and what remains is ordinary decl plumbing.
  **(e) `gate_stage._jtbl_prepare` DELETED (R33), not patched.** It carried the SAME config-only undo and
  ate the tree again on the first ladder run (5 orphan region files, truncated TUs, `undefined reference to
  func_80192F64`) — which **invalidated that run's 0/10**, so it was re-measured, not reported (R35). It was
  wrong on two axes: §61b had already byte-proved the carve must FOLLOW the splice (a pre-pass carving
  unspliced functions yields a spec that fails when the body lands), and `harvest_verify` now does the
  correct per-draft prep one layer down. Two implementations of one capability, the outer one ineffective
  AND destructive → delete.
  **(f) THE HONEST LADDER MEASUREMENT (clean tree, tree verified clean after):** **0/10 bank**; **9/10 now
  COMPILE** and land as whole-binary byte-DIFF, **1/10** still plumbing. `match_one` reports **close=0** on
  several (the function's own bytes exact) and `rtu_match` says **MATCH in the real TU** for
  `func_80135888` — while `func_801299C8`'s transformed draft does not compile in its real TU at all. So the
  residual is **MIXED, not uniform**, and at least one is an IMAGE-level effect rather than the draft or its
  TU decl context. **Not generalized from one data point** — the next increment is to identify what changes
  at the image level for a close=0/rtu-MATCH function (prime suspect: the jtbl/rodata carve placement).
  **This prices Task 14 stages 2-3 with a measurement, not a projection:** the existing ladder converts
  **0/10** of these residuals, so stages 2-3 are NOT "wire in `normalize_self_decls` + the type-lift and
  collect 10 banks."
  **VERIFIED:** R22 clean-fleet **140/140 byte-identical** (post-sweep) + a final clean-fleet after the
  giant bank; `tools-health` OK (dedup 1848/0, C1 234481/234481, cdecl 53189/53189, audit-binaries 140);
  0 NON_MATCHING (G4). Nothing was ever committed broken — both times the tree was eaten it was restored
  from HEAD and re-verified byte-identical BEFORE any further work.
  **Housekeeping:** cookbook — the `git add -u` complementary hole (an isolation's NEW region file is
  untracked → a carve/isolation bank needs `git add -A src/ config/`; `jtbl_family_bank`'s uncommitted-tree
  guard is what caught it).

> **🛑 SESSION-8 CHECKPOINT (2026-07-22) — supersedes SESSION-7; safe to open a FRESH session here.**
> Tree clean (only R23 `db.*.gbf` churn). **R22 clean-fleet 140/140 byte-identical** (run 3× this session);
> `make tools-health` OK (dedup 1848/0, C1 234481/234481, cdecl 53189/53189, audit-binaries 140 citizens);
> 0 NON_MATCHING (G4). HEAD `commit:0812`. **Drew pushes** all commits (R6/R20).
> **Fleet 78.2% instr · 67.0% distinct-code · 87.98% fn-count** (opened 78.0/66.5/87.9).
> **Banked: +138 function-instances = +25,275 ins** — exactly 137×181 (the `func_80135A4C` family) + 478
> (the giant `func_8018F694`). Predicted and measured agree to the instruction.
>
> **THE HEADLINE: §61c — the phase's single named blocker — IS REFUTED, and the real defect it was hiding
> is FIXED in two tools.**
> * §61c claimed the jtbl carve path yields a bank that is incrementally valid and clean-invalid ("139/140,
>   twice"). **It does not reproduce:** per-binary clean BYTE-IDENTICAL; `make clean && extract-all &&
>   check-all` **140/140, twice, independently.**
> * The real defect, byte-witnessed: **`jr_isolate_all` truncates the ORIGINAL `src/<ov>/<nm>.c`** when it
>   repartitions, and BOTH `harvest_verify._jtbl_restore` and `gate_stage._jtbl_prepare` snapshotted only
>   `config/` — so every REJECTED draft permanently ate that TU's stubs (measured: 419→414→406→395 →
>   `undefined reference`). **Invisible to the byte-gate**, because the incremental build keeps linking
>   stale objects (§42b) while a clean rebuild fails. That is exactly the "139/140" signature.
> * Fixed in `harvest_verify` (full src snapshot-restore, negative-control-validated); **DELETED** from
>   `gate_stage` (R33 — §61b had already byte-proved the batch pre-pass cannot work, and harvest_verify does
>   it correctly one layer down). Also fixed: `classify_fail` was returning a CONSTANT label (the §58
>   `memcpy` warning won on 8/8 failures across four real causes).
>
> **THE RE-PROBE (Drew-directed) — 11 preserved t5wave cracks, one invocation each:**
> **`func_8018F694` (478 ins) BANKED.** The other 10 gave TEN DISTINCT diagnoses: **4 data-decl · 3
> callee-decl · 3 self-decl**; **ZERO jtbl-drift, ZERO local-type redef, ZERO codegen DIFF** — so §61a's
> "§8e-2 jtbl drift blocks 10 of 12" does **not** survive the carve-follows-splice prep.
> Through `gate_stage`'s ladder (honest re-measurement on a clean tree): **0/10 bank**, **9/10 now COMPILE**
> and land as whole-binary byte-DIFF, 1/10 plumbing. `match_one` close=0 on several; `rtu_match` MATCH-in-
> real-TU for `func_80135888`; `func_801299C8` does not compile in its real TU at all → the residual is
> **MIXED**, and at least one is an IMAGE-level effect (prime suspect: jtbl/rodata carve placement).
>
> **▶ THE SINGLE NEXT TASK:** for a close=0 / rtu-MATCH residual (`func_80135888` is the clean specimen),
> find what changes at the IMAGE level when it is spliced — diff the built image / `.ld` / the carved
> subseg's placement against the un-spliced build. That decides whether the 9 are a carve-placement class
> (one fix, nine banks) or nine separate residuals. **Do not** wire more transforms into the ladder first:
> measured, it converts **0 of 10**, so Task 14 stages 2-3 are not the ten free banks the backlog implies.
>
> **STANDING CONSTRAINTS:** one jtbl draft per `harvest_verify` invocation (isolation repartitions shared
> source). A carve/isolation bank must commit with **`git add -A src/ config/`** — `-u` misses the new
> region file. **Never measure while a background job mutates the tree** (a mid-run `progress.py` reading
> misled me by 54 ins this session).
> **Effort:** xHigh is right for the image-level diff (settled shape); prompt **Max** if it becomes
> non-obvious root-cause work.
> **Preserved (R20, do NOT re-draft):** all 12 t5wave cracks at `.run/giants/t5wave_*` (~2M agent tokens);
> 10 of them now carry a precise per-function blocker.

- **✅ 2026-07-22 (cont.) — THE RECOMMENDED DIAGNOSIS: there is no image-level difference. The ISOLATION
  must follow the splice too. 5 of the 11 preserved cracks now banked.**
  **(a) THE ANSWER.** Performed by hand, `func_80135888` builds **BYTE-IDENTICAL** (R22 clean-fleet 140/140):
  `splice → jtbl_carve (NON-CONTIGUOUS) → jr_isolate_all --only <fn> **WITH THE BODY STILL SPLICED** →
  make extract → jtbl_carve → make extract → build`. The draft was never wrong and neither was the carve.
  The ladder path differed by ONE line: `_jtbl_prep_one` **un-spliced before isolating**, so
  `jr_isolate_all` partitioned a TU whose function was still `INCLUDE_ASM`. It accumulates each object's
  file-scope decls as the new region's `ambient` set, so partitioning around a STUB hands the region a
  different decl context than the body needs — surfacing as a **byte-DIFF, not a compile error**, which is
  exactly why the batch read as "9 compile / 0 bank" and looked like a codegen wall.
  **→ §61b's law extends one step: THE CARVE MUST FOLLOW THE SPLICE — AND SO MUST THE ISOLATION.**
  (Third layer of one root cause this session: carve-before-splice, an undo narrower than its write scope,
  and now isolate-around-a-stub. All three presented as compiler walls; all three were ours.)
  **(b) FIXED** in `harvest_verify._jtbl_prep_one` + new `_unsplice_body()` (the un-splice existed only
  because the tool is stub-centric; it now finds the file that NOW holds the body — isolation may have
  MOVED it — and restores the stub line for THAT subseg, so the gate re-splices identical text).
  **(c) BANKED — 5 of 11 preserved t5wave cracks** (each whole-binary gated, one per invocation, R22
  clean-fleet 140/140 after each batch): `func_8018F694` (478) · `func_80135888` (113, reach 138) ·
  `func_80135D20` (100, reach 138) · `func_801749C8` (105, reach 136) · `func_8019059C` (673, a giant).
  **(d) THE REMAINING 6, honestly classed:** 2 genuine **DIFF** (`func_80135260`, `func_80191C50`) · 2
  **CC1-FAIL** (`func_801365B8`, `func_80165CA0`) · 2 **§57 self-decl** (`func_801299C8` "prototype
  declaration", `func_8012AAAC` own-name conflict). A real residual, not a tooling artifact.
  **(e) ⚠️ RETRACTED: "the ladder converts 0/10, which prices Task 14 stages 2-3."** WRONG, withdrawn.
  Three of those ten bank through `harvest_verify` alone using **gate_stage's own final-stage draft** —
  so the 0/10 measured gate_stage's interference, not the residuals. **Task 14 stages 2-3 are UNPRICED.**
  **(f) ▶ THE OPEN QUESTION (the next task): `gate_stage` REJECTS drafts its own byte-gate ACCEPTS.**
  Both hypotheses are **untested**: the arity pre-pass A/B (`GATE_NO_ARITY=1`) came back STILL-STUBBED but
  was **CONFOUNDED** — gate_stage **re-transforms an already-transformed input** (feeding it `-s2in-uni`
  produced `ab-cn`, `ab-cn-cast`, … on top), so that run tested a doubly-transformed draft and establishes
  nothing. Candidate causes: (i) the transforms are **not idempotent** (§19 already found `sig_unify`
  regresses already-canonical drafts); (ii) **tree-state residue** across the ladder's multiple `_gate1`
  calls (earlier stages' jtbl preps applied/undone) means the winning draft is gated against a different
  tree than a fresh invocation. **Design the A/B so gate_stage gets a RAW draft in both arms.**
  **Until then: use `harvest_verify` DIRECTLY for jtbl-class drafts** — it is the proven path.
  **(g) Diagnostic gap noted:** `gate_stage` captures `harvest_verify`'s stdout, so the `[jtbl]` prep lines
  are invisible in its logs — which is why this took a direct run to see.
  **Fleet: 78.2% instr · 67.0% distinct · 87.99% fn-count** (10,234,240 ins).

- **✅ 2026-07-22 (cont.) — THE SWEEP: 2 of 5 families swept ×137 (274 siblings, ~29.2k ins); 3 REFUSED,
  informatively. Fleet 78.2→78.5% instr · 67.0→67.5% distinct.**
  **SWEPT COMPLETE (0 failures, commit per chunk, `git add -A`):** `func_80135888` **137/137** (~15.5k ins)
  · `func_80135D20` **137/137** (~13.7k ins). Both via `jtbl_family_bank` (§53: table-bearing → the carve
  path). **R22 clean-fleet 140/140 byte-identical.**
  **REFUSED — and the refusals are the finding:**
  * `func_801749C8` (105 ins × 135) — **I MIS-ROUTED IT** to `jtbl_family_bank`; it references **no
    `jtbl_` at all** (the re-probe had already recorded `jtbl_lines=0`; its siblings merely LIVE in
    `_jr_*` TUs, which is not the same thing — the §53 carve law in reverse). `jtbl_carve` refused loudly
    (`references no jtbl_ (not a jr/switch function?)`), `jtbl_family_bank` reverted per sibling, cost =
    time only. Re-routed to the plain `family_sweep --hseq`: **staged 135, banked 0.**
  * `func_8019059C` (2 siblings) gate-fail · `func_8018F694` (2 siblings) gate-fail.
  **THE FINDING (worth more than the 0.02pp the small ones represent): a PURE family does NOT imply a
  mechanical ×N.** `func_801749C8` is `diff_class: PURE`, `has_mid_jr: false`, `n_templatable: 135`,
  `n_matched: 3` — the classifier's best case — and it stages all 135 and banks **zero**. This is §57a's
  "staging ≠ banking" law reappearing on a family the manifest predicts should template, i.e. the
  manifest's `n_templatable` remains a PREDICTION the whole-binary gate is free to refuse (the Phase-26
  ≈0% lesson, same shape). **Blocker undiagnosed — do NOT bill it as available yield.**
  **TOOLING ANSWER (Drew's question — the offline-tooling-first rule):** three items, different states.
  **(1) DONE:** the isolate-with-body fix + the full-src snapshot/restore are IN `harvest_verify` (they
  were computable, so they are in the tool, not in prose). **(2) LATENT, evidence-gated:**
  `jtbl_family_bank` isolates AROUND THE STUB (the body is spliced later, after `remap_hseq`) — the same
  ordering defect just fixed in `harvest_verify`. It did **not** fire across 274 swept siblings this
  session (isolation only triggers on the §8b walls), so it is latent, not universal; fixing it on theory
  after a 274/274 run would be the very error this phase keeps catching. **Fix it when a sweep fails with
  the signature (isolation fires → gate DIFF), not before.** **(3) BLOCKED:** "route jtbl-class drafts to
  `harvest_verify` directly, not `gate_stage`" is still prose, correctly — it is a routing rule, and
  routing IS computable, but the REASON gate_stage rejects what its own gate accepts is undiagnosed, and
  encoding a workaround before knowing the cause bakes in a guess.

> **🛑 SESSION-9 CHECKPOINT (2026-07-22) — supersedes SESSION-8; safe to open a FRESH session here.**
> Tree clean (only R23 `db.*.gbf` churn). **R22 clean-fleet 140/140 byte-identical** (verified 6× today);
> `make tools-health` OK (dedup 1848/0, C1 234481/234481, cdecl 53189/53189, audit-binaries 140);
> 0 NON_MATCHING (G4). **Drew pushes** all commits (R6/R20).
> **Fleet 78.5% instr · 67.5% distinct-code · 88.1% fn-count** (opened 78.0/66.5/87.9 → **+0.5pp instr,
> +1.0pp distinct**). Banked today: the `func_80135A4C` family ×138, 5 preserved t5wave cracks, and
> `func_80135888`/`func_80135D20` ×137 each.
>
> **THE THROUGH-LINE: three layers of ONE root cause, all of which had been recorded as compiler walls.**
> (1) carve-before-splice (§61b) · (2) an undo whose scope was narrower than its write scope (§61d) ·
> (3) isolation performed around a STUB. Each surfaced as a byte-DIFF, and each was invisible to the
> byte-gate because the incremental build keeps linking stale objects (§42b) while a clean rebuild fails.
> **§61c is REFUTED; the law is now: THE CARVE MUST FOLLOW THE SPLICE — AND SO MUST THE ISOLATION.**
>
> **▶ NEXT TASK (highest value, non-mechanical): DIAGNOSE `gate_stage`.** It rejects drafts its own
> byte-gate accepts — 3 functions banked through `harvest_verify` alone using **gate_stage's own
> final-stage draft**. Both hypotheses are UNTESTED: the `GATE_NO_ARITY=1` A/B was **CONFOUNDED**
> (gate_stage RE-TRANSFORMS an already-transformed input — feeding it `-s2in-uni` produced `ab-cn`,
> `ab-cn-cast`, … on top). **Design the A/B so gate_stage receives a RAW draft in both arms.** Candidates:
> non-idempotent transforms (§19: `sig_unify` regresses already-canonical drafts) or tree-state residue
> across its multiple `_gate1` calls. This gates the offline-tooling routing rule AND silently suppresses
> conversions in every future wave.
> **Then:** `func_801749C8`'s PURE-but-0/135 blocker · Task 7 (burn-down + ROI-gated close + fix the
> STALE CHECKBOXES: Tasks 2/3/6 are logged complete but still show `[ ]`).
>
> **⚠️ RETRACTED THIS SESSION (do not re-use):** "the ladder converts 0/10, which prices Task 14 stages
> 2-3" — it measured gate_stage's interference, not the residuals. **Stages 2-3 are UNPRICED.**
> **MEASURED, do not re-derive:** a **PURE** family does not imply a mechanical ×N (`func_801749C8`:
> PURE, `has_mid_jr:false`, `n_templatable:135`, stages 135, banks **0**) — `n_templatable` is a
> PREDICTION the gate may refuse. The 2 remaining 700-ins giants are **reach-3** (~0.03pp) — reach, not
> size, is the multiplier.
> **6 preserved cracks remain** (2 DIFF, 2 CC1-FAIL, 2 §57 self-decl) at `.run/giants/t5wave_*` — do NOT
> re-draft. **Effort:** xHigh for the gate_stage A/B; prompt **Max** if it turns into deep debugging.

- **✅ 2026-07-22 (cont.) — TASK 7 BURN-DOWN + the zero-crack sweep track. Fleet 78.5→78.6% instr ·
  67.5→67.9% distinct.**
  **BURN-DOWN INSTRUMENT LIVE** (`tools/burndown.py`, snapshots in `docs/burndown.jsonl`, git-HEAD-keyed).
  Two snapshots seeded this session. **FLOOR VERDICT NOT AVAILABLE — the tool requires ≥3 inter-commit
  deltas and has 2.** So the phase-close cannot yet be justified on "yield floored out", and my earlier
  eyeballed "+2.5 → +1.1 → +0.6 → +0.2pp" trend is NOT the instrument's verdict — do not close on it.
  **THE FRONTIER (measured, and independent of the gate_stage SHA bug — `family_hseq` derives from sigs +
  source, not from the gate):** substantial = **568 families / 1,500,308 templatable ins (~11.5pp)**, of
  which **70 are matched-sibling ZERO-CRACK sweeps worth ~2.6pp** (no drafting, no agents) and ~498 need
  a fresh crack.
  **SWEPT THIS BLOCK:** `func_801299C8` **137/137, 0 failed** (~21.6k ins) — a family that became
  sweepable ONLY because the gate_stage SHA fix let it bank ×1 an hour earlier. **This is the compounding
  effect: every ×1 bank converts a family into free sweep fuel**, so the zero-crack pool is fed by the
  crack track rather than being a fixed stock.
  **REFUSED — `0x8013C414` (329 ins ×137 = 45,073, the single LARGEST zero-crack item): 3/3 gate-fail**,
  the predicted **-O0 cluster wall** (members compile -O2; the fix is the per-overlay -O0 carve that hit a
  splat byte-shift wall on 3 of 4 overlays in Task-2 Arm A). **So the ~2.6pp zero-crack figure must be
  DISCOUNTED by this item until the -O0 rollout is solved.** The 3-member probe settled it in ~1 minute
  instead of a 40-minute full sweep — the probe-before-scaling invariant paying for itself.
  **⚠️ TOOL DEFECT FOUND (fix next): `jtbl_family_bank`'s per-sibling revert leaves the tree GIT-CLEAN BUT
  UNBUILDABLE.** After the failed probe, `git status` was empty yet `ov_SC01_004` failed to link
  (`undefined reference to jtbl_8018DAC8`): the revert restores `config/` from git but does NOT re-extract,
  so the on-disk asm stays stale — and `git status` is structurally blind to that (the R22 corollary, now
  inside a tool's own undo path). It also emitted `error: pathspec '…_jr_8013C414.c' did not match any
  file(s) known to git` while trying to `git checkout` a file the isolation had created but never tracked.
  Recovered by `make extract` per overlay (all 3 byte-identical). **Fix: the revert must re-extract, and
  must delete untracked region files rather than git-checkout them.**
  **OBSERVED PATTERN (2 data points, NOT yet a rule): a zero-crack family either sweeps ~100% or refuses
  wholesale** — 137/137, 137/137, 138/138, 137/137 vs 0/135, 0/3. No partial middle so far. Worth
  confirming across more families before relying on it for planning.

- **✅ 2026-07-22 (cont.) — ZERO-CRACK SWEEP TRACK + the revert fix + the FLOOR-VERDICT correction.**
  **SWEPT/PROPAGATED:** `func_801299C8` **137/137** (~21.6k ins) · `func_80167714` **×134** via
  `dedup_propagate --addr` (h_exact; the 4 SC07 overlays byte-diverge and were correctly excluded,
  kept ×1). **REFUSED (3-member probes, ~1 min each vs a 40-min full sweep):** `0x8013C414` **0/3**
  (the -O0 cluster wall — and it is the LARGEST zero-crack item at 45,073 ins, so the ~2.6pp headline
  must be discounted by it) · `0x8013C0F8` **0/3**.
  **PATTERN (5 sweeps vs 3 refusals, still a heuristic not a law): a zero-crack family either sweeps
  ~100% or refuses WHOLESALE — no partial middle**, and a 3-member probe has predicted the family every
  time. That makes the remaining ~65 zero-crack families cheap to TRIAGE even though their aggregate
  yield is clearly well under the 2.6pp headline.
  **TOOL FIX — `jtbl_family_bank.revert` left the tree GIT-CLEAN BUT UNBUILDABLE:** restoring `config/`
  from git does not rewind `asm/`, and within a sweep each sibling is a DIFFERENT overlay, so the next
  sibling's extract never repairs the previous one. `revert()` now re-extracts (`extract=False` only at
  the clean-slate call, which extracts anyway) and only `git checkout`s TRACKED paths (an isolation's new
  region files were emitting `error: pathspec ... did not match any file(s) known to git`).
  **Negative-control-validated:** the same probe still gate-fails 3/3, and all 3 overlays now build
  BYTE-IDENTICAL with a clean `git status`.
  **⚠️ THE FLOOR VERDICT WAS AN ARTIFACT — CORRECTED.** `burndown.py` averaged the last 3 INTER-COMMIT
  deltas, but the ROI criterion is per-SESSION yield. Three mid-session snapshots of a **+0.7pp** session
  averaged to **+0.23** and printed **"AT THE FLOOR — consider closing P29"**. **I nearly closed the phase
  on it.** Fixed: `--session-close` marks a session boundary and the verdict uses ONLY those; honest
  output is now "0 SESSION-to-SESSION delta(s) logged — need >=3". **P29 must NOT close on ROI grounds:
  the floor is UNDETERMINED and needs 3 session closes to become computable.**
  **⚠️ PROCESS: I left two `while pgrep -f <pat>; do sleep; done` waiters spinning** (one for 4 h) — they
  self-match their own `bash -c` command line and can never exit. The SESSION-7 checkpoint had warned
  about exactly this, and the standing rule is no sleep-polling (the harness notifies). Killed; harmless
  to the work, but do not write them.

- **✅ 2026-07-22 (cont.) — ZERO-CRACK VEIN BYTE-PROVEN TAPPED + main folded into the weighted denominators.**
  **THE SWEEP VERDICT (4 refusals in a row, ~137 members each — no partial middle):** `func_801749C8`
  **0/135** · `0x80144090` **0/136** · `0x801365B8` **0/133** · `0x80133AB0` **0/137**. Against the day's
  4 successes at 137-138/138. **THE DISCRIMINATOR IS NOT THE FAMILY'S `PURE` CLASS — IT IS THE EXEMPLAR'S
  PROVENANCE:** every success templated from a core **freshly banked ×1 today** (`jtbl_family_bank`);
  every refusal templated from an **ov_SC01_077** exemplar (`family_sweep --hseq`). This CONFIRMS §57a
  ("the substantial-family frontier is NOT broadly mechanical") rather than contradicting it.
  **⇒ The remaining zero-crack pool (61 families / 166,769 ins / 1.27pp after excluding 7 done + 7
  refused) is LARGELY UNAVAILABLE via the h_seq sweep path. Do not bill it as yield. Stopped after 4
  refusals rather than proving it 57 more times.**
  **⇒ STRATEGIC INVERSION (the day's most useful planning finding): sweeps only pay when they RIDE a
  fresh ×1 crack. Cracking is the GENERATOR of sweep fuel, not a parallel track.** The compounding loop
  demonstrated today: `func_801299C8` banked ×1 (only possible after the gate_stage SHA fix) → immediately
  swept 137/137. So P29 item 1 (core cracks) should drive item 2, and the honest fuel source is the
  **per-overlay Ghidra-C prefetch** (Task 5 measured `ov_SC06_018` alone at 1.59pp of fresh families;
  it is imported, and ~89 of its 101 cached substantial stubs are still undrafted).
  **METRICS CONTRACT MET (roadmap §1):** `progress.py` now folds **main into the weighted denominators**.
  It had been a separate provisional line since Phase-27 T10, so the headline silently measured 139 of 140
  binaries — omitting the least-decompiled one. **instr 78.7% → 78.4% · distinct 67.9% → 67.1%** (the
  headline DROPS; that is the point). A continuity line keeps the ex-main figure comparable; the
  binary-count label is corrected ("resident+139 overlays" → "main + resident + 138 overlays").
  **Caveat restated precisely:** main's numbers do NOT drift (boundaries come from the fixed original
  bytes; matched-state from the live `corpus.stubs`) — the real limitation is **R34**: `sig_image` cannot
  independently validate a PS-X EXE, so main has no second, disagreeing oracle. The LINKED-PsyQ exclusion
  is correct for a GAME-CODE contract.

> **🛑 SESSION-10 CHECKPOINT (2026-07-22) — supersedes SESSION-9; safe to open a FRESH session here.**
> Tree clean (only R23 `db.*.gbf` churn). **R22 clean-fleet 140/140 byte-identical** (verified 9× today);
> `tools-health` OK (dedup 1848/0, C1 234481/234481); 0 NON_MATCHING (G4). **Drew pushes** (R6/R20).
> **Fleet (main NOW INCLUDED, roadmap §1): 78.4% instr · 67.1% distinct · 88.14% fn-count.**
> Ex-main continuity figure: 78.7% instr (session opened 78.0).
>
> **THE SESSION IN ONE LINE: five "compiler walls" were our own tooling, and the biggest one had made
> the shared byte-gate unable to bank ANY binary except ov_SC01_077 for a month.**
> 1. **`gate_stage` gated every non-077 binary against ov_SC01_077's SHA** (`good_sha=a.good_sha or
>    DEF_SHA`, truthy default beat the per-binary lookup). Builds one binary, compares another's hash →
>    every draft reports `"near"` → nothing can bank. **Blast radius MEASURED: 0 of 6,708 backlog records
>    affected** (all 4 programmatic callers pass the sha correctly — which is why the grinder banked in
>    ov_SC03_014 while the CLI banked 0/10 the same week, a disagreement nobody compared).
> 2. **The jtbl undo was EATING THE TREE** — `jr_isolate_all` truncates the original `src/<ov>/<nm>.c`;
>    both `harvest_verify` and `gate_stage` snapshotted only `config/`. Fixed in the former, the batch
>    pre-pass DELETED from the latter (R33).
> 3. **The isolation must follow the splice** (like the carve, §61b) — isolating around a STUB gives the
>    region the wrong ambient decl set → byte-DIFF, not a compile error.
> 4. **`jtbl_family_bank.revert` left the tree GIT-CLEAN BUT UNBUILDABLE** (restores config, never
>    re-extracts). Fixed + negative-control-validated.
> 5. **The FLOOR VERDICT was an artifact of snapshot frequency** — three mid-session snapshots of a
>    +0.7pp session averaged to +0.23 and printed "AT THE FLOOR — consider closing P29". **I nearly closed
>    the phase on it.** `--session-close` added; floor now UNDETERMINED, needs 3 session boundaries.
>
> **BANKED:** 7 of 12 preserved t5wave cracks + 5 families swept ×134-138 (`func_80135A4C`,
> `func_80135888`, `func_80135D20`, `func_801299C8`, `func_80167714`) ≈ **+680 member-instances**.
>
> **▶ NEXT (recommended, in order):**
> 1. **A CRACK WAVE over `ov_SC06_018`'s prefetch** (~89 of 101 cached substantial stubs undrafted;
>    Task-5 measured this overlay at 1.59pp of fresh families). **BREADTH — prompt Drew for
>    `/effort ultracode` and WAIT for the toggle (R27); do not launch on a verbal yes.**
>    **Rationale (the day's key planning finding): sweeps only pay when they RIDE a fresh ×1 crack —
>    cracking GENERATES sweep fuel.** The h_seq sweep from an ov_SC01_077 exemplar is byte-proven dead
>    (4 refusals × ~137 members); the remaining 1.27pp zero-crack pool is largely UNAVAILABLE.
> 2. **P29 item 4, the family-adapt fine-tune** — the only untouched plan item; compute-bound, local, $0,
>    kill criterion = beat v3 on a 50-fn byte-gated sample. Today makes it *more* interesting:
>    adaptation-from-a-fresh-exemplar is exactly the task that worked.
> 3. **Do NOT close P29 on ROI grounds** — the floor is undetermined by the (now-honest) instrument.
> **CARRIED:** 5 t5wave cracks still blocked (2 DIFF, 2 CC1-FAIL, 1 §57) at `.run/giants/t5wave_*` — do
> NOT re-draft. **HYGIENE:** a bankless `family_sweep` leaves byte-neutral NSD churn on matched code —
> `git checkout -- src/` after a 0-bank sweep (§57a NB); 133 such files reverted at this checkpoint.

- **✅ 2026-07-22 (SESSION-11, ultracode) — ov_SC06_018 CRACK-WAVE CALIBRATION + the fresh-exemplar-sweep
  thesis MEASURED (it is FAMILY-SPECIFIC, not universal). Fleet 78.4→78.5% instr · 67.1→67.5% distinct ·
  88.14→88.18% fn-count.**
  **Scoping (R33/R35 — corrected the SESSION-10 assumptions vs the bytes via `corpus`):** the ov_SC06_018
  prefetch (`.run/ov_SC06_018_funcs.txt`) = **95 genuine stubs, ALL with cached Ghidra-C**, all substantial
  (80–710 ins), **94/95 in jr-carve files but only 12 with an in-body jtbl** (83 bank via plain harvest_verify).
  Total family leverage **≈201k ins-instances ≈1.54pp** (confirms Task-5's 1.59pp), concentrated in **5 top
  shared-region families** (reach 133–138 ≈115k). Manifest `.run/wave_sc06018_scope.json`.
  **Wave (new `tools/workflows/wave_binary.js`, binary-aware; 8-target calibration, 8 xHigh drafters):
  7/8 match_one MATCH, 1 near** (func_80181468 close=70, regalloc-coalescing → permuter fuel).
  **BANKED (whole-binary byte-gate, R22 clean-fleet 140/140):**
  - **func_801365B8 (155, reach 133) ×138** — the THESIS TEST. SESSION-10 refused this family 0/133 from an
    ov077 exemplar; cracked FRESH in ov_SC06_018 + `family_sweep --hseq --source ov_SC06_018 --allow-pins` →
    **132/132 siblings banked** (+the ov_SC06_018 ×1). **THESIS CONFIRMED for this family.** (~+20.6k ins.)
  - **func_80133AB0 (137, reach 137) ×1** — the OTHER SESSION-10 refusal (0/137). Cracked fresh + banked ×1
    (needed a §17a-1 byte-neutral cast reconcile of the banked caller `func_801343C4`: `int(int,s16,s16,int)`
    view preserved via a call-site cast so the def's canonical `s32(s16,s16,s16,s32)` could splice). BUT the
    family **sweep FAILED 0/136 even from the fresh exemplar** (reverted clean) — **THESIS REFUTED for this
    family**: genuine per-member divergence beyond reloc symbols.
  **⇒ THE REFINED FINDING (R14/R31, → decision-log): the fresh-exemplar sweep is FAMILY-SPECIFIC.** A fresh
  ×1 crack is NECESSARY but NOT SUFFICIENT; the whole-binary byte-gate arbitrates each family. 1 of 2
  thesis-test families swept (~50% on this tiny sample) → **the ~1.5pp campaign estimate must be discounted**
  (not every fresh crack unlocks its family). The SESSION-10 "provenance is the discriminator" thesis holds
  DIRECTIONALLY (func_801365B8 swept where ov077 couldn't) but is not a blanket mechanical ×137.
  **Tooling fixes (R33, all this session):** (1) `family_sweep --source` override now searches
  `matched_members` too (a freshly-banked source member leaves `members` after a sig-regen → the override was
  silently missing it → templated from ov077 → refuse); (2) `cdecl._depth0_spans` consumes `\`-continuations
  so a raw-draft `#define` macro body no longer leaks bogus "declarations" (audit-cdecl was choking on the
  func_80191C50 draft's `XFER` macro; committed source is cpp-expanded so was never affected).
  **⚠️ PHANTOM BANK (trust source, not the report — SESSION-10 class):** `gate_stage` reported func_8017D648
  banked but source stayed INCLUDE_ASM. NOT actually banked — needs a real re-bank (callee-conflict reconcile).
  **func_8017D648 (102, reach 82, MODAL/cross-address) — DONE ×71 (3rd data point).** Re-banked ×1 (a
  byte-neutral §17a-1 callee-cast reconcile of func_8012F14C to the TU's 1-arg convention) → swept **70/82
  (85%)** (+3 gate-fail, +8 remap-refused unresolved-immediates). **⇒ across 3 thesis families the sweep rate
  is 100% / 0% / 85%** — the majority sweep at high per-family rates; func_80133AB0 is the per-member-wall
  minority. Commit `commit:0841` (batch 2); `commit:0840` (batch 1). Drew pushes.

> **🛑 SESSION-11 CHECKPOINT (2026-07-22, ultracode) — supersedes SESSION-10; safe to open a FRESH session here.**
> Tree clean (only R23 `db.*.gbf` churn). **R22 clean-fleet 140/140 byte-identical** (verified per batch);
> `tools-health` OK (dedup 1849/0, C1 234615/234615, cdecl green, audit-binaries 140); 0 NON_MATCHING (G4).
> **Drew pushes** (R6/R20). Commits `commit:0840`, `commit:0841`.
> **Fleet: 78.6% instr · 67.5% distinct · 88.20% fn-count** (session opened 78.4/67.1/88.14 → **+0.2pp instr,
> +0.4pp distinct**).
>
> **THE SESSION IN ONE LINE: the SESSION-10 "fresh crack unlocks the family" thesis is now MEASURED — it is
> FAMILY-SPECIFIC (2 of 3 thesis families swept, at 100% / 85%; 1 is a genuine per-member wall at 0%).**
> Delivered by a binary-aware crack-wave (`tools/workflows/wave_binary.js`) over ov_SC06_018's prefetch
> (95 stubs, all cached-Ghidra-C, 80–710 ins; scoping corrected vs SESSION-10 via `corpus`, R33). Banked:
> **func_801365B8 ×138** (SESSION-10 refused 0/133 from ov077 → 132/132 from a fresh ov_SC06_018 exemplar),
> **func_8017D648 ×71**, **func_80133AB0 ×1** (family sweep refused — per-member wall). Three tooling fixes
> (R33): `family_sweep --source` searches `matched_members`; `cdecl._depth0_spans` consumes `\`-continuations;
> the §17a-1 byte-neutral caller-cast reconcile pattern applied twice (func_801343C4, func_8012F14C).
>
> **▶ NEXT (recommended, in order) — the campaign is VALIDATED; scale it:**
> 1. **The 3 high-reach jtbl families** `func_80135EB0`/`80135260`/`8012AAAC` (reach 138, ≈76k ins ≈+0.58pp) —
>    wave MATCHes are drafted (`.run/drafts-sc06018-calib/`), members.json staged (`.run/jtbl_members_*.json`).
>    Path: bank the ov_SC06_018 jtbl exemplar ×1 via the §8e carve (jtbl_carve + JTBL_PADS + harvest_verify;
>    cookbook §8e / §61c REFUTED-block), commit (jtbl_family_bank needs a clean tree), then
>    `jtbl_family_bank <func> ov_SC06_018 <addr> .run/jtbl_members_<addr>.json` (per-sibling carve+bank).
>    Also `func_80191C50` ×3 (710-ins jtbl giant, drafted; its `XFER` `\`-macro is fine — cdecl fixed).
> 2. **The ~87 untested ov_SC06_018 targets** — a full `wave_binary.js` wave (batch ~15–20), then the
>    gate/bank/sweep ladder (plain harvest_verify for the 83 non-jtbl; jtbl path for the 12). Each fresh ×1
>    crack → `--source ov_SC06_018 --allow-pins` sweep (gate arbitrates; expect ~2/3 families to sweep well).
> 3. **The near-miss** `func_80181468` (close=70, regalloc-coalescing) → permuter/grinder fuel.
> 4. **More per-overlay Ghidra-C prefetch** (Task-5 greedy cover: ov_SC03_015/ov_SC07_006/… each +~0.3–0.6pp)
>    once ov_SC06_018 is drained — cracking is the fuel generator (SESSION-10 strategic inversion).
> **CARRIED:** the 5 t5wave cracks (`.run/giants/t5wave_*`) still blocked — do NOT re-draft. The
> `func_80133AB0` family is a documented per-member wall (do not re-sweep from a single exemplar).
> **Effort:** ultracode for the waves (breadth); Max for jtbl §8e surgery + synthesis. **Do NOT close P29 on
> ROI grounds** — the burn-down floor is still undetermined (needs 3 session-close deltas).

- **✅ 2026-07-22 (SESSION-11 cont., Max) — jtbl POST-CARVE RECONCILE fix built + validated; the reach-138
  jtbl families byte-REFUTED as plumbing wins (they are near-misses/walls). Fleet unchanged 78.6% (no bank).**
  Drew set /effort max ("fix the tooling once") on the finding that all 3 reach-138 jtbl families
  (func_80135EB0/80135260/8012AAAC) + func_80191C50 failed banking on `conflicting types`.
  **ROOT CAUSE (diagnosed):** the jtbl carve's §8b carried-decl layer conflicts with each draft's externs;
  the reconcile chain (`cast_call_sites`+`reconcile_tu`, both `--src-file`-aware) exists but gate_stage runs
  it PRE-carve against the wrong TU (a jtbl fn's real TU is the split file, which doesn't exist yet).
  **FIX (cookbook §62):** `harvest_verify._jtbl_reconcile(fn)` runs the same chain POST-carve against the
  carved TU, updating the draft in place (draft-only, no §61 undo; gate is sole arbiter). Guarded by
  `_jsnap is not None`. **VALIDATED:** func_80135260 (callee func_80134A74) + func_80191C50 (data D_801152A8)
  both went `conflicting types` → a genuine codegen **DIFF** — plumbing dissolved.
  **THE FINDING (R14/R31 → decision-log):** dissolving the plumbing REVEALED all 4 jtbl drafts have a deeper
  issue: func_80135260/80191C50 = a real `%hi`-sharing regalloc residual (agents' reloc-masked match_one
  MATCH over-claimed it); func_8012AAAC = def-side-arity + FLEET-SHARED (engine_core.h) + still DIFFs after
  the arity fix (def-side register-threading wall); func_80135EB0 = carve `isolate FAILED`. **⇒ the
  "+0.58pp from 3 reach-138 jtbl families" is REFUTED** — they are per-function near-misses/walls, not cheap
  plumbing. The fix's value: it BANKS any plumbing-only jtbl family with a TRUE match, and makes the jtbl
  gate HONEST (attributes plumbing vs codegen). **⚠️ §61 traps re-confirmed** (§62): gate jtbl ONE-AT-A-TIME
  (a mid-batch isolate-FAIL corrupts the whole batch → `SHA None`); `fix_arity` on an engine_core.h fn leaks
  fleet-wide (a `git checkout src/<ov>/` restore MISSES `src/shared/` — caught by full `git status` + R22).
  **R22 clean-fleet 140/140; tools-health-safe (tool change only, not committed bytes).** Commit: the
  `_jtbl_reconcile` hook + §62 + decision-log; Drew pushes.
  **▶ REVISED NEXT (the yield is cheaper elsewhere):** the ~83 NON-jtbl ov_SC06_018 targets (no carve, no §8b
  layer — plain harvest_verify) via a `wave_binary.js` breadth wave = the cleaner path. The reach-138 jtbl
  families need re-draft/permuter for their real residuals (not this phase's cheap lever). func_80135260's
  `%hi`-sharing residual is a decent permuter seed; func_8012AAAC/80135EB0 are documented walls.

- **✅ 2026-07-22/23 (SESSION-11 cont., ultracode) — NON-JTBL ov_SC06_018 wave (80 targets, 3 batches of 25/25/30).
  BATCH-1 COMMITTED `commit:0844`: 8 ×1 + 30 swept = 38 instances; distinct 67.5→67.6%.**
  Ran `wave_binary.js` over the 80 non-jtbl undrafted stubs (`.run/wave_sc06018_nonjtbl.json`, all reach 2-14
  modal — 65k leverage ≈0.5pp total, low per-crack yield). **Batch-1: 13/25 match_one MATCH → 8 whole-binary
  banked** (4 plain harvest_verify + 4 via `gate_stage --src-file <jr TU>` — non-jtbl fns in a jr-split file
  need `--src-file`, the same class as the jtbl fix). **4 families swept → 30 members / 13 overlays.** 5 matches
  deferred (missing-sym/§58/deeper plumbing); 12 nears = permuter fuel (several close=2/3/4).
  **⚠️ gate_stage arity-undo BUG FOUND + FIXED (R33, committed):** the arity pre-pass snapshotted `src/<bin>/*.c`
  BEFORE `_gate1` splices the banks there, so an unbanked draft triggered a snapshot-restore that SILENTLY
  REVERTED the banks (4 lost + recovered). Fix: restore ONLY `src/shared/` (the fleet hazard). `GATE_NO_ARITY=1`
  was the interim workaround. **RESUME AIDS:** wave args staged `.run/wave_b{2,3}_args.json`; batch-2 drafts →
  `.run/drafts-sc06018-b2/`; scope `.run/wave_sc06018_nonjtbl.json`. Gate non-jtbl with
  `gate_stage --src-file src/ov_SC06_018/ov_SC06_018_jr_8017C24C.c` (or _jr_8019059C for those addrs).
  **⚠️ ROI CAVEAT:** batch-1 = +0.1pp distinct for ~5M tokens (low-reach modal → poor yield). Assess after
  batch 2 whether to run batch 3 or stop the non-jtbl tail. **R22 clean-fleet after batch-2 (can't `make clean`
  while drafters read asm/).**

> **🛑 SESSION-12 CHECKPOINT (2026-07-23, ultracode) — supersedes SESSION-11; safe to open a FRESH session here.**
> Tree clean (only R23 `db.*.gbf` churn). **R22 clean-fleet 140/140 byte-identical**; audit-binaries OK;
> 0 NON_MATCHING (G4). **Drew pushes** (R6/R20). Commits this session: `commit:0840` `commit:0841` `commit:0842`
> `commit:0843` `commit:0844` `commit:0845` `commit:0846`.
> **Fleet: 78.6% instr · 67.6% distinct · 88.22% fn-count** (session-11 opened 78.4/67.1/88.14 → **+0.2 instr,
> +0.5 distinct**). Long multi-part session (several usage-limit/crash interruptions, all recovered).
>
> **WHAT LANDED (all byte-gated, committed):**
> 1. **The fresh-exemplar sweep is FAMILY-SPECIFIC** (SESSION-11): func_801365B8 ×138 (ov077 refused 0/133),
>    func_8017D648 ×71 (modal), func_80133AB0 ×1 (per-member wall). 3 families: 100%/85%/0% sweep. → decision-log.
> 2. **jtbl post-carve reconcile** (`harvest_verify._jtbl_reconcile`, cookbook §62) — dissolves the carve's §8b
>    carried-decl plumbing; **REFUTED the reach-138 jtbl families as cheap wins** (real residuals/arity/isolate).
> 3. **ov_SC06_018 NON-JTBL wave** (`wave_binary.js`, 80 targets): batch-1 (8 ×1 + 30 swept) + batch-2 partial
>    (5 ×1 + 21 swept) = **13 ×1 + 51 swept = 64 instances**. Low-reach modal → **low ROI (~0.1pp distinct/batch)**.
> 4. **gate_stage arity-undo BUG fixed** (R33): its snapshot-restore silently reverted banks; now restores only
>    src/shared/. `--src-file <jr TU>` is REQUIRED to gate non-jtbl fns in jr-split files.
>
> **▶ NEXT (resume aids all staged) — but WEIGH THE ROI FIRST:**
> - The non-jtbl tail is **low-yield** (0.1pp/batch of large modal fns). **Recommendation: do NOT grind all 80.**
>   Remaining: batch-2's 20 undrafted (`.run/wave_b2_args.json`) + batch-3's 30 (`.run/wave_b3_args.json`),
>   drafts → `.run/drafts-sc06018-b{2,3}/`. Gate with `gate_stage --src-file src/ov_SC06_018/ov_SC06_018_jr_8017C24C.c`
>   (or `_jr_8019059C` for 0x8019xxxx addrs), then `family_sweep --hseq --source ov_SC06_018 --allow-pins --only <addrs>`.
> - **Higher-value alternatives:** (a) the **12 batch-1 + growing permuter-fuel nears** (func_8017F0F4 close=2,
>   func_801811DC close=3, func_80189000 close=4, etc. — grinder/permuter_ils, drafts in `.run/drafts-sc06018-b1/`);
>   (b) a **different per-overlay Ghidra-C prefetch** (Task-5 greedy cover: ov_SC03_015/ov_SC07_006 each ~+0.3-0.6pp
>   of FRESH families — higher-reach than ov_SC06_018's non-jtbl tail); (c) P29 item 4 (family-adapt fine-tune).
> - **DO NOT close P29 on ROI** (burn-down floor still undetermined). **CARRIED:** the 5 batch-1 deferred matches
>   (missing-sym/§58/deeper) + the jtbl residuals (func_80135260 %hi-share = permuter seed). `wave_binary.js` is
>   the reusable binary-aware wave; scope `.run/wave_sc06018_nonjtbl.json`.

- **✅ 2026-07-23 (SESSION-13, ultracode) — took option (b): ov_SC07_006 reach-138 fresh-exemplar crack-wave
  batch-1. Fleet 78.6→78.7% instr · 67.6 distinct (flat) · 88.22 fn-count (flat); ov_SC07_006 84.6→84.8%.**
  New `tools/build_wave_args.py` emits `wave_binary.js` args from a fuel manifest (asm/ghidra_c path resolve +
  jtbl detect). Scoped ov_SC07_006 = **122 draft-now reach-138 WAVE families** (all cached → zero prefetch;
  ov_SC03_015 had 100 but 227 uncached). Ran batch-1 = **top-24 by nins*reach leverage** (`wave_binary.js`, 24
  xHigh). **Wave: 16 self-assessed MATCH, 8 killed by the Anthropic session usage limit** (resets ~1:40am
  Denver — no more agent waves possible this session).
  **Byte-gate ladder (all inline, no agent tokens): 6 ×1 banked** — plain harvest_verify 2 (func_801325B8,
  func_80165CA0) + `gate_stage` reconcile 4 (func_8014FE60, func_8014A048, func_801678F0, func_80167540). 17
  PLUMBING-fail / 2 CC1-FAIL / 2 DIFF. **Propagation (§55b: banks committed FIRST, then targeted):**
  `dedup_propagate --addr` → **func_801325B8 +3 onboarded-tail siblings**; func_8014A048/func_801678F0
  byte-DIVERGE in the SC07 cluster (×1); func_8014FE60/func_80167540 local-type-blocked §20 (×1);
  **func_80165CA0 consolidated its h_exact subgroup (+0) then `family_sweep --hseq` 0/135 — a PER-MEMBER WALL**
  (like func_80133AB0 0/136). **Net ≈ 9 newly-matched functions.** R22 clean-fleet 140/140 ×2 (engine_core.h
  arity edit fleet-safe); tools-health green (dedup 1850/0).
  **THE FINDING (R14/R35 → decision-log 2026-07-23):** the fuel manifest's `nins*reach` leverage OVER-COUNTS —
  a reach-138 family matched in ~135 overlays yields +(live), not +138. Corrected metric = **live-siblings**:
  the 122-pool splits **76 fresh (≥100 live) / 44 onboarded-tail (<5 live)**, and they have OPPOSITE difficulty
  — the tail banks easily (has a sibling to port; 5 of 6 banks) but +few; the fresh families are the HARD tail
  (def-side plumbing `conflicting types for func_XXXX` → §54 `--fix-def-sig`; DIFF → permuter; per-member
  walls). A fresh crack does NOT reliably unlock its family. `build_wave_args.py --rank live` now ranks by the
  true lever + reports the fresh/tail split. Commits: `commit:0848` (6 banks) + the propagation/tooling commit.

> **🛑 SESSION-13 CHECKPOINT (2026-07-23, ultracode) — supersedes SESSION-12; safe to open a FRESH session here.**
> Tree clean after commit (only R23 `db.*.gbf` churn). **R22 clean-fleet 140/140 byte-identical** ×2;
> tools-health OK (dedup 1850/0, 0 NON_MATCHING G4). **Drew pushes** (R6/R20). Commits: `commit:0848` + the
> propagation/tooling/checkpoint commit.
> **Fleet: 78.7% instr · 67.6% distinct · 88.22% fn-count** (SESSION-12 opened 78.6/67.6/88.22 → **+0.1 instr,
> flat distinct/fn** — a SMALL, honest delta; the reach-138 wave path is LOW-ROI, 3rd such data point).
>
> **WHAT LANDED (all byte-gated, committed):**
> 1. **ov_SC07_006 reach-138 batch-1: 6 ×1 banks + 3 propagated = ~9 functions** (84.6→84.8%). Wave killed
>    early by the usage limit (8/24 drafters).
> 2. **The corrected-metric finding** (R14/R35): rank by LIVE-siblings, not `nins*reach`. `build_wave_args.py
>    --rank live` shipped. The reach-138 family well is largely SPENT via wave+gate (re-confirms Phase-26).
> 3. func_80165CA0 = a per-member wall (0/135 sweep) — the fresh-exemplar bet is family-specific, and this one
>    lost.
>
> **▶ NEXT — the batch-1 evidence says DON'T run more ov_SC07_006 wave batches (low-ROI). Options, ranked:**
> - **(a) RE-SCOPE FIRST (cheap, token-free):** `build_wave_args.py --rank live --min-live 100 --binary ov_SC07_006`
>   emits the 76 genuine-fresh pool; then decide if ANY are worth a permuter/§54 attack. Most fresh-138 are
>   walls/def-side-plumbing (batch-1 proof), so expect a thin real yield.
>   **DIAGNOSED the fresh-138 def-side blocker (token-free probe, func_8014CD80, 138 live, no macro):**
>   engine_core.h forward-declares it inside a shared-caller macro with a SIMPLIFIED sig
>   (`void func_8014CD80(s32,void*,void*)` @ line 8966) that mismatches the byte-true def
>   (`int func_8014CD80(s32,u16*,u16*)`) in RETURN TYPE + param types. `gate_stage`'s arity pre-pass is
>   param-COUNT-only (misses return/ptr-type); §54 `reconcile_def_sig` rewrites the DRAFT to match the header
>   (wrong direction — the header is the simplified one, matching it can DCE the return). **The missing tool is
>   a HEADER-decl reconcile (fix the engine_core.h caller decl to the byte-true def, then fleet-verify R22) —
>   fleet-shared, so it INHERITS the §61 snapshot-undo constraint.** This is Task-14-stage-2-adjacent and is
>   the real gate the fresh-138 families need; until it exists they are per-function hand-surgery, not breadth.
> - **(b) TOKEN-FREE per-function grind (I am out of agent-wave budget):** permuter/grinder on batch-1's 2 DIFFs
>   (func_80177940, func_80169228 — incomplete session-limit drafts) + the 7 gate-near reconcile-fails; and
>   `family_sweep --fix-def-sig` (§54) on the def-side-plumbing fails (func_8014D12C/func_80168070/func_8014CD80
>   — "conflicting types for func_XXXX"). Drafts staged in `.run/drafts-sc07006-b1/`, pool
>   `.run/wave_sc07006_nonjtbl_pool.json`.
> - **(c) A DIFFERENT lever entirely** — the reach-138 family campaign's easy wins are banked; Task 7's
>   ROI-gated close now has 3 low-yield data points (ov_SC06_018 non-jtbl ≈0.1pp; ov_SC07_006 reach-138 ≈9 fns).
> - **DO NOT close P29 on ROI** — burn-down floor still undetermined (needs 3 session-close deltas; this is one).
> **CARRIED:** the 8 session-limit-unfinished drafts (redraft when the limit resets); `func_80165CA0`/the
> diverging tail families are documented walls — do NOT re-sweep.

> **🔥 SESSION-13 LATE UPDATE (R35 — the probe REVERSED the "low-ROI/spent" verdict). Commit `<pending>`.**
> Ran the bounded header-decl probe on **func_8014CD80** (138 live, 0 matched, universal body, clean MATCH
> draft). Blocker = engine_core.h `DEFINE_func_8014CD0C()` declares it `void(s32,void*,void*)` vs byte-true
> `int(s32,u16*,u16*)`. **One byte-neutral header edit → harvest_verify ×1 BYTE-IDENTICAL → `dedup_propagate
> --addr` 138/138 byte-identical (live 138→0) → R22 140/140.** **THE FRESH-138 FAMILIES ARE RECOVERABLE ×138**
> — the def-side header decl was the ONLY blocker (func_80165CA0's 0/135 was a non-universal *body*, a
> different failure mode). Fleet **78.7→78.8% instr · 88.22→88.26% fn-count** from this ONE family.
> **Quantified market: 38 of the 75 fresh (≥100-live) families carry the exact pattern** (engine_core.h caller
> forward-decl, simplified `void`/`void*`) → each a candidate ×138 ≈ **+1.5–2.8pp instr**. → decision-log.
>
> **✅ `tools/fix_header_decl.py` BUILT + SELF-TESTED (SESSION-13, cookbook §63).** `--fn --draft
> [--check|--apply]`: parses the byte-true sig, canon-compares (typedef-aware, skips ALREADY-OK), REFUSES
> ABI-changing rewrites (param-count / ptr↔scalar / scalar-class), preserves the macro `\` continuation,
> snapshots + prints the git-restore (§61). 4 self-tests pass: idempotent on func_8014CD80; correct rewrite
> +`\` preserved; REFUSE on a 2-vs-3 param mismatch; **end-to-end `--apply` on func_8014D12C turned the
> `conflicting types` PLUMBING into a clean codegen DIFF** (plumbing dissolved; func_8014D12C's body is a
> near-miss so it didn't bank — the tool is the INTEGRATION half, reverted clean).
>
> **▶ THE SINGLE NEXT TASK (needs agent budget — wave reset ~1:40am Denver):** run the fresh-family pipeline
> over the 38-family market. `build_wave_args.py --rank live --min-live 100 --binary ov_SC07_006` → wave the
> fresh families (byte-true UNIVERSAL bodies) → `fix_header_decl --apply` per fn → `harvest_verify` →
> `dedup_propagate --addr` → R22. Expect ~half-to-most bank ×138 (residual risk = a non-universal body, a
> per-member wall like func_80165CA0, NOT the header). Option (b) reopened as the campaign's best lever
> (≈+1.5–2.8pp instr). **The onboarded-tail low-ROI read still stands; only the FRESH read flipped.**

> **🔧 SESSION-13 CONT (2026-07-23, ultracode) — 3 parallel streams launched; gate-on-completion pending.**
> **Stream A — CRACK WAVE RUNNING:** Workflow `w9lidyi5b` drafting **24 fresh (LIVE=138) families** →
> `.run/drafts-sc07006-fresh/`. Batch/args `.run/wave_sc07006_fresh_b1_args.json`. **ON COMPLETION:** gate
> each — class-1 self-def blockers via `fix_header_decl --fn <fn> --draft <d> --apply` → `harvest_verify` →
> `dedup_propagate --addr 0x<a> --recover` → (batch) R22. Full fresh pool (74) in `.run/wave_sc07006_fresh_nonjtbl_pool.json`.
> **Stream C — PERMUTER WIN:** `func_8014D12C` (fresh-138) cracked score-0 → `.run/perm_d12c_winners/func_8014D12C.c`.
> Bank it: `fix_header_decl --fn func_8014D12C --draft .run/perm_d12c_winners/func_8014D12C.c --apply`
> (its header decl is `void(s32,void*,void*)`; byte-true `s32(s32,u16*,u16*)`) → harvest_verify → dedup_propagate ×138.
> **Stream B — `fix_header_decl` v2 BUILT + committed:** `--reconcile-externs` fixes CALLEE decls in shared
> headers too (sources byte-true sig from the draft's `extern`). --check validated (func_80174CB0 → func_80012C6C
> s32→s16, all SAFE; v1 unbroken). **⚠️ v2 LIMITATION (byte-gate caught it, fail-closed):** it fixes only
> `src/shared/*.h`, NOT per-overlay-local decls — func_80174CB0 still blocked by a LOCAL decl of func_80012C6C
> at `src/ov_SC07_006/ov_SC07_006_jr_8015C32C.c:8523`. **v3 = extend the fix to the per-overlay split .c the
> draft targets (or wire it into harvest_verify's splice).** func_80174CB0/func_801463A0 (data, multi-symbol)
> carried as v3 exemplars. R22 NOT yet run this stream (no bank landed — wave pending). Tree clean.

> **🛑 SESSION-13 CHECKPOINT (2026-07-23, ultracode) — supersedes SESSION-12; safe to open a FRESH session here.**
> Tree clean (R23 db churn only). **R22 clean-fleet 140/140** (verified 4× this session); tools-health OK
> (dedup 1853/0); 0 NON_MATCHING. **Drew pushes** (R6/R20). **Fleet: 78.9% instr · 67.6% distinct · 88.34%
> fn-count** (opened 78.6/67.6/88.22 → +0.3 instr, +0.12 fn-count; distinct flat — shared-family work).
> ov_SC07_006 84.6→85.1%. Commits: `commit:0848 commit:0849 commit:0850 commit:0851 commit:0852 commit:0853 commit:0854
> commit:0855 commit:0856` (9).
>
> **WHAT LANDED:**
> 1. **func_8014CD80 ×138** — the header-reconcile PROOF (fresh-138 def-side blocker → byte-neutral header fix).
> 2. **fix_header_decl v1+v2 built + self-tested** (cookbook §63). **⚠️ CORRECTED same session:** it is FRAGILE
>    for SHARED multi-caller decls (rewriting a decl breaks callers that use the return → CC1-FAIL). Keep it for
>    the narrow single-caller/ignored-return self-def case ONLY. **The integration SPINE is `gate_stage`'s
>    call-site-cast, NOT header rewriting.** (decision-log 2026-07-23 ×3 entries.)
> 3. **Two fresh-138 crack waves** (batch-1: 24, batch-2: 24; ~40 MATCH bodies total). **Banked: batch-1 6 ×1 +
>    func_801325B8 propagated; batch-2 7 ×1 cores + 2 ×138 (func_80130C08, func_80137178, +274).** ov_SC07_006
>    reach-138 pool: ~15 cores banked of 74.
> 4. **THE INTEGRATION-WALL finding (the real P29 bottleneck):** drafting is SOLVED (bodies byte-match); three
>    walls stack on propagation — (a) extern/decl plumbing (gate_stage clears ~⅓: 7/20), (b) **§20 local-type cap
>    ("not self-contained") — blocked 4/6 from ×138**, (c) per-member divergence (func_80169228, whole SC03
>    cluster). Each ×138 family must clear ALL THREE.
> 5. **Full remaining-work map + roadmap deltas** (decision-log): 40,395 overlay stubs / 2.74M ins + main 84k;
>    159 reach-138 fams; **top-100 fams = 53% of remaining**; B1 pessimism partially reversed; **B7 behemoth list
>    stale — 0x80183814 (5122, ov_SC07_006) is the new largest**; prefetch gap is the tail (146/159 reach-138
>    cached), not the top.
>
> **⚠️ INCIDENT (recovered, 0 work lost):** `dedup_propagate --recover` on func_80169228 (many byte-divergent
> stragglers) THRASHED >1hr (re-gates the fleet per excluded straggler = quadratic). Killed + reverted 326
> half-mutated files to the committed baseline; re-ran WITHOUT --recover (droppers drop instantly). **LESSON:
> --recover is only for a FEW stragglers; a broadly-divergent family must be dropped or capped, never --recover'd.**
> Banks were committed BEFORE the propagate (§55b) so nothing was lost.
>
> **▶ NEXT (highest-value, in order):**
> 1. **`build_engine_types` type-lift** — the §20 local-type cap is the single biggest propagation unlock: it
>    frees the 4 blocked cores here (func_8012B4B8/80175308/8012E138/8012A1BC → +552 stubs) AND a large fleet-wide
>    fraction (roadmap B4). ⚠️ known-fragile (R32: hard-exited on 81% of its corpus for 4 phases) — verify/fix
>    its coverage FIRST (R32/R35), then re-propagate the 4 + a fleet sweep.
> 2. **gate_stage the ~13 staged near/plumbing batch-2 bodies** (`.run/drafts-sc07006-fresh/` — byte-correct,
>    integration-blocked) + permuter the 3 nears (func_80177940/8014C6F4/80140D68 close 17/10/27).
> 3. **Next fresh-138 wave** over the remaining ~59-family pool (`.run/wave_sc07006_fresh_nonjtbl_pool.json`,
>    `--rank live --min-live 100`); the GIANT families (150–371 ins) are the biggest untapped wins (I capped at 150).
> **CARRIED:** func_80169228 (divergent, ×1, do NOT --recover); the 4 local-type-blocked cores (need type-lift);
> fix_header_decl (narrow use only). **Do NOT close P29 on ROI** — burn-down floor undetermined.

> **🔧 SESSION-13 TYPE-LIFT ADDENDUM (2026-07-23) — §20 cap partially cracked, +276.**
> Built **`tools/lift_types.py`** (fleet-wide targeted §20 type-lift; brace-aware parser, canonical-def picker,
> retires the `[^;]*` regex that broke twice — R35). Lifted the CLEAN types **Mat32 + Cam8012E138** fleet-wide
> (139 files stripped) → unblocked + propagated **func_8012B4B8 + func_8012E138 ×138 (+276 stubs)**. R22 140/140.
> **Fleet 79.0% instr · 67.6% distinct · 88.38% fn-count** (session opened 78.6/67.6/88.22). Commits through
> `commit:0860` (16 this session). **DOCTRINE (decision-log):** classify types first; lift 1-def/copy-only-variant
> types NOW (byte-neutral, R22-verified); DEFER fleet-split variants (MATRIX 3-def, Vec8 180/139, Buf 3-def, M8)
> to a per-camp field-access reconcile pass — the remaining hard part of roadmap B4.
> **▶ NEXT:** (1) the variant-reconcile pass for MATRIX/Vec8/Buf (per-camp: pick canonical, rewrite variant
> field-access, R22) — unblocks func_80175308/func_8012A1BC + many fleet-wide; (2) the ~13 staged near/plumbing
> batch-2 bodies (`.run/drafts-sc07006-fresh/`) via gate_stage; (3) next fresh-138 GIANT-family wave.

- **✅ 2026-07-23 (SESSION-14, Max) — THE BROAD §20 TYPE-LIFT LANDS: 154 types fleet-wide, R22 140/140.**
  The three-session-carried blocker ("needs collision-vetting + -O0 strip precision") was **misdiagnosed on
  all three counts** — fixing the instrument first (R35) changed every answer. Cookbook **§64**, decision-log.
  **(1) The "case-variant collision" is a TAGGED TYPEDEF counted twice.** `typedef struct Tag {...} Alias;`
  is matched by BOTH finders with OVERLAPPING spans → the inner span (starting at `struct`) is emitted as a
  *variable definition*, the alias is redeclared, and the strip deletes highest-first so the outer span's end
  offset is STALE and over-deletes. MEASURED: **13 pairs / 6,142 occurrences, 0 standalone tags.**
  `build_engine_types.resolve_type_defs()` is now the ONE shared model (R33); `assert_disjoint()` enforces
  span disjointness at every mutation (R32). The case-insensitive exclude was a heuristic over a structural
  fact — and would have wrongly dropped the legitimate `Obj`/`obj` + `Vec`/`vec` pairs. Key by (kind, name).
  **(2) The "-O0 strip precision" bug is a VISIBILITY bug.** `ov_SC01_077_o0.c` is the **1 TU of 3,226** that
  deliberately omits `engine_core.h`. Stripping its types DELETED them; `multiple definition of D_801DAA08`
  was three steps downstream (undeclared → parse error → implicit int → tentative def → link collision),
  naming a data symbol no diff ever touched. `bet.type_visible()` derives the visible-header set from the
  include graph and keeps such defs local, named.
  **(3) A third blocker, mine, caught by R22: `--candidates` classifies per ENTITY but emits per NAME.**
  Passing `Prim` dragged in the deferred VARIANT `typedef Prim`, repointing 103 overlays at the header's
  different layout. Compiled clean; the per-binary pre-filter passed; **R22 37/140** — and the 103 failures
  were **exactly** the 103 Prim-stripped overlays (set equality, byte-verified). Fixed by the strip invariant
  *"remove a local def only if what becomes visible is TEXTUALLY IDENTICAL"*, placed at the mutation so a
  selector bug cannot reach the source; divergent copies reported as per-camp reconcile work.
  **RESULT: 154 types lifted, 2,958 files stripped, `engine_types.h` +510 lines, R22 clean-fleet 140/140
  BYTE-IDENTICAL** (attempt 2; attempt 1 correctly refused). Negative controls: `assert_disjoint` refuses the
  overlap shape; forcing `--types Prim` now refuses all 103 divergent copies and strips only the 1 that matches.
  **DEFERRED + NAMED (not dropped):** 8 VARIANT entities (MATRIX 3-def, Buf 3-def, Vec8, Prim, Handler, Blk8,
  V8, Prim_8016E7C8) = the per-camp field-access reconcile, still the hard part of roadmap B4; 14 carried
  tags; 5 types kept local in the -O0 TU.
  **SEQUENCING LESSON (§61 one level down):** `make build BINARY=ov_SC01_077` reproduced the -O0 failure in
  **0.26 s** with a compile error naming the 5 affected types, where the fleet cycle gave a link error naming
  an unrelated symbol — but a pre-filter is evidence ONLY about what it filtered (ov_SC01_077 passed the
  Prim-broken run too). **Pre-filter on a binary that FAILED.**
  **TWO SELF-INFLICTED MEASUREMENT ERRORS (R14 applies to my own 3-line scripts):** an `__attribute__` regex
  artifact invented a "defs that also declare an object" class (zero real instances — I nearly built a cdecl
  vetter for it), and a `while read` loop counted the literal string `check-all:` as an overlay name.
  **GATES:** R22 clean-fleet **140/140 byte-identical**; `tools-health` OK (corpus 0 PHANTOM/0 TRUNCATED,
  cdecl ALL ORACLES GREEN, audit-binaries 140 full citizens, **dedup-check 1854 validated / 0 failed**,
  C1 235170/235170); 0 NON_MATCHING in any default build (G4).
  **METRICS UNCHANGED — 79.0% instr · 67.6% distinct · 88.38% fn-count.** Expected and honest (P9): a
  type-lift banks NO functions. Its value is removing the §20 cap that stops already-matched cores from
  propagating ×138 — the yield shows up in the NEXT propagate, not here.

- **✅ 2026-07-23 (SESSION-14 cont.) — THE LIFT'S PAYOFF: 13 cores propagated ×138, −831 stubs.**
  With the §20 cap lifted, `dedup_propagate --auto-from ov_SC01_077 --check-only` planned **17**
  self-contained cores (was blocked); the batch banked **12** + `func_80175308` (propagated separately,
  138/138) = **13 cores ×138**. **5 were correctly DROPPED as cross-overlay stragglers** (`0x8012A018`,
  `0x80172C50`, `0x80173A60`, `0x80144090` in ov_SC01_000; `0x801495C4` in ov_SC07_006) — h_exact sharing
  is all-or-nothing and those overlays' bytes diverge; dropping is right, `--recover` is the documented
  thrash hazard and was NOT used.
  **`func_80175308` is the provable unblock** — it is the core the SESSION-13 checkpoint named as
  local-type-blocked. (I do NOT claim all 17 were unblocked by this lift: measuring that needs a pre-lift
  re-scan I did not run — P9.)
  **GATES: R22 clean-fleet 140/140 BYTE-IDENTICAL** (2nd full cycle this session); `make report` green;
  **dedup-check 1867 validated / 0 failed** (was 1854), C1 236964/236964; 0 NON_MATCHING (G4).
  **FLEET: instr 79.0 → 79.3% · fn-count 88.38 → 88.61% · INCLUDE_ASM stubs 41,112 → 40,281 (−831).**
  **distinct-code stays 67.6% — correct and expected:** propagation replicates code already counted as
  distinct-matched; only a fresh crack moves that number.
  **STILL BLOCKED: 13 cores, "not self-contained (local types)"** — blocked by exactly the 8 deferred
  VARIANT entities. That is the next lever, and it is a per-camp FIELD-ACCESS RECONCILE, not a lift.

> **🛑 SESSION-14 CHECKPOINT (2026-07-23, Max) — supersedes SESSION-13; safe to open a FRESH session here.**
> Tree clean (only R23 `db.*.gbf` churn). **R22 clean-fleet 140/140 byte-identical** (verified 2× this
> session); `tools-health` OK (corpus 0 PHANTOM/0 TRUNCATED, cdecl ALL ORACLES GREEN, audit-binaries 140
> full citizens); **dedup-check 1867 validated / 0 failed**, C1 236964/236964; 0 NON_MATCHING (G4).
> **Drew pushes** (R6/R20). Commits: `commit:0863`, `commit:0864`.
> **Fleet: 79.3% instr · 67.6% distinct · 88.61% fn-count** (opened 79.0/67.6/88.38 → **+0.3pp instr,
> +0.23pp fn-count, −831 INCLUDE_ASM stubs**; distinct flat — shared-family propagation, not fresh cracks).
>
> **THE SESSION IN ONE LINE: the 3-session-carried "collision-vet + -O0 strip precision" blocker was
> misdiagnosed on all three counts, and fixing the INSTRUMENTS first changed every answer (R35).**
> 1. The "case-variant collision" (`actor4c`/`Actor4C`) is a **TAGGED TYPEDEF counted twice** with
>    OVERLAPPING spans — 13 pairs / 6,142 occurrences / **0 standalone tags**. The inner span starts at
>    `struct`, so lifting it emits a *variable definition*; and the highest-first strip leaves the outer
>    span's end offset STALE → over-deletes past its end. `build_engine_types.resolve_type_defs()` is now
>    the ONE shared model (R33); `assert_disjoint()` enforces disjointness at every mutation (R32).
>    **The case-insensitive exclude was a heuristic over a structural fact** — it would ALSO have wrongly
>    dropped the legitimate `Obj`/`obj` + `Vec`/`vec` pairs. Key by **(kind, name)** — the C namespace.
> 2. The "-O0 strip precision" bug is a **VISIBILITY** bug: `ov_SC01_077_o0.c` is the **1 TU of 3,226**
>    that deliberately omits `engine_core.h`, so the strip DELETED its types. `multiple definition of
>    D_801DAA08` was **3 steps downstream** (undeclared → parse error → implicit int → tentative def →
>    link collision) and named a data symbol no diff ever touched. `bet.type_visible()` now derives the
>    visible-header set from the include graph and keeps such defs local, NAMED.
> 3. **A third blocker, introduced by me and caught by R22:** `--candidates` classifies per ENTITY but
>    emits per NAME, so passing `Prim` dragged in the deferred VARIANT `typedef Prim` → 103 overlays
>    repointed at the header's different layout. Compiled clean, per-binary pre-filter GREEN, **R22
>    37/140** — and the 103 failures were EXACTLY the 103 Prim-stripped overlays (set equality).
>
> **WHAT LANDED:** 154 types lifted fleet-wide (2,958 files stripped, `engine_types.h` +510) → then
> **13 cores propagated ×138** (12 via `--auto-from` + `func_80175308`, the provable unblock), −831 stubs.
> 5 cores correctly DROPPED as cross-overlay stragglers; `--recover` NOT used (quadratic thrash hazard).
>
> **▶ NEXT (ranked):**
> 1. **The per-camp FIELD-ACCESS RECONCILE for the 8 VARIANT entities** — MATRIX (3 defs), Buf (3), Vec8,
>    Prim, Handler, Blk8, V8, Prim_8016E7C8. They block the **13 cores still "not self-contained (local
>    types)"**. Pick a canonical layout per camp, rewrite the variant camps' FIELD ACCESS, R22. **This is
>    NOT a lift** — lifting them blindly is exactly what broke 103 overlays today. Remaining hard part of
>    roadmap B4. Enumerate with `lift_types.py --candidates` (VARIANT bucket).
> 2. **Fresh cracks** — the only lever that moves **distinct-code** (flat at 67.6% all session).
> 3. Do NOT close P29 on ROI — the burn-down floor is still undetermined (needs 3 session-close deltas).
> **TOOLING NOW SAFE TO RE-RUN:** `lift_types.py --candidates` is derived + reproducible (retires the
> ad-hoc 102-type pipeline); 4 negative controls armed (overlap refused, containment folded, visibility
> False on the -O0 TU, divergent copies refused). **PRE-FILTER LESSON (§61 one level down): a pre-filter
> is evidence ONLY about what it filtered** — `ov_SC01_077` passed the Prim-broken run too. **Pre-filter on
> a binary that FAILED.** Also: `cmd | tail` masks make's exit status — the harness reported "exit 0" on a
> run that failed 103/140. **Two of my own 3-line scripts lied before any tool did (R14).**

- **✅ 2026-07-23 (SESSION-14 cont., xHigh) — VARIANT camps: the plan CORRECTED to UNIQUIFY, validated on `Buf`.**
  **THE CORRECTION (measurement, not opinion — cookbook §64a):** the checkpoint said the 8 VARIANT types
  need a "per-camp field-access reconcile." Measuring the camps refutes that for most of them:
  `Vec8` = `{s32 w[8]}` (32B) in 180 files AND `{s16 unk0..unk6}` (8B) in 139 files; `MATRIX` 48B/32B/32B;
  `Buf` 16B / 0x20+ / DrawEnv-based. **These are DIFFERENT types sharing an identifier in different TUs
  of the same overlay** — reconciling to a canonical layout would MERGE them, the same failure that broke
  103 binaries on `Prim`. **The right op is UNIQUIFY** (rename the non-majority camp): byte-neutral (a type
  name emits no code), TU-local by construction, and it makes every camp single-def → liftable by the
  existing rules. **NEW `tools/uniquify_type.py`** (deterministic camp order; majority keeps the name;
  rewrites ONLY files that DEFINE the camp; `\bT\b` so `Buf` never matches `Buf80153978`).
  **VALIDATED on `Buf` (cheapest camp: 578/6/1 files):** 11 identifiers across 7 files → 3 camps LIFTABLE →
  lifted (585 local copies stripped) → **R22 140/140** → blocked queue **13 → 11** (`0x8012ea90`,
  `0x801749c8` freed). Propagated `0x8012EA90` ×138; `0x801749C8` DROPPED (straggler in ov_SC07_006).
  **YIELD, HONESTLY (P9): ZERO new matched functions.** fn-count 88.61%, instr 79.3%, stubs 40,281 — all
  UNCHANGED; dedup 1867→1868, C1 +138. `0x8012EA90`'s members were ALREADY matched in all 138 overlays, so
  the propagation consolidated duplication into one shared macro (a DRY win) rather than banking coverage.
  The increment's real value is the **proven recipe** + the queue moving 13→11, NOT the numbers.
  **ALSO FIXED (R32):** `dedup_propagate`'s skip line printed a COUNT and no names, and aggregated THREE
  unrelated causes into `n_local` — a body skipped for merely containing a `//` comment (macro-unsafe, a
  1-line fix) was reported identically to one genuinely using an overlay-local type. Now named + split by
  cause; the 13 turned out to be all the real cap, but the queue is no longer invisible.
  **NEXT CAMPS by cost:** `MATRIX` (578/71/6) · `Vec8` (180/139 — no clear minority, expect to name BOTH) ·
  then Handler / Blk8 / V8 / Prim / Prim_8016E7C8.

> **🛑 SESSION-14 FINAL CHECKPOINT (2026-07-23) — supersedes the SESSION-14 block above.**
> Tree clean (only R23 `db.*.gbf` churn). **R22 clean-fleet 140/140 byte-identical — verified 4× this
> session** (after the broad lift, after the 13-core propagate, after the Buf lift, after the final
> propagate). `tools-health` OK; **dedup-check 1868 validated / 0 failed**, C1 237102/237102;
> 0 NON_MATCHING (G4). **Drew pushes** (R6/R20). Commits: `commit:0863` `commit:0864` `commit:0865` `commit:0866`.
> **Fleet: 79.3% instr · 67.6% distinct · 88.61% fn-count** (opened 79.0/67.6/88.38).
> **Burn-down `--session-close` logged: +0.60pp instr / +0.47pp fn-count.** NB its "distinct −0.30pp" is
> against an OLDER baseline snapshot under a different denominator convention — **this session's
> distinct-code was exactly FLAT** (3811442/5634875 at both open and close). 3 session-close snapshots on
> record; still **<3 deltas, so the ROI floor remains UNDETERMINED — do NOT close P29 on ROI.**
>
> **WHAT LANDED:** (1) the broad §20 type-lift — **154 types, 2,958 files, engine_types.h +510**, after all
> three carried "blockers" proved misdiagnosed (§64); (2) **13 cores propagated ×138, −831 stubs**;
> (3) the VARIANT plan CORRECTED from reconcile to **UNIQUIFY** + `tools/uniquify_type.py`, validated on
> `Buf` (§64a), blocked queue **13 → 11**; (4) R32 fix: `dedup_propagate` now NAMES what it skips and
> splits the three causes it had aggregated.
>
> **▶ NEXT (ranked):**
> 1. **Uniquify the remaining camps** — `MATRIX` (578/71/6) then `Vec8` (180/139 — no clear majority, so
>    expect to name BOTH camps), then Handler / Blk8 / V8 / Prim / Prim_8016E7C8. Recipe PROVEN:
>    `uniquify_type --apply` → `lift_types --candidates` → `--types <camps> --apply` → pre-filter build →
>    R22 → `dedup_propagate --addr`. Expect this to keep draining the 11-core blocked queue.
>    ⚠️ **Temper the expected yield:** the Buf increment banked **0 new matched functions** (its members
>    were already matched; propagation only de-duplicated source). Unblocking a core ≠ new coverage.
> 2. **Fresh cracks** — the ONLY lever that moves `distinct-code` (flat at 67.6% ALL session). Breadth →
>    prompt Drew for `/effort ultracode` and WAIT for the toggle (R27).
> 3. Do NOT close P29 on ROI (floor undetermined).
> **CARRIED:** 11 cores still overlay-local-type-blocked (named in the skip output); 5+1 cross-overlay
> stragglers correctly dropped (`--recover` NOT used — quadratic thrash hazard).
> **STANDING LESSONS THIS SESSION:** a pre-filter is evidence ONLY about what it filtered (pre-filter on a
> binary that FAILED); `cmd | tail` masks make's exit status (echo the real status inside the command);
> and R14 applies to my own 3-line scripts — two of them produced false evidence before any project tool did.

- **✅ 2026-07-23 (SESSION-14 cont.) — MATRIX camps uniquified + lifted; blocked queue 11 → 10.**
  `uniquify_type --type MATRIX --apply` → **77 files rewritten** (camp1 `{short m[3][3]; long t[3]}` ×71
  jr-split TUs → `MATRIX_c1`; camp2 `{short m[3][3]; short pad; s32 t[3]}` ×6 → `MATRIX_c2`; the 578-file
  `{s32 m[3][3]; s32 t[3]}` majority keeps the name). All 3 camps → LIFTABLE → lifted, **655 local copies
  stripped**. Pre-filtered on one overlay from EACH camp (ov_SC01_000 camp1 / ov_SC01_077 camp2 /
  ov_SC06_033 camp0) then **R22 clean-fleet 140/140 byte-identical**. Freed `0x8012e778`.
  **⚠️ R22 STATUS-READING NOTE:** the harness reported the background job as `exit code -1` (the session
  forked and killed the shell wrapper AFTER make finished). The verdict was taken from the log's final
  `check-all: 140 passed, 0 failed of 140` — that summary is emitted only on completion, so it proves the
  run finished. Same discipline as the earlier `cmd | tail` masking: **read the gate's own output, never
  the wrapper's exit code.**

- **✅ 2026-07-23 (SESSION-14 cont.) — Vec8 camps uniquified + lifted; `0x8012E778` ×138; queue 10 → 7.**
  `0x8012E778` (the MATRIX-freed core) propagated **138/138 byte-identical, 0 stragglers**. Then `Vec8`:
  camp1 `{s16 unk0,unk2,unk4,unk6}` (8B) ×**139 files** → `Vec8_c1`; the 180-file `{s32 w[8]}` (32B)
  majority keeps the name — **two genuinely different types that had been sharing one identifier across
  TUs of the same overlay**. Both lifted, **319 local copies stripped**; pre-filtered on both camps →
  **R22 clean-fleet 140/140**. Freed `0x8012a464`, `0x8014ffdc`, `0x801502ec`.
  **QUEUE ARC THIS SESSION: 13 → 11 (Buf) → 10 (MATRIX) → 7 (Vec8)** — 6 cores unblocked by uniquify.
  **Remaining camps:** Handler · Blk8 · V8 · Prim · Prim_8016E7C8 (all small).
