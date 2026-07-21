#!/usr/bin/env python3
"""residual_class.py — the DETERMINISTIC residual→class classifier (Phase-29 Task-13A).

The permuter-failure autopsy (docs/hindsight-study.md §7) needs to route every plateau to one of
  missing-transform | mis-classified | seed-structural | genuine-wall
and today that routing is done by an LLM reading a scalar (`closeness`) plus a free-text
`where_stuck` label a wave agent typed months ago. Both are weak: 91% of the open backlog has NO
class label at all (1,597 of 1,752), so `permuter_weights.classify()` returns None and the grinder
searches UNDIRECTED over almost the whole corpus.

This module decides the class FROM THE BYTES. It is deterministic, LLM-free, and cheap, so the
expensive tier is spent only on what it genuinely cannot decide.

WHAT IT READS. Two aligned instruction streams (`masked_diff.insns_from_object` /
`insns_from_s`) — MY compiled draft and the ORIGINAL target. Masking is match_one semantics
(mask driven by MY object's relocs; the .s target is already resolved), so this module's
`closeness` is EXACTLY `len(masked_diff.structured_diff(mine, tgt))` and the collector asserts
that equality against the independent existing implementation (R34: a second oracle that can
disagree, not a better assertion inside one).

THE ONE THING IT ADDS THAT `closeness` CANNOT SAY. `closeness` is index-wise, so a SINGLE extra
instruction at index 8 of a 200-instruction function reports ~192 mismatches and looks like a
catastrophic wall. It is a one-instruction structural delta. Drift detection runs FIRST and
collapses it back, because that inflated number is precisely what routes a fixable draft into a
"genuine wall" verdict — the failure mode this project has manufactured repeatedly (Phase-26's
≈0% doctrine, the func_80178004 close=0 ledger myth, the 155 PC16 closeness lies).

THE CLASSES (decision tree, first match wins; every path terminates in a NAMED class — an
unclassifiable residual is `UNKNOWN`, COUNTED, never silently bucketed, R32):

  MATCH               streams identical under the mask
  LENGTH-DRIFT        len differs and ONE shift point explains the whole tail  -> permuter
                      if |delta|<=2 (profile `length`), else structural
  SIZE-MISMATCH       len differs wildly and no shift explains it: the draft is -> redraft
                      a different-sized function, never a near-miss
  SHIFT-DRIFT         len equal but a small shift re-aligns most of the tail   -> structural
  REGALLOC-PERM       every diff is register-only AND a consistent injective   -> regalloc
                      register map explains them all (the §31 S11/RC-3 class)
  SCHEDULE-REORDER    the diff positions hold the SAME masked instructions in  -> schedule
                      a different order (S1..S5 LUID / chain-priority)
  DELAY-SLOT          nop-vs-instruction at the diff positions (D1..D4)        -> schedule
  REGALLOC-LOCAL      register-only diffs, no consistent global map            -> regalloc
  WIDTH               load/store WIDTH flip (lw↔lh↔lb, sw↔sh↔sb)               -> structural (idiom)
  STRENGTH            mult/div ↔ shift/add re-association                      -> cse
  ADDRESSING          addu/addiu/lui base-address shape (§10 hoist-vs-remat)   -> cse
  BRANCH-POLARITY     beq↔bne / bgez↔bltz (loop-guard operand order)           -> structural (idiom)
  OPCODE-MIXED        different operations, no single family                   -> structural
  IMM-OFFSET          same ops+regs, immediates differ by a CONSTANT (a frame  -> structural
                      or struct-layout shift)
  IMM-VALUE           same ops+regs, unrelated immediates (wrong constant)     -> cse
  MIXED               several kinds, none dominant                             -> unknown
  UNKNOWN             an opcode the field decoder does not cover               -> unknown

BUCKETS (what the autopsy does with it):
  permuter    — local mutation CAN reach it; the permuter is the right tool (and if it plateaued
                anyway, that is a genuine missing-transform candidate — the highest-value bucket)
  structural  — local mutation CANNOT introduce it (a different access width, a flipped
                branch, a multi-instruction shape change). Spending permuter CPU here is waste; it wants a
                C-level idiom, and WIDTH / BRANCH-POLARITY / IMM-OFFSET map to KNOWN cookbook
                idioms (§18 cast-at-use, §43 K&R s16, the loop-guard class).
  integration — closeness 0: byte-correct standalone, blocked purely on plumbing (§58/§59). The
                permuter can never help; the reconcile ladder is the tool.
  redraft     — the stored draft is not this function (a stub-sized body against a large target).
                Not a wall and not a near-miss: UN-ATTEMPTED work misfiled as a near-miss. Route it
                to a fresh crack, and never let its inflated closeness rank it as "nearly done".
  unknown     — the residue the LLM tier is for.

NOT A GATE. Like every closeness metric in this repo, a verdict here is a CANDIDATE. The
whole-binary byte-gate (tools/harvest_verify.py) remains the sole arbiter (G3/P9).
"""
import collections

