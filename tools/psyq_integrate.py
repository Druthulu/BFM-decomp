#!/usr/bin/env python3
"""Wire real PsyQ library objects into the splat build, replacing stub subsegments (Phase 7 2'.3).

Run after `make extract`. Given a library's ELF objects and the stub subsegment(s) splat emitted
for the library's text region(s), this:
  1. prepares each object (objcopy: .text/.data/.rdata/.bss align=4; weaken every .bss/.sbss
     named symbol so a strong --defsym beats its scattered weak def) -> <objdir>/*.o
  2. rewrites the splat linker script: each `build/src/<stub>.o(.text);` line is replaced by the
     real objects' `<objdir>/<obj>.o(.text);` lines (the library's objects form one contiguous
     block per stub, so concatenation places them at their exact vrams); each object's
     .data/.rdata/.bss is added as a NOLOAD section at its vram (addresses only — the flat data
     subseg still supplies the bytes, no carve)
  3. writes <syms.ld>: `NAME = 0xADDR;` for every external the objects reference but no linked
     object defines (other libs' funcs + module data globals) — added to the link via -T.

Stub<->block mapping is by vram order: the i-th stub (in vram order) gets the i-th contiguous
object block. Non-library gaps between blocks keep their own stub subsegment untouched.

Usage: psyq_integrate.py <elf_dir> <ld_path> <objdir> <syms_ld> <stub1>[,<stub2>,...]
"""
import os, re, subprocess, sys, tempfile
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from psyq_link import recover_sym_addrs, AS, sh, VRAM_BASE, DATA_SECTIONS
from psyq_link_region import classify, placement

EXE = "extracted/retail/SLUS_007.26"


def contiguous_blocks(order):
    """Split vram-ordered objects into contiguous runs (a non-library gap starts a new block)."""
    blocks, cur, end = [], [], None
    for name, (vram, ins) in order:
        if end is not None and vram != end:
            blocks.append(cur)
            cur = []
        cur.append((name, vram, ins))
        end = vram + ins * 4
    if cur:
        blocks.append(cur)
    return blocks


def trial_undefined(ld_path, extra_syms=None):
    """Full-build link with the rewritten .ld; return the set of undefined symbol names."""
    td = tempfile.mkdtemp(dir=".run")
    elf = os.path.join(td, "trial.elf")
    cmd = [f"{AS}ld", "-T", ld_path, "-T", "undefined_syms_auto.txt",
           "-T", "undefined_funcs_auto.txt", "--no-check-sections", "-o", elf]
    if extra_syms:
        cmd += ["-T", extra_syms]
    p = subprocess.run(cmd, capture_output=True)
    err = p.stderr.decode()
    # a weakened .bss common referenced by another object whose .bss we discarded shows up not as
    # "undefined reference" but as "defined in discarded section" — capture both forms.
    return (set(re.findall(r"undefined reference to [`']([^`']+)'", err))
            | set(re.findall(r"[`']([^`']+)' referenced in section .*? defined in discarded section", err)))


