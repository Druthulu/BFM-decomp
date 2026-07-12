#!/usr/bin/env python3
"""Phase-25 family template-instantiation: mechanically remap a MATCHED exemplar's C to a byte-variant
h_norm SIBLING by positionally pairing their per-overlay symbol references.

The Phase-24 reframe found the unmatched frontier clusters into h_norm STRUCTURAL families (same code
shape across overlays, byte-shattered because each member references PER-OVERLAY symbols). T3 proved these
are NOT free `--tier h_norm` dedup (one C body can't name 134 overlays' different symbols). But two
h_norm-identical members have IDENTICAL instruction streams except in the masked reloc fields (jal target,
lui/lo address) — so: disassemble both overlay images at ADDR, pair the resolved reloc targets in
instruction order, and substitute the exemplar C's per-overlay symbol NAMES (`D_<addr>`/`func_<addr>`)
with the sibling's. Shared EXE/resident symbols map to themselves. The result is the sibling's C —
generated mechanically from ONE crack, for ~0 agent tokens. The whole-binary byte-gate stays the sole
arbiter (G3/P9): a wrong remap is rejected.

Phase-26 extends this to the looser h_seq family key (mnemonic skeleton, immediates may differ):
  * reloc_targets propagates a pending lui-hi through add/addu index arithmetic (the gcc-2.7.2
    indexed-global `lui;addu $idx;lw %lo($at)` idiom the pre-26 tracker dropped — the "reach-1 tail"
    was largely this blind spot, not unique code);
  * remap does a SINGLE-PASS simultaneous substitution (the old sequential re.sub corrupted chained /
    permuted maps) and merges an optional imm_map (T2a per-member immediate edits);
  * to_addr enables cross-address siblings (same engine fn at a different vram per overlay, T2b).

  tools/family_remap.py --addr 0xADDR --from ov_SC01_077 --to ov_SC01_000 [--to-addr 0xADDR2] [--out draft.c]
"""
import struct, json, glob, re, sys, argparse, collections

VRAM = 0x80128158
# lo-type ops whose rs is a hi-base (loads/stores incl. unaligned, addiu, ori)
LO_OPS = {0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x28, 0x29, 0x2A, 0x2B, 0x2E, 0x09, 0x0D}


def img_path(ov):
    _, sc, fn = ov.split("_")
    p = f"extracted/retail/{sc}.CD.dir/FILE_{fn}.dir/0.4.dec"
    return p if glob.glob(p) else None


def nins_of(ov, addr):
    for line in open(f".run/sig.{ov}.jsonl"):
        d = json.loads(line)
        if int(d["addr"], 16) == addr:
            return d["nins"]
    return None


def reloc_targets(ov, addr):
    """ordered [(kind, resolved_addr)] for jal targets + lui/lo address loads, in instruction order.
    Verified against splat .s ground truth (22/22 on func_80141100; 15/15 on func_801407F4 whose
    indexed-global D[i] accesses the pre-Phase-26 tracker missed — see the add/addu hi-propagation)."""
    data = open(img_path(ov), "rb").read()
    n = nins_of(ov, addr)
    off = addr - VRAM
    out, pend = [], {}
    for k in range(n):
        pc = addr + k * 4
        w = struct.unpack_from("<I", data, off + k * 4)[0]
        op = w >> 26
        if op in (2, 3):                                   # j / jal
            out.append(("call", ((pc + 4) & 0xF0000000) | ((w & 0x03FFFFFF) << 2)))
        elif op == 0x0F:                                   # lui -> rt holds the hi
            pend[(w >> 16) & 0x1F] = (w & 0xFFFF) << 16
        elif op in LO_OPS:
            rs = (w >> 21) & 0x1F
            if rs in pend:
                lo = w & 0xFFFF
                if lo >= 0x8000:
                    lo -= 0x10000
                out.append(("data", pend[rs] + lo))
                del pend[rs]
            pend.pop((w >> 16) & 0x1F, None)               # rt overwritten
        elif op == 0:                                      # R-type
            funct = w & 0x3F
            rd = (w >> 11) & 0x1F
            if funct in (0x20, 0x21):                       # add / addu: the indexed-global idiom
                # gcc-2.7.2 emits `lui $at,%hi(D); addu $at,$at,$idx; lw ..%lo(D)($at)` for D[i] —
                # the addu PRESERVES the hi anchor (index shifts the runtime value, not the symbol).
                # Propagate the pending hi through the add so the following %lo still resolves D.
                rs = (w >> 21) & 0x1F
                rt = (w >> 16) & 0x1F
                if rs in pend:
                    pend[rd] = pend[rs]
                elif rt in pend:
                    pend[rd] = pend[rt]
                else:
                    pend.pop(rd, None)
            else:
                pend.pop(rd, None)                          # rd overwritten with a non-address value
    return out


