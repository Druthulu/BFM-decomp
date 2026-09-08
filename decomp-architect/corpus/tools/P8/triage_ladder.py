#!/usr/bin/env python3
"""tools/triage_ladder.py — the ZERO-TOKEN pre-agent triage ladder. (P31 S69)

WHAT IT IS. One deterministic, local pass that sits between `wave_args` and the drafting agent and
answers *"does this target need an agent at all?"* before one is spent — and a second pass, after a
draft exists, that answers *"does this draft need another agent, or just a gate?"*.

    draw -> cards -> packs -> wave_args -> [PRE ladder] -> draft -> [POST ladder] -> gate -> bank
                                              |                        |
                                    banked / wall / parked      gate-first / redraft / escalate

THE PRE/POST SPLIT IS THE CORRECTION THIS TOOL EXISTS TO MAKE (S68's spec conflated them).
`residual_rules_b.classify` needs a DRAFT: it runs `match_one` and reasons about the residual. At
DRAW time there is no draft, so only the TARGET-SIDE tiers can fire — and those are the ones that
save the whole agent rather than one iteration:

    PRE  (no draft, no build, milliseconds)   BANKED · WALL-332 · PARKED
    POST (a draft exists, runs match_one)     everything in residual_rules_b

WHY THE POST TIERS ARE NOT "FREE BANKS" — measured S69, the reason this file is not just a wrapper.
S68 advertised 32 free banks: 10 `NOCOMPILE-UNDECLARED-FIXED` (an `extern` derived from the target's
own `.s` makes the draft compile) + 22 `INTEG-STANDALONE-MATCH` (already matches standalone), all
verified by `match_one` at closeness 0. Gated today, the honest numbers were:

    4 of 32 had already banked since the checkpoint was written (stale by construction)
    the other 28 gated 0/28 — every failure a DECLARATION conflict inside the real TU:
        `conflicting types for func_X` · `too few arguments to function func_X'`

`match_one` compiles the draft ALONE. The TU it must live in already carries a forward declaration
written for a call site (`extern void func_X(void);`) that conflicts with the draft's real signature
(`void func_X(void *a0)`). **A standalone closeness of 0 proves the BODY and says nothing about the
TU accepting the SIGNATURE.** The autodecl arm is actively worse in-TU: the `extern` it adds to
satisfy the standalone probe is a SECOND conflicting declaration.

So these tiers route to GATE-FIRST *with a recipe*, never to "bank it":

    fix_arity_callers --any-proto --binary <B> --funcs <FN>   # 1: `conflicting types'
    cast_self_callers --binary <B> --funcs <FN> --drafts <D>  # 2: `too few arguments' (§378)
    then gate                                                 # the byte-gate is the only arbiter

Step 2 only becomes visible once step 1 lands — the no-proto decl makes the DRAFT'S DEFINITION the
prototype in scope, so the TU's own call site fails anew. Stopping at step 1 is how this class read
as dead for a whole session; with both, S69 banked it (byte-proven ov_SC04_010/func_8017D6CC).

THE QUIESCENCE RULE (R34/R42, measured S69). The stub oracle is transiently wrong IN BOTH DIRECTIONS
while a gate lane runs: a concurrently-running gate had `ov_SC01_004:func_8017EB30` banked in the
working tree when a second gate read the oracle, so it was skipped as `already-banked` — and it is
still an INCLUDE_ASM stub today, because killing that gate mid-merge lost the bank. A ladder that
reads a moving tree manufactures exactly the false skip it exists to prevent, so this tool REFUSES
to classify while a gate or a drafting lane is live (`--force` to override, loudly).

ASYMMETRY (why the acceptance test is not optional polish). A false "needs an agent" costs one
draft. A false "skip — already banked" silently drops a bankable function, possibly forever. So
`--acceptance` runs the PRE ladder over the WHOLE corpus in both directions and fails on any
disagreement:

    R39 false-skip   every OPEN stub must NOT classify BANKED          (denominator: all open stubs)
    R39 recall       a sample of MATCHED functions must classify BANKED
    R39 wall-NC      no already-banked function may trip the WALL tier (it matched, so it cannot be
                     a toolchain wall) — the negative control against the already-succeeded population
    R32 coverage     classified == denominator, and every row carries a verdict

Usage:
    triage_ladder.py --pre .run/<wave>            # classify a wave's targets.json -> <wave>/triage.json
    triage_ladder.py --pre-list B:FN[,B:FN...]    # ad-hoc PRE classification
    triage_ladder.py --escalate B:FN              # exit 2 if this target must not be escalated
    triage_ladder.py --post <dir|B:PATH,...>      # full residual_rules_b routing for existing drafts
    triage_ladder.py --acceptance                 # the R39/R32 harness (no builds; seconds)
"""
import argparse
import json
import os
import random
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

