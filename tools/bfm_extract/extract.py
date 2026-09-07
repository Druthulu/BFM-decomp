"""Unified full-disc extractor for the BFM USA disc (SLUS-00726).

Phase 2 pipeline driver. Walks the ISO9660 root and writes every file: the 24
files on the Track-1 data track verbatim, and the 3 ``.DA`` files as raw CD-DA
audio read from tracks 2-4. Later tasks extend the ``extract_root_file`` seam
with ``.CD``/PAC splitting and LZSS type-4 decompression (T3/T4) and add the
deterministic SHA1 manifest (T5). It composes over the frozen
``iso9660.Iso9660Image`` foundation and reuses the Phase-1 EXE constants.

Run from the repo root (use ``python3`` on Linux/WSL)::

    python3 tools/bfm_extract/extract.py
    python3 tools/bfm_extract/extract.py --list
    python3 tools/bfm_extract/extract.py --bin path/to/track1.bin --out extracted/retail

Output under ``extracted/`` is ROM-derived bulk; it is gitignored except the
committed EXE and the manifest. Re-running reproduces it byte-for-byte.

Multi-track note: the 3 ``.DA`` files (DUMMY_DA.DA, ST01_13A.DA, ST01_13B.DA)
are CD-DA audio. Their ISO directory entries point past the Track-1 data track
into AUDIO tracks 2-4 (each ``(Track N).bin`` carries a 150-sector INDEX 00->01
pregap, then the audio). We extract them as the raw 2352-byte/sector audio of
their track (the true bytes on disc), so the extracted size differs from the
2048-based ISO directory size. If the sibling ``(Track N).bin`` files are not
staged, the ``.DA`` files are skipped with a note.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import sys
from dataclasses import dataclass, field
from pathlib import Path

# Allow running as a plain script as well as a module (mirrors extract_exe.py).
try:
    from .iso9660 import (
        Iso9660Image,
        Iso9660Error,
        FileRecord,
        USER_DATA_SIZE,
        RAW_SECTOR_SIZE,
    )
    from .extract_exe import (
        EXE_NAME,
        EXPECTED_SIZE,
        EXPECTED_EXE_SHA1,
        validate_ps_exe,
    )
    from . import cd_archive, pac, lzss, manifest
except ImportError:  # pragma: no cover - exercised only as a loose script
    sys.path.insert(0, str(Path(__file__).resolve().parent))
    from iso9660 import (  # type: ignore
        Iso9660Image,
        Iso9660Error,
        FileRecord,
        USER_DATA_SIZE,
        RAW_SECTOR_SIZE,
    )
    from extract_exe import (  # type: ignore
        EXE_NAME,
        EXPECTED_SIZE,
        EXPECTED_EXE_SHA1,
        validate_ps_exe,
    )
    import cd_archive  # type: ignore
    import pac  # type: ignore
    import lzss  # type: ignore
    import manifest  # type: ignore

# Disc staged on ext4 in Phase 2 (docs/SETUP.md §4.4).
DEFAULT_BIN = Path("disks") / "Brave Fencer Musashi (USA) (Track 1).bin"
DEFAULT_OUT = Path("extracted") / "retail"  # per-ROM subfolder (protos live in extracted/proto/)

# Each AUDIO track .bin carries a 150-sector (2s) INDEX 00->01 pregap before the
# audio data, per the .cue. The .DA files map to the audio (INDEX 01 onward).
AUDIO_PREGAP_SECTORS = 150


@dataclass(frozen=True)
class AudioTrack:
    """One AUDIO track (2-4) located by absolute LBA, for .DA extraction."""

    index01_lba: int     # absolute LBA where the audio (INDEX 01) starts
    audio_sectors: int   # raw 2352-byte sectors of audio (after the pregap)
    bin_path: Path       # the (Track N).bin file
    audio_offset: int    # byte offset of the audio start within bin_path


def discover_audio_tracks(track1_bin: Path, track1_sectors: int) -> list[AudioTrack]:
    """Locate the AUDIO tracks following Track 1 via redump multi-bin naming.

    Walks ``(Track 2).bin``, ``(Track 3).bin``, ... siblings of ``track1_bin``,
    accumulating absolute LBAs and applying the 150-sector pregap. Returns ``[]``
    when no sibling AUDIO .bin is present (Track-1-only staging) or the file name
    does not follow the ``(Track 1)`` convention.
    """
    tracks: list[AudioTrack] = []
    abs_lba = track1_sectors
    n = 2
    while True:
        name = track1_bin.name.replace("(Track 1)", f"(Track {n})")
        if name == track1_bin.name:  # naming didn't match; can't locate siblings
            break
        binp = track1_bin.with_name(name)
        if not binp.is_file():
            break
        size = binp.stat().st_size
        if size == 0 or size % RAW_SECTOR_SIZE != 0:
            break
        bin_sectors = size // RAW_SECTOR_SIZE
        tracks.append(
            AudioTrack(
                index01_lba=abs_lba + AUDIO_PREGAP_SECTORS,
                audio_sectors=bin_sectors - AUDIO_PREGAP_SECTORS,
                bin_path=binp,
                audio_offset=AUDIO_PREGAP_SECTORS * RAW_SECTOR_SIZE,
            )
        )
        abs_lba += bin_sectors
        n += 1
    return tracks


def in_track1(img: Iso9660Image, rec: FileRecord) -> bool:
    """True iff the file's whole extent lies within the Track-1 data track."""
    sectors = (rec.size + USER_DATA_SIZE - 1) // USER_DATA_SIZE
    return rec.lba < img.sector_count and rec.lba + sectors <= img.sector_count


