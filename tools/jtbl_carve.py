#!/usr/bin/env python3
"""Phase-26 §8 (overlay ×134): set up the jtbl-rodata carve for an overlay's matched jr-functions.

An overlay's gcc switch jump tables sit in one contiguous `.rodata` island at the TAIL of the flat
blob. Matching a jr-function makes its C emit that jtbl into `.rodata` (floated to the FRONT by
section_order) while the raw copy stays in the data tail -> duplicate + wrong address. This tool
carves each named jr-function's jtbl(s) out of the `[…, data, tail]` region into a dotted
`[.rodata, <code-subseg>]` subseg (spimdisasm migrates it into the fn's object), splitting the data
tail into the surrounding `data` subsegs, and sets the `<ov>_JTBL_INTERLEAVE` var in
config/overlays.mk so `make extract` runs `ld_interleave --order` (the address-ordered
data->rodata->data->…->data sandwich; cookbook §8/§8a).

Per-sibling: the SAME function is at the same vram across overlays but its jtbl is at a DIFFERENT
address in each (the island floats with the overlay's size), so the carve is recomputed per overlay.

MULTI-jtbl (Phase-26 session 3): the carve is ADDITIVE and regenerated from the current config —
each `--func` call re-derives the FULL address-ordered set of {data pieces, existing .rodata carves,
the new jtbl(s)} and re-emits the region + an `--order` interleave list. So banking a 2nd matched
jr-function into an overlay that already has one (the ×134 accumulation case) Just Works. A single
code object contributes at most ONE contiguous .rodata run, so two matched jr-functions in the SAME
code subseg (non-adjacent jtbls in the island) are UNSATISFIABLE -> this tool fails loud, and the
caller must first isolate one into its own code subseg (the whale `_o0b` precedent).

MULTI-TABLE spans & the 8-align pad spec (Phase-29 §8e; .run/probe_jtbl/verdict.md): cc1 emits
`.align 3` before EVERY jump table and maspsx passes it through, so a merged same-subseg span whose
non-first table sits at an original vram ≡4 mod 8 would gain a +4 interior pad the original does
not have (originally-separate TUs pack TIGHT) — and conversely a real intra-TU pad word must be
reproduced where the original HAS one. When a span holds >1 table, this tool derives the per-table
pad spec by the payload ZERO-WORD rule (pad before table K iff the word at start[K]-4 is zero — a
zero can never be a table entry) over the span's TABLE STARTS, and writes a per-object `JTBL_PADS`
target var into config/overlays.mk; the Makefile then pipes that object through
tools/jtbl_rodata_pads.py, which REPLACES each rodata `.align` with the spec'd pad bytes. Table
starts are PERSISTED in the var's `tables=` comment (extract prunes matched owners' stub .s, so
they are unrecoverable later); an untouched span's committed line is reused verbatim; sibling
sweeps transfer span structure from the exemplar via `--like` (same family => same structure,
pads still derived from the local payload); `--span-tables` is the pre-§8e archaeology escape.
Single-table carves get NO var and keep today's byte-identical pipeline.

Usage:  jtbl_carve.py <ov> --func func_XXXX [--func ...]   # add these matched jr-fns to the carve set
        jtbl_carve.py <ov> --revert                        # restore the config from git (drop carves)
Idempotent: re-running with the same (accumulated) funcs reproduces the same config.
"""
import argparse
import glob
import os
import re
import subprocess
import sys
import mk_write as MKW    # atomic, collapse-refusing overlays.mk writer (P31 S60)

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# §8e CLI state (set by main)
LIKE_OV = None
SPAN_TABLES_OVERRIDE = {}

PIECE_RE = re.compile(r"^(\s*)- \[(0x[0-9A-Fa-f]+),\s*([.\w]+),\s*(\w+)\]")
EOF_RE = re.compile(r"^\s*- \[(0x[0-9A-Fa-f]+)\]\s*(?:#.*)?$")


def cfg_path(ov):
    # The S58 blanket refusal of md_*/main is LIFTED (P31 S59) now that `parse_config` implements
    # its documented contract — see its docstring for the measured corruption it used to cause and
    # tools/test_jtbl_parse_config.py for the proof (171 non-md configs byte-unchanged, 42 md_*
    # configs now keep their `c` line). Two class facts the refusal had lumped together:
    #   * md_* (42 configs) was the real corruption class — the §154-A leading island puts a
    #     `.rodata` piece BEFORE the `c` piece.
    #   * main was never in it. Its pieces are already [all c ..., data, .rodata, data], so the
    #     contract held; main's defects were this path (there is no `config/splat.main.yaml`) and
    #     the file base (see overlay_vram_base).
    # What is still refused is the OPERATION that cannot work, not the binary class: a carve that
    # lands in a leading island is rejected in build_carve, which names the lane that owns it.
    if ov == "main":
        # main is `config/splat.us.exe.yaml` — there is no `splat.main.yaml`, and the unguarded
        # open() below used to raise FileNotFoundError on every main jtbl target.
        p = os.path.join(REPO, "config/splat.us.exe.yaml")
        if not os.path.exists(p):
            sys.exit(f"jtbl_carve: no splat config at {p} for binary 'main'")
        return p
    p = os.path.join(REPO, f"config/splat.{ov}.yaml")
    if not os.path.exists(p):
        sys.exit(f"jtbl_carve: no splat config at {p} for binary {ov!r}")
    return p


def overlay_vram_base(ov):
    """The binary's file0->vram delta (all location overlays share the 0x80128158 slot, but read it).

    Every `off` in this module is a FILE offset into the payload and every address is a vram, so
    this is the one place the two coordinate systems meet: vram = base + off.

    main is the exception the naive `first vram: in the yaml` read gets WRONG. The EXE carries a
    0x800 header before its code segment, so its delta is the code segment's `vram - start`
    (0x80010000 - 0x800 = 0x8000F800), not 0x80010000. With the naive value every vram->offset
    conversion (`s_vram - base`) comes out 0x800 too small and `payload_word` silently reads 0x800
    early — a wrong word, not an error. That derivation already exists once, in
    family_remap.vram_of (P31 T3); call it rather than write a second one (R33)."""
    if ov == "main":
        return _main_file_base()
    txt = open(cfg_path(ov)).read()
    m = re.search(r"vram:\s*(0x[0-9A-Fa-f]+)", txt)
    if not m:
        sys.exit(f"jtbl_carve: no vram in {cfg_path(ov)}")
    return int(m.group(1), 16)


def _main_file_base():
    """main's file0->vram delta, via the single derivation in family_remap.vram_of (R33).

    family_remap reads cwd-relative config paths (its callers run at the repo root) while this
    module is REPO-absolute on purpose, so the cwd is switched for the call and restored."""
    sys.path.insert(0, os.path.join(REPO, "tools"))
    cwd = os.getcwd()
    try:
        os.chdir(REPO)
        import family_remap
        return family_remap.vram_of("main")
    finally:
        os.chdir(cwd)


def asm_dir(ov):
    """The root of this binary's split asm tree.

    Overlays and modules get `asm/<alias>/…`; main is the ONE binary splat writes to the tree root
    (`asm/nonmatchings/800/func_8001A114.s`, `asm/data/*.data.s`) because it is the EXE the project
    is named for and its yaml predates the per-binary layout. Hardcoding `asm/<ov>` therefore made
    every main lookup miss a directory that does not exist and report the miss as
    "already spliced AND no stale copy" — a true-sounding message about the wrong tree (R43)."""
    return os.path.join(REPO, "asm") if ov == "main" else os.path.join(REPO, "asm", ov)


def payload_path(ov):
    """The overlay's decompressed payload, derived from the config's target_path (R33)."""
    m = re.search(r"target_path:\s*(\S+)", open(cfg_path(ov)).read())
    if not m:
        sys.exit(f"jtbl_carve: no target_path in {cfg_path(ov)}")
    p = os.path.join(REPO, m.group(1))
    if not os.path.exists(p):
        sys.exit(f"jtbl_carve: payload {p} missing — run `make extract` first (R32: refusing to "
                 f"skip the gap-word check)")
    return p


def payload_word(ov, off):
    """The little-endian u32 at file offset `off` in the overlay's payload."""
    with open(payload_path(ov), "rb") as f:
        f.seek(off)
        b = f.read(4)
    if len(b) != 4:
        sys.exit(f"jtbl_carve: short read at payload offset 0x{off:x}")
    return int.from_bytes(b, "little")


# Per-object pad-spec lines in config/overlays.mk (Phase-29 §8e — consumed by the Makefile's
# jtbl_rodata_pads.py stage). One line per multi-table span; the comment PERSISTS the span's
# table starts as span-relative offsets (the durable record — matched owners' stub .s files are
# pruned by extract, so starts can't be reconstructed later without it):
#   build/src/<ov>/<sub>.o: JTBL_PADS := 0,0,4,0  # §8e pads (jtbl_carve.py) tables=+0x0,+0x20,+0x38,+0x58
def pads_comment(rel_starts):
    if rel_starts is None:      # carried from a line predating the tables= persistence
        return "  # §8e pads (jtbl_carve.py)"
    return ("  # §8e pads (jtbl_carve.py) tables="
            + ",".join(f"+0x{r:x}" for r in rel_starts))


def pads_line_re(ov):
    return rf"^build/src/{re.escape(ov)}/(\w+)\.o: JTBL_PADS := ([\d,]+)\s*(?:#[^\n]*)?$"


def current_pads_specs(ov, txt=None):
    """{subseg: (spec, rel_starts_or_None)} from the CURRENT overlays.mk."""
    if txt is None:
        txt = open(os.path.join(REPO, "config/overlays.mk")).read()
    out = {}
    for m in re.finditer(pads_line_re(ov), txt, re.M):
        spec = [int(x) for x in m.group(2).split(",")]
        line = m.group(0)
        tm = re.search(r"tables=([+0-9a-fx,]+)", line)
        rel = [int(x, 16) for x in tm.group(1).replace("+", "").split(",")] if tm else None
        out[m.group(1)] = (spec, rel)
    return out


def code_pieces(ov):
    """[(vram, subseg)] for every `- [off, c, name]` code piece in the config, ascending."""
    base = overlay_vram_base(ov)
    out = []
    for ln in open(cfg_path(ov)):
        m = re.match(r'\s*- \[(0x[0-9A-Fa-f]+),\s*c,\s*(\w+)\]', ln)
        if m:
            out.append((base + int(m.group(1), 16), m.group(2)))
    return sorted(out)


