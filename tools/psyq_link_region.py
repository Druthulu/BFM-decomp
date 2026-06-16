#!/usr/bin/env python3
"""Link a whole PsyQ library's objects into the build IN PLACE OF asm stubs — no data carving.

The wiring trick (cookbook §9.2): each object's `.text` is LOADED at its EXE vram (the asm
stubs there are removed); each object's `.data`/`.rdata`/`.bss` is placed as a **NOLOAD**
section at its vram — addresses only, zero bytes — so the build's existing flat `data`
subsegment still supplies those bytes (no carve, no double-emit) while the ~hundreds of
section-relative `.text` references resolve via the NOLOAD placement. Mislabelled common-style
`.bss` globals are `--weaken-symbol`'d so a strong `--defsym` to their real (scattered) address
wins (cookbook §9.1). Symbols that no linked object defines (other libraries' functions, module
data globals) are emitted for `symbols.us.txt`.

This module both VERIFIES the region links byte-identical and EMITS the build artifacts:
  --emit <prefix>  ->  <prefix>.ld  (text lines + NOLOAD sections, for the main linker script)
                       <prefix>.syms (NAME = 0xADDR;  external symbols for symbols.us.txt)

Usage: psyq_link_region.py <elf_dir> [text_lo text_hi] [--emit <prefix>]
"""
import json, os, re, subprocess, sys, tempfile
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from psyq_link import (section_table, symbol_table, recover_sym_addrs, unique_byte_vram,
                       VRAM_BASE, DATA_SECTIONS, AS, sh)

EXE = "extracted/retail/SLUS_007.26"


def placement(elf_dir, lo, hi, vram_base=VRAM_BASE, exe=EXE):
    cmd = (["python3", "tools/psyq_identify.py", elf_dir] + ([lo, hi] if lo else [])
           + ["--vram-base", hex(vram_base), "--exe", exe])
    placed = {}
    for ln in subprocess.check_output(cmd, text=True).splitlines():
        m = re.match(r"\s+0x([0-9A-Fa-f]+)\s+(\S+\.o)\s+\((\d+) ins\)", ln)
        if m:
            placed[m.group(2)] = (int(m.group(1), 16), int(m.group(3)))
    return placed


def classify(obj, text_vram, exe, vram_base=VRAM_BASE):
    """Per-object: NOLOAD section bases, and the .bss/.sbss symbols to weaken.

    Every named symbol psyq-obj-parser put in .bss/.sbss is a common-style global the original
    linker scattered (their st_values are not honoured). Weaken them ALL so a strong --defsym to
    the recovered address wins over the (placed or discarded) weak definition — uniform across the
    genuine (CD_*) and mislabelled (St*) cases, and across objects (a .bss symbol of object A
    referenced by object B).
    """
    secs = section_table(obj)
    symtab = symbol_table(obj)
    sym_addr = recover_sym_addrs(obj, text_vram, exe, vram_base)

    bases = {}
    for S in DATA_SECTIONS:
        if S in secs and secs[S][0] > 0:
            b = unique_byte_vram(obj, S, exe, vram_base) if S not in (".bss", ".sbss") else None
            if b is None:
                b = sym_addr.get(S)              # the object referenced the section symbol
            if b is not None:
                bases[S] = b
    weaken = [s for s, (sec, _) in symtab.items() if sec in (".bss", ".sbss")]
    return bases, weaken, sym_addr


def defined_text_syms(obj):
    out = sh(f"{AS}readelf", "-s", obj).stdout.decode()
    names = set()
    secs = {}
    # map section index -> name to find .text-defined symbols
    for ln in sh(f"{AS}readelf", "-S", obj).stdout.decode().splitlines():
        m = re.match(r"\s*\[\s*(\d+)\]\s+(\.\S+)", ln)
        if m:
            secs[m.group(1)] = m.group(2)
    for ln in out.splitlines():
        p = ln.split()
        if len(p) >= 8 and p[0].endswith(":") and re.fullmatch(r"[0-9a-f]+", p[1]):
            if p[6].isdigit() and secs.get(p[6]) == ".text" and not p[7].startswith("."):
                names.add(p[7])
    return names


