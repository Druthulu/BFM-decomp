#!/usr/bin/env python3
"""leverage_rank.py: rank the fleet's functions and data by how many unique bodies reference them.

For every binary: read build/<dir>/<b>.map placements, parse each placed .o (ELF32 LE, SHT_REL, pure Python,
addends from the relocated word), and attribute every relocation (all sections) to a source body and a target unit,
or to a named exclusion. Unattributed must be 0 (else exit 1). References are deduplicated to unique-body keys
(source key, offset, reloc type, target unit), so the same body linked into many binaries counts once.

  source body: text -> sig row of b containing the place (h_exact, off); none -> ("raw", b, nearest FUNC <= A)
               data -> nearest preceding data symbol of b's output section ((space, sym), off)
  target unit: func (h_exact of the sig function starting at T in its holder), func raw:<space>:<addr> (no sig row, T
               starts an ELF FUNC/global symbol), or data (space, addr); other text targets: TEXT-NOSIG, JTBL-CASE (data
               word into a sig body), LOCAL-LABEL (text reloc into a sig body)
  space:       b's own image -> its VRAM_BASE; else main's; else resident's; else another image (slot); else abs

Controls: (1) per-object reloc count == `objdump -r` reloc lines; (2) one function and one datum: refs == an
independent objdump grep of the name; (3) attributed multiplicity + hi16 + excluded == raw total.
Struct ownership (.run/P37/census struct_map.json + sites.jsonl, refused when stale against HEAD for src/include):
own(d) = sum over struct types T held by data unit d of reach(T) / holders(T); reach = distinct h_exact of the bodies
of T's sites (headers through every include site and its SHARED_FN); holders = data units of T's global/gaddr sites
and globals_at/globals_ptr. score = (refs + own) * (1 + log10(fan)).
Writes docs/leverage.tsv and docs/leverage.md. `--check` recomputes in memory (controls included: the .md records
their verdicts) and byte-compares both (exit 1 on any difference). Usage: leverage_rank.py [-j N] [--check]
"""
import argparse, bisect, collections, json, math, os, re, struct, subprocess, sys
from concurrent.futures import ThreadPoolExecutor
from multiprocessing import get_context

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import share_census as sc  # noqa: E402


class Fail(Exception):
    """Raised in workers (a sys.exit there kills the worker and hangs the pool)."""

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OBJDUMP = "mipsel-linux-gnu-objdump"
OUT_TSV = os.path.join(REPO, "docs", "leverage.tsv")
OUT_MD = os.path.join(REPO, "docs", "leverage.md")
CENSUS = os.path.join(".run", "P37", "census")    # tools/type_census.py --sites default out dir
TEXT_SECS = {".text"}
DATA_SECS = {".data", ".rodata", ".sdata", ".sbss", ".bss"}
R_32, R_26, R_HI16, R_LO16, R_PC16 = 2, 4, 5, 6, 10
RNAME = {R_32: "R_MIPS_32", R_26: "R_MIPS_26", R_HI16: "R_MIPS_HI16", R_LO16: "R_MIPS_LO16", R_PC16: "R_MIPS_PC16"}
PLACEHOLDER = re.compile(r"^(func|D|jtbl|L|sym|jpt|lbl)_[0-9A-Fa-f]{6,8}$")
SHN_UNDEF, SHN_ABS, SHN_COMMON = 0, 0xFFF1, 0xFFF2
STT_OBJECT, STT_FUNC, STT_SECTION, STT_FILE = 1, 2, 3, 4
SEC_IN = re.compile(r"^ (\S+)\s+0x([0-9a-f]+)\s+0x([0-9a-f]+)\s+(\S+\.o)$")
SEC_NAME_ONLY = re.compile(r"^ (\.\S+|COMMON)$")
SEC_CONT = re.compile(r"^\s+0x([0-9a-f]+)\s+0x([0-9a-f]+)\s+(\S+\.o)$")
LD_ASSIGN = re.compile(r"^\s*(\w+)\s*=", re.M)


def sext16(v):
    return v - 0x10000 if v & 0x8000 else v


def h8(v):
    return "abs" if v is None else "%08X" % v


# ------------------------------------------------------------------------------------------ ELF32 LE reader
def read_elf(path):
    """-> (bytes, sections [(name, type, flags, addr, offset, size, link, info)])."""
    d = open(path, "rb").read()
    if d[:4] != b"\x7fELF" or d[4] != 1 or d[5] != 1:
        raise Fail(f"{path} is not ELF32 LE")
    shoff, = struct.unpack_from("<I", d, 0x20)
    shentsize, shnum, shstrndx = struct.unpack_from("<HHH", d, 0x2E)
    raw = [struct.unpack_from("<10I", d, shoff + i * shentsize) for i in range(shnum)]
    so = raw[shstrndx][4]
    secs = []
    for r in raw:
        n0 = so + r[0]
        secs.append((d[n0:d.index(b"\0", n0)].decode(), r[1], r[2], r[3], r[4], r[5], r[6], r[7]))
    return d, secs


def elf_symbols(d, secs):
    """-> [(name, value, size, type, bind, shndx)] of the first SYMTAB (index order kept)."""
    for s in secs:
        if s[1] == 2:
            strofs = secs[s[6]][4]
            out = []
            for name, value, size, info, _o, shndx in struct.iter_unpack("<IIIBBH", d[s[4]:s[4] + s[5]]):
                n0 = strofs + name
                out.append((d[n0:d.index(b"\0", n0)].decode() if name else "", value, size, info & 0xF, info >> 4, shndx))
            return out
    return []


def parse_obj(path):
    """-> (secs, syms, rels) with rels = [(tgt_secname, tgt_flags, [(off, type, symidx, word)])], in file order."""
    d, secs = read_elf(path)
    syms = elf_symbols(d, secs)
    rels = []
    for s in secs:
        if s[1] == 4:
            raise Fail(f"{path} has SHT_RELA {s[0]}; this reader handles SHT_REL only")
        if s[1] != 9:
            continue
        t = secs[s[7]]
        ents = []
        for off, info in struct.iter_unpack("<II", d[s[4]:s[4] + s[5]]):
            word = struct.unpack_from("<I", d, t[4] + off)[0] if t[1] != 8 else 0
            ents.append((off, info & 0xFF, info >> 8, word))
        rels.append((t[0], t[2], ents))
    return secs, syms, rels


