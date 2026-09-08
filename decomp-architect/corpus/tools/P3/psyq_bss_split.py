#!/usr/bin/env python3
"""psyq_bss_split.py — split a PsyQ object's scattered `.bss` into per-base pieces so it links byte-exact (P31 S78 #4).

THE WALL, RESTATED.  psyq-obj-parser packs an object's common-style globals into ONE `.bss` section
with sequential offsets.  The original PsyQ linker allocated those commons individually, so the game
has them at several unrelated addresses ("scattered commons", cookbook §9.1).  A common referenced
BY NAME is recovered by name and `--defsym`'d (§9.2).  But the compiler references the object's own
statics through the `.bss` SECTION SYMBOL plus an offset — a relocation with no name to defsym — and
the build can NOLOAD-place a section at only ONE base.  `psyq_bss_probe.py` (§484) asked the question
nobody had: are the offsets behind each base DISJOINT?  For SYS.o and VM_F.o they are, so the section
can be cut into pieces that each have a single base.  This tool makes the cut.

WHAT IT DOES TO THE OBJECT (an ELF32 REL rewrite; no pyelftools — the project's readers are regexes
over readelf, and a WRITER needs the real structs anyway):
  1. derives the bases FROM THE BYTES: for every HI16/LO16 pair against the section symbol,
     addend = the object's immediates, resolved = the game's immediates at the same `.text` offset,
     base = resolved − addend (the probe's arithmetic, R33: one implementation, the probe imports it);
  2. walks the references in offset order; each maximal run with one base is a piece.  A cut between
     two runs SNAPS TO A SYMBOL START (the linker scattered SYMBOLS, so a piece that begins mid-symbol
     is a fiction): SYS.o's second run begins inside `_que` (+0x148) and the piece begins at `_que`
     (+0x144) — and `_que`, recovered independently BY NAME from SYS.o's four named references, is
     0x800C5510 = base2 + 0x144.  VM_F.o's second run begins at `_svm_sreg_buf` (+0x508), which 62
     other sound objects recover to 0x800B9B58 = base2 + 0x508.  Two unrelated oracles agree on both
     cuts (R34).  With no symbol start between the runs the cut is at the run's first reference;
  3. REFUSES, loudly (R43), when the references cannot be tiled: a sized symbol straddling a cut (one
     common referenced at two bases), a HI16 whose LO16s fall in different pieces, an orphan LO16, a
     reference far outside the section, or a relocation type other than HI16/LO16/32 against the
     section symbol.  Coverage is asserted: every reference against the section symbol is classified
     or the split fails (R32).  Problems are FATAL ONLY WHEN A SPLIT IS NEEDED — an object one base
     already serves passes through untouched, exactly as before this tool existed (R39: the first
     build refused a libcd object for an end-of-buffer `.bss + size` reference it never needed split
     for; 235 placed objects across the 9 curated dirs now pass with 0 refusals and exactly 3 splits).
     GS_001.o, which the S77 probe called "5 interleaved bases, NOT splittable" by grouping per base,
     is SIX symbol-aligned runs under this model and links byte-identical;
  4. emits `.bss` = [0, s2) and new NOBITS sections `.bss2` = [s2, s3) …; moves each symbol at/after a
     cut into its piece (value −= piece start); adds one LOCAL section symbol per piece (inserted with
     the existing section symbols — every later symbol index in every REL entry is bumped); retargets
     each reference to its piece's symbol and REWRITES ITS ADDEND IN PLACE: the HI16/LO16 immediates
     in `.text` (hi' = (A'+0x8000)>>16, lo' = A' & 0xFFFF, A' = A − piece start) or the R_MIPS_32 word;
  5. self-checks: the rewritten object's code/data differ from the original at exactly the retargeted
     sites whose value changed, and nowhere else (the tool diffs its own artifact, R37).

WHERE IT RUNS.  Not in the curated dirs — at LINK-PREPARE time, in the one path `psyq_link.link_object`
(per-object verify), `psyq_link_region.build_region` (region verify) and `psyq_integrate.integrate`
(the build) all share: `prepare_object()`.  `classify()` then recovers one base per piece from the
piece's own section symbol and NOLOAD-places each — no config, no recorded split offset that could go
stale (R51).  An object with a single base passes through untouched.

    tools/psyq_bss_split.py <obj.o> --vram <text_vram> --exe <binary> --vram-base <hex> [-o out.o]
    (no -o = report the plan only)
"""
import argparse
import os
import re
import struct
import sys

