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


def region_files(ov):
    """The §8b isolation region files currently on disk for this overlay."""
    return set(glob.glob(f"src/{ov}/{ov}_jr_*.c"))


def revert(ov, cf=None, keep_regions=None):
    """Restore the overlay to its committed state. `keep_regions` = the region files that existed
    BEFORE this bank attempt (a previously-banked core's, possibly still uncommitted) — only the
    files THIS attempt created are removed."""
    if cf:
        subprocess.run(f"git checkout -- {cf}", shell=True)
    sh(f"python3 tools/jtbl_carve.py {ov} --revert")
    subprocess.run(f"git checkout -- src/{ov}/ 2>/dev/null", shell=True)
    if keep_regions is not None:
        for f in region_files(ov) - keep_regions:
            os.remove(f)


def isolate(ov, func):
    """§8b LAZY isolation: give `func` its own code subseg so its jtbl carves without a same-subseg
    collision. Only invoked when jtbl_carve reports a NON-CONTIGUOUS collision — i.e. `func` shares a
    code object with an already-banked jr whose jtbl is not adjacent to it. Isolating every jr in all
    134 overlays upfront is byte-proven (R22 136/136) but would add ~7,200 region files, so we pay
    only for the cores we actually bank."""
    return sh(f"python3 tools/jr_isolate_all.py {ov} --only {func}")


def bank(func, from_ov, from_addr, to_ov, to_addr):
    # CROSS-ADDRESS families: the sibling hosts the same function at a DIFFERENT vram, so its symbol
    # is func_<to_addr>, not the exemplar's name. Everything on the sibling side (carve, isolation,
    # stub lookup, reconcile) must use the sibling's name; `remap_hseq` already self-renames the body
    # (T2b). The first two banked jr families were same-address, so this never surfaced until
    # func_80182268 (ov_SC01_077 @0x80182268 -> ov_SC02_000/003 @0x8017FCB0).
    to_func = "func_%08X" % to_addr
    # clean slate (idempotent): restore this overlay's config AND src to the committed state
    keep = region_files(to_ov)
    revert(to_ov)
    subprocess.run(f"git checkout -- src/{to_ov}/ 2>/dev/null", shell=True)
    # Extract FIRST so the on-disk asm matches the reverted committed config (the carve reads the
    # new fn's raw jtbl from asm/<ov>/data — a stale/absent asm from a prior config would miss it).
    if sh(f"make --no-print-directory extract BINARY={to_ov}").returncode:
        revert(to_ov, keep_regions=keep); return "extract0-fail", ""
    r = sh(f"python3 tools/jtbl_carve.py {to_ov} --func {to_func}")
    if r.returncode and "NON-CONTIGUOUS" in (r.stdout + r.stderr):
        # the §8b same-subseg wall -> isolate this core, re-extract, retry the carve
        if isolate(to_ov, to_func).returncode:
            revert(to_ov, keep_regions=keep); return "isolate-fail", ""
        if sh(f"make --no-print-directory extract BINARY={to_ov}").returncode:
            revert(to_ov, keep_regions=keep); return "extract-iso-fail", ""
        r = sh(f"python3 tools/jtbl_carve.py {to_ov} --func {to_func}")
    if r.returncode:
        revert(to_ov, keep_regions=keep)
        return "carve-fail", ((r.stdout + r.stderr).strip().splitlines()[-1:] or [""])
    if sh(f"make --no-print-directory extract BINARY={to_ov}").returncode:
        revert(to_ov, keep_regions=keep); return "extract-fail", ""
    body, info = remap_hseq(from_addr, from_ov, to_ov, to_addr)
    if body is None:
        revert(to_ov, keep_regions=keep); return "remap-refuse", info
    cf = stub_file(to_ov, to_func)
    if not cf:
        revert(to_ov, keep_regions=keep); return "no-stub", ""

    # TWO-STAGE GATE — the recovery pass is a FALLBACK, never unconditional (the §19 lesson, now
    # byte-proven for canon_sig_reconcile too): reconcile rewrites the def to the canonical sig, and
    # its `void`->`s32` return promotion is NOT byte-neutral for a void body with no `return` — it
    # costs one instruction (proven on func_80182268: raw = MATCH 31 ins, reconciled = 32 ins, and the
    # extra word shifted the whole image +4). So gate the RAW remapped body first and only reconcile
    # if it fails (which is what the §41 def-side wall actually needs).
    orig = open(cf).read()
    m = re.search(rf'INCLUDE_ASM\("[^"]*",\s*{to_func}\);', orig)
    if not m:
        revert(to_ov, keep_regions=keep); return "no-stub", ""
    stages = [("raw", lambda: body), ("reconciled", lambda: reconcile(to_func, body, tu_path=cf))]
    for name, make in stages:
        try:
            cand = make()
        except Exception as e:
            revert(to_ov, keep_regions=keep); return "reconcile-err", repr(e)[:160]
        open(cf, "w").write(orig[:m.start()] + cand + orig[m.end():])
        b = sh(f"make --no-print-directory build BINARY={to_ov}")
        if b.returncode == 0 and "[ OK ]" in b.stdout:
            return "BANKED", f"{cf} [{name}]"
        open(cf, "w").write(orig)          # restore the stub before the next stage
    revert(to_ov, cf, keep_regions=keep)
    return "gate-fail", ""


def main():
    func, from_ov, from_addr_hex, members_path = sys.argv[1:5]
    from_addr = int(from_addr_hex, 16)
    members = json.load(open(members_path))
    # The per-sibling revert restores config/ and src/ from HEAD, so an UNCOMMITTED prior family
    # bank would be silently reverted mid-sweep. Stop loudly instead (P9).
    dirty = subprocess.run("git status --porcelain -- config/ src/", shell=True,
                           capture_output=True, text=True).stdout.strip()
    if dirty:
        sys.exit("jtbl_family_bank: config/ or src/ has uncommitted changes — the per-sibling revert "
                 "restores from HEAD, so a prior uncommitted bank would be lost.\nCommit (or stash) "
                 "the previous family before sweeping the next.\n" + dirty[:400])
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
