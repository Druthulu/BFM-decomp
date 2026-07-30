#!/usr/bin/env python3
"""rollout_o0.py — the GENERALIZED -O0 two-file atomic rollout (P30 T2; generalizes
tools/rollout_801457a4_o0.py, the Phase-29 T85 driver that banked 130/130 with no splat change).

An -O0 function's matched definition lives in an `ov_SC01_077 *_o0*.c` TU (compiled -O0); in every
other overlay the member's stub sits in an -O2 TU, so `family_sweep --hseq` stages into the wrong
opt level and the gate correctly rejects (§116 — opt level is a property of the FILE). The banking
move is ATOMIC ACROSS TWO FILES per member overlay:

    append the remapped body to <ov>_o0b.c   AND   drop the INCLUDE_ASM from its own TU
    (one edit; splat stops emitting the .s if the stub LINE merely moves — T80's refuted shortcut)

then build that overlay and compare `config/check.<ov>.sha`; on ANY mismatch restore BOTH files
(§61). Deliberately NO splat change — a re-carve is the Arm-A `+0x20` wall (3 of 4 sampled).

Scope rules (R14/§52b — every claim gated, nothing forced):
  * `--all-o0` derives the route-ready set from `.run/family_hseq.json` + the ov077 -O0 TUs:
    families whose exemplar is MATCHED in an ov077 `*_o0*.c` (a real definition — `DEFINE_` or a
    plain def — not an INCLUDE_ASM stub), `has_mid_jr` EXCLUDED (the jr+o0 composites need the
    carve INSIDE the -O0 TU — probe those individually via --fn, expect gate-reject until the
    composite is built; §53 carve law).
  * members come from the family map (handles cross-address families: the stub NAME is derived
    from the MEMBER's address, not the exemplar's); each member's stub line is located in any of
    its overlay's non-`_o0` TUs (T85 hardcoded `_after.c`; SC05_017's stub lives elsewhere).
  * overlays without `<ov>_o0b.c` (the 4 SC07) are reported OUT-OF-SCOPE, never guessed at.
  * the driver does NOT commit; the operator commits per family after the batch's R22 clean-fleet.

  tools/rollout_o0.py --fn func_8013B6A0 [--apply] [--limit N] [--jobs N]
  tools/rollout_o0.py --all-o0 [--apply] [--limit-families N]
"""
import argparse
import concurrent.futures as futures
import glob
import hashlib
import json
import os
import re
import subprocess
import sys
from collections import Counter

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(REPO, "tools"))
import family_remap as FR  # noqa: E402

EX_OV = "ov_SC01_077"
SC07_NO_O0B = {"ov_SC07_006", "ov_SC07_007", "ov_SC07_010", "ov_SC07_011"}

NOTE = ("/* {fn} (@0x{addr:08X}) is an -O0 function; its definition lives in {o0b} (the -O0\n"
        " * whale object). Mirrors ov_SC01_077 (rollout_o0, generalizing §116/T85). */")


def sha1(p):
    h = hashlib.sha1()
    with open(p, "rb") as fh:
        for b in iter(lambda: fh.read(1 << 20), b""):
            h.update(b)
    return h.hexdigest()


def good_sha(ov):
    return open(os.path.join(REPO, f"config/check.{ov}.sha")).read().split()[0]


