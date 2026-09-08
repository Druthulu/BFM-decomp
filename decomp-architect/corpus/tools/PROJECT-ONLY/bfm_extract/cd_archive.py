"""Brave Fencer Musashi ``.CD`` container reader (TOC walker).

A ``.CD`` archive (MAIN.CD, SC01-SC07.CD) begins with a TOC in sector 0::

    +0x00  u32 LE  count        number of sub-files (MAIN.CD = 49)
    +0x04  u32 LE  zero
    +0x08  count * { u32 LE rel_sector, u32 LE length }

``rel_sector`` is relative to the ``.CD`` start (x 2048). Sub-files begin at
sector 1, are sector-aligned (0x800), and are zero-padded. All 8 archives share
this format.

LIST.CD is NOT an archive (it is the concatenated trimmed TOCs of the 8
archives, formats.md §2.3) and must never be parsed here -- the caller excludes
it by name.

See docs/formats.md §2. Pure stdlib; operates on in-memory buffers, so it is
unit-testable without a disc.
"""

from __future__ import annotations

import struct
from dataclasses import dataclass
from typing import Iterator

SECTOR = 0x800
PAC_MAGIC = b"PAC\x00"
SQV_MAGIC = b".sqv"


class CdArchiveError(Exception):
    """Raised on a malformed or out-of-bounds ``.CD`` TOC."""


@dataclass(frozen=True)
class CdEntry:
    index: int        # 0-based TOC ordinal (-> FILE_%03d)
    rel_sector: int   # u32 LE start sector, relative to the .CD file
    byte_offset: int  # rel_sector * SECTOR
    length: int       # u32 LE byte length (unpadded)


@dataclass(frozen=True)
class CdToc:
    count: int
    entries: tuple[CdEntry, ...]


def toc_byte_span(count: int) -> int:
    """Bytes the TOC header occupies: ``8 + 8*count`` (for the LIST.CD F4 check)."""
    return 8 + 8 * count


def parse_toc(buffer: bytes) -> CdToc:
    """Parse the ``.CD`` TOC from the start of ``buffer`` (the whole ``.CD`` or
    at least its header). Validates the count and that the header fits.
    """
    if len(buffer) < 8:
        raise CdArchiveError(f".CD too small for a TOC header ({len(buffer)} bytes)")
    count = struct.unpack_from("<I", buffer, 0)[0]
    if count == 0 or count > 0xFFFF:
        raise CdArchiveError(f"implausible .CD sub-file count {count}")
    need = toc_byte_span(count)
    if need > len(buffer):
        raise CdArchiveError(f"TOC needs {need} bytes but buffer is {len(buffer)}")
    entries = []
    for i in range(count):
        rel_sector, length = struct.unpack_from("<II", buffer, 8 + 8 * i)
        entries.append(
            CdEntry(
                index=i,
                rel_sector=rel_sector,
                byte_offset=rel_sector * SECTOR,
                length=length,
            )
        )
    return CdToc(count=count, entries=tuple(entries))


def iter_subfiles(cd_buffer: bytes, toc: CdToc) -> Iterator[tuple[CdEntry, bytes]]:
    """Yield ``(entry, raw sub-file bytes)`` for each TOC entry, in order."""
    for e in toc.entries:
        end = e.byte_offset + e.length
        if e.byte_offset > len(cd_buffer) or end > len(cd_buffer):
            raise CdArchiveError(
                f"sub-file {e.index} [{e.byte_offset}:{end}] out of bounds "
                f"(.CD is {len(cd_buffer)} bytes)"
            )
        yield e, cd_buffer[e.byte_offset:end]


def classify_subfile(buffer: bytes) -> str:
    """Return ``'pac'`` | ``'sqv'`` | ``'raw'`` from the leading magic (no parsing)."""
    head = buffer[:4]
    if head == PAC_MAGIC:
        return "pac"
    if head == SQV_MAGIC:
        return "sqv"
    return "raw"
