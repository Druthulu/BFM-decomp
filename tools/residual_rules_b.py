#!/usr/bin/env python3
"""residual_rules_b.py — residual-SHAPE -> cookbook-rule classifier (head-to-head implementation B).

Given a candidate C draft that does NOT byte-match, say WHY and prescribe the fix, by recognising
the residual's mechanical shape. Sits ON TOP of tools/match_one.py (the measurement instrument) and
tools/residual_class.py (the deterministic klass) — this module adds the cookbook-rule layer.

DESIGN CHOICES THAT DIFFER FROM THE OBVIOUS APPROACH
  1. NO DISASSEMBLY TEXT IS EVER PARSED. The two sides of a match_one residual are disassembled by
     different tools (objdump vs the splat .s comments) and disagree on `$` prefixes, operand order
     display, and constant base (`30` vs `0x1E`). Every equality decision here is made on the raw
     32-bit WORD (each residual row's text begins with 8 hex digits; --emit-streams carries the full
     word streams), decoded with residual_class.decode(). Formatting cannot lie about a word.
  2. TARGET-SIDE ORACLES FIRE FIRST. A §332 wall is a property of the TARGET bytes, not of any
     draft — wall_sweep.scan() (reused, not rewritten) decides it before the draft is even read.
     Likewise the §188 epilogue wall is decided by a REAL second compile (cc1 raw + `as -O2`
     bypass, oracle_reorder semantics): bypass == 0 diffs while the pinned triple > 0 is PROOF the
     C is right and the pinned assembler can never emit it. Certainty comes from oracles, not
     pattern confidence.
  3. FULL STREAMS, NOT THE CAPPED RESIDUAL. match_one caps `residual` at 48 rows — exactly enough
     to hide a drift signature. --emit-streams provides the uncapped word streams; the aligned diff
     is recomputed here with masked_diff.mask_for (match_one semantics, mask from MY side).

THE RULES, each with its TELL, FIX, CONFIDENCE and — required — WHAT WOULD REFUTE IT
  W332  maspsx %lo-in-delay-slot wall                                        [certain]
        TELL  wall_sweep.scan(target .s) > 0 hits (a delay slot holding a macro tail `%lo(...)`).
        FIX   none from C: toolchain wall. Ledger it, never draft, never escalate (§332/§332a).
        REFUTED BY a function with a hit that the whole-binary gate nevertheless banks from C.
  INTEG standalone MATCH                                                     [certain]
        TELL  match_one status == "match" (closeness 0).
        FIX   the C is byte-correct; the blocker is TU plumbing — reconcile ladder (§58/§59, §367).
        REFUTED BY a standalone MATCH whose whole-TU compile fails for a CODEGEN (not decl) reason.
  W188  epilogue/assembler-reorder wall, oracle-proven                       [certain]
        TELL  the SAME draft, cc1 raw output (move->addu) + `as -O2` bypass, diffs == 0 while the
              pinned maspsx + `as -O1` path diffs > 0.
        FIX   none from C under the pinned triple (§188, tools/oracle_reorder.py). Stop grinding.
        REFUTED BY a bypass-0 function later banked by a pure C change under the pinned triple.
  R368  reload-remat constant                                                [certain / high]
        TELL  a wrong-register diff row on a COMMUTATIVE op whose shared operand crosses slots —
              mine (x, c) vs target (c', x) — i.e. the constant's register is operand-2 in mine
              and operand-1 in the target (§368: cse forces constants to op-2; reload-remat's
              rematerialised constant lands op-1). CERTAIN when a companion diff row loads the SAME
              immediate into c/c' from $zero (the constant's materialisation moved registers too).
        FIX   function-scope single-set local for the constant, assigned once at entry, used
              constant-first (§368). Pins measured WORSE — do not pin.
        REFUTED BY a swap-row residual that §368's lever does not close and RTL dumps attribute
        elsewhere (cf. §372, whose rows have NO commutative operands — that absence is the border).
  R372  copy-capture pair                                                    [high]
        TELL  a wrong-register diff row where MINE reads the DESTINATION of a nearby MATCHING copy
              insn (addu $dst,$src,$zero == `move`) whose source is what the TARGET reads. cse
              make_regs_eqv / optimize_reg_copy_1 re-based my use onto the copy dest (§372).
        FIX   spell the copy as `P = X + zr` with `register s32 zr __asm__("$0")` — byte-identical
              encoding, kills both passes (§372).
        REFUTED BY the mirror direction dominating (target reads the copy dest): then the ORIGINAL
        kept the capture and the +zr edit is exactly wrong (reported as R372-INV, medium).
  R370  reorg slot-steal not reproduced                                      [high]
        TELL  LENGTH-DRIFT +1 whose extra MINE row is a `nop` in a branch delay slot, and the
              TARGET's slot word occurs in MINE within the 8 insns before the branch — reorg stole
              the first eligible insn scanning back; my accumulator was ineligible (§370/§373).
        FIX   spell the value SPLIT so it accumulates outside the register-heavy tail (§370); or
              the §373.2 pin that deletes the sched2 anti-dep.
        REFUTED BY the "stolen" insn being a %lo macro tail (that is W332 — checked first).
  R373  target fills a delay slot where mine holds nop (aligned)             [high]
        TELL  >=half of the aligned diff rows are mine-nop vs target-insn immediately after a
              branch/jump (the DELAY-SLOT klass, target-filled direction).
        FIX   §373 (dead-reset cse-breaker; anti-dep pin) / §370 (eligibility) / §176-A statement
              order around the call.
        REFUTED BY wall_sweep hits (then it is W332) — checked first.
  R5A   gcc stole a slot the target leaves as nop (reverse direction)        [high]
        TELL  aligned diff rows mine-insn vs target-NOP in a delay slot.
        FIX   zero-byte `__asm__("")` fence before the branch — reorg stop_search_p halts the
              filler (§5a + §34; §336: at the BOTTOM of a duplicated block).
        REFUTED BY the row not sitting in any delay slot (plain reorder — not this rule).
  R366  group_case_nodes stacked-label merge                                 [high]
        TELL  mine SHORTER (length drift < 0, |d| 2..40) AND the draft C stacks consecutive case
              labels (`case 5: case 6:`) — gcc merged them into one range node (§366).
        FIX   give every case its own duplicated body + break; let cross_jump re-fold (§366/§298).
        REFUTED BY unstacking not recovering the drift (then the node count difference is real
        — e.g. R339's missing node).
  R339  missing third case node                                              [high]
        TELL  mine SHORTER by exactly 2 and the target's extra rows at the drift point decode to
              slti/sltiu + branch — the low-bound range test only >=3 case nodes emit (§339).
        FIX   add the missing case arm (e.g. `case 0: return;`).
        REFUTED BY the extra pair not being compare+branch.
  R333  frame-size drift                                                     [high]
        TELL  every imm-diff row is $sp-relative (mem base $sp, or `addiu $sp,$sp,K`), same ops
              and regs, ONE constant delta across all rows (§333/§334/§335/§193-I).
        FIX   declare the missing bytes as an unreferenced TRAILING aggregate local (§333); check
              §334 (a reload spill slot rounds to 8B) and §335 (extern u16[] dead temps).
        REFUTED BY the delta not being constant, or rows off non-$sp bases (struct layout, not frame).
  R35   slti/sltiu signedness flip                                           [high]
        TELL  diff rows differing ONLY slti<->sltiu with equal regs+imm (§35).
        FIX   keep a separate SIGNED copy of the unsigned load; spell each bound as its own if (§21).
        REFUTED BY regs/imm also differing (then it is not the pure signedness class).
  RPOL  branch polarity                                                      [high]
        TELL  diff rows differing ONLY beq<->bne (same regs) (§3-T4, BRANCH-POLARITY klass).
        FIX   invert the source condition / swap arms (§3-T4, §32.2).
  RJINT internal `j` to the wrong label                                      [high]
        TELL  a diff row where BOTH words are `j` (op 2) — same instruction, different target:
              break-vs-return / goto to the wrong label (§195-D, §162).
        FIX   re-check which arm falls through vs jumps: the surviving cross-jump copy is the LATER
              one; a BACKWARD j into a sibling arm is a source `goto` (§162).
  R31   clean register permutation                                           [medium]
        TELL  klass REGALLOC-PERM: one injective map explains every diff (cycles named).
        FIX   §31 decl/stmt-order levers, §17 register pins, permuter `regalloc` profile.
        (medium on purpose: the CLASS is certain, the specific lever is not.)
  NOCOMPILE                                                                  [high for decl conflicts]
        TELL  cc1/cpp/as failure; stderr names a decl conflict (§337/§367) or other blocker.
        FIX   adopt the TU's banked spelling / §37 asm-label alias; finish on the whole-TU compile.
  REDRAFT (pass-through of residual_class SIZE-MISMATCH)                     [medium — rebadged]
        The draft is a different-sized function: re-draft, never seed-tweak. Marked medium and
        flagged `rebadged` because the knowledge predates this tool (residual_class.py).

SCORING HONESTY. `certain`/`high` are claimed ONLY for oracle-backed or double-confirmed tells.
The eval summary separates compile-fails and rebadged verdicts so the money metric cannot be
inflated by them. A sweep that returns 0 must prove it can return non-zero: --selftest runs the two
development cases (proven §368 / proven §332) and refuses to pass unless both classify correctly.

USAGE
  python3 tools/residual_rules_b.py --binary ov_SC03_105 --fn func_80187A30 \
      --draft .run/S68o1/opus/func_80187A30.c            # one function, human report
  python3 tools/residual_rules_b.py --selftest            # the two dev cases (must pass)
  python3 tools/residual_rules_b.py --eval .run/S68_rules_eval_set.json --jobs 8
                                                          # held-out sweep + score table
"""
import argparse
import collections
import json
import os
import re
import subprocess
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(REPO, "tools"))