NOBITS_RE = re.compile(r"^\.s?bss\d*$")          # .bss .sbss and the pieces this tool makes (.bss2 …)
SHT_SYMTAB, SHT_STRTAB, SHT_NOBITS, SHT_REL = 2, 3, 8, 9
STT_SECTION, STB_LOCAL = 3, 0
R_MIPS_32, R_MIPS_HI16, R_MIPS_LO16 = 2, 5, 6
RNAME = {2: "R_MIPS_32", 4: "R_MIPS_26", 5: "R_MIPS_HI16", 6: "R_MIPS_LO16"}
EHDR = struct.Struct("<16sHHIIIIIHHHHHH")
SHDR = struct.Struct("<IIIIIIIIII")
SYM = struct.Struct("<IIIBBH")
REL = struct.Struct("<II")


class SplitRefused(Exception):
    """The section's references cannot be tiled into single-base pieces. Say so; never place them wrongly."""


def s16(x):
    x &= 0xFFFF
    return x - 0x10000 if x & 0x8000 else x


def u16(buf, off):
    return struct.unpack_from("<H", buf, off)[0]


def u32(buf, off):
    return struct.unpack_from("<I", buf, off)[0]


def cstr(buf, off):
    return bytes(buf[off:buf.index(b"\0", off)]).decode()


