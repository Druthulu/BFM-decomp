#!/usr/bin/env python3
"""permuter_weights.py — §31-directed decomp-permuter mutation (Phase 24 T5).

Turns the permuter's RANDOM walk into a DIRECTED search over the gcc-2.7.2 lever space
(docs/gcc-2.7.2-map/{regalloc,sched,cse_expr}.md). A near-miss draft's residual has a KNOWN
class (the wave agent already diagnosed it — the `klass`/`where_stuck` fields in the backlog,
the `@class:`/`@stuck:` headers on .run/wave/*.c). §31 says which C-level lever moves each
class; each lever is exercised by a specific decomp-permuter `perm_*` randomization pass. So
biasing the pass-selection weights toward the class's levers (and away from value/type noise
that a COUNT-EXACT register/schedule permutation can never use) makes every mutation land on
the residual instead of a random subexpression.

Mechanism (NO decomp-permuter submodule edit — R3/R20): the permuter reads a top-level
`weight_overrides` table from the scratch dir's settings.toml (src/main.py:336), merges it over
the compiler-type defaults per-key (helpers.py:43 merge_randomization_weights REPLACES a key's
weight; unknown keys are ignored, all base keys survive), and the Randomizer picks a pass with
`random_weighted(methods)` (randomizer.py:2467). So a partial {pass: weight} override reshapes
the mutation distribution. This module emits that table from a residual class.

The whole-binary byte-gate (tools/harvest_verify.py) remains the SOLE arbiter (G3/P9): a biased
search only reaches the SAME output-0 candidates faster/at-all — a permuter output-0 is a strong
candidate to gate, never a bank.

Pass→class map (grounded in the §31 catalog; keys are the exact perm_* method names in
tools/decomp-permuter/src/randomizer.py / default_weights.toml [base]):
  perm_reorder_decls        RC-1 spill-slot order · RC-3 callee-saved creation-order tie (K1)
  perm_reorder_stmts        RC-2 live-range shaping · S1 LUID order · D1 delay-slot adjacency
  perm_temp_for_expr        S2 birthing-boost (fresh single-set local) · RC-2 (the workhorse)
  perm_expand_expr          S2 kill (inline a temp) · S3 re-decompose a chain
  perm_split_assignment     set-count/position → S2 / RC-2
  perm_duplicate_assignment 2nd SET → kills the S2 boost / defeats RC-7 REG_EQUIV
  perm_add_self_assignment  2nd SET (as above)
  perm_commutative          operand order of a commutative op → cse/combine mult-canon (RC-cse)
  perm_factor_mult/shift     product re-decomposition → cse/S3
  perm_pad_var_decl         nudges K1 pseudo-creation order → RC-1
  perm_struct_ref           a->b ↔ (*a).b access SHAPE → RC-1 (spill vs temp vs MEM)
  perm_ins_block            scoping → RC-5 pin/var range
  (value/type noise, down-weighted for count-exact residuals): perm_add_mask, perm_xor_zero,
  perm_mult_zero, perm_add_sub, perm_inequalities, perm_cast_simple, perm_refer_to_var,
  perm_float_literal, perm_condition, perm_dummy_comma_expr, perm_compound_assignment,
  perm_randomize_{internal,external,function}_type, perm_empty_stmt, perm_remove_ast.
"""
import re

# --- The class profiles ------------------------------------------------------------------
# Each maps perm_* pass -> weight (REPLACES the gcc default for that key). Absent keys keep
# their gcc default (default_weights.toml [base]+[gcc]). Noise passes are pushed to ~0.1 (not
# a hard 0 — keep a sliver of diversity) so the search spends its budget on the class's levers.

_NOISE = {
    "perm_add_mask": 0.1, "perm_xor_zero": 0.1, "perm_mult_zero": 0.1,
    "perm_add_sub": 0.1, "perm_inequalities": 0.1, "perm_cast_simple": 0.3,
    "perm_refer_to_var": 0.2, "perm_float_literal": 0.1, "perm_condition": 0.3,
    "perm_dummy_comma_expr": 0.1, "perm_compound_assignment": 0.3,
    "perm_randomize_internal_type": 1.0, "perm_randomize_external_type": 0.2,
    "perm_randomize_function_type": 0.2, "perm_empty_stmt": 0.5, "perm_remove_ast": 0.5,
    "perm_inline": 1.0,
}