def func_subseg(ov, func):
    """The code subseg that owns `func`, derived from the CONFIG (address -> containing code piece).

    NOT from the asm tree: `make extract` does not prune stale subseg directories, so after a §8b
    isolation BOTH `nonmatchings/<ov>_after/<func>.s` (stale) and `nonmatchings/<ov>_jr_<ADDR>/<func>.s`
    (current) exist on disk, and an `os.listdir` scan can return the STALE owner — silently
    re-creating the same-subseg NON-CONTIGUOUS collision the isolation just removed. The config is
    authoritative and stale-proof."""
    addr = int(func[len("func_"):], 16)
    owner = None
    for vram, name in code_pieces(ov):
        if vram <= addr:
            owner = name
        else:
            break
    if owner is None:
        sys.exit(f"jtbl_carve: {func} (0x{addr:08x}) precedes every code piece in {cfg_path(ov)}")
    return owner


def overlay_jtbl_addrs(ov):
    """Every jtbl_ vram referenced by ANY per-function .s under asm/<ov>/nonmatchings/ (stale
    copies included — a matched fn's last stub .s still names its tables, and jtbl refs are
    address-stable). Used to reconstruct the TABLE STARTS inside an existing carve span, whose
    dlabels are long gone from the data asm (Phase-29 §8e)."""
    addrs = set()
    for p in glob.glob(os.path.join(asm_dir(ov), "nonmatchings", "*", "func_*.s")):
        for m in re.finditer(r"jtbl_([0-9A-Fa-f]{8})", open(p).read()):
            addrs.add(int(m.group(1), 16))
    return addrs


def spec_from_starts(ov, base, s_off, e_off, tables):
    """The JTBL_PADS spec for a span [s_off, e_off) given its table starts (absolute vrams):
    one entry per table, pad[K] = 4 iff the payload word right before table K is zero.

    Sound because a zero word can never be a jump-table ENTRY (0x00000000 is not a jump target —
    the §8a-pad axiom), so the word at start[K]-4 is zero IFF it is the original `.align 3` pad.
    Needs no entry counts — derived from {table starts} + the payload (R33)."""
    s_vram, e_vram = base + s_off, base + e_off
    tables = sorted(set(tables))
    # R32 COVERAGE — the given starts must EXPLAIN the span, not merely fit inside it (P30 S29,
    # §132). Every zero word INSIDE the span is an original `.align 3` pad (same axiom this
    # function's pad rule already rests on: a zero can never be an ENTRY), so the word after it
    # STARTS a table. The caller's union can silently miss an interior table when the span is a
    # pre-§8e MERGED DOUBLE: no persisted `tables=`, and the extra owner is already MATCHED so
    # `make extract` pruned the stub .s that named its table. The old code then inferred
    # "single-table predecessor", emitted a spec one table SHORT, and jtbl_rodata_pads refused
    # mid-stream at build time — correctly, but the truncated object it left behind (no
    # .DELETE_ON_ERROR, now fixed) surfaced one build later as `undefined reference to $L105`.
    # Recover those starts here, from the payload, at the single choke point (R33).
    # HONEST LIMIT: this recovers only PAD-SEPARATED boundaries. A tight (0-pad) interior boundary
    # is indistinguishable from a continuing table in the payload, so it stays unrecovered — but it
    # then makes the spec SHORT, which the filter's table-count guard rejects LOUDLY at build time.
    # The failure mode is therefore never silent in either branch.
    recovered = sorted({base + o + 4 for o in range(s_off, e_off, 4)
                        if payload_word(ov, o) == 0 and o + 4 < e_off} - set(tables))
    if recovered:
        print("jtbl_carve: span 0x%x..0x%x: RECOVERED %d interior table start(s) from the payload "
              "zero-word rule (pre-§8e span with no persisted tables=): %s"
              % (s_off, e_off, len(recovered), ", ".join("0x%x" % r for r in recovered)))
        tables = sorted(set(tables) | set(recovered))
    if not tables or tables[0] != s_vram or tables[-1] >= e_vram:
        sys.exit(f"jtbl_carve: span 0x{s_off:x}..0x{e_off:x}: table starts "
                 f"{['0x%x' % t for t in tables]} do not fit the span (first must equal the "
                 f"span start; all must lie inside)")
    spec = [0]
    for a in tables[1:]:
        spec.append(4 if payload_word(ov, (a - base) - 4) == 0 else 0)
    return spec, [a - tables[0] for a in tables]


def func_jtbls(ov, func):
    """(subseg, [jtbl_hex,...]) that `func` references (from its .s %hi(jtbl_...)).

    The owning SUBSEG is config-derived (stale-proof, see func_subseg). The .s CONTENT lookup may
    fall back to a stale-location copy (Phase-29 §8e): once the fn is spliced as C and re-extracted
    (e.g. after a jr isolation), no fresh .s exists anywhere — but a stale one in a previous owner's
    dir still holds the correct jtbl refs (the fn's code, hence its %hi(jtbl_...) set, is
    address-stable regardless of which subseg owned it)."""
    sub = func_subseg(ov, func)
    p = os.path.join(asm_dir(ov), "nonmatchings", sub, f"{func}.s")
    if not os.path.exists(p):
        stale = sorted(glob.glob(os.path.join(asm_dir(ov), "nonmatchings", "*", f"{func}.s")))
        if not stale:
            sys.exit(f"jtbl_carve: no .s for {func} anywhere under {os.path.relpath(asm_dir(ov), REPO)}/nonmatchings/ — "
                     f"already spliced AND no stale copy; re-extract from the stub state first")
        p = stale[0]
        print(f"jtbl_carve: {func}.s not in config-derived subseg '{sub}' — using stale-location "
              f"{os.path.relpath(p, REPO)} for jtbl refs (content is address-stable)")
    s = open(p).read()
    return sub, sorted(set(re.findall(r"jtbl_([0-9A-Fa-f]{8})", s)))


def all_data_labels(ov):
    """All (jtbl_|D_) dlabel vrams across every asm/<ov>/data/*.data.s, sorted ascending."""
    labels = set()
    for p in glob.glob(os.path.join(asm_dir(ov), "data", "*.data.s")):
        for ln in open(p):
            m = re.match(r"\s*(?:dlabel|glabel)\s+(?:jtbl_|D_)([0-9A-Fa-f]{8})", ln)
            if m:
                labels.add(int(m.group(1), 16))
    return sorted(labels)


def jtbl_words(ov, jtbl_hex):
    """The raw `.word` values under `dlabel jtbl_<hex>`, in order."""
    pat = re.compile(rf"dlabel\s+jtbl_{jtbl_hex}\b", re.I)
    for p in glob.glob(os.path.join(asm_dir(ov), "data", "*.data.s")):
        lines = open(p).read().split("\n")
        for i, ln in enumerate(lines):
            if pat.search(ln):
                out = []
                for ln2 in lines[i + 1:]:
                    m = re.search(r"\.word\s+(0x[0-9A-Fa-f]+)", ln2)
                    if m:
                        out.append(int(m.group(1), 16))
                        continue
                    if re.search(r"\b(?:dlabel|glabel|enddlabel)\b", ln2):
                        break
                return out
    return []


def _label_words(ov, prefix, hex_addr):
    """The raw `.word` values under `dlabel <prefix><hex>`, in order (generic jtbl_words)."""
    pat = re.compile(rf"dlabel\s+{prefix}{hex_addr}\b", re.I)
    for p in glob.glob(os.path.join(asm_dir(ov), "data", "*.data.s")):
        lines = open(p).read().split("\n")
        for i, ln in enumerate(lines):
            if pat.search(ln):
                out = []
                for ln2 in lines[i + 1:]:
                    m = re.search(r"\.word\s+(0x[0-9A-Fa-f]+)", ln2)
                    if m:
                        out.append(int(m.group(1), 16))
                        continue
                    if re.search(r"\b(?:dlabel|glabel|enddlabel)\b", ln2):
                        break
                return out
    return []


def _sltiu_bounds(ov, fn, sub):
    """Every `sltiu $x, $y, N` immediate in <fn>'s disassembly — the switch RANGE CHECKS.

    THE AUTHORITATIVE ORACLE for how many entries a jump table has: gcc emits
    `sltiu $v0, $idx, N` immediately before the indexed load, so the FUNCTION ITSELF declares
    its table length. Everything else (the next dlabel, an xref census, the trailing-zero trim)
    is inference about what spimdisasm chose to emit; this is the program's own statement."""
    p = os.path.join(asm_dir(ov), "nonmatchings", sub, f"{fn}.s")
    if not os.path.exists(p):
        return set()
    out = set()
    for ln in open(p, errors="replace"):
        m = re.search(r"\bsltiu\s+\$\w+,\s*\$\w+,\s*(0x[0-9A-Fa-f]+|\d+)", ln)
        if m:
            out.add(int(m.group(1), 16) if m.group(1).startswith("0x") else int(m.group(1)))
    return out


def _table_bound(ov, fn, sub, jtbl_hex):
    """The entry count of ONE table: the `sltiu $x, $y, N` that guards ITS OWN dispatch.

    P31 S75 (byte-proven on ov_SC01_004/func_8017EB30, ov_SC01_008/func_8017EC68,
    ov_SC01_005+006/func_8017F2D4 — the four 279-ins reloc-only siblings of ov_SC01_009/
    func_8017EB08 that gated DIFF 4/4 across S70-S74). `_sltiu_bounds` returns the SET of every
    `sltiu` immediate in the function, and both the split-table repair and the over-span clamp
    below use it only when that set is a SINGLETON — so a function with any other unsigned range
    check (`(u32)(x - lo) < n` is `sltiu` too, cookbook I1) silently disables BOTH. Those four
    functions carry {0xA, 0x4, 0x28, 0x32, 0xF0}; spimdisasm had run each table's dlabel one word
    into the following non-zero data (0x696F760A / 0x000013FF / 0x62647020 — string bytes), the
    zero-word trim could not touch it, the clamp was skipped, and the carve reserved 0x2C for a
    0x28 table: -4 bytes, ~850 `%lo`s moved, whole-binary DIFF with a byte-identical .text.

    gcc-2.7.2's dispatch is a fixed idiom — `sltiu $v0,$idx,N ; beqz $v0,default ; sll $v0,$idx,2 ;
    lui $at,%hi(jtbl_X) ; addu $at,$at,$v0 ; lw $v0,%lo(jtbl_X)($at)` — so the `sltiu` nearest
    ABOVE the first `%hi(jtbl_X)` is unambiguous per table, whatever else the function tests.
    Returns None when the .s or the idiom is not found (callers fall back to the old set)."""
    p = os.path.join(asm_dir(ov), "nonmatchings", sub, f"{fn}.s")
    if not os.path.exists(p):
        stale = sorted(glob.glob(os.path.join(asm_dir(ov), "nonmatchings", "*", f"{fn}.s")))
        if not stale:
            return None
        p = stale[0]
    ins = [ln for ln in open(p, errors="replace") if re.match(r"\s*/\* [0-9A-F]+ [0-9A-F]{8} ", ln)]
    needle = f"%HI(JTBL_{jtbl_hex.upper()})"
    hi = next((i for i, ln in enumerate(ins) if needle in ln.upper()), None)
    if hi is None:
        return None
    for ln in reversed(ins[max(0, hi - 8):hi]):
        m = re.search(r"\bsltiu\s+\$\w+,\s*\$\w+,\s*(0x[0-9A-Fa-f]+|\d+)", ln)
        if m:
            return int(m.group(1), 16) if m.group(1).startswith("0x") else int(m.group(1))
    return None


