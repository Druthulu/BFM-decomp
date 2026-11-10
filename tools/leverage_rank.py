#!/usr/bin/env python3
"""leverage_rank.py: rank the fleet's functions and data by how many unique bodies reference them.

For every binary: read build/<dir>/<b>.map placements, parse each placed .o (ELF32 LE, SHT_REL, pure Python,
addends from the relocated word), and attribute every relocation (all sections) to a source body and a target unit,
or to a named exclusion. Unattributed must be 0 (else exit 1). References are deduplicated to unique-body keys
(source key, offset, reloc type, target unit), so the same body linked into many binaries counts once.

  source body: text -> sig row of b containing the place (h_exact, off); none -> ("raw", b, nearest FUNC <= A)
               data -> nearest preceding data symbol of b's output section ((space, sym), off)
  target unit: func (h_exact of the sig function starting at T in its holder) or data (space, addr)
  space:       b's own image -> its VRAM_BASE; else main's; else resident's; else another image (slot); else abs

Controls: (1) per-object reloc count == `objdump -r` reloc lines; (2) one function and one datum: refs == an
independent objdump grep of the name; (3) attributed multiplicity + hi16 + excluded == raw total.
Writes docs/leverage.tsv (provisional score = refs). `--check` recomputes in memory and byte-compares (exit 1 on
any difference; skips the objdump controls). Usage: leverage_rank.py [-j N] [--check]
"""
import argparse, bisect, collections, os, re, struct, subprocess, sys
from concurrent.futures import ThreadPoolExecutor
from multiprocessing import get_context

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import share_census as sc  # noqa: E402


class Fail(Exception):
    """Raised in workers (a sys.exit there kills the worker and hangs the pool)."""

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OBJDUMP = "mipsel-linux-gnu-objdump"
OUT_TSV = os.path.join(REPO, "docs", "leverage.tsv")
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
        if typ == STT_FUNC:
            funcs.add(value)
        elif b.cls_at(value)[0] == "data":
            datas.add(value)
    b.funcs = sorted(funcs)
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
    if r is not None:
        if r[0] == t:
            return "unit", ("func", r[2])
        return "excl", "TEXT-INTERIOR"
    cls, sec = h.cls_at(t)
    if cls == "text":
        return "excl", "TEXT-NOSIG"
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
                if cls == "data" and kind == "excl" and val == "TEXT-INTERIOR":
                    interior.add(A)
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


