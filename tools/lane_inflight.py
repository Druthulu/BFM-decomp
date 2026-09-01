#!/usr/bin/env python3
"""lane_inflight.py — the AUTHORITATIVE record of which drafting agents are live. (P31 S68)

WHY A LEDGER AND NOT A HEURISTIC. `make clean` deletes `asm/` and `build/`, and every drafting agent
READS `asm/<binary>/nonmatchings/**/<fn>.s`. Agents never WRITE `src/`, so a dirty-tree check cannot
see them — they DEPEND on state the operation destroys. FOUR times in S68 an R22 pulled `asm/` out
from under a live draft; one agent survived only by finding a stale snapshot and still returned
MATCH, which is luck rather than safety.

The first guard I wrote used the mtime of the agents' scratch directories as a liveness proxy. It
failed twice over, in both possible directions:
  * `.run/*wave*` in its `find` expanded to so many entries that the shell refused the command
    ("Argument list too long") — the guard then found nothing and PASSED, and I ran `make clean` on
    a live lane;
  * even with the glob fixed, an agent that THINKS for longer than the window looks identical to a
    finished one — the exact flaw I had already written down for the verdicts file and then rebuilt
    here anyway.

So liveness is RECORDED, not inferred: the orchestrator adds a target when it launches the workflow
and removes it when the verdict returns. Both are actions it already takes, so the ledger cannot
drift without the orchestrator skipping a step it performs anyway.

    tools/lane_inflight.py add ov_SC05_017 func_80189240
    tools/lane_inflight.py done ov_SC05_017 func_80189240
    tools/lane_inflight.py list          # exit 1 if ANY are live — this is the guard
"""
import json
import os
import sys
import time

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PATH = os.path.join(REPO, ".run/lane_inflight.json")


def load():
    try:
        with open(PATH) as fh:
            return json.load(fh)
    except (OSError, ValueError):
        return {}


def save(d):
    os.makedirs(os.path.dirname(PATH), exist_ok=True)
    with open(PATH, "w") as fh:
        json.dump(d, fh, indent=1, sort_keys=True)


def main():
    if len(sys.argv) < 2:
        sys.exit(__doc__)
    cmd = sys.argv[1]
    d = load()
    if cmd == "add":
        d["%s:%s" % (sys.argv[2], sys.argv[3])] = time.strftime("%Y-%m-%dT%H:%M:%S")
        save(d)
        print("in-flight: %d" % len(d))
    elif cmd == "done":
        d.pop("%s:%s" % (sys.argv[2], sys.argv[3]), None)
        save(d)
        print("in-flight: %d" % len(d))
    elif cmd == "clear":
        save({})
        print("in-flight: 0")
    elif cmd == "list":
        for k, v in sorted(d.items()):
            print("  %s  (since %s)" % (k, v))
        print("in-flight: %d" % len(d))
        return 1 if d else 0
    else:
        sys.exit("unknown command %r" % cmd)
    return 0


if __name__ == "__main__":
    sys.exit(main())
