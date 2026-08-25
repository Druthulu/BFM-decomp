#!/usr/bin/env python3
"""fix_tu_ret_decls.py — retype a binary's OWN stale forward-decls to a draft's byte-true return,
then gate the draft; restore every edit the gate does not pay for. (P31 S59)

THE WALL THIS REMOVES, measured on 14 of sweep-1's 42 non-banks (the old "near-11" cluster, all
`near 0` after the S59 draft fixes — byte-correct bodies): the destination TU forward-declares the
member `extern void func_X(void);` (a caller-derived spelling — the caller ignores the value) while
the byte-true definition returns `s32`. The gate's arity pre-pass rewrites the PARENS
(`(void)`->`()`); the RETURN TYPE still conflicts, and cc1 rejects the TU with the byte-correct
body in it (`conflicting types for 'func_80184F10'`, rtu-diagnosed at the TU's own line — not
engine_core.h, so this is a T1 edit, unlike fix_header_decl's fleet-tier case).

BYTE-NEUTRALITY (same argument as fix_header_decl, TU-scoped): the true fn always sets $v0; a
caller that declared it `void` never read $v0, so widening the decl to the true return changes
type-checking only. Param spelling goes to no-proto `()` (the arity pre-pass's own proven form).
The whole-binary byte-gate stays the sole arbiter (G3/P9): every edit is journaled with its literal
before/after, and every edit for a fn that does NOT bank is restored before exit.

  tools/fix_tu_ret_decls.py --pairs '[["ov_SC03_002","func_80184F10"], ...]' --drafts DIR [-j 8]
  tools/fix_tu_ret_decls.py --pairs-file pairs.json --drafts DIR
"""
import argparse
import glob
import json
import os
import re
import shutil
import sys
from concurrent.futures import ProcessPoolExecutor

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(REPO, "tools"))
import backlog          # noqa: E402
import gate_stage       # noqa: E402


def draft_ret(draft_text, fn):
    """the definition's return type, or None (K&R and ANSI defs both).

    A K&R definition's param decls sit BETWEEN the paren list and the brace
    (`s32 f(a0)\nvoid *a0;\n{`), so any single regex demanding `... ) {` with no `;` between
    misses every K&R draft — the first run of this tool SKIPped 30 of 32 exactly there. The
    definition START line is the reliable anchor: a line that names the fn with a leading
    type and is not an extern/call."""
    for m in re.finditer(rf'^[ \t]*([A-Za-z_][\w \t\*]*?)\s+\**{re.escape(fn)}\s*\(', draft_text, re.M):
        ret = m.group(1).strip()
        if ret.startswith("extern") or ret.split()[0] in ("return",):
            continue
        return ret or None
    return None


def _one(job):
    b, fn, draft = job["binary"], job["fn"], job["draft"]
    txt = open(draft).read()
    ret = draft_ret(txt, fn)
    if not ret or ret == "void":
        return {"binary": b, "fn": fn, "verdict": "SKIP", "note": f"definition return is {ret!r}"}
    ad = re.search(r'func_([0-9A-Fa-f]+)', fn).group(1)
    decl_re = re.compile(rf'(^[ \t]*)extern\s+[A-Za-z_][\w \t\*]*?\bfunc_{ad}\s*\([^;{{)]*\)\s*;',
                         re.M | re.I)
    journal = []
    for f in sorted(glob.glob(os.path.join(REPO, f"src/{b}/{b}*.c"))):
        t = open(f).read()

        def _sub(m, _f=f):
            new = f"{m.group(1)}extern {ret} {fn}();"
            if m.group(0) == new:
                return m.group(0)
            journal.append({"file": _f, "before": m.group(0), "after": new})
            return new
        t2 = decl_re.sub(_sub, t)
        if t2 != t:
            open(f, "w").write(t2)
    if not journal:
        return {"binary": b, "fn": fn, "verdict": "NO-DECL", "note": "no TU-local conflicting decl found"}

    d = os.path.join(REPO, f".run/fix_tu_ret/{b}")
    shutil.rmtree(d, ignore_errors=True)
    os.makedirs(d, exist_ok=True)
    shutil.copy(os.path.join(REPO, draft), os.path.join(d, fn + ".c"))
    os.makedirs(os.path.join(REPO, ".run/auto/bulk"), exist_ok=True)
    backlog.JSONL = os.path.join(".run/auto/bulk", f"{b}.backlog.jsonl")
    backlog.MD = os.path.join(".run/auto/bulk", f"{b}.backlog.md")
    try:
        r = gate_stage.run_gate(f".run/fix_tu_ret/{b}", binary=b, propagate=False, commit=False,
                                source_tag="fix-tu-ret", lock_path=f".run/auto/gate.{b}.lock",
                                verified_out=f".run/auto/bulk/{b}.verified.txt",
                                failed_out=f".run/auto/bulk/{b}.failed.txt", compute_fleet=False)
        banked = fn in (r.get("verified") or [])
    except Exception as e:
        banked, r = False, {"error": repr(e)}
    if not banked:
        # restore every edit — the gate did not pay for it (§61: undo scope covers write scope)
        missing = 0
        for e in journal:
            t = open(e["file"]).read()
            if e["after"] in t:
                open(e["file"], "w").write(t.replace(e["after"], e["before"], 1))
            else:
                missing += 1
        return {"binary": b, "fn": fn, "verdict": "NOT-BANKED",
                "note": f"{len(journal)} decl(s) edited+restored ({missing} missing)", "gate": r}
    return {"binary": b, "fn": fn, "verdict": "BANKED",
            "note": f"{len(journal)} TU decl(s) retyped to `extern {ret} {fn}();` and KEPT"}


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    g = ap.add_mutually_exclusive_group(required=True)
    g.add_argument("--pairs", help='JSON list of [binary, fn]')
    g.add_argument("--pairs-file")
    ap.add_argument("--drafts", required=True, help="dir of <binary>/<fn>.c drafts")
    ap.add_argument("-j", "--jobs", type=int, default=6)
    a = ap.parse_args()
    os.chdir(REPO)
    pairs = json.loads(a.pairs) if a.pairs else json.load(open(a.pairs_file))
    jobs, seen_bin = [], set()
    for b, fn in pairs:
        p = os.path.join(a.drafts, b, fn + ".c")
        if not os.path.isfile(p):
            print(f"[skip] {b}/{fn}: no draft at {p}")
            continue
        jobs.append({"binary": b, "fn": fn, "draft": p})
        seen_bin.add(b)
    # one job per binary at a time is guaranteed by the per-binary gate lock; parallelism across
    # DISTINCT binaries only (two same-binary jobs would edit the same TU concurrently)
    by_bin = {}
    for j in jobs:
        by_bin.setdefault(j["binary"], []).append(j)
    serial_tail = [j for js in by_bin.values() for j in js[1:]]
    first = [js[0] for js in by_bin.values()]
    results = []
    with ProcessPoolExecutor(max_workers=a.jobs) as ex:
        results += list(ex.map(_one, first))
    for j in serial_tail:                                    # same-binary follow-ups run serially
        results.append(_one(j))
    ok = sum(1 for r in results if r["verdict"] == "BANKED")
    for r in results:
        print(f'{r["verdict"]:10} {r["binary"]:14} {r["fn"]}  {r["note"]}')
    print(f"fix_tu_ret_decls: {ok}/{len(results)} banked (whole-binary SHA, G3/P9)")
    json.dump(results, open(".run/fix_tu_ret/results.json", "w"), indent=1, default=str)
    return 0


if __name__ == "__main__":
    sys.exit(main())
