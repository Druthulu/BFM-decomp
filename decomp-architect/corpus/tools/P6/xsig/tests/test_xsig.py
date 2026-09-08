#!/usr/bin/env python3
"""tests/test_xsig.py — xsig's properties on the committed fixtures (no compiler, no game bytes needed).

    python3 tests/test_xsig.py            # from tools/xsig/ (or anywhere: paths are resolved from this file)

The fixtures (see make_fixtures.sh) are objdump -dr listings of one small function of our own, compiled once with the
gcc-2.7.2 toolchain and linked at two different addresses with --emit-relocs, plus a splat-style .s rendering of the
same function and a second, different function in the same listings.
"""
import io
import json
import os
import sys
import unittest
from contextlib import redirect_stdout, redirect_stderr

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.dirname(HERE))
import xsig  # noqa: E402

A = os.path.join(HERE, "fixture_a.txt")
B = os.path.join(HERE, "fixture_b.txt")
S = os.path.join(HERE, "fixture_a.s")


def fn(path, name):
    for n, pairs, mnem in xsig.parse_objdump_dr(open(path).read()):
        if n == name:
            return pairs, mnem
    raise AssertionError(f"{name} not in {path}")


class Fixtures(unittest.TestCase):
    def test_same_function_two_link_addresses_same_signature(self):
        pa, _ = fn(A, "fixture"); pb, _ = fn(B, "fixture")
        self.assertNotEqual([w for w, _ in pa], [w for w, _ in pb], "the raw words must differ (different link addresses)")
        self.assertEqual(xsig.signature(pa)["sig"], xsig.signature(pb)["sig"])

    def test_relocated_fields_are_present_and_masked(self):
        pa, _ = fn(A, "fixture")
        self.assertTrue(any(a for _, a in pa), "the fixture carries HI16/LO16 relocations")
        self.assertTrue(any((w >> 26) in xsig.J_OPS for w, _ in pa), "the fixture carries a jal")
        c = xsig.compare(pa, fn(B, "fixture")[0])
        self.assertTrue(c["same"]); self.assertEqual(c["diffs"], []); self.assertGreaterEqual(c["relocated"], 3)

    def test_different_function_different_signature(self):
        self.assertNotEqual(xsig.signature(fn(A, "fixture")[0])["sig"], xsig.signature(fn(A, "other")[0])["sig"])

    def test_register_flip_changes_signature_and_is_classified(self):
        pa, _ = fn(A, "fixture")
        idx = next(i for i, (w, a) in enumerate(pa) if not a and (w >> 26) not in xsig.J_OPS and (w >> 26) != 0)
        flipped = list(pa); w, a = flipped[idx]; flipped[idx] = (w ^ (1 << 16), a)
        self.assertNotEqual(xsig.signature(flipped)["sig"], xsig.signature(pa)["sig"])
        c = xsig.compare(pa, flipped)
        self.assertEqual([d[3] for d in c["diffs"]], ["register"])

    def test_splat_s_frontend_agrees_with_objdump(self):
        ps, _ = xsig.parse_splat_s(S)
        self.assertEqual(xsig.signature(ps)["sig"], xsig.signature(fn(A, "fixture")[0])["sig"])

    def test_cli_sign_and_cross_find_the_pair(self):
        out_a, out_b = os.path.join(HERE, ".a.jsonl"), os.path.join(HERE, ".b.jsonl")
        try:
            with redirect_stderr(io.StringIO()):
                self.assertEqual(xsig.main(["sign-objdump", A, "--project", "left", "-o", out_a]), 0)
                self.assertEqual(xsig.main(["sign-objdump", B, "--project", "right", "-o", out_b]), 0)
            buf = io.StringIO()
            with redirect_stdout(buf):
                self.assertEqual(xsig.main(["cross", out_a, out_b, "--min-ins", "4"]), 0)
            hits = [l for l in buf.getvalue().splitlines() if l and not l.startswith("#") and not l.startswith("nins")]
            names = {(l.split("\t")[3], l.split("\t")[6]) for l in hits}
            self.assertIn(("fixture", "fixture"), names); self.assertIn(("other", "other"), names)
            self.assertNotIn(("fixture", "other"), names)
        finally:
            for p in (out_a, out_b):
                if os.path.exists(p):
                    os.unlink(p)

    def test_cli_verify(self):
        with redirect_stdout(io.StringIO()):
            self.assertEqual(xsig.main(["verify", A, B, "--name-a", "fixture", "--name-b", "fixture"]), 0)
            self.assertEqual(xsig.main(["verify", A, B, "--name-a", "fixture", "--name-b", "other"]), 1)

    def test_selftest(self):
        with redirect_stdout(io.StringIO()):
            self.assertEqual(xsig.selftest(), 0)


if __name__ == "__main__":
    unittest.main(verbosity=1)
