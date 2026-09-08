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
import os
import re
import struct
import subprocess

import cdecl   # the C-declaration oracle — the shared typedef-strip primitive (Phase-27 T4)

OBJDUMP = "mipsel-linux-gnu-objdump"

_HDR_RE = re.compile(r"^[0-9a-f]+ <([^>]+)>:")
_INS_RE = re.compile(r"\s+([0-9a-f]+):\s+([0-9a-f]{8})\s+(.*)")
_REL_RE = re.compile(r"R_MIPS_(\w+)\s+(\S+)")

# scalar/M2C typedef REDEFINITIONS common.h already provides (C89 rejects the dup). match_one and the
# permuter compile a draft in ISOLATION with `#include "common.h"` prepended, so the strip-set is
# exactly what common.h provides — derived from the header once (R33), never a hand-kept name list.
# DEPRECATED: SCALAR_TYPEDEF_RE (its `[^;]*` body cannot cross a `;`, so a multi-typedef LINE stripped
# NONE and the isolated compile then failed on the dup — 42 masked-MATCH drafts discarded over
# whitespace). Kept only as a fallback if the header probe can't run; strip_scalar_typedefs is correct.
SCALAR_TYPEDEF_RE = re.compile(
    r"^[ \t]*typedef\b[^;]*\b(u8|u16|u32|u64|s8|s16|s32|s64|f32|f64|"
    r"M2C_UNK|M2C_UNK8|M2C_UNK16|M2C_UNK32|M2C_UNK64)[ \t]*;[ \t]*\n",
    re.M,
)

_COMMON_TD = None


def _common_typedefs():
    """The typedef names common.h provides — derived from the header once, cached. This is the
    strip-set for an ISOLATED compile (match_one / the permuter prepend common.h). Falls back to the
    deprecated regex's name set if the cpp probe can't run (offline / no toolchain)."""
    global _COMMON_TD
    if _COMMON_TD is None:
        # PER-PROCESS probe path. It used to be the single shared "src/.masked_diff_probe.c", so N
        # concurrent match_one/permuter processes wrote, read and DELETED the same file: whoever
        # unlinked first made another's open() or parse fail, and that process died with a
        # traceback instead of a verdict. Measured cost: 14 of 1752 drafts lost in one 12-way
        # autopsy collect (0.8%) — and every parallel wave has been paying it invisibly, because a
        # drafter that crashes on its self-check just looks like a drafter that failed. Exactly the
        # shared-scratch defect Phase 28 found one level up in match_one's --work (whose docstring
        # promised isolation the default contradicted); same fix, same reason.
        probe = os.path.join(cdecl.REPO, "src", ".masked_diff_probe.%d.c" % os.getpid())
        try:
            with open(probe, "w") as f:
                f.write('#include "common.h"\n')
            _COMMON_TD = frozenset(cdecl.typedef_names(probe))
        except Exception:
            _COMMON_TD = frozenset("u8 u16 u32 u64 s8 s16 s32 s64 f32 f64 "
                                   "M2C_UNK M2C_UNK8 M2C_UNK16 M2C_UNK32 M2C_UNK64".split())
        finally:
            if os.path.exists(probe):
                os.remove(probe)
    return _COMMON_TD


def strip_scalar_typedefs(text):
    """Strip the scalar/M2C typedef redefinitions common.h provides, splitting multi-typedef lines
    correctly (the T4 primitive). Keeps the draft's OWN custom struct/fn-ptr typedefs — common.h
    doesn't provide those, and an isolated compile needs them. Replaces SCALAR_TYPEDEF_RE.sub('', …)."""
    return cdecl.strip_provided_typedefs(text, _common_typedefs())


def _reloc_kind(name):
    if "26" in name:
        return "26"
    if "HI16" in name:
        return "HI16"
    if "LO16" in name:
        return "LO16"
    if "PC16" in name:                # R_MIPS_PC16 — see mask_for() (Phase 26-A audit)
        return "PC16"
    return name


