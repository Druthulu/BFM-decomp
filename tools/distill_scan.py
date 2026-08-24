#!/usr/bin/env python3
"""distill_scan.py — one pass of the distill lane: which harvested waves still need mining?

STATE IS {tag: novel-count AT THE TIME IT WAS MINED}, never a bare done-list. A wave that is
RE-GATED rewrites its candidate file with new rows under the SAME tag, so "have I seen this tag"
answers the wrong question: wave `at` was re-gated hours after its first harvest and an mtime-keyed
seed mis-classified it, and a hand-edited done-list nearly buried `ax`+`bm` — 82 candidates that had
been gated minutes earlier — because "queued for review" was folded into "reviewed". Compare COUNTS,
and a tag re-opens the moment its file grows.

Writes a READY marker when the pending rows are worth a reviewer's turn. Writes nothing else.

The reviewer is an **Opus or Sonnet** subagent, never Fable (Drew, 2026-08-24): distilling is
judgement over an existing corpus, not a new wall class.

  distill_scan.py <state.json> <ready_dir> <min_novel> <min_waves>
"""
import glob
import json
import os
import re
import sys
import time

NOVEL = re.compile(r"\*\*(\d+) novel-idiom candidates\*\*")


def main():
    state_p, ready_dir, min_novel, min_waves = sys.argv[1], sys.argv[2], int(sys.argv[3]), int(sys.argv[4])
    try:
        st = json.load(open(state_p))
    except Exception:
        st = {"mined": {}}
    mined = st.setdefault("mined", {})

    pend = []
    for p in sorted(glob.glob(".run/idiom_candidates.*.md")):
        tag = os.path.basename(p).split(".")[1]
        if tag == "ALL":
            continue
        m = NOVEL.search(open(p, errors="replace").read(4000))
        n = int(m.group(1)) if m else 0
        if n > mined.get(tag, -1):
            if n:
                pend.append((tag, n, p))
            else:
                mined[tag] = 0                     # nothing to mine; close it out at zero

    tot = sum(n for _t, n, _p in pend)
    if pend and (tot >= min_novel or len(pend) >= min_waves):
        batch = "".join(t for t, _n, _p in pend)[:24]
        out = os.path.join(ready_dir, batch + ".json")
        json.dump({"waves": [t for t, _n, _p in pend],
                   "novel": tot,
                   "counts": {t: n for t, n, _p in pend},
                   "files": [p for _t, _n, p in pend],
                   "t": time.time()}, open(out, "w"), indent=1)
        print("  BATCH READY: %d wave(s) / %d novel candidates -> %s" % (len(pend), tot, out))
    elif pend:
        print("  accumulating: %d wave(s) / %d novel candidates (need %d or %d waves)"
              % (len(pend), tot, min_novel, min_waves))
    json.dump(st, open(state_p, "w"), indent=1)


if __name__ == "__main__":
    main()
