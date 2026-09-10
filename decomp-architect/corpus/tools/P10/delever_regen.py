#!/usr/bin/env python3
"""delever_regen.py — re-run NEW generator families over the whole residue, read-only, and bank what closes.

    tools/delever_regen.py --families R22 R23 [-j 12] [--only X ...] [--exclude FN ...] [--label L]   # read-only pass
    tools/delever_regen.py --bank .run/P36/regen/<label>.tsv                                       # the ONE writer

WHY (P36 S103). Every T7 landing is harvested into a generator (R15-R23 so far), but the residue's 2,078 NO-MATCH
attempts were all made BEFORE the newest families existed, and nothing re-tried them. The first time it mattered: R23,
widened from agent c16's close, reproduces that close alone — `split p into 9` scores 0 on func_8013D178's start text —
so any other residue body with the same shape is a free bank that no search would revisit. A full engine re-sweep is the
wrong tool: it writes the tree (it cannot run beside a bank), and it spends its budget re-trying every old family first.

WHAT IT DOES. For every residue class (`delever_search.exemplars(include_done=True)`), two starting texts — the
lever-free body (`lever_free_body`) and the engine's best text (`.run/P36/engine/bodies/<alias>__<fn>.c`) — are fed to
`delever.recipe_candidates(..., families=<the named families>, cap=None)`, and every candidate is scored by
`delever_search.py --try TU FN FILE --body` (the agents' scorer: a scratch copy of the TU, zero tree writes). One worker
per class, candidates of one class in sequence (the scorer's scratch dir is per function, so two candidates of one class
must never run at once). A class stops at its first score 0. Result: `.run/P36/regen/<label>.tsv`, one row per class
with its best candidate, and the candidate texts under `.run/P36/regen/<label>/`.

`--bank` re-scores each score-0 row on the CURRENT tree first (the tree may have moved since the pass), then
`delever.apply_body_core` (the whole-object gate, rung E) and `delever --propagate`. It is a tree writer: never while a
sweep or another bank runs (the S102 two-writer rule). Follow it with the R22 fleet run like any bank.
"""
import argparse, concurrent.futures as cf, csv, json, os, pathlib, re, subprocess, sys, time

REPO = pathlib.Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO / "tools"))
import delever as dl                # noqa: E402
import delever_search as ds         # noqa: E402

PY = str(REPO / ".venv" / "bin" / "python")
OUT = REPO / ".run" / "P36" / "regen"
SCORE = re.compile(r": score (\d+) \((\w[\w-]*); mine (\d+) ins, target (\d+)\)")


def score(tu, fn, path):
    """(score | None, class, line) — one read-only `--try --body`; None when the scorer did not produce a score."""
    r = subprocess.run([PY, "tools/delever_search.py", "--try", tu, fn, str(path), "--body"],
                       capture_output=True, text=True, cwd=REPO)
    line = ((r.stdout or "") + (r.stderr or "")).strip().split("\n")[0]
    m = SCORE.search(line)
    if m:
        return int(m.group(1)), m.group(2), line
    # R61: a candidate that does not COMPILE was judged and failed; only a scorer that could not run is "not judged"
    return None, ("COMPILE-ERROR" if "COMPILE-ERROR" in line or "COMPILE-CRASH" in line else "ERROR"), line[:200]


def starts(e):
    """[(name, body text)] — the lever-free body and the engine's best text, whichever exist."""
    out = []
    raw = (REPO / e["tu"]).read_text(errors="surrogateescape")
    try:
        free = ds.lever_free_body(e["tu"], raw, e["fn"], ds.sites_by_body().get((e["tu"], e["fn"]), []))
        d_ = ds.body_span(free, e["tu"], e["fn"])
        if d_:
            ls = dl.line_starts(free)
            out.append(("free", free[ls[d_["line"] - 1]:ls[d_["end"]]]))
    except ds.Unstrippable:
        pass
    bp = ds.RUN / "bodies" / f"{e['alias']}__{e['fn']}.c"
    if bp.exists():
        out.append(("best", bp.read_text(errors="surrogateescape")))
    return out


def one(e, fams, label):
    d = OUT / label / f"{e['alias']}__{e['fn']}"
    best = None
    tried = compile_errors = 0
    for sname, body in starts(e):
        try:
            cands = dl.recipe_candidates(body, "src/fx/regen.c", e["fn"], [], cap=None, families=fams)
        except Exception as x:                               # a generator crash is a finding, not a silent skip (R43)
            return dict(e, verdict="GEN-ERROR", err=str(x)[:160], tried=tried)
        for rec, desc, cand in cands:
            d.mkdir(parents=True, exist_ok=True)
            p = d / f"{sname}_{tried:03d}.c"
            p.write_text(cand, errors="surrogateescape")
            s, cls, line = score(e["tu"], e["fn"], p)
            tried += 1
            compile_errors += cls == "COMPILE-ERROR"
            if s is not None and (best is None or s < best["score"]):
                best = dict(score=s, cls=cls, family=rec, desc=desc, start=sname, path=str(p.relative_to(REPO)))
            if s == 0:
                return dict(e, verdict="MATCH", tried=tried, **best)
    if best is None:
        return dict(e, verdict="NO-CANDIDATE" if tried == 0 else ("COMPILE-ERROR" if compile_errors == tried else "UNSCORED"),
                    tried=tried)
    return dict(e, verdict="BEST", tried=tried, **best)


