#!/usr/bin/env python3
"""Link a single PsyQ ELF object so its `.text` is byte-identical to the BFM EXE.

This is the generalised form of the session-C SYS.o proof (cookbook §9): given a
PsyQ-SDK object (a `.LIB` member converted to ELF by psyq-obj-parser) and the vram
where the EXE links its `.text`, reproduce the EXE bytes exactly by:

  1. section sizes              — `objdump -h`
  2. locate .rdata/.data vram   — unique byte-search of the EXE (objcopy --only-section)
  3. recover externals          — read each undefined symbol's address straight out of the
                                  EXE's already-RESOLVED relocations (R_MIPS_26 jump field;
                                  HI16/LO16 immediate-field pair), minus the object addend
  4. alignment fix              — objcopy --set-section-alignment .text/.rdata/.data = 4
                                  (psyq-obj-parser emits 2**3; the original is 4-aligned, so
                                  an 8-align bumps a 4-but-not-8 vram +4)
  5. link                       — ld -T <SECTIONS placing each section at its vram>
                                  --defsym NAME=ADDR per recovered external
  6. verify                     — objcopy -O binary --only-section .text -> byte-compare

The byte-compare of `.text` is the ground-truth check (G3/P9). Externals defined by *other*
objects of the same library are recovered here too (single-object mode); the whole-library
wiring (2'.3) links them together so those resolve internally and only true externals def(
DMACallback, hardware) need --defsym.

Usage:
    psyq_link.py <obj.o> <text_vram> [--name NAME] [--quiet]
    -> prints PASS/FAIL + recovered externals; exit 0 on byte-identical .text.

Importable: link_object(obj, text_vram) -> dict(result).
"""
import struct, subprocess, sys, os, re, tempfile

EXE = "extracted/retail/SLUS_007.26"
VRAM_BASE = 0x8000F800
AS = "mipsel-linux-gnu-"


def sh(*a, **k):
    return subprocess.run(a, check=True, capture_output=True, **k)


def u32(buf, off):
    return struct.unpack_from("<I", buf, off)[0]


def s16(x):
    x &= 0xFFFF
    return x - 0x10000 if x & 0x8000 else x


def only_section(obj, sec):
    """Raw bytes of one section, or b'' if absent/empty."""
    try:
        return sh(f"{AS}objcopy", "-O", "binary", "--only-section", sec, obj, "/dev/stdout").stdout
    except subprocess.CalledProcessError:
        return b""


def section_table(obj):
    """{name: (size, align_pow)} from objdump -h."""
    out = sh(f"{AS}objdump", "-h", obj).stdout.decode()
    t = {}
    for ln in out.splitlines():
        m = re.match(r"\s+\d+\s+(\.\S+)\s+([0-9a-f]+)\s+[0-9a-f]+\s+[0-9a-f]+\s+[0-9a-f]+\s+2\*\*(\d+)", ln)
        if m:
            t[m.group(1)] = (int(m.group(2), 16), int(m.group(3)))
    return t


def undefined_syms(obj):
    out = sh(f"{AS}readelf", "-s", obj).stdout.decode()
    u = set()
    for ln in out.splitlines():
        p = ln.split()
        # Num: Value Size Type Bind Vis Ndx Name
        if len(p) >= 8 and p[6] == "UND" and p[7] and not p[7].startswith("."):
            u.add(p[7])
    return u


def text_relocs(obj):
    """Ordered (offset, type, sym) for .text relocations."""
    out = sh(f"{AS}readelf", "-r", obj).stdout.decode()
    relocs, in_text = [], False
    for ln in out.splitlines():
        if ln.startswith("Relocation section"):
            in_text = "'.rel.text'" in ln or '".rel.text"' in ln or ".rel.text" in ln
            continue
        if not in_text:
            continue
        m = re.match(r"\s*([0-9a-f]+)\s+[0-9a-f]+\s+(R_MIPS_\S+)\s+[0-9a-f]+\s+(\S+)", ln)
        if m:
            relocs.append((int(m.group(1), 16), m.group(2), m.group(3)))
    return relocs


SECTION_IDX_RE = re.compile(r"\s*\[\s*(\d+)\]\s+(\.\S+)")
DATA_SECTIONS = (".data", ".rdata", ".rodata", ".sdata", ".bss", ".sbss")


def section_index_names(obj):
    """{section index: name} from readelf -S."""
    out = sh(f"{AS}readelf", "-S", obj).stdout.decode()
    idx = {}
    for ln in out.splitlines():
        m = SECTION_IDX_RE.match(ln)
        if m:
            idx[int(m.group(1))] = m.group(2)
    return idx