# REGALLOC — RC-1/2/3, S7, S11 register-permutation: decl-order + range-shaping + boost, under
# the draft's hand-applied pins holding the callee-saved core stable (§31 S11 protocol).
_REGALLOC = {
    "perm_reorder_decls": 40.0,      # RC-1 slot order, RC-3 tie order — THE regalloc lever
    "perm_reorder_stmts": 40.0,      # RC-2 range shaping / S11 LUID
    "perm_temp_for_expr": 60.0,      # S2 boost / fresh single-set (the workhorse)
    "perm_split_assignment": 20.0,
    "perm_expand_expr": 15.0,
    "perm_duplicate_assignment": 8.0,
    "perm_add_self_assignment": 8.0,
    "perm_struct_ref": 8.0,          # access SHAPE (RC-1)
    "perm_pad_var_decl": 5.0,        # K1 creation-order nudge
    "perm_ins_block": 6.0,           # RC-5 scope
    "perm_sameline": 4.0,
    "perm_commutative": 2.0,
    "perm_chain_assignment": 2.0, "perm_long_chain_assignment": 1.0,
    **_NOISE,
}

# SCHEDULE — S1..S5, D1..D4: statement reorder dominates (LUID), plus S2 boost + S4 fillers.
_SCHEDULE = {
    "perm_reorder_stmts": 60.0,      # THE schedule lever (LUID order)
    "perm_temp_for_expr": 60.0,      # S2 boost
    "perm_expand_expr": 25.0,        # S2 kill / re-decompose
    "perm_reorder_decls": 15.0,
    "perm_split_assignment": 15.0,
    "perm_duplicate_assignment": 8.0, "perm_add_self_assignment": 8.0,
    "perm_ins_block": 10.0, "perm_empty_stmt": 5.0,   # S4 filler (empty_stmt un-suppressed here)
    "perm_sameline": 6.0,
    "perm_commutative": 4.0,
    "perm_struct_ref": 5.0,
    **{k: v for k, v in _NOISE.items() if k != "perm_empty_stmt"},
}

# CSE / COMBINE — operand-order + re-decomposition canonicalization (func_80148094 mult-order).
_CSE = {
    "perm_commutative": 40.0,        # mult/add operand order — the cse-canon residual
    "perm_expand_expr": 40.0,        # re-decompose a folded expression
    "perm_split_assignment": 30.0,
    "perm_temp_for_expr": 60.0,
    "perm_factor_mult": 10.0, "perm_factor_shift": 8.0,   # product re-decomposition
    "perm_reorder_stmts": 15.0, "perm_reorder_decls": 10.0,
    "perm_add_sub": 4.0,
    **{k: v for k, v in _NOISE.items()
       if k not in ("perm_add_sub",)},
}

# LENGTH — a +-1..2 instruction-count delta (Phase-29 Task-13B). The residual is not WHICH
# registers or WHAT order, it is one instruction too many or too few, so the levers are the passes
# that materialize or dissolve a temporary: perm_temp_for_expr (introduce a temp -> an extra
# move/load), perm_expand_expr (inline a temp -> one fewer), perm_split_assignment (split one
# statement into two). The reorder/decl-order levers that dominate the regalloc/schedule profiles
# cannot change an instruction COUNT at all, so they are down-weighted here rather than up.
_LENGTH = {
    "perm_temp_for_expr": 70.0,       # introduce a temp -> +1 insn (THE lever in this direction)
    "perm_expand_expr": 70.0,         # inline a temp     -> -1 insn (THE lever in the other)
    "perm_split_assignment": 40.0,
    "perm_duplicate_assignment": 20.0, "perm_add_self_assignment": 20.0,
    "perm_cast_simple": 15.0,         # a cast can add/remove a widening insn
    "perm_add_mask": 10.0,            # an explicit mask can materialize an andi
    "perm_ins_block": 8.0, "perm_empty_stmt": 6.0,
    "perm_reorder_stmts": 10.0, "perm_reorder_decls": 8.0,   # count-neutral: kept low
    "perm_commutative": 4.0, "perm_struct_ref": 6.0,
    **{k: v for k, v in _NOISE.items()
       if k not in ("perm_cast_simple", "perm_add_mask", "perm_empty_stmt")},
}