def obj_reloc_count(path):
    d, secs = read_elf(path)
    return sum(s[5] // 8 for s in secs if s[1] == 9)


# ------------------------------------------------------------------------------------------ fleet tables
def build_base(alias):
    if alias == "main":
        return os.path.join("build", "us", "SLUS_007.26")
    return os.path.join("build", alias, alias)


def parse_map(path):
    """-> [(obj, sec, addr, size)] for every input section after 'Linker script and memory map'."""
    out, live, pending = [], False, None
    with open(path) as f:
        for ln in f:
            ln = ln.rstrip("\n")
            if not live:
                live = ln.startswith("Linker script and memory map")
                continue
            if pending is not None:
                m = SEC_CONT.match(ln)
                if m:
                    out.append((m.group(3), pending, int(m.group(1), 16), int(m.group(2), 16)))
                pending = None
                continue
            m = SEC_IN.match(ln)
            if m:
                out.append((m.group(4), m.group(1), int(m.group(2), 16), int(m.group(3), 16)))
                continue
            m = SEC_NAME_ONLY.match(ln)
            if m:
                pending = m.group(1)
    return out


def sec_class(name):
    if name in TEXT_SECS:
        return "text"
    if name in DATA_SECS:
        return "data"
    return "other"


class Bin:
    pass


def load_bin(alias):
    """Stage A for one binary: placements, image, intervals, ELF symbols, sig rows."""
    base = build_base(alias)
    b = Bin()
    b.alias = alias
    b.place = {}
    places = parse_map(os.path.join(REPO, base + ".map"))
    for obj, sec, addr, size in places:
        if (obj, sec) in b.place:
            raise Fail(f"{alias}: {obj} {sec} placed twice")
        b.place[(obj, sec)] = addr
    b.objs = sorted({p[0] for p in places})
    # intervals of placed alloc input sections (size > 0), by class
    iv = sorted((addr, addr + size, sec) for obj, sec, addr, size in places if size and addr)
    b.iv_lo = [x[0] for x in iv]
    b.iv = iv
    b.iv_maxend, m = [], 0      # main overlays NOLOAD psyq sections on its data blobs: overlaps are real
    for x in iv:
        m = max(m, x[1])
        b.iv_maxend.append(m)
    d, secs = read_elf(os.path.join(REPO, base + ".elf"))
    b.vbase = VB[alias]
    alloc = [(s[3], s[3] + s[5]) for s in secs if s[2] & 2 and s[5]]
    b.end = max(e for _a, e in alloc)
    b.outsecs = sorted(a for a in alloc if a[0] >= b.vbase)
    ld_names = set(LD_ASSIGN.findall(open(os.path.join(REPO, base + ".ld")).read()))
    syms = elf_symbols(d, secs)
    b.glob = {}      # name -> value (global/weak defined)
    b.loc = {}       # name -> [values] (local defined)
    b.at = collections.defaultdict(list)   # value -> [names] (real symbols, not linker markers)
    funcs, datas = set(), set()
    fst = collections.defaultdict(list)     # value -> [(not FUNC, name)]: ELF FUNC or global symbols (raw func units)
    for name, value, size, typ, bind, shndx in syms:
        if not name or typ in (STT_SECTION, STT_FILE) or shndx == SHN_UNDEF:
            continue
        if bind in (1, 2):
            b.glob.setdefault(name, value)
        else:
            b.loc.setdefault(name, []).append(value)
        if name in ld_names:    # ABS names stay: they are the symbol files (undefined_syms_auto.txt)
            continue
        b.at[value].append(name)
        if (typ == STT_FUNC or bind in (1, 2)) and not name.startswith(("jtbl_", "jpt_")):
            fst[value].append((typ != STT_FUNC, bool(PLACEHOLDER.match(name)), name))
        if typ == STT_FUNC:
            funcs.add(value)
        elif b.cls_at(value)[0] == "data":
            datas.add(value)
    b.funcs = sorted(funcs)
    b.fstart = {v: min(c)[2] for v, c in fst.items()}
    b.datas = sorted(datas)
    try:
        b.sig = sorted(sc.sig_rows(alias))
    except SystemExit as e:
        raise Fail(str(e))
    b.sig_lo = [r[0] for r in b.sig]
    b.cur = sc.curated_names(alias)     # addr -> curated name (this binary's symbol stack)
    return b


def _cls_at(self, t):
    """-> (class, secname) of the input section containing t in this binary, or (None, None)."""
    i = bisect.bisect_right(self.iv_lo, t) - 1
    best = None
    while i >= 0 and self.iv_maxend[i] > t:      # innermost (smallest) input section containing t
        lo, hi, sec = self.iv[i]
        if t < hi and (best is None or hi - lo < best[1] - best[0]):
            best = self.iv[i]
        i -= 1
    return (sec_class(best[2]), best[2]) if best else (None, None)


def _sig_at(self, t):
    i = bisect.bisect_right(self.sig_lo, t) - 1
    if i >= 0:
        r = self.sig[i]
        if t < r[0] + 4 * r[1]:
            return r
    return None


Bin.cls_at = _cls_at
Bin.sig_at = _sig_at

VB, BINS, ORDER, SLOTS = {}, {}, [], []


def setup_slots():
    """Images other than main/resident grouped by VRAM_BASE: (base, max end, merged text intervals)."""
    groups = collections.defaultdict(list)
    for a in ORDER:
        if a not in ("main", "resident"):
            groups[BINS[a].vbase].append(BINS[a])
    for base in sorted(groups):
        mem = groups[base]
        txt = []
        for lo, hi in sorted((lo, hi) for m in mem for lo, hi, sec in m.iv if sec_class(sec) == "text"):
            if txt and lo <= txt[-1][1]:
                txt[-1][1] = max(txt[-1][1], hi)
            else:
                txt.append([lo, hi])
        SLOTS.append((base, max(m.end for m in mem), [x[0] for x in txt], txt))


def in_slot_text(slot, t):
    _b, _e, lo, txt = slot
    i = bisect.bisect_right(lo, t) - 1
    return i >= 0 and t < txt[i][1]


# ------------------------------------------------------------------------------------------ stage B
def classify_target(b, t, named, symname, rtype, objsyms_at_t, stats):
    """-> ("unit", unit) | ("excl", bucket) | ("anon", (holder, t))."""
    if b.vbase <= t < b.end:
        h = b
    elif BINS["main"].vbase <= t < BINS["main"].end:
        h = BINS["main"]
    elif BINS["resident"].vbase <= t < BINS["resident"].end:
        h = BINS["resident"]
    else:
        hits = [s for s in SLOTS if s[0] <= t < s[1]]
        if not hits:
            if rtype in (R_26, R_PC16):
                return "excl", "ABS-CALL"
            return "unit", ("data", None, t)
        if len(hits) > 1:
            stats["slot_multi_base"] += 1
        if any(in_slot_text(s, t) for s in hits):
            return "excl", "SLOT-CALL"
        return "unit", ("data", hits[0][0], t)
    r = h.sig_at(t)
    cls, sec = h.cls_at(t)
    if r is not None and r[0] == t:
        return "unit", ("func", r[2])
    if r is not None or cls == "text":
        was = "TEXT-INTERIOR" if r is not None else "TEXT-NOSIG"
        stats["was:" + was] += 1
        if t in h.fstart:        # starts an ELF FUNC/global symbol: a function with no sig row of its own
            stats["was:" + was + ":raw"] += 1
            return "unit", ("func", "raw:%s:%08X" % (h8(h.vbase), t))
        return "excl", was
    if cls is None:          # in the image, in no input section: main's bss exists only as ABS symbols
        if rtype in (R_26, R_PC16):
            return "excl", "CALL-GAP"
        stats["data_in_gap"] += 1
    elif cls == "other":     # .bss2-6 / .rdata input sections hold data too
        stats["data_in:" + sec] += 1
    names = [symname] if named else (h.at.get(t, []) + objsyms_at_t)
    if any(n.startswith(("jtbl_", "jpt_")) for n in names):
        return "excl", "JTBL"
    if not named and not names:
        return "anon", (h.alias, t)
    return "unit", ("data", h.vbase, t)


def resolve_sym(b, obj, osecs, sym):
    """-> (named, name, address or None, why) for a symbol of the .o, seen from binary b."""
    name, value, _size, typ, bind, shndx = sym
    if shndx == SHN_ABS:
        return True, name, value, None
    if shndx in (SHN_UNDEF, SHN_COMMON):
        v = b.glob.get(name)
        if v is None:
            lv = b.loc.get(name, [])
            v = lv[0] if len(lv) == 1 else None
        return True, name, v, (None if v is not None else "UNRESOLVED")
    sec = osecs[shndx][0]
    a = b.place.get((obj, sec))
    if a is None:
        if typ != STT_SECTION and bind in (1, 2) and name in b.glob:   # discarded weak copy: the linker's definition
            return True, name, b.glob[name], None
        return typ != STT_SECTION, name, None, "UNPLACED-TARGET-SECTION:" + sec
    return typ != STT_SECTION, name, a + value, None


def work_bin(alias):
    b = BINS[alias]
    keys = collections.Counter()
    excl = collections.Counter()
    anon = collections.Counter()
    interior = set()
    stats = collections.Counter()
    hi16 = 0
    raw = 0
    for obj in b.objs:
        secs, syms, rels = parse_obj(os.path.join(REPO, obj))
        # .o symbols by linked address (non-section, defined), for the LITERAL test
        oat = collections.defaultdict(list)
        for s in syms:
            if s[0] and s[3] not in (STT_SECTION, STT_FILE) and 0 < s[5] < len(secs):
                a = b.place.get((obj, secs[s[5]][0]))
                if a is not None:
                    oat[a + s[1]].append(s[0])
        for tsec, tflags, ents in rels:
            raw += len(ents)
            cls = sec_class(tsec)
            if cls == "other":
                excl[("NONALLOC:" if not tflags & 2 else "SECTION:") + tsec] += len(ents)
                continue
            base = b.place.get((obj, tsec))
            if base is None:
                excl["UNPLACED-SOURCE-SECTION:" + tsec] += len(ents)
                continue
            last_hi = {}
            for i, (off, rtype, si, word) in enumerate(ents):
                A = base + off
                if rtype == R_HI16:
                    last_hi[si] = word
                named, name, S, why = resolve_sym(b, obj, secs, syms[si])
                if why:
                    excl[why] += 1
                    continue
                if named:
                    T = S
                elif rtype == R_32:
                    T = (S + word) & 0xFFFFFFFF
                elif rtype == R_26:
                    T = S + ((word & 0x3FFFFFF) << 2)
                elif rtype == R_PC16:
                    T = S + (sext16(word & 0xFFFF) << 2) + 4
                elif rtype == R_HI16:
                    lo = next((e for e in ents[i + 1:] if e[1] == R_LO16 and e[2] == si), None)
                    if lo is None:
                        excl["HI16-UNPAIRED"] += 1
                        continue
                    T = (S + ((word & 0xFFFF) << 16) + sext16(lo[3] & 0xFFFF)) & 0xFFFFFFFF
                elif rtype == R_LO16:
                    hw = last_hi.get(si)
                    if hw is None:
                        excl["LO16-UNPAIRED"] += 1
                        continue
                    T = (S + ((hw & 0xFFFF) << 16) + sext16(word & 0xFFFF)) & 0xFFFFFFFF
                else:
                    excl["RTYPE:%d" % rtype] += 1
                    continue
                kind, val = classify_target(b, T, named, name, rtype, [] if named else oat.get(T, []), stats)
                if kind == "excl" and val == "TEXT-INTERIOR":
                    if cls == "data":
                        interior.add(A)
                    val = "JTBL-CASE" if cls == "data" else "LOCAL-LABEL"
                if kind == "excl":
                    excl[val] += 1
                    continue
                if kind == "anon":
                    anon[val] += 1
                    continue
                # source body
                if cls == "text":
                    r = b.sig_at(A)
                    if r is not None:
                        src, soff = r[2], A - r[0]
                    else:
                        j = bisect.bisect_right(b.funcs, A) - 1
                        f = b.funcs[j] if j >= 0 else 0
                        src, soff = ("raw", alias, f), A - f
                        stats["raw_src"] += 1
                else:
                    j = bisect.bisect_right(b.datas, A) - 1
                    o0 = max(lo for lo, _hi in b.outsecs if lo <= A)
                    s0 = b.datas[j] if j >= 0 and b.datas[j] >= o0 else o0
                    src, soff = (b.vbase, s0), A - s0
                if rtype == R_HI16:
                    hi16 += 1
                    continue
                keys[(src, soff, rtype, val)] += 1
    return alias, keys, excl, anon, interior, stats, hi16, raw


# ------------------------------------------------------------------------------------------ controls
def objdump_scan(obj, names):
    """-> (reloc line count, {name: non-HI16 refs in text/data sections})."""
    out = subprocess.run([OBJDUMP, "-r", os.path.join(REPO, obj)], capture_output=True, text=True, check=True).stdout
    n, hits, sec = 0, collections.Counter(), None
    for ln in out.splitlines():
        if ln.startswith("RELOCATION RECORDS FOR ["):
            sec = ln[len("RELOCATION RECORDS FOR ["):-2]
            continue
        p = ln.split()
        if len(p) == 3 and re.fullmatch(r"[0-9a-f]{8}", p[0]):
            n += 1
            if sec_class(sec) != "other" and p[1] != "R_MIPS_HI16":
                v = re.split(r"[+-]0x", p[2])[0]
                if v in names:
                    hits[v] += 1
    return n, hits


# ------------------------------------------------------------------------------------------ struct ownership
FUNC_NAME = re.compile(r"^func_([0-9A-Fa-f]{8})$")
DATA_NAME = re.compile(r"^D_([0-9A-Fa-f]{8})$")
UNK = re.compile(r"\b(Unkstruct_\w+)")


def data_space(b, t):
    """c1's space rule for a datum at t seen from binary b: b's image, main's, resident's, a slot's (first base), else abs."""
    for h in (b, BINS["main"], BINS["resident"]):
        if h.vbase <= t < h.end:
            return h.vbase
    hits = [s for s in SLOTS if s[0] <= t < s[1]]
    return hits[0][0] if hits else None


def scan_includes(rel):
    """-> (rel, [(included file, active SHARED_FN or None)]) of one src file (masked text, asm alias decls applied)."""
    text = open(os.path.join(REPO, rel), errors="surrogateescape").read()
    if "include" not in text:
        return rel, []
    masked = sc.mask_text(text)
    aliases = dict(sc.alias_decls(masked))
    ev = [(m.start(), 0, m.group(1)) for m in sc.SHARED_FN_DEF.finditer(masked)]
    ev += [(m.start(), 1, "") for m in sc.SHARED_FN_UNDEF.finditer(masked)]
    ev += [(m.start(), 2, m.group(1)) for m in sc.INCLUDE_LINE.finditer(masked)]
    out, cur = [], None
    for _p, kind, val in sorted(ev):
        if kind == 0:
            cur = aliases.get(val, val)
        elif kind == 1:
            cur = None
        else:
            for cand in (os.path.join(os.path.dirname(rel), val), os.path.join("src", val), os.path.join("include", val)):
                cand = os.path.normpath(cand)
                if os.path.isfile(os.path.join(REPO, cand)):
                    out.append((cand, cur))
                    break
    return rel, out


def ownership(aliases, dirs, data_set, jobs):
    """own(d) = sum over struct types T held by data unit d of reach(T) / holders(T). -> (own, owner, info)."""
    sm = json.load(open(os.path.join(REPO, CENSUS, "struct_map.json")))
    types = collections.defaultdict(list)       # name -> holder names; same-named entries (distinct ids) are one C name
    for t in sm["types"]:
        types[t["name"]] += t.get("globals_at", []) + t.get("globals_ptr", [])
    dir_al = collections.defaultdict(list)
    for a in aliases:
        dir_al[dirs[a]].append(a)            # a twin's dir is its primary's: both aliases
    tu_memo = {}

    def tu_aliases(tu):
        if tu not in tu_memo:
            d = os.path.dirname(tu)
            while d and d not in dir_al and not d.startswith("src/shared"):
                d = os.path.dirname(d)
            tu_memo[tu] = sorted(dir_al.get(d, []))
        return tu_memo[tu]
    name2addr = {}
    for a in aliases:
        m = {}
        for v, n in sorted(BINS[a].cur.items()):
            m.setdefault(n, v)
        name2addr[a] = m
    sigstart = {a: {r[0]: r[2] for r in BINS[a].sig} for a in aliases}

    def faddr(a, fn):
        m = FUNC_NAME.match(fn)
        if m:
            return int(m.group(1), 16)
        v = name2addr[a].get(fn)
        return BINS[a].glob.get(fn) if v is None else v

    def resolve(als, fn):
        if not als:
            return "NO-ALIAS"
        hs, found = set(), False
        for a in als:
            v = faddr(a, fn)
            if v is None:
                continue
            found = True
            if v in sigstart[a]:
                hs.add(sigstart[a][v])
        return frozenset(hs) if hs else ("NO-SIG" if found else "NO-ADDR")
    # include graph of src (nested includes followed; an inner #define SHARED_FN wins over the includer's)
    files = sorted(os.path.relpath(os.path.join(dp, f), REPO) for dp, _d, fs in os.walk(os.path.join(REPO, "src"))
                   for f in fs if f.endswith((".c", ".h")))
    edges = collections.defaultdict(list)
    with get_context("fork").Pool(jobs) as pool:
        for rel, out in pool.map(scan_includes, files, chunksize=64):
            for tgt, v in out:
                edges[tgt].append((rel, v))
    xmemo = {}

    def expand(hdr, stack=()):
        if hdr in xmemo:
            return xmemo[hdr]
        res = []
        for f, v in edges.get(hdr, []):
            if f.endswith(".c"):
                res.append((f, v))
            elif f not in stack:
                res.extend((c, v or w) for c, w in expand(f, stack + (hdr,)))
        xmemo[hdr] = res
        return res
    info = collections.Counter()
    bmemo = {}

    def bodies_of(tu, fn, header):
        k = (tu, fn)
        if k not in bmemo:
            if fn is None:
                res = "NO-FN (macro definition line)"
            elif not header:
                res = resolve(tu_aliases(tu), fn)
            else:
                inc = expand(tu)
                hs, causes = set(), collections.Counter()
                for c, v in inc:
                    name = v if fn == "SHARED_FN" else fn
                    r = "HEADER-INCLUDE-NO-SHARED_FN" if name is None else resolve(tu_aliases(c), name)
                    if isinstance(r, str):
                        causes[r] += 1
                    else:
                        hs |= r
                info["header include sites unresolved"] += sum(causes.values())
                res = frozenset(hs) if hs else ("HEADER-" + min(causes) if causes else "HEADER-NOT-INCLUDED")
            bmemo[k] = res
        return bmemo[k]

    def site_aliases(r):
        if not r["header"]:
            return tu_aliases(r["tu"])
        return sorted({a for c, _v in expand(r["tu"]) for a in tu_aliases(c)})
    reach = collections.defaultdict(set)
    hold_names = collections.defaultdict(set)    # T -> {(name, aliases)}
    name_als = collections.defaultdict(set)      # global/gaddr base name -> aliases of its sites
    unmapped = collections.Counter()
    nsites = typed = 0
    with open(os.path.join(REPO, CENSUS, "sites.jsonl")) as f:
        for ln in f:
            nsites += 1
            r = json.loads(ln)
            ts = set()
            if r.get("type") in types:
                ts.add(r["type"])
            m = UNK.search(r.get("ctype") or "")
            if m and m.group(1) in types:
                ts.add(m.group(1))
            hb = r["bclass"] in ("global", "gaddr") and r.get("base")
            if not ts and not hb:
                continue
            als = tuple(site_aliases(r))
            if hb:
                name_als[r["base"]].update(als)
            if not ts:
                continue
            typed += 1
            bs = bodies_of(r["tu"], r["fn"], r["header"])
            if isinstance(bs, str):
                unmapped[bs] += 1
            else:
                for T in ts:
                    reach[T] |= bs
            if hb:
                for T in ts:
                    hold_names[T].add((r["base"], als))
    for T in sorted(types):
        for n in types[T]:
            als = tuple(sorted(name_als.get(n) or [a for a in aliases if n in BINS[a].glob] or ["main"]))
            hold_names[T].add((n, als))
    rmemo, unres = {}, {}

    def hunits(n, als):
        if (n, als) not in rmemo:
            us, why = set(), "NO-ADDRESS"
            for a in als:
                b = BINS[a]
                t = b.glob.get(n)
                if t is None:
                    lv = b.loc.get(n, [])
                    t = lv[0] if len(lv) == 1 else name2addr[a].get(n)
                if t is None:
                    m = DATA_NAME.match(n)
                    t = int(m.group(1), 16) if m else None
                if t is None:
                    continue
                u = ("data", data_space(b, t), t)
                if u in data_set:
                    us.add(u)
                else:
                    why = "NO-DATA-UNIT %s:%08X" % (h8(u[1]), t)
            if not us:
                unres[n] = why
            rmemo[(n, als)] = us
        return rmemo[(n, als)]
    holders = {}
    for T in sorted(hold_names):
        hs = set()
        for n, als in sorted(hold_names[T]):
            hs |= hunits(n, als)
        if hs:
            holders[T] = hs
    own, owner = collections.defaultdict(float), {}
    for T in sorted(holders):
        share = len(reach[T]) / len(holders[T])
        for d in holders[T]:
            own[d] += share
            best = owner.get(d)
            if best is None or (-len(reach[T]), T) < (-len(reach[best]), best):
                owner[d] = T
    resolved = {n for (n, _a), us in rmemo.items() if us}
    info.update({"sites": nsites, "typed sites": typed, "types": len(types), "type entries": len(sm["types"]),
                 "types with reach": sum(1 for T in types if reach[T]), "types with holders": len(holders),
                 "types with reach and holders": sum(1 for T in holders if reach[T]),
                 "holder names resolved": len(resolved), "holder names unresolved": len(set(unres) - resolved),
                 "data units owning": len(own), "own total": round(sum(own.values()), 3)})
    unres = {n: w for n, w in unres.items() if n not in resolved}
    return own, owner, {"head": sm["head"], "info": info, "unmapped": unmapped, "unresolved": unres}


def render_md(rows, kinds, total_refs, raw, attributed, hi16, excl, stats, oinfo, report, nbins, all_objs, placed):
    """docs/leverage.md: the ranking's method, weights, denominators, controls and top 50 (no dates, no HEAD)."""
    oi = oinfo["info"]
    pct = lambda a, b: "%.1f%%" % (100.0 * a / b) if b else "n/a"
    top = lambda n: sum(r["refs"] for r in rows[:n])
    L = ["<!-- generated by tools/leverage_rank.py; do not edit; regenerate: /usr/bin/python3 tools/leverage_rank.py -j 16 -->",
         "# Leverage ranking: functions and data by unique-body references", "",
         "Generated by `tools/leverage_rank.py` with `docs/leverage.tsv` (one row per unit, sorted by score). "
         "`leverage_rank.py --check` regenerates both in memory and byte-compares them.", "",
         "## Inputs",
         f"- `build/`: linker maps, ELFs and .o files of {nbins} binaries; {len(all_objs)} objects "
         f"({len(placed)} placed, {len(all_objs) - len(placed)} unlinked).",
         f"- `.run/sig.<alias>.jsonl`: {sum(len(BINS[a].sig) for a in ORDER)} sig rows (h_exact per function instance).",
         f"- `{CENSUS}/struct_map.json` (`tools/type_census.py`): {oi['type entries']} type entries, "
         f"{oi['types']} distinct names (same-named entries are one C name and merge).",
         f"- `{CENSUS}/sites.jsonl` (`tools/type_census.py --sites`, same run): {oi['sites']} site rows, "
         f"{oi['typed sites']} typed by a struct_map type (`type`, or a C-form `ctype` naming one).",
         "- The tool refuses to run when `git diff --quiet <census head> HEAD -- src include` fails (regenerate the census first); "
         "the head is not printed here, so a census regenerated at a new HEAD with unchanged src/include keeps `--check` green.", "",
         "## Columns",
         "- `key`: h_exact[:12] (func), `raw:<space>:<addr>` (func with no sig row), `<space>:<addr>` (data). `space`: vram base of "
         "the image holding the address (`abs` outside every image). `addr`: exemplar address. `named`: yes/partial/no. `refs`: "
         "unique-body references. `bodies`: distinct source bodies. `nins`: instructions of the body (sig funcs only). `addrs`: "
         "distinct instance addresses. `fan`: instances (func) or referencing binaries (data). `binaries`: referencing binaries. "
         "`own`: struct ownership credit. `owner`: the held type of largest reach. `rank43`: rank among the units 3.43 may name.", "",
         "## Method",
         "- Every relocation of every object (all sections) is attributed to a source body and a target unit, or to a named "
         "exclusion; unattributed must be 0. A text source body is the sig row containing the place (h_exact, offset), so a body "
         "linked into many binaries counts once; a data source is the nearest preceding data symbol of its output section.",
         "- Units: `func` = one h_exact (every instance of one body); `func` `raw:<space>:<addr>` = a target with no sig row that "
         "starts an ELF FUNC or global symbol; `data` = (space, addr). Space: the binary's own image (its VRAM base), else main's, "
         "else resident's, else another image's slot base, else `abs`.",
         "- References are deduplicated to unique-body keys (source body, offset, reloc type, target unit); HI16 halves are "
         "counted once through their LO16.",
         "- Struct ownership: each typed site's body (tu, fn) maps to the h_exact it compiles into (non-header: the TU's alias "
         "and the function's address; a `src/shared/**` header: every include site in src with its active `SHARED_FN`, nested "
         "includes followed). reach(T) = distinct h_exact over all sites typed T. holders(T) = distinct data units named by a "
         "global/gaddr site typed T, plus T's `globals_at`/`globals_ptr`, resolved through the TU alias's symbols, then the space rule.",
         "", "## Weights",
         "`score = (refs + own) x (1 + log10(fan))`, printed with 3 decimals; ties by refs, kind, key.",
         "- **refs**, 1 per unique-body reference: one occurrence of the name in the one-text-per-body source, so one rename "
         "rewrites exactly refs sites.",
         "- **own** = sum over struct types T held by the unit of reach(T) / holders(T): a global is where a struct type gets its "
         "name, and every body using the type reads that name; the reach is split among the holders so each type is credited once.",
         "- **fan factor** `1 + log10(fan)` (fan = instances for a function, referencing binaries for a datum): a name reaches "
         "every instance's symbol stack and Ghidra view for one decision but adds no source occurrence. Damped, not linear: "
         "`nins x reach` over-counted (docs/decision-log.md:1655-1667).",
         "", "## Denominators",
         f"- Relocations: raw {raw} = attributed {attributed} + hi16 {hi16} + excluded {sum(excl.values())}.",
         "- Exclusions: " + ", ".join(f"{bk} {excl[bk]}" for bk in sorted(excl)) + ".",
         f"- TEXT-NOSIG before units {stats['was:TEXT-NOSIG']} (raw func units {stats['was:TEXT-NOSIG:raw']}, left {excl['TEXT-NOSIG']}); "
         f"TEXT-INTERIOR before {stats['was:TEXT-INTERIOR']} (raw func units {stats['was:TEXT-INTERIOR:raw']}, "
         f"JTBL-CASE {excl['JTBL-CASE']} from data words, LOCAL-LABEL {excl['LOCAL-LABEL']} from text).",
         f"- Unique refs {total_refs}. Top 100 by score cover {top(100)} ({pct(top(100), total_refs)}); top 500 cover "
         f"{top(500)} ({pct(top(500), total_refs)}).",
         "- Units ranked: " + "; ".join(f"{k} {sum(1 for r in rows if f(r))} (refs > 0: {sum(1 for r in rows if f(r) and r['refs'])})"
                                        for k, f in kinds.items()) + f"; total {len(rows)}.",
         "- Already named (`named` = yes): " + "; ".join(f"{k} {sum(1 for r in rows if f(r) and r['named'] == 'yes')}"
                                                         for k, f in kinds.items()) + ".",
         ]
    can = [r for r in rows if r["named"] != "yes"]
    t43 = [r for r in can if r["rank43"] <= 500]
    can_refs, t43_refs = sum(r["refs"] for r in can), sum(r["refs"] for r in t43)
    L += ["- Units 3.43 may name (`named` != yes): " + "; ".join(f"{k} {sum(1 for r in can if f(r))}" for k, f in kinds.items())
          + f"; total {len(can)} holding {can_refs} refs. The top 500 of those (`rank43` <= 500: "
          + ", ".join(f"{k} {sum(1 for r in t43 if f(r))}" for k, f in kinds.items())
          + f") cover {t43_refs} refs: {pct(t43_refs, total_refs)} of all unique refs, {pct(t43_refs, can_refs)} of the nameable units' refs.",
          f"- Ownership: {oi['types with reach']} of {oi['types']} types have reach; {oi['types with holders']} have a resolved holder "
          f"({oi['types with reach and holders']} both); {oi['data units owning']} data units own, total own {oi['own total']}. "
          f"Holder names resolved {oi['holder names resolved']}, unresolved {oi['holder names unresolved']} (printed by the tool).",
          f"- Typed sites unmapped to a body: {sum(oinfo['unmapped'].values())}"
          + ("" if not oinfo["unmapped"] else " (" + ", ".join(f"{k} {v}" for k, v in sorted(oinfo["unmapped"].items())) + ")")
          + f"; header include sites that resolved no body {oi['header include sites unresolved']}.",
          "", "## Controls"]
    L += ["- " + ln.strip() for ln in report if ln.strip().startswith("control")]
    L += ["", "## Top 50", "", "| rank | kind | key | name | named | refs | own | fan | score | owner |",
          "|---:|---|---|---|---|---:|---:|---:|---:|---|"]
    for r in rows[:50]:
        L.append(f"| {r['rank']} | {r['kind']} | {r['key']} | {r['name']} | {r['named']} | {r['refs']} | {r['own']:.3f} | "
                 f"{r['fan']} | {r['score']:.3f} | {r['owner']} |")
    L += ["", "## Known limits",
          "- Param-typed structs credit no unit: a type seen only through parameters and locals has reach but no holder.",
          "- Slot-space conflation: overlays sharing a VRAM base share one space, so `data` and `raw:` units at the same slot "
          "address in different overlays pool into one unit.",
          "- `abs` space: targets outside every image (main's bss past its last section, fixed addresses) form one space with no binary.",
          "- `globals_at`/`globals_ptr` are capped at 20 names per type; the full holder set comes from the sites.", ""]
    return "\n".join(L)


def run_pool(fn, items, jobs):
    with get_context("fork").Pool(jobs) as pool:
        return pool.map(fn, items, chunksize=1)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("-j", type=int, default=os.cpu_count())
    ap.add_argument("--check", action="store_true")
    args = ap.parse_args()
    os.chdir(REPO)
    head = re.match(r'\{"head": "(\w+)"', open(os.path.join(REPO, CENSUS, "struct_map.json")).read(64)).group(1)
    if subprocess.run(["git", "diff", "--quiet", head, "HEAD", "--", "src", "include"]).returncode != 0:
        sys.exit(f"leverage_rank: {CENSUS} (head {head}) is stale against HEAD for src/include: run "
                 "/usr/bin/python3 tools/type_census.py -j 16 --sites first")
    aliases, _dirs = sc.fleet_and_dirs()
    VB.update(sc.vram_bases())
    ORDER.extend(aliases)
    # stage A
    for b in run_pool(load_bin, aliases, args.j):
        BINS[b.alias] = b
    setup_slots()
    all_objs = sorted(os.path.relpath(os.path.join(dp, f), REPO) for dp, _d, fs in os.walk(os.path.join(REPO, "build"))
                      for f in fs if f.endswith(".o"))
    placed = sorted({o for a in aliases for o in BINS[a].objs})
    missing = sorted(set(placed) - set(all_objs))
    if missing:
        sys.exit(f"leverage_rank: maps place objects not on disk: {missing[:5]}")
    unlinked = sorted(set(all_objs) - set(placed))
    # stage B (largest binaries first for balance; merged in sorted order)
    big_first = sorted(aliases, key=lambda a: (-len(BINS[a].objs), a))
    res = {r[0]: r for r in run_pool(work_bin, big_first, args.j)}
    keys, key_bins = {}, collections.defaultdict(set)
    excl, anon, stats = collections.Counter(), collections.Counter(), collections.Counter()
    interior = {}
    hi16 = raw = 0
    for a in aliases:
        _a, k, e, an, it, st, h, r = res[a]
        for key, c in k.items():
            keys[key] = keys.get(key, 0) + c
            key_bins[key].add(a)
        excl.update(e)
        anon.update(an)
        stats.update(st)
        interior[a] = it
        hi16 += h
        raw += r
    for (holder, t), c in sorted(anon.items()):
        excl["JTBL" if t in interior[holder] else "LITERAL"] += c
    un_relocs = sum(obj_reloc_count(o) for o in unlinked)
    excl["UNLINKED-OBJECT"] += un_relocs
    raw += un_relocs
    attributed = sum(keys.values())
    unattributed = raw - attributed - hi16 - sum(excl.values())
    # units
    inst = collections.defaultdict(list)    # h_exact -> [(alias, addr, name)]
    hnins = {}                              # h_exact -> instructions of the body (equal bytes, equal count)
    for a in aliases:
        for addr, _n, h, name in BINS[a].sig:
            inst[h].append((a, addr, BINS[a].cur.get(addr) or name))
            hnins[h] = _n
    refs, bodies, ubins = collections.Counter(), collections.defaultdict(set), collections.defaultdict(set)
    for key in sorted(keys, key=repr):
        src, _off, _rt, unit = key
        refs[unit] += 1
        bodies[unit].add(src)
        ubins[unit].update(key_bins[key])

    def spell(n, addr):
        if not n:
            return "func_%08X" % addr
        m = FUNC_NAME.match(n)
        return "func_%08X" % int(m.group(1), 16) if m else n

    def row(kind, key, space, addr, sym, name, u, nins, addrs, fan):
        return dict(kind=kind, key=key, space=h8(space) if not isinstance(space, str) else space, addr=h8(addr), sym=sym,
                    name=name, named="yes" if name and not PLACEHOLDER.match(name) else "no", refs=refs[u],
                    bodies=len(bodies[u]), nins=nins, addrs=addrs, fan=fan, binaries=len(ubins[u]), u=u, own=0.0, owner="")
    rows = []
    for h in sorted(inst):
        il = sorted(inst[h])
        nm = [bool(n) and not PLACEHOLDER.match(n) for _a, _ad, n in il]
        ex = il[0]
        u = ("func", h)
        r = row("func", h[:12], BINS[ex[0]].vbase, ex[1], ex[2] or "", spell(ex[2], ex[1]), u, hnins[h],
                len({ad for _a, ad, _n in il}), len(il))
        r["named"] = "yes" if all(nm) else ("partial" if any(nm) else "no")
        rows.append(r)
    if len({r["key"] for r in rows}) != len(rows):
        sys.exit("leverage_rank: h_exact[:12] is not unique")
    for u in sorted(u for u in refs if u[0] == "func" and u[1].startswith("raw:")):
        _r, sp, ad = u[1].split(":")
        t = int(ad, 16)
        hold = [a for a in aliases if h8(BINS[a].vbase) == sp and t in BINS[a].fstart]
        sym = min((bool(PLACEHOLDER.match(BINS[a].fstart[t])), BINS[a].fstart[t]) for a in hold)[1]
        rows.append(row("func", u[1], sp, t, sym, spell(sym, t), u, "", 1, len(hold)))
    data_units = sorted((u for u in refs if u[0] == "data"), key=lambda u: (u[1] is not None, u[1] or 0, u[2]))
    own, owner, oinfo = ownership(aliases, _dirs, set(data_units), args.j)
    for u in data_units:
        _k, space, addr = u
        name = ""
        for a in sorted(ubins[u]):
            cand = sorted(BINS[a].at.get(addr, []), key=lambda n: ("." in n, bool(PLACEHOLDER.match(n)), n))
            if cand:
                name = cand[0]
                break
        r = row("data", f"{h8(space)}:{addr:08X}", space, addr, name, name, u, "", 1, len(ubins[u]))
        r["own"], r["owner"] = own.get(u, 0.0), owner.get(u, "")
        rows.append(r)
    for r in rows:
        r["score"] = (r["refs"] + r["own"]) * (1 + math.log10(max(r["fan"], 1)))
    rows.sort(key=lambda r: (-r["score"], -r["refs"], r["kind"], r["key"]))
    total_refs = sum(r["refs"] for r in rows)
    n43 = 0
    for i, r in enumerate(rows, 1):
        r["rank"] = i
        if r["named"] != "yes":
            n43 += 1
        r["rank43"] = n43 if r["named"] != "yes" else ""
    cols = ["rank", "kind", "key", "space", "addr", "name", "named", "refs", "bodies", "nins", "addrs", "fan", "binaries",
            "own", "owner", "score", "rank43"]
    lines, cum = ["\t".join(cols + ["cum_share"])], 0
    for r in rows:
        cum += r["refs"]
        lines.append("\t".join("%.3f" % r[c] if c in ("own", "score") else str(r[c]) for c in cols) + "\t%.6f" % (cum / total_refs))
    tsv = "\n".join(lines) + "\n"
    # report
    kinds = collections.OrderedDict((("func (sig)", lambda r: r["kind"] == "func" and not r["key"].startswith("raw:")),
                                     ("func (raw)", lambda r: r["key"].startswith("raw:")), ("data", lambda r: r["kind"] == "data")))
    out = []
    say = out.append
    say(f"leverage_rank: {len(aliases)} binaries, objects {len(all_objs)} (placed {len(placed)}, unlinked {len(unlinked)})")
    say(f"  relocations raw {raw}  attributed {attributed}  hi16 {hi16}  excluded {sum(excl.values())}  unattributed {unattributed}")
    for bk in sorted(excl):
        say(f"  excl {bk:34s} {excl[bk]}")
    for was in ("TEXT-NOSIG", "TEXT-INTERIOR"):
        rest = excl[was] if was == "TEXT-NOSIG" else excl["JTBL-CASE"] + excl["LOCAL-LABEL"]
        say(f"  {was} before {stats['was:' + was]}  -> raw func units {stats['was:' + was + ':raw']}  "
            + (f"left {rest}" if was == "TEXT-NOSIG" else f"JTBL-CASE {excl['JTBL-CASE']}  LOCAL-LABEL {excl['LOCAL-LABEL']}"))
    say(f"  unique refs {len(keys)} (total refs {total_refs})  units " + "  ".join(
        f"{k} {sum(1 for r in rows if f(r))} (refs>0 {sum(1 for r in rows if f(r) and r['refs'])})" for k, f in kinds.items())
        + f"  raw-source refs {stats['raw_src']}  slot multi-base {stats['slot_multi_base']}")
    say("  data targets outside the listed sections: " + "  ".join(f"{k} {v}" for k, v in sorted(stats.items())
                                                                 if k.startswith("data_in")))
    oi = oinfo["info"]
    say(f"  ownership (struct_map head {oinfo['head']}): " + "  ".join(f"{k} {oi[k]}" for k in sorted(oi)))
    say(f"  unmapped typed sites {sum(oinfo['unmapped'].values())}: " + "  ".join(
        f"{k} {v}" for k, v in sorted(oinfo["unmapped"].items())))
    ur = collections.defaultdict(list)
    for n, w in sorted(oinfo["unresolved"].items()):
        ur[w.split(" ")[0]].append(n if w == "NO-ADDRESS" else f"{n}={w.split(' ')[1]}")
    for w in sorted(ur):
        say(f"  holder names resolving to no data unit, {w} {len(ur[w])}: " + " ".join(ur[w]))
    ok = unattributed == 0
    ctrl3 = attributed + hi16 + sum(excl.values()) == raw
    say(f"  control 3 (attributed+hi16+excluded == raw): {'PASS' if ctrl3 else 'FAIL'}")
    # control 2 candidates: global, refs >= 20, every referencing body single-instance
    src_bins = collections.defaultdict(set)
    for key, bs in key_bins.items():
        src_bins[key[0]].update(bs)

    def single(src):
        if isinstance(src, str):
            return len(inst[src]) == 1
        return len(src_bins[src]) == 1
    name_bins = collections.defaultdict(set)     # a control name must mean one thing fleet-wide
    for a in aliases:
        for _addr, _n, _h, nm in BINS[a].sig:
            name_bins[nm].add((a, "sig"))
        for v, nms in BINS[a].at.items():
            for nm in nms:
                name_bins[nm].add(a)
    picks = {}
    for r in rows:
        kind, u, name = r["kind"], r["u"], r["sym"]
        if kind in picks or r["refs"] < 20 or not name or "." in name or r["key"].startswith("raw:"):
            continue
        if kind == "func" and len(inst[u[1]]) != 1:
            continue
        if len({x[0] if isinstance(x, tuple) else x for x in name_bins[name]}) != 1:
            continue
        if not all(single(s) for s in bodies[u]):
            continue
        definer = inst[u[1]][0][0] if kind == "func" else sorted(ubins[u])[0]
        addr = inst[u[1]][0][1] if kind == "func" else u[2]
        if name not in BINS[definer].glob or set(BINS[definer].at.get(addr, [])) != {name}:
            continue
        picks[kind] = (name, r["refs"])
    names = {v[0] for v in picks.values()}
    with ThreadPoolExecutor(args.j) as ex:
        scans = list(ex.map(lambda o: objdump_scan(o, names), all_objs))
    mine = [obj_reloc_count(o) for o in all_objs]
    bad = [o for o, m, (n, _h) in zip(all_objs, mine, scans) if m != n]
    ctrl1 = not bad
    say(f"  control 1 (per-object reloc count == objdump -r): {'PASS' if ctrl1 else 'FAIL'}  "
        f"mine {sum(mine)} objdump {sum(s[0] for s in scans)} objects {len(all_objs)} mismatched {len(bad)} {bad[:3]}")
    pset = set(placed)
    grep = collections.Counter()
    for o, (_n, h) in zip(all_objs, scans):
        if o in pset:
            grep.update(h)
    ctrl2 = len(picks) == 2
    for kind in ("func", "data"):
        if kind not in picks:
            say(f"  control 2 {kind}: no candidate symbol")
            continue
        name, rf = picks[kind]
        good = grep[name] == rf
        ctrl2 = ctrl2 and good
        say(f"  control 2 {kind} {name}: refs {rf} objdump grep {grep[name]} {'PASS' if good else 'FAIL'}")
    passed = sum([ctrl1, ctrl2, ctrl3])
    say(f"  controls {passed}/3 PASS")
    print("\n".join(out))
    md = render_md(rows, kinds, total_refs, raw, attributed, hi16, excl, stats, oinfo, out, len(aliases), all_objs, placed)
    if args.check:
        diffs = [p for p, txt in ((OUT_TSV, tsv), (OUT_MD, md))
                 if (open(p).read() if os.path.exists(p) else None) != txt]
        print("  --check docs/leverage.tsv docs/leverage.md: " + ("IDENTICAL" if not diffs else
                                                                   "DIFFERS " + " ".join(os.path.relpath(p, REPO) for p in diffs)))
        return 0 if ok and passed == 3 and not diffs else 1
    if ok and passed == 3:
        open(OUT_TSV, "w").write(tsv)
        open(OUT_MD, "w").write(md)
        print(f"  wrote docs/leverage.tsv ({len(rows)} rows) and docs/leverage.md")
    return 0 if ok and passed == 3 else 1

if __name__ == "__main__":
    try:
        sys.exit(main())
    except Fail as e:
        sys.exit(f"leverage_rank: {e}")
