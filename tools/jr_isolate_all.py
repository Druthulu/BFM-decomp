#!/usr/bin/env python3
"""Phase-26 §8b: isolate every jr (switch) function in an overlay into its OWN code
subseg — the one-shot multi-cut resegment that unblocks the Stage-2 heavy-jr-core
harvest (each isolated jr carves its jtbl independently, so banking any core is a
clean fill with no same-subseg collision; cookbook §8/§8b, the whale `_o0b` precedent
generalized).

For each -O2 code object that contains jr-functions, the object is cut right BEFORE
each jr vram:  [gap0][jr1 + trailing non-jr][jr2 + ...] ...  . The leading gap keeps
the object's name; each jr-led region becomes `<ov>_jr_<addr>`. Source is repartitioned
(overlay_src_split, H5) and INCLUDE_ASM stub paths repointed to the new subseg. The 2
already-banked jr (their real-C is PRESERVED) have their `.rodata` carve repointed to
their new `_jr_<addr>` subseg (config piece + overlays.mk --order) — no un-banking, no
metric churn. -O0 objects (`*_o0`, `*_o0b`) are skipped (their new subsegs would lose
the Makefile -O0 flag; the heavy Stage-2 cores are all -O2).

Byte-neutral by construction: the split only reorganizes .text into more objects placed
contiguously in address order (the existing -O0 multi-object precedent), and the carve
bytes are unchanged (only the owning object's NAME changes). `make build` (SHA1) is the
sole arbiter (G3/P9/R22).

    jr_isolate_all.py <ov> [--only func_X,func_Y] [--dry-run]
"""
import argparse
import glob
import json
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import overlay_src_split as oss

REPO = oss.REPO
O0_SUFFIX = ("_o0", "_o0b")


def sh(cmd):
    return subprocess.run(cmd, shell=True, cwd=REPO, capture_output=True, text=True)


def oss_vram(ov):
    txt = open(os.path.join(REPO, f"config/splat.{ov}.yaml")).read()
    m = re.search(r"vram:\s*(0x[0-9A-Fa-f]+)", txt)
    if not m:
        sys.exit(f"jr_isolate_all: no vram in config for {ov}")
    return int(m.group(1), 16)


def code_objects(cfg_lines):
    """[(line_idx, indent, off, name)] for every `- [off, c, name]` code piece, in order."""
    objs = []
    for i, ln in enumerate(cfg_lines):
        m = re.match(r'^(\s*)- \[(0x[0-9A-Fa-f]+),\s*c,\s*(\w+)\]', ln)
        if m:
            objs.append((i, m.group(1), int(m.group(2), 16), m.group(3)))
    return objs


def rodata_carves(cfg_lines):
    """[(line_idx, off, subseg)] for every `.rodata` carve piece."""
    out = []
    for i, ln in enumerate(cfg_lines):
        m = re.match(r'^\s*- \[(0x[0-9A-Fa-f]+),\s*\.rodata,\s*(\w+)\]', ln)
        if m:
            out.append((i, int(m.group(1), 16), m.group(2)))
    return out


def jr_inventory(ov):
    """Return (all_jr:{vram:src_kind}, banked:{vram:func_name}). src_kind in
    {'asm','banked'}. jr = INCLUDE_ASM funcs whose .s references a jtbl_ + the
    already-banked jr (real-C `def`/`define` items whose name is recorded in a
    .run/banked_func_*.json — the exemplar is NOT in its own sibling list, so we
    confirm presence by parsing the source, not by the sibling roster)."""
    asm_jr = {}
    for p in glob.glob(os.path.join(REPO, f"asm/{ov}/nonmatchings/*/*.s")):
        if re.search(r'jtbl_[0-9A-Fa-f]{8}', open(p).read()):
            fn = os.path.basename(p)[:-2]
            if re.fullmatch(r'func_[0-9A-Fa-f]{8}', fn):
                asm_jr[int(fn[5:], 16)] = fn
    # candidate banked-jr names (global roster) -> confirm each is a real-C def here
    cand = set()
    for bj in glob.glob(os.path.join(REPO, ".run/banked_func_*.json")):
        cand.add(os.path.basename(bj)[len("banked_"):-len(".json")])
    realc = {}                                          # addr -> name for def/define items
    syms = oss.load_ov_syms(ov)
    for cf in glob.glob(os.path.join(REPO, f"src/{ov}/*.c")):
        _, items = oss.parse_overlay_c(open(cf).read(), syms)
        for addr, name, kind, _ in items:
            if kind in ("def", "define") and name and addr is not None:
                realc[addr] = name
    banked = {a: nm for a, nm in realc.items() if nm in cand}
    alljr = dict(asm_jr)
    alljr.update({a: "banked" for a in banked})       # marker; name in `banked`
    return alljr, banked


