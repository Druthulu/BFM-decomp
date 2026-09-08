#!/bin/bash
# decompme_replica.sh — run a function through decomp.me's EXACT PS1 `gcc2.7.2-psx` toolchain, locally, and compare
# the code words against the ROM-derived target; run our Makefile pipeline on the same source as the control.
#
# WHY (P33 E1, 2026-09-07). decomp.me's API is Cloudflare-blocked to scripts and a preset cannot be deleted by its
# owner (the backend returns 405 — admin panel only), so a preset must be right before it is saved. decomp.me does
# not run our toolchain: its image is built from decompme/compilers `platforms/ps1/gcc2.7.2-psx/Dockerfile`:
#   old-gcc release 0.13 `gcc-2.7.2-psx.tar.gz`   (we run 0.17)
#   maspsx at commit 86ccd7d8 (values.yaml `maspsx_hash`; we pin 874855c5 — 86ccd7d8 is 4 commits later)
#   `as` = a two-line wrapper: python3 maspsx.py --run-assembler -I${COMPILER_DIR} "$@"
# and the backend (coreapp/compilers.py PS1_GCC) drives it as
#   /usr/bin/cpp -nostdinc INPUT | sed "s/^# 0/# 1/" > INPUT.i ; gcc ${COMPILER_FLAGS} -c -pipe -B${COMPILER_DIR}/ -o OUT INPUT.i
# This script rebuilds that directory under .run/decompme/ (the tarball sha256-checked, maspsx from our submodule's
# object store) and runs the same two commands. A byte-identical verdict here is what "the preset matches on
# decomp.me" means, minus the browser.
#
# READ THE VERDICT, NOT THE .text SIZE: gas without `-no-pad-sections` (decomp.me's wrapper passes none) pads .text to
# 16 bytes, so the object may carry trailing zero words after the function; they are reported separately and never
# counted against the match (an instrument artefact caught on the first run — R40).
#
# Usage:
#   tools/decompme_replica.sh                       # the canonical probe: func_80018F20 from src/800.c (Phase-6 fingerprint fn)
#   tools/decompme_replica.sh --src probe.c --fn NAME [--binary main] [--flags "<preset flags>"]
#   tools/decompme_replica.sh --upstream            # print decomp.me's CURRENT pins (Dockerfile/values.yaml) vs the constants here
# The --src TU must be self-contained (typedefs + the function), exactly what a decomp.me scratch's context + source is.
# Exit 0 only when the decomp.me replica is byte-identical to the target on the function's words.
set -u
REPO="$(cd "$(dirname "$0")/.." && pwd)"
cd "$REPO" || exit 2
SCRATCH="$REPO/.run/decompme"

# ---- decomp.me's pins (source: decompme/compilers main, read 2026-09-07; verify with --upstream) ----
OLDGCC_REL="0.13"
OLDGCC_URL="https://github.com/decompals/old-gcc/releases/download/${OLDGCC_REL}/gcc-2.7.2-psx.tar.gz"
OLDGCC_SHA256="aca64479041aa2d645dc52ebcaace276c0aa06f258c0e3f190ccf6d76701ffbc"
MASPSX_HASH="86ccd7d8c89682c0562d1425bbb15a09f42eb522"
UPSTREAM_DOCKERFILE="https://raw.githubusercontent.com/decompme/compilers/main/platforms/ps1/gcc2.7.2-psx/Dockerfile"
# the project's preset (docs/decompme-preset.md, SETUP §6.5)
PRESET_FLAGS='-O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker -Wa,--aspsx-version=2.56,--expand-div'

FN="func_80018F20"; BINARY="main"; SRC=""; FLAGS="$PRESET_FLAGS"; UPSTREAM=0
while [ $# -gt 0 ]; do
  case "$1" in
    --fn) FN="$2"; shift 2;;
    --binary) BINARY="$2"; shift 2;;
    --src) SRC="$2"; shift 2;;
    --flags) FLAGS="$2"; shift 2;;
    --upstream) UPSTREAM=1; shift;;
    -h|--help) sed -n '2,30p' "$0"; exit 0;;
    *) echo "decompme_replica: unknown argument $1" >&2; exit 2;;
  esac