def build_ok(ov):
    r = subprocess.run(["make", "build", f"BINARY={ov}"], cwd=REPO,
                       stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    out = os.path.join(REPO, f"build/{ov}/{ov}")
    return r.returncode == 0 and os.path.exists(out) and sha1(out) == good_sha(ov)


def o0_matched_exemplars():
    """addr -> True for fns with a REAL definition in an ov077 -O0 TU (not an INCLUDE_ASM stub)."""
    out = set()
    for p in glob.glob(os.path.join(REPO, f"src/{EX_OV}/{EX_OV}_o0*.c")):
        t = open(p).read()
        for m in re.finditer(r'\bfunc_([0-9A-Fa-f]{8})\b', t):
            # a def or DEFINE_ instantiation counts; an INCLUDE_ASM line does not
            line_start = t.rfind("\n", 0, m.start()) + 1
            line = t[line_start:t.find("\n", m.start())]
            if "INCLUDE_ASM" not in line:
                out.add(int(m.group(1), 16))
    return out


def stub_file_of(ov, fn):
    """The overlay TU holding `INCLUDE_ASM(..., <fn>);` — any non-_o0 split (T85 assumed _after)."""
    pat = re.compile(rf'^INCLUDE_ASM\("[^"]+",\s*{fn}\);\s*$', re.M)
    for p in sorted(glob.glob(os.path.join(REPO, f"src/{ov}/{ov}*.c"))):
        if "_o0" in os.path.basename(p):
            continue
        if pat.search(open(p).read()):
            return p, pat
    return None, pat


def attempt(ex_addr, ov, member_addr, apply):
    fn = "func_%08X" % member_addr
    if ov in SC07_NO_O0B:
        return ov, "out-of-scope-sc07", ""
    o0b = os.path.join(REPO, f"src/{ov}/{ov}_o0b.c")
    if not os.path.exists(o0b):
        return ov, "no-o0b", ""
    stub_path, pat = stub_file_of(ov, fn)
    if not stub_path:
        return ov, "no-stub", "already banked?"
    draft, info = FR.remap_hseq(ex_addr, EX_OV, ov, member_addr)
    if draft is None:
        return ov, "remap-refused", str(info)[:60]
    a_txt, b_txt = open(stub_path).read(), open(o0b).read()
    m = pat.search(a_txt)
    new_a = a_txt[:m.start()] + NOTE.format(fn=fn, addr=member_addr, o0b=os.path.basename(o0b)) \
        + a_txt[m.end():]
    new_b = b_txt.rstrip("\n") + "\n\n" + draft.rstrip("\n") + "\n"
    if not apply:
        return ov, "would-try", ""
    open(stub_path, "w").write(new_a)
    open(o0b, "w").write(new_b)
    if build_ok(ov):
        return ov, "BANKED", ""
    open(stub_path, "w").write(a_txt)                   # restore BOTH, always (§61)
    open(o0b, "w").write(b_txt)
    return ov, "gate-reject", ""


def sweep_family(fam, apply, jobs):
    ex_addr = int(re.search(r'0x([0-9A-Fa-f]+)', str(fam["exemplar"])).group(1), 16)
    members = [(ov, int(a, 16)) for ov, a in (tuple(m) for m in fam["members"])]
    print(f"== family 0x{ex_addr:08x} nins={fam['nins']} open={len(members)} jr={fam['has_mid_jr']}",
          flush=True)
    res = []
    if jobs > 1 and apply:
        with futures.ThreadPoolExecutor(max_workers=jobs) as ex:
            for r in ex.map(lambda m: attempt(ex_addr, m[0], m[1], apply), members):
                res.append(r)
                print(f"  {r[0]}: {r[1]} {r[2]}", flush=True)
    else:
        for ov, ma in members:
            r = attempt(ex_addr, ov, ma, apply)
            res.append(r)
            print(f"  {r[0]}: {r[1]} {r[2]}", flush=True)
    c = Counter(r[1] for r in res)
    print(f"   -> {dict(c)}", flush=True)
    return c


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--fn", help="one family by exemplar fn name (func_XXXXXXXX)")
    ap.add_argument("--all-o0", action="store_true",
                    help="derive + sweep every route-ready non-jr -O0 family (map + ov077 -O0 TUs)")
    ap.add_argument("--apply", action="store_true", help="write + gate (default: dry run)")
    ap.add_argument("--limit", type=int, default=0, help="cap members per family")
    ap.add_argument("--limit-families", type=int, default=0)
    ap.add_argument("--jobs", type=int, default=1)
    a = ap.parse_args()

    fams = json.load(open(os.path.join(REPO, ".run/family_hseq.json")))["families"]
    matched_o0 = o0_matched_exemplars()

    picked = []
    if a.fn:
        want = int(a.fn.replace("func_", ""), 16)
        for f in fams:
            ex = re.search(r'0x([0-9A-Fa-f]+)', str(f["exemplar"]))
            if ex and int(ex.group(1), 16) == want:
                picked.append(f)
                break
        if not picked:
            sys.exit(f"family with exemplar {a.fn} not found in the map")
    elif a.all_o0:
        for f in fams:
            ex = re.search(r'0x([0-9A-Fa-f]+)', str(f["exemplar"]))
            if not ex or int(ex.group(1), 16) not in matched_o0:
                continue
            if f["has_mid_jr"]:
                print(f"  [skip jr+o0 composite] 0x{ex.group(1)} nins={f['nins']} "
                      f"open={len(f['members'])} — probe individually via --fn (§53)", flush=True)
                continue
            if f["members"]:
                picked.append(f)
        picked.sort(key=lambda f: -(f["nins"] * len(f["members"])))
        if a.limit_families:
            picked = picked[:a.limit_families]
    else:
        sys.exit("need --fn or --all-o0")

    total = Counter()
    for f in picked:
        if a.limit:
            f = dict(f, members=f["members"][:a.limit])
        total += sweep_family(f, a.apply, a.jobs)
    print(f"TOTAL over {len(picked)} families: {dict(total)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
