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
import struct, json, glob, re, sys, argparse, collections, functools, os

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import cdecl                                                    # noqa: E402

VRAM = 0x80128158
# lo-type ops whose rs is a hi-base (loads/stores incl. unaligned, addiu, ori)
LO_OPS = {0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x28, 0x29, 0x2A, 0x2B, 0x2E, 0x09, 0x0D}


_PATH_CACHE = {}


def img_path(ov):
    """The binary's extracted payload, DERIVED from its splat config's `target_path` (R33).

    NEVER reconstruct this path from the alias. The first 134 overlays put their code at PAC entry 0
    (`0.4.dec`), but the four SC07 overlays the Phase-27 disc-completeness audit found put graphics at
    entry 0 and CODE at entry 1 (`1.4.dec`). The old hardcoded `…/FILE_{fn}.dir/0.4.dec` guess returned
    None for them, and None was SILENT: `_img` -> None -> `stream_words` -> None -> `classify_member`
    -> ("LEN", []) — i.e. every SC07 member was dropped as "not templatable" and, worse, poisoned its
    family's `diff_class` to MIXED (`family_hseq.py:141-143` counts LEN against n_templatable). A
    scanner that mis-reports a whole overlay as structurally-different, silently, is exactly the
    silent-skip defect class (R32) — and it is the SAME bug `new_overlay.sh` had (its hardcoded
    `0.4.dec` glob hid these four overlays for a month), left uncorrected in a second tool.

    `config/splat.<bin>.yaml` is what the BUILD reads, so it cannot drift from the bytes. This also
    makes the resident work for free (its target_path is `MAIN.CD.dir/FILE_010.dir/1.1`).

    Raises rather than returning None: a missing payload is a DEFECT, not a state (R32). Every caller
    either opened it unguarded already (`reloc_targets`, `jr_isolate_all`) or silently mis-classified.
    """
    if ov not in _PATH_CACHE:
        cfg = f"config/splat.{ov}.yaml"
        if not glob.glob(cfg):
            raise FileNotFoundError(f"img_path({ov}): no {cfg} — is this binary onboarded?")
        m = re.search(r"^\s*target_path:\s*(\S+)\s*$", open(cfg).read(), re.M)
        if not m:
            raise ValueError(f"img_path({ov}): {cfg} has no `target_path:` — cannot derive the payload")
        p = m.group(1)
        if not glob.glob(p):
            raise FileNotFoundError(f"img_path({ov}): {cfg} names {p}, which does not exist — run `make extract BINARY={ov}`")
        _PATH_CACHE[ov] = p
    return _PATH_CACHE[ov]


def nins_of(ov, addr):
    for line in open(f".run/sig.{ov}.jsonl"):
        d = json.loads(line)
        if int(d["addr"], 16) == addr:
            return d["nins"]
    return None


@functools.lru_cache(maxsize=None)
def fn_addrs(ov):
    """The FUNCTION start addresses in <ov> — the same sig set `nins_of` treats as the boundary
    oracle (R33: one oracle, cached because symbol_map asks per reloc slot per member)."""
    return frozenset(int(json.loads(l)["addr"], 16) for l in open(f".run/sig.{ov}.jsonl"))