import masked_diff            # noqa: E402  — mask_for / insns_from_s / strip_scalar_typedefs
import residual_class         # noqa: E402  — decode() and the deterministic klass
import wall_sweep             # noqa: E402  — the §332 detector, REUSED not rewritten

WORK_ROOT = os.path.join(REPO, ".run", "rules_b")

# ---------------------------------------------------------------------------------------------
# word-level helpers (no disassembly text is ever consulted)
# ---------------------------------------------------------------------------------------------
_COMMUTATIVE = {0x18, 0x19, 0x20, 0x21, 0x24, 0x25, 0x26}   # mult multu add addu and or xor
_CMP_FN = {0x2A, 0x2B}                                       # slt sltu (R-type)


def _op(w):
    return w >> 26


def _fields(w):
    return (w >> 21) & 31, (w >> 16) & 31, (w >> 11) & 31, w & 0xFFFF   # rs rt rd imm


def is_branch(w):
    op = _op(w)
    if op in (2, 3, 4, 5, 6, 7):                       # j jal beq bne blez bgtz
        return True
    if op == 1:                                        # REGIMM bltz/bgez/…
        return True
    if op == 0 and (w & 63) in (8, 9):                 # jr jalr
        return True
    if op in (16, 17, 18, 19) and ((w >> 21) & 31) == 8:   # BCzT/BCzF
        return True
    return False


def _is_move(w):
    """addu/or $rd,$src,$zero (or $rd,$zero,$src) -> (dst, src) or None. gcc's `move`."""
    if _op(w) != 0 or (w & 63) not in (0x21, 0x25):
        return None
    rs, rt, rd, _ = _fields(w)
    if rd == 0:
        return None
    if rt == 0 and rs != 0:
        return rd, rs
    if rs == 0 and rt != 0:
        return rd, rt
    return None


def _const_load(w):
    """addiu/ori/li $rt,$zero,K -> (rt, K) or None."""
    if _op(w) in (9, 13):                              # addiu / ori
        rs, rt, _rd, imm = _fields(w)
        if rs == 0:
            return rt, imm
    return None


class Streams:
    """Aligned view over the two full word streams, match_one mask semantics."""

    def __init__(self, mine_words, tgt_words, mine_relocs):
        self.mine = mine_words
        self.tgt = tgt_words
        self.masks = []
        for i, w in enumerate(mine_words):
            rk = mine_relocs.get(str(i)) or mine_relocs.get(i)
            self.masks.append(masked_diff.mask_for(w, rk["kind"] if rk else None))

    def eqm(self, i, j):
        if i >= len(self.mine) or j >= len(self.tgt):
            return False
        return (self.mine[i] & self.masks[i]) == (self.tgt[j] & self.masks[i])

    def diffs(self):
        return [i for i in range(max(len(self.mine), len(self.tgt))) if not self.eqm(i, i)]


# ---------------------------------------------------------------------------------------------
# the measurement step — match_one as a subprocess (the sanctioned instrument)
# ---------------------------------------------------------------------------------------------
class Banked(Exception):
    """The function is no longer an open stub — corpus.matched (sig MINUS stubs, the invariant-
    derived oracle) says it already builds from C byte-exactly. The 28-of-113 eval-set entries in
    this state are what a naive `[s for s in stubs if s.symbol==fn][0]` resolver CRASHES on: the
    functions banked after the set was drawn (S68 closed 23), so their INCLUDE_ASM — and usually
    their .s — is gone. 'Already banked, the draft is obsolete' is a real classification, not an
    error."""