import corpus                       # noqa: E402  the derived corpus oracle (R33)
import wall_sweep                   # noqa: E402  the §332 enumerator

PARKED_LEDGER = os.path.join(REPO, ".run/triage_parked.json")

# Verdicts the PRE ladder can reach. The ROUTE is what the caller acts on.
SKIP_VERDICTS = ("BANKED", "WALL-332", "PARKED")

ROUTE = {
    "BANKED":   "SKIP — already byte-matches in the tree; zero tokens (a stale card).",
    "WALL-332": "SKIP — §332 maspsx delay-slot wall; never draft, never escalate.",
    "PARKED":   "SKIP — on the parked ledger with a recorded reason.",
    "DRAFT":    "DRAFT — nothing target-side refuses it.",
}


# ---------------------------------------------------------------- quiescence

def _live_processes():
    """Rows of any running gate/build lane. `pgrep -af`, never `pgrep -c`.

    MEASURED S69: `pgrep -c "[p]arallel_gate"` returned 0 twice for a process that `pgrep -af`
    listed seconds later, and acting on that false zero tore down a live run. A COUNT is not
    evidence here; the rows are.
    """
    pat = r"parallel_gate\.py|harvest_verify\.py|gate_stage\.py|gater_lane\.py|gate_wave\.py"
    r = subprocess.run(["pgrep", "-af", pat], capture_output=True, text=True)
    rows = [ln for ln in r.stdout.splitlines() if ln.strip()]
    # MEASURED S69: the raw match counted 34 "gate processes" on a tree running exactly 2. `pgrep -af`
    # matches ANY argv containing the pattern — the harness's own `/bin/bash -c` wrapper, a grep, this
    # tool's own command line. A guard that can never pass is as useless as one that never fires (R54),
    # so keep only rows that are an actual interpreter invoking one of those tools.
    keep = []
    for ln in rows:
        argv = ln.split(None, 1)[1] if " " in ln else ""
        if "triage_ladder" in argv or argv.startswith("/bin/bash") or argv.startswith("bash "):
            continue
        if "python" not in argv.split(" ")[0] and "python" not in argv[:40]:
            continue
        keep.append(ln)
    return keep


def _live_agents():
    try:
        import lane_inflight
        return list(lane_inflight.load().items())
    except Exception:
        return []


def assert_quiescent(force=False):
    procs, agents = _live_processes(), _live_agents()
    if not procs and not agents:
        return
    who = []
    if procs:
        who.append("%d gate/build process(es): %s" % (len(procs), procs[0][:110]))
    if agents:
        who.append("%d drafting agent(s) in flight: %s" % (len(agents), ", ".join(k for k, _ in agents[:4])))
    msg = ("REFUSED — the tree is not quiescent (%s). The stub oracle is transiently wrong in BOTH "
           "directions while a gate merges, which manufactures the exact false skip this ladder "
           "exists to prevent (S69: ov_SC01_004:func_8017EB30). Wait, or pass --force."
           % "; ".join(who))
    if not force:
        sys.exit(msg)
    print("[triage] WARNING, --force: " + msg, file=sys.stderr)


# ---------------------------------------------------------------- PRE tiers

_stub_cache = {}


def open_stubs(binary):
    if binary not in _stub_cache:
        _stub_cache[binary] = {s.symbol: s for s in corpus.stubs(binary).values()}
    return _stub_cache[binary]


def load_parked():
    try:
        with open(PARKED_LEDGER) as fh:
            return json.load(fh)
    except (OSError, ValueError):
        return {}


