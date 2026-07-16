#!/usr/bin/env python3
"""Phase-29 T2 Arm A: carve the -O0 cluster (vram 0x8013B568..0x8013C98C, file 0x13410..0x14834)
into its own -O0 object per single-file overlay, so the h_seq family members of those 9 matched
-O0 exemplars can bank whole-binary (they masked-MATCH only at -O0 — the Task-1 swing verdict).

Background (the swing verdict, 2026-07-16): `family_sweep --hseq` compiled the -O0 cluster members
at -O2 (member stub files are -O2), so their remapped bodies masked-MATCH but fail the whole-binary
gate. gcc-2.7.2 has no per-function optimize pragma (opt is per-FILE), so — exactly like the whale
(rollout_whale_o0.py, §38) and ov_SC01_077's own _o0 split (Phase-19 §18) — each overlay must
compile the cluster in its own -O0 TU. This tool builds that split; the family sweep then fills it.

The cluster is a contiguous run of 16 fns (all INCLUDE_ASM stubs in an unswept overlay). We carve
<ov>.c into 3 objects (a single object's .text can't be split around a middle object):
  - <ov>.c       = before the cluster (0x0..0x13410), keeps name + nonmatchings/<ov> asm paths
  - <ov>_o0.c    = the -O0 cluster (0x13410..0x14834), asm paths -> nonmatchings/<ov>_o0
  - <ov>_o2b.c   = after the cluster (0x14834..data tail), asm paths -> nonmatchings/<ov>_o2b
The Makefile O0_CLUSTER_OBJS wildcard -O0-compiles every <ov>_o0.o. Byte-NEUTRAL by construction:
INCLUDE_ASM pastes the ORIGINAL bytes regardless of -O0/-O2, so a freshly-carved (all-stub) overlay
stays byte-identical — gate it before sweeping. Idempotent (skips carved overlays). The whole-binary
byte-gate (make check-all) is the sole arbiter (G3/P9). Usage:
  rollout_o0_cluster.py <ov> [<ov> ...]      # single-file overlays only (files=1); whale/jr-carved
                                             # overlays keep the cluster inside jr_801380E0 (not handled)
"""
import sys, re, os

BASE = 0x80128158
LO_FOFF, HI_FOFF = 0x13410, 0x14834       # cluster vram 0x8013B568 .. 0x8013C98C
START_FN = "func_8013B568"                # first fn of the cluster (0x13410)
LAST_FN = "func_8013C964"                 # last fn of the cluster (just below 0x14834)
CLUSTER_FNS = [                           # the 16 contiguous -O0 fns (from ov_SC01_077_o0.c)
    "func_8013B568", "func_8013B598", "func_8013B6A0", "func_8013B7AC",
    "func_8013B7F4", "func_8013B83C", "func_8013BC7C", "func_8013BCDC",
    "func_8013BD34", "func_8013BD74", "func_8013C08C", "func_8013C0F8",
    "func_8013C360", "func_8013C414", "func_8013C938", "func_8013C964",
]


def header_end(lines):
    """Header = the leading #include block (+ trailing blanks). Stops at the first non-#include,
    non-blank line (a DEFINE_func macro / decl), so the low-address dedup macros stay in `before`."""
    last_inc = -1
    for i, l in enumerate(lines):
        s = l.strip()
        if s.startswith("#include"):
            last_inc = i
        elif s and last_inc >= 0:
            break
    he = last_inc + 1
    while he < len(lines) and lines[he].strip() == "":
        he += 1
    return he


def unit_start(lines, fn):
    """Line index where `fn`'s definition/stub begins (an INCLUDE_ASM stub or a `... fn(` def line)."""
    for i, l in enumerate(lines):
        if re.search(rf'INCLUDE_ASM\("[^"]*",\s*{fn}\)\s*;', l):
            return i, "stub"
        if re.search(rf'\b{fn}\s*\(', l) and not l.lstrip().startswith(("//", "*", "extern")) \
                and "INCLUDE_ASM" not in l and (l.rstrip().endswith("{") or ")" in l and ";" not in l):
            return i, "def"
    return None, None