def reloc_targets(ov, addr, data=None):
    """ordered [(kind, resolved_addr)] for jal targets + lui/lo address loads, in instruction order.
    Verified against splat .s ground truth (22/22 on func_80141100; 15/15 on func_801407F4 whose
    indexed-global D[i] accesses the pre-Phase-26 tracker missed — see the add/addu hi-propagation).

    `data` (optional) = the overlay image bytes, read once by the caller and passed to AVOID the
    per-call `open(...).read()` when scanning many functions of one overlay (jr_inventory reads it
    once, then calls this ~2,300× — 6s -> 0.1s). Omit it and the image is re-read fresh per call
    (the default, so a re-extraction mid-process is always seen)."""
    if data is None:
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
    # img_path raises on a missing payload (R32), so this can no longer hand `None` downstream and
    # manufacture a phantom LEN. `classify_member`'s None-guard now catches only a genuine
    # `nins_of` miss (the address is not in that overlay's sig), which is a real state.
    if ov not in _IMG_CACHE:
        _IMG_CACHE[ov] = open(img_path(ov), "rb").read()
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
    name. Duplicate-identical externs are legal C; a type-conflict is the §41 reconcile class (rare).

    COMMENT-MASKED (Phase 29 T53). Every scan below runs over `cdecl._mask`ed text — comments and
    string literals blanked, length-preserving, so offsets still index the original. Two same-class
    defects this closes, both the §96 disease (matching by raw TEXT):
      * a symbol named only in the body's PROSE counted as a reference. `func_80135260`'s header
        comment mentions its sibling `func_80135D20` twice, so the scan demanded a decl for it and
        printed "the sibling will not compile" on all 137 members — a 100%-false-alarm warning that
        masked real causes for two tasks. T52 settled it empirically: all 132 banked anyway.
      * a COMMENTED-OUT `extern` in the exemplar TU could be selected as the carried declaration and
        spliced into the sibling as live code. Not yet observed; closed by construction.
    The emitted text is sliced from the ORIGINAL by span — a masked decl is all blanks."""
    self_sym = f"func_{from_addr:08X}"
    unit_mask = cdecl._mask(unit)
    refs = set(re.findall(r'\b(?:func_[0-9A-Fa-f]{8}|D_[0-9A-Fa-f]{8})\b', unit_mask)) - {self_sym}
    tu = _tu_text(from_ov)
    tu_mask = cdecl._mask(tu)
    lines, seen, unresolved = [], set(), []

    # STATEMENT-oriented, not line-oriented (Phase 26-A audit).
    #
    # The scan used `[^\n;{}]*`, which cannot cross a newline — so a WRAPPED comma-separated extern was
    # invisible in BOTH directions: the first physical line has no ';' and the continuation line has no
    # `extern`. src/ov_SC01_077/ov_SC01_077.c:271-272 declares NINE symbols that way:
    #     extern unsigned char D_801DAA78, D_801DAA79, ..., D_801DAA7C,
    #                          D_801DAA7D, ..., D_801DAA80;
    # and the exemplar that references them (func_8013D178) is a substantial family with 133 members.
    # Every sibling was therefore staged with NO declaration for those symbols, failed to compile
    # (`D_801DAA7D undeclared`), and — because the gate chunks by (overlay, split) — bisect-stormed the
    # whole group with it. Booked as a compile failure, i.e. invisible.
    _EXTERN_STMT = re.compile(r'^[ \t]*extern\b[^;{}]*?;', re.M | re.S)
    # (masked_text, original_text) per statement: MATCH on the mask, EMIT from the original.
    stmts = [(tu_mask[s.start():s.end()], tu[s.start():s.end()])
             for s in _EXTERN_STMT.finditer(tu_mask)]
    unit_stmts = [unit_mask[s.start():s.end()] for s in _EXTERN_STMT.finditer(unit_mask)]
    # FILE-SCOPE DECLS FIRST (Phase 29 T61). This function's contract is "file-scope `extern` decls
    # from the exemplar TU", but `^[ \t]*extern` also matches an INDENTED one — a block-scope decl
    # living inside some OTHER function's body, which is not even in scope at the exemplar's own
    # definition. Carrying it and re-emitting it at FILE scope in the sibling is how
    # `extern void func_80155FF8(void *, u8);` (ov_SC01_077 L1213, inside another function) landed
    # above the sibling's `DEFINE_func_80155FF8()` macro definition and collided with it —
    # 137 members booked as a compile failure.
    # Ordered, not filtered: a col-0 decl wins, and an indented one is still available as the
    # fallback it always was, so a symbol declared ONLY block-scope keeps working exactly as before.
    stmts.sort(key=lambda so: 0 if so[0].startswith('extern') else 1)

    for sym in sorted(refs):
        if any(re.search(rf'\b{sym}\b', s) for s in unit_stmts):
            continue                                         # already declared inside the unit
        if sym in seen:
            continue
        hit = next((orig for masked, orig in stmts if re.search(rf'\b{sym}\b', masked)), None)
        if hit is None:
            unresolved.append(sym)                           # REPORTED, never silently dropped (R32)
            continue
        lines.append(" ".join(hit.split()))                  # collapse the wrap to one legal C line
        seen.add(sym)
    if unresolved:
        print(f"[gather_externs] func_{from_addr:08X}: {len(unresolved)} referenced symbol(s) have NO "
              f"file-scope decl in {from_ov} — the sibling will not compile: {unresolved[:6]}")
    return lines


def remap_hseq_body(from_addr, from_ov, to_ov, to_addr, body):
    """the h_seq remap (symbol + immediate + cross-address self-rename) applied to a PROVIDED body text
    (a RAW crack draft), NOT the extract_unit matched body — for the per-sibling reconcile path (§41c):
    remap the raw draft to the sibling, then canon_sig_reconcile it against the sibling's own TU. No
    extern-carry (reconcile handles ambient decls). Returns (remapped_text, info) or (None, error)."""
    nins = nins_of(from_ov, from_addr)
    ex_words = stream_words(from_ov, from_addr, nins)
    sib_words = stream_words(to_ov, to_addr, nins)
    cls, _ = classify_member(ex_words, sib_words)
    if cls in ("STRUCT", "LEN"):
        return None, f"member class {cls}"
    m, err = symbol_map(from_addr, from_ov, to_ov, to_addr)
    if err:
        return None, err
    imm_map, unresolved = ({}, [])
    if cls == "IMM":
        imm_map, unresolved = imm_map_tier1(body, ex_words, sib_words)
        if unresolved:
            return None, f"unresolved immediates: {unresolved}"
    table = dict(m)
    if from_addr != to_addr:
        table[f"func_{from_addr:08X}"] = f"func_{to_addr:08X}"
    table.update(imm_map)
    body, off_notes = fix_derived_offsets(body, table)      # §84, BEFORE the name substitution
    return apply_remap(body, table), {"symbol_map": m, "imm_map": imm_map,
                                      "derived_offsets": off_notes}


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
    unit, off_notes = fix_derived_offsets(unit, table)      # §84, BEFORE the name substitution
    return apply_remap(unit, table), {"symbol_map": m, "imm_map": imm_map, "unresolved": unresolved,
                                      "n_externs": len(externs), "cf": cf,
                                      "derived_offsets": off_notes}


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
            # Name the symbol by WHAT THE ADDRESS IS, not by HOW IT WAS LOADED (Phase 26-A audit).
            #
            # The prefix used to come from the reloc KIND: `func_` for a `jal`, `D_` for anything else.
            # But reloc_targets labels every lui/%lo pair "data" — and a FUNCTION's address taken via
            # lui/%lo (an address-taken callback) is exactly that shape. splat's own .s proves it:
            # `%lo(func_8017E1D4)` occurs 7 times in ov_SC01_077's asm. For all 7 the map got a
            # `D_<ADDR>` key while the exemplar's C writes `func_<ADDR>`, so apply_remap's word-bounded
            # substitution matched NOTHING and silently no-op'd. The sibling body then kept the
            # EXEMPLAR's function pointer, the whole-binary gate rejected it, and the loss was booked
            # as a BYTE failure — indistinguishable from a genuine compiler wall. (3 families x 37
            # still-stubbed members, live.)
            #
            # Belt-and-braces: for a data-kind reloc emit BOTH keys. Addresses are unique and
            # apply_remap is a single simultaneous pass, so only the token that actually appears in the
            # C can ever match — the extra key is free and cannot mis-substitute.
            # ...and that rule has to govern the TARGET side too (Phase 29 T82). The block below
            # used to spell the sibling's symbol from the EXEMPLAR's kind — `func_` if the exemplar's
            # slot was a function, `D_` if data. For a CROSS-ADDRESS family the two sides need not
            # agree: `func_80174784`'s callback slot is the FUNCTION `func_801747CC`, while member
            # `func_8017CFD4`'s same slot is the DATA symbol `D_80182688`. The map emitted
            # `func_80182688` — a name for an address that is not a function — so the body
            # materialized the wrong symbol and the whole-binary gate rejected all 251 members.
            #
            # It reads as a compiler wall because the two oracles disagree in the most misleading
            # possible way: `rtu_match` MASKS HI16/LO16, so a wrong %hi/%lo symbol still reports
            # MATCH (measured: `MATCH (10 ins)` on a member the fleet gate refused). Spell the
            # target by what the target address IS in the SIBLING's overlay.
            tgt = f"func_{at:08X}" if at in fn_addrs(to_ov) else f"D_{at:08X}"
            if ke == "call":
                m[f"func_{ae:08X}"] = tgt
            else:
                m[f"D_{ae:08X}"] = tgt
                m[f"func_{ae:08X}"] = tgt
    return m, None


# A machine-generated FILE-SCOPE decl layer terminates here; extract_unit's backward preamble
# walk must not cross it (the layer belongs to the file, not to the function beneath it).
_DECL_LAYER_END = re.compile(r"end (?:§8b carried decl layer|canonical-sig layer)")

_DEFINE_FN = re.compile(r'^\s*#define\s+([A-Za-z_]\w*)\s*\(')


def _carry_macros(lines, start, end, unit_text):
    r"""The file-scope function-like `#define` macros the unit BODY references but does not itself
    contain — returned in file order, to be prepended to the unit (Phase-27 T5).

    A GTE-heavy per-location function calls C inline-asm macros (`gte_ldv0(...)`, `gte_rtps()`, …)
    that are `#define`d at FILE scope, above the function, NOT pulled from common.h (common.h carries
    the *assembler* gte_macros.inc for the INCLUDE_ASM path; the C macros live only in the exemplar's
    .c). extract_unit's backward preamble walk stops at the first `#define`/continuation line, so it
    dropped them — and a sibling staged without them saw every GTE op as an implicit-declaration CALL.
    That is TWO failures in one: the sibling fails to compile, AND — if the body carries a caller-saved
    register pin — the phantom call pushes cc1's sched1 into `create_reg_dead_note`'s abort
    (sched.c:2725), the SIGABRT long mis-recorded as the §42e "pin-crash wall" (`.run/giants/
    pin_crash_sigabrt.md`: the wall is this staging drop, not a compiler limit — a pinned family
    stages 133/133 clean once its macros ride along). Carried macros never reach dedup_propagate's
    engine_core.h lift (that path builds from its own body, not extract_unit), so no `#define` is ever
    embedded inside a `DEFINE_func_*()` macro."""
    carried, i = [], 0
    while i < len(lines):
        m = _DEFINE_FN.match(lines[i])
        if not m:
            i += 1
            continue
        j = i
        while j < len(lines) and lines[j].rstrip().endswith("\\"):
            j += 1
        inside = start <= i and j <= end
        if not inside and re.search(rf'\b{re.escape(m.group(1))}\s*\(', unit_text):
            carried.append("\n".join(lines[i:j + 1]))
        i = j + 1
    return carried


def _def_head_at(ln, paren_idx):
    """Does the `func_…(` occurrence whose '(' is at `paren_idx` head a DEFINITION on this line?

    The old test was "the line does not end in `;`", which is wrong whenever a line holds BOTH a
    declaration and a definition (Phase 29 T65). ov_SC01_077_jr_80154C24.c:1346 is

        extern void func_80156044(int, int); int func_80155FF8(int, int) { __asm__ … }

    and the line does not end in `;`, so `func_80156044` — which appears only in the DECLARATION —
    was taken as a definition head. extract_unit therefore lifted the neighbouring wrapper instead of
    the real definition seven lines below, and every sibling got `redefinition of func_80155FF8`.

    The correct question is what follows the parameter list: `;` is a declaration, `{` (or end of
    line, i.e. the brace-on-its-own-line form) is a definition."""
    depth = 0
    for i in range(paren_idx, len(ln)):
        if ln[i] == '(':
            depth += 1
        elif ln[i] == ')':
            depth -= 1
            if depth == 0:
                rest = ln[i + 1:].strip()
                rest = re.sub(r'^(/\*.*?\*/|//.*)\s*', '', rest)
                if rest == '' or rest.startswith('{'):
                    return True
                if rest.startswith(';'):
                    return False
                return '{' in rest
    return True                      # param list continues past this line -> an ANSI definition


def _foreign_defs(unit_text, addr):
    """Every `func_XXXXXXXX` this unit DEFINES other than its target (Phase 29 T65, §110).

    Definition vs declaration is the same test extract_unit uses on the way in: a declaration ends in
    `;` once trailing comments are stripped. `DEFINE_func_X()` macro instantiations are not matched —
    there is no word boundary before `func_` inside `DEFINE_func_`, which is exactly what we want,
    since a macro instantiation defines nothing the sibling does not already have."""
    self_sym = f"func_{addr:08X}".lower()
    out = []
    for ln in cdecl._mask(unit_text).split("\n"):
        for m in re.finditer(r'\bfunc_[0-9A-Fa-f]{8}\s*\(', ln):
            name = m.group(0).split("(")[0].strip()
            if name.lower() == self_sym:
                continue
            # The text before the name must look like a DECLARATION HEAD (a return type), which
            # excludes call sites (`iVar4 = func_X(` / a bare `func_X(a);` statement). Split on the
            # last `;` first, so a definition sharing its line with a preceding declaration — the
            # wrapper form that caused this whole bug — is still seen.
            pre_tail = ln[:m.start()].rsplit(';', 1)[-1]
            if not re.fullmatch(r'\s*[A-Za-z_][\w \*]*', pre_tail):
                continue
            if not _def_head_at(ln, ln.index('(', m.start())):          # a declaration, not a def
                continue
            if name not in out:
                out.append(name)
    return out


def extract_unit(ov, addr):
    """the matched inline def + its contiguous preceding extern/blank/comment lines, from the overlay src.
    func_<addr> names are UPPERCASE-hex in src (func_8013DBE4); match case-insensitively to be safe."""
    pat = re.compile(rf'^\s*[A-Za-z_][\w \*]*\bfunc_{addr:08X}\s*\(', re.I)
    for cf in sorted(glob.glob(f"src/{ov}/{ov}*.c")):
        lines = open(cf).read().split("\n")
        for i, ln in enumerate(lines):
            # A DECLARATION ends in `;` — but m2c writes them with a trailing comment
            # (`M2C_UNK func_80178D40(s32, s32);   /* extern */`), so the raw line ends in `*/` and the
            # old `endswith(";")` guard let it through as a DEFINITION. The forward brace-scan then ran
            # past it and swallowed the NEXT function's body, handing remap_hseq a garbage unit (5 of 35
            # substantial-family exemplars — all still INCLUDE_ASM stubs). The whole-binary gate rejected
            # every one, so no wrong match was ever banked (G3/P9) — but the family engine burned a
            # build per sibling on them and any extract_unit-based readiness analysis was wrong.
            # Strip trailing comments before the `;` test. (Phase 26 session 8, R14.)
            code = re.sub(r'(/\*.*?\*/|//.*)\s*$', '', ln).rstrip()
            _m = pat.search(ln)
            if _m and "INCLUDE_ASM" not in ln and not code.endswith(";") \
                    and _def_head_at(ln, ln.index('(', _m.end() - 1)):
                j = i - 1
                # Grab the fn's own preceding decls: externs, comments, AND single-line typedefs
                # (Phase-26 §8: jr-function bodies define local `typedef struct {…} Foo_<addr>;` that
                # must template with the body, else the sibling sees `Foo undeclared`. Multi-line
                # typedefs aren't carried — those functions route through the engine_types.h lift).
                # STOP at a machine-generated FILE-SCOPE decl layer (the §8b carried layer that
                # jr_isolate_all prepends to an isolated region, or the Phase-17 canonical-sig layer):
                # those belong to the FILE, not to the first function under them. Absorbing one makes
                # the unit drag ~140 unrelated externs into every sibling — several naming types the
                # sibling's TU lacks — and the whole family gate-fails (Phase 26 session 6).
                while j >= 0 and (lines[j].strip() == "" or
                                  lines[j].lstrip().startswith(("extern", "//", "/*", "*", "typedef"))):
                    if _DECL_LAYER_END.search(lines[j]):
                        break
                    # A LINE THAT STARTS WITH `extern` CAN STILL HOLD A DEFINITION (Phase 29 T65).
                    # ov_SC01_077_jr_80154C24.c:1346 is
                    #     extern void func_80156044(int, int); int func_80155FF8(int, int) { __asm__ … }
                    # — a declaration AND a complete handwritten inline-asm function on ONE line. The
                    # scan absorbed it as a "preceding decl", so the unit for func_80156044 carried a
                    # SECOND function definition, and every sibling that already defines that function
                    # via its shared DEFINE_ macro got `redefinition of func_80155FF8`. 137 members,
                    # booked as a compile failure. A pure declaration never contains `{`; a single-line
                    # `typedef struct {…} Foo;` legitimately does, and is still carried.
                    if "{" in lines[j] and not lines[j].lstrip().startswith("typedef"):
                        break
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
                unit_text = "\n".join(lines[start:end + 1])
                extra = _foreign_defs(unit_text, addr)
                if extra:
                    # R32: a unit that defines a function OTHER than its target cannot be templated —
                    # the sibling already has that function (inline, or via its shared DEFINE_ macro),
                    # so splicing produces `redefinition of …`. Refuse LOUDLY rather than hand the
                    # sweep a unit that will fail 137 times and read as a compiler wall.
                    print(f"[extract_unit] func_{addr:08X} in {ov}: unit also DEFINES {extra} — "
                          f"refusing (a multi-definition unit cannot template; §110)")
                    return None, None
                macros = _carry_macros(lines, start, end, unit_text)   # gte_* etc. the body needs (T5)
                if macros:
                    unit_text = "\n".join(macros) + "\n" + unit_text
                return unit_text, cf
    return _macro_unit(addr)


def _macro_unit(addr):
    r"""Fallback: reconstruct the unit from its SHARED `DEFINE_func_<ADDR>()` macro.

    A function can be MATCHED with no inline definition in ANY .c — once dedup_propagate lifts it, the
    body lives only as a macro in src/shared/engine_core.h and every overlay carries a bare
    `DEFINE_func_X()` instantiation. extract_unit globbed only `src/<ov>/<ov>*.c`, so for those it
    returned None — and the caller reads None as "not matched".

    MEASURED (Phase 26-A audit, CRITICAL): 93 of the 218 h_seq exemplars the manifest calls MATCHED are
    phantom for exactly this reason, carrying 2,157 candidate members of which **1,834 are still
    INCLUDE_ASM stubs that are PURE/IMM-clean, symbol_map-clean and unpinned** — i.e. they would be
    staged and byte-gated today, and were instead dropped before the first build. And because these are
    the functions dedup lifted precisely BECAUSE their reach is high, the loss is concentrated in the
    largest families.

    This is an exact INVERSE of dedup_propagate.make_macro(), which built the macro from `externs +
    def block` as:  `#define DEFINE_func_<ADDR>() \` then, per line, 4 spaces + line.rstrip() + ` \`
    (no continuation on the last). So the reconstruction IS the unit extract_unit wants — it is derived
    from the generator, not re-guessed from the text.

    NOTE for callers: the returned path is a HEADER, not a TU. family_sweep must keep using the
    SIBLING's src_rel for its reconcile/scope_data step."""
    head = f"#define DEFINE_func_{addr:08X}() \\"
    for hp in sorted(glob.glob("src/shared/*.h")):
        lines = open(hp).read().split("\n")
        for i, ln in enumerate(lines):
            if ln.rstrip() != head:
                continue
            body, j = [], i + 1
            while j < len(lines):
                raw = lines[j]
                cont = raw.rstrip().endswith("\\")
                stripped = re.sub(r'\s*\\$', '', raw)          # drop the line-continuation
                body.append(stripped[4:] if stripped.startswith("    ") else stripped)
                j += 1
                if not cont:
                    break
            return "\n".join(body), hp

    # There is a SECOND shared-body mechanism, and a macro-only fallback would be blind to it: a DIRECT
    # definition in a shared header, #included per overlay rather than instantiated as a macro. The whale
    # (func_80144B9C, 770 ins, -O0) is shared exactly that way — config/dedup.us.yaml records it as
    # `func: func_80144B9C  # ... shared via a HEADER #included in each overlay's -O0 <ov>_o0b.c (NOT a
    # DEFINE_ macro)`. Costs nothing today (the whale is fully banked), but the shape is armed for the
    # next shared-header function, and "the tool silently says NOT MATCHED" is precisely the failure
    # class this audit exists to remove. Be TOTAL over both mechanisms.
    # COLUMN 0 only. A shared header is mostly MACRO BODIES, and make_macro indents every body line by
    # exactly 4 spaces — so anchoring at column 0 excludes them by construction. That matters: a macro
    # body line like `    extern void func_80144B9C(void); \` would otherwise be read as a DEFINITION,
    # because the trailing line-continuation means the line does not end in ';' and the decl guard never
    # fires. That is exactly the declaration-read-as-definition bug fixed at commit:0552 — do not re-open
    # it. The whale's direct definition (`void func_80144B9C(void) {`) is at column 0, as any real
    # file-scope definition must be.
    pat = re.compile(rf'^[A-Za-z_][\w \*]*\bfunc_{addr:08X}\s*\(', re.I)
    for hp in sorted(glob.glob("src/shared/*.h")):
        lines = open(hp).read().split("\n")
        for i, ln in enumerate(lines):
            code = re.sub(r'\s*\\$', '', ln)                       # drop a macro line-continuation FIRST
            code = re.sub(r'(/\*.*?\*/|//.*)\s*$', '', code).rstrip()
            if not (pat.search(ln) and "INCLUDE_ASM" not in ln and not code.endswith(";")):
                continue
            depth, started, end = 0, False, i
            for k in range(i, len(lines)):
                depth += lines[k].count("{") - lines[k].count("}")
                if "{" in lines[k]:
                    started = True
                if started and depth <= 0:
                    end = k
                    break
            return "\n".join(lines[i:end + 1]), hp
    return None, None