def pre_classify(binary, fn, parked=None, asm_path=None):
    """Target-side only: no draft, no build. Returns a verdict dict."""
    out = {"binary": binary, "fn": fn, "verdict": None, "evidence": None, "asm": asm_path}
    stubs = open_stubs(binary)
    st = stubs.get(fn)
    if st is None:
        out["verdict"] = "BANKED"
        out["evidence"] = "not an open stub in %s (corpus.stubs = sig - INCLUDE_ASM)" % binary
        return out
    out["asm"] = asm_path or st.asm_path
    out["sub"] = st.asm_dir
    out["nins"] = None

    park = (parked if parked is not None else load_parked()).get("%s:%s" % (binary, fn))
    if park:
        out["verdict"] = "PARKED"
        out["evidence"] = str(park)[:200]
        return out

    s_abs = os.path.join(REPO, out["asm"])
    try:
        hits = wall_sweep.scan(s_abs)
    except Exception as e:                       # a refusing scanner is reported, never assumed clean
        out["verdict"] = "DRAFT"
        out["evidence"] = "wall scan refused (%s) — not treated as clean, treated as unknown" % str(e)[:80]
        out["scan_error"] = True
        return out
    if hits:
        out["verdict"] = "WALL-332"
        out["evidence"] = ("%d delay slot(s) hold a %%lo macro tail (first: line %d)"
                           % (len(hits), hits[0][0]))
        return out

    out["verdict"] = "DRAFT"
    out["evidence"] = "open stub, no wall, not parked"
    return out


# ---------------------------------------------------------------- modes

def mode_pre(wave, force, out_path=None):
    assert_quiescent(force)
    tgt = os.path.join(REPO, wave, "targets.json")
    if not os.path.exists(tgt):
        sys.exit("REFUSED: no %s" % tgt)
    targets = json.load(open(tgt))
    parked = load_parked()
    rows = []
    for t in targets:
        b, fn = t.get("binary"), t.get("name")
        if not b or not fn:
            sys.exit("REFUSED: target without binary/name: %r (R43)" % t)
        rows.append(pre_classify(b, fn, parked, t.get("asm")))
    assert len(rows) == len(targets), "R32: classified %d of %d" % (len(rows), len(targets))
    _report(rows, len(targets))
    out = out_path or os.path.join(REPO, wave, "triage.json")
    json.dump(rows, open(out, "w"), indent=1)
    keep = [t for t, r in zip(targets, rows) if r["verdict"] == "DRAFT"]
    excl = os.path.join(REPO, wave, "triage_exclude.txt")
    with open(excl, "w") as fh:
        for t, r in zip(targets, rows):
            if r["verdict"] != "DRAFT":
                fh.write("%s:%s\t%s\t%s\n" % (r["binary"], r["fn"], r["verdict"], r["evidence"]))
    print("[triage] wrote %s and %s; %d of %d target(s) still need an agent"
          % (os.path.relpath(out, REPO), os.path.relpath(excl, REPO), len(keep), len(targets)))
    return 0


def mode_pre_list(spec, force):
    assert_quiescent(force)
    pairs = [s.split(":", 1) for s in spec.split(",") if s.strip()]
    parked = load_parked()
    rows = [pre_classify(b, fn, parked) for b, fn in pairs]
    for r in rows:
        print("%-14s %-16s %-9s %s" % (r["binary"], r["fn"], r["verdict"], r["evidence"]))
    _report(rows, len(pairs))
    return 0


def mode_escalate(spec, force):
    """The check S68 was missing: it escalated a §332 wall at closeness 8 to a frontier model."""
    assert_quiescent(force)
    if ":" not in spec:
        sys.exit("--escalate wants BINARY:FN")
    b, fn = spec.split(":", 1)
    r = pre_classify(b, fn)
    print("%s:%s -> %s (%s)" % (b, fn, r["verdict"], r["evidence"]))
    if r["verdict"] in SKIP_VERDICTS:
        print("REFUSED TO ESCALATE: %s" % ROUTE[r["verdict"]])
        return 2
    print("escalation allowed by the target-side tiers (the residual tier is the caller's job)")
    return 0


def mode_post(spec, force, jobs):
    """Full residual routing for drafts that already exist. Runs match_one — needs a quiet tree."""
    assert_quiescent(force)
    import residual_rules_b as rr
    cases = []
    if os.path.isdir(spec):
        for b in sorted(os.listdir(spec)):
            d = os.path.join(spec, b)
            if not os.path.isdir(d):
                continue
            binary = b.split("-")[0]
            for f in sorted(os.listdir(d)):
                if f.endswith(".c"):
                    cases.append((binary, f[:-2], os.path.relpath(os.path.join(d, f), REPO)))
    else:
        for item in spec.split(","):
            b, path = item.split(":", 1)
            cases.append((b, os.path.basename(path)[:-2], path))
    if not cases:
        sys.exit("REFUSED: --post found no drafts in %r" % spec)
    rows = []
    for binary, fn, path in cases:
        pre = pre_classify(binary, fn)
        if pre["verdict"] in SKIP_VERDICTS:
            pre["route"] = ROUTE[pre["verdict"]]
            rows.append(pre)
            continue
        v = rr.classify(binary, fn, path)
        v["route"] = _route_post(v)
        rows.append(v)
    assert len(rows) == len(cases), "R32: classified %d of %d" % (len(rows), len(cases))
    for r in rows:
        print("%-14s %-16s %-26s %s" % (r["binary"], r["fn"], r.get("top") or r.get("verdict"),
                                        (r.get("route") or "")[:80]))
    return 0