import masked_diff

# --------------------------------------------------------------------------------------------
# MIPS-I field decoding — the primitive the whole classifier rests on
# --------------------------------------------------------------------------------------------
# decode(word) -> (skel, regs, imm)
#   skel : hashable identity of the OPERATION with every register and immediate field removed.
#          Two words with equal skel do the same thing to (possibly) different operands.
#   regs : tuple of (role, slot, value); role 'g' = GPR, 'c' = coprocessor register.
#   imm  : the immediate / shift-amount / trap-code field, or None where the format has none.
#
# Coverage is asserted, not assumed (R32): an opcode outside the table raises UnknownOpcode and
# the caller COUNTS it as UNKNOWN. A silent fallthrough here would misread a coprocessor word as
# a register difference and invent a regalloc verdict out of nothing.


_KEEP = object()          # _v() sentinel: keep the static _ROUTE entry


class UnknownOpcode(Exception):
    pass


def decode(w):
    op = w >> 26
    rs, rt, rd = (w >> 21) & 31, (w >> 16) & 31, (w >> 11) & 31
    sa, fn, imm = (w >> 6) & 31, w & 63, w & 0xFFFF

    if op == 0:                                    # SPECIAL (R-type)
        if fn in (12, 13):                         # syscall / break — the 20-bit code is ONE field
            return ("sp", fn), (), (w >> 6) & 0xFFFFF
        return ("sp", fn), (("g", 0, rs), ("g", 1, rt), ("g", 2, rd)), sa
    if op == 1:                                    # REGIMM — rt IS the sub-opcode, not a register
        return ("ri", rt), (("g", 0, rs),), imm
    if op in (2, 3):                               # j / jal — the target is a link-time value
        return ("j", op), (), None
    if op in (4, 5, 6, 7):                         # beq / bne / blez / bgtz
        return ("b", op), (("g", 0, rs), ("g", 1, rt)), imm
    if 8 <= op <= 14:                              # addi addiu slti sltiu andi ori xori
        return ("i", op), (("g", 0, rs), ("g", 1, rt)), imm
    if op == 15:                                   # lui — rs unused
        return ("i", op), (("g", 1, rt),), imm
    if op in (16, 17, 18, 19):                     # COP0..COP3 (op 18 = COP2 = GTE)
        if rs & 0x10:                              # bit 25 set -> a COP function word (no GPRs)
            return ("cf", op, w & 0x1FFFFFF), (), None
        if rs == 8:                                # BCzT / BCzF
            return ("cb", op, rt), (), imm
        return ("cm", op, rs), (("g", 1, rt), ("c", 2, rd)), None   # mfcz/mtcz/cfcz/ctcz
    if 32 <= op <= 38 or 40 <= op <= 46:           # lb lh lwl lw lbu lhu lwr / sb sh swl sw swr
        return ("m", op), (("g", 0, rs), ("g", 1, rt)), imm
    if 48 <= op <= 51 or 56 <= op <= 59:           # LWCz / SWCz (op 50/58 = GTE load/store)
        return ("m", op), (("g", 0, rs), ("c", 1, rt)), imm
    raise UnknownOpcode(op)


