#!/usr/bin/env python3
"""twin_sweep.py — bank every open stub that has an ALREADY-BANKED structural twin, for ~0 tokens.

THE LEVER (P31 S65, byte-measured). For each open `INCLUDE_ASM` stub, ask whether ANY already-banked
function fleet-wide shares its signature hash. If one does, `family_remap` rewrites that exemplar's C
to this overlay's symbols mechanically and the whole-binary gate decides (G3/P9). Measured yields:

    h_exact (identical instruction bytes modulo reloc fields) : 139/157 = 88.5%
    h_norm  (identical after masking the reloc fields)        : 36/45   = 80%   (first probe)
                                                                178/234 = 76%   (parallel sweep)
    h_seq   (mnemonic skeleton, immediates may differ)        : 0%  — Phase-26 refuted it; NOT USED

**THE POOL REFILLS.** Every bank becomes an exemplar for its own siblings, so a sweep that ends with
0 candidates is NOT the end: re-run after any wave, recovery pass, or sweep. Measured: immediately
after banking 178 functions, 165 fresh twin candidates existed that had none before.

**RUN THIS BEFORE DRAWING A WAVE.** A drafting slot spent on a function that has a banked twin is
pure waste, and `t5_cards.py` does NOT build `seed_ref`, so cards actively assert "no banked twin —
derive from the .s" for these. Measured cost of not doing it: a t5u Opus slot ground
ov_SC03_023:func_8017BEBC to closeness 45 while ov_SC02_004 held a byte-identical banked copy.

  twin_sweep.py [--tier exact|norm|both] [--workers 10] [--plan-only] [--commit] [--r22]

Staging is pure computation (family_remap only READS build/ + asm/), so it is safe to run while
something else holds the tree; only the gate needs `tools/parallel_gate.py` and a quiet tree.
"""
import argparse, collections, json, os, shutil, subprocess, sys
from concurrent.futures import ThreadPoolExecutor

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(REPO)
sys.path.insert(0, "tools")
PY = ".venv/bin/python"


def candidates(tier):
    """[{to, to_addr, from, addr, same_addr, nins, tier}] — an open stub + its banked exemplar.

    Prefers a SAME-ADDRESS exemplar (the same engine fn in a sibling overlay) because the remap is
    then a pure symbol substitution; a cross-address twin additionally needs --to-addr."""
    import family_sweep as FS, corpus, progress
    sigs = FS.load_sigs()
    open_by = {}
    for b in progress.BINARIES:
        try:
            open_by[b] = {int(s.symbol[5:], 16) for s in corpus.stubs(b).values()}
        except Exception:
            pass
    banked = {"exact": collections.defaultdict(list), "norm": collections.defaultdict(list)}
    for b, addrs in sigs.items():
        op = open_by.get(b, set())
        for addr, (nins, hx, hn) in addrs.items():
            if addr in op:
                continue
            banked["exact"][hx].append((b, addr, nins))
            banked["norm"][hn].append((b, addr, nins))
    want = ("exact", "norm") if tier == "both" else (tier,)
    out, seen = [], set()
    for b, addrs in sigs.items():
        op = open_by.get(b, set())
        for addr, (nins, hx, hn) in addrs.items():
            if addr not in op or (b, addr) in seen:
                continue
            for t in want:                      # exact first: a stricter twin is a safer remap
                pool = banked[t].get(hx if t == "exact" else hn)
                if not pool:
                    continue
                fb, fa, _ = sorted(pool, key=lambda x: (x[1] != addr, x[0]))[0]
                out.append({"to": b, "to_addr": "0x%08x" % addr, "from": fb, "addr": "0x%08x" % fa,
                            "same_addr": fa == addr, "nins": nins, "tier": t})
                seen.add((b, addr))
                break
    return out


def stage(item):
    b, rows, root = item
    d = os.path.abspath(os.path.join(root, b))
    shutil.rmtree(d, ignore_errors=True)
    os.makedirs(d)
    made = 0
    for r in rows:
        fn = "func_%s" % r["to_addr"][2:].upper()
        cmd = [PY, "tools/family_remap.py", "--addr", r["addr"], "--from", r["from"],
               "--to", b, "--out", "%s/%s.c" % (d, fn)]
        if not r["same_addr"]:
            cmd += ["--to-addr", r["to_addr"]]
        p = subprocess.run(cmd, capture_output=True, text=True)
        if p.returncode == 0 and os.path.exists("%s/%s.c" % (d, fn)):
            made += 1
    return b, made, len(rows), d


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--tier", default="both", choices=("exact", "norm", "both"))
    ap.add_argument("--workers", type=int, default=10)
    ap.add_argument("--plan-only", action="store_true")
    ap.add_argument("--commit", action="store_true")
    ap.add_argument("--r22", action="store_true")
    ap.add_argument("--root", default=".run/twin_stage")
    a = ap.parse_args()

    cands = candidates(a.tier)
    by = collections.defaultdict(list)
    for r in cands:
        by[r["to"]].append(r)
    tc = collections.Counter(r["tier"] for r in cands)
    print("[twin] %d candidate(s) across %d binaries (%d ins) — %s"
          % (len(cands), len(by), sum(r["nins"] for r in cands),
             ", ".join("%s %d" % kv for kv in sorted(tc.items()))), flush=True)
    if not cands:
        print("[twin] nothing to do — re-run after the next wave/recovery bank (the pool REFILLS)")
        return

    with ThreadPoolExecutor(max_workers=12) as ex:
        res = list(ex.map(stage, [(b, rows, a.root) for b, rows in by.items()]))
    plan = [{"binary": b, "drafts": d} for b, made, _, d in res if made]
    json.dump(plan, open(".run/twin_plan.json", "w"), indent=1)
    print("[twin] staged %d/%d remap(s); plan .run/twin_plan.json (%d binaries)"
          % (sum(m for _, m, _, _ in res), sum(t for _, _, t, _ in res), len(plan)), flush=True)
    if a.plan_only:
        return

    cmd = [PY, "tools/parallel_gate.py", "--plan", ".run/twin_plan.json",
           "--workers", str(a.workers)]
    if a.commit:
        cmd.append("--commit")
    if a.r22:
        cmd.append("--r22")
    sys.exit(subprocess.call(cmd))


if __name__ == "__main__":
    main()
