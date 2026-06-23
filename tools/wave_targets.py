#!/usr/bin/env python3
"""wave_targets.py — select a worker-wave target batch from the fuel manifest.

Emits a JSON array of {name, addr, nins, class, asm, ghidra_c} for tools/workflows/worker_wave.js
(passed as args.targets). Filters to still-OPEN (INCLUDE_ASM) cached targets in the chosen pool,
ranked by leverage (reach*nins), skipping known walls already logged 'failed'/'stub' in the backlog.

Pools (ROI rotation): tractable (reach-134 WAVE/PINS/STRUCT <=150 ins, main region) | giants |
o0 | capped | any-reach134 | reach1 (overlay-unique reach-1 fns, region main, sorted SMALLEST-FIRST
— the Phase-21 idiom-mining harvest: easy wins + distill the gcc quirk each reveals, feed forward).

Usage: tools/wave_targets.py --pool tractable --n 24 [--region main|a|any] [--out -]
"""
import argparse, glob, json, os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import backlog

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
STUB_RE = re.compile(r"INCLUDE_ASM\([^,]+,\s*(\w+)\)")
ASM_SUBDIR = "asm/ov_SC01_077/nonmatchings/ov_SC01_077"

# Canonical gcc-quirk residual classes (the cookbook §17–20 taxonomy). A wave studies ONE of these
# at a time (the Phase-18 learning model): bank what the class's idiom reaches, distill the quirk,
# feed it forward. Keyword-matched from the worker's self-reported klass + its where_stuck note.
CLASS_KEYWORDS = [
    ("REGALLOC", ("regalloc", "register", "$s", " pin", "reg-order", "reg order", "swap")),
    ("SCHEDULE", ("schedule", "sched", "store-vs-load", "store vs load", "delay slot", "reorder", "operand-order", "operand order")),
    ("REMAT", ("hoist", "remat", "rematerial", "array-decay", "array decay")),
    ("STRUCT", ("struct", "field", " type", "layout", "%lo", "array-of-struct", "array of struct", "union")),
    ("IV", ("iv-combine", "iv combine", "induction", "biv", "halfword rmw")),
    ("LOOPGUARD", ("loop-guard", "loop guard", "get_condition", "strength-reduc")),
    ("LOOSE", ("loose-typing", "loose typing", "arity", "conflicting types", "narrow-param")),
    ("PLUMBING", ("plumbing", "declaration", "extern", "call-site cast", "callee", "no-proto", "sibling decl")),
]


def canon_class(rec):
    """Normalize a backlog record (klass + where_stuck) to a canonical residual class."""
    blob = ((rec.get("klass") or "") + " " + (rec.get("where_stuck") or "")).lower()
    for name, kws in CLASS_KEYWORDS:
        if any(k in blob for k in kws):
            return name
    return "OTHER"


def live_stubs():
    s = set()
    for p in glob.glob(os.path.join(REPO, "src/ov_SC01_077/ov_SC01_077*.c")):
        s |= set(STUB_RE.findall(open(p).read()))
    return s


def backlog_walls():
    """names already logged as 'failed'/'stub' — skip (don't waste agents re-drafting known walls)."""
    walls = set()
    p = os.path.join(REPO, ".run/backlog.jsonl")
    if os.path.exists(p):
        for line in open(p):
            line = line.strip()
            if not line:
                continue
            r = json.loads(line)
            if r.get("status") in ("failed", "stub") and r.get("name"):
                walls.add(r["name"])
    return walls


def plumbing_blocked():
    """SELF-MATCH-but-gate-REJECTED near-misses (DEF-side / TU loose-typing plumbing). Re-drafting just
    reproduces the same byte-correct body the gate rejects again -> NEVER banks via a worker wave
    (Phase-21 finding). Skip in POOL selection so agents draft FRESH targets; these stay in the backlog
    as recovery-tooling / hand-finish fuel (an improved sig_unify / recovery gate banks them out-of-band).

    Signal: closeness==0 (post-recovery match_one MATCH) OR a drafter self-MATCH verdict in where_stuck
    ('none — MATCH …'). The latter is needed because sig_unify can REGRESS a self-MATCH draft to close>0
    post-transform (Phase-19), so it dodges the ==0 filter though the body is byte-correct & gate-blocked."""
    blocked = set()
    p = os.path.join(REPO, ".run/backlog.jsonl")
    if not os.path.exists(p):
        return blocked
    # Scan ALL raw records, not backlog.load_best(): load_best returns one record/fn and can
    # return an early closeness>0 near-miss that MASKS a later 'none — MATCH' self-match-gate-reject
    # record (both can share a closeness, e.g. a sig_unify-regressed self-match logged at close 14).
    # A fn that EVER self-matched-but-gate-rejected is plumbing-blocked: re-drafting reproduces the
    # same gate-rejected body -> skip it from waves (it's recovery-tooling / hand-finish fuel).
    for line in open(p):
        line = line.strip()
        if not line:
            continue
        r = json.loads(line)
        if r.get("status") != "near" or not r.get("name"):
            continue
        ws = (r.get("where_stuck") or "").strip().lower()
        if r.get("closeness") == 0 or ws.startswith("none —") or ws.startswith("none -") or "— match" in ws or "match_one match" in ws:
            blocked.add(r["name"])
    return blocked


