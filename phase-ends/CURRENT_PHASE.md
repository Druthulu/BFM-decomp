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
> **STATE AS OF 2026-07-23 (SESSION-14 close) — boxes reconciled against the per-task log.**
> GENUINELY OPEN: **Task 4** (member harvest + grinder family-warm-start + the 2 Phase-22 grinder
> bugs) · **Task 5** (per-overlay Ghidra-C prefetch — ov_SC06_018 done, greedy cover carries on;
> needs `/mcp`, R23/R29) · **Task 6's permuter backlog sweep** · **Task 7** (ROI-gated close —
> BLOCKED: burn-down needs >=3 session-to-session deltas). Everything else is complete.
> **NEXT-SESSION PRIORITY (re-ranked by the SESSION-14 finding): FRESH CRACKS** — the only lever that
> moves distinct-code; the propagation cap is byte-proven to gate de-duplication, not coverage.

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
- [x] **Task 14 stage 2 — type-lift stage [Max]** ✅ 2026-07-23 (SESSION-14): DELIVERED as the broad §20
      type-lift (`lift_types.py` hardened, 154 types) + the UNIQUIFY operation (`uniquify_type.py`, §64/§64a).
      Superseded spec below. — the
      corrected frontier says every remaining lever is ≤~1pp at low measured conversion; Task 7's
      ROI-gated close is the honest alternative. (Superseded spec below.)
- [x] **(SUPERSEDED — see Task 14 stage 2 above; left for its context)** Task 14 — enrich `gate_stage`'s ladder (§57/§59) so more wins auto-integrate + grinder auto-R22
      [Max]** — the permuter-automation program's final stage (Tasks 12→13→14). Justified as the SHARED
      BANKING SPINE, not as a bucket: today 3 of 24 permuter wins were lost to plumbing (12.5% of work
      already paid for in CPU), the 12-draft probe banked 1/12, and crack-wave-4's 6 -O2 cores ×138 were
      explicitly deferred to this ladder. **Corrected ceiling for the integration bucket alone: 0.84pp**
      (NOT the 3.2pp I first quoted — see the valuation correction below). Start by splicing 6–10 failures
      individually and reading real cc1/ld stderr: the shared `conflicting types for built-in function`
      label is a §58 red-herring, so the causes are UNDIAGNOSED.
- [x] **Task 2 — Act on the verdict [Max/xHigh]** ✅ (log: "TASK 2 SUBSTANTIVELY COMPLETE", Arm B tail +
      Arm A verdict-as-banked-fact; the -O0 fleet rollout stays DEFERRED on the splat wall.) Orig spec: — **branch = 2a (tooling).** Build the -O0-cluster
      split rollout (adapt `rollout_whale_o0.py` → per-overlay `[0x13410,c,<ov>_o0]` carve, -O0 Makefile
      rule) + teach `family_sweep --hseq` per-member opt-level awareness; WHOLE-BINARY gate one overlay
      (convert the verdict to a banked fact), then fleet + the type-lift sweep. `member_adapt.py` NOT
      needed for this pool. Originally: (2a) extend `family_remap.symbol_map` + re-run
      the legacy-PURE `family_sweep --hseq` (the ~478k-ins mechanical win); OR (2b) build
      `tools/member_adapt.py` (exemplar→member delta engine + per-member delta briefs); OR both.
- [x] **Task 3 — Core-crack track [Ultracode/xHigh/Max]** ✅ (log: "TASK 3 COMPLETE (both deliverables)" —
      5 banked ×1 + the §53 has_mid_jr interlock; 12 giant drafts preserved.) Orig spec: —
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
- [~] **Task 6 — Mechanical mass [Ultracode/permuter]** — mega-pool track ✅ COMPLETE (+4,801 members via
      `--fix-def-sig`, §54); **permuter backlog sweep still OPEN** (the close-1..4 drafts). Orig spec:
      — `0x80131eec` (2,887×15) + `0x80130d0c` (2,679×15) via `imm_map`; the 550 close-1..4
      backlog drafts via grinder/`permuter_ils`.
- [ ] **Task 7 — Burn-down tracker + velocity/3-metric report + ROI-gated close [Max]** — close
      when per-session yield across both tracks floors out; Roadmap delta; hand P30 an honest frontier.
- [~] **Task 16 — THE INTEGRATION-RECOVERY PASS (measurement-first, blast-radius-typed)**
      SESSION-16, plan approved 2026-07-24 (plan mirror
      `~/.claude/plans/max-effort-set-plan-reactive-gem.md`). The SESSION-15 audit measured the wave
      bottleneck as INTEGRATION (~92% of drafts byte-correct, ~27% bank) — 36 stranded byte-correct
      reach-138 drafts sit in `.run/drafts-s15` (18) + `.run/drafts-s14r` (18), all `ov_SC07_006`.
      Sub-tasks: **T1** instrument the probe ✅ · **T2** S0 measure all 36 [KILL GATE A] ·
      **T3** reproduce the ladder as a baseline · **T4** extend `recover_integration.py` into the
      tiered driver · **T5** run the T0/T1 stages [KILL GATE B] · **T6** class-1 de-macroize probe
      [KILL GATE E] · **T7** bank/propagate/R22/distill.
      **The design spine — a BLAST-RADIUS TAXONOMY that makes §61 structural, not remembered:**
      T0 draft-only → per-binary gate · T1 binary-local (`src/<binary>/**`) → per-binary gate is
      SUFFICIENT (the write set cannot reach another binary) · T2 fleet-shared (`src/shared/**`) →
      **R22 mandatory** (§63 UPDATE: the per-binary gate is necessary-not-sufficient). Every stage
      declares its tier; the driver MEASURES the write set and asserts containment.
      Drew's Phase-Start decisions: probe-then-continue with kill gates; class-1 de-macroize IN
      scope as a bounded ×1 probe (the ×138 variant is OUT of scope).

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

- **📌 → PHASEEND (Drew-requested, 2026-07-23): "would types-first help a fresh decomp / Vagrant Story?"**
  Answer, grounded in this project's own measurements — **mostly NO, with one cheap exception.**
  **(a) For MATCHING: no. Byte-proven three times.** Phases 16/17/18 each re-confirmed struct types are
  **byte-NEUTRAL** for byte-matching: codegen depends on access WIDTH + OFFSET, which we read off the MIPS
  opcode (`lh`/`lhu`/`lw` + displacement); a struct is just a nicer spelling of `*(s16*)(p+0x24)`. Phase 16
  spent a whole phase betting on "recover the actor struct → matching gets easier" and the byte-gate said
  no. **SESSION-14 confirms it from the other side: lifting 154 types banked ZERO new matched functions.**
  **(b) What types actually gate is SHARING, not matching** — and that is ARCHITECTURE-SPECIFIC. Our
  economics are "match once → stamp into 138 near-identical overlays"; a matched body naming a file-local
  type can't enter the shared header, so it can't be stamped (the §20 cap). A game WITHOUT heavy
  cross-binary duplication barely has this lever, so types-first buys much less there. **Unmeasured for
  Vagrant Story** — same compiler (gcc-2.7.2-psx) and CC0 so IDIOMS transfer, but whether VS has
  comparable duplication is unknown; measure before claiming.
  **(c) The cheap day-one exception — a NAMING/PROCESS discipline, not type recovery:**
    1. **Seed the real SDK types immediately.** `MATRIX`/`SVECTOR`/`VECTOR`/`DVECTOR` have documented PsyQ
       layouts. We didn't, and this tree accumulated **THREE contradictory `MATRIX` defs**; the 578-file
       MAJORITY is `{s32 m[3][3]; s32 t[3]}` (48B) while the 71-file camp `{short m[3][3]; long t[3]}` (32B)
       is the DOCUMENTED PsyQ layout. **The most widespread definition in our tree is probably the wrong
       one** — it spread because it never mattered for bytes. Same for `Vec8` existing as 32B AND 8B.
    2. **Forbid drafters from inventing BARE generic type names; require an address suffix.** MEASURED:
       of the 8 collided names, **7 are bare** (MATRIX, Buf, Vec8, Handler, Blk8, V8, Prim); the single
       address-suffixed one (`Prim_8016E7C8`) differs only in a MEMBER's type spelling, not layout.
    3. A shared types header from day one, so anything genuinely common has one home.
  **ROOT CAUSE (the transferable lesson): the camps are self-inflicted** — hundreds of parallel AI drafting
  agents each invented a local name+layout for the same memory. The fix is a convention enforced at DRAFT
  time, which costs nothing; today's cleanup cost a session. **Blunt form: types-first would not have made
  a single function match sooner — a NAMING CONVENTION would have saved most of this session.**
  **📌 → PHASEEND FOLLOW-UP (Drew asked, same session): "are the primitive types now DONE, or are more
  still to define from the PsyQ headers?"** MEASURED: **not done — consistency is fixed, CORRECTNESS is not.**
  - Real PsyQ headers in-tree: **exactly one** (`include/psyq/libcd.h`, Phase 7). **No libgpu/libgte
    headers at all** — no `POLY_F4`, `DR_TPAGE`, `DISPENV`/`DRAWENV`, `P_TAG`.
  - **27 drafter-invented PsyQ LOOKALIKES** now live in `engine_types.h`: MATRIX(+_c1,_c2,2,_8016E7C8,
    _8017E6D8) · SVECTOR(+2,_8016E7C8,_8017E6D8,_80184F08) · VECTOR · DVECTOR2 · P_TAG(+2) ·
    PolyF3/F4/FT3/FT4 · DrawEnv(+1) · TPage/PTag/UVEC/LineF2_8018F694 · Poly_8016CBC0. (159 types total.)
  - SESSION-14 made each type **single-def + shared**; it checked **none** against its documented PsyQ
    layout. Different problems; only the first is done.
  - **It is BYTE-NEUTRAL to fix** (per the verdict above) → a comprehension/public-repo QUALITY item, NOT a
    matching lever. Sequence it with the Gen2 quality work, not the harvest.
  - **⚠️ HAZARD NOW BAKED IN:** the fleet-wide name **`MATRIX` holds the 48-byte** `{s32 m[3][3]; s32 t[3]}`
    while **`MATRIX_c1` holds the 32-byte** `{short m[3][3]; long t[3]}` — the ACTUAL PsyQ layout. The
    canonical-looking name carries the wrong type; a future reader will be misled. Fix when the real
    headers are seeded (rename the true one to `MATRIX`, suffix the imposter).
  - **The real defs are already in hand** (derivable, not research): the **2,599 PsyQ 4.0 types imported
    into Ghidra** (Phase 1, `psyq400.gdt`) + the SDK `.LIB`s at `tools/psyq/` that Phase 8 linked
    byte-identically. `ExportSymbols.java`-style extraction of the .gdt types is the obvious route.

- **✅ 2026-07-23 (SESSION-14 close) — 3 Vec8-freed cores ×138; R22 140/140. ⚠️ AND THE HONEST ROI VERDICT.**
  `0x8012A464`/`0x8014FFDC`/`0x801502EC` propagated **138/138, 0 stragglers**, 3 new groups.
  **R22 clean-fleet 140/140; dedup 1872/0; C1 237654/237654.**
  **THE UNIQUIFY CAMPAIGN'S NET COVERAGE IS ~NIL (P9).** Measured across Buf+MATRIX+Vec8 + 5 propagations
  + 4 R22 cycles: **fn-count 313,429 → 313,435 (+6 functions) · instr +558 · stubs 40,281 → 40,275 (−6)**.
  All three percentages UNCHANGED (79.3 / 67.6 / 88.61). The freed cores' members were **already matched
  individually**; propagation only consolidated them into shared macros.
  **⇒ THE FINDING (R14/R31): the §20 propagation cap was NOT holding back COVERAGE — it was holding back
  source-level DE-DUPLICATION.** "Unblock a capped core" ≠ "bank new bytes". The Buf increment hinted this
  (0 new fns); the full campaign confirms it at scale.
  **SESSION ATTRIBUTION, honestly:** of the session's **−837 stubs / +0.3pp instr / +0.23pp fn-count**,
  **−831 stubs came from the FIRST batch** (broad §20 lift → 13 cores ×138). The entire uniquify campaign
  contributed **−6 stubs**. The recipe, the tool, and the queue drop (13 → 7) are real; the coverage is not.
  **⇒ NEXT-SESSION PRIORITY CHANGES:** do NOT keep uniquifying camps expecting coverage (Handler/Blk8/V8/
  Prim/Prim_8016E7C8 are all small AND now known low-yield). **Fresh cracks are the only lever that moves
  distinct-code**, which sat at exactly 67.6% (3811442/5634875) ALL SESSION, unmoved by any of this.