def plan(ov, only=None):
    """Compute the resegment plan without touching disk. Returns a dict."""
    base = oss_vram(ov)
    cfg_lines = open(os.path.join(REPO, f"config/splat.{ov}.yaml")).read().splitlines()
    objs = code_objects(cfg_lines)
    obj_ranges = []                                    # (start_vram, end_vram, name, line_idx, indent)
    for k, (li, ind, off, nm) in enumerate(objs):
        end = objs[k + 1][2] if k + 1 < len(objs) else None
        obj_ranges.append((base + off, (base + end) if end is not None else None, nm, li, ind))

    def obj_of(vram):
        for s, e, nm, li, ind in obj_ranges:
            if s <= vram and (e is None or vram < e):
                return nm
        return None

    alljr, banked = jr_inventory(ov)
    if only:
        only_addrs = {int(x[5:], 16) for x in only if re.fullmatch(r'func_[0-9A-Fa-f]{8}', x)}
        alljr = {a: v for a, v in alljr.items() if a in only_addrs}
        banked = {a: nm for a, nm in banked.items() if a in only_addrs}

    # group jr by their -O2 object (skip -O0 objects + objects with no jr)
    skipped_o0 = []
    per_obj = {}
    for a in sorted(alljr):
        nm = obj_of(a)
        if nm is None:
            continue
        if nm.endswith(O0_SUFFIX):
            skipped_o0.append(a)
            continue
        per_obj.setdefault(nm, []).append(a)

    # banked jr -> its object (for carve repoint)
    banked_obj = {banked[a]: obj_of(a) for a in banked}
    return {
        "base": base, "cfg_lines": cfg_lines, "obj_ranges": obj_ranges,
        "per_obj": per_obj, "banked": banked, "banked_obj": banked_obj,
        "skipped_o0": skipped_o0,
    }


def subseg_name(ov, vram):
    return f"{ov}_jr_{vram:08X}"          # uppercase hex, matching the func_XXXXXXXX convention


def build_new_config(ov, p):
    """Return (new_cfg_lines, new_files:{path:content}, carve_renames:{old_sub:new_sub})."""
    base = p["base"]
    cfg_lines = list(p["cfg_lines"])
    syms = oss.load_ov_syms(ov)

    # 1) source repartition + the config code-region replacement (per object, bottom-up so
    #    line indices stay valid).
    new_files = {}
    replacements = []            # (line_idx, [new config lines])
    carve_renames = {}           # old code-subseg name -> banked jr's new _jr_ subseg
    banked_by_obj = {}
    for fn, obj in p["banked_obj"].items():
        banked_by_obj.setdefault(obj, []).append(fn)

    for s, e, nm, li, ind in p["obj_ranges"]:
        if nm not in p["per_obj"]:
            continue
        cuts = p["per_obj"][nm]                                # jr vrams in this object
        srcpath = os.path.join(REPO, f"src/{ov}/{nm}.c")
        header, regions = _partition(srcpath, cuts, syms)
        # region 0 (lo=None) keeps the object name; each jr-led region -> _jr_<lo>. Regions are
        # processed in address order, accumulating this object's file-scope decls as `ambient` so
        # each region carries the decl context it had in the original single object.
        cfg_block = []
        ambient = []
        for (lo, hi, items) in regions:
            sub = nm if lo is None else subseg_name(ov, lo)
            off = (s if lo is None else lo) - base
            cfg_block.append(f"{ind}- [{hex(off)}, c, {sub}]")
            body = _render_region(header, items, old_sub=nm, new_sub=sub, ambient=ambient)
            new_files[os.path.join(REPO, f"src/{ov}/{sub}.c")] = body
            ambient = ambient + _file_scope_decls(items)      # context for later regions
            # a banked jr leading this region -> its carve must repoint to `sub`
            if lo is not None:
                for fn in banked_by_obj.get(nm, []):
                    if int(fn[5:], 16) == lo:
                        carve_renames[nm] = sub
        replacements.append((li, cfg_block))

    # apply config code-region replacements bottom-up
    for li, block in sorted(replacements, reverse=True):
        cfg_lines[li:li + 1] = block

    # 2) repoint the .rodata carve pieces to the banked jr's new subseg
    for i, ln in enumerate(cfg_lines):
        m = re.match(r'^(\s*- \[0x[0-9A-Fa-f]+,\s*\.rodata,\s*)(\w+)(\].*)$', ln)
        if m and m.group(2) in carve_renames:
            cfg_lines[i] = m.group(1) + carve_renames[m.group(2)] + m.group(3)

    return cfg_lines, new_files, carve_renames


