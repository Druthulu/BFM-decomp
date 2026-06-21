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
- [ ] **T4 — Worker Workflow** (Max; agents xHigh) → new Workflow, sample-validate ~8–10 fresh targets. **← P6 rules re-read after this.**
- [ ] **T5 — Grinder daemon repoint** (xHigh) → `auto_driver.py` permutes worker near-misses + full gate pipeline + backlog logging.
- [ ] **T6 — ROI orchestrator loop + hybrid keep-alive + full-loop sample-validate** (a few hours; Max).
- [ ] **T7 — Stage ready-to-launch + Phase close (PhaseEnd)** (Max, Tier-1).

**Current task:** T1.

## Verification invariant (every banked step + at close)
`make clean && (extract all 136) && make check-all` → 136/136 byte-identical (R22); `make report` → 0 NON_MATCHING (G4), `dedup-check 0 failed`.

## Blockers
(none)

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
