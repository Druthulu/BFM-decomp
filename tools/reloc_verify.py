#!/usr/bin/env python3
"""reloc_verify.py — RESOLVE every relocation in a draft and compare it to the target.

Closes three of the four oracle blindness classes catalogued in cookbook §87, BEFORE a gate cycle
is spent on the draft:

  §87 LINK   `match_one` / `rtu_match` COMPILE but never LINK, so a callee that no symbol table can
             resolve — or simply the WRONG callee — reads as MATCH.
  §84 %lo    `masked_diff` masks HI16/LO16, so a data address that is off by a per-overlay symbol
             DISTANCE (the derived-offset bug) is invisible: the instruction word matches after
             masking and the image differs by one byte.
  §81 jtbl   R_MIPS_26 is masked too, so an internal `j` to the wrong destination passes clean.

WHY IT CAN WORK AT ALL: every symbol in this project encodes its own vram address in its NAME
(`func_80176734`, `D_801D9C20`), so a relocation can be RESOLVED to a number and compared with the
address the target's disassembly names at the same instruction index.

THE TRAP THIS EXISTS FOR (§84): MIPS ELF is REL, so the addend lives in the instruction field and
`objdump -r` does NOT print it. For a HI16/LO16 pair the real address is
    sym + ((imm_hi << 16) + sign_extend16(imm_lo))
Reading only the relocation's symbol therefore misses exactly the derived-offset class. This tool
pairs HI16 with its LO16 and recovers the implicit addend.

Promoted to tools/ in SESSION-21 from `.run/giants/s21_g21_reloc_verify.py`, where it was written
for a single function with a hard-coded base address. The base is now DERIVED from the target .s
(R33), and the parse is coverage-asserted (R32) so a silently-unparsed target cannot report "clean".

Usage:
  .venv/bin/python tools/reloc_verify.py <fn> --c <draft.c> --asm-subdir <dir> [--o0]
  .venv/bin/python tools/reloc_verify.py <fn> --obj <t.o> --asm-subdir <dir>

Exit 0 = every jal callee, every %hi/%lo address and every internal j destination resolves to the
target's. Exit 1 = at least one mismatch (printed). Exit 2 = usage / could not build.
"""
import argparse, os, re, struct, subprocess, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

OBJDUMP = "mipsel-linux-gnu-objdump"
CPP = "mipsel-linux-gnu-cpp"
CC1 = "tools/bin/gcc-2.7.2-psx/cc1"
MASPSX = "tools/maspsx/maspsx.py"
AS = "mipsel-linux-gnu-as"
PY = ".venv/bin/python"
CPPFLAGS = ("-lang-c -Iinclude -undef -Wall -fno-builtin -Dmips -D__GNUC__=2 -D__OPTIMIZE__ "
            "-Dpsx -D_PSYQ -D_MIPSEL -D_LANGUAGE_C").split()
ASFLAGS = "-Iinclude -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0".split()

# "/* off vaddr word */ mnem ops" — splat's disassembly line.
S_LINE = re.compile(r"\s*/\*\s*\S+\s+([0-9A-Fa-f]{8})\s+([0-9A-Fa-f]{8})\s*\*/\s*(\S+)\s*(.*)")
HILO = re.compile(r"%(hi|lo)\(([^)]+)\)")
SYM_ADDR = re.compile(r"(8[0-9A-Fa-f]{7})")


def addr_of(sym):
    """The vram address a symbol NAMES (func_80176734 -> 0x80176734). None if it names none."""
    m = SYM_ADDR.search(sym)
    return int(m.group(1), 16) if m else None


def s16(x):
    return x - 0x10000 if x & 0x8000 else x


def build_object(fn, cfile, work, o0):
    """Compile a draft through the PINNED triple (SETUP §5.4) — the same path match_one uses."""
    import masked_diff
    wd = os.path.join(work, fn)
    os.makedirs(wd, exist_ok=True)
    src = masked_diff.strip_scalar_typedefs(open(cfile).read())
    if '#include "common.h"' not in src:
        src = '#include "common.h"\n' + src
    open(f"{wd}/t.c", "w").write(src)
    cc1flags = f"-quiet {'-O0' if o0 else '-O2'} -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker".split()

    def pipe(cmd, data=None):
        return subprocess.run(cmd, input=data, capture_output=True)

    p = pipe([CPP] + CPPFLAGS + [f"{wd}/t.c"])
    if p.returncode:
        sys.exit("CPP FAIL\n" + p.stderr.decode()[-1200:])
    p = pipe([CC1] + cc1flags, p.stdout)
    if p.returncode:
        sys.exit("CC1 FAIL\n" + p.stderr.decode()[-1500:])
    p = pipe([PY, MASPSX, "--aspsx-version=2.56", "--expand-div"], p.stdout)
    if p.returncode:
        sys.exit("MASPSX FAIL\n" + p.stderr.decode()[-1200:])
    p = pipe([AS] + ASFLAGS + ["-o", f"{wd}/t.o"], p.stdout)
    if p.returncode:
        sys.exit("AS FAIL\n" + p.stderr.decode()[-1200:])
    return f"{wd}/t.o"


