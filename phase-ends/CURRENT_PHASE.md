# CURRENT PHASE — Phase 22: Hand-grind the giants (×134) + idiom-distill-then-fan-out flywheel

**Generation:** Gen2 (14th phase of the arc; Phase 14 deferred to Gen3+) · **Started:** 2026-06-26 · **Effort:** Max (giants/synthesis) ↔ Ultracode (idiom waves, prompt per R27) · **Plan approved:** gate 1 ✅ (Drew)

> Per-task crash-recovery log (P3). The full approved plan is at `~/.claude/plans/plan-mode-enabled-max-shimmering-thimble.md`. This file is the committable state a fresh session resumes from.

## Goal

Drive the **byte-weighted** progress number (~30% decomp.dev-comparable; the function-count metric is at 63.18%) by **hand-grinding the giants** (reach-134, >150 ins — each banks ×134), distilling each crack into a reusable idiom, then fanning that idiom out across its class via the existing wave harness. Open-ended; monotonic; zero regressions; close at a clean checkpoint when giant ROI drops.

## Decisions (Drew, gate 1)
- **Calibrate on a mid-giant first:** `func_8015126C` (254 ins / 135K, already a **close=2** backlog near-miss) → `func_8014EE14` (248 / 131K, close=6) → escalate toward `func_80144B9C` (770 / 410K).
- **Background grinder ON:** token-free permuter daemon on the regalloc/coalescing residual, alongside the hand-loop.

## The operating loop
A. Hand-decomp next giant (Max) → §27 recipe → match_one → harvest_verify byte-gate → dedup_propagate ×134 → commit. ROI-gate: irreducible class → bank closest draft to backlog (P9), move on.
B. Distill the last-mile idiom → cookbook (R16/R30).
C. If general → fan out a few waves (Ultracode, prompt R26/R27) applying it → gate_stage → distill.js → backlog.
D. Rinse and repeat (next giant, highest byte-weight first).

## Tasks
- [x] **T0 — Unified byte-weighted ranked worklist** *(done — `commit:0296`)* — `tools/worklist.py` → `docs/worklist.md` + `.run/worklist.json`.
- [x] **T1 — Calibrate on func_8015126C** *(done — banked ×134, fleet 63.18→63.22%, check-all 136/136)* — pin idiom + canonical-extern/block-scope recovery cracked it; all 23 giants confirmed Ghidra-C-cached (no prefetch needed).
- [ ] **T2 — Hand-decomp giants by byte-weight (loop)** — func_8014EE14 → … → func_80144B9C; one at a time, byte-gated, propagated ×134, committed. Report each (P3).
- [x] **T3 — Distill idioms → cookbook** *(done for func_8015126C — cookbook §28/§28a + `tools/recover_giant.py`, `commit:0298`)* — recurring per future crack.
- [ ] **T4 — Idiom fan-out waves (Ultracode)** — a few waves per learned idiom over its class (prompt R27). *(close=0 canonical-extern "wave" was probed → R14 refuted near-free; only func_8015126C banked.)*
- [x] **T5 — Background grinder** *(started + STOPPED for handoff; STOP sentinel set; banked 0 on the hard giants it sampled)* — RESUME: `rm .run/auto/STOP` then `DRIVER=tools/grinder.py setsid nohup bash tools/auto_supervisor.sh --permute-secs 120 -j 14 >/dev/null 2>&1 & disown`; monitor `bash tools/auto_status.sh`.
- [ ] **T6 — Progress honesty + PhaseEnd** — keep worklist/backlog/progress.fleet.md fresh; track both %s; PhaseEnd_Phase22.md at close (Tier-1 Max).

## ▶ RESUME HERE (fresh session)
**State:** Phase 22 in progress (NOT a phase end — no PhaseEnd file). 3 commits this session on top of Phase-21 close `commit:0295`: `commit:0296` (T0 worklist) · `commit:0297` (T1 func_8015126C ×134) · `commit:0298` (T3 cookbook §28 + recover_giant.py) + a reports-regen checkpoint commit. All 136 binaries byte-identical (`make check-all` 136/136); fleet **63.22%** function-count; dedup-check 1617/0. Working tree clean except the R23 `db.*.gbf` churn (do NOT stage). **Drew commits AND pushes the session work (R6/R8).** Grinder STOPPED (STOP sentinel set).

