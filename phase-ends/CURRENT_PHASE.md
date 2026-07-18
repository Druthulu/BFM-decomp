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

- [ ] ▶ **Task 2 — Act on the verdict [Max/xHigh]** — **branch = 2a (tooling).** Build the -O0-cluster
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
- [ ] **Task 5 — Fleet Ghidra-C prefetch (JIT drafting fuel) [xHigh; MCP: R23/R29 — prompt /mcp]** —
      built only when Task-3 waves exhaust the ~300-fn cache.
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