def reserved_walls(min_attempts=2):
    """Near-misses re-drafted >= min_attempts times WITHOUT banking are walls: two independent
    toolkit-aware drafters (the initial wave + a smallest-first re-serve with the richer cookbook)
    both failed to byte-match. Crackable near-misses crack on attempt 2 (observed: func_801651B8 /
    func_801549F8 / func_80153D7C); the survivors are permuter-class schedule/regalloc/iv walls
    (func_80140E6C: close=4 on BOTH wave 24 & 25). Smallest-first keeps re-serving them at the front
    of every wave (fixed small nins) -> a slow leak that compounds as the band climbs. Skip them from
    blind waves; they stay in the backlog for the grinder (permuter) or a TARGETED `--class` re-attempt
    (which feeds the drafter the prior stuck-point — a far better shot than another blind draft).
    A banked fn isn't a live stub, so it's already excluded by the stubs gate (it never reaches here)."""
    import collections
    p = os.path.join(REPO, ".run/backlog.jsonl")
    if not os.path.exists(p):
        return set()
    c = collections.Counter()
    for line in open(p):
        line = line.strip()
        if not line:
            continue
        r = json.loads(line)
        if r.get("status") == "near" and r.get("name"):
            c[r["name"]] += 1
    return {n for n, k in c.items() if k >= min_attempts}


def emit(batch, out):
    s = json.dumps(batch, indent=0)
    if out == "-":
        sys.stdout.write(s + "\n")
    else:
        open(os.path.join(REPO, out), "w").write(s)
        print(f"{len(batch)} targets -> {out}", file=sys.stderr)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--pool", default="tractable",
                    choices=["tractable", "giants", "o0", "capped", "any-reach134", "reach1"])
    ap.add_argument("--class", dest="rclass", default=None,
                    help="CLASS-GROUPED wave: select backlog near-misses of this residual class "
                         "(REGALLOC/SCHEDULE/REMAT/STRUCT/IV/LOOPGUARD/LOOSE/PLUMBING/OTHER) to re-attempt")
    ap.add_argument("--list-classes", action="store_true",
                    help="print the backlog residual-class histogram (ranked by leverage) and exit")
    ap.add_argument("--n", type=int, default=24)
    ap.add_argument("--region", default="main", choices=["main", "a", "any"])
    ap.add_argument("--max-nins", type=int, default=150)
    ap.add_argument("--include-walls", action="store_true", help="don't skip backlog failed/stub")
    ap.add_argument("--out", default="-")
    a = ap.parse_args()

    # --- CLASS-GROUPED modes (Phase-21 flywheel): operate on the backlog's classified near-misses ---
    if a.list_classes:
        import collections
        recs = [r for r in backlog.load_best() if r.get("status") == "near"]
        cnt = collections.Counter(canon_class(r) for r in recs)
        lev = collections.Counter()
        for r in recs:
            lev[canon_class(r)] += (r.get("reach") or 1)
        for cls, _ in lev.most_common():
            print(f"{cls:10} n={cnt[cls]:3}  reach-weight={lev[cls]}")
        return
    if a.rclass:
        rc = a.rclass.upper()
        stubs = live_stubs()   # still-unbanked only (a banked fn left the INCLUDE_ASM stub set)
        recs = [r for r in backlog.load_best()
                if r.get("status") == "near" and canon_class(r) == rc and r.get("name")
                and r["name"] in stubs                                          # skip already-banked (stale near records)
                and isinstance(r.get("closeness"), int) and r["closeness"] > 0]  # genuine near-miss; close==0 = plumbing-blocked (re-draft can't bank)
        recs.sort(key=lambda r: (-(r.get("reach") or 1), r.get("closeness") if isinstance(r.get("closeness"), int) else 999))
        batch = [{"name": r["name"], "addr": r.get("addr") or ("0x" + r["name"][5:].lower()),
                  "nins": r.get("nins"), "class": rc, "asm": f"{ASM_SUBDIR}/{r['name']}.s",
                  "ghidra_c": f".run/ghidra_c/{r['name']}.c", "prior_stuck": r.get("where_stuck"),
                  "prior_closeness": r.get("closeness")}
                 for r in recs[:a.n]]
        emit(batch, a.out)
        return

    m = json.load(open(os.path.join(REPO, ".run/fuel_manifest.json")))
    stubs = live_stubs()
    walls = set() if a.include_walls else (backlog_walls() | plumbing_blocked() | reserved_walls())

    def ok(t):
        if t["name"] not in stubs or not t["cached"]:
            return False
        if t["name"] in walls:
            return False
        if a.region != "any" and t["region"] != a.region:
            return False
        if a.pool == "tractable":
            return t["reach_134"] and t["class"] in ("WAVE", "PINS", "STRUCT") and (t["nins"] or 999) <= a.max_nins
        if a.pool == "giants":
            return t["class"] == "GIANT"
        if a.pool == "o0":
            return t["class"] == "O0"
        if a.pool == "any-reach134":
            return t["reach_134"]
        if a.pool == "reach1":   # overlay-unique fuel (Phase 21 idiom-mining), smallest-first sorted below
            return (not t["reach_134"]) and t["class"] in ("WAVE", "PINS", "STRUCT", "STUB") and (t["nins"] or 999) <= a.max_nins
        return False

    pool = [t for t in m["targets"] if ok(t)]
    if a.pool == "capped":  # the matched-but-local recovery set (not stubs)
        pool = [{"name": n, "addr": "0x" + n[5:].lower(), "nins": None, "class": "CAPPED",
                 "reach": 134, "leverage": 0} for n in m.get("capped_recovery", [])]
    if a.pool == "reach1":
        pool.sort(key=lambda t: t.get("nins") or 0)            # SMALLEST-FIRST (idiom-mining order, Drew)
    else:
        pool.sort(key=lambda t: t.get("leverage") or 0, reverse=True)
    pool = pool[:a.n]

    batch = [{"name": t["name"], "addr": t["addr"], "nins": t["nins"], "class": t["class"],
              "asm": f"{ASM_SUBDIR}/{t['name']}.s", "ghidra_c": f".run/ghidra_c/{t['name']}.c"}
             for t in pool]
    emit(batch, a.out)


if __name__ == "__main__":
    main()
