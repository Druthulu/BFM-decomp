"""Phase 1 CLI: extract and validate the BFM main executable (SLUS_007.26).

Walks the ISO9660 file system on the MODE2/2352 data track (it does NOT use a
hardcoded byte offset), extracts SLUS_007.26 verbatim -- including its 2048-byte
PS-EXE header, which ghidra_psx_ldr needs -- writes it to a gitignored output
path, then validates the PS-EXE header fields and the exact file size and prints
a PASS/FAIL report plus the SHA1 of the extracted file.

Run from the repo root (use ``python3`` on Linux/WSL)::

    python tools/bfm_extract/extract_exe.py
    python tools/bfm_extract/extract_exe.py --list
    python tools/bfm_extract/extract_exe.py --verify-disc
    python tools/bfm_extract/extract_exe.py --bin path/to/track.bin --out path/out

Output under ``extracted/`` is ROM-derived and is gitignored on purpose; it must
never be committed.
"""

from __future__ import annotations

import argparse
import hashlib
import struct
import sys
import zlib
from pathlib import Path

# Allow running as a plain script (``python tools/bfm_extract/extract_exe.py``)
# as well as a module; fall back to a path-relative import in the script case.
try:
    from .iso9660 import Iso9660Image, Iso9660Error
except ImportError:  # pragma: no cover - exercised only as a loose script
    sys.path.insert(0, str(Path(__file__).resolve().parent))
    from iso9660 import Iso9660Image, Iso9660Error  # type: ignore

# --- Known-good facts for the BFM USA dump ----------------------------------

DEFAULT_BIN = (
    Path("Brave Fencer Musashi (USA)")
    / "Brave Fencer Musashi (USA) (Track 1).bin"
)
DEFAULT_OUT = Path("extracted") / "SLUS_007.26"

EXE_NAME = "SLUS_007.26"
EXPECTED_SIZE = 0x65000  # 413,696 bytes, header included
# SHA1 of the extracted SLUS_007.26 (stable, independently reproduced from raw
# sectors in Phase 1). Not publicly documented; used as the full-disc round-trip
# anchor by extract.py.
EXPECTED_EXE_SHA1 = "143dbb89f34491258bbc27810d0a12ec8b43a8dd"

PS_EXE_MAGIC = b"PS-X EXE"

# Redump-published Track-1 hashes for SLUS-00726 (USA). The canonical retail
# disc has build date 1998-08-25. Matching these proves the local dump is the
# canonical redump dump, which transitively validates the extracted EXE (the
# EXE's own SHA1 is not publicly documented).
REDUMP_TRACK1_SHA1 = "b44f0f0a19936f23b26188b658e13201a6a9c211"
REDUMP_TRACK1_CRC32 = "c238191b"

HASH_CHUNK = 1 << 20  # 1 MiB streaming reads; never load the ~348 MB BIN whole

# (label, header byte offset, expected little-endian u32 value)
EXPECTED_HEADER_FIELDS = [
    ("pc0",    0x10, 0x80010000),
    ("gp0",    0x14, 0x00000000),
    ("t_addr", 0x18, 0x80010000),
    ("t_size", 0x1C, 0x00064800),
    ("sp_base", 0x30, 0x801FFFF0),
]


def _u32(buf: bytes, off: int) -> int:
    return struct.unpack_from("<I", buf, off)[0]


def validate_ps_exe(data: bytes) -> list[tuple[str, bool, str]]:
    """Check magic, the five header fields, and the total size.

    Returns a list of (check name, passed, detail) tuples.
    """
    checks: list[tuple[str, bool, str]] = []

    magic = data[: len(PS_EXE_MAGIC)]
    checks.append(
        (
            "magic 'PS-X EXE'",
            magic == PS_EXE_MAGIC,
            f"found {magic!r}",
        )
    )

    for label, off, expected in EXPECTED_HEADER_FIELDS:
        actual = _u32(data, off) if len(data) >= off + 4 else None
        ok = actual == expected
        detail = (
            f"@0x{off:02X} = 0x{actual:08X} (expected 0x{expected:08X})"
            if actual is not None
            else f"@0x{off:02X} = <truncated>"
        )
        checks.append((label, ok, detail))

    checks.append(
        (
            "size == 0x65000",
            len(data) == EXPECTED_SIZE,
            f"{len(data)} bytes (expected {EXPECTED_SIZE})",
        )
    )
    return checks