def _route_post(v):
    top = v.get("top")
    if top in ("INTEG-STANDALONE-MATCH", "NOCOMPILE-UNDECLARED-FIXED", "NOCOMPILE-UNDECLARED",
               "NOCOMPILE-UNDECLARED-MEASURED", "NOCOMPILE-DECL-CONFLICT"):
        return ("GATE-FIRST (integration-blocked, NOT a free bank — S69 gated 0/28 of this class raw). "
                "Run BOTH steps, in order — fixing the first only reveals the second (§376/§378): "
                "fix_arity_callers --any-proto --binary %s --funcs %s   [conflicting types] ; "
                "cast_self_callers --binary %s --funcs %s --drafts <dir>   [too few arguments] ; "
                "then gate."
                % (v.get("binary"), v.get("fn"), v.get("binary"), v.get("fn")))
    if top == "ALREADY-BANKED":
        return ROUTE["BANKED"]
    if top == "W332-MASPSX-WALL":
        return ROUTE["WALL-332"]
    if top == "REDRAFT-SIZE-MISMATCH":
        return "REDRAFT — the draft is not the target function."
    return "DRAFT/ITERATE — no cheaper route found."


def _report(rows, denom):
    counts = {}
    for r in rows:
        counts[r["verdict"]] = counts.get(r["verdict"], 0) + 1
    parts = ", ".join("%s %d" % (k, counts[k]) for k in sorted(counts))
    skipped = sum(counts.get(k, 0) for k in SKIP_VERDICTS)
    print("[triage] %d of %d classified (R32): %s — %d skip, %d draft"
          % (len(rows), denom, parts, skipped, counts.get("DRAFT", 0)))


# ---------------------------------------------------------------- acceptance

