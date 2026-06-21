#!/usr/bin/env python3
"""wave_targets.py — select a worker-wave target batch from the fuel manifest.

Emits a JSON array of {name, addr, nins, class, asm, ghidra_c} for tools/workflows/worker_wave.js
(passed as args.targets). Filters to still-OPEN (INCLUDE_ASM) cached targets in the chosen pool,
ranked by leverage (reach*nins), skipping known walls already logged 'failed'/'stub' in the backlog.

Pools (ROI rotation): tractable (reach-134 WAVE/PINS/STRUCT <=150 ins, main region) | giants |
o0 | capped | any-reach134.

Usage: tools/wave_targets.py --pool tractable --n 24 [--region main|a|any] [--out -]
"""
import argparse, glob, json, os, re, sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
STUB_RE = re.compile(r"INCLUDE_ASM\([^,]+,\s*(\w+)\)")
ASM_SUBDIR = "asm/ov_SC01_077/nonmatchings/ov_SC01_077"


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


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--pool", default="tractable",
                    choices=["tractable", "giants", "o0", "capped", "any-reach134"])
    ap.add_argument("--n", type=int, default=24)
    ap.add_argument("--region", default="main", choices=["main", "a", "any"])
    ap.add_argument("--max-nins", type=int, default=150)
    ap.add_argument("--include-walls", action="store_true", help="don't skip backlog failed/stub")
    ap.add_argument("--out", default="-")
    a = ap.parse_args()

    m = json.load(open(os.path.join(REPO, ".run/fuel_manifest.json")))
    stubs = live_stubs()
    walls = set() if a.include_walls else backlog_walls()

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
        return False

    pool = [t for t in m["targets"] if ok(t)]
    if a.pool == "capped":  # the matched-but-local recovery set (not stubs)
        pool = [{"name": n, "addr": "0x" + n[5:].lower(), "nins": None, "class": "CAPPED",
                 "reach": 134, "leverage": 0} for n in m.get("capped_recovery", [])]
    pool.sort(key=lambda t: t.get("leverage") or 0, reverse=True)
    pool = pool[:a.n]

    batch = [{"name": t["name"], "addr": t["addr"], "nins": t["nins"], "class": t["class"],
              "asm": f"{ASM_SUBDIR}/{t['name']}.s", "ghidra_c": f".run/ghidra_c/{t['name']}.c"}
             for t in pool]
    out = json.dumps(batch, indent=0)
    if a.out == "-":
        sys.stdout.write(out + "\n")
    else:
        open(os.path.join(REPO, a.out), "w").write(out)
        print(f"{len(batch)} targets -> {a.out} (pool={a.pool} region={a.region})", file=sys.stderr)


if __name__ == "__main__":
    main()