# ---- Phase-26 shared word-diff classifier (family_hseq survey T1, imm engine T2a, sweep pre-filter T3) ----
# Two members of an h_seq family have IDENTICAL mnemonic sequences but may differ in reloc fields
# (symbol-remappable), in true immediates / shift amounts (imm-substitutable, T2a), OR in REGISTER
# allocation (NOT templatable — h_seq ignores registers). Classify each differing instruction so a
# family/member is bucketed PURE (reloc-only) / IMM / STRUCT-EXCLUDED (regalloc drift or collision).

_IMG_CACHE = {}


def _img(ov):
    if ov not in _IMG_CACHE:
        p = img_path(ov)
        _IMG_CACHE[ov] = open(p, "rb").read() if p else None
    return _IMG_CACHE[ov]


def stream_words(ov, addr, nins):
    """the nins raw instruction words of a function from its overlay image (cached)."""
    data = _img(ov)
    if data is None:
        return None
    off = addr - VRAM
    return [struct.unpack_from("<I", data, off + k * 4)[0] for k in range(nins)]


def reloc_indices(words):
    """set of instruction indices that participate in an ADDRESS reloc — jal, an addr-anchor lui
    (confirmed by a %lo consumer, propagated through add/addu), and the %lo consumer itself."""
    pend, jal, lui_addr, lo = {}, set(), set(), set()      # pend: reg -> originating lui index
    for k, w in enumerate(words):
        op = w >> 26
        if op in (2, 3):
            jal.add(k)
        elif op == 0x0F:
            pend[(w >> 16) & 0x1F] = k
        elif op in LO_OPS:
            rs = (w >> 21) & 0x1F
            if rs in pend:
                lo.add(k)
                lui_addr.add(pend[rs])
                del pend[rs]
            pend.pop((w >> 16) & 0x1F, None)
        elif op == 0:
            funct = w & 0x3F
            rd = (w >> 11) & 0x1F
            if funct in (0x20, 0x21):
                rs, rt = (w >> 21) & 0x1F, (w >> 16) & 0x1F
                if rs in pend:
                    pend[rd] = pend[rs]
                elif rt in pend:
                    pend[rd] = pend[rt]
                else:
                    pend.pop(rd, None)
            else:
                pend.pop(rd, None)
    return jal | lui_addr | lo


def reg_fields(w):
    """the register + opcode-identity fields (everything EXCEPT the imm / jump-target / shift-amount).
    Equal reg_fields with unequal words ⟹ the diff is purely immediate/target/sa (not regalloc)."""
    op = w >> 26
    if op == 0:                                            # R-type: rs, rt, rd, funct (sa excluded)
        return (0, (w >> 21) & 0x1F, (w >> 16) & 0x1F, (w >> 11) & 0x1F, w & 0x3F)
    if op in (2, 3):                                       # j / jal: target excluded
        return (op,)
    if op == 0x0F:                                         # lui: rt only (hi excluded)
        return (op, (w >> 16) & 0x1F)
    return (op, (w >> 21) & 0x1F, (w >> 16) & 0x1F)        # I-type: rs, rt (imm excluded)


_SHIFT_FUNCTS = (0x00, 0x02, 0x03)                          # sll srl sra (sa is the immediate); sllv/srlv/srav excluded