def parse_args(argv: list[str] | None = None) -> argparse.Namespace:
    p = argparse.ArgumentParser(
        description="Extract and validate the BFM main executable (SLUS_007.26).",
    )
    p.add_argument(
        "--bin",
        type=Path,
        default=DEFAULT_BIN,
        help=f"Path to the MODE2/2352 data-track BIN (default: {DEFAULT_BIN}).",
    )
    p.add_argument(
        "--out",
        type=Path,
        default=DEFAULT_OUT,
        help=f"Output path for the extracted executable (default: {DEFAULT_OUT}).",
    )
    p.add_argument(
        "--list",
        action="store_true",
        help="List the root directory and exit (no extraction).",
    )
    p.add_argument(
        "--verify-disc",
        action="store_true",
        help=(
            "Hash the entire Track-1 BIN and compare against redump's "
            "published SHA1/CRC32, then exit (no extraction)."
        ),
    )
    return p.parse_args(argv)


def cmd_list(img: Iso9660Image) -> int:
    files = img.list_files()
    print(f"Volume: {img.volume_id!r}  ({len(files)} root entries)")
    print(f"{'LBA':>7}  {'SIZE':>11}  {'DIR':>3}  NAME")
    for rec in files:
        print(
            f"{rec.lba:>7}  {rec.size:>11}  "
            f"{'yes' if rec.is_dir else '  -':>3}  {rec.raw_name}"
        )
    return 0


def cmd_extract(img: Iso9660Image, out_path: Path) -> int:
    rec = img.find(EXE_NAME)
    if rec is None:
        print(f"FAIL: {EXE_NAME} not found in the ISO root directory", file=sys.stderr)
        return 1
    print(f"Located {rec.raw_name} at LBA {rec.lba}, size {rec.size} bytes")

    data = img.read_extent(rec.lba, rec.size)

    out_path.parent.mkdir(parents=True, exist_ok=True)
    out_path.write_bytes(data)
    print(f"Wrote {len(data)} bytes -> {out_path}")

    # --- validation report ---
    print("\nPS-EXE validation:")
    checks = validate_ps_exe(data)
    all_ok = True
    for name, ok, detail in checks:
        status = "PASS" if ok else "FAIL"
        all_ok = all_ok and ok
        print(f"  [{status}] {name:<16} {detail}")

    sha1 = hashlib.sha1(data).hexdigest()
    print(f"\nSHA1: {sha1}")

    if all_ok:
        print("\nRESULT: PASS - all PS-EXE header and size checks passed.")
        return 0
    print("\nRESULT: FAIL - one or more validation checks failed.", file=sys.stderr)
    return 1


def cmd_verify_disc(bin_path: Path) -> int:
    """Hash the entire Track-1 BIN and compare against redump's published values.

    Streams the ~348 MB file in fixed-size chunks (never loaded whole) and
    computes both SHA1 and CRC32 in one pass. A PASS means the dump is the
    canonical redump dump (build date 1998-08-25), which transitively validates
    the extracted EXE.
    """
    if not bin_path.is_file():
        print(f"ERROR: BIN data track not found: {bin_path}", file=sys.stderr)
        return 2

    sha1 = hashlib.sha1()
    crc32 = 0
    total = 0
    with open(bin_path, "rb") as fh:
        while True:
            chunk = fh.read(HASH_CHUNK)
            if not chunk:
                break
            sha1.update(chunk)
            crc32 = zlib.crc32(chunk, crc32)
            total += len(chunk)

    actual_sha1 = sha1.hexdigest()
    actual_crc32 = f"{crc32 & 0xFFFFFFFF:08x}"

    print(f"Track 1: {bin_path}")
    print(f"  size  : {total} bytes")

    sha1_ok = actual_sha1 == REDUMP_TRACK1_SHA1
    crc32_ok = actual_crc32 == REDUMP_TRACK1_CRC32
    print(
        f"  [{'PASS' if sha1_ok else 'FAIL'}] SHA1  {actual_sha1} "
        f"(redump {REDUMP_TRACK1_SHA1})"
    )
    print(
        f"  [{'PASS' if crc32_ok else 'FAIL'}] CRC32 {actual_crc32} "
        f"(redump {REDUMP_TRACK1_CRC32})"
    )

    if sha1_ok and crc32_ok:
        print(
            "\nRESULT: PASS - Track 1 matches the canonical redump dump "
            "(SLUS-00726 USA, build 1998-08-25)."
        )
        return 0
    print(
        "\nRESULT: FAIL - Track 1 does NOT match the redump dump; "
        "this is not the canonical disc image.",
        file=sys.stderr,
    )
    return 1


def main(argv: list[str] | None = None) -> int:
    args = parse_args(argv)
    if args.verify_disc:
        return cmd_verify_disc(args.bin)
    try:
        with Iso9660Image(args.bin) as img:
            if args.list:
                return cmd_list(img)
            return cmd_extract(img, args.out)
    except Iso9660Error as e:
        print(f"ERROR: {e}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    raise SystemExit(main())
