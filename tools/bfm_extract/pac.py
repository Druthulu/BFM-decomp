"""Brave Fencer Musashi PAC chain splitter.

A PAC chain is a run of entries, each with a 0x800-byte header::

    +0x00  u32 LE  magic 'PAC\\0' (0x00434150)
    +0x04  u8      type    (0-8; only type 4 is LZSS-compressed)
    +0x05  u8      last-entry flag (1 = last)
    +0x08  u32 LE  unknown   preserved verbatim -- formats.md open question F2
    +0x0C  u32 LE  length    INCLUDING the 0x800 header

The next entry starts at the next 0x800 boundary:
``pos += (length + 0x7FF) & ~0x7FF``.

Our naming is ``{index}.{type}``. CUE's brave.c names entries by *type only* and
so silently overwrites two same-type entries in one chain; carrying the chain
index fixes that. See docs/formats.md §3. Pure stdlib.
"""

from __future__ import annotations

import struct
from dataclasses import dataclass

PAC_MAGIC = 0x00434150     # "PAC\0" little-endian at +0x00
HEADER_SIZE = 0x800        # also the chain alignment
COMPRESSED_TYPE = 4        # the only LZSS-compressed type
RAW_TYPES = frozenset({0, 1, 2, 3, 8})
UNKNOWN_TYPES = frozenset({5, 6, 7})


class PacError(Exception):
    """Raised on a malformed PAC entry (bad magic, bad length, overrun)."""


@dataclass(frozen=True)
class PacEntry:
    index: int       # 0-based position in the chain (-> {index}.{type})
    type: int        # u8 @ +0x04
    is_last: bool    # u8 @ +0x05
    unknown: int     # u32 LE @ +0x08 (open question F2, preserved verbatim)
    length: int      # u32 LE @ +0x0C, INCLUDING the 0x800 header
    offset: int      # entry start within the chain buffer
    payload: bytes   # buffer[offset+0x800 : offset+length]


def is_pac(buffer: bytes) -> bool:
    """True iff ``buffer`` begins with the PAC magic."""
    return len(buffer) >= 4 and struct.unpack_from("<I", buffer, 0)[0] == PAC_MAGIC


def split_pac(buffer: bytes) -> list[PacEntry]:
    """Walk the PAC chain and return its entries. Raises :class:`PacError` on a
    malformed entry."""
    entries: list[PacEntry] = []
    pos = 0
    n = len(buffer)
    index = 0
    while True:
        if pos + HEADER_SIZE > n:
            raise PacError(f"entry {index}: header at {pos} runs past end ({n})")
        magic = struct.unpack_from("<I", buffer, pos)[0]
        if magic != PAC_MAGIC:
            raise PacError(f"entry {index} at {pos}: bad magic 0x{magic:08X}")
        type_ = buffer[pos + 0x04]
        is_last = buffer[pos + 0x05] != 0
        unknown = struct.unpack_from("<I", buffer, pos + 0x08)[0]
        length = struct.unpack_from("<I", buffer, pos + 0x0C)[0]
        if length < HEADER_SIZE or pos + length > n:
            raise PacError(
                f"entry {index} at {pos}: length {length} out of bounds (n={n})"
            )
        entries.append(
            PacEntry(
                index=index,
                type=type_,
                is_last=is_last,
                unknown=unknown,
                length=length,
                offset=pos,
                payload=buffer[pos + HEADER_SIZE : pos + length],
            )
        )
        if is_last:
            break
        advance = (length + (HEADER_SIZE - 1)) & ~(HEADER_SIZE - 1)
        if advance <= 0:
            raise PacError(f"entry {index}: non-positive advance {advance}")
        pos += advance
        index += 1
    return entries