def resolve_stub(binary, fn):
    """(asm_dir, s_path) via corpus.stubs; raises Banked for a since-matched function; falls back
    to a tree glob so a carve-dirty binary still yields the target .s when it exists."""
    import corpus
    try:
        for s in corpus.stubs(binary).values():
            if s.symbol == fn:
                return s.asm_dir, os.path.join(REPO, s.asm_dir, fn + ".s")
    except Exception as e:
        err = repr(e)
    else:
        err = "no open stub named %s in %s" % (fn, binary)
        try:
            m = corpus.matched(binary)
            addr = None
            if re.fullmatch(r"func_[0-9A-Fa-f]{8}", fn):
                addr = int(fn[5:], 16)
            if (addr in m) or any((r.get("name") or "").lower() == fn.lower() for r in m.values()):
                raise Banked("%s/%s builds from C already (corpus.matched, sig-minus-stubs)"
                             % (binary, fn))
        except Banked:
            raise
        except Exception:
            pass
    root = os.path.join(REPO, "asm") if binary == "main" else os.path.join(REPO, "asm", binary)
    hits = subprocess.run(["find", root, "-name", fn + ".s", "-path", "*nonmatchings*"],
                          capture_output=True, text=True).stdout.split()
    if binary == "main":                                # main's tree root also holds every overlay
        hits = [h for h in hits
                if os.path.relpath(h, os.path.join(REPO, "asm")).split(os.sep)[0] == "nonmatchings"]
    if len(hits) == 1:
        return os.path.relpath(os.path.dirname(hits[0]), REPO), hits[0]
    raise LookupError("%s/%s: %s; glob found %d candidates" % (binary, fn, err, len(hits)))


def run_match_one(fn, draft, asm_dir, tag):
    wd = os.path.join(WORK_ROOT, tag)
    os.makedirs(wd, exist_ok=True)
    streams_path = os.path.join(wd, "streams.json")
    p = subprocess.run([sys.executable, "tools/match_one.py", fn, "--c", draft,
                       "--asm-subdir", asm_dir, "--json", "--work", wd,
                       "--emit-streams", streams_path],
                      capture_output=True, text=True, cwd=REPO, timeout=300)
    last = p.stdout.strip().splitlines()[-1] if p.stdout.strip() else ""
    try:
        res = json.loads(last)
    except (json.JSONDecodeError, ValueError):
        raise RuntimeError("match_one emitted no JSON (rc=%d): stdout=%r stderr=%r"
                           % (p.returncode, p.stdout[-400:], p.stderr[-400:]))
    streams = None
    if os.path.exists(streams_path):
        with open(streams_path) as f:
            sj = json.load(f)
        streams = Streams(sj["mine"], sj["tgt"], sj.get("mine_relocs", {}))
    return res, streams


def bypass_as_o2(fn, draft, s_path, tag):
    """The §188 oracle (oracle_reorder semantics): cc1 raw, move->addu, `as -O2`, NO maspsx.
    Returns the masked diff count, or None when the bypass path itself fails (no verdict)."""
    wd = os.path.join(WORK_ROOT, tag, "bypass")
    os.makedirs(wd, exist_ok=True)
    src = masked_diff.strip_scalar_typedefs(open(draft).read())
    if '#include "common.h"' not in src:
        src = '#include "common.h"\n' + src
    open(os.path.join(wd, "t.c"), "w").write(src)
    cpp = ("mipsel-linux-gnu-cpp -lang-c -Iinclude -undef -Wall -fno-builtin -Dmips -D__GNUC__=2 "
           "-D__OPTIMIZE__ -Dpsx -D_PSYQ -D_MIPSEL -D_LANGUAGE_C").split() + [os.path.join(wd, "t.c")]
    cc1 = ["tools/bin/gcc-2.7.2-psx/cc1"] + "-quiet -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker".split()
    p = subprocess.run(cpp, capture_output=True, cwd=REPO)
    if p.returncode:
        return None
    q = subprocess.run(cc1, input=p.stdout, capture_output=True, cwd=REPO)
    if q.returncode:
        return None
    asm = re.sub(r"\tmove\t(\$\w+),(\$\w+)",
                 lambda m: "\taddu\t%s,%s,$0" % (m.group(1), m.group(2)), q.stdout.decode())
    r = subprocess.run(["mipsel-linux-gnu-as"] + "-Iinclude -march=r3000 -mtune=r3000 -no-pad-sections -O2 -G0".split()
                       + ["-o", os.path.join(wd, "t.o")], input=asm.encode(), capture_output=True, cwd=REPO)
    if r.returncode:
        return None
    try:
        mine = masked_diff.insns_from_object(os.path.join(wd, "t.o"), fn)
        tgt = masked_diff.insns_from_s(s_path)
        if not mine:
            return None
        return len(masked_diff.structured_diff(mine, tgt))
    except Exception:
        return None


# ---------------------------------------------------------------------------------------------
# the rules
# ---------------------------------------------------------------------------------------------
def _fire(rules, rule, conf, section, evidence, fix, **extra):
    rules.append(dict(rule=rule, confidence=conf, section=section,
                      evidence=evidence, fix=fix, **extra))


def rule_368(st, diffs, rules):
    """Reload-remat constant: commutative-swap wrong-register rows + moved constant load."""
    swaps, consts = [], []
    for i in diffs:
        if i >= len(st.mine) or i >= len(st.tgt):
            continue
        mw, tw = st.mine[i], st.tgt[i]
        cl_m, cl_t = _const_load(mw), _const_load(tw)
        if cl_m and cl_t and cl_m[1] == cl_t[1] and cl_m[0] != cl_t[0]:
            consts.append((i, cl_m[0], cl_t[0], cl_m[1]))
            continue
        if _op(mw) == 0 and _op(tw) == 0 and (mw & 63) == (tw & 63) and (mw & 63) in _COMMUTATIVE:
            m_rs, m_rt, m_rd, _ = _fields(mw)
            t_rs, t_rt, t_rd, _ = _fields(tw)
            if m_rd != t_rd:
                continue
            # ANTI-REORDER GUARD (held-out audit, func_80020DA4): in a schedule-reordered stream
            # of many mults, an aligned-position compare can pair two DIFFERENT mults and read
            # them as an operand swap. A genuine §368 swap row's words exist NOWHERE else in the
            # residual; a reorder's words re-occur verbatim at another diff position.
            reorder = (any(j != i and j < len(st.tgt) and st.tgt[j] == mw for j in diffs)
                       or any(j != i and j < len(st.mine) and st.mine[j] == tw for j in diffs))
            if reorder:
                continue
            # shared operand crossed slots: mine (x, c) vs target (c', x)
            if m_rs == t_rt and m_rt != t_rs and (m_rs, m_rt) != (t_rs, t_rt):
                swaps.append((i, m_rt, t_rs))            # (row, c_mine, c_target)
    if not swaps:
        return
    # constant confirmation: a const row whose register pair matches a swap row's pair
    confirmed = [s for s in swaps for c in consts if (s[1], s[2]) == (c[1], c[2])]
    conf = "certain" if confirmed else "high"
    _fire(rules, "R368-RELOAD-REMAT", conf, "§368",
          "commutative-swap wrong-register row(s) at %s (constant reg op-2 in mine, op-1 in "
          "target)%s" % ([s[0] for s in swaps],
                         "; SAME immediate 0x%X loads into the swapped registers at %s"
                         % (consts[0][3], [c[0] for c in consts]) if confirmed else ""),
          "function-scope single-set local for the constant, assigned once at entry, used "
          "constant-first (§368). Do NOT pin — pins measured worse (18/14 vs 8).")