def _continuation_words(ov, vram):
    """The words of the `D_<vram>` label if they all look like jump targets, else None.

    'Look like' = every word is a code address in this overlay's text. That is necessary but NOT
    sufficient to absorb the label — the caller additionally requires the owning function's own
    `sltiu` bound to demand those words. See the call site for why an xref census is NOT used."""
    words = _label_words(ov, "D_", f"{vram:08X}")
    if not words:
        return None
    if not all(0x80100000 <= w < 0x801D0000 for w in words):
        return None
    return words


def jtbl_range(ov, jtbl_hex, labels, region_end_vram, fn=None, sub=None):
    """(start_vram, end_vram) of a RAW jtbl_<hex>: end = the next data dlabel, MINUS any trailing
    zero words.

    A trailing `.word 0x00000000` under a jtbl dlabel is NOT a table entry — it is the original TU's
    intra-rdata **`.align 3` padding** (a jtbl whose entries end ≡4 mod 8, with another jtbl of the
    same TU following, gets one zero word of alignment fill). It cannot be an entry: 0x00000000 is
    not a jump target, and the function's `sltiu <n>` range check names the true entry count
    (byte-confirmed: `func_8015AE2C` → `sltiu 0x7` = 7 entries, yet the raw dlabel spans 8 words).

    Why trim (CORRECTED Phase-29 §8e — the old rationale "maspsx drops `.align`" was FALSE; maspsx
    passes it through, .run/probe_jtbl/verdict.md): the pad belongs to the NEXT table's `.align 3`,
    which is emitted only if that next table's owner is compiled in the SAME object. When the next
    owner is unmatched (or another TU), the carved object ends at the last real entry, so carving
    to the next dlabel would reserve the pad word the object does not supply — under-filling the
    `.rodata` piece by 4 bytes and shifting every later symbol (the same +4 image corruption class
    as §41d). Trimming leaves the pad where it belongs: in the raw post-carve data piece — and when
    the next owner IS matched into the same span later, the merge re-attributes the pad to that
    table's JTBL_PADS spec (pad[K]=4) and jtbl_rodata_pads.py emits it. This also retroactively
    explains the §8a `func_80159C84` "5 words vs the real 6" false-MATCH."""
    start = int(jtbl_hex, 16)
    if start not in labels:
        sys.exit(f"jtbl_carve: jtbl_{jtbl_hex} not found in the raw data asm "
                 f"(asm/{ov}/data/*.data.s) — already carved / stale asm? re-extract or --revert first")
    nxt = next((a for a in labels if a > start), None)
    end = nxt if nxt is not None else region_end_vram

    # ---- SPLIT-TABLE REPAIR (Phase 29 SESSION-21) -------------------------------------------
    # "end = the next data dlabel" assumes every dlabel is an object boundary. spimdisasm does not
    # guarantee that: it can CUT ONE JUMP TABLE IN HALF, emitting the tail under an invented `D_`
    # label. Measured on func_8012AAAC: its 50-word table appears as jtbl_801D7FB0 (28 words) +
    # D_801D8020 (22 words, ZERO xrefs anywhere in the tree). Carving to the next dlabel then
    # reserves 112 B for an object that supplies 200 B of .rodata — under-filling the piece and
    # shifting every later symbol (the same image-corruption class the trailing-pad trim exists
    # for, in the opposite direction). match_one is structurally blind to it (§84); it surfaces
    # only as a whole-binary DIFF, which is the most expensive place to learn it.
    #
    # AUTHORIZATION: the owning function's own `sltiu N` range check. A label is absorbed ONLY if
    # the function demands more entries than the dlabel boundary supplies, the following label is
    # immediately adjacent, its words are all code addresses, and absorbing it lands EXACTLY on
    # the entry count the function asked for. Then the extension is the program's own statement,
    # not a guess.
    #
    # An xref census was tried first and REJECTED as the gate. The wave agent that found this bug
    # reported D_801D8020 as having "ZERO xrefs anywhere in the tree"; it actually has two
    # (`.word D_801D8020` and `+ 0x2` in tail.data.s). Those two are almost certainly spimdisasm
    # mis-symbolizing packed halfword data — their neighbours are unaligned non-addresses like
    # 0x8012801B — but "almost certainly" is not a gate, and acting on the agent's stated remedy
    # (delete the label) would have removed a symbol two emitted words reference. The sltiu bound
    # needs no such judgement call. (R14: the agent's CONCLUSION was right and its EVIDENCE was
    # wrong; only re-deriving from the bytes separates those.)
    # A function may own SEVERAL switches, so there is no single "the" bound — use the SET and
    # require an EXACT hit. `max()` would be a guess, and a wrong absorption corrupts the image.
    bounds = _sltiu_bounds(ov, fn, sub) if fn and sub else set()
    # PER-TABLE BOUND FIRST (P31 S75, see _table_bound): the `sltiu` guarding THIS table's own
    # dispatch is unambiguous even when the function has several range checks, which is exactly
    # when the whole-function set below is >1 and the repair/clamp used to stand down silently.
    tb = _table_bound(ov, fn, sub, jtbl_hex) if fn and sub else None
    if tb is not None:
        if bounds and tb not in bounds:
            print(f"jtbl_carve: ⚠ jtbl_{jtbl_hex}: dispatch `sltiu {tb}` is not among {fn}'s sltiu "
                  f"set {sorted(bounds)} — instrument disagreement, using the dispatch bound", file=sys.stderr)
        bounds = {tb}
    absorbed = []                      # words pulled in from continuation labels, in order
    while bounds:
        have = (end - start) // 4
        if end is None or end >= region_end_vram or have in bounds:
            break
        tail = _continuation_words(ov, end)
        if tail is None:
            break
        # The continuation ends at ITS OWN last `.word`, not at the next dlabel: the label may be
        # followed by unlabeled data (here D_801D8020 holds 22 words to 0x801D8078 while the next
        # dlabel is 0x801D8158, 224 B further on). Using the next dlabel as the stop is the very
        # assumption this repair exists to correct.
        stop = end + len(tail) * 4
        n = (stop - start) // 4
        if n not in bounds:
            break                      # absorbing this label does not land exactly on a bound
        print(f"jtbl_carve: jtbl_{jtbl_hex}: absorbing D_{end:08X} ({len(tail)} words) — "
              f"{fn}'s own `sltiu {n}` demands {n} entries but the dlabel boundary supplies only "
              f"{have}; spimdisasm split ONE table across two dlabels (SESSION-21 repair)")
        absorbed.extend(tail)
        end = stop
    if len(bounds) == 1 and (end - start) // 4 < next(iter(bounds)):
        # R32: report a shortfall — but ONLY when the pairing is unambiguous. A multi-switch
        # function has several bounds and no way to say which one owns THIS table, and a warning
        # that fires on ambiguity is noise, not a signal (it fired ~90 times across 38 tables
        # before this guard).
        want = next(iter(bounds))
        print(f"jtbl_carve: ⚠ jtbl_{jtbl_hex}: {fn}'s only `sltiu` is {want} but the carve spans "
              f"{(end - start) // 4} — the object may supply more .rodata than the carve reserves "
              f"(§84-class image shift). Verify before banking.", file=sys.stderr)
    # The trailing-pad trim must see the WHOLE table, absorbed continuations included. Trimming
    # against the first dlabel's words alone re-truncates the range the repair above just widened
    # (measured: absorb 22 words -> trim 22 straight back off, net zero).
    words = jtbl_words(ov, jtbl_hex) + absorbed
    if words:
        n = len(words)
        while n > 0 and words[n - 1] == 0:
            n -= 1
        trimmed = start + n * 4
        if trimmed < end:
            print(f"jtbl_carve: jtbl_{jtbl_hex}: trimmed {(end - trimmed) // 4} trailing .align pad "
                  f"word(s) — {n} real entries")
            end = trimmed

    # ---- OVER-SPAN CLAMP (P30 S28) ----------------------------------------------------------
    # The trim above only removes ZERO words, because its axiom is "0x00000000 cannot be a jump
    # target". But spimdisasm attributes to a dlabel everything up to the NEXT dlabel, and that
    # trailing remainder is not always zero — it can be ordinary NON-ZERO data. Then nothing trims,
    # the carve reserves more words than the table has, the object supplies only the real entries,
    # and the `.rodata` piece UNDER-FILLS: every later symbol shifts down and every `%lo` that
    # references one changes. That is the exact §84-class image shift this function's docstring
    # warns about, arriving through the one door the zero-word rule does not cover.
    #
    # MEASURED (ov_SC06_018 / func_80191C50, the P30 "jtbl_carve diverges" instrument failure):
    # `sltiu 0xC` = 12 entries; the emitted .rodata has 12 words; the carve reserved 13 (the 13th
    # word is 0x3038200A — real data, non-zero, so untrimmed). Result: −4 bytes, 812 `%lo`
    # immediates changed, whole-binary DIFF. Isolate alone was byte-neutral; only the carve broke.
    #
    # AUTHORIZATION is the same as the SPLIT-TABLE REPAIR above and no weaker: the owning
    # function's OWN `sltiu N`, used only when it is UNAMBIGUOUS (exactly one bound — a
    # multi-switch function cannot say which table owns which bound), and only when the surplus
    # words are NOT plausible jump targets. A word inside this overlay's text range might be a real
    # entry, so if any surplus word looks like a code address we REFUSE to clamp and fall through
    # to the existing loud shortfall/So-verify path rather than silently dropping a live entry.
    if len(bounds) == 1 and words:
        want = next(iter(bounds))
        have = (end - start) // 4
        if have > want:
            surplus = words[want:have]
            if any(0x80100000 <= w < 0x801D0000 for w in surplus):
                print(f"jtbl_carve: ⚠ jtbl_{jtbl_hex}: span {have} exceeds {fn}'s `sltiu {want}`, "
                      f"but {sum(1 for w in surplus if 0x80100000 <= w < 0x801D0000)} surplus "
                      f"word(s) look like code addresses — REFUSING to clamp (a real entry may be "
                      f"at stake). Verify by hand before banking.", file=sys.stderr)
            else:
                print(f"jtbl_carve: jtbl_{jtbl_hex}: clamped {have - want} trailing NON-ZERO "
                      f"word(s) — {fn}'s own `sltiu {want}` names {want} entries and the surplus is "
                      f"not code (spimdisasm ran the dlabel into the following data)")
                end = start + want * 4
    return start, end


