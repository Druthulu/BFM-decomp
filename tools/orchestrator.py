#!/usr/bin/env python3
"""orchestrator.py — Phase 21 ROI orchestrator (the deterministic half of the worker loop).

The unattended loop is: the Claude orchestrator (/loop, Max) runs one cycle per tick —
  orchestrator.py prep   -> pick the current ROI pool, emit .run/auto/wave_batch.json
  <orchestrator launches the worker Workflow over that batch (the ONE step only the model can do)>
  orchestrator.py finish -> gate_stage the drafts (bank/propagate/log), record the close-rate,
                            rotate the pool when it's tapped, print a compact JSON summary
This file owns the ROI state + pool rotation; the model owns launching the Workflow. The grinder
(tools/grinder.py) runs alongside, token-free, draining the backlog the waves fill.

ROI rotation (balanced, ROI-gated — Drew): harvest a pool until its banked/drafts close-rate is
below --threshold for --patience consecutive waves, then advance: tractable -> giants -> o0 ->
capped -> (wrap to tractable). auto_stop.sh's STOP sentinel halts everything.

State: .run/auto/orch_state.json {pool, idx, low_streak, waves, banked_total, history:[...]}.

Usage:
  orchestrator.py prep   [--n 24] [--region main]
  orchestrator.py finish --drafts .run/drafts-wave [--commit]
  orchestrator.py status
"""
import argparse, json, os, re, subprocess, sys, time
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gate_stage

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PY = ".venv/bin/python"
STATE = os.path.join(REPO, ".run/auto/orch_state.json")
BATCH = ".run/auto/wave_batch.json"
POOLS = ["tractable", "giants", "o0", "capped"]   # ROI rotation order


def load_state():
    if os.path.exists(STATE):
        return json.load(open(STATE))
    return {"pool": POOLS[0], "idx": 0, "low_streak": 0, "waves": 0, "banked_total": 0, "history": []}


def save_state(s):
    os.makedirs(os.path.dirname(STATE), exist_ok=True)
    json.dump(s, open(STATE, "w"), indent=1)


def sh(cmd, timeout=None):
    return subprocess.run(cmd, capture_output=True, text=True, cwd=REPO, timeout=timeout)


def _top_class(min_n):
    """The backlog residual class with the most near-misses (>= min_n), for a class-focused wave."""
    out = sh([PY, "tools/wave_targets.py", "--list-classes"], timeout=60).stdout
    best, bestn = None, 0
    for line in out.splitlines():
        m = re.match(r"(\w+)\s+n=\s*(\d+)", line.strip())
        if m and m.group(1) != "OTHER":
            n = int(m.group(2))
            if n > bestn:
                best, bestn = m.group(1), n
    return (best, bestn) if bestn >= min_n else (None, bestn)


def cmd_prep(a):
    s = load_state()
    sh(["rm", "-rf", ".run/drafts-wave"])                   # fresh draft dir per wave
    os.makedirs(os.path.join(REPO, ".run/drafts-wave"), exist_ok=True)
    sh([PY, "tools/build_fuel_manifest.py"], timeout=120)   # refresh cached/stub status (cheap)
    # FLYWHEEL: prefer a CLASS-FOCUSED re-attempt wave when the backlog has a worthwhile, distill-able
    # class (the Phase-18 learning model); else harvest a FRESH pool (which classifies new near-misses).
    mode, sel = "pool", s["pool"]
    if a.mode in ("auto", "class"):
        cls, cn = _top_class(a.class_threshold)
        if cls:
            mode, sel = "class", cls
    if mode == "class":
        sh([PY, "tools/wave_targets.py", "--class", sel, "--n", str(a.n), "--out", BATCH], timeout=120)
    else:
        sh([PY, "tools/wave_targets.py", "--pool", sel, "--n", str(a.n),
            "--region", a.region, "--out", BATCH], timeout=120)
    n = 0
    try:
        n = len(json.load(open(os.path.join(REPO, BATCH))))
    except Exception:
        pass
    print(json.dumps({"mode": mode, "sel": sel, "n": n, "batch": BATCH, "wave": s["waves"] + 1}))


def cmd_finish(a):
    s = load_state()
    summary = gate_stage.run_gate(a.drafts, source_tag="worker", commit=a.commit)
    banked, drafts = summary.get("banked", 0), summary.get("drafts", 0) or 1
    close = banked / drafts
    s["waves"] += 1
    s["banked_total"] += banked
    s["history"] = (s.get("history", []) + [{"pool": s["pool"], "banked": banked,
                    "drafts": summary.get("drafts", 0), "prop": summary.get("propagated", 0),
                    "fleet": summary.get("fleet_pct"), "ts": time.strftime("%Y-%m-%d %H:%M:%S")}])[-50:]
    # ROI gate: rotate the pool after `patience` low-yield waves
    if close < a.threshold:
        s["low_streak"] = s.get("low_streak", 0) + 1
    else:
        s["low_streak"] = 0
    rotated = False
    if s["low_streak"] >= a.patience:
        s["idx"] = (s.get("idx", 0) + 1) % len(POOLS)
        s["pool"] = POOLS[s["idx"]]
        s["low_streak"] = 0
        rotated = True
    save_state(s)
    print(json.dumps({**summary, "close_rate": round(close, 3), "pool": s["history"][-1]["pool"],
                      "rotated_to": s["pool"] if rotated else None,
                      "waves": s["waves"], "banked_total": s["banked_total"]}))


def cmd_status(a):
    s = load_state()
    print(json.dumps(s, indent=1))


def main():
    ap = argparse.ArgumentParser()
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("prep"); p.add_argument("--n", type=int, default=24); p.add_argument("--region", default="main")
    p.add_argument("--mode", default="auto", choices=["auto", "class", "pool"],
                   help="auto=class-focused wave when the backlog has a distill-able class, else pool harvest")
    p.add_argument("--class-threshold", dest="class_threshold", type=int, default=6,
                   help="min near-misses in a class before a class-focused wave fires")
    f = sub.add_parser("finish"); f.add_argument("--drafts", default=".run/drafts-wave")
    f.add_argument("--commit", action="store_true"); f.add_argument("--threshold", type=float, default=0.15)
    f.add_argument("--patience", type=int, default=2)
    sub.add_parser("status")
    a = ap.parse_args()
    {"prep": cmd_prep, "finish": cmd_finish, "status": cmd_status}[a.cmd](a)


if __name__ == "__main__":
    main()
