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

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# §8e CLI state (set by main)
LIKE_OV = None
SPAN_TABLES_OVERRIDE = {}

PIECE_RE = re.compile(r"^(\s*)- \[(0x[0-9A-Fa-f]+),\s*([.\w]+),\s*(\w+)\]")
EOF_RE = re.compile(r"^\s*- \[(0x[0-9A-Fa-f]+)\]\s*(?:#.*)?$")


def cfg_path(ov):
    return os.path.join(REPO, f"config/splat.{ov}.yaml")


def overlay_vram_base(ov):
    """The overlay's load vram (all location overlays share the 0x80128158 slot, but read it)."""
    txt = open(cfg_path(ov)).read()
    m = re.search(r"vram:\s*(0x[0-9A-Fa-f]+)", txt)
    if not m:
        sys.exit(f"jtbl_carve: no vram in {cfg_path(ov)}")
    return int(m.group(1), 16)


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
    for p in glob.glob(os.path.join(REPO, "asm", ov, "nonmatchings", "*", "func_*.s")):
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
    p = os.path.join(REPO, "asm", ov, "nonmatchings", sub, f"{func}.s")
    if not os.path.exists(p):
        stale = sorted(glob.glob(os.path.join(REPO, "asm", ov, "nonmatchings", "*", f"{func}.s")))
        if not stale:
            sys.exit(f"jtbl_carve: no .s for {func} anywhere under asm/{ov}/nonmatchings/ — "
                     f"already spliced AND no stale copy; re-extract from the stub state first")
        p = stale[0]
        print(f"jtbl_carve: {func}.s not in config-derived subseg '{sub}' — using stale-location "
              f"{os.path.relpath(p, REPO)} for jtbl refs (content is address-stable)")
    s = open(p).read()
    return sub, sorted(set(re.findall(r"jtbl_([0-9A-Fa-f]{8})", s)))


def all_data_labels(ov):
    """All (jtbl_|D_) dlabel vrams across every asm/<ov>/data/*.data.s, sorted ascending."""
    labels = set()
    for p in glob.glob(os.path.join(REPO, "asm", ov, "data", "*.data.s")):
        for ln in open(p):
            m = re.match(r"\s*(?:dlabel|glabel)\s+(?:jtbl_|D_)([0-9A-Fa-f]{8})", ln)
            if m:
                labels.add(int(m.group(1), 16))
    return sorted(labels)


def jtbl_words(ov, jtbl_hex):
    """The raw `.word` values under `dlabel jtbl_<hex>`, in order."""
    pat = re.compile(rf"dlabel\s+jtbl_{jtbl_hex}\b", re.I)
    for p in glob.glob(os.path.join(REPO, "asm", ov, "data", "*.data.s")):
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
    for p in glob.glob(os.path.join(REPO, "asm", ov, "data", "*.data.s")):
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
    p = os.path.join(REPO, "asm", ov, "nonmatchings", sub, f"{fn}.s")
    if not os.path.exists(p):
        return set()
    out = set()
    for ln in open(p, errors="replace"):
        m = re.search(r"\bsltiu\s+\$\w+,\s*\$\w+,\s*(0x[0-9A-Fa-f]+|\d+)", ln)
        if m:
            out.add(int(m.group(1), 16) if m.group(1).startswith("0x") else int(m.group(1)))
    return out


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
    return start, end


def parse_config(ov):
    """Parse the flat-overlay config's tail data region.

    Returns (lines, indent, region_lo_idx, region_hi_idx, tail_start, region_end, trailing_present,
             existing_carves) where:
      - lines: the config file split into lines.
      - region_lo_idx..region_hi_idx: the [inclusive, exclusive) line range of the `- [...]` data/
        rodata PIECE lines to replace (the `bin,trailing` + EOF lines stay).
      - tail_start / region_end: file offsets bounding the regenerated data region.
      - trailing_present: whether a `[off, bin, trailing]` piece caps the region.
      - existing_carves: [(start_off, end_off, subseg), ...] for the `.rodata` carves already present.
    """
    lines = open(cfg_path(ov)).read().splitlines()
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
    # The data region = the trailing run of {data, .rodata} pieces after the last `c` piece.
    data_pieces = [p for p in pieces if p[3] in ("data", ".rodata")]
    if not data_pieces:
        sys.exit(f"jtbl_carve: no data-tail region in {cfg_path(ov)}")
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
        elif prior is None and sub in old_span_start:
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
        if LIKE_OV:
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


def apply(ov, funcs):
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
    var = f"{ov}_JTBL_INTERLEAVE := {args}  # Phase-26 §8 jtbl-rodata carve"
    if re.search(rf"^{re.escape(ov)}_JTBL_INTERLEAVE\b", txt, re.M):
        txt = re.sub(rf"^{re.escape(ov)}_JTBL_INTERLEAVE.*$", var, txt, count=1, flags=re.M)
    else:
        # insert right after the overlay's SPLAT_YAML line
        anchor = f"{ov}_SPLAT_YAML := config/splat.{ov}.yaml"
        if anchor not in txt:
            sys.exit(f"jtbl_carve: no {anchor} anchor in overlays.mk")
        txt = txt.replace(anchor, anchor + "\n" + var, 1)
    open(mk, "w").write(txt)


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
    before = current_pads_specs(ov, txt)
    after = {sub: sr for sub, sr in pads_map.items() if len(sr[0]) > 1}
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
    open(mk, "w").write(txt)
    for sub in set(before) | set(after):
        if before.get(sub) != after.get(sub):
            obj = os.path.join(REPO, f"build/src/{ov}/{sub}.o")
            if os.path.exists(obj):
                os.remove(obj)
                print(f"jtbl_carve: JTBL_PADS changed for {sub} — removed stale {obj}")


def revert(ov):
    """Restore this overlay's carve state to the COMMITTED one.

    `<ov>_JTBL_INTERLEAVE` must be restored to its committed VALUE, not deleted: every overlay now
    carries a committed carve (134/134 since func_8012ACE0 / func_801734BC banked ×134), so an
    unconditional drop would destroy a banked carve on any failed sweep. And `overlays.mk` is SHARED
    by all 134 overlays, so a blunt `git checkout` of it would wipe the OTHER siblings' in-flight
    vars mid-sweep — hence the surgical, per-overlay line splice."""
    subprocess.check_call(["git", "-C", REPO, "checkout", "--", cfg_path(ov)])
    mk = os.path.join(REPO, "config/overlays.mk")
    txt = open(mk).read()
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
    open(mk, "w").write(txt)
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
    elif a.func:
        apply(a.ov, a.func)
    else:
        ap.error("give --func <fn> (repeatable) or --revert")


if __name__ == "__main__":
    main()