def _migrated_spans(ov, func):
    """[(start_off, end_off, n_pad_words)] for each table MIGRATED into FUNC's own `.s`
    (§154-A: a module's island tables live in the owning stub's `.s`, never in the data asm).

    Word counts come from the dlabel block itself — the only place a migrated table's extent
    exists (the island has no per-table dlabels anywhere else). A trailing `.word 0x00000000`
    is counted separately (`n_pad_words`): in the STUB state the `.s` supplies it, but a MATCHED
    body's cc1 re-emits only the real entries (a single table at section offset 0 gets no
    `.align 3` pad), so a padded migrated table cannot round-trip byte-identically without the
    §8e pad machinery — which config/modules.mk does not carry. Callers refuse on pads (R43)."""
    base = overlay_vram_base(ov)
    sub = func_subseg(ov, func)
    p = os.path.join(asm_dir(ov), "nonmatchings", sub, f"{func}.s")
    if not os.path.exists(p):
        stale = sorted(glob.glob(os.path.join(asm_dir(ov), "nonmatchings", "*", f"{func}.s")))
        if not stale:
            sys.exit(f"jtbl_carve: no .s for {func} anywhere under "
                     f"{os.path.relpath(asm_dir(ov), REPO)}/nonmatchings/ — cannot derive the "
                     f"migrated table span; re-extract first")
        p = stale[0]
    spans, cur, words = [], None, []
    for ln in open(p).read().split("\n"):
        m = re.match(r"\s*dlabel\s+jtbl_([0-9A-Fa-f]{8})", ln)
        if m:
            cur, words = int(m.group(1), 16) - base, []
            continue
        if cur is None:
            continue
        w = re.search(r"\.word\s+(\S+)", ln)
        if w:
            words.append(w.group(1))
            continue
        if re.search(r"\benddlabel\b", ln):
            pad = 0
            while words and words[-1] in ("0x00000000", "0"):
                words.pop(); pad += 1
            spans.append((cur, cur + 4 * (len(words) + pad), pad))
            cur = None
    return sorted(spans)


def island_probe(ov, func):
    """Classify how FUNC's jump tables become bankable in OV — READ-ONLY, nothing is written.

    Returns (kind, detail). Kinds and the lane that owns each (R43):
      'tail'           — table(s) in the data tail: the standard §8a carve; harvest_verify's
                         gate-time `_jtbl_prep_one` handles it (merge / auto-isolate included).
      'covered'        — §260 island split already in place (piece named for the fn's own
                         isolated object, extent == the fn's table span): the carve is a no-op.
      'island-end'     — §154-A leading-island table that is END-ADJACENT (its span abuts the
                         next config piece): the automated §260 split (jr_isolate_all --only +
                         `--island-split`) reaches it — harvest_verify does this at gate time.
      'island-blocked' — an island table with ANOTHER owner's bytes between it and the next
                         piece. The island is a stack (§260): peel the end-adjacent owner first;
                         this member becomes 'island-end' after that owner banks.
      'island-pads'    — the migrated table carries a trailing pad word, or multiple tables
                         with a 4-mod-8 interior boundary: needs §8e JTBL_PADS, which
                         config/modules.mk is not wired for. A named wall, not a lane.
      'main-manual'    — main is parked off the automated path (its gate is a whole-EXE clean
                         rebuild that bisects); route through tools/gate_main.py by hand.
      'no-jtbl' / 'mixed' / 'error' — see detail.

    R32 — what this classifier does and does NOT guarantee: it decides the STRUCTURAL class
    only (which mechanism can reach the table). It does not predict that the carve will
    succeed — §61b proved same-subseg contiguity is only detectable with the body spliced, so
    span-fit/table-count-drift refusals still surface at gate time, honestly, as CARVE-REFUSED."""
    if ov == "main":
        return ("main-manual",
                "main jtbl functions are parked: gate = tools/gate_main.py (whole-EXE clean "
                "rebuild, off the automated lane per the S59 decision); isolation is also "
                "unported for main (jr_isolate_all reads config/splat.main.yaml, which does "
                "not exist)")
    try:
        sub, js = func_jtbls(ov, func)
        if not js:
            return ("no-jtbl", f"{func} references no jtbl_")
        base = overlay_vram_base(ov)
        _, _, _, _, tail_start, _, _, existing = parse_config(ov)
        offs = sorted(int(j, 16) - base for j in js)
        # TAIL-COVERED (S74, byte-proven on ov_SC07_002/func_80180248, sha fad71342…).
        # A carve piece is bound to a code SUBSEG, not to one function, so once ANY function in
        # that subseg is banked the piece can already SPAN a sibling's table: spimdisasm migrates
        # the sibling's still-raw table into its own stub `.s` as `.section .rodata`, the stub's
        # INCLUDE_ASM `.include`s it into the same object in source (= address) order, and the
        # piece is filled exactly. Banking that sibling swaps a migrated `.align 3` + table for
        # cc1's identical `.align 3` + table at the same object offset — nothing to carve.
        #
        # The old code called this 'tail' (its tables' ADDRESSES are in the tail region — true)
        # and routed it to build_carve, which resolves spans out of the RAW data asm and dies
        # `jtbl_… not found in the raw data asm — already carved / stale asm?`. harvest_verify
        # then books CARVE-REFUSED: a verdict about the ROUTE, on a function that needs no carve
        # (R43). Measured: func_80180248 banks with ZERO config change, clean-rebuild SHA green.
        #
        # PADS ARE THE ONE WALL: if the migrated table carries a trailing `.word 0` (§8a-pad), a
        # matched body re-emits only the real entries and the piece under-fills — same refusal the
        # island path makes. Say so instead of routing it anywhere.
        cov = [o for o in offs if any(s <= o < e and sub == _sub for (s, e, _sub) in existing)]
        if cov and len(cov) == len(offs):
            pw = sum(p for _s, _e, p in _migrated_spans(ov, func))
            if pw:
                return ("covered-tpad",
                        "the fn's table already sits inside its own subseg's carve, BUT its "
                        "retail copy carries %d trailing pad word(s) (§8a-pad) that the stub's "
                        "migrated block supplies and a matched body will not — cc1 re-emits only "
                        "the real entries, so the piece under-fills by %d bytes. BANKABLE, and "
                        "byte-proven (ov_SC06_029/func_80182ED8): add this object's cc1 table to "
                        "its JTBL_PADS spec with the trailing token `0t%d`. jtbl_carve does not "
                        "yet DERIVE a mixed (cc1 + migrated) span's spec, so that entry is a hand "
                        "step today — named rather than mis-routed (R43)." % (pw, 4 * pw, pw))
            # PAD CAVEAT, stated because it is NOT always zero-config. spimdisasm emits the
            # migrated block's `.align 3` ONLY when the table's SPAN-RELATIVE offset is 8-aligned
            # (measured: jtbl_80113ED8 span+0x0 got one, jtbl_80113F14 span+0x3c and jtbl_80113F8C
            # span+0xb4 got none); cc1 emits `.align 3` before EVERY table. So a covered table at a
            # 4-mod-8 span offset GAINS 4 bytes when it banks unless the object's §8e JTBL_PADS
            # spec pins it to 0 — and any object that already HAS a spec needs one more entry for
            # the new cc1 table whatever its alignment (the filter consumes every cc1 `.align 3`
            # and refuses on count drift, loudly, at build time).
            _cs = min(s for (s, e, _x) in existing if s <= offs[0] < e)
            _need = [o - _cs for o in offs if (o - _cs) % 8 == 4]
            return ("covered",
                    "table(s) already inside the existing `.rodata` carve bound to this fn's own "
                    "subseg '%s' — the CARVE is a NO-OP; cc1 re-emits the same table where the "
                    "stub's migrated copy sits.%s" % (
                        sub,
                        (" PADS: span offset(s) %s are 4 mod 8, so cc1's `.align 3` adds 4 bytes "
                         "the stub had not — pin them with a JTBL_PADS `0` entry on this object "
                         "(and every object that already has a spec needs one more entry per new "
                         "cc1 table)." % ", ".join("+0x%x" % r for r in _need)) if _need else
                        " No pad entry needed (every table is 8-aligned within the span), unless "
                        "the object already carries a JTBL_PADS spec — then it needs one more "
                        "entry for the new cc1 table."))
        if cov:
            return ("mixed", "some tables already inside this subseg's carve and some still raw "
                             "in the data tail — no precedent (R32); refuse rather than half-carve")
        if all(o >= tail_start for o in offs):
            return ("tail", "table(s) in the data tail — standard §8a carve at gate time")
        if any(o >= tail_start for o in offs):
            return ("mixed", "tables in BOTH the leading island and the data tail — no "
                             "precedent (R32); refuse rather than half-carve")
        spans = _migrated_spans(ov, func)
        if not spans:
            return ("error", "island table referenced but no migrated dlabel in the fn's .s")
        if any(p for _, _, p in spans):
            return ("island-pads", "migrated table carries trailing pad word(s) — a matched "
                                   "body re-emits only real entries; needs §8e pads for "
                                   "modules.mk (not wired)")
        lo, hi = min(s for s, _, _ in spans), max(e for _, e, _ in spans)
        if sum(e - s for s, e, _ in spans) != hi - lo:
            return ("island-pads", "the fn's tables are not tight-contiguous in the island")
        if len(spans) > 1 and any(s % 8 == 4 for s, _, _ in spans[1:]):
            return ("island-pads", "multi-table span with a 4-mod-8 interior boundary — cc1's "
                                   ".align 3 would pad where the island is tight (§8e law 5)")
        # config pieces at/after the span: is the split already there, or is the span end-adjacent?
        pieces = []
        for ln in open(cfg_path(ov)):
            m = PIECE_RE.match(ln)
            if m:
                pieces.append((int(m.group(2), 16), m.group(3), m.group(4)))
        pieces.sort()
        at_lo = [p for p in pieces if p[0] == lo]
        nxt = next((p for p in pieces if p[0] > lo), None)
        if at_lo:
            off, kind, name = at_lo[0]
            if kind == ".rodata" and name == sub and nxt and nxt[0] == hi:
                return ("covered", f"§260 split in place: `- [{hex(lo)}, .rodata, {sub}]`, "
                                   f"extent {hex(hi - lo)} == the fn's table span")
            return ("error", f"a piece already sits at {hex(lo)} ({kind}, {name}) but does not "
                             f"cover the fn's span as its own object — inspect by hand")
        if nxt is None or nxt[0] != hi:
            return ("island-blocked",
                    f"table span {hex(lo)}..{hex(hi)} does not abut the next piece "
                    f"(at {hex(nxt[0]) if nxt else '?'}) — another owner's island bytes sit "
                    f"between; §260: the island peels from the END, peel that owner first")
        return ("island-end",
                f"span {hex(lo)}..{hex(hi)} abuts the next piece — the §260 split reaches it "
                f"(jr_isolate_all --only {func}, then --island-split; automated in "
                f"harvest_verify._jtbl_prep_one)")
    except SystemExit as e:                     # helpers fail loud; the probe reports, not dies
        return ("error", str(e)[:300])


