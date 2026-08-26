#!/usr/bin/env python3
"""rtu_shadow.py — shadow-mode rtu_match beside the wave gate, to decide whether to INVERT the gate.

WHY (P31 S61, frontier-analysis-s60 §3). The gate ladder spends ~3 whole-binary builds per FAILING
draft (stage 0 raw, stage 1 after transforms, stage 2 after sig_unify) and ~1 per banking draft, so
at 1-6% conversion almost every build is spent confirming a failure. `rtu_match` compiles the real
split TU with the draft spliced in — no build tree, no locks, ~2 s, parallel-safe — and could be the
gate's stage 0, so that whole-binary builds are spent only on rtu-MATCH drafts (builds proportional
to BANKS, not drafts). That is a ~20x reduction at current conversion — IF rtu-MATCH predicts
banking and rtu-non-MATCH does not throw away banks. This tool measures exactly that, with zero
behavioural change to the gate (G3/P9 untouched: the SHA gate stays the sole arbiter).

  PROSPECTIVE (run BEFORE the wave is gated — no peeking; and NOT while a gate is in flight, because
  a gate transiently splices bodies into the very src/ TUs rtu reads):
      tools/rtu_shadow.py --wave fa --wave fb -j 32
      -> .run/rtu_shadow/<wave>.jsonl  one row per draft: rtu verdict, ndiff, reloc pre-filter status
  JOIN (run AFTER the gate committed):
      tools/rtu_shadow.py --join fa --join fb
      -> confusion matrix rtu-verdict x outcome, the false-negative rate (banks rtu would have refused),
         and the build accounting (current ladder vs inverted), every figure with its denominator (R41).

Drafts are mapped to their binary through the SHARD'S targets file, never by bare function name — a
wave drafts siblings under the same name in several binaries (54 of wave fa's 470 cards).
"""
import argparse
import collections
import glob
import json
import os
import re
import sys
import time
from concurrent.futures import ThreadPoolExecutor

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import corpus                                                            # noqa: E402
import integration_resolver as ir                                        # noqa: E402

REPO = ir.REPO
OUT = ".run/rtu_shadow"


def wave_drafts(w):
    """[(shard, card, draft_path)] with the card taken from that shard's own targets file."""
    rows, unmapped, ambiguous = [], 0, 0
    for tp in sorted(glob.glob(f".run/wave_{w}_targets.*.json"),
                     key=lambda p: int(p.rsplit(".", 2)[1])):
        i = int(tp.rsplit(".", 2)[1])
        try:
            targets = json.load(open(tp))
        except Exception:
            continue
        by_name = collections.defaultdict(list)
        for c in targets:
            by_name[c.get("name") or c.get("fn")].append(c)
        for d in glob.glob(f".run/wave_{w}/shard{i}/*.c"):
            fn = os.path.basename(d)[:-2]
            cs = by_name.get(fn) or []
            if not cs:
                unmapped += 1
                continue
            if len(cs) > 1:
                ambiguous += 1
                continue
            rows.append((i, cs[0], d))
    return rows, unmapped, ambiguous


def reloc_status(w):
    out = {}
    if not os.path.exists(ir.REJECTS):
        return out
    for line in open(ir.REJECTS, errors="replace"):
        try:
            r = json.loads(line)
        except Exception:
            continue
        if r.get("wave") == w and r.get("fn") and r.get("binary"):
            out[(r["binary"], r["fn"])] = (r.get("status"), r.get("shape"))
    return out


def shadow(w, jobs):
    rows, unmapped, ambiguous = wave_drafts(w)
    rl = reloc_status(w)
    head = ir.sh(["git", "rev-parse", "--short", "HEAD"], 30).stdout.strip()
    ir.say(f"wave {w}: {len(rows)} drafts mapped via shard targets (unmapped {unmapped}, ambiguous-name {ambiguous}); "
           f"reloc pre-filter rows for this wave: {len(rl)}; HEAD {head}")

    def one(item):
        i, c, d = item
        b, fn = c["binary"], c.get("name") or c.get("fn")
        row = {"wave": w, "shard": i, "binary": b, "fn": fn, "draft": d, "draft_sha": ir.sha(d),
               "nins_card": c.get("nins"), "reloc": rl.get((b, fn), ("AGREE?", None))[0],
               "reloc_shape": rl.get((b, fn), (None, None))[1], "head": head,
               "ts": time.strftime("%Y-%m-%d %H:%M:%S")}
        rb = ir.real_binary(b)
        if rb is None or rb == "main":
            row.update(rtu="UNSUPPORTED", ndiff=None, nins=None, note="main / unknown binary")
            return row
        idx, err = ir.stub_index(rb)
        if err:
            row.update(rtu="HARNESS-CORPUS", ndiff=None, nins=None, note=err)
            return row
        stub = idx.get(fn)
        if stub is None:
            row.update(rtu="NOT-A-STUB", ndiff=None, nins=None, note="already banked")
            return row
        work = os.path.join(OUT, "work", w, f"{b}__{fn}")
        v = ir.rtu(rb, fn, stub, d, work, corpus.is_o0(stub.path))
        row.update(rtu=v["verdict"], ndiff=v.get("ndiff"), nins=v.get("nins"), note=v.get("note", "")[:160])
        return row

    t0 = time.time()
    with ThreadPoolExecutor(max_workers=jobs) as ex:
        res = list(ex.map(one, rows))
    os.makedirs(OUT, exist_ok=True)
    with open(os.path.join(OUT, f"{w}.jsonl"), "w") as f:
        for r in res:
            f.write(json.dumps(r) + "\n")
    c = collections.Counter(r["rtu"] for r in res)
    ir.say(f"wave {w}: shadow verdicts in {time.time() - t0:.0f}s: " + "  ".join(f"{k}={v}" for k, v in sorted(c.items())))
    cg = collections.Counter(r["rtu"] for r in res if r["reloc"] == "AGREE?")
    ir.say(f"wave {w}: among drafts the pre-filter will pass (no reject row): " + "  ".join(f"{k}={v}" for k, v in sorted(cg.items())))
    return res


