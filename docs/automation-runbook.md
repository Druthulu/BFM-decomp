# Phase-21 Automation Runbook (the unattended grind)

The automation manager: a **token-free grinder** (CPU permuter) + a **token-heavy worker** (LLM
agent waves), both banking through the **incorruptible whole-binary byte-gate** (G3/P9 — a wrong
match can NEVER bank) and logging every near-miss to a **ranked backlog** for hand-finishing.

## What is running right now

- **Grinder** (`tools/grinder.py` under `tools/auto_supervisor.sh`) — **LAUNCHED**, token-free.
  Permutes the backlog's closest near-misses → byte-gate → banks the real matches → propagates ×134.
  Idles when the backlog is drained (waiting for worker-produced near-misses). Survives crashes
  (supervisor relaunches). Heartbeat: `.run/auto/grinder_heartbeat.json`.

## Monitor (read-only, from anywhere)

```sh
bash tools/auto_status.sh                 # grinder + worker heartbeats, backlog size, recent commits
cat .run/auto/grinder_heartbeat.json      # grinder: state/current/banked/fleet
.venv/bin/python tools/orchestrator.py status   # worker ROI state (pool, waves, banked_total)
.venv/bin/python tools/backlog.py show -n 40     # the ranked near-miss backlog (docs/backlog.md)
git log --oneline -15 | grep phase-21     # what banked
make report BINARY=main                   # fleet % (+ dedup byte-honesty check, must be 0 failed)
```

## STOP everything (the kill switch)

```sh
bash tools/auto_stop.sh        # touches .run/auto/STOP -> grinder finishes its current step, exits;
                               # the supervisor sees STOP and does not relaunch. Safe at any time.
rm .run/auto/STOP              # to allow a relaunch later
```

## Launch the WORKER waves (token-heavy — the high-yield engine)

The worker drafts matching C with LLM agents (the §17–20 toolkit: register pins, array-of-struct
%lo-fold, call-site casts) — it cracks the hard tail the grinder can't. It needs a **Claude session**
(only a session can invoke the Workflow tool), so it runs as a self-paced **`/loop`**:

1. In a Claude Code session in this repo, run **`/loop`** with this cycle as the prompt:
   > Run one Phase-21 orchestrator cycle, then stop if `.run/auto/STOP` exists:
   > (a) `.venv/bin/python tools/orchestrator.py prep --n 24` — auto-picks a **class-focused** wave (re-attempt
   > the backlog's biggest gcc-quirk class) or a **fresh pool** wave; it prints `{mode, sel, n, batch}`.
   > (b) Read `.run/auto/wave_batch.json` and launch the **`tools/workflows/worker_wave.js`** Workflow with
   > `args={draftDir:".run/drafts-wave", targets:<the batch array>}`. Wait for it.
   > (c) `.venv/bin/python tools/orchestrator.py finish --drafts .run/drafts-wave --commit` — gates, banks,
   > propagates ×134, logs near-misses; prints `{banked, propagated, near, verified, ...}`.
   > (d) If `verified` is non-empty, launch the **`tools/workflows/distill.js`** Workflow with
   > `args={draftsDir:".run/drafts-wave", verified:<the verified array>}` — it extracts any NEW byte-verified
   > gcc idiom into the cookbook so the next wave inherits it (the learning flywheel).
   > (e) Report the one-line result.
2. **The learning flywheel:** fresh waves classify their near-misses by gcc-quirk (the drafter stamps
   `// @class`/`// @stuck`); once a class accrues ≥6 near-misses, `prep` fires a **class-focused re-attempt
   wave** for it (drafters get the prior stuck-point + the live cookbook); `distill` turns each wave's banked
   techniques into new cookbook idioms. This is the Phase-18 close-rate-rising loop, automated.
3. `/loop` self-paces (~15–20 min/wave, ~275k tokens/wave of ~24 agents). The grinder runs alongside,
   draining near-misses. Cost-bounded by the ROI gate + `auto_stop.sh`. Inspect classes anytime:
   `.venv/bin/python tools/wave_targets.py --list-classes`.

**Remote management (Drew has laptop + can remote into the dev box):** you don't need a bulletproof
keep-alive — if the worker `/loop` session dies, just remote in and re-run `/loop` (the grinder daemon
keeps running regardless, and every bank is already committed, so nothing is lost). Monitor with
`tools/auto_status.sh`; stop with `tools/auto_stop.sh`; resume by re-launching. The byte-gate guarantees
correctness while unattended, so the worst case of a crash is "it paused," never "it broke something."

## Re-prefetch fuel (only if adding fresh targets, needs Ghidra)

The run is **cache-based** (no live MCP needed). To add targets to the Ghidra-C cache later:
```sh
bash tools/ghidra_mcp_stop.sh                                    # R23 (free the project lock)
.venv/bin/python tools/build_fuel_manifest.py --emit-prefetch .run/prefetch_addrs.txt
"$HOME/ghidra_12.1_PUBLIC/support/analyzeHeadless" "$HOME/bfm-decomp/ghidra" bfm \
  -process ov_SC01_077 -noanalysis -readOnly -scriptPath tools/ghidra_scripts \
  -postScript DecompileFunctions.java .run/prefetch_addrs.txt .run/ghidra_c
```

## Safety invariants (why this is safe to leave running)

- **Byte-gate is the sole arbiter (G3/P9):** every bank is whole-binary SHA1-verified; a wrong draft
  is reverted, never banked. `make check-all` stays 136/136.
- **git is the crash-safe state machine:** every bank is a checkpoint commit (push is manual, R6 —
  nothing leaves the machine on its own); `dedup_propagate --auto-from` is additive/resumable.
- **`auto_stop.sh`** halts both engines at the next safe boundary.
- **Honest measurement (P9):** only byte-matches bank; near-misses go to `docs/backlog.md`, ranked.