def island_split(ov, func):
    """§260: insert the ONE config line that peels FUNC's island table into its own object.

    Preconditions (both checked, both named on refusal — R43):
      * island_probe says 'island-end' (or 'covered' — then this is an idempotent no-op), and
      * FUNC already owns an isolated `<ov>_jr_<ADDR>` code subseg (jr_isolate_all --only) —
        the inserted piece binds by NAME to that object (the §8a dotted-subseg law), and
        inserting before the isolation would make jr_inventory's carve-ownership check abort
        UNOWNED on the next isolation in this binary.

    Writes ONLY config/splat.<ov>.yaml (one inserted line). No overlays.mk var (a single-table
    piece needs none — §8e), no extract (the caller extracts). The island piece at 0x0 is left
    untouched: its extent shrinks automatically (end = next piece's offset) — the review-proven
    correction to the `_pre` design (docs/tool-designs/jtbl-island-split-review.md #7)."""
    kind, detail = island_probe(ov, func)
    if kind == "covered":
        print(f"jtbl_carve --island-split {ov} {func}: already split — no-op ({detail})")
        return
    if kind != "island-end":
        sys.exit(f"jtbl_carve --island-split: {ov}/{func} is '{kind}', not 'island-end' — "
                 f"{detail}")
    sub = func_subseg(ov, func)
    want = f"{ov}_jr_{int(func[len('func_'):], 16):08X}"
    if sub != want:
        sys.exit(f"jtbl_carve --island-split: {func} still lives in code subseg '{sub}', not its "
                 f"own '{want}' — run `tools/jr_isolate_all.py {ov} --only {func}` first "
                 f"(harvest_verify._jtbl_prep_one does this automatically at gate time)")
    spans = _migrated_spans(ov, func)
    lo = min(s for s, _, _ in spans)
    size = sum(e - s for s, e, _ in spans)
    lines = open(cfg_path(ov)).read().splitlines()
    ins_at, indent = None, "      "
    for i, ln in enumerate(lines):
        m = PIECE_RE.match(ln)
        if not m:
            continue
        off = int(m.group(2), 16)
        indent = m.group(1)
        if off < lo:
            ins_at = i + 1                  # after the last piece that precedes the span
        elif ins_at is not None:
            break
    if ins_at is None:
        sys.exit(f"jtbl_carve --island-split: no config piece precedes offset {hex(lo)} in "
                 f"{cfg_path(ov)} — layout not the §154-A island shape")
    new = f"{indent}- [{hex(lo)}, .rodata, {sub}]   # §154-A island split (jtbl_carve --island-split)"
    lines.insert(ins_at, new)
    open(cfg_path(ov), "w").write("\n".join(lines) + "\n")
    print(f"jtbl_carve --island-split {ov}: inserted `- [{hex(lo)}, .rodata, {sub}]` (§260).")
    print(f"  object-level discriminator after the build (a green SHA alone cannot tell a split "
          f"that WORKED from one that did nothing — §260): {sub}.o .rodata sh_size == {hex(size)} "
          f"and {ov}.o's .rodata shrinks by exactly {hex(size)}.")


def parse_config(ov, lines=None):
    """Parse the flat-overlay config's tail data region.

    `lines` overrides the on-disk text (used by revert() to run the SAME region derivation over the
    COMMITTED config — one derivation, two callers; never a second regex model of the same file).

    Returns (lines, indent, region_lo_idx, region_hi_idx, tail_start, region_end, trailing_present,
             existing_carves) where:
      - lines: the config file split into lines.
      - region_lo_idx..region_hi_idx: the [inclusive, exclusive) line range of the `- [...]` data/
        rodata PIECE lines to replace (the `bin,trailing` + EOF lines stay).
      - tail_start / region_end: file offsets bounding the regenerated data region.
      - trailing_present: whether a `[off, bin, trailing]` piece caps the region.
      - existing_carves: [(start_off, end_off, subseg), ...] for the `.rodata` carves already present.
    """
    lines = open(cfg_path(ov)).read().splitlines() if lines is None else list(lines)
    pieces = []   # (idx, indent, off, kind, name)
    eof_off = None
    for i, ln in enumerate(lines):
        m = PIECE_RE.match(ln)
        if m:
            pieces.append((i, m.group(1), int(m.group(2), 16), m.group(3), m.group(4)))
            continue
        e = EOF_RE.match(ln)
        if e:
            eof_off = int(e.group(1), 16)
    # THE DATA REGION IS THE TRAILING RUN AFTER THE LAST `c` PIECE. That is what this docstring
    # has always claimed and what apply()'s splice `lines[:lo] + region + lines[hi:]` requires;
    # until P31 S59 the code took `data_pieces[0]` — the first data/.rodata piece ANYWHERE in the
    # file — and the two agree only by accident of layout:
    #   * 171 configs (every ov_*, main, resident) are [all c pieces ... , data tail] -> same line.
    #   * 42 md_* configs open with the §154-A LEADING ISLAND `- [0x0, .rodata, md_XXX]` BEFORE
    #     their `c` piece -> region_lo_idx pointed at the island, and the splice DELETED the `c`
    #     line, corrupting the yaml ON DISK before the tool errored out for unrelated reasons.
    # Deriving the region from the last `c` makes the contract true for both layouts, and leaves a
    # leading island where it belongs: outside the region this function describes.
    c_idxs = [q[0] for q in pieces if q[3] == "c"]
    last_c = c_idxs[-1] if c_idxs else -1
    data_pieces = [q for q in pieces if q[3] in ("data", ".rodata") and q[0] > last_c]
    if not data_pieces:
        sys.exit(f"jtbl_carve: no data/.rodata region after the last `c` piece in {cfg_path(ov)}")
    region_lo_idx = data_pieces[0][0]
    indent = data_pieces[0][1]
    tail_start = data_pieces[0][2]
    # Where the regenerated pieces stop: the trailing bin piece, else the EOF marker.
    trailing = [p for p in pieces if p[3] == "bin" and p[4] == "trailing"]
    if trailing:
        region_hi_idx = trailing[0][0]
        region_end = trailing[0][2]
        trailing_present = True
    else:
        if eof_off is None:
            sys.exit(f"jtbl_carve: no trailing bin and no EOF marker in {cfg_path(ov)}")
        # region_hi_idx = the EOF marker line index
        region_hi_idx = next(i for i, ln in enumerate(lines) if EOF_RE.match(ln))
        region_end = eof_off
        trailing_present = False
    # R43 GUARD, not an assumption. Everything downstream REWRITES [region_lo_idx, region_hi_idx)
    # wholesale, so a `c` piece inside that window is destroyed source configuration, not a bad
    # carve. The derivation above cannot produce one; this fires if a future layout, or an edit to
    # that derivation, ever reintroduces the md_* corruption.
    inside = [i for i in c_idxs if region_lo_idx <= i < region_hi_idx]
    if inside:
        sys.exit(f"jtbl_carve: REFUSING {ov} — `c` piece(s) at line(s) "
                 f"{[i + 1 for i in inside]} lie inside the data region "
                 f"[{region_lo_idx + 1}, {region_hi_idx + 1}) that apply() rewrites wholesale. "
                 f"Rewriting it would delete them from {cfg_path(ov)}.")
    # Existing .rodata carves: end = the following piece's off (or region_end for the last).
    region = [p for p in data_pieces if region_lo_idx <= p[0] < region_hi_idx]
    existing = []
    for j, (_, _, off, kind, name) in enumerate(region):
        if kind == ".rodata":
            end = region[j + 1][2] if j + 1 < len(region) else region_end
            existing.append((off, end, name))
    return lines, indent, region_lo_idx, region_hi_idx, tail_start, region_end, trailing_present, existing