def _partition(srcpath, cuts, syms):
    """overlay_src_split.partition but taking a preloaded syms dict."""
    header, items = oss.parse_overlay_c(open(srcpath).read(), syms)
    if any(it[0] is None and it[2] == "tail" for it in items):
        sys.exit(f"jr_isolate_all: unaddressable content in {srcpath}")
    footer = [it for it in items if it[2] == "footer"]
    addressed = [it for it in items if it[0] is not None]
    cuts = sorted(set(cuts))
    bounds = [None] + cuts + [None]
    regions = []
    for lo, hi in zip(bounds[:-1], bounds[1:]):
        sel = sorted((it for it in addressed
                      if (lo is None or it[0] >= lo) and (hi is None or it[0] < hi)),
                     key=lambda it: it[0])
        regions.append((lo, hi, sel))
    if footer:
        lo, hi, sel = regions[-1]
        regions[-1] = (lo, hi, sel + footer)
    return header, regions


# a hoistable declaration line: an `extern` decl, or a func/data prototype ending in `;`
# with no `{` body. These are legal to REPEAT in C (unlike typedef/struct/enum), so we hoist a
# deduped copy to the region top — every symbol is then declared before any body uses it (a cut can
# strand a use above its in-region decl; the source redundantly re-declares externs per fn-group).
_HOIST_RE = re.compile(
    r'^\s*(?:extern\b.*;'
    r'|[A-Za-z_][\w\*\s]*\b(?:func_[0-9A-Fa-f]{8}|D_[0-9A-Fa-f]{8})\b[^{]*;)\s*(?:/\*.*\*/)?\s*$')


_SYM_RE = re.compile(r'\b((?:D_|func_)[0-9A-Fa-f]{8})\b')
# a decl whose base type is a BUILTIN / include-provided type is safe to hoist to the region
# top; one that names a FILE-LOCAL type (`Vec8`, `struct BigCopy`, ...) must stay where the type
# is defined (hoisting it above the typedef is a parse error), so it is NOT carried as ambient.
_SAFE_TYPE = re.compile(
    r'^\s*(?:extern\s+)?(?:const\s+)?(?:(?:un)?signed\s+)?'
    r'(?:void|char|short|int|long|float|double'
    r'|[su](?:8|16|32|64)|M2C_UNK|MNC_UNK)\b')


def _file_scope_decls(items):
    """[(line, [syms])] for each COL-0 (file-scope) extern/proto decl with a builtin base type,
    in item order (file-local-typed decls are left in place — see _SAFE_TYPE)."""
    out = []
    for _, _, _, text in items:
        for line in text.split("\n"):
            if not line or line[0].isspace():          # col-0 only (block-scope stays put)
                continue
            if "{" in line or "}" in line:
                continue
            if _HOIST_RE.match(line) and _SAFE_TYPE.match(line):
                out.append((line.rstrip(), _SYM_RE.findall(line)))
    return out


