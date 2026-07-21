#!/usr/bin/env python3
"""test_residual_class.py — synthetic unit tests for the deterministic residual classifier.

Hand-encoded MIPS-I words (verified against the encoding, not against our own decoder — a test
that reuses the code under test proves nothing). Every named class must fire on a stream that
exhibits it, and the classes that route to `structural` must NOT be misread as regalloc/schedule:
that misread is the whole failure mode this classifier exists to prevent, because it sends the
permuter to grind CPU at a residual local mutation can never reach.

Run: .venv/bin/python tools/test_residual_class.py
"""
import sys
import os

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import residual_class as rc


def I(word, mnem="", reloc=None):
    return {"word": word, "mnem": mnem, "reloc_kind": reloc, "reloc_op": None}


# --- hand-encoded words -----------------------------------------------------------------------
ADDU_V0_A0_A1 = 0x00851021      # addu $v0,$a0,$a1   op0 rs=4 rt=5 rd=2 funct=0x21
ADDU_V1_A0_A1 = 0x00851821      # addu $v1,$a0,$a1   rd=3
ADDU_S0_S1_S2 = 0x02328021      # addu $s0,$s1,$s2   rs=17 rt=18 rd=16
ADDU_S1_S0_S2 = 0x02128821      # addu $s1,$s0,$s2   rs=16 rt=18 rd=17
OR_S2_S0_ZERO = 0x02009025      # or   $s2,$s0,$zero rs=16 rt=0  rd=18 funct=0x25
OR_S2_S1_ZERO = 0x02209025      # or   $s2,$s1,$zero rs=17
OR_S2_S2_ZERO = 0x02409025      # or   $s2,$s2,$zero rs=18
LW_V0_8_A0 = 0x8C820008         # lw   $v0,8($a0)    op=35 rs=4 rt=2 imm=8
LH_V0_8_A0 = 0x84820008         # lh   $v0,8($a0)    op=33
LW_V0_12_A0 = 0x8C82000C        # lw   $v0,12($a0)   imm=12
LW_V0_16_A0 = 0x8C820010        # lw   $v0,16($a0)   imm=16
LW_V0_20_A0 = 0x8C820014        # lw   $v0,20($a0)   imm=20
SLL_V0_A0_2 = 0x00042080        # sll  $v0,$a0,2     op0 rt=4 rd=2 sa=2 funct=0
MULT_A0_A1 = 0x00850018         # mult $a0,$a1       op0 rs=4 rt=5 funct=0x18
BEQ_A0_A1 = 0x10850004          # beq  $a0,$a1,+4    op=4
BNE_A0_A1 = 0x14850004          # bne  $a0,$a1,+4    op=5
NOP = 0x00000000
JAL = 0x0C000000                # jal (target is a link-time value -> always masked)

PASS = []
FAIL = []


def check(name, got, want_klass, want_bucket=None):
    ok = got["klass"] == want_klass and (want_bucket is None or got["bucket"] == want_bucket)
    (PASS if ok else FAIL).append(
        "%-22s -> %-17s %-11s %s" % (name, got["klass"], got["bucket"], got["sig"]))
    if not ok:
        FAIL[-1] += "   EXPECTED %s/%s" % (want_klass, want_bucket)


