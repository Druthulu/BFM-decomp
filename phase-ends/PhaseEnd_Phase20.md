# PhaseEnd — Phase 20: Close the propagation cap, crack the gcc residual classes, then scale the waves
**Date:** 2026-06-21 · **Project Version:** 1.19.0 · **Phase Status:** Complete (open-ended phase, closed at a clean checkpoint — Drew, gate 2) · **Generation:** Gen2 (12th phase)

> Gen2 phase 12 of the arc (8→9→10→11→12→13→15→16→17→18→19→**20**; 14 deferred to Gen3+). Ran across **multiple
> sessions**; the granular per-task/per-session trail (the T1 type-lift, the T6 wave, the cap-tool diagnosis, the
> -O0/data-cast byte-proofs, the T3a crack) is preserved on-demand at **`phase-ends/logs/Phase20.md`** (R19 — NOT
> auto-loaded; consult only when researching a mechanism). This file is the synthesis. Owner decisions (Drew):
> class-crack first + skip the permuter grind (this phase); then exhaust the cheap-recovery levers in order
> (cap-tool → -O0 rollout → data-cast → T3a); **close Phase 20 at a clean checkpoint** and do the **automation
> architecture as a fresh-session, plan-mode Phase 21** (the approved design is the Phase-21 Backlog below).

## Build Log

**Files created/changed and complete — do not recreate:**

*New reusable tooling (the phase's durable output):*
- `tools/cast_call_sites.py` — **(THE cap tool, cookbook §20)** the §17a-1 per-site function-pointer cast recovery
  for the loose-typing CALLEE-conflict class. Pure `--in`/`--out` draft transform (sibling of sig_unify /
  canon_resident_calls): per draft, for each callee whose canonical TU sig differs from the draft's intended sig,
  rewrite the decl line → canonical (kills the in-TU `conflicting types`, keeps the symbol in scope) AND cast each
  call site → the draft's intended sig `((ret(*)(args))func_X)(args)` (decl lines never cast; gcc folds the cast of
  a known symbol → direct `jal`). Whole-binary gate is the sole arbiter (G3/P9). Pipeline:
  `canon_resident_calls → cast_call_sites → sig_unify → harvest_verify --chunk 1`.
- `tools/build_engine_types.py` — **(T1, extended)** added `find_typedefs()` (brace-aware anon-struct / fn-ptr /
  alias typedefs) + same-name-different-layout collision + tagged-struct-typedef overlap guards; emits typedefs
  after named structs in dep order. Closed the §19 type-blocked propagation cap.
- `tools/exemplar_miner.py` — **(T2)** residual router: `wall_taxonomy.json` + per-overlay reach →
  `docs/exemplar_curriculum.md` + `.run/exemplar_routing.json` (WAVE/STRUCT/PINS/STUB pools, reach-ranked).

*Config / source (the matches):*
- `src/ov_SC01_077/ov_SC01_077.c` + `src/shared/engine_core.h` + `config/dedup.us.yaml` + the 134 overlay `.c`
  files — T1's 9 typedef-freed fns ×134, T6 batch-1's 8 (7 ×134 + 1 local), the cap tool's 6 (5 ×134 + 1 local),
  all byte-gated + propagated. `config/dedup.us.yaml` **1485 → 1513** validated cross-binary groups (0 failed).
- `src/ov_SC01_077/ov_SC01_077_o0.c` — **(T3a)** func_8013B7AC matched via the array-of-struct `%lo`-fold idiom
  (×1 — the -O0 cluster is overlay-local).

*Docs / knowledge base (R16 flywheel, R21):*
- `docs/matching-cookbook.md` — **§20** (NEW: the wave-at-scale GATE CAP = loose-typing call-graph wall; the cap
  tool RESOLUTION + the R14 re-diagnosis = DEF-side wall dominates, not callee-conflicts; the data-cast MOOT
  finding; the confirmed-irreducible classes store-vs-load / hoist-vs-remat / IV-combine / hoisted-invariant /
  the -O1 class; the stale-`.o` + args-as-array + `--chunk 1` gotchas) + **§18** (T3a `%lo`-fold CRACKED via
  array-of-struct + the -O0-cluster-is-overlay-local R14 correction) + **§17a** (the gate-cap framing).
