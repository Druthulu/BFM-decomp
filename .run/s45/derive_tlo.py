#!/usr/bin/env python3
"""S45 II.1 pre-step: derive each module's TEXT_LO (code-start file offset) from the §154 law.

Law (memory-map §S44 / cookbook §154): payload word0 is a global module id; some payloads follow
it with a fn-ptr table of vram addresses inside the module's own load region. Code starts at
min(table target) - vram when a table exists, else right after the id word (0x4).

Output: a TSV roster (alias, payload, vram, size, id, n_ptrs, text_lo, first-code-word) for
eyeball + consumption by the onboarding loop. Read-only; touches nothing outside .run/s45/.
"""
import struct, sys, os
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
SLOT_A, SLOT_B, SLOT_RES, SLOT_SC07 = 0x800CAE08, 0x800CCB1C, 0x800CEDF8, 0x801A00D8

def payload_of(cd, n):
    d = ROOT / f"extracted/retail/{cd}.CD.dir/FILE_{n:03d}.dir"
    cands = sorted(d.glob("*.1"))
    if len(cands) != 1:
        raise SystemExit(f"{d}: expected exactly one type-1 payload, got {[c.name for c in cands]}")
    return cands[0]

def derive(path, vram):
    data = path.read_bytes()
    size = len(data)
    n_words = size // 4
    words = struct.unpack(f"<{n_words}I", data[: n_words * 4])
    mod_id = words[0]
    lo, hi = vram, vram + size
    # consecutive in-region pointers immediately after the id word = the fn-ptr table
    ptrs = []
    i = 1
    while i < n_words and lo <= words[i] < hi:
        ptrs.append(words[i]); i += 1
    tlo = (min(ptrs) - vram) if ptrs else 4
    table_end = 4 + 4 * len(ptrs)
    gap = tlo - table_end  # non-table bytes between table end and code start (expect 0)
    return size, mod_id, len(ptrs), tlo, gap, (words[tlo // 4] if tlo // 4 < n_words else 0)

rows = []
def add(alias, cd, n, vram):
    p = payload_of(cd, n)
    size, mod_id, nptr, tlo, gap, w = derive(p, vram)
    rows.append((alias, str(p.relative_to(ROOT)), f"0x{vram:08X}", size, f"0x{mod_id:X}",
                 nptr, f"0x{tlo:X}", gap, f"0x{w:08X}"))

# resident-slot boot modules (loadDestPtrTable[0]); MAIN/0 ≡ MAIN/1 — onboard once as md_MAIN_001
add("md_MAIN_001", "MAIN", 1, SLOT_RES)
add("md_MAIN_008", "MAIN", 8, SLOT_RES)
add("md_MAIN_011", "MAIN", 11, SLOT_RES)
for n in range(13, 42):   # D_800D3764: MAIN/13..41 -> slot A
    add(f"md_MAIN_{n:03d}", "MAIN", n, SLOT_A)
for n in range(42, 48):   # D_800D384C: MAIN/42..47 -> slot B
    add(f"md_MAIN_{n:03d}", "MAIN", n, SLOT_B)
add("md_SC07_003", "SC07", 3, SLOT_SC07)
add("md_SC07_004", "SC07", 4, SLOT_SC07)

# MAIN/0 twin check
t0 = payload_of("MAIN", 0).read_bytes(); t1 = payload_of("MAIN", 1).read_bytes()
print(f"# MAIN/0 == MAIN/1 byte-identical: {t0 == t1}  ({len(t0)} vs {len(t1)} bytes)")

out = ROOT / ".run/s45/module_roster.tsv"
with open(out, "w") as f:
    f.write("alias\tpayload\tvram\tsize\tmod_id\tn_ptrs\ttext_lo\tgap\tword_at_tlo\n")
    for r in rows:
        f.write("\t".join(str(x) for x in r) + "\n")
print(f"# wrote {out} ({len(rows)} modules)")
for r in rows:
    print("\t".join(str(x) for x in r))