def mode_acceptance(force, sample, seed=1234):
    """R39 both directions + R32 coverage. No builds — the PRE ladder is pure filesystem work."""
    assert_quiescent(force)
    rnd = random.Random(seed)
    import dup_report
    binaries = list(dup_report.BINARIES)
    parked = load_parked()
    fails = []

    # --- R39 FALSE-SKIP: no OPEN stub may classify as a skip verdict for the BANKED reason.
    n_open = 0
    false_skips = []
    for b in binaries:
        try:
            stubs = open_stubs(b)
        except Exception as e:
            fails.append("stub oracle refused %s: %s" % (b, str(e)[:80]))
            continue
        for fn in stubs:
            n_open += 1
            r = pre_classify(b, fn, parked)
            if r["verdict"] == "BANKED":
                false_skips.append("%s:%s" % (b, fn))
    print("[accept] R39 false-skip: %d open stub(s) scanned across %d binaries; %d classified BANKED"
          % (n_open, len(binaries), len(false_skips)))
    if false_skips:
        fails.append("FALSE SKIP — %d open stub(s) called BANKED: %s"
                     % (len(false_skips), " ".join(false_skips[:8])))

    # --- R39 RECALL: matched functions must classify BANKED.
    n_recall, misses = 0, []
    for b in binaries:
        try:
            m = corpus.matched(b)
        except Exception:
            continue
        names = [row.get("name") for row in m.values() if row.get("name")]
        if not names:
            continue
        for fn in rnd.sample(names, min(sample, len(names))):
            n_recall += 1
            r = pre_classify(b, fn, parked)
            if r["verdict"] != "BANKED":
                misses.append("%s:%s -> %s" % (b, fn, r["verdict"]))
    print("[accept] R39 recall: %d matched function(s) sampled; %d not classified BANKED"
          % (n_recall, len(misses)))
    if misses:
        fails.append("RECALL MISS — %d matched fn(s) not seen as banked: %s"
                     % (len(misses), " ".join(misses[:8])))

    # --- R39 WALL CONTROL, two-sided, over a denominator that can actually exist.
    # THE FIRST DRAFT OF THIS TEST ASKED FOR EVIDENCE THAT CANNOT EXIST (P31 S69): it scanned the
    # `.s` of already-BANKED functions, reasoning that code the triple emitted from C cannot be a
    # toolchain wall. But splat writes assembly only for functions still wrapped in INCLUDE_ASM, so
    # a banked function has NO `.s` at all — the control scanned 0 files and printed `0 tripped`,
    # which reads exactly like a pass. The R32 empty-denominator assertion below is the only reason
    # it was ever visible, on its first run. Replaced with the control that is possible: sweep every
    # OPEN stub and require the wall tier to fire on EXACTLY the enumerated wall set — extra hits are
    # over-firing (a false skip, the expensive direction), missing hits are under-firing.
    n_nc, fired = 0, set()
    for b in binaries:
        try:
            stubs = open_stubs(b)
        except Exception:
            continue
        for fn, st in stubs.items():
            n_nc += 1
            r = pre_classify(b, fn, parked)
            if r["verdict"] == "WALL-332":
                fired.add("%s:%s" % (b, fn))
    known = set()
    wl = os.path.join(REPO, ".run/S68_walls_332.txt")
    if os.path.exists(wl):
        known = {ln.strip() for ln in open(wl) if ln.strip()}
    extra, missing = sorted(fired - known), sorted(known - fired)
    print("[accept] R39 wall control: %d open stub(s) swept; tier fired on %d; enumerated %d "
          "(extra %d, missing %d)" % (n_nc, len(fired), len(known), len(extra), len(missing)))
    if extra:
        fails.append("WALL OVER-FIRE — %d stub(s) called a wall that the enumeration does not list: %s"
                     % (len(extra), " ".join(extra[:8])))
    if known and missing:
        fails.append("WALL UNDER-FIRE — %d enumerated wall(s) the tier did not catch: %s"
                     % (len(missing), " ".join(missing[:8])))

    # --- R32 COVERAGE: the denominator is stated, and it is not zero.
    if n_open == 0 or n_recall == 0 or n_nc == 0:
        fails.append("R32 COVERAGE — a test scanned an EMPTY denominator (open=%d recall=%d nc=%d); "
                     "a green run over nothing is the silent-skip defect this rule exists for"
                     % (n_open, n_recall, n_nc))

    if fails:
        print("\n[accept] FAILED — %d problem(s):" % len(fails))
        for f in fails:
            print("  * " + f)
        return 1
    print("\n[accept] PASS — false-skip 0/%d, recall %d/%d, wall NC 0/%d" % (n_open, n_recall - len(misses), n_recall, n_nc))
    return 0


def _matched_asm_path(binary, fn):
    """A banked function's .s still exists on disk even though no INCLUDE_ASM references it."""
    root = os.path.join(REPO, "asm") if binary == "main" else os.path.join(REPO, "asm", binary)
    if not os.path.isdir(root):
        return None
    r = subprocess.run(["find", root, "-name", fn + ".s", "-path", "*nonmatchings*"],
                       capture_output=True, text=True)
    hits = r.stdout.split()
    if binary == "main":
        hits = [h for h in hits
                if os.path.relpath(h, os.path.join(REPO, "asm")).split(os.sep)[0] == "nonmatchings"]
    return hits[0] if len(hits) == 1 else None


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--pre", metavar="WAVE", help="classify <WAVE>/targets.json (no builds)")
    ap.add_argument("--pre-list", metavar="B:FN,...", help="ad-hoc PRE classification")
    ap.add_argument("--escalate", metavar="B:FN", help="exit 2 if this target must not be escalated")
    ap.add_argument("--post", metavar="DIR|B:PATH,...", help="full residual routing (runs match_one)")
    ap.add_argument("--acceptance", action="store_true", help="the R39/R32 harness")
    ap.add_argument("--sample", type=int, default=3, help="per-binary sample for the acceptance tests")
    ap.add_argument("--jobs", type=int, default=8)
    ap.add_argument("--out", default=None)
    ap.add_argument("--force", action="store_true", help="classify even on a non-quiescent tree (loud)")
    a = ap.parse_args()

    if a.acceptance:
        return mode_acceptance(a.force, a.sample)
    if a.pre:
        return mode_pre(a.pre.rstrip("/"), a.force, a.out)
    if a.pre_list:
        return mode_pre_list(a.pre_list, a.force)
    if a.escalate:
        return mode_escalate(a.escalate, a.force)
    if a.post:
        return mode_post(a.post, a.force, a.jobs)
    ap.print_help()
    return 1


if __name__ == "__main__":
    sys.exit(main())