- `docs/SETUP.md` — `cast_call_sites.py` tooling-inventory row.
- `README.md` / `docs/{progress,difficulty,duplicates}.*.md` — Phase-20 status + regenerated digests.
- `phase-ends/CURRENT_PHASE.md` → **`phase-ends/logs/Phase20.md`** (R19 archive). `phase-ends/PhaseEnd_Phase20.md` — this file.

**Local artifacts (gitignored / regenerable):** `.run/drafts-t6-*` (wave + cast + sig_unify recovery stages),
`.run/drafts-t3a/*`, `.run/ghidra_c/*` (300 cached Ghidra-C), `.run/exemplar_routing.json`,
`.run/harvest_*.txt`, `build/`, `expected/`, `asm/`, `assets/`. The 134 overlay Ghidra programs are
script-reproducible (DB-commit deferred as regenerable).

**Tools/packages installed:** None — the whole phase used the existing Phase-4/6/10/11/12/13 toolchain + venv.

**Verification results (literal) — the milestone proof:**
- **`make check-all` → 136 passed, 0 failed of 136** (main `143dbb89…`, resident `8e17e02f…`, ov_SC01_077
  `d19c9580…`, all 134 overlays), reproduced from clean after every banked step (R22). A stale-artifact false
  failure (ov_SC01_005, from the reverted -O0 test) was caught by check-all and cleared by a clean re-extract —
  see Deviations.
- **`make report`:** FLEET byte-identical **202,350 / 344,010 = 58.82%** (phase start **58.00%** / 199,541 →
  **+0.82%**); LINKED 959; **dedup 1485 → 1513 validated, 0 failed**; **0 NON_MATCHING** in any default build (G4).
- **Phase arc (banked):** T1 type-lift **+0.35%** (9 fns ×134) · T6 batch-1 **+0.28%** (8 matches) · the cap tool
  **+0.19%** (6 matches) · T3a func_8013B7AC (×1). The cracks/findings (below) are the durable non-% value.
- `git status`: only `config/`/`tools/`/`src/`/`docs/`/`phase-ends/` tracked; zero ROM-derived/generated bulk
  staged. **No Ghidra DB change** this phase (matching used cached Ghidra-C + asm; the `db.*.gbf` churn is
  SessionStart-restart noise — R23 no-op, NOT staged).

**Milestone achieved (confirmed by Drew, gate 2):** the open-ended phase is closed at a **clean checkpoint** —
fleet rose **58.00% → 58.82%**, **136/136 binaries byte-identical**, **0 NON_MATCHING**, with three reusable
tools (the cap tool, the typedef-lift, the residual router), the **gcc-2.7.2 codegen map** distilled (cookbook
§20), the **T3a `%lo`-fold class CRACKED** (array-of-struct idiom — a long-"irreducible" residual, now a reusable
cookbook idiom), and **three byte-proven strategic findings** (R14) that retire two dead levers and sharpen the
roadmap: the cap is the **DEF-side loose-typing wall** (not callee-conflicts), the **-O0 cluster is overlay-local**
(the ×134 rollout is invalid), and **data-cast is moot** (0 real data conflicts).

**Next:** **Phase 21 — the automation architecture** (the "automation manager" / supervised-autonomous grind).
A fresh session, **plan mode** (Tier-1). The full approved design + the 6 build-pieces are the **Phase-21 Backlog**
below — plan from it.

## Deviations
| Item | Plan | Actual | Reason |
|---|---|---|---|
| The cap "~33" recovery | the §20 cast tool recovers the batch's lost ~33 | **6 recovered** | R14 re-diagnosis: the 33 are NOT mostly callee-conflicts (the cast tool's class); ~18 are the DEF-side loose-typing wall (byte-proven both ways), + a DATA tail. §20 corrected. |
| -O0 ×134 rollout | bank the 6 matched -O0 fns ×134 (~+0.6% "free") | **INVALID — skipped** | R14 byte-proof: only 1/134 overlays shares the cluster bytes; the fns reference per-overlay data → overlay-local. Built+reverted the split infra; cookbook §18 corrected. |
| data-cast extension | complete the cap tool with `*(T*)&D_x` | **MOOT — not built** | R14 byte-proof: 0 drafts have a real data-type conflict; the lone case was a typedef-redef masking the def-sig wall. |
| T3a `%lo`-folding | likely cite-irreducible (§18 wall) | **CRACKED** | the array-of-struct idiom folds `%lo` (the failing forms materialize `&sym`); a better-than-expected result. |
| T3b/T3c | crack-or-cite | **cited** (T3b R14-reframed strength-reduction; T3c store-vs-load confirmed unsteerable, sched.c) | genuine compiler residuals; byte-evidenced verdicts in §20. |
| Phase close | grind T5 waves + giants | **closed at a clean checkpoint; automation → Phase 21** | Drew: the cached ≤90-ins tail is byte-exhausted; the autonomy is a Tier-1 architecture deserving a fresh plan-mode phase. |
| ov_SC01_005 check-all | (n/a) | **stale-artifact false-fail caught + fixed** | the reverted -O0 test left a stale `.ld`/asm (3-way split); `make check` doesn't re-extract → linked a deleted `.o`. Clean re-extract restored `56760dbe`. → the R22 corollary (a reverted *config* needs a re-extract). |
| Effort | Max | Max throughout (orchestration + the deep diagnosis/synthesis); no Ultracode needed (Workflow sets per-agent effort) | the cap diagnosis + T3a crack + the automation design are deep single-thread work. |

