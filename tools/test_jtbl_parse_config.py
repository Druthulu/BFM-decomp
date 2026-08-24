#!/usr/bin/env python3
"""test_jtbl_parse_config.py — the regression + negative control for jtbl_carve.parse_config.

WHY THIS EXISTS (P31 S58/S59). `parse_config`'s docstring said "the trailing run of {data,
.rodata} pieces after the last `c` piece" and its code said `data_pieces[0]` — the first
data/.rodata piece anywhere in the file. Those agree on 171 configs and disagree on 42, because
the md_* modules open with the §154-A LEADING ISLAND `- [0x0, .rodata, md_XXX]` before their `c`
piece. On those, apply()'s splice `lines[:lo] + region + lines[hi:]` DELETED the `c` line and
wrote the yaml to disk before the tool errored out for unrelated reasons. S58 responded with a
blanket md_*/main refusal in cfg_path; S59 fixed the derivation and lifted it.

Three checks, all read-only (no config on disk is touched — the splice is simulated in memory):

  NC-1 REGRESSION — on every config that is NOT in the corruption class, the fixed derivation
        returns EXACTLY what the historical one returned. The overlay carve pipeline is byte-gated
        and green; a "fix" that moves it is a regression, not a fix. The historical derivation is
        re-implemented below (`_legacy_region_lo`) precisely so this comparison is possible.

  NC-2 THE DEFECT — on every md_* config, the historical derivation is SHOWN to delete a `c`
        piece line (the defect is demonstrated, not asserted from the failure signature), and the
        fixed one is shown to preserve every `c` line.

  NC-3 CLASS FACTS — main resolves to config/splat.us.exe.yaml with file base 0x8000F800 (not the
        yaml's first `vram:` 0x80010000, which reads 0x800 early), and main is NOT in the
        corruption class: its pieces are already [all c ..., data, .rodata, data].

Run: .venv/bin/python tools/test_jtbl_parse_config.py
"""
import glob
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import jtbl_carve as jc                                              # noqa: E402

REPO = jc.REPO
FAIL = []


def alias_of(cfg):
    """binary alias from a config path — 'config/splat.<alias>.yaml', with the EXE's exception."""
    base = os.path.basename(cfg)
    return "main" if base == "splat.us.exe.yaml" else base[len("splat."):-len(".yaml")]


def pieces_of(lines):
    """[(line_idx, indent, off, kind, name)] — the same scan parse_config does."""
    out = []
    for i, ln in enumerate(lines):
        m = jc.PIECE_RE.match(ln)
        if m:
            out.append((i, m.group(1), int(m.group(2), 16), m.group(3), m.group(4)))
    return out


def _legacy_region_lo(pieces):
    """THE HISTORICAL DERIVATION (pre-S59), kept only so NC-1 can compare against it.

    `data_pieces[0]` — the first data/.rodata piece anywhere in the file, regardless of where the
    `c` pieces are."""
    data = [p for p in pieces if p[3] in ("data", ".rodata")]
    return data[0][0] if data else None


def check(cond, msg):
    if not cond:
        FAIL.append(msg)
    return cond


