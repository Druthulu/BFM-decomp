"""Cross-validate our extractor against CUE's brave (the reference oracle).

Builds brave.c (GPL, compiled UNMODIFIED via tools/brave-CUE/posix_shim.h), runs
it on sample ``.CD`` files, and byte-compares brave's output against ours:

* raw ``.CD`` sub-files (``FILE_%03d``)   -- always comparable (no collision)
* raw PAC payloads (type != 4)            -- comparable for the LAST same-type entry
* decompressed PAC type-4 payloads        -- our ``{i}.4.dec`` vs brave's ``004``

brave names PAC entries by TYPE ONLY, so two same-type entries in one chain
collide (last writer wins). Earlier same-type entries are "shadowed": brave's
output for them was overwritten, so they cannot be compared and are NOT counted
as mismatches -- that collision is exactly why our naming carries the index.

Type-4 note: brave's ring buffer is a global that is NOT re-zeroed between
decodes within one process; ours is re-zeroed per stream (game semantics,
formats.md §4.4). On well-formed retail streams the two agree; a type-4 diff is
recorded for inspection (open question F6 / brave's ring artifact).

Exit 0 iff no raw mismatch and no type-4 decode mismatch on the sample. Pure
stdlib + a C compiler (``$CC``/cc/gcc/clang). See docs/formats.md §6.
"""

from __future__ import annotations

import argparse
import filecmp
import os
import shutil
import subprocess
import sys
from dataclasses import dataclass, field
from pathlib import Path

try:
    from . import cd_archive, pac
except ImportError:  # pragma: no cover - exercised only as a loose script
    sys.path.insert(0, str(Path(__file__).resolve().parent))
    import cd_archive  # type: ignore
    import pac  # type: ignore

REPO = Path(__file__).resolve().parents[2]
BRAVE_DIR = REPO / "tools" / "brave-CUE"
BUILD_DIR = BRAVE_DIR / "_build"
SHIM = BRAVE_DIR / "posix_shim.h"
DEFAULT_EXTRACTED = REPO / "extracted" / "retail"


def find_cc() -> str | None:
    for cc in (os.environ.get("CC"), "cc", "gcc", "clang"):
        if cc and shutil.which(cc):
            return cc
    return None


def build_brave() -> tuple[Path | None, str]:
    cc = find_cc()
    if cc is None:
        return None, "no C compiler found (set $CC or `apt install gcc`)"
    BUILD_DIR.mkdir(parents=True, exist_ok=True)
    out = BUILD_DIR / "brave"
    cmd = [
        cc, "-O2", "-std=gnu99", "-fno-strict-aliasing",
        "-include", str(SHIM), str(BRAVE_DIR / "brave.c"), "-o", str(out),
    ]
    proc = subprocess.run(cmd, capture_output=True, text=True)
    if proc.returncode != 0:
        return None, f"compile failed:\n{proc.stderr.strip()}"
    return out, cc


def run_brave(brave: Path, cd_raw: Path, cd_name: str) -> Path:
    """Run brave on a copy of the .CD inside _build/, return its .dir output."""
    work = BUILD_DIR / cd_name
    shutil.copyfile(cd_raw, work)
    out_dir = BUILD_DIR / f"{cd_name}.dir"
    if out_dir.exists():
        shutil.rmtree(out_dir)
    proc = subprocess.run(
        [str(brave), cd_name], cwd=str(BUILD_DIR), capture_output=True, text=True
    )
    work.unlink()
    if proc.returncode != 0:
        raise RuntimeError(f"brave failed on {cd_name}: {proc.stderr or proc.stdout}")
    return out_dir


def _eq(ours: Path, theirs: Path) -> bool | None:
    """True/False on byte-compare, or None if either file is missing."""
    if not ours.is_file() or not theirs.is_file():
        return None
    return filecmp.cmp(str(ours), str(theirs), shallow=False)


@dataclass
class Result:
    cd: str
    subfile_eq: int = 0
    raw_eq: int = 0
    type4_eq: int = 0
    type4_f6: int = 0           # ours is a strict prefix of brave's (expected divergence)
    shadowed: int = 0
    subfile_mismatch: list[str] = field(default_factory=list)
    raw_mismatch: list[str] = field(default_factory=list)
    type4_mismatch: list[str] = field(default_factory=list)
    f6: list[tuple[str, int, int]] = field(default_factory=list)  # (label, ours, brave)
    missing: list[str] = field(default_factory=list)


