#!/usr/bin/env python3
"""gater_lane.py — the CONTINUOUS GATER: drain a drafting wave's finished drafts into
`parallel_gate`, grouped by binary, while the drafting lane keeps streaming. (P31 S68)

WHY THIS EXISTS (measured S67, and the reason it is finally worth building):
gating used to be the constraint, so the shape was "draft the whole wave, then gate it". Three S67
fixes removed that: `-j` on every per-binary build (7.18 s -> 1.18 s, 6.1x), `parallel_gate`'s
worktree isolation as the DEFAULT (13 fns / 13 binaries in 139 s at 12 workers), and the jtbl
unlock (`isolate_asm` + splicing the carve state, 19 fns / 14 binaries in 166 s against 58 minutes
for ONE binary serially). Consumption is now ~5 fns/min against a production rate of roughly one
draft every 30-90 s — 3-5x headroom — so banking can run continuously alongside drafting.

WHY NOT GATE STRICTLY PER COMPLETION — three measured reasons, all from S67:
  1. SAME-BINARY DRAFTS MUST SHARE A BUILD. One S67 batch held `ov_SC05_010` x3 and `ov_SC03_105`
     x2; gating each alone triples that binary's build cost for nothing. So this tool ACCUMULATES:
     it fires when `--min-drafts` have landed (or when `--drain` says take whatever is there).
  2. PROPAGATION IS CROSS-BINARY and still a build-per-candidate loop. It stays BATCHED and is NOT
     run from here (`parallel_gate` workers gate with --no-propagate by design).
  3. `twin_sweep` AND HARVEST NEED AGGREGATE. `twin_sweep` is a fleet-wide scan; harvest is worse —
     cookbook §330 existed only because four independent instances appeared in ONE wave. Both stay
     periodic, driven by the operator, not by this loop.

WHAT IT ASSERTS
  * a draft is gated at most once — the ledger `.run/gate_lane/ledger.json` is keyed
    "binary:fn" (R48: NEVER key by bare function name; the same `func_8017BEBC` is a different
    function in different overlays and a name-keyed ledger silently drops the second one);
  * a draft whose function is no longer an OPEN stub is dropped with a reason, not gated (it banked
    by another route — propagation, a twin sweep, a sibling's gate);
  * a draft whose (binary, fn) cannot be resolved from the wave's own `targets.json` is REFUSED
    LOUDLY rather than guessed at (R43) — `wave_args.py` already asserted those pairs, so an
    unresolvable draft means the wave dir and the drafts disagree and a guess would gate the wrong TU;
  * every count printed carries its denominator (R41).

`--r22` is passed to `parallel_gate` by DEFAULT here. It re-verifies the whole fleet from
`make clean` after the merge and ABORTS instead of committing a red binary — the guard that would
have caught S67's "13 of 213 red, every one a jtbl binary" at once. It costs ~2.5 minutes; a red
binary costs a revert and a re-run. Pass --no-r22 only when you are gating into a tree you have
another reason to trust.

  tools/gater_lane.py --waves .run/S68o1,.run/S68m1 --min-drafts 3 [--drain] [--workers 12] [--dry]
"""
import argparse
import json
import os
import shutil
import subprocess
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(REPO, "tools"))
import corpus  # noqa: E402

def sh(cmd, cwd=REPO):
    return subprocess.run(cmd, capture_output=True, text=True, cwd=cwd)


LEDGER = os.path.join(REPO, ".run/gate_lane/ledger.json")
VERDICTS = os.path.join(REPO, ".run/gate_lane/verdicts.jsonl")
STAGE = os.path.join(REPO, ".run/gate_lane")


