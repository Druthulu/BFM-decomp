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
- [ ] **T3 — Backlog ledger + shared deterministic bank/log stage** (Max) → `tools/gate_stage.py` + `tools/backlog.py` + `docs/backlog.md`; verify on the 7 capped fns (~+0.3%).
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