def classify_member(words_ex, words_sib):
    """returns (cls, positions): cls in {PURE, IMM, STRUCT, LEN}; positions = [(idx, kind)] for each
    DIFFERING instruction, kind in {RELOC, IMM, IMM_SA, STRUCT}. Reuses the extended reloc tracker."""
    if words_ex is None or words_sib is None:
        return "LEN", []
    if len(words_ex) != len(words_sib):
        return "LEN", []
    rel = reloc_indices(words_ex)
    positions = []
    for k, (a, b) in enumerate(zip(words_ex, words_sib)):
        if a == b:
            continue
        if reg_fields(a) != reg_fields(b):                 # opcode/register/funct drift -> not templatable
            positions.append((k, "STRUCT"))
        elif k in rel:
            positions.append((k, "RELOC"))
        elif (a >> 26) == 0:
            positions.append((k, "IMM_SA" if (a & 0x3F) in _SHIFT_FUNCTS else "STRUCT"))
        else:
            positions.append((k, "IMM"))                   # I-type non-address immediate (incl. const-lui hi)
    if any(c == "STRUCT" for _, c in positions):
        cls = "STRUCT"
    elif any(c in ("IMM", "IMM_SA") for _, c in positions):
        cls = "IMM"
    else:
        cls = "PURE"
    return cls, positions


# ---- Phase-26 T2a: the diff-driven immediate engine (Tier 1) ----
# h_seq IMM families differ in a handful of true immediates (per-location constants). Extract only the
# DIFFERING imm/sa positions, and where a value is unambiguous (maps 1:1 and doesn't recur at a
# non-differing position) swap its C literal. Ambiguous/folded values are left UNRESOLVED (Tier 2 probe
# / agent queue). The whole-binary byte-gate arbitrates — a wrong swap simply fails.

_SIGNED_IMM = frozenset((0x08, 0x09, 0x0A, 0x0B, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26,
                         0x28, 0x29, 0x2A, 0x2B, 0x2E))          # addi/addiu/slti/sltiu + loads/stores
_UNSIGNED_IMM = frozenset((0x0C, 0x0D, 0x0E))                     # andi/ori/xori


def imm_value(w, is_reloc):
    """the human immediate value at an instruction (signed where the field is), or None if this
    position carries no plain substitutable immediate (reloc lo/hi, register op, lui const-hi)."""
    if is_reloc:
        return None
    op = w >> 26
    if op == 0:
        return (w >> 6) & 0x1F if (w & 0x3F) in _SHIFT_FUNCTS else None
    if op in _SIGNED_IMM:
        v = w & 0xFFFF
        return v - 0x10000 if v >= 0x8000 else v
    if op in _UNSIGNED_IMM:
        return w & 0xFFFF
    return None                                                  # lui const-hi etc. -> Tier 2


def _c_literal_swap(unit, exv, sibv):
    """find a C integer-literal occurrence of exv and return (found_token, replacement_same_style),
    or (None, None). Tries hex (both cases) then decimal; preserves sign + hex-case style."""
    forms = ([f"0x{exv:x}", f"0x{exv:X}", str(exv)] if exv >= 0
             else [f"-0x{-exv:x}", f"-0x{-exv:X}", str(exv)])
    for t in forms:
        if re.search(r'(?<!\w)' + re.escape(t) + r'\b', unit):
            if "x" in t.lower():
                digits = t.lstrip("-")[2:]
                up = any(c.isalpha() and c.isupper() for c in digits)
                rep = ("-" if sibv < 0 else "") + "0x" + (f"{abs(sibv):X}" if up else f"{abs(sibv):x}")
            else:
                rep = str(sibv)
            return t, rep
    return None, None


def imm_map_tier1(unit, ex_words, sib_words):
    """Tier 1: {c_literal_token: replacement} for the unambiguous immediate diffs; plus the list of
    UNRESOLVED (value, reason) that need the Tier-2 probe. Returns (imm_map, unresolved)."""
    rel = reloc_indices(ex_words)
    valpos = [imm_value(w, k in rel) for k, w in enumerate(ex_words)]
    diff_idx = {k for k in range(len(ex_words)) if ex_words[k] != sib_words[k]}
    by_val = collections.defaultdict(set)                        # ex human-value -> {sib values}
    handled = set()
    unresolved = []
    for k in sorted(diff_idx):
        if k in rel:                                             # reloc -> symbol_map's job
            continue
        ev = valpos[k]
        if ev is None:                                           # differing lui-hi / other -> Tier 2
            unresolved.append((f"@{k}", f"non-imm diff op={ex_words[k] >> 26:#x}"))
            continue
        by_val[ev].add(imm_value(sib_words[k], False))
        handled.add(k)
    imm_map = {}
    for exv, sibvs in by_val.items():
        if len(sibvs) != 1 or None in sibvs:
            unresolved.append((exv, "multi-target")); continue
        sibv = next(iter(sibvs))
        if any(valpos[k] == exv for k in range(len(ex_words)) if k not in diff_idx and valpos[k] is not None):
            unresolved.append((exv, "asm-ambiguous")); continue  # value also used at a fixed position
        tok, rep = _c_literal_swap(unit, exv, sibv)
        if tok is None:
            unresolved.append((exv, "not-in-C")); continue
        imm_map[tok] = rep
    return imm_map, unresolved