done

if [ "$UPSTREAM" = 1 ]; then
  echo "decomp.me's current gcc2.7.2-psx recipe ($UPSTREAM_DOCKERFILE):"
  body=$(curl -fsSL "$UPSTREAM_DOCKERFILE") || { echo "  fetch failed"; exit 1; }
  rel=$(printf '%s\n' "$body" | grep -o 'old-gcc/releases/download/[^/]*/' | head -1 | cut -d/ -f4)
  mh=$(printf '%s\n' "$body" | grep -o 'maspsx/archive/[0-9a-f]*' | head -1 | cut -d/ -f3)
  echo "  old-gcc release: ${rel:-?}   (this script: $OLDGCC_REL)"
  echo "  maspsx commit:   ${mh:-?}   (this script: $MASPSX_HASH)"
  if [ "$rel" = "$OLDGCC_REL" ] && [ "$mh" = "$MASPSX_HASH" ]; then echo "  pins UNCHANGED"; exit 0; fi
  echo "  pins DRIFTED — update the constants in $0 and re-run the probe (docs/decompme-preset.md §4)"; exit 1
fi

for t in cpp mipsel-linux-gnu-as mipsel-linux-gnu-ld mipsel-linux-gnu-objcopy mipsel-linux-gnu-cpp python3 sha256sum; do
  command -v "$t" >/dev/null || { echo "decompme_replica: $t not found (apt: gcc binutils-mipsel-linux-gnu cpp-mipsel-linux-gnu)" >&2; exit 2; }
done
[ -x tools/bin/gcc-2.7.2-psx/cc1 ] || { echo "decompme_replica: tools/bin/gcc-2.7.2-psx/cc1 missing — run tools/bootstrap.sh" >&2; exit 2; }
[ -x .venv/bin/python ] || { echo "decompme_replica: .venv missing — run tools/bootstrap.sh" >&2; exit 2; }

mkdir -p "$SCRATCH"
# ---- 1. decomp.me's compiler directory, rebuilt ----
DM="$SCRATCH/gcc2.7.2-psx"
if [ ! -x "$DM/gcc" ] || [ ! -x "$DM/cc1" ]; then
  mkdir -p "$SCRATCH/oldgcc-$OLDGCC_REL" "$DM"
  tb="$SCRATCH/oldgcc-$OLDGCC_REL/gcc-2.7.2-psx.tar.gz"
  [ -f "$tb" ] || curl -fsSL -o "$tb" "$OLDGCC_URL" || { echo "decompme_replica: download failed: $OLDGCC_URL" >&2; exit 1; }
  echo "$OLDGCC_SHA256  $tb" | sha256sum --check --quiet || { echo "decompme_replica: sha256 MISMATCH for $tb — refusing" >&2; exit 1; }
  tar xzf "$tb" -C "$SCRATCH/oldgcc-$OLDGCC_REL" || exit 1
  cp "$SCRATCH/oldgcc-$OLDGCC_REL"/{gcc,cc1,cpp} "$DM/"
fi
if [ ! -f "$DM/maspsx/maspsx.py" ]; then
  git -C tools/maspsx cat-file -e "$MASPSX_HASH^{commit}" 2>/dev/null || git -C tools/maspsx fetch -q origin || true
  git -C tools/maspsx cat-file -e "$MASPSX_HASH^{commit}" 2>/dev/null || { echo "decompme_replica: maspsx $MASPSX_HASH not in tools/maspsx (fetch failed)" >&2; exit 1; }
  mkdir -p "$DM/maspsx" && git -C tools/maspsx archive "$MASPSX_HASH" | tar -x -C "$DM/maspsx" || exit 1
fi
# the wrapper, verbatim from the Dockerfile
printf '#!/bin/bash\npython3 $(dirname -- $0)/maspsx/maspsx.py --run-assembler -I${COMPILER_DIR} $@\n' > "$DM/as"
chmod +x "$DM"/gcc "$DM"/cc1 "$DM"/cpp "$DM"/as