def extract_root_file(
    img: Iso9660Image, rec: FileRecord, out_root: Path
) -> tuple[Path | None, bytes | None]:
    """Extract one in-Track-1 file verbatim; ``(None, None)`` if beyond Track 1.

    This is the dispatch seam later tasks extend: T4 branches here on ``.CD``
    archives (split into sub-files via cd_archive/pac) while still writing the
    raw container. For now every in-track file is written verbatim.
    """
    if not in_track1(img, rec):
        return None, None
    data = img.read_extent(rec.lba, rec.size)
    out_path = out_root / rec.name
    out_path.parent.mkdir(parents=True, exist_ok=True)
    out_path.write_bytes(data)
    return out_path, data


def extract_audio_file(
    rec: FileRecord, audio_tracks: list[AudioTrack], out_root: Path
) -> tuple[Path | None, int | None, int | None]:
    """Extract a ``.DA`` file as raw CD-DA audio from tracks 2-4.

    The ISO entry counts 2048-byte logical sectors; on-disc audio is 2352
    bytes/sector, so we emit ``file_sectors * 2352`` raw bytes (capped at the
    track's remaining audio). Returns ``(out_path, nbytes, track_no)`` or
    ``(None, None, None)`` if no staged audio track covers the file's LBA.
    """
    file_sectors = (rec.size + USER_DATA_SIZE - 1) // USER_DATA_SIZE
    for track_no, t in enumerate(audio_tracks, start=2):
        if t.index01_lba <= rec.lba < t.index01_lba + t.audio_sectors:
            sector_off = rec.lba - t.index01_lba
            nsec = min(file_sectors, t.audio_sectors - sector_off)
            byte_off = t.audio_offset + sector_off * RAW_SECTOR_SIZE
            with open(t.bin_path, "rb") as fh:
                fh.seek(byte_off)
                data = fh.read(nsec * RAW_SECTOR_SIZE)
            out_path = out_root / rec.name
            out_path.parent.mkdir(parents=True, exist_ok=True)
            out_path.write_bytes(data)
            return out_path, len(data), track_no
    return None, None, None


@dataclass
class SplitStats:
    """Counters and findings accumulated while splitting the .CD archives."""

    cd_counts: dict[str, int] = field(default_factory=dict)  # name -> sub-file count (F5)
    subfiles: int = 0
    pac_chains: int = 0
    pac_entries: int = 0
    type4: int = 0
    sqv: int = 0
    unknown_types: list[tuple[str, int]] = field(default_factory=list)
    pac_errors: list[str] = field(default_factory=list)
    lzss_warnings: list[str] = field(default_factory=list)