> **🛑 SESSION-14 CLOSING CHECKPOINT (2026-07-23) — supersedes ALL earlier SESSION-14 blocks. Fresh session safe here.**
> Tree clean (only R23 `db.*.gbf` churn). **R22 clean-fleet 140/140 byte-identical — verified 6× this session.**
> `tools-health` green; **dedup 1872 validated / 0 failed**, C1 237654/237654; 0 NON_MATCHING (G4).
> **Drew pushes** (R6/R20). Commits: `commit:0863` `commit:0864` `commit:0865` `commit:0866` `commit:0867` `commit:0868`
> `commit:0869` `commit:0870` `commit:0871` `commit:0872`.
> **Fleet: 79.3% instr · 67.6% distinct · 88.61% fn-count · 40,275 stubs** (opened 79.0 / 67.6 / 88.38 / 41,112).
>
> **⚠️ BURN-DOWN: do NOT log another `--session-close`.** One was logged MID-session at 79.3% instr (my
> error — the same granularity mistake that manufactured SESSION-13's false floor). Work continued after it,
> but that work moved instr by ~0.00pp, so the recorded boundary is accurate for this session. Floor is
> still UNDETERMINED (needs ≥3 session-to-session deltas) → **P29 must NOT close on ROI.**
>
> **WHAT LANDED:** (1) the **broad §20 type-lift** — 154 types, 2,958 files, after all three carried
> "blockers" proved misdiagnosed (§64); (2) **13 cores ×138, −831 stubs**; (3) the VARIANT plan corrected
> from *reconcile* to **UNIQUIFY** + `tools/uniquify_type.py` (§64a), applied to Buf/MATRIX/Vec8 → blocked
> queue **13 → 7**, 6 cores freed, 5 propagated ×138; (4) R32 fix — `dedup_propagate` now NAMES what it
> skips and splits the 3 causes it had aggregated; (5) the **types-first verdict** + the **PsyQ-primitives
> audit**, both recorded for the PhaseEnd at Drew's request.
>
> **⚠️ THE SESSION'S MOST USEFUL FINDING (and it is a NEGATIVE one): the §20 cap gated DE-DUPLICATION, not
> COVERAGE.** The entire uniquify campaign = +6 functions / −6 stubs / **0.00pp** on all three metrics.
> Roadmap **B4 is re-labelled a maintainability item, not a coverage lever**.
>
> **▶ NEXT (re-ranked BY this finding):**
> 1. **FRESH CRACKS — the only lever that moves `distinct-code`**, which sat at EXACTLY 3811442/5634875 =
>    67.6% at open AND close, untouched by everything above. Breadth-shaped → **prompt Drew for
>    `/effort ultracode` and WAIT for the toggle** (R27). Fuel: `build_wave_args.py --rank live
>    --min-live 100`; the fresh-138 header-decl class (§63) is the known-good integration path.
> 2. Remaining camps (Handler/Blk8/V8/Prim/Prim_8016E7C8) — small AND now known low-yield. **Opportunistic
>    only; never the session's main bet.**
> 3. PsyQ primitive-type correctness (27 lookalikes; the `MATRIX` 48B-vs-32B name hazard) — byte-NEUTRAL,
>    so a Gen2/public-repo QUALITY item, sequenced away from the harvest. Derivable from the 2,599 Ghidra
>    `psyq400.gdt` types.
> **CARRIED:** 7 cores still overlay-local-type-blocked (named in the skip output); 6 cross-overlay
> stragglers correctly dropped (`--recover` NOT used — quadratic thrash hazard).
> **STANDING LESSONS:** a pre-filter is evidence ONLY about what it filtered (pre-filter on a binary that
> FAILED); read the GATE's own output, never the wrapper's exit code (`| tail` masked a 103/140 failure as
> "exit 0"; a session fork later reported a GREEN run as "exit -1"); R14 applies to my own 3-line scripts —
> two produced false evidence before any project tool did.

- **✅ 2026-07-23 (SESSION-14 cont.) — PsyQ primitive-type CORRECTNESS: the `MATRIX` name hazard fixed.**
  **Oracle-sourced (G1, Ghidra `types get`, /LIBGTE.H, psyq400.gdt):** `MATRIX` = **32B** (`short m[3][3]`
  @+0x00, `long t[3]` @**+0x14** — 2B pad after m) · `SVECTOR` = 8B · `VECTOR` = **16B** (`long vx,vy,vz,pad`).
  **THE HAZARD, CONFIRMED AND FIXED:** the fleet-wide name `MATRIX` held `{s32 m[3][3]; s32 t[3]}` = **48B,
  NOT a PsyQ type**, while THREE other names (`MATRIX_c1`, `MATRIX_c2`, `MATRIX2`) held the true 32B layout.
  Swapped by pure consistent rename across **205 files**: the 48B invention → **`MATRIX_L48`** (kept — ~131
  files are byte-correct against it; "fixing" it to 32B would change sizeof/stride and therefore codegen),
  and the true layout now owns **`MATRIX`**. **R22 clean-fleet 140/140 byte-identical.**
  **`VECTOR` left UNCHANGED deliberately:** ours is 12B vs PsyQ's 16B (missing the trailing `pad`), and I
  first called it dead — **WRONG, it has 1 live use** (`engine_core.h` `gte_ldlv0((VECTOR*)sp)`). vx/vy/vz
  offsets already agree so a fix is likely byte-neutral, but it is a LAYOUT change and must not be bundled
  with a rename (an R22 failure would then be ambiguous about which caused it). Own commit, later.
  **`engine_types.h` now carries an oracle-sourced GROUND-TRUTH block** documenting the real layouts, which
  of our names are true vs invented, and the draft-time rule (address-suffix anything you invent — 7 of the
  8 collisions were bare generic names). SCOPE HELD: renamed + documented; did NOT force code onto real
  PsyQ definitions.
  **⚠️ EXIT-CODE TRAP, THIRD VARIANT TODAY:** this R22 was reported by the harness as **"failed, exit 1"** —
  the exit came from my own trailing `grep -c '^\[FAIL\]'`, which returns 1 when it matches NOTHING. The
  failure signal WAS the success. Today the wrapper status has been wrong three separate ways: `| tail`
  masked a real 103/140 failure as exit 0; a session fork reported a green run as exit -1; and now
  grep-no-match reported a green run as exit 1. **Read the gate's own output. Never the wrapper's status.**

- **✅ 2026-07-23 (SESSION-14, ULTRACODE) — fresh-crack wave: 6 reach-138 cores banked; the FIRST distinct-code gain.**
  `wave_binary` fanned 24 xHigh drafters over FRESH (unmatched, live=138) ov_SC07_006 families → 20
  self-reported match_one MATCH. **Whole-binary byte-gate (sole arbiter, R14/G3) banked 6:** func_8014C6F4,
  func_801463A0, func_8012B77C, func_80136F3C, func_80156670, func_801749C8 (`commit:0877`). 1 propagated ×138
  (func_80136F3C), 4 §20-capped, 1 straggler (`commit:0878`). **THE WIN (byte-verified): distinct-code UNIQUE
  count 64832 → 64837 (+5) — the FIRST distinct-code movement of the entire session.** Every prior lever
  today was de-duplication (0 on distinct-code); these are genuinely UNMATCHED cores. Fleet instr 79.3→79.4%,
  fn-count 88.61→88.65%. **The pivot to fresh cracks is byte-validated as the correct lever.**
  **⚠️ WORKFLOW HAZARD + FIX:** the 24 drafters reported MATCH but wrote winners under SCRATCH filenames;
  only 3 func_<name>.c persisted. All 24 were recovered from per-agent transcripts (Write calls + Bash
  heredocs → `.run/drafts-s14r/`). `wave_binary.js` drafter prompt HARDENED: a mandatory copy-back +
  existence check as the final step (a whole wave's winners were nearly lost).
  **⚠️ §63 RECOVERY PASS REVERTED (a clean byte-gate save):** `fix_header_decl` banked 3 more (func_8012CC88/
  func_8014D12C/func_8014CF04) under the PER-BINARY gate, but **R22 clean-fleet FAILED 139/140 — ov_SC01_077
  broke.** `fix_header_decl --check`'s `[SAFE]` verdict is FLEET-BLIND (inspects only the one caller's
  return-use; a shared engine_core.h decl widen reaches all ~137 matched overlays and shifts a caller's
  codegen). Reverting the 12-ref func_8012CC88 didn't fix it → the 2-ref widenings break it too. **Entire
  recovery pass reverted to `commit:0878`; 0 broken landed; R22 re-verified 140/140.** RULE (cookbook §63
  UPDATE): a fix_header_decl edit is §61 shared-state — validate with full R22, the per-binary gate is
  necessary-not-sufficient. The 3 drafts are byte-correct in isolation → backlog (need a per-overlay-local
  decl path, not a fleet header widen).
  **EXIT-CODE TRAP recurred 2 MORE times** (`grep -c` returning 1 on zero matches reported a green R22 as
  "exit 1", twice) + a real one: a FOREGROUND `make build` raced a background R22's build/ dir and produced
  a phantom pass. **Never foreground-build while a background R22 runs; read the gate line, not the wrapper.**

> **🛑 SESSION-14 ULTRACODE CHECKPOINT (2026-07-23) — supersedes the earlier SESSION-14 closing block. Fresh session safe here.**
> Tree clean (only R23 db churn). **R22 clean-fleet 140/140 byte-identical** (verified many times this session);
> 0 NON_MATCHING (G4); dedup 1873/0. **Drew pushes** (R6/R20). HEAD `commit:0879`.
> **Fleet: 79.4% instr · 67.6% distinct (count 64,837, +5 this wave) · 88.65% fn-count · 40,275→~ stubs.**
>
> **THIS ULTRACODE STRETCH (after the /effort ultracode toggle):**
> 1. Housekeeping: reconciled the stale task checklist (Task 8) + PsyQ MATRIX name hazard fixed — the true
>    32B PsyQ layout now owns `MATRIX`, the 48B invention is `MATRIX_L48`, ground-truth block in engine_types.h
>    (Task 9, oracle-sourced via Ghidra `types get`).
> 2. **FRESH-CRACK WAVE (Task 10, the headline):** 24 xHigh drafters over fresh reach-138 ov_SC07_006 families
>    → **6 banked ×1** → **distinct-code count 64832→64837, the session's FIRST distinct-code gain.** The pivot
>    to fresh cracks is byte-validated. Commits commit:0877 / commit:0878 / commit:0879.
>
> **THREE HARD LESSONS (all → docs, all cost real time):**
> - **wave_binary drafters lose their winners** to scratch filenames — recovered all 24 from transcripts;
>   prompt hardened (mandatory copy-back). If a future wave reports MATCH but `.run/<draftdir>/func_*.c` is
>   missing, recover from `subagents/workflows/<runid>/agent-*.jsonl` (Write calls + Bash heredocs).
> - **fix_header_decl `[SAFE]` is FLEET-BLIND** — a shared engine_core.h decl widen broke ov_SC01_077 fleet-wide
>   though it passed the per-binary gate. §61 shared-state → ALWAYS R22-validate. Cookbook §63 UPDATE.
> - **Exit codes lie** (5+ times today): `cmd | tail` masks make status; `grep -c` returns 1 on 0 matches; a
>   FOREGROUND build racing a background R22's build/ gives a phantom pass. **Read the `check-all:` line.**
>
> **▶ NEXT (ranked):**
> 1. **MORE FRESH-CRACK WAVES** — the proven distinct-code lever. Pipeline: `build_wave_args.py --rank live
>    --min-live 100` fuel (ov_SC07_006 has ~57 fresh families left; then greedy-cover the next overlay's
>    prefetch, R23/R29 /mcp). Gate per-TU with `gate_stage --src-file <jr> --no-propagate`, R22, commit,
>    propagate. **Do NOT use fix_header_decl for the integration nears** — it's fleet-blind (backlog those).
> 2. **Permuter backlog sweep (Task 11)** — token-free, close-1..4 nears via grinder/permuter_ils; the 2
>    "carried grinder bugs" were ALREADY fixed in Phase 28 (verified — asm_subdir_for globs */; blacklist
>    purged w/ R35 rule). Runs alongside a wave.
> 3. The 4 §20-capped fresh cracks (0x8012b77c/0x801463a0/0x8014c6f4/0x80156670) → uniquify/lift to bank
>    ×138 (fn-count, low-value de-dup — opportunistic). The 12 s14 nears (drafts in `.run/drafts-s14r/`) →
>    permuter/backlog.
> **DO NOT close P29 on ROI** — burn-down floor undetermined (needs ≥3 session-to-session deltas). One
>    session-close already logged this session — do NOT log a second (SESSION-13 granularity error).

- **📊 2026-07-23 (SESSION-14 close) — REMAINING-WORK MAP + next targets (measured, read-only).**
  **Total distinct work: 9,591 unique fns / 556,531 ins** (the "39,098 stubs" is ×138 fleet-inflation).
  **By band (distinct):** behemoth>1000 5/6,870(1.2%) · large151-1000 609/155,843(28%) · substantial80-150
  1,237/131,048(23.5%) · mid16-79 6,824/252,471(45.4%) · tiny≤15 916/10,299(1.9%).
  **BY REACH — the targeting crux:**
    - **reach≥100 (shared cores): only 153 distinct fns / 11,361 ins — but they cover 21,025 stub-instances
      = 54% of remaining fn-count work.** THE high-leverage batch. 28 substantial + 17 giants + tail.
    - reach 5-99 (regional): 354 fns / 22,630 ins → 2,382 instances.
    - **reach<5 (overlay-UNIQUE): 9,084 fns / 522,540 ins → 15,691 instances.** 94% of distinct work, ×1 each.
  **STRATEGIC READ (honest): the shared-core well is nearly dry (153 left). After it, ~94% of remaining
  work is overlay-unique — no propagation leverage, a linear hand-crack grind.** The endgame transitions
  from "crack once → stamp ×138" economics to "9,000 unique fns, one at a time."
  **NEXT TARGETS, ranked:**
    1. **The 153 reach≥100 shared cores** — highest leverage left; today's fresh-crack wave hit these (6 banked).
       Keep running `wave_binary` waves (`build_wave_args.py --rank live --min-live 100`), gate per-TU, ×138.
    2. **The 954 permuter near-misses (close≤8)** — drafts exist; func_8014F3E8 close=1 reach=134 is 1 ins from
       ×134. **The grinder is running this NOW** (autonomous, byte-gates + commits itself; STOP via
       tools/auto_stop.sh). Skips 1,571 non-permuter (redraft/structural/integration) — only 75 permuter-shaped.
    3. **The 9,084 overlay-unique tail** — the true endgame, ×1 each, no shortcut. Sequence by the mid band
       (6,824 fns = 45% of remaining ins) via per-overlay Ghidra-C prefetch (needs /mcp, R23/R29).
  **GRINDER RUNNING (Task 11):** `.run/grinder_s14.log`; banks+commits byte-verified matches autonomously
  (gate_stage commit=True, fail-closed, winning C persisted pre-bank). Let it run; STOP + it's already committed.

> **🛑 SESSION-15 CHECKPOINT (2026-07-24) — supersedes all earlier SESSION-14/15 blocks. Fresh session safe here.**
> Tree clean (only R23 db churn). **R22 clean-fleet 140/140 byte-identical** (verified many times); 0
> NON_MATCHING (G4); dedup 1879/0. **Drew pushes** (R6/R20). HEAD `commit:0914`.
> **Fleet: 79.6% instr · 67.7% distinct (count 64,860) · 88.86% fn-count.**
>
> **WHAT LANDED THIS SESSION (all byte-gated, committed):**
> 1. **s14 + s15 fresh-crack waves** (ov_SC07_006 reach-138 families): 12 cores banked, 6 propagated ×138.
>    All 24 s15 winners persisted to the canonical path — the drafter-prompt copy-back fix HELD at scale
>    (vs s14's 3/24 recovered from transcripts). match_one isolation (per-pid --work) confirmed clean.
> 2. **Permuter overnight harvest**: ran to EXHAUSTION (75 permuter-shaped candidates), banked **29 distinct
>    fns** (39% conversion), ALL low-reach overlay-unique (0x8017-0x8018). The high-reach near-misses are
>    NOT permuter-shaped (redraft/structural) — permuter can't reach them.
> 3. **distinct-code 64,832 → 64,860 (+28 unique fns)** — the FIRST real distinct-code movement in many
>    sessions (waves +11, permuter +17). Every de-dup lever this session moved it 0.
> 4. **PsyQ MATRIX hazard FIXED** (Task 9): the true 32B PsyQ layout now owns `MATRIX`; the 48B invention is
>    `MATRIX_L48`; oracle-sourced ground-truth block in engine_types.h. VECTOR (12B vs PsyQ 16B, 1 live use)
>    left for its own commit.
> 5. **Backlog pruned + kept-current** (Drew's ask): `backlog.py prune` (6,867 → 1,704 open), wired into
>    `make report`. The backlog was 98% already-banked noise.
>
> **THE HEADLINE FINDING (efficiency audit → decision-log): the crack-wave bottleneck is INTEGRATION, not
> idioms.** Byte-verified: ~92% of drafts are byte-correct (match_one MATCH) but only ~27% bank whole-binary;
> the non-banks are byte-correct bodies stranded by def-side-sig / data-extern / unshared-struct plumbing —
> NOT a missing codegen idiom (only ~2/wave are a genuine residual, the phantom-frame schedule class). We
> strand ~16 paid-for correct functions per 2.6M-token wave. **A fleet-safe integration-recovery pass would
> ~3.7× every wave's yield for ZERO new drafting tokens** — saving ~40M+ tokens over the 153 shared cores.
>
> **▶ NEXT TASK (Tier-1, plan-mode/Max — the approved direction): BUILD THE INTEGRATION-RECOVERY PASS, SCOPED.**
> - Start with the ONE fleet-safe transform already built + hardened this session: **auto-struct-lift via
>   `lift_types.py`** (§64/§64a) as a POST-GATE recovery step, with **MANDATORY R22 self-validation** (the
>   fix_header_decl lesson: a per-binary gate is necessary-not-sufficient for shared-state edits — proven
>   again by a 139/140 probe break this session).
> - **Consume the FRESH per-wave stranded drafts** (in the wave dir), NOT the backlog. The backlog's
>   `closeness` field is UNRELIABLE (byte-correct drafts logged closeness>0) and its drafts are
>   overlay-specific (per-location symbols) → a messy recovery source. The wave-dir strandeds are matched to
>   the right overlay. Live test set: the s15 nears in `.run/drafts-s15/` (16 byte-correct, gate-rejected).
> - Measure the recovered fraction on that set BEFORE adding the riskier def-side-sig / data-extern
>   reconciles (probe-before-scaling). Do NOT use `fix_header_decl` (fleet-blind, §63 UPDATE).
> - Then resume waves at ~3× efficiency. **Waves HELD until Drew re-authorizes** (breadth → prompt for
>   ultracode). The endgame map: 153 reach≥100 shared cores left (the wave lever), then a 9,084-fn
>   overlay-unique tail (×1, hand-crack, no shortcut).
> **CARRIED:** the 16 s15 nears + 18 s14 nears (byte-correct, integration-blocked) in the wave dirs — the
> recovery tool's first fuel. The 2 s15 genuine nears (func_80175820/func_801758FC, phantom-frame) → permuter.
> **DO NOT close P29 on ROI** — burn-down floor undetermined.

- **✅ 2026-07-24 (SESSION-16, Max) — Task 16 / T1: the two-oracle blocker probe BUILT. Read-only; `src/` untouched.**
  **`tools/rtu_match.py` (2 additions).** `--stderr-out PATH` persists EVERY stage's stderr via an
  `atexit` flush (so all `sys.exit` paths are covered); `//@EDIT` replacements now accept `\n`
  (multi-line), which T6's macro expansion needs. **The `--stderr-out` change earned itself on its
  first run:** the tail rtu_match prints inline for `func_80161374` is **100% warnings**, while the
  real errors sit ~180 lines earlier. Nobody diagnosing from that tail could have seen the cause —
  §58's red-herring one level down, and the reason every prior per-function verdict for these
  drafts was inferred rather than read.
  **`tools/blocker_probe.py` (NEW, read-only, two oracles — R34).** *Static:* `cdecl.parse` +
  **`cdecl.compatible`** (never text equality — `.run/diag_plumbing.py` compared decl TEXT, so
  `extern u8 D_X;` vs `extern unsigned char D_X;` read as a conflict though `common.h` makes them
  the same type; that is very likely the whole "~10 data-extern co-blockers" figure). *Real cc1:*
  shells out to `rtu_match` (ONE implementation of the compile, R33) → `CC1-FAIL:<first non-warning
  error>` / `MATCH` / `DIFF`. Output leads with the DISAGREEMENT table, not the agreement rate.
  **DELETED `.run/diag_plumbing.py`** (R3 tooling belongs in `tools/`; R33 — net −1 scanner).
  **Two corrections the build forced (both would have mis-routed the recovery):**
  **(1) `cdecl.tu_scope` runs REAL cpp** (`tu_statements`, the §8c law) — so it ALREADY expands an
  instantiated `DEFINE_func_*` macro body and is authoritative about whether a conflict exists. My
  first cut added a redundant macro scanner for DETECTION. Its real job is **ATTRIBUTION**: a decl
  in the TU's own text is rewritten in place (`normalize_self_decls`), one inside an instantiated
  shared-header macro is escaped by de-macroizing that single instantiation (§63's route). Both are
  T1 — but they are different edits, and the first version mis-labelled the second as the first.
  Byte-checked against the tree: `func_80161374` has NO literal decl in its TU (only the
  `INCLUDE_ASM` at :3861 and `DEFINE_func_80161278()` at :3853); the conflicting
  `extern void func_80161374(void *a0, s32 a1);` is `engine_core.h:7533`, inside the macro body.
  The probe now reports exactly that.
  **(2) BLOCKERS STACK, and cc1 only ever reveals the FIRST.** All 3 smoke-test functions carry
  2–5 independent blockers (e.g. `func_80161374`: 4 callee_decl + 1 self_decl_hdr). So the tier a
  function needs is the **MAX** over its blockers, not the first one's — and the static oracle's
  COMPLETE list is the routing signal, with cc1 confirming only "yes, it is a decl conflict".
  **Smoke test (3 fns, `-v`): both oracles AGREE 3/3, 0 static-only, 0 cc1-only.** Not yet evidence
  about the population — that is T2.

- **✅ 2026-07-24 (SESSION-16, Max) — Task 16 / T2 = S0: KILL GATE A PASSED ON MEASURED NUMBERS, and
  the §20 "DEF-conflict is unrecoverable by text transform" doctrine is REFUTED for the per-overlay case.**
  Whole probe over all 36 stranded drafts: **9.2 s**. Both oracles agree 36/36 (0 static-only, 0 cc1-only).
  **THE POPULATION, corrected (R14).** The SESSION-15 audit's "~92% of drafts are byte-correct" is a
  WHOLE-WAVE figure. Among the STRANDED residue, `match_one` says **24/36 MATCH · 11 near · 1 ERR = 67%**.
  The 11 `near` are unfinished drafts, NOT integration problems — and they are exactly the 4 that
  compile in their real TU and DIFF. So "we strand ~16 paid-for CORRECT functions per wave" is ~11,
  not 16, and one third of the "stranded correct" premise was never correct.
  **BLOCKERS (per-blocker counts; they STACK — cc1 reveals only the first):** `self_decl_hdr` **21** ·
  `callee_decl` 19 · `data_decl` 16 · `self_decl_tu` 5 · `local_type` 5. **Per function by MAX tier:
  T0=6 · T1=26 · not-an-integration-problem=4.** The dominant blocker is the SHARED-HEADER self-decl —
  far bigger than the pre-probe static inference (6–7 of 16) predicted.
  **T3's baseline, measured early and for free.** Running the EXISTING draft-side ladder transforms
  (`cast_call_sites` + `reconcile_tu`) over all 36 clears what they target — `callee_decl` 19→3,
  `data_decl` 16→**0** — and converts exactly **1 of 36** from CC1-FAIL to compiling, which then
  **DIFFs**. That is §61d reproducing verbatim: dissolving the plumbing reveals what the plumbing hid.
  The existing ladder cannot bank this population; the wave's gate orchestration was NOT broken.
  **THE ESCAPE, BUILT AND BYTE-PROVEN — `tools/demacroize.py` (NEW).** The conflicting `extern` lives
  INSIDE a `DEFINE_func_*` macro BODY in `engine_core.h`, so it exists only where the macro is
  INSTANTIATED. Replacing those instantiations, in this overlay's own TU, with the macro's own
  expansion — correcting ONLY the conflicting decl to the draft's byte-true sig, never dropping it
  (§57a-1) — dissolves the conflict while writing nothing outside `src/ov_SC07_006/`. This is the
  "per-overlay-local decl" §63's own note named as the unexplored alternative.
  **Measured on the 14 clean candidates** (match_one MATCH, `self_decl_hdr` their only remaining
  blocker): **13 MATCH / 1 DIFF** in the REAL TU (1–12 macro instantiations each; `func_8014F3E8`
  DIFFs at 28-vs-32 ins — a short draft, not an integration failure).
  **END-TO-END PROOF (the arbiter, not the proxy):** `func_8012CC88` (6 instantiations)
  → `harvest_verify --chunk 1` → **verified 1 / failed 0, BYTE-IDENTICAL**; stub gone, confirmed by
  `grep INCLUDE_ASM` on the source, never the report (§55b trap 4).
  **THE TIER CLAIM, VALIDATED EMPIRICALLY:** full R22 `make clean && extract-all && check-all` →
  **140 passed, 0 failed of 140** (80 s). A `src/<binary>/**`-confined edit does not perturb the
  fleet — which is precisely the difference from `fix_header_decl`, whose `src/shared/` write broke
  139/140 under the same per-binary green light (§63 UPDATE).
  **GATE A:** cond-1 ≥12/36 with a real decl/type error → **32/36 PASS**; cond-2 ≥12/36 rtu-MATCH
  once the blocker is simulated → **13/36 PASS**. Proceed.

- **✅ 2026-07-24 (SESSION-16, Max) — Task 16 / T5+T6: 14 STRANDED DRAFTS RECOVERED AND BANKED. R22 140/140 ×3.**
  **Banked ×1, all whole-binary BYTE-IDENTICAL** (stub-gone confirmed by `grep INCLUDE_ASM`, never the
  report — §55b trap 4): `func_8012CC88` `func_8012F40C` `func_80138DE0` `func_80144B14` `func_80146750`
  `func_80147364` `func_8014CF04` `func_8014D12C` `func_8014D610` `func_80161374` `func_8016163C`
  `func_80161774` `func_80161888` `func_801778A8`.
  **Recipe:** existing draft-side transforms (`cast_call_sites` → `reconcile_tu`) → **`demacroize --apply`**
  → `harvest_verify --chunk 1` → R22. Every rtu-MATCH in the self-decl class converted: **13/13**.
  **GATE B** (≥4/36 required): **14/36 = 39%** — passed with room.
  **THE GENERALIZATION THAT PAID:** relaxing `demacroize` from "the draft's own function" to "any decl
  the DRAFT declares incompatibly" reached the callee-conflict variant too (`RotTransPers`/`RotTransSV`
  declared differently by a macro than by the draft) — `func_8012F40C` banked on it.
  **⚠️ THE ONE FAILURE, AND WHAT IT TEACHES (§65c):** `func_8012F49C` was rtu-MATCH but the whole-binary
  gate REJECTED it. rtu_match is **relocation-masked**, so a wrong call TARGET is invisible to it and
  fatal to the real link — and this was a *callee*-decl case, i.e. exactly where the correction touches
  something the mask hides. **Trust rtu MATCH for self-decl corrections; distrust it for callee ones.**
  I reverted its edits and re-banked only the winner rather than leave byte-neutral churn on matched
  code (§57a-4). Cost: one build. The gate remains the only arbiter (G3/P9).
  **METRICS (honest):** distinct-code **64,860 → 64,874 unique fns (+14)** — the FULL credit, since
  `progress.py:645` marks an h_exact class matched if ANY instance is. instr-weighted **79.6%** and
  fn-count **88.86%** are ~FLAT, because a de-macroized bank is ×1 and cannot propagate ×138. That
  price was stated in the plan before the work. dedup 1879/0; 0 NON_MATCHING (G4).
  **THE HONEST MULTIPLE:** 14 of 36 = **39%** recovered, vs the SESSION-15 projection of "all 22".
  Implied wave bank-rate 6/24 → ~20/24 = **~2.3×, not 3.7×** — and it lands on distinct-code, not on
  the decomp.dev display number. Right trade for the 0-stubs contract; wrong one for the headline.
  **DISTILLED IN-SESSION (R30):** cookbook **§65/§65a–§65e** (the blast-radius taxonomy · the
  de-macroize escape + the §20 refutation · the rtu-vs-gate divergence · the existing-ladder baseline ·
  the two-oracle practice) · `docs/decision-log.md` (R31) · `docs/calibration.md` (the measured table) ·
  `docs/SETUP.md` tooling rows for `blocker_probe`/`demacroize` **plus the three rows the inventory was
  missing** (`lift_types`, `uniquify_type`, `fix_header_decl`-as-retired) — R21 debt cleared.
  **CARRIED, named (not silently dropped):** 10 `match_one`-MATCH drafts still blocked by stacked
  classes — 3 `self_decl_tu` (→ `normalize_self_decls`, the other named-but-unwired ladder stage),
  3 `local_type`+`self_decl_hdr` (→ draft type uniquify, which already exists as
  `canon_sig_reconcile._uniquify_draft_types`, then de-macroize), 1 struct-TAG redefinition
  (`func_80173A60` — the static oracle's blind spot, named by cc1), 1 rtu-over-claim (`func_8012F49C`),
  2 with no static blocker whose real cc1 error still needs reading. The 11 `near` drafts are NOT
  recovery fuel — they are unfinished drafts and belong to the permuter/redraft track.
  **STILL OPEN (T4):** encoding this recipe into `tools/recover_integration.py` (add `--draft-dir`,
  `--run-id`, tier assertion, `banked_from_source`) so future waves run it as one command. The recipe
  is now PROVEN, so the driver can be written against a measured procedure rather than a hypothesis.



> **🛑 SESSION-16 CHECKPOINT (2026-07-24, Max) — supersedes SESSION-15. Fresh session safe here.**
> Tree clean (only R23 `db.*.gbf` churn — never staged). **R22 clean-fleet 140/140 byte-identical**
> (verified 3× this session); 0 NON_MATCHING (G4); dedup 1879/0. **Drew pushes** (R6/R20).
> HEAD `commit:0919`. Commits: `commit:0916` `commit:0917` `commit:0918` `commit:0919`.
> **Fleet: 79.6% instr · 67.7% distinct (count 64,874, +14) · 88.86% fn-count.**
>
> **THE SESSION IN ONE LINE:** the wave-integration bottleneck was measured rather than assumed, and
> the measurement both **shrank the prize** (the audit's 3.7× is really ~2.3×, on distinct-code only)
> and **opened a wall §20 had closed for 9 phases** — a byte-correct draft blocked by a shared-header
> macro decl can be recovered *per overlay*, without touching the shared header at all.
>
> **WHAT LANDED (all byte-gated, committed):**
> 1. **`tools/blocker_probe.py`** (NEW, read-only, two oracles R34) + `rtu_match --stderr-out` and
>    multi-line `//@EDIT`. Deleted `.run/diag_plumbing.py` (R33 net −1).
> 2. **`tools/demacroize.py`** (NEW) — the per-overlay-local decl escape (§65b). **T1**: writes
>    confined to `src/<binary>/**`, so no R22 risk is created by construction.
> 3. **14 stranded drafts recovered and banked ×1**, R22 140/140 three times.
> 4. **Cookbook §65/§65a–e**, decision-log (R31), calibration.md, SETUP.md (+3 missing inventory rows).
>
> **FOUR FINDINGS THAT CHANGE THE PLAN (all measured, all in §65):**
> - **The residue is 67% byte-correct, not ~92%** — that figure was whole-wave. A third of the
>   "stranded correct functions" premise was never correct (the 11 `near` are unfinished drafts).
> - **The existing ladder cannot reach this population**: it clears its own classes (callee 19→3,
>   data 16→0) and converts **1 of 36** to compiling, which then DIFFs. §61d verbatim.
> - **§20's DEF-conflict wall is REFUTED per-overlay.** Its reasoning was right about the shared
>   header and never asked what one overlay's own TU can do locally.
> - **`rtu_match` MATCH is class-dependent evidence**: 13/13 on self-decl, failed on the first
>   callee-decl case (it is relocation-masked, so a wrong call target is invisible to it).
>
> **▶ NEXT (ranked):**
> 1. **T4 — encode the recipe in `tools/recover_integration.py`** (`--draft-dir`, `--run-id`, tier
>    assertion via `git status` containment, `banked_from_source`, run-local `verified_out` to close
>    §55b trap 4). The recipe is now PROVEN, so the driver is written against a measured procedure.
>    Until it exists, running the recovery on a new wave is manual.
> 2. **The 10 carried MATCH drafts**, each named with its blocker above: 3 `self_decl_tu` (wire
>    `normalize_self_decls` — still the only named-but-unwired ladder stage), 3
>    `local_type`+`self_decl_hdr` (`canon_sig_reconcile._uniquify_draft_types` already exists), 1
>    struct-TAG redefinition, 1 rtu over-claim, 2 needing their real cc1 error read.
> 3. **Then resume waves** (breadth → prompt Drew for `/effort ultracode`, R27) at the measured ~2.3×.
> **⚠️ `dedup_propagate --auto-from` would RE-MACROIZE the de-macroized sites and undo them.** Always
> `--check-only` first and assert the 14 banked addresses are absent from the plan (§55b bans
> `--auto-from` anyway; use targeted `--addr`).
> **DO NOT close P29 on ROI** — burn-down floor still undetermined.

- **✅ 2026-07-24 (SESSION-16, Max) — Task 16 / T4: the recipe ENCODED in `tools/recover_integration.py`.**
  Extended, not replaced (a new driver would be a 7th snapshot implementation — R33). It already owned
  the right shape: exact snapshot/restore, split-aware grouping, and the two-pass
  *gate-all → restore → re-stage winners only* protocol.
  **Added:** `--draft-dir` (repeatable — consume a WAVE dir, not the backlog, whose `closeness` is
  unreliable and whose drafts are overlay-specific) · `--run-id` (all scratch under
  `.run/recover/<id>/`, and run-local `verified_out`/`failed_out` passed into `run_gate` — **closes
  §55b trap 4, which the cookbook still lists as "armed"**) · `--stages` with the new **demacroize**
  stage · `--max-tier` · `--r22` · `--probe-only` · `--report`.
  **The tier taxonomy is now ENFORCED, not documented:** each stage declares T0/T1/T2; the driver
  measures the write set via `git status --porcelain` before/after and **aborts** if a stage writes
  outside its declared blast radius (§61d: an undo narrower than the write scope destroys work no
  byte-gate can see). A fleet-tier stage is refused unless `--max-tier fleet` AND `--r22` are both
  given. Negative-control-tested: both refusals fire with the right message.
  **`stub_map` now derives from `corpus.stubs`** (R33 — one coverage-asserting oracle) instead of a
  private regex that could silently return a short map; **`banked_from_source()`** (stub GONE from src)
  is the sole bank oracle for reporting.
  **END-TO-END on the remaining 22 strandeds: excluded the 26 already-banked by name, ran demacroize on
  12 of 22, banked 0, restored exactly (src/ clean), 14/14 prior banks intact.** A clean negative —
  the driver does not manufacture banks. Those 22 are the 11 unfinished `near` drafts plus the 10 whose
  blockers stack beyond this stage (they need `normalize_self_decls` / draft type-uniquify wired next).

- **⚠️ 2026-07-24 (SESSION-16, Max) — Task 16 / T8: `normalize_self_decls` does NOT recover the
  `self_decl_tu` class as-is. Reverted; honest negative, nothing landed.**
  Targets were the 3 carried MATCH drafts whose own function is declared incompatibly by literal TU
  text (not a macro): `func_801376E8`, `func_80163534`, `func_8016706C`.
  **Gap 2 confirmed exactly as predicted:** `func_801376E8` normalizes **0** decls — NSD skips a
  literal `()` unconditionally (line ~160), and its conflict is on the RETURN type (`void` vs
  `void *`), which a no-prototype does not excuse. The skip's comment is right about PARAMS and blind
  to the return.
  **The other two produced edits and BROKE THE BUILD** (`harvest_verify` → `final SHA None`, i.e. no
  image, not a byte-DIFF): NSD rewrote each TU decl to the draft's narrow sig
  (`(s32 a0)`→`(short)`, `(s32×6)`→`(s32,u16,u16,s32,u16,s32)`). Reverted with `git checkout`;
  `make check BINARY=ov_SC07_006` → **BYTE-IDENTICAL**, tree clean.
  **Why this is not a surprise, and what it costs:** §57a already classes NSD as **SURGICAL-ONLY** —
  it edits the TU FILE, so a bad edit poisons the whole group and, unlike a bad DRAFT, cannot be
  bisected away per-member. That is exactly what happened. **It needs its own diagnosis session**
  (read the real cc1/ld error from the failing build, not the classified file — which was empty
  because classification never ran once the build produced no image at all).
  **So the `self_decl_tu` class (5 blockers / 3 carried functions) stays OPEN**, and the recovery
  pass's measured yield stands at **14 of 36**. I did not force it: forcing a TU edit past a failing
  build is how the ≈0% doctrine got manufactured.

> **🛑 SESSION-16 FINAL CHECKPOINT (2026-07-24) — supersedes the SESSION-16 block above. Fresh session safe here.**
> Tree clean (only R23 `db.*.gbf` churn). **R22 clean-fleet 140/140** (3× this session); `make check
> BINARY=ov_SC07_006` BYTE-IDENTICAL after the T8 revert; 0 NON_MATCHING (G4); dedup 1879/0.
> **Drew pushes** (R6/R20). HEAD `commit:0922`. Commits `commit:0916` `commit:0917` `commit:0918` `commit:0919`
> `commit:0920` `commit:0921` `commit:0922`.
> **Fleet: 79.6% instr · 67.7% distinct (count 64,874, +14) · 88.86% fn-count.**
>
> **DELIVERED:** the measurement (Gate A, two oracles, 9 s for 36 drafts) · `tools/blocker_probe.py` ·
> `tools/demacroize.py` · **14 stranded drafts recovered and banked** · the recipe encoded in
> `tools/recover_integration.py` with **tiers ENFORCED** (write-set assertion + validator selection)
> and **§55b trap 4 closed** · cookbook **§65/§65a–e** · decision-log · calibration · SETUP (+3 rows).
>
> **▶ NEXT (ranked, all named with their blocker):**
> 1. **Diagnose `normalize_self_decls`** (T8's negative) — it breaks the build on the narrow-param
>    rewrite, and its literal-`()` skip is blind to RETURN-type conflicts. Read the real cc1/ld error
>    from the failing build (the classified file is EMPTY when no image is produced — a gap worth
>    fixing in `harvest_verify` too). Unblocks 3 carried functions.
> 2. **The `local_type` class (3 fns)** — `canon_sig_reconcile._uniquify_draft_types` already exists;
>    rename the draft's colliding type (T0, draft-only, byte-neutral) then de-macroize.
> 3. **`func_80173A60`** — struct-TAG redefinition, the static oracle's known blind spot (cc1 named it).
> 4. **Then resume waves** at the measured ~2.3× — breadth-shaped, so **prompt Drew for
>    `/effort ultracode` and WAIT for the toggle** (R27).
> **⚠️ STANDING HAZARD:** `dedup_propagate --auto-from` would RE-MACROIZE the 14 de-macroized sites and
> undo them. `--check-only` first; targeted `--addr` only (§55b bans `--auto-from` anyway).
> **DO NOT close P29 on ROI** — burn-down floor still undetermined.

- **⚠️ 2026-07-24 (SESSION-16, xHigh) — Task 16 / T9: the `local_type` class does NOT recover either.
  0 of 4 banked. Reverted; nothing landed; `make check` BYTE-IDENTICAL; tree clean.**
  Targets `func_8014C4AC` (Blk8) · `func_80174CB0` (MATRIX/SVECTOR) · `func_80176144` (S_AF634) ·
  `func_80173A60` (struct-TAG `S80126B38`).
  **The ordering bug I introduced and then fixed (worth the record):** uniquifying the draft's type
  renames it inside the draft's own `extern <T> D_x;` decls too, so it **trades a `redefinition of
  struct T` for a `conflicting types for D_x`** — i.e. running it AFTER `reconcile_tu` re-breaks what
  that pass had conformed. Re-ordered (uniquify FIRST), one compiled — and then **DIFFed 48/53**,
  because the data reconcile's cast-at-use genuinely changes codegen when the body depends on its own
  struct layout. A struct-TYPED data extern is the case `reconcile_tu` cannot cast.
  **`func_8014C4AC` is the instructive one:** `rtu_match` MATCH, then the whole-binary gate returned
  **`final SHA 6a37625c…` — a REAL hash, not `None`** — meaning the *baseline* (draft reverted,
  de-macroize edits still applied) no longer built byte-identical. The de-macroize edit itself shifted
  the codegen of one of the four macros' OWN already-matched functions. **That is the §63 failure mode,
  relocated from the fleet (where it broke 139/140 invisibly) into a place the per-binary gate catches
  for free.** Measured boundary: **de-macroize is byte-neutral 14 times of 15.**
  **Read the FINAL SHA, not the verified count:** `None` = no image (compile/link break, T8's shape);
  a real hash ≠ locked = the TU edit moved bytes (T9's shape). Different faults, different fixes.
  **⇒ Two consecutive honest negatives (T8, T9). The EXISTING transforms stop at 14 of 36 (39%).**
  The remaining ~8 are not "run one more tool" — each needs a transform that does not exist yet.
  Distilled to cookbook **§65f** (the lever's measured boundary + the SHA-reading rule) and **§65g**
  (where the cheap levers stop, so the next session does not re-buy this negative).

> **🛑 SESSION-16 CLOSING CHECKPOINT (2026-07-24) — supersedes ALL earlier SESSION-16 blocks. Fresh session safe here.**
> Tree clean (only R23 `db.*.gbf` churn). `make check BINARY=ov_SC07_006` **BYTE-IDENTICAL**; last full
> R22 **140/140**; 0 NON_MATCHING (G4); dedup 1879/0. **Drew pushes** (R6/R20). HEAD `commit:0925`.
> **Fleet: 79.6% instr · 67.7% distinct (count 64,874, +14) · 88.86% fn-count.** ov_SC07_006 stubs 344→330.
>
> **THE SESSION'S RESULT IN ONE LINE:** the integration-recovery pass is BUILT, PROVEN, and ENCODED —
> and its ceiling with existing transforms is **measured at 14 of 36 (39%)**, not the projected "all 22".
>
> **DELIVERED:** `tools/blocker_probe.py` (two oracles) · `tools/demacroize.py` (the per-overlay escape
> that refutes §20's DEF-conflict wall) · **14 stranded drafts banked** · the recipe encoded in
> `tools/recover_integration.py` with tiers ENFORCED and §55b trap 4 closed · cookbook **§65–§65g** ·
> decision-log · calibration · SETUP (+3 missing rows).
>
> **THREE BYTE-RECORDED NEGATIVES — do NOT re-buy them:**
> - **`self_decl_tu` class (3 fns): 0 banked** — `normalize_self_decls`'s `()` skip is blind to
>   RETURN-type conflicts, and its narrow-param rewrite breaks the build (`final SHA None`). §57a
>   already classed it SURGICAL-ONLY.
> - **`local_type` class (4 fns): 0 banked** — uniquify trades `redefinition of struct T` for
>   `conflicting types for D_x`; fixing the order lets one compile, which then DIFFs 48/53 (a
>   struct-TYPED data extern is what `reconcile_tu` cannot cast).
> - **de-macroize is byte-neutral 14 of 15**, not always (§65f) — the 15th shifted a macro's own
>   already-matched function, caught by the gate for free.
>
> **▶ NEXT — the productive path is to RESUME THE WAVES, not to grind the residue.**
> The recovery pass converts ~39% of a wave's strandeds, and a wave produces FRESH strandeds in the
> classes it handles (`self_decl_hdr` was 21 of 36). Grinding the current ~8 leftovers means building a
> new transform per function; running a wave and recovering it is the better trade.
> Waves are breadth-shaped → **prompt Drew for `/effort ultracode` and WAIT for the toggle (R27)**.
> Pipeline: `build_wave_args.py --rank live --min-live 100` → wave → then
> `recover_integration.py --draft-dir <wave dir> --binary <ov> --run-id <id> --stages demacroize
> --no-propagate --r22`.
> **⚠️ STANDING HAZARD:** `dedup_propagate --auto-from` would RE-MACROIZE the 14 de-macroized sites and
> undo them. `--check-only` first; targeted `--addr` only.
> **DO NOT close P29 on ROI** — burn-down floor still undetermined.

> **📋 SESSION-17 QUEUE (agreed with Drew 2026-07-24, at the SESSION-16 close) — read this FIRST.**
>
> **THE PLAN: small batches, isolated agents, xHigh, NO ultracode.**
> Batch size is a RISK lever, not a token lever: each agent drafts one fn in its own context, so N
> agents cost ~N× one agent whether concurrent or serial (~110k tok/drafted fn, measured s14+s15).
> Concurrency buys wall-clock only. Therefore **batches of ~5–6**: ~600k tokens of exposure per batch,
> a measured yield before committing the next, and a clean stop at any boundary.
> - **Do NOT draft one-at-a-time in the MAIN LOOP** — results accumulate in the orchestrator's context
>   and are re-read every turn (quadratic). Small batch via ISOLATED agents keeps that flat.
> - **Ultracode is NOT needed** for a batch this size (it is xHigh + large-scale orchestration; agents
>   spawn fine at xHigh). R26/R27 govern big fan-outs. Phase-13 T7 measured Max 14/80 vs UC 13/80 =
>   noise, so per-agent depth does not move drafting yield anyway.
> - A dying batch is survivable: Workflow runs are RESUMABLE (completed agents cached+replayed) — a
>   13-agent wave already hit a usage limit at 2/13 this phase and resumed cleanly to 13/13.
> - Free tiers do NOT apply to this fuel: local v3 saturates at ≤15-ins (these are 80+), and the
>   token-free permuter was run to EXHAUSTION last session (75 candidates).
> **Pipeline:** `build_wave_args.py --rank live --min-live 100` → 5–6 drafters →
> `recover_integration.py --draft-dir <wave dir> --binary <ov> --run-id <id> --stages demacroize
> --no-propagate --r22` → commit → targeted `dedup_propagate --addr` (NEVER `--auto-from`).
> **Expected:** 24 drafts used to yield 6 banks (~460k tok each); with recovery ~13/24 ≈ **200k tok per
> banked fn**. A 6-batch should bank ~3. ⚠️ That 2.3× is PROJECTED — the 39% recovery was measured on
> OLD strandeds, not on a fresh wave's output. **The first batch tests the projection.**
>
> **⚠️ TOOL-VERIFICATION STATUS — what is byte-proven vs what is NOT (do not assume):**
> - **BYTE-PROVEN, heavily exercised:** `rtu_match` (--stderr-out + multi-line //@EDIT, ~60 runs) ·
>   `blocker_probe` (36 drafts ×3 runs, both oracles, attribution bug found+fixed+re-verified against
>   the tree) · `demacroize` (**15 whole-binary gate attempts: 14 banked byte-identical, 1 correctly
>   REJECTED** — both `--emit-edits` and `--apply`, self-decl AND callee-decl forms).
> - ~~**NOT VERIFIED — `recover_integration.py`'s SUCCESS PATH.**~~ **DONE 2026-07-24 (SESSION-17) — the
>   free test was run and the success path is VERIFIED end-to-end** (pass1 → restore → pass2 → `--commit`
>   → `r22()` → `--report`). See the T10 log entry below: it also found 2 real defects, both fixed.
>   STILL unexercised: `assert_write_set`'s ABORT branch and `r22()`'s failure-detection branch (both
>   only fire on a fault this run did not produce).
> - **THE FREE TEST (the recipe, now proven — cookbook §66):** revert ONE banked function back to its
>   stub, then re-bank it THROUGH the driver (`--draft-dir` on the saved draft, `--commit`, `--r22`).
>   Two properties make it strong: the reverted stub state must rebuild BYTE-IDENTICAL (so a faithful
>   revert proves itself — but it needs `make extract` first, or the `.s` the stub includes does not
>   exist), and `git diff <pre-revert-commit> -- src/` must come back EMPTY (the driver has to reproduce
>   the known-good state character-for-character). One build's cost.
> - Known+recorded LIMITATION (not a bug): `blocker_probe`'s static oracle is blind to a bare
>   `struct Tag {…}` redefinition — cc1 catches it (§65e). Leave it; the second oracle covers it.

- **✅ 2026-07-24 (SESSION-17, high on Opus 5) — Task 16 / T10: the driver's SUCCESS PATH is VERIFIED
  end-to-end by the free re-bank test, and it surfaced TWO real defects — one of them a safety hole.**
  **THE TEST (cookbook §66).** Target `func_801778A8` (the clean single-blocker case: `self_decl_hdr`
  only, tier T1, draft preserved in `.run/drafts-s15`). Reverted its bank surgically — the def back to
  `INCLUDE_ASM`, and the 2 de-macroized instantiations (`DEFINE_func_80176FF4` / `DEFINE_func_80177340`)
  back to their macro form. **The reverted stub state rebuilds BYTE-IDENTICAL** (`7ca772be…` ==
  `config/check.ov_SC07_006.sha`), so the revert proved itself before the driver ran. *It needed
  `make extract` first:* splat only emits `asm/nonmatchings/**/<fn>.s` for functions NOT defined in
  source, so the `.s` the restored stub includes did not exist yet (`can't open …/func_801778A8.s`) —
  the R22 corollary in its source-reverted form.
  **THE RUN:** `recover_integration.py --draft-dir .run/drafts-t17a --binary ov_SC07_006 --run-id t17a
  --stages demacroize --no-propagate --commit --r22 --report` → `pass 1 banked 1/1` → exact restore →
  `pass 2 banked 1/1` → commit **`commit:0928`** → **R22 `check-all: 140 passed, 0 failed of 140`** →
  `report.json {"banked":["func_801778A8"],"r22":true,"tier":"binary"}`. Bank confirmed from the SOURCE
  (`grep INCLUDE_ASM` → gone), never the report (§55b trap 4).
  **THE EQUIVALENCE CHECK — the part that makes this a test and not a smoke test:** `git diff commit:0927
  -- src/` = **one blank line**, which I introduced in the hand revert. The driver reproduced SESSION-16's
  banked state character-for-character.
  **⚠️ DEFECT 1 (SAFETY — found by READING the path before firing it).** **Propagation is a FLEET-tier
  write and was both undeclared and the DEFAULT.** `run_gate(propagate=True)` shells out to
  `dedup_propagate --auto-from`, which writes `src/shared/engine_core.h` + up to 138 overlay `.c` — so
  `--max-tier binary` (the default, meaning "no shared-state edits") still permitted the widest write in
  the toolchain. The §65a taxonomy had been applied to the stages I wrote and NOT to the pipeline's own
  inherited behaviour. **`assert_write_set` structurally cannot catch it:** it runs before the gate, and
  under `--commit` the writes are already committed, so `git status --porcelain` sees a clean tree and
  passes. **FIXED up front, the way stage tiers already are:** propagation now requires `--max-tier fleet`
  AND `--r22`, and is **refused outright after a `demacroize` stage** (those banks are ×1 by construction
  and `--auto-from` would re-macroize the expanded sites and undo them — `demacroize.py`'s own stated
  price, and §55b bans `--auto-from` regardless). Ordered general-rule-first so BOTH branches stay
  reachable; **both negative-control-tested, exit 1.** This retires the checkpoint's "STANDING HAZARD"
  from something you must remember into something the tool refuses.
  **⚠️ DEFECT 2 (METRIC).** `gate_stage` scraped the fleet % with a regex for a `progress.py` label that
  no longer exists (`byte-identical :` → the three-metric block). `fp` has been `None` ever since:
  **50 gate commits record `fleet None%`** (counted in `git log`). Fixed to read `FLEET instr-weighted`
  with the legacy label as fallback **and a loud stderr warning when neither matches** — now parses 79.6.
  **STALE DIGEST (R14, caught in passing).** `docs/progress.fleet.md` at HEAD disagreed with HEAD's own
  source by 45 in the dedup-shared attribution (`238365` vs `238410`; ov_SC07_006 `1503` vs `1548`).
  Regenerating from committed source gives 238410 in **two independent runs** (in-gate and standalone),
  and `commit:0919` had already recorded 1548 — so the committed digest was generated during the §65g
  `local_type` trial, whose edits were then reverted. Headline percentages unaffected (79.6/67.7/88.86);
  the regenerated file is committed. Lesson: regenerate digests on a CLEAN tree.
  **VERIFICATION:** `make tools-health` → **OK** (corpus(+resident) 0 PHANTOM/0 TRUNCATED · cdecl ALL
  ORACLES GREEN · audit-binaries 140 onboarded, every one a full citizen · lint OK · **dedup-check 1879
  validated / 0 failed**, C1 238484/238484). Fleet unchanged at **79.6% instr · 67.7% distinct · 88.86%
  fn-count** — expected: one function reverted and re-banked is net zero.
  **DISTILLED IN-SESSION (R30):** cookbook **§66** (the free re-bank test + its two strong properties),
  **§66a** (the widest write in a pipeline is the one most likely to be undeclared; a measurement-based
  containment guard is blind once anything commits), **§66b** (a metric scraped from another tool's prose
  goes NULL silently on a label change — and the same shape one level up: a digest regenerated over an
  experiment's uncommitted edits). **R21 debt cleared:** `docs/SETUP.md` had no inventory row for
  `recover_integration.py` at all; added.

- **⛔ 2026-07-24 (SESSION-17, high on Opus 5) — Task 4/wave: THE QUEUE'S WAVE PREMISE IS REFUTED BY
  MEASUREMENT — the cached high-reach drafting pool is EXHAUSTED. Nothing spent; no agents launched.**
  The SESSION-17 queue's pipeline opens `build_wave_args.py --rank live --min-live 100`. Run against
  `ov_SC07_006`: **37 candidates, 0 never-attempted.** Against `ov_SC06_018` (the overlay Task 5
  prefetched precisely for this): **163 candidates, 33 never-attempted — all reach-1, live 1–4.**
  **Fleet-wide, the decisive query** (all 139 src binaries; live = how many still hold it as an
  INCLUDE_ASM stub; 983 cached Ghidra-C files; drafts = every `.run/**/func_*.c` that is NOT the
  Ghidra-C cache): **cached & live≥100 = 141 → 111 gated in the backlog, 30 carrying a preserved draft
  (`.run/wt_uni/`, `.run/drafts_wave4/`, `.run/giants/`), and *0* genuinely never attempted.**
  The only never-attempted cached fuel anywhere is **40 functions, every one live 1–4** (overlay-unique,
  ×1). **So a 5–6 agent wave has no reach-138 fuel to draft** — the s14/s15 waves plus the Task-3 giant
  runs drained it, and the queue's "6 drafts → ~3 banks ×138" economics do not apply to what is left.
  **⚠️ TWO SELECTION BUGS IN MY OWN FILTER, both caught before spending (R14 on myself):**
  **(1)** my first exclusion set came from the backlog alone and missed `.run/giants/` — so the top three
  "fresh" targets were `func_80176734` (close=76, §27 frame-pressure lock), `func_80176218` (close=271,
  "hardest of the set") and `func_80140958` (close=116, LICM) — ~2.6M agent tokens of preserved,
  *characterized permuter-only* work that a wave would have re-bought. **(2)** my corrected scan then
  counted `.run/ghidra_c/func_*.c` as drafts, but that is the Ghidra decompile **input**, not an
  attempt — which made 100% of every pool read "already tried" (5,488 phantom attempts; 169 in one
  band). A selection tool whose candidate set is derived from the wrong directory manufactures both
  false work and false exhaustion, in the same afternoon. §66c.
  **THE GATING DEPENDENCY, unchanged from Task 5's own measurement:** fresh high-reach fuel is created
  by a **per-overlay Ghidra-C prefetch**, not found. Task 5 measured the greedy cover — ov_SC06_018 was
  #1 (now drafted out), imports 2–8 (`ov_SC03_015`, `ov_SC07_006`, `ov_SC03_124`, `ov_SC06_029`,
  `ov_SC02_011`, `ov_SC03_094`, `ov_SC04_011`) add **+0.59pp combined**, then a 632-family long tail.
  That import needs the MCP server restarted and **Drew to run `/mcp`** (R23/R29) — a human step, so it
  is a genuine gate, not something to work around.
  **WHAT IS ACTUALLY AVAILABLE, priced honestly:** (a) 40 cached reach-1..4 targets — real distinct-code
  units, ~×1 each, ≈0.006pp instr for a 6-agent batch; (b) the ~8 stranded functions §65g says need a
  transform that does not exist yet; (c) the characterized permuter-class giants — token-FREE CPU, but
  blocked on pycparser refusing the `register __asm__` pins (`.run/giants` README, §66-adjacent tooling);
  (d) the Ghidra-C prefetch (a), which restores wave economics and needs `/mcp`.

- **✅ 2026-07-24 (SESSION-17, high on Opus 5) — Task 17 / probe: THE PERMUTER *CAN* INGEST THE PINNED
  GIANT DRAFTS — the `.run/giants` README's "pycparser/permuter CANNOT ingest it as-is" is REFUTED, and
  `func_80177940` went 5 → 1 on the first bounded run.**
  **THE INGESTION CLAIM, checked against the tool instead of the note (R35).** `p16_permute.setup` has a
  **b64-pragma pin carrier** (Phase-24 T5) built for exactly `register T x __asm__("$sN")` pins and bare
  `__asm__` statements: it rewrites each into `#pragma _permuter b64literal <b64>`, which pycparser parses
  as an opaque node and decomp-permuter's own `process_pragmas` decodes back on emit. Measured on
  `func_80177940`'s draft: **6 pins → 6 carriers, 0 raw `__asm__` left**, `target.o` built, `settings.toml`
  carrying the §31 `schedule` profile. The README's warning is true of the RAW draft and false of the tool
  built for it — the third recorded wall this session that dissolved on contact with the right tool.
  **DRIFT-CHECKED FIRST (R14):** every preserved draft still reproduces its recorded closeness exactly —
  `func_80177940` 101/101 ins **5 mismatched**, `func_8014D820` 304/304 **33**, `func_80176734` 369/371
  **76**, `func_80140958` 260/260 **116**. And **`func_801670E4` (close=16) is already banked fleet-wide**
  (0 binaries still stub it) — the preserved README is stale on that one; it is not work.
  **THE RUN (900 s, -j12, §31 schedule profile): 5 → 4 → 3 → 2 → 1.** The permuter closed the exact
  4-instruction residual the drafting agent had recorded as *not* steerable ("equal-priority
  `birthing_insn_p` ties broken by INSN_LUID, not steerable from source order" — it swept all 6 assign
  orders and all pin combos by hand). A randomized search over declaration/statement order moves the LUIDs
  that a hand sweep cannot, which is precisely the division of labour §31 predicts.
  **THE LAST INSTRUCTION, and what the bytes said about it.** Residual = idx 51 only: mine `andi
  $a2,$v0,0xf` vs target `addu $a2,$v0,$zero`. The fix came from a **byte-verified sibling**:
  `func_801778A8` (banked byte-identical, same family, same nibble walk) writes `nib = uVar1;` — a plain
  copy — after the identical `(x << 16) >> 28` shift pair, with BOTH variables hard-pinned, which is what
  materializes the `addu`. Dropping my redundant `& 0xf` alone **collapsed the copy entirely** (100 vs 101
  ins, 52 mismatched — gcc reused one register), proving the target genuinely needs a distinct register
  holding a copy, not just an unmasked value. Pinning the copy target to `$a2` (`register u32 n
  __asm__("$6")`) + `n = nn;` restores **101/101 ins with 6 mismatched**, and `residual_class` now types
  the remainder **`ADDRESSING` → [permuter], profile=cse** (which register holds the intermediate + one
  store reorder) — so it is handed back to the permuter from the structurally-correct seed rather than
  hand-designed. Runs in flight: `func_80177940` (seed=6, cse, -j12) and `func_8014D820` (seed=33,
  regalloc, -j8).
  **⚠️ TOOLING BUG FIXED (throughput):** `p16_permute.run_permuter`'s cleanup was
  `pkill -f permuter/run_masked.py` — a pattern matching EVERY concurrent run, so two permuter processes
  on the 32-thread box silently killed each other the moment the first timed out, with no error anywhere.
  Scoped to the run's own scratch dir (which is in argv). This is what makes grinding several giants at
  once safe, and it is why the giant queue had only ever been run one-at-a-time.

- **✅ 2026-07-24 (SESSION-17) — `func_80177940` (101 ins, reach-138) BANKED byte-identical in
  ov_SC01_077. R22 clean-fleet 140/140. The permuter→diagnose→idiom→permuter loop closed a giant the
  drafting agent had characterized as un-steerable.**
  **The loop, in order:** (1) permuter, §31 `schedule` profile, 900 s @ -j12 → **5 → 1**, closing the
  4-instruction INSN_LUID scheduler tie by itself. (2) Read the last instruction: `andi $a2,$v0,0xf` vs
  target `addu $a2,$v0,$zero`. (3) Fixed it from a **byte-verified sibling** — `func_801778A8`'s
  `nib = uVar1;` plain copy between two hard-pinned vars — NOT by guessing: dropping the redundant mask
  alone collapsed the copy (100 vs 101 ins, 52 mismatched), which is what proved the target needs a
  distinct pinned register rather than an unmasked value. (4) `register u32 n __asm__("$6")` + `n = nn;`
  → 101/101, 6 left, retyped by `residual_class` as `ADDRESSING` → [permuter]/cse. (5) permuter again
  from that structurally-correct seed, cse profile, 1800 s → **MATCH**. Its edit was two uses of one
  temp (`new_var = a_` as a cse-opaque copy; `new_var = n * 8` splitting the expression) — the kind of
  thing a hand sweep does not find and a search does.
  **GATE (the sole arbiter, G3/P9):** `harvest_verify --chunk 1` → `verified 1 / failed 0`, final SHA
  **`d19c9580…` BYTE-IDENTICAL**; stub confirmed GONE from source by `grep INCLUDE_ASM`, never the
  report (§55b trap 4). **R22 `make clean && extract-all && check-all` → 140 passed, 0 failed of 140.**
  **⚠️ NEGATIVE, recorded so it is not re-bought:** the same pin idiom does NOT transfer to
  `func_8014D820`. Its residual is the mirror image (target holds the `lhu` results in `$v1` and keeps
  `$a0` live to fill the load-delay slot), but pinning its reusable temp `t` to `$3` made it far worse
  — **303 vs 304 ins, 285 mismatched** (`$v1` is needed elsewhere). §44's "each giant is its own class"
  holds: the *loop* transfers, the *specific pin* does not. Its permuter run improved **33 → 27** in
  1800 s @ -j8 and plateaued; the 27-seed is kept at `.run/perm_s17c/best27.c` for an ILS warm restart.

> **🛑 SESSION-17 CHECKPOINT (2026-07-24, high on Opus 5) — supersedes the SESSION-17 QUEUE block above.
> Fresh session safe here.**
> Tree clean (only R23 `db.*.gbf` churn — never staged). **R22 clean-fleet 140/140 byte-identical**
> (verified 3× this session: after the driver test, after the bank, after the propagation); 0
> NON_MATCHING (G4); dedup **1880**/0. **Drew pushes** (R6/R20). HEAD `commit:0935`.
> **Fleet: 79.7% instr · 67.7% distinct (64,875) · 88.90% fn-count** (opened at 79.6 / 67.7 / 88.86).
>
> **WHAT LANDED (all byte-gated, committed):**
> 1. **`recover_integration.py`'s SUCCESS path is VERIFIED** end-to-end by the §66 free re-bank test
>    (revert one banked fn → re-bank through the driver with `--commit --r22`). Two real defects fixed:
>    **propagation was an undeclared FLEET-tier write left ON by default** (now refused up front — needs
>    `--max-tier fleet` AND `--r22`, and refused outright after `demacroize`; both refusals
>    negative-control-tested, exit 1), and a **dead fleet-% regex** that had written `fleet None%` into
>    **50** gate commits. Also: the committed `progress.fleet.md` disagreed with committed source by 45
>    (generated over the §65g trial's since-reverted edits) — regenerated.
> 2. **`func_80177940` (101 ins) BANKED and propagated ×138** via the permuter⇄reader loop (§66d):
>    permuter 5→1, sibling idiom + `$a2` pin, permuter 6→0, whole-binary gate `d19c9580` BYTE-IDENTICAL,
>    138 overlays byte-identical after propagation. **+13,938 instructions.**
> 3. **Cookbook §66 / §66a / §66b / §66c / §66d (+§66d-1/-2)**; SETUP gains the missing
>    `recover_integration.py` inventory row (R21 debt).
>
> **THREE MEASURED FINDINGS THAT CHANGE THE PLAN:**
> - **THE QUEUED WAVE HAS NO FUEL.** Fleet-wide (139 binaries, 983 cached Ghidra-C, live recomputed from
>   `corpus.stubs`): **cached & live≥100 = 141 → 111 gated, 30 draft-only, 0 never attempted.** The only
>   never-attempted cached fuel anywhere is **40 fns at live 1–4**. High-reach wave fuel is **CREATED by a
>   per-overlay Ghidra-C prefetch, not found** — and that needs an MCP restart + **Drew running `/mcp`**
>   (R23/R29). Do not re-run `build_wave_args --min-live 100` expecting targets.
> - **The permuter INGESTS pinned giant drafts** — `p16_permute.setup`'s b64-pragma carrier handles
>   `register __asm__` pins (6 pins → 6 carriers, 0 raw `__asm__`). The `.run/giants` README's
>   "pycparser/permuter CANNOT ingest it as-is" is true of the RAW draft and false of the tool. The whole
>   preserved-giant queue is therefore permuter-addressable.
> - **`func_801670E4` (close=16) is ALREADY BANKED fleet-wide** — the preserved README is stale on it.
>
> **▶ NEXT (ranked):**
> 1. **Continue the giant queue with the §66d loop** — the proven, token-free lever. Live queue, all
>    drift-checked this session: `func_8014D820` (304 ins, **33→27**, seed at `.run/perm_s17c/best27.c`,
>    → ILS warm restart via `tools/permuter_ils.py`) · `func_80176734` (369/371, 76, frame-pressure lock)
>    · `func_80140958` (260, 116, LICM) · `func_80176218` (327, 271, hardest). Read the residual between
>    runs; `[permuter]` → back to the search, `[structural]` → read it.
> 2. **The Ghidra-C prefetch** (Task 5's greedy cover, imports 2–8 ≈ +0.59pp combined) if fresh wave fuel
>    is wanted — **needs Drew to run `/mcp`** after the server restart (R29). This is the only thing that
>    restores wave economics.
> 3. The 40 cached reach-1..4 targets (×1, moves distinct-code) and the ~8 stranded (§65g: each needs a
>    transform that does not exist yet) remain available, both lower-value.
> **⚠️ STANDING HAZARD (unchanged):** `dedup_propagate --auto-from` would re-macroize the 14
> de-macroized sites and undo them. `--check-only` first; targeted `--addr` only — as done for
> `func_80177940` this session (plan held exactly one address, so the hazard could not apply).
> **DO NOT close P29 on ROI** — burn-down floor still undetermined.

- **⛔ 2026-07-24 (SESSION-17) — `func_8014D820`: ILS PLATEAU at 25, and the §17 barrier probe is inert.
  A genuine stop, not an effort gap. Seed handed forward.**
  `permuter_ils` from the best-27 waypoint (regalloc profile, 8 cycles × 240 s @ -j10): **27 → 25 in
  cycle 1, then unchanged for seven consecutive cycles** — the warm-restart mode that drove
  `func_80148094` 72→36 has nothing left to find here.
  **The residual, read (25 of 304):** the target emits `addu $s3,$a1,$zero` FIRST and `addu $s4,$a0,$zero`
  twelfth; mine emits them in the opposite order. **Same register→param mapping, swapped BIRTH ORDER**,
  which cascades into the prologue save order (idx 1/6) and the load base registers (idx 10/11: target
  loads via `$a3`/`$s3`, mine via `$a2`/`$a1`). This is §17's register-ORDER class — the same shape the
  permuter closed unaided on `func_80177940`.
  **Probe (§17 pins+barrier): a one-line `__asm__("" : "=r"(a1) : "0"(a1))` scheduling barrier on `a1`,
  placed after the declaration block, changed NOTHING** — byte-identical residual, still 25. (First
  attempt put it before the declarations, which C89 rejects; worth knowing the barrier has to go after
  them.) That corroborates the drafting agent's note that it had already swept pins and barriers.
  **Carried:** seeds at `.run/perm_s17c/best25.c` (and `best27.c`). Next moves for it, in cost order:
  force the birth order by staging BOTH pointer params through pinned locals in the target's order
  (needs use-replacement through a 304-line body — the expensive option the permuter found for free on
  `func_80177940` via its `new_var` staging), or hand it to Fable5 as a §66d "reader's turn" case.
  **Do not spend more CPU on this seed** — 7 identical cycles is the measurement.

- **📈 2026-07-24 (SESSION-17) — `func_80140958`: ILS is WORKING — 116 → 59 in 8 cycles, still
  descending on the last one. Continuation launched (14 × 300 s from the 59-waypoint).**
  Per-cycle: **80 → 75 → 72 → 69 → 64 → 62 → 60 → 59** (cse profile, -j10). Monotone the whole way and
  it never repeated a score — the exact opposite of `func_8014D820`'s seven identical cycles.
  **THE READABLE SIGNAL, worth more than either number:** an ILS that repeats its best score is DONE
  (`func_8014D820`: 25, ×7 → stop, spend a reader/Fable5 instead); an ILS still dropping at the last
  cycle is BUDGET-LIMITED, not stuck (`func_80140958`: 59 and falling → buy more cycles, it is CPU not
  tokens). Read the per-cycle series, never just the final best — the two look identical in a summary
  line and mean opposite things. Seeds: `.run/perm_s17d/best59.c`.

- **⛔ 2026-07-24 (SESSION-17) — `func_80140958` CONVERGED at 56. §66d-3 called both decisions right.**
  Continuation from the 59-waypoint (14 × 300 s @ -j12): **58 → 57 → 56, then unchanged for ELEVEN
  cycles.** Session net **116 → 56** (a 52% cut), and the search is now genuinely done — the same
  repeat-signal that stopped `func_8014D820`. The rule paid for itself in both directions on its first
  outing: it said *continue* at 59-and-falling (bought 3 more) and *stop* at 56-×11.
  **Both remaining giants are now READER/Fable5 cases, with fresh warm seeds far better than the
  preserved drafts:** `func_80140958` 116 → **56** (`.run/permuter/func_80140958/output-56-1/source.c`),
  `func_8014D820` 33 → **25** (`.run/perm_s17c/best25.c`). That is the durable output — the next
  reader starts from a much closer draft than the ~2.6M-token Task-3 originals.

> **🛑 SESSION-17 FINAL CHECKPOINT (2026-07-24, high on Opus 5) — supersedes the SESSION-17 checkpoint
> above. Fresh session safe here.**
> Tree clean (only R23 `db.*.gbf` churn — never staged). **R22 clean-fleet 140/140** (verified 3× this
> session; last after the ×138 propagation); 0 NON_MATCHING (G4); **dedup 1880 validated / 0 failed**
> (C1 238,622/238,622). **Drew pushes** (R6/R20).
> **Fleet: 79.7% instr · 67.7% distinct (64,875) · 88.90% fn-count** (opened 79.6 / 67.7 / 88.86).
>
> **BANKED THIS SESSION:** `func_80177940` (101 ins) ×138 = **+13,938 instructions**, via the §66d
> permuter⇄reader loop.
> **TOOLS FIXED:** `recover_integration` (propagation refused unless fleet-tier + `--r22`, and outright
> after `demacroize`) · `gate_stage` (the fleet-% regex that wrote `fleet None%` into 50 commits) ·
> `p16_permute` (the global `pkill` that made concurrent runs kill each other).
> **KNOWLEDGE:** cookbook **§66, §66a, §66b, §66c, §66d (+ correction, -1, -2, -3)**; SETUP row for
> `recover_integration.py` (R21).
>
> **▶ NEXT (ranked, all with measured state):**
> 1. **`func_80176734` (369/371, close=76) — the only giant not yet given a permuter run this session.**
>    Its residual is a LENGTH gap (-2), i.e. reader-shaped by §66d, and the Task-3 note says the 2 missing
>    instructions are a `lh`+`lhu` double-load of `D_80126CE0` whose every C form triggers a frame
>    0x40→0x38 save-offset cascade (§27 frame-pressure lock). Try an ILS anyway per the §66d correction
>    (low cost, CPU only) before spending a reader.
> 2. **Reader/Fable5 on the two converged seeds** — `func_80140958` at 56 and `func_8014D820` at 25.
>    For `func_8014D820` the diagnosis is already written: the two callee-saved param copies are born in
>    the wrong ORDER (§17 register-ORDER); pins and a scheduling barrier are both byte-proven inert, so
>    the remaining idea is staging BOTH params through pinned locals in the target's order.
> 3. **The Ghidra-C prefetch** if fresh wave fuel is wanted — **needs Drew to run `/mcp`** (R23/R29).
>    Still the only thing that restores wave economics; nothing else in the queue creates fuel.
> **⚠️ STANDING HAZARD (unchanged):** `dedup_propagate --auto-from` would re-macroize the 14
> de-macroized sites. `--check-only` first; targeted `--addr` only.
> **DO NOT close P29 on ROI** — burn-down floor still undetermined.

- **⛔ 2026-07-24 (SESSION-17) — `func_8014D820`: the §17 toolkit is EXHAUSTED on it. Four moves,
  byte-proven inert or worse. Stopping; it is now a genuine Fable5 case.**
  Best remains the ILS's **25/304** (`.run/perm_s17c/best25.c`). Tried, each measured, nothing forced:
  | move | result |
  |---|---|
  | scheduling barrier on `a1` (after the decl block) | **25 — byte-identical residual, inert** |
  | scheduling barrier on `a2` (the copy-propagated pin the note names) | **25 — inert** |
  | stage BOTH params through pinned locals `$s3`/`$s4` in the target's birth order | **35** (worse) |
  | the same staging + the `a2` barrier | **34** (worse) |
  **What the staging DID show (worth keeping):** it fixed the register *assignment* — mine started
  loading via `$v1` like the target, instead of `$a0` — while shuffling the *order*. So assignment and
  birth-order are separately steerable here, and no combination tried gets both at once.
  **The named residual, unchanged:** target loads through the pinned COPIES (`lhu $v1,0($a3)` /
  `lhu $v0,0($s3)`); mine loads through the INCOMING registers, i.e. gcc copy-propagates the `$a3` pin
  and a barrier does not stop it. That is precisely the Task-3 note's diagnosis, now independently
  reproduced and with the obvious antidotes eliminated.
  **⇒ Escalation is now justified by the doctrine, not by frustration:** the class is known (§17
  register-ORDER) but every documented lever for it is byte-proven inert here, which is the definition
  of a new wall variant — the one thing Fable5 is reserved for. Give it `best25.c` + this table.

> **🛑 SESSION-17 CLOSING CHECKPOINT (2026-07-24) — supersedes ALL earlier SESSION-17 blocks. Fresh
> session safe here.**
> Tree clean (only R23 `db.*.gbf` churn). **R22 clean-fleet 140/140** (3× this session); 0 NON_MATCHING
> (G4); **dedup 1880/0** (C1 238,622/238,622). **Drew pushes** (R6/R20).
> **Fleet: 79.7% instr · 67.7% distinct (64,875) · 88.90% fn-count** (opened 79.6 / 67.7 / 88.86).
>
> **THE SESSION IN ONE LINE:** the recovery driver's success path was verified (and two defects in it
> fixed), the queued wave was byte-proven to have NO fuel, and the permuter track banked one giant ×138
> and drove **every** remaining giant to its measured search floor.
>
> **BANKED:** `func_80177940` (101 ins) ×138 = **+13,938 ins** (§66d permuter⇄reader loop).
> **THE GIANT QUEUE, ALL NOW AT THEIR PERMUTER FLOOR** (seeds TRACKED at `.run/giants/s17_*.c` — note
> `.run/giants/*.c` is allowlisted but **subdirectories are NOT**, so they live at the top level):
> | fn | ins | was | now | ILS series | verdict |
> |---|---|---|---|---|---|
> | `func_80177940` | 101 | 5 | **BANKED ×138** | — | done |
> | `func_8014D820` | 304 | 33 | **25** | 25 ×7 | converged; §17 toolkit EXHAUSTED (4 moves, all inert/worse) → Fable5 |
> | `func_80140958` | 260 | 116 | **56** | 116→59 falling, then 56 ×11 | converged → reader/Fable5 |
> | `func_80176734` | 371 | 76 | **57** | 57 ×9 | converged → reader/Fable5 |
> | `func_80176218` | 327 | 271 | 271 | not run | the hardest; untouched this session |
> Remaining value if cracked: ~**+1.3pp instr** across the four (each ×138).
>
> **▶ NEXT (ranked):**
> 1. **Fable5 on `func_8014D820`** (closest at 25/304, and the ONLY one where escalation is justified by
>    the doctrine rather than by difficulty — the class is known §17 register-ORDER but every documented
>    lever is byte-proven inert; the table of 4 dead moves is in the log above). Give it
>    `.run/giants/s17_func_8014D820_close25.c`.
> 2. **`func_80176218`** — never permuter-run; do that first (CPU, not tokens) before any reader spend.
> 3. **Reader/Fable5 on `func_80140958` (56) / `func_80176734` (57)**.
> 4. **The Ghidra-C prefetch** — still the only thing that restores WAVE economics, still **needs Drew to
>    run `/mcp`** (R23/R29). Worth ~+0.59pp across imports 2–8, i.e. less than the giants.
> **⚠️ STANDING HAZARDS:** `dedup_propagate --auto-from` would re-macroize the 14 de-macroized sites
> (`--check-only` first; targeted `--addr` only) · `p16_permute.setup` WIPES `.run/permuter/<fn>/`, so
> copy a best waypoint out before re-running (§66d-2).
> **DO NOT close P29 on ROI** — burn-down floor still undetermined.

- **✅ 2026-07-24 (SESSION-17) — `func_80176218` (the last untried giant): 271 → 110, converged. THE
  GIANT QUEUE IS NOW COMPLETE — every one is at its measured permuter floor.**
  ILS 12 × 300 s @ -j12, regalloc profile: **110 in cycle 1, then unchanged for eleven** — §66d-3's
  "one easy waypoint then done" shape. A 59% cut on the hardest of the set, for CPU only.
  Seed tracked: `.run/giants/s17_func_80176218_close110.c`.
  **Final giant ledger (all seeds at `.run/giants/s17_*.c`, all far better than the ~2.6M-token Task-3
  originals):** `func_80177940` **BANKED ×138** · `func_8014D820` 33→**25** · `func_80140958` 116→**56**
  · `func_80176734` 76→**57** · `func_80176218` 271→**110**. Remaining value ≈ **+1.3pp instr** if the
  four crack. All four are now reader/frontier cases; the search has given what it has.

- **🔎 2026-07-24 (SESSION-17) — THE DECISION SPINE WAS 9 DAYS STALE, and refreshing it changes what to
  do next (R35).** `docs/worklist.md` + `.run/fuel_manifest.json` were dated 2026-07-15 and claimed
  **223 live stubs / 870,668 ins**, ranking three ALREADY-BANKED functions in the top 7
  (`func_801325B8`, `func_8014ADE0`, `func_8012CC88` — each verified 0-live in `src/`). Regenerated:
  **160 live stubs / 583,077 ins.**
  **⚠️ The sharp edge that hid it:** `worklist.py --assert-partition` **exits at the assertion and never
  rewrites the doc** — so "regenerating" with that flag leaves the stale file in place and still exits 0.
  (Its own assertion printed "160 live stubs, 160 rows → PARTITION OK" while the doc it left behind said
  223. The two numbers were on screen at once.) Run it bare to write.
  **WHAT THE REFRESHED SPINE SAYS — the next lever is INTEGRATION, not the giants.** The top is a cluster
  of byte-correct drafts stranded on plumbing: `func_80174CB0` (123, close=0, `Buf` typedef collision) ·
  `func_8012CC88` (105, close=0 — banked in ov_SC07_006, still a stub in ov_SC01_077) · `func_80169228`
  (105, close=0) · `func_801463A0` (101, close=0) · `func_8012B4B8` (84, close=0) · `func_80156670` (83,
  close=0) · `func_80158638` (87, close=1) ≈ **83,000 ins ≈ +0.6pp**, versus the two giants above them at
  close=110 and close=91 (documented §52 walls).
  **The plan (no agents, no MCP — the drafts exist):** run `recover_integration.py` **ladder-only first**
  (no `demacroize`) so anything that banks is a NORMAL bank and propagates **×138**; only then add
  `--stages demacroize` for the remainder, whose banks are **×1 by construction** (the guard added this
  session refuses to propagate them).

- **✅ 2026-07-24 (SESSION-17) — INTEGRATION PASS off the refreshed spine: 2 banked + propagated ×138.
  R22 140/140. Fleet 79.7 → 79.9% instr.**
  Ladder-only (`--stages ""`, no demacroize, so these are NORMAL banks): **`func_8012B4B8` (84) +
  `func_80169228` (105), 2 of 5**, each confirmed gone from src; `dedup_propagate --addr` (targeted,
  `--check-only` first) → **138 overlays byte-identical, 2 new groups**. ≈ **+26,082 ins**.
  **DRIFT-CHECK EARNED ITS KEEP (R14) — 2 of 7 spine entries were wrong:** `func_8012CC88`'s "close=0"
  is for **ov_SC07_006**, and its draft is **13 off in ov_SC01_077** (the documented "backlog drafts are
  overlay-specific" caveat, now confirmed by measurement); `func_80158638` is 2 off, not 0. Never gate a
  spine row without re-measuring it.
  **THE 3 NON-BANKS, DIAGNOSED (blocker_probe, both oracles agreeing):**
  · `func_801463A0` — **real cc1 says MATCH 101 ins in its own TU**, yet the whole-binary gate rejects it:
    the §65c rtu-vs-gate divergence (rtu is relocation-masked, so a wrong call target is invisible).
    Needs a link-level look, not a codegen one.
  · `func_80156670` / `func_80174CB0` — **`local_type`, and the drafts say so themselves**: each carries
    "standalone-only scaffolding (drop when banking)" typedefs that are **TEXTUALLY IDENTICAL** to the
    canonical ones in `engine_types.h` (gcc-2.7.2 rejects a duplicate typedef even when identical).
    **Stripping the cc1-named one is NOT enough — blockers STACK:** removing `S8` exposed `B8`; removing
    `MATRIX`/`SVECTOR` exposed a `callee_decl` conflict on `func_80012ABC` (which the ladder handles but
    a bare `harvest_verify` does not). Both gate attempts left the tree BYTE-IDENTICAL (`d19c9580`), so
    the failures are clean (§65f SHA-reading rule).
  **⇒ The remedy is mechanical and named:** strip **all** shared-provided typedefs (`cdecl.
  strip_provided_typedefs` with the full provided set — note `cdecl.typedef_names` takes a **PATH**, not
  text) and re-run through the **driver's ladder**, not bare `harvest_verify`. Drafts staged at
  `.run/perm_s17i/`. Worth ≈ **+0.4pp** for the two.

> **🛑 SESSION-17 FINAL CHECKPOINT (2026-07-24) — supersedes ALL earlier SESSION-17 blocks. Fresh
> session safe here.**
> Tree clean (only R23 `db.*.gbf` churn). **R22 clean-fleet 140/140** (verified 5× this session);
> 0 NON_MATCHING (G4); dedup **1882**/0. **Drew pushes** (R6/R20).
> **Fleet: 79.9% instr · 67.7% distinct (64,875) · 88.98% fn-count** (opened 79.6 / 67.7 / 88.86).
>
> **BANKED: 3 functions, all propagated ×138** — `func_80177940` (101, §66d permuter⇄reader loop) +
> `func_8012B4B8` (84) + `func_80169228` (105) ≈ **+40,020 instructions**.
> **TOOLS FIXED:** `recover_integration` (propagation refused unless fleet-tier + `--r22`, and outright
> after `demacroize`; SUCCESS PATH now verified end-to-end) · `gate_stage` (the `fleet None%` regex,
> dead for 50 commits) · `p16_permute` (the global `pkill` that made concurrent runs kill each other).
> **KNOWLEDGE:** cookbook **§66–§66d-3**; SETUP row for `recover_integration.py` (R21).
>
> **▶ NEXT (ranked, all measured):**
> 1. **Finish the integration cluster** — the cheapest known work. `func_80156670` + `func_80174CB0`:
>    strip ALL shared-provided typedefs (`cdecl.strip_provided_typedefs`; `typedef_names` takes a PATH)
>    then run the **driver's ladder** (not bare `harvest_verify` — the residual blocker is a callee
>    conflict the ladder clears). ≈ **+0.4pp**. Drafts staged at `.run/perm_s17i/`.
> 2. **`func_801463A0`** (101, +13,938 ins) — real-cc1 MATCH in its own TU but gate-rejected: the §65c
>    divergence. A link-level diagnosis, and a NEW instance of a class we have only seen once.
> 3. **Re-run `worklist.py` (bare) before choosing anything else** — the spine was 9 days stale today and
>    ranked 3 already-banked fns in its top 7. `--assert-partition` does NOT rewrite the doc.
> 4. **The giants** are all at their permuter floor (`func_8014D820` 25 · `func_80140958` 56 ·
>    `func_80176734` 57 · `func_80176218` 110; seeds `.run/giants/s17_*.c`) — reader/frontier work,
>    ≈ +1.3pp if they crack. `func_8014D820` is the justified Fable5 case (4 §17 levers byte-proven inert).
> 5. **The Ghidra-C prefetch** — still the only thing that creates fresh WAVE fuel; MCP is currently UP
>    serving `SLUS_007.26`, and only that program is open. Ask Drew for `/mcp` if a restart is needed.
> **⚠️ STANDING HAZARDS:** `dedup_propagate --auto-from` would re-macroize the 14 de-macroized sites
> (`--check-only` first; targeted `--addr` only) · `p16_permute.setup` WIPES `.run/permuter/<fn>/` —
> copy a best waypoint out before re-running (§66d-2).
> **DO NOT close P29 on ROI** — burn-down floor still undetermined.

- **⛔ 2026-07-24 (SESSION-17) — the 2 typedef-blocked drafts do NOT bank: blockers stack THREE deep,
  and the last layer is a class the existing transforms do not reach. 0/2, tree restored exactly.**
  Did it properly this time: computed each draft's **own TU's** provided-typedef set via
  `cdecl.typedef_names(tu_path)` (217 / 215 names — note it takes a **PATH**, not text) →
  `strip_provided_typedefs` dropped **2 of 2** typedef lines from each draft → ran the **driver's
  ladder** (`--stages ""`, so `canon_resident_calls → cast_call_sites → sig_unify → gate`).
  **Result: pass 1 banked 0/2**, `src/` restored exactly (only `.run/backlog.jsonl` moved).
  **The stack, layer by layer** (cc1 reveals ONLY the first, so each fix exposes the next — §65):
  | fn | layer 1 | layer 2 | layer 3 (now) |
  |---|---|---|---|
  | `func_80156670` | `S8` dup typedef | `B8` dup typedef | **`conflicting types for D_801270A8`** — a DATA-extern conflict |
  | `func_80174CB0` | `MATRIX`/`SVECTOR` dup typedefs | — | **`conflicting types for func_80012ABC`** — a callee conflict `cast_call_sites` did NOT clear |
  **⚠️ A NEW STATIC-ORACLE BLIND SPOT, and the two-oracle design is what caught it (R34):**
  `func_80156670`'s data-extern conflict is **CC1-ONLY** — `blocker_probe`'s static oracle reports
  `none` while real cc1 fails. That is the first CC1-ONLY case measured (SESSION-16's 36-draft probe was
  36/36 agreement, 0 cc1-only). The static side needs a data-extern comparison it currently lacks; until
  it has one, a `static: none` verdict is NOT evidence that a draft is clean.
  **⇒ Honest status: these two are §65g-class** — not "run one more tool", but "needs a transform that
  does not exist yet" (a data-extern reconcile that `reconcile_tu` does not reach, and a callee
  reconcile `cast_call_sites` does not reach). **Estimated value if solved: ≈ +0.4pp.** Fully-stripped
  drafts preserved at `.run/perm_s17j/` so the next attempt starts three layers in, not from scratch.

- **🔎 2026-07-24 (SESSION-17) — `func_801463A0`: the §65c "rtu MATCH but gate rejects" case is SOLVED
  at the root, and the mechanism is sharper than the doctrine said. Not yet banked; now an ordinary
  near-miss.**
  **The hunt (all byte-evidence, no guessing):** rtu_match reproduced **MATCH (101 ins)** in the real TU
  while the whole-binary gate rejected with the baseline intact (`d19c9580`), so the divergence had to
  live where a masked diff cannot look. Compared the two symbol sets: **every one of the 9 `jal` targets
  agreed**, and of 15 data symbols the target references, the draft referenced **14** — missing exactly
  **`D_80126BE8`**.
  **THE CAUSE:** the draft declared `extern M8_801463A0 D_80126BE0_s;` / `D_80126BE8_s;` — **`_s`-suffixed
  ALIASES that no symbol table defines.** The drafter invented them because `D_80126BE0` was already
  declared at a different type (`u8 D_80126BE0[]`) in the same draft, and C cannot have both.
  **⇒ THE MECHANISM, corrected (§65c refinement):** the doctrine says rtu over-claims because it is
  *relocation-masked*. The deeper reason is that **`rtu_match` COMPILES but never LINKS** — so an extern
  that no symbol table can resolve is invisible to it *by construction*, not merely masked. Any draft
  inventing a symbol name will read MATCH in rtu and can never bank. **A cheap, general guard falls out:
  diff the draft's referenced symbol set against the target `.s`'s `%hi/%lo/jal` set before gating** —
  it is one `comm` over two greps, and it found this in seconds.
  **FIXED:** aliases repointed to the real `D_80126BE0`/`D_80126BE8`, duplicate `u8[]` decl dropped, the
  u16 store re-expressed as `(*(u16 *)&D_80126BE0)`. Symbol set now complete; the struct copy emits the
  correct inline `lwl/lwr` shape. **Residual: 100 vs 101 ins, 36 mismatched — register assignment
  (`$a3/$a1` vs the target's `$a1/$a0`) plus one folded instruction.** That is a NORMAL near-miss now,
  permuter-shaped, not a link failure. Fixed draft preserved: `.run/giants/s17_func_801463A0_symfix.c`.

- **🔎 2026-07-24 (SESSION-17) — `func_801463A0` driven from "gate rejects, cause unknown" to a
  MASKED-MATCH with ONE named blocker left. Not banked; the remaining step is a documented §H antidote.**
  Three byte-measured iterations, each falsifying the previous hypothesis:
  | variant | decls | result |
  |---|---|---|
  | original | `_s` aliases (undefined symbols) | rtu MATCH, gate reject — **the symbol set was missing `D_80126BE8`** |
  | struct-typed `&sym` | `extern M8 D_80126BE0;` | 100 vs 101 ins, 36 mismatched |
  | array-decay + cast-at-use | `extern u8 D_80126BE0[];` | 100 vs 101, 36 — **identical**, so decay was not the lever |
  | **direct-symbol scalar** | `extern u16 D_80126BE0;` | **MATCH (101 ins)** ✅ |
  **WHY the length differed (byte-read at idx 76–81):** the target **re-materializes `lui $at,%hi(sym)`
  at every scalar store** (2 ins each); the array/struct forms let gcc CSE the address into `$a3` once
  and store in 1 — so my drafts were exactly one instruction short. The direct-symbol form restores the
  per-store materialization.
  **THE REMAINING BLOCKER, named:** in the REAL TU `D_80126BE0`'s canonical decl is
  `extern u8 D_80126BE0[];` — and it lives **inside a `DEFINE_func_*` macro body** in
  `engine_core.h:19813`. So the `u16` form that MATCHES standalone gives `conflicting types for
  D_80126BE0` in the TU (real cc1, via `rtu_match --stderr-out`).
  **⇒ Two exits, and the cheap one is a trap:** `demacroize` would clear it but banks **×1** (+101 ins,
  ~0.001pp) and forfeits the ×138 — **not worth it** for this function. The right exit is the
  **§H CSE address-fold antidote** (`gcc-2.7.2-map/cse_expr.md` §H): a **balanced if/else diamond**
  whose label is barrier-preceded makes cse start a FRESH table, killing the fold with **zero asm**, so
  the canonical `u8[]` decl can stay and the bank propagates **×138 (+13,938 ins)**. That is the next
  move on it — deliberate, function-specific work, not a guess.
  Preserved: `.run/giants/s17_func_801463A0_match101.c` (the standalone-MATCH form) +
  `s17_func_801463A0_symfix.c` (the symbol-corrected form).

- **⛔ 2026-07-24 (SESSION-17) — `func_801463A0`: the §H antidotes do NOT reach this fold. Two more
  byte-recorded negatives; stopping with the blocker precisely named.**
  With the TU-canonical `u8 D_80126BE0[]` decls (the form that avoids the TU conflict), the address is
  CSE'd into a register and the function comes out one instruction short (100 vs 101, 36 mismatched).
  Tried, both **inert — byte-identical 100/36, no movement at all**:
  | antidote | source | result |
  |---|---|---|
  | balance the existing `if (iVar1 != 0)` with an empty `else {}` (§H diamond: make the join label barrier-preceded) | `cse_expr.md` §H | **100/36, unchanged** |
  | zero-instruction `__asm__ __volatile__("" ::: "memory")` between the struct copy and the scalar store | §17 barrier | **100/36, unchanged** |
  **Why they miss:** §H's diamond kills a fold *across a join*; here both uses sit in the SAME basic
  block with no join between them (the copy and the store are adjacent statements), so there is nowhere
  for a fresh cse table to start. The memory clobber constrains memory ops, not the address constant.
  **⇒ THE STATE, exactly:** a standalone **MATCH (101 ins)** exists — `.run/giants/
  s17_func_801463A0_match101.c` with direct-symbol `extern u16` decls — and it is blocked ONLY by the
  canonical `extern u8 D_80126BE0[]` living inside a `DEFINE_func_*` macro body at
  `engine_core.h:19813`. Every remaining exit is a decl-visibility move, not a codegen one:
  (a) `demacroize` → banks **×1** (+101 ins) and forfeits ×138 — measured trap, not recommended;
  (b) change the shared canonical decl → **T2 fleet-shared**, the §63 disaster class, R22-mandatory;
  (c) find a C form that keeps `u8[]` AND defeats the address CSE — the open question.
  **Value if (c) is found: +13,938 ins (×138).** Do not re-buy (a) or the two antidotes above.

- **⛔ 2026-07-24 (SESSION-17) — THE GHIDRA-C PREFETCH (#5) IS MEASURABLY NOT WORTH IT ANY MORE. Its
  fleet-wide ceiling is 0.51pp, spread across 87 overlays at ~0.01pp each. Nothing spent; no import run.**
  Measured locally (no MCP needed to decide): per overlay, stubs that are substantial (nins≥80) AND have
  **no cached Ghidra-C** AND **no surviving draft anywhere** — i.e. exactly what an import would unlock:
  | overlay | fns | ins | ceiling |
  |---|---:|---:|---|
  | ov_SC07_006 | 5 | 6,062 | 0.05pp |
  | ov_SC06_032 | 14 | 2,331 | 0.02pp |
  | ov_SC06_022 | 12 | 2,120 | 0.02pp |
  | **87 overlays, total** | — | **67,116** | **0.51pp** |
  **Why it decayed:** Task 5's greedy cover (2026-07-21) measured ov_SC06_018 at **+1.59pp** and imports
  2–8 at +0.59pp — but those families have since been DRAFTED (the s14/s15 waves + the permuter runs).
  The cover was a snapshot of a **consumable**, and it has been consumed. The remaining uncached pool is
  overlay-unique tail code, ~×1, in 87 separate overlays — each import needing a server restart and a
  human `/mcp` (R23/R29) for ~0.01pp.
  **⇒ RANKED AGAINST THE ALTERNATIVES (all measured this session):** the 4 converged giants ≈ **+1.3pp**
  (seeds ready, `.run/giants/s17_*.c`) · `func_801463A0` ≈ **+0.11pp** (one named open question) · the
  ENTIRE prefetch program ≈ **+0.51pp** at ~87 human-gated imports. **The prefetch is now the WORST
  lever on the board, not the wave-unblocker the roadmap treats it as.**
  **⚠️ A CORRECTION I OWE MY OWN EARLIER MEASUREMENT (R14):** a 3-line `ls` of two draft dirs made
  `func_8014032C` (live=137, cached) look never-attempted and therefore look like high-reach fresh fuel.
  The full glob found **six** drafts for it (`.run/drafts_wave3*`, `.run/wt_uni`, `.run/w3_*`). The
  fleet-wide figure — **0 cached + never-drafted targets at live≥100** — is the one that survives. Same
  failure mode as §66c, committed by the same person twice in one session: *check every draft directory,
  and prefer the glob over a hand-listed pair.*

> **🛑 SESSION-17 CLOSING CHECKPOINT (2026-07-24, high on Opus 5) — supersedes ALL earlier SESSION-17
> blocks. Fresh session safe here. NEXT SESSION STARTS ON THE GIANTS (Drew, at close).**
> Tree clean (only R23 `db.*.gbf` churn — never staged). **R22 clean-fleet 140/140** (verified 5× this
> session); 0 NON_MATCHING (G4); **dedup 1882 / 0 failed**. **Drew pushes** (R6/R20). HEAD `commit:0953`.
> **Fleet: 79.9% instr · 67.7% distinct (64,875) · 88.98% fn-count** (opened 79.6 / 67.7 / 88.86).
>
> **BANKED: 3 fns, all propagated ×138 ≈ +40,020 ins** — `func_80177940` (101, §66d loop) ·
> `func_8012B4B8` (84) · `func_80169228` (105).
> **TOOLS FIXED:** `recover_integration` (propagation refused unless fleet-tier + `--r22`, refused
> outright after `demacroize`; **SUCCESS PATH VERIFIED end-to-end** by the §66 free re-bank test) ·
> `gate_stage` (the fleet-% regex dead for 50 commits) · `p16_permute` (global `pkill` killing
> concurrent runs). **KNOWLEDGE:** cookbook **§66–§66d-3**; SETUP row for `recover_integration.py`.
>
> ## ▶ START HERE: THE GIANTS (everything needed is below — no re-discovery)
> All four are at their **measured permuter floor** (ILS converged; see §66d-3 for the read-the-series
> rule). Seeds are TRACKED at `.run/giants/s17_*.c` (note: `.run/giants/*.c` is allowlisted but
> **subdirectories are NOT**). **Drew: no Fable5 for now** — this is reader work + permuter cleanup.
> | fn | ins | seed | ILS series | residual, as diagnosed |
> |---|---:|---|---|---|
> | `func_8014D820` | 304 | `s17_func_8014D820_close25.c` | 27→25, then 25 ×7 | **the closest.** Target births `$s3←a1` FIRST, `$s4←a0` twelfth; mine the reverse. Same register→param MAPPING, swapped BIRTH ORDER → cascades into prologue save order (idx 1/6) + load bases (idx 10/11: target `$a3`/`$s3`, mine `$a2`/`$a1`). §17 register-ORDER class. |
> | `func_80140958` | 260 | `s17_func_80140958_close56.c` | 116→59 falling, then 56 ×11 | LICM hoists inner-loop consts to the outer preheader, stealing the two callee regs the target gives const-3 (`$fp`) and `&D_801879BE` (`$s6`). |
> | `func_80176734` | 371 | `s17_func_80176734_close57.c` | 76→57 in cycle 1, then ×9 | `D_80126CE0` needs BOTH `lh` (test) + `lhu` (value); every C form forcing the 2nd load relieves pressure → frame 0x40→0x38 save-offset cascade (§27 frame-pressure lock). |
> | `func_80176218` | 327 | `s17_func_80176218_close110.c` | 271→110 in cycle 1, then ×11 | ne-boolean coalescing copy + blk-1 delay-slot steal + blk-2 cross-jumped into the adjust tail. |
> **`func_8014D820` — DO NOT RE-BUY THESE (each byte-measured this session, all inert or worse):**
> `__asm__("" : "=r"(a1) : "0"(a1))` barrier after the decl block → **25, unchanged** · the same barrier
> on `a2` (the copy-propagated pin the note names) → **25, unchanged** · staging BOTH params through
> pinned locals `$s3`/`$s4` in the target's birth order → **35** (worse) · staging + the `a2` barrier →
> **34**. *(A barrier placed BEFORE the declaration block is a C89 error — it must go after.)*
> **The one useful sub-finding:** staging **fixed the register ASSIGNMENT** (loads via `$v1` like the
> target) while shuffling the ORDER — so assignment and birth-order are **separately steerable**, and no
> combination tried gets both at once. That is the crack to aim at.
> **THE UNFINISHED PROBE (I was mid-check when the session closed):** birth order may follow **first-use
> order** (§31 regalloc RC-1/RC-2/RC-3: declaration/use order drives `allocno_compare` density). Measured
> so far in the body: `a2` first used at body-line 27, `a1` at 28 — **`a0`'s first use was NOT located
> yet.** If `a0` is used before `a1`, reordering the first touches (semantically neutral) is an untried,
> cheap lever. If `a0` is used AFTER `a1`, then use-order is already target-shaped and is NOT the lever —
> which itself would be worth knowing. **Finish that check first; it is one grep.**
> **The §66d loop is the method:** structural change by reading → hand back to `permuter_ils` to clean
> up the fallout. That is exactly how `func_80177940` banked this session (5→1 search, sibling idiom by
> reading, 6→0 search).
>
> ## Also carried (lower value, all measured)
> - **`func_801463A0`** (101 ins, **+13,938 ins**): a standalone **MATCH exists** —
>   `s17_func_801463A0_match101.c`, direct-symbol `extern u16` decls — blocked ONLY by the canonical
>   `extern u8 D_80126BE0[]` living inside a `DEFINE_func_*` macro body at `engine_core.h:19813`.
>   Exits: (a) `demacroize` = **×1 trap** (+101 ins, forfeits ×138); (b) change the shared decl = **T2 /
>   §63 disaster class**; (c) a C form keeping `u8[]` that defeats the address CSE = **the open question**.
>   Both §H antidotes (balanced-if diamond, zero-ins memory barrier) are **byte-proven inert** — §H kills
>   a fold ACROSS A JOIN and here both uses are adjacent statements in one basic block.
> - **The Ghidra-C prefetch is SPENT** — 0.51pp ceiling across 87 overlays (~0.01pp each, each needing a
>   human `/mcp`). Task 5's +1.59pp cover was a snapshot of a consumable and has been consumed. It is now
>   the WORST lever on the board; do not plan P30 around it without re-measuring.
> - `func_80156670` + `func_80174CB0`: **§65g-class**, blockers stack 3 deep (dup typedefs → a DATA-extern
>   conflict / a callee conflict the ladder does not clear). Fully-stripped drafts at `.run/perm_s17j/`.
> - **NEW static-oracle blind spot (R34):** `blocker_probe`'s static side missed a data-extern conflict
>   that real cc1 caught — the **first CC1-ONLY case ever measured**. `static: none` is NOT proof a draft
>   is clean. Worth a data-extern comparison in the static oracle.
> - **A cheap guard worth building:** diff a draft's referenced symbol set against the target `.s`'s
>   `%hi/%lo/jal` set BEFORE gating. One `comm` over two greps; it found the `func_801463A0` invented-alias
>   bug in seconds, and `rtu_match` is blind to that whole class **because it compiles without linking**.
>
> **⚠️ STANDING HAZARDS:** `dedup_propagate --auto-from` would re-macroize the 14 de-macroized sites
> (`--check-only` first; targeted `--addr` only) · `p16_permute.setup` **WIPES** `.run/permuter/<fn>/` —
> copy the best waypoint out before re-running (§66d-2) · `worklist.py --assert-partition` does NOT
> rewrite the doc (run it bare) · when checking "was this attempted?", **glob every draft dir** — a
> hand-listed pair produced a false "fresh fuel" finding twice this session (§66c).
> **DO NOT close P29 on ROI** — burn-down floor still undetermined.

- **🔎 2026-07-24 (SESSION-18, Opus 5 @ High) — `func_8014D820` driven 25 → 16 by READING, with the
  prologue now byte-exact and the instruction count landed on 304. The SESSION-17 diagnosis was right
  about the symptom and wrong about the class: this is instruction PLACEMENT, not register ORDER.**
  Distilled as **cookbook §67** (written in-session, R30).
  **First, the unfinished probe is ANSWERED — and it is a negative that retires the lever:** `a0`'s
  first use is **body-line 41** (`ent = *((Ent **)(a0 + 0x170))`), `a1`'s is 28, `a2`'s is 5. So use
  order **already matched** the target's birth order (a1 before a0) while the birth order was inverted
  ⇒ the §31 RC-1/RC-2/RC-3 *first-use-order* hypothesis is **REFUTED for this class**. Declaration order
  is inert too (moving `ent`/`p` to the end of the decl block: byte-identical). **Do not re-buy either.**
  **The root cause, byte-read:** gcc schedules the arg→pseudo entry copies as ordinary in-block insns;
  an unconstrained copy is hoisted to the earliest slot. Mine raced `move $s4,$a0` to idx 2, which
  **freed `$a0` to become the early load temp** (target uses `$v1`) and left the target's idx-12
  load-delay slot unfilled (`nop`) — so the "wrong temp register", the "mirrored `sw $sN`/`move $sN`
  prologue", and the +1 instruction were **one defect wearing three costumes**, not three residuals.
  **The fix (§67):** an unpinned launder `__asm__ __volatile__("" : "=r"(a0v) : "0"(a0));` placed at the
  statement where the target's copy sits, all later `a0` uses rewritten to `a0v`. Zero instructions.
  Prerequisite: collapse the redundant `new_var2 = a1;` alias first (the two-pseudo split was making
  gcc serve the first use from the incoming arg reg and defer the copy — that alone fixed idx 11).
  | variant | result |
  |---|---|
  | s17 seed (baseline) | 304/304, **25** |
  | + collapse `new_var2` alias | 304/304, 27 (idx 11 fixed; a0/a2 copies then swapped) |
  | + launder the `a2` pin (`"0"(a2x)`) so CSE can't serve `$6` | 305/304, prologue exact from idx 11 |
  | + `t` pinned `$3` | 305/304, temps now `$v1` — **structurally identical, off by the one copy** |
  | **+ a0 launder before `t = a2[2];`** | **304/304, 16** ✅ (`s18_func_8014D820_close16.c`) |
  | − the `t` pin (now redundant) | 304/304, **16** — same bytes, simpler C |
  **Placement is the knob and it is not linear** (target slot 12): before `dx = t - u;` → slot 10
  (305 ins); before `t = a2[2]` / `u = a1[2]` / `dz = t - u` → **slot 12** ✅; before the `if` → slot 16
  (18 mismatched). A 3-statement plateau, so sweep anchors rather than aiming.
  **MEASURED NEGATIVES — do not re-buy:** pinning the laundered var to `$s4` (`__asm__("$20")`) →
  gcc pre-stages via `$t0`, 305 ins · pinning the reused temp `t` to `$3` on the *old* base → 287
  mismatched / 303 ins · an artificial `"r"(t)` input dependency to force the slot → **inert**, gcc
  still hoisted above the load · laundering *after* the `beqz` (SESSION-18 exp5/exp6) → forces a second
  materialization, 305 ins · dropping the `a2` pin entirely → 29 · reordering the pos/desc block
  wholesale, or sinking `z0 = ent->z` → +1 ins (the `ent->z` load position is load-bearing).
  **Residual 16, in 3 clusters:** idx 21/22 scratch `$v1` vs `$a0` (2) · idx 84–98 the `desc.y` /
  `currentLocationId` schedule (11) · idx 271/272 a load-order swap (2). All regalloc/schedule class ⇒
  handed to `permuter_ils` per the §66d loop (running: 10 cycles × 180 s, `-j 14`, from the close=16
  seed; old close=25 waypoints preserved at `.run/permuter_bak_func_8014D820_s17_close25/` per §66d-2).
  **Also measured, for the other giants:** `func_80140958` 260/260 **54** · `func_80176734` 371/371
  **56** · `func_80176218` **328 vs 327** — the +1 is NOT §67 (its prologue is fine); mine burns an extra
  callee-saved (`sw $s6`) to **hoist** a global address (`lui/addiu $s6`) the target rematerializes ⇒
  the hoist-vs-remat / array-decay lever (§17), a different antidote.

- **🔎 2026-07-24 (SESSION-18) — `func_8014D820` 16 → 14 → 12 via WEIGHT-VARIED permuter passes; the
  residual is now ONE contiguous scheduling cluster. Not banked (G3).** The pattern is the useful part:
  each ILS pass with a *different* `--klass` profile drops ~2 and then converges flat, so the weight
  profile — not run length — is the variable that moves a converged seed.
  | pass | seed | series | result | what it actually changed |
  |---|---|---|---|---|
  | `--klass REGALLOC` 10×180 s | close=16 | 14, then ×9 flat | **14** | hoisted `desc.y + 0x10` into a temp → cleared idx 271/272 |
  | `--klass SCHEDULE` 8×240 s | close=14 | 12, then ×7 flat | **12** | hoisted `(s16) dx` into a temp → cleared idx 21/22 (the `$v1` vs `$a0` scratch) |
  | `--klass cse` 10×240 s | close=12 | *running* | — | targeting the `currentLocationId` address placement |
  Both permuter edits are trivially semantics-preserving (pure temp hoists), verified by reading the
  diff — not the store-rewriting kind §66d warns about. Seeds tracked: `s18_func_8014D820_close{16,14,12}.c`.
  **The residual 12 is entirely idx 84–98** — the `pos`/`desc` block schedule. Mine hoists the
  `ent->z` load to idx 87; the target issues it at 91 (and orders `pos.y`/`desc.y` before it).
  **SOURCE REORDERING THAT BLOCK IS A DEAD END — four attempts, two bases, all inert or worse:**
  transcribing the target's *exact* instruction order into source order (idx 82–101 read off the `.s`)
  → **305 ins** · sinking `z0 = ent->z` to its use → **305 ins, twice, on two different bases** ·
  swapping the `y0`/`z0` load order → inert (12) · storing `desc.x` last → inert (16). **The
  `z0 = ent->z` position is load-bearing; do not re-buy any of these.** The lesson generalizes: *the
  target's instruction order is NOT reachable by making source order match asm order* — the scheduler
  produced it from a different source shape, so this block is search-shaped, not reader-shaped.
  **Pre-gate de-risked:** `symcheck` (NEW, below) → **12/12 symbols agree**, so a match here will link
  cleanly; the §65c "rtu MATCH but gate rejects" class is ruled out for this function in advance.

- **🔧 2026-07-24 (SESSION-18) — built `tools/symcheck.py`, the pre-gate SYMBOL-SET guard SESSION-17
  left as a TODO. Negative-control proven.** Diffs the symbols a draft's object references (reloc
  records) against the target `.s`'s `%hi`/`%lo`/`jal` set; reports MISSING (the invented-alias
  signature) and INVENTED separately. **It fills a real structural hole:** `match_one`/`masked_diff`
  compare relocation-MASKED words (object-vs-`.s` is symbol-agnostic *by construction*) and `rtu_match`
  **compiles without linking** — so both are blind to a draft that invents an extern no symbol table
  defines, which is exactly the SESSION-17 `func_801463A0` `_s`-alias trap (rtu MATCH, gate always
  rejects). **Negative control:** rename one data extern to an invented alias → `match_one` reports the
  **same 14 mismatched as the correct draft**, `symcheck` exits 1 naming both symbols. Run it after any
  decl-rewriting transform (`sig_unify`, `canon_resident_calls`, `cast_call_sites`,
  `canon_sig_reconcile`) and before paying for a gate. Cookbook **§67a**; SETUP inventory row (R21).
  A necessary condition, NOT a match oracle — finish on the byte-gate (G3/P9).

- **🧭 2026-07-24 (SESSION-18) — BANKING PATH FOR `func_8014D820` PRE-CLEARED (blocker_probe run BEFORE
  the match, not after).** Three blocker classes, all known, none novel — so when the search lands a 0
  the bank is plumbing, not discovery:
  | class | n | tier | disposition |
  |---|---|---|---|
  | `local_type` (typedef redefs) | 32 | T0 | automatic — `harvest_verify` strips per-TU via `cdecl` (P27 T4) |
  | `data_decl` (`D_801152AC` hdr `s16` vs draft `u16`, +2) | 3 | T0 | `reconcile_decls` |
  | `self_decl_hdr` | 1 | **T1→T2 in practice** | **`DEFINE_func_8014D790`'s body declares `func_8014D820` as `void (s32, void*, void*)`; the byte-true def is `s32 (s32, u16*, u16*)`** — the §30#2 **def-side return-type macro-widen**, the same blocker all three Phase-23 giants hit |
  **⚠️ The macro-widen edits `src/shared/engine_core.h` ⇒ FLEET-SHARED (T2): R22 is MANDATORY, the
  per-binary gate is necessary-not-sufficient (§61/§63, and the SESSION-14 incident where a per-binary
  BYTE-IDENTICAL was RIGHT about its binary while 137 others were broken).** Widening `void`→`s32` is
  byte-neutral only IF every caller discards the return — verify, don't assume.
  `symcheck` already cleared the link-level class (12/12). So the only open question on this function
  remains the 12-instruction schedule.

- **🔎 2026-07-24 (SESSION-18) — `func_8014D820` 12 → 10 → **9**. The permuter⇄reader alternation
  (§66d) is paying on every turn.** `--klass cse` took 12 → 10 (flat ×9 after cycle 1, the same shape as
  the other two profiles). Its edits are again pure dead-variable temp hoists + comparison-operand swaps
  — semantics-preserving, verified by reading the diff.
  **Then a READER fix took 10 → 9 for one compile:** the CSE pass had swapped `if (p == ent)` →
  `if (ent == p)`, which *gained* elsewhere but introduced a local regression at idx 110
  (`beq $s2,$s1` vs the target's `beq $s1,$s2`). Reverting just that operand order kept every gain and
  removed the regression. **This is the §66d loop's whole point: a random search cannot see that one of
  its own edits is locally wrong; a reader can, in seconds.** Check the diff for operand-order
  regressions after every permuter pass — they are free points.
  **Residual 9, all still idx 84–98** (the `pos`/`desc` block): mine issues `z0 = ent->z` at 87 and
  stores `desc.x` at 90 / `pos.y` at 98; the target issues `z0` at 91 and stores `pos.y` at 89 /
  `desc.x` at 98. **Source-shape attempts on this block now stand at EIGHT, all inert or worse** (add:
  splitting the `desc.y` chain into a temp — inert ×2; the uniform per-axis `pos.N = (vN = ent->N)`
  idiom — **305 ins**; matching the target's store order `desc.x → pos.z → desc.z` — inert). Treat this
  block as search-only; do not spend more reader time on statement order here.
  `symcheck` re-run on every waypoint: **12/12 symbols agree** throughout.

> **🛑 SESSION-18 CHECKPOINT (2026-07-24, Opus 5 @ High — a deliberate calibration vs the Opus-4.8/Max
> giant sessions). Fresh session safe here. Two searches were IN FLIGHT at write time — read their logs
> before trusting the numbers below.**
> Tree clean apart from R23 `db.*.gbf` churn (never staged). **No bank this session ⇒ fleet unchanged:
> 79.9% instr · 67.7% distinct · 88.98% fn-count; 140/140; 0 NON_MATCHING; dedup 1882/0.** **Drew pushes**
> (R6/R20). Nothing was gated, so R22 was not re-run — the tree is exactly HEAD plus docs/seeds.
>
> ## `func_8014D820`: 25 → 9 mismatched (304/304 ins, prologue byte-exact). NOT banked (G3).
> | step | score | how |
> |---|---|---|
> | s17 seed | 25 | — |
> | reading (§67 launder + alias collapse) | **16** | ~15 cheap compile-and-measure cycles |
> | ILS `--klass REGALLOC` | 14 | temp hoist, cleared idx 271/272 |
> | ILS `--klass SCHEDULE` | 12 | temp hoist, cleared idx 21/22 |
> | ILS `--klass cse` | 10 | temp hoists + operand swaps |
> | **reader fix of a permuter regression** | **9** | reverted `ent == p` → `p == ent` (idx 110) |
> Seeds tracked: `.run/giants/s18_func_8014D820_close{16,14,12,10,9}.c`. The close=9 seed keeps only the
> `a2` `$7` pin (load-bearing: dropping it → 29); the inherited `t` and `u` pins were both proven
> redundant and removed.
>
> ## THE TWO METHOD FINDINGS (both reusable, both cookbook'd)
> 1. **§67 — the arg-copy PLACEMENT lever.** An unpinned launder
>    `__asm__ __volatile__("" : "=r"(pv) : "0"(p));` at the statement where the target's copy lands.
>    Zero instructions. It dissolved what looked like three separate residuals (wrong temp register,
>    mirrored prologue saves, +1 ins with an unfilled load-delay `nop`) — they were ONE defect.
>    **Signature to look for: a draft one instruction OVER with a `nop` the target fills.**
> 2. **Weight-profile diversity — worth a cheap pass, NOT expected yield (corrected later in-session).**
>    On `func_8014D820` each unused `--klass` profile dropped ~2 then went flat (16→14→12→10), so
>    **"ILS converged" can mean converged FOR THAT PROFILE, not a floor** — SESSION-17 used §66d-3's
>    read-the-series rule to call all four giants floored, and for this one that was wrong.
>    **BUT the same experiment on `func_80140958` returned ZERO** (base 56, fresh `cse` pass, 8 cycles,
>    no change) — 3-for-3 on one giant, 0-for-1 on the next. Treat it as a ~0-token lottery ticket to
>    spend before declaring a floor; **do NOT project giant yields from the func_8014D820 curve.**
>    A *repeated* profile yields nothing at all (two round-2 runs, both flat). See §66d-4.
>
> ## ⛔ DEAD END — do not spend more reader time here
> The residual 9 is entirely **idx 84–98**, the `pos`/`desc` block schedule (mine issues `z0 = ent->z`
> at 87 and stores `desc.x` at 90 / `pos.y` at 98; target issues `z0` at 91, stores `pos.y` at 89 /
> `desc.x` at 98). **NINE source-shape attempts, two bases, all inert or worse:** target-order
> transcription (305) · sink `z0` (305, ×2) · swap `y0`/`z0` load order (inert) · `desc.x` stored last
> (inert) · target store order `desc.x→pos.z→desc.z` (inert) · split the `desc.y` chain into a temp
> (inert ×2) · uniform per-axis `pos.N = (vN = ent->N)` idiom (305) · **memory-clobber barrier after the
> `desc.y` store (19, over-constrains)**. Lesson: *the target's instruction order is NOT reachable by
> making source order match asm order.* Search-only from here.
>
> ## BANKING IS PRE-CLEARED (done before the match, not after)
> `symcheck` **12/12 symbols agree** on every waypoint ⇒ the §65c link class is ruled out.
> `blocker_probe`: 32 `local_type` (T0, `harvest_verify` strips them) · 3 `data_decl` (T0,
> `reconcile_decls`) · **1 `self_decl_hdr`** — `DEFINE_func_8014D790`'s body declares `func_8014D820`
> as `void (s32, void*, void*)` vs the byte-true `s32 (s32, u16*, u16*)` ⇒ the §30#2 **macro-widen**,
> which edits `src/shared/engine_core.h` ⇒ **FLEET-SHARED (T2), R22 MANDATORY** (§61/§63).
>
> ## ▶ NEXT SESSION STARTS HERE
> 1. **Read the two in-flight logs first** — `.run/giants/s18_d820_ils_rr2.log` (REGALLOC round 2 from
>    close=9; tests the round-robin hypothesis) and `.run/giants/s18_d140958_ils_cse.log` (giant #2,
>    `func_80140958`, CSE profile — its prior profile was regalloc, series 116→59→56). Waypoints land in
>    `.run/permuter/<fn>/output-<score>-*/source.c`. **If round 2 yields, keep round-robining profiles —
>    that is the cheapest lever on the board.**
> 2. **After every permuter pass, diff for operand-order regressions** (`a == b` vs `b == a`, `x >= k`
>    vs `k <= x`). One such revert was worth a full point this session, for one compile.
> 3. **The other giants:** `func_80176734` 371/371 **56** (frame-pressure lock, §27) · `func_80176218`
>    **328 vs 327** — its +1 is NOT §67; it burns an extra callee-saved (`sw $s6`) to hoist
>    `&D_8018A23C` (declared `extern u8 *D_8018A23C[]`) which the target rematerializes ⇒ the §17
>    array-decay / direct-symbol-scalar lever, per the SESSION-17 `func_801463A0` pair.
> **⚠️ HAZARDS (unchanged):** `p16_permute.setup` WIPES `.run/permuter/<fn>/` — waypoints for this
> session are preserved at `.run/permuter_bak_func_8014D820_s18_close{12,10}` and
> `..._s17_close25` · `dedup_propagate --auto-from` would re-macroize the 14 de-macroized sites
> (`--check-only` first, targeted `--addr` only) · concurrent ILS runs on *different* functions are
> safe (the `pkill` at `p16_permute.py:240` is scoped to the per-function dir — verified, not assumed).
> **DO NOT close P29 on ROI** — burn-down floor still undetermined.

- **⛔ 2026-07-24 (SESSION-18) — the idx 84–98 block: ELEVEN source-shape attempts, and the negative is
  now a positive finding.** Added since the checkpoint: eliminating the `z0` variable so CSE places the
  load at first use → **305** · transcribing the target's exact *interleave* (`addu` | `lhu z0` |
  `addiu +8` | `sh desc.y` | `addu tz`, splitting the `desc.y` chain with the load in the gap) → **305**.
  **THE PATTERN, across five independent arrangements: any source change that relocates
  `z0 = ent->z` LATER costs exactly +1 instruction, every time — while the target issues it late at
  ZERO cost.** ⇒ The target's late placement is not expressible in source: it is produced by the
  SCHEDULER from a source in which the load is EARLY (which is what my draft already has). So the load
  must STAY early in source and only the search can move it. That closes the question — this block is
  search-only, and further reader time on statement order here is provably wasted.
- **📏 2026-07-24 (SESSION-18) — the profile round-robin, MEASURED both ways.** Different profile from a
  converged seed ⇒ ~2 each (REGALLOC 16→14, SCHEDULE 14→12, cse 12→10). **Repeated profile ⇒ nothing:**
  REGALLOC round-2, warm-started from close=9 (a seed it had never seen), was **flat all 10 cycles, 0
  gain**. The lever is **profile diversity, not seed novelty** — budget three passes per giant, then
  stop. Cookbook **§66d-4** (amends §66d-3's "measured permuter floor", which SESSION-17 applied to all
  four giants and which is now shown to be profile-relative, not absolute).

- **🔬 2026-07-24 (SESSION-18) — `residual_class`'s `structural` bucket says "permuter CPU here is
  waste". MEASURED FALSE for schedule permutations — a project-wide mis-route.** `func_8014D820` was
  classed `OPCODE-MIXED [structural]`, later `WIDTH [structural] sig=WIDTH/lhu!=sh`, at **every**
  waypoint — while the permuter moved it **16 → 14 → 12 → 10** across three profiles. Six points inside
  a bucket documented as "don't run the permuter", *and* the guidance it does give ("read it") was the
  part that failed (11 attempts).
  **Why it is fooled:** the classifier reasons position-by-position, and a pure schedule PERMUTATION
  changes what lands at every index in the window — so an all-present-but-reordered block reads as
  "different operations, no single family" or as a width flip, because index *i* now holds a `sh` where
  the target holds an `lhu`. Its `SHIFT-DRIFT` rule only catches the case where ONE shift point
  re-aligns the tail; a permutation with matching endpoints re-aligns nowhere.
  **Corrected routing (cookbook §66d-5):** `structural` ⇒ read FIRST, but it is **not a permuter veto**
  — if reading fails 2–3× AND the instruction COUNTS match AND the same multiset of ops appears
  reordered, run the three profiles. **Count equality is the tell:** a genuine shape change usually
  changes the count; a permutation never does.
  **FOLLOW-UP, sized honestly (P30 fuel, NOT done):** the obvious re-check — sweep the backlog for
  OPCODE-MIXED/WIDTH entries with equal instruction counts — **is not cheaply available**: all 1,736
  `.run/backlog.jsonl` rows carry `residual: null` (and 1,549 carry no `klass` either), so the class
  would have to be **recomputed per entry by compiling each preserved `best_draft`**. That is a real,
  bounded batch job (~1 compile/entry, no agent tokens) and a good P30 opener, but it is not a grep.
  Worth doing precisely because the mis-route has been silently steering this class away from the only
  tool that moves it for the whole project.

- **🔎 2026-07-24 (SESSION-18) — `func_80176734` (371/371, **56**): SESSION-17's diagnosis CONFIRMED
  against the bytes, with the exact C idiom named.** At idx 270–275 the target loads `D_80126CE0`
  **twice from the same address at two widths** — `lh $v0, %lo(D_80126CE0)` (signed, feeding the
  `beqz $v0` test) *and* `lhu $a1, %lo(D_80126CE0)` (unsigned, feeding the value stored via
  `sb $v1, 0x4B($s1)`). Mine loads it once (`lh` → `$v1`) and reuses it (`move a0,v1`,
  `andi v1,a0,0xff`), which is why the whole window shifts.
  **The idiom to force it:** read through two differently-typed lvalues — plain `D_80126CE0` (declared
  `u16`) for the `lhu`, and `*(s16 *) &D_80126CE0` for the `lh`. A cast of a single `u16` lvalue will
  NOT do it (that compiles to `lhu` + `sll/sra`); it must be two distinct memory reads.
  **The known catch (SESSION-17, unverified this session):** forcing the second load relieves register
  pressure and cascades the frame 0x40→0x38 into every save offset (§27 frame-pressure lock) — so
  expect the fix to trade 56 mismatches for a different set until the frame is re-locked. Untouched
  this session; this is the next giant to read after `func_8014D820`.

- **📐 2026-07-24 (SESSION-18) — `func_8014D820` close=9 is a **MEASURED FLOOR**, by the corrected
  §66d-4 rule, not a guess.** All THREE weight profiles now come back flat **from the same close=9
  seed**: `regalloc` (10 cycles, 0 gain) · `schedule` (8 cycles, 0) · `cse` (8 cycles, 0). Combined with
  reading being exhausted (11 source-shape attempts, and the +1-instruction law that proves the
  placement is scheduler-produced), **both cheap tiers are genuinely spent on this function** — which is
  a very different claim from SESSION-17's "at its measured permuter floor" at close=25, because that
  one rested on a single profile.
  **Backlog updated** (`tools/backlog.py log`): `func_8014D820`, reach 138, nins 304, closeness **9**
  (was 25), class `schedule`, best draft `.run/giants/s18_func_8014D820_close9.c`, with the full
  diagnosis + the pre-cleared banking path recorded in `where_stuck`.
  **⇒ THIS IS NOW THE JUSTIFIED FABLE5 CASE, and it is Drew's call** (he set "no Fable5 for now" at the
  SESSION-17 close and asked this session to "see if we need Fable5 later"). The doctrine's condition is
  met exactly: cheap-Opus reading stalled, the permuter stalled across all profiles, and the residual is
  a *single named mechanism* (a 9-instruction schedule permutation in one 15-instruction window) rather
  than a vague wall — the shape Fable5 has historically cracked (§45 flagship, §52). Value if solved:
  **×138**. Cost control: one isolated agent on this one function, per the parallel-isolated doctrine.

- **⛔ 2026-07-24 (SESSION-18) — `func_80176734`: the dual-width-load idiom is NECESSARY BUT NOT
  SUFFICIENT. Two byte-recorded negatives; do not re-buy either in isolation.** Forcing the second read
  of `D_80126CE0` through a distinct lvalue works — both directions produce the two loads — but each
  lands at **373 ins vs the target's 371 (+2) and 103 mismatched**, worse than the 371/371 **56**
  baseline:
  | variant | shape | result |
  |---|---|---|
  | keep `extern s16` (→ `lh` test), value via `*(u16 *) &D_80126CE0` | two loads | 373/371, 103 |
  | declare `extern u16` (→ `lhu` value), test via `*(s16 *) &D_80126CE0` | two loads | 373/371, 103 |
  **+2, not +1** — so the extra cost is the second load *plus* fallout, exactly the §27 frame-pressure
  cascade SESSION-17 predicted (relieving the pressure re-sizes the frame 0x40→0x38 and moves every
  save offset). ⇒ The idiom must be applied **together with** whatever re-locks the frame; applied alone
  it is a regression. Next reader session on this function should start from the frame, not the load.

- **🔎 2026-07-24 (SESSION-18) — `func_80176218`: the hoist is DIAGNOSED AND REMOVED; the residual
  flipped from +1 to −2 instructions. A real lead, not a wall.** The SESSION-17 label was
  "hoist-vs-remat"; the bytes say it is the **indexed-global idiom** and my draft simply had the wrong C.
  **Target** (idx 324–326): `lbu $v0,0x4A($s1)` · `sll $v0,$v0,2` · `lui $at,%hi(D_8018A23C)` ·
  `addu $at,$at,$v0` · `lw $a0,%lo(D_8018A23C)($at)` — the address is materialized **inline through
  `$at` with the index folded in**, never kept in a register.
  **My draft** declared `u8 **new_var;`, assigned `new_var = D_8018A23C;` at line 96, and indexed it at
  line 277 — that early intermediate is what forced `&D_8018A23C` into a callee-saved `$s6` (plus its
  `sw`/restore), i.e. **exactly the §67 two-pseudo law in a different costume: an intermediate pointer
  variable makes gcc materialize early.**
  **Result of deleting `new_var` and writing `D_8018A23C[idx]` at the use site:** the hoist, its save and
  its restore all disappear — **328 ins (+1) → 325 ins (−2)** against the target's 327. So the idiom is
  RIGHT and now overshoots: two instructions the target has are missing. (Raw mismatch count reads worse,
  271 vs 105, but that is LENGTH-DRIFT misalignment, not divergence — cf. the §67 EXP4 lesson that a
  length-shifted diff's *count* is meaningless.)
  Draft preserved: `.run/giants/s18_func_80176218_indexedglobal.c`. **Next reader session starts here:
  find the 2 missing instructions**, not the hoist — that question is closed.

- **🔧 2026-07-24 (SESSION-18) — operational note for whoever launches the next ILS batch.** I watched
  six ILS runs with `Monitor` + `tail -f … | grep`, which is the documented anti-pattern: `tail -f`
  never exits, so each watcher stayed armed until its 1-hour timeout **long after its result had
  arrived** — Drew saw 7 live monitors when only 1 job was actually running. `permuter_ils` also buffers
  stdout, so nothing streams anyway; the whole run lands in one batch at exit. **Use a single
  self-terminating waiter instead**, e.g. Bash `run_in_background` with
  `until ! pgrep -f "permuter_ils.py <fn>" >/dev/null; do sleep 20; done; tail -3 <log>` — one
  notification, exits on its own. Reserve `Monitor` for genuinely per-occurrence streams.
  **⚠️ AND THE OBVIOUS WAITER SELF-DEADLOCKS — I hit this immediately after writing the line above.**
  `until ! pgrep -f "permuter_ils.py <fn>"` matches **the waiter's own command line** (it contains that
  string), so the loop never exits and you get a phantom "still RUNNING" forever. Use a PID captured at
  launch, which cannot self-match:
  `nohup … & echo $! > .run/ils.pid` then `until ! kill -0 "$(cat .run/ils.pid)" 2>/dev/null; do sleep 20; done`.
  (Or `pgrep -f` with a pattern the waiter does not contain.) Same class as every other instrument bug
  this project keeps finding: the tool answered a slightly different question than the one asked.

- **⚖️ 2026-07-24 (SESSION-18) — §66d-4 QUALIFIED by its own counter-example (R14). `func_80140958`
  (giant #2): fresh `--klass cse` pass, base 56, prior profile `regalloc` → **best=56, ZERO improvement
  across all 8 cycles** (196 waypoints, every one at 56).** So profile diversity is **3-for-3 on
  `func_8014D820`, 0-for-1 on `func_80140958`** — it is a cheap lottery ticket, not expected yield.
  The rule stands as *"before declaring a floor, spend one unattended pass per unused profile"* (it costs
  ~0 tokens and it did unlock 6 points on one giant); it does **NOT** stand as *"each profile is worth
  ~2"*. Cookbook §66d-4 amended in place — I recorded the general form off one function earlier this
  session and the second data point refuted it, which is exactly the R14 failure mode this project keeps
  catching. **Consequence for planning: do not project giant yields from the `func_8014D820` curve.**
  `func_80140958` remains at **54** (match_one) / 56 (permuter object scorer) with its SESSION-17
  diagnosis intact (LICM hoists inner-loop constants to the outer preheader, stealing the two callee
  regs the target gives const-3 `$fp` and `&D_801879BE` `$s6`) — untouched by reading this session.

- **🌊 2026-07-24 (SESSION-18) — WAVE BATCH 1 (Drew-authorised: 2 drafters, no ultracode, Opus 5 @ High).
  The premise was WRONG and checking it first saved the tokens.** `build_wave_args --rank live
  --min-live 100` on ov_SC07_006 selected `func_80174CB0` + `func_8014D4C0` — and a glob of every draft
  dir (§66c) showed **0 of the 36 fresh non-jtbl targets are never-drafted**; `func_80174CB0` alone has
  **100 existing drafts**, and `func_8014D4C0` already had a byte-correct **MATCH** sitting unbanked in
  `.run/drafts-sc07006-fresh-cn-cast/`. This confirms SESSION-17's "0 cached + never-drafted targets at
  live≥100" at wave-selection time: **on this pool, drafting is not the bottleneck — integration is.**
  **⇒ THE REFRAME THAT MADE THE WAVE WORTH RUNNING:** a draft's blocker class is determined by *how it
  declares its callees*, so the agents were pointed at the **named blocker** with the canonical callee
  signature supplied verbatim, i.e. "produce a BANKABLE variant of known-correct C" rather than
  "re-derive the C". **Result on `func_8014D4C0`: MATCH (84 ins) on the first iteration, 55 s, 32k
  tokens** — vs the ~110k/fn measured for cold drafting. The change was two lines (canonical
  `func_80135A4C` decl + argument casts at the call site, both compile-time-only).
  **THEN THE BLOCKER MOVED ONE LEVEL UP (§65 layering, as designed):** with the callee fixed, cc1 now
  reports `conflicting types for func_8014D4C0` itself — `self_decl_tu`. The TU declares
  `extern void func_8014D4C0(s32 a0, void *a1, void *a2);` (inside a `DEFINE_` body,
  engine_core.h:9530) while the byte-true def is `s32 (s32, u16 *, u16 *)`.
  **Route (a) REFUTED by bytes:** re-declaring the def `void` (returns kept) → **81 ins vs 84**, the
  `li $v0` returns are dropped. So the return value is real codegen, not paperwork.
  **⇒ The correct route is the §30#2 macro-widen** (`extern void`→`s32` in the macro), and it is
  **byte-neutral here because the callers discard the return** (`func_8014D4C0(a0, buf1, buf2);`,
  verified at engine_core.h:9543 + ov_SC07_006:4127). That is a **T2 fleet-shared edit ⇒ R22
  MANDATORY** (§61/§63). Value 84×138 = 11,592 ins ≈ **0.09pp**.
  **BATCH THE WIDEN:** `func_8014D820` is blocked on the *identical* class (`DEFINE_func_8014D790`
  declaring it `void (s32, void*, void*)`). Do the widens together and pay ONE R22 cycle, not two.
  **⚠️ PROCESS SLIP (mine):** I ran `recover_integration` against `.run/drafts-s18b1/` while a second
  agent was still WRITING into that directory — it picked up the half-finished sibling and reported
  0/2. Nothing was corrupted (tree stayed clean, the run banks nothing on failure), but **never gate a
  draft dir that a live agent owns** — copy the finished file out first (`.run/drafts-s18b1-solo/`).

- **✅ 2026-07-24 (SESSION-18) — `func_80174CB0` BANKED into ov_SC07_006 (123 ins, live 138). The
  SESSION-17 "§65g-class — needs a transform that does not exist yet" verdict is REFUTED: it needed the
  right SIGNATURE, not a new tool.** Agent B (isolated, Opus 5 @ High, 65k tokens / 4.7 min) found the
  layer nobody had reached under the callee conflict — **the function's OWN declaration**. The TU
  expands `DEFINE_func_80174C80()` carrying `extern s32 func_80174CB0(s32, s32);`, while **every prior
  draft (100 of them) defined `void func_80174CB0(s32, s16)`** — which matches perfectly standalone and
  dies in the TU with `conflicting types`. Defining it `s32 (s32, s32)` and recovering param_2's
  s16-ness with an explicit `(s16)param_2` cast at the `func_80012558` use site is byte-identical.
  The agent also self-verified through the **real** cpp→cc1→maspsx→as chain on a scratch TU copy
  (cc1 rc=0, 123/123 ins, 0 diffs) *before* handing back — which is why the bank was first-try clean.
  `make check BINARY=ov_SC07_006` → **BYTE-IDENTICAL** (`7ca772be…`). R22 clean-fleet running.
  **⚠️ HYPOTHESIS TO TEST AFTER R22 — the recovery tool may have taken a FLEET-TIER edit it did not
  need.** The bank rewrote `src/shared/engine_core.h` (2 lines, `DEFINE_func_80174C60` +
  `DEFINE_func_80174C80`) relaxing `extern s32 func_80174CB0(s32, s32);` → `extern s32
  func_80174CB0();`, plus the same in 2 overlay-local files. **But the banked definition is
  `s32 func_80174CB0(s32 param_1, s32 param_2)`, which AGREES with the original prototype** — the
  conflict belonged to the *old* `void (s32, s16)` drafts. So the relaxation looks unnecessary, and it
  converted a T1 binary-local bank into a **T2 fleet-shared** one (blast radius 138 overlays, R22
  mandatory) for nothing. The `()` form is byte-safe *here* only because both call sites pass `s32`
  (Phase-15: `()` is REJECTED when a param needs default promotion — `s8/s16/u8/u16/float`).
  **Test: revert the 4 decl lines, re-gate. If it still banks, `recover_integration` should probe
  whether a stage is NEEDED before applying it** — an unrequested tier escalation is exactly the class
  R32–R35 exist to catch.

- **🚨 2026-07-24 (SESSION-18) — THE PROPAGATION "TYPE CAP" IS A MISLABEL. Measured 7/7 CARRY-FIXABLE,
  0/7 actual type problems. This is why a fix Phase 21 already specified was never built.**
  `dedup_propagate.compiles_standalone()` returned a bare `False` and the caller filed EVERY failure
  under `"overlay-local TYPE (the real cap)"`. Reproducing the compile by hand shows the real cc1
  errors are **undeclared file-scope externs** — the body references `extern` decls that live OUTSIDE
  the extracted def block. For `func_80174CB0`: 22 carried externs make it compile **clean** (verified:
  cc1 rc=0). It is not a type problem at all; it is the exact gap Phase-27's
  `family_remap._carry_macros` closed for file-scope `#define`s, one level over — **extern decls**.
  **FIXED (safe, read-only classification):** `compiles_standalone` now returns `(ok, stderr)` and the
  skip is classified by ACTUAL cause — `missing file-scope extern (CARRY-FIXABLE): <names>` vs
  `overlay-local TYPE (the real cap)`. R32/R33/R34: a skip that discards its own diagnosis is invisible
  work; one that ASSERTS the wrong cause is worse — it redirects every later session.
  **FLEET SIZING (`--auto-from ov_SC01_077 --check-only`, touches nothing): 7 skipped, ALL 7
  CARRY-FIXABLE, ZERO genuine type-cap.**
  | addr | missing externs |
  |---|---|
  | 0x8016A73C | ApplyMatrixSV, D_800AE620, RotMatrixYXZ, func_80048EAC |
  | 0x80155800 | D_8011F730, func_8001382C, func_80146DB8, func_80146E98 |
  | 0x80167540 | func_80146A6C, func_80146C3C, func_801670E4, rand |
  | 0x801535F4 | func_8014CC28, func_8014ED28, func_8014FA04 |
  | 0x8016F0AC | D_80126B58, func_80165770 |
  | 0x80142B2C | func_80142C84, func_80143994 |
  | 0x8014FE60 | D_801152A8 |
  **⚠️ THE HISTORY MATTERS:** `0x80142B2C`, `0x801535F4`, `0x80155800` are on the **Phase-21 backlog's
  "7 callee/data-plumbing capped fns"** list, whose note already read *"a macro-extern-injection (or
  canonical-callee-sig embed) frees them ×134 (~+0.3%)"*. **Phase 21 diagnosed it correctly and it was
  never built** — and in the meantime the mislabel told every subsequent session these were the type
  wall. A wrong diagnostic label cost this project ~4 phases of a known, mechanical win.
  **VALUE LOCKED BEHIND THE CARRY FIX:** these 7 (Phase-21 estimated ~+0.3pp) **plus `func_80174CB0`
  itself** (123 ins × 138 = 16,974 ins ≈ **+0.13pp**), so ≈ **+0.4pp mechanical, ~0 agent tokens**.
  **NEXT (spec, deliberately NOT built in this long session — it writes 138 overlay files, the §63
  disaster class):** add `_carry_externs` to `dedup_propagate` mirroring `family_remap._carry_macros` —
  collect the file-scope `extern` lines matching the identifiers the body references, emit them INSIDE
  the lifted `DEFINE_func_*` body (existing macros already carry externs, e.g. `DEFINE_func_80174C60`,
  so the shape is established), dedupe against decls the target TU already has, then `--check-only` →
  one gate → **R22 mandatory**. `func_80174CB0` is banked ×1 today and is the ready-made test case.

- **✅ 2026-07-25 (SESSION-18) — WAVE BATCH 2 / `func_8014F3E8`: MATCH (32 ins), real-TU verified, and
  the agent CORRECTED MY PREMISE — the named callee was not the wall.** I briefed it that
  `conflicting types for func_8014F468` was the blocker. It disposed of that entirely with the
  canonical `extern void func_8014F468(void)` + a **call-site return-cast**
  (`((s32 (*)(void))func_8014F468)()`, the §17a-1 idiom) and found the real wall one layer down: **this
  function's own return type**. Byte-true def-sig is `s32 func_8014F3E8(s32)`.
  **`void` is PROVABLY impossible here — 4 variants tested, all byte-recorded:**
  | variant | result |
  |---|---|
  | plain `void`, no pin | 32 ins, **1 diff** — delay slot becomes `nop` (the `$v0` set is DCE'd at a void epilogue) |
  | `register s32 rv __asm__("$2"); rv = 0;` | identical 1-diff `nop` — dead store deleted |
  | + `__asm__ __volatile__("" : : "r"(rv))` | `move $v0,$zero` DOES fill the slot, but the asm keeps `$L2` non-empty so the `func_8014F6F4` arm can't fall through → `j $L1`+nop → **34 ins** |
  | `register volatile` | gets a stack slot, frame 0x20 → 5 diffs |
  The tell is the guard branch's delay slot `bnez $v0,.L8014F458 / addu $v0,$zero,$zero` — dbr's
  eager-steal of the `return 0;` value-set after cc1 collapses `$L2`/`$L5` into the shared epilogue.
  ⇒ textbook **§30 #2**, def-side return-type wall with a macro escape.
  **REAL-TU PROOF (both directions):** spliced into a scratch copy of the TU — with today's
  `engine_core.h`, cc1 **rc=33** `conflicting types for 'func_8014F3E8'`; with a scratch-shadowed
  header carrying the widen, cc1 **rc=0** and the object's `func_8014F3E8` is **32/32 ins, 0 diffs**.
  Nothing under `src/` was touched; artifacts at `.run/drafts-s18b2/{tu_base,tu_widen,w3,try}`.
  **THE BANKING RECIPE (mechanical, byte-neutral) — and its one trap:**
  `sed -E -i 's/extern void (func_8014F3E8)/extern s32 \1/g' src/shared/engine_core.h src/*/*.c`
  - **15** decls in `engine_core.h`, all inside `DEFINE_func_*` bodies (4120, 7733, 7747, 7774, 7788,
    7815, 7829, 7856, 7883, 7910, 8215, 19216, 20926, 21103, 25586). 11 discard the return; **4 already
    read `$v0`** via `((s32 (*)(s32))func_8014F3E8)(…)` — `engine_core.h:25593` even documents
    *"canonical func_8014F3E8 is void, but its $v0 is tested here"*.
  - **3,349** decls in `src/*/*.c` (3,197 `(s32 a0)` + 140 `(s32)` + 12 K&R `()`) — the §8b carried
    decl layers.
  - **⚠️ ALL SPELLINGS MUST MOVE TOGETHER.** Widening only the header RE-CREATES the conflict
    per-overlay — reproduced on `src/ov_SC01_000/ov_SC01_000_jr_80154C24.c` (`:736` void vs `:1265`
    s32). The K&R `()` form stays compatible (`s32` is promotion-safe).
  - Byte-neutrality spot-checked bit-identical before/after on 3 files incl. two that instantiate the
    return-casting macros (`DEFINE_func_80157580` / `DEFINE_func_801612B8`). **`make check-all` is
    still the arbiter (G3/P9).**
  **⇒ THE §30#2 WIDEN IS NOW A BATCH OF ≥2** (`func_8014F3E8` 32×138 = 4,416 ins · `func_8014D4C0`
  84×138 = 11,592 ins ≈ **+0.12pp combined**), and `func_8014D820` will join it when it matches. The
  sed is per-function-name so it is narrow and reviewable, but it is FLEET-SHARED ⇒ **one R22 for the
  whole batch**, never one per function.

- **⚖️ 2026-07-25 (SESSION-18) — the §68 comment-halt fix UNBLOCKED the plan but only banked ×3, not
  ×138. The measured reason is exactly the risk I flagged when enabling the carry.**
  `dedup_propagate --addr 0x80174CB0 --recover` → *"propagated 1 function(s); **3 overlays** rebuilt
  byte-identical"*; **135 overlays excluded** with `byte-diverge / irreconcilable here -> kept ×1`.
  **That message is misleading and the bytes say so:** the plan listed 138 members because all 138
  share the same `h_exact` — the function's bytes ARE identical everywhere. So the exclusions are NOT
  byte divergence; they are the **carried file-scope externs colliding with each target overlay's own
  declarations** of the same symbols. The 3 that landed (ov_SC07_006/007/011) are the overlays whose
  existing decls happened to be compatible.
  **⇒ THE CARRY IS NECESSARY BUT NOT SUFFICIENT — the spec for Task 8 tightens:** collecting the
  referenced file-scope decls is step 1; step 2 is **reconciling them against each TARGET TU** (drop a
  carried decl the target already declares compatibly; refuse/repair where it declares it
  incompatibly — `cdecl.compatible()` is the oracle, and `reconcile_tu` already does this shape of
  work for data externs). Without step 2 the macro is only instantiable in overlays that happen to
  agree, which is what we just measured.
  **Also worth fixing: the exclusion message itself.** `byte-diverge / irreconcilable` conflates "the
  function's bytes differ here" with "the instantiation would not compile here" — two causes with
  opposite remedies, and today it reported the wrong one. Same defect family as §68's mislabel, in the
  same tool, one function down. Make it print the failing cc1 line.
  **Net today: ×1 → ×3** (+246 ins, ≈0.002pp) — honest, small, and the structure (a real
  `DEFINE_func_80174CB0` in engine_core.h) is correct and reusable once step 2 lands. R22 running.

- **✅ 2026-07-25 (SESSION-19, Opus 5 @ High) — THE §30#2 WIDEN BATCH EXECUTED. Both functions banked;
  the widen is byte-neutral fleet-wide; and the batch produced a §30#2 REFINEMENT the recipe missed.**
  **Scope verified against the tree before touching anything (R14/R35).** The SESSION-18 recipe's
  counts reproduce EXACTLY: `extern void func_8014F3E8` = **15** in `src/shared/engine_core.h` +
  **3,349** across 1,729 `src/*/*.c`; `extern void func_8014D4C0` = **1** + **1,730**. An exhaustive
  spelling census (`extern|definition` forms of both names over every `.c`/`.h` under `src/`) found
  **no decl outside the `extern void <name>` shape** and **no header other than `engine_core.h`**
  carrying one — so the sed is complete, not merely plausible. Pre-existing `extern s32` decls of
  either name: **0**.
  **Applied as ONE fleet edit** (`find src -name '*.c' -o -name '*.h' | xargs sed -E -i
  's/extern void (func_8014F3E8|func_8014D4C0)/extern s32 \1/g'`) → 1,731 files changed; post-state
  15+1 / 3,349+1,730 `extern s32`, **0 `extern void` remaining**. Snapshot discipline (§61/§63): `src/`
  was clean at `commit:0991`, so `git checkout -- src/` is the restore path — no inverse transform.
  **BYTE-NEUTRALITY OF THE WIDEN, ISOLATED FIRST (cheap, before spending a gate cycle):**
  `make build BINARY=ov_SC07_006` → `7ca772be…` and `BINARY=ov_SC01_000` → `9052dc0e…`, both
  **BYTE-IDENTICAL**. ov_SC01_000 was chosen deliberately — it instantiates the two return-CASTING
  macros (`DEFINE_func_80157580` / `DEFINE_func_801612B8`), the only sites where the decl's return
  type could plausibly interact with codegen. Isolating the shared edit from the drafts is what made
  the one failure below trivially attributable.
  **GATE 1 — `func_8014F3E8` VERIFIED (32 ins), `func_8014D4C0` FAILED `PLUMBING`.**
  **⇒ THE RECIPE WAS HALF A FIX, and the gate said so precisely:** `conflicting types for
  'func_8014D4C0'` persisted because the canonical decl
  (`engine_core.h:9530`, inside `DEFINE_func_8014D438`) is `(s32 a0, void *a1, void *a2)` while the
  byte-true draft used `u16 *`. **The widen addresses the RETURN half of a self-decl conflict only;
  the PARAMETER half is a separate axis.** `func_8014F3E8` (single `s32` param) never had one, which
  is why the SESSION-18 recipe — derived from it — did not mention the case.
  **FIX = draft-local (T0), NOT a second fleet edit:** define with the canonical `void *` params and
  cast **at each use** (`((u16 *)a1)[1]`, `*(u16 *)a1`, …) — the §17a-1 move applied to the def's own
  signature, exactly as `func_80174CB0` needed in SESSION-18. **GATE 2 → VERIFIED, `7ca772be…`.**
  **⇒ §30#2 GENERALIZED (cookbook update):** a def-side self-decl conflict has TWO independent axes —
  *return* (fix = the fleet macro-widen, T2, R22-mandatory) and *params* (fix = canonical param types
  + casts at each use, **T0, no fleet edit at all**). Diagnose which axis before reaching for the
  expensive one; reaching for the fleet edit when the params are the wall spends an R22 cycle and
  still fails.
  **REACH CONFIRMED BY THE SIGS, not assumed:** both are present in **138/138** overlay sigs with a
  **single distinct `h_exact`** each (`2ccf344d` / `acc0ee6d`) — genuine ×138 candidates, so
  propagation is worth its own gated pass (32+84 ins × 138 = 16,008 ins ≈ **+0.12pp** if it lands).
  Drafts: `.run/drafts-s18-widen/` (F3E8) + `.run/drafts-s18-widen2/` (D4C0, the param-axis variant).

- **✅ 2026-07-25 (SESSION-19) — §72 PIN-SAFETY AUDIT (open action #3): the 5-pin behemoth draft is
  SAFE, and the audit produced the general test (§74).** `.run/giants/s18_func_8017D960_b2.c` carries
  `register __asm__` pins on `$25 $17 $19 $20 $21`. **`$25` is `$t9` — CALLER-SAVED**, which is the
  only genuinely corrupting form of the §72 hazard (gcc-2.7.2 does not save/restore an
  explicit-register variable across a call, so a live range spanning a `jal` is destroyed silently).
  **Audited without recompiling** — the SESSION-18 `match_one` object survives at
  `.run/match/func_8017D960.2216347/func_8017D960/t.o` and `cmp` proves its `t.c` IS this draft.
  **VERDICT — mode (1) does not arise:** the object contains **exactly 3 `jal`s, all at `0x2c–0x50`,
  and the first pin write is at `0x58`** ⇒ *no call after the pins are established*. Corroborated in
  the C: every call-shaped token after line 270 is a macro defined in the file (`gte_*`, `BOXTEST`,
  `ATTEN`, `CLAMP80`) — checked by token census, not by eye, because a 636-line behemoth hides a
  `jal` easily.
  **Mode (2) IS present and is benign:** write-counts per pinned reg are 2/3/3/5/5 against 2
  assignments each (+1 epilogue restore for the callee-saved four). The excess is gcc using the pinned
  register as a SCRATCH before the pinned variable's own value lands — `lui s4,..; lw s4,0(s4);
  addiu s4,s4,-128` (`$20` carrying the raw `D_801CBC90` for two insns) with `addu t9,s4,zero`
  routing `r1`'s value out through it. Self-consistent; nothing live was clobbered.
  **⇒ the draft is safe to keep building on**, and the reusable test is cookbook **§74** (objdump the
  surviving `match_one` object; compare `jal` addresses against the first pin write; expect
  `writes == assignments + 1 epilogue lw`). **Standing rule:** prefer a **callee-saved** register for
  any pin whose variable outlives a call; if the target genuinely wants a caller-saved reg across a
  `jal`, the pin cannot express it — that is a real wall verdict, not a drafting slip.

- **🚨 2026-07-25 (SESSION-19) — THE PROPAGATION CAP IS A MINORITY-SPELLING SOURCE OVERLAY. Measured,
  not inferred; and it retires the "build a reconciliation engine" framing of Task 8/open-action-2.**
  Propagating the two banked functions: **`func_8014D4C0` → ×138** (all 138 rebuilt byte-identical,
  group registered) but **`func_8014F3E8` → dropped**, then on a re-run **×4**.
  **TWO SEPARATE CAUSES, and the first was MINE:**
  **(1) The drop was a FLAG OMISSION, not a wall.** Without `--recover`, `dedup_propagate` takes the
  historical all-or-nothing path on the first culprit overlay — so ONE divergent member costs the
  WHOLE group (×0). With `--recover`, Part A excludes just the culprit. **Always pass `--recover` on a
  targeted `--addr` run.** (The `[drop]` message even printed *"reach<2 after exclude"* when reach was
  **138** and no exclude had been attempted — the no-recover branch jumps straight to `dropped`.)
  **(2) The 134 exclusions are a COMPILE conflict, and the message's stated cause is impossible.**
  `[exclude] … byte-diverge / irreconcilable` — but members are selected **by `h_exact`**, so all 138
  are byte-identical *by construction* (single hash `2ccf344d`). A byte divergence cannot be what
  excluded them. The census names the real cause in 30 seconds:
  | spelling of `func_8014F468` (the carried extern) | count |
  |---|---|
  | `extern s32 func_8014F468(void);` | **1,710** |
  | `s32 func_8014F468(void)` (definition) | **134** |
  | `extern void func_8014F468(void);` | 20 |
  | `void func_8014F468(void)` (definition) | **4 — all `ov_SC07_{006,007,010,011}`** |
  `dedup_propagate` carries the SOURCE overlay's file-scope externs into the shared macro **verbatim**,
  and the overlay I banked from is one of the four outliers. The macro inherited `extern void`, the
  134 overlays that *define* the symbol `s32` rejected it, and propagation landed on exactly that
  4-overlay island. **Nothing about the code was hard.**
  **⇒ THE FIX IS NORMALIZATION, NOT A RECONCILIATION ENGINE — and the engine would not have worked.**
  One macro text is instantiated in 138 TUs; it **cannot** carry a per-overlay extern, so if members
  genuinely disagree no per-member rewrite of a *shared* body can satisfy them — they must be made to
  agree first. (`reconcile_tu.fix()` already does "TU wins + cast at use" for DATA decls and skips
  `d.kind == 'func'`; extending it would not have reached this, because the conflicting text lives in
  the shared header, not in a draft.) Flipped the 24 minority occurrences to the fleet canon (4
  definitions + 19 overlay externs + the 1 macro line). `func_8014F468` is a pure inline-asm `$sp`-switch
  trampoline — no C-level value flow — and 134 overlays had already *proved* `s32` byte-correct for the
  identical function. **Blast radius byte-gated in full** (the 4 instantiators): `7ca772be` / `b3b95547`
  / `d7b5875d` / `9885af74`, all BYTE-IDENTICAL. Fleet now uniform: 1,730 `extern s32` + 138 defs, **0
  `void`**. → cookbook **§75**.
  **THE FOLLOW-UP IS `dedup_extend`, NOT `dedup_propagate`** (§75 #3): once banked, the body IS a macro,
  and `--addr` can only author from an *inline def* ("no source overlay has it matched"). `dedup_extend
  --check-only` over the 134 excluded overlays planned **400 extensions / 3 groups per binary** — so
  this also picks up **`func_80174CB0`**, stuck at ×3 since SESSION-18 on what looks like the identical
  class. It also refuses a dirty tree (H4), which is why the normalization commits first.
  **R22 clean-fleet after the propagation: 140 passed, 0 failed of 140.**

- **✅ 2026-07-25 (SESSION-19) — THE EXTEND SWEEP: `func_8014F3E8` reaches ×138, and the residual
  exclusions are ENUMERATED with named causes (§75a).** One `dedup_extend --binaries <the 134
  excluded>` run: **banked 134 / 400 planned**, i.e. **`func_8014F3E8` VERIFIED in all 134** (→ ×138
  total, +4,288 ins) — the §75 normalization converted a 4-overlay island into full fleet reach with
  no drafting at all. The other two planned groups failed in *every* binary, and
  `harvest_verify`'s classifier named a **different cause for each**, which is the real deliverable:
  | class | cc1/ld | example | remedy |
  |---|---|---|---|
  | **A — minority spelling** | `conflicting types` + a lopsided census | `func_8014F468` 1,710 `s32` vs 4 `void` | normalize (done, §75) — cheap, byte-neutral |
  | **B — genuine arity split** | same message, TWO real populations | `func_8012F14C` **1,944 `(s32)` vs 968 `(s32,s32,s32)`** | the §29 loose-typing wall; a K&R `()` in the macro MAY satisfy both (order-dependent per `cdecl.compatible`) — **probe, do not normalize on a guess** |
  | **C — missing carried extern** | `undefined reference to 'SHB'` (a LINK error) | `func_80165CA0` | the SESSION-18 CARRY-FIXABLE class |
  **⚠️ I ALMOST GENERALIZED FROM ONE SAMPLE (R14).** I predicted `func_80174CB0` was "the identical
  class" as `func_8014F3E8`. It is class A *in kind* but on **different symbols, and different ones
  per overlay** — `func_80012ABC` at ov_SC01_000 (73 `s32` vs 7 `s16` — the minority is on the TARGET
  side this time), `func_8012F14C` at ov_SC01_001 (class B). **One member's error names one blocker,
  not the blocker set** — collect the classifier's line across the whole sweep before scoping a fix.
  **The discriminator is ONE grep and it decides the remedy:** census every spelling of the symbol cc1
  named. ≥95/5 ⇒ class A, normalize. Two substantial populations ⇒ class B, an arity change is **not**
  byte-neutral by inspection, measure first. A *link* error ⇒ class C, nothing to do with types.
  → cookbook **§75a**. `func_80174CB0` (123 ins, ×3 since SESSION-18) and `func_80165CA0` stay capped,
  now with a named cause and a named next probe each — not a wall verdict.

- **✅ 2026-07-25 (SESSION-19) — `func_80165CA0` ×3 → ×135: the blocker was a `#define` extraction
  never carried (§75b). The full-sweep census REVERSED my ranking (R14/R35).**
  §75a says collect the classifier's line across the WHOLE sweep before scoping. Doing that on the
  134-binary log inverted the plan I had just written:
  | blocked fn | blocker cc1 named | count | class |
  |---|---|---|---|
  | `func_80174CB0` | `func_8012F14C` | **131 / 134** | B — genuine arity split |
  | `func_80174CB0` | `func_80012ABC` | **3** | A — minority spelling |
  | `func_80165CA0` | `SHB` | **132 / 132** | C |
  **I had ranked the class-A normalization FIRST at "~+0.13pp if it reaches ×138". It is worth 3
  overlays, not 138.** The dominant blocker is the class-B arity split, and the genuinely cheap win
  was the one I had ranked third.
  **`SHB` IS NOT A SYMBOL — it is a file-scope `#define`** (`__asm__("" : "=r"(x) : "0"(x))`, a
  sign-extension barrier). An unexpanded `SHB(x)` parses as a call to an undeclared function, compiles
  clean, and dies at LINK — which is why this class reports `undefined reference`, never `conflicting
  types`. `extract_unit` walks back over contiguous `extern …;` lines and **does not collect
  `#define`s**, so the define was left behind in the source overlay — sitting literally BETWEEN the
  two carried externs and the instantiation:
  `extern s32 D_8011D030; / extern s32 D_80126728; / #define SHB(x) … / DEFINE_func_80165CA0()`.
  The other 132 overlays DO define `SHB` — ~300 lines further down (`ov_SC01_001`: stub @4462,
  `#define` @4781), i.e. **below** the splice point. **Pure ordering; nothing was missing.**
  **THE CONFIRMATION THAT IT WASN'T JUST A FITTING STORY:** the 3 stuck members are *precisely* the 3
  files carrying the `__volatile__` spelling of `SHB` — that define is the function's own preamble,
  still above its own instantiation. The diagnosis predicted the membership exactly.
  **FIX:** `engine_core.h` owns the barrier as **`ENGINE_SHB`** (a DISTINCT name — the overlays define
  `SHB` themselves in two different spellings, 3 volatile / 132 non-volatile, so a shared `#define SHB`
  with a different replacement list is a hard redefinition error); the body's 7 uses now call it.
  Volatile form = what the 3 banked members actually compile with (not what a stale body comment
  claims). Byte-gated on the full existing radius first: `d19c9580` / `9052dc0e` / `7ca772be`.
  **RESULT: `dedup_extend` banked 157 / 478 planned across 135 binaries** — `func_80165CA0` **×135**
  (99 ins × 135 ≈ **+0.10pp**) plus **22 other functions ×1** picked up in the 3 overlays the first
  sweep had excluded. → cookbook **§75b**.
  **`func_80174CB0` (123 ins) failed in 133 — class B, unchanged and untouched.** An arity change is
  not byte-neutral by inspection (§29's narrow-param wall is exactly this), so it gets a measured
  probe, not a guess.

- **✅ 2026-07-25 (SESSION-19) — CLASS B RESOLVED: the remedy is the FULL §17a-1 PAIR, and a
  decl-only fix MOVES the error rather than shrinking it (§75c).** The K&R `()` probe on
  `func_8012F14C` was byte-neutral on the 3 members but banked **0/179** — and the failure class
  moved **PLUMBING → CC1-FAIL**, which is the tell that the first wall fell and a second appeared.
  I reproduced it by hand-splicing the macro into `ov_SC01_001` and reading real cc1 stderr
  (**not** the classifier's bare `make … Error 33`):
  `ov_SC01_001_jr_801734BC.c:2616: too many arguments to function 'func_8012F14C'`.
  C's composite-type rule: after `void f(s32);` then `void f();` the composite is **still
  `void f(s32)`** — the earlier prototype wins — so a 3-arg call is a hard error no declaration
  spelling can rescue. **FIX = the other half §17a-1 always specified** (what `cast_call_sites.py`
  implements): keep the `()` decl (conflict-free in either order) **and** cast the call —
  `((void (*)(s32,s32,s32))func_8012F14C)(…)`; gcc folds a cast of a KNOWN function symbol back to
  a direct `jal`, so the bytes are unchanged. Byte-gated on all 3 members (`7ca772be` / `b3b95547`
  / `9885af74`), then `func_80174CB0` VERIFIED on the first extended binary. → cookbook **§75c**.

- **🚨 2026-07-25 (SESSION-19) — A TOOL DEFECT I INTRODUCED THE CONDITIONS FOR, AND CAUGHT:
  `dedup_extend` STRIPPED A LOAD-BEARING INCLUDE FROM 135 BINARIES.** On a 0-banked run,
  `if not banked: ensure_include_revert(b)` fired **unconditionally**. `ensure_include()` returns
  True only when *it* inserted the line, but the revert ignored that return value — so on the 135
  binaries that already had `#include "../shared/engine_core.h"` from earlier work, the class-B
  probe's zero-bank run **removed it from all 135 at once**, leaving every `DEFINE_func_*()` in
  those overlays unresolvable.
  **Why it survived until now:** the tool's designed case is NEWLY-onboarded binaries (which
  genuinely lack the include, so the revert is correct there), and every prior run banked ≥1 per
  binary so the branch never fired.
  **WHY NO BYTE-GATE SAW IT (R34):** the damage lands **after** the last gate — `harvest_verify`
  had already finished and reverted its drafts. The byte-gate is a null oracle for state mutated
  after it runs. Caught by reading `git status` before moving on; `git checkout -- src/` restored;
  **nothing was committed, nothing lost.**
  **CLASS:** §61/§63 — an undo written as an **inverse transform** instead of a snapshot restore,
  applied without checking whether the forward action was ever taken. Identical shape to the
  SESSION-14 `fix_arity_callers --revert` incident.
  **FIXED** (`added_include = ensure_include(b)`; revert only if this run added it) and
  **NEGATIVE-CONTROL-PROVEN**: stripping the include from `ov_SC01_004` makes `make audit-binaries`
  fail loud (`[FAIL] … does NOT include ../shared/engine_core.h`, make Error 1) — the **R36
  citizenship gate is exactly the detector for this class**, then restored. `make tools-health` →
  **OK** (sigs fresh; corpus+resident, cdecl, binaries, report/lint/dedup all green).

- **✅ 2026-07-25 (SESSION-19) — `func_80174CB0` ×3 → ×135, and the census predicted the residual
  EXACTLY.** With the §75c pair in place, `dedup_extend` banked **132 / 179 planned across 135
  binaries** — `func_80174CB0` VERIFIED in **132**, failed in **3**. The class-A census
  (`func_80012ABC`: **73 `s32` vs 7 `s16`**) had predicted the class-B fix would leave exactly the
  class-A overlays behind, and it left **3** — the same 3 the original sweep's blocker breakdown
  named (131 class-B / 3 class-A). **A measurement that predicts its own residual to the overlay is
  the strongest evidence this session produced that the classes are real and not a story fitted to
  the failures.** 123 ins × 132 ≈ **+0.12pp**. The remaining 3 are worth 3 overlays; normalize the 7
  `s16` decls only if trivially cheap.

- **🏆 2026-07-25 (SESSION-19) — BEHEMOTH #3 `func_8017F510` CRACKED, PIN-FREE: 97 → MATCH (1,511 ins).
  The first xHigh behemoth, and the first distinct-code movement of the session.** An Opus 5 agent at
  **xHigh** (behemoths #1–#3 were worked at **High** — Drew's effort experiment) closed a residual that
  a full lower-tier pass had localized but not moved, and that **3,663 permuter candidates at base 97
  had failed to improve by even 1**.
  **VERIFIED INDEPENDENTLY, NOT TAKEN ON REPORT (R14):** I re-ran `match_one` → **MATCH (1511 ins)**,
  then the real arbiter — `harvest_verify --binary ov_SC03_006` → **BYTE-IDENTICAL**; **R22 clean-fleet
  140/140**. The agent honoured its sandbox exactly: zero changes outside `.run/giants/`.
  **METRICS: distinct-code 3,813,512 → 3,815,023 = +1,511 — EXACTLY the function's instruction count,
  and the ONLY distinct-code movement all session.** (instr-weighted 80.3%, fn-count 89.18%.) Reach is
  **×1** by sig — no propagation — which is precisely why it moves the metric propagation cannot.
  **THE MECHANISM (→ cookbook §76): the allocno CLASS (local vs global) is the dominant lever, and C
  reaches it ONLY through declaration scope and variable reuse.** Four of the five decisions were class
  choices — unreachable by statement order, expression shape, pins, or random search, which is exactly
  why the permuter was provably spent. Levers: (1) `otp` declared **per emit ARM** (4 deaths → four
  1-death local pseudos; `local-alloc.c:472`), whose second-order effect via `global.c:668-671`
  (local placements re-marked as HARD registers for global-alloc) had made the target's `otp = $a0`
  *structurally impossible*; (2) `cb` reused as the unlit `rgbc` temp — refs 27→39 lifts its
  `global.c:594 allocno_compare` priority past `tp`, flipping the 3-colouring → **97 → 10**; (3) one
  shared `rgbw` temp → **10 → 2**; (4) `mny` before `my` + one zero-byte `__asm__` at the head of the
  tri cull block → **MATCH**.
  **THREE CORRECTIONS TO THE BRIEF I GAVE IT — all byte-evidenced, all worth more than the match:**
  · **Residual B was never a scheduling residual** — it fell out free with lever 2 (a register grant
  observed as a schedule diff). · **Residual A is RTL EXPANSION order, not scheduling** — proven with
  `-fno-schedule-insns` AND `-fno-schedule-insns2` (source order survives both). **That attribution
  primitive is the reusable bit: run it before calling anything a scheduling residual.** · **Residual C
  had no single `c3` seed** — `c3` has no lever of its own and moves only when `cb` out-ranks `tp`. The
  cascade was real; the seed I briefed was not the steerable thing.
  **ALSO FOUND — a latent defect in a SHARED HEADER, pre-existing and unrelated to the draft:**
  `src/shared/engine_types.h` closed its include guard at line 1174 of 1259, leaving **11 typedefs / 85
  lines OUTSIDE the guard** since the Phase-29 crack-wave lift. Any TU including the header twice
  re-declares them, and gcc-2.7.2 rejects a repeated typedef even when identical — it surfaced as
  `conflicting types for 'Blk16_956C'` the first time a draft produced a double include. Guard moved to
  EOF; byte-neutral; R22 140/140.
  **ARTIFACTS (tracked — `.run/giants/*.{c,md,sh,py}` are allowlisted):**
  `.run/giants/s19_func_8017F510_b4.c` (130-line dossier) + `.run/giants/s19_f510_report.md`, whose
  **~50-row do-not-re-buy table is arguably worth more than the match** + `s19_{cc.sh,full.py,side.py,
  mk.py,sweep.py,probe.sh}`.
  **STRETCH, MEASURED NOT ASSUMED:** `func_8017F5B4` (1,511 ins, `ov_SC02_031`) is a **different
  h_exact** — so it is NOT a dedup sibling; it is a `family_remap` TEMPLATE candidate (same shape, same
  3-callee set, per-overlay reloc symbols). Worth a positional-remap attempt off the b4 source.

- **🏆 2026-07-25 (SESSION-19) — `func_8017F5B4` (1,511 ins) BANKED MECHANICALLY off the behemoth-#3
  crack: ~0 agent tokens. Two behemoths in one stretch; +3,022 distinct-code ins total.**
  `func_8017F5B4` @ `ov_SC02_031` shares behemoth #3's **h_norm AND h_seq** (`96fe0455c344` /
  `9a6bd2b91fd4`) but a different `h_exact` — i.e. the same instruction stream differing only in
  masked reloc fields. That is the §40 `family_remap` case exactly, so **no agent was spent**:
  `family_remap --addr 0x8017F510 --from ov_SC03_006 --to ov_SC02_031 --to-addr 0x8017F5B4`
  substituted **52 per-overlay symbols correctly on the FIRST invocation**. `match_one` → **MATCH
  (1511 ins)**; `harvest_verify --binary ov_SC02_031` → **BYTE-IDENTICAL**; **R22 140/140**.
  **ALL the work was PREAMBLE, none of it the body (→ cookbook §77).** Four `CC1 FAIL` rounds, each
  naming one construct the extractor drops: (1) multi-line `typedef struct {…} PolyGT4;` —
  `family_remap`'s backward walk accepts a line only if it STARTS with `extern`/`typedef`/comment, and
  a multi-line typedef ENDS with `} PolyGT4;`, so the walk halts there **and loses everything above
  it**; (2) consequently the file-scope `extern` block above the `#define BOXTEST/ATTEN` block; (3) the
  exemplar's own `#include` lines (`PolyFT3`/`PolyFT4` live in `engine_types.h`).
  **THIS IS THE THIRD CONFIRMATION TODAY OF ONE DEFECT CLASS, NOW ACROSS TWO TOOLS** — §75b found
  `dedup_propagate` dropping a file-scope `#define` and PREDICTED the generalisation; `family_remap`
  then dropped a typedef, an extern block and the includes. **Rule (§77): after any mechanical
  template/propagate step, diff the exemplar's full file-scope preamble against what the tool emitted.
  A `CC1 FAIL` on a remapped sibling is a PREAMBLE report until proven otherwise — it says nothing
  about whether the remap was right.** Don't reason about what the tool should have carried; compile
  and let cc1 enumerate the gaps one per round.
  **METRICS: distinct-code 3,815,023 → 3,816,534 (+1,511).** Combined with behemoth #3 that is
  **+3,022 distinct-code ins from the two**, versus **+0 from every propagation win this session**.
  Artifact preserved: `.run/giants/s19_func_8017F5B4_remap.c`.

- **🏆🏆 2026-07-25 (SESSION-19) — BEHEMOTH #2 `func_8017D960` CRACKED (1,806 → 0, PIN-FREE) AND ITS
  ENTIRE 5-MEMBER FAMILY BANKED: 16,690 distinct-code ins from ONE crack.** Opus 5 agent @ **xHigh**.
  **VERIFIED INDEPENDENTLY (R14):** `match_one` → **MATCH (3338 ins)**; then the real arbiter,
  `harvest_verify` on all five binaries → **BYTE-IDENTICAL** each; **R22 clean-fleet 140/140**.
  | overlay | fn | how |
  |---|---|---|
  | ov_SC03_090 | `func_8017D960` | the crack |
  | ov_SC03_089 · ov_SC03_104 | `func_8017D960` | §40 remap → MATCH **first try** |
  | ov_SC03_091 | `func_8017E778` | §40 remap (cross-address) → MATCH **first try** |
  | ov_SC03_102 | `func_8017CD9C` | §40 remap (cross-address) → MATCH **first try** |
  **METRICS: distinct-code 3,816,534 → 3,833,224 (+16,690) — 67.7% → 68.0%, the first percentage-point
  movement in that metric all session.** instr-weighted 80.3% → **80.5%**. Session distinct-code total
  **+19,712 ins**, ALL of it from the three behemoths; every propagation win contributed **+0**.
  **MY OWN BRIEF WAS WRONG IN AN INSTRUCTIVE WAY (→ cookbook §78).** I told the agent a negative length
  drift means "we are MISSING instructions the target has." True, but the CAUSE was not missing code:
  the 4 absent instructions were **4 emit tails × 1 `nop`** — delay slots the target could not fill
  *because the register it wanted was still live*. `u32 *otp;` at function scope has 4 deaths ⇒ fails
  `local-alloc.c:472` ⇒ global allocno in `$a2` ⇒ via `global.c:668-671` that pushes `tp` off `$a1` ⇒
  the `0xFFFFFF` mask is free early ⇒ maspsx hoists it into the slot and the `nop` vanishes.
  **Declaring `otp` per emit ARM fixed the entire drift in ONE edit** (3334→3338, 1806→333).
  **⇒ SECOND TIME IN ONE SESSION a residual that LOOKED structural was an allocno-class choice** (the
  first: F510's "scheduling" transposition, §76). **Rule: a `nop` present in the target but absent from
  your draft is usually a register-liveness fact, not a missing instruction — check for a register
  grant before treating a length or ordering diff as structural.**
  **TWO MORE REUSABLE FINDINGS (§78):** (1) gcc-2.7.2 `fold` **never** leaves a literal in the first
  term of an `|` chain — 7 parenthesisations measured, all reassociate — so `or acc, var, K` FIRST in
  the target means **`K` was a VARIABLE in the original source**; a direct asm→source read that retires
  a whole family of parenthesisation sweeps. (2) "make it a variable" has **two separable effects** —
  opacity to `fold` (structure) and a new allocno (registers); a **fresh short-lived local** gets
  structure right and allocation catastrophically wrong (690 mismatched, damage ~300 ins away),
  **reusing an already-busy variable** gets both.
  **THE ECONOMIC LESSON:** 9 levers, each proven necessary by drop-one ablation — and **5 of the 9 were
  read straight off the MATCHED relatives** `func_8017F510` (1,511, cracked earlier TODAY) and
  `func_8017CA80` (952), "worth more than every expression sweep combined". **Crack the smaller family
  member first; it is a lever library for the larger one.**
  **NEW TOOLING:** `.run/giants/s19_remap_family.py` — `family_remap` + the §77 preamble carry in one
  step (reproduces the exemplar's FULL file-scope preamble with the tool's own substitution map
  applied). It took the four siblings from "4 rounds of `CC1 FAIL` each" to **MATCH first try, ×4**.
  Artifacts: `s19_func_8017D960_b5.c` (dossier), `s19_d960_report.md` (~90-row do-not-re-buy table +
  citations), `d960_{mk,cc,score,full,side,hist,probe}` tooling.

- **✅ 2026-07-25 (SESSION-19) — THE h_norm-REMAPPABLE POOL: +4,919 ins banked, no cracking, no agent.
  And TWO of my own counts collapsed under scrutiny before I acted on either (R14/R35).**
  Surveying beyond the behemoths for stubs whose `h_norm` ALREADY has a matched instance (⇒ free §40
  remap):
  | my first reading | the truth | why |
  |---|---|---|
  | "`func_8017CA80`'s family = **102** unmatched" | **13** | my count tallied family members whose NAME appears as a stub ANYWHERE in the fleet, not instances actually unmatched. Semantics error, not arithmetic. |
  | "**56,267** ins remappable" | **8,114** | 86% of it was the known `-O0`/deferred set (`func_80144B9C` the whale, the `func_8013C414` cluster). |
  **I nearly recommended a target on the first number.** Both were caught by re-deriving before acting —
  the R35 discipline, applied to myself.
  **BANKED (each whole-binary byte-gated; `make check-all` → 140/140):** `func_80130D48` ×4 (1,064) ·
  `func_8018F3E4` (478) · `func_8018B3D0` (478) · `func_8017DECC`/`8017E428`/`8017EFB0`/`8017E830`/
  `8017F314`/`80180404`/`80180FEC`/`801819B8`/`801829D8`/`80183ED8`/`8018451C`/`801857C4`/`8018BA5C`
  (13 × 223 = 2,899) — **+4,919 ins**, distinct-code 68.0% → **68.1%**.
  **THE §77 CARRY GAP IS NOW THE DOMINANT COST OF MECHANICAL REMAP — 23 of 27 first-pass CC1-FAILs.**
  A second carry tool closed almost all of them: **`.run/giants/s19_remap_tu.py`** (companion to
  `s19_remap_family.py`) sources the preamble from the exemplar's **overlay TU** — the block between
  the previous top-level `}` and the def — instead of a standalone draft, applies `family_remap`'s own
  substitution map to it, and adds the two includes `match_one` never adds. **Result: 21 drafts went
  from 0 MATCH → 14 MATCH.** The 13 × 223-ins family all share ONE exemplar (`func_8017E6D8` @
  ov_SC06_018), so a single preamble fix cleared all 13.
  **A USEFUL ASYMMETRY OBSERVED:** `func_8018F3E4`/`func_8018B3D0` **failed `match_one` but BANKED in
  the whole-binary gate** — the real TU supplies decls the standalone compile lacks. So a `CC1 FAIL`
  from `match_one` is NOT a reason to skip the real gate on a remapped sibling.
  **RESIDUAL — 3,195 ins, 3 named causes, none chased on a guess:** `func_8017D5C0` (952) matches
  standalone but the whole-binary gate reports `conflicting types for 'memcpy'` — **the §58
  red-herring** (a WARNING from an unrelated TU position, not the real error; SESSION-14 hit the same
  label and the true cause was `conflicting types for func_XXXX` found only by hand-splicing and
  reading real cc1 stderr). `func_80166994` ×3 (1,107) and `func_8016A290` ×4 (1,136) still CC1-FAIL
  after the TU carry — a further preamble class, not yet classified.
  **⚠️ FULL R22 DEFERRED, DELIBERATELY:** `make clean` wipes `asm/`, and the concurrently-running
  BF14 agent reads `asm/ov_SC03_116/…/func_8017BF14.s` on every probe. This batch changed only
  `src/*.c` (no config), so `make check-all` (140/140, run) is sound here; **the full clean R22 must
  still be run once the agent finishes.**

- **⚖️ 2026-07-25 (SESSION-19) — THE COLD-START EXPERIMENT: `func_8017BF14` (4,763 ins) reached
  4763/4763, **45 mismatched** (99.06% byte, 99.94% structural) — NOT a match, and the honest answer
  to Drew's effort question. It also REFUTED THE PREMISE I GAVE IT (§79).**
  Verified independently: `match_one` → `mine=4763 target=4763, 45 mismatched, OPCODE-MIXED`. Agent
  respected its sandbox (only `.run/giants/`). **Nothing banked — 45 ≠ 0, and the byte-gate is the
  sole arbiter (G3/P9).**
  **MY BRIEF'S "NO MATCHED RELATIVE — A GENUINE COLD START" WAS WRONG, BY CONSTRUCTION.** I picked this
  target partly BECAUSE §71's callee-set fingerprint returned jaccard 0.00 against every matched giant.
  But **this function makes ZERO `jal` calls**, so its callee fingerprint is EMPTY and §71 *cannot
  fire* — 0.00 meant "cannot answer", not "no relative". Grepping the target's **data** symbol
  `D_800A5E60` found the matched `func_8017BEBC` immediately: `func_8017BF14` is the **4-light-box**
  member of the very renderer family whose 3-box sibling `func_8017D960` we matched hours earlier.
  **⇒ §79: when §71 returns an empty/zero-overlap callee set, fall back to DATA-symbol fingerprinting.
  An empty fingerprint must never be allowed to become a cold-start brief.**
  **NEW LEVER — THE FRAME LAYOUT IS A DECLARATION-ORDER ORACLE (§79).** gcc-2.7.2 assigns stack slots
  to spilled pseudos in pseudo-number order, and pseudo numbers follow first use ≈ declaration order —
  so **the target's frame map reads back its source's declaration order**. Moving ONE line (`f0..f3`
  after `pkt`) took 73% → 84% structural and brought **all 127 slots** into exact correspondence.
  Counterpart to §78's asm→source reads. Automatable (`.run/giants/bf14_slots.py`).
  **§76 CONFIRMED AT SCALE:** the entire **−62 length residual was ONE allocno-class decision**
  (`s32 c0..c3` declared inside the cull blocks ⇒ 1-death local allocnos ⇒ `global.c:668-671` removes
  those regs from the global pool ⇒ `r1lo` spills): 52% → 93%. An `__asm__` ref-dial reached the same
  spill and scored WORSE — **declaration scope beat the ref dial, again.**
  **PIN NUANCE:** pins are SAFE on a 0-`jal` function (§74's caller-saved-across-a-call hazard cannot
  arise); 4 pins took 94% → 99%. **But §72 held — pins 5 and 6 made it worse.**
  **THE EFFORT ANSWER, HONESTLY:** xHigh from a genuine cold start on a 4,763-ins giant bought the
  decode, the exact length, the exact frame and 99.06% — but **did not close**. The residual is **three
  register-grant ties, zero structural divergence**. Budget a SECOND pass for anything this size: the
  first buys structure, the last ~1% is register grants. Named next move: **variable REUSE across
  `c0..c3`/`a0v..a3v`** — the one §76 lever class this pass never reached.
  Artifacts: `s19_func_8017BF14_b1.c` (45/4763) + a **pin-free fallback at 789/4763 that is 100%
  structural** + `s19_bf14_report.md` (~40-row do-not-re-buy table, 4 refuted diagnoses).

- **🏆🏆🏆 2026-07-25 (SESSION-19) — `func_8017BF14` (4,763 ins) CLOSED IN ROUND 2: 45 → 0.
  The 4th behemoth of the session, and the largest single function matched in the project.**
  `45 → 37 → 33 → 21 → 11 → 3 → 2 → 0`, reproduced 3× from independent work dirs. **Verified
  independently (R14):** `match_one` → **MATCH (4763 ins)**; `harvest_verify --binary ov_SC03_116`
  → **BYTE-IDENTICAL**. (Agent was interrupted mid-run by a weekly API limit and RESUMED FROM ITS
  TRANSCRIPT — its round-2 harness `bf14_mk2.py`/`bf14_sw2.sh` survived intact, so nothing was
  re-derived.)
  **⚠️ THE PROCESS CORRECTION THAT MATTERS MORE THAN THE MATCH (→ §80): A DO-NOT-RE-BUY ENTRY IS
  SCOPED TO ITS BASE, NOT TO THE FUNCTION.** Three of round 1's ~40 carefully-measured negatives
  **INVERTED** on round 2's base — the same edit (`qsingle23`) measured **1,040 mismatched on the
  45-base and 11 on the 21-base**. Re-testing the round-1 negative list cost **~20 seconds** and
  produced **three of the seven winning levers**. **A do-not-re-buy table records `(edit, base) →
  result`, NOT `edit → useless`; after any lever that moves the base materially, RE-RUN THE NEGATIVE
  LIST.** This retroactively qualifies every such table in the cookbook (§45, §60b, §75a, §76, §78,
  §79) — they are starting hypotheses at the base where they were taken, not closed questions.
  Concrete instance: round 1 measured "removing the `va→$t2` pin costs 4% elsewhere" ⇒ *keep the pin*;
  on a base with `c0..c3` at function scope, **removing those pins is worth 21→13** — opposite
  conclusion, same experiment.
  **MY FLAGGED "#1 MOVE" LOST, AND THE FAILURE IS THE FINDING.** I briefed variable REUSE (§45-A /
  RC-14) as the #1 lever because it took `func_8017F510` from 97→10. Swept in full here: **every
  merge lost, 43–3294 across 8 merges.** Reason: **the TRI and QUAD grants did not differ by RANK,
  they differed by IDENTITY — two independent allocno sets, and re-ranking inside one set cannot fix
  a two-set problem.** Diagnose ranking-vs-identity BEFORE reaching for a merge. The actual fix
  (`s32 c0,c1,c2,c3;` at **function** scope, 33→21) was **read off the two matched relatives**
  (`b5:310`, `b4:338`) and confirmed against the target (its TRI grants are identical to its QUAD
  grants) — **the 4th time today that reading a matched relative beat the clever lever.**
  **THE PIN'S HIDDEN COST, WITH A CITATION:** `combine_regs`' hard-register branch
  (`local-alloc.c:1795`, reached from `:1295` with `already_dead == 0`) records the pinned register in
  **`qty_phys_sugg` UNCONDITIONALLY — no death guard**. A pin doesn't merely *prefer* a register, it
  invites local-alloc to tie producer chains into it. New cure **R7**: a zero-byte `__asm__` ref that
  keeps the pinned value LIVE PAST the temp so `find_free_reg` can't honour the suggestion — closed
  the last 2 ins, and was necessary because `c1→$a0` is uniquely load-bearing (it is what spills
  `r1lo`; every alternative pin lost 64 ins).
  **§78's ATTRIBUTION PRIMITIVE RUN AND REPRODUCED:** under `-fno-schedule-insns`,
  `-fno-schedule-insns2`, and both, the order was **unchanged** ⇒ the rgb-accumulator transposition
  was never a `sched.c` decision (a 3-statement accumulator pins the value, so no scheduler *could*
  hoist the `or` above the `sw`). Changing the grant fixed the order for free.
  **COLD-START ECONOMICS, NOW COMPLETE:** round 1 = decode + exact length + exact frame + 99.06%;
  round 2 = the last 45, and far cheaper than round 1. **Budget TWO passes at this size; do not read a
  99% round-1 result as a stall.** Also found a **5th original-source copy-paste artefact** (QUAD
  vertex-1 box-3 y-axis accumulates into `a2v` while its kill branch still says `a3v`).

- **🏆 2026-07-25 (SESSION-19) — `func_8017C954` (1,194 ins) MATCHED **AND NOW BANKED** — the 3-deep
  carve chain CLEARED (§81). Root cause was a one-line tool defect, not config.**
  **RESOLUTION (each step byte-gated BEFORE the next was built on it):** a one-line fix to
  `jr_isolate_all._engine_types()` → `jr_isolate_all --only func_8017C954` (2 fns / 1 object, NOT the
  bare 47-fn resegment) → **byte-identical `b7b0d4ae`** → `jtbl_carve --func func_8017C954` (44-piece
  carve set + interleave order) → **byte-identical** → `harvest_verify` → **VERIFIED BYTE-IDENTICAL** →
  **R22 clean-fleet 140/140**, `tools-health` OK. distinct-code → **3,844,100**.
  **THE DEFECT: a shared type that was PRESENT but INVISIBLE.** `_engine_types()` harvested shared type
  names with four patterns (`typedef … X;` · `} X;` · forward-decl `struct X;` · fn-ptr typedef); a
  **tagged definition with a body** — `struct PW8017E6D8 { int w; } __attribute__((packed));` at
  `engine_types.h:658` — matches **none** of them. **Measured: 77 such tags in `engine_types.h` were
  invisible to the check.** One added pattern fixed it.
  **WHY IT COST 20 MINUTES INSTEAD OF A MYSTERY BYTE-DIFF THREE PHASES LATER:** the Phase-26 audit had
  already converted this predicate's *silent drop* into a **loud refusal**. The original bug dropped
  **4,040 col-0 decls, 683 of them function PROTOTYPES** — and a dropped prototype is a **silent
  byte-changer** (C89 implicit `int f()`; return type drives delay-slot fill here). The refusal named
  the exact symbols AND the remedy. **A loud "I cannot place this" is worth far more than a green
  build** — the audit paying for itself, live.
  *(Original entry, for the record: the blocker was a 3-deep build-infra chain, named exactly, NOT a
  matching problem.)*
  Opus 5 @ xHigh cracked it: `match_one` → **MATCH (1194 ins)**, 100% on every region, progression
  1129 → 1069 → 37 → 28 → MATCH. **I verified it independently.** It is the matched base
  `func_8017CA80` (952) **+ two deltas**: a 14-ins prologue computing two replicated grey colour words
  from `D_801DCCA0`, and a **fifth switch arm** (`case 2`/`case 3` split, proved against the real jump
  table) emitting a POLY_FT4 plus a 7-word subtractive overlay.
  **⛔ THE WHOLE-BINARY GATE SAID `DIFF` — and it is RIGHT.** This is a **jr (jump-table) function**
  (`jr $v0` at .s:409; its table is `jtbl_801DB70C` in `asm/ov_SC06_029/data/tail21.data.s`). Matching
  the C makes gcc emit that jtbl into `.rodata` while the raw copy stays in the data tail ⇒ duplicate +
  wrong address. **`match_one` masks jal/HI16/LO16, so it CANNOT see this** — exactly the §53 carve law.
  **THE CHAIN, each step failing LOUD with its own remedy (good tooling, R32/R35):**
  1. `harvest_verify` → **DIFF** (not PLUMBING — a real byte difference).
  2. `jtbl_carve ov_SC06_029 --func func_8017C954` → refuses: subseg `ov_SC06_029_jr_8017AE2C` would
     host **NON-CONTIGUOUS** `.rodata` carves (0xb3468 and 0xb35b4) — one object cannot leave a gap for
     the unmatched jtbl between them. Remedy it names: isolate into its own code subseg first.
  3. `jr_isolate_all ov_SC06_029 --dry-run` (47 jr in 21 objects) → **REFUSES**: 2 file-scope decls
     (`extern struct PW8017E6D8 D_801E1EC4;` / `…EC8;`) could not be placed, and it will not emit a
     region that silently omits them — *"a dropped prototype is a SILENT BYTE-CHANGER"* (in C89 an
     undeclared function is implicitly `int f()`, and return type drives delay-slot fill here).
     Remedy it names: carry the naming type (`file_scope_types`) or add it to `engine_types.h`.
     **NB `struct PW8017E6D8` IS already in `engine_types.h:658`** — so this looks like a placement-logic
     gap, not a missing type. That is the precise next thing to check.
  **⇒ BANKING WAS A BOUNDED BUILD-INFRA TASK (T2 — config resegment ⇒ full R22), NOT more matching —
  and Drew directed it be cleared first; it was. Artifacts:**
  `.run/giants/s19_func_8017C954_b1.c` (~160-line dossier) + `s19_c954_report.md` + the harness
  `c954_{cc,probe,probe2,score,sweep,sw}.sh` / `c954_{full,side,reg,alloc,slots,regmap,mk}.py`.
  **AGENT FINDINGS WORTH KEEPING:** **§80(i) confirmed twice more** — `x_e1swap` measured *exactly
  neutral* then later paid −2; the `za` lever measured *worse* and became necessary two levers later.
  **New diagnostic proposed:** when a residual is "a whole block of registers renamed by ONE SLOT",
  read the `.greg` `;; N conflicts:` **and** `;; N preferences:` lines for the block's top allocno — a
  *missing* hard-reg conflict plus a *new* copy preference is the signature of a one-slot slide, one
  dial away rather than forty bugs. The per-region scorer `c954_reg.py` is the reusable tool.
  **HONEST CAVEAT FROM THE AGENT:** its lever 1 is a hand-placed byte-free `__asm__` register-clobber
  dial, not a construct the original author would have typed; 14 natural spellings were tried and
  measured. The bytes are unaffected but the true source shape is unfound — the report names the exact
  next probe.

- **🏆 2026-07-25 (SESSION-19) — BEHEMOTH #6 `func_8017C730` (1,061 ins) CRACKED **AND BANKED** via the
  §81 carve chain. Two new SOURCE-SHAPE ORACLES (§82) — the best of the session.**
  **Verified independently (R14):** `match_one` → **MATCH (1061 ins)** (agent re-matched 3× from clean
  runs; 100% register-masked AND register-kept, all 10 regions, frame `0x270` exact). Carve chain clean
  first try: `jr_isolate_all --only` → **byte-identical `cacaf7c2`** → `jtbl_carve` (43-piece set) →
  **byte-identical** → bank → **R22 clean-fleet 140/140**, `tools-health` OK.
  **WHAT IT IS:** the matched base `func_8017CA80` + **camera height-band cull + distance-driven CLUT
  fade**. `func_8004974C` (TransposeMatrix) sits in a 36-ins prologue deriving a Y band; the part-level
  `lim >= g.otz` cull is GONE (no `gte_stszotz` at all); flat arms gain an `sz < lim` near-plane cull.
  The base+one-extra-callee fingerprint predicted this exactly.
  **§82 ORACLE 1 — A DUPLICATED `addiu $aN,$sp,K` ACROSS A `jal` MEANS THE BLOCK WAS INLINED.** `&X` on
  any non-first local always creates a pseudo and CSE always merges two of them (`expr.c:6260`
  ADDR_EXPR → `force_operand(..., NULL)`; the exception is virtual-stack-vars offset 0). So if the
  target re-materialises the SAME stack address at two sites separated by a `jal`, CSE was *prevented*
  from merging them ⇒ they were not in the same function body. **17 non-inline spellings failed; a
  `static inline` helper reproduced the prologue BYTE-FOR-BYTE first try.** Reusable probe that found
  it: scan the ~1,200 built objects for that duplicated-`addiu` signature in NON-`INCLUDE_ASM`
  functions (i.e. known-real source shapes).
  **§82 ORACLE 2 — SCALAR vs AGGREGATE DECIDES *WHEN* A STACK SLOT IS ALLOCATED:** lazily at first `&`
  for a scalar, **at declaration** for an aggregate. The six GTE result words had to be six separate
  `long`s, not a struct — only then do they land after the inlined helper's temps (0x118..0x12F) and
  the frame comes out `0x270`. **Second-order:** it also flips `MEM_IN_STRUCT_P` (§30's `/s`) — with one
  word a fixed-address scalar, `((PolyF3*)pkt)->rgbc` stops aliasing it, so a store needed respelling
  `*(u32 *)(pkt + 4)` to keep the target's `nop`. **A scalar-vs-struct choice is simultaneously a
  frame-layout AND an aliasing decision.**
  **BANKING FOOTNOTE (§75a class A, one line):** the first bank was rejected `conflicting types for
  'ApplyMatrixSV'` — draft `(MATRIX2 *, SVECTOR2 *, SVECTOR2 *)` vs the TU/fleet canon
  `(void *, void *, void *)` (**2,286 of 2,835 sites**). Conforming the decl is byte-neutral (pointer
  args pass identically) and banked first try. **On a jr function expect BOTH gates to speak: the carve
  chain answers the jump table, §75a answers the declarations.**
  **Also reproduced:** §78 (reuse a busy variable — `t32 = mid` matched where a fresh temp did not) ·
  **§80(i)** (a lever went −8 ins → *exactly neutral* as the base moved) · §72 (a `register` pin made it
  worse).
  **AGENT'S OWN CAVEAT, recorded not hidden:** one zero-byte `__asm__ volatile ("" : : "r"(mnc))`
  survives, keeping a provably vestigial `mnc = hmid` alive that `flow.c` would delete (costing 10 ins
  and the 0x130 spill slot). It emits nothing and the compile is 1061 exact, but it is a documented
  stand-in — 12 natural spellings measured, all DCE'd; the next probe is named in the report.
  Artifacts: `s19_func_8017C730_b1.c` (~140-line dossier, 12 levers each with a drop-one ablation) +
  `s19_c730_report.md` (~40-row do-not-re-buy table) + `c730_{cc,probe,probe2,score,sweep,sw,sw2}.sh` /
  `c730_{reg,side,mk,abl}.py` (**`c730_abl.py` = a new drop-one ablation matrix**).

- **◐ 2026-07-25 (SESSION-19) — `func_8017C730` @ **ov_SC03_013** (the h_seq sibling): standalone
  **MATCH (1061 ins)** achieved, **NOT banked** — a precise, cheap handoff.**
  With the ov_SC03_010 exemplar banked, I probed the sibling. `family_remap` alone: **−56 LENGTH-DRIFT**.
  **§77's own text predicted the cause verbatim** — *"any preamble construct that is not an `extern` —
  `#define`, a file-scope `typedef`, **a `static` helper**"*. The exemplar uses
  `static inline void bandsetup(...)` (the §82-oracle-1 inlined helper) and the remap carried **none**
  of it. Carrying helper + its 5 externs: **−56 → −34**. Carrying the **whole 2,993-line region file**
  as preamble: **MATCH (1061 ins)**.
  **BUT THE FULL-FILE CARRY IS WRONG FOR BANKING** and that is my error: it is correct for a standalone
  `match_one` compile and collides wholesale in the real TU. Gate → **PLUMBING**, reported as
  `conflicting types for 'memcpy'` — **the §58 red-herring** (a warning from an unrelated TU position;
  the real cause needs a hand-splice + real cc1 stderr, exactly as SESSION-14 documented).
  **NAMED NEXT STEP (cheap):** build the **MINIMAL** preamble — the `bandsetup` helper + its 5 externs
  + the **18 `gte_*` macros** defined in that region file (helper+externs alone left −34, so the gte
  macros are the likely remainder) — then the **§81 carve chain**, because this sibling is ALSO a jr
  function (`jr` count = 1). Draft preserved: `.run/giants/s19_func_8017C730_SC03_013_nearmiss.c`.
  **⇒ §77 GAINED ITS 5th MEASURED VARIANT (`static` helper — NOW FOLDED INTO THE COOKBOOK, commit `commit:1027`) and a NEW COROLLARY: the right carry is the
  MINIMAL closure of what the body references, not the whole file — over-carrying trades a
  `match_one` failure for an in-TU collision.** My `s19_remap_tu.py`'s walk-back-to-previous-`}`
  heuristic also breaks on an **isolated region file**, where the preceding construct IS the needed
  helper (it returned a 1-line preamble).

> **🛑 SESSION-19 CLOSING CHECKPOINT (2026-07-25, Opus 5 @ xHigh) — FINAL. Fresh session safe here.**
> **No background job is running.** Tree clean (only R23 `db.*.gbf` churn — never staged).
> **R22 clean-fleet 140/140, run 12×** (the last after the `func_8017C730` bank). `make tools-health`
> → **OK**. **0 NON_MATCHING** (G4). dedup **1886 validated / 0 failed**, C1 coverage complete.
> HEAD `commit:1025`, **38 commits this session**. **Drew pushes** (R6/R20).
>
> ## FLEET
> **80.6% instr** (10,587,608 / 13,141,652) · **distinct-code 3,845,161 = 68.2%** · fn-count **89.18%**
> Session opened at **80.0 / 67.7 / 89.02**.
> **+31,649 distinct-code ins this session: 26,730 from SIX behemoths + 4,919 from the h_norm-remap
> pool. Every PROPAGATION win contributed +0 to distinct-code** — that split is the session's single
> most actionable finding.
>
> ## BANKED THIS SESSION
> | fn | ins | reach | how |
> |---|---|---|---|
> | `func_8014D4C0` | 84 | ×138 | §30#2 widen + the §73 PARAM axis |
> | `func_8014F3E8` | 32 | ×138 | §75 minority-spelling normalization + `dedup_extend` |
> | `func_80165CA0` | 99 | ×135 | §75b `ENGINE_SHB` (the carried-`#define` gap) |
> | `func_80174CB0` | 123 | ×135 | §75c the full §17a-1 pair (decl **and** call-site cast) |
> | 19 pool fns | — | ×1 | h_norm remap + the §77 preamble carry (**+4,919**) |
> | **`func_8017F510`** | **1,511** | ×1 | **BEHEMOTH — §76 allocno-class levers, pin-free** |
> | **`func_8017F5B4`** | **1,511** | ×1 | **BEHEMOTH — §40 remap off F510, ~0 agent tokens** |
> | **`func_8017D960` + 5-member family** | **3,338 ×5** | ×1 ea | **BEHEMOTH — §78; 4 first-try remaps = 16,690 ins** |
> | **`func_8017BF14`** | **4,763** | ×1 | **THE LARGEST MATCH IN THE PROJECT — cold start → 45 → 0 (§79/§80)** |
> | **`func_8017C954`** | **1,194** | ×1 | **BEHEMOTH — banked via the §81 jr-carve chain** |
> | **`func_8017C730`** | **1,061** | ×1 | **BEHEMOTH — §82 two source-shape oracles** |
>
> ## TEN COOKBOOK ENTRIES, §73–§82 — ALL FROM MEASUREMENT
> **§73** a def-side self-decl conflict has TWO axes: RETURN (fleet widen, T2/R22) and PARAMS (casts at
> each use, T0) · **§74** the pin-safety audit (the corrupting form is a CALLER-SAVED pin spanning a
> `jal`) · **§75** census the carried extern before believing an exclusion message; prefer a
> majority-spelling source overlay; always `--recover` · **§75a** the three exclusion classes + the one
> grep that discriminates them · **§75b** extraction lifts `extern`s but NOT `#define`s (signature = a
> LINK error) · **§75c** class B needs the PAIR, decl **and** call-site cast · **§76** the allocno CLASS
> is the dominant regalloc lever, reachable ONLY via declaration scope + variable reuse · **§77** every
> extraction tool carries a NARROW preamble set — **5 measured variants** (`#define` · multi-line
> `typedef` · `extern` above a `#define` · the exemplar's `#include`s · a **`static` helper**, the only
> one that gives NO diagnostic — just a negative length drift) + the corollary: carry the **MINIMAL
> TRANSITIVE CLOSURE** of what the body references, not the whole file (over-carrying trades a
> `match_one` failure for an in-TU collision, measured) · **§78** a LENGTH/ORDERING diff can be a register grant in disguise; `fold` never leaves a
> literal first in an `|` chain · **§79** the frame layout is a declaration-order oracle; DATA-symbol
> fingerprinting when §71 cannot fire · **§80** a do-not-re-buy entry is scoped to its BASE; the pin's
> unconditional `qty_phys_sugg`; diagnose ranking-vs-identity before a merge · **§81** the 3-step
> jr-carve chain and why `match_one` cannot see the problem · **§82** a duplicated `addiu $aN,$sp,K`
> across a `jal` means the block was INLINED; scalar-vs-aggregate decides WHEN a stack slot is allocated.
>
> ## THE THROUGH-LINE
> **Almost every cap this session was our own tooling or my own use of it, not gcc.** A missing
> `--recover` flag · a minority-spelling source overlay · four preamble-carry gaps · a shared type
> present-but-invisible to its own checker (77 tags) · `dedup_extend` stripping a load-bearing include
> from 135 binaries · and four of MY OWN claims that collapsed under checking ("102 unmatched" → 13;
> "56,267 ins" → 8,114; "the identical class" → different symbols per overlay; "a genuine cold start" →
> §71 *couldn't fire* and the relative was one grep away). **In every case I read a tool's output
> without first asking whether the tool could answer the question** — R35 aimed at myself.
>
> ## ▶ START HERE NEXT SESSION — the recommended order, with reasons
> **⚠️ SUPERSEDED BY THE SESSION-20 CHECKPOINT AT THE END OF THIS FILE — item 1 below is DONE
> (banked 2026-07-26). Items 2–6 stand. Read the SESSION-20 block, not this one, for the next move.**
> **1. `func_8017C730` @ ov_SC03_013 — FINISH IT FIRST (~30 min, +1,061 ins).** The match ALREADY
> EXISTS (standalone `match_one` MATCH, 1061/1061). This is pure integration, no drafting, no agent:
> build the **MINIMAL** preamble — `bandsetup` (the `static inline` helper) + its 5 externs + the
> **18 `gte_*` macros** from `src/ov_SC03_010/ov_SC03_010_jr_8017C730.c` — then run the **§81 carve
> chain** (`jr_isolate_all ov_SC03_013 --only func_8017C730` → gate → `jtbl_carve` → gate →
> `harvest_verify` → full R22). Draft: `.run/giants/s19_func_8017C730_SC03_013_nearmiss.c`.
> **Do NOT re-carry the whole region file** — that gives a standalone MATCH that fails the real gate
> (§77 corollary, measured).
>
> **2. THEN `func_80183814` (5,122 ins, ov_SC07_006) — the biggest prize left, one Opus 5 agent @ xHigh.**
> **Set expectations honestly: the family bonanza is OVER.** All six behemoths banked this session
> belonged to ONE renderer family with matched relatives bracketing them — that is why 5 of 9 levers
> were *readable* rather than *discoverable*. `func_80183814` has **0 fingerprint overlap** with that
> family and **37 distinct callees**; it is a different subsystem, and none of §76–§82's family levers
> transfer for free. It is `jr` (⇒ §81 chain to bank) and only *mapped* from a prior session (666
> drafted, a 35× repeated template found). **Budget TWO passes** — expect the `func_8017BF14` shape
> (round 1 = decode + length + frame + ~99%; round 2 = the last few), NOT the `func_8017C954`
> near-one-shot. **A 99% round 1 is on-plan, not a stall.**
>
> **3. Then `func_8017D2DC` (1,586, ov_SC01_001, 32 callees, jr) and `func_8017DC1C` (1,518,
> ov_SC07_006, jr).** ⚠️ **`func_8017DC1C` has ZERO callees — §71 CANNOT fire on it.** Use §79
> DATA-symbol fingerprinting (SHARED symbols only, `< 0x80128158`; and read a MATCHED relative's
> fingerprint from its **banked C**, never from `asm/`, which no longer has its `.s`). A 0.00 from §71
> on a leaf means **"cannot answer"**, not "no relative" — that mistake cost me a whole agent brief
> this session. `func_8017D2DC`'s 32 callees mean §71 IS usable there; run it before assuming.
>
> **If the behemoths stall, the next-best lever is item 4 below (fresh cracks) — but note that
> behemoths were the ONLY thing that moved distinct-code this session (+26,730 of +31,649).**
>
> ## ⚠️ OPEN ACTIONS, ranked
> 1. **`func_8017C730` @ ov_SC03_013** — standalone **MATCH (1061)** already achieved; banking needs the
>    **MINIMAL** preamble (the `bandsetup` static-inline helper + its 5 externs + the **18 `gte_*`
>    macros**; helper+externs alone left −34) then the **§81 carve chain** (it is also a jr fn). Draft:
>    `.run/giants/s19_func_8017C730_SC03_013_nearmiss.c`. **+1,061 ins, cheap.**
> 2. **4 BEHEMOTHS REMAIN / 9,287 ins:** `func_80183814` 5,122 (ov_SC07_006, 37 callees, mapped-only,
>    different subsystem) · `func_8017D2DC` 1,586 (ov_SC01_001, 32 callees) · `func_8017DC1C` 1,518
>    (ov_SC07_006, **0 callees** ⇒ use §79 DATA-symbol fingerprinting, NOT §71) · `func_8017C730` 1,061
>    (ov_SC03_013, = item 1). **Behemoths are the PROVEN distinct-code lever (+26,730 today).**
> 3. **The h_norm-remap residual, 3,195 ins, causes NAMED:** `func_8017D5C0` (952) matches standalone,
>    gate reports the **§58 memcpy red-herring** (needs a hand-splice + real cc1 stderr);
>    `func_80166994` ×3 + `func_8016A290` ×4 still CC1-FAIL after the TU carry.
> 4. **Fresh-crack wave** (Task 4) — 48 families / 0.62pp with a cached member + the `ov_SC06_018`
>    prefetch (101 uncached substantial stubs). Breadth ⇒ prompt for `/effort ultracode` (R26/R27).
> 5. **Permuter backlog sweep** (Task 5) under the tightened §60b rule; fix the 2 carried Phase-22
>    grinder bugs first.
> 6. **Audit the other `*_revert`-shaped undos** for the §61 inverse-transform bug — it has now bitten
>    twice (SESSION-14, SESSION-19).
>
> ## ⚠️ METHOD TRAPS THAT COST ME TIME — DO NOT REDISCOVER
> - **§71's callee fingerprint CANNOT fire on a leaf fn** (0 callees ⇒ empty set ⇒ 0.00 reads as "no
>   relative"). Fall back to §79 DATA symbols.
> - **Compare SHARED symbols only** (`< 0x80128158`): per-overlay `D_801?????` names never match across
>   overlays.
> - **A MATCHED function has no `nonmatchings/*.s`** — read its fingerprint from its **banked C**.
> - Each of the three above silently returns **0.00**, which looks exactly like a finding.
> - **On a jr function, `match_one` MATCH is not the end** (§81) — and expect BOTH gates to speak: the
>   carve chain answers the jump table, §75a answers the declarations.
> - **`jr_isolate_all` / `jtbl_carve`: ALWAYS `--only <func>`.** Bare resegments every jr in the overlay
>   (47 across 21 objects on ov_SC06_029); `--only` touched 2 in 1.
>
> ## BEHEMOTH ECONOMICS, MEASURED
> Round 1 on a 4,763-ins cold start bought the decode + exact length + exact frame + 99.06%; **round 2
> bought the last 45 and was CHEAPER.** **Budget two passes at that size; do not read a 99% round-1
> result as a stall.** And **reading a matched relative beat the clever lever I proposed FIVE times** —
> crack the smaller family member first; it is a lever library for the larger one.
>
> **⚠️ HAZARDS:** `dedup_propagate --auto-from` re-macroizes de-macroized sites (`--check-only` first,
> targeted `--addr` only) · **`dedup_extend` refuses a dirty tree (H4)** · `p16_permute.setup` WIPES
> `.run/permuter/<fn>/` · `.run` subdirs are largely untracked (`.run/giants/*.{c,md,sh,py}` ARE
> allowlisted) · sig names lowercase, splat `.s` UPPERCASE · **never `make clean` while an agent is
> running — it wipes `asm/`, which agents read on every probe.**
> **DO NOT close P29 on ROI** — burn-down floor still undetermined.

---

- **✅ 2026-07-26 (SESSION-20) — `func_8017C730` @ ov_SC03_013 BANKED (+1,061 ins). The SESSION-19
  handoff's item 1, closed exactly as specified — no drafting, no agent, no new levers.**
  **The chain, each step byte-gated before the next was built on it (§81):**
  1. **Minimal preamble built** per §77's corollary — the 18 `gte_*` macros + the 5 externs
     (`ReadRotMatrix`/`PushMatrix`/`PopMatrix`/`func_8004974C`/`ApplyMatrixSV`) + the `bandsetup`
     `static inline` helper = **519 lines, vs 2,993 for the whole-file carry.**
     `match_one` → **MATCH (1061 ins)**.
  2. `jr_isolate_all ov_SC03_013 --only func_8017C730` → 2 fns in 1 object (same blast radius as the
     exemplar) → `make extract && make build` → **BYTE-IDENTICAL `7042bc71`**.
  3. `jtbl_carve ov_SC03_013 --func func_8017C730` → single-table carve (the exemplar's `_jr_8017C730`
     object carries no `JTBL_PADS`, so no `--like` needed), 44-piece interleave →
     **BYTE-IDENTICAL `7042bc71`**.
  4. `harvest_verify --binary ov_SC03_013 --drafts .run/drafts-s20-c730 --chunk 1` →
     **verified 1 / failed 0**, final SHA `7042bc71` **BYTE-IDENTICAL**.
  5. **R22 clean-fleet from a genuinely clean tree: `make clean` + extract-all (139+main) +
     `check-all` → 140 passed, 0 failed of 140.** `make tools-health` → **OK**;
     dedup **1886 validated / 0 failed**, C1 coverage 239,604/239,604; **0 NON_MATCHING** (G4).
  **FLEET:** instr-weighted 10,587,608 → **10,588,669 / 13,141,652 = 80.6%** · distinct-code
  3,845,161 → **3,846,222 = 68.3%** (+1,061, i.e. **+0.1pp, all of it distinct** — a behemoth-class
  bank, not a propagation) · fn-count **89.18%**.
  **NO §75a class spoke.** SESSION-19 predicted "expect BOTH gates to speak on a jr function"; here the
  carve chain answered the jump table and the declarations were already clean, because the exemplar's
  `ApplyMatrixSV(void*,void*,void*)` canon fix (the §82 banking footnote) was carried in the draft.
  **⇒ §77's ladder is CLOSED with all four rungs measured** (`-56` → `-34` → MATCH-but-uncommittable
  → **MATCH + BANKED**), and the corollary is now a banked fact rather than a prediction.
  **NEW (cookbook §77, distilled in-session per R30): the CANDIDATE gate and the REAL gate need
  DIFFERENT preambles.** `match_one` compiles standalone (`cpp -Iinclude`, no `engine_core.h`), so a
  shared-type body gives `'PolyFT4' undeclared` + a cascade of `parse error before ')'` — which looks
  exactly like a broken draft and is not one. The real TU gets those types free via
  `engine_core.h` → guarded `engine_types.h`. **The types header belongs in a throwaway PROBE COPY,
  never in the banked draft.**
  **⚠️ AND THAT SHORTCUT HAS ALREADY LEAKED — A PORTABILITY DEFECT NO BYTE-GATE CAN SEE.**
  **21 git-tracked source files / 23 lines** hardcode
  `#include "/home/musashi/bfm-decomp/src/shared/engine_types.h"`. **Verified all 21 are semantically
  guarded no-ops** (each has `#include "../shared/engine_core.h"` at line 2, which already pulls the
  guarded header — so deleting them is byte-neutral and R22-provable). **But `cpp` must still FIND that
  literal path, so those 21 TUs cannot preprocess on any clone not at `/home/musashi/bfm-decomp`** —
  directly against the project's reproducibility criterion ("a stranger with their own dump can
  `make extract && make build && make check` green"). Invisible to every gate here because the path
  exists on this machine: **R34's null-oracle shape, aimed at portability instead of coverage.**
  **NOT ACTED ON — it is outside this task's approved scope (P5d) and touches 21 files fleet-wide;
  proposed to Drew as the next task.** File list: `grep -rln '#include "/home/musashi' src/`.
  *(Housekeeping done in passing: a stale `asm/ov_SC03_013/nonmatchings/ov_SC03_013_jr_8017C730/`
  dir (74 `.s`, from a reverted earlier experiment, config had no such subseg) was removed before the
  baseline build — the Phase-20 R22 corollary, a reverted config leaves stale asm behind.)*

> **🛑 SESSION-20 CHECKPOINT (2026-07-26, Opus 5 @ xHigh) — fresh session safe here.**
> **No background job is running.** Tree: the Phase-29 bank is committed; only the R23 `db.*.gbf`
> churn is unstaged (never stage it). **R22 clean-fleet 140/140**, `tools-health` **OK**, dedup
> **1886/0**, **0 NON_MATCHING** (G4), main `143dbb89`, ov_SC03_013 `7042bc71`.
> **FLEET: 80.6% instr · 68.3% distinct-code · 89.18% fn-count.**
>
> ## ▶ START HERE NEXT SESSION
> **The SESSION-19 handoff's item 1 is DONE.** Its items 2–6 stand unchanged and are still the ranked
> list — re-read that block for the full reasoning (behemoth economics, the §71-cannot-fire trap, the
> `--only` rule, the hazards). The order from here:
> **1. `func_80183814` (5,122 ins, ov_SC07_006)** — the biggest prize left; one Opus 5 agent @ xHigh,
>    **budget TWO passes**; 0 fingerprint overlap with the renderer family (37 callees, different
>    subsystem — none of §76–§82's family levers transfer free); it is `jr` ⇒ §81 chain to bank.
> **2.** `func_8017D2DC` (1,586, ov_SC01_001, 32 callees ⇒ §71 IS usable) and `func_8017DC1C`
>    (1,518, ov_SC07_006, **0 callees ⇒ §71 CANNOT fire, use §79 DATA-symbol fingerprinting**).
> **3. NEW — the 21-file absolute-include portability defect** (above). Byte-neutral, R22-provable,
>    cheap; needs Drew's go-ahead since it touches 21 files. Good "cold-start" task for a fresh
>    session: `grep -rln '#include "/home/musashi' src/` → delete the line → R22.
> **4.** Fresh-crack wave (Task 4) — 48 families / 0.62pp cached + the `ov_SC06_018` prefetch (101
>    uncached substantial stubs). Breadth ⇒ **prompt for `/effort ultracode`** (R26/R27).
> **5.** Permuter backlog sweep (Task 6) under the tightened §60b rule; fix the 2 Phase-22 grinder
>    bugs first. **6.** Audit the other `*_revert`-shaped undos for the §61 inverse-transform bug.
>
> **METHOD NOTE ADDED THIS SESSION:** a `match_one` CC1-FAIL on a shared-type body is a **preamble
> report about the PROBE**, not a verdict on the draft — prepend `engine_types.h` to a scratch copy
> and re-run before touching a single lever (cookbook §77).
> **DO NOT close P29 on ROI** — burn-down floor still undetermined.

---

## 📌 PhaseEnd CARRY ITEMS (Drew, 2026-07-26 — do NOT lose these at close)
> Deferred deliberately, with Drew's sign-off. The PhaseEnd synthesis must surface each one
> (either as a Deviation, a Notes-for-Future-Phases entry, or a proposed next-phase task).

1. **The absolute-include PORTABILITY DEFECT — 21 git-tracked files / 23 lines.**
   `#include "/home/musashi/bfm-decomp/src/shared/engine_types.h"` is hardcoded in 21 overlay region
   files. **Verified byte-neutral to remove** (all 21 carry `#include "../shared/engine_core.h"` at
   line 2, which already pulls the guarded `engine_types.h`, so each absolute line is a semantic
   no-op). **But `cpp` must still FIND the literal path ⇒ those 21 TUs cannot preprocess on any clone
   not at `/home/musashi/bfm-decomp`** — a direct hit on the project's reproducibility criterion
   ("a stranger with their own dump can `make extract && make build && make check` green from README
   alone", PROJECT_CONTEXT "What Success Looks Like"). **Invisible to every byte-gate** because the
   path exists on this machine — R34's null-oracle shape aimed at portability rather than coverage.
   **Drew's call (2026-07-26): leave it for now, handle later — note it at PhaseEnd.**
   Fix: `grep -rln '#include "/home/musashi' src/` → delete the line → full R22. Root cause + the
   prevention rule are in cookbook §77 ("the CANDIDATE gate and the REAL gate need DIFFERENT
   preambles" — the types header belongs in a throwaway probe copy, never in the banked draft).
   *Also worth a line at PhaseEnd: this is the second portability/documents-class defect the
   byte-gate could not see (the first was Phase-28's `yaml.safe_dump` registry destruction, H5).
   Both argue the same thing — R34 wants a non-byte oracle for the repo's NON-byte invariants.*

---

## ▶ THE MEASURED-ORDER PLAN (Drew-approved 2026-07-26, SESSION-20)
> Drew's framing: *"idiom discovery and shortcuts that could solve tons of funcs is the priority —
> why hand-grind everything if a smarter order can unveil a hidden secret."* **Agreed and confirmed**,
> with one calibration recorded honestly: in 21 phases **no single discovery ever cracked 50%** — the
> biggest (§31, the codegen map) converted expensive *discovery* into cheap *application*. The real
> shape is many 1–5% unlocks that compound; that is how the project went **3.8% → 80.6%**, and almost
> none of it came from grinding. So: order for discovery, but do not wait on a master key.

### The frontier, MEASURED 2026-07-26 (derived, not quoted — roadmap §2 is 11 days + ~11pp stale)
Fleet **80.6% instr · 68.3% distinct-code · 89.18% fn-count**, 140 binaries.
Remaining: **38,249 stubs · 2,552,983 weighted ins · 1,788,653 distinct ins (22,550 unique fns)**.

| bucket | measured | note |
|---|---|---|
| behemoths >1000 | **3 fns / 8,226 ins** | 1 in flight; 2 of 3 in ov_SC07_006 |
| 700–999 | **60 fns / 52,028 ins** | `func_8017BEBC` matched ×3, **stubbed ×56**; sibling-remap shape |
| 500–699 | **44 fns / 25,202 ins** | same shape |
| main EXE game code | **~59,765 ins / ~1,048 stubs** (0.7%) | not idiom-blocked — un-attempted |
| resident | **14 stubs** | classed dossier exists |
| walls | 2 permanent giants | model-relative, re-priced each phase |
| SDK residue | gsgap 5 + libapi 800c3 ~22 objs | mechanical → LINKED |
| 39 type-1 modules | **unquantified** | needs load-address RE first |
| sub-500 mass | **~38,000 stubs ≈ 94% of remaining** | avg ~79 ins/fn |
*(Scan floor: the band counts came from `.s` files >25 KB; the sub-500 figure is derived by
subtraction from corpus totals, not counted directly.)*
**The honest headline: the top four buckets are 5.7% of what is left. The endgame is ~38,000
small-to-medium functions — not behemoths, not walls.**

### THE OPEN QUESTION T0.1 EXISTS TO ANSWER
Do the remaining 22,550 distinct fns cluster into few structural families (⇒ one idiom + remap per
family = the 50%-class lever) or are they genuinely distinct (⇒ knowing grind)? **This has flipped
three times, every time on TOOLING, never on the compiler:**
P25 ~986 templatable families → P26 byte-refuted (3 probes **0%**), thesis declared spent →
P28 found one probe had a **missing carve**; same family run properly banked **89%**, and recorded
*"the ≈0% doctrine has NO surviving post-fix evidence"* → P29 T1 found the residual was an **-O0
compile-flag artifact, not a regalloc wall**: *"ceiling ≫ 3%; the pool is back on the table."*
**Nobody has re-measured it since, on fixed tools, over 140 binaries.** It is the highest-leverage
unknown in the project and it costs **zero agent tokens**.

### The order (approved)
- **T0.1 — frontier survey re-run on fixed tools, 140 binaries.** Decides T2.2's entire method.
- **T0.2 — bounded 8-member gate probe on the 700–999 sibling band.** Tests today's 40-min no-agent
  recipe at scale. **A number from the gate, never a projection** (R14) — this is the exact class
  where P26 read 0% off a broken tool and P28 read 89% off a fixed one.
- **T0.3 — triage the 1,670 untriaged backlog entries** (already paid for in CPU, invisible to planning).
- **T1.1 — `func_80183814`** (in flight). Its value is NOT its 5,122 ins: every prior behemoth was a
  *renderer*; this is a 21-case **state machine in a different subsystem** = the best available probe
  for a NEW idiom class. **T1.2 — `func_8017DC1C`** after it, *from its distilled levers* (same subseg,
  0 callees ⇒ §71 cannot fire ⇒ 80183814 is its only relative).
- **T2.1 — main EXE** (~59,765 ins, highest certain return). **T2.2 — the sub-500 mass**, method
  chosen by T0.1.
- **T3 — structural completeness**: the 39 type-1 modules (load-address RE first), resident's 14,
  SDK residue, walls re-priced, and the roadmap re-baseline.

### Why T0 leads
Not caution — **T0 is the cheapest thing that can invalidate everything below it.** If the families
template, T2.2 becomes "crack N exemplars and stamp" and most of that bucket evaporates. If they do
not, we grind *knowingly* instead of hopefully. R35 exists because this project has scoped whole
phases against broken readings twice; P26 spent its longest phase on a thesis its own tools had
already refuted.

### ⚠️ CONCURRENCY CONSTRAINT (while any behemoth agent is live)
Agents read `asm/` on **every** probe. **No `make clean`, no `make extract`** until the agent
resolves. T0.1/T0.3 only read sigs/configs and write `.run/` + `docs/` ⇒ safe concurrently.
**T0.2 builds ⇒ it waits for the agent.** Banking is exclusive per overlay for the same reason
(the §81 chain runs `make extract BINARY=<ov>`).

### Roadmap-to-100 gaps found while planning this (→ PhaseEnd carry)
1. **The 39 type-1 code modules appear in NO phase's task list** (checked P30/P31/P32). P27's
   PhaseEnd updated the completion *contract*; nobody added the *tasks*. §1 still reads "currently 136".
2. **B7 (behemoths) missed the biggest function in the game** — `func_80183814` (5,122) and
   `func_8017DC1C` (1,518) are absent because both live in `ov_SC07_006`, an overlay that did not
   exist in the fleet when the roadmap was written (2026-07-15). So **every B-bucket silently excludes
   the 4 late SC07 overlays**, and 4 of B7's 5 listed behemoths are now banked.
3. §2's numbers are stale — but the roadmap *declares* this (§0 + its own risk register), so that one
   is a documented limitation, handled correctly.

- **✅ 2026-07-26 (SESSION-20) — T0.1 FRONTIER SURVEY re-run on fixed tools over 138 overlay sigs.
  VERDICT: the family/templating thesis is ALIVE, the structure is STABLE, and there is a concrete
  224,410-ins zero-drafting pool. Zero agent tokens.**
  **Tool verified BEFORE its scan was trusted (R35).** `family_hseq.load()` derives its scope from
  `glob("src/ov_*")` + `glob(".run/sig.ov_*.jsonl")` — so it genuinely covered all **138** overlays.
  **But its generated header hardcoded "134"** — a doc that misreports its own scope reads exactly
  like a tool that missed 4 binaries (it cost me a real double-take). **Fixed to derive from the same
  glob `load()` scans, so it cannot drift.** *(Cosmetic defect, real confusion risk — the P28 `img_path`
  hardcode that hid 6,174 members was this same shape, only load-bearing.)*
  **Sigs were fresh** (11:47 today, regenerated by `make tools-health`).
  **STALE (2026-07-23, 134 ovs) → FRESH (2026-07-26, 138 ovs):**
  fleet 88.5/79.0/68.4% → **89.4/80.9/69.0%** · unmatched instances 40,620 → **37,201** ·
  unmatched ins 2,743,730 → **2,491,691** · **distinct classes 22,621 → 22,536 (only −85)** ·
  target families 2,721 → **2,688** · substantial 558 → **544** · with-matched-sibling 74 → **76**.
  **READ: 3,419 instances were banked but only 85 distinct CLASSES fell** — recent yield was
  propagation, not new classes. That is the same split SESSION-19 flagged, now visible fleet-wide.
  **THE ANSWER TO THE OPEN QUESTION — the family structure is NOT an artifact.** It survived the
  fixed-tool re-run essentially unchanged (2,688 vs 2,721 families). So the P25 reframe stands, and
  P26's "≈0%" remains unsupported post-fix. **The lever is real; the only open number is its GATE
  CONVERSION RATE.**
  **⭐ THE ZERO-CRACK POOL (the actionable shortcut): 76 substantial families whose exemplar is
  ALREADY MATCHED = 347,892 ins = 19.4% of the 1,788,653 distinct ins remaining. No drafting at all —
  remap + preamble + gate.** Decomposed by ACTUAL BLOCKER (not reported as one flat number):
  | blocker | fams | ins | share |
  |---|---|---|---|
  | **FREE — PURE, non-jr, non-O0** | **61** | **224,410** | **64.5%** |
  | jr (needs the §81 carve chain — proven today, ~40 min ea) | 13 | 57,311 | 16.5% |
  | -O0 cluster (KNOWN, characterized, deferred build-infra) | 2 | 66,171 | 19.0% |
  **The FREE subset = 224,410 ins = 12.5% of remaining distinct code, in exactly the shape banked
  today** (`func_8017C730`: matched sibling → remap → minimal preamble → gate, 40 min, 0 agent tokens)
  **minus even the carve chain.** Top: `0x8013d53c` (240×123=29,520) · `0x80144090` (154×136=20,944) ·
  `0x80133ab0` (137×136=18,632) · `0x8012cc88` (105×137=14,385) · `0x801749c8` · `0x801463a0` …
  Exemplars concentrate in **ov_SC01_077** (the canonical harvest source) and **ov_SC07_006**.
  **⚠️ THIS IS STILL A PREDICTION, NOT A BANK (R14/G3).** h_seq classes members PURE; the whole-binary
  gate decides. This is precisely the class where **P26 read 0% off a tool with a missing carve and
  P28 read 89% off the fixed one** — and where P29-T2's Arm B sweep already banked ~4,155 members and
  left a pin/drift/plumbing residual. **Some of this pool is that residual and will refuse.**
  **⇒ T0.2 IS RE-TARGETED FROM THIS DATA** (it was aimed at a hand-picked `func_8017BEBC` guess): probe
  **8 members sampled across the FREE subset's top families**, byte-gated, and report a MEASURED
  conversion rate. Do not scale any (families)×(members) arithmetic until that rate exists.
  **-O0 note:** the pool's single largest family (`0x8013c414`, 45,073 ins) is -O0-blocked — and Arm A
  already PROVED -O0 members bank (9/9 on ov_SC07_010, R22-verified); the blocker is the *fleet-scale*
  carve's splat `%lo` re-disassembly sensitivity, deferred on ROI. **That is a build-infra task with a
  known shape, not a compiler wall** — worth re-pricing once the FREE subset is harvested.

- **◐ 2026-07-26 (SESSION-20) — T1.1 `func_80183814` (5,122 ins, ov_SC07_006) ROUND 1: 99.3%
  structural, NOT banked. The predicted shape, with a precise named next move. → cookbook §83.**
  **Verified independently (R14), agent did NOT over-claim:** my own `match_one` re-run reproduces
  `DIFF mine=5127 target=5122, 4622 mismatched`, class **LENGTH-DRIFT/+5**. Tree untouched
  (`git status config/ src/` clean — the agent respected the no-build-tree constraint).
  **The honest state, difflib-aligned:** **36 / 5,122 structurally unmatched (99.3% exact)** under a
  register-blind mask · 1,201 register-sensitive · **args+locals byte-exact at 216 B** · frame 8 B over
  (2 extra callee-saved regs) · **17 of 21 case bodies structurally EXACT** (case 20, 525 ins, perfect).
  **⚠️ THE 4,622 IS AN ARTEFACT OF INDEX-WISE COMPARISON** — a +5 length delta smears every later
  index. 4,622 and 36 describe the SAME draft. **On a LENGTH-DRIFT class, the mismatch count is not a
  progress signal** (§83a) — this is exactly how a 99.3% draft gets mistaken for a 10% one.
  **THE LEVER (and the vindication of a flag I raised):** the handoff's *"35× repeated template"*
  claim — which I passed to the agent **flagged UNVERIFIED because it appeared nowhere in the recon** —
  **is TRUE and was the whole game.** Three callees each appear exactly 35× as ONE 72-ins body
  parameterised by `(KIND, START, BOUND)` (`member==KIND*4`, `array==&D_801F61C0[START]`,
  `prev.BOUND==next.START`) = **2,625 of 5,122 ins (51%) from a single definition**. Flagging it cost
  nothing and the discipline stands: an unverified premise is a hypothesis to TEST, not a foundation.
  **TWO INHERITED-RECON CORRECTIONS (both R14-class):** (1) the `pad[32]` "dead local" is **gcc's own
  spill area** — declaring it corrupts the layout; removing it made the locals area byte-exact (§83c);
  (2) the recon's case 12 was **incomplete** (it cross-jumps into case 14's tail).
  **THE STALL, WITH A SOURCE CITATION:** one global regalloc fork — gcc CSEs three `&D_8018E27C`-class
  address constants across two call groups sharing a basic block, eating 2 callee-saved regs the target
  spends on real variables. **`cse.c:8340` sizes the quantity table `max(nsets*2,500)+max_reg` — gated
  by WHOLE-FUNCTION pseudo count**, which is why no local rewrite of case 0 ever moved it (§83d).
  **⇒ NAMED NEXT MOVE (round 2):** find the ~5 spurious instructions (5127→5122). That buys length
  parity **and** perturbs `max_reg` — the same lever — then **re-run the 15-row do-not-re-buy table on
  the new base** (§80). Round-2 economics are measured-cheaper than round 1 (§79/SESSION-19).
  **§80 VINDICATED THE DAY AFTER IT WAS WRITTEN:** cases 6 and 11 (8 and 7 diffs) had been written off
  as "pure allocation"; they were a copy-pointer walk (`pa = msa; pb = msb;`) and went to **zero**.
  **NO PINS IN THE DELIVERABLE.** A diagnostic `a0→$s2` pin halves the residual and makes the prologue
  byte-exact (confirming the diagnosis) but is a hand-placed dial and does not fix the frame — recorded
  as row 15 of the do-not-re-buy table, not shipped (§72/§74). **Agent self-reported this unprompted.**
  Artifacts: `.run/giants/s20_func_80183814_b1.c` · `s20_80183814_report.md` (15-row table with BASES)
  · 6 × `s20_g14_*.py` (regenerate the draft identically; edit the template once → all 35 sites).
  Cost: 367,677 agent tokens / 115 tool-uses / ~41 min.
  **DECISION: do NOT spend round 2 now.** Per the approved order this is a ~0.04pp lever while **T0.2
  is a measured probe on a 224,410-ins (12.5%) pool** — and T0.2 was blocked only by this agent holding
  `asm/`. Round 2 is queued with its lever named; nothing is lost (§80 table + harness are on disk).

- **✅ 2026-07-26 (SESSION-20) — T0.2 BOUNDED GATE PROBE on the FREE zero-crack pool. THE ANSWER:
  the pool is NOT wall-blocked — it is DECLARATION-PLUMBING-blocked. 12 attempts, 4 banked, and
  ALL 8 failures are PLUMBING (zero DIFF, zero compiler walls).**
  Method (bounded, per R14 — measure, never project): `family_sweep --hseq --only <8 FREE-subset
  exemplars> --band substantial --no-preclassify --stage-only` → staged **803 member drafts / 664
  groups**; then `harvest_verify --chunk 1` (one draft per build = clean attribution) on 2 overlays.
  **RESULT — 12 gate attempts across ov_SC01_000 + ov_SC01_001:**
  | outcome | n | detail |
  |---|---|---|
  | **BANKED** | **4** | `func_8017B490` ×2, `func_801463A0` ×2 — both binaries BYTE-IDENTICAL |
  | failed **PLUMBING** | **8** | `conflicting types for 'D_800A651C'` (DATA sym) · `conflicting types for 'func_8013D53C'` (the member's OWN def-side decl) |
  | failed **DIFF** (a real codegen wall) | **0** | — |
  **⇒ RAW CONVERSION 4/12 = 33%. But 0% of the failures are walls** — every one is the §75a/def-side
  loose-typing class, which this project has NAMED TOOLS for. **The ceiling is not 33%.**
  **⚠️ TWO CORRECTIONS TO THE T0.1 POOL MATH (both measured, both lower it):**
  1. **2 of the 8 top FREE families were refused outright by the §42e pinned-exemplar guard**
     (`0x80133ab0`, `0x801749c8` = the 270 skips). So the "FREE" classification does **not** imply
     sweepable — pins are a *third* blocker T0.1's decomposition did not separate. `--allow-pins`
     exists and SESSION-19 proved some pinned families bank ×134, so this is recoverable, not lost.
  2. `n_templatable` counts the matched exemplar too, so every T0.1 family figure is ~1 member
     (~0.7%) high. Immaterial to the decision, recorded for honesty.
  **NEGATIVE RESULT (§80 — scoped to THIS base): `--fix-def-sig` REGRESSES this class.** Re-staging the
  4 failing families with it and re-gating the same 8: **0 banked, and 2 PLUMBING turned into
  CC1-FAIL.** It is the wrong lever here despite targeting the same error text. Do not re-buy it on
  this base without re-testing.
  **THE NAMED NEXT LEVER (untested, bounded-run required):** `family_sweep --normalize-self-decls`
  — its own help text says it fixes *"the `conflicting types for func_X` that blocked 133/137 of
  func_801670E4"*, i.e. **exactly** the `conflicting types for 'func_8013D53C'` failure here. It is a
  GATE-phase transform (edits each sibling's own TU, snapshot+revert, byte-gate arbitrates), so it
  cannot run under `--stage-only`, and `--limit` caps FAMILIES not MEMBERS — so testing it costs a
  full ~123-member family run. **That is the single highest-value tooling probe outstanding.**
  **STRATEGIC READ (this is the answer to Drew's "is there a shortcut that cracks tons at once"):**
  the 224,410-ins FREE pool's blocker is **declaration plumbing, not gcc**. If
  `--normalize-self-decls` (or a `canon_sig_reconcile`/`reconcile_decls` pass) clears the class, a
  large fraction of that pool converts **for ~0 agent tokens** — the same economics as P28's
  `dedup_extend` (6,174 members, 95.6%, one new mode) and P19's `fix_arity_callers`. **Plumbing
  recovery has out-earned drafting in every phase that measured both.**

- **✅ 2026-07-26 (SESSION-20) — T0.2b `--normalize-self-decls`: CLEAN NEGATIVE, 0/123. The plumbing
  class blocking the FREE pool is NOT the one that flag fixes.**
  Ran the full `func_8013D53C` family (the one whose failure text — `conflicting types for
  'func_8013D53C'` — matches the flag's own documented fix, *"blocked 133/137 of func_801670E4"*):
  `family_sweep --hseq --only 0x8013d53c --band substantial --no-preclassify --normalize-self-decls`
  → **BANKED 0 / 123 failed across 123 overlays.** Zero agent tokens; the lever simply does not apply.
  **⚠️ AND IT LEFT 123 FILES OF VALUELESS CHURN.** The flag's transform (`extern void func_X(void)` →
  `(void *arg0v)` **+** a compensating call-site cast `((void (*)(void))func_X)()`) is **byte-neutral
  by construction**, so the tool's non-neutral backstop never fired — and it therefore **left every
  edit in place after banking nothing**: 123 files / 246 insertions / 246 deletions of dead diff.
  **Byte-safe but a real hygiene defect** — a `git add -A` after a 0-bank run would commit 123 files of
  pure noise. **Reverted (`git checkout -- src/` → 0 modified); spot-rebuilt ov_SC01_000 `9052dc0e`
  and ov_SC07_010 `d7b5875d`, both BYTE-IDENTICAL.** *(Candidate tool fix: on a 0-bank group, restore
  the snapshot regardless of neutrality — "neutral" is not "wanted". §61's law says undo by snapshot
  restore; this is the same law applied to the SUCCESS path.)*
  **⇒ The FREE pool's blocker is a DIFFERENT declaration class** than either `--fix-def-sig` (which
  regressed it) or `--normalize-self-decls` (which no-ops on it). Two named levers measured and
  eliminated for ~0 tokens. Next candidates, untested: `canon_sig_reconcile.py` v3.2 (the def-side
  wall cracker, §41) and `reconcile_decls.py` (the DATA-symbol analog — note one of the two failure
  texts is `conflicting types for 'D_800A651C'`, a **DATA** symbol, which neither tested flag targets).

- **✅ 2026-07-26 (SESSION-20) — T0.3 BACKLOG TRIAGE. The ledger is CURRENT (0 stale) but 92%
  UNCLASSIFIED — and its `addr` field is null for 93% of entries.**
  **1,622 live near-miss entries** (79 `failed`, 1 `near-miss`, 1,621 `near`).
  **P9 filter: 0 already-banked** — `backlog.py`'s drop-now-matched filter is working; the ledger is
  not carrying dead weight. *(Verified against a fleet-wide live-stub set of 9,567 distinct addresses
  derived from `corpus.stubs`.)*
  **⚠️ LEDGER DEFECT (R32 class, found while triaging): `addr` is `null` for 1,501 of 1,622 entries
  (93%)** — the address survives only inside `name` (`func_80174CB0`). **Any consumer keying on `addr`
  silently processes 7% of the ledger.** My first triage pass read 121 entries and reported "0 stale"
  off a 7% sample; deriving the address from `name` resolves **1,622/1,622 = 100%**. This is precisely
  the silent-skip shape R32 exists for. **Fix: make `backlog.py log` derive `addr` from `name` when
  the caller omits it, and add a coverage assertion.** *(Not yet applied — it is a write-path change to
  a ledger mid-session; flagged for the next tooling pass.)*
  **LIVE backlog by closeness:** 0 → **333** · 1–4 → **184** · 5–20 → **589** · 21–100 → 431 · 100+ → 85.
  **LIVE by class — the actionable read: 1,486 of 1,622 (92%) have NO class label**, exactly as
  `residual_class.py`'s own docstring warns ("91% of the open backlog has NO class label … so the
  grinder searches UNDIRECTED over almost the whole corpus"). Labelled: schedule 28 · struct 28 ·
  regalloc-order 27 · plumbing 14 · WAVE 14 · other 6 · PINS 4 · remat 3 · STUB 3 · STRUCT 3 ·
  loose-typing 2.
  **⇒ The single highest-value backlog action is to RUN `residual_class.py` over the 1,486 unlabelled
  entries** (deterministic, LLM-free, reads the bytes) so the 333 close=0 + 184 close-1-4 band can be
  routed to the right lever instead of grinding undirected. That is a zero-token tooling run.

- **✅ 2026-07-26 (SESSION-20) — T0.3b AUTOPSY: every backlog residual RECOMPUTED from the bytes
  (1,699 rows, `-j 12`, zero agent tokens). Three findings, one of them a large honesty correction.**
  `autopsy.py collect` re-derives each residual through the validated `match_one` path, deriving the
  asm subdir AND the `-O0` flag from `corpus.py` (both are documented silent-artefact generators).
  **R34 cross-check PASSED: closeness agreed with `masked_diff.structured_diff` on all 1,610 built
  rows, 0 classifier errors.** 89 `nobuild` rows REPORTED, not silently dropped (R32).
  **THE BUCKETS (reach-weighted in parens):**
  | bucket | fns | meaning |
  |---|---|---|
  | **redraft** | **707** (1,638) | *the stored draft is NOT this function* — un-attempted work MISFILED as a near-miss |
  | **structural** | **528** (5,067) | local mutation cannot introduce it — wants a C-level idiom, not CPU |
  | **integration** | **315** (2,454) | **byte-correct standalone; blocked on PLUMBING** |
  | permuter | **57** (855) | local mutation CAN reach it — the only true permuter fuel |
  | unknown | 3 (140) | the residue the LLM tier is for |
  **① THE HONESTY CORRECTION — 707 of 1,610 (44%) of the "near-miss backlog" ARE NOT NEAR-MISSES.**
  Class `SIZE-MISMATCH` (614 `short` + 93 `long`): the stored best-draft is a PARTIAL — an agent's
  incomplete attempt logged with a closeness score, exactly like `func_80183814`'s 666-of-5,122 recon.
  **`docs/backlog.md` — "the phase's other durable deliverable" (PhaseEnd 21) — has been overstating
  readiness by ~44% ever since.** These route to a FRESH CRACK, not to a wall and not to the permuter.
  **② THE ACTIONABLE POOL — 315 entries are `match_one` MATCH RIGHT NOW**, blocked only on the
  §58/§59 reconcile ladder. Recomputing beat trusting the stored label exactly as the tool's docstring
  argued: the tree has moved (type-lifts, shared-header work) since these were logged. Top by value:
  `func_80174CB0` (123×134 = 16,482) · `func_801463A0` (101×134 = 13,534) · `func_80173A60` (59×134) ·
  `func_80176144` (53×138) · `func_8012F49C` (51×138); **total ≈108,959 gain-ins** where reach is
  known. Spread across ~40 binaries (35 in ov_SC01_077). **⚠️ §52b still applies — ~half of close=0
  drafts fail the whole-binary gate — so this is 315 CANDIDATES, not 315 banks.**
  **③ THE PERMUTER BUCKET IS 57.** Task-13B measured 75/972 (7.7%) permuter-shaped and concluded
  *"the problem was TARGETING, not a missing transform"*; the fresh recompute says **57 of 1,610
  (3.5%)**. **Extending the mutation set is confirmed NOT the big lever** — it is a small, real, and
  now precisely-bounded one.
  **④ R34 EARNS ITS KEEP AGAIN — 3 of 4 comparable labels DISAGREE with the measurement:**
  `func_80140D68`, `func_8012A328`, `func_801549F8` were all recorded **schedule** (→ schedule levers)
  but measure **ADDRESSING** (→ cse levers). **The grinder was being pointed at the wrong levers for
  these**, which is precisely the `mis-classified` bucket the autopsy exists to find.
  **⇒ STRATEGIC CONVERGENCE (the answer to "what one thing unlocks the most"):** T0.2's gate probe
  (8/8 failures PLUMBING, 0 walls) and T0.3b's autopsy (315 integration-class) **independently point
  at the SAME lever — the declaration/integration reconcile ladder.** It is worth the 224,410-ins FREE
  pool *and* ~108,959 backlog gain-ins. Two candidate keys were eliminated today (`--fix-def-sig`
  regresses; `--normalize-self-decls` 0/123); the untried ones are **`canon_sig_reconcile` v3.2** and
  **`reconcile_decls.py`** (the DATA-symbol analog — and one of T0.2's two failure texts was a DATA
  symbol, `conflicting types for 'D_800A651C'`, which neither tested flag targets).

- **⚠️ 2026-07-26 (SESSION-20) — CORRECTION TO MY OWN T0.1 FRAMING (Drew asked the right question:
  "did we bank all those?"). NO. We banked 4 of 1,073 members = 0.4%.**
  **The measured state of the "zero-crack pool":**
  | | |
  |---|---|
  | T0.1 PREDICTED (zero-crack, 76 fams) | 347,892 ins |
  | T0.1 PREDICTED ("FREE" subset, 61 fams) | 224,410 ins |
  | nominated for the T0.2 probe (8 top fams) | **1,073 members** |
  | **ACTUALLY BANKED** | **4 members** (`func_801463A0` ×2, `func_8017B490` ×2) |
  | fleet movement | **+396 instr-weighted / +194 distinct-code** |
  **⇒ ~1 part in 900 of the prediction.**
  **THE FRAMING ERROR, owned: I labelled it "FREE" and "the actionable shortcut."** The
  classification establishes **"no DRAFTING needed"** (the exemplar is matched; the members are the
  same code). It does **NOT** establish "no WORK needed" — and "FREE" reads as the latter. The probe
  then located the work precisely: **2 of 8 top families (270 members) were refused BEFORE any gate
  by the §42e pin guard** (so "FREE" did not even imply *sweepable*), and of what reached the gate
  **67% hit declaration plumbing** (0% hit compiler walls). **Both plumbing keys tried failed**
  (`--fix-def-sig` regressed; `--normalize-self-decls` 0/123).
  **HONEST STATUS OF THE POOL: real, structurally confirmed, NOT gcc-blocked — and still locked.**
  We found a large room and proved it is not bricked up; we have not found the key.
  **TO ACTUALLY BANK IT:** (1) find the working plumbing key — **`reconcile_decls.py`** (the
  DATA-symbol analog; one of the two failure texts WAS a DATA symbol, `conflicting types for
  'D_800A651C'`) or **`canon_sig_reconcile` v3.2** — both UNTRIED; (2) then re-sweep, which is
  mechanical and zero-token; (3) handle the pin-refused families separately via `--allow-pins`
  (SESSION-19 proved some pinned families bank ×134). **Until (1) lands the pool converts at the
  MEASURED 33% of whatever clears the pin guard, not the ~100% a "free" reading implies.**
  **WHY THIS IS RECORDED RATHER THAN QUIETLY SUPERSEDED:** this exact pool has been mis-called in
  BOTH directions — P26 declared it dead off a broken tool (0%), P28 found the same family bank 89%.
  A prediction stated as a bank is how that happens. **Any future session reading the T0.1 entry must
  read this one with it.**

- **✅ 2026-07-26 (SESSION-20) — THE T0.2 FAILURES, ALL FOUR DIAGNOSED. 3 of 4 causes are MECHANICAL
  and now proven; 3 banked. Drew: "succeed it; if it fails, see why and try again."**
  The diagnostic that did it (reusable, ~15 min/function): **splice the laddered draft → build →
  byte-diff the image against the extracted payload → decode the differing word.** It converts
  "PLUMBING, cause unknown" into a named root cause.
  | family | value | cause | outcome |
  |---|---|---|---|
  | `func_8013D53C` | 240×123 ≈ 29,520 | **§84 derived-offset** (remap carried a literal encoding a per-overlay symbol distance) | ✅ BANKED |
  | `func_8012CC88` | 105×137 ≈ 14,385 | **§73/§30#2 RETURN axis** (def `s32` vs fleet `extern void`) | ✅ BANKED |
  | `func_8014D12C` | 93×137 ≈ 12,741 | same RETURN-axis conflict | ✅ BANKED |
  | `func_80144090` | 154×136 ≈ 20,944 | **LENGTH-DRIFT** +13 B (~3 ins), shifting 255 downstream regions | ❌ genuine codegen — real matching work |
  **⇒ The "33% conversion" from T0.2 was measuring MY MISSING LADDER, not the pool.** Bare
  `harvest_verify` is the last rung; `gate_stage` runs canon → cast → reconcile_tu → ARITY →
  sig_unify → harvest_verify. Re-measured properly: **3 of 4 mechanical.**
  **THE FLEET-WIDEN FAILURE AND THE RETRY (→ §85):** widening only `engine_core.h` banked the target
  overlay and **BROKE `ov_SC01_077` — R22 139/140.** The source overlay carries its OWN local
  `extern void func_X(...)` decls, so a shared-header-only widen conflicts with them by construction.
  **The per-binary gate passed while breaking a binary it never built** (§63/§61 — a T2 write set is
  provable only by R22). **A half-done axis is a guaranteed break, not a smaller win.** The retry did
  the WHOLE axis: **3,668 decl sites / 2,688 files → 0 remaining** (R32 completion assertion), after
  verifying the precondition **0 callers consume the return value** ⇒ byte-neutral by construction.
  **R22 140/140, tools-health OK, dedup 1886/0.**
  **⚠️ MY OWN VERIFICATION ERROR, recorded not buried:** I spot-checked ov_SC01_077 with
  `make build | grep … | head; echo rc=$?` and read **rc=0 as success** — that is `head`'s exit
  status, not `make`'s, and the output had **no `BYTE-IDENTICAL` line**. I reported a false
  BYTE-IDENTICAL to Drew in the interim. **Assert on the expected SUCCESS STRING, never `$?` after a
  pipe.** R22 caught the real breakage; my reading of the cheap check did not. → cookbook §85.
  **Session fleet: instr 80.6% (10,589,503) · distinct-code 68.3% (3,846,656) · fn-count 89.19%.**

> **🛑 SESSION-20 CHECKPOINT (2026-07-26) — fresh session safe here.**
> **Nothing running.** Tree clean except the R23 `db.*.gbf` churn (never stage). **R22 clean-fleet
> 140/140** (run 5× this session), `tools-health` **OK**, dedup **1886/0**, **0 NON_MATCHING** (G4).
> HEAD `commit:1041`. **Drew pushes** (R6/R20).
> **FLEET: 80.6% instr · 68.3% distinct-code · 89.19% fn-count** (opened 80.6 / 68.2 / 89.18).
>
> ## BANKED THIS SESSION
> `func_8017C730` @ ov_SC03_013 (1,061, §81 carve chain) · 4 sibling members (T0.2) ·
> `func_8013D53C` (§84) · `func_8012CC88` + `func_8014D12C` (§85 fleet widen).
>
> ## ▶ START HERE NEXT SESSION — the unlock is IDENTIFIED but NOT YET HARVESTED
> **1. SWEEP THE TWO RETURN-AXIS FAMILIES (~27,126 ins, ~0 tokens).** The §85 widen is a ONE-TIME
>    fleet edit that is now DONE — so the other ~272 members of `func_8012CC88`/`func_8014D12C`
>    should no longer hit the conflict. Stage + `gate_stage` them. **Sample 8 FIRST** (probe-before-
>    scale — it caught my T0.2 error today), then the rest.
> **2. IMPLEMENT THE §84 OFFSET RECOMPUTE in `family_remap`** (`correct_literal =
>    mapped(aliased_sym) − mapped(base_sym)`), then sweep `func_8013D53C`'s 123 members (~29,520 ins).
>    133 staged drafts all carry the un-recomputed `+0x20` with different per-overlay bases.
> **3.** `func_80144090` is LENGTH-DRIFT — real matching work, not mechanical. Deprioritise.
> **4.** T1.1b `func_80183814` round 2 (99.3%, lever named: close the +5 to move `max_reg`).
> **5.** The 315 integration-class backlog entries (T0.3b) — same ladder, ~108,959 gain-ins.
>
> ## ⚠️ TWO TOOL-HYGIENE DEFECTS FOUND (both leave dead diff after a 0-bank run)
> `--normalize-self-decls` (123 files) and the **ARITY pre-pass** (40 TUs) both leave their edits in
> the tree when nothing banks, because their transforms are byte-neutral so the non-neutral backstop
> never fires. **Fix: on a 0-bank group, restore the snapshot regardless of neutrality** — §61's law
> applied to the success path ("neutral" is not "wanted"). Both reverted; binaries verified.
> **DO NOT close P29 on ROI** — burn-down floor still undetermined.

- **✅ 2026-07-26 (SESSION-20) — BOTH MECHANICAL LEVERS HARVESTED END-TO-END. 395 members banked,
  0 failed, ~56,200 ins, ZERO agent tokens.**
  | lever | members | mechanism | recipe | Δinstr | Δdistinct |
  |---|---|---|---|---|---|
  | **§85 return-axis** | **272** | ONE-TIME fleet widen (3,668 sites / 2,688 files) | widen → **plain** `harvest_verify` | +26,928 | **+0** |
  | **§84 derived-offset** | **123** | per-member literal recompute (`family_remap.fix_derived_offsets`) | recompute → **`gate_stage` LADDER** | +29,280 | **+27,840** |
  Both 100%: return-axis 8/8 sample then 264/0; §84 3/3 sample then 119/0. `func_8013D53C` and both
  return-axis functions are now stubbed in **ZERO** overlays. R22 **140/140** after each; tools-health
  OK; dedup 1886/0; 0 NON_MATCHING (G4).
  **⚠️ THE TWO RECIPES ARE NOT INTERCHANGEABLE — and sampling is what caught it.** The return-axis
  members bank with plain `harvest_verify` (the fleet widen removed their conflict *globally*), but
  the §84 members do **not**: with the recompute alone the sample was **0/8**; through the ladder,
  **3/3 → 119/119**. **Had I reused the return-axis recipe I would have swept 123 members to zero
  banks and concluded the §84 fix was wrong.** Probe-before-scale earned its keep twice today (it
  also caught the T0.2 missing-ladder error).
  **📊 THE METRIC FINDING (carry this into P30 planning):** §84 moved **distinct-code +27,840**;
  the return-axis sweep moved **distinct-code +0**. §84-class members are byte-VARIANTS ⇒ each is a
  NEW unique function; propagation-class members were already counted once via their shared exemplar.
  **⇒ variant-cracking moves the RE-COMPLETENESS number; propagation moves only the DISPLAY number.**
  This sharpens SESSION-19's split into an actionable selection rule: **to move distinct-code, target
  byte-VARIANT families, not high-reach h_exact ones.**
  **Session fleet: 80.6 → 81.0% instr · 68.2 → 68.8% distinct-code · 89.18 → 89.30% fn-count.**

> **🛑 SESSION-20 FINAL CHECKPOINT (2026-07-26) — fresh session safe here.**
> **Nothing running.** Tree clean but for the R23 `db.*.gbf` churn (never stage). **R22 140/140**
> (run 8× this session), `tools-health` **OK**, dedup **1886/0**, **0 NON_MATCHING**, HEAD `commit:1044`.
> **FLEET: 81.0% instr · 68.8% distinct-code · 89.30% fn-count.** **Drew pushes** (R6/R20).
>
> ## ▶ START HERE NEXT SESSION
> **1. APPLY §84/§85 TO THE REST OF THE POOL.** Both root causes are fixed IN THE TOOLING now, so the
>    remaining zero-crack families should be re-probed against them. **Re-run T0.1's decomposition
>    first** (`family_hseq` + the FREE-subset query) — it is stale by 395 banked members. Then sample
>    8 per family before each sweep. **Route by class: variant families for distinct-code, h_exact
>    families for the display metric.**
> **2. `func_80144090`** (154×136 ≈ 20,944) — LENGTH-DRIFT, +13 B / ~3 ins. Genuine codegen; real
>    matching work, NOT mechanical. The 4th T0.2 cause and the only one still open.
> **3. The 315 integration-class backlog entries** (T0.3b) — now that the ladder + §84/§85 are
>    understood, re-gate them through `gate_stage`; ~108,959 gain-ins.
> **4. T1.1b `func_80183814` round 2** — 99.3% structural, lever named (close the +5 to move `max_reg`).
> **5.** The 707 `redraft` backlog entries are NOT near-misses (44% of the ledger) — route to fresh
>    cracks, never to the permuter.
>
> ## ⚠️ CARRIED DEFECTS (unfixed, both recorded)
> - **The absolute-include portability defect** — 21 files, PhaseEnd carry item (Drew: handle later).
> - **Two ladder-hygiene bugs:** `--normalize-self-decls` (123 files) and the **ARITY pre-pass**
>   (40 TUs) both leave their edits after a 0-bank run, because the transforms are byte-neutral so the
>   non-neutral backstop never fires. **Fix: on a 0-bank group restore the snapshot regardless of
>   neutrality** (§61's law applied to the success path). Both reverted manually this session.
> **DO NOT close P29 on ROI** — burn-down floor still undetermined.

- **✅ 2026-07-26 (SESSION-20) — T0.5 COMPLETE: pool re-derived + 657 more members banked.
  SESSION TOTAL ≈ 1,070 members from FIVE root causes, all zero-token.**
  **Pool re-derived post-harvest** (T0.1's numbers were stale by 395 banked members):
  zero-crack **76 fams / 347,892 ins → 73 / 290,850**; FREE subset **58 fams / 167,368 ins**.
  **FREE sweep:** 389 banked; `func_801463A0` / `func_8017B490` / `func_80156670` → **0 stubs**.
  **`--allow-pins` sweep:** 268 banked; `func_801749C8` / `func_8014C6F4` → **0 stubs (137 each)**.
  **⇒ §86 — PIN TEMPLATABILITY IS PER-FAMILY, NOT PER-MEMBER.** 2 families 100%, 3 families ~1%.
  **My reported "37%" was an ARTEFACT** — a 19-member sample straddling families reported their
  AVERAGE and hid the bimodality. **Sample PER-FAMILY, never per-pool** (counterpart to §80).
  **The §42e guard is OVER-CONSERVATIVE:** it refused **680 of 1,083 members (63%) before any gate**,
  yet `--allow-pins` banked 268 with **ZERO cc1 crashes** — the SIGABRT it guards was Phase 27's
  `extract_unit` macro-drop, not a compiler limit. **New default procedure: probe ONE member per
  pinned family → sweep or skip.** (The blanket run spent ~412 futile cycles, 60%, on dead families.)
  **Left UNDIAGNOSED on purpose:** why 2 template and 3 do not — likely caller-saved pins spanning a
  `jal` (§74) vs local-allocno pins. **Diagnose before extending `--allow-pins` fleet-wide.**
  **MY SCRIPT BUG (fixed + negative-controlled):** the sweep loop globbed `.run/sweep/*/`, matching
  `gate_stage`'s own intermediate ladder dirs (`-cn`/`-cast`/`-rc`/`-s2in`/`-uni`) and calling them as
  binaries → 24 phantom PARTIALs that inflated `notbanked` 0→56. Fixed by requiring
  `config/splat.<ov>.yaml`. **Ground truth is the STUB COUNT, not the tally.**
  **Fleet: 81.5% instr · 69.0% distinct-code · 89.49% fn-count** (opened 80.6 / 68.2 / 89.18).

> **🛑 SESSION-20 CLOSING CHECKPOINT (2026-07-26) — FINAL. Fresh session safe here.**
> **Nothing running.** Tree clean but for R23 `db.*.gbf` churn (never stage). **R22 140/140** (run
> 11× this session), `tools-health` **OK**, dedup **1886/0**, **0 NON_MATCHING** (G4).
> HEAD `commit:1047`. **Drew pushes** (R6/R20).
> **FLEET: 81.5% instr · 69.0% distinct-code · 89.49% fn-count** — session **+0.9 / +0.8 / +0.31 pp**.
>
> ## THE SESSION IN ONE LINE
> **~1,070 members banked from FIVE root causes — and every one was OUR OWN TOOLING, not gcc:**
> a remap carrying a per-overlay symbol distance as a literal (§84) · a declaration axis applied to
> half its sites (§85) · a recovery ladder never invoked (T0.2's false "33%") · a pin guard refusing
> a class it no longer needs to (§86) · a sweep loop globbing its own scratch dirs.
>
> ## ▶ START HERE NEXT SESSION
> **1. Continue the FREE subset** — 58 families / 167,368 ins were mapped; ~5 swept. Re-derive first
>    (stale by ~657 members), then **1-member probe per family** (§86), then sweep. Route by class:
>    **variant families move distinct-code; h_exact families move only the display metric.**
> **2. Diagnose the §86 pin split** (2 template / 3 do not) — one cracked axis unlocks the 412 refused.
> **3. `func_80144090`** (154×136 ≈ 20,944) — LENGTH-DRIFT, +13 B. Genuine codegen, real work.
> **4. The 315 integration-class backlog entries** (T0.3b) — re-gate through `gate_stage`, ~108,959 ins.
> **5. T1.1b `func_80183814` round 2** — 99.3%, lever named (close the +5 to move `max_reg`).
>
> ## ⚠️ CARRIED DEFECTS (unfixed, recorded)
> - The **absolute-include portability defect** (21 files) — PhaseEnd carry item, Drew: handle later.
> - **Ladder hygiene:** `--normalize-self-decls` + the ARITY pre-pass leave byte-neutral edits after a
>   0-bank group. **Fix: restore the snapshot regardless of neutrality** (§61 on the success path).
> - The 707 `redraft` backlog entries are NOT near-misses — route to fresh cracks, never the permuter.
> **DO NOT close P29 on ROI** — burn-down floor still undetermined.

---

# 🛑 SESSION-20 FINAL CHECKPOINT (2026-07-26) — FRESH SESSION STARTS HERE

**Nothing running.** Tree clean but for R23 `db.*.gbf` churn (never stage). HEAD **`commit:1055`**,
**26 commits this session**. **R22 clean-fleet 140/140** (run 13×), `tools-health` **OK**, dedup
**1886/0**, **0 NON_MATCHING** (G4). **Drew pushes** (R6/R20).

**FLEET: 81.7% instr · 69.3% distinct-code · 89.52% fn-count · 37,054 stubs.**
Session opened at 80.6 / 68.2 / 89.18 → **+1.1 / +1.1 / +0.34 pp**.

**🏆 ZERO BEHEMOTHS REMAIN** — no unmatched function >1000 ins exists anywhere in the fleet.
`func_80183814` (5,122 — the largest in the game) · `func_8017D2DC` (1,586) · `func_8017DC1C` (1,518)
· `func_8017C730` (1,061). ~1,070 family members also banked.

---

## ▶ THE ENDGAME MAP (iterated repeatedly this session — this is the CURRENT, MEASURED version)

**Remaining: 2,405,364 instr-weighted / 1,732,609 distinct ins / 37,054 stubs.**

| # | bucket | size | state / routing |
|---|---|---|---|
| 1 | **Sub-500 mass** | **~37,000 stubs ≈ 94% of ALL remaining** | THE endgame. Untouched. Breadth ⇒ Ultracode waves. **NEXT.** |
| 2 | **Main EXE game code** | **~59,765 ins @ 0.7%** | Untouched, NOT idiom-blocked. Machinery exists (Phase-7 rodata/jtbl). Single binary ⇒ gating serialises. |
| 3 | **-O0 cluster** | 2 fams / 66,171 ins | Known blocker: splat `%lo` re-disassembly at fleet scale. Arm A PROVED members bank (9/9). |
| 4 | **jr families** | 13 fams / 57,311 ins | §81 chain proven 5× today; `jtbl_family_bank.py` exists. Zero-token. |
| 5 | **FREE families** | ~38 unprobed of 53 | §86 one-member probe FIRST. Top-of-ranking already consumed; expect diminishing returns. |
| 6 | `func_80144090` | 20,944 gain-ins | **LENGTH-DRIFT** (+13 B) — genuine codegen, real work, not mechanical. |
| 7 | 707 `redraft` backlog | — | NOT near-misses — partial drafts misfiled. Route to fresh cracks, NEVER the permuter. |
| 8 | Resident | 14 stubs | Classed dossier: 5 PLUMBING / 4 DIFF / 5 jtbl-deferred. |
| 9 | 2 permanent giant walls | `func_801412A8` (close=110) · `func_80178004` (close=91) | Model-relative; re-price each phase. |
| 10 | **39 type-1 modules** | unquantified | Need load-address RE (PCSX-Redux RAM proof) BEFORE they can be built. **IN NO PHASE OF THE ROADMAP.** |

**⚠️ SIZING TRAP (Drew caught me on this):** `nins × members` is **reach-weighted gain-ins**, NOT a
function size. `func_80144090` is **154 ins × 136 copies**, not a 20,944-ins monster. **Always label
which one you are quoting.**

### THE ROUTING RULE (measured today — it decides what to attack for WHICH metric)
- **Byte-VARIANT families move distinct-code** (§84's family: +27,840 distinct) — each member is a
  new unique function.
- **Propagation/h_exact families move ONLY the display metric** (§85's 272 members: **+0 distinct**) —
  already counted once via the shared exemplar.
**⇒ To move RE-completeness, target variant families. To move the decomp.dev number, target reach.**

---

## THE SESSION'S THROUGH-LINE — FIVE ROOT CAUSES, ALL OUR OWN TOOLING
1. **§84** a remap carrying a per-overlay symbol DISTANCE through as a literal · 2. **§85** a
declaration axis applied to half its sites · 3. a recovery ladder never invoked (T0.2's false "33%") ·
4. **§86** a pin guard refusing 63% of a pool, defending a crash Phase 27 already fixed · 5. a sweep
loop globbing its own scratch dirs. **Not one was gcc.**

## NEW LAWS — cookbook §84–§89 (all distilled in-session, R30)
- **§84** derived-offset recompute; `match_one` masks `%lo` so it is BLIND to it (one-byte gate diff).
- **§85** the RETURN axis is ALL-OR-NOTHING — widening only the shared header GUARANTEES a break
  (the source overlay carries its own local `extern void` decls). Precondition: 0 callers consume the
  return. 3,668 sites / 2,688 files, R22-verified byte-neutral.
- **§86** pin templatability is **PER-FAMILY, not per-member** (2 fams 100%, 3 fams ~1%). **Probe ONE
  member, then sweep or skip.** A sample straddling families reports their AVERAGE and hides the
  bimodality. The §42e guard is OVER-CONSERVATIVE (0 cc1 crashes in hundreds of pinned compiles).
- **§87** **`match_one` COMPILES but never LINKS** ⇒ an unresolvable symbol reads as MATCH; stored
  drafts also go STALE against the tree. **FOUR blindness classes now catalogued: §81 jtbl · §84
  masked `%lo` · §87 link · §87 staleness.** A stored MATCH is **a claim with a timestamp**.
- **§88** `cross_jump` will NOT merge a call-bearing suffix (write those longhand; never hand-factor
  the call-free tails) · the `slti` literal-position law · **§88c its equality-comparison FALSE
  POSITIVE** (no `beqi`, so `==` constants are ALWAYS materialised — §78/§88b are scoped to ORDERED
  comparisons only) · **§88d BANKING ORDER: carve chain BEFORE banking** (banking first let
  `overlay_src_split` drop all 39 of a draft's externs) · **§88e** an inherited "named lever" is a
  hypothesis with a citation — round 2 refuted round 1's `max_reg` story three ways; the real cause
  was a `CODE_LABEL` from a `break`.
- **§89** the two throughput rules the project already had and was not following.

## NEW TOOLS — the standing sequence
```
family_sweep --stage-only → sweep_parallel.py -j 12 → blast_radius.py
                                    T2? → R22 mandatory   T1? → per-binary gates already ran; commit
```
- **`tools/blast_radius.py`** — MEASURES the write set, enforces §63's tier. `--expect t1 --binary X`
  fails loud when the tree disagrees. Negative-controlled on 4 cases incl. the §85 shape.
- **`tools/sweep_parallel.py`** — reaches `bulk_harvest`'s per-binary gate farm from the family path
  (SESSION-20 gated 389+268+104 members SERIALLY for no architectural reason). Filters the phantom
  ladder-dirs at source.
- **`.run/giants/s21_g21_reloc_verify.py`** — resolves EVERY relocation (incl. the implicit MIPS-REL
  addend `objdump -r` omits) against the target. **Promote to `tools/` — it closes 3 of the 4
  blindness classes before a gate cycle is spent.**

## ▶ NEXT MOVE — THE ULTRACODE MASS WAVE (Drew's call, agreed)
**Target: the sub-500 mass (~37,000 stubs, 94% of remaining).** Breadth ⇒ **prompt Drew for
`/effort ultracode`** (R26/R27 — Claude cannot toggle it).
1. **CALIBRATE ON ~50 FIRST and MEASURE.** Phase-15's mass wave yielded **+0.36% for ~4.1M tokens**
   while deterministic recovery beat it **~7×**; tonight repeated that pattern (367k tokens → 0 banks
   from an agent, vs ~1,070 members for ~0 tokens from tooling). **Do not scale on hope.**
2. Gate via `sweep_parallel -j 12`, tier-check via `blast_radius`, R22 only if T2.
3. **Flip back to Max** for synthesis / PhaseEnd / hard diagnosis (Ultracode caps depth at xHigh).
**Zero-token alternative if tokens are precious: the jr families (#4, 57,311 ins), §81 proven 5×.**

## ⚠️ CARRIED DEFECTS (unfixed, all recorded)
- **21-file absolute-include portability defect** — PhaseEnd carry item (Drew: handle later).
- **Ladder hygiene:** `--normalize-self-decls` (123 files) and the ARITY pre-pass (40 TUs) both leave
  byte-neutral edits after a 0-bank run — the backstop only fires on NON-neutral. **Fix: restore the
  snapshot regardless of neutrality** (§61 on the success path).
- **Backlog ledger `addr` is null for 93% of entries** — address survives only in `name`. An
  addr-keyed consumer silently sees 7%. **I fell into this twice in one session.**
- **`docs/backlog.md` is NOT a work queue** — 44% misfiled partials (§83) + the integration bucket
  doesn't link (§87). Re-gate a sample before planning against ANY stored-draft pool.
- **Roadmap re-baseline owed:** B-buckets predate 4 overlays; B7 omits the largest function in the
  game; the 39 type-1 modules appear in no phase.
**DO NOT close P29 on ROI** — burn-down floor still undetermined.

---

# SESSION-21 (2026-07-26/27) — THE FAMILY-EXEMPLAR MASS WAVE

**Opened:** effort **ultracode** (Drew toggled; R27 honoured — prompted and waited).
**Opening state:** HEAD `commit:1056`, fleet **81.7% instr · 69.3% distinct-code · 89.52% fn-count**,
140/140 byte-identical, dedup 1886/0, 0 NON_MATCHING.

## ✅ T1 — THE SUB-500 FRONTIER, MEASURED (zero agent tokens, R35: tool verified before its scan)

Ran `.run/s21_frontier.py` off `corpus.py` (derived: stubs from the self-describing `INCLUDE_ASM`
line, matched from the proven invariant `sig − stubs`; no hand-listed binaries, R33). Sigs were
FRESH (22:10, regenerated by `make tools-health`); `.run/family_hseq.json` was **stale by ~657
banked members** and was regenerated first — the checkpoint's own instruction, and it mattered.

| band | stubs | weighted ins | h_exact-FREE | free ins |
|---|---|---|---|---|
| tiny 1–15 | 2,663 | 31,703 | 248 (9.3%) | 2,823 |
| mid 16–79 | 25,712 | 1,013,875 | 2,671 (10.4%) | 129,741 |
| substantial 80–499 | 7,544 | 1,224,642 | 322 (4.3%) | 37,119 |
| large 500–999 | 101 | 75,379 | 4 (4.0%) | 3,080 |
| **TOTAL** | **36,020** | **2,345,599** | **3,245 (9.0%)** | **172,763** |

**① PROPAGATION IS TAPPED.** Only **9.0%** of remaining stubs have a byte-identical copy already
matched somewhere in the fleet (238 distinct classes / 3,245 instances). The h_exact lever that
carried Phases 24–28 is spent; what remains is 22,498 distinct classes / 1,680,097 distinct ins.

**② THE MASS IS FLAT, NOT CONCENTRATED.** Every overlay carries ~300–550 sub-500 stubs / ~20–28k
ins. There is no rich binary to raid — `ov_SC04_011` (the richest) holds 28,400 ins of 2,345,599.
So "pick the best overlay" is not a strategy; the axis has to be something other than location.

## ✅ T2 — THE AXIS THAT IS NOT LOCATION: h_seq FAMILY EXEMPLARS

Re-derived from the fresh family map (`.run/s21_targets.py` → `.run/s21_targets.json`):

**1,342 substantial families / 1,298,135 templatable ins = 55% of ALL remaining weighted
instructions.** The endgame is therefore **~1,342 exemplar cracks**, not 36,020 function matches.

| route | fams | templ ins | share |
|---|---|---|---|
| jr → §81 carve chain | 181 | 435,546 | 33.6% |
| **DRAFT, cached Ghidra-C (agent-ready NOW)** | **91** | **371,053** | **28.6%** |
| DRAFT, modal exemplar (other overlay, needs MCP) | 1,023 | 356,425 | 27.5% |
| zero-crack (exemplar already matched) | 45 | 85,017 | 6.5% |
| permanent walls (re-price only) | 2 | 50,094 | 3.9% |

Filtered to **live + cached + non-wall exemplars in ov_SC01_077: 54 families / 589,502 ins**, and
the value is steeply concentrated — **entries 1–24 carry 566,236 of 589,502 (96%)**; entries 25–54
are ×1–×16 leverage worth ~23k combined. `.run/s21_draft_pool.json`.

**⚠️ THIS IS A PREDICTION, NOT A BANK (R14/G3).** `n_templatable` is an h_seq classification; the
whole-binary gate decides. SESSION-20's own lesson stands: the T0.1 "FREE" pool converted at
1 part in 900 until the real blockers (§84/§85/§86) were named. Expect a residual here too.

## ▶ T3 — WAVE 1 LAUNCHED: 24 family exemplars, stake 575,488 templatable ins (24% of remaining)

`tools/workflows/family_core_wave.js` (**new**, committed) — 24 xHigh drafter agents, one per
exemplar, drafts to `.run/drafts-s21`. It supersedes `worker_wave.js` for family work: worker_wave
predates §84–§89 and treats every target as an isolated function, so it never told the agent what a
crack was WORTH. The new prompt carries the family stake per target and encodes at source the four
§58/§87 integration rules that made 9/9 of an earlier wave's match_one MATCHes fail the real gate
(splat `D_<UPPERHEX>` names not Ghidra `DAT_`; never invent a symbol; canonical callee sigs from
`engine_core.h`; don't chase decl plumbing — the ladder owns it), plus a mandatory `symcheck.py`
run on any claimed MATCH (§67a/§87 — the guard that catches the link-invisible-symbol class before
a gate cycle is paid for).

Spread (deliberate, so the calibration measures more than one path): 11 giants >150 ins · 2 -O0
(`_o0` TU) · 10 whose family carries a mid-jr (member sweep needs the §81 carve chain) · 11 with a
prior recorded attempt · TUs spanning plain/`_a`/`_after`/`_o0`/6 distinct `_jr_*` carves.

**Concurrency constraint honoured:** agents read `asm/` on every probe, so NO `make clean`/`extract`
runs until the wave resolves; drafters are explicitly forbidden from running any make target.

## ✅ T3b — THE TWO CARRIED LADDER-HYGIENE DEFECTS, FIXED (zero-token, done while the wave drafted)

Both SESSION-20 carry items were the SAME defect wearing two masks: **a transform that is
byte-neutral was therefore left in the tree when it bought nothing.** "Byte-safe" was being used as
the test for "wanted", so a 0-bank run committed itself to the working tree as pure noise.

- **`tools/family_sweep.py`** — the `--normalize-self-decls` backstop only fired on `MISMATCH` (a
  NON-neutral edit). A 0-bank group left every edit in place: SESSION-20's `func_8013D53C` run
  banked 0/123 and left **123 files / 246 insertions / 246 deletions** of dead diff. Now: on
  `nver == 0`, restore the phase-1 snapshot unconditionally. No rebuild needed — if the edit had
  been non-neutral the existing branch would already have run.
- **`tools/gate_stage.py`** — the ARITY pre-pass undo deliberately narrowed itself to `src/shared/`
  (correct: the splice hazard, a 9-draft run that silently reverted its own 4 banks). But that
  narrowing also left the binary's own TU edits behind on a 0-bank run (~40 TUs). Now: when
  `verified` is empty there are **no banks to preserve**, so the restore widens to the full snapshot.
  The splice hazard is untouched in the partial-bank case.

Both are §61's undo law applied to the SUCCESS path. Neither can cost a match by construction (they
only fire when nothing banked).

## ✅ T3c — THE BACKLOG `addr` DEFECT, FIXED (R32/R33)

SESSION-20 found `addr` null for 1,501 of 1,622 live entries and noted *"I fell into this twice in
one session."* The address was never actually missing — `func_80174CB0` states it.
- `tools/backlog.py`: new **`addr_of(rec)`** derives the address from `name` when `addr` is absent
  (R33 — derive, don't re-ask), new **`assert_addr_coverage()`** fails loud on any row that cannot
  be keyed (R32), and `append_record` now fills BOTH directions of the name↔addr pair.
- **Latent bug found while fixing it:** `load_best()` keyed on `r["addr"] or name`, so a function
  logged once each way produced **two** "best" records. Now keyed on the derived address.
- **Measured:** rows keyable **128/1,701 (7.5%) → 1,701/1,701 (100%)**; coverage assertion PASSES;
  `load_best` → 1,689 open records.