def split_overlay(ov):
    cdir = f"src/{ov}"
    main_c = f"{cdir}/{ov}.c"
    o0_c, o2b_c = f"{cdir}/{ov}_o0.c", f"{cdir}/{ov}_o2b.c"
    yaml = f"config/splat.{ov}.yaml"
    if os.path.exists(o0_c):
        return f"SKIP {ov} (o0 exists)"
    if not (os.path.exists(main_c) and os.path.exists(yaml)):
        return f"SKIP {ov} (missing .c or yaml)"
    lines = open(main_c).read().split("\n")

    # every cluster fn must be present in THIS file (single-file overlay) — else the cluster is
    # carved elsewhere (jr-embedded overlay) and this tool must not touch it.
    missing = [fn for fn in CLUSTER_FNS if not any(re.search(rf'\b{fn}\b', l) for l in lines)]
    if missing:
        return f"SKIP {ov} (cluster fns not in base .c: {missing[:3]}... — jr-embedded?)"

    si, _ = unit_start(lines, START_FN)
    li, lkind = unit_start(lines, LAST_FN)
    if si is None or li is None:
        return f"ERROR {ov}: boundary fn not found (start={si}, last={li})"
    if lkind != "stub":
        return f"SKIP {ov} ({LAST_FN} is matched inline — cluster not all-stub; carve by hand)"
    # end = first non-blank line after the LAST_FN stub (keeps the after-region fn's forward externs
    # with the after-region, not the cluster).
    ei = li + 1
    while ei < len(lines) and lines[ei].strip() == "":
        ei += 1
    if not (si < li < ei):
        return f"ERROR {ov}: bad boundary order si={si} li={li} ei={ei}"

    header = "\n".join(lines[:header_end(lines)]).rstrip("\n")
    before, cluster, after = lines[:si], lines[si:ei], lines[ei:]

    OLD = f'nonmatchings/{ov}"'
    open(main_c, "w").write("\n".join(before).rstrip("\n") + "\n")
    cluster_body = "\n".join(cluster).replace(OLD, f'nonmatchings/{ov}_o0"')
    open(o0_c, "w").write(header + "\n\n" + cluster_body.rstrip("\n") + "\n")
    after_body = "\n".join(after).replace(OLD, f'nonmatchings/{ov}_o2b"')
    open(o2b_c, "w").write(header + "\n\n" + after_body.rstrip("\n") + "\n")

    # carve the yaml code subseg  [0x0, c, <ov>]  ->  before / o0 cluster / o2b after
    y = open(yaml).read()
    pat = re.compile(r'^(\s*)- \[0x0, c, ' + re.escape(ov) + r'\].*$', re.M)
    m = pat.search(y)
    if not m:
        return f"ERROR {ov}: '- [0x0, c, {ov}]' not found in yaml"
    ind = m.group(1)
    repl = (f'{ind}- [0x0, c, {ov}]  # -O2 before -O0 cluster (file 0x0..0x{LO_FOFF:X})\n'
            f'{ind}- [0x{LO_FOFF:X}, c, {ov}_o0]  # -O0 cluster 0x8013B568..0x8013C98C (0x{LO_FOFF:X}..0x{HI_FOFF:X})\n'
            f'{ind}- [0x{HI_FOFF:X}, c, {ov}_o2b]  # -O2 after -O0 cluster (0x{HI_FOFF:X}..data tail)')
    open(yaml, "w").write(pat.sub(lambda _m: repl, y, count=1))
    ncl = sum(1 for l in cluster if "INCLUDE_ASM" in l)
    return f"OK {ov}: before {len(before)} / cluster {len(cluster)} ({ncl} stubs) / after {len(after)} lines"


if __name__ == "__main__":
    targets = sys.argv[1:]
    if not targets:
        print(__doc__)
        sys.exit(2)
    n_ok = 0
    for ov in targets:
        r = split_overlay(ov)
        if r.startswith("OK"):
            n_ok += 1
        print(r)
    print(f"--- {n_ok}/{len(targets)} carved ---")