# mnemonic families for sub-classifying an OPERATION difference. The mnemonic text comes from
# objdump and is used ONLY to name the family; every equality decision is made on the word.
_WIDTH = {"lb", "lbu", "lh", "lhu", "lw", "lwl", "lwr", "sb", "sh", "sw", "swl", "swr"}
_STRENGTH = {"mult", "multu", "div", "divu", "mfhi", "mflo", "sll", "srl", "sra",
             "sllv", "srlv", "srav"}
_ADDRESSING = {"addu", "addiu", "add", "addi", "subu", "sub", "lui", "ori"}
_BRANCH = {"beq", "bne", "blez", "bgtz", "bltz", "bgez", "bltzal", "bgezal", "b", "beqz", "bnez"}


def _mnem(s):
    return (s or "").split()[0] if s else ""


# --------------------------------------------------------------------------------------------
# the classifier
# --------------------------------------------------------------------------------------------
# Profile = the permuter_weights profile this class's levers live in. None = no directed profile
# (the permuter would run on gcc defaults; for a structural class it should not run at all).
_ROUTE = {
    "MATCH":            (None,       "integration"),
    "LENGTH-DRIFT":     (None,       "structural"),
    "SIZE-MISMATCH":    (None,       "redraft"),
    "SHIFT-DRIFT":      (None,       "structural"),
    "REGALLOC-PERM":    ("regalloc", "permuter"),
    "SCHEDULE-REORDER": ("schedule", "permuter"),
    "DELAY-SLOT":       ("schedule", "permuter"),
    "REGALLOC-LOCAL":   ("regalloc", "permuter"),
    "WIDTH":            (None,       "structural"),
    "STRENGTH":         ("cse",      "structural"),
    "ADDRESSING":       ("cse",      "permuter"),
    "BRANCH-POLARITY":  (None,       "structural"),
    "OPCODE-MIXED":     (None,       "structural"),
    "IMM-OFFSET":       (None,       "structural"),
    "IMM-VALUE":        ("cse",      "permuter"),
    "MIXED":            (None,       "unknown"),
    "UNKNOWN":          (None,       "unknown"),
    "EMPTY":            (None,       "unknown"),
}

KLASSES = tuple(_ROUTE)


def _masks(mine):
    return [masked_diff.mask_for(i["word"], i["reloc_kind"]) for i in mine]