## Commit Message
```
(Phase 20 landed across multi-session commits; final session commit:0173..commit:0177 + this PhaseEnd.)

feat(phase-20): close — cap tool + T3a %lo crack + 3 byte-proven findings; fleet 58.00%->58.82% (v1.19.0)

- THE CAP TOOL tools/cast_call_sites.py (§17a-1 callee-cast): per draft, callee whose canonical
  TU sig != draft's intended sig -> decl->canonical + call-site cast ((ret(*)(args))func_X)(args)
  (codegen-neutral; gcc folds the cast of a known symbol -> direct jal). Recovered 6 of T6 batch-1's
  33 gate-fails byte-identical (5 x134 + 1 local). Pipeline canon_resident_calls -> cast_call_sites
  -> sig_unify -> harvest_verify --chunk 1.
- T3a CRACKED (not cited): the %lo-folding indexed-global -O0 residual falls to the array-of-STRUCT
  idiom (extern Struct base[], sizeof==stride, base[i].field; NOT *(T*)(&sym+i*stride) which
  materializes &sym). func_8013B7AC banked. Reusable idiom fleet-wide. cookbook §18/§20.
- THREE byte-proven findings (R14): (1) the wave cap is the DEF-side loose-typing wall, not
  callee-conflicts (the §20 "~33" projection was wrong); (2) the -O0 cluster is OVERLAY-LOCAL,
  not reach-134 -> the ×134 rollout is INVALID; (3) data-cast is MOOT (0 real data conflicts).
- T1 typedef type-lift (+0.35%, 9 fns x134); T2 exemplar_miner router; T4 codegen map (cookbook §20);
  T6 batch-1 (+0.28%, 8). dedup 1485->1513/0 failed. check-all 136/136 BYTE-IDENTICAL (R22);
  0 NON_MATCHING (G4). fleet 58.00% -> 58.82%.
- rule R30 (capture context-dependent knowledge before a fresh session). worklog -> logs/Phase20.md.
- bumps 1.18.0 -> 1.19.0
```

## Rules Added This Phase
| Rule | Reason |
|---|---|
| **R30 — Capture context-dependent knowledge artifacts before a fresh session.** Cookbook entries, byte-verified findings, codegen-map distillations, and doc corrections whose quality depends on the current session's full live context MUST be written DURING that session, before any fresh-session handoff (the fresh session inherits only compressed summaries and loses the detail / nuance / byte-evidence). Defer only mechanical / continuable work (build the next tool, run the next wave). Extends R16 (the flywheel — adds the timing constraint). Memory `capture-knowledge-before-fresh-session`. | Candidate since the multi-session handoff (Drew, 2026-06-21 — prompted by nearly deferring T4's §20 distillation to a fresh session that would have lost the byte-evidence). Exercised all session: §20 RESOLUTION, the §18 T3a crack, and the three R14 findings were all written during the producing session. |

*(Not elevated to rules — captured as cookbook techniques per the Phase-8+ precedent: the call-site-cast recovery (§20), the array-of-struct `%lo`-fold idiom (§18), the DEF-side-wall / overlay-local / data-cast-moot findings (§18/§20). The **R22 corollary** — a reverted **config** needs a `make extract`, not just `make check`, or it leaves a stale `.ld`/asm while `git status` looks clean — is a §13/§18 build-infra note, governed by the existing R22.)*