PROFILES = {"regalloc": _REGALLOC, "schedule": _SCHEDULE, "cse": _CSE, "length": _LENGTH}

# --- The classifier ----------------------------------------------------------------------
# Precedence: the `klass` TAG is the primary bucket (a seed tagged `regalloc-order` gets the
# regalloc profile even though its `where` text mentions LUID/schedule mechanism), EXCEPT a cse
# residual (mult-canon / operand-order) overrides — it wants the commutative-heavy profile no
# matter the tag (func_80148094 is tagged regalloc-order but its residual is a cse mult-order).
# A generic tag (WAVE/GIANT/none) falls back to the longer `where` diagnosis. Unknown -> None
# (broad gcc default: a safe superset — never worse than today's undirected search).
_CSE_RE = re.compile(r"cse|combine|mult-?canon|canonicali|operand-?order|neg\w*first|mem-?first", re.I)
_REGALLOC_TAG = re.compile(r"regalloc|reg-?alloc|remat|spill|coalesc|pressure|prologue|-order\b|\brc-?\d", re.I)
_SCHED_TAG = re.compile(r"sched|\bs[1-9]\b|\bd[1-9]\b|delay|birthing|chain-?prior|dbr", re.I)
# `where`-text fallbacks (only consulted when the klass tag is generic): note S11/S10 must NOT
# read as the S1 schedule token, so the schedule fallback excludes a following digit.
_SCHED_WHERE = re.compile(r"schedul|\bs[1-9](?![0-9])\b|\bd[1-9]\b|delay-?slot|birthing|chain-?prior|dbr|luid", re.I)
_REGALLOC_WHERE = re.compile(r"regalloc|reg-?alloc|\brc-?\d|s1[01]\b|s7\b|spill|callee-?saved|coalesc|pressure|prologue-?weave|allocno", re.I)


def classify(klass, where=""):
    """residual class string(s) -> profile name in {'cse','schedule','regalloc'} or None.

    `klass` = the short class TAG (backlog `klass` / .c `@class:`); `where` = the longer
    diagnosis text (backlog `where_stuck`). The tag decides the primary bucket; cse residuals
    override; a generic tag falls back to the where text.
    """
    kt = klass or ""
    wt = where or ""
    # A caller may pass a PROFILE NAME directly — tools/residual_class.py derives the profile from
    # the bytes, which is strictly better than re-deriving it from a free-text label (91% of backlog
    # records carry no label at all). Accept it verbatim rather than round-tripping through regexes
    # that were written to parse an agent's prose.
    if kt in PROFILES:
        return kt
    if _CSE_RE.search(kt) or _CSE_RE.search(wt):     # residual-level override
        return "cse"
    if _REGALLOC_TAG.search(kt):
        return "regalloc"
    if _SCHED_TAG.search(kt):
        return "schedule"
    # generic tag (WAVE / GIANT / None) -> use the diagnosis text
    if _SCHED_WHERE.search(wt):
        return "schedule"
    if _REGALLOC_WHERE.search(wt):
        return "regalloc"
    return None


def weight_overrides_for(klass, where=""):
    """residual class -> the {perm_*: weight} override dict (empty if unknown/None)."""
    prof = classify(klass, where)
    return dict(PROFILES.get(prof, {}))


def render_settings_toml(fn, compiler_type="gcc", klass=None, where=""):
    """the full settings.toml body: func_name + compiler_type + (optional) [weight_overrides].
    Empty overrides => no table => decomp-permuter uses the plain gcc defaults (unchanged)."""
    prof = classify(klass, where)
    ov = dict(PROFILES.get(prof, {}))
    lines = [f'func_name = "{fn}"', 'compiler_type = "%s"' % compiler_type]
    if ov:
        lines.append("")
        lines.append(f"# §31-directed mutation (Phase 24 T5): profile={prof} for class={klass!r}")
        lines.append("[weight_overrides]")
        for k in sorted(ov):
            lines.append(f"{k} = {float(ov[k])}")
    return "\n".join(lines) + "\n", prof


if __name__ == "__main__":
    import sys
    klass = sys.argv[1] if len(sys.argv) > 1 else "regalloc-order"
    where = sys.argv[2] if len(sys.argv) > 2 else ""
    body, prof = render_settings_toml("func_TEST", klass=klass, where=where)
    print(f"# classify({klass!r}, {where!r}) -> profile={prof}\n")
    print(body)
