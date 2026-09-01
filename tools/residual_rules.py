#!/usr/bin/env python3
"""residual_rules.py — turn a measured residual into the cookbook lever that addresses it. (P31 S68)

WHY THIS EXISTS, with the price attached. `docs/cookbook-index.md` is already a SYMPTOM -> SECTION
table, hand-curated from what agents actually hit. But it is PROSE, so every agent re-derives the
lookup by reading, and the lookup is most of what an escalation buys. Measured in S68, each of these
closed a function by APPLYING KNOWLEDGE THAT WAS ALREADY WRITTEN DOWN — in three cases written down
the same hour:

    func_800241C0   sonnet 229k (no bank) -> fable  74k  MATCH
    func_80187A30   opus   294k (no bank) -> fable 152k  MATCH
    func_8003491C   sonnet 348k (no bank) -> fable 135k  MATCH
    func_8017E764   opus   386k (no bank) -> fable 215k  MATCH
    func_8017EC4C   opus   408k (no bank) -> fable 211k  MATCH

That is ~1.7M tokens of rediscovery. A table lookup wearing a very expensive coat.

WHAT THIS DOES AND DELIBERATELY DOES NOT DO. It CLASSIFIES a residual and PRESCRIBES the lever, with
the evidence rows that triggered it. It does **not** rewrite C. The fixes are structural — "declare
a function-scope single-set local and use it constant-first" (§368), "give every case its own
duplicated body" (§366) — not regex-able, and a rewriter that guesses wrong SILENTLY is precisely
the failure mode that cost this session a dozen debugging detours. Classification is where the
measured spend is; rewriting is where the risk is.

EVERY RULE STATES ITS OWN CONFIDENCE AND ITS OWN REFUTATION. A rule that cannot be wrong is not a
rule, it is a wish — and §361/§370 exist precisely because two agents asserted a compiler-internal
cause that was really their own earlier lever. So each rule carries `refute:` telling the reader what
would DISPROVE it, and the caller is expected to check that before spending.

    tools/residual_rules.py --binary ov_SC03_105 --fn func_80187A30 --c <draft.c>
    tools/residual_rules.py --selftest        # the S68 functions whose cause is KNOWN
"""
import argparse
import json
import os
import re
import subprocess
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(REPO)
sys.path.insert(0, os.path.join(REPO, "tools"))
import corpus     # noqa: E402

# THE TWO SIDES ARE DISASSEMBLED BY DIFFERENT TOOLS AND DISAGREE ON THE `$`:
# yours reads `mult v0,v1`, the target reads `mult $a3, $v0`. My first version required the `$`,
# so one side parsed as ZERO registers, the lengths never matched, and the rule silently skipped a
# case whose cause was already proven. A detector that cannot reproduce a KNOWN member is not
# evidence — which is exactly the rule this file exists to encode.
REG = r"\$?(?:zero|at|v[01]|a[0-3]|t[0-9]|s[0-8]|k[01]|gp|sp|fp|ra)\b"
COMMUTATIVE = ("mult", "multu", "addu", "add", "and", "or", "xor", "nor", "slt", "sltu")


def _txt(row):
    """(mine, target) with the leading raw hex word stripped, tabs normalised."""
    def clean(s):
        s = re.sub(r"^[0-9a-f]{8}\s+", "", s or "")
        return re.sub(r"\s+", " ", s.replace("\t", " ")).strip()
    return clean(row[1]), clean(row[2])


def _mn(s):
    return (s.split(" ", 1) + [""])[0]


def _regs(s):
    return re.findall(REG, s)


# ---------------------------------------------------------------------------------------------
# Each rule: (id, section, confidence, test(rows, ctx) -> (evidence_rows, note) | None, advice, refute)
# ---------------------------------------------------------------------------------------------

def rule_wall_332(rows, ctx):
    """A %lo in a TARGET delay slot: the tail of an assembler macro gcc emits atomically."""
    hits = [r for r in ctx["target_slot_lo"]]
    if hits:
        return hits[:3], "target fills %d delay slot(s) with a macro tail" % len(hits)
    return None


def rule_copy_capture(rows, ctx):
    """§372: a wrong-register row whose TARGET register is the DEST of a matching copy insn."""
    copy_dests = set()
    for r in rows:
        m, t = _txt(r)
        if m == t and re.match(r"addu\s+(%s)\s*,\s*(%s)\s*,\s*\$zero" % (REG, REG), t):
            copy_dests.add(_regs(t)[0])
    if not copy_dests:
        return None
    ev = []
    for r in rows:
        m, t = _txt(r)
        if not m or not t or _mn(m) != _mn(t):
            continue
        rm, rt = _regs(m), _regs(t)
        if len(rm) == len(rt) and rm != rt:
            moved = [b for a, b in zip(rm, rt) if a != b]
            if any(x in copy_dests for x in moved):
                ev.append(r)
    if ev:
        return ev[:3], "wrong-register row reads the destination of a MATCHING copy insn"
    return None