def completed():
    """{(binary, fn)} whose drafting workflow has RETURNED A VERDICT.

    A draft file appears in <wave>/<arm>/<fn>.c long before its agent is finished — agents iterate
    in place, and the wave brief tells them to write the file, not to write it last. Gating one
    mid-flight spends a build on an unfinished draft, records an honest-looking rejection, and then
    LEDGERS it, so the finished draft is skipped as "already-gated" when it lands. Measured S68 on
    ov_SC01_000:func_8017E594 — gated at 0 banked while its workflow was still running.

    The orchestrator appends one JSON object per returned verdict; nothing else is a completion
    signal (a quiet file mtime is not one — an agent that thinks for four minutes between edits looks
    identical to a finished one).
    """
    out = set()
    try:
        with open(VERDICTS) as fh:
            for ln in fh:
                ln = ln.strip()
                if not ln:
                    continue
                try:
                    r = json.loads(ln)
                except ValueError:
                    continue
                if r.get("binary") and r.get("fn"):
                    # KEYED BY ARM. A (binary, fn) can be drafted by several tiers, and an
                    # ESCALATION is by definition launched while the lower tier's verdict already
                    # exists. Keying by (binary, fn) alone lets the fable draft be staged on the
                    # strength of the OPUS verdict while the fable agent is still iterating —
                    # exactly the in-flight bug this function exists to prevent, one level up.
                    # An arm-less row (a hand-written backfill) counts for every arm.
                    out.add((r["binary"], r["fn"], r.get("arm")))
    except OSError:
        pass
    return out


def has_verdict(done, binary, fn, arm):
    return (binary, fn, arm) in done or (binary, fn, None) in done


def load_ledger():
    try:
        with open(LEDGER) as fh:
            return json.load(fh)
    except (OSError, ValueError):
        return {}


def save_ledger(d):
    os.makedirs(os.path.dirname(LEDGER), exist_ok=True)
    with open(LEDGER, "w") as fh:
        json.dump(d, fh, indent=1, sort_keys=True)


# Escalation supersedes: a function drafted by several arms is staged from the HIGHEST tier that
# produced a draft. Without this the arm dirs are walked alphabetically ("fable" < "opus" <
# "sonnet") and the staging copy silently OVERWRITES, so a sonnet NEAR would replace the fable MATCH
# that was escalated to rescue it — the escalation's whole product, lost to a directory listing
# order. Measured live in S68 on main/func_800241C0 (sonnet closeness 19, fable MATCH).
ARM_RANK = {"fable": 40, "opus": 30, "sonnet": 20, "v3": 15, "haiku": 10}


def wave_targets(wave):
    """{fn: binary} for one wave, from the file wave_args.py already asserted."""
    with open(os.path.join(REPO, wave, "targets.json")) as fh:
        return {t["name"]: t["binary"] for t in json.load(fh)}


def open_stub(binary, fn, cache={}):
    if binary not in cache:
        try:
            cache[binary] = {s.symbol for s in corpus.stubs(binary).values()}
        except Exception as e:                       # a refusing oracle is loud, never a silent skip
            print("  [oracle refused] %s: %r" % (binary, e), file=sys.stderr)
            cache[binary] = None
    known = cache[binary]
    return None if known is None else (fn in known)