def symbol_table(obj):
    """{name: (section_name|'UND'|'ABS', st_value)} from readelf -s."""
    idx = section_index_names(obj)
    out = sh(f"{AS}readelf", "-s", obj).stdout.decode()
    syms = {}
    for ln in out.splitlines():
        p = ln.split()
        # Num: Value Size Type Bind Vis Ndx Name
        if len(p) >= 8 and p[0].endswith(":") and re.fullmatch(r"[0-9a-f]+", p[1]):
            ndx, name = p[6], p[7]
            if name.startswith("."):
                continue
            if ndx in ("UND", "ABS"):
                sec = ndx
            elif ndx.isdigit():
                sec = idx.get(int(ndx), "?")
            else:
                continue
            syms[name] = (sec, int(p[1], 16))
    return syms


def recover_sym_addrs(obj, text_vram, exe):
    """Resolved EXE address of every symbol referenced by a .text relocation.

    Works for section symbols (name == '.data' etc.) and named data/bss/extern
    symbols alike: reads the already-linked field(s) out of the EXE and subtracts
    the object's in-field addend.  R_MIPS_26 (jump) and HI16/LO16 pairs.
    """
    text = only_section(obj, ".text")
    addr, pending_hi = {}, {}
    for off, typ, sym in text_relocs(obj):
        if typ == "R_MIPS_26":
            if sym not in addr:
                site = text_vram + off
                exew = u32(exe, site - VRAM_BASE)
                objw = u32(text, off)
                A = (objw & 0x03FFFFFF) << 2
                addr[sym] = ((((exew & 0x03FFFFFF) << 2) | (site & 0xF0000000)) - A) & 0xFFFFFFFF
        elif typ == "R_MIPS_HI16":
            pending_hi.setdefault(sym, []).append(off)
        elif typ == "R_MIPS_LO16":
            his = pending_hi.get(sym)
            if his:
                hi_off = his[-1]
                if sym not in addr:
                    ehi = u32(exe, text_vram + hi_off - VRAM_BASE) & 0xFFFF
                    elo = u32(exe, text_vram + off - VRAM_BASE) & 0xFFFF
                    ohi = u32(text, hi_off) & 0xFFFF
                    olo = u32(text, off) & 0xFFFF
                    addr[sym] = (((ehi << 16) + s16(elo)) - ((ohi << 16) + s16(olo))) & 0xFFFFFFFF
                pending_hi[sym] = his[:-1]
    return addr


def unique_byte_vram(obj, sec, exe):
    raw = only_section(obj, sec)
    if not raw:
        return None
    hits, start = [], 0
    while True:
        j = exe.find(raw, start)
        if j < 0:
            break
        hits.append(j + VRAM_BASE)
        start = j + 1
        if len(hits) > 1:
            return None  # ambiguous
    return hits[0] if hits else None


