"""Game-semantics LZSS decoder for Brave Fencer Musashi PAC type-4 payloads.

Byte-verified against docs/formats.md §4 (itself verified against the US game's
MIPS decompressor at 0x80018730 and CUE's brave.c). The load-bearing details
that make this NOT a generic LZSS, and NOT CUE's tool:

* **Absolute ring indices, not relative distances.** A match's low 10 bits are a
  direct index into the 1024-byte ring buffer.
* **The -1 bias.** Stored positions are the encoder's ring index + 1, so the
  first copied byte is ``ring[(pos - 1) & 0x3FF]``. An off-by-one here corrupts
  every overlay.
* **Game terminator: a match whose ``pos == 0`` ends the stream** (streams end
  with ``00 00``) and emits nothing. CUE's brave.c instead runs until it has
  consumed the PAC length; on well-formed retail data the two agree, and the
  length cross-check here flags any stream where they would not (formats.md F6).

Pure stdlib. The decoder is a pure function of its input buffer (the ring is
re-zeroed per call), so output is deterministic and unit-testable without a disc.
"""

from __future__ import annotations

from dataclasses import dataclass

RING_SIZE = 1024            # N = 1 << POS_BITS
POS_BITS = 10
POS_MASK = RING_SIZE - 1    # 0x3FF
THRESHOLD = 1               # real match length = (6-bit field) + THRESHOLD


class LzssError(Exception):
    """Raised only on a structurally impossible decode state."""


@dataclass(frozen=True)
class LzssResult:
    data: bytes                # decompressed payload
    input_consumed: int        # bytes read from `encoded`, incl. the 00 00 terminator
    terminated: bool           # True iff stopped on a pos==0 match (clean end-of-stream)
    warnings: tuple[str, ...]  # length-cross-check / anomaly notes (never raised)


def decompress(encoded: bytes, *, expected_len: int | None = None) -> LzssResult:
    """Decode one PAC type-4 stream using GAME semantics (stop on ``pos == 0``).

    ``expected_len`` is the PAC payload length (``len - 0x800``) for the length
    cross-check; it defaults to ``len(encoded)``. Warnings are collected, not
    raised: a stream that exhausts its input without a terminator, overruns, or
    carries non-zero data past the terminator still returns its partial data plus
    a warning (forensics for formats.md open question F6).
    """
    ring = bytearray(RING_SIZE)   # zero-filled, re-created per call (determinism)
    r = 0
    out = bytearray()
    flags = 0
    p = 0
    n = len(encoded)
    terminated = False

    while True:
        # Flag engine: LSB-first, 0xFF00 sentinel reloads a new flag byte every
        # 8 tokens (matches brave.c's `if (!((flags >>= 1) & 0xFF00)) ...`).
        flags >>= 1
        if (flags & 0xFF00) == 0:
            if p >= n:
                break  # input exhausted at a token boundary (no terminator)
            flags = 0xFF00 | encoded[p]
            p += 1

        if flags & 1:
            # Literal: copy one byte through the ring.
            if p >= n:
                break
            b = encoded[p]
            p += 1
            out.append(b)
            ring[r] = b
            r = (r + 1) & POS_MASK
        else:
            # Match: a 2-byte little-endian reference (absolute ring index).
            if p + 1 >= n:
                p = n  # only a partial code remained; no terminator
                break
            code = encoded[p] | (encoded[p + 1] << 8)
            p += 2
            pos = code & POS_MASK
            if pos == 0:
                terminated = True
                break  # end-of-stream; emit nothing
            length = (code >> POS_BITS) + THRESHOLD
            for i in range(length + 1):  # inclusive 0..=length => length+1 bytes
                b = ring[(pos - 1 + i) & POS_MASK]  # the -1 bias
                out.append(b)
                ring[r] = b
                r = (r + 1) & POS_MASK

    warnings: list[str] = []
    exp = len(encoded) if expected_len is None else expected_len
    if not terminated:
        warnings.append(f"no pos==0 terminator: input exhausted after {p} bytes")
    elif p > exp:
        warnings.append(f"overrun: consumed {p} > expected payload length {exp}")
    elif any(encoded[p:exp]):
        warnings.append(
            f"non-zero data after terminator ({exp - p} trailing bytes before payload end)"
        )

    return LzssResult(
        data=bytes(out),
        input_consumed=p,
        terminated=terminated,
        warnings=tuple(warnings),
    )
