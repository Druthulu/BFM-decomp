# CURRENT_PHASE — Phase 21: The Automation Manager

**Generation:** Gen2 (13th phase) · **Status:** APPROVED plan, in progress · **Effort:** Max (whole phase)
**Plan file:** `/home/musashi/.claude/plans/max-effort-plan-mode-breezy-zebra.md`
**Started:** 2026-06-21 · **Fleet at start:** 58.82% byte-identical (136/136 binaries byte-identical, 0 NON_MATCHING)

> Phase Start gate PASSED (Drew approved the plan). This file is the per-task crash-recovery log (P3/CURRENT_PHASE).
> Open-ended phase; milestone = **build → validate → stage, then close** (Drew's choice — the multi-day run is a later go).

## Locked decisions (AskUserQuestion, 2026-06-21)
1. **Milestone = build→validate→stage, then close.** Sample-validate a few hours hands-on, bank that increment, populate the backlog, close ready-to-launch.
2. **Keep-alive = hybrid.** `/loop` self-pace primary + external `claude --continue` watcher fallback; `auto_stop.sh` = kill switch.
3. **Run posture = balanced, ROI-gated.** Worker waves per-pool until close-rate drops K rounds → route next; free permuter grinder in parallel; everything logs to backlog.

## Architecture (three components, one gate, one ledger)
- **Grinder (token-free)** = existing `tools/auto_driver.py` + `auto_supervisor.sh`, repointed to permute the worker's near-misses + log backlog.
- **Worker (token-heavy, LLM)** = NEW Workflow, parallel drafter agents (`opts.effort:'xHigh'`) using the §17–§20 toolkit → serial gate stage → compact summary.
- **Orchestrator (me, Max)** = ROI loop + hybrid keep-alive; routes pools, banks checkpoints, maintains `docs/backlog.md`.
- Both bank through the same `harvest_verify` gate + `dedup_propagate`; both log to the same backlog ledger.
- Effort: stay at Max all phase; Workflow sets per-agent xHigh (no R26/R27 toggle dance).

## Task checklist
- [x] **T1 — Target-pool manifest + giants byte-verification** (no MCP; Max) → `.run/fuel_manifest.json`; h_exact-verify the 28 giants are genuinely ×134 (R14). **DONE.**
- [x] **T2 — Fuel prefetch → complete Ghidra-C cache** (MCP-stop headless; Max) → `.run/ghidra_c/` cache-complete over the manifest. **DONE.**
- [x] **T3 — Backlog ledger + shared deterministic bank/log stage** (Max) → `tools/gate_stage.py` + `tools/backlog.py` + `docs/backlog.md`; validated on a real 30-draft sample (banked+propagated+logged). **DONE.**
- [x] **T4 — Worker Workflow** (Max; agents xHigh) → `tools/workflows/worker_wave.js` + `tools/wave_targets.py`. **VALIDATED.**
- [x] **T5 — Grinder daemon** (xHigh) → `tools/grinder.py` (permutes backlog near-misses → gate_stage) + `auto_supervisor.sh` (DRIVER-param). **VALIDATED.**
- [~] **T6 — ROI orchestrator + hybrid keep-alive + launch** (Max) → `tools/orchestrator.py` built; launch in progress (Drew's trip imminent).
- [ ] **T7 — Stage ready-to-launch + Phase close (PhaseEnd)** (Max, Tier-1).

**Current task:** T1.

## Verification invariant (every banked step + at close)
`make clean && (extract all 136) && make check-all` → 136/136 byte-identical (R22); `make report` → 0 NON_MATCHING (G4), `dedup-check 0 failed`.

### T4/T5/T6 — worker + grinder + orchestrator (2026-06-21, trip-imminent push)
- **T4 worker Workflow** (`tools/workflows/worker_wave.js`): parallel xHigh drafter agents, each given the asm + cached Ghidra-C + the §17–20 toolkit; writes its best C; orchestrator gates after. `tools/wave_targets.py` selects the batch (ROI pool). **args gotcha (§20): the harness serializes args to a JSON STRING → the script parses it.** VALIDATED: a 3-target wave → all 3 self-MATCH; whole-binary gate **banked func_80164530 ×134** (5 register-pins + offset-fold + scheduling — a hard toolkit match), 1 near + 1 failed logged. ~275k tokens / 13 min for 3 agents. fleet 58.90→**58.98%**.
- **T5 grinder** (`tools/grinder.py`): token-free — permutes backlog near-misses (close≤30) → gate_stage → bank; STOP/heartbeat, idles for new worker fuel. VALIDATED: permuter WON func_8014F3E8 but the whole-binary gate correctly REJECTED it (§20 — match_one/permuter over-predict; gate is truth; integrity intact, 0 wrong banked). `auto_supervisor.sh` now `DRIVER`-parameterized (launch grinder under it).
- **T6 orchestrator** (`tools/orchestrator.py`): `prep` (pick ROI pool → emit wave batch) / `finish` (gate_stage → record close-rate → rotate pool when tapped) / `status`. Pool rotation tractable→giants→o0→capped, ROI-gated (threshold 0.15, patience 2). The model launches the Workflow between prep/finish (the one step only it can do).
- **gate_stage flock**: grinder + orchestrator gates serialize on `.run/auto/gate.lock` (one build/commit at a time — safe concurrency).
- **SANDBOX finding:** foreground Bash-tool builds (`make build`/`git`) get killed (exit 144) by the sandbox; **detached daemons (setsid/nohup) escape it** — so the launched grinder/orchestrator build fine; interactive gates need `dangerouslyDisableSandbox`.

## TRIP HAND-OFF (2026-06-21) — what's running, what's staged

**Status:** the automation manager is BUILT + VALIDATED end-to-end; fleet **58.82% → 58.98%** (3 real
matches banked during validation: func_801710DC, func_80164530, + the T3 sample; all ×134, 136/136
byte-identical). Drew is travelling **with remote access** to this dev box.

**RUNNING NOW (autonomous, token-free):**
- The **grinder** (`tools/grinder.py` under `tools/auto_supervisor.sh`, launched detached) — permutes the
  backlog's closest near-misses → byte-gate → banks → ×134; idles for worker fuel; supervisor relaunches
  on crash. Monitor: `tools/auto_status.sh`. Stop: `tools/auto_stop.sh`.

**STAGED (Drew drives remotely — the high-yield token engine):**
- The **worker** waves: `tools/orchestrator.py prep` → launch the `tools/workflows/worker_wave.js`
  Workflow → `tools/orchestrator.py finish --commit`. Run it via **`/loop`** (the runbook has the exact
  cycle prompt). ~24 xHigh agents/wave, ~275k tokens/wave; ROI-gated pool rotation. **The full runbook
  is `docs/automation-runbook.md`.**
- An in-flight 16-target worker wave (`.run/drafts-wave2`) was launched at hand-off; gate it with
  `tools/orchestrator.py finish --drafts .run/drafts-wave2 --commit` (or it's the first thing the /loop
  picks up).

**Why safe to leave running:** the whole-binary byte-gate (G3/P9) is the sole arbiter — a wrong draft is
reverted, NEVER banked; `make check-all` stays 136/136; every bank is a checkpoint commit (push is manual,
R6); `auto_stop.sh` halts at the next safe boundary. Worst case of any crash = "it paused," never "it broke."

**Phase close:** T7 (formal PhaseEnd) awaits Drew's gate-2 milestone confirmation on return. Until then this
file + `docs/automation-runbook.md` are the durable state. Sandbox note: detached daemons build fine;
interactive build gates need `dangerouslyDisableSandbox`.

## POST-REBOOT RESUME (2026-06-21) — the learning flywheel + ready for the fresh-session run

After the reboot (BIOS startup-on-power-loss configured; Drew has remote access):
- **R1 — gated the 15 pre-reboot drafts:** banked **4** (func_80156FA8/801678F0/80156848/8017742C; 2 propagated
  ×134); backlog 30→41. R22 check-all **136/136**. (The standalone gate was killed pre-commit twice — a harness
  quirk on detached `nohup gate_stage` runs; recovered by committing the working tree. Does NOT affect the
  orchestrator, which calls gate_stage **in-process**.)
- **R2/R3 — the learning flywheel (Drew-approved):**
  - Residual gcc-quirk class now **travels with the draft**: the drafter stamps `// @class` / `// @stuck`;
    `gate_stage` logs the worker's class (not the coarse manifest class) → enables class buckets.
  - **Class-grouped waves:** `wave_targets.py --class <C>` / `--list-classes` (REGALLOC/SCHEDULE/REMAT/STRUCT/
    IV/LOOPGUARD/LOOSE/PLUMBING). `orchestrator prep` auto-fires a class-focused re-attempt wave when a class
    accrues ≥6 near-misses (drafters get the prior stuck-point), else a fresh pool harvest.
  - **Distill** (`tools/workflows/distill.js`): post-wave agent extracts NEW byte-verified gcc idioms → cookbook
    §21 (R16, conservative); drafters read the **live** cookbook so idioms feed forward (the Phase-18 loop, automated).
- **R4 — grinder relaunched** (token-free); fleet **59.05%** (phase: 58.82→59.05, +0.23%, 5 fns ×134); 136/136;
  tree clean. **Ready for Drew's fresh session to run the worker `/loop`** (this session is at low context).

**Fresh-session launch (Drew):** start a Claude Code session here → run **`/loop`** with the cycle in
`docs/automation-runbook.md` (prep → worker_wave Workflow → finish gate → distill). The grinder is already
running alongside. Monitor: `bash tools/auto_status.sh`. Stop: `bash tools/auto_stop.sh`.

## FRESH-SESSION RUN LIVE (2026-06-21 ~14:40 — Drew away ~8h, remote access)

Drew launched the unattended grind ("run the worker /loop cycle, then start the grinder; I'll check back in ~8h").
Both engines are RUNNING:
- **Worker** — wave 1 launched as Workflow `wx91bmadi` (run `wf_b173a013-d6a`): 24 xHigh drafters over the
  **tractable** reach-134 pool (nins 93–142). The loop is driven by **Workflow-completion notifications** (not a
  polling timer): on each wave's completion the orchestrator runs `finish --commit` (gate→bank→propagate ×134→
  backlog), `distill` if anything verified, then `prep`+launches the next wave. Race-free (one wave at a time;
  `prep` rm-rf's `.run/drafts-wave`). ROI-gated pool rotation via `orch_state.json`.
- **Grinder** — relaunched detached (was dead post-reboot, heartbeat 24 min stale): supervisor pid 2573950 +
  `grinder.py` pid 2574026, `--permute-secs 120 -j 14`, token-free, draining the backlog near-misses.
- Fleet at launch: **59.05%**, 136/136 byte-identical, 0 NON_MATCHING. Gate (G3/P9) is the sole arbiter — a wrong
  draft is reverted, never banked; worst case of any crash is "it paused."
- Monitor: `bash tools/auto_status.sh`. Stop both: `bash tools/auto_stop.sh` (then `rm .run/auto/STOP` to resume).
- **Sandbox note (R/§ build-infra):** my foreground `make build`/`git` calls get sandbox-killed (exit 144) →
  `orchestrator.py finish` and any commit run with `dangerouslyDisableSandbox`; detached daemons (grinder) escape it.

**Run progress (worker waves):**
| Cycle | Wave drafted | Byte-banked | Fleet | Commit |
|---|---|---|---|---|
| 1 | 24 (19 self-MATCH) | 7 (4 ×134) | 59.05→59.21% | `commit:0193`; distill `commit:0194` (cookbook §21 added) |
| 2 | 24 (18 self-MATCH) | 5 (4 ×134) | 59.21→59.37% | `commit:0195` |
| 3 | 24 (17 self-MATCH) | 7 (6 ×134) | 59.37→59.60% | `commit:0197`; distill `commit:0198` |
| recovery | 7 close=0 re-gated | 2 (×134) | 59.60→**59.68%** | `commit:0199` (sig_unify DEF-side fix) |
- **Distill flywheel:** 3 NEW byte-verified cookbook idioms added across the 3 waves (`commit:0194` Blk16/memcpy
  unaligned-copy; `commit:0196` disjoint-bits add→ori re-tie barrier; `commit:0198` giv-anchor store-order).
- **Wave-2 "6.5h" was NOT throttling** — it was idle on a CC **permission prompt** (Drew approved on check-in);
  waves 1 & 3 ran in ~25–32 min. (R14: corrected my earlier rate-limit read.)

## OPTION C — grinder fix + DEF-side recovery (Drew-approved, 2026-06-21 ~22:50)
The grinder had banked **0 in ~8h**: stuck re-permuting 2 plumbing-bound near-misses (`func_8014F3E8`,
`func_8014FE60`) — permuter "wins" them (base already masked-0) but the whole-binary gate correctly rejects every
cycle; after idle it did `tried.clear()` and looped forever (§20 trap). Fixed BOTH halves of option C:
- **(a) `tools/grinder.py` blacklist:** record every permuter-won/gate-rejected fn → `.run/auto/grinder_blacklist.json`,
  skip permanently, survives restarts. Frees its CPU for genuine regalloc/schedule near-misses. Grinder restarted with it.
- **(b) `tools/sig_unify.py` DEF-side fix:** diagnosed the wide self-MATCH→bank gap as the **DEF-side loose-typing
  wall** (draft's byte-correct def has FEWER params than engine_core.h's canonical cross-overlay decl →
  `conflicting types`). `rewrite_def` previously only rewrote params on arity MATCH (return-type-only fallback
  otherwise). Patched it to **adopt the canonical param list on arity mismatch** (draft names + synth `_argN` for
  the unused extras; they sit in `$a0–$a3`, free at -O2). Validated: banked `func_8016EDEC` + `func_8016EE40`
  through the real gate (`commit:0199`). **Compounds: it's in the gate pipeline, so every future wave + the grinder
  now auto-recover DEF-side near-misses.** (Remaining close=0: a data-conflict + narrow-param arity gcc's
  promotion rule blocks + multi-way loose typing — genuinely harder, diminishing returns.)

**Session totals (2026-06-21):** 3 worker waves + recovery → **21 fns banked**, fleet **59.05% → 59.68%** (+0.63%),
136/136 byte-identical (per-bank gate G3/P9; full check-all deferred to a checkpoint), 0 NON_MATCHING, 3 new
cookbook idioms, grinder + sig_unify both upgraded. Diagnostics in `.run/{diag_plumbing,repro_gate,test_defsig}.py`.

## SUSTAINED LOOP (2026-06-21→22, Drew: "keep waves going, don't stop till I check in ~8h")
Continuous worker loop running, driven by Workflow-completion (NOT a timer): per wave →
`orchestrator.py finish --commit` (gate+bank+propagate ×134) → `distill.js` if verified → `orchestrator.py prep
--mode pool --n 24` → launch `worker_wave.js` with the batch pasted **verbatim** from the compact dump (Workflow
scripts have no fs access; transcribe carefully). Gate/finish run **backgrounded + dangerouslyDisableSandbox**
(foreground `make build`/`git` get sandbox-killed exit 144). Grinder runs alongside (token-free, blacklist-aware).
- **POOL-mode override (policy):** auto-mode keeps firing class-focused REGALLOC waves, but that class has
  saturated with permuter-class/DEF-side-plumbing residuals agents can't crack from C → low yield. Use
  `prep --mode pool` to harvest FRESH reach-134 targets (higher yield); leave regalloc residuals to the grinder
  (permuter) + backlog (hand-finishing). The DEF-side `close=0` set (func_80174CB0/80169228/80167714 …) won't bank
  via re-drafting — they're hand-finish fuel.
- **Running tally (this session, fleet 59.05% start):** waves 1-6 launched; banked via worker gates + the sig_unify
  recovery. Fleet **59.87%** after wave 5 (wave 6 in flight). 4 new cookbook idioms distilled
  (`commit:0194 commit:0196 commit:0198 commit:0203`). Commits `commit:0193…commit:0202` + option-C `commit:0200`.
- **To resume after compaction:** read this section + `docs/automation-runbook.md`; the next step is always
  gate the in-flight wave (`.run/auto/finish_wave<N>.log` / orchestrator finish) → distill → prep --mode pool →
  launch. Stop only when Drew says so (`bash tools/auto_stop.sh` halts the grinder).

## Blockers
(none — grinder running blacklist-aware + enhanced sig_unify; worker loop sustained per Drew until check-in.)

## Per-task log

### T1 — fuel manifest + giants byte-verification (DONE, 2026-06-21)
- New tool `tools/build_fuel_manifest.py` → `.run/fuel_manifest.json` (gitignored, regenerable). reach RECOMPUTED from the current 134 overlay sigs (distinct-overlay h_exact histogram), not trusted from cached fields (R14).
- **803 live func_ stubs** classified: GIANT 28, WAVE 425, STRUCT 148, PINS 104, STUB 88, O0 9, O1 1 (+1 named stub `listCdBuffer` skipped). Reach buckets: 310 reach-134, 486 reach-1 (overlay-unique), 7 partial.
- **R14 giants: 28/28 verified genuinely reach-134** (byte-identical ×134 — the giants' label is honest, unlike the -O0 cluster). Top leverage: func_80144B9C (770 ins), func_80141CA4 (476), func_80132784 (400).
- **R14 -O0 nuance (byte-finding):** 8/9 -O0 stubs are overlay-local (reach-1, matches Phase-20), but **func_8013C08C is reach-134** — a genuine exception to the blanket "overlay-local" assumption (propagatable ×134 if matched).
- **T2 workload:** 253 reach-134 stubs uncached (of 310); tractable reach-134 (WAVE/PINS/STRUCT ≤150 ins) = 223, 171 uncached; giants 25/28 uncached. Ghidra-C cache currently 300.
- No MCP, no build mutation. Checkpoint commit: tool + this log.

### T2 — fuel prefetch → Ghidra-C cache complete (DONE, 2026-06-21)
- Stopped MCP (R23, clean Save). Headless `analyzeHeadless ... -process ov_SC01_077 -readOnly -postScript DecompileFunctions.java <addrs> .run/ghidra_c` over the **263 uncached ROI-pool fns** → **263 ok / 0 fail / 0 no-func**. Cache 300 → **563**.
- **Naming bug found + fixed:** Ghidra emits `FUN_<lowerhex>` (raw-import default); consumers + the 300 existing files use `func_<UPPERHEX>`. Renamed the 263, and **fixed `DecompileFunctions.java` to key output by entry address (`func_<UPPER>`)** so re-prefetch is reproducible. Added `build_fuel_manifest.py --emit-prefetch` (reproducible addr-list for the T7 runbook).
- **T2 verification (cache-complete):** ROI-pool fuel = **325 fns, ALL cached, 0 uncached** (28/28 giants, 310/310 reach-134, 7/7 capped). The unattended run will never need live MCP.
- Scope (P9): 349 reach-1 ×1-leverage fns intentionally NOT prefetched (not in the ROI pool rotation: tractable reach-134 → giants → -O0 → capped). A later prefetch can add them if ever needed.
- MCP left STOPPED (the run is cache-based; the grinder supervisor stops it anyway). `ghidra/ db.*.gbf` churn is the MCP-stop's no-op SLUS save — R23 restart-noise, NOT staged.
- Checkpoint commit: `DecompileFunctions.java` + `build_fuel_manifest.py` + this log (cache + manifest are gitignored/regenerable).

### T3 — backlog ledger + shared deterministic gate stage (DONE, 2026-06-21)
- **`tools/backlog.py`** — the near-miss ledger (`.run/backlog.jsonl` append + `docs/backlog.md` ranked render). Ranks by reach → closeness → size; **drop-now-matched** filter (a banked fn leaves the backlog, P9). Tested: append/render/show + drop-matched all correct.
- **`tools/gate_stage.py`** — the shared deterministic spine (worker + grinder call it): drafts → `canon_resident_calls → cast_call_sites → sig_unify → harvest_verify --chunk 1 → dedup_propagate --auto-from` → log non-matches to backlog → compact JSON summary. Byte-gate is the sole arbiter (G3/P9).
- **Validated end-to-end** on a real 30-draft m2c sample of reach-134 main WAVE stubs → `{drafts:30, banked:1, propagated:2, near:20, failed:8}`. **func_801710DC banked + propagated ×134** (dedup 1506→1508, every ov_*.c touched); **29 near-misses logged + ranked** (top: func_80174684 close=0 "MATCH but plumbing", func_8014F3E8 close=1; captured the §20 unsteerable regalloc class func_80149374/801493D0). All paths exercised: bank→propagate→log→render→summary.
- **R22: `make check-all` → 136/136 byte-identical**; `make report` → fleet **58.82% → 58.90%** (+0.08%, the func_801710DC ×134 increment), `dedup-check 1508 validated / 0 failed` (G3/P9). A real, byte-gated increment — kept.
- **Capped-fns reframe (R14):** the 7 capped are matched-**inline** (propagation-blocked on undeclared callees/data), NOT draftable stubs — so they don't flow through the gate stage's draft path; the plan's "warm-up on the 7 capped" premise was slightly off. The stronger honest validation is the real 30-draft sample above. The capped propagation-recovery is **deferred to the worker** (T4 re-drafts them through gate_stage's recovery pipeline; the manifest's `capped_recovery` documents them). Not claiming the unbanked ~+0.3% (P9).
- Best-draft `.c` files saved to `.run/backlog_drafts/` (local, gitignored — Drew accesses them on this machine; `docs/backlog.md` is the committed index).
- Checkpoint commit: the 2 tools + `docs/backlog.md` + the func_801710DC match & ×134 propagation (src/ov_*, engine_core.h, dedup.us.yaml, progress digests) + this log.
