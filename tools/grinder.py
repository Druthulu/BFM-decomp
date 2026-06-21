#!/usr/bin/env python3
"""grinder.py — Phase 21 token-free permuter grinder (the CPU-bound worker).

Pulls the closest near-misses from the backlog, runs decomp-permuter on each (the permuter
closes regalloc/scheduling gaps — exactly the residual the worker's drafts leave), banks the
true byte-matches through the shared gate_stage (the sole arbiter, G3/P9), and re-logs any
improved-but-still-near draft. LLM-FREE — runs unattended for days under auto_supervisor.sh,
alongside the token-heavy worker waves (CPU budget vs token budget).

  backlog near-miss  ->  decomp-permuter (output-0-* = true byte-match)  ->  gate_stage  ->  bank x reach
  no winner          ->  re-log (closeness may improve) and move on

SAFE EXIT: touch .run/auto/STOP (tools/auto_stop.sh) — finishes the current permute+gate, exits 0.
HEARTBEAT: .run/auto/grinder_heartbeat.json — {ts, state, current, banked, fleet_pct}.

Usage: grinder.py [--permute-secs 120] [-j 14] [--batch 10] [--max-nins 220]
                  [--max-closeness 30] [--attempts 2] [--idle-secs 90] [--once]
"""
import argparse, glob, json, os, shutil, subprocess, sys, time
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import p16_permute, gate_stage, backlog

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
AUTODIR = ".run/auto"
STOP = f"{AUTODIR}/STOP"
HB = f"{AUTODIR}/grinder_heartbeat.json"
DRAFTS = f"{AUTODIR}/grinder_drafts"


def stop_requested():
    return os.path.exists(os.path.join(REPO, STOP))


def log(m):
    print(f"[{time.strftime('%H:%M:%S')}] grinder: {m}", flush=True)


def heartbeat(state, current=None, banked=0, fp=None):
    os.makedirs(os.path.join(REPO, AUTODIR), exist_ok=True)
    json.dump({"ts": time.strftime("%Y-%m-%d %H:%M:%S"), "state": state, "current": current,
               "banked": banked, "fleet_pct": fp},
              open(os.path.join(REPO, HB), "w"), indent=1)


def candidates(max_nins, max_close, tried, attempts):
    """closest still-open near-misses with a saved best draft (permuter-amenable), least-tried first."""
    out = []
    for r in backlog.load_best():
        nm = r.get("name")
        if r.get("status") != "near" or not r.get("best_draft") or not nm:
            continue
        if tried.get(nm, 0) >= attempts:
            continue
        c = r.get("closeness")
        if c is None or c > max_close:          # permuter closes small regalloc/sched gaps, not large rewrites
            continue
        if (r.get("nins") or 999) > max_nins:
            continue
        if not os.path.exists(os.path.join(REPO, r["best_draft"])):
            continue
        out.append(r)
    out.sort(key=lambda r: (tried.get(r["name"], 0), r.get("closeness") or 999))
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--permute-secs", type=int, default=120)
    ap.add_argument("-j", type=int, default=14)
    ap.add_argument("--batch", type=int, default=10)
    ap.add_argument("--max-nins", type=int, default=220)
    ap.add_argument("--max-closeness", type=int, default=30)
    ap.add_argument("--attempts", type=int, default=2)
    ap.add_argument("--idle-secs", type=int, default=90)
    ap.add_argument("--once", action="store_true")
    a = ap.parse_args()
    os.chdir(REPO)
    os.makedirs(AUTODIR, exist_ok=True)
    if stop_requested():
        log("STOP present at startup; remove it to run."); return
    tried, banked, fp = {}, 0, None
    log(f"start (permute={a.permute_secs}s -j{a.j} batch={a.batch} max_close={a.max_closeness})")
    while True:
        if stop_requested():
            log("STOP — clean exit."); heartbeat("stopped", None, banked, fp); return
        cand = candidates(a.max_nins, a.max_closeness, tried, a.attempts)[:a.batch]
        if not cand:
            if a.once:
                log("no candidates (once) — exit."); heartbeat("dry", None, banked, fp); return
            heartbeat("idle", None, banked, fp)
            log(f"no untried candidates; idle {a.idle_secs}s (worker may add more)")
            for _ in range(a.idle_secs):
                if stop_requested():
                    break
                time.sleep(1)
            if stop_requested():
                continue
            tried.clear()                       # let the stochastic permuter re-try after idle
            continue
        if os.path.exists(os.path.join(REPO, DRAFTS)):
            shutil.rmtree(os.path.join(REPO, DRAFTS))
        os.makedirs(os.path.join(REPO, DRAFTS), exist_ok=True)
        won = 0
        for r in cand:
            if stop_requested():
                break
            fn = r["name"]; tried[fn] = tried.get(fn, 0) + 1
            heartbeat("permuting", fn, banked, fp)
            try:
                draft = open(os.path.join(REPO, r["best_draft"])).read()
                pd = p16_permute.setup(fn, draft)
                if not pd:
                    continue
                win = p16_permute.run_permuter(pd, a.permute_secs, a.j)
                if win:
                    open(os.path.join(REPO, DRAFTS, fn + ".c"), "w").write(
                        p16_permute.winner_to_draft(open(win).read()))
                    won += 1; log(f"permuter WON {fn} (close was {r.get('closeness')})")
            except Exception as e:
                log(f"{fn}: {e}")
        if won:
            heartbeat("gating", None, banked, fp)
            s = gate_stage.run_gate(DRAFTS, source_tag="grinder", commit=True)
            banked += s.get("banked", 0); fp = s.get("fleet_pct", fp)
            log(f"gate: banked {s.get('banked')} (+{s.get('propagated')} prop); total {banked}; fleet {fp}%")
            heartbeat("running", None, banked, fp)
        if a.once:
            log(f"once done — banked {banked}."); heartbeat("done", None, banked, fp); return


if __name__ == "__main__":
    main()