def _src_regs(w):
    """The GPR numbers this word READS (source roles only — a dest-register difference is an
    allocation choice, not a captured use; counting it fabricated a §372 hit on func_80186020)."""
    op = _op(w)
    rs, rt, rd, _ = _fields(w)
    if op == 0:
        fn = w & 63
        if fn in (0, 2, 3):                      # sll/srl/sra: rt is the source
            return [rt]
        if fn in (4, 6, 7):                      # sllv/srlv/srav: rs=amount, rt=value
            return [rs, rt]
        if fn in (8, 9):                         # jr/jalr
            return [rs]
        if fn in (16, 18):                       # mfhi/mflo
            return []
        if fn in (17, 19):                       # mthi/mtlo
            return [rs]
        return [rs, rt]                          # alu 3-reg, mult/div, syscall-ish
    if op == 1 or op in (6, 7):                  # regimm / blez / bgtz
        return [rs]
    if op in (4, 5):                             # beq/bne
        return [rs, rt]
    if 8 <= op <= 14:                            # addi..xori: rs source, rt dest
        return [rs]
    if op == 15:                                 # lui
        return []
    if 32 <= op <= 38:                           # loads: base only
        return [rs]
    if 40 <= op <= 46:                           # stores: base AND value
        return [rs, rt]
    if 48 <= op <= 51 or 56 <= op <= 59:         # lwc/swc: base
        return [rs]
    return [rs, rt]


def rule_372(st, diffs, rules, klass=None):
    """Copy-capture: a wrong-register row READS the dest of a nearby MATCHING copy. §372's own
    wording scopes the tell to REGALLOC residuals; on a structural klass (WIDTH/OPCODE-MIXED/…)
    the same register coincidence rides on a different instruction shape, so confidence drops."""
    diffset = set(diffs)
    fwd_hits, inv_hits = [], []
    for i in diffs:
        if i >= len(st.mine) or i >= len(st.tgt):
            continue
        mw, tw = st.mine[i], st.tgt[i]
        # same operation, register fields differ, immediate agrees under the mask
        try:
            sm, rm, im = residual_class.decode(mw)
            stg, rt_, it = residual_class.decode(tw)
        except residual_class.UnknownOpcode:
            continue
        if sm != stg or len(rm) != len(rt_):
            continue
        if (im != it) and (st.masks[i] & 0xFFFF):
            continue
        pairs = [(a, b) for a, b in zip(_src_regs(mw), _src_regs(tw)) if a != b]
        if not pairs:
            continue
        lo, hi = max(0, i - 10), min(len(st.mine), i + 11)
        for j in range(lo, hi):
            if j in diffset or j >= len(st.tgt):
                continue                                  # the copy insn itself must MATCH
            mv = _is_move(st.mine[j])
            if not mv:
                continue
            dst, src = mv
            for a, b in pairs:
                if (a, b) == (dst, src):
                    fwd_hits.append((i, j, dst, src))     # mine reads dest, target reads src
                elif (a, b) == (src, dst):
                    inv_hits.append((i, j, dst, src))
    reg_klass = klass in (None, "REGALLOC-PERM", "REGALLOC-LOCAL")
    if fwd_hits:
        _fire(rules, "R372-COPY-CAPTURE", "high" if reg_klass else "medium", "§372",
              "wrong-register row(s) %s read the DEST of matching copy insn(s) at %s (cse "
              "make_regs_eqv / optimize_reg_copy_1 re-based the use onto the copy dest)"
              % (sorted({h[0] for h in fwd_hits}), sorted({h[1] for h in fwd_hits})),
              "spell the copy as `P = X + zr` with `register s32 zr __asm__(\"$0\")` — "
              "byte-identical addu encoding, defeats both capture passes (§372).")
    elif inv_hits:
        _fire(rules, "R372-INV-COPY-KEPT", "medium", "§372",
              "TARGET reads the copy DEST where mine reads the src (rows %s, copies at %s): the "
              "original source kept the capture alive"
              % (sorted({h[0] for h in inv_hits}), sorted({h[1] for h in inv_hits})),
              "let the copy capture: order the uses AFTER the copy in source order, or keep a "
              "live copy of the incoming argument (§372 entry-copy flavor, WITHOUT +zr).")


def _rediff_without(st, drop):
    """Masked diff count + positions of (mine minus the index `drop`) vs tgt."""
    m = [(w, k) for i, (w, k) in enumerate(zip(st.mine, st.masks)) if i != drop]
    out = []
    for i in range(max(len(m), len(st.tgt))):
        if i >= len(m) or i >= len(st.tgt):
            out.append(i)
            continue
        w, k = m[i]
        if (w & k) != (st.tgt[i] & k):
            out.append(i)
    return m, out


def rule_slot(st, verdict, diffs, rules):
    """§370 slot-steal / §373 slot-fill / §5a over-eager fill.

    THE +1 SHAPE, derived by construction, not assumed: a slot-steal the draft fails to reproduce
    displaces the stolen insn (mine has it BEFORE the branch, the target has it IN the slot) AND
    inserts a nop — so the residual is never a clean one-point tail drift. The operational test is
    REMOVE THE SLOT NOP AND RE-DIFF: if what remains is equal, the target filled the slot from the
    fall-through; if what remains is a small same-multiset window, the filler was stolen from
    upstream (reorg fill_simple_delay_slots scanning back)."""
    d = len(st.mine) - len(st.tgt)
    if d == 1 and diffs:
        cands = [s for s in range(1, len(st.mine))
                 if st.mine[s] == 0 and is_branch(st.mine[s - 1])
                 and diffs[0] - 12 <= s <= diffs[-1] + 1]
        for s in cands:
            m2, d2 = _rediff_without(st, s)
            if not d2:
                _fire(rules, "R373-SLOT-FILL", "high", "§373/§370/§176-A",
                      "removing MY slot nop at %d makes the streams EQUAL — the target fills that "
                      "branch's delay slot from the fall-through where mine emits nop" % s,
                      "statement order around the branch/call decides the filler (§176-A); §373 "
                      "dead-reset / §373.2 anti-dep pin / §370 eligibility.")
                return
            if len(d2) <= 12 and d2[-1] - d2[0] <= 16:
                win = range(d2[0], min(d2[-1] + 1, len(m2), len(st.tgt)))
                ms = collections.Counter(m2[i][0] & m2[i][1] for i in win)
                ts = collections.Counter(st.tgt[i] & m2[i][1] for i in win)
                if ms == ts:
                    _fire(rules, "R370-SLOT-STEAL", "high", "§370/§373",
                          "mine +1 with a nop in the delay slot at %d; removing it leaves a "
                          "same-multiset window %s — the target's slot holds an insn reorg STOLE "
                          "from upstream; my spelling made it ineligible" % (s, [d2[0], d2[-1]]),
                          "spell the accumulating value SPLIT (early/mid/late statements) so it "
                          "lives outside the tail's registers and becomes slot-eligible (§370); "
                          "or the §373.2 pin that deletes the sched2 anti-dep.")
                    return
    # aligned nop-vs-insn rows
    tgt_filled, mine_filled = [], []
    for i in diffs:
        if i == 0 or i >= len(st.mine) or i >= len(st.tgt):
            continue
        after_branch = is_branch(st.mine[i - 1]) or is_branch(st.tgt[i - 1])
        if not after_branch:
            continue
        if st.mine[i] == 0 and st.tgt[i] != 0:
            tgt_filled.append(i)
        elif st.tgt[i] == 0 and st.mine[i] != 0:
            mine_filled.append(i)
    if tgt_filled and len(tgt_filled) * 2 >= len(diffs):
        _fire(rules, "R373-SLOT-FILL", "high", "§373/§370",
              "target fills delay slot(s) at %s where mine emits nop" % tgt_filled,
              "§373 dead-reset cse-breaker / §373.2 anti-dep pin / §370 split-accumulator "
              "eligibility; check §176-A statement order first on a call slot.")
    elif mine_filled and len(mine_filled) * 2 >= len(diffs):
        _fire(rules, "R5A-FENCE", "high", "§5a/§34/§336",
              "MINE fills delay slot(s) at %s the target leaves as nop — gcc's filler was more "
              "eager than the original's" % mine_filled,
              "zero-byte `__asm__(\"\")` fence: reorg stop_search_p halts the filler (§5a, §34); "
              "place it at the BOTTOM of a duplicated block (§336).")