_TU_CACHE = {}


def _tu_text(ov):
    if ov not in _TU_CACHE:
        _TU_CACHE[ov] = "".join(open(f).read() for f in sorted(glob.glob(f"src/{ov}/{ov}*.c")))
    return _TU_CACHE[ov]


def gather_externs(from_ov, from_addr, unit):
    """file-scope `extern` decls from the exemplar TU for every func_/D_ symbol the body references but
    the extracted unit does NOT already declare. extract_unit only grabs the immediately-preceding
    externs; a per-location body that indexes a global (`(*D_x[..])()`) references symbols declared once
    at file scope elsewhere — templated into a sibling TU that never declared them, they're `undeclared`
    at the gate. Carrying them (they get remapped downstream) fixes the decl class. Excludes the self
    name. Duplicate-identical externs are legal C; a type-conflict is the §41 reconcile class (rare)."""
    self_sym = f"func_{from_addr:08X}"
    refs = set(re.findall(r'\b(?:func_[0-9A-Fa-f]{8}|D_[0-9A-Fa-f]{8})\b', unit)) - {self_sym}
    tu = _tu_text(from_ov)
    lines, seen = [], set()
    for sym in sorted(refs):
        if re.search(rf'^\s*extern\b[^\n;{{}}]*\b{sym}\b[^\n;{{}}]*;', unit, re.M):
            continue                                         # already declared inside the unit
        m = re.search(rf'^\s*(extern\b[^\n;{{}}]*\b{sym}\b[^\n;{{}}]*;)', tu, re.M)
        if m and sym not in seen:
            lines.append(m.group(1).strip()); seen.add(sym)
    return lines


def remap_hseq(from_addr, from_ov, to_ov, to_addr=None):
    """h_seq family template: reloc symbol remap (§40b) + immediate substitution (T2a Tier 1) +
    cross-address self-rename (T2b) + carried file-scope externs. Returns (draft, info) or
    (None, error_str). info = {symbol_map, imm_map, unresolved, n_externs, cf}. A member with register
    drift (STRUCT) or unresolved immediates is refused (the caller skips it — byte-gate would reject)."""
    if to_addr is None:
        to_addr = from_addr
    nins = nins_of(from_ov, from_addr)
    ex_words = stream_words(from_ov, from_addr, nins)
    sib_words = stream_words(to_ov, to_addr, nins)
    cls, _ = classify_member(ex_words, sib_words)
    if cls in ("STRUCT", "LEN"):
        return None, f"member class {cls} (not templatable)"
    unit, cf = extract_unit(from_ov, from_addr)
    if not unit:
        return None, f"no matched unit for func_{from_addr:08x} in {from_ov}"
    m, err = symbol_map(from_addr, from_ov, to_ov, to_addr)
    if err:
        return None, err
    imm_map, unresolved = ({}, [])
    if cls == "IMM":
        imm_map, unresolved = imm_map_tier1(unit, ex_words, sib_words)
        if unresolved:
            return None, f"unresolved immediates (Tier-2): {unresolved}"
    externs = gather_externs(from_ov, from_addr, unit)
    if externs:
        unit = "\n".join(externs) + "\n" + unit
    table = dict(m)
    if from_addr != to_addr:
        table[f"func_{from_addr:08X}"] = f"func_{to_addr:08X}"
    table.update(imm_map)
    return apply_remap(unit, table), {"symbol_map": m, "imm_map": imm_map, "unresolved": unresolved,
                                      "n_externs": len(externs), "cf": cf}


def symbol_map(addr, from_ov, to_ov, to_addr=None):
    """{exemplar_name: sibling_name} for the per-overlay symbols (positional zip). None,err if not clean.
    to_addr defaults to addr (same-address h_norm sibling); pass it for a cross-address (T2b) sibling."""
    if to_addr is None:
        to_addr = addr
    ex, tg = reloc_targets(from_ov, addr), reloc_targets(to_ov, to_addr)
    if len(ex) != len(tg):
        return None, f"reloc-count mismatch {len(ex)}!={len(tg)} (not an h_norm-clean pair)"
    m = {}
    for (ke, ae), (kt, at) in zip(ex, tg):
        if ke != kt:
            return None, "reloc-kind mismatch (not h_norm-clean)"
        if ae != at:
            pfx = "func_" if ke == "call" else "D_"
            m[f"{pfx}{ae:08X}"] = f"{pfx}{at:08X}"
    return m, None


