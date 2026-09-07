#!/usr/bin/env bash
# tools/public_rewrite/probe_github.sh — Drew's post-purge probe: do the OLD hashes still resolve on GitHub? (P33 C10)
#
#   tools/public_rewrite/probe_github.sh [--after-flip] [--repo Druthulu/BFM-decomp] [--n 30]
#
# Needs `gh auth login` in the running shell (Drew's) and .run/public_rewrite/old-to-new.tsv (build_commit_map.py).
# Samples N old hashes evenly over the map + the pruned commit's old hash + the old tag tip (if recorded) and, for each:
#   * `gh api repos/<repo>/commits/<sha>` must FAIL with 404 (still 200 = GitHub still serves the old object);
#   * `git fetch origin <sha>` must FAIL (still fetchable = still on the server, cached views or not).
# Positive control: the current `main` sha MUST succeed both ways (proves the probe can see a live commit).
# --after-flip additionally probes 7-char prefixes UNAUTHENTICATED at https://github.com/<repo>/commit/<7> (expect 404).
# Exit 0 only when every old sha is gone and the control passes. Re-run daily while anything returns 200.
set -uo pipefail
REPO="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
GH_REPO="Druthulu/BFM-decomp"; N=30; AFTER=0
while [ $# -gt 0 ]; do case "$1" in --after-flip) AFTER=1 ;; --repo) GH_REPO="$2"; shift ;; --n) N="$2"; shift ;; *) echo "unknown arg $1" >&2; exit 2 ;; esac; shift; done
MAP="$REPO/.run/public_rewrite/old-to-new.tsv"
[ -f "$MAP" ] || { echo "probe: $MAP missing (run build_commit_map.py)"; exit 2; }
command -v gh >/dev/null || { echo "probe: gh not on PATH"; exit 2; }
gh auth status >/dev/null 2>&1 || { echo "probe: gh is not authenticated — run: gh auth login"; exit 2; }
cd "$REPO"
mapfile -t OLD < <(awk -F'\t' 'NR>1 && $2 != $3 {print $2}' "$MAP")     # skip commits the rewrite left identical (old == new)
total=${#OLD[@]}; step=$(( total / N )); [ "$step" -lt 1 ] && step=1
SAMPLE=(); for ((i=0; i<total; i+=step)); do SAMPLE+=("${OLD[$i]}"); done
PRUNED="$(awk -F'\t' 'NR>1 && $3 ~ /^0{40}$/ {print $2}' "$MAP" | head -1)"; [ -n "$PRUNED" ] && SAMPLE+=("$PRUNED")
[ -f "$REPO/.run/public_rewrite/old_tag_tip.txt" ] && SAMPLE+=("$(cat "$REPO/.run/public_rewrite/old_tag_tip.txt")")
echo "probe: $GH_REPO — ${#SAMPLE[@]} old hashes (every ${step}th of $total + pruned + tag tip)"
alive=0
for sha in "${SAMPLE[@]}"; do
    code="$(gh api "repos/$GH_REPO/commits/$sha" --silent 2>&1 | grep -oE 'HTTP [0-9]{3}' | head -1)"
    api_gone=0; [ -z "$code" ] && code="HTTP 200"; [[ "$code" == *404* ]] && api_gone=1
    if git fetch --quiet origin "$sha" 2>/dev/null; then fetch_gone=0; else fetch_gone=1; fi
    if [ $api_gone = 1 ] && [ $fetch_gone = 1 ]; then echo "  gone  $sha"; else echo "  ALIVE $sha (api $code, fetch $([ $fetch_gone = 1 ] && echo fails || echo SUCCEEDS))"; alive=$((alive+1)); fi
    if [ $AFTER = 1 ]; then
        http="$(curl -s -o /dev/null -w '%{http_code}' "https://github.com/$GH_REPO/commit/${sha:0:7}")"
        [ "$http" = 404 ] || { echo "  ALIVE unauthenticated /commit/${sha:0:7} -> HTTP $http"; alive=$((alive+1)); }
    fi
done
cur="$(git rev-parse main)"
if gh api "repos/$GH_REPO/commits/$cur" --silent >/dev/null 2>&1 && git fetch --quiet origin "$cur" 2>/dev/null; then
    echo "  control: current main $cur resolves (OK)"
else
    echo "  control FAILED: current main $cur does not resolve — the probe cannot be trusted"; exit 2
fi
if [ $alive = 0 ]; then echo "probe: PASS — every sampled old hash is gone from $GH_REPO"; exit 0; fi
echo "probe: $alive still ALIVE — wait for the Support purge / GC and re-run"; exit 1
