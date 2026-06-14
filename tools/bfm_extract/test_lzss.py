"""Standalone unit tests for the game-semantics LZSS decoder (lzss.py).

Run::

    python3 tools/bfm_extract/test_lzss.py

Synthetic streams hand-encoded from docs/formats.md §4 to exercise literals, the
``pos == 0`` terminator, a back-reference match, and the load-bearing -1 ring
bias. No disc required. Real-data byte-for-byte validation against CUE's brave
happens in T6 (crosscheck.py).
"""

from __future__ import annotations

import sys
from pathlib import Path

try:
    from .lzss import decompress
except ImportError:  # pragma: no cover - exercised only as a loose script
    sys.path.insert(0, str(Path(__file__).resolve().parent))
    from lzss import decompress  # type: ignore


def test_literals_then_terminator():
    # flag 0x07 = literal,literal,literal,match; 'A','B','C'; then 00 00 (pos=0).
    stream = bytes([0x07, 0x41, 0x42, 0x43, 0x00, 0x00])
    r = decompress(stream)
    assert r.data == b"ABC", r.data
    assert r.terminated is True
    assert r.input_consumed == 6, r.input_consumed
    assert r.warnings == (), r.warnings


def test_backreference_and_minus1_bias():
    # 'A','B' literals, then a match (pos=1, len-field=0) which via the -1 bias
    # copies ring[0],ring[1] = 'A','B'; then 00 00 terminates. Output "ABAB".
    # flag 0x03 = literal,literal,match,match.
    stream = bytes([0x03, 0x41, 0x42, 0x01, 0x00, 0x00, 0x00])
    r = decompress(stream)
    assert r.data == b"ABAB", r.data
    assert r.terminated is True
    assert r.input_consumed == 7, r.input_consumed
    assert r.warnings == (), r.warnings


def test_longer_match_overlapping_copy():
    # 'X' literal, then a match pos=1 with len-field=2 -> length=3 -> 4 bytes.
    # The match reads ring[(pos-1+i)] = ring[i] while the write pointer (r=1)
    # advances alongside, so the single 'X' propagates: an overlapping/RLE-style
    # copy. The 4 match bytes are all 'X'. Output = "X" + "XXXX" = "XXXXX".
    # Validates both (code>>10)+1 length and the self-referential ring copy.
    # code = (2 << 10) | 1 = 0x0801 -> low 0x01, high 0x08.
    # flag 0x01 = literal, match, match-terminator.
    stream = bytes([0x01, 0x58, 0x01, 0x08, 0x00, 0x00])
    r = decompress(stream)
    assert r.data == b"XXXXX", r.data
    assert r.terminated is True
    assert r.warnings == (), r.warnings


def test_no_terminator_warns():
    # one literal 'Z', then input ends with no pos==0 match.
    stream = bytes([0x01, 0x5A])
    r = decompress(stream)
    assert r.data == b"Z", r.data
    assert r.terminated is False
    assert any("no pos==0 terminator" in w for w in r.warnings), r.warnings


def test_trailing_nonzero_after_terminator_warns():
    # flag 0x00 -> first token is a match; 00 00 terminates immediately; a stray
    # 0xFF follows within the buffer -> length cross-check warning.
    stream = bytes([0x00, 0x00, 0x00, 0xFF])
    r = decompress(stream)
    assert r.data == b"", r.data
    assert r.terminated is True
    assert r.input_consumed == 3, r.input_consumed
    assert any("after terminator" in w for w in r.warnings), r.warnings


def _run() -> int:
    tests = [v for k, v in sorted(globals().items()) if k.startswith("test_")]
    for t in tests:
        t()
        print(f"  [PASS] {t.__name__}")
    print(f"\n{len(tests)} lzss tests passed.")
    return 0


if __name__ == "__main__":
    raise SystemExit(_run())
