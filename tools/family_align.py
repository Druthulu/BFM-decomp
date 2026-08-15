#!/usr/bin/env python3
"""P31 T7 — the LEN-tolerant aligned classifier + the mechanical LEN-LI engine (plan Leg B / A1).

WHY A NEW MODULE (design decision D1): `family_remap.classify_member` refuses any length drift with
`("LEN", [])`, and `remap_hseq` tests `cls in ("STRUCT","LEN")` — an unknown class string returned
from classify_member would silently PASS that check into index-zipped machinery (`imm_map_tier1`
indexes sib_words[k] over ex indices). So the aligned engine lives here with NEW entry points;
every existing caller keeps its exact refusal behavior (R39-safe by construction).

WHAT IT DOES: align a member's word stream against a MATCHED seed's via SequenceMatcher over
`family_cousins.tok` streams; classify the drift:

  LEN-LI       every indel region is a recognized li-CLUSTER (constant materialization whose
               instruction count changed — lui/ori/addiu chains; the measured dominant near-pair
               drift, §168: the ex and sib spell DIFFERENT CONSTANTS in different lengths) and
               every remaining aligned pair is PURE/IMM  ->  FULLY MECHANICAL: same C, swap the
               constant literal, cc1 re-emits the right instruction count.
  LEN-NOP      indel is nop-only -> permuter `length` profile (schedule artifact, not a literal).
  LEN-JTBL     indel adjacent to a mid-fn jr -> jtbl carve lane.
  LEN-STRUCT   any other indel, or an unrecognized cluster -> agent cards.
  STRUCT-ALIGNED  an aligned pair drifts in registers/opcode -> agent cards / warmstart.
  PURE / IMM   equal-length equivalents of classify_member's verdicts (NC-1 asserts equivalence).

THE LI-CLUSTER SUBTLETY (measured on the tok streams): a 1-ins li (`addiu rt,$0,imm`) aligning
against a 2-ins li (`lui rt,hi; addiu rt,rt,lo`) pairs the two `addiu`s as an EQUAL tok block —
but that pair differs in rs ($0 vs rt), which a naive per-pair scan calls register drift. So each
indel region is EXTENDED to absorb adjacent differing li-class pairs that continue the cluster's
dest-register chain, and the whole cluster is reconstructed to ONE constant per side.

Byte-gate note: everything here is ADVISORY routing + draft construction — `harvest_verify`
remains the sole arbiter (G3/P9); a wrong cluster read costs a build, never a wrong bank.
"""
import collections, os, sys
from difflib import SequenceMatcher

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import family_remap as FR
import family_cousins as FC

LI_OPS = {0x0F, 0x0D, 0x09}          # lui, ori, addiu


def align_blocks(ex_words, sib_words):
    """SequenceMatcher opcodes over the two tok streams (R33: family_cousins.tok is THE tokenizer)."""
    a = [FC.tok(w) for w in ex_words]
    b = [FC.tok(w) for w in sib_words]
    return SequenceMatcher(None, a, b, autojunk=False).get_opcodes()


def _li_const(words, idxs):
    """Reconstruct ONE li chain over `idxs` (ordered) -> (dest_reg, value32) or None.
    Recognizes: lui / lui+addiu / lui+ori / addiu-from-$0 / ori-from-$0."""
    v = dest = None
    for k in idxs:
        w = words[k]
        op = w >> 26
        rt, rs, imm = (w >> 16) & 31, (w >> 21) & 31, w & 0xFFFF
        if op == 0x0F:                                   # lui rt, hi
            if v is not None:
                return None                              # a second chain in one region
            dest, v = rt, imm << 16
        elif op in (0x09, 0x0D):                         # addiu / ori
            if v is None:
                if rs != 0:
                    return None                          # not li-from-zero
                dest = rt
                v = (imm - 0x10000 if imm >= 0x8000 else imm) if op == 0x09 else imm
            else:
                if rs != dest or rt != dest:
                    return None                          # chain broken
                v = (v + (imm - 0x10000 if imm >= 0x8000 else imm)) if op == 0x09 else (v | imm)
        else:
            return None
    return (dest, v & 0xFFFFFFFF) if dest is not None else None


