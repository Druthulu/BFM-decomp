#!/usr/bin/env python3
"""run_masked.py — run decomp-permuter with our floor-free relocation-masked scorer (Phase 24 T2).

Rebinds src.main.Scorer -> tools/masked_scorer.MaskedScorer BEFORE main() runs (main.py resolves the
`Scorer` global at instantiation time, line ~362), so the search scores true masked-.text closeness
(0 = reloc-masked byte match) instead of the stock mnemonic-diff floor. NO edit to the pinned
tools/decomp-permuter submodule (R3/R20) — the swap lives entirely in our layer.

Invoke exactly like tools/decomp-permuter/permuter.py:
    run_masked.py <scratch_dir> -j N --stop-on-zero
"""
import os
import sys

_HERE = os.path.dirname(os.path.abspath(__file__))          # tools/permuter
_REPO = os.path.dirname(os.path.dirname(_HERE))
sys.path.insert(0, os.path.join(_REPO, "tools", "decomp-permuter"))   # the `src` package
sys.path.insert(0, os.path.join(_REPO, "tools"))                      # masked_scorer / masked_diff

import src.main as pmain                    # noqa: E402
from masked_scorer import MaskedScorer      # noqa: E402

pmain.Scorer = MaskedScorer                 # the drop-in swap

if __name__ == "__main__":
    pmain.main()
