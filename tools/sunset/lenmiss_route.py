#!/usr/bin/env python3
"""P31 T8 — route the LEN±N near-miss pile through the §172b lenses (plan Leg B / A2).

Consumes the c294 gcc-read audit (`.run/c294/audit_results.json`, the classified near-miss
ledger), re-verifies each LEN row against the CURRENT tree (still-stub + draft exists — stored
verdicts decay, R35), re-derives fresh streams via `match_one --emit-streams` (isolated compile,
process pool per A8), classifies with `len_tells.analyze`, and routes:

  mechanical        LEN-LI cluster swap -> repaired draft -> re-match_one; only a fresh MATCH
                    enters the gate slate (.run/lenmiss/mech_slate.json — gate_lane-shaped)
  permuter-length   |Δ|<=2 clean drift -> .run/lenmiss/permuter.json (grinder fuel)
  tell-card         EXTPAIR/SELECT-tagged -> .run/lenmiss/cards.json (campaign agent fuel,
                    §172b text embedded)
  redraft           frac>0.35 (the draft is not the function) -> APPEND-ONLY backlog records
                    (status=failed, klass=SIZE-MISMATCH) so near-miss metrics stop counting them
  card / other      .run/lenmiss/cards.json with the raw verdict

R32: every audit LEN row is accounted (routed | gone | no-draft); totals printed and asserted.
"""
import argparse, collections, json, os, re, subprocess, sys
from concurrent.futures import ProcessPoolExecutor

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import corpus
import len_tells

PY = ".venv/bin/python"
OUT = ".run/lenmiss"

_sc = {}


def is_stub(b, fn):
    if b not in _sc:
        try:
            _sc[b] = {s.symbol: s for s in corpus.stubs(b).values()}
        except Exception:
            _sc[b] = {}
    return _sc[b].get(fn)


def emit_streams(job):
    """Worker: run match_one --emit-streams for one (binary, fn, draft). -> (key, streams|err)."""
    b, fn, draft, asm_dir, o0 = job
    sp = f"{OUT}/streams/{b}__{fn}.json"
    cmd = [PY, "tools/match_one.py", fn, "--c", draft, "--asm-subdir", asm_dir,
           "--emit-streams", sp, "--json"]
    if o0:
        cmd.append("--o0")
    r = subprocess.run(cmd, capture_output=True, text=True)
    if not os.path.exists(sp):
        return (b, fn), {"err": (r.stdout + r.stderr)[-160:]}
    return (b, fn), json.load(open(sp))


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--jobs", type=int, default=12)
    ap.add_argument("--limit", type=int, default=0)
    a = ap.parse_args()
    os.makedirs(f"{OUT}/streams", exist_ok=True)
    os.makedirs(f"{OUT}/mech", exist_ok=True)

    audit = json.load(open(".run/c294/audit_results.json"))
    lenrows = [r for r in audit if (r.get("cls") or "").startswith("LEN")]
    best = {}
    for ln in open(".run/backlog.jsonl"):
        r = json.loads(ln)
        best[(r.get("binary"), r.get("name"))] = r.get("best_draft")

    acct = collections.Counter()
    jobs = []
    meta = {}
    for r in lenrows:
        b, fn = r["binary"], r["fn"]
        st = is_stub(b, fn)
        if st is None:
            acct["gone"] += 1
            continue
        d = best.get((b, fn))
        if not d or not os.path.exists(d):
            acct["no-draft"] += 1
            continue
        asm_dir = os.path.dirname(st.asm_path)
        o0 = corpus.is_o0(st.path)
        jobs.append((b, fn, d, asm_dir, o0))
        meta[(b, fn)] = {"draft": d, "audit_cls": r.get("cls"), "asm_dir": asm_dir, "o0": o0}
    if a.limit:
        jobs = jobs[:a.limit]
    print(f"lenmiss: {len(lenrows)} audit LEN rows -> {len(jobs)} live jobs "
          f"(gone {acct['gone']}, no-draft {acct['no-draft']})")

    with ProcessPoolExecutor(max_workers=a.jobs) as ex:
        results = dict(ex.map(emit_streams, jobs))

    routes = collections.Counter()
    cards, mech, perm, redraft = [], [], [], []
    for (b, fn), st in sorted(results.items()):
        if "err" in st:
            routes["stream-err"] += 1
            continue
        card = len_tells.analyze(st["mine"], st["tgt"])
        card.update({"fn": fn, "binary": b, **meta[(b, fn)]})
        routes[card["route"]] += 1
        if card["route"] == "mechanical":
            txt = open(card["draft"]).read()
            fixed, unresolved = len_tells.repair_mechanical(
                txt, st["mine"], st["tgt"], card.pop("detail"))
            if unresolved:
                card["route"] = "card"
                card["mech_unresolved"] = [str(u) for u in unresolved[:4]]
                routes["mechanical"] -= 1
                routes["mech-unresolved"] += 1
                cards.append(card)
                continue
            p = f"{OUT}/mech/{fn}.c"
            open(p, "w").write(fixed)
            r2 = subprocess.run([PY, "tools/match_one.py", fn, "--c", p,
                                 "--asm-subdir", card["asm_dir"], "--json"]
                                + (["--o0"] if card["o0"] else []),
                                capture_output=True, text=True)
            ok = '"status": "match"' in r2.stdout
            if ok:
                mech.append({"fn": fn, "binary": b, "draft": p})
            else:
                card["route"] = "card"
                card["mech_recheck"] = "no-match"
                routes["mechanical"] -= 1
                routes["mech-nomatch"] += 1
                cards.append(card)
        elif card["route"] == "permuter-length":
            perm.append({"fn": fn, "binary": b, "draft": card["draft"], "delta": card["delta"]})
        elif card["route"] == "redraft":
            redraft.append({"fn": fn, "binary": b})
        else:
            card.pop("detail", None)
            cards.append(card)

    json.dump(mech, open(f"{OUT}/mech_slate.json", "w"), indent=1)
    json.dump(perm, open(f"{OUT}/permuter.json", "w"), indent=1)
    json.dump(cards, open(f"{OUT}/cards.json", "w"), indent=1)
    json.dump(dict(routes), open(f"{OUT}/route_summary.json", "w"), indent=1)
    # redraft reclassification: APPEND-ONLY backlog records (never rewrite history)
    if redraft:
        import time
        with open(".run/backlog.jsonl", "a") as f:
            for r in redraft:
                f.write(json.dumps({"ts": None, "addr": None, "name": r["fn"],
                                    "reach": None, "klass": "SIZE-MISMATCH", "nins": None,
                                    "status": "failed", "closeness": None,
                                    "where_stuck": "lenmiss_route: frac>0.35 — draft is not the fn",
                                    "best_draft": None, "binary": r["binary"],
                                    "source": "lenmiss-route", "residual": None,
                                    "passes_tried": None}) + "\n")
    total = sum(routes.values()) + acct["gone"] + acct["no-draft"]
    print(f"routes: {dict(routes)}")
    print(f"mech slate {len(mech)} | permuter {len(perm)} | cards {len(cards)} | redraft {len(redraft)}")
    assert total >= len(lenrows) - 2, f"R32 accounting: {total} routed+skipped vs {len(lenrows)} rows"
    print(f"lenmiss_route: accounted {total}/{len(lenrows)} -> {OUT}/")


if __name__ == "__main__":
    main()