def collect(waves, require_verdict=True):
    """[(binary, fn, path)] for every draft file not yet gated. Refuses unresolvable drafts."""
    led = load_ledger()
    out, skipped = [], {"already-gated": [], "already-banked": [], "UNRESOLVED": [], "oracle": [],
                        "IN-FLIGHT (no verdict yet)": []}
    best, seen_arms = {}, {}
    done = completed()
    for wave in waves:
        tgts = wave_targets(wave)
        wdir = os.path.join(REPO, wave)
        for arm in sorted(os.listdir(wdir)):
            adir = os.path.join(wdir, arm)
            if not os.path.isdir(adir) or arm in ("packs", "scratch"):
                continue
            for name in sorted(os.listdir(adir)):
                if not name.endswith(".c"):
                    continue
                fn = name[:-2]
                binary = tgts.get(fn)
                if binary is None:                    # R43: refuse, never guess the TU
                    skipped["UNRESOLVED"].append("%s/%s/%s" % (wave, arm, name))
                    continue
                # THE LEDGER KEY CARRIES THE ARM. Gating the opus draft of a function that is
                # currently being escalated must NOT ledger away the fable draft that follows it —
                # the escalation exists precisely because the lower tier did not bank. The
                # already-banked check below is what stops a genuine duplicate: once a function
                # banks, its stub is gone and every arm's draft is skipped as banked-elsewhere.
                key = "%s:%s:%s" % (binary, fn, arm)
                if key in led:
                    skipped["already-gated"].append(key)
                    continue
                st = open_stub(binary, fn)
                if st is None:
                    skipped["oracle"].append(key)
                    continue
                if not st:
                    skipped["already-banked"].append(key)
                    led[key] = "banked-elsewhere"
                    continue
                if require_verdict and not has_verdict(done, binary, fn, arm):
                    skipped["IN-FLIGHT (no verdict yet)"].append("%s[%s]" % (key, arm))
                    continue
                cand = (ARM_RANK.get(arm, 0), arm, binary, fn, os.path.join(adir, name))
                cur = best.get(key)
                if cur is None or cand[0] > cur[0]:
                    best[key] = cand
                seen_arms.setdefault(key, []).append(arm)
    for key, (_, arm, binary, fn, path) in sorted(best.items()):
        arms = seen_arms.get(key, [])
        if len(arms) > 1:                       # never resolve a collision silently (R43)
            print("[gater] %s drafted by %s — staging the %s draft (highest tier wins)"
                  % (key, "/".join(sorted(arms)), arm))
        out.append((binary, fn, path))
    save_ledger(led)
    return out, skipped