def split_pac_entries(sub_path: Path, sub: bytes, stats: SplitStats) -> None:
    """Split a PAC-chain sub-file into ``{index}.{type}`` entries (+ ``.dec`` for
    decompressed type-4) under ``<sub_path>.dir/``."""
    try:
        entries = pac.split_pac(sub)
    except pac.PacError as e:
        stats.pac_errors.append(f"{sub_path.name}: {e}")
        return
    stats.pac_chains += 1
    pac_dir = sub_path.parent / (sub_path.name + ".dir")
    pac_dir.mkdir(parents=True, exist_ok=True)
    for pe in entries:
        entry_path = pac_dir / f"{pe.index}.{pe.type}"
        entry_path.write_bytes(pe.payload)
        stats.pac_entries += 1
        if pe.type == pac.COMPRESSED_TYPE:
            stats.type4 += 1
            res = lzss.decompress(pe.payload)
            (pac_dir / f"{pe.index}.{pe.type}.dec").write_bytes(res.data)
            if res.warnings:
                stats.lzss_warnings.append(
                    f"{sub_path.name}/{entry_path.name}: {'; '.join(res.warnings)}"
                )
        elif pe.type in pac.UNKNOWN_TYPES:
            stats.unknown_types.append((entry_path.name, pe.type))


def split_cd(name: str, cd_buffer: bytes, out_root: Path, stats: SplitStats) -> None:
    """Split a ``.CD`` archive into ``<name>.dir/FILE_%03d`` sub-files, splitting
    PAC chains further. LIST.CD must be excluded by the caller."""
    cd_dir = out_root / f"{name}.dir"
    try:
        toc = cd_archive.parse_toc(cd_buffer)
        stats.cd_counts[name] = toc.count
        cd_dir.mkdir(parents=True, exist_ok=True)
        for entry, sub in cd_archive.iter_subfiles(cd_buffer, toc):
            sub_path = cd_dir / f"FILE_{entry.index:03d}"
            sub_path.write_bytes(sub)
            stats.subfiles += 1
            kind = cd_archive.classify_subfile(sub)
            if kind == "pac":
                split_pac_entries(sub_path, sub, stats)
            elif kind == "sqv":
                stats.sqv += 1
    except cd_archive.CdArchiveError as e:
        stats.pac_errors.append(f"{name}: {e}")


def print_split_summary(stats: SplitStats) -> None:
    print(
        f"\n.CD split: {stats.subfiles} sub-files, {stats.pac_chains} PAC chains, "
        f"{stats.pac_entries} entries ({stats.type4} type-4 decoded), {stats.sqv} SQV."
    )
    if stats.cd_counts:
        print(
            "  sub-file counts (F5): "
            + ", ".join(f"{k}={v}" for k, v in sorted(stats.cd_counts.items()))
        )
    if stats.unknown_types:
        kinds = sorted({t for _n, t in stats.unknown_types})
        print(f"  unknown PAC types present: {kinds} ({len(stats.unknown_types)} entries)")
    if stats.lzss_warnings:
        print(f"  LZSS cross-check warnings: {len(stats.lzss_warnings)}")
        for w in stats.lzss_warnings[:8]:
            print(f"    - {w}")
    if stats.pac_errors:
        print(f"  PAC/TOC errors: {len(stats.pac_errors)}")
        for e in stats.pac_errors[:8]:
            print(f"    - {e}")


def extract_all(
    img: Iso9660Image, out_root: Path, audio_tracks: list[AudioTrack]
) -> tuple[list[FileRecord], bytes | None]:
    """Walk the ISO root in disc (directory) order and extract every file."""
    files = [rec for rec in img.list_files() if not rec.is_dir]
    print(f"Volume {img.volume_id!r}: {len(files)} root files -> {out_root}/")
    if audio_tracks:
        print(f"AUDIO tracks staged: {len(audio_tracks)} (for .DA extraction)")
    print(f"{'SIZE':>11}  NAME")
    total = 0
    skipped: list[FileRecord] = []
    exe_data: bytes | None = None
    stats = SplitStats()
    for rec in files:
        _out_path, data = extract_root_file(img, rec, out_root)
        if data is None:
            _out_path, nbytes, track_no = extract_audio_file(rec, audio_tracks, out_root)
            if nbytes is None:
                skipped.append(rec)
                print(f"{'(skip)':>11}  {rec.name}  — beyond Track 1; no audio track staged")
            else:
                total += nbytes
                print(f"{nbytes:>11}  {rec.name}  — raw CD-DA audio (Track {track_no})")
            continue
        total += len(data)
        if rec.name == EXE_NAME:
            exe_data = data
        print(f"{len(data):>11}  {rec.name}")
        if rec.name.endswith(".CD") and rec.name != "LIST.CD":
            split_cd(rec.name, data, out_root, stats)
    summary = f"\nExtracted {len(files) - len(skipped)} files, {total} bytes total."
    if skipped:
        summary += " Skipped " + ", ".join(r.name for r in skipped)
    print(summary)
    print_split_summary(stats)
    return files, exe_data


