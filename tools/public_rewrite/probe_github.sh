#!/usr/bin/env bash
# tools/public_rewrite/probe_github.sh — Drew's post-purge probe: do the OLD hashes still resolve on GitHub? (P33 C10)
#
#   tools/public_rewrite/probe_github.sh [--after-flip] [--repo Druthulu/BFM-decomp] [--n 30]
#
# Needs `gh auth login` in the running shell (Drew's) and .run/public_rewrite/old-to-new.tsv (build_commit_map.py).
# Samples N old hashes evenly over the map + the pruned commit's old hash + the old tag tip (if recorded) and, for each:
#   * `gh api repos/<repo>/commits/<sha>` must FAIL with 404/422 (still 200 = GitHub still serves the old object);
#   * a `git fetch` of that sha from origin must FAIL (still fetchable = still on the server, cached views or not).
# Positive control: the current `main` sha MUST succeed both ways (proves the probe can see a live commit).
# --after-flip additionally probes 7-char prefixes UNAUTHENTICATED at https://github.com/<repo>/commit/<7> (expect 404).
# Exit 0 only when every old sha is gone and the control passes. Re-run daily while anything returns 200.
#
# R57 (S88, 2026-09-07) — the fetch check runs in a THROWAWAY bare repo under .run/public_rewrite/, NEVER in the working
# repo: a successful `git fetch origin <old-sha>` downloads that commit's whole object closure — the purged EXE, the RAM
# dumps, the Ghidra DB, the SDK — into whichever repository runs it. The S87 baseline run and the first S88 run did exactly
# that to ~/bfm-decomp (30 packs / 5.97 GiB of unreachable old-history objects where C9 had left one 80 MB pack). Now the
# scratch repo is created per run and deleted on exit, and the fetch is `--filter=blob:none --depth=1` (the commit and its
# trees only — existence is the question, not content). The probe ends with a self-check that the WORKING repo holds none
# of the sampled old commits and prints the gc recipe if it does (that warning does not change the exit code).
set -uo pipefail
REPO="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
GH_REPO="Druthulu/BFM-decomp"; N=30; AFTER=0
while [ $# -gt 0 ]; do case "$1" in --after-flip) AFTER=1 ;; --repo) GH_REPO="$2"; shift ;; --n) N="$2"; shift ;; *) echo "unknown arg $1" >&2; exit 2 ;; esac; shift; done
MAP="$REPO/.run/public_rewrite/old-to-new.tsv"
[ -f "$MAP" ] || { echo "probe: $MAP missing (run build_commit_map.py)"; exit 2; }
command -v gh >/dev/null || { echo "probe: gh not on PATH"; exit 2; }
gh auth status >/dev/null 2>&1 || { echo "probe: gh is not authenticated — run: gh auth login"; exit 2; }
cd "$REPO"
URL="$(git remote get-url origin)"
SCRATCH="$REPO/.run/public_rewrite/probe_scratch.git"       # throwaway; holds whatever GitHub still serves, deleted on exit
rm -rf "$SCRATCH"
{ git init -q --bare "$SCRATCH" && git -C "$SCRATCH" remote add origin "$URL"; } || { echo "probe: cannot create $SCRATCH"; exit 2; }
trap 'rm -rf "$SCRATCH"' EXIT
fetchable() {   # $1 = full sha. Exit 0 iff origin still serves that commit. Objects land in $SCRATCH only (R57).
    git -C "$SCRATCH" fetch --quiet --no-tags --filter=blob:none --depth=1 origin "$1" >/dev/null 2>&1
}
mapfile -t OLD < <(awk -F'\t' 'NR>1 && $2 != $3 {print $2}' "$MAP")     # skip commits the rewrite left identical (old == new)
total=${#OLD[@]}; step=$(( total / N )); [ "$step" -lt 1 ] && step=1
SAMPLE=(); for ((i=0; i<total; i+=step)); do SAMPLE+=("${OLD[$i]}"); done
PRUNED="$(awk -F'\t' 'NR>1 && $3 ~ /^0{40}$/ {print $2}' "$MAP" | head -1)"; [ -n "$PRUNED" ] && SAMPLE+=("$PRUNED")
[ -f "$REPO/.run/public_rewrite/old_tag_tip.txt" ] && SAMPLE+=("$(cat "$REPO/.run/public_rewrite/old_tag_tip.txt")")
echo "probe: $GH_REPO — ${#SAMPLE[@]} old hashes (every ${step}th of $total + pruned + tag tip); fetch check in $SCRATCH"
alive=0
for sha in "${SAMPLE[@]}"; do
    code="$(gh api "repos/$GH_REPO/commits/$sha" --silent 2>&1 | grep -oE 'HTTP [0-9]{3}' | head -1)"
    # GitHub's commits API answers 422 ("No commit found for SHA") for an object it does not have, 404 for a repo it
    # cannot see; both mean gone (measured S87: the old tag tip = 422 + fetch fails)
    api_gone=0; [ -z "$code" ] && code="HTTP 200"; [[ "$code" == *404* || "$code" == *422* ]] && api_gone=1
    if fetchable "$sha"; then fetch_gone=0; else fetch_gone=1; fi
    if [ $api_gone = 1 ] && [ $fetch_gone = 1 ]; then echo "  gone  $sha"; else echo "  ALIVE $sha (api $code, fetch $([ $fetch_gone = 1 ] && echo fails || echo SUCCEEDS))"; alive=$((alive+1)); fi
    if [ $AFTER = 1 ]; then
        http="$(curl -s -o /dev/null -w '%{http_code}' "https://github.com/$GH_REPO/commit/${sha:0:7}")"
        [ "$http" = 404 ] || { echo "  ALIVE unauthenticated /commit/${sha:0:7} -> HTTP $http"; alive=$((alive+1)); }
    fi
done
cur="$(git rev-parse main)"
if gh api "repos/$GH_REPO/commits/$cur" --silent >/dev/null 2>&1 && fetchable "$cur"; then
    echo "  control: current main $cur resolves (OK)"
else
    echo "  control FAILED: current main $cur does not resolve — the probe cannot be trusted"; exit 2
fi
# R57 self-check: the instrument must not have written old objects into the repository it guards (nor may earlier runs have)
held=0; for sha in "${SAMPLE[@]}"; do git cat-file -e "$sha" 2>/dev/null && held=$((held+1)); done
if [ "$held" -gt 0 ]; then
    echo "probe: WARNING — the WORKING repo's object store holds $held of ${#SAMPLE[@]} sampled OLD commits (unreachable; a pre-S88"
    echo "       probe fetched them). Drop them:  git reflog expire --expire-unreachable=now --all && git gc --prune=now"
fi
if [ $alive = 0 ]; then echo "probe: PASS — every sampled old hash is gone from $GH_REPO"; exit 0; fi
echo "probe: $alive still ALIVE — wait for the Support purge / GC and re-run"; exit 1