def classify_streams(mine, tgt):
    """Two instruction streams -> a verdict dict. THE authoritative entry point: it sees the FULL
    residual, so drift detection and the permutation/reorder tests are exact.

    Returns {klass, profile, bucket, closeness, nins_mine, nins_tgt, sig, detail}.
    `closeness` is index-wise and equals len(masked_diff.structured_diff(mine, tgt)) by
    construction — the collector asserts that against the independent implementation."""
    nm, nt = len(mine), len(tgt)
    if not nm or not nt:
        return _v("EMPTY", 0 if nm == nt else max(nm, nt), nm, nt, {"reason": "empty stream"})

    msk = _masks(mine)

    def eqm(i, j):
        """mine[i] vs tgt[j] under mine[i]'s mask (the generalization of match_one's compare to a
        shifted alignment — the mask is a property of MY instruction, not of the position)."""
        if i >= nm or j >= nt:
            return False
        return (mine[i]["word"] & msk[i]) == (tgt[j]["word"] & msk[i])

    diffs = [i for i in range(max(nm, nt)) if not eqm(i, i)]
    closeness = len(diffs)
    if closeness == 0 and nm == nt:
        return _v("MATCH", 0, nm, nt, {})

    # ---- 1. DRIFT FIRST. A single inserted/removed instruction desynchronizes everything after
    # it and inflates `closeness` by the length of the tail. Detecting it turns a "200-mismatch
    # wall" back into the one-instruction structural delta it actually is.
    k = diffs[0]
    d = nm - nt
    if d != 0:
        # mine longer by d (d>0): d extra instructions at k. mine shorter (d<0): d missing at k.
        if d > 0 and all(eqm(k + d + t, k + t) for t in range(nt - k)):
            return _v("LENGTH-DRIFT", closeness, nm, nt,
                      {"delta": d, "at": k, "explains": "tail",
                       "mine_extra": [_show(mine, k + t) for t in range(min(d, 4))]},
                      sig="LENGTH-DRIFT/+%d" % d, **_drift_route(d))
        if d < 0 and all(eqm(k + t, k - d + t) for t in range(nm - k)):
            return _v("LENGTH-DRIFT", closeness, nm, nt,
                      {"delta": d, "at": k, "explains": "tail",
                       "tgt_extra": [_show(tgt, k + t) for t in range(min(-d, 4))]},
                      sig="LENGTH-DRIFT/%d" % d, **_drift_route(d))
        # No single shift point explains it. Now the SIZE ratio decides between two very different
        # situations that a scalar `closeness` renders identical:
        #   a draft 1-2 instructions off  -> a real near-miss; a seed tweak or a known idiom closes it
        #   a 15-instruction draft against a 132-instruction target -> THE DRAFT IS NOT THE FUNCTION
        # The second is not a near-miss at all, and its recorded "closeness 278" is pure length
        # artefact. It matters because the routing is opposite: the first wants a small edit, the
        # second wants a re-draft — and a corpus full of the second, ranked by closeness, is how a
        # queue of NEVER-PROPERLY-ATTEMPTED functions comes to look like a wall of hard ones.
        # Evidence first (the shift test above), ratio only as the fallback discriminator.
        if abs(d) > max(2, 0.15 * nt):
            return _v("SIZE-MISMATCH", closeness, nm, nt,
                      {"delta": d, "at": k, "ratio": round(nm / float(nt), 2),
                       "note": "draft is a different-sized function — re-draft, do not seed-tweak"},
                      sig="SIZE-MISMATCH/%s" % ("short" if d < 0 else "long"))
        return _v("LENGTH-DRIFT", closeness, nm, nt,
                  {"delta": d, "at": k, "explains": "partial"},
                  sig="LENGTH-DRIFT/%d?" % d, **_drift_route(d))
    if closeness > 8:
        # equal lengths: an insert+delete pair re-aligns the middle. Accept a shift only if it
        # explains most of the run (a coincidental partial alignment must not become a verdict).
        tail = [i for i in diffs if i >= k]
        for s in (1, -1, 2, -2, 3, -3):
            ok = sum(1 for i in tail if eqm(i, i + s))
            if ok >= max(4, int(0.8 * len(tail))):
                return _v("SHIFT-DRIFT", closeness, nm, nt,
                          {"shift": s, "at": k, "realigned": ok, "of": len(tail)},
                          sig="SHIFT-DRIFT/%+d" % s)

    # ---- 2. per-position KIND (aligned; lengths equal here, or the un-explained ragged case)
    kinds, unknown = [], 0
    reg_pairs, imm_pairs, op_pairs = [], [], []
    for i in diffs:
        if i >= nm or i >= nt:
            kinds.append("len")
            continue
        try:
            sa_, ra_, ia_ = decode(mine[i]["word"])
            sb_, rb_, ib_ = decode(tgt[i]["word"])
        except UnknownOpcode:
            unknown += 1
            kinds.append("unknown")
            continue
        if sa_ != sb_:
            kinds.append("opcode")
            op_pairs.append((i, _mnem(mine[i]["mnem"]), _mnem(tgt[i]["mnem"])))
            continue
        # same operation: is the difference in the registers, the immediate, or both?
        dr = ra_ != rb_
        # the immediate may be masked away (HI16/LO16/PC16) — then it is NOT a real difference
        di = (ia_ != ib_) and (msk[i] & 0xFFFF) != 0
        if dr and not di:
            kinds.append("reg")
            reg_pairs.append((i, ra_, rb_))
        elif di and not dr:
            kinds.append("imm")
            imm_pairs.append((i, ia_, ib_))
        elif dr and di:
            kinds.append("reg+imm")
            reg_pairs.append((i, ra_, rb_))
            imm_pairs.append((i, ia_, ib_))
        else:
            # equal fields but unequal masked words: the difference is in a field this format
            # does not expose (e.g. a coprocessor function word). Count it, never guess.
            unknown += 1
            kinds.append("unknown")
    hist = dict(collections.Counter(kinds))

    if unknown and unknown == len(diffs):
        return _v("UNKNOWN", closeness, nm, nt, {"kinds": hist}, sig="UNKNOWN")

    only = lambda *ks: all(k_ in ks for k_ in kinds)          # noqa: E731

    # ---- 3. REGISTER PERMUTATION: every diff is register-only AND one injective map explains all
    if only("reg") and reg_pairs:
        m = _reg_map(reg_pairs)
        if m is not None:
            glob = _map_is_global(mine, tgt, msk, m, nm)
            cyc = _cycles(m)
            return _v("REGALLOC-PERM", closeness, nm, nt,
                      {"map": {_R(a): _R(b) for a, b in sorted(m.items())},
                       "cycles": cyc, "global": glob, "kinds": hist},
                      sig="REGALLOC-PERM/" + ",".join(cyc))

    # ---- 4. SCHEDULE REORDER: the same masked instructions, in a different order
    a_ms = collections.Counter(mine[i]["word"] & msk[i] for i in diffs if i < nm)
    b_ms = collections.Counter(tgt[i]["word"] & msk[i] for i in diffs if i < nt)
    if a_ms and a_ms == b_ms:
        return _v("SCHEDULE-REORDER", closeness, nm, nt,
                  {"span": [diffs[0], diffs[-1]], "kinds": hist},
                  sig="SCHEDULE-REORDER/%d" % len(diffs))

    # ---- 5. DELAY SLOT: nop against a real instruction (gcc filled the slot differently)
    nops = sum(1 for i in diffs
               if i < nm and i < nt and ((mine[i]["word"] == 0) != (tgt[i]["word"] == 0)))
    if nops and nops >= len(diffs) / 2:
        return _v("DELAY-SLOT", closeness, nm, nt, {"nop_positions": nops, "kinds": hist},
                  sig="DELAY-SLOT/%d" % nops)

    # ---- 6. register-only but no single map
    if only("reg"):
        return _v("REGALLOC-LOCAL", closeness, nm, nt,
                  {"kinds": hist, "sample": [(i, _R2(a), _R2(b)) for i, a, b in reg_pairs[:6]]},
                  sig="REGALLOC-LOCAL")

    # ---- 7. OPERATION differences -> family
    if op_pairs:
        fams = {_family(a, b) for _i, a, b in op_pairs}
        fams.discard(None)
        pair = "%s!=%s" % (op_pairs[0][1], op_pairs[0][2])
        if fams == {"width"}:
            return _v("WIDTH", closeness, nm, nt, {"pairs": op_pairs[:6], "kinds": hist},
                      sig="WIDTH/" + pair)
        if fams == {"branch"}:
            return _v("BRANCH-POLARITY", closeness, nm, nt, {"pairs": op_pairs[:6], "kinds": hist},
                      sig="BRANCH-POLARITY/" + pair)
        if fams == {"strength"}:
            return _v("STRENGTH", closeness, nm, nt, {"pairs": op_pairs[:6], "kinds": hist},
                      sig="STRENGTH/" + pair)
        if fams == {"addressing"}:
            return _v("ADDRESSING", closeness, nm, nt, {"pairs": op_pairs[:6], "kinds": hist},
                      sig="ADDRESSING/" + pair)
        return _v("OPCODE-MIXED", closeness, nm, nt,
                  {"pairs": op_pairs[:6], "families": sorted(fams), "kinds": hist},
                  sig="OPCODE-MIXED/" + ",".join(sorted(fams)) if fams else "OPCODE-MIXED")

    # ---- 8. immediate-only
    if only("imm") and imm_pairs:
        deltas = {(b - a) & 0xFFFF for _i, a, b in imm_pairs}
        if len(deltas) == 1:
            dv = deltas.pop()
            return _v("IMM-OFFSET", closeness, nm, nt,
                      {"delta": dv if dv < 0x8000 else dv - 0x10000, "n": len(imm_pairs),
                       "kinds": hist},
                      sig="IMM-OFFSET/%d" % (dv if dv < 0x8000 else dv - 0x10000))
        return _v("IMM-VALUE", closeness, nm, nt,
                  {"sample": imm_pairs[:6], "kinds": hist}, sig="IMM-VALUE")

    return _v("MIXED", closeness, nm, nt, {"kinds": hist},
              sig="MIXED/" + ",".join("%s:%d" % kv for kv in sorted(hist.items())))


