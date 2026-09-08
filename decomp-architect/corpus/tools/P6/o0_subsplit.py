#!/usr/bin/env python3
"""P30 T2 — the CARVE WITHIN A CARVE: route an `-O0` address range inside an `-O2` object.

Some `-O0` regions sit INSIDE an object that is otherwise `-O2` (a jr split, or the main body).
gcc-2.7.2 has no per-function optimize pragma, so opt level is per FILE (§116): the range must be
cut into its own object(s) and named so the Makefile's `-O0` wildcard selects it.

WHAT THIS TOOL EXISTS TO GET RIGHT (cookbook §126, byte-proven):
  **An address range is not an optimization region.** A range selected by address contains everything
  in it — including already-MATCHED functions, whose bodies expand from engine_core.h as
  `DEFINE_func_*()` instantiations (or sit inline) and are compiled `-O2`. Flipping the FILE to `-O0`
  recompiles those too and they stop matching. So the `-O0` bound is

        (address range)  MINUS  (already-matched bodies)

  and a range with K interleaved matched functions needs **K+1** `-O0` sub-regions, not one.

  The contents are derived from the SOURCE ANCHORS (`overlay_src_split.parse_overlay_c`: `asm` =
  unmatched stub, `define`/`def`/`nonmatch` = matched), NEVER from an asm-file scan — a matched
  function emits no `.s`, so a scan of `asm/**/*.s` is structurally blind to exactly the bodies that
  break the flip. That blindness is what made the range look like a clean contiguous run (§124's shape).

The split itself reuses `jr_isolate_all` verbatim (plan / build_new_config / the ascending-unique
validation / repoint_overlays_mk): region naming there is purely positional, so only the cut list is
injected. That keeps source-repartition and `.rodata` carve-repoint semantics on the proven path,
including the one-carve-per-region law (every already-banked jr in the object must also be a cut).

The whole-binary byte-gate remains the sole arbiter (G3/P9). After running this:
    make extract BINARY=<ov> && make build BINARY=<ov>     -> must be BYTE-IDENTICAL
(the split is byte-neutral by construction; a divergence means a bound is wrong), then bank drafts
into the `_o0*` files and gate again, then a full R22 (config changed => T2 blast radius).

Usage:
    tools/o0_subsplit.py <ov> --lo 0x80183CF0 --hi 0x80184920 [--dry-run]
"""
import argparse
import os
import re
import string
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import jr_isolate_all as J          # noqa: E402
import overlay_src_split as oss     # noqa: E402

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
MATCHED_KINDS = {"define", "def", "nonmatch"}      # already carry real C => must stay -O2


