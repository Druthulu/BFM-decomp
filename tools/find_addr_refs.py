#!/usr/bin/env python3
"""find_addr_refs.py — REGISTER-TRACKED search for code that materializes an absolute address.

Applies cookbook §155 (learned the hard way in S45 p4, where a window-pairing scanner produced
convincing phantom cross-references that steered an entire evening): a `lui` must be paired ONLY
with a later op whose BASE REGISTER is the one the lui wrote, and the register must be invalidated
the moment anything else clobbers it. Window-paired lui/lo16 is not evidence.

Recognised materializations of ADDR = hi<<16 + lo:
    lui  rt, hi          ; addiu rt, rs(=rt), lo        -> address in rt
    lui  rt, hi          ; ori   rt, rs(=rt), lo        -> address in rt
    lui  rt, hi          ; lw/sw/lh/lhu/lb/lbu/sh/sb rd, lo(rt)   -> access AT the address
    lui  rt, hi          ; addu  rd, rt, rx             -> INDEXED access (base + index): reported
                                                           separately, since that is how a TABLE is read

Usage:
    tools/find_addr_refs.py 0x801EF468
    tools/find_addr_refs.py 0x801EF468 --binaries resident,ov_SC03_001
"""
import argparse
import glob
import os
import re
import struct
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

LUI = 0x0F
ADDIU = 0x09
ORI = 0x0D
ADDU = 0x21          # special funct
SPECIAL = 0x00
MEMOPS = {0x20: "lb", 0x21: "lh", 0x23: "lw", 0x24: "lbu", 0x25: "lhu",
          0x28: "sb", 0x29: "sh", 0x2B: "sw"}
REGN = ["zero", "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3",
        "t4", "t5", "t6", "t7", "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
        "t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra"]


def s16(x):
    return x - 0x10000 if x & 0x8000 else x


def writes_reg(w):
    """Which register does this instruction write? None if it writes no GPR (or we don't care)."""
    op = w >> 26
    if op == SPECIAL:
        funct = w & 0x3F
        if funct in (0x08, 0x09):        # jr / jalr(rd)
            return (w >> 11) & 31 if funct == 0x09 else None
        return (w >> 11) & 31            # rd
    if op in (0x02, 0x03):               # j / jal -> clobbers ra on jal
        return 31 if op == 0x03 else None
    if op in (0x04, 0x05, 0x06, 0x07, 0x14, 0x15, 0x16, 0x17):   # branches
        return None
    if op in (0x28, 0x29, 0x2A, 0x2B, 0x2E, 0x38, 0x39, 0x3A, 0x3B):  # stores
        return None
    return (w >> 16) & 31                # rt for the I-type forms we track


def scan(data, base, target):
    """(vaddr, kind, detail) for register-tracked materializations of `target`.

    A filter over scan_all — ONE tracking implementation, so a caller that needs every
    materialization (tools/idxtab_map.py) cannot drift from the one that needs a single target
    (R33). Behaviour is unchanged: same hits, same order."""
    return [(va, kind, det) for va, kind, addr, det in scan_all(data, base) if addr == target]


