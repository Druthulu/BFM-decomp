#!/usr/bin/env python3
"""campaign_status.py — ONE status view covering EVERY lane, not just the loud one.

WHY (Drew, P31 S59): status checks kept reporting the overlay drafter and the gater — the lanes
whose logs scroll — while the main lane, the maintenance lane and the distill lane went unmentioned
for hours. A lane you do not report is a lane you do not notice failing: the main lane spent an
afternoon on an old config and bisected a whole batch to zero banks without that ever reaching a
status line. This prints all of them, each with ITS OWN metrics, from the artefacts rather than
from memory.

  tools/campaign_status.py            # everything
  tools/campaign_status.py --brief    # one block per lane, no history
"""
import argparse
import glob
import json
import os
import re
import subprocess
import sys
import time

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(REPO, "tools"))

LANES = ("drafter", "gater", "maintenance", "stallguard", "distill", "main")


def sh(cmd):
    return subprocess.run(["bash", "-c", cmd], capture_output=True, text=True, cwd=REPO).stdout.strip()


def alive(lane):
    """Anchored: `pgrep -f 'bash .run/x.sh'` matched THIS tool's own `bash -c "pgrep ..."` wrapper, so
    every lane read `ok` with zero processes alive (S60 shutdown; verified S61 with a clean ps)."""
    return bool(sh(f"pgrep -f '^bash \\.run/{lane}\\.sh' | head -1"))


def agents_by_wave():
    out = {}
    for p in sh("pgrep -f '^\\.venv/bin/python -u tools/api_agent' || true").split():
        try:
            cl = open(f"/proc/{p}/cmdline", "rb").read().decode(errors="replace").replace("\0", " ")
        except OSError:
            continue
        m = re.search(r"wave_([a-z0-9]+)", cl)
        w = m.group(1) if m else "?"
        env = ""
        try:
            env = open(f"/proc/{p}/environ", "rb").read().decode(errors="replace")
        except OSError:
            pass
        mt = re.search(r"MAXTOK=(\d+)", env)
        out.setdefault((w, mt.group(1) if mt else "?"), 0)
        out[(w, mt.group(1) if mt else "?")] += 1
    return out


def rate(window=300):
    now, req, f429 = time.time(), 0, 0
    try:
        for line in open(os.path.join(REPO, ".run/api_rate.jsonl"), errors="replace"):
            line = line.strip()
            if not line:
                continue
            try:
                r = json.loads(line)
            except Exception:
                continue
            if now - r.get("t", 0) > window:
                continue
            if r.get("ev") == "POST":
                req += 1
            elif "429" in str(r.get("ev")):
                f429 += 1
    except OSError:
        return None
    return req, f429, req / (window / 60.0)