def _render_region(header, items, old_sub, new_sub, ambient):
    """Region .c = header + AMBIENT file-scope decls (from earlier regions of this object, in
    original order, deduped by symbol) + the region's items unchanged. Ambient preserves the
    exact decl visibility each function had in the original single object (a cut otherwise
    strands a use above the decl that lived in an earlier region) — byte-neutral (decls emit
    nothing; order preserved). Prepending is always safe: a symbol that has a file-scope decl
    cannot also carry a *different*-typed block-scope shadow (the original would not compile),
    so a same-typed block-scope redeclaration below is compatible."""
    if new_sub != old_sub:
        items = [(a, n, k, oss.rewrite_asm_subseg(t, old_sub, new_sub)) for a, n, k, t in items]
    lines, seen = [], set()
    for line, syms in ambient:
        key = tuple(sorted(syms)) if syms else (line,)
        if key in seen:
            continue
        seen.add(key)
        lines.append(line)
    parts = [header]
    if lines:
        parts.append("/* Phase-26 §8b jr_isolate_all.py: ambient file-scope decls carried from "
                     "earlier code regions of this object (original order, shadow-excluded => "
                     "byte-neutral). */\n" + "\n".join(lines))
    parts.extend(t for _, _, _, t in items)
    return "\n".join(parts) + "\n"


def repoint_overlays_mk(carve_renames, dry):
    mk = os.path.join(REPO, "config/overlays.mk")
    txt = open(mk).read()
    changed = []
    for old_sub, new_sub in carve_renames.items():
        pat = rf'(--order[^#\n]*?){re.escape(old_sub)}\.o'
        if re.search(pat, txt):
            txt = re.sub(pat, lambda m: m.group(1) + new_sub + ".o", txt, count=1)
            changed.append(f"{old_sub}.o -> {new_sub}.o")
    if not dry:
        open(mk, "w").write(txt)
    return changed


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("ov")
    ap.add_argument("--only", help="comma-separated func_XXXX to isolate (default: all -O2 jr)")
    ap.add_argument("--dry-run", action="store_true")
    a = ap.parse_args()
    only = set(a.only.split(",")) if a.only else None

    p = plan(a.ov, only)
    n_jr = sum(len(v) for v in p["per_obj"].values())
    print(f"jr_isolate_all {a.ov}: {n_jr} jr in {len(p['per_obj'])} -O2 objects "
          f"{ {k: len(v) for k, v in p['per_obj'].items()} }")
    if p["skipped_o0"]:
        print(f"  SKIPPED {len(p['skipped_o0'])} jr in -O0 objects: {[hex(x) for x in p['skipped_o0']]}")
    if not p["per_obj"]:
        print("  nothing to isolate.")
        return

    cfg_lines, new_files, carve_renames = build_new_config(a.ov, p)
    mk_changes = repoint_overlays_mk(carve_renames, dry=True)
    print(f"  -> {len(new_files)} region .c files; carve repoints: {carve_renames or '(none)'}")
    for c in mk_changes:
        print(f"     overlays.mk --order: {c}")

    if a.dry_run:
        print("  [dry-run] no files written.")
        return

    # write config, source region files, overlays.mk
    cfg_path = os.path.join(REPO, f"config/splat.{a.ov}.yaml")
    open(cfg_path, "w").write("\n".join(cfg_lines) + "\n")
    # remove the original per-object .c files that were replaced (region 0 rewrites them;
    # extra regions are new — but a stale original with the OLD single-object content would
    # shadow nothing since we overwrite region 0 to the same path). Write all region files:
    for path, content in new_files.items():
        open(path, "w").write(content)
    repoint_overlays_mk(carve_renames, dry=False)
    print(f"  wrote config + {len(new_files)} region files + overlays.mk. Run `make extract "
          f"BINARY={a.ov} && make build BINARY={a.ov}` to byte-gate (R22).")


if __name__ == "__main__":
    main()