def parse_target(path):
    """index -> what the TARGET names there. Base vram is DERIVED from the first line (R33)."""
    calls, data, jumps = {}, {}, {}
    base, i = None, 0
    for line in open(path, errors="replace"):
        m = S_LINE.match(line)
        if not m:
            continue
        vaddr, _word, mnem, ops = int(m.group(1), 16), m.group(2), m.group(3), m.group(4).strip()
        if base is None:
            base = vaddr
        if mnem in ("jal", "j"):
            if ops.startswith(".L"):
                jumps[i] = (int(ops[2:], 16) - base) // 4      # internal jump -> instruction index
            else:
                calls[i] = (addr_of(ops), ops)
        else:
            h = HILO.search(ops)
            if h:
                a = addr_of(h.group(2))
                if a is not None:
                    # The .s word field is LITTLE-ENDIAN HEX TEXT ("0080033C"), not the instruction
                    # integer — masked_diff byte-swaps it (struct.unpack("<I", ...)) and so must we.
                    # Comparing the unswapped text-int against my object's real word reported
                    # "word differs" on three sites that are byte-IDENTICAL (SESSION-21).
                    tword = struct.unpack("<I", bytes.fromhex(m.group(2)))[0]
                    data[i] = (h.group(1).upper(), a, h.group(2), tword)
        i += 1
    # R32: a target that parsed to nothing must not read as "clean".
    if i == 0:
        sys.exit(f"reloc_verify: parsed ZERO instructions from {path} — refusing to report a "
                 f"verdict (a silently-unparsed target would read as ALL RESOLVED).")
    return calls, data, jumps, i, base


def object_words(obj, fn):
    """MY object's instruction words, in the SAME index space as parse_object (-drz)."""
    import masked_diff
    return [i["word"] for i in masked_diff.insns_from_object(obj, fn)]