def wave_commits(w):
    out = []
    for line in ir.sh(["git", "log", "--format=%h %s", "-600"], 60).stdout.splitlines():
        h, _, s = line.partition(" ")
        if re.search(r"ox wave %s(\b|$)" % re.escape(w), s):
            out.append(h)
    return out


def join(w):
    p = os.path.join(OUT, f"{w}.jsonl")
    if not os.path.exists(p):
        ir.say(f"wave {w}: no shadow ledger at {p}")
        return
    rows = [json.loads(l) for l in open(p) if l.strip()]
    commits = wave_commits(w)
    if not commits:
        ir.say(f"wave {w}: no gate commit found yet (git log has no 'ox wave {w}') — not gated")
        return
    banked = set()
    pat = re.compile(r'^-.*INCLUDE_ASM\("(asm/[^"]+)",\s*(\w+)\)')
    for h in commits:
        for line in ir.sh(["git", "show", "--unified=0", h, "--", "src/"], 120).stdout.splitlines():
            m = pat.match(line)
            if m:
                parts = m.group(1).split("/")
                banked.add((parts[1] if parts[1] != "nonmatchings" else "main", m.group(2)))
    outcome = collections.Counter()
    table = collections.Counter()
    for r in rows:
        k = (r["binary"], r["fn"])
        if r["rtu"] == "NOT-A-STUB":
            o = "ALREADY-BANKED"
        elif k in banked:
            o = "BANKED"
        elif r["reloc"] != "AGREE?":
            o = "PREFILTER-DROPPED"
        else:
            idx, err = ir.stub_index(r["binary"])
            o = "GATE-REJECTED" if (idx and r["fn"] in idx) else "BANKED-ELSEWHERE"
        outcome[o] += 1
        table[(r["rtu"], o)] += 1
    ir.say(f"wave {w}: gate commit(s) {commits}; outcomes: " + "  ".join(f"{k}={v}" for k, v in sorted(outcome.items())))
    print("  %-16s %-8s %-14s %-18s %-16s %s" % ("rtu verdict", "BANKED", "GATE-REJECTED", "PREFILTER-DROPPED", "BANKED-ELSEWHERE", "ALREADY"))
    for v in sorted({r["rtu"] for r in rows}):
        print("  %-16s %-8d %-14d %-18d %-16d %d" % (v, table[(v, "BANKED")], table[(v, "GATE-REJECTED")],
                                                     table[(v, "PREFILTER-DROPPED")], table[(v, "BANKED-ELSEWHERE")],
                                                     table[(v, "ALREADY-BANKED")]))
    gated = [r for r in rows if r["reloc"] == "AGREE?" and r["rtu"] not in ("NOT-A-STUB", "UNSUPPORTED", "HARNESS-CORPUS")]
    g_b = [r for r in gated if (r["binary"], r["fn"]) in banked]
    g_r = [r for r in gated if (r["binary"], r["fn"]) not in banked]
    m_b = sum(1 for r in g_b if r["rtu"] == "MATCH")
    m_r = sum(1 for r in g_r if r["rtu"] == "MATCH")
    n_m = m_b + m_r
    print(f"  gated drafts {len(gated)}: banked {len(g_b)}, rejected {len(g_r)}")
    print(f"  P(bank | rtu MATCH)     = {m_b}/{n_m}" + (f" = {100.0 * m_b / n_m:.1f}%" if n_m else ""))
    print(f"  false-negative (banks rtu would refuse) = {len(g_b) - m_b}/{len(g_b)}"
          + (f" = {100.0 * (len(g_b) - m_b) / len(g_b):.1f}%" if g_b else ""))
    cur = len(g_b) * 1 + len(g_r) * 3
    inv = m_b * 1 + m_r * 3
    print(f"  whole-binary builds, current ladder ~ {cur} (1/bank + 3/reject) vs inverted ~ {inv} (rtu-MATCH only)"
          + (f" -> {cur / max(1, inv):.1f}x fewer" if inv else ""))
    dropped_match = sum(1 for r in rows if r["reloc"] != "AGREE?" and r["rtu"] == "MATCH")
    print(f"  pre-filter-dropped drafts that rtu-MATCH the real TU (never gated): {dropped_match}")


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--wave", action="append", default=[], help="prospective shadow over this wave's drafts")
    ap.add_argument("--join", action="append", default=[], help="join a shadowed wave with its gate outcome")
    ap.add_argument("-j", "--jobs", type=int, default=32)
    a = ap.parse_args()
    os.chdir(REPO)
    for w in a.wave:
        shadow(w, a.jobs)
    for w in a.join:
        join(w)
    return 0


if __name__ == "__main__":
    sys.exit(main())