def integrate(elf_dir, ld_path, objdir, syms_path, stubs):
    exe = open(EXE, "rb").read()
    order = sorted(placement(elf_dir, None, None).items(), key=lambda kv: kv[1][0])
    recovered, weaken_by, bases_by = {}, {}, {}
    for name, (vram, _) in order:
        bases, weaken, sym_addr = classify(os.path.join(elf_dir, name), vram, exe)
        bases_by[name], weaken_by[name] = bases, weaken
        for s, a in sym_addr.items():
            if not s.startswith("."):
                recovered[s] = a

    # 1. prepare objects (persistent)
    os.makedirs(objdir, exist_ok=True)
    for name, _ in order:
        args = []
        for S in (".text",) + DATA_SECTIONS:
            args += ["--set-section-alignment", f"{S}=4"]
        for w in weaken_by[name]:
            args += ["--weaken-symbol", w]
        sh(f"{AS}objcopy", *args, os.path.join(elf_dir, name), os.path.join(objdir, name))

    blocks = contiguous_blocks(order)
    if len(blocks) != len(stubs):
        sys.exit(f"integrate: {len(blocks)} object blocks but {len(stubs)} stub(s) given "
                 f"({[len(b) for b in blocks]} objs/block)")

    # 2. rewrite the linker script
    ld = open(ld_path).read()
    already = objdir in ld          # idempotent: a re-run on an already-rewritten .ld only redoes syms
    for stub, block in zip(stubs, blocks):
        textlines = "\n".join(f'        "{objdir}/{nm}"(.text);' for nm, _, _ in block)
        pat = re.compile(r"^[ \t]*build/src/" + re.escape(stub) + r"\.o\(\.text\);[ \t]*$", re.M)
        if pat.search(ld):
            ld = pat.sub(textlines, ld, count=1)
        elif not already:
            sys.exit(f"integrate: stub text line for '{stub}' not found in {ld_path}")
        # drop the stub object's other (empty) section lines so it is not linked at all
        # (else its INCLUDE_ASM-stub symbols multiply-define the real objects' symbols)
        other = re.compile(r"^[ \t]*build/src/" + re.escape(stub)
                           + r"\.o\(\.(?:rodata|data|bss|sdata|sbss)\);[ \t]*\n", re.M)
        ld = other.sub("", ld)
    # NOLOAD data sections, sorted by vram (keeps ld's location counter monotonic), before /DISCARD/
    nol_items = sorted((b, name, S) for name, (_, _) in order
                       for S, b in bases_by[name].items())
    nol = [f'    .nl_{i} 0x{b:08X} (NOLOAD) : {{ "{objdir}/{name}"(.{S[1:]}) }}'
           for i, (b, name, S) in enumerate(nol_items)]
    if ".nl_0 " not in ld:
        ld = re.sub(r"^([ \t]*/DISCARD/ :)", "\n".join(nol) + r"\n\n\1", ld, count=1, flags=re.M)
    open(ld_path, "w").write(ld)

    # 3. resolve every symbol the rewritten build ACTUALLY leaves undefined (a full link, so symbols
    #    still defined elsewhere — e.g. VSync in the 800 region — never appear and can't be
    #    double-defined). A removed libcd stub used to define each libcd-region symbol by its splat
    #    name (func_<addr> or a symbols.us.txt name like BIOS_OBJ_3B8) and the data blob / external
    #    code references it by that name; the real object defines a PsyQ name instead. So map each
    #    back to its address: func_<addr> -> the address; a named symbol -> symbols.us.txt; a
    #    recovered data/extern global (St*, CD_*) -> its recovered address.
    symu = {}
    for ln in open("config/symbols.us.txt"):
        m = re.match(r"(\w+)\s*=\s*0x([0-9A-Fa-f]+)", ln)
        if m:
            symu[m.group(1)] = int(m.group(2), 16)
    # every weakened .bss common must be defsym'd to its recovered (scattered) address: where its
    # object's .bss is NOLOAD-placed it otherwise resolves to that weak placement (wrong) and never
    # shows as undefined; the strong defsym overrides the weak def uniformly.
    weaken_all = {w for ws in weaken_by.values() for w in ws}
    externals = {s: recovered[s] for s in weaken_all if s in recovered}
    missing = []
    for s in sorted(set(trial_undefined(ld_path)) - set(externals)):
        m = re.fullmatch(r"func_([0-9A-Fa-f]{8})", s)
        if m:
            externals[s] = int(m.group(1), 16)
        elif s in symu:
            externals[s] = symu[s]
        elif s in recovered:
            externals[s] = recovered[s]
        else:
            missing.append(s)
    with open(syms_path, "w") as f:
        for s, a in sorted(externals.items(), key=lambda kv: kv[1]):
            f.write(f"{s} = 0x{a:08X};\n")
    print(f"integrate {os.path.basename(elf_dir)}: {len(order)} objects in {len(blocks)} block(s) "
          f"-> stubs {stubs}; {len(nol)} NOLOAD sections; {len(externals)} externals -> {syms_path}")
    if missing:
        print(f"  !! {len(missing)} UNRESOLVED (not func_<addr>, not recovered): {missing[:16]}")


def main():
    if len(sys.argv) != 6:
        sys.exit(__doc__)
    integrate(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4], sys.argv[5].split(","))


if __name__ == "__main__":
    main()
