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
import p16_permute, gate_stage, backlog, autopsy

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
AUTODIR = ".run/auto"
STOP = f"{AUTODIR}/STOP"
HB = f"{AUTODIR}/grinder_heartbeat.json"
DRAFTS = f"{AUTODIR}/grinder_drafts"
BLACKLIST = f"{AUTODIR}/grinder_blacklist.json"   # fns the permuter wins but the byte-gate rejects = plumbing-bound; never re-permute
# A BLACKLIST ENTRY IS A VERDICT FROM A SPECIFIC GATE, AND IT EXPIRES WHEN THAT GATE CHANGES.
# Purged 2026-07-15 (Phase-28 T2). The 22 entries were recorded when harvest_verify was single-TU: it
# spliced only into `src/<bin>/<bin>.c`, so a SPLIT-hosted fn's stub literal was never found, the draft
# was never compiled, and the permuter's byte-match was discarded UNBUILT — which this file then recorded
# permanently as "plumbing-bound, never re-permute". 16 of 22 were split-hosted (docs/tooling-audit.md
# :931). The proof it was manufactured, not observed: **8 of the 22 have since MATCHED anyway**
# (func_80131D68/80149374/8014FE60/80150528/8016BBE0/80171C64/80174684/8017F290), and the other 14 would
# have been skipped forever on a verdict from a gate that no longer exists. harvest_verify now derives
# each stub's home TU from the corpus oracle and splices into whichever TU holds it (:122, render()), so
# the mechanism that manufactured these is gone.
# RULE (R35): when the gate changes, purge this file — a persisted negative verdict is only as good as the
# instrument that produced it. Re-derive from the fixed gate; never inherit.


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


def candidates(max_nins, max_close, tried, attempts, blacklist, verdicts=None, stats=None):
    """closest still-open near-misses with a saved best draft (permuter-amenable), least-tried first.

    TARGETING (Phase-29 Task-13A). "closest" is a scalar and a bad proxy for "a search-closer can
    reach it". Measured over the whole open backlog through the whole-binary compile path: of the
    972 records this filter admits, **75 (7.7%) are permuter-shaped**; 547 are STRUCTURAL (a
    different load width, an extra instruction, a flipped branch — no local mutation introduces
    those) and 348 are drafts that are not the function at all (a 15-instruction body against a
    132-instruction target, whose "closeness 117" is pure length artefact).

    So the daemon has been spending ~92% of its CPU where the permuter provably cannot win. That —
    not a missing transform — is why it banked 7 functions all-time, all in Phase 21, and 0 since
    (the Phase-22 audit). Filtering by the MEASURED residual class is the whole fix, and it is free.

    Degrades to the previous undirected behaviour when the corpus has not been collected, and says
    which mode it is in rather than filtering silently (R32)."""
    out = []
    for r in backlog.load_best():
        nm = r.get("name")
        if r.get("status") != "near" or not r.get("best_draft") or not nm:
            continue
        if nm in blacklist:                      # permuter-won-but-gate-rejected (plumbing) — never re-permute
            continue
        if verdicts:
            v = verdicts.get(nm)
            if v is None:                        # not in the corpus (logged after the last collect)
                if stats is not None:
                    stats["unclassified"] += 1   # kept: unknown is not a reason to skip
            elif v.get("bucket") != "permuter":
                if stats is not None:
                    stats[v.get("bucket") or "?"] += 1
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
    ap.add_argument("--no-targeting", action="store_true",
                    help="ignore the measured residual classes and search undirected (the "
                         "pre-Task-13 behaviour; for A/B-ing the targeting filter)")
    a = ap.parse_args()
    os.chdir(REPO)
    os.makedirs(AUTODIR, exist_ok=True)
    if stop_requested():
        log("STOP present at startup; remove it to run."); return
    tried, banked, fp = {}, 0, None
    last_sig = {}                                # fn -> draft_sig at last permute (input-changed gate, T5)
    blacklist = load_blacklist()
    # the MEASURED residual class per function (tools/autopsy.py collect). Empty = not collected;
    # the daemon then runs undirected exactly as before, and says so.
    verdicts = {} if a.no_targeting else autopsy.verdicts()
    log(f"start (permute={a.permute_secs}s -j{a.j} batch={a.batch} max_close={a.max_closeness}; "
        f"blacklist={len(blacklist)} plumbing-bound fns skipped)")
    log("targeting: %s" % (
        f"ON — {len(verdicts)} classified; only bucket=permuter is admitted"
        if verdicts else
        "OFF — no .run/autopsy/residuals.jsonl (run tools/autopsy.py collect); "
        "searching UNDIRECTED, which historically wastes ~92% of the CPU"))
    while True:
        if stop_requested():
            log("STOP — clean exit."); heartbeat("stopped", None, banked, fp); return
        import collections as _c
        skipped = _c.Counter()
        cand = candidates(a.max_nins, a.max_closeness, tried, a.attempts, blacklist,
                          verdicts, skipped)[:a.batch]
        if skipped:
            log("targeting skipped %d non-permuter candidate(s): %s"
                % (sum(skipped.values()), dict(skipped)))
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
                # the MEASURED class beats the logged label: 91% of records carry no label at
                # all, so permuter_weights.classify() returned None and the search ran on gcc
                # defaults. residual_class names the class from today's bytes.
                _v = verdicts.get(fn) or {}
                pd = p16_permute.setup(fn, draft, asm_sub,
                                       klass=_v.get("profile") or r.get("klass"),
                                       where=r.get("where_stuck") or "")
                if not pd:
                    continue
                win = p16_permute.run_permuter(pd, a.permute_secs, a.j)
                if win:
                    _wtext = p16_permute.winner_to_draft(open(win).read())
                    open(os.path.join(REPO, DRAFTS, fn + ".c"), "w").write(_wtext)
                    # Task-12: durably persist the winning C BEFORE gate_stage banks/propagates/commits, so a
                    # mid-flight interrupt (kill or a revert of the uncommitted bank) never loses a hard-won
                    # permuter crack (this session's lesson: 3 wins lost to exactly that). permuter-winners/ is
                    # the recovery source — winner_to_draft(...) form, re-gateable any time.
                    _wdir = os.path.join(REPO, ".run", "permuter-winners"); os.makedirs(_wdir, exist_ok=True)
                    open(os.path.join(_wdir, fn + ".c"), "w").write(_wtext)
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
                # §55b LAW: bank with --no-propagate, commit the cheap verified banks, and run
                # ONE targeted `dedup_propagate --addr <banked>` afterwards as its own batch.
                # gate_stage's propagate=True path is `dedup_propagate --auto-from`, the fleet-wide
                # slow route that timed out at 3600s and left 90/140 overlays broken (887 files) —
                # and because it runs INSIDE the gate, a propagate failure takes the banks with it.
                # The grinder is the unattended caller, so it must never fire that path.
                s = gate_stage.run_gate(DRAFTS, binary=binary, source_tag="grinder", commit=True,
                                        propagate=False)
                banked += s.get("banked", 0); fp = s.get("fleet_pct", fp)
                verified |= set(s.get("verified", []))
                log(f"gate {binary}: banked {s.get('banked')} (UN-propagated by design, §55b); "
                    f"total {banked}; fleet {fp}%")
                if s.get("verified"):
                    log("  -> propagate as its own batch: "
                        + "; ".join("tools/dedup_propagate.py --addr 0x%s --recover" % f.split('_')[-1]
                                    for f in s["verified"][:4]))
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
