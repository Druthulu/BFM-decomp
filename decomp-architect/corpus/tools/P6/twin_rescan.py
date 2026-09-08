#!/usr/bin/env python3
"""tools/twin_rescan.py — after a bank, report what just became a REMAP instead of a draft. (P31 S69)

WHY (§397, measured at ~250k wasted tokens in one session). The twin oracle answers *"is there a
BANKED body like this?"*. An OPEN-OPEN cluster therefore reports **"no banked twin" for every member,
correctly** — none of them is banked. The instant you bank ONE, that answer is stale for all the
others, and nothing in the pipeline notices.

S69 paid for the lesson: a reach-6 cluster's exemplar cost 203k tokens to crack, then FOUR siblings
were drafted at ~60k each. They were exact clones — the agents' own diffs read *"label-stripped .s
diff vs the twin is EMPTY"* and *"an EXACT clone (asm diff = labels only)"*. `family_remap` + the
§378 chain banks those for ~0. One sibling had already burned **257k tokens plateauing at
permuter-class NEAR** before the remap closed it in seconds.

WHAT IT DOES. Runs the twin scan and DIFFS it against the previous snapshot, so the output is not
"here is the whole board" but **"here is what changed since the last bank"** — the only part anyone
acts on. Rows that gained a banked twin are printed with the ready-to-run remap command.

    tools/twin_rescan.py                 # rescan, diff vs the last snapshot, print what is now free
    tools/twin_rescan.py --snapshot-only # take a baseline without reporting (first run)

Run it AFTER EVERY GATE THAT BANKED. It is the cheap half of the loop: crack one exemplar, bank it,
rescan, remap everything that just lit up, and draft only what is left.
"""
import argparse
import json
import os
import subprocess
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SNAP = os.path.join(REPO, ".run/twin_rescan.snapshot.json")
VENV = os.path.join(REPO, ".venv/bin/python")


def scan(max_d):
    out = os.path.join(REPO, ".run/twin_rescan.latest.json")
    r = subprocess.run([VENV, "tools/seed_ref.py", "--near", "--max-d", str(max_d), "--json", out],
                       cwd=REPO, capture_output=True, text=True)
    if r.returncode or not os.path.exists(out):
        sys.exit("[twin_rescan] seed_ref --near failed: %s" % (r.stderr or r.stdout)[-300:])
    return {(x["binary"], x["fn"]): x for x in json.load(open(out))["rows"]}


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--max-d", type=int, default=5)
    ap.add_argument("--snapshot-only", action="store_true")
    a = ap.parse_args()

    cur = scan(a.max_d)
    prev = {}
    if os.path.exists(SNAP):
        prev = {(k.split("|")[0], k.split("|")[1]): v for k, v in json.load(open(SNAP)).items()}

    # R41: state the denominator, not just the exciting number.
    withtwin = {k: v for k, v in cur.items() if v.get("d") is not None}
    print("[twin_rescan] %d open stub(s) scanned; %d have a banked twin at d<=%d"
          % (len(cur), len(withtwin), a.max_d))

    if not a.snapshot_only and prev:
        gained = [k for k, v in withtwin.items() if prev.get(k, {}).get("d") is None]
        print("[twin_rescan] NEWLY FREE since the last snapshot: %d" % len(gained))
        for k in sorted(gained, key=lambda k: -(cur[k].get("nins") or 0)):
            v = cur[k]
            tw = v.get("twin") or "?"
            fb, fa = (tw.split(":") + ["?"])[:2]
            print("  %-14s %-16s d=%-3s %-4s ins  twin %s" % (k[0], k[1], v.get("d"), v.get("nins"), tw))
            print("     .venv/bin/python tools/family_remap.py --addr %s --from %s --to %s "
                  "--to-addr 0x%s --out <dir>/%s.c" % (fa, fb, k[0], k[1].split("_")[-1].lower(), k[1]))
        if not gained:
            print("  (nothing new — the last bank did not unlock a sibling)")
    elif not prev:
        print("[twin_rescan] no previous snapshot; this run is the baseline")

    json.dump({"%s|%s" % k: v for k, v in cur.items()}, open(SNAP, "w"))
    print("[twin_rescan] snapshot written to %s" % os.path.relpath(SNAP, REPO))
    return 0


if __name__ == "__main__":
    sys.exit(main())