_CASE_RE = re.compile(r"case\s+(0[xX][0-9a-fA-F]+|\d+)\s*:\s*case\s+(0[xX][0-9a-fA-F]+|\d+)\s*:")


def rule_366(draft_text, verdict, rules):
    if verdict.get("klass") not in ("LENGTH-DRIFT", "SIZE-MISMATCH"):
        return
    d = verdict.get("detail", {}).get("delta", 0)
    if not (-40 <= d <= -2):
        return
    stacked = [(int(a, 0), int(b, 0)) for a, b in _CASE_RE.findall(draft_text)]
    consec = [p for p in stacked if p[1] == p[0] + 1 or p[0] == p[1] + 1]
    if consec:
        _fire(rules, "R366-STACKED-CASES", "high", "§366",
              "mine SHORTER by %d and the draft stacks consecutive case labels %s — "
              "group_case_nodes merged them into range nodes" % (-d, consec[:4]),
              "give EVERY case its own duplicated body + break; order arms so each family's "
              "cross_jump fold lands after its last contributing arm (§366, §298).")


def rule_339(st, verdict, rules):
    if verdict.get("klass") != "LENGTH-DRIFT" or verdict.get("detail", {}).get("delta") != -2:
        return
    k = verdict["detail"].get("at", 0)
    if k + 1 >= len(st.tgt):
        return
    w0, w1 = st.tgt[k], st.tgt[k + 1]
    is_cmp = _op(w0) in (10, 11) or (_op(w0) == 0 and (w0 & 63) in _CMP_FN)   # slti/sltiu/slt/sltu
    if is_cmp and is_branch(w1):
        _fire(rules, "R339-MISSING-CASE-NODE", "high", "§339",
              "mine shorter by exactly 2 and the target's extra pair at %d is compare+branch "
              "(%08x/%08x) — the low-bound range test only >=3 case nodes emit" % (k, w0, w1),
              "a case node is missing from the draft: add the missing arm (e.g. `case 0: "
              "return;`) — read the case count off the range test (§339).")


def rule_333(st, diffs, rules):
    if not diffs or len(st.mine) != len(st.tgt):
        return
    deltas, n_sp = set(), 0
    for i in diffs:
        if i >= len(st.mine) or i >= len(st.tgt):
            return
        mw, tw = st.mine[i], st.tgt[i]
        try:
            sm, rm, im = residual_class.decode(mw)
            stg, rt_, it = residual_class.decode(tw)
        except residual_class.UnknownOpcode:
            return
        if sm != stg or rm != rt_ or im is None or it is None:
            return
        base_sp = any(role == "g" and slot == 0 and v == 29 for role, slot, v in rm)
        is_mem = sm[0] == "m"
        is_sp_add = sm == ("i", 9) and base_sp
        if not ((is_mem and base_sp) or is_sp_add):
            return
        n_sp += 1
        dv = (it - im) & 0xFFFF
        dv = dv if dv < 0x8000 else dv - 0x10000
        # the sp-adjust rows (`addiu $sp,$sp,-F`) move OPPOSITE to the offset rows when the frame
        # grows: normalise to "frame delta" sign so one frame change reads as ONE delta.
        deltas.add(-dv if is_sp_add else dv)
    if n_sp and len(deltas) == 1:
        dv = deltas.pop()
        _fire(rules, "R333-FRAME-SIZE", "high", "§333/§334/§335/§193-I",
              "all %d diff rows are $sp-relative with ONE constant delta %+d — the frame differs, "
              "the body does not" % (n_sp, dv),
              "declare the missing bytes as an UNREFERENCED trailing aggregate local (§333); if "
              "+8/+16, suspect a reload spill slot rounded to 8B (§334) or extern-array dead "
              "temps (§335); N arrays vs one struct shifts every displacement (§193-I).")


def rule_333_component(st, diffs, rules):
    """A CONSISTENT frame-size delta visible in the prologue/epilogue rows of an OTHERWISE noisy
    residual (held-out audit, func_80020DA4: `addiu $sp,-8` vs `-0x18` + all four save/restore
    offsets shifted +0x10 amid a mult-chain reorder). A component verdict, deliberately medium:
    it explains PART of the residual, not all of it."""
    if any(r["rule"] == "R333-FRAME-SIZE" for r in rules) or len(st.mine) != len(st.tgt):
        return
    deltas, rows = set(), []
    for i in diffs:
        if i >= len(st.mine) or i >= len(st.tgt):
            continue
        mw, tw = st.mine[i], st.tgt[i]
        om, ot = _op(mw), _op(tw)
        m_rs, m_rt, _rd, im = _fields(mw)
        t_rs, t_rt, _trd, it = _fields(tw)
        dv = (it - im) & 0xFFFF
        dv = dv if dv < 0x8000 else dv - 0x10000
        if om == ot == 9 and m_rs == t_rs == 29 and m_rt == t_rt == 29:      # addiu $sp,$sp,K
            deltas.add(-dv)
            rows.append(i)
        elif (om == ot and (32 <= om <= 46) and m_rs == t_rs == 29 and m_rt == t_rt):
            deltas.add(dv)                                                   # $sp-relative mem
            rows.append(i)
    if len(rows) >= 3 and len(deltas) == 1:
        dv = deltas.pop()
        if dv:
            _fire(rules, "R333-FRAME-COMPONENT", "medium", "§333/§334/§335",
                  "%d prologue/epilogue rows (%s) show ONE consistent frame delta %+#x amid other "
                  "residual noise" % (len(rows), rows[:6], dv),
                  "part of this residual is a frame-size delta: an unreferenced trailing aggregate "
                  "(§333), a reload spill slot rounded to 8B (§334), or extern-array dead temps "
                  "(§335) — fix the frame first, then re-measure the rest.")