def run_pool(fn, items, jobs):
    with get_context("fork").Pool(jobs) as pool:
        return pool.map(fn, items, chunksize=1)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("-j", type=int, default=os.cpu_count())
    ap.add_argument("--check", action="store_true")
    args = ap.parse_args()
    os.chdir(REPO)
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
    for a in aliases:
        for addr, _n, h, name in BINS[a].sig:
            inst[h].append((a, addr, BINS[a].cur.get(addr) or name))
    refs, bodies, ubins = collections.Counter(), collections.defaultdict(set), collections.defaultdict(set)
    for key in sorted(keys, key=repr):
        src, _off, _rt, unit = key
        refs[unit] += 1
        bodies[unit].add(src)
        ubins[unit].update(key_bins[key])
    rows = []
    for h in sorted(inst):
        il = sorted(inst[h])
        nm = [bool(n) and not PLACEHOLDER.match(n) for _a, _ad, n in il]
        named = "yes" if all(nm) else ("partial" if any(nm) else "no")
        ex = il[0]
        u = ("func", h)
        rows.append(["func", h[:12], h8(BINS[ex[0]].vbase), h8(ex[1]), ex[2] or "", named,
                     refs[u], len(bodies[u]), len(il), len(ubins[u]), u])
    if len({r[1] for r in rows}) != len(rows):
        sys.exit("leverage_rank: h_exact[:12] is not unique")
    data_units = sorted((u for u in refs if u[0] == "data"), key=lambda u: (u[1] is not None, u[1] or 0, u[2]))
    for u in data_units:
        _k, space, addr = u
        name = ""
        for a in sorted(ubins[u]):
            cand = sorted(BINS[a].at.get(addr, []), key=lambda n: ("." in n, bool(PLACEHOLDER.match(n)), n))
            if cand:
                name = cand[0]
                break
        rows.append(["data", f"{h8(space)}:{addr:08X}", h8(space), h8(addr), name,
                     "yes" if name and not PLACEHOLDER.match(name) else "no",
                     refs[u], len(bodies[u]), len(ubins[u]), len(ubins[u]), u])
    for r in rows:
        r.insert(10, r[6])           # provisional score = refs
    rows.sort(key=lambda r: (-r[10], -r[6], r[0], r[1]))
    total_refs = sum(r[6] for r in rows)
    lines, cum = ["rank\tkind\tkey\tspace\taddr\tname\tnamed\trefs\tbodies\tfan\tbinaries\tscore\tcum_share"], 0
    for i, r in enumerate(rows, 1):
        cum += r[6]
        lines.append("\t".join(str(x) for x in [i] + r[:11]) + "\t%.6f" % (cum / total_refs))
    tsv = "\n".join(lines) + "\n"
    # report
    nfunc = sum(1 for r in rows if r[0] == "func")
    print(f"leverage_rank: {len(aliases)} binaries, objects {len(all_objs)} (placed {len(placed)}, unlinked {len(unlinked)})")
    print(f"  relocations raw {raw}  attributed {attributed}  hi16 {hi16}  excluded {sum(excl.values())}  unattributed {unattributed}")
    for bk in sorted(excl):
        print(f"  excl {bk:34s} {excl[bk]}")
    print(f"  unique refs {len(keys)} (total refs {total_refs})  units func {nfunc} (refs>0 {sum(1 for r in rows if r[0] == 'func' and r[6])})"
          f"  data {len(data_units)}  raw-source refs {stats['raw_src']}  slot multi-base {stats['slot_multi_base']}")
    print("  data targets outside the listed sections: " + "  ".join(f"{k} {v}" for k, v in sorted(stats.items())
                                                                   if k.startswith("data_in")))
    ok = unattributed == 0
    ctrl3 = attributed + hi16 + sum(excl.values()) == raw
    print(f"  control 3 (attributed+hi16+excluded == raw): {'PASS' if ctrl3 else 'FAIL'}")
    if args.check:
        cur = open(OUT_TSV).read() if os.path.exists(OUT_TSV) else None
        same = cur == tsv
        print(f"  --check docs/leverage.tsv: {'IDENTICAL' if same else 'DIFFERS'}")
        return 0 if ok and ctrl3 and same else 1
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
        kind, u, name = r[0], r[11], r[4]
        if kind in picks or r[6] < 20 or not name or "." in name:
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
        picks[kind] = (name, r[6])
    names = {v[0] for v in picks.values()}
    with ThreadPoolExecutor(args.j) as ex:
        scans = list(ex.map(lambda o: objdump_scan(o, names), all_objs))
    mine = [obj_reloc_count(o) for o in all_objs]
    bad = [o for o, m, (n, _h) in zip(all_objs, mine, scans) if m != n]
    ctrl1 = not bad
    print(f"  control 1 (per-object reloc count == objdump -r): {'PASS' if ctrl1 else 'FAIL'}  "
          f"mine {sum(mine)} objdump {sum(s[0] for s in scans)} objects {len(all_objs)} mismatched {len(bad)} {bad[:3]}")
    pset = set(placed)
    grep = collections.Counter()
    for o, (_n, h) in zip(all_objs, scans):
        if o in pset:
            grep.update(h)
    ctrl2 = len(picks) == 2
    for kind in ("func", "data"):
        if kind not in picks:
            print(f"  control 2 {kind}: no candidate symbol")
            continue
        name, rf = picks[kind]
        good = grep[name] == rf
        ctrl2 = ctrl2 and good
        print(f"  control 2 {kind} {name}: refs {rf} objdump grep {grep[name]} {'PASS' if good else 'FAIL'}")
    passed = sum([ctrl1, ctrl2, ctrl3])
    print(f"  controls {passed}/3 PASS")
    if ok and passed == 3:
        open(OUT_TSV, "w").write(tsv)
        print(f"  wrote docs/leverage.tsv ({len(rows)} rows)")
    return 0 if ok and passed == 3 else 1


if __name__ == "__main__":
    try:
        sys.exit(main())
    except Fail as e:
        sys.exit(f"leverage_rank: {e}")