def collect_extra(pairs, skipped):
    """[(binary, fn, path)] for drafts that do not come from a wave (twin remaps, recovery output).

    The binary must be stated, never inferred: a draft file is named `func_XXXXXXXX.c` and that name
    is ambiguous across the fleet (R48), so there is nothing in the path to infer it from safely.
    """
    led = load_ledger()
    out = []
    for spec in pairs:
        if ":" not in spec:
            sys.exit("[gater] --extra wants BINARY:PATH, got %r" % spec)
        binary, path = spec.split(":", 1)
        if not os.path.exists(path):
            sys.exit("[gater] --extra path does not exist: %s" % path)
        fn = os.path.basename(path)[:-2] if path.endswith(".c") else os.path.basename(path)
        key = "%s:%s:%s" % (binary, fn, os.path.basename(os.path.dirname(path)))
        if key in led:
            skipped["already-gated"].append(key); continue
        st = open_stub(binary, fn)
        if st is None:
            skipped["oracle"].append(key); continue
        if not st:
            skipped["already-banked"].append(key); led[key] = "banked-elsewhere"; continue
        out.append((binary, fn, path))
    save_ledger(led)
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--waves", default="", help="comma-separated wave dirs (repo-relative)")
    ap.add_argument("--extra", action="append", default=[], metavar="BINARY:PATH",
                    help="a draft from OUTSIDE a wave: 'ov_SC06_032:.run/S68_twin/drafts/ov_SC06_032/func_X.c'. "
                         "Repeatable. The binary is given EXPLICITLY because there is no targets.json to "
                         "assert it against, and a guessed binary gates the wrong TU (R43/R48).")
    ap.add_argument("--min-drafts", type=int, default=3,
                    help="do nothing unless at least this many ungated drafts exist (default 3)")
    ap.add_argument("--drain", action="store_true", help="gate whatever is there, ignoring --min-drafts")
    ap.add_argument("--skip-binary", default="",
                    help="comma-separated binaries to leave alone this pass. USE THIS when another "
                         "lane may be writing that binary's src/ — an investigation agent permitted "
                         "to splice-and-restore, a carve, a recovery run. A gate that races such a "
                         "lane produces a FALSE verdict on a draft that is fine (measured S68: a "
                         "clean-fleet R22 raced an authorised src/800.c splice and reported "
                         "'212 passed, 1 failed' on a tree that rebuilt byte-identical minutes "
                         "later). Being clean RIGHT NOW is not the test; nothing being able to "
                         "dirty it during the run is.")
    ap.add_argument("--any-draft", action="store_true",
                    help="gate drafts that have no recorded verdict yet (see completed(); this gates "
                         "work an agent may still be iterating on and will ledger the result)")
    ap.add_argument("--workers", type=int, default=12)
    ap.add_argument("--no-r22", action="store_true", help="skip the post-merge clean-fleet verify (see docstring)")
    ap.add_argument("--dry", action="store_true", help="print the plan, stage nothing, gate nothing")
    a = ap.parse_args()

    waves = [w.strip() for w in a.waves.split(",") if w.strip()]
    if not waves and not a.extra:
        sys.exit("[gater] nothing to do — give --waves and/or --extra")
    ready, skipped = collect(waves, require_verdict=not a.any_draft)
    skipb = {x.strip() for x in a.skip_binary.split(",") if x.strip()}
    if skipb:
        held = [r for r in ready if r[0] in skipb]
        ready = [r for r in ready if r[0] not in skipb]
        print("[gater] HOLDING %d draft(s) for %s — another lane may be writing them: %s"
              % (len(held), ",".join(sorted(skipb)), " ".join("%s:%s" % (b, f) for b, f, _ in held[:8])))
    ready.extend(collect_extra(a.extra, skipped))
    for why, items in skipped.items():
        if items:
            print("[gater] skipped %d (%s): %s" % (len(items), why, " ".join(items[:6])))
    if skipped["UNRESOLVED"]:
        sys.exit("[gater] ABORT — %d draft(s) do not appear in their wave's targets.json; the wave "
                 "dir and the drafts disagree and guessing the TU would gate the wrong file (R43)"
                 % len(skipped["UNRESOLVED"]))

    total_seen = len(ready) + sum(len(v) for v in skipped.values())
    print("[gater] %d ungated draft(s) of %d seen across %d wave(s)" % (len(ready), total_seen, len(waves)))
    if not ready:
        return 0
    if len(ready) < a.min_drafts and not a.drain:
        print("[gater] holding — %d < --min-drafts %d (same-binary drafts must share a build)"
              % (len(ready), a.min_drafts))
        return 0

    bybin = {}
    for binary, fn, path in ready:
        bybin.setdefault(binary, []).append((fn, path))
    print("[gater] %d fn(s) across %d binaries: %s"
          % (len(ready), len(bybin), " ".join("%s×%d" % (b, len(v)) for b, v in sorted(bybin.items()))))
    if a.dry:
        return 0

    # MAIN IS GATED IN THE MAIN TREE, NOT IN A WORKTREE.
    # parallel_gate's worktree staging copies the three generated files the Makefile NAMES
    # (<b>_LD_SCRIPT / <b>_UNDEF_SYMS / <b>_UNDEF_FUNCS), which is enough for every overlay. main's
    # link additionally runs the psyq_integrate chain, which needs inputs that staging does not
    # carry, so a worktree gate of main returns 0 banked with no error — measured S68, repeatedly,
    # while the SAME drafts banked byte-identical through harvest_verify in the main tree.
    # main is ONE binary, so there is no parallelism to lose by gating it here (R43: handle the
    # input correctly rather than processing it wrongly).
    main_items = bybin.pop("main", None)
    if main_items:
        d = os.path.join(STAGE, "main_intree")
        shutil.rmtree(d, ignore_errors=True)
        os.makedirs(d)
        for fn, path in main_items:
            shutil.copyfile(path, os.path.join(d, fn + ".c"))
        cmd = [os.path.join(REPO, ".venv/bin/python"), "tools/harvest_verify.py", "--binary", "main",
               "--drafts", d, "--chunk", "1",
               "--verified-out", ".run/gate_lane/main.verified",
               "--failed-out", ".run/gate_lane/main.failed"]
        print("[gater] main: %d draft(s) IN-TREE via harvest_verify (not a worktree): %s"
              % (len(main_items), " ".join(fn for fn, _ in main_items)), flush=True)
        rc_main = subprocess.run(cmd, cwd=REPO).returncode
        print("[gater] main harvest_verify rc=%d" % rc_main, flush=True)
        led = load_ledger()
        for fn, path in main_items:
            led["main:%s:%s" % (fn, os.path.basename(os.path.dirname(path)))] = "gated-intree:rc%d" % rc_main
        save_ledger(led)
        # COMMIT WHAT BANKED. The worktree path commits via parallel_gate; this one runs
        # harvest_verify directly in the main tree, so without this a banked function sits
        # UNCOMMITTED and the next tool to see a dirty src/ either refuses (parallel_gate does) or
        # sweeps it into an unrelated commit. R42: commit banked work the moment it exists.
        dirty = sh(["git", "status", "--porcelain", "--", "src"]).stdout.strip()
        if dirty:
            # DERIVE the banked list from harvest_verify's OWN verified-out file, not from
            # corpus.stubs — corpus memoizes, so a fresh query right after the bank returns the
            # STALE pre-bank set and the message reads "0 fn(s)" for a commit that contains work.
            # Measured on the func_8003A0E4 bank (R33: derive from the invariant the tool wrote).
            try:
                with open(os.path.join(REPO, ".run/gate_lane/main.verified")) as fh:
                    verified = {w for w in fh.read().split() if w.startswith("func_")}
            except OSError:
                verified = set()
            banked_now = sorted(verified & {fn for fn, _ in main_items})
            sh(["git", "add", "--", "src"])
            msg = ("feat(decomp): main in-tree gate — %d fn(s)\n\n%s"
                   % (len(banked_now), "\n".join("  main  %s" % f for f in banked_now))[:2000])
            sh(["git", "-c", "user.name=Drew T", "-c", "user.email=50529377+Druthulu@users.noreply.github.com",
                "commit", "-q", "-m", msg])
            print("[gater] main: committed %s" % sh(["git", "rev-parse", "HEAD"]).stdout.strip()[:9],
                  flush=True)
        if not bybin:
            return rc_main

    stamp = "%08x" % (abs(hash(tuple(sorted(k for k in bybin)))) & 0xFFFFFFFF)
    root = os.path.join(STAGE, "batch_%s" % stamp)
    shutil.rmtree(root, ignore_errors=True)
    plan = []
    for binary, items in sorted(bybin.items()):
        d = os.path.join(root, binary)
        os.makedirs(d)
        for fn, path in items:
            shutil.copyfile(path, os.path.join(d, fn + ".c"))
        plan.append({"binary": binary, "drafts": d})
    planp = os.path.join(root, "plan.json")
    with open(planp, "w") as fh:
        json.dump(plan, fh, indent=1)

    cmd = [sys.executable, "tools/parallel_gate.py", "--plan", planp,
           "--workers", str(min(a.workers, len(plan))), "--commit"]
    if not a.no_r22:
        cmd.append("--r22")
    print("[gater] %s" % " ".join(cmd), flush=True)
    rc = subprocess.run(cmd, cwd=REPO).returncode
    print("[gater] parallel_gate rc=%d" % rc, flush=True)

    # Ledger the ATTEMPT, not the outcome: a refused draft must not be re-gated unchanged on the
    # next tick (that is the 0/23 stored-re-gate law from T1 — a fresh verdict needs a fresh fix).
    led = load_ledger()
    for binary, fn, path in ready:
        arm = os.path.basename(os.path.dirname(path))
        led["%s:%s:%s" % (binary, fn, arm)] = "gated:rc%d" % rc
    save_ledger(led)
    return rc


if __name__ == "__main__":
    sys.exit(main())