def rule_small_flips(st, diffs, rules):
    """slti<->sltiu (§35) and beq<->bne (§3-T4) pure flips, decided on words."""
    if not diffs:
        return
    sign, pol = [], []
    for i in diffs:
        if i >= len(st.mine) or i >= len(st.tgt):
            return
        mw, tw = st.mine[i], st.tgt[i]
        om, ot = _op(mw), _op(tw)
        if {om, ot} == {10, 11} and (mw & 0x03FFFFFF) == (tw & 0x03FFFFFF):
            sign.append(i)
        elif {om, ot} == {4, 5} and (mw & 0x03FFFFFF & st.masks[i]) == (tw & 0x03FFFFFF & st.masks[i]):
            pol.append(i)
        else:
            return                                       # not a PURE flip residual
    if sign and not pol:
        _fire(rules, "R35-SIGNEDNESS", "high", "§35/§21",
              "diff rows %s are slti<->sltiu with identical regs+imm" % sign,
              "keep a separate SIGNED int copy of the unsigned load (§35); write each bound as "
              "its own if/goto so the range does not fold (§21).")
    elif pol and not sign:
        _fire(rules, "RPOL-BRANCH-POLARITY", "high", "§3-T4/§32",
              "diff rows %s are beq<->bne with identical operands" % pol,
              "invert the source condition / swap the arms (§3-T4); see §32.2 for operand order.")


def rule_jint(st, diffs, rules):
    rows = [i for i in diffs if i < len(st.mine) and i < len(st.tgt)
            and _op(st.mine[i]) == 2 and _op(st.tgt[i]) == 2]
    if rows and len(rows) == len(diffs):
        _fire(rules, "RJINT-WRONG-J-TARGET", "high", "§195-D/§162",
              "every diff row (%s) is a `j` on both sides — same instruction, different label: "
              "break-vs-return or a goto to the wrong arm" % rows,
              "check which arm falls through vs jumps: the surviving cross-jump copy is the "
              "LATER one; a backward `j` into a sibling arm is a source `goto` (§162, §195-D).")


def _shape_rules(st, verdict, diffs, draft, rules):
    """The word-level shape rules + klass-driven advisories, shared by the direct path and the
    post-autodecl path."""
    rule_368(st, diffs, rules)
    rule_372(st, diffs, rules, klass=verdict.get("klass"))
    rule_slot(st, verdict, diffs, rules)
    try:
        rule_366(open(os.path.join(REPO, draft)).read(), verdict, rules)
    except OSError:
        pass
    rule_339(st, verdict, rules)
    rule_333(st, diffs, rules)
    rule_333_component(st, diffs, rules)
    rule_small_flips(st, diffs, rules)
    rule_jint(st, diffs, rules)

    # klass-driven ADVISORIES (medium: the klass is residual_class's, the section mapping is the
    # cookbook-index's symptom table — useful routing, but not this tool's own discovery)
    if verdict.get("klass") == "BRANCH-POLARITY" and not any(
            r["confidence"] in ("certain", "high") for r in rules):
        _fire(rules, "RPOL-KLASS", "medium", "§3-T4/§32",
              "residual_class: every opcode diff is a branch-family flip",
              "invert the source condition / swap the arms (§3-T4, §32.2); trailing return-0 "
              "note at cookbook L1344.")
    if verdict.get("klass") == "DELAY-SLOT" and not any(
            r["confidence"] in ("certain", "high") for r in rules):
        _fire(rules, "RSLOT-KLASS", "medium", "§373/§370/§176-A/§5a",
              "residual_class: nop-vs-insn dominates the diff rows",
              "delay-slot fill difference: §176-A statement order first, then §373 dead-reset / "
              "§370 eligibility (target-filled) or the §5a/§34 fence (mine-filled).")


def _autodecl_retry(binary, fn, draft, s_path, undecl, tag):
    """Compute the missing externs FROM THE TARGET .s BYTE EVIDENCE (decl_from_use — access
    widths/signs read off real opcodes, nothing invented), patch the draft, re-measure. Up to two
    rounds (a first patch can surface further undeclared symbols).

    Returns (match_one_result, Streams, note) or (None, None, why_not_str). `note["defaulted"]`
    marks decls that carried a sign/width DEFAULT — the caller caps rule confidence for those,
    because a defaulted width can itself be the residual it then classifies."""
    try:
        import decl_from_use as dfu
    except Exception as e:
        return None, None, "decl_from_use unavailable: %r" % e
    try:
        text = open(os.path.join(REPO, draft)).read()
    except OSError as e:
        return None, None, "draft unreadable: %r" % e
    decls, defaulted = {}, False
    try:
        ev, _seen_section = dfu.collect(s_path, binary)
    except Exception as e:
        return None, None, "collect(%s) failed: %r" % (os.path.basename(s_path), e)
    todo = list(undecl)
    for _round in (1, 2):
        try:
            masked = dfu.blank_decl_statements(text)
        except Exception:
            masked = text
        for sym in todo:
            if sym in decls:
                continue
            try:
                forms = dfu.usage_forms(masked, sym)
                r = dfu.infer(sym, ev, forms)
                decls[sym] = r["decl"]
                if any("default" in f for f in r.get("flags", [])):
                    defaulted = True
            except dfu.Refuse as e:
                return None, None, "infer(%s) refused: %s" % (sym, e)
            except Exception as e:
                return None, None, "infer(%s) failed: %r" % (sym, e)
        try:
            patched = dfu.insert_decls(text, decls)
        except Exception as e:
            return None, None, "insert_decls failed: %r" % e
        pdir = os.path.join(WORK_ROOT, tag)
        os.makedirs(pdir, exist_ok=True)
        ppath = os.path.join(pdir, "autodecl.c")
        open(ppath, "w").write(patched)
        try:
            res, st = run_match_one(fn, os.path.relpath(ppath, REPO),
                                    os.path.relpath(os.path.dirname(s_path), REPO),
                                    tag + ".ad%d" % _round)
        except Exception as e:
            return None, None, "re-measure failed: %r" % e
        if res.get("status") in ("match", "near", "fail"):
            return res, st, {"decls": decls, "defaulted": defaulted, "rounds": _round}
        more = sorted(set(re.findall(r"`(\w+)' undeclared", res.get("error", ""))) - set(decls))
        if not more:
            return None, None, ("patched compile still fails (%s): %s"
                                % (res.get("status"), res.get("error", "")[:120]))
        todo = more
    return None, None, "undeclared symbols kept surfacing after 2 rounds"