# ---- 2. the probe TU ----
WORK="$SCRATCH/probe_$FN"; rm -rf "$WORK"; mkdir -p "$WORK"
if [ -z "$SRC" ]; then
  if [ "$FN" != "func_80018F20" ] || [ "$BINARY" != "main" ]; then echo "decompme_replica: --src is required for anything but the canonical probe" >&2; exit 2; fi
  { printf 'typedef unsigned char u8;\ntypedef unsigned int  u32;\ntypedef int           s32;\n\n'
    awk '/^void func_80018F20\(/{f=1} f{print} f&&/^}/{exit}' src/800.c; } > "$WORK/probe.c"
  grep -q 'func_80018F20' "$WORK/probe.c" || { echo "decompme_replica: could not extract func_80018F20 from src/800.c" >&2; exit 1; }
else
  cp "$SRC" "$WORK/probe.c"
fi

# ---- 3. the target words, from the extracted image (never from our source) ----
.venv/bin/python tools/verbatim_target_s.py --binary "$BINARY" --fn "$FN" --out "$WORK/target" >/dev/null 2>"$WORK/target.err" \
  || { echo "decompme_replica: verbatim_target_s failed:"; cat "$WORK/target.err"; exit 1; }
TS="$WORK/target/$BINARY/$FN.s"; [ -f "$TS" ] || { echo "decompme_replica: no target .s at $TS" >&2; exit 1; }
VADDR=$(grep -o '^/\* [0-9A-F]* [0-9A-F]* [0-9A-F]* \*/' "$TS" | head -1 | awk '{print "0x"$3}')
grep -o '^/\* [0-9A-F]* [0-9A-F]* [0-9A-F]* \*/' "$TS" | awk '{print $4}' > "$WORK/target_words.txt"
NT=$(wc -l < "$WORK/target_words.txt")
echo "target: $BINARY:$FN — $NT words at $VADDR (tools/verbatim_target_s.py, from the image)"

compare() {  # $1 = object, $2 = label ; prints the verdict, returns 0 iff identical on the target's words
  local obj="$1" label="$2"
  mipsel-linux-gnu-ld -Ttext="$VADDR" -e "$FN" -o "$obj.elf" "$obj" 2>"$obj.ld.err" || { echo "  $label: LINK FAILED"; head -3 "$obj.ld.err"; return 1; }
  mipsel-linux-gnu-objcopy -O binary -j .text "$obj.elf" "$obj.bin" || return 1
  python3 - "$obj.bin" "$WORK/target_words.txt" "$label" <<'PY'
import sys
b=open(sys.argv[1],'rb').read(); tgt=[int.from_bytes(bytes.fromhex(l.strip()),'little') for l in open(sys.argv[2]) if l.strip()]
got=[int.from_bytes(b[i:i+4],'little') for i in range(0,len(b)-len(b)%4,4)]
n=len(tgt); head=got[:n]; tail=got[n:]
same=sum(1 for a,c in zip(head,tgt) if a==c)
pad='' if not tail else f"; +{len(tail)} trailing word(s) beyond the function: {'all zero (gas section padding)' if not any(tail) else 'NON-ZERO — read them'}"
if len(head)==n and same==n: print(f"  {sys.argv[3]}: BYTE-IDENTICAL on all {n} words{pad}"); sys.exit(0)
print(f"  {sys.argv[3]}: DIFFERS — {same}/{n} words identical, produced {len(got)} words{pad}")
for i,(a,c) in enumerate(zip(head,tgt)):
    if a!=c: print(f"    word {i:3d}: got {a:08x}  target {c:08x}")
if len(head)<n: print(f"    short by {n-len(head)} word(s)")
sys.exit(1)
PY
}