def build_carve(ov, funcs):
    """Return (region_lines, order_arg, pads_map): the regenerated data-region `- [...]` piece
    lines, the `ld_interleave --order` object list, and {subseg: [pad,...]} for every carve span,
    for the accumulated carve set (existing + the new funcs)."""
    base = overlay_vram_base(ov)
    (_, indent, _, _, tail_start, region_end, trailing_present, existing) = parse_config(ov)
    region_end_vram = base + region_end

    # carves: (start_off, end_off, subseg). Existing ones come from the config (already migrated).
    carves = list(existing)
    have = {c[0] for c in carves}
    # A new jtbl's end is bounded by the next RAW data dlabel OR the next EXISTING carve start
    # (an already-carved adjacent jtbl is gone from the data asm, so the raw dlabels alone would
    # over-extend the new jtbl past it — the merge would then see an overlap, not an abutment).
    labels = sorted(set(all_data_labels(ov)) | {base + c[0] for c in existing})
    for f in funcs:
        sub, js = func_jtbls(ov, f)
        if not js:
            sys.exit(f"jtbl_carve: {f} references no jtbl_ (not a jr/switch function?)")
        for jh in js:
            # ISLAND CHECK FIRST, from the table's OWN address — before jtbl_range, which resolves
            # the span out of the RAW data asm and therefore reports an island table as "not found
            # in asm/<ov>/data/*.data.s — already carved / stale asm?". That message is true and
            # useless: an island table was never in the data asm, it is INCLUDE_RODATA'd from the
            # module's leading `.rodata` piece, and re-extracting will never produce it.
            #
            # A table BELOW the data region cannot be reached by a tail carve at all: apply() only
            # rewrites [tail_start, region_end), so the piece line would land out of address order
            # and splat would mis-slice the module. That is the island-split lane's job — ONE
            # inserted `.rodata` line at the table's own offset plus jr_isolate_all.py --only
            # (docs/tool-designs/jtbl-island-split-review.md) — so name it and refuse (R43).
            isl_off = int(jh, 16) - base
            if isl_off < tail_start:
                sys.exit(
                    f"jtbl_carve: {f}'s jtbl_{jh} at file 0x{isl_off:x} is BELOW {ov}'s data "
                    f"region (starts 0x{tail_start:x}) — it lives in the §154-A leading .rodata "
                    f"island, which a tail carve cannot reach. That is the island split (§260): "
                    f"jr_isolate_all.py --only {f}, then `jtbl_carve.py {ov} --island-split "
                    f"--func {f}` — automated at gate time by harvest_verify._jtbl_prep_one "
                    f"(docs/tool-designs/jtbl-island-split-review.md).")
            s_vram, e_vram = jtbl_range(ov, jh, labels, region_end_vram, fn=f, sub=sub)
            s_off, e_off = s_vram - base, e_vram - base
            if s_off in have:
                continue                       # idempotent: already carved
            carves.append((s_off, e_off, sub))
            have.add(s_off)
    carves.sort()

    # A code object emits its jtbls CONTIGUOUS in .rodata (gcc source order). So two carves in the
    # SAME subseg are byte-correct only if ADJACENT in the island — where "adjacent" is abutting
    # (gap 0) OR separated by exactly one original `.align 3` pad word (gap 4, verifiably zero in
    # the payload; Phase-29 §8e) -> merge them into one spanning .rodata piece. Any other
    # same-subseg gap is unsatisfiable (a single object can't leave a hole for the raw jtbl
    # between) -> isolate one fn into its own subseg (jr_isolate_all.py).
    merged = []
    for s_off, e_off, sub in carves:
        if merged and merged[-1][2] == sub:
            gap = s_off - merged[-1][1]
            if gap in (0, 4):
                if gap == 4:
                    w = payload_word(ov, merged[-1][1])
                    if w != 0:
                        sys.exit(
                            f"jtbl_carve: the 4-byte gap at 0x{merged[-1][1]:x} between same-subseg "
                            f"carves is 0x{w:08x}, not a zero .align pad word — treating as "
                            f"NON-CONTIGUOUS. Isolate one matched jr-function into its own code "
                            f"subseg first (tools/jr_isolate_all.py), then re-carve.")
                merged[-1] = (merged[-1][0], e_off, sub)
                continue
        merged.append((s_off, e_off, sub))
    seen_subsegs = {}
    for s_off, _, sub in merged:
        if sub in seen_subsegs:
            sys.exit(
                f"jtbl_carve: subseg '{sub}' would host NON-CONTIGUOUS .rodata carves "
                f"(0x{seen_subsegs[sub]:x} and 0x{s_off:x}) — a single object can't leave a gap for the "
                f"unmatched jtbl between them. Isolate one matched jr-function into its own code subseg "
                f"first (tools/jr_isolate_all.py, the whale `_o0b` precedent), then re-carve.")
        seen_subsegs[sub] = s_off
    carves = merged

    # Per-span pad specs (spec, rel_starts), source priority per span:
    #   (a) UNTOUCHED this run + an existing overlays.mk line -> reuse verbatim (byte-gated when
    #       written; its tables= comment is the durable starts record).
    #   (b) touched/new span -> table starts = union of {the new fn's .s refs, any surviving
    #       stub .s refs, the existing line's tables= (rebased on the old span start),
    #       --span-tables override, --like <exemplar-ov> role-transfer} -> pads by the payload
    #       zero-word rule (spec_from_starts). Matched owners' stub .s are PRUNED by extract, so
    #       persistence (tables=) + the --like transfer are what make sibling sweeps possible
    #       (the func_8013F350 lesson: a pre-§8e Phase-26 merged double had NO recoverable
    #       structure — interval carry mis-defaulted it to [0]).
    def _like_role_matches(ov_name, sub_name, fns):
        """Is the `--like` role-transfer VALID for this subseg? (Phase 29 SESSION-21)

        The transfer's premise is "same family => same span structure", and it keys on the SUBSEG
        ROLE (`ov_SC01_077_a` -> `_a`). That premise silently breaks when the exemplar and the
        sibling host the function in subsegs with DIFFERENT roles — which happens whenever the
        exemplar has a split the sibling does not.

        MEASURED (func_8012AAAC): the exemplar hosts it in `ov_SC01_077_a` (role `_a`) while every
        sibling hosts it in the MAIN subseg (role ``). The transfer therefore looked up
        `ov_SC01_077` — an unrelated 7-table span belonging to different functions — and stamped
        those starts onto a sibling span that holds one table. The pad stage then refused with
        `consumed 1 rodata .align(s) but 2 pad spec(s) given — table-count drift`, and
        jtbl_family_bank deliberately does NOT treat that error as isolate-fixable, so all 137
        siblings returned a bare `gate-fail` with no cause attached.

        So: transfer ONLY when the exemplar's subseg for THIS function has the sibling's role.
        Otherwise derive the span locally, which is what the sibling's own carve already computes
        correctly. Fail-open is not acceptable here — a wrong table set corrupts the image."""
        if not LIKE_OV:
            return False
        want = role(sub_name, ov_name)
        for f in fns:
            try:
                if role(func_subseg(LIKE_OV, f), LIKE_OV) == want:
                    return True
            except SystemExit:
                continue                       # not present in the exemplar — cannot vouch for it
        return False

    prior_map = current_pads_specs(ov)
    old_span_start = {sub: s for (s, _e, sub) in existing}   # pre-merge span starts (for rebase)
    new_offs = {}                                            # sub -> new table offs added this run
    for f in funcs:
        sub_f, js_f = func_jtbls(ov, f)
        for jh in js_f:
            new_offs.setdefault(sub_f, set()).add(int(jh, 16) - base)
    like_map = current_pads_specs(LIKE_OV) if LIKE_OV else {}

    def role(sub_name, ov_name):
        return sub_name[len(ov_name):] if sub_name.startswith(ov_name) else sub_name

    pads_map = {}
    for s_off, e_off, sub in carves:
        touched = any(s_off <= o < e_off for o in new_offs.get(sub, ()))
        prior = prior_map.get(sub)
        if not touched:
            if prior is not None:
                pads_map[sub] = prior                        # (a) reuse verbatim
            # untouched + no line = a pre-§8e span whose natural `.align 3`s are already
            # byte-correct (it is committed green) — leave it unfiltered, reconstruct nothing.
            continue
        s_vram = base + s_off
        starts = {base + o for o in new_offs.get(sub, ()) if s_off <= o < e_off}
        starts.update(a for a in overlay_jtbl_addrs(ov) if s_vram <= a < base + e_off)
        if prior is not None and prior[1] is not None and sub in old_span_start:
            starts.update(base + old_span_start[sub] + r for r in prior[1])
        elif sub in old_span_start:
            # P31 S75 — WIDENED from `prior is None`: a JTBL_PADS line WITHOUT a `tables=` comment
            # (written by jtbl_pads_fix, or predating persistence) used to fall through BOTH
            # branches, so the existing table's start was lost and the merge refused with "first
            # must equal the span start" — which harvest_verify then "fixed" with a needless
            # jr_isolation (measured ov_SC01_005+006/func_8017F2D4: `JTBL_PADS := 0  # ... 1
            # table(s), byte-proven by jtbl_pads_fix`). The invariant is the same one the
            # validator asserts: EVERY carve span begins with a table, so its start is always a
            # known start whatever the line says. Interior starts of a no-`tables=` multi-table
            # span stay recoverable only by the payload zero-word rule (below), and the build-time
            # count guard remains the loud backstop.
            # SINGLE-TABLE PREDECESSOR (Phase 29 SESSION-21). A span with no overlays.mk line was a
            # SINGLE-table carve — "Single-table carves get NO var" — and a single-table carve spans
            # exactly its one table, so ITS SPAN START *IS* THAT TABLE'S START. Adding a second table
            # to such a subseg otherwise loses the first one entirely: `new_offs` has only the new
            # table, `overlay_jtbl_addrs` cannot see the old one (its owner is banked, so extract
            # PRUNED the stub .s that referenced it), and there is no `tables=` to rebase. The span
            # then fails its own validator with "first must equal the span start" — which is the
            # invariant naming the missing entry.
            #
            # This is the recoverable half of the documented func_8013F350 lesson: that case was a
            # pre-§8e MERGED double (two tables, no record, genuinely unrecoverable); a single-table
            # predecessor needs no record because its start is implied by its span. Inference, not
            # persistence — so it also works for spans carved before tables= existed.
            starts.add(base + old_span_start[sub])
        if sub in SPAN_TABLES_OVERRIDE:
            starts.update(SPAN_TABLES_OVERRIDE[sub])
        if LIKE_OV and _like_role_matches(ov, sub, funcs):
            lk = like_map.get(LIKE_OV + role(sub, ov))
            if lk is not None and lk[1] is not None:
                # role-transfer: same family => same span structure; rebase rel offsets on THIS
                # span's start. The local payload zero-word rule still derives the pads honestly.
                starts.update(s_vram + r for r in lk[1])
        pads_map[sub] = spec_from_starts(ov, base, s_off, e_off, sorted(starts))

    # Walk the region [tail_start, region_end), emitting a `data` piece before each carve.
    pieces = []          # (off, kind, name)
    order = []           # object leaves for --order, in address order
    cursor = tail_start
    n_data = 0
    def data_name():
        nonlocal n_data
        n_data += 1
        return "tail" if n_data == 1 else f"tail{n_data}"
    for s_off, e_off, sub in carves:
        if cursor < s_off:
            nm = data_name()
            pieces.append((cursor, "data", nm))
            order.append(f"{nm}.data.o")
        pieces.append((s_off, ".rodata", sub))
        order.append(f"{sub}.o")
        cursor = e_off
    if cursor < region_end:
        nm = data_name()
        pieces.append((cursor, "data", nm))
        order.append(f"{nm}.data.o")
    if trailing_present:
        order.append("trailing.o")

    region_lines = []
    for off, kind, name in pieces:
        comment = "  # Phase-26 §8 jtbl-rodata carve (jtbl_carve.py)" if kind == ".rodata" else ""
        region_lines.append(f"{indent}- [{hex(off)}, {kind}, {name}]{comment}")
    return region_lines, "--order " + ",".join(order), pads_map