## PhaseEnd Changelog
**v1.18.0 → v1.19.0 — Phase 20 complete (Gen2 phase 12; open-ended, closed at a clean checkpoint).** The fleet
rose **58.00% → 58.82%** byte-identical-from-source (136/136 binaries byte-identical, 0 NON_MATCHING throughout),
banked by the **typedef type-lift** (T1, +0.35%, closing the §19 propagation cap), an **enriched wave** (T6
batch-1, +0.28%), and the phase's headline tool — **`tools/cast_call_sites.py`**, the §17a-1 per-site
function-pointer cast that recovers the loose-typing **callee-conflict** class (+0.19%, codegen-neutral, byte-gated).
The **T3a `%lo`-folding -O0 residual was CRACKED** (not the expected cite-irreducible): the **array-of-struct
idiom** (`extern Struct base[]`, `base[i].field`) folds `%lo` where `*(T*)(&sym+i*stride)` materializes — a
reusable fleet-wide idiom. The phase's most valuable output is **three byte-proven (R14) strategic findings** that
retire two dead levers and sharpen the roadmap: the wave cap is the **DEF-side loose-typing wall** (a banked caller
declares the draft's own function incompatibly; caller-side fix blocked because `INCLUDE_ASM` declares no symbol),
**not** callee-conflicts as §20 first projected; the **-O0 cluster is overlay-local** (per-overlay data addresses),
so the ×134 rollout is **invalid** (the "reach-134" label conflated function-present with byte-identical); and the
**data-cast is moot** (0 real data conflicts). The gcc-2.7.2 **codegen map** is distilled (cookbook §20). Net read:
the reach-134 ≤90-ins **cached** tail is byte-exhausted of cheap recoveries; the remaining yield is fresh targets,
the giants, and the hard walls. One rule (**R30**, capture-knowledge-before-fresh-session). The phase closes
deliberately so the **automation architecture** (the supervised-autonomous grind) gets its own fresh, plan-mode
**Phase 21** — designed and Drew-approved, captured as the Backlog below.

## Plain-English Recap
This phase squeezed the remaining easy wins out of the game's shared engine code and, just as importantly, *proved
which "easy wins" were actually mirages.* We built a tool that auto-fixes a common reason a correct function won't
slot in (a function-declaration mismatch) — it recovered six functions cleanly. We then chased two more ideas and
the automatic bit-for-bit referee proved both were dead ends (functions we thought were shared across all 134
levels turned out unique to each; "data conflicts" weren't real) — so we proved them dead, wrote down exactly why,
and faked nothing. The happy surprise: a residual we'd long called "impossible" actually *cracked* with a clean C
trick (treat the global as an array of structs), now a reusable recipe. We finished at ~58.8% of the game rebuilt
bit-for-bit, with everything still byte-perfect. The big takeaway is honest: the leftover functions in this
size-band are genuinely the hard wall now, not low-hanging fruit — so the next phase is a different shape entirely.
We designed (and you approved) an **automation manager** setup for your 5 days away: I orchestrate; swarms of AI
agents do the matching in isolated workflows (so my own memory stays clean enough to run for days); a background
brute-forcer grinds the mechanical cases; and — the key deliverable — *everything that gets close but doesn't
finish is logged as a ranked backlog* for you to hand-finish when you're back. That automation is its own fresh
phase, planned from the design captured below.

## Phase-21 Backlog — "The automation manager" (the approved design; nothing here is lost on close)

> Phase 21 opens in **plan mode** (Tier-1 architecture). Drew-approved design: **supervised-autonomous**,
> **verify-giants-first**, **build-now**. I am the orchestrator (Max); workflows are the workers (xHigh via
> `opts.effort` — no global Ultracode needed). The goal: spend ~5 idle days grinding as much as possible and
> **storing results** — banking byte-matches AND logging every near-miss (closest-achieved) as a ranked backlog
> for Drew's hand-sessions. The byte-gate (G3/P9) prevents false matches; the ROI-gate prevents wall-grinding.

**The 6 build-pieces (prioritised):**
1. **[FIRST, no MCP] Verify giants shared-ness + build the target-pool manifest.** Byte-verify the 28 giants
   (reach-134 fns >150 ins) are genuinely shared ×134 (h_exact across overlays — the -O0 "reach-134" was a
   mislabel, so don't trust it). Assemble the fuel manifest: fresh tractable reach-134 ov_SC01_077 stubs + the
   SHARED giants + the 9 -O0 stubs (idiom-known), each tagged reach + class + size.
2. **[needs `/mcp` once, up front] Fuel prefetch.** Stop MCP (R23) → `DecompileFunctions.java` over the manifest
   → cache Ghidra-C to `.run/ghidra_c/` (cache is 300; ov_SC01_077 has 668). **CRITICAL: pre-load ALL fuel so the
   unattended run never needs live MCP** (the run is cache-based — no `/mcp` reconnect mid-run).
3. **Worker workflow + deterministic gate/bank/propagate stage.** A Workflow: fan-out drafter agents (xHigh) over
   the pool using the full toolkit (§17 pins, §18/T3a array-of-struct, §19 recovery, §20 cast tool) → each returns
   `{matched | near-miss + best-draft + diff + class | failed}`. Deterministic stage:
   `canon_resident_calls → cast_call_sites → sig_unify → harvest_verify --chunk 1 → dedup_propagate`. Returns ONE
   compact summary (keeps the orchestrator's context lean). Validate on a small sample before scaling.
4. **The backlog ledger** (`docs/backlog.md` + `.run/backlog.jsonl`, committed) — **the deliverable**: every
   near-miss logged with closest-achieved draft, diff score, residual class, reach, and where it stuck —
   ranked for Drew's hand-sessions. Honest (P9): only byte-matches bank.
5. **Grinder workflow** — re-cast the Phase-16 `auto_driver` as a Workflow: decomp-permuter (CPU-bound, local,
   free) on the regalloc/schedule-class near-misses, banking through the same gate, logging near-misses. Runs
   alongside the worker waves (CPU budget vs token budget).
6. **[LAST] ROI orchestrator loop + `auto_supervisor` keep-alive.** The between-wave loop (Max): bank → route →
   assess close-rate; when a pool's close-rate drops below threshold for K rounds, switch pools (≤90-ins → giants
   → -O0) or pause. Deploy the Phase-16 `auto_supervisor.sh` (detect stalled/exited session → resume via
   `continue`; `auto_stop.sh` sentinel = Drew's kill switch). Sample-validate the full loop (a few hours) BEFORE
   the unattended stretch, then launch.

**Carried context for the plan:**
- The reusable wave recipe (proven Phase 20): `gen_harvest_targets --min-reach 134 --max-nins 90` → filter to
  cached Ghidra-C → Workflow (one agent/target, **args as a JSON array NOT a string** — the gotcha) →
  `canon_resident_calls → cast_call_sites → sig_unify → harvest_verify --chunk 1 → dedup_propagate --auto-from`.
- Honest fuel/ROI caveat: the cached ≤90-ins tail is byte-exhausted; fresh targets are finite (~+a few %); the
  giants are high byte-weight but low auto-yield (Phase-16 ~3% wall) → they're primarily **backlog fuel**
  (workers get them close, log near-misses, Drew hand-finishes). 5 days of runtime ≠ 5 days of wins — the value
  is the harvested tractable % **plus** the ranked near-miss backlog.
- The 7 callee/data-plumbing capped fns (reach-134, matched-but-local): `0x80142B2C 0x801535F4 0x80155E30
  0x80157580 0x801576A8 0x80168F40 0x80170B48` — fail `compiles_standalone` on undeclared callees/data; a
  macro-extern-injection (or canonical-callee-sig embed) frees them ×134 (~+0.3%). Worker-workflow fodder.
- The -O1 class (`func_80161A90`) — needs an `-O1` split file (the §18 -O0 precedent); build-infra, low priority.

## 🛑 Stop Here
PhaseEnd written; `CURRENT_PHASE.md` archived → `phase-ends/logs/Phase20.md` (R19). **Drew commits AND pushes**
this PhaseEnd + the archived log + the final-session matching commits (`commit:0173`..`commit:0177`) (R6/R8 — Drew's
commit is the gate-2 sign-off). No Ghidra DB change this phase (R23 no-op — the `db.*.gbf` churn is restart-noise,
do NOT stage it). Gen2 continues — do **NOT** start Phase 21 here. Start a **fresh session** (effort **Max**,
**plan mode**) for **Phase 21 — the automation manager** (the Backlog above; verify giants → prefetch fuel →
worker/grinder/feeder workflows + backlog ledger → ROI loop + supervisor). Keep this file forever.