_ADDR_RANGES = ((0x80010000, 0x80200000), (0x1F800000, 0x1F810000))


def addr_true_rel(words):
    """`reloc_indices` minus the lui-anchor pairs whose combined hi+lo value is NOT a plausible
    address (T8: `reloc_indices` conservatively flags EVERY lui+consumer as an anchor — right for
    h_norm masking, wrong for li-cluster recognition, where a 32-bit CONSTANT materialization must
    stay eligible). jal indices are always kept. The pairing walk mirrors norm_stream's tracker."""
    rel = FR.reloc_indices(words)
    keep = set()
    pending = {}                                          # reg -> (lui_idx, hi)
    for k, w in enumerate(words):
        op = w >> 26
        if op in (2, 3):                                  # j/jal
            keep.add(k)
            continue
        if op == 0x0F:                                    # lui
            pending[(w >> 16) & 31] = (k, (w & 0xFFFF) << 16)
            continue
        rs, rt = (w >> 21) & 31, (w >> 16) & 31
        if k in rel and rs in pending:
            lk, hi = pending[rs]
            imm = w & 0xFFFF
            lo = imm - 0x10000 if imm >= 0x8000 and op in (0x09, 0x23, 0x21, 0x25, 0x20, 0x24,
                                                           0x2B, 0x29, 0x28, 0x22, 0x26, 0x2A, 0x2E) else imm
            v = (hi + lo) & 0xFFFFFFFF
            if any(a <= v < b for a, b in _ADDR_RANGES):
                keep.add(lk)
                keep.add(k)
            # else: a constant materialization — both indices stay OUT of the address-true set
        # register kill tracking (approximate, matches reloc_indices' conservatism)
        if op == 0:
            pending.pop((w >> 11) & 31, None)
        else:
            pending.pop(rt, None)
    return keep