def run(a):
    fams = tuple(a.families)
    unknown = [f for f in fams if f not in dl.ALL_FAMILIES]
    if unknown:
        sys.exit(f"delever_regen: unknown families {unknown} (known: {dl.ALL_FAMILIES})")   # R43
    ex = [e for e in ds.exemplars(include_done=True) if ds.matches(e, a.only) and e["fn"] not in set(a.exclude)]
    if a.limit:
        ex = ex[:a.limit]
    if not ex:
        sys.exit("delever_regen: no residue class selected — refusing an empty work list (R68)")
    label = a.label or time.strftime("regen_%Y%m%d_%H%M%S")
    OUT.mkdir(parents=True, exist_ok=True)
    print(f"delever_regen: {len(ex)} residue class(es), families {' '.join(fams)}, -j{a.jobs}, label {label}", flush=True)
    rows, n, t0 = [], 0, time.time()
    with cf.ThreadPoolExecutor(max_workers=a.jobs) as pool:
        futs = {pool.submit(one, e, fams, label): e for e in ex}
        for f in cf.as_completed(futs):
            r = f.result()
            rows.append(r)
            n += 1
            if r["verdict"] == "MATCH":
                print(f"  MATCH {r['alias']}__{r['fn']} ({r['copies']} copies) {r['family']} {r['desc']} from {r['start']} "
                      f"-> {r['path']}", flush=True)
            if n % 50 == 0:
                c = {v: sum(1 for x in rows if x["verdict"] == v) for v in ("MATCH", "BEST", "NO-CANDIDATE", "COMPILE-ERROR", "UNSCORED", "GEN-ERROR")}
                print(f"  {n}/{len(ex)} classes · {c} · {time.time() - t0:.0f} s", flush=True)
    tsv = OUT / f"{label}.tsv"
    cols = ["verdict", "alias", "fn", "tu", "copies", "score", "cls", "family", "desc", "start", "path", "tried", "err"]
    with open(tsv, "w", newline="") as fh:
        w = csv.writer(fh, delimiter="\t")
        w.writerow(cols)
        for r in sorted(rows, key=lambda r: (r["verdict"] != "MATCH", r.get("score") if r.get("score") is not None else 10**6,
                                             -r["copies"])):
            w.writerow([r.get(c, "") for c in cols])
    c = {v: sum(1 for x in rows if x["verdict"] == v) for v in ("MATCH", "BEST", "NO-CANDIDATE", "COMPILE-ERROR", "UNSCORED", "GEN-ERROR")}
    m = [r for r in rows if r["verdict"] == "MATCH"]
    print(f"delever_regen: {len(rows)} of {len(ex)} classes judged in {time.time() - t0:.0f} s — {c}; "
          f"{len(m)} class(es) close at score 0 ({sum(r['copies'] for r in m)} bodies) -> {tsv.relative_to(REPO)}")
    return 0


def bank(a):
    rows = [r for r in csv.DictReader(open(a.bank), delimiter="\t") if r["verdict"] == "MATCH"]
    if not rows:
        sys.exit(f"delever_regen --bank: no MATCH row in {a.bank} — refusing an empty work list (R68)")
    label = pathlib.Path(a.bank).stem
    n_b = n_s = 0
    for r in rows:
        tu, fn, path = r["tu"], r["fn"], REPO / r["path"]
        s, cls, line = score(tu, fn, path)                   # the tree may have moved since the pass
        if s != 0:
            print(f"  STALE {tu}:{fn}: re-score {s} ({line[:120]}) — not banked")
            continue
        msg = dl.apply_body_core(tu, fn, path.read_text(errors="surrogateescape"), f"{label}", "E",
                                 source=f"delever_regen {r['family']} {r['desc']}")[1]
        print(" ", msg, flush=True)
        if "KEPT" not in msg:
            continue
        n_b += 1
        p = subprocess.run([PY, "tools/delever.py", "--propagate", tu, fn, "--label", f"{label}p", "--dirty-ok"],
                           capture_output=True, text=True, cwd=REPO)
        last = [l for l in (p.stdout or "").split("\n") if l.startswith("delever --propagate")]
        print("  ", last[-1] if last else (p.stdout or p.stderr)[-200:], flush=True)
        m = re.search(r"(\d+) of \d+ sibling", last[-1]) if last else None
        n_s += int(m.group(1)) if m else 0
    print(f"delever_regen --bank: {n_b} of {len(rows)} MATCH row(s) banked, {n_s} sibling(s) propagated — now run the "
          f"R22 fleet gate")
    return 0


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--families", nargs="+", default=["R22", "R23"])
    ap.add_argument("-j", "--jobs", type=int, default=12)
    ap.add_argument("--only", nargs="*", default=[])
    ap.add_argument("--exclude", nargs="*", default=[], help="functions an agent is working on (never score them here)")
    ap.add_argument("--limit", type=int)
    ap.add_argument("--label")
    ap.add_argument("--bank", help="bank the MATCH rows of this TSV (the one writer)")
    a = ap.parse_args()
    os.chdir(REPO)
    return bank(a) if a.bank else run(a)


if __name__ == "__main__":
    sys.exit(main())