# ---------------------------------------------------------------------------------------------
# per-case driver
# ---------------------------------------------------------------------------------------------
def classify(binary, fn, draft, tag=None):
    """One case -> a verdict dict with the fired rules, best-first."""
    tag = tag or ("%s.%s" % (binary, fn))
    out = dict(binary=binary, fn=fn, draft=draft, rules=[], status=None, klass=None)
    rules = out["rules"]

    try:
        asm_dir, s_path = resolve_stub(binary, fn)
    except Banked as e:
        out["status"] = "banked"
        _fire(rules, "ALREADY-BANKED", "certain", "corpus.matched",
              str(e), "the function already byte-matches in the tree — this draft is obsolete; "
              "spend zero tokens (a stale card, not a matching problem).")
        return _finish(out)
    except Exception as e:
        out["status"] = "error"
        out["error"] = "resolve: %s" % e
        return out
    out["asm_dir"] = asm_dir

    # W332 — target-side, draft-independent, checked FIRST
    hits = wall_sweep.scan(s_path)
    if hits:
        _fire(rules, "W332-MASPSX-WALL", "certain", "§332",
              "%d delay slot(s) in the TARGET hold a %%lo macro tail (first: line %d, `%s` / "
              "slot `%s`) — unreachable from C under the pinned triple, whatever the draft says"
              % (len(hits), hits[0][0], hits[0][1][-40:], hits[0][2][-40:]),
              "toolchain wall: ledger it, never draft, never escalate (§332/§332a); needs the "
              "narrow maspsx macro-hop patch, not C work.")

    if not os.path.exists(os.path.join(REPO, draft)):
        out["status"] = "error"
        out["error"] = "draft file missing: %s" % draft
        return out

    try:
        res, st = run_match_one(fn, draft, asm_dir, tag)
    except Exception as e:
        out["status"] = "error"
        out["error"] = "match_one: %s" % e
        return out

    out["status"] = res.get("status")
    out["closeness"] = res.get("closeness")
    verdict = res.get("verdict") or {}
    out["klass"] = verdict.get("klass")

    if out["status"] not in ("match", "near", "fail"):           # a toolchain-stage failure
        err = res.get("error", "")
        if re.search(r"conflicting types|redeclar|redefin", err):
            _fire(rules, "NOCOMPILE-DECL-CONFLICT", "high", "§337/§367/§37",
                  "cc1 rejects a declaration conflict: %s" % err.strip().splitlines()[-1][:160],
                  "adopt the TU's banked spelling and adapt the use site (§367), or the §37/§183 "
                  "asm-label alias; the static blocker oracle is blind here (§337) — finish on "
                  "the real whole-TU compile.")
            return _finish(out)
        undecl = sorted(set(re.findall(r"`(\w+)' undeclared", err)))
        if undecl:
            res2, st2, note = _autodecl_retry(binary, fn, draft, s_path, undecl, tag)
            if res2 is not None:
                out["autodecl"] = note
                if res2.get("status") == "match":
                    out["status"] = "match"
                    out["closeness"] = 0
                    _fire(rules, "NOCOMPILE-UNDECLARED-FIXED", "certain", "decl_from_use/§58",
                          "the ONLY defect was %d missing extern(s) (%s); with decls COMPUTED "
                          "from the target .s access widths the body byte-matches standalone"
                          % (len(undecl), ", ".join(note["decls"].values())),
                          "add the computed extern(s) and route to integration — the matching "
                          "work is already done.")
                    return _finish(out)
                if res2.get("status") in ("near", "fail") and st2 is not None:
                    out["status"] = res2["status"]
                    out["closeness"] = res2.get("closeness")
                    verdict = res2.get("verdict") or {}
                    out["klass"] = verdict.get("klass")
                    _fire(rules, "NOCOMPILE-UNDECLARED-MEASURED", "medium", "decl_from_use",
                          "%d missing extern(s) auto-computed from the .s (%s); the patched "
                          "draft measures closeness %s %s"
                          % (len(undecl), ", ".join(note["decls"].values()),
                             res2.get("closeness"), verdict.get("klass")),
                          "add the computed extern(s); then treat the residual below.")
                    res, st = res2, st2
                    diffs = st.diffs()
                    out["ndiffs"] = len(diffs)
                    _shape_rules(st, verdict, diffs, draft, rules)
                    if note.get("defaulted"):
                        for r in rules:                 # a defaulted sign/width can BE the residual
                            if r["confidence"] in ("certain", "high") and r["rule"] not in (
                                    "W332-MASPSX-WALL",):
                                r["confidence"] = "medium"
                                r["capped"] = "autodecl sign/width default may cause this residual"
                    return _finish(out)
            _fire(rules, "NOCOMPILE-UNDECLARED", "high", "§337/decl_from_use",
                  "undeclared symbol(s) %s%s" % (undecl, "; " + note if isinstance(note, str) else ""),
                  "supply the externs (tools/decl_from_use.py computes them from the target .s "
                  "access widths) or gate in-TU where the TU already declares them.")
            return _finish(out)
        _fire(rules, "NOCOMPILE", "medium", "§337",
              "%s: %s" % (out["status"], err.strip().splitlines()[-1][:160] if err else "?"),
              "fix the compile blocker first; the residual cannot be measured until it builds.")
        return _finish(out)

    if out["status"] == "match":
        _fire(rules, "INTEG-STANDALONE-MATCH", "certain", "§58/§59/§367",
              "closeness 0: the draft is byte-correct standalone",
              "the blocker is TU integration (decl reconcile ladder, §367 banked-spelling rule); "
              "matching is done — budget for banking.")
        return _finish(out)

    if st is None:
        out["error"] = "no streams emitted"
        return _finish(out)

    diffs = st.diffs()
    out["ndiffs"] = len(diffs)

    # W188 — the as -O2 bypass oracle (skip for -O0 targets: no scheduling there)
    o0 = False
    try:
        from o0_detect import detect_o0
        o0 = detect_o0(s_path)
    except Exception:
        pass
    if not o0 and not any(r["rule"] == "W332-MASPSX-WALL" for r in rules):
        bd = bypass_as_o2(fn, draft, s_path, tag)
        out["bypass_diffs"] = bd
        if bd == 0:
            _fire(rules, "W188-EPILOGUE-WALL", "certain", "§188",
                  "the SAME C, maspsx bypassed + `as -O2`, gives 0 diffs — the draft is "
                  "byte-correct and the pinned `as -O1` can never emit it",
                  "file IMMOVABLE (§188): no C-level work can close it; candidate for "
                  "psyq_integrate if it is an SDK object (§332a).")

    # the shape rules, word-level
    _shape_rules(st, verdict, diffs, draft, rules)

    # pass-throughs (existing knowledge, deliberately capped at medium)
    if verdict.get("klass") == "SIZE-MISMATCH" and not rules:
        _fire(rules, "REDRAFT-SIZE-MISMATCH", "medium", "residual_class",
              "the draft is a different-sized function (ratio %s)"
              % verdict.get("detail", {}).get("ratio"),
              "re-draft from the target .s; never seed-tweak this (rebadged residual_class verdict).",
              rebadged=True)
    if verdict.get("klass") == "REGALLOC-PERM" and not any(
            r["confidence"] in ("certain", "high") for r in rules):
        _fire(rules, "R31-REGALLOC-PERM", "medium", "§31/§17/§76",
              "one injective register map explains every diff: %s"
              % verdict.get("detail", {}).get("cycles"),
              "§31 decl/statement-order levers; §17 register pins; §76 condition-local reuse; "
              "permuter `regalloc` profile.")

    return _finish(out)