def free_letters(ov, n):
    """n unused `<ov>_o0<letter>` suffixes (b is the whale's, so start at c and skip taken ones)."""
    taken = {m.group(1) for m in
             (re.fullmatch(rf"{re.escape(ov)}_o0(\w?)\.c", f)
              for f in os.listdir(os.path.join(REPO, "src", ov))) if m}
    out = []
    for ch in string.ascii_lowercase[2:]:          # c, d, e, ...
        if ch not in taken:
            out.append(ch)
        if len(out) == n:
            return out
    sys.exit(f"o0_subsplit: ran out of free _o0<letter> suffixes for {ov}")


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("ov")
    ap.add_argument("--lo", required=True, help="first vram of the -O0 range (inclusive)")
    ap.add_argument("--hi", required=True, help="first vram AFTER the -O0 range (exclusive)")
    ap.add_argument("--dry-run", action="store_true")
    a = ap.parse_args()

    # MAIN IS NOT AN OVERLAY, AND CRASHING IS NOT REFUSING (P31 S77, R43/R61a). Every tool in this
    # chain is overlay-shaped: jr_isolate_all reads `config/splat.<ov>.yaml` (main's is
    # `config/splat.us.exe.yaml`) and overlay_src_split reads `src/<ov>/` (main's TUs are top-level
    # `src/*.c`). Run on main it died with `FileNotFoundError: config/splat.main.yaml`, which reads
    # as a missing file rather than an unsupported input — the same main-blindness that made
    # draw_waves silently draw ZERO main functions for the whole project (S76). Say so instead.
    if a.ov == "main":
        sys.exit("o0_subsplit: main is NOT SUPPORTED — this chain is overlay-shaped (jr_isolate_all "
                 "wants config/splat.main.yaml, overlay_src_split wants src/main/; main has "
                 "config/splat.us.exe.yaml and top-level src/*.c). Main's -O0 sub-splits are carved "
                 "by hand: cut the code subseg 3 ways in config/splat.us.exe.yaml, split the .rodata "
                 "row if the span's jtbl owners land in different pieces, split the .c to match, and "
                 "add the file to the -O0 glob. The byte-identical rebuild BEFORE banking is the "
                 "check that the bounds are right.")
    ov, lo, hi = a.ov, int(a.lo, 16), int(a.hi, 16)

    p = J.plan(ov)

    def obj_of(v):
        for s, e, nm, li, ind in p["obj_ranges"]:
            if s <= v and (e is None or v < e):
                return nm
        return None

    nm = obj_of(lo)
    if nm is None or obj_of(max(lo, hi - 1)) != nm:
        sys.exit(f"o0_subsplit: [{a.lo}, {a.hi}) does not lie inside ONE code object "
                 f"(lo in {nm}, hi-1 in {obj_of(max(lo, hi - 1))})")
    if nm.endswith(J.O0_SUFFIX) or re.search(r"_o0\w?$", nm):
        sys.exit(f"o0_subsplit: {nm} is ALREADY an -O0 object — nothing to route.")

    # ---- derive the range's contents FROM THE SOURCE (never an asm scan) --------------------
    srcpath = os.path.join(REPO, f"src/{ov}/{nm}.c")
    _hdr, items = oss.parse_overlay_c(open(srcpath).read(), oss.load_ov_syms(ov))
    inrange = sorted([it for it in items if it[0] is not None and lo <= it[0] < hi],
                     key=lambda it: it[0])
    if not inrange:
        sys.exit(f"o0_subsplit: no addressed source anchors in [{a.lo}, {a.hi}) of {nm}")

    stubs = [it for it in inrange if it[2] == "asm"]
    matched = [it for it in inrange if it[2] in MATCHED_KINDS]
    print(f"o0_subsplit {ov}: object {nm}")
    print(f"  range 0x{lo:08X}..0x{hi:08X}: {len(inrange)} anchors "
          f"= {len(stubs)} unmatched stub(s) + {len(matched)} ALREADY-MATCHED (must stay -O2)")
    for ad, nam, kind, _t in matched:
        print(f"    -O2 island: 0x{ad:08X} {nam} [{kind}]")
    if not stubs:
        sys.exit("o0_subsplit: every anchor in the range is already matched — nothing to route.")

    # ---- maximal runs of consecutive UNMATCHED anchors = the -O0 sub-regions ----------------
    runs, cur = [], []
    for it in inrange:
        if it[2] == "asm":
            cur.append(it)
        else:
            if cur:
                runs.append(cur)
            cur = []
    if cur:
        runs.append(cur)

    letters = free_letters(ov, len(runs))
    cuts, renames = set(), {}
    for run, ch in zip(runs, letters):
        start = run[0][0]
        after = next((it[0] for it in inrange if it[0] > run[-1][0]), hi)
        cuts.add(start)
        cuts.add(after)                      # close the region (the next anchor, or hi)
        renames[start] = f"o0{ch}"
        print(f"  -O0 region {ov}_o0{ch}: 0x{start:08X}..0x{after:08X}  ({len(run)} fns)")

    # sanity (this scan IS valid for stubs — only MATCHED fns lack a .s): every -O0 candidate
    # should carry the frame-pointer prologue. Warn, don't refuse: the byte-gate is the arbiter.
    import corpus
    nofp = []
    for run in runs:
        for ad, nam, _k, _t in run:
            ap_ = corpus.asm_path(ov, nam)
            if ap_ and os.path.exists(os.path.join(REPO, ap_)):
                txt = open(os.path.join(REPO, ap_)).read()
                if not re.search(r'addu\s+\$fp,\s*\$sp,\s*\$zero', txt):
                    nofp.append(nam)
    if nofp:
        print(f"  ⚠ {len(nofp)} stub(s) in the -O0 runs lack the frame-pointer prologue "
              f"({nofp[:5]}{'…' if len(nofp) > 5 else ''}) — check the bounds; gate decides.")

    # ---- the one-carve-per-region law: every already-banked jr here must also be cut --------
    _alljr, banked = J.jr_inventory(ov)
    banked_here = [x for x in banked if obj_of(x) == nm]
    allcuts = sorted(cuts | set(banked_here))
    print(f"  banked jr in object: {[hex(x) for x in banked_here]} (forced cuts)")
    print(f"  final cuts: {[hex(c) for c in allcuts]}")

    _orig = J.subseg_name
    J.subseg_name = lambda o, vram: (f"{o}_{renames[vram]}" if vram in renames else _orig(o, vram))
    p["per_obj"] = {nm: allcuts}
    cfg_lines, new_files, carve_renames = J.build_new_config(ov, p)

    # jr_isolate_all's fail-loud ascending/unique validation, verbatim
    code_re = re.compile(r'^\s*- \[(0x[0-9A-Fa-f]+), c, (\w+)\]')
    seen_off, seen_nm = -1, set()
    for ln in cfg_lines:
        m = code_re.match(ln)
        if not m:
            continue
        off, n2 = int(m.group(1), 16), m.group(2)
        if off <= seen_off or n2 in seen_nm:
            sys.exit(f"o0_subsplit: REFUSING corrupt config — [{hex(off)}, {n2}] "
                     f"{'out of order' if off <= seen_off else 'duplicate'}")
        seen_off, seen_nm = off, seen_nm | {n2}

    print(f"  -> {len(new_files)} region .c files; carve repoints: {carve_renames or '(none)'}")
    if a.dry_run:
        print("  [dry-run] nothing written.")
        return
    open(os.path.join(REPO, f"config/splat.{ov}.yaml"), "w").write("\n".join(cfg_lines) + "\n")
    for path, content in new_files.items():
        open(path, "w").write(content)
    J.repoint_overlays_mk(carve_renames, dry=False)
    print(f"  wrote config + region files + overlays.mk.\n"
          f"  NEXT: make extract BINARY={ov} && make build BINARY={ov}  -> must be BYTE-IDENTICAL "
          f"(the split is byte-neutral by construction; a divergence means a bound is wrong).")


if __name__ == "__main__":
    main()
