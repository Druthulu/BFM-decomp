#!/usr/bin/env python3
"""masked_diff.py — the shared relocation-masked instruction oracle (BFM Phase 24 T2).

The single source of truth for "how close are two MIPS objects, ignoring link-time relocations."
Factored out of tools/match_one.py so match_one AND the permuter's MaskedScorer (tools/masked_scorer.py)
use ONE masking rule — and upgraded to `objdump -drz` so runs of nops are NOT collapsed (the `-dr`
nop-elision that under-counted GTE-heavy seeds, e.g. func_80132784 read as 384 ins instead of 400).

The mask (identical to the psyq_identify / match_one rule):
  * jal / j (opcode>>26 in {2,3}) or any R_MIPS_*_26 reloc  -> ignore the whole 26-bit target field
  * R_MIPS_HI16 / R_MIPS_LO16                               -> ignore the 16-bit immediate (linker fills it)
  * everything else                                         -> compare the full 32-bit word

Two compare modes:
  * OBJECT vs OBJECT (the permuter: both target.o and cand.o carry relocs) — mask driven by the target's
    relocs, AND require reloc-operand (symbol+addend) equality at masked positions. This is STRICTER than
    match_one: a jal to the wrong symbol scores a mismatch (match_one, comparing against a resolved .s,
    can't see the symbol). A masked count of 0 here ⟺ the two functions link to identical bytes.
  * OBJECT vs splat .s (match_one: the target .s is RESOLVED, no relocs) — mask driven by MY object's
    relocs, applied to both words; symbol-agnostic (the .s word is already the final linked value).

Neither mode is the byte-gate: the whole-binary rebuild (tools/harvest_verify.py) is the sole arbiter
(G3/P9). These masked metrics only rank candidates / measure closeness.
"""
import re
import struct
import subprocess

OBJDUMP = "mipsel-linux-gnu-objdump"

_HDR_RE = re.compile(r"^[0-9a-f]+ <([^>]+)>:")
_INS_RE = re.compile(r"\s+[0-9a-f]+:\s+([0-9a-f]{8})\s+(.*)")
_REL_RE = re.compile(r"R_MIPS_(\w+)\s+(\S+)")
# scalar/M2C typedef REDEFINITIONS common.h already provides (C89 rejects the dup); shared so match_one
# and the permuter setup strip exactly the same set and never the draft's own custom struct typedefs.
SCALAR_TYPEDEF_RE = re.compile(
    r"^[ \t]*typedef\b[^;]*\b(u8|u16|u32|u64|s8|s16|s32|s64|f32|f64|"
    r"M2C_UNK|M2C_UNK8|M2C_UNK16|M2C_UNK32|M2C_UNK64)[ \t]*;[ \t]*\n",
    re.M,
)


def _reloc_kind(name):
    if "26" in name:
        return "26"
    if "HI16" in name:
        return "HI16"
    if "LO16" in name:
        return "LO16"
    return name


def mask_for(word, reloc_kind):
    """The compare mask for one instruction word given its reloc kind (or None)."""
    if (word >> 26) in (2, 3):        # jal / j — the 26-bit target is a link-time value
        return 0
    if reloc_kind == "26":
        return 0
    if reloc_kind in ("HI16", "LO16"):
        return 0xFFFF0000             # keep opcode+regs, drop the linker-filled immediate
    return 0xFFFFFFFF


def insns_from_object(obj, fn=None):
    """objdump -drz an object's .text -> [{word, mnem, reloc_kind, reloc_op}]. -z keeps nop runs
    (no collapse). fn: restrict to that <function> label; None = all .text (a one-function object)."""
    out = subprocess.run([OBJDUMP, "-drz", "-j", ".text", obj],
                         capture_output=True, text=True).stdout
    insns = []
    infn = fn is None
    for line in out.splitlines():
        h = _HDR_RE.match(line)
        if h:
            infn = (fn is None) or (h.group(1) == fn)
            continue
        if not infn:
            continue
        mi = _INS_RE.match(line)
        if mi:
            insns.append({"word": int(mi.group(1), 16), "mnem": mi.group(2).strip(),
                          "reloc_kind": None, "reloc_op": None})
        elif insns:
            rm = _REL_RE.search(line)
            if rm:
                insns[-1]["reloc_kind"] = _reloc_kind(rm.group(1))
                insns[-1]["reloc_op"] = rm.group(2)
    # fn given but nothing matched (unlabeled .text) -> fall back to the whole section
    if fn is not None and not insns:
        return insns_from_object(obj, None)
    return insns


def insns_from_s(s_path):
    """splat .s -> [{word, mnem, reloc_kind:None, reloc_op:None}] from each `/* off vaddr LEHEX */ mnem`
    line. The target is RESOLVED (no relocs); the mask is driven by MY object's relocs at compare time."""
    insns = []
    for line in open(s_path, errors="replace"):
        mi = re.match(r"\s*/\*\s*[0-9A-Fa-f]+\s+[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})\s*\*/\s+(.*)", line)
        if mi:
            insns.append({"word": struct.unpack("<I", bytes.fromhex(mi.group(1)))[0],
                          "mnem": re.sub(r"\s+", " ", mi.group(2).strip()),
                          "reloc_kind": None, "reloc_op": None})
    return insns


def diff_object_object(cand, tgt):
    """masked mismatch count between two objdump'd objects (permuter scorer). Mask driven by the
    TARGET's relocs; at masked reloc/jal positions also require reloc-operand (symbol+addend) equality.
    Length delta counts as mismatches (a wrong-instruction-count draft scores high). 0 ⟺ same linked bytes."""
    n = max(len(cand), len(tgt))
    diffs = 0
    for i in range(n):
        if i >= len(cand) or i >= len(tgt):
            diffs += 1
            continue
        c, t = cand[i], tgt[i]
        m = mask_for(t["word"], t["reloc_kind"])
        if (c["word"] & m) != (t["word"] & m):
            diffs += 1
            continue
        if m == 0 or m == 0xFFFF0000:   # a masked reloc/jal slot -> the symbol+addend must also match
            if (c["reloc_op"] or "") != (t["reloc_op"] or ""):
                diffs += 1
    return diffs


def diff_object_s(myobj, tgt_s):
    """match_one semantics: mask driven by MY object's relocs, applied to both words; symbol-agnostic
    (the .s target is already resolved). Returns the masked mismatch count."""
    n = max(len(myobj), len(tgt_s))
    diffs = 0
    for i in range(n):
        if i >= len(myobj) or i >= len(tgt_s):
            diffs += 1
            continue
        c, t = myobj[i], tgt_s[i]
        m = mask_for(c["word"], c["reloc_kind"])
        if (c["word"] & m) != (t["word"] & m):
            diffs += 1
    return diffs


if __name__ == "__main__":   # spot-check: masked_diff.py <a.o> <b.o|.s> [fn]
    import sys
    a = sys.argv[1]
    b = sys.argv[2]
    fn = sys.argv[3] if len(sys.argv) > 3 else None
    ai = insns_from_object(a, fn)
    if b.endswith(".s"):
        print(f"object-vs-.s: {diff_object_s(ai, insns_from_s(b))} mismatched "
              f"(mine={len(ai)} ins, target={len(insns_from_s(b))})")
    else:
        bi = insns_from_object(b, fn)
        print(f"object-vs-object: {diff_object_object(ai, bi)} mismatched "
              f"(a={len(ai)} ins, b={len(bi)})")