def link_object(obj, text_vram, name=None, exe_bytes=None):
    """Place .text at its EXE vram, --defsym every external it references, byte-verify.

    The robust model (validated against the psyq-obj-parser .bss-mislabelling: it packs
    common-style globals into per-object .bss with sequential st_values the original
    linker did NOT honour): trust NO st_value. Place only .text; DISCARD every other
    section; resolve every symbol the .text references by its address recovered from the
    EXE's already-linked relocations (R_MIPS_26 / HI16+LO16). Internal .text labels are
    left for ld to place. Discarding the defining section makes a --defsym of a
    once-defined symbol conflict-free, so this is uniform for externals, data, and bss.

    Section bases (.rdata/.data/.bss) are still computed — for the report and the
    whole-library build wiring (2'.3) — but they do not gate the .text verification.
    """
    name = name or os.path.basename(obj)
    exe = exe_bytes if exe_bytes is not None else open(EXE, "rb").read()
    secs = section_table(obj)
    tsize = secs.get(".text", (0, 0))[0]
    res = {"name": name, "text_vram": text_vram, "tsize": tsize}

    symtab = symbol_table(obj)
    sym_addr = recover_sym_addrs(obj, text_vram, exe)

    def sym_section(s):
        if s in secs:        # section symbol (.data/.rdata/.bss/…)
            return (s, 0)
        return symtab.get(s, ("UND", 0))

    # section bases for placement: byte-search (initialised) or the section-symbol reloc.
    bases = {}
    for S in DATA_SECTIONS:
        if S not in secs or secs[S][0] == 0:
            continue
        b = unique_byte_vram(obj, S, exe) if S not in (".bss", ".sbss") else None
        if b is None:
            b = sym_addr.get(S)          # set iff the object referenced the section symbol
        bases[S] = b
    placed = {S: b for S, b in bases.items() if b is not None}
    res["rdata_vram"] = bases.get(".rdata") or bases.get(".rodata")
    res["data_vram"] = bases.get(".data")
    res["bss_vram"] = bases.get(".bss")

    # Classify each referenced symbol: resolve by section placement, or by --defsym to its
    # recovered address — weakening a placed-but-mislabelled definition first (psyq-obj-parser
    # packs common-style globals into .bss with st_values the original linker did not honour).
    defs, weaken = {}, []
    for s, a in sym_addr.items():
        sec, val = sym_section(s)
        if sec == ".text":
            continue                                  # internal label -> ld placement
        if s in secs:                                 # a section symbol (.data/.bss/…)
            if s not in placed:
                defs[s] = a                           # its section was discarded
            continue
        if sec in placed and a == (placed[sec] + val) & 0xFFFFFFFF:
            continue                                  # genuine member -> ld placement
        defs[s] = a
        if sec in placed:
            weaken.append(s)                          # mislabelled inside a placed section
    externals = {s: a for s, a in defs.items() if sym_section(s)[0] == "UND"}
    res["externals"] = externals
    res["unrecovered"] = sorted(undefined_syms(obj) - set(externals))

    with tempfile.TemporaryDirectory(dir=".run") as td:
        aligned = os.path.join(td, "a.o")
        align_args = ["--set-section-alignment", ".text=4"]
        for S in placed:
            align_args += ["--set-section-alignment", f"{S}=4"]
        for s in weaken:
            align_args += ["--weaken-symbol", s]
        sh(f"{AS}objcopy", *align_args, obj, aligned)
        ld = os.path.join(td, "link.ld")
        lines = ["SECTIONS {", f"  . = 0x{text_vram:08X};", "  .text : { *(.text) }"]
        for S, b in placed.items():
            lines += [f"  . = 0x{b:08X};", f"  {S} : {{ *({S}) }}"]
        lines += ["  /DISCARD/ : { *(*) }", "}"]
        open(ld, "w").write("\n".join(lines) + "\n")
        cmd = [f"{AS}ld", "-T", ld, "-o", os.path.join(td, "out.elf"), aligned]
        for s, a in sorted(defs.items()):
            cmd += ["--defsym", f"{s}=0x{a:08X}"]
        p = subprocess.run(cmd, capture_output=True)
        if p.returncode != 0:
            res["ok"] = False
            res["error"] = "ld: " + p.stderr.decode().strip().split("\n")[-1]
            return res
        got = sh(f"{AS}objcopy", "-O", "binary", "--only-section", ".text",
                 os.path.join(td, "out.elf"), "/dev/stdout").stdout

    want = exe[text_vram - VRAM_BASE: text_vram - VRAM_BASE + tsize]
    res["ok"] = (got == want)
    if not res["ok"]:
        diffs = [i for i in range(0, min(len(got), len(want)), 4) if got[i:i+4] != want[i:i+4]]
        res["ndiff"] = len(diffs) + abs(len(got) - len(want)) // 4
        res["first_diff"] = (text_vram + diffs[0]) if diffs else None
    return res


def main():
    if len(sys.argv) < 3:
        sys.exit(__doc__)
    obj, text_vram = sys.argv[1], int(sys.argv[2], 0)
    name = None
    quiet = "--quiet" in sys.argv
    if "--name" in sys.argv:
        name = sys.argv[sys.argv.index("--name") + 1]
    r = link_object(obj, text_vram, name)
    tag = "PASS" if r["ok"] else "FAIL"
    print(f"[{tag}] {r['name']:14s} .text@0x{text_vram:08X} ({r['tsize']} B) "
          f".rdata@{r['rdata_vram'] if not isinstance(r['rdata_vram'],int) else hex(r['rdata_vram'])} "
          f".data@{r['data_vram'] if not isinstance(r['data_vram'],int) else hex(r['data_vram'])}")
    if r.get("error"):
        print("   ", r["error"])
    if not r["ok"] and "ndiff" in r:
        fd = r["first_diff"]
        print(f"    {r['ndiff']} word(s) differ; first @ {hex(fd) if fd else '(size)'}")
    if not quiet:
        print(f"    externals recovered ({len(r['externals'])}):")
        for s, a in sorted(r["externals"].items()):
            print(f"      {s:14s} = 0x{a:08X}")
        if r["unrecovered"]:
            print(f"    UNRECOVERED undefined: {', '.join(r['unrecovered'])}")
    sys.exit(0 if r["ok"] else 1)


if __name__ == "__main__":
    main()
