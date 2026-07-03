#!/usr/bin/env python3
"""masked_scorer.py — a drop-in for decomp-permuter's Scorer that scores relocation-masked .text
closeness (Phase 24 T2). Rebound over src.main.Scorer by tools/permuter/run_masked.py.

The stock Scorer diffs objdump MNEMONIC sequences and symbolizes relocations, penalizing any
symbol/addend divergence (scorer.py PENALTY_REGALLOC/REORDERING/INSERTION). For BFM's dotless
symbols (func_800…/D_800…) its `field_matches_any_symbol` wildcard never fires, so the score floats
on a nonzero FLOOR the search can't cross (func_80176D94 base~225/best~210/never 0) — the random walk
diverges. This scorer instead returns masked_diff.diff_object_object(cand, target): same-count,
non-reloc words identical, reloc/jal slots matching opcode+regs AND symbol+addend. It bottoms out at
exactly 0 ⟺ the two functions link to identical bytes, giving the search a gradient that reaches 0.

Same contract as Scorer: __init__(target_o, *, stack_differences, algorithm, debug_mode);
score(cand_o)->(int,str); PENALTY_INF. NOT the byte-gate — the whole-binary rebuild (harvest_verify)
is the sole arbiter (G3/P9); a permuter output-0 is a strong CANDIDATE to gate, not a bank.
"""
import hashlib
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import masked_diff


class MaskedScorer:
    PENALTY_INF = 10 ** 9

    def __init__(self, target_o, *, stack_differences=False, algorithm="", debug_mode=False):
        # target.o and cand.o each hold exactly ONE function (p16_permute assembles/compiles one),
        # so whole-.text is unambiguous — no function-name plumbing needed.
        self.target_o = target_o
        self.debug_mode = debug_mode
        self.target = masked_diff.insns_from_object(target_o)

    def score(self, cand_o):
        if not cand_o:
            return (self.PENALTY_INF, "")
        cand = masked_diff.insns_from_object(cand_o)
        if not cand:
            return (self.PENALTY_INF, "")
        d = masked_diff.diff_object_object(cand, self.target)
        # deterministic content hash of the candidate's asm (words + relocs) so the permuter dedups
        # identical candidates — mirrors the stock Scorer's "hash the objdump output" second field.
        h = hashlib.sha256(
            "".join(f"{i['word']:08x}:{i['reloc_kind'] or ''}:{i['reloc_op'] or ''}"
                    for i in cand).encode()
        ).hexdigest()
        return (d, h)