# ---- 4. A: decomp.me's two commands, verbatim ----
echo "A. decomp.me replica — old-gcc $OLDGCC_REL driver + maspsx ${MASPSX_HASH:0:8} as-wrapper; flags: $FLAGS"
cpp -nostdinc "$WORK/probe.c" | sed 's/^# 0/# 1/' > "$WORK/probe.i"
( export COMPILER_DIR="$DM"; "$DM/gcc" $FLAGS -c -pipe -B"$DM/" -o "$WORK/dm.o" "$WORK/probe.i" ) >"$WORK/dm.log" 2>&1
rcA=$?
if [ $rcA -ne 0 ] || [ ! -f "$WORK/dm.o" ]; then echo "  decomp.me replica: COMPILE FAILED (rc $rcA)"; head -12 "$WORK/dm.log"; RES_A=1; else compare "$WORK/dm.o" "decomp.me replica"; RES_A=$?; fi

# ---- 5. B: our Makefile pipeline on the same TU (the control) ----
CPPFLAGS='-lang-c -Iinclude -undef -Wall -fno-builtin -Dmips -D__GNUC__=2 -D__OPTIMIZE__ -Dpsx -D_PSYQ -D_MIPSEL -D_LANGUAGE_C'
CC1FLAGS='-quiet -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker'
ASFLAGS='-Iinclude -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0'
echo "B. our pipeline — old-gcc 0.17 cc1 + maspsx $(git -C tools/maspsx rev-parse --short HEAD) (Makefile flags)"
mipsel-linux-gnu-cpp $CPPFLAGS "$WORK/probe.c" > "$WORK/ours.i" 2>/dev/null
tools/bin/gcc-2.7.2-psx/cc1 $CC1FLAGS < "$WORK/ours.i" > "$WORK/cc1_ours.s" 2>"$WORK/cc1_ours.err"
.venv/bin/python tools/maspsx/maspsx.py --aspsx-version=2.56 --expand-div < "$WORK/cc1_ours.s" > "$WORK/mas_ours.s" 2>"$WORK/mas_ours.err"
mipsel-linux-gnu-as $ASFLAGS -o "$WORK/ours.o" "$WORK/mas_ours.s" 2>"$WORK/as_ours.err" && compare "$WORK/ours.o" "our pipeline (control)"; RES_B=$?

# ---- 6. attribution: swap one component at a time (text diffs, so a difference names its producer) ----
"$DM/cc1" $CC1FLAGS < "$WORK/ours.i" > "$WORK/cc1_dm.s" 2>/dev/null
if diff -q "$WORK/cc1_dm.s" "$WORK/cc1_ours.s" >/dev/null; then echo "C1. cc1 $OLDGCC_REL vs 0.17 on the same input: identical assembly text"; else echo "C1. cc1 $OLDGCC_REL vs 0.17: TEXT DIFFERS (diff below, ours = '>')"; diff "$WORK/cc1_dm.s" "$WORK/cc1_ours.s" | head -20; fi
python3 "$DM/maspsx/maspsx.py" --aspsx-version=2.56 --expand-div < "$WORK/cc1_ours.s" > "$WORK/mas_dm.s" 2>/dev/null
if diff -q "$WORK/mas_dm.s" "$WORK/mas_ours.s" >/dev/null; then echo "C2. maspsx ${MASPSX_HASH:0:8} vs $(git -C tools/maspsx rev-parse --short HEAD) on the same cc1 output: identical text"; else echo "C2. maspsx ${MASPSX_HASH:0:8} vs ours: TEXT DIFFERS (diff below, ours = '>')"; diff "$WORK/mas_dm.s" "$WORK/mas_ours.s" | head -20; fi

echo "scratch: $WORK"
if [ "$RES_B" -ne 0 ]; then echo "decompme_replica: the CONTROL failed — the probe TU does not reproduce the function in our own pipeline; fix the TU before reading A (R56)"; exit 3; fi
[ "$RES_A" -eq 0 ] && { echo "decompme_replica: PASS — the preset reproduces $FN byte-identically through decomp.me's toolchain"; exit 0; }
echo "decompme_replica: FAIL — decomp.me's toolchain does not reproduce $FN with these flags; see C1/C2 for the producer"; exit 1