def main():
    cfgs = sorted(glob.glob(os.path.join(REPO, "config/splat.*.yaml")))
    legacy_class, held_class = [], []
    for cfg in cfgs:
        lines = open(cfg).read().splitlines()
        pieces = pieces_of(lines)
        if not [p for p in pieces if p[3] in ("data", ".rodata")]:
            continue                                      # no data region at all — not our subject
        c_idxs = [p[0] for p in pieces if p[3] == "c"]
        lo_legacy = _legacy_region_lo(pieces)
        (legacy_class if (c_idxs and lo_legacy < c_idxs[-1]) else held_class).append(cfg)

    print(f"configs with a data region : {len(legacy_class) + len(held_class)}")
    print(f"  corruption class (md_*)  : {len(legacy_class)}")
    print(f"  contract already held    : {len(held_class)}")
    check(len(legacy_class) == 42, f"NC: expected 42 configs in the corruption class, got {len(legacy_class)}")
    check(all(os.path.basename(c).startswith("splat.md_") for c in legacy_class),
          "NC: the corruption class must be exactly the md_* modules")

    # ---- NC-1: the fix moves nothing outside the corruption class ------------------------------
    moved = []
    for cfg in held_class:
        ov = alias_of(cfg)
        lines = open(cfg).read().splitlines()
        lo_legacy = _legacy_region_lo(pieces_of(lines))
        lo_new = jc.parse_config(ov)[2]
        if lo_legacy != lo_new:
            moved.append((ov, lo_legacy, lo_new))
    check(not moved, f"NC-1 REGRESSION: the region start moved on {moved}")
    print(f"NC-1 regression : {len(held_class)}/{len(held_class)} configs unchanged by the fix")

    # ---- NC-2: the defect, demonstrated, and the fix, demonstrated -----------------------------
    demonstrated, preserved = 0, 0
    for cfg in legacy_class:
        ov = alias_of(cfg)
        lines = open(cfg).read().splitlines()
        pieces = pieces_of(lines)
        c_lines = {ln for i, ln in enumerate(lines) if i in {p[0] for p in pieces if p[3] == "c"}}

        _, _, lo_new, hi_new, tail_start, _, _, _ = jc.parse_config(ov)
        lo_legacy = _legacy_region_lo(pieces)

        # apply() splices lines[:lo] + <regenerated region> + lines[hi:]; a `c` line inside the
        # replaced window is GONE from the file. hi is the same under both derivations.
        legacy_after = set(lines[:lo_legacy]) | set(lines[hi_new:])
        new_after = set(lines[:lo_new]) | set(lines[hi_new:])
        lost_legacy = c_lines - legacy_after
        lost_new = c_lines - new_after
        if lost_legacy:
            demonstrated += 1
        if not lost_new:
            preserved += 1
        check(lost_legacy, f"NC-2 {ov}: the historical derivation was expected to delete a `c` line, it did not")
        check(not lost_new, f"NC-2 {ov}: the FIXED derivation still deletes {sorted(lost_new)}")
        # and the leading island must sit OUTSIDE the region the fix will rewrite
        island = [p for p in pieces if p[3] == ".rodata" and p[2] == 0]
        check(all(p[0] < lo_new for p in island),
              f"NC-2 {ov}: the leading island piece is inside the rewritten region")
        check(tail_start > 0, f"NC-2 {ov}: tail_start 0x{tail_start:x} — the region still starts at the island")
    print(f"NC-2 defect     : {demonstrated}/{len(legacy_class)} md_* configs LOSE a `c` line under the "
          f"historical derivation; {preserved}/{len(legacy_class)} keep every `c` line under the fix")

    # ---- NC-3: main's class facts --------------------------------------------------------------
    check(jc.cfg_path("main").endswith("config/splat.us.exe.yaml"),
          f"NC-3: main resolved to {jc.cfg_path('main')}")
    base = jc.overlay_vram_base("main")
    check(base == 0x8000F800, f"NC-3: main file base is 0x{base:x}, expected 0x8000F800")
    check(all(alias_of(c) != "main" for c in legacy_class), "NC-3: main must NOT be in the corruption class")
    lo_main = jc.parse_config("main")[2]
    lines_main = open(jc.cfg_path("main")).read().splitlines()
    c_last = max(p[0] for p in pieces_of(lines_main) if p[3] == "c")
    check(lo_main > c_last, f"NC-3: main region starts at line {lo_main + 1}, last `c` at {c_last + 1}")
    print(f"NC-3 main       : cfg=config/splat.us.exe.yaml base=0x{base:x} "
          f"region starts line {lo_main + 1} (last `c` line {c_last + 1})")

    if FAIL:
        print("\nFAILED:")
        for f in FAIL:
            print("  -", f)
        return 1
    print("\nALL CHECKS PASS")
    return 0


if __name__ == "__main__":
    sys.exit(main())