_CONF_ORD = {"certain": 0, "high": 1, "medium": 2, "low": 3}


def _finish(out):
    out["rules"].sort(key=lambda r: _CONF_ORD.get(r["confidence"], 9))
    out["top"] = out["rules"][0]["rule"] if out["rules"] else None
    out["top_confidence"] = out["rules"][0]["confidence"] if out["rules"] else None
    return out


# ---------------------------------------------------------------------------------------------
# eval sweep + selftest
# ---------------------------------------------------------------------------------------------
def _one(e, idx):
    try:
        return classify(e["binary"], e["fn"], e["draft"], tag="%03d.%s.%s" % (idx, e["binary"], e["fn"]))
    except Exception as ex:                              # loud in the data, never silent (R32)
        return dict(binary=e["binary"], fn=e["fn"], draft=e["draft"],
                    status="error", error="classify crashed: %r" % ex, rules=[],
                    top=None, top_confidence=None)


def run_eval(path, jobs):
    import concurrent.futures as cf
    cases = json.load(open(path))
    print("eval set: %d cases (the denominator)" % len(cases))
    results = [None] * len(cases)
    with cf.ThreadPoolExecutor(max_workers=jobs) as ex:
        futs = {ex.submit(_one, e, i): i for i, e in enumerate(cases)}
        done = 0
        for f in cf.as_completed(futs):
            i = futs[f]
            results[i] = f.result()
            done += 1
            r = results[i]
            print("  [%3d/%3d] %-14s %-16s %-7s top=%s (%s)"
                  % (done, len(cases), r["binary"], r["fn"], r.get("status"),
                     r.get("top"), r.get("top_confidence")), flush=True)
    os.makedirs(WORK_ROOT, exist_ok=True)
    with open(os.path.join(WORK_ROOT, "eval_results.jsonl"), "w") as f:
        for r in results:
            f.write(json.dumps(r) + "\n")
    summarize(results)
    return results


def summarize(results):
    n = len(results)
    errored = [r for r in results if r.get("status") == "error"]
    banked = [r for r in results if r.get("status") == "banked"]
    classified = [r for r in results if r.get("status") != "error"]
    nocompile = [r for r in classified
                 if r.get("status") not in ("match", "near", "fail", "banked")]
    fired = [r for r in classified if r.get("top")]
    certhigh = [r for r in fired if r.get("top_confidence") in ("certain", "high")]
    ch_resid = [r for r in certhigh
                if r["top"] not in ("ALREADY-BANKED",) and not r["top"].startswith("NOCOMPILE")
                and not r["rules"][0].get("rebadged")]
    print("\n================ SCORE (denominator: %d cases) ================" % n)
    print("processed without error : %d  (%.0f%%)" % (len(classified), 100.0 * len(classified) / n))
    print("ERRORED                 : %d" % len(errored))
    for r in errored:
        print("    %s/%s: %s" % (r["binary"], r["fn"], r.get("error", "?")[:120]))
    print("ALREADY-BANKED (stale entries — the rival's 28-error class): %d" % len(banked))
    print("any rule fired          : %d  (%.0f%%)" % (len(fired), 100.0 * len(fired) / n))
    print("certain/high (ALL)      : %d  (%.0f%%)" % (len(certhigh), 100.0 * len(certhigh) / n))
    print("certain/high RESIDUAL-SHAPE only (excl. ALREADY-BANKED + NOCOMPILE + rebadged): "
          "%d  (%.0f%%)" % (len(ch_resid), 100.0 * len(ch_resid) / n))
    print("  (compile-fail drafts in the set: %d)" % len(nocompile))
    tab = collections.Counter()
    for r in classified:
        for ru in r["rules"]:
            tab[(ru["rule"], ru["confidence"])] += 1
    print("\nper-rule firing table (every fired rule, not only top):")
    for (rule, conf), c in sorted(tab.items(), key=lambda kv: (-kv[1], kv[0])):
        print("  %-26s %-8s %3d" % (rule, conf, c))
    klasses = collections.Counter(r.get("klass") for r in classified)
    print("\nresidual_class klass distribution: %s" % dict(klasses))


def selftest():
    """The two development cases with KNOWN, PROVEN causes. A detector that cannot reproduce a
    case whose answer is known is not evidence — this must pass before any sweep is trusted."""
    ok = True
    r1 = classify("ov_SC03_105", "func_80187A30", ".run/S68o1/opus/func_80187A30.c", tag="self.368")
    top1 = [ru for ru in r1["rules"] if ru["rule"] == "R368-RELOAD-REMAT"]
    print("dev case §368 ov_SC03_105/func_80187A30: top=%s conf=%s"
          % (r1.get("top"), r1.get("top_confidence")))
    if not top1 or top1[0]["confidence"] not in ("certain", "high") or r1["top"] != "R368-RELOAD-REMAT":
        print("  FAIL: expected R368-RELOAD-REMAT as top rule; got %s" % r1["rules"])
        ok = False
    else:
        print("  OK   evidence: %s" % top1[0]["evidence"][:140])
    r2 = classify("main", "func_8005D734", ".run/S68m1/sonnet/func_8005D734.c", tag="self.332")
    print("dev case §332 main/func_8005D734: top=%s conf=%s"
          % (r2.get("top"), r2.get("top_confidence")))
    if r2.get("top") != "W332-MASPSX-WALL" or r2.get("top_confidence") != "certain":
        print("  FAIL: expected W332-MASPSX-WALL certain; got %s" % r2["rules"])
        ok = False
    else:
        print("  OK   evidence: %s" % r2["rules"][0]["evidence"][:140])
    print("SELFTEST %s" % ("PASS" if ok else "FAIL"))
    return 0 if ok else 1


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--binary")
    ap.add_argument("--fn")
    ap.add_argument("--draft")
    ap.add_argument("--eval", dest="eval_path")
    ap.add_argument("--jobs", type=int, default=8)
    ap.add_argument("--selftest", action="store_true")
    a = ap.parse_args()
    os.makedirs(WORK_ROOT, exist_ok=True)
    if a.selftest:
        return selftest()
    if a.eval_path:
        run_eval(a.eval_path, a.jobs)
        return 0
    if not (a.binary and a.fn and a.draft):
        ap.error("need --binary --fn --draft (or --eval / --selftest)")
    r = classify(a.binary, a.fn, a.draft)
    print(json.dumps(r, indent=1))
    return 0


if __name__ == "__main__":
    sys.exit(main())