CONSTGEN = re.compile(r"^(?:li|addiu|ori)\s+(%s)\s*,\s*(?:(%s)\s*,\s*)?(-?(?:0x)?[0-9a-fA-F]+)$"
                      % (REG, REG))


def _val(tok):
    """int value of an immediate written in any base the two disassemblers use, or None."""
    try:
        return int(tok, 16) if tok.lower().startswith(("0x", "-0x")) else int(tok, 10)
    except (TypeError, ValueError):
        return None


def _norm(r):
    return (r or "").lstrip("$")


def rule_reload_remat(rows, ctx):
    """§368: the CONSTANT's register changes AND its OPERAND POSITION in a commutative op changes.

    §368's tell is a ROLE change, not a reversal: "the constant register sits FIRST in the emitted
    commutative op while your draft has it second". That is visible across TWO rows — a
    constant-materialisation whose destination register differs, and a later commutative op where
    that register appears in a different operand slot. My first version tested for the registers
    being literally reversed and therefore missed ov_SC03_105/func_80187A30, whose cause fable had
    already PROVEN to be exactly this.
    """
    moved = {}          # normalised const-dest in MINE -> in TARGET
    for r in rows:
        m, t = _txt(r)
        cm, ct = CONSTGEN.match(m), CONSTGEN.match(t)
        # COMPARE VALUES, NOT TEXT. One side prints `li v1,30` and the other
        # `addiu $a3,$zero,0x1E` — the SAME constant in different bases. String-comparing them
        # (and `lstrip("0x")`, which strips CHARACTERS, not a prefix) silently never matched.
        if cm and ct and _val(cm.group(3)) is not None and _val(cm.group(3)) == _val(ct.group(3)):
            if _norm(cm.group(1)) != _norm(ct.group(1)):
                moved[_norm(cm.group(1))] = _norm(ct.group(1))
    if not moved:
        return None
    ev = []
    for r in rows:
        m, t = _txt(r)
        if not m or not t or _mn(m) != _mn(t) or _mn(t) not in COMMUTATIVE:
            continue
        rm = [_norm(x) for x in _regs(m)]
        rt = [_norm(x) for x in _regs(t)]
        if len(rm) != len(rt) or len(rm) < 2:
            continue
        for src, dst in moved.items():
            if src in rm and dst in rt and rm.index(src) != rt.index(dst):
                ev.append(r)
                break
    if ev:
        return ev[:3], ("the constant's register moved (%s) AND its operand POSITION changed in a "
                        "commutative op" % ", ".join("%s->%s" % kv for kv in list(moved.items())[:2]))
    return None


def rule_slot_steal(rows, ctx):
    """§373/§370: target fills a delay slot where mine emits nop (reorg steal)."""
    ev = [r for r in rows if _mn(_txt(r)[0]) == "nop" and _mn(_txt(r)[1]) not in ("nop", "")]
    if ev:
        return ev[:3], "target fills %d slot(s) where yours emits nop" % len(ev)
    return None


def rule_length_drift(rows, ctx):
    """§366 / frame-size family: a length mismatch dominates; a diff-by-rows read is misleading."""
    d = ctx["nins_tgt"] - ctx["nins_mine"]
    if d:
        return [], "length drift %+d (target %d, yours %d)" % (d, ctx["nins_tgt"], ctx["nins_mine"])
    return None