# --------------------------------------------------------------------------------------------
# helpers
# --------------------------------------------------------------------------------------------
_REGN = ("zero", "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3", "t4", "t5",
         "t6", "t7", "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "t8", "t9", "k0", "k1",
         "gp", "sp", "fp", "ra")


def _R(rk):
    role, n = rk
    return ("$" + _REGN[n]) if role == "g" else ("c%d" % n)


def _R2(regs):
    return ",".join(_R((r[0], r[2])) for r in regs)


def _show(stream, i):
    return "%08x %s" % (stream[i]["word"], stream[i]["mnem"]) if 0 <= i < len(stream) else "--"


def _reg_map(reg_pairs):
    """A consistent INJECTIVE register map explaining every register-only diff, or None.

    Consistency is what separates 'gcc allocated the same values to different registers' (one map,
    the §31 S11/RC-3 class the permuter's decl/stmt-order levers actually move) from 'the drafts
    disagree all over' (no map — a different computation)."""
    fwd, rev = {}, {}
    for _i, ra, rb in reg_pairs:
        if len(ra) != len(rb):
            return None
        for (role_a, slot_a, va), (role_b, slot_b, vb) in zip(ra, rb):
            if role_a != role_b or slot_a != slot_b:
                return None
            if va == vb:
                continue
            ka, kb = (role_a, va), (role_b, vb)
            if fwd.setdefault(ka, kb) != kb or rev.setdefault(kb, ka) != ka:
                return None                       # not a function / not injective
    return fwd or None