def check_exe_roundtrip(exe_data: bytes | None) -> bool:
    """Confirm the full-disc walk reproduces the known-good SLUS_007.26."""
    print("\nEXE round-trip (SLUS_007.26):")
    if exe_data is None:
        print(f"  [FAIL] {EXE_NAME} was not extracted")
        return False
    sha1 = hashlib.sha1(exe_data).hexdigest()
    size_ok = len(exe_data) == EXPECTED_SIZE
    sha_ok = sha1 == EXPECTED_EXE_SHA1
    hdr_ok = all(ok for _name, ok, _detail in validate_ps_exe(exe_data))
    print(f"  [{'PASS' if size_ok else 'FAIL'}] size {len(exe_data)} (expected {EXPECTED_SIZE})")
    print(f"  [{'PASS' if sha_ok else 'FAIL'}] sha1 {sha1}")
    print(f"  [{'PASS' if hdr_ok else 'FAIL'}] PS-EXE header fields")
    return size_ok and sha_ok and hdr_ok


def cmd_list(img: Iso9660Image) -> int:
    files = img.list_files()
    print(f"Volume: {img.volume_id!r}  ({len(files)} root entries)")
    print(f"{'LBA':>7}  {'SIZE':>11}  NAME")
    for rec in files:
        print(f"{rec.lba:>7}  {rec.size:>11}  {rec.raw_name}")
    return 0


def parse_args(argv: list[str] | None = None) -> argparse.Namespace:
    p = argparse.ArgumentParser(
        description="Extract every file from the BFM USA disc (Track-1 data + .DA audio).",
    )
    p.add_argument(
        "--bin",
        type=Path,
        default=DEFAULT_BIN,
        help=f"Path to the MODE2/2352 Track-1 data BIN (default: {DEFAULT_BIN}).",
    )
    p.add_argument(
        "--out",
        type=Path,
        default=DEFAULT_OUT,
        help=f"Output root directory (default: {DEFAULT_OUT}).",
    )
    p.add_argument(
        "--list",
        action="store_true",
        help="List the root directory and exit (no extraction).",
    )
    p.add_argument(
        "--verify",
        action="store_true",
        help="Re-hash the output tree against its manifest and exit (no extraction).",
    )
    p.add_argument(
        "--expect-manifest",
        type=Path,
        default=None,
        help=(
            "P33 B1 (the public `make disc-extract`): compare the extraction against this committed "
            "manifest.jsonl (the oracle) INSTEAD of writing one. Identical -> nothing written, exit 0; "
            "different -> the actual manifest goes to .run/extract/, the first differences are listed, "
            "exit 1. The committed oracle is never overwritten by a build step."
        ),
    )
    p.add_argument(
        "--allow-missing-audio",
        action="store_true",
        help=(
            "With no sibling `(Track 2).bin` staged, compare/verify WITHOUT the 3 .DA audio rows and "
            "report PARTIAL instead of failing (a Track-1-only dump). Without this flag a partial "
            "extraction against the 4-track oracle FAILS."
        ),
    )
    return p.parse_args(argv)


def _is_audio_row(path: str) -> bool:
    return path.upper().endswith(".DA")


def cmd_verify(out_root: Path, allow_missing_audio: bool = False) -> int:
    ok, problems = manifest.verify(out_root)
    partial = []
    if allow_missing_audio:
        partial = [p for p in problems if p.startswith("missing file: ") and _is_audio_row(p)]
        problems = [p for p in problems if p not in partial]
        ok = not problems
    if ok:
        if partial:
            print(f"RESULT: PASS (PARTIAL) - every artifact under {out_root}/ matches "
                  f"{manifest.MANIFEST_NAME} except {len(partial)} unstaged .DA audio file(s): "
                  + ", ".join(p.split(': ', 1)[1] for p in partial))
        else:
            print(f"RESULT: PASS - every artifact under {out_root}/ matches {manifest.MANIFEST_NAME}.")
        return 0
    print(f"RESULT: FAIL - {len(problems)} problem(s):", file=sys.stderr)
    for p in problems[:20]:
        print(f"  - {p}", file=sys.stderr)
    return 1


