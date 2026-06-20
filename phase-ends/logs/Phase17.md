# CURRENT PHASE — Phase 17: Raise the harness ceiling to "eureka level", then gate the compute run

**Generation:** Gen2 (9th phase) · **Arc:** 8→9→10→11→12→13→15→16→**17** (14 deferred to Gen3+)
**Plan approved (gate 1):** 2026-06-19 (Drew) · **Status:** T1–T6 DONE & committed (`commit:0129`→`commit:0133`).
The "raise the ceiling" thesis FAILED across all 5 avenues → **PIVOT to guided hand-matching** (see START
HERE). T7 (go/no-go + PhaseEnd) is reframed: NO-GO on brute force, GO on hand-matching pending the demo.

> Approved plan: `~/.claude/plans/plan-mode-enabled-deep-reserach-reactive-toucan.md` (the durable copy of
> the deep-research findings + the task design). This file is the per-task crash-recovery log (P3/R28).

## 🚩 START HERE (fresh session 4, after session 3) — BUILD THE CANONICAL-SIG LAYER, then scale the wave
**Guided hand-matching is GO and proven at scale.** Demo (session 2) = 4/5; session 3 = the calibration
Ultracode wave (+0.47% → fleet **55.51%**, 136/136 byte-identical, committed `commit:0136`/`commit:0137`/`commit:0138`).
**The bottleneck is now identified and singular** — read `docs/hand-matching-process.md` §7 first.

**THE FINDING:** in the calibration wave the agents hit **60% match_one MATCH but only 33% whole-binary**, and
the entire gap is **SIG CONFLICTS** (parallel agents declare shared callees like `func_80131CA8` with
different sigs → they conflict when built in the one big TU; 100% of failures were compile-errors, ZERO
codegen). `sig_unify` auto-recovered 2/9. **The canonical-sig layer is the essential ~2× yield enabler.**

**NEXT TASK (Max, ultracode OFF — deep design):** build the **canonical-sig layer** before scaling:
1. Identify the high-frequency shared callees among the targets (the ones that conflict — `func_80131CA8`,
   `func_80131E00`, `func_801472C8`, `func_8001D074`, …).
2. Establish ONE canonical sig per shared callee — match the shared-callee residuals **first** (callees
   before callers, so their def fixes the sig), or derive the sig from the asm/usage and seed `engine_core.h`.
   (Surgical/byte-gated per-callee — NOT a blanket global decls header; Phase-16 proved a global header breaks
   loose matches, but the demo + sig_unify prove per-callee canonicalization works.)
3. Enforce it in the wave (agents reference engine_core.h + a strengthened `sig_unify` post-pass).
Then **scale the wave** to the remaining ~270 targets (`.run/harvest_targets_s3.json`, sorted by reach), in
Ultracode batches (R26/R27 — prompt Drew for `/effort ultracode`), gate (`harvest_verify`), propagate
(`dedup_propagate --auto-from ov_SC01_077`), `make check-all` (R22), `make report`. Then **T7 close + PhaseEnd**.

**REUSABLE HARNESS (all in place):** `tools/ghidra_scripts/DecompileFunctions.java` (headless batch Ghidra-C —
NO /mcp needed; re-run: stop MCP, `analyzeHeadless ghidra bfm -process ov_SC01_077 -noanalysis -postScript
DecompileFunctions.java <addrfile> <outdir>`); `.run/ghidra_c/func_<ADDR>.c` (300 cached); `.run/harvest_wave_s3.js`
(Workflow — **targets EMBEDDED, edit LIMIT**; the `args` channel does NOT transit arrays); `.run/harvest_targets_s3.json`
(300 tractable, relocs≤5, reach-sorted); `tools/harvest_verify.py` (whole-binary gate — use `--chunk 1` to avoid
cross-draft conflicts masking good drafts); `tools/sig_unify.py`; `tools/dedup_propagate.py`. Idioms + the full
calibration writeup: `docs/hand-matching-process.md` §2/§4/§6/§7; `docs/matching-cookbook.md` §16.