def extract_unit(ov, addr):
    """the matched inline def + its contiguous preceding extern/blank/comment lines, from the overlay src.
    func_<addr> names are UPPERCASE-hex in src (func_8013DBE4); match case-insensitively to be safe."""
    pat = re.compile(rf'^\s*[A-Za-z_][\w \*]*\bfunc_{addr:08X}\s*\(', re.I)
    for cf in sorted(glob.glob(f"src/{ov}/{ov}*.c")):
        lines = open(cf).read().split("\n")
        for i, ln in enumerate(lines):
            if pat.search(ln) and "INCLUDE_ASM" not in ln and not ln.rstrip().endswith(";"):
                j = i - 1
                while j >= 0 and (lines[j].strip() == "" or
                                  lines[j].lstrip().startswith(("extern", "//", "/*", "*"))):
                    j -= 1
                start = j + 1
                depth, started, end = 0, False, i
                for k in range(i, len(lines)):
                    depth += lines[k].count("{") - lines[k].count("}")
                    if "{" in lines[k]:
                        started = True
                    if started and depth <= 0:
                        end = k
                        break
                return "\n".join(lines[start:end + 1]), cf
    return None, None


def apply_remap(unit, table):
    """single-pass simultaneous substitution of {source_token: replacement} over unit — each source
    token is matched once against the ORIGINAL text, so chained/permuted maps (D_A->D_B, D_B->D_C, or
    an immediate value permutation 0x10->0xA & 0x4->0x10) are correct where the old sequential re.sub
    corrupted them. Tokens are word-bounded (`\\b`); longest-first avoids any prefix ambiguity."""
    if not table:
        return unit
    keys = sorted(table, key=len, reverse=True)
    rx = re.compile(r'\b(?:' + '|'.join(re.escape(k) for k in keys) + r')\b')
    return rx.sub(lambda mm: table[mm.group(0)], unit)


def remap(addr, from_ov, to_ov, to_addr=None, imm_map=None):
    """returns (draft_text, symbol_map) or (None, error_str).
    Same-overlay-address remap by default; pass to_addr for a cross-address (T2b) sibling — the self
    name func_<ADDR> is then remapped to func_<TO_ADDR> too. imm_map (T2a) merges per-member immediate
    /literal token substitutions into the SAME single pass. The returned map is the per-overlay symbol
    map only (self-rename + imm edits excluded), preserving the pre-Phase-26 contract."""
    if to_addr is None:
        to_addr = addr
    m, err = symbol_map(addr, from_ov, to_ov, to_addr)
    if err:
        return None, err
    unit, cf = extract_unit(from_ov, addr)
    if not unit:
        return None, f"no matched unit for func_{addr:08x} in {from_ov}"
    table = dict(m)
    if addr != to_addr:                                    # self-rename: definition + any recursion
        table[f"func_{addr:08X}"] = f"func_{to_addr:08X}"
    if imm_map:
        table.update(imm_map)
    unit = apply_remap(unit, table)
    return unit, m


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--addr", required=True)
    ap.add_argument("--from", dest="frm", required=True)
    ap.add_argument("--to", required=True)
    ap.add_argument("--to-addr", dest="to_addr", default=None,
                    help="sibling address if different from --addr (cross-address T2b family)")
    ap.add_argument("--out", default=None)
    a = ap.parse_args()
    addr = int(a.addr, 16)
    to_addr = int(a.to_addr, 16) if a.to_addr else None
    draft, m = remap(addr, a.frm, a.to, to_addr)
    if draft is None:
        print(f"REMAP FAIL (func_{addr:08x} {a.frm}->{a.to}): {m}")
        sys.exit(1)
    out = a.out or f".run/remap_{a.to}_{(to_addr or addr):08x}.c"
    open(out, "w").write(draft + "\n")
    print(f"remapped {len(m)} per-overlay symbol(s) {a.frm}->{a.to}: {m}")
    print(f"-> {out}")


if __name__ == "__main__":
    main()
