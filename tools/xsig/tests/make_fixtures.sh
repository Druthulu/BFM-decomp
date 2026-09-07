#!/usr/bin/env bash
# tests/make_fixtures.sh — regenerate the committed fixtures from tests/fixture.c with the pinned toolchain.
#
# Needs the BFM-decomp checkout's toolchain (run from that repository's root): the vintage cc1 under tools/bin/,
# maspsx under tools/maspsx/, and mipsel-linux-gnu binutils. The OUTPUTS are what the tests read — plain objdump
# listings and a splat-style .s — so the tests themselves need no compiler and contain no game bytes.
#
#   fixture_a.txt   objdump -dr of fixture.o linked at 0x80010000 (helper @0x80012000, table @0x80020000)
#   fixture_b.txt   the same object linked at 0x80200000 (helper @0x80212000, table @0x80230000)
#   fixture_a.s     fixture() from fixture_a.txt rewritten in splat's `/* off vaddr WORD */ mnemonic operands` form,
#                   with %hi()/%lo() operands where the listing carries R_MIPS_HI16/LO16
# The two listings differ ONLY in relocated fields (link addresses); xsig must sign them identically.
set -euo pipefail
HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO="${BFM_REPO:-$(cd "$HERE/../../.." && pwd)}"
CC1="$REPO/tools/bin/gcc-2.7.2-psx/cc1"; MASPSX="$REPO/tools/maspsx/maspsx.py"; PY="${PY:-$REPO/.venv/bin/python}"
[ -x "$CC1" ] || { echo "make_fixtures: $CC1 missing (tools/bootstrap.sh in the BFM checkout)"; exit 2; }
W="$(mktemp -d "$HERE/.fx.XXXX")"; trap 'rm -rf "$W"' EXIT
mipsel-linux-gnu-cpp -lang-c -undef -Wall -fno-builtin -Dmips -D__GNUC__=2 -D__OPTIMIZE__ -Dpsx -D_PSYQ -D_MIPSEL -D_LANGUAGE_C "$HERE/fixture.c" \
  | "$CC1" -quiet -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker \
  | "$PY" "$MASPSX" --aspsx-version=2.56 --expand-div \
  | mipsel-linux-gnu-as -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0 -o "$W/fixture.o"
link() {  # $1 out.elf  $2 text  $3 helper  $4 table
    mipsel-linux-gnu-ld -q -e fixture -Ttext="$2" --defsym "helper=$3" --defsym "table=$4" -o "$1" "$W/fixture.o"
}
link "$W/a.elf" 0x80010000 0x80012000 0x80020000
link "$W/b.elf" 0x80200000 0x80212000 0x80230000
# objdump interleaves relocation records into the disassembly only for OBJECT files; for a linked ELF (--emit-relocs)
# it lists them separately (`-r`, section-relative offsets). Merge them in, exactly in the interleaved format an
# object listing has — the format xsig's front-end reads.
listing() {  # $1 elf  $2 text-vma  $3 out
    "$PY" - "$1" "$2" "$3" <<'PYEOF'
import re, subprocess, sys
elf, base, out = sys.argv[1], int(sys.argv[2], 16), sys.argv[3]
dis = subprocess.run(["mipsel-linux-gnu-objdump", "-d", elf], capture_output=True, text=True, check=True).stdout
rel = subprocess.run(["mipsel-linux-gnu-objdump", "-r", elf], capture_output=True, text=True, check=True).stdout
recs = {}
sect = None
for ln in rel.splitlines():
    m = re.match(r"RELOCATION RECORDS FOR \[(\S+)\]:", ln)
    if m:
        sect = m.group(1); continue
    m = re.match(r"^([0-9a-f]+)\s+(R_MIPS_\w+)\s+(\S+)", ln)
    if m and sect == ".text":
        recs.setdefault(base + int(m.group(1), 16), []).append((m.group(2), m.group(3)))
lines = []
for ln in dis.splitlines():
    lines.append(ln)
    m = re.match(r"^\s*([0-9a-f]+):\s+[0-9a-f]{8}\s", ln)
    if m:
        for typ, sym in recs.get(int(m.group(1), 16), []):
            lines.append(f"\t\t\t{m.group(1)}: {typ}\t{sym}")
open(out, "w").write("\n".join(lines) + "\n")
print(f"{out}: {sum(len(v) for v in recs.values())} relocation records merged")
PYEOF
}
listing "$W/a.elf" 0x80010000 "$HERE/fixture_a.txt"
listing "$W/b.elf" 0x80200000 "$HERE/fixture_b.txt"
# the splat-style .s of fixture() from listing A: /* off vaddr LEHEX */ mnemonic operands, %hi/%lo from the reloc lines
"$PY" - "$HERE/fixture_a.txt" "$HERE/fixture_a.s" <<'EOF'
import re, struct, sys
src, dst = sys.argv[1], sys.argv[2]
lines = open(src).read().splitlines()
out, cur, i = [], None, 0
while i < len(lines):
    ln = lines[i]
    h = re.match(r"^([0-9a-f]+) <([^>]+)>:", ln)
    if h:
        cur = h.group(2); i += 1; continue
    m = re.match(r"^\s*([0-9a-f]+):\s+([0-9a-f]{8})\s+(\S+)\s*(.*)", ln)
    if m and cur == "fixture":
        addr, word, mn, ops = int(m.group(1), 16), int(m.group(2), 16), m.group(3), m.group(4).strip()
        reloc = lines[i + 1] if i + 1 < len(lines) and "R_MIPS" in lines[i + 1] else ""
        if "_HI16" in reloc:
            ops = re.sub(r"0x[0-9a-f]+|-?\d+$", "%hi(table)", ops) if ops else "%hi(table)"
        elif "_LO16" in reloc:
            ops = re.sub(r"(-?0x[0-9a-f]+|-?\d+)(\(\$\w+\))?$", r"%lo(table)\2", ops) if ops else "%lo(table)"
        le = struct.pack("<I", word).hex().upper()
        out.append(f"/* {addr - 0x80010000:X} {addr:X} {le} */  {mn} {ops}".rstrip())
    i += 1
open(dst, "w").write("glabel fixture\n" + "\n".join(out) + "\n")
print(f"{dst}: {len(out)} instructions")
EOF
echo "fixtures regenerated: $(grep -c '^ *[0-9a-f]*:' "$HERE/fixture_a.txt") + $(grep -c '^ *[0-9a-f]*:' "$HERE/fixture_b.txt") listing lines"