def parse_object(obj, fn):
    """index -> what MY object relocates there, with the implicit REL addend recovered (§84).

    ⚠️ `-drz`, NOT `-dr`. Without `-z`, objdump ELIDES runs of identical instructions ("..."), which
    silently DROPS instructions from the listing — so the index space shifts and every later index
    is compared against the wrong instruction. Measured while promoting this tool (SESSION-21):
    func_801330E0 read 104 instructions under `-dr` and 110 under `-drz` (6 elided nops), which
    manufactured 2 phantom mismatches on a draft that is in fact clean at those sites. `masked_diff`
    has always used `-drz`; this tool's ancestor did not, and the two therefore indexed differently.
    A comparison tool MUST share its reference oracle's index space exactly."""
    dis = subprocess.run([OBJDUMP, "-drz", "-j", ".text", obj],
                         capture_output=True, text=True).stdout
    words, relocs, idx = [], {}, -1
    in_fn = False
    for line in dis.splitlines():
        fm = re.match(r"^[0-9a-f]+ <([^>]+)>:", line)
        if fm:
            in_fn = (fm.group(1) == fn)
            continue
        if not in_fn:
            continue
        m = re.match(r"\s*([0-9a-f]+):\s+([0-9a-f]{8})\s+(\S+)\s*(.*)", line)
        if m:
            idx += 1
            words.append((int(m.group(2), 16), m.group(3), m.group(4)))
            continue
        r = re.match(r"\s*[0-9a-f]+:\s+(R_MIPS_\S+)\s+(\S+)", line)
        if r and idx >= 0:
            relocs[idx] = (r.group(1), r.group(2))

    data, calls, jumps = {}, {}, {}
    hi_pending = {}
    for k in sorted(relocs):
        kind, sym = relocs[k]
        w = words[k][0]
        if kind == "R_MIPS_26":
            if sym.startswith("."):
                jumps[k] = w & 0x3FFFFFF
            else:
                a = addr_of(sym)
                calls[k] = ((a + ((w & 0x3FFFFFF) << 2)) if a is not None else None, sym)
        elif kind == "R_MIPS_HI16":
            hi_pending.setdefault(sym, []).append(k)
        elif kind == "R_MIPS_LO16":
            if sym.startswith("."):
                continue
            lo = s16(w & 0xFFFF)
            base_a = addr_of(sym)
            ks = hi_pending.get(sym)
            if ks and base_a is not None:
                khi = ks.pop(0)
                A = ((words[khi][0] & 0xFFFF) << 16) + lo      # the addend objdump does not print
                data[khi] = ("HI", base_a + A)
                data[k] = ("LO", base_a + A)
            elif base_a is not None:
                data[k] = ("LO", base_a + lo)
    return calls, data, jumps, len(words)


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("fn")
    ap.add_argument("--c", help="draft C file (compiled through the pinned triple)")
    ap.add_argument("--obj", help="a prebuilt .o instead of --c")
    ap.add_argument("--asm-subdir", required=True)
    ap.add_argument("--o0", action="store_true", help="compile -O0 (the _o0/_o0b splits)")
    ap.add_argument("--work", default=None)
    a = ap.parse_args()

    tgt_path = os.path.join(a.asm_subdir, f"{a.fn}.s")
    if not os.path.exists(tgt_path):
        sys.exit(f"reloc_verify: no target asm at {tgt_path}")

    obj = a.obj
    if not obj:
        if not a.c or not os.path.exists(a.c):
            sys.exit("reloc_verify: need --c <draft.c> or --obj <t.o>")
        work = a.work or os.path.join(".run/relocv", f"{a.fn}.{os.getpid()}")
        obj = build_object(a.fn, a.c, work, a.o0)

    t_calls, t_data, t_jumps, t_n, base = parse_target(tgt_path)
    m_calls, m_data, m_jumps, m_n = parse_object(obj, a.fn)

    # Words of MY object, for the "no reloc in mine" adjudication below.
    m_words = object_words(obj, a.fn)

    bad, jtbl, baked = [], [], []
    for k, v in t_calls.items():
        m = m_calls.get(k)
        ok = m is not None and ((v[0] is not None and m[0] == v[0]) or m[1] == v[1])
        if not ok:
            bad.append(("CALL", k, v[1], (m[1] if m else None)))
    for k, v in t_data.items():
        kind, taddr, tsym, tword = v
        m = m_data.get(k)
        if m is not None:
            if m[1] != taddr:
                bad.append(("DATA", k, "%s %08X" % (kind, taddr), "%s %08X" % (m[0], m[1])))
            continue
        # MY object has NO relocation here. Three very different situations — do not lump them
        # into one scary "mismatch" (that is how a routing signal becomes noise):
        if tsym.startswith("jtbl_"):
            # gcc emits its OWN switch table via a LOCAL label, so there is no external
            # relocation to compare. Expected — and it is the §81 signal: this function banks
            # through the jtbl carve chain, never through a plain harvest_verify.
            jtbl.append((k, tsym))
        elif k < len(m_words) and m_words[k] == tword:
            # The compiler materialised the same constant inline. Byte-correct HERE. It is only a
            # hazard if that symbol is per-overlay (an overlay-space D_/jtbl_ address), in which
            # case the exemplar matches and every SIBLING breaks — the §84 shape. Reported, not
            # failed, because a genuine constant (D_80000000 and friends) looks identical.
            baked.append((k, tsym, "%08X" % taddr))
        else:
            bad.append(("DATA", k, "%s %08X" % (kind, taddr), "no reloc, word differs"))
    for k, v in t_jumps.items():
        if m_jumps.get(k) != v:
            bad.append(("JUMP", k, v, m_jumps.get(k)))
    extra = sorted(set(m_data) - set(t_data)) + sorted(set(m_calls) - set(t_calls))

    print(f"{a.fn}: target {t_n} ins (base 0x{base:08X}) | mine {m_n} ins")
    print(f"checked: {len(t_calls)} jal callees, {len(t_data)} %hi/%lo addresses, "
          f"{len(t_jumps)} internal j targets")
    if m_n != t_n:
        print(f"NOTE: length differs ({m_n} vs {t_n}) — index-wise comparison is unreliable on a "
              f"LENGTH-DRIFT draft (§83a); fix the length first.")
    if jtbl:
        print(f"JTBL: {len(jtbl)} site(s) reference a splat jump table "
              f"({', '.join(sorted({s for _, s in jtbl}))}) — gcc emits its own table via a LOCAL "
              f"label, so there is nothing to relocate here. EXPECTED, and it is the routing "
              f"signal: this function banks through the §81 jtbl carve chain "
              f"(tools/jtbl_family_bank.py), never a plain harvest_verify.")
    if baked:
        print(f"BAKED-LITERAL: {len(baked)} site(s) where the target names a symbol and my object "
              f"materialised the same constant inline (bytes agree here):")
        for k, s, addr in baked[:10]:
            print(f"   idx {k:5d}  {s} ({addr})")
        print("   ^ byte-correct in THIS binary. If any of those symbols is per-overlay, the "
              "exemplar matches and every SIBLING breaks — the §84 shape. Check before sweeping.")
    print(f"mismatches: {len(bad)}")
    for b in bad[:25]:
        print("   %-5s idx %5d  target=%s  mine=%s" % b)
    if extra:
        print(f"mine relocates where the target does not, at idx: {extra[:10]}")
    if not bad and not extra:
        print("ALL RESOLVED — every jal callee, every %hi/%lo address (including derived-offset "
              "sites) and every internal j destination matches the target."
              + (" (JTBL sites noted above route to the carve chain.)" if jtbl else ""))
        return 0
    return 1


if __name__ == "__main__":
    sys.exit(main())
