#!/usr/bin/env python3
"""psyq_libs_from_disc.py — the 20 PsyQ 4.0 `PSX/LIB/*.LIB` files, extracted from the runtime-library disc.

The EXE links PsyQ 4.0 objects (main's LINKED regions). Sony's libraries are not redistributable and have no
public download; they are on the redump disc "PlayStation - Programmer Tools - Run-time Library 4.0 (USA)
(PC-CD ROM Release 2.0)" (DTL-S2002; ISO volume `PROGTOOL`), directory `PSX/LIB/`. This walks that disc's
Track-1 image with the project's own MODE2/2352 ISO9660 reader (tools/bfm_extract/iso9660.py — the same one
`make disc-extract` uses on the game disc) and writes the `.LIB` files out, printing each file's sha256 so
`tools/psyq_CHECKSUMS.sha256` can be checked against them. Called by tools/fetch_psyq.sh --disc. (P33 B4)

  python3 tools/psyq_libs_from_disc.py "<... Run-time Library 4.0 ... (Track 1).bin>" tools/psyq/lib40

Refuses (R43) a disc without `PSX/LIB` and a directory that does not hold exactly 20 `.LIB` files (R32).
"""
import hashlib
import pathlib
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent / "bfm_extract"))
from iso9660 import Iso9660Image, Iso9660Error  # noqa: E402

EXPECTED_LIBS = 20


def main(argv):
    if len(argv) != 3:
        sys.exit(__doc__)
    binp, out = pathlib.Path(argv[1]), pathlib.Path(argv[2])
    if not binp.is_file():
        sys.exit(f"psyq_libs_from_disc: no such disc image: {binp}")
    out.mkdir(parents=True, exist_ok=True)
    try:
        with Iso9660Image(binp) as img:
            psx = img.find("PSX")
            lib = img.find("LIB", psx) if psx is not None else None
            if lib is None or not lib.is_dir:
                sys.exit(f"psyq_libs_from_disc: no PSX/LIB directory on {binp.name} (volume {img.volume_id!r}) — "
                         "expected the Run-time Library 4.0 disc (volume PROGTOOL)")
            n = 0
            for rec in sorted(img.iter_directory(lib), key=lambda r: r.raw_name):
                if rec.is_dir:
                    continue
                name = rec.raw_name.split(";")[0]
                if not name.upper().endswith(".LIB"):
                    continue
                data = img.extract_file(rec.raw_name, lib)
                (out / name).write_bytes(data)
                print(f"{hashlib.sha256(data).hexdigest()}  {out / name}  ({len(data)} B)")
                n += 1
            vol = img.volume_id
    except Iso9660Error as e:
        sys.exit(f"psyq_libs_from_disc: {e}")
    print(f"psyq_libs_from_disc: {n} .LIB files -> {out}/ (volume {vol!r})", file=sys.stderr)
    if n != EXPECTED_LIBS:
        sys.exit(f"psyq_libs_from_disc: expected {EXPECTED_LIBS} .LIB files in PSX/LIB, found {n} (R32)")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
