#!/usr/bin/env python3
"""idiom_loop.py — Phase-21 NEVERENDING idiom-learning meta-loop (the wall->next-idiom->fuel engine).

The harvest model: each session drains the EASY reach-134 wave fuel until ~80% is consumed (a WALL),
then learns the next gcc-quirk IDIOM that unlocks the highest-leverage residual, and hands off to a
fresh session (clean context) to crack + harvest it. Repeat forever (Phase 21 ends only when Drew says).

  --fuel-status            : how much FRESH cached reach-134 wave fuel remains (the wall detector).
                             "WALL" when fresh ≤ --wall (default 12) -> run --assess.
  --assess                 : cluster the backlog near-misses by gcc-quirk class, rank by reach-134
                             leverage, and name (a) the next IDIOM to LEARN (top close>0 codegen class)
                             and (b) the cheap DETERMINISTIC recovery lever (close=0 plumbing/decl).
  --gen-fuel <class>       : write the fuel manifest (.run/auto/idiom_fuel.json) for <class>: each fn's
                             addr/nins/reach/closeness/where_stuck/best_draft/asm/ghidra_c — the
                             research+harvest fuel for the next idiom-learning session.

A fresh session then: research the gcc pass (R17, tools/reference/gcc-papermario) -> crack the lowest-
closeness exemplar -> distill the idiom (cookbook) -> re-wave the class with it ×134 -> at ~80% of THAT
fuel, --assess again. Knowledge compounds toward 100% decomp.
"""
import argparse, collections, glob, json, os, re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BACKLOG = os.path.join(ROOT, ".run/backlog.jsonl")
GHIDRA_C = ".run/ghidra_c"
# asm subdirs to probe per region (first existing wins)
ASM_DIRS = ["asm/ov_SC01_077/nonmatchings/ov_SC01_077_a",
            "asm/ov_SC01_077/nonmatchings/ov_SC01_077",
            "asm/ov_SC01_077/nonmatchings/ov_SC01_077_o0"]


def _open_stubs():
    """func names STILL INCLUDE_ASM stubs in ov_SC01_077*.c (unmatched). A name absent => banked/gone
    (mirrors backlog._matched_now; the drop-now-matched P9 honesty)."""
    stub_re = re.compile(r"INCLUDE_ASM\([^,]+,\s*(\w+)\)")
    stubs = set()
    for f in glob.glob(os.path.join(ROOT, "src/ov_SC01_077/ov_SC01_077*.c")):
        try:
            stubs.update(stub_re.findall(open(f).read()))
        except OSError:
            pass
    return stubs


def load_backlog():
    """last record per fn (the freshest near-miss state); only still-unbanked, STILL-STUBBED near/fail.
    Drops fns banked SINCE their last ledger record (stale status 'near' but no longer a stub) — the same
    drop-now-matched honesty backlog.render applies (P9); without it every assess count over-inflates
    with already-matched fns (cont.7: func_8016EDEC/EE40 etc.)."""
    recs = {}
    if os.path.exists(BACKLOG):
        for line in open(BACKLOG):
            line = line.strip()
            if not line:
                continue
            try:
                r = json.loads(line)
            except ValueError:
                continue
            if r.get("name"):
                recs[r["name"]] = r
    open_stubs = _open_stubs()
    return [r for r in recs.values()
            if r.get("status") in ("near", "failed") and r.get("name") in open_stubs]


def klass_of(r):
    k = r.get("klass") or "unknown"
    return k.strip().split()[0] if k.strip() else "unknown"


def asm_for(name):
    for d in ASM_DIRS:
        p = os.path.join(ROOT, d, name + ".s")
        if os.path.exists(p):
            return os.path.join(d, name + ".s")
    return None


def cluster(rows):
    by = collections.defaultdict(lambda: {"n": 0, "r134": 0, "r1": 0, "close": []})
    for r in rows:
        d = by[klass_of(r)]
        d["n"] += 1
        rch = r.get("reach") or 0
        if rch and rch >= 134:
            d["r134"] += 1
        elif rch == 1:
            d["r1"] += 1
        c = r.get("closeness")
        if isinstance(c, int):
            d["close"].append(c)
    return by