def _map_is_global(mine, tgt, msk, m, n):
    """Does the map explain the WHOLE function (not just the diff positions)? A global permutation
    is the clean S11 signature; a local one means the allocation diverges only in a region."""
    for i in range(n):
        try:
            sa_, ra_, _ = decode(mine[i]["word"])
            sb_, rb_, _ = decode(tgt[i]["word"])
        except UnknownOpcode:
            return False
        if sa_ != sb_ or len(ra_) != len(rb_):
            return False
        for (role, _s, va), (_rb, _sb, vb) in zip(ra_, rb_):
            if m.get((role, va), (role, va)) != (role, vb):
                return False
    return True


def _cycles(m):
    """The map as cycle notation ('$s0>$s1>$s0'), the compact human/clustering form."""
    seen, out = set(), []
    for k in sorted(m):
        if k in seen:
            continue
        cyc, cur = [], k
        while cur in m and cur not in seen:
            seen.add(cur)
            cyc.append(_R(cur))
            cur = m[cur]
        if cyc:
            cyc.append(_R(cur))
            out.append(">".join(cyc))
    return out


def _family(a, b):
    for name, s in (("width", _WIDTH), ("strength", _STRENGTH),
                    ("branch", _BRANCH), ("addressing", _ADDRESSING)):
        if a in s and b in s:
            return name
    return None


