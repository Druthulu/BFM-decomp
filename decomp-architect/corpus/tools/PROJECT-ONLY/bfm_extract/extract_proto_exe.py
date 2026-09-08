"""Extract a main executable from a Brave Fencer Musashi PROTOTYPE disc.

Companion to ``extract_exe.py``, which is deliberately retail-locked: it hard-
validates ``SLUS_007.26``'s exact size, SHA1, and PS-EXE header field *values*.
The prototypes differ from retail in all three, and one of them hides its real
executable in a subdirectory, so a separate tool is cleaner than loosening the
retail validator:

* Sep-8 1998 "Musashi Master"  -> root ``SLUS_007.26``  (~413,696 B, near-retail)
* Aug-31 1998 "Musashi Demo"   -> ``MUSASHI/USA_DEMO.EXE`` (415,744 B); the root
  ``LAUNCH.EXE`` is only a bootloader.

This tool reuses the general ``iso9660`` reader (which knows nothing about any
specific file), supports an optional ``--dir`` subdirectory path, and validates
only the ``PS-X EXE`` magic -- the header fields and SHA1 are printed for the
record (each header field is compared against retail's value purely as
information, so the diff is visible at a glance).

ROM-derived output under ``extracted/`` is gitignored; never commit the proto
binaries (the discs in ``disks/`` are gitignored and reproduce them).

Examples (run from the repo root)::

    # Sep-8 Master (root SLUS_007.26)
    python3 tools/bfm_extract/extract_proto_exe.py \\
        --bin "disks/Brave Fencer Musashi (Sep 8, 1998 prototype)/PSX - Musashi Master.img" \\
        --exe-name SLUS_007.26 --out extracted/proto/sep8_SLUS_007.26

    # Aug-31 Demo (MUSASHI/USA_DEMO.EXE)
    python3 tools/bfm_extract/extract_proto_exe.py \\
        --bin "disks/Brave Fencer Musashi (Aug 31, 1998 prototype)/PSX - Musashi Demo.img" \\
        --dir MUSASHI --exe-name USA_DEMO.EXE --out extracted/proto/aug31_USA_DEMO.EXE

    # List a directory (root, or a subdir via --dir) and exit
    python3 tools/bfm_extract/extract_proto_exe.py --bin <img> --list
    python3 tools/bfm_extract/extract_proto_exe.py --bin <img> --dir MUSASHI --list
"""

from __future__ import annotations

import argparse
import hashlib
import sys
from pathlib import Path

# Allow running as a plain script as well as a module (mirrors extract_exe.py).
try:
    from .iso9660 import Iso9660Image, Iso9660Error
    from .extract_exe import PS_EXE_MAGIC, EXPECTED_HEADER_FIELDS, _u32
except ImportError:  # pragma: no cover - exercised only as a loose script
    sys.path.insert(0, str(Path(__file__).resolve().parent))
    from iso9660 import Iso9660Image, Iso9660Error  # type: ignore
    from extract_exe import PS_EXE_MAGIC, EXPECTED_HEADER_FIELDS, _u32  # type: ignore


def resolve_dir(img: Iso9660Image, dirname: str | None) -> "FileRecord | None":  # noqa: F821
    """Return the FileRecord for a named subdirectory, or None for the root."""
    if not dirname:
        return None
    rec = img.find(dirname)
    if rec is None or not rec.is_dir:
        raise Iso9660Error(f"subdirectory not found: {dirname!r}")
    return rec


def cmd_list(img: Iso9660Image, directory) -> int:
    where = "<root>" if directory is None else directory.name
    files = img.list_files(directory)
    print(f"Volume: {img.volume_id!r}  dir={where}  ({len(files)} entries)")
    print(f"{'LBA':>7}  {'SIZE':>11}  {'DIR':>3}  NAME")
    for rec in files:
        print(
            f"{rec.lba:>7}  {rec.size:>11}  "
            f"{'yes' if rec.is_dir else '  -':>3}  {rec.raw_name}"
        )
    return 0


def report_header(data: bytes) -> bool:
    """Print the PS-EXE magic + header fields. Returns True iff the magic is valid.

    Header field values are shown against retail's for context ('same as retail'
    vs 'differs') -- this is informational only; a proto is expected to differ.
    """
    print("\nPS-EXE header (field values compared to retail SLUS_007.26 for context):")
    magic = data[: len(PS_EXE_MAGIC)]
    magic_ok = magic == PS_EXE_MAGIC
    print(f"  [{'PASS' if magic_ok else 'FAIL'}] magic 'PS-X EXE'  found {magic!r}")
    for label, off, retail in EXPECTED_HEADER_FIELDS:
        actual = _u32(data, off) if len(data) >= off + 4 else None
        if actual is None:
            print(f"  [ -- ] {label:<8} @0x{off:02X} = <truncated>")
            continue
        tag = "same as retail" if actual == retail else f"differs (retail 0x{retail:08X})"
        print(f"  [info] {label:<8} @0x{off:02X} = 0x{actual:08X}  ({tag})")
    return magic_ok


def cmd_extract(img: Iso9660Image, directory, exe_name: str, out_path: Path) -> int:
    rec = img.find(exe_name, directory)
    where = "<root>" if directory is None else directory.name
    if rec is None:
        print(f"FAIL: {exe_name!r} not found in {where}", file=sys.stderr)
        return 1
    if rec.is_dir:
        print(f"FAIL: {exe_name!r} is a directory, not a file", file=sys.stderr)
        return 1
    print(f"Located {rec.raw_name} in {where} at LBA {rec.lba}, size {rec.size} bytes")

    data = img.read_extent(rec.lba, rec.size)
    out_path.parent.mkdir(parents=True, exist_ok=True)
    out_path.write_bytes(data)
    print(f"Wrote {len(data)} bytes -> {out_path}")

    magic_ok = report_header(data)
    sha1 = hashlib.sha1(data).hexdigest()
    print(f"\nsize: {len(data)} bytes")
    print(f"SHA1: {sha1}")

    if magic_ok:
        print("\nRESULT: PASS - PS-X EXE extracted (magic verified).")
        return 0
    print("\nRESULT: FAIL - extracted file is not a PS-X EXE.", file=sys.stderr)
    return 1


def parse_args(argv: list[str] | None = None) -> argparse.Namespace:
    p = argparse.ArgumentParser(
        description="Extract a main EXE from a BFM prototype disc (magic-only validation).",
    )
    p.add_argument("--bin", type=Path, required=True, help="Path to the proto MODE2/2352 data track (.img/.bin).")
    p.add_argument("--dir", dest="subdir", default=None, help="Subdirectory holding the EXE (e.g. MUSASHI). Default: root.")
    p.add_argument("--exe-name", default=None, help="EXE file name to extract (e.g. SLUS_007.26, USA_DEMO.EXE).")
    p.add_argument("--out", type=Path, default=None, help="Output path for the extracted executable.")
    p.add_argument("--list", action="store_true", help="List the directory (root, or --dir) and exit (no extraction).")
    return p.parse_args(argv)


def main(argv: list[str] | None = None) -> int:
    args = parse_args(argv)
    try:
        with Iso9660Image(args.bin) as img:
            directory = resolve_dir(img, args.subdir)
            if args.list:
                return cmd_list(img, directory)
            if not args.exe_name or args.out is None:
                print("ERROR: --exe-name and --out are required (or use --list).", file=sys.stderr)
                return 2
            return cmd_extract(img, directory, args.exe_name, args.out)
    except Iso9660Error as e:
        print(f"ERROR: {e}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    raise SystemExit(main())