ACTUAL_DIR = Path(".run") / "extract"   # where a NON-matching extraction's manifest is written (R12)


def compare_with_oracle(records: list[dict], oracle: Path, allow_missing_audio: bool) -> int:
    """Compare the freshly built records against the committed oracle manifest.jsonl.

    Never writes into the oracle's directory. On a match prints the oracle's own SHA1 (the single
    value a contributor quotes to prove their extraction). On a mismatch writes the ACTUAL manifest
    to .run/extract/ and prints the first 20 differences (missing / extra / mismatched paths)."""
    if not oracle.is_file():
        print(f"ERROR: oracle manifest not found: {oracle}", file=sys.stderr)
        return 2
    text = oracle.read_text(encoding="ascii")
    oracle_sha1 = hashlib.sha1(text.encode("ascii")).hexdigest()
    sha_file = oracle.with_name(manifest.MANIFEST_SHA1_NAME)
    if sha_file.is_file():
        recorded = sha_file.read_text(encoding="ascii").strip()
        if recorded != oracle_sha1:
            print(f"ERROR: {sha_file} records {recorded} but {oracle.name} hashes to {oracle_sha1} — "
                  f"the committed oracle is internally inconsistent; refusing to compare", file=sys.stderr)
            return 2
    expected = {}
    for line in text.splitlines():
        if line.strip():
            r = json.loads(line)
            expected[r["path"]] = (r["size"], r["sha1"])
    actual = {r["path"]: (r["size"], r["sha1"]) for r in records}
    partial = []
    if allow_missing_audio:
        partial = sorted(p for p in expected if _is_audio_row(p) and p not in actual)
        for p in partial:
            del expected[p]
    missing = sorted(set(expected) - set(actual))
    extra = sorted(set(actual) - set(expected))
    mismatch = sorted(p for p in expected if p in actual and expected[p] != actual[p])
    if not (missing or extra or mismatch):
        note = (f" PARTIAL: {len(partial)} .DA audio row(s) unverified ({', '.join(partial)})"
                if partial else "")
        print(f"\nManifest: {len(actual)} artifacts == the committed oracle {oracle} "
              f"(sha1 {oracle_sha1}); nothing written.{note}")
        return 0
    ACTUAL_DIR.mkdir(parents=True, exist_ok=True)
    digest = manifest.write(ACTUAL_DIR, records)
    print(f"\nManifest MISMATCH against the oracle {oracle} (sha1 {oracle_sha1}): "
          f"{len(missing)} missing, {len(extra)} extra, {len(mismatch)} mismatched — "
          f"actual manifest written to {ACTUAL_DIR}/ (sha1 {digest})", file=sys.stderr)
    shown = 0
    for label, paths in (("missing", missing), ("extra", extra), ("mismatch", mismatch)):
        for p in paths:
            if shown >= 20:
                break
            print(f"  - {label}: {p}", file=sys.stderr)
            shown += 1
    return 1


def main(argv: list[str] | None = None) -> int:
    args = parse_args(argv)
    if args.verify:
        return cmd_verify(args.out, args.allow_missing_audio)
    try:
        with Iso9660Image(args.bin) as img:
            if args.list:
                return cmd_list(img)
            audio_tracks = discover_audio_tracks(args.bin, img.sector_count)
            _files, exe_data = extract_all(img, args.out, audio_tracks)
    except Iso9660Error as e:
        print(f"ERROR: {e}", file=sys.stderr)
        return 2

    records = manifest.build(args.out)
    if args.expect_manifest:
        rc = compare_with_oracle(records, args.expect_manifest,
                                 allow_missing_audio=args.allow_missing_audio and not audio_tracks)
        if rc:
            return rc
    else:
        digest = manifest.write(args.out, records)
        print(
            f"\nManifest: {len(records)} artifacts -> "
            f"{args.out}/{manifest.MANIFEST_NAME} (sha1 {digest})"
        )

    if check_exe_roundtrip(exe_data):
        print("\nRESULT: PASS - full disc extracted; EXE reproduces the known-good binary.")
        return 0
    print("\nRESULT: FAIL - EXE round-trip mismatch.", file=sys.stderr)
    return 1


if __name__ == "__main__":
    raise SystemExit(main())
