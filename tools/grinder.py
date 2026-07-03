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
BLACKLIST = f"{AUTODIR}/grinder_blacklist.json"   # fns the permuter wins but the byte-gate rejects = plumbing-bound; never re-permute


def stop_requested():
    return os.path.exists(os.path.join(REPO, STOP))


def load_blacklist():
    try:
        return set(json.load(open(os.path.join(REPO, BLACKLIST))))
    except Exception:
        return set()


def save_blacklist(bl):
    json.dump(sorted(bl), open(os.path.join(REPO, BLACKLIST), "w"), indent=1)


def draft_sig(r):
    """the input SIGNATURE the permuter's yield depends on: (best_draft mtime, closeness). A fn
    whose signature is unchanged since we last permuted it can NEVER newly win (the permuter is
    deterministic given base.c + target.o) — so re-permuting it just burns CPU. Used by the
    input-changed idle gate (T5), replacing the old blind tried.clear() that re-tried every
    floor-victim on every idle tick (the R14-identified churn — Phase 24 CURRENT_PHASE)."""
    p = r.get("best_draft")
    try:
        m = round(os.path.getmtime(os.path.join(REPO, p)), 3) if p else 0.0
    except OSError:
        m = 0.0
    return (m, r.get("closeness"))


def log(m):
    print(f"[{time.strftime('%H:%M:%S')}] grinder: {m}", flush=True)


def asm_subdir_for(binary, fn):
    """the asm subdir holding binary's <fn>.s (main or _a/_o0 split); None if absent."""
    g = glob.glob(os.path.join(REPO, f"asm/{binary}/nonmatchings/*/{fn}.s"))
    return os.path.dirname(os.path.relpath(g[0], REPO)) if g else None


def heartbeat(state, current=None, banked=0, fp=None):
    os.makedirs(os.path.join(REPO, AUTODIR), exist_ok=True)
    json.dump({"ts": time.strftime("%Y-%m-%d %H:%M:%S"), "state": state, "current": current,
               "banked": banked, "fleet_pct": fp},
              open(os.path.join(REPO, HB), "w"), indent=1)


def candidates(max_nins, max_close, tried, attempts, blacklist):
    """closest still-open near-misses with a saved best draft (permuter-amenable), least-tried first."""
    out = []
    for r in backlog.load_best():
        nm = r.get("name")
        if r.get("status") != "near" or not r.get("best_draft") or not nm:
            continue
        if nm in blacklist:                      # permuter-won-but-gate-rejected (plumbing) — never re-permute
            continue
        if tried.get(nm, 0) >= attempts:
            continue
        c = r.get("closeness")
        if c is None or c > max_close:          # permuter closes small regalloc/sched gaps, not large rewrites
            continue
        if r.get("nins") is not None and r["nins"] > max_nins:   # known-too-big; None (off-077 manifest) = allow
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
    last_sig = {}                                # fn -> draft_sig at last permute (input-changed gate, T5)
    blacklist = load_blacklist()
    log(f"start (permute={a.permute_secs}s -j{a.j} batch={a.batch} max_close={a.max_closeness}; "
        f"blacklist={len(blacklist)} plumbing-bound fns skipped)")
    while True:
        if stop_requested():
            log("STOP — clean exit."); heartbeat("stopped", None, banked, fp); return
        cand = candidates(a.max_nins, a.max_closeness, tried, a.attempts, blacklist)[:a.batch]
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
            # INPUT-CHANGED GATING (T5, replaces the old blind `tried.clear()`): re-open ONLY the
            # fns whose input signature changed since we last permuted them — i.e. the worker
            # improved the draft or its closeness. The permuter is deterministic given base.c +
            # target.o, so re-permuting an UNCHANGED floor-victim can never newly win; the old
            # clear() re-tried every one on every idle tick, burning CPU for zero banks (the
            # R14-identified idle-churn). With the T2 floor-free scorer, a genuinely closeable fn
            # wins on its FIRST pass; anything still open after `attempts` is input-bound until the
            # worker feeds it a better draft.
            cur = {r.get("name"): draft_sig(r) for r in backlog.load_best() if r.get("name")}
            reopened = [fn for fn in list(tried) if cur.get(fn) != last_sig.get(fn)]
            for fn in reopened:
                tried.pop(fn, None); last_sig.pop(fn, None)
            if reopened:
                log(f"input-changed: re-opened {len(reopened)} fn(s) "
                    f"({', '.join(reopened[:6])}{'…' if len(reopened) > 6 else ''})")
            else:
                log("no inputs changed since last pass — staying idle (no churn)")
            continue
        if os.path.exists(os.path.join(REPO, DRAFTS)):
            shutil.rmtree(os.path.join(REPO, DRAFTS))
        os.makedirs(os.path.join(REPO, DRAFTS), exist_ok=True)
        won = []                                  # (fn, binary): gate grouped by binary (harvest_verify filters)
        for r in cand:
            if stop_requested():
                break
            fn = r["name"]; tried[fn] = tried.get(fn, 0) + 1
            last_sig[fn] = draft_sig(r)                    # record the input we're about to permute (T5 gate)
            binary = r.get("binary") or "ov_SC01_077"     # legacy records: the canonical site (a 077-stub fn still gates)
            asm_sub = asm_subdir_for(binary, fn)
            heartbeat("permuting", fn, banked, fp)
            try:
                if not asm_sub:
                    log(f"{fn}: no .s under {binary} — skip"); continue
                draft = open(os.path.join(REPO, r["best_draft"])).read()
                # §31-directed mutation (T5): the wave-diagnosed residual class biases the pass
                # weights toward that class's levers (permuter_weights). A generic/absent class
                # -> the plain gcc defaults (unchanged undirected search).
                pd = p16_permute.setup(fn, draft, asm_sub,
                                       klass=r.get("klass"), where=r.get("where_stuck") or "")
                if not pd:
                    continue
                win = p16_permute.run_permuter(pd, a.permute_secs, a.j)
                if win:
                    open(os.path.join(REPO, DRAFTS, fn + ".c"), "w").write(
                        p16_permute.winner_to_draft(open(win).read()))
                    won.append((fn, binary)); log(f"permuter WON {fn} @ {binary} (close was {r.get('closeness')})")
            except Exception as e:
                log(f"{fn}: {e}")
        if won:
            heartbeat("gating", None, banked, fp)
            import collections
            by_bin = collections.defaultdict(list)
            for fn, binary in won:
                by_bin[binary].append(fn)
            verified = set()
            for binary, fns in sorted(by_bin.items()):     # one gate per source binary; propagate stamps × reach
                s = gate_stage.run_gate(DRAFTS, binary=binary, source_tag="grinder", commit=True)
                banked += s.get("banked", 0); fp = s.get("fleet_pct", fp)
                verified |= set(s.get("verified", []))
                log(f"gate {binary}: banked {s.get('banked')} (+{s.get('propagated')} prop); total {banked}; fleet {fp}%")
            # A permuter win the whole-binary gate STILL rejects is plumbing-bound (not regalloc/sched) —
            # re-permuting can never bank it. Blacklist so the grinder stops churning it (the §20 trap).
            rejected = [f for f, _b in won if f not in verified]
            if rejected:
                blacklist.update(rejected); save_blacklist(blacklist)
                log(f"blacklisted {len(rejected)} permuter-won/gate-rejected (plumbing): {', '.join(rejected)}")
            heartbeat("running", None, banked, fp)
        if a.once:
            log(f"once done — banked {banked}."); heartbeat("done", None, banked, fp); return


if __name__ == "__main__":
    main()