def scan_all(data, base):
    """Yield (vaddr, kind, addr, detail) for EVERY register-tracked address materialization.

    Same §155 discipline as before: a `lui` pairs only with a later op whose BASE REGISTER is the
    one it wrote, and the register dies the moment anything clobbers it. Window-pairing is not
    evidence."""
    n = len(data) // 4
    words = struct.unpack(f"<{n}I", data[:n * 4])
    hi = {}          # reg -> (hi_value<<16, vaddr_of_lui)
    val = {}         # reg -> fully materialized address (for indexed forms)
    via_index = set()  # regs whose hi half arrived through an `addu` index add (see the ADDU branch)
    out = []
    for i, w in enumerate(words):
        va = base + i * 4
        op = w >> 26
        rs, rt, imm = (w >> 21) & 31, (w >> 16) & 31, w & 0xFFFF
        carry = None

        if op == LUI:
            hi[rt] = (imm << 16, va)
            val.pop(rt, None)
            continue

        if op == ADDIU and rs in hi:
            a = hi[rs][0] + s16(imm)
            out.append((hi[rs][1], "addiu", a, f"lui ${REGN[rs]} @0x{hi[rs][1]:08X} + addiu -> 0x{a:08X}"))
            val[rt] = a
            hi.pop(rt, None) if rt != rs else None
            continue

        if op == ORI and rs in hi:
            a = hi[rs][0] | imm
            out.append((hi[rs][1], "ori", a, f"lui ${REGN[rs]} @0x{hi[rs][1]:08X} + ori -> 0x{a:08X}"))
            val[rt] = a
            continue

        if op in MEMOPS and rs in hi:
            a = hi[rs][0] + s16(imm)
            kind = MEMOPS[op] + ("-indexed" if rs in via_index else "")
            out.append((va, kind, a,
                        f"{kind} ${REGN[rt]}, 0x{imm:X}(${REGN[rs]}) -> 0x{a:08X}"))

        if op == SPECIAL and (w & 0x3F) == ADDU:
            # base+index: the TABLE-READ shape. Report when either operand holds a materialized addr.
            rd = (w >> 11) & 31
            # ALSO the gcc form for indexing a GLOBAL ARRAY, which this tracker used to be blind to:
            #     lui  $at, HI ; addu $at, $at, idx ; lh rt, LO($at)
            # The address is split across the lui and the LOAD, with the index added in between — so
            # killing $at at the addu (it is written, after all) threw away the only link, and the
            # load looked like an offset off an unknown register. Every per-overlay IDXTAB in the
            # game is read exactly like this, which is why a fleet-wide scan for their addresses
            # returned ZERO references and the tables looked unreachable (S46). Carry the hi half
            # through the add — still strictly register-tracked, never window-paired (§155) — and
            # label what it feeds `-indexed` so a caller can tell the two shapes apart.
            for r in (rs, rt):
                if r in hi:
                    carry = (rd, hi[r])
                    break
            # STRICT: require the FULL address to be materialized in the register. Matching only
            # the hi half (the 64 KB page) fires on every unrelated address in that page — coverage
            # without discrimination (§155a), which is how the p4 phantoms happened one level up.
            for r in (rs, rt):
                if r in val:
                    out.append((va, "addu-index", val[r],
                                f"addu ${REGN[rd]}, ${REGN[rs]}, ${REGN[rt]}  (INDEXED off 0x{val[r]:08X})"))
                    break

        wr = writes_reg(w)
        if wr is not None and wr != 0:
            hi.pop(wr, None)
            val.pop(wr, None)
            via_index.discard(wr)
        if op == SPECIAL and (w & 0x3F) == ADDU and carry and carry[0] != 0:
            hi[carry[0]] = carry[1]          # re-arm AFTER the clobber above (rd was just written)
            via_index.add(carry[0])
    return out


def binaries(only=None):
    for cfg in sorted(glob.glob(os.path.join(REPO, "config/splat.*.yaml"))):
        alias = os.path.basename(cfg)[len("splat."):-len(".yaml")]
        if alias == "us.exe":
            alias, path, base = "main", "extracted/retail/SLUS_007.26", 0x8000F800
        else:
            t = open(cfg).read()
            m = re.search(r"target_path:\s*(\S+)", t)
            v = re.search(r"vram(?:_addr)?:\s*(0x[0-9A-Fa-f]+)", t)
            if not (m and v):
                continue
            path, base = m.group(1), int(v.group(1), 16)
        if only and alias not in only:
            continue
        p = os.path.join(REPO, path)
        if os.path.exists(p):
            yield alias, p, base


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("addr")
    ap.add_argument("--binaries")
    a = ap.parse_args()
    target = int(a.addr, 16)
    only = set(a.binaries.split(",")) if a.binaries else None
    print(f"register-tracked search for 0x{target:08X}  (§155: no window-pairing)\n")
    total = 0
    for alias, path, base in binaries(only):
        data = open(path, "rb").read()
        hits = scan(data, base, target)
        if hits:
            total += len(hits)
            print(f"=== {alias}  (base 0x{base:08X}) — {len(hits)} hit(s)")
            for va, kind, det in hits[:12]:
                print(f"    0x{va:08X}  {kind:11s} {det}")
    print(f"\ntotal: {total} register-verified reference(s)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
