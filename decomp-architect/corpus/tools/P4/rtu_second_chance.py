#!/usr/bin/env python3
"""rtu_second_chance.py — re-judge standalone COMPILE-FAIL drafts against their REAL TU (P31 S59).

WHY. The A-prop lane's pre-gate filter (reloc_identity) compiles each draft STANDALONE via
match_one, and drops every COMPILE-FAIL before the gate. But a mechanically-remapped draft is
written to land in a specific TU, and that TU provides context the standalone compile does not:
typedefs (`parse error before 'Blk8'`), struct definitions (`dereferencing pointer to incomplete
type`), and canonical decls. Measured on the 21:04 pass: 43 of 182 drafts (24%) were dropped this
way, unjudged — and the equivalent §173 recovery earlier this phase took such a population from
0/14 to 9/14. A standalone verdict is the WRONG ORACLE for a TU-destined draft (R33): the right
local oracle is rtu_match, which compiles the whole split TU with the candidate spliced in and
INCLUDE_ASM neutralized — no build tree, no locks, parallel-safe.

    reloc_out.json (COMPILE-FAIL rows)  ->  rtu_match per draft (parallel)  ->
        MATCH        -> stage into <stage>/<binary>/<fn>.c  (the byte-gate still arbitrates, G3/P9)
        CC1/DIFF/... -> named in the summary (R32: every drop counted, nothing silent)

Usage:
  tools/rtu_second_chance.py --reloc .run/s59_aprop2/reloc_out.json --slate .run/s59_aprop2/slate.json \
      --stage .run/s59_aprop2/sweep [-j 8] [--statuses COMPILE-FAIL,UNRESOLVED]
"""
import argparse
import collections
import json
import os
import re
import shutil
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import corpus                                                            # noqa: E402

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PY = ".venv/bin/python"


def _one(row, workroot):
    fn, b, draft = row["fn"], row["binary"], row["draft"]
    try:
        st = next((s for s in corpus.stubs(b).values() if s.symbol == fn), None)
    except Exception as e:
        return dict(row, verdict="NO-CORPUS", note=repr(e)[:120])
    if st is None:
        return dict(row, verdict="NOT-A-STUB", note="no open INCLUDE_ASM stub in %s" % b)
    split = os.path.basename(st.path)[:-2]
    cmd = [PY, "tools/rtu_match.py", fn, "--split", split, "--source", b, "--c", draft,
           "--work", os.path.join(workroot, "%s__%s" % (b, fn))]
    if corpus.is_o0(st.path):
        cmd += ["--o0"]
    try:
        r = subprocess.run(cmd, capture_output=True, text=True, cwd=REPO, timeout=600)
    except subprocess.TimeoutExpired:
        return dict(row, verdict="TIMEOUT", note="rtu_match > 600s")
    out = (r.stdout or "") + (r.stderr or "")
    first = next((l for l in out.splitlines() if l.strip()), "?")
    if re.search(r"^MATCH\b", first) or "\nMATCH" in out:
        return dict(row, verdict="RTU-MATCH", note=first[:120])
    for tag in ("CC1 FAIL", "DIFF", "LENGTH-DRIFT", "NOMATCH"):
        if tag in out:
            line = next((l for l in out.splitlines() if tag in l), tag)
            err = next((l for l in out.splitlines()
                        if re.search(r":\d+: ", l) and "warning" not in l), "")
            return dict(row, verdict=tag.replace(" ", "-"), note=(line + " | " + err)[:200])
    return dict(row, verdict="UNKNOWN", note=first[:200])


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--reloc", required=True, help="reloc_identity --out JSON")
    ap.add_argument("--slate", required=True, help="aprop_autodraft slate (draft paths)")
    ap.add_argument("--stage", required=True, help="stage dir for RTU-MATCH drafts")
    ap.add_argument("--out", default=None, help="verdict JSON (default <reloc>.rtu.json)")
    ap.add_argument("--statuses", default="COMPILE-FAIL",
                    help="comma-separated reloc statuses to re-judge")
    ap.add_argument("--work", default=".run/rtu_2nd")
    ap.add_argument("-j", "--jobs", type=int, default=8)
    a = ap.parse_args()
    os.chdir(REPO)

    want = set(a.statuses.split(","))
    reloc = json.load(open(a.reloc))
    slate = {(r["binary"], r["fn"]): r for r in json.load(open(a.slate))}
    rows = []
    for r in reloc:
        if r.get("status") not in want:
            continue
        s = slate.get((r.get("binary"), r["fn"]))
        if s is None or not os.path.isfile(s["draft"]):
            continue
        rows.append({"fn": r["fn"], "binary": r["binary"], "draft": s["draft"]})
    print("rtu_second_chance: %d of %d reloc rows carry status in %s and have a draft"
          % (len(rows), len(reloc), sorted(want)))
    if not rows:
        return 0

    shutil.rmtree(a.work, ignore_errors=True)
    os.makedirs(a.work, exist_ok=True)
    with ThreadPoolExecutor(max_workers=a.jobs) as ex:          # subprocess waits -> threads
        results = list(ex.map(lambda r: _one(r, a.work), rows))

    staged = 0
    for r in results:
        if r["verdict"] == "RTU-MATCH":
            d = os.path.join(a.stage, r["binary"])
            os.makedirs(d, exist_ok=True)
            shutil.copy(r["draft"], os.path.join(d, r["fn"] + ".c"))
            staged += 1
    cnt = collections.Counter(r["verdict"] for r in results)
    outp = a.out or (a.reloc[:-5] + ".rtu.json" if a.reloc.endswith(".json") else a.reloc + ".rtu.json")
    json.dump(results, open(outp, "w"), indent=1)
    print("rtu_second_chance: " + "  ".join("%s=%d" % kv for kv in sorted(cnt.items())))
    print("rtu_second_chance: staged %d RTU-MATCH draft(s) into %s (byte-gate still decides); "
          "verdicts -> %s" % (staged, a.stage, outp))
    return 0


if __name__ == "__main__":
    sys.exit(main())