def wave_rows(pattern, n):
    """(tag, cards, drafts, truncated) for the most recent waves matching a card-file glob."""
    rows = []
    for cp in sorted(glob.glob(os.path.join(REPO, pattern)), key=os.path.getmtime)[-n:]:
        tag = os.path.basename(cp).split("_")[1]
        try:
            c = json.load(open(cp))
            c = c if isinstance(c, list) else c.get("cards", [])
        except Exception:
            c = []
        d = len(glob.glob(os.path.join(REPO, f".run/wave_{tag}/shard*/*.c")))
        tr = 0
        for lp in glob.glob(os.path.join(REPO, f".run/wave_{tag}/shard*.log")):
            try:
                tr += sum(1 for l in open(lp, errors="replace") if "finish=length" in l)
            except OSError:
                pass
        rows.append((tag, len(c), d, tr))
    return rows


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--brief", action="store_true")
    a = ap.parse_args()
    os.chdir(REPO)
    print(f"=== CAMPAIGN STATUS {time.strftime('%H:%M:%S')} ===")

    # ---- lanes ---------------------------------------------------------------------------------
    print("lanes : " + "  ".join(f"{l}={'ok' if alive(l) else 'DEAD'}" for l in LANES))
    ab = agents_by_wave()
    tot = sum(ab.values())
    detail = " · ".join(f"{w}:{n}@{mt}tok" for (w, mt), n in sorted(ab.items(), key=lambda x: -x[1]))
    print(f"agents: {tot}   {detail}")
    r = rate()
    if r:
        print(f"rate  : {r[2]:.0f} req/min · {r[1]} 429 in 5 min")

    # ---- overlay drafting lane -----------------------------------------------------------------
    print("\n-- OVERLAY LANE (drafter -> gater) --")
    for tag, cards, drafts, tr in wave_rows(".run/wave_??_cards.json", 4 if not a.brief else 2):
        print(f"   wave {tag}: {cards:4} cards · {drafts:4} drafts ({100*drafts/max(cards,1):3.0f}%) · {tr:4} truncated turns")
    for line in sh("grep -E 'GATE [a-z]+: banked' .run/gater.log 2>/dev/null | tail -3").splitlines():
        print("   " + line.strip()[:110])
    print(f"   ready queue: [{sh('ls .run/ready/ 2>/dev/null | tr \"\\n\" \" \"')}]")

    # ---- main lane -------------------------------------------------------------------------------
    print("\n-- MAIN LANE (its own gate cadence) --")
    for tag, cards, drafts, tr in wave_rows(".run/wave_m??_cards.json", 3 if not a.brief else 1):
        print(f"   wave {tag}: {cards:4} cards · {drafts:4} drafts ({100*drafts/max(cards,1):3.0f}%) · {tr:4} truncated turns")
    for line in sh("grep -E 'banked|nothing banked|BISECT' .run/main_lane.log 2>/dev/null | tail -4").splitlines():
        print("   " + line.strip()[:110])
    try:
        import corpus
        # HONEST denominator (P31 S62 T5pre; frontier-s61 §1.3): corpus.stubs('main') counts the 959
        # LINKED PsyQ objects + blobs as open. Derive the open set the way progress.py does.
        try:
            import progress as _P
            _P.set_binary('main')
            _real, _empty, _nm, _stubs, _blobs, _linked = _P.classify()
            print(f"   open main fns: {len(_stubs)} stubs + {len(_nm)} NON_MATCHING  (LINKED {len(_linked)} + blobs {len(_blobs)} excluded; raw INCLUDE_ASM lines {len(corpus.stubs('main'))})")
        except Exception as _e:
            print(f"   open main stubs (raw INCLUDE_ASM lines, incl. LINKED): {len(corpus.stubs('main'))}  [honest count unavailable: {_e!r}]")
    except Exception as e:
        print(f"   (main stub count unavailable: {type(e).__name__})")

    # ---- the free lanes ---------------------------------------------------------------------------
    print("\n-- MAINTENANCE / DISTILL (zero model tokens) --")
    for line in sh("tail -3 .run/maintenance.log 2>/dev/null").splitlines():
        print("   maint: " + line.strip()[:104])
    pend = sh("ls .run/distill_ready/ 2>/dev/null | tr '\\n' ' '")
    try:
        mined = len(json.load(open(".run/distill_state.json")).get("mined", {}))
    except Exception:
        mined = "?"
    print(f"   distill: {mined} wave(s) mined · ready batches: [{pend}]")

    # ---- totals ----------------------------------------------------------------------------------
    # BANKED TODAY IS DERIVED FROM THE INCLUDE_ASM INVARIANT, NOT FROM COMMIT SUBJECTS (S61, R33).
    # The subject regex summed "— N banked" and missed every bank that rode in a chore/maint commit:
    # the S60 A-prop pass put 357 banks in 274932d20 ("chore: ...") and the regex reported 2,185
    # for a day whose stub count fell by 2,644 net (frontier-analysis-s60 §1). Stubs are counted at
    # the last commit before midnight, at HEAD, and in the working tree (uncommitted banks — R42
    # says commit them, the number says whether anyone did). Carves re-add stubs, so this is NET.
    def _stubs(rev):
        if rev == "tree":
            return int(sh("grep -rc 'INCLUDE_ASM(' src/ --include='*.c' | awk -F: '{s+=$NF} END {print s+0}'") or 0)
        return int(sh(f"git grep -c 'INCLUDE_ASM(' {rev} -- src/ | awk -F: '{{s+=$NF}} END {{print s+0}}'") or 0)
    base = sh("git rev-list -1 --before='00:00' HEAD")
    s_base, s_head, s_tree = _stubs(base), _stubs("HEAD"), _stubs("tree")
    subj = sh("git log --since='00:00' --format='%s' | grep -oE '[—-] [0-9]{1,4} banked' "
              "| awk '{s+=$2} END {print s+0}'")
    print(f"\ntoday : {s_base - s_head} net stubs removed since {base[:9]} ({s_base} -> {s_head} committed"
          f"{'' if s_tree == s_head else f', {s_head - s_tree:+d} more uncommitted in the tree'}) · "
          f"{sh('git log --since=00:00 --oneline | wc -l')} commits · subject-regex sum {subj} (undercounts)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