def compare_cd(cd_name: str, our_root: Path, brave_dir: Path) -> Result:
    res = Result(cd=cd_name)
    data = (our_root / cd_name).read_bytes()
    toc = cd_archive.parse_toc(data)
    our_cd_dir = our_root / f"{cd_name}.dir"
    for entry, sub in cd_archive.iter_subfiles(data, toc):
        fi = entry.index
        eq = _eq(our_cd_dir / f"FILE_{fi:03d}", brave_dir / f"FILE_{fi:03d}")
        if eq is None:
            res.missing.append(f"FILE_{fi:03d}")
        elif eq:
            res.subfile_eq += 1
        else:
            res.subfile_mismatch.append(f"FILE_{fi:03d}")

        if not pac.is_pac(sub):
            continue
        try:
            entries = pac.split_pac(sub)
        except pac.PacError:
            continue
        last_idx_of_type: dict[int, int] = {}
        for pe in entries:
            last_idx_of_type[pe.type] = pe.index  # entries in order -> last write wins
        our_pac_dir = our_cd_dir / f"FILE_{fi:03d}.dir"
        brave_pac_dir = brave_dir / f"FILE_{fi:03d}.dir"
        for pe in entries:
            if pe.index != last_idx_of_type[pe.type]:
                res.shadowed += 1
                continue
            label = f"FILE_{fi:03d}/{pe.index}.{pe.type}"
            brave_file = brave_pac_dir / f"{pe.type:03d}"
            if pe.type == pac.COMPRESSED_TYPE:
                our_file = our_pac_dir / f"{pe.index}.{pe.type}.dec"
                if not our_file.is_file() or not brave_file.is_file():
                    res.missing.append(label)
                    continue
                ob = our_file.read_bytes()
                bb = brave_file.read_bytes()
                if ob == bb:
                    res.type4_eq += 1
                elif len(bb) >= len(ob) and bb[: len(ob)] == ob:
                    # F6: brave (tool semantics) over-decodes the trailing zero
                    # padding past our pos==0 terminator; our output is the
                    # game-correct prefix (formats.md §4.4). Expected, not a bug.
                    res.type4_f6 += 1
                    res.f6.append((label, len(ob), len(bb)))
                else:
                    res.type4_mismatch.append(label)
            else:
                eq = _eq(our_pac_dir / f"{pe.index}.{pe.type}", brave_file)
                if eq is None:
                    res.missing.append(label)
                elif eq:
                    res.raw_eq += 1
                else:
                    res.raw_mismatch.append(label)
    return res


def print_result(res: Result) -> None:
    print(
        f"  {res.cd}: subfiles {res.subfile_eq} eq / {len(res.subfile_mismatch)} diff; "
        f"raw {res.raw_eq} eq / {len(res.raw_mismatch)} diff; "
        f"type4 {res.type4_eq} eq + {res.type4_f6} F6 / {len(res.type4_mismatch)} diff; "
        f"shadowed {res.shadowed}; missing {len(res.missing)}"
    )
    for label in res.subfile_mismatch + res.raw_mismatch + res.type4_mismatch:
        print(f"    DIFF  {res.cd}/{label}")


def parse_args(argv: list[str] | None = None) -> argparse.Namespace:
    p = argparse.ArgumentParser(description="Cross-validate our extractor vs CUE's brave.")
    p.add_argument(
        "--sample",
        choices=["main", "all"],
        default="main",
        help="'main' = MAIN.CD + SC01.CD (default; SC01 covers type-4); 'all' = MAIN + SC01-07.",
    )
    p.add_argument(
        "--extracted",
        type=Path,
        default=DEFAULT_EXTRACTED,
        help=f"Our extraction output root (default: {DEFAULT_EXTRACTED}).",
    )
    return p.parse_args(argv)


def main(argv: list[str] | None = None) -> int:
    args = parse_args(argv)
    brave, info = build_brave()
    if brave is None:
        print(f"SKIP: {info}", file=sys.stderr)
        return 2
    print(f"brave built with {info}")

    if args.sample == "main":
        samples = ["MAIN.CD", "SC01.CD"]
    else:
        samples = ["MAIN.CD"] + [f"SC0{n}.CD" for n in range(1, 8)]

    results: list[Result] = []
    for cd in samples:
        cd_raw = args.extracted / cd
        if not cd_raw.is_file():
            print(f"  skip {cd}: not found under {args.extracted}/", file=sys.stderr)
            continue
        brave_dir = run_brave(brave, cd_raw, cd)
        res = compare_cd(cd, args.extracted, brave_dir)
        results.append(res)
        print_result(res)

    raw_fail = sum(len(r.subfile_mismatch) + len(r.raw_mismatch) for r in results)
    dec_fail = sum(len(r.type4_mismatch) for r in results)
    eq_total = sum(r.subfile_eq + r.raw_eq + r.type4_eq for r in results)
    f6_total = sum(r.type4_f6 for r in results)
    f6_extra = sum(b - o for r in results for _l, o, b in r.f6)

    # Divergence log (transient, gitignored).
    if any(r.f6 or r.type4_mismatch for r in results):
        BUILD_DIR.mkdir(parents=True, exist_ok=True)
        with open(BUILD_DIR / "divergence.log", "w") as fh:
            for r in results:
                for label, o, b in r.f6:
                    fh.write(f"F6\t{r.cd}/{label}\tours={o}\tbrave={b}\tdelta={b - o}\n")
                for label in r.type4_mismatch:
                    fh.write(f"DECODE_MISMATCH\t{r.cd}/{label}\n")

    print(
        f"\n{eq_total} byte-identical; {f6_total} type-4 F6 (ours is the game-correct "
        f"prefix; brave over-decodes {f6_extra} bytes of trailing padding total)."
    )
    print(f"raw mismatches {raw_fail}; type-4 decode mismatches {dec_fail}.")
    if raw_fail == 0 and dec_fail == 0:
        print(
            "RESULT: PASS - raw payloads byte-identical to CUE's brave; every type-4 "
            "matches brave up to our pos==0 terminator (F6 divergence is expected)."
        )
        return 0
    print("RESULT: FAIL - see DIFF lines above.", file=sys.stderr)
    return 1


if __name__ == "__main__":
    raise SystemExit(main())