_DERIVED_OFF_RE = re.compile(r'&\s*(D_([0-9A-Fa-f]{8}))\s*\+\s*(0[xX][0-9A-Fa-f]+|\d+)')


def fix_derived_offsets(unit, table):
    """§84 — recompute `&D_<ex> + <lit>` literals against the MEMBER's own symbol addresses.

    A crack may reach a symbol via a DIFFERENT symbol plus a literal offset, so gcc cannot CSE the two
    %hi/%lo pairs into one:
        (*(S9 *)&D_801DAA78) = *(S9 *)(&D_801DA998 + 0x20);   /* same addr as &D_801DA9B8 */
    The literal is NOT a constant of the algorithm — it is the DISTANCE BETWEEN TWO PER-OVERLAY
    SYMBOLS, and that distance differs per overlay. Substituting the NAMES while carrying the literal
    through emits a wrong %lo, and `match_one` CANNOT SEE IT (it masks HI16/LO16) — only the
    whole-binary gate does, as a ONE-BYTE diff. Measured: exemplar 0x801DA998+0x20 == 0x801DA9B8, but
    member 0x801A5778+0x20 == 0x801A5798 while the true member symbol is 0x801A5790 (delta 0x18).

    `unit` is the EXEMPLAR body (pre-substitution) and `table` the exemplar->member symbol map, so both
    endpoints resolve here. Returns (unit', notes); notes carries (base, old, new) per site, with
    new=None where an endpoint is NOT a mapped symbol — REPORTED, never silently carried (R32: a
    silent skip is a defect, and a silent skip is exactly how this survived)."""
    notes = []

    def repl(m):
        base_ex, hexs, lit_s = m.group(1), m.group(2), m.group(3)
        lit = int(lit_s, 16) if lit_s.lower().startswith('0x') else int(lit_s)
        target_ex = "D_%08X" % (int(hexs, 16) + lit)
        base_mem, target_mem = table.get(base_ex), table.get(target_ex)
        if base_mem is None or target_mem is None:
            notes.append((base_ex, lit, None))       # not a symbol-to-symbol distance -> leave as-is
            return m.group(0)
        new_lit = int(target_mem[2:], 16) - int(base_mem[2:], 16)
        notes.append((base_ex, lit, new_lit))
        if new_lit == lit:
            return m.group(0)
        return m.group(0).replace(lit_s, ("0x%X" % new_lit) if new_lit >= 0 else ("-0x%X" % -new_lit))

    return _DERIVED_OFF_RE.sub(repl, unit), notes


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
    unit, _off_notes = fix_derived_offsets(unit, table)     # §84, BEFORE the name substitution
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
