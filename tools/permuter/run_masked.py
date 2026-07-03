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
import src.ast_types as _at                 # noqa: E402
from masked_scorer import MaskedScorer      # noqa: E402

pmain.Scorer = MaskedScorer                 # the drop-in swap

# Tolerate our hidden register-pin vars in the type-aware randomizer passes: a pin's declaration is
# carried in a b64literal pragma (so cc1 still binds the reg), which leaves the var absent from
# typemap.var_types -> perm_split_assignment / perm_temp_for_expr raise KeyError ("internal permuter
# failure"). Fall back to `int` for an unknown identifier so those passes MUTATE pinned drafts (the
# RC-2/RC-3 regalloc levers) instead of aborting. The whole-binary byte-gate remains the sole arbiter.
_orig_expr_type = _at.expr_type
def _pin_safe_expr_type(node, typemap):
    try:
        return _orig_expr_type(node, typemap)
    except KeyError:
        return _at.basic_type("int")
_at.expr_type = _pin_safe_expr_type

if __name__ == "__main__":
    pmain.main()
