#!/bin/bash
# bank.sh <binary> <tu> <asmdir> <arm> <title> fn...  — verbatim grep, rtu_match each, splice each, ONE build, sha vs config, commit on green.
# Refuses (exit 1) on: __asm__/.word in a draft, rtu non-MATCH, splice failure, build rc≠0, sha mismatch. Never commits on red.
set -u
cd /home/musashi/bfm-decomp
bin=$1; tu=$2; asmdir=$3; arm=$4; title=$5; shift 5
fns=("$@"); [ ${#fns[@]} -ge 1 ] || { echo "REFUSED: no function names given after the title (R43)"; exit 2; }
want=$(cut -d' ' -f1 config/check.$bin.sha); log=.run/P32/t3s3/bank_${bin}_$(date +%H%M%S).log
for fn in "${fns[@]}"; do d=.run/P32/t3/$arm/$fn.c; [ -f "$d" ] || { echo "NO DRAFT $d"; exit 1; }
  n=$(grep -cE '\.ent|\.word|__asm__[^;]*"[^"]*\b[a-z]{2,5}[ \t]+\$' "$d" || true); [ "$n" = 0 ] || { echo "VERBATIM-SUSPECT $fn ($n): an asm carrying an instruction (zero-byte fences/launders are fine)"; exit 1; }
  r=$(.venv/bin/python tools/rtu_match.py $fn --split $bin --source $bin --c "$d" --asm-subdir "$asmdir" --work .run/P32/t3s3/verify_bank/$fn 2>&1 | grep -m1 '^MATCH\|^DIFF\|^CC1'); echo "$fn: $r"
  case "$r" in MATCH*) ;; *) echo "STOP: $fn not MATCH"; exit 1;; esac; done
for fn in "${fns[@]}"; do .venv/bin/python .run/P32/t3s3/splice.py "$tu" "$asmdir" $fn .run/P32/t3/$arm/$fn.c || exit 1; done
make build BINARY=$bin -j8 > "$log" 2>&1; rc=$?; echo "BUILD_RC=$rc"
grep -in 'error\|conflicting\|undefined ref' "$log" | head -6
[ $rc = 0 ] || { echo "BUILD FAILED — tree left for diagnosis (R42: do not blind-revert)"; exit 1; }
got=$(sha1sum build/$bin/$bin | cut -d' ' -f1); echo "sha $got vs $want"
[ "$got" = "$want" ] || { echo "SHA MISMATCH"; exit 1; }
left=$(grep -c INCLUDE_ASM "$tu" || true)
body=""; for fn in "${fns[@]}"; do body+="- $fn: draft .run/P32/t3/$arm/$fn.c ($arm agent, agent MATCH re-verified by coordinator rtu_match in the real TU)"$'\n'; done
git add "$tu" || exit 1
git commit -q -F - <<EOM || { echo "COMMIT FAILED"; exit 1; }
$title

$body- one build for the same-TU batch: make build BINARY=$bin -j8 rc 0; sha1 $got == config/check.$bin.sha (BYTE-IDENTICAL)
- $tu: $left INCLUDE_ASM left

Claude-Session: 491895ad-3c84-4037-b04f-bf7e5ee16a0c
EOM
git log --oneline -1