def mask_for(word, reloc_kind):
    """The compare mask for one instruction word given its reloc kind (or None).

    R_MIPS_PC16 (Phase 26-A audit). An over-approximating sweep of every reloc type `objdump -drz`
    emits across all 3,367 real build objects found EXACTLY FOUR: R_MIPS_26 (1,090,661), R_MIPS_HI16
    (633,662), R_MIPS_LO16 (633,437) — and R_MIPS_PC16 (211). The table handled three. PC16 fell
    through to a FULL-WORD compare, but the object holds an UNRESOLVED PLACEHOLDER in the branch
    displacement, so that compare can never succeed:

        build/src/libgs6.o  func_80053E28  MINE 1040ffff (beqz v0,388)  TGT 10400018 (beqz $v0, GS_123…)
                                                ^^^^ placeholder                ^^^^ real displacement

    THE DECISIVE TEST — derived from the proven invariant, not from reading the regex: INCLUDE_ASM
    pastes the ORIGINAL assembly, so for EVERY stub the build object's bytes ARE the target .s bytes,
    and diff_object_s() MUST return 0. Run over all 60,740 stubs it returned 0 for 60,585 — and LIED
    on 155.

    Why a lying closeness oracle is worse than a slow one: every crack agent trusts this number. A
    phantom non-zero sends an agent to grind at a wall that is not there, and the wasted attempt is
    then booked into the backlog as a MATCHING failure, which feeds reserved_walls() and PERMANENTLY
    BLACKLISTS a function that was never actually broken. A silent skip compounding into a false wall
    — the same mechanism that made nine byte-exact functions look like an intrinsic compiler wall.

    Masking PC16 exactly like HI16/LO16 (keep opcode+regs, drop the linker-filled displacement) cures
    151 of the 155 and introduces ZERO new lies across all 60,740 functions (auditor's counterfactual,
    independently re-run by a skeptic). The 4 survivors are a separate length-delta defect."""
    # AN INTERNAL `j` IS NOT A LINK-TIME VALUE (P31 S54, cookbook §195). This short-circuit used to
    # sit AHEAD of the reloc dispatch and fire on the OPCODE alone, so every `j .L…` to a local label
    # in the same function -- which the assembler resolves itself, emitting NO relocation -- was
    # dropped from the comparison. That is a semantic hole, not a cosmetic one: for a loop or switch
    # arm, which label the `j` targets is the whole difference between `break` (fall into the shared
    # tail, executing its calls) and `return` (skip them). Byte-proven on ov_SC03_118:func_801825EC,
    # where the banked `break;` and a `return;` variant that SKIPS a call differ in exactly one word
    # (0800003e vs 08000041) and both reported MATCH. The blindness reached match_one, the permuter's
    # scorer, family_cousins.tok and the atlas tiers at once -- nothing between a draft and the
    # whole-binary gate could see it. Now: mask the 26-bit field only when the assembler left it for
    # the LINKER (reloc_kind "26"); an unrelocated `j`/`jal` word is compared in full.
    # KEEP THE OPCODE EVEN WHEN THE TARGET IS LINK-TIME (P31 S65). Returning a 0 mask here meant
    # "compare NOTHING at this position" — and because both comparers pick the mask from ONE side
    # (diff_object_s from MINE, diff_object_object from the TARGET's), a masked `j`/`jal` on that
    # side swallowed WHATEVER the other side held. Byte-witnessed on synthetic pairs built from real
    # encodings: my `j 8017e248` (0805f892) vs a target `bne v0,v1` (14430002), vs a `nop`
    # (00000000), and my `jal` vs a target `bne` all scored 0 — while the mirror case (my `bne` vs a
    # target `j`) scored 1, because then the full-word mask came from my side. That asymmetry is how
    # a draft reported a false match at one index (reported by a t5s drafting agent on func_8017EB30,
    # then reproduced here). `_j_mismatch` cannot cover it: it fires only when BOTH sides carry an
    # internal-`j` target, which a `j`-vs-`bne` pair by definition does not.
    # The 26-bit field stays masked (it IS link-time); the 6-bit opcode never is.
    if reloc_kind == "26":            # jal / j to an EXTERNAL symbol — the target is link-time
        return 0xFC000000
    if reloc_kind in ("HI16", "LO16", "PC16"):
        return 0xFFFF0000             # keep opcode+regs, drop the linker-filled immediate/displacement
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
            insns.append({"off": int(mi.group(1), 16), "word": int(mi.group(2), 16),
                          "mnem": mi.group(3).strip(), "reloc_kind": None, "reloc_op": None,
                          "jrel": None})
        elif insns:
            rm = _REL_RE.search(line)
            if rm:
                insns[-1]["reloc_kind"] = _reloc_kind(rm.group(1))
                insns[-1]["reloc_op"] = rm.group(2)
    # fn given but nothing matched (unlabeled .text) -> fall back to the whole section
    if fn is not None and not insns:
        return insns_from_object(obj, None)
    _annotate_jrel(insns, insns[0]["off"] if insns else 0,
                   lambda i: i["reloc_kind"] == "26" and i["reloc_op"] == ".text")
    return insns