def classify_aligned(ex_words, sib_words):
    """-> (verdict, detail). detail: {'pairs', 'clusters': [(exv,sibv)], 'imm_pairs', 'reasons'}.
    Equal-length identical-tok inputs reproduce classify_member's PURE/IMM/STRUCT verdicts (NC-1).
    TWO reloc sets per side: the FULL conservative set (classify_member-equivalent pair semantics,
    NC-1) and the ADDRESS-TRUE subset (indel-region eligibility only — a constant li-cluster must
    not read as 'reloc-in-indel')."""
    rel_ex = FR.reloc_indices(ex_words)
    rel_sib = FR.reloc_indices(sib_words)
    rel_ex_addr = addr_true_rel(ex_words)
    rel_sib_addr = addr_true_rel(sib_words)
    ops = align_blocks(ex_words, sib_words)

    pairs = []                                            # aligned (i, j) index pairs
    regions = []                                          # non-equal blocks
    for tag, i1, i2, j1, j2 in ops:
        if tag == "equal":
            pairs += [(i1 + k, j1 + k) for k in range(i2 - i1)]
        else:
            regions.append([i1, i2, j1, j2])

    reasons = []
    if not regions:
        # equal tok streams: pure per-pair classification (classify_member semantics)
        cls, imm_pairs, struct = _classify_pairs(ex_words, sib_words, pairs, rel_ex, rel_sib, set(), set())
        if struct:
            return "STRUCT-ALIGNED", {"reasons": struct[:4]}
        return ("IMM" if imm_pairs else "PURE"), {"pairs": pairs, "clusters": [],
                                                  "imm_pairs": imm_pairs, "reasons": []}

    # extend each region over adjacent DIFFERING li-class pairs (the split-cluster absorb), then
    # classify the region
    pair_pos = {p: n for n, p in enumerate(pairs)}
    consumed_pairs = set()
    clusters = []
    verdict_flags = set()
    for i1, i2, j1, j2 in regions:
        ex_idx = list(range(i1, i2))
        sib_idx = list(range(j1, j2))
        # absorb following aligned li pairs that differ and continue a chain
        nxt = pair_pos.get((i2, j2))
        while nxt is not None and nxt < len(pairs):
            i, j = pairs[nxt]
            if (i, j) in consumed_pairs:
                break
            we, ws = ex_words[i], sib_words[j]
            if we == ws or (we >> 26) not in LI_OPS or (ws >> 26) not in LI_OPS:
                break
            ex_idx.append(i)
            sib_idx.append(j)
            consumed_pairs.add((i, j))
            nxt = pair_pos.get((i + 1, j + 1))
        region_words_ex = [ex_words[k] for k in ex_idx]
        region_words_sib = [sib_words[k] for k in sib_idx]
        all_ops = [w >> 26 for w in region_words_ex + region_words_sib]
        if all(w == 0 for w in region_words_ex + region_words_sib):
            verdict_flags.add("NOP")
            continue
        if any(k in rel_ex_addr for k in ex_idx) or any(k in rel_sib_addr for k in sib_idx):
            reasons.append("reloc-in-indel")
            verdict_flags.add("STRUCT")
            continue
        if any((ex_words[k] >> 26) == 0 and (ex_words[k] & 0x3F) == 0x08 and ((ex_words[k] >> 21) & 31) != 31
               for k in ex_idx if ex_words[k]) or \
           any((sib_words[k] >> 26) == 0 and (sib_words[k] & 0x3F) == 0x08 and ((sib_words[k] >> 21) & 31) != 31
               for k in sib_idx if sib_words[k]):
            verdict_flags.add("JTBL")
            continue
        if not all(op in LI_OPS for op in all_ops):
            reasons.append("non-li-indel")
            verdict_flags.add("STRUCT")
            continue
        ce = _li_const(ex_words, ex_idx) if ex_idx else None
        cs = _li_const(sib_words, sib_idx) if sib_idx else None
        if ce is None or cs is None or ce[0] != cs[0]:
            reasons.append("cluster-unrecognized")
            verdict_flags.add("STRUCT")
            continue
        clusters.append((ce[1], cs[1], tuple(ex_idx)))

    live_pairs = [p for p in pairs if p not in consumed_pairs]
    cls, imm_pairs, struct = _classify_pairs(ex_words, sib_words, live_pairs, rel_ex, rel_sib,
                                             set(), set())
    if struct:
        return "STRUCT-ALIGNED", {"reasons": (struct + reasons)[:6]}
    if "STRUCT" in verdict_flags:
        return "LEN-STRUCT", {"reasons": reasons[:6]}
    if "JTBL" in verdict_flags:
        return "LEN-JTBL", {"reasons": reasons[:6]}
    if "NOP" in verdict_flags and not clusters:
        return "LEN-NOP", {"pairs": live_pairs, "clusters": [], "imm_pairs": imm_pairs, "reasons": []}
    return "LEN-LI", {"pairs": live_pairs, "clusters": clusters, "imm_pairs": imm_pairs,
                      "reasons": reasons}


def _classify_pairs(ex_words, sib_words, pairs, rel_ex, rel_sib, skip_ex, skip_sib):
    """classify_member's per-word semantics over aligned pairs. -> (cls, imm_pairs, struct_reasons)."""
    imm_pairs = []
    struct = []
    for i, j in pairs:
        we, ws = ex_words[i], sib_words[j]
        if we == ws:
            continue
        # classify_member's TEST ORDER: registers first — a reloc-slot word whose REGISTER differs
        # is STRUCT (symbol_map substitutes the target, never the register), so reg_fields must be
        # checked BEFORE the reloc skip (NC-1's ov_SC01_074 store-rt case).
        if FR.reg_fields(we) != FR.reg_fields(ws):
            struct.append(f"regfields@{i}")
            continue
        in_rel_e, in_rel_s = i in rel_ex, j in rel_sib
        if in_rel_e and in_rel_s:
            continue                                       # symbol_map's job
        if in_rel_e != in_rel_s:
            struct.append(f"reloc-shape@{i}")
            continue
        # classify_member semantics: an R-type diff with equal reg_fields differs only in sa —
        # IMM for real shifts (sll/srl/sra), STRUCT for anything else (NC-1's one mismatch).
        if (we >> 26) == 0 and (we & 0x3F) not in (0x00, 0x02, 0x03):
            struct.append(f"rtype-sa@{i}")
            continue
        imm_pairs.append((i, j))
    return ("IMM" if imm_pairs else "PURE"), imm_pairs, struct