def _drift_route(d):
    """A LENGTH-DRIFT of +-1..2 is permuter-shaped (one local add/drop of an instruction); anything
    larger is a wrong-shaped draft. Phase-29 measurement: |d|<=2 is 339 fns / 472k instruction-
    weighted member-instances (~3.6pp of the fleet) — 10x the entire pre-existing permuter bucket,
    which is why this magnitude split is worth having at all."""
    return {"profile": "length", "bucket": "permuter"} if abs(d) <= 2 else {}


def _v(klass, closeness, nm, nt, detail, sig=None, profile=_KEEP, bucket=_KEEP):
    """`profile`/`bucket` override the static _ROUTE entry for the cases where the ROUTE depends on
    the residual's MAGNITUDE, not just its kind — LENGTH-DRIFT being the one that matters: a ±1-2
    instruction delta is plausibly reachable by a local mutation that adds or drops one instruction
    (perm_temp_for_expr / perm_expand_expr), while a larger drift means the draft's shape is wrong
    and no amount of search fixes it. Same class, opposite tool."""
    prof, bkt = _ROUTE[klass]
    return {"klass": klass,
            "profile": prof if profile is _KEEP else profile,
            "bucket": bkt if bucket is _KEEP else bucket,
            "closeness": closeness,
            "nins_mine": nm, "nins_tgt": nt, "sig": sig or klass, "detail": detail}


# --------------------------------------------------------------------------------------------
# the degraded path — a STORED, CAPPED residual (legacy backlog records)
# --------------------------------------------------------------------------------------------
def classify_residual(residual, nins=None):
    """Classify from a STORED `[[idx, 'hex mnem', 'hex mnem'], ...]` residual.

    DEGRADED ON PURPOSE and it says so (`detail.degraded`): a stored residual is capped (48
    entries) and carries no reloc kinds, so drift detection and the reorder multiset are not
    trustworthy. Use classify_streams wherever the objects still exist — which, for this repo, is
    always, because the draft and the .s are both on disk and recompiling is a second of CPU."""
    mine, tgt = [], []
    for ent in residual or []:
        _i, me, tg = (list(ent) + ["--", "--"])[:3]
        for txt, dst in ((me, mine), (tg, tgt)):
            if txt == "--" or not txt:
                continue
            w, _, mn = txt.partition(" ")
            try:
                dst.append({"word": int(w, 16), "mnem": mn, "reloc_kind": None, "reloc_op": None})
            except ValueError:
                pass
    if not mine or not tgt or len(mine) != len(tgt):
        return _v("UNKNOWN", len(residual or []), len(mine), len(tgt),
                  {"degraded": True, "reason": "stored residual not pairwise-complete"})
    v = classify_streams(mine, tgt)
    v["detail"]["degraded"] = True
    v["closeness"] = len(residual or [])
    if nins:
        v["nins_mine"] = v["nins_tgt"] = nins
    return v


def profile_for(verdict):
    """The permuter_weights profile name this verdict routes to (None = do not direct / do not
    permute). The bridge Task-13B's autopsy uses to extend permuter_weights from measured
    residuals instead of from a wave agent's typed label."""
    return verdict.get("profile")


# --------------------------------------------------------------------------------------------
if __name__ == "__main__":
    import sys
    if len(sys.argv) >= 3:                          # residual_class.py <mine.o> <target.s> [fn]
        fn = sys.argv[3] if len(sys.argv) > 3 else None
        mine = masked_diff.insns_from_object(sys.argv[1], fn)
        tgt = (masked_diff.insns_from_s(sys.argv[2]) if sys.argv[2].endswith(".s")
               else masked_diff.insns_from_object(sys.argv[2], fn))
        import json
        print(json.dumps(classify_streams(mine, tgt), indent=1))
    else:
        print(__doc__)