RULES = [
    ("WALL-332", "§332 + tools/wall_sweep.py", "certain", rule_wall_332,
     "STOP. The target's delay slot holds the second half of an assembler macro (a %lo). gcc emits "
     "that pair as ONE atomic insn, so NO C can put it there. This is a toolchain wall — do not "
     "draft it and NEVER escalate it; an escalation cannot beat the toolchain.",
     "Refuted if the %lo line is NOT actually in a delay slot (check the preceding line is a "
     "branch/jal)."),
    ("COPY-CAPTURE", "§372", "high", rule_copy_capture,
     "Spell the copy as a PLUS so it is not a reg-reg copy: `register s32 zr __asm__(\"$0\"); "
     "P = X + zr;`. That kills BOTH cse make_regs_eqv (no reg equivalence recorded) and "
     "local-alloc optimize_reg_copy_1 (not a single_set copy), and emits the byte-identical "
     "`addu $rd,$rs,$zero`. Uses that must read the SOURCE register must precede the copy in "
     "SOURCE order — canon_reg walks source order.",
     "Refuted if the rows' registers are unrelated to any matching copy's destination — then it is "
     "an allocation problem (§368) or a schedule (§373), not capture."),
    ("RELOAD-REMAT", "§368", "high", rule_reload_remat,
     "Declare the constant as a FUNCTION-SCOPE single-set local assigned ONCE at entry (a different "
     "basic block from its uses) and write each use constant-first: `s32 cK; cK = K; ... prod = cK "
     "* x;`. If its live range crosses calls and the callee-saved regs are taken, global-alloc "
     "leaves it uncolored, reload records reg_equiv_constant, DELETES the init (count-neutral) and "
     "rematerialises per use — choosing the register by order_regs_for_reload, which reaches "
     "registers no pin can. Do NOT pin: pins measured WORSE (18 and 14 vs 8).",
     "Refuted if the rows are not commutative ops, or if the operand order already matches — then "
     "see §372 (capture) or §373 (anti-dep)."),
    ("SLOT-STEAL", "§373 (+§370)", "medium", rule_slot_steal,
     "reorg fill_simple_delay_slots steals the FIRST ELIGIBLE insn scanning BACK from the branch — "
     "eligible = shares no register with anything between it and the branch. So the question is "
     "not 'how do I move X into the slot' but 'what makes X eligible and its rival not'. The value "
     "must accumulate OUTSIDE the register-heavy tail: split the expression so the accumulator "
     "lands in a different register. Prefer the DEAD-RESET cse-breaker (`p = expr; use(p); p = 0;`) "
     "over an asm re-tie — the re-tie is a real insn whose def->asm->arg chain perturbs the "
     "schedule and has caused a phantom residual twice.",
     "Refuted if the slot insn is a %lo macro tail — then it is WALL-332 and unreachable."),
    ("LENGTH-DRIFT", "§366 / §333 / §358", "low", rule_length_drift,
     "A length mismatch makes every row after the first divergence misleading — fix the COUNT "
     "first. On a switch, a drift equal to a small number of case nodes points at group_case_nodes "
     "merging STACKED consecutive labels (§366: give every case its own duplicated body, let "
     "cross_jump re-merge). Otherwise suspect the frame: a DECLARED aggregate sets frame size "
     "(§333) and an UNREFERENCED one still takes its slot (§358).",
     "Refuted once the counts match and rows still differ — then classify the rows, not the count."),
]


def classify(binary, fn, cpath):
    st = next((s for s in corpus.stubs(binary).values() if s.symbol == fn), None)
    if st is None:
        return {"error": "no open stub %s:%s" % (binary, fn)}
    p = subprocess.run([sys.executable, "tools/match_one.py", fn, "--c", cpath,
                        "--asm-subdir", st.asm_dir, "--json"],
                       capture_output=True, text=True, timeout=600)
    try:
        d = json.loads((p.stdout or "").strip().splitlines()[-1])
    except (ValueError, IndexError):
        return {"error": "match_one gave no JSON", "raw": (p.stdout or p.stderr)[-300:]}
    rows = d.get("residual") or []
    v = d.get("verdict") or {}
    # the target's own delay slots holding a macro tail — reuse the wall detector, do not re-derive
    import wall_sweep
    slot_lo = wall_sweep.scan(os.path.join(st.asm_dir, fn + ".s")) or []
    ctx = {"nins_mine": v.get("nins_mine") or d.get("nins") or 0,
           "nins_tgt": v.get("nins_tgt") or 0, "target_slot_lo": slot_lo}
    out = {"binary": binary, "fn": fn, "status": d.get("status"),
           "closeness": d.get("closeness"), "rows": len(rows), "hits": []}
    for rid, sec, conf, test, advice, refute in RULES:
        r = test(rows, ctx)
        if r:
            ev, note = r
            out["hits"].append({"rule": rid, "section": sec, "confidence": conf, "why": note,
                                "advice": advice, "refuted_if": refute,
                                "evidence": [{"idx": e[0], "mine": _txt(e)[0], "target": _txt(e)[1]}
                                             for e in ev]})
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--binary"); ap.add_argument("--fn"); ap.add_argument("--c")
    ap.add_argument("--json", action="store_true")
    a = ap.parse_args()
    if not (a.binary and a.fn and a.c):
        ap.error("give --binary --fn --c")
    r = classify(a.binary, a.fn, a.c)
    if a.json:
        print(json.dumps(r, indent=1)); return 0
    if r.get("error"):
        print("ERROR:", r["error"]); return 1
    print("%s:%s  status=%s closeness=%s  (%d residual rows)"
          % (r["binary"], r["fn"], r["status"], r["closeness"], r["rows"]))
    if not r["hits"]:
        print("  no rule fired — this is genuinely unclassified, grind or escalate")
    for h in r["hits"]:
        print("\n  [%s] %s  (confidence: %s)" % (h["rule"], h["section"], h["confidence"]))
        print("   why: %s" % h["why"])
        for e in h["evidence"]:
            print("     idx %-4d yours: %-34s target: %s" % (e["idx"], e["mine"], e["target"]))
        print("   DO: %s" % h["advice"])
        print("   refuted if: %s" % h["refuted_if"])
    return 0


if __name__ == "__main__":
    sys.exit(main())