def insns_from_s(s_path):
    """splat .s -> [{word, mnem, reloc_kind:None, reloc_op:None}] from each `/* off vaddr LEHEX */ mnem`
    line, **counting only what is in .text**.

    THE SECTION FILTER IS LOAD-BEARING (P30 S47, byte-witnessed on func_801EDC18, a 57-member family).
    A splat `.s` may bundle a leading data symbol with the function — here a `.section .rodata` block
    re-emitting `D_801ED98C` as two `.word`s ahead of `.section .text`. Those `.word` lines carry the
    same `/* off vaddr HEX */` comment shape as instructions, so an unfiltered scan counted them as
    TARGET INSTRUCTIONS. The other side of the compare, `insns_from_object`, runs `objdump -j .text`
    and can never emit them — so a BYTE-PERFECT draft read as `mine=26, target=28, 26 mismatched`,
    every real position shifted by a constant +2, and `match_one` classified it `SIZE-MISMATCH
    [redraft]`. An agent correctly abandoned it at "closeness 6"; the whole-binary byte-gate then
    banked the very same body. A verdict that turns a two-line fix into a wall is worse than no
    verdict, and this is the same artifact the cookbook records at §129a for post-carve jump tables
    (there the jtbl inflates the count; here it is leading rodata) — one shape, one fix.

    Sections are tracked by directive: content counts only while the current section is .text (a file
    with no `.section` directive at all is assumed to be all-text, which is the common case)."""
    insns = []
    in_text = True                      # no .section directive anywhere => the whole file is text
    seen_section = False
    for line in open(s_path, errors="replace"):
        sec = re.match(r"\s*\.section\s+([.\w]+)", line)
        if sec:
            if not seen_section:
                seen_section = True
            in_text = sec.group(1).startswith(".text")
            continue
        if not in_text:
            continue
        mi = re.match(r"\s*/\*\s*[0-9A-Fa-f]+\s+([0-9A-Fa-f]+)\s+([0-9A-Fa-f]{8})\s*\*/\s+(.*)", line)
        if mi:
            insns.append({"off": int(mi.group(1), 16) & 0x0FFFFFFF,
                          "word": struct.unpack("<I", bytes.fromhex(mi.group(2)))[0],
                          "mnem": re.sub(r"\s+", " ", mi.group(3).strip()),
                          "reloc_kind": None, "reloc_op": None, "jrel": None})
    _annotate_jrel(insns, insns[0]["off"] if insns else 0, lambda i: True)
    return insns


def _annotate_jrel(insns, fn_start, is_internal):
    """THE INTERNAL-`j` TARGET (P31 T1, 2026-08-26; supersedes the §195 note below). The assembler
    DOES emit `R_MIPS_26 .text` for a `j .L…` inside the same section (objdump: `j 4604
    <fn+0x88>` + `R_MIPS_26 .text`), so the "26 => mask the target" rule made the comparer blind to
    WHICH label a `j` takes — two resolver drafts scored rtu MATCH with a wrong `goto` target and
    the whole-binary gate refused them on exactly one byte each (ov_SC02_027/func_801831F4,
    ov_SC06_000/func_80182E38). A `j`'s target is knowable on both sides RELATIVE TO THE FUNCTION
    START: object side = (field << 2) - fn section offset; .s side = (field << 2) - (fn vaddr &
    0x0FFFFFFF). `jrel` carries that; the comparers require it to agree. `jal` is left masked on
    purpose: a static callee's position legitimately differs under rtu's neutralized siblings."""
    for i in insns:
        if (i["word"] >> 26) == 2 and is_internal(i):
            i["jrel"] = ((i["word"] & 0x3FFFFFF) << 2) - fn_start


def _j_mismatch(a, b):
    """True when both sides carry an internal-`j` target and they disagree (see _annotate_jrel)."""
    ja, jb = a.get("jrel"), b.get("jrel")
    return ja is not None and jb is not None and ja != jb


def structured_diff(mine, tgt):
    """The per-instruction relocation-masked mismatch list: [(idx, mine_str, tgt_str), ...] over
    two insns_from_* streams. Each entry is a mismatching instruction position; mine_str/tgt_str are
    '<word_hex> <mnemonic>' (or '--' past the end of the shorter stream). len() == the masked mismatch
    count (the `closeness`). This is the STRUCTURED RESIDUAL telemetry the permuter-autopsy classifier
    reads (Phase-29 Task-12): idx localizes the residual, the word+mnem pair says what codegen differs
    (a reg-alloc swap, a scheduled-order flip, an extra/absent instruction). Shared by match_one +
    gate_stage's near-record so the same residual an agent reads is the one the autopsy mines."""
    n = max(len(mine), len(tgt))
    diffs = []
    for i in range(n):
        mw = mine[i]['word'] if i < len(mine) else None
        mask = mask_for(mine[i]['word'], mine[i]['reloc_kind']) if i < len(mine) else 0xFFFFFFFF
        me = (mw & mask) if mw is not None else None
        tg = (tgt[i]['word'] & mask) if i < len(tgt) else None
        if me != tg or (i < len(mine) and i < len(tgt) and _j_mismatch(mine[i], tgt[i])):
            diffs.append((i,
                          ('%08x %s' % (mine[i]['word'], mine[i]['mnem'])) if i < len(mine) else '--',
                          ('%08x %s' % (tgt[i]['word'], tgt[i]['mnem'])) if i < len(tgt) else '--'))
    return diffs


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
        if (c["word"] & m) != (t["word"] & m) or _j_mismatch(c, t):
            diffs += 1
            continue
        if m == 0xFC000000 or m == 0xFFFF0000:   # a masked reloc/jal slot -> symbol+addend must match too
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
        if (c["word"] & m) != (t["word"] & m) or _j_mismatch(c, t):
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