def build_region(elf_dir, lo=None, hi=None, emit=None, vram_base=VRAM_BASE, exe_path=EXE):
    exe = open(exe_path, "rb").read()
    placed = placement(elf_dir, lo, hi, vram_base, exe_path)
    order = sorted(placed.items(), key=lambda kv: kv[1][0])     # by vram
    region_lo = order[0][1][0]
    region_hi = order[-1][1][0] + order[-1][1][1] * 4

    recovered, weaken_by, bases_by = {}, {}, {}
    conflicts = []
    for name, (vram, _) in order:
        obj = os.path.join(elf_dir, name)
        bases, weaken, sym_addr = classify(obj, vram, exe, vram_base)
        bases_by[name] = bases
        weaken_by[name] = weaken
        for s, a in sym_addr.items():
            if s.startswith("."):
                continue                    # section symbols are per-object (NOLOAD-placed)
            if s in recovered and recovered[s] != a:
                conflicts.append((s, recovered[s], a))
            recovered[s] = a

    td = tempfile.mkdtemp(dir=".run")
    prepared = []
    for name, (vram, _) in order:
        dst = os.path.join(td, name)
        args = []
        for S in (".text",) + DATA_SECTIONS:
            args += ["--set-section-alignment", f"{S}=4"]
        for w in weaken_by[name]:
            args += ["--weaken-symbol", w]
        sh(f"{AS}objcopy", *args, os.path.join(elf_dir, name), dst)
        prepared.append((name, vram, dst))

    # Each object's .text is placed at its EXACT vram (the region is two contiguous libcd
    # sub-blocks split by a 76-byte non-libcd gap, so naive concatenation would drift past it).
    def write_ld(path, objref):
        lines = ["SECTIONS {"]
        for i, (name, vram, dst) in enumerate(prepared):
            lines += [f"  . = 0x{vram:08X};", f"  .t{i} : {{ {objref(dst)}(.text) }}"]
        n = 0
        for name, _, dst in prepared:
            for S, b in bases_by[name].items():
                lines.append(f"  .nl_{n} 0x{b:08X} (NOLOAD) : {{ {objref(dst)}(.{S[1:]}) }}")
                n += 1
        lines += ["  /DISCARD/ : { *(*) }", "}"]
        open(path, "w").write("\n".join(lines) + "\n")

    # ---- link: let ld report which symbols are unresolved, then --defsym exactly those ----
    # (symbols defined by some object's .text, or genuinely placed via NOLOAD, resolve internally.)
    weaken_all = {w for ws in weaken_by.values() for w in ws}
    ld = os.path.join(td, "verify.ld")
    write_ld(ld, lambda d: f'"{d}"')
    elf = os.path.join(td, "out.elf")
    base_cmd = [f"{AS}ld", "--no-check-sections", "-T", ld, "-o", elf]
    # weakened .bss commons resolve to their (wrong) weak def, so they never show as "undefined";
    # defsym them explicitly. Then a probe link surfaces the remaining true externals (other libs).
    forced = {s for s in weaken_all if s in recovered}
    probe = base_cmd + [arg for s in sorted(forced) for arg in ("--defsym", f"{s}=0x{recovered[s]:08X}")]
    p = subprocess.run(probe, capture_output=True)
    undef = set(re.findall(r"undefined reference to [`']([^`']+)'", p.stderr.decode()))
    externals = {s: recovered[s] for s in (forced | undef) if s in recovered}
    missing = sorted(s for s in undef if s not in recovered)
    cmd = base_cmd + [arg for s, a in sorted(externals.items())
                      for arg in ("--defsym", f"{s}=0x{a:08X}")]
    p = subprocess.run(cmd, capture_output=True)
    ok = (p.returncode == 0)
    ndiff = badobjs = None
    if ok:
        # verify each object's .text bytes individually (gap bytes are not ours to provide)
        ndiff = 0
        badobjs = []
        for i, (name, vram, _) in enumerate(prepared):
            got = sh(f"{AS}objcopy", "-O", "binary", "--only-section", f".t{i}", elf, "/dev/stdout").stdout
            want = exe[vram - vram_base: vram - vram_base + len(got)]
            d = sum(1 for j in range(0, min(len(got), len(want)), 4) if got[j:j+4] != want[j:j+4])
            ndiff += d
            if d:
                badobjs.append(name)
        ok = (ndiff == 0)
    else:
        print("ld error:", p.stderr.decode().strip().split("\n")[-1])

    weaken_all = {w for ws in weaken_by.values() for w in ws}
    print(f"region {os.path.basename(elf_dir)} [0x{region_lo:08X}..0x{region_hi:08X}] "
          f"{len(order)} objects | conflicts={len(conflicts)} | externals={len(externals)}")
    print(f"  weakened commons: {sorted(weaken_all)}")
    if missing:
        print(f"  !! {len(missing)} undefined symbols NOT in recovered map: {missing}")
    print(f"  per-object .text byte-identical: {ok}"
          + (f" ({ndiff} words differ in {badobjs})" if ndiff else ""))

    if emit and ok:
        write_ld(emit + ".ld", lambda d: os.path.join("build/psyq", os.path.basename(elf_dir),
                                                        os.path.basename(d)))
        with open(emit + ".syms", "w") as f:
            for s, a in sorted(externals.items(), key=lambda kv: kv[1]):
                f.write(f"{s} = 0x{a:08X};\n")
        print(f"  emitted {emit}.ld + {emit}.syms ({len(externals)} externals)")
    return ok


def main():
    import argparse
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("elf_dir")
    ap.add_argument("window", nargs="*", help="optional scan-narrowing window: text_lo text_hi")
    ap.add_argument("--emit", help="output prefix for <prefix>.ld + <prefix>.syms")
    ap.add_argument("--vram-base", default=hex(VRAM_BASE),
                    help="fileoff->vram delta of the target binary (default the EXE's; required T8)")
    ap.add_argument("--exe", default=EXE, help="target binary path (default: the retail EXE)")
    a = ap.parse_args()
    lo = a.window[0] if len(a.window) > 0 else None
    hi = a.window[1] if len(a.window) > 1 else None
    ok = build_region(a.elf_dir, lo, hi, a.emit, vram_base=int(a.vram_base, 0), exe_path=a.exe)
    sys.exit(0 if ok else 1)


if __name__ == "__main__":
    main()