def migrated_tables(ov, funcs):
    """The subset of `funcs` whose jump tables are ALREADY inside the code object — nothing to carve.

    §154-A LAYOUT (P30 S48). A module binary binds its `.rodata` island to the SAME subseg as its
    code (`- [0x0, .rodata, md_SC03_076]` + `- [0x27C, c, md_SC03_076]`), so spimdisasm MIGRATES each
    referenced table into its owning function's `.s` instead of leaving it in `asm/<bin>/data/*.data.s`.
    There is then no table to move: when the function is matched its `.s` is pruned and the C emits
    the table into the same object's `.rodata`, at the same address, by construction.

    The carve nonetheless ran and died with `jtbl_… not found in the raw data asm`, which
    `harvest_verify` correctly turns into CARVE-REFUSED and never builds — so **every jr member of
    every family that lands in a module is unbankable**, with a verdict that names the tool rather
    than the layout (12 slots in the S48 wave-1 propagation alone; no module has ever banked a jr
    function, so nothing contradicted it).

    A carve is a no-op here, NOT a refusal. Detection is by evidence, not by binary-name prefix:
    the table is absent from the data asm AND present as a `dlabel` in the function's own `.s`.
    A function with SOME tables migrated and some not is a layout we have never seen — refuse loud
    (R32) rather than half-carve."""
    data_labels = set(all_data_labels(ov))
    migrated = []
    for f in funcs:
        sub, js = func_jtbls(ov, f)
        if not js:
            continue
        p = os.path.join(asm_dir(ov), "nonmatchings", sub, f"{f}.s")
        if not os.path.exists(p):
            stale = sorted(glob.glob(os.path.join(asm_dir(ov), "nonmatchings", "*", f"{f}.s")))
            p = stale[0] if stale else None
        own = set()
        if p:
            own = {m.group(1).lower() for m in
                   re.finditer(r"^\s*dlabel\s+jtbl_([0-9A-Fa-f]{8})", open(p).read(), re.M)}
        in_data = [j for j in js if int(j, 16) in data_labels]
        in_own = [j for j in js if j.lower() in own]
        if in_own and not in_data:
            migrated.append(f)
        elif in_own and in_data:
            if set(in_data) == set(js):
                # EVERY table the fn references is still in the data asm: the own-.s copy is
                # spimdisasm's post-ISOLATION migration (a fresh, small c-segment re-associates the
                # table with its function) while the tail piece has not been carved yet. That is the
                # standard tail state, not a half-migrated layout — carve the tail as usual; the
                # re-extract after the carve resolves the duplicate. (P31 S62 T3: 9 gate-time
                # CARVE-REFUSED drafts — ov_SC03_107/ov_SC02_037/ov_MAIN_012 func_8015444C et al. —
                # were exactly this after jr_isolate_all.)
                print(f"jtbl_carve: {f}: tables {in_data} in the data asm AND migrated into its own .s "
                      f"(post-isolation) — treating as tail")
                continue
            sys.exit(f"jtbl_carve: {f} has tables in BOTH the data asm ({in_data}) and its own .s "
                     f"({in_own}) — refusing to half-carve a layout we have no precedent for (R32)")
    return migrated


def apply(ov, funcs):
    # S74: a batch whose tables are ALREADY inside their own subseg's carve needs no carve at all
    # (tail-covered or the §260 island split). Checked FIRST, because both of the routes below
    # resolve spans out of the RAW data asm and a covered table is no longer there — they would
    # refuse a function that is bankable as it stands (R43: name the state, do not mis-route it).
    _cov = {f: island_probe(ov, f) for f in funcs}
    if all(k == "covered" for k, _d in _cov.values()):
        for f in funcs:
            print(f"jtbl_carve {ov}: {f} — {_cov[f][1]}. Nothing to carve (no-op OK).")
        return
    _walls = {f: kd for f, kd in _cov.items() if kd[0] == "covered-tpad"}
    if _walls:
        sys.exit("jtbl_carve: %s — %s" % (sorted(_walls),
                 "; ".join(d for _k, d in _walls.values())))

    mig = migrated_tables(ov, funcs)
    # THE PROBE OVERRIDES THE CLASSIFIER FOR 'tail' (P31 S70). `migrated_tables` can flag a function
    # whose table is actually in the DATA TAIL, and the island branch below then refuses the whole
    # batch — even though `island_probe` classifies it 'tail' and its own detail says "standard §8a
    # carve at gate time", i.e. it names the ordinary lane as the owner (R43: each kind names its
    # lane). That refusal reads as a permanent wall while the function is simply in the wrong branch:
    # measured on ov_SC02_000/func_8017F950, which is 'tail' yet died on the LEADING-ISLAND exit.
    # Consult the probe FIRST and let a tail function fall through to build_carve below.
    if mig:
        _tail = [f for f in mig if island_probe(ov, f)[0] == "tail"]
        if _tail:
            print(f"jtbl_carve {ov}: {sorted(_tail)} probe as 'tail' (data-tail table) — routing to "
                  f"the standard §8a carve, not the §154-A island branch")
            mig = [f for f in mig if f not in _tail]
    if mig:
        # §154-A migrated tables. Two states, byte-distinguished by island_probe:
        #   * 'covered' — the §260 island split is IN PLACE (the fn is isolated into its own
        #     `_jr_` object and a same-named `.rodata` piece spans exactly its tables). Then the
        #     carve is genuinely a NO-OP: stub state migrates the table into the jr object's .s,
        #     matched state has cc1 emit the same table into the same object at the same offset
        #     (single table at section offset 0 — `.align 3` pads nothing). Byte-proven on
        #     md_SC03_076/func_801F218C (sha 9a165e36…, jr .rodata 0x14 / md .rodata 0x268).
        #   * anything else — the historical refusal below stands. The split IS implemented now
        #     (island_split + jr_isolate_all --only, automated in harvest_verify._jtbl_prep_one),
        #     but it must run BEFORE this carve, and only an END-ADJACENT table can take it
        #     (§260: the island is a stack).
        if set(mig) != set(funcs):
            sys.exit(f"jtbl_carve: {ov}: {sorted(set(funcs) - set(mig))} carve from the data "
                     f"tail while {mig} carry migrated island tables — no precedent for a mixed "
                     f"batch (R32); carve them in separate invocations")
        uncovered = {}
        for f in mig:
            kind, detail = island_probe(ov, f)
            if kind != "covered":
                uncovered[f] = (kind, detail)
        if not uncovered:
            for f in mig:
                print(f"jtbl_carve {ov}: {f} — §260 island split in place; its migrated table "
                      f"IS its own object's .rodata piece already. Nothing to carve (no-op OK).")
            return
        sys.exit(
            f"jtbl_carve: {ov} is a §154-A LEADING-ISLAND binary and {sorted(uncovered)} carry "
            f"MIGRATED tables with no island split in place — a tail carve cannot help (P30 S48, "
            f"byte-measured on md_SC03_076/func_801F0F28).\n"
            + "".join(f"    {f}: {k} — {d}\n" for f, (k, d) in sorted(uncovered.items()))
            + f"  WHY: the module binds `.rodata` at 0x0 to the SAME subseg as its code, so the object's\n"
            f"  rodata order is the C file's include chain — INCLUDE_RODATA pieces, then each\n"
            f"  INCLUDE_ASM'd function's migrated table, in address order. That reproduces the island\n"
            f"  exactly WHILE THE FUNCTION IS A STUB. Matching it PRUNES its .s, so its table leaves the\n"
            f"  chain and cc1 re-emits it at the END of the object's .rodata — 8 bytes of growth and\n"
            f"  every later symbol shifted (build 43,768 vs 43,760 bytes; first diff at 0x144, inside\n"
            f"  the island's own pointer table).\n"
            f"  WHAT WORKS (§260, byte-proven; AUTOMATED in harvest_verify._jtbl_prep_one): for an\n"
            f"  END-ADJACENT table, `jr_isolate_all.py {ov} --only <fn>` then\n"
            f"  `jtbl_carve.py {ov} --island-split --func <fn>`, re-extract, and re-run this carve\n"
            f"  (it then reports the no-op). A NON-end-adjacent table waits its turn on the stack.\n"
            f"  JTBL_PADS alone does NOT reach it: `jtbl_rodata_pads` refuses this object outright — "
            f"  'unexpected rodata content .include \"…/D_801EF468.s\"' — because the carve model covers\n"
            f"  jump tables only, not an island of mixed included data.")
    region_lines, order_arg, pads_map = build_carve(ov, funcs)
    lines, indent, lo, hi, *_ = parse_config(ov)
    new_lines = lines[:lo] + region_lines + lines[hi:]
    open(cfg_path(ov), "w").write("\n".join(new_lines) + "\n")
    set_overlays_var(ov, order_arg)
    set_pads_vars(ov, pads_map)
    multi = {s: p[0] for s, p in pads_map.items() if len(p[0]) > 1}
    print(f"jtbl_carve {ov}: carve set = {len(region_lines)} pieces; JTBL_INTERLEAVE = {order_arg}"
          + (f"; JTBL_PADS = {multi}" if multi else ""))


def set_overlays_var(ov, args):
    mk = os.path.join(REPO, "config/overlays.mk")
    txt = open(mk).read()
    _mk_base = txt
    var = f"{ov}_JTBL_INTERLEAVE := {args}  # Phase-26 §8 jtbl-rodata carve"
    if re.search(rf"^{re.escape(ov)}_JTBL_INTERLEAVE\b", txt, re.M):
        txt = re.sub(rf"^{re.escape(ov)}_JTBL_INTERLEAVE.*$", var, txt, count=1, flags=re.M)
    else:
        # insert right after the overlay's SPLAT_YAML line
        anchor = f"{ov}_SPLAT_YAML := config/splat.{ov}.yaml"
        if anchor not in txt:
            sys.exit(f"jtbl_carve: no {anchor} anchor in overlays.mk")
        txt = txt.replace(anchor, anchor + "\n" + var, 1)
    MKW.write_overlays_mk(txt, path=mk, base=_mk_base)


def set_pads_vars(ov, pads_map):
    """Write this overlay's per-object JTBL_PADS lines (Phase-29 §8e), preserving carried values.

    Only multi-table spans (len(spec) > 1) get a line; single-table spans get none (their pipeline
    stays byte-identical to pre-§8e). All of this overlay's current pads lines are replaced by the
    regenerated block as one unit (values were CARRIED into pads_map by current_pads_specs, so this
    is a rewrite of the same state plus the new boundary — not a re-derivation). Any object whose
    spec appears, changes, or disappears gets its stale build/src/<ov>/<sub>.o deleted: the spec is
    no make-prerequisite, and a padless stale object would fail the SHA gate mystifyingly."""
    mk = os.path.join(REPO, "config/overlays.mk")
    txt = open(mk).read()
    _mk_base = txt
    before = current_pads_specs(ov, txt)
    after = {sub: sr for sub, sr in pads_map.items() if len(sr[0]) > 1}
    # SECOND, DISAGREEING ORACLE (R34; P30 S48). The carry above is keyed by SUBSEG NAME, so a span
    # whose owning object was RENAMED (jr_isolate_all moving it into `<ov>_jr_<addr>`) looks like a
    # span with no prior spec and its line is dropped — silently, and never byte-neutral: the pads
    # exist precisely because cc1's `.align 3` would otherwise pad a non-8-aligned interior table
    # (measured on ov_SC02_037: spec 0,0,0,0 lost => `built, bytes differ`). A spec may legitimately
    # disappear only when its span is re-derived to a single table; if the SUBSEG ITSELF is gone from
    # the carve set, the loss is drift, not derivation. jr_isolate_all now repoints the line with the
    # span, so this should be unreachable — it is here because the failure mode is a silent byte diff.
    live_subs = set(re.findall(r"- \[0x[0-9A-Fa-f]+,\s*\.rodata,\s*(\w+)\]", open(cfg_path(ov)).read()))
    vanished = [s for s in before if s not in after and s not in live_subs]
    if vanished:
        sys.exit(f"jtbl_carve: JTBL_PADS spec(s) for {vanished} would VANISH — their subseg is no "
                 f"longer in {ov}'s carve set, so the spec was not re-derived, it was LOST (R32/R34). "
                 f"If the object was renamed, repoint the line to the new object; if two spans "
                 f"merged, fold the `tables=` starts into the surviving line first.")
    # drop all current lines for this overlay, then insert the regenerated block
    txt = re.sub(pads_line_re(ov) + r"\n", "", txt, flags=re.M)
    if after:
        block = "\n".join(
            f"build/src/{ov}/{sub}.o: JTBL_PADS := {','.join(map(str, spec))}{pads_comment(rel)}"
            for sub, (spec, rel) in sorted(after.items()))
        m = re.search(rf"^{re.escape(ov)}_JTBL_INTERLEAVE.*$", txt, re.M)
        if not m:
            sys.exit(f"jtbl_carve: no {ov}_JTBL_INTERLEAVE line to anchor JTBL_PADS on")
        txt = txt[:m.end()] + "\n" + block + txt[m.end():]
    MKW.write_overlays_mk(txt, path=mk, base=_mk_base)
    for sub in set(before) | set(after):
        if before.get(sub) != after.get(sub):
            obj = os.path.join(REPO, f"build/src/{ov}/{sub}.o")
            if os.path.exists(obj):
                os.remove(obj)
                print(f"jtbl_carve: JTBL_PADS changed for {sub} — removed stale {obj}")