**NEXT TASK — T2: hand-decomp the next giants by byte-weight** (effort **Max**; the loop is A hand-crack → B distill → C fan-out). Use `docs/worklist.md` (the GIANT queue, refreshed) as the decision spine. Concrete queue:
1. **func_80132784** (400 ins, #2 byte-weight giant; backlog close=240: prologue+GTE pipelines match, residual = else-branch `$s0` pointer regalloc + GTE-section stack-ptr allocation → §17 pins). The biggest reachable hand target.
2. **The struct-walled close=0 trio** `func_80156B74` (214), `func_8014F74C` (174), `func_80163C2C` (167): match_one MATCH but blocked by a local `struct S8`/`B8` colliding with the TU (§28 case 3). Lever: lift `S8`/`B8` to `src/shared/engine_types.h` (or reuse the existing def / rename), then `tools/recover_giant.py` + gate. Could bank ~3 giants if the type-lift resolves it.
3. **func_80178004** (165): saved draft regressed (DIFF 91) — re-derive from cached Ghidra-C (it had register-pins-per-sibling-func_80177EA4 keys).
4. **decomp.wiki levers to try** (§28a): `func_801412A8` (198, offset-fold-vs-advance residual) → the **negative-struct-offset-in-loop** idiom (`for(...; p++)`); the **branch-duplication** lever for call-crossing regalloc swaps.
5. After each bank: `dedup_propagate` ×134 (BACKGROUND), `make check-all`, commit, distill any new idiom (T3), then optionally a fan-out wave (T4, prompt for Ultracode R27).

**Reusable this session:** `tools/recover_giant.py` (canonical-extern recovery for pure-extern close=0 giants); `tools/worklist.py --refresh` (the ranked decision table); calib drafts in `.run/drafts-t1-calib6/`. **Op gotchas (cookbook §28):** run `dedup_propagate` in BACKGROUND; `git checkout src/` does NOT revert `config/dedup.us.yaml` (reset both on a redo). **Pending tooling polish:** `gate_stage.py` commit message hardcodes "phase-21" → make phase-agnostic before the T4 worker waves.

## Verification invariant (every bank)
`make check-all` → 136/136 byte-identical from a CLEAN tree (R22); `dedup-check` validated, 0 failed; 0 NON_MATCHING (G4); byte-gate (harvest_verify) is the sole arbiter (G3/P9); each bank = checkpoint commit; the `db.*.gbf` churn is R23 restart-noise (do NOT stage).

## Reuse (no rewrites)
orchestrator / wave_targets / worker_wave.js / distill.js / gate_stage / idiom_loop / grinder + supervisor / harvest_verify / match_one / dedup_propagate / build_fuel_manifest / backlog; cookbook §17–§27 + hand-matching-process.md + automation-runbook.md.

## Guardrails
- Don't grind confirmed-irreducible classes (store-vs-load sched, hoist-vs-remat, IV-combine, hoisted-invariant order, narrow-param loose-typing, cross-jump merge) — ROI-gate, bank closest, move on.
- Actor struct is byte-NEUTRAL for matching (comprehension only).
- R27 effort transitions: prompt Drew to toggle Max↔Ultracode at every A/B↔C boundary; never launch a Workflow on a verbal yes.

## Blockers
(none)

## Progress log
- 2026-06-26: Phase plan approved (gate 1). Task list built (R28). CURRENT_PHASE.md written. Starting T0.
- 2026-06-26: **T0 done** (commit `commit:0296`) — `tools/worklist.py` + `docs/worklist.md` + `.run/worklist.json`. 451 live stubs / 1.85M ins remaining gain; GIANT queue = 23 fns = 37.2% of remaining gain; top = func_80144B9C (770 ins, 5.58%).
- 2026-06-26: **T1 calibration on func_8015126C (254 ins, top-5 giant) — CRACKED, byte-identical in ov_SC01_077; ×134 propagation running (bg bl73feigi).** Key findings (→ T3 distill):
  - **(idiom) §17 pin for the coalescing residual:** the `(s16)p[0x79]!=1000` compare wanted `$a0` (coalesced) not `$v1`. Lever: `register s32 cmp79 __asm__("$4")` + assign **inside** the `&&` (lazy, not hoisted) → MATCH. Reusable for the regalloc-coalescing giant group.
  - **(THE close=0 wall, byte-proven) why match_one MATCH ≠ whole-binary bank:** the saved draft's *self-contained file-scope externs* conflict with engine_core.h's canonical sigs (e.g. my `extern void func_8015173C(void*)` vs canonical `void func_8015173C(s32*)`). `cast_call_sites`/`sig_unify` do NOT canonicalize these → the close=0 giants sit unbanked. **Fix (deterministic):** rewrite each engine_core.h-callee extern to its canonical def-sig AND move ALL externs **block-scope** (inside the body) so `find_site`/`compiles_standalone`/`dedup_propagate` accept them (file-scope externs are excluded from the lifted body → "not self-contained"). This is a missing gate-stage recovery step.
  - **(gotcha) saved best_drafts get clobbered** by later worse attempts (func_8015126C's close=0 winner was overwritten by a close=2/case-broken copy). Trust the gate, re-derive from match_one.
  - **(gotcha) propagation is slow** (134 overlay builds) — run dedup_propagate in the background, not a 2-min foreground (a SIGTERM leaves a partial non-atomic state: macro + instantiations applied, registry unwritten).
  - **(T4 hypothesis)** the other close=0 giants (func_80156B74 214, func_8014F74C 174, func_80163C2C 167, func_80178004 165) likely unblock with the SAME canonical-extern + block-scope recovery → a deterministic near-free wave.
- 2026-06-26: **T1 CLOSED — func_8015126C banked ×134, fleet 63.18%→63.22%, `make check-all` 136/136 byte-identical, dedup-check 1617 validated/0 failed.** The full loop is proven end-to-end (hand-crack → bank → ×134 propagate → fleet-verify). Calib draft saved at `.run/drafts-t1-calib6/`. Reusable canonical-extern recovery: extract each engine_core.h callee's def-sig, rewrite the draft's extern to it, move ALL externs block-scope; then harvest_verify + dedup_propagate (run propagate in BACKGROUND — foreground gets killed; and `git checkout src/` does NOT revert `config/dedup.us.yaml`, so reset BOTH on a redo).
- 2026-06-26: Drew Q — decomp.wiki/compilers/GCC patterns: ~6 useful for us (PS1 gcc-2.7.2-psx). Top for giants: **negative-struct-offset-in-loops** (`for(...;ptr++)` → directly addresses func_801412A8's offset-fold residual), **branch-invariant code duplication** (alt to §17 pins for call-crossing regalloc swaps), **load-coalescing** (`if(t->a||t->b)`→`lw`). Also: div magic-constant table, s16/s8 div-by-2, gcc-2.7.2.x `slti …,0`. N/A to PS1: `bnel`-likely (MIPS II+), `.lit4` NOPs (PS2), C++ bool (C only). → fold the 3 top into cookbook in T3.
- 2026-06-26: **close=0-giant fan-out probed — R14 REFUTES "near-free" (only func_8015126C was pure-extern).** Of the 5 close=0 giants: func_8015126C #1 pure-extern (BANKED); func_80156B74/func_8014F74C/func_80163C2C #3 STRUCT-walled (local `struct S8`/`B8` collide w/ TU — need type-lift); func_8014F74C also #2 masked-residual (§27, permuter); func_80178004 #4 regressed draft (DIFF 91, re-derive). The canonical-extern lever is real but the group is NOT uniformly near-free. **T3 captured:** cookbook §28 (the 4-way close=0 triage + the canonical-extern recovery + the coalescing pin) + §28a (decomp.wiki PS1 patterns) + `tools/recover_giant.py` (promoted). Net giant strategy unchanged: genuine per-giant hand-work (T2), grinder for the masked/coalescing tail (T5).
- 2026-06-26: **Session paused at a clean checkpoint (Drew).** T0/T1/T3 committed; T5 grinder started then STOPPED for handoff (banked 0). Reports regenerated. Tree clean (only R23 db churn). Resume from the ▶ RESUME HERE block → T2 giants. Grinder is OFF (STOP sentinel) until a fresh session restarts it.
- 2026-06-26 (new session, effort **xHigh** — Drew testing xHigh vs Max on giants): tasklist rebuilt (R28); T2/T3/T4 reframed as a recurring cycle (Drew). **T2 giant #1 BANKED: func_80156B74 (214 ins) ×134** — the struct-walled close=0 trio's lever proven. Method (→ cookbook §28b): lifted the `S8`/`B8` typedefs from ov_SC01_077.c's prelude block to `src/shared/engine_types.h` (shared fleet-wide; byte-neutral verified on resident + 2 overlays), removed the dup typedefs, `recover_giant.py` (block-scope externs) → whole-binary `harvest_verify` MATCH → `dedup_propagate` ×134. **Fleet 63.22% → 63.25%** (function-count; +28,676 ins byte-weighted), `make check-all` **136/136**, dedup-check **1618**/0 failed, 0 NON_MATCHING. Gotcha hit + fixed: a concurrent `make` job (check-all racing dedup_propagate) corrupted an `.o` AND dropped the propagation's registry write — re-ran dedup_propagate (idempotent) to register; **lesson: serialize all make jobs** (cookbook §28b-6). NEXT: func_80163C2C (167, Blk16/Buf32 — same type-lift lever; recovered draft staged in `.run/drafts-t2/`).
- 2026-06-26 (xHigh): **T2 giant #2 BANKED: func_80163C2C (167 ins) ×134** — same type-lift lever. Lifted `Blk16`(u32×4) + `Buf32`(2×Blk16) to engine_types.h, removed the Blk16 dupes from ov_SC01_077.c AND ov_SC01_077_a.c (the -O0 split), byte-neutral verified → recover_giant → harvest_verify MATCH → dedup_propagate ×134. **Fleet 63.25% → 63.29%** (+22,378 ins byte-weighted), `make check-all` **136/136**, dedup-check **1619**/0 failed. Struct-walled close=0 trio DONE (func_80156B74 ✓, func_80163C2C ✓; func_8014F74C is masked-residual → grinder fuel, not type-liftable). **Tool quirk (recurring, benign):** dedup_propagate's first full run applies source + registers but its per-overlay byte-gate output didn't appear in-log; the authoritative gate is the post-bank `make check-all` (136/136). NEXT: restart grinder (T5) on permuter-class giants; hand-decomp func_80132784 (400, close=240, §17 pins GTE-section regalloc — the big one).