def main():
    # 1. identical streams -> MATCH
    s = [I(ADDU_V0_A0_A1), I(LW_V0_8_A0), I(NOP)]
    check("identical", rc.classify_streams(s, list(s)), "MATCH", "integration")

    # 2. a jal whose target differs is MASKED away -> still MATCH (relocation-invariance)
    a = [I(JAL | 0x111, "jal x", "26"), I(NOP)]
    b = [I(JAL | 0x222, "jal y"), I(NOP)]
    check("jal target masked", rc.classify_streams(a, b), "MATCH", "integration")

    # 3. GLOBAL register permutation $s0<->$s1 -> REGALLOC-PERM (the §31 S11/RC-3 class)
    a = [I(ADDU_S0_S1_S2, "addu"), I(OR_S2_S0_ZERO, "or"), I(NOP)]
    b = [I(ADDU_S1_S0_S2, "addu"), I(OR_S2_S1_ZERO, "or"), I(NOP)]
    v = rc.classify_streams(a, b)
    check("reg permutation", v, "REGALLOC-PERM", "permuter")
    assert v["detail"]["global"] is True, "a whole-function swap must read as global"

    # 4. two instructions swapped in ORDER -> SCHEDULE-REORDER
    a = [I(LW_V0_8_A0, "lw"), I(ADDU_V0_A0_A1, "addu"), I(NOP)]
    b = [I(ADDU_V0_A0_A1, "addu"), I(LW_V0_8_A0, "lw"), I(NOP)]
    check("stmt reorder", rc.classify_streams(a, b), "SCHEDULE-REORDER", "permuter")

    # 5a. a nop hoisted INTO the delay slot, same instruction multiset -> SCHEDULE-REORDER.
    #     Reorder is the tighter (and correct) reading of a pure swap; what matters for routing is
    #     that it lands on the SCHEDULE profile either way.
    a = [I(BEQ_A0_A1, "beq"), I(NOP, "nop"), I(ADDU_V0_A0_A1, "addu")]
    b = [I(BEQ_A0_A1, "beq"), I(ADDU_V0_A0_A1, "addu"), I(NOP, "nop")]
    v = rc.classify_streams(a, b)
    check("delay-slot swap", v, "SCHEDULE-REORDER", "permuter")
    assert v["profile"] == "schedule", "a nop/insn swap must route to the schedule profile"

    # 5b. gcc filled the slot with an instruction we left empty and the multisets DIFFER
    #     -> DELAY-SLOT in its own right
    a = [I(BEQ_A0_A1, "beq"), I(NOP, "nop"), I(ADDU_V0_A0_A1, "addu")]
    b = [I(BEQ_A0_A1, "beq"), I(ADDU_V0_A0_A1, "addu"), I(SLL_V0_A0_2, "sll")]
    check("delay-slot fill", rc.classify_streams(a, b), "DELAY-SLOT", "permuter")

    # 6. ONE extra instruction near the front of a long function -> LENGTH-DRIFT, not a wall.
    #    closeness reads ~tail-length; the class must say "+1 instruction", the structural truth.
    body = [I(LW_V0_8_A0 + (i << 0), "lw") for i in range(0, 40)]
    a = body[:4] + [I(NOP, "nop")] + body[4:]
    b = list(body)
    v = rc.classify_streams(a, b)
    check("one extra insn", v, "LENGTH-DRIFT", "structural")
    assert v["detail"]["delta"] == 1 and v["detail"]["explains"] == "tail", v["detail"]
    assert v["closeness"] > 30, "index-wise closeness really is inflated (that is the point)"

    # 7. access WIDTH flip lw->lh -> structural (an §18/§43 idiom, NOT permuter fuel)
    a = [I(LW_V0_8_A0, "lw $v0,8($a0)"), I(ADDU_V0_A0_A1, "addu")]
    b = [I(LH_V0_8_A0, "lh $v0,8($a0)"), I(ADDU_V0_A0_A1, "addu")]
    check("load width flip", rc.classify_streams(a, b), "WIDTH", "structural")

    # 8. branch polarity flip -> structural
    a = [I(BEQ_A0_A1, "beq $a0,$a1,4"), I(NOP)]
    b = [I(BNE_A0_A1, "bne $a0,$a1,4"), I(NOP)]
    check("branch polarity", rc.classify_streams(a, b), "BRANCH-POLARITY", "structural")

    # 9. strength reduction mult <-> sll
    a = [I(MULT_A0_A1, "mult $a0,$a1"), I(NOP)]
    b = [I(SLL_V0_A0_2, "sll $v0,$a0,2"), I(NOP)]
    check("strength reduction", rc.classify_streams(a, b), "STRENGTH", "structural")

    # 10. every immediate off by a CONSTANT -> IMM-OFFSET (a frame/struct-layout shift)
    a = [I(LW_V0_8_A0, "lw"), I(LW_V0_12_A0, "lw"), I(LW_V0_16_A0, "lw")]
    b = [I(LW_V0_12_A0, "lw"), I(LW_V0_16_A0, "lw"), I(LW_V0_20_A0, "lw")]
    v = rc.classify_streams(a, b)
    check("constant imm shift", v, "IMM-OFFSET", "structural")
    assert v["detail"]["delta"] == 4, v["detail"]

    # 11. a HI16/LO16 immediate difference is MASKED -> not a residual at all
    a = [I(0x3C020000 | 0x8013, "lui $v0,0x8013", "HI16"), I(NOP)]
    b = [I(0x3C020000 | 0x8017, "lui $v0,0x8017"), I(NOP)]
    check("hi16 imm masked", rc.classify_streams(a, b), "MATCH", "integration")

    # 12a. TWO disjoint swaps ($s0<->$s1 and $v0->$v1) are still ONE consistent injective map,
    #      so this is a genuine permutation — asserting it is not, is the mistake to avoid.
    a = [I(ADDU_S0_S1_S2, "addu"), I(ADDU_V0_A0_A1, "addu")]
    b = [I(ADDU_S1_S0_S2, "addu"), I(ADDU_V1_A0_A1, "addu")]
    check("two disjoint swaps", rc.classify_streams(a, b), "REGALLOC-PERM", "permuter")

    # 12b. a CONTRADICTORY map ($s0->$s1 here, $s0->$s2 there) is not a permutation
    #      -> REGALLOC-LOCAL: still regalloc, but honestly labelled as unexplained
    a = [I(ADDU_S0_S1_S2, "addu"), I(OR_S2_S0_ZERO, "or")]
    b = [I(ADDU_S1_S0_S2, "addu"), I(OR_S2_S2_ZERO, "or")]
    check("contradictory map", rc.classify_streams(a, b), "REGALLOC-LOCAL", "permuter")

    # 13. coverage assertion: an opcode the decoder does not cover must be COUNTED as UNKNOWN,
    #     never silently absorbed into a neighbouring class (R32).
    a = [I(0xF4000000, "??"), I(NOP)]
    b = [I(0xF4000001, "??"), I(NOP)]
    check("uncovered opcode", rc.classify_streams(a, b), "UNKNOWN", "unknown")

    # 14. the degraded (stored-residual) path declares itself degraded
    v = rc.classify_residual([[0, "%08x addu" % ADDU_S0_S1_S2, "%08x addu" % ADDU_S1_S0_S2]])
    assert v["detail"].get("degraded") is True, "the capped path must flag itself"
    PASS.append("%-22s -> %-17s %-11s %s" % ("degraded path", v["klass"], v["bucket"], "flagged"))

    # 15. every class in the route table is reachable from KLASSES and has a bucket
    for k in rc.KLASSES:
        assert rc._ROUTE[k][1] in ("permuter", "structural", "integration",
                                   "redraft", "unknown"), k

    for line in PASS:
        print("  ok   " + line)
    for line in FAIL:
        print("  FAIL " + line)
    print("\n%d passed, %d failed" % (len(PASS), len(FAIL)))
    return 1 if FAIL else 0


if __name__ == "__main__":
    sys.exit(main())
