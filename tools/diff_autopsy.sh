#!/bin/bash
# tools/diff_autopsy.sh <binary> <fn> <tu.c> <draft.c> — splice the RAW draft into the real TU (what the gate
# WHY (P31 T1, 2026-08-26): the whole-binary gate says DIFF but not WHERE. This reproduces exactly what the gate
# saw (raw draft spliced into the real TU), cmp's the built binary against the byte-good one, decodes the
# diverging words, and restores the tree + build output. Two resolver DIFF refusals were autopsied to a single
# wrong internal-`j` target each this way (cookbook §301). Use tools/vaddr: file offset + splat vram => symbol via the .map.
# sees), build the overlay, cmp against the byte-good binary, map the first diverging offsets, RESTORE.
set -u; cd /home/musashi/bfm-decomp
B=$1; F=$2; TU=$3; DR=$4; D=.run/diff_autopsy; GOOD=$(cut -c1-40 config/check.$B.sha)
cp "$TU" "$D/$B.$F.tu.orig"
restore(){ cp "$D/$B.$F.tu.orig" "$TU"; make build BINARY=$B >/dev/null 2>&1; echo "restored: $(sha1sum build/$B/$B | cut -c1-12) vs good ${GOOD:0:12}"; }
trap restore EXIT
make build BINARY=$B > "$D/$B.base.log" 2>&1
S=$(sha1sum build/$B/$B | cut -c1-40); [ "$S" = "$GOOD" ] || { echo "BASELINE NOT GOOD ($S) — aborting"; exit 2; }
cp build/$B/$B "$D/$B.good"
python3 - "$TU" "$F" "$DR" <<'PY'
import sys,re
tu,fn,dr=sys.argv[1:4]; t=open(tu).read(); d=open(dr).read()
pat=re.compile(r'^INCLUDE_ASM\("[^"]+",\s*%s\);\s*$'%re.escape(fn),re.M)
assert len(pat.findall(t))==1, pat.findall(t)
open(tu,'w').write(pat.sub(lambda m:d, t))
PY
make build BINARY=$B > "$D/$B.$F.build.log" 2>&1; rc=$?
echo "build rc=$rc $(grep -ciE 'error' $D/$B.$F.build.log) error-lines"
cp build/$B/$B "$D/$B.$F.bad"
echo "sizes good=$(stat -c %s $D/$B.good) bad=$(stat -c %s $D/$B.$F.bad)"
N=$(cmp -l "$D/$B.good" "$D/$B.$F.bad" | wc -l); echo "differing bytes: $N"
cmp -l "$D/$B.good" "$D/$B.$F.bad" | awk '{printf "off=0x%X good=%02X bad=%02X\n",$1-1,strtonum("0"$2),strtonum("0"$3)}' | head -12
echo "-- diff offsets (first/last): $(cmp -l $D/$B.good $D/$B.$F.bad | awk 'NR==1{printf "0x%X ",$1-1} END{printf "0x%X\n",$1-1}')"
ls build/$B/ | head -8
