#!/usr/bin/env python3
"""recover_rejects.py — turn pre-gate rejects back into bankable drafts, for zero model tokens.

WHY (P31 S59). Two paths exist for a draft that does not bank, and until now only one was recorded.
A draft that reaches the GATE and fails gets a backlog row with its closeness, class and best body.
A draft the **reloc pre-filter** drops never reaches the gate, so it was recorded nowhere and simply
sat in its shard directory: measured over eight waves, **569 of 1,261 drafts — 45%**.

They are not all garbage. Of the `MISMATCH?` rejects, **13% carry `shape: MATCH`** — the instruction
stream already matches and only the SYMBOL NAMES are wrong. That is precisely the §171 stale-seed
class `aprop_symfix` rebases deterministically, and it banked 4 of 4 the last time it was pointed at
that population. Roughly six recoverable drafts per wave were being thrown away for want of an index.

WHAT THIS DOES
    read .run/reloc_rejects.jsonl  (written by ox_campaign.reloc_filter)
      -> keep shape==MATCH rows whose function is STILL AN OPEN STUB
      -> aprop_symfix --fix   (rebase the stale symbols onto the target's own)
      -> stage the rebased bodies into .run/sweep_maint/<binary>/<fn>.c
    The maintenance lane then gates and commits them on its existing free pass. Nothing here
    substitutes, gates or commits: staging is the whole job, so a bad recovery can only waste a
    build, never a bank.

Recovered functions are remembered in .run/recover_rejects_seen.json so a draft that cannot be
rebased is not retried every 45 minutes forever.

  tools/recover_rejects.py [--limit 60] [--dry-run]
"""
import argparse
import json
import os
import shutil
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import corpus                                                            # noqa: E402

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
REJECTS = ".run/reloc_rejects.jsonl"
SEEN = ".run/recover_rejects_seen.json"
STAGE = ".run/sweep_maint"
SLATE = ".run/recover_rejects_slate.json"


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--limit", type=int, default=60)
    ap.add_argument("--dry-run", action="store_true")
    a = ap.parse_args()
    os.chdir(REPO)

    if not os.path.exists(REJECTS):
        print("recover_rejects: no rejects index yet — nothing to do")
        return 0
    try:
        seen = set(json.load(open(SEEN)))
    except Exception:
        seen = set()

    rows, dup = [], set()
    for line in open(REJECTS, errors="replace"):
        line = line.strip()
        if not line:
            continue
        try:
            r = json.loads(line)
        except Exception:
            continue                                   # a concurrent append can interleave
        # THE RECOVERABLE CLASS, and only it: the body already matches instruction-for-instruction
        # (shape MATCH) and the pre-filter objected to the SYMBOLS. Anything else is a wrong body,
        # which is a re-draft, not a rebase — and re-drafting is the fleet's job, not this lane's.
        if r.get("shape") != "MATCH" or r.get("status") == "AGREE":
            continue
        fn = r.get("fn")
        if not fn or fn in seen or fn in dup or not r.get("draft"):
            continue
        if not os.path.exists(r["draft"]):
            continue
        dup.add(fn)
        rows.append(r)

    if not rows:
        print(f"recover_rejects: 0 recoverable rows (index has "
              f"{sum(1 for _ in open(REJECTS))} entries, {len(seen)} already tried)")
        return 0

    # STILL OPEN? A function banked since the reject was written needs no recovery, and staging it
    # would re-stage a body over source that already byte-matches (R43/§ the NOT-A-STUB lesson).
    open_by_bin = {}
    keep = []
    for r in rows:
        b = r.get("binary")
        if b not in open_by_bin:
            try:
                open_by_bin[b] = {s.symbol for s in corpus.stubs(b).values()}
            except Exception:
                open_by_bin[b] = set()
        if r["fn"] in open_by_bin[b]:
            keep.append(r)
    print(f"recover_rejects: {len(rows)} shape-MATCH reject(s), {len(keep)} still open stubs")
    keep = keep[:a.limit]
    if not keep:
        return 0

    json.dump([{"fn": r["fn"], "binary": r["binary"], "draft": r["draft"]} for r in keep],
              open(SLATE, "w"), indent=1)
    if a.dry_run:
        print(f"recover_rejects: [dry-run] slate of {len(keep)} written to {SLATE}")
        return 0

    p = subprocess.run([".venv/bin/python", "tools/aprop_symfix.py", SLATE, "--fix"],
                       capture_output=True, text=True, cwd=REPO)
    out = (p.stdout or "") + (p.stderr or "")
    print(out.strip()[-600:])

    fixed = []
    try:
        fixed = json.load(open(".run/aprop_symfix_slate.json"))
    except Exception:
        pass
    staged = 0
    for r in fixed:
        b, fn, d = r.get("binary"), r.get("fn"), r.get("draft")
        if not (b and fn and d and os.path.exists(d)):
            continue
        os.makedirs(f"{STAGE}/{b}", exist_ok=True)
        shutil.copy(d, f"{STAGE}/{b}/{fn}.c")
        staged += 1

    seen |= {r["fn"] for r in keep}                     # tried once is tried; do not loop on it
    json.dump(sorted(seen), open(SEEN, "w"), indent=1)
    print(f"recover_rejects: rebased {len(fixed)}, staged {staged} into {STAGE}/ "
          f"for the maintenance lane's free gate")
    return 0


if __name__ == "__main__":
    sys.exit(main())