**Giant `func_80144B9C` DEFERRED** (call-heavy = hardest class; reassess after the canonical-sig-layer'd wave).
**A-only (Drew):** quirk tail stays `INCLUDE_ASM` stub — NO NON_MATCHING correct-C track until public.

---

## 🚩 (SUPERSEDED — session 3 demo protocol) START HERE — PIVOT to guided hand-matching, then a demo

**What happened:** Phase 17 tested all 5 planned avenues (T1–T6 below, done & committed). **The harness
ceiling did NOT rise to "eureka":** T2 = 0 functions, T3 = +0.52% (banked, real), T4/T5 = byte-neutral,
T6 permuter = 0 whole-binary. Drew + Claude then chatted strategy (outside the original task plan); the
decisions + everything the next session needs are captured here.

**DECISIONS (Drew, 2026-06-19):**
- **NO-GO** on the 5-day unattended brute-force run with the current strategy (it would bank ~0 *real* matches).
- **GO** on **guided hand-matching**: Claude hand-writes byte-exact C for the hard functions, **gated against
  the whole binary**. It's the only *proven* path on hard functions (it's how all 187k existing matches landed),
  the actor struct now accelerates it, and each giant propagates **×134** across the fleet.
- **After** the demo + the Phase-17 PhaseEnd: **plan-mode a NEW phase** for a **whole-binary-gated permuter
  driven by Ghidra-C** (the untried, correct-target automated approach — fixes T6's exact flaw).

**THE DEMO — do this first (this session):** prove the loop on ONE medium (~50–100 ins) struct-using function,
then escalate to a **giant** for the ×134 payoff. Protocol:
1. Pick a `STRUCTURAL_MISS` fn that accesses `arg0` (the actor struct) from `.run/wall_taxonomy.json`.
   Medium loop-proof candidates: **func_801298F4 (53 ins), func_8012A328 (60)**. Giants (×134, max leverage):
   **func_80144B9C (770, bad-deref/struct), func_8017C974 (947, jtbl), func_80178D40 (890, jtbl), func_80141CA4 (476)**.
2. Get the richest decompile: `tools/decompile.py <fn> --context .run/actor_ctx2.c` (m2c + the actor struct)
   AND Ghidra `get_code(<addr>)` (needs `/mcp`; richer for complex control flow).
3. **Hand-write CORRECT C:** fix m2c's structural errors; use the actor struct fields (`docs/actor-struct.md`);
   resolve callee signatures from `src/shared/engine_core.h` / `tools/gen_harvest_targets.py` (the §14c canonical set).
4. **Iterate against the WHOLE-BINARY GATE, never match_one alone:** substitute into
   `src/ov_SC01_077/ov_SC01_077.c` → `make build BINARY=ov_SC01_077` → SHA must equal
   `d19c9580a02dc63ba1f0e7e0c770f3b10de35635`. Use asm-differ (`diff_settings.py`, env `BFM_BINARY=ov_SC01_077`)
   for the per-instruction diff to converge. (`tools/harvest_verify.py` does substitute+build+gate+revert.)
5. When byte-identical: `tools/dedup_propagate.py --auto-from ov_SC01_077` (×134) → `make report` +
   `make check-all` (R22, 136/136) → commit. **If it lands, the go/no-go becomes "GO on guided hand-matching."**

**THE CRUX (why the demo must gate whole-binary):** match_one AND the permuter optimize an *isolated*,
relocation-MASKED target — they mask `jal`/`%hi`/`%lo`, so they CANNOT verify call/data targets. An isolated
"MATCH" does NOT imply a whole-binary match (T6 proved it: isolated MATCH but 0/4 whole-binary). **The
whole-binary build is the only truth (G3/P9).** Get the externs/callees sig-consistent with the 077 TU or the gate fails.

**THE ACTOR STRUCT (the hand-matching asset):** base **`0x80078E00`**, ~154 fields / 0x24C bytes. Confirmed
(live, R10): HP `+0xB4` (u16), BP/stamina `+0xB8`, gold `+0x8C`, day `+0xAC`, hour `+0xB1`, position
`+0x108/+0x10C` (s16), dispatch-state `+0x14/+0x15`. Pointers: `+0x54/58/5C/68/6C/70` + ~26 code-inferred.
Files: `docs/actor-struct.md`, `.run/actor_fields.json`, `.run/actor_struct.h`, `.run/actor_ctx2.c` (m2c context).
**Byte-neutral for m2c (proven) but ESSENTIAL for HAND-writing correct C** (it's the comprehension that lets a
human/Claude fix m2c's structural errors).

**TOOLING MAP:** `harvest_verify.py` = THE whole-binary byte-gate (the arbiter — NOT match_one). `decompile.py
--context` = m2c scaffold. `dedup_propagate.py --auto-from ov_SC01_077` = ×134 propagation. Ghidra MCP
`get_code` = richer decompile. asm-differ via `diff_settings.py` + `BFM_BINARY`. **Note:** the whole fleet must
be extracted before propagation/`check-all` (`for b in $(BINARIES); do make extract BINARY=$b; done` — done
this session; a fresh `make clean` requires re-running it, ~5 min).

**DEFERRED / decided — do NOT re-litigate:**
- **CUDA/ML brute-force:** CUDA can't run gcc-2.7.2; the bottleneck is the gcc compile + the whole-binary gate,
  NOT search speed, so raw GPU permutation doesn't apply. The real ML angle = a *learned gcc-2.7.2 codegen
  predictor/ranker* (Drew has CUDA + LightGBM skills) — a high-risk, months-long research wildcard, a *bounded
  future experiment*, NOT the plan. No off-the-shelf byte-exact MIPS/gcc-2.7.2 decompiler exists (Phase-16 research).
- **Actor-struct emulator field-NAMING pass:** PAUSED (comprehension/decomp.me value only — byte-neutral).
  PCSX-Redux reachable at `172.17.208.1:8081` (host saved in `.run/ram/HOST.txt`); `tools/ram_probe.py` is the
  workhorse. Bincho-field mechanics noted in chat (a clean discrete event for later field-naming).

**EFFORT:** **Max** for hand-matching (Tier-1, deepest single-function reasoning) — re-set it (session-only;
the saved default is now xHigh). **MCP:** the SessionStart hook restarts the Ghidra server → run `/mcp` when
prompted, then one cheap `get_binary_info` (G2) before any `get_code` (R29).

## Why this phase (one paragraph)
Phase 16 proved the m2c→permuter brute-force tops out at ~3% on the ~964 struct-heavy **shared** engine
functions; a 5-day/32-thread unattended run at that ceiling buys only ~3% fleet — too low to commit. Drew's
decision: **pursue ALL avenues to raise the harness's per-pass yield from single-digit to "eureka level"
BEFORE the run**, measuring with *attended* trials as each lever lands. Deep-research (this session) revised
the premise: type recovery is NOT a blanket match-% lever (global type-prop *breaks* loose matches; struct
def is byte-neutral for fns m2c gets right) — BUT it unlocks a *subset* (m2c structural-misses, fn-ptr
tables) + comprehension. The matching path is **m2c + rich `--context`** (not Ghidra-C). A named,
never-built deterministic lever exists: the DATA-symbol byte-array canonical header (cookbook §14c-c).

## Goal & milestone (P9, observable)
Widen the matchable/permuter-viable draft set across all avenues so the *measured* ceiling (known-answer
re-derivation rate + attended-trial yield) climbs from single-digit to eureka level → then an evidence-based
go/no-go on the unattended run. **Milestone (gate 2):** measured ceiling rise (ladder + trial evidence) +
go/no-go decision with projected run yield; all 136 binaries still byte-identical (R22); findings folded into
`docs/matching-cookbook.md` + `docs/struct-core-pivot.md`. (Open-ended like Phase 15 — monotonic rise, zero
regressions, not a fixed-% gate.)

## Baseline (phase start)
- `make check-all`: 136/136 binaries byte-identical from clean (main `143dbb89…`, resident `8e17e02f…`, 134 overlays).
- `make report`: FLEET REAL 185,779 / LINKED 959 / **54.48% byte-identical-from-source** / 0 NON_MATCHING / 1395 dedup groups.
- ~964 struct-heavy shared stubs remain in `ov_SC01_077` (the harvest source).

## Tasks (one commit per task, P4/R8 cadence per Drew; sequencing of T2–T5 may reorder per T1)
- [x] **T1 — Wall taxonomy** [Max]. **DONE 2026-06-19.** `tools/wall_taxonomy.py` (new) censused all 957
  residual shared stubs → `docs/wall-taxonomy.md` + `.run/wall_taxonomy.json` (reproducible, ~22 s).
  Classifier validated against the real byte-gate (R14): SIG_FIXABLE_KR = exactly the gate-passing set (4/4).
  **Headline findings (drive T2–T5 sequencing):** T4+T5 rich-context (struct/jtbl/fn-ptr-table) = **67%** of
  residuals incl. all 30 jump-table giants; T6 permuter = 146 candidates (101 ≤4-mismatch); T3 sig_unify =
  48 gate-proven free wins; loose-typing WALL = 99 (10%); **T2 DATA-symbol header = 0 functions → recommend SKIP.**
- [ ] **T2 — Avenue 1: DATA-symbol byte-array canonical header** [xHigh]. Split `gen_engine_decls.py`; data →
  universal `extern u8 D_X[];`; overlay `.c` includes it; drafts strip own data decls. Probe (~20-30) → scale.
- [x] **T3 — Avenue 2: K&R loose-signature modeling** [Max]. **DONE 2026-06-19.** Banked **42** gate-proven
  `SIG_FIXABLE_KR` matches (of 48; 6 honestly reverted by the byte-gate) + propagated **13** ×134 fleet-wide →
  **fleet 54.48% → 55.00% (+0.52%)**, REAL +1,778, **136/136 byte-identical** (R22), dedup-check 1408/0.
  Probed the wall: raw drafts 0/99, sig_unify fails — and verifying against the bytes (R14) found a **T1
  classifier bug** (the "LOOSE_TYPING_WALL" was byte-neutral pre-existing warnings, not a wall). Corrected:
  real wall = **ARITY_WALL 74** (§14e dead-end); no K&R lever there. Avenue exhausted; rest is structural →
  T4/T5. (Did a one-time full-fleet `make extract`; fixed `wall_taxonomy.py` + amended `docs/wall-taxonomy.md`.)
- [~] **T4 — Avenue 3: m2ctx-style rich context generator** [xHigh]. **IN PROGRESS — mechanism proven,
  build pending.** Probe established: m2c `--context` declaring a fn-ptr table as an array makes m2c emit the
  correct `D_x[idx](arg)` call (vs the broken `*(&D_x+...)()`) — fixes the §15-S2 fnptr-call class. Decls reach
  drafts via the existing chain (`overlay.c → engine_core.h → engine_types.h`); redeclaration with the same
  type is byte-neutral. Matched code already carries **163 ground-truth fn-ptr-table types**; residual drafts
  use **186 tables** (175 drafts). **KEY LIMIT:** the fn-ptr fix *unblocks compilation* but does NOT byte-match
  the big functions (e.g. func_8015EA3C 197 vs 204 ins) — the real byte-lever is the **actor struct (T5)**.
  So T4's context generator is built **together with T5's struct** (the plan's intent). Next: write
  `gen_m2c_context.py` (fn-ptr-tables + canonical sigs[context-only, not a compile header — Phase-16] + data +
  structs), wire `--context` into the harvest, then T5 adds the inferred+emulator-typed struct. Scratch:
  `.run/t4_known_fnptr.txt`, `.run/t4_used_tables.txt`.
- [ ] **T5 — Avenue 4: struct inference + emulator field-typing** [Max + Drew emu]. Infer actor struct from
  m2c field-access union; Drew-driven PCSX-Redux field-typing (R10); feed via T4 context. Scoped to the
  structural-miss + fn-ptr buckets + comprehension.
- [x] **T6 — Avenue 5: permuter validation** [mixed]. **DONE 2026-06-19 — 0 whole-binary yield.** The
  permuter CLOSES isolated near-misses (3-4/8 in ≤75s; converted winners match_one MATCH 17/53/54 ins) but
  **0/4 survive the whole-binary gate.** Root-caused (R17): the isolated compile context ≠ the whole-binary
  TU (callee inlining in the one-big-file 077.c), so match_one's "isolated == whole-binary" assumption is
  FALSE for these — the permuter optimizes the wrong target and matches don't transfer. This is the mechanism
  behind Phase 16's "42% mirage." Making the permuter whole-binary-faithful = recompile the 7k-line TU per
  candidate = prohibitive for a search. **The last byte lever yields ~0.**
- [ ] **T7 — Go/no-go on the unattended run + phase close** [Max]. Present measured ceiling + projected run
  yield → decide; if GO deploy `auto_driver`+supervisor supervised-first; fold findings; PhaseEnd (R18/R25/R19).

## Verification discipline (every task)
`make clean && (extract all) && make check-all` → 136/136 (R22); `make report` fleet-% is the OUTCOME metric
(verify it, not just the gate — §14d); probe each lever on a ~20-30 known-answer sample before scaling (§14d);
0 NON_MATCHING in any default build (G4).

## Decisions / notes
- **bgIsolation disabled for this repo (2026-06-19, Drew-approved):** added `"worktree": {"bgIsolation":
  "none"}` to `.claude/settings.json` so sessions edit in place. The background-job worktree directive is
  incompatible with this project (R2/H2 single ext4 clone; clone-bound gitignored toolchain
  `.venv`/`tools/bin`/`disks/`; live Ghidra MCP bound to the main clone for T5; R6/R8/R20
  commit-on-`main`/Drew-pushes-via-GitHub-Desktop). HEAD==origin/main; origin unreachable from WSL (R6).
- **Execution deferred to a fresh normal session (Drew, 2026-06-19):** this session did the deep-research +
  Phase-Start planning (gate 1) only. The fresh session starts at T1 and, per R28, creates the live task list
  (one TaskCreate per T1–T7) before starting work.

## Blockers
- (none — unblocked once bgIsolation:none was set)

## Resequence after T1 — APPROVED by Drew 2026-06-19 (P5d gate passed)
**T3 (48 gate-proven free wins) → T4+T5 built together (rich context: struct + jump-table + fn-ptr-table
types — 67% reach incl. the giants) → T6 (validate the 146 permuter candidates, then close).** **T2 DROPPED**
(DATA-symbol byte-array header — addresses 0 functions). Task list updated: T2 deleted, T3 in_progress.

## Progress log
- 2026-06-19: Deep-research complete (3 agents, web+codebase, X2); findings revised Phase-16 premise (durable
  copy in the approved plan file). Phase 17 plan approved (gate 1, Drew). Resolved the bg-isolation/worktree
  conflict (bgIsolation:none, Drew-approved). CURRENT_PHASE.md written. Paused before T1 per Drew — execution
  resumes in a fresh normal session.
- 2026-06-19: **T1 DONE** (Max). Built `tools/wall_taxonomy.py`; censused all 957 residual shared stubs →
  `docs/wall-taxonomy.md` + `.run/wall_taxonomy.json`. Classifier byte-gate-validated (R14: SIG_FIXABLE_KR =
  4/4 gate-passing). Findings: T4+T5 context lever = 67%, T6 = 146 permuter candidates, T3 = 48 free wins,
  wall = 99, **T2 = 0 (skip)**. Baseline still 136/136 byte-identical (T1 was read-only; restored the .c
  after the gate validation). Recommended resequence recorded above; paused for Drew's nod before T2/T4.
- 2026-06-19: **Resequence APPROVED** (Drew): T3 → T4+T5 → T6, drop T2. Task list updated (T2 deleted).
- 2026-06-19: **T3 DONE** (Max). Banked 42 + propagated 13 ×134 → fleet **55.00% (+0.52%)**, 136/136 R22 green.
  One-time full-fleet `make extract` (needed for per-overlay propagation gate + check-all). Verifying the wall
  against the bytes (R14) exposed + fixed a T1 classifier bug (LOOSE_TYPING_WALL was byte-neutral warnings →
  real wall is ARITY_WALL 74); `wall_taxonomy.py` fixed, `docs/wall-taxonomy.md` amended. Avenue exhausted.
  **NEXT: T4 (m2ctx rich-context generator) [xHigh] — prompt Drew for the /effort toggle (R27).**
- 2026-06-19: **Effort → xHigh** (Drew, saved default). **T4 investigation** (xHigh): proved the m2c-context
  fn-ptr-table mechanism (m2c emits correct `D_x[idx](arg)` calls with the type in context); mapped the
  byte-safe shared-header integration; collected 163 ground-truth + 186 used tables. Found the fn-ptr fix
  unblocks compilation but the byte-lever is T5's struct → build T4 generator + T5 struct **together**.
  Checkpoint: no committable artifact yet (probes in `.run/` scratch; tree clean, 077 d19c9580). **T5 needs
  Drew's PCSX-Redux emulator field-typing pass — scheduling pending.**
- 2026-06-19: **T4 + T5 DONE — byte-neutral (negative result, like Phase 16).** Recovered the actor struct
  cold via PCSX-Redux (base `0x80078E00`, ~154 fields, 32 pointers; HP/BP/gold/day/hour/position all
  live-verified, anchored to Phase-3) → `docs/actor-struct.md` + `tools/ram_probe.py`. m2c **adopts** the
  struct (`arg0->f_X`) but it's **byte-neutral**: structural-miss sample 0 better / 10 same / 2 worse (proven
  with the full pointer set). The misses are 50–98% mismatched = m2c decompiler limits, not missing types. T4
  fn-ptr context unblocks compilation but the functions stay structural. **Rich context is a comprehension /
  decomp.me win, NOT a byte lever** (deep-research caveat confirmed; struct-core-pivot.md updated). Emulator
  pass PAUSED (Drew). **NEXT: T6 — validate the permuter on the 146 PERMUTER_CLASS near-misses (the last
  untested byte lever), then T7 go/no-go.**
- 2026-06-19: **T6 DONE — permuter yields 0 whole-binary matches.** Closes isolated near-misses but the
  winners don't transfer (isolated≠whole-binary TU; callee inlining). All 5 avenues now tested: T2=0,
  T3=+0.52% (banked), T4/T5 byte-neutral, T6=0. **The harness ceiling did NOT rise to eureka.** NEXT: **T7 —
  go/no-go (recommend NO-GO on the big unattended run) + PhaseEnd. Tier-1/Max — prompt Drew for /effort Max.**
- 2026-06-19 (session 2, Max): **DEMO DONE → GO on guided hand-matching.** Pivoted from brute-force to the
  Ghidra-driven hand-match loop (Drew steered to Ghidra whole-binary for local/global). Sampled **5 residuals,
  4 CLOSED (80%)**: **func_8012D3B4** (PERMUTER_CLASS, CLOSED + propagated **×134**); **func_8012832C**
  (STRUCTURAL_MISS switch, CLOSED); **func_8015F89C** (fnptr-call §15-S2, CLOSED); **func_80147B5C**
  (pure struct, CLOSED first-try); **func_8012A328** (STRUCTURAL_MISS globals+call) = 60/60 structure +
  correct registers but **1-instr gcc placement quirk** (§10 hard tail; permuter floor-polluted — the only
  miss). 🔑 **KEY FINDING: the Phase-16 "loose-typing wall" is NOT fundamental —
  it's a signature-CONSISTENCY problem that dissolves via byte-neutral canonical-widening (void→s32 for
  $v0-returning fns) + the (u16)/(s16) cast idiom.** 4 widenings this session, fleet re-verified **136/136
  byte-identical** (R22); fleet **55.00%→55.04%**; dedup-check 1409/0. **Full process + idioms + current state +
  automation notes captured durably in `docs/hand-matching-process.md`** (so a fresh session loses nothing).
  Drew's plan (in order): **sample 1-2 more (struct-using + fnptr-call) → prove the giant func_80144B9C →
  build the canonical-widening pass + harvest → document fully + automate.** Tasks 5/6/7 created. **NEXT:
  sample 2 more, then the giant.** Effort: Max (hand-matching, Tier-1).
- 2026-06-19 (session 3, normal Max→Ultracode): **TASK 1 (sample 2 more) DONE + DECISION + CALIBRATION WAVE DONE.**
  - **Task 1:** banked **func_8015F9A4** (fnptr, ×1, CLEAN) `commit:0136`; 3 struct near-misses had 100%-correct
    bodies but gcc-quirk tails (§10 remat, phantom -O2 frame, v0/v1 coalescing — even the permuter couldn't
    close relocs=0 func_8014C308 in 12min). New idioms → hand-matching-process.md §2 (mask-local; shared-ret0
    goto). **Selection lesson:** low-m2c-mismatch struct = the quirk tail; clean closes = fnptr/relocs-low/
    m2c-mis-structured. **Sizing (§6):** tractable easy classes are LOW-reach; ×134 yield is in quirk-heavy
    STRUCTURAL_MISS(7.6%)/PERMUTER_CLASS(3.6%). Permuter route refuted (T6 callee-inlining).
  - **DECISIONS (Drew):** (1) "decompile to correct C, defer byte-perfect?" → **A-only**: byte-match tractable
    classes; quirk tail stays INCLUDE_ASM stub (NO NON_MATCHING correct-C track until public). (2) **harvest
    tractable first; giant func_80144B9C DEFERRED** (call-heavy = hardest). (3) **Ghidra pre-pass YES.**
  - **Ghidra pre-pass:** `tools/ghidra_scripts/DecompileFunctions.java` (headless batch — NO /mcp needed) →
    300 Ghidra-C cached to `.run/ghidra_c/func_<ADDR>.c` (high quality, better than m2c on local/global).
  - **CALIBRATION WAVE (Ultracode, `.run/harvest_wave_s3.js`, top-30 by reach):** 18/30 match_one MATCH (60%);
    **10/30 whole-binary verified (33%)** after sig_unify recovered 2 → propagated ×134 (+2 demo catch-ups);
    **fleet 55.04%→55.51% (+0.47%), 136/136 (R22)**, `commit:0137`. **KEY FINDING: the match_one→whole-binary gap
    (60%→33%) is 100% SIG CONFLICTS** (shared callees like func_80131CA8 declared inconsistently across
    parallel agents), NOT codegen → **the canonical-sig layer is the ESSENTIAL enabler** (would lift 33%→~60%,
    ~2× yield/token). 12/30 = genuine gcc-quirk tail. **NEXT (scaling, Max):** build the canonical-sig layer
    (establish/enforce shared-callee canonical sigs; match shared callees before callers), then scale the wave
    to the remaining ~270 targets (`.run/harvest_targets_s3.json`). Then T7 close.
- 2026-06-19 (session 4, Max): **CANONICAL-SIG LAYER BUILT + a key sizing correction (R14/P9).**
  - **Tools (new, committed):** `tools/census_conflict_callees.py` (the accurate conflict predicate:
    undeclared-stub callee with `decl_sources = n_callers + is_target >= 2`) + `tools/derive_canonical_sigs.py`
    (byte-neutral canonical = `s32` return + `s32`/arity params; arity from Ghidra-C cache AND asm
    read-before-write `$a0-$a3`, agreeing on all 14 cached, 6 stubs call-site-validated).
  - **THE LAYER:** 20 conflict callees (14 are themselves wave targets / 4 at reach-134; 6 non-target stubs)
    declared once as a file-top `extern s32 ...` block in `src/ov_SC01_077/ov_SC01_077.c` (LOCAL, NOT
    engine_core.h — reach-1 names like func_801809BC differ across overlays; it's matched in ov_SC03_096).
    `gen_harvest_targets` + `sig_unify` both already read ov_SC01_077.c → the layer auto-wires (no tool change).
    Census after: **conflict callees 20→0, blocked targets 24→0**. Byte-neutral: ov_SC01_077 clean-rebuilds
    `d19c9580` (R22). sig_unify test: rewrites a wrong `extern void func_801758FC(s32)` → canonical
    `extern s32 func_801758FC(void)`. ✓
  - **SIZING CORRECTION (R14):** the §7c "~2× scaling lever" was measured on the top-30's IN-FLIGHT conflicts;
    since those callees got banked the wall shrank. For the remaining 270 it is **only 20 callees / 24 targets /
    7% of wave reach** — a modest unblock, NOT the dominant lever. The wave's real ceiling is the gcc-quirk tail
    (§2/§10), unchanged by the layer.
  - **PIPELINE CHANGE (required):** harvest_verify uses an ACCUMULATING baseline from ov_SC01_077.c (now with
    the file-top block) → a raw draft's own guessed extern would clash with the block even at `--chunk 1`. So
    the wave gate is now **draft → sig_unify (MANDATORY, normalizes to the file-top canonical) → harvest_verify
    --chunk 1 → propagate** (sig_unify was previously a recovery-only pass).
  - **NEXT (Drew decision pending — R27 Ultracode prompt + the resized expected value):** scale the wave (task 5,
    needs `/effort ultracode`) vs. a focused Max session matching the 4 reach-134 circular targets + tractable
    high-reach subset by hand. Layer done (task 2); sig_unify wired (task 3). Tasks 4/5/6/7 open.
- 2026-06-19 (session 4 cont., Max): **TASK 4 — hand-matched the 4 reach-134 circular targets (Drew chose A);
  ALL 4 are gcc-quirk/regalloc/layout-bound → 0 banked. Layer validated independently; the finding is the
  high-reach core IS the quirk tail (confirms §4).** Drafts in `.run/drafts-s4/` (scratch, none gated).
  - `func_8012B4B8` (matrix transform): **§10 stack-addr rematerialize-vs-hoist** — gcc caches `&mtx` in a
    callee-saved reg (3 saved); the original re-materializes `addiu $a1,$sp,0x10` per call (2 saved). Not
    source-steerable (2 variations tried).
  - `func_8012B8E4` (angle-diff + `--expand-div`): **structurally PERFECT (75=75)**, down to a `$s0/$s1`
    regalloc swap + a reassociation = 24-mismatch near-miss. **Permuter probe (external callee `ratan2` →
    T6 inlined-callee concern does NOT apply): base 530, NO improvement in 90s** → not in the permuter's
    randomization space (§3). Scratch `.run/permuter/func_8012B8E4/` (reusable: header+macro.inc → target.o).
  - `func_8016A8FC` / `func_80169A4C`: **local-struct-builders** (stack-layout/scheduling-bound). Assessed hard.
  - **CONCLUSION:** the layer makes the high-reach circular targets *declarable* but they are the **gcc-quirk
    tail, not the sig-conflict wall** — the layer doesn't unlock them. Its value: a **sig-conflict-clean wave**
    banking the TRACTABLE (mostly lower-reach) subset. **Wave yield is quirk-tail-limited (~2-4% fleet), NOT
    ~2×.** This IS the task-7 go/no-go input. **Decision pending (Drew): run the layer-clean wave (task 5,
    /effort ultracode) vs. close Phase 17 + defer the wave to a dedicated/unattended run (Phase-16 auto_driver).**
