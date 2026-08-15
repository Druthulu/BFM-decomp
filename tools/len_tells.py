#!/usr/bin/env python3
"""P31 T8 — classify a LEN±N near-miss (draft vs its OWN target) and build the routing card.

This is where `family_align` earns its keep (the T7 probe refuted the cousin use — but a draft vs
its own target is the SAME function, so registers agree outside the drift and the aligned
classifier's premise holds). Per draft:

  - align draft↔target word streams (family_align.classify_aligned; draft = ex side, so the
    mechanical repair swaps DRAFT literals toward the TARGET's)
  - LEN-LI with resolvable clusters  -> MECHANICAL repair candidate (swap the C literal, recompile)
  - LEN-NOP / |Δ|<=2 clean drift     -> permuter `length` profile
  - LEN-STRUCT                        -> tag the target-side indels with the §172b tells
        EXTPAIR  target-extra sll/sra promotion pair  (a multi-def s16/s8 the draft collapsed)
        SELECT   target-extra slt+branch select       (a swapped-arm textual repeat)
    -> agent tell-cards (the §172b cookbook text rides on the card)
  - frac > 0.35                       -> redraft (SIZE-MISMATCH — the draft is not the function)

Detectors are IMPORTED from atlas_features (one implementation, R33).
"""
import os, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import family_align as FA
from atlas_features import extpair_count, dupselect_count

COOKBOOK = {
    "EXTPAIR": "§172b-1: the target's extra sll/sra-16|24 pair = a REGISTER-held short promotion "
               "(a multi-def s16/s8 variable, e.g. branch-merged); keep the short in a named local "
               "used both ways so the promotion pair exists.",
    "SELECT": "§172b-2: the target's extra slt+branch+move select = the source textually REPEATED "
              "a compare with SWAPPED arms ((b>a)?b:a vs (a<b)?a:b); repeat the expression with "
              "swapped operands at the extra site.",
    "NOP": "schedule artifact — route to the permuter length profile, not an edit.",
}


def analyze(mine_words, tgt_words):
    """-> card dict {verdict, delta, frac, clusters, tells, blocks, route}."""
    delta = len(tgt_words) - len(mine_words)
    frac = abs(delta) / max(1, len(tgt_words))
    verdict, detail = FA.classify_aligned(mine_words, tgt_words)

    tells = []
    blocks = []
    if verdict in ("LEN-STRUCT", "STRUCT-ALIGNED"):
        ops = FA.align_blocks(mine_words, tgt_words)
        for tag, i1, i2, j1, j2 in ops:
            if tag == "equal":
                continue
            tw = tgt_words[max(0, j1 - 2):min(len(tgt_words), j2 + 2)]
            kinds = []
            if extpair_count(tw):
                kinds.append("EXTPAIR")
            if dupselect_count(tgt_words[max(0, j1 - 8):min(len(tgt_words), j2 + 8)]):
                kinds.append("SELECT")
            if all(w == 0 for w in tgt_words[j1:j2]) and i1 == i2:
                kinds.append("NOP")
            blocks.append({"mine": [i1, i2], "tgt": [j1, j2], "kinds": kinds,
                           "tgt_words": [f"{w:08x}" for w in tgt_words[j1:j2][:12]]})
            tells += kinds
    clusters = [(hex(a), hex(b)) for a, b, _ in detail.get("clusters", [])]

    if frac > 0.35:
        route = "redraft"
    elif verdict == "LEN-LI" and clusters and all(a != b for a, b in clusters):
        route = "mechanical"
    elif verdict == "LEN-NOP" or (verdict.startswith("LEN") and abs(delta) <= 2 and not tells):
        route = "permuter-length"
    elif tells:
        route = "tell-card"
    elif verdict in ("PURE", "IMM"):
        route = "imm-or-reloc"          # equal length reached here = not a LEN case at all
    else:
        route = "card"
    return {"verdict": verdict, "delta": delta, "frac": round(frac, 3),
            "clusters": clusters, "tells": sorted(set(tells)),
            "tell_refs": [COOKBOOK[t] for t in sorted(set(tells)) if t in COOKBOOK],
            "blocks": blocks[:8], "route": route,
            "detail": detail if route == "mechanical" else None}


def repair_mechanical(draft_text, mine_words, tgt_words, detail):
    """Swap the draft's cluster/imm literals toward the target's. -> (new_text, unresolved)."""
    return FA.imm_map_aligned(draft_text, mine_words, tgt_words, detail)