def _swap_variants(v):
    """Candidate human renderings of a 32-bit li constant for _c_literal_swap lookup."""
    out = [v]
    if v >= 0x80000000:
        out.append(v - 0x100000000)                       # signed form
    return out


def imm_map_aligned(unit, ex_words, sib_words, detail):
    """The tier-1 imm engine generalized to aligned pairs + li clusters. -> (unit', unresolved).

    Semantics mirror `imm_map_tier1`: build ex-value -> sib-value candidates from the differing
    aligned pairs (reloc slots excluded — symbol_map's job) plus the reconstructed cluster
    constants; refuse multi-target and fixed-position-ambiguous values; swap via the same
    `_c_literal_swap` primitive (format-preserving). Ordinal resolution is deliberately OUT in v1
    (refused as 'asm-ambiguous'); add if a probe prices it in (R37)."""
    rel_ex = FR.reloc_indices(ex_words)
    valpos = [FR.imm_value(w, k in rel_ex) for k, w in enumerate(ex_words)]
    diff_ex = {i for i, _ in detail.get("imm_pairs", [])}
    cluster_ex = set()
    for _, _, idxs in detail.get("clusters", []):
        cluster_ex.update(idxs)

    by_val = collections.defaultdict(set)
    unresolved = []
    for i, j in detail.get("imm_pairs", []):
        ev = valpos[i]
        if ev is None:
            unresolved.append((f"@{i}", "non-imm diff"))
            continue
        by_val[ev].add(FR.imm_value(sib_words[j], False))
    for exv, sibv, _idxs in detail.get("clusters", []):
        evs = exv if exv < 0x80000000 else exv - 0x100000000      # signed rendering
        svs = sibv if sibv < 0x80000000 else sibv - 0x100000000
        by_val[evs].add(svs)

    for exv, sibvs in sorted(by_val.items(), key=lambda kv: str(kv[0])):
        if len(sibvs) != 1 or None in sibvs:
            unresolved.append((exv, "multi-target"))
            continue
        sibv = next(iter(sibvs))
        # a value that ALSO occurs at a fixed (non-diff, non-cluster) position would be corrupted
        # by a global swap — tier-1 tries the ordinal engine here; v1 refuses (conservative).
        fixed_use = any(valpos[k] == exv for k in range(len(ex_words))
                        if k not in diff_ex and k not in cluster_ex and valpos[k] is not None)
        if fixed_use:
            unresolved.append((exv, "asm-ambiguous"))
            continue
        tok = rep = None
        for ev in _swap_variants(exv if exv >= 0 else exv + 0x100000000):
            tok, rep = FR._c_literal_swap(unit, ev, sibv)
            if tok is not None:
                break
        if tok is None:
            unresolved.append((exv, "not-in-C"))
            continue
        unit = _apply_swap(unit, tok, rep)
    return unit, unresolved


def _apply_swap(unit, tok, rep):
    """Word-bounded single-token swap on the C text (all occurrences of the literal token —
    matching tier-1's imm_map semantics, which apply_remap substitutes globally)."""
    import re
    return re.sub(rf"(?<![\w]){re.escape(tok)}(?![\w])", rep, unit)


def classify_ref(seed_ref, member_ref):
    """Convenience: classify from (binary, addr, nins) refs."""
    ex = FR.stream_words(seed_ref[0], seed_ref[1], seed_ref[2])
    sib = FR.stream_words(member_ref[0], member_ref[1], member_ref[2])
    if ex is None or sib is None:
        return "NO-STREAM", {}
    return classify_aligned(ex, sib)
