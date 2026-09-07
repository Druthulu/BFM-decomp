#!/usr/bin/env python3
"""main_seed_ends.py — the EXE's game-code function boundaries, DERIVED from the build (P33 A2, R33).

Emits `0xVRAM NINS` per function (the two-column `--seeds` form tools/sig_image.py accepts, where a
seeded nins is authoritative) for every function in main's GAME-CODE objects:

  * the `.text` input sections of the link map (build/us/SLUS_007.26.map) give each object's vram
    and size — the same map the byte-identical link wrote, so the numbers are the build's own;
  * objects that are LINKED PsyQ subsegs (progress._main_linked_segs_from_makefile — the Makefile's
    psyq_integrate stub lists, R33) or that live under build/psyq/ are skipped: Sony's objects are
    outside the game-code denominator whether the machine linked the real SDK objects or the
    INCLUDE_ASM fallback tiles;
  * inside one object `.text` is contiguous code — the interleaved rodata islands and the linked
    library blocks sit BETWEEN objects — so slicing at the object's own `nm` function symbols, with
    the last function ending at the section size, is exact. No func_end heuristic, no Ghidra.

Why this exists: main's only whole-EXE sig was Ghidra's (.run/sig.SLUS_007.26.jsonl, 2026-08-05),
which a public clone cannot regenerate and whose flow-derived boundary on FUN_80023bf0 is 22 ins
short (P31 S79: the corrected game-code denominator is 41,556, the digest printed 41,534). The old
`make sig-main` seeded from `corpus.py main --seed-ends` = the open STUB list, which is empty at
100% — a sig of nothing.

Coverage assertions (R32 — a silent skip is a defect): every game-code `.text` section is
non-empty and 4-aligned, starts with a function symbol at offset 0, and its functions tile it
exactly; every object the map lists is either counted, LINKED-skipped, or psyq-skipped, and all
three counts are printed with the instruction totals (R41). Any object counted from outside
build/src/ is named, so an unexpected code source cannot slip in unnoticed (R14).
"""
import argparse
import pathlib
import re
import subprocess
import sys

ROOT = pathlib.Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))

NM = "mipsel-linux-gnu-nm"
# gas emits these two at .text+0 for every gcc-2.7.2 TU; they are markers, not functions.
NOT_FUNCS = {"__gnu_compiled_c", "gcc2_compiled."}
MAP_TEXT = re.compile(r"^\s*\.text\s+(0x[0-9a-fA-F]+)\s+(0x[0-9a-fA-F]+)\s+(\S+\.o)\s*$")
MAP_TEXT_WRAPPED = re.compile(r"^\s*\.text\s*$")
MAP_CONT = re.compile(r"^\s+(0x[0-9a-fA-F]+)\s+(0x[0-9a-fA-F]+)\s+(\S+\.o)\s*$")


def text_sections(map_path):
    """[(vram, size, obj_path)] for every `.text` input section in a GNU ld map. A long object
    name makes ld wrap the record onto the next line; both forms are read."""
    out, lines = [], map_path.read_text(errors="replace").splitlines()
    i = 0
    while i < len(lines):
        m = MAP_TEXT.match(lines[i])
        if m:
            out.append((int(m.group(1), 16), int(m.group(2), 16), m.group(3)))
        elif MAP_TEXT_WRAPPED.match(lines[i]) and i + 1 < len(lines):
            m2 = MAP_CONT.match(lines[i + 1])
            if m2:
                out.append((int(m2.group(1), 16), int(m2.group(2), 16), m2.group(3)))
                i += 1
        i += 1
    return out


def object_functions(obj_path):
    """[(offset, name)] of the function symbols in an object's .text, sorted, one per offset."""
    res = subprocess.run([NM, "-n", "--defined-only", str(obj_path)], capture_output=True, text=True)
    if res.returncode != 0:
        sys.exit(f"main_seed_ends: {NM} failed on {obj_path}: {res.stderr.strip()}")
    seen, funcs = set(), []
    for ln in res.stdout.splitlines():
        parts = ln.split()
        if len(parts) != 3 or parts[1] not in ("T", "t"):
            continue
        off, name = int(parts[0], 16), parts[2]
        if name in NOT_FUNCS or name.startswith((".L", "$L")):
            continue
        if off in seen:                       # an alias for the same entry — one function
            continue
        seen.add(off)
        funcs.append((off, name))
    funcs.sort()
    return funcs


def derive(map_path, repo):
    import progress
    linked = progress._main_linked_segs_from_makefile()
    rows, n_linked, n_psyq, n_code, foreign = [], 0, 0, 0, []
    for vram, size, obj in text_sections(map_path):
        if size == 0:
            continue
        stem = pathlib.Path(obj).stem
        if obj.startswith("build/psyq/"):
            n_psyq += 1
            continue
        if stem in linked:
            n_linked += 1
            continue
        if size % 4:
            sys.exit(f"main_seed_ends: {obj} .text size {size:#x} is not 4-aligned")
        p = repo / obj
        if not p.exists():
            sys.exit(f"main_seed_ends: {obj} listed in the map but absent on disk — rebuild main")
        funcs = object_functions(p)
        if not funcs or funcs[0][0] != 0:
            sys.exit(f"main_seed_ends: {obj} .text does not start with a function symbol "
                     f"(first symbol at {funcs[0][0] if funcs else 'none'}) — bytes owned by no function")
        if not obj.startswith("build/src/"):
            foreign.append(obj)
        n_code += 1
        for i, (off, name) in enumerate(funcs):
            end = funcs[i + 1][0] if i + 1 < len(funcs) else size
            if end <= off or (end - off) % 4:
                sys.exit(f"main_seed_ends: {obj}:{name} bad extent {off:#x}..{end:#x}")
            rows.append((vram + off, (end - off) // 4, name))
    rows.sort()
    addrs = [a for a, _, _ in rows]
    if len(set(addrs)) != len(addrs):
        sys.exit("main_seed_ends: duplicate vram across objects — the map and the objects disagree")
    return rows, n_code, n_linked, n_psyq, foreign


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--map", default="build/us/SLUS_007.26.map", help="the main link map")
    ap.add_argument("--out", default=None, help="write `0xVRAM NINS` lines here (default: stdout)")
    a = ap.parse_args()
    map_path = pathlib.Path(a.map)
    if not map_path.is_absolute():
        map_path = ROOT / map_path
    if not map_path.exists():
        sys.exit(f"main_seed_ends: no link map at {map_path} — run `make check BINARY=main` first")
    rows, n_code, n_linked, n_psyq, foreign = derive(map_path, ROOT)
    text = "".join(f"0x{a:08X} {n}\n" for a, n, _ in rows)
    if a.out:
        pathlib.Path(a.out).write_text(text)
    else:
        sys.stdout.write(text)
    tot = sum(n for _, n, _ in rows)
    print(f"main_seed_ends: {len(rows)} functions / {tot} ins from {n_code} game-code objects "
          f"(skipped {n_linked} LINKED subseg objects + {n_psyq} build/psyq objects)"
          + (f"; NOTE code counted from outside build/src/: {', '.join(foreign)}" if foreign else ""),
          file=sys.stderr)


if __name__ == "__main__":
    main()