def med(xs):
    xs = sorted(xs)
    return xs[len(xs) // 2] if xs else None


def cmd_assess(rows):
    by = cluster(rows)
    print(f"{'class':<16}{'count':>6}{'r134':>6}{'r1':>5}{'med_close':>10}")
    for k, d in sorted(by.items(), key=lambda kv: -kv[1]["r134"]):
        print(f"{k:<16}{d['n']:>6}{d['r134']:>6}{d['r1']:>5}{str(med(d['close'])):>10}")
    # the next IDIOM to LEARN = the top class whose residual is real codegen (median closeness > 0),
    # excluding the deterministic/plumbing buckets (those are a recovery-tool job, not a gcc idiom).
    RECOVERY = {"plumbing", "loose-typing"}
    codegen = [(k, d) for k, d in by.items()
               if k not in RECOVERY and k not in ("unknown", "GIANT") and (med(d["close"]) or 0) > 0]
    codegen.sort(key=lambda kv: -kv[1]["r134"])
    # the cheap DETERMINISTIC lever = close=0 reach-134 fns (byte-correct, declaration-blocked).
    # HONESTY (cont.7, byte-proven): a close=0 fn that ALREADY went through a recovery gate (source
    # 'recover-*') and is STILL unbanked is the §16/§20 DEF-SIDE loose-typing WALL, not cheap fuel —
    # re-running recovery on it banks 0 (cont.6 main 0/40 + cont.7 _a 0/20). match_one reports close=0
    # (masked MATCH) but the whole-binary gate rejects the def-sig conflict. Only NEVER-recovery-gated
    # close=0 fns are genuine ~0-token fuel; split the count so the loop stops re-burning the wall.
    c0 = [r for r in rows if (r.get("reach") or 0) >= 134 and r.get("closeness") == 0]
    det_walled = sum(1 for r in c0 if str(r.get("source", "")).startswith("recover"))
    det_fresh = len(c0) - det_walled
    print()
    if codegen:
        k, d = codegen[0]
        print(f"NEXT IDIOM TO LEARN -> '{k}'  ({d['r134']} reach-134 fns, median {med(d['close'])} ins off)")
        print(f"  gen its fuel:  .venv/bin/python tools/idiom_loop.py --gen-fuel {k}")
    print(f"DETERMINISTIC RECOVERY LEVER -> {det_fresh} FRESH close=0 reach-134 fns (never recovery-gated) "
          f"= the only genuine ~0-token ×134 recovery fuel; gate these first.")
    print(f"  (+{det_walled} close=0 are recovery-FAILED = the def-side loose-typing WALL (cont.6/7): do NOT "
          f"re-run recovery — they need a per-fn type-split or hand-finish, NOT a free bank.)")


def cmd_gen_fuel(rows, klass, out):
    fuel = []
    for r in rows:
        if klass_of(r) != klass:
            continue
        name = r["name"]
        addr = r.get("addr")
        fuel.append({
            "name": name,
            "addr": (f"0x{addr:08x}" if isinstance(addr, int) else addr),
            "nins": r.get("nins"),
            "reach": r.get("reach"),
            "closeness": r.get("closeness"),
            "where_stuck": r.get("where_stuck"),
            "best_draft": r.get("best_draft"),
            "asm": asm_for(name),
            "ghidra_c": (f"{GHIDRA_C}/{name}.c" if os.path.exists(os.path.join(ROOT, GHIDRA_C, name + ".c")) else None),
        })
    # closest-first: the lowest-closeness exemplar is the one to crack the idiom on
    fuel.sort(key=lambda f: (f["closeness"] if isinstance(f["closeness"], int) else 9999))
    os.makedirs(os.path.dirname(os.path.join(ROOT, out)), exist_ok=True)
    open(os.path.join(ROOT, out), "w").write(json.dumps(fuel, indent=1))
    cached = sum(1 for f in fuel if f["ghidra_c"] and f["asm"])
    r134 = sum(1 for f in fuel if (f["reach"] or 0) >= 134)
    print(f"wrote {len(fuel)} '{klass}' fns -> {out}  ({r134} reach-134, {cached} cached/draftable)")
    print("exemplars to crack the idiom on (closest first):")
    for f in fuel[:5]:
        print(f"  {f['name']} close={f['closeness']} reach={f['reach']} nins={f['nins']}: "
              f"{(f['where_stuck'] or '')[:90]}")


def cmd_fuel_status(wall):
    """remaining FRESH cached reach-134 fns wave_targets would serve (not yet in the backlog)."""
    seen = set()
    if os.path.exists(BACKLOG):
        for line in open(BACKLOG):
            try:
                seen.add(json.loads(line).get("name"))
            except ValueError:
                pass
    # approximate fresh fuel = cached ghidra_c fns not yet attempted, with an _a/main asm.
    cdir = os.path.join(ROOT, GHIDRA_C)
    cached = {f[:-2] for f in os.listdir(cdir)} if os.path.isdir(cdir) else set()
    fresh = [n for n in cached if n not in seen and asm_for(n)]
    state = "WALL — run --assess" if len(fresh) <= wall else "fuel OK — keep waving"
    print(f"fresh cached unbanked fuel ≈ {len(fresh)} (wall ≤ {wall}) -> {state}")


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--assess", action="store_true")
    ap.add_argument("--gen-fuel", metavar="CLASS")
    ap.add_argument("--fuel-status", action="store_true")
    ap.add_argument("--out", default=".run/auto/idiom_fuel.json")
    ap.add_argument("--wall", type=int, default=12)
    a = ap.parse_args()
    rows = load_backlog()
    if a.fuel_status:
        cmd_fuel_status(a.wall)
    elif a.gen_fuel:
        cmd_gen_fuel(rows, a.gen_fuel, a.out)
    elif a.assess:
        cmd_assess(rows)
    else:
        ap.print_help()


if __name__ == "__main__":
    main()