class Elf32:
    """Minimal ELF32 little-endian relocatable reader/writer: headers + contents, symbols, REL entries.
    Sections keep their index order on write; file offsets are recomputed."""

    def __init__(self, data):
        f = EHDR.unpack_from(data, 0)
        if f[0][:4] != b"\x7fELF" or f[0][4] != 1 or f[0][5] != 1:
            raise ValueError("not an ELF32 little-endian file")
        (self.ident, self.type, self.machine, self.version, self.entry, self.phoff, shoff, self.flags,
         self.ehsize, self.phentsize, self.phnum, self.shentsize, shnum, self.shstrndx) = f
        self.sh, self.data = [], []
        for i in range(shnum):
            name, typ, flg, addr, off, size, link, info, align, ent = SHDR.unpack_from(data, shoff + i * SHDR.size)
            self.sh.append(dict(name=name, type=typ, flags=flg, addr=addr, size=size, link=link,
                                info=info, align=align, entsize=ent))
            self.data.append(bytearray() if typ == SHT_NOBITS else bytearray(data[off:off + size]))
        self.symidx = next(i for i, s in enumerate(self.sh) if s["type"] == SHT_SYMTAB)
        st = self.sh[self.symidx]
        self.strtab = st["link"]
        self.syms = [list(SYM.unpack_from(self.data[self.symidx], k * SYM.size))     # [name value size info other shndx]
                     for k in range(st["size"] // SYM.size)]
        self.rels = {}                                                              # rel-section idx -> [[r_offset, r_sym, r_type]]
        for i, s in enumerate(self.sh):
            if s["type"] == SHT_REL and s["link"] == self.symidx:
                self.rels[i] = [[o, info >> 8, info & 0xFF]
                                for o, info in (REL.unpack_from(self.data[i], k * REL.size)
                                                for k in range(s["size"] // REL.size))]

    def secname(self, i):
        return cstr(self.data[self.shstrndx], self.sh[i]["name"])

    def section_index(self, name):
        return next((i for i in range(len(self.sh)) if self.secname(i) == name), None)

    def symname(self, k):
        return cstr(self.data[self.strtab], self.syms[k][0])

    def add_string(self, secidx, s):
        off = len(self.data[secidx])
        self.data[secidx] += s.encode() + b"\0"
        return off

    def serialize(self):
        self.data[self.symidx] = bytearray(b"".join(SYM.pack(*y) for y in self.syms))
        for i, rl in self.rels.items():
            self.data[i] = bytearray(b"".join(REL.pack(o, (sym << 8) | typ) for o, sym, typ in rl))
        out, offs = bytearray(EHDR.size), []
        for i, s in enumerate(self.sh):
            if i == 0:
                offs.append(0)
                continue
            a = min(max(s["align"], 1), 16) if s["type"] != SHT_NOBITS else 4
            while len(out) % a:
                out.append(0)
            offs.append(len(out))
            if s["type"] != SHT_NOBITS:
                out += self.data[i]
        while len(out) % 4:
            out.append(0)
        shoff = len(out)
        for i, s in enumerate(self.sh):
            size = s["size"] if s["type"] == SHT_NOBITS else len(self.data[i])
            out += SHDR.pack(s["name"], s["type"], s["flags"], s["addr"], offs[i], size,
                             s["link"], s["info"], s["align"], s["entsize"])
        EHDR.pack_into(out, 0, self.ident, self.type, self.machine, self.version, self.entry, self.phoff,
                       shoff, self.flags, self.ehsize, self.phentsize, self.phnum, self.shentsize,
                       len(self.sh), self.shstrndx)
        return bytes(out)


class Piece:
    __slots__ = ("index", "lo", "hi", "base", "name", "cut_sym", "shndx", "symidx", "refs")

    def __init__(self, index, lo, hi, base, name, cut_sym):
        self.index, self.lo, self.hi, self.base, self.name, self.cut_sym = index, lo, hi, base, name, cut_sym
        self.shndx = self.symidx = None
        self.refs = 0

    @property
    def addr(self):                       # where the piece lands in the target binary
        return None if self.base is None else (self.base + self.lo) & 0xFFFFFFFF


def _plan_section(e, bi, ssym, text_vram, exe, vram_base):
    """Analyse one NOBITS section referenced through its section symbol `ssym`.
    Returns dict(shndx, size, bases, pieces, actions, nrefs, by_section) — `pieces` has ONE entry when
    a single base covers every reference (no split needed)."""
    sec = e.secname(bi)
    size = e.sh[bi]["size"]
    text_i = e.section_index(".text")
    points, clusters, nrefs, by_section, problems = [], [], 0, {}, []
    # Problems found while walking the references are FATAL only if a split turns out to be needed:
    # an object one base already serves must pass through exactly as it did before this tool existed
    # (R39 — a refusal check ships only after the previously-passing population still passes).
    for ri, rl in e.rels.items():
        tgt = e.sh[ri]["info"]
        body = e.data[tgt]
        tname = e.secname(tgt)
        cluster = None                    # [his, los, closed] — LO16s after a HI16 group share it (one lui, several uses)
        for k, (off, sym, typ) in enumerate(rl):
            if sym != ssym:
                continue
            nrefs += 1
            by_section[tname] = by_section.get(tname, 0) + 1
            if typ == R_MIPS_HI16:
                if tgt != text_i:
                    problems.append(f"{sec}: R_MIPS_HI16 in non-text section {tname}")
                    continue
                if cluster is None or cluster[2]:
                    cluster = [[], [], False, ri]     # his, los, closed, rel-section index
                    clusters.append(cluster)
                cluster[0].append(k)
            elif typ == R_MIPS_LO16:
                if tgt != text_i or cluster is None or not cluster[0]:
                    problems.append(f"{sec}: orphan R_MIPS_LO16 at {tname}+{off:#x} (no preceding HI16)")
                    continue
                cluster[2] = True
                hi_off = rl[cluster[0][-1]][0]
                A = (u16(body, hi_off) << 16) + s16(u16(body, off))
                site = text_vram + hi_off - vram_base
                resolved = (u16(exe, site) << 16) + s16(u16(exe, text_vram + off - vram_base))
                base = (resolved - A) & 0xFFFFFFFF
                cluster[1].append((k, A, base))
                points.append((A, base, ri, k))
            elif typ == R_MIPS_32:
                A = u32(body, off)
                points.append((A, None, ri, k))     # no base derivable without the section's own placement; tiled by offset
            else:
                problems.append(f"{sec}: unsupported relocation {RNAME.get(typ, typ)} against the section symbol at {tname}+{off:#x}")
    for A, base, ri, k in points:
        # An addend == size is an END pointer (`&buf[N]`, a loop bound) and belongs to the last piece;
        # small negative addends are gcc's folded `&arr[i-1]`. Only an addend far outside the section
        # can be a mis-paired HI16/LO16, and THAT is what is refused (libc2 SETJMP-style end pointers
        # at .bss+size hit the stricter `< size` form on the first build, S78 #4).
        if not (-0x8000 <= A <= size + 0x8000):
            problems.append(f"{sec}: reference at {e.secname(e.sh[ri]['info'])}+{e.rels[ri][k][0]:#x} has addend {A:#x} far outside the section (size {size:#x}) — mis-paired relocation?")
    based = sorted((A, b) for A, b, _, _ in points if b is not None)
    # maximal runs of one base, in offset order
    runs = []                                       # [lo_addend, hi_addend, base, count]
    for A, b in based:
        if runs and runs[-1][2] == b:
            runs[-1][1] = A
            runs[-1][3] += 1
        else:
            runs.append([A, A, b, 1])
    bases = {}
    for A, b in based:
        lo, hi, n = bases.get(b, (A, A, 0))
        bases[b] = (min(lo, A), max(hi, A), n + 1)
    syms = sorted((y[1], y[2], e.symname(k)) for k, y in enumerate(e.syms)
                  if y[5] == bi and (y[3] & 0xF) != STT_SECTION)
    pieces = []
    if len(runs) > 1 and problems:
        raise SplitRefused(f"{sec}: needs splitting ({len(runs)} runs) but the references could not all be "
                           f"classified — {problems[0]}" + (f" (+{len(problems) - 1} more)" if len(problems) > 1 else ""))
    if runs:
        cuts = [(0, None)]
        for prev, cur in zip(runs, runs[1:]):
            cands = [(v, nm) for v, _sz, nm in syms if prev[1] < v <= cur[0]]
            v, nm = max(cands) if cands else (cur[0], None)
            for sv, ssz, snm in syms:
                if ssz and sv < v < sv + ssz:
                    raise SplitRefused(f"{sec}: symbol `{snm}` [{sv:#x},{sv+ssz:#x}) straddles the cut at {v:#x} — "
                                       f"one common is referenced at two bases ({prev[2]:#010x} and {cur[2]:#010x}); not splittable")
            cuts.append((v, nm))
        for j, (v, nm) in enumerate(cuts):
            hi = cuts[j + 1][0] if j + 1 < len(cuts) else size
            pieces.append(Piece(j, v, hi, runs[j][2], sec if j == 0 else f"{sec}{j + 1}", nm))

    def piece_of(A):
        return max((p for p in pieces if p.lo <= A), key=lambda p: p.lo, default=pieces[0])

    actions = []                                    # (rel_sec, entry, piece, new_field_value)
    for cl in clusters:
        his, los, ri = cl[0], cl[1], cl[3]
        target, hi_new = None, None
        for k, A, base in los:
            p = piece_of(A)
            A2 = A - p.lo
            lo2 = A2 & 0xFFFF
            hi2 = ((A2 + 0x8000) >> 16) & 0xFFFF
            if target is None:
                target, hi_new = p, hi2
            elif p is not target or hi2 != hi_new:
                raise SplitRefused(f"{sec}: one HI16 is shared by LO16s that need different pieces/high halves "
                                   f"(addends {[a for _, a, _ in los]}) — not splittable")
            actions.append((ri, k, p, lo2))
        for k in his:
            actions.append((ri, k, target, hi_new))
    return dict(shndx=bi, size=size, bases=bases, runs=runs, pieces=pieces, actions=actions,
                nrefs=nrefs, by_section=by_section, points=points, syms=syms, problems=problems)



def analyze(obj_path, text_vram, exe, vram_base, elf=None):
    """{section name: plan} for every NOBITS section referenced through its section symbol."""
    e = elf or Elf32(open(obj_path, "rb").read())
    plans = {}
    for bi, s in enumerate(e.sh):
        if s["type"] != SHT_NOBITS:
            continue
        ssym = next((k for k, y in enumerate(e.syms) if (y[3] & 0xF) == STT_SECTION and y[5] == bi), None)
        if ssym is None:
            continue
        plan = _plan_section(e, bi, ssym, text_vram, exe, vram_base)
        if plan["nrefs"]:
            plans[e.secname(bi)] = plan
    return plans


def needs_split(plans):
    return {sec: p for sec, p in plans.items() if len(p["pieces"]) > 1}


def describe(plans):
    """One line per split section, for build logs."""
    out = []
    for sec, p in needs_split(plans).items():
        parts = []
        for pc in p["pieces"]:
            cut = f" (cut at `{pc.cut_sym}`)" if pc.cut_sym else ""
            parts.append(f"{pc.name} [{pc.lo:#06x},{pc.hi:#06x}) @{pc.addr:#010x}{cut}")
        out.append(f"{sec} split ×{len(p['pieces'])}: " + " · ".join(parts))
    return "; ".join(out)


def split(obj_path, text_vram, exe, vram_base, out_path, plans=None):
    """Write the split object to out_path. Returns the plans (empty dict when nothing needed splitting
    and nothing was written)."""
    raw = open(obj_path, "rb").read()
    e = Elf32(raw)
    plans = plans if plans is not None else analyze(obj_path, text_vram, exe, vram_base, elf=e)
    todo = needs_split(plans)
    if not todo:
        return {}
    # 1. new NOBITS sections for pieces 2..n; shrink the original to piece 1
    for sec, p in todo.items():
        bi = p["shndx"]
        for pc in p["pieces"][1:]:
            addr = pc.addr
            align = min(addr & -addr, 8) if addr else e.sh[bi]["align"]
            pc.shndx = len(e.sh)
            e.sh.append(dict(name=e.add_string(e.shstrndx, pc.name), type=SHT_NOBITS, flags=e.sh[bi]["flags"],
                             addr=0, size=pc.hi - pc.lo, link=0, info=0, align=max(align, 1), entsize=0))
            e.data.append(bytearray())
        e.sh[bi]["size"] = p["pieces"][0].hi
    # 2. one LOCAL section symbol per new piece, inserted right after the existing section symbols
    #    (locals precede globals); every later symbol index in every REL entry moves up.
    insert_at = 1 + max(k for k, y in enumerate(e.syms) if (y[3] & 0xF) == STT_SECTION)
    n_new = sum(len(p["pieces"]) - 1 for p in todo.values())
    st = e.sh[e.symidx]
    if insert_at > st["info"]:
        raise SplitRefused("symbol table: section symbols are not in the LOCAL range (sh_info=%d)" % st["info"])
    for rl in e.rels.values():
        for r in rl:
            if r[1] >= insert_at:
                r[1] += n_new
    st["info"] += n_new
    k = insert_at
    for sec, p in todo.items():
        for pc in p["pieces"][1:]:
            e.syms.insert(k, [e.add_string(e.strtab, pc.name), 0, 0, (STB_LOCAL << 4) | STT_SECTION, 0, pc.shndx])
            pc.symidx = k
            k += 1
    # 3. move the symbols that live in a later piece
    for sec, p in todo.items():
        bi = p["shndx"]
        for y in e.syms:
            if y[5] == bi and (y[3] & 0xF) != STT_SECTION:
                pc = max((q for q in p["pieces"] if q.lo <= y[1]), key=lambda q: q.lo, default=p["pieces"][0])
                if pc.index:
                    y[5], y[1] = pc.shndx, y[1] - pc.lo
    # 4. retarget + rewrite the addend field of every reference in a later piece
    changed = {}                                                  # (target sec idx, offset) -> new word
    for sec, p in todo.items():
        text_i = e.section_index(".text")
        for ri, k, pc, field in p["actions"]:
            off, sym, typ = e.rels[ri][k]
            tgt = e.sh[ri]["info"]
            pc.refs += 1
            if pc.index == 0:
                continue
            e.rels[ri][k][1] = pc.symidx
            w = u32(e.data[tgt], off)
            nw = (w & 0xFFFF0000) | field
            struct.pack_into("<I", e.data[tgt], off, nw)
            if nw != w:
                changed[(tgt, off)] = nw
        for A, base, ri, k in p["points"]:                       # R_MIPS_32 words (data pointers into the section)
            off, sym, typ = e.rels[ri][k]
            if typ != R_MIPS_32:
                continue
            pc = max((q for q in p["pieces"] if q.lo <= A), key=lambda q: q.lo, default=p["pieces"][0])
            pc.refs += 1
            if pc.index == 0:
                continue
            tgt = e.sh[ri]["info"]
            e.rels[ri][k][1] = pc.symidx
            struct.pack_into("<I", e.data[tgt], off, A - pc.lo)
            changed[(tgt, off)] = A - pc.lo
    blob = e.serialize()
    open(out_path, "wb").write(blob)
    # 5. self-check: only the retargeted fields changed, in the code/data sections; re-read what we wrote
    o, n = Elf32(raw), Elf32(blob)
    for i in range(len(o.sh)):
        if o.sh[i]["type"] in (SHT_SYMTAB, SHT_STRTAB, SHT_REL, SHT_NOBITS) or i == o.shstrndx:
            continue
        a, b = o.data[i], n.data[i]
        if len(a) != len(b):
            raise AssertionError(f"self-check: section {o.secname(i)} changed size")
        diff = {j for j in range(0, len(a), 4) if a[j:j + 4] != b[j:j + 4]}
        want = {off for (t, off) in changed if t == i}
        if diff != want:
            raise AssertionError(f"self-check: {o.secname(i)} differs at {sorted(diff ^ want)[:8]} beyond the retargeted sites")
    for sec, p in todo.items():
        ni = n.section_index(sec)
        if n.sh[ni]["size"] != p["pieces"][0].hi or any(n.section_index(pc.name) is None for pc in p["pieces"][1:]):
            raise AssertionError(f"self-check: {sec} pieces not present as written")
    return plans


def prepare_object(obj_path, text_vram, exe, vram_base, outdir):
    """The object to LINK: the original path, or a split copy under outdir when a NOBITS section is
    referenced at more than one base. SplitRefused propagates — a build must not place bytes wrongly."""
    plans = analyze(obj_path, text_vram, exe, vram_base)
    if not needs_split(plans):
        return obj_path, {}
    os.makedirs(outdir, exist_ok=True)
    out = os.path.join(outdir, os.path.basename(obj_path))
    split(obj_path, text_vram, exe, vram_base, out, plans)
    return out, plans


def report(plans, name):
    lines = []
    for sec, p in plans.items():
        lines.append(f"{name}: {sec} {p['size']:#x} B, {p['nrefs']} section-symbol ref(s) in "
                     + ", ".join(f"{s} ×{n}" for s, n in p["by_section"].items()))
        for b, (lo, hi, n) in sorted(p["bases"].items()):
            lines.append(f"   base {b:#010x} : {n:2d} ref(s), {sec} offsets {lo:#06x}..{hi:#06x}")
        if len(p["pieces"]) > 1:
            lines.append(f"   SPLITTABLE: YES — {len(p['pieces'])} pieces:")
            for pc in p["pieces"]:
                cut = f"  cut snapped to `{pc.cut_sym}`" if pc.cut_sym else ("" if pc.index == 0 else "  (no symbol start between the runs)")
                lines.append(f"      {pc.name:7s} [{pc.lo:#06x},{pc.hi:#06x}) -> {pc.addr:#010x}{cut}")
        elif p["runs"]:
            lines.append("   single base — no split needed")
        else:
            lines.append("   no HI16/LO16 pairs against the section symbol — nothing to place")
    return "\n".join(lines)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("obj")
    ap.add_argument("--vram", required=True, help="the object's .text vram in the target binary")
    ap.add_argument("--exe", required=True, help="target binary path")
    ap.add_argument("--vram-base", required=True, help="fileoff->vram delta of the target binary")
    ap.add_argument("-o", "--out", help="write the split object here (omit to report only)")
    a = ap.parse_args()
    exe = open(a.exe, "rb").read()
    name = os.path.basename(a.obj)
    try:
        plans = analyze(a.obj, int(a.vram, 0), exe, int(a.vram_base, 0))
    except SplitRefused as ex:
        print(f"{name}: REFUSED — {ex}")
        return 2
    if not plans:
        print(f"{name}: no NOBITS section is referenced through its section symbol — the scattered-.bss wall does not apply")
        return 0
    print(report(plans, name))
    if a.out and needs_split(plans):
        split(a.obj, int(a.vram, 0), exe, int(a.vram_base, 0), a.out, plans)
        n = sum(pc.refs for p in needs_split(plans).values() for pc in p["pieces"][1:])
        print(f"   wrote {a.out}: {n} reference(s) retargeted; {describe(plans)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