def _revert_yaml_region(ov):
    """Restore ONLY the carve's own data/rodata region in `config/splat.<ov>.yaml` from HEAD.

    WHY NOT `git checkout --` THE FILE (P31 S74, paid for three times in one session). The carve
    owns exactly the trailing `data`/`.rodata` region — the `c` pieces above it are source
    configuration this tool never writes. A blunt checkout cannot tell "carve state I just added"
    from "the §431 TU split someone added to the same uncommitted file", so `--revert` after a
    carve PROBE silently un-split the overlay: three independent agents hit it in one session, and
    each recovered only because they had backed the yaml up by hand first. This is the same
    surgical discipline `revert()` already applies to the SHARED `config/overlays.mk`, and for the
    same reason — the file holds more than this overlay's carve.

    R43 guard: if the committed region carves a `.rodata` onto a subseg the CURRENT config no
    longer has (a split that re-homed a carved subseg), restoring it would produce a config that
    cannot extract — so refuse loudly and name the subseg instead of writing it.
    """
    cur = open(cfg_path(ov)).read().splitlines()
    head = subprocess.run(["git", "-C", REPO, "show", f"HEAD:config/splat.{ov}.yaml"],
                          capture_output=True, text=True)
    if head.returncode != 0:
        sys.exit(f"jtbl_carve: cannot read HEAD:config/splat.{ov}.yaml — {head.stderr.strip()}")
    hl = head.stdout.splitlines()
    _, _, clo, chi, *_ = parse_config(ov, lines=cur)
    _, _, hlo, hhi, *_ = parse_config(ov, lines=hl)
    cur_c = [m.group(4) for m in (PIECE_RE.match(l) for l in cur) if m and m.group(3) == "c"]
    missing = sorted({m.group(4) for m in (PIECE_RE.match(l) for l in hl[hlo:hhi])
                      if m and m.group(3) == ".rodata"} - set(cur_c))
    if missing:
        sys.exit(f"jtbl_carve: REFUSING to revert {ov} — the committed carve region attaches "
                 f".rodata to subseg(s) {missing}, which the current config no longer defines "
                 f"(a §431 split re-homed them). Restoring it would write a config that cannot "
                 f"extract. Reconcile the carve lines with the new subseg names by hand.")
    open(cfg_path(ov), "w").write("\n".join(cur[:clo] + hl[hlo:hhi] + cur[chi:]) + "\n")
    head_c = [m.group(4) for m in (PIECE_RE.match(l) for l in hl) if m and m.group(3) == "c"]
    if cur_c != head_c:
        print(f"jtbl_carve {ov}: PRESERVED {len(cur_c)} uncommitted `c` piece(s) "
              f"(committed: {len(head_c)}) — only the carve region was reverted")


def revert(ov):
    """Restore this overlay's carve state to the COMMITTED one.

    `<ov>_JTBL_INTERLEAVE` must be restored to its committed VALUE, not deleted: every overlay now
    carries a committed carve (134/134 since func_8012ACE0 / func_801734BC banked ×134), so an
    unconditional drop would destroy a banked carve on any failed sweep. And `overlays.mk` is SHARED
    by all 134 overlays, so a blunt `git checkout` of it would wipe the OTHER siblings' in-flight
    vars mid-sweep — hence the surgical, per-overlay line splice."""
    _revert_yaml_region(ov)
    mk = os.path.join(REPO, "config/overlays.mk")
    txt = open(mk).read()
    _mk_base = txt
    committed = subprocess.run(["git", "-C", REPO, "show", "HEAD:config/overlays.mk"],
                               capture_output=True, text=True).stdout
    m = re.search(rf"^{re.escape(ov)}_JTBL_INTERLEAVE.*$", committed, re.M)
    has_now = re.search(rf"^{re.escape(ov)}_JTBL_INTERLEAVE\b", txt, re.M)
    if m and has_now:
        txt = re.sub(rf"^{re.escape(ov)}_JTBL_INTERLEAVE.*$", lambda _: m.group(0), txt,
                     count=1, flags=re.M)
    elif m:                                   # committed var was dropped -> put it back
        anchor = f"{ov}_SPLAT_YAML := config/splat.{ov}.yaml"
        if anchor not in txt:
            sys.exit(f"jtbl_carve: no {anchor} anchor in overlays.mk")
        txt = txt.replace(anchor, anchor + "\n" + m.group(0), 1)
    else:                                     # no committed carve -> drop ours
        txt = re.sub(rf"^{re.escape(ov)}_JTBL_INTERLEAVE.*\n", "", txt, flags=re.M)
    # JTBL_PADS lines (Phase-29 §8e): restore this overlay's per-object pad specs to the committed
    # set with the same surgical splice (a failed sibling bank must not leave its spec behind, and
    # a blunt checkout would wipe OTHER siblings' in-flight lines — overlays.mk is shared).
    now_pads = current_pads_specs(ov, txt)
    committed_pads = current_pads_specs(ov, committed)
    txt = re.sub(pads_line_re(ov) + r"\n", "", txt, flags=re.M)
    committed_lines = [l for l in committed.splitlines()
                       if re.match(pads_line_re(ov), l)]
    if committed_lines:
        m2 = re.search(rf"^{re.escape(ov)}_JTBL_INTERLEAVE.*$", txt, re.M)
        if not m2:
            sys.exit(f"jtbl_carve: no {ov}_JTBL_INTERLEAVE line to anchor committed JTBL_PADS on")
        txt = txt[:m2.end()] + "\n" + "\n".join(committed_lines) + txt[m2.end():]
    MKW.write_overlays_mk(txt, path=mk, base=_mk_base)
    for sub in set(now_pads) | set(committed_pads):
        if now_pads.get(sub) != committed_pads.get(sub):
            obj = os.path.join(REPO, f"build/src/{ov}/{sub}.o")
            if os.path.exists(obj):
                os.remove(obj)
    print(f"jtbl_carve {ov}: reverted config + JTBL_INTERLEAVE restored to committed"
          f"{'' if m else ' (none)'}"
          + (f" + {len(committed_lines)} JTBL_PADS line(s) restored" if committed_lines else ""))


def main():
    global LIKE_OV, SPAN_TABLES_OVERRIDE
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("ov")
    ap.add_argument("--func", action="append", default=[], help="matched jr-function to carve (repeatable)")
    ap.add_argument("--revert", action="store_true", help="restore config from git + drop the var")
    ap.add_argument("--island-split", action="store_true",
                    help="§260: insert the one-line .rodata piece that peels --func's END-ADJACENT "
                         "leading-island table into its own (already-isolated) _jr_ object. "
                         "Idempotent; refuses non-end-adjacent tables (the island is a stack).")
    ap.add_argument("--probe", action="store_true",
                    help="READ-ONLY: classify how --func's tables become bankable "
                         "(tail / covered / island-end / island-blocked / island-pads / …) and exit 0. "
                         "The classifier build_wave_atlas and jtbl_lane use.")
    ap.add_argument("--like", metavar="OV",
                    help="§8e sibling sweep: transfer span table-structure (tables= rel offsets) "
                         "from this exemplar overlay's committed JTBL_PADS lines, role-matched by "
                         "subseg suffix (same family => same structure; pads still derived from "
                         "THIS overlay's payload)")
    ap.add_argument("--span-tables", action="append", default=[], metavar="SUB=A1,A2,..",
                    help="§8e escape hatch: absolute table-start vrams for a span whose owners' "
                         "stub .s are pruned and no persisted tables= exists (pre-§8e archaeology)")
    a = ap.parse_args()
    LIKE_OV = a.like
    for ent in a.span_tables:
        sub, addrs = ent.split("=", 1)
        SPAN_TABLES_OVERRIDE[sub] = {int(x, 16) for x in addrs.split(",")}
    if a.revert:
        revert(a.ov)
    elif a.probe:
        if len(a.func) != 1:
            ap.error("--probe takes exactly one --func")
        kind, detail = island_probe(a.ov, a.func[0])
        # RUN THE REAL PLANNER TOO (P31 S67, R35).  `island_probe` answers "where does this table
        # live", which is necessary but NOT sufficient: `build_carve` additionally refuses a plan
        # whose same-subseg .rodata carves are NON-CONTIGUOUS (one object cannot leave a hole for
        # an uncarved neighbour's table), and that refusal is invisible to island_probe.  Measured:
        # ov_SC03_010/func_8017F6C0 probes clean `tail` and the gate then books CARVE-REFUSED — and
        # the S66 free-wins audit priced 32 functions as free on exactly this blind probe.
        # build_carve is a pure planner (it reads config + payload and writes nothing), so calling
        # it here costs nothing and cannot mutate the tree; its refusals are `sys.exit(msg)`.
        # ...but NOT for a 'covered' function (S74): there is no plan to validate — its table is
        # already inside its own subseg's carve, so build_carve resolves nothing out of the raw
        # data asm and reports the absence as a refusal. Probing it as `plan-refused` contradicts
        # the byte-proven no-op (ov_SC07_002/func_80180248 banks with zero config change).
        try:
            if kind not in ("covered", "covered-tpad"):
                build_carve(a.ov, [a.func[0]])
        except SystemExit as e:
            msg = str(e) if not isinstance(e.code, int) else ""
            if msg:
                kind = "plan-refused"
                detail = msg.replace("\n", " ")
        print(f"jtbl_carve --probe {a.ov} {a.func[0]}: {kind} — {detail}")
    elif a.island_split:
        if len(a.func) != 1:
            ap.error("--island-split takes exactly one --func")
        island_split(a.ov, a.func[0])
    elif a.func:
        apply(a.ov, a.func)
    else:
        ap.error("give --func <fn> (repeatable) or --revert")


if __name__ == "__main__":
    main()
