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

The optional [text_lo text_hi] window narrows the psyq_identify placement scan to the library's
text region. This is REQUIRED when an object's `.text` pattern is too short to anchor uniquely over
the whole EXE but is unique within the library region (e.g. libgs GS_106, an 8-instruction object
whose pattern recurs in game code — ambiguous in the default 0x80010000..0x800629DC window, unique
in 0x80051804..0x80057928). Without it that object drops out of the placement map and its block
splits, breaking the block<->stub count.

Usage: psyq_integrate.py [--vram-base HEX] [--exe PATH] [--symbols FILE]
                         <elf_dir> <ld_path> <objdir> <syms_ld> <stub1>[,<stub2>,...] [text_lo text_hi]
"""
import glob, os, re, subprocess, sys, tempfile
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from psyq_link import recover_sym_addrs, AS, sh, DATA_SECTIONS
from psyq_link_region import classify, placement


def stub_ranges(yaml_path, stubs, vram_base):
    """{stub_name: [vram_lo, vram_hi)} for the named code subsegs of a splat yaml (vram = fileoff + vram_base;
    a subseg ends where the next subseg row begins). Loud on a stub the yaml does not name (R43)."""
    import yaml as _yaml
    y = _yaml.safe_load(open(yaml_path))
    rows = []
    for seg in y["segments"]:
        if isinstance(seg, dict) and "subsegments" in seg:
            for r in seg["subsegments"]:
                if isinstance(r, list) and len(r) >= 3:
                    rows.append((int(r[0]), str(r[2])))
                elif isinstance(r, list) and len(r) == 1:
                    rows.append((int(r[0]), None))
    rows.sort()
    out = {}
    for i, (off, name) in enumerate(rows):
        if name in stubs:
            end = rows[i + 1][0] if i + 1 < len(rows) else off
            out[name] = (off + vram_base, end + vram_base)
    missing = [st for st in stubs if st not in out]
    if missing:
        sys.exit(f"integrate: stub subseg(s) {missing} not found in {yaml_path}")
    return out


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
    """Full-build link with the rewritten .ld; return the set of undefined symbol names.
    extra_syms is a list of already-emitted sibling *_externals.ld (from prior library integrations);
    including them stops THIS library's trial from re-flagging symbols another library already resolved
    (e.g. integrating libgs6 after libcd: libcd's objects reference DMACallback etc., defined only in
    libcd_externals.ld — without it the libgs6 trial reports them as spurious 'UNRESOLVED')."""
    td = tempfile.mkdtemp(dir=".run")
    elf = os.path.join(td, "trial.elf")
    cmd = [f"{AS}ld", "-T", ld_path, "-T", "undefined_syms_auto.txt",
           "-T", "undefined_funcs_auto.txt", "--no-check-sections", "-o", elf]
    for es in (extra_syms or []):
        cmd += ["-T", es]
    p = subprocess.run(cmd, capture_output=True)
    err = p.stderr.decode()
    # a weakened .bss common referenced by another object whose .bss we discarded shows up not as
    # "undefined reference" but as "defined in discarded section" — capture both forms.
    return (set(re.findall(r"undefined reference to [`']([^`']+)'", err))
            | set(re.findall(r"[`']([^`']+)' referenced in section .*? defined in discarded section", err)))


def integrate(elf_dir, ld_path, objdir, syms_path, stubs, lo=None, hi=None,
              *, vram_base, exe_path, symbols_path, yaml_path=None):
    exe = open(exe_path, "rb").read()
    order = sorted(placement(elf_dir, lo, hi, vram_base, exe_path).items(), key=lambda kv: kv[1][0])
    if yaml_path:
        # P31 S78: the fixed psyq_identify (§485) locates objects inside subsegs that are NOT this
        # library's stub blocks (e.g. libgte's FGO_01-06 fill the 800b_5 "game code" gap exactly), and
        # contiguous_blocks() then MERGES adjacent blocks -> "3 object blocks but 22 stubs" -> the whole
        # main link dies. Placement is not the same thing as wiring: only objects inside the stub subsegs
        # named on this call are wired; the others are the LINKED RESIDUE and are printed, not swallowed
        # (the completion contract's "residue empties" line reads exactly this).
        ranges = stub_ranges(yaml_path, stubs, vram_base)
        residue = [(nm, v, n) for nm, (v, n) in order if not any(a <= v < b for a, b in ranges.values())]
        order = [(nm, vn) for nm, vn in order if any(a <= vn[0] < b for a, b in ranges.values())]
        if residue:
            print(f"  ~~ {len(residue)} located object(s) / {sum(n for _, _, n in residue)} ins OUTSIDE the "
                  f"stub subsegs of {os.path.basename(elf_dir)} — byte-placed but NOT wired (LINKED residue):")
            for nm, v, n in residue:
                print(f"     0x{v:08X} {nm:14s} {n:5d} ins")
    recovered, weaken_by, bases_by = {}, {}, {}
    for name, (vram, _) in order:
        bases, weaken, sym_addr = classify(os.path.join(elf_dir, name), vram, exe, vram_base)
        bases_by[name], weaken_by[name] = bases, weaken
        for s, a in sym_addr.items():
            if not s.startswith("."):
                recovered[s] = a

    # 1. prepare objects (persistent)
    # P31 S78 — CURATED NAMES WIN (R15) FOR A LIBRARY OBJECT'S *DEFINED* SYMBOLS TOO. A 4.0 object can
    # export a name that the EXE's newer library assigned to a DIFFERENT address: libapi 4.0's A66.o
    # exports `firstfile` (0x80062248), but the EXE links libapi 4.2, where that trampoline is
    # `firstfile2` and `firstfile` is FIRST.o's C wrapper at 0x80061FA8 (LIBMCRD.o's `jal` word
    # EA87010C targets 0x80061FA8 — the bytes say so). Once 0x80061FA8 carries its real name in C, the
    # two object definitions collide at link. So: every symbol an object DEFINES whose recovered
    # address the curated symbol file names differently is `--redefine-sym`'d to the curated name.
    # Safe by construction: another object's reference to the OLD name is then undefined at the trial
    # link and resolves through `recovered` to the address its own relocation bytes encode.
    curated_by_addr = {}
    for ln in open(symbols_path):
        m = re.match(r"(\w+)\s*=\s*0x([0-9A-Fa-f]+)", ln)
        if m:
            curated_by_addr.setdefault(int(m.group(2), 16), m.group(1))
    os.makedirs(objdir, exist_ok=True)
    for name, (vram, _) in order:
        args = []
        for S in (".text",) + DATA_SECTIONS:
            args += ["--set-section-alignment", f"{S}=4"]
        for w in weaken_by[name]:
            args += ["--weaken-symbol", w]
        defined = subprocess.run([f"{AS}nm", "--defined-only", os.path.join(elf_dir, name)],
                                 capture_output=True, text=True).stdout
        for dl in defined.splitlines():
            parts = dl.split()
            if len(parts) == 3 and parts[1] in "TtDdRrBb" and not parts[2].startswith("."):
                sym = parts[2]
                # a .text symbol's EXE address = object vram + its section offset (nm prints the offset)
                addr = vram + int(parts[0], 16) if parts[1] in "Tt" else recovered.get(sym)
                cn = curated_by_addr.get(addr) if addr is not None else None
                if cn and cn != sym:
                    args += ["--redefine-sym", f"{sym}={cn}"]
                    print(f"  == {name}: exported `{sym}` @0x{addr:08X} is curated `{cn}` -> redefined (R15)")
        sh(f"{AS}objcopy", *args, os.path.join(elf_dir, name), os.path.join(objdir, name))

    if yaml_path:
        # Stub<->objects by SUBSEG RANGE (P31 S78), not by run-contiguity: two adjacent stub subsegs are
        # one contiguous byte run (libgte2..libgte7 touch), and the fixed psyq_identify reports section
        # words incl. the alignment pad, so contiguity-splitting can no longer reproduce the yaml's blocks.
        # Each stub must be tiled EXACTLY by its objects (first at lo, each abutting, last ending at hi
        # up to the 8-byte section alignment) — anything else is a carve error and fails loud (R43).
        by_stub = {st: [] for st in stubs}
        for nm, (v, n) in order:
            for st, (a, b) in ranges.items():
                if a <= v < b:
                    by_stub[st].append((nm, v, n))
        blocks = []
        for st in stubs:
            objs = sorted(by_stub[st], key=lambda t: t[1])
            a, b = ranges[st]
            if not objs:
                sys.exit(f"integrate: stub subseg '{st}' [0x{a:08X},0x{b:08X}) has NO located object")
            cur = a
            for nm, v, n in objs:
                if v != cur:
                    sys.exit(f"integrate: stub '{st}' not tiled — expected an object at 0x{cur:08X}, "
                             f"found {nm} at 0x{v:08X}")
                cur = v + n * 4
            if not (b - 8 < cur <= b):
                sys.exit(f"integrate: stub '{st}' ends at 0x{b:08X} but its objects end at 0x{cur:08X}")
            blocks.append(objs)
    else:
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
    # NOLOAD data sections, sorted by vram (keeps ld's location counter monotonic), before /DISCARD/.
    # Section names are namespaced by the objdir basename (e.g. .nl_libgs6_*) so MULTIPLE integrations
    # (libcd then libgs6) each add their own NOLOAD sections idempotently — a global `.nl_0` guard would
    # let the 2nd library's NOLOAD placement be skipped, discarding its .rdata/.bss (the OBJT3 break).
    tag = os.path.basename(objdir)
    nol_items = sorted((b, name, S) for name, (_, _) in order
                       for S, b in bases_by[name].items())
    nol = [f'    .nl_{tag}_{i} 0x{b:08X} (NOLOAD) : {{ "{objdir}/{name}"(.{S[1:]}) }}'
           for i, (b, name, S) in enumerate(nol_items)]
    if f".nl_{tag}_0 " not in ld:
        ld = re.sub(r"^([ \t]*/DISCARD/ :)", "\n".join(nol) + r"\n\n\1", ld, count=1, flags=re.M)
    # Globally re-sort ALL .nl_* NOLOAD lines by vram across libraries. Successive integrations (libcd
    # then libgs6) otherwise leave two separately-sorted groups whose vram ranges interleave, so ld's
    # location counter moves backwards (a harmless warning — NOLOAD emits no bytes). Pure reordering.
    nlre = re.compile(r"^[ \t]*\.nl_\w+ (0x[0-9A-Fa-f]+) \(NOLOAD\) : \{[^}]*\}$", re.M)
    items = sorted((int(m.group(1), 16), m.group(0).strip()) for m in nlre.finditer(ld))
    if len(items) > 1:
        ld = re.sub(r"\n{3,}", "\n\n", nlre.sub("", ld))
        block = "\n".join("    " + t for _, t in items)
        ld = re.sub(r"^([ \t]*/DISCARD/ :)", block + "\n\n" + r"\1", ld, count=1, flags=re.M)
    open(ld_path, "w").write(ld)

    # 3. resolve every symbol the rewritten build ACTUALLY leaves undefined (a full link, so symbols
    #    still defined elsewhere — e.g. VSync in the 800 region — never appear and can't be
    #    double-defined). A removed libcd stub used to define each libcd-region symbol by its splat
    #    name (func_<addr> or a symbols.us.txt name like BIOS_OBJ_3B8) and the data blob / external
    #    code references it by that name; the real object defines a PsyQ name instead. So map each
    #    back to its address: func_<addr> -> the address; a named symbol -> symbols.us.txt; a
    #    recovered data/extern global (St*, CD_*) -> its recovered address.
    symu = {}
    for ln in open(symbols_path):
        m = re.match(r"(\w+)\s*=\s*0x([0-9A-Fa-f]+)", ln)
        if m:
            symu[m.group(1)] = int(m.group(2), 16)
    # every weakened .bss common must be defsym'd to its recovered (scattered) address: where its
    # object's .bss is NOLOAD-placed it otherwise resolves to that weak placement (wrong) and never
    # shows as undefined; the strong defsym overrides the weak def uniformly.
    weaken_all = {w for ws in weaken_by.values() for w in ws}
    externals = {s: recovered[s] for s in weaken_all if s in recovered}
    missing = []
    siblings = [f for f in glob.glob(os.path.join(os.path.dirname(syms_path) or ".", "*_externals.ld"))
                if os.path.abspath(f) != os.path.abspath(syms_path)]
    for s in sorted(set(trial_undefined(ld_path, siblings)) - set(externals)):
        m = re.fullmatch(r"func_([0-9A-Fa-f]{8})", s)
        if m:
            externals[s] = int(m.group(1), 16)
        elif s in symu:
            externals[s] = symu[s]
        elif s in recovered:
            externals[s] = recovered[s]
        else:
            missing.append(s)
    # MONOTONIC MERGE — the externals file may only GROW for a given tree state.
    #
    # `trial_undefined` above is evaluated against the CURRENT ld_path, so its answer depends on how
    # much of the linker script has ALREADY been rewritten. On a virgin splat .ld the apicard region
    # is still the stub object (which defines only `firstfile2`), so at the libmcrd stage `firstfile`
    # is undefined and gets an entry. On an ALREADY-REWRITTEN .ld, A66.o is present and defines
    # `firstfile` at 0x80062248, the trial no longer reports it undefined, and the entry
    # `firstfile = 0x80061FA8;` was DROPPED — after which LIBMCRD's `jal` binds to A66.o and main
    # comes out 2 bytes different from retail (file 0x51674, VA 0x80060E74).
    #
    # That is why main was green only on the first build after a fresh extract and red on every
    # incremental relink, and it is the true identity of the long-standing "main link defect"
    # (2026-08-15): the extra C function did not break the link, the RELINK it forced did.
    # integrate()'s own comment at the top already claimed this operation was idempotent
    # ("a re-run on an already-rewritten .ld only redoes syms"); this makes that true.
    #
    # Newly-derived values WIN on a name collision (an address that legitimately moved must move);
    # names the new derivation no longer sees are KEPT at their previous address. So the file is a
    # function of the tree, not of the number of times this ran. Diagnosed P31 S68 (fable).
    prior = {}
    if os.path.exists(syms_path):
        for ln in open(syms_path):
            m = re.match(r"(\w+)\s*=\s*0x([0-9A-Fa-f]+)", ln)
            if m:
                prior[m.group(1)] = int(m.group(2), 16)
    readded = sorted(set(prior) - set(externals))
    merged = dict(prior)
    merged.update(externals)          # new derivation wins where both have the name
    with open(syms_path, "w") as f:
        for s, a in sorted(merged.items(), key=lambda kv: kv[1]):
            f.write(f"{s} = 0x{a:08X};\n")
    if readded:
        print(f"  (kept {len(readded)} extern(s) this re-run no longer saw as undefined: "
              f"{readded[:8]}{'...' if len(readded) > 8 else ''})")
    externals = merged
    print(f"integrate {os.path.basename(elf_dir)}: {len(order)} objects in {len(blocks)} block(s) "
          f"-> stubs {stubs}; {len(nol)} NOLOAD sections; {len(externals)} externals -> {syms_path}")
    if missing:
        print(f"  !! {len(missing)} UNRESOLVED (not func_<addr>, not recovered): {missing[:16]}")


def main():
    import argparse
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("elf_dir")
    ap.add_argument("ld_path")
    ap.add_argument("objdir")
    ap.add_argument("syms_ld")
    ap.add_argument("stubs")
    ap.add_argument("window", nargs="*", help="optional scan-narrowing window: text_lo text_hi")
    ap.add_argument("--vram-base", required=True,
                    help="fileoff->vram delta of the target binary (e.g. the EXE's 0x8000F800)")
    ap.add_argument("--exe", required=True, help="target binary path")
    ap.add_argument("--symbols", required=True,
                    help="symbol-address file for stub-name->address resolution")
    ap.add_argument("--yaml", default=None,
                    help="splat yaml of the target binary: wire ONLY objects inside the named stub subsegs; "
                         "print the rest as the LINKED residue (P31 S78)")
    a = ap.parse_args()
    lo = a.window[0] if len(a.window) > 0 else None
    hi = a.window[1] if len(a.window) > 1 else None
    integrate(a.elf_dir, a.ld_path, a.objdir, a.syms_ld, a.stubs.split(","), lo, hi,
              vram_base=int(a.vram_base, 0), exe_path=a.exe, symbols_path=a.symbols, yaml_path=a.yaml)


if __name__ == "__main__":
    main()
