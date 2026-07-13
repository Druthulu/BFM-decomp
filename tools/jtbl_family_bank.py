#!/usr/bin/env python3
"""Phase-26 §8 ×134: bank a matched jr-function exemplar across its h_seq family siblings.

Per sibling (idempotent, revert-on-fail — the whole-binary byte-gate G3/P9 is the sole arbiter):
  1. jtbl_carve  — carve the sibling's jtbl into a dotted .rodata subseg + set <ov>_JTBL_INTERLEAVE
  2. make extract — regenerate asm + run ld_interleave (the data->rodata->data sandwich)
  3. remap_hseq + canon_sig_reconcile — template the exemplar body onto the sibling's TU
  4. make build  — whole-binary gate; keep iff byte-identical, else revert (config + src)

Usage:  jtbl_family_bank.py <func> <from_ov> <from_addr_hex> <members.json>
        members.json = [[to_ov, to_addr_hex], ...]
"""
import glob
import json
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__))))
from family_remap import remap_hseq          # noqa: E402
from canon_sig_reconcile import reconcile     # noqa: E402


def sh(cmd):
    return subprocess.run(cmd, shell=True, capture_output=True, text=True)


def stub_file(ov, func):
    for cf in sorted(glob.glob(f"src/{ov}/{ov}*.c")):
        if re.search(rf'INCLUDE_ASM\("[^"]*",\s*{func}\);', open(cf).read()):
            return cf
    return None


def revert(ov, cf=None):
    if cf:
        subprocess.run(f"git checkout -- {cf}", shell=True)
    sh(f"python3 tools/jtbl_carve.py {ov} --revert")


def bank(func, from_ov, from_addr, to_ov, to_addr):
    # clean slate (idempotent): restore this overlay's config AND src to the committed state
    revert(to_ov)
    subprocess.run(f"git checkout -- src/{to_ov}/ 2>/dev/null", shell=True)
    # Extract FIRST so the on-disk asm matches the reverted committed config (the carve reads the
    # new fn's raw jtbl from asm/<ov>/data — a stale/absent asm from a prior config would miss it).
    if sh(f"make --no-print-directory extract BINARY={to_ov}").returncode:
        revert(to_ov); return "extract0-fail", ""
    r = sh(f"python3 tools/jtbl_carve.py {to_ov} --func {func}")
    if r.returncode:
        revert(to_ov)
        return "carve-fail", ((r.stdout + r.stderr).strip().splitlines()[-1:] or [""])
    if sh(f"make --no-print-directory extract BINARY={to_ov}").returncode:
        revert(to_ov); return "extract-fail", ""
    body, info = remap_hseq(from_addr, from_ov, to_ov, to_addr)
    if body is None:
        revert(to_ov); return "remap-refuse", info
    cf = stub_file(to_ov, func)
    if not cf:
        revert(to_ov); return "no-stub", ""
    try:
        rec = reconcile(func, body, tu_path=cf)
    except Exception as e:
        revert(to_ov); return "reconcile-err", repr(e)[:160]
    src = open(cf).read()
    m = re.search(rf'INCLUDE_ASM\("[^"]*",\s*{func}\);', src)
    open(cf, "w").write(src[:m.start()] + rec + src[m.end():])
    b = sh(f"make --no-print-directory build BINARY={to_ov}")
    if b.returncode == 0 and "[ OK ]" in b.stdout:
        return "BANKED", cf
    revert(to_ov, cf)
    return "gate-fail", ""


def main():
    func, from_ov, from_addr_hex, members_path = sys.argv[1:5]
    from_addr = int(from_addr_hex, 16)
    members = json.load(open(members_path))
    tally = {}
    banked = []
    for i, (to_ov, to_addr_hex) in enumerate(members, 1):
        status, detail = bank(func, from_ov, from_addr, to_ov, int(to_addr_hex, 16))
        tally[status] = tally.get(status, 0) + 1
        if status == "BANKED":
            banked.append(to_ov)
        print(f"[{i:3}/{len(members)}] {to_ov:16} {status}"
              + (f"  {detail}" if status not in ("BANKED",) else ""), flush=True)
    print(f"\n=== {func}: {tally} ===")
    print(f"banked {len(banked)} siblings")
    json.dump(banked, open(f".run/banked_{func}.json", "w"))


if __name__ == "__main__":
    main()
