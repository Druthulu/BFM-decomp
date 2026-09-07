#!/usr/bin/env bash
# tools/wiki_sync.sh [--push] [--wiki-url URL] — publish docs/wiki/ + docs/how-to-ai-decomp/ to the GitHub wiki (P33 F3).
#
# The wiki is authored IN THIS REPOSITORY (owner decision 8): the pages under docs/wiki/ and the how-to chapters under
# docs/how-to-ai-decomp/ are the source of truth, link-checked by tools/doc_links.py and covered by the history rewrite.
# This script renders them into GitHub-wiki page names (tools/wiki_render.py rewrites the relative links), stages them
# in a clone of the wiki repository under .run/wiki/, shows the resulting diff, and — ONLY with --push, which is Drew's
# to run (R6: Claude never pushes) — commits and pushes.
#
#   tools/wiki_sync.sh            # dry run: render, refresh the clone if it exists, print `git status --short` of the sync
#   tools/wiki_sync.sh --push     # Drew: the same, then commit + push to <repo>.wiki.git
#
# The wiki repository (https://github.com/Druthulu/BFM-decomp.wiki.git) exists only after Wikis is ENABLED in the repo settings
# (works while the repo is still private — a private repo's wiki is private and flips with it; S89) AND
# after someone creates the first page in the GitHub UI (Wiki → "Create the first page"); until then the clone fails and
# the dry run still renders and lists the pages (exit 0) while --push refuses (exit 2). A page edited on GitHub is
# overwritten by the next sync — edit docs/wiki/ instead.
set -uo pipefail
REPO="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$REPO"
PUSH=0; URL="https://github.com/Druthulu/BFM-decomp.wiki.git"
while [ $# -gt 0 ]; do case "$1" in --push) PUSH=1 ;; --wiki-url) URL="$2"; shift ;; *) echo "wiki_sync: unknown arg $1" >&2; exit 2 ;; esac; shift; done
RENDER="$REPO/.run/wiki/render"; CLONE="$REPO/.run/wiki/BFM-decomp.wiki"
mkdir -p "$REPO/.run/wiki"

# 1. render (refuses on a dead link) — always, so a dry run proves the pages before any wiki exists
rm -rf "$RENDER"
.venv/bin/python tools/wiki_render.py --selftest >/dev/null || { echo "wiki_sync: wiki_render --selftest FAILED — fix the renderer first"; exit 1; }
.venv/bin/python tools/wiki_render.py "$RENDER" || exit 1
n=$(ls "$RENDER"/*.md | wc -l)

# 2. the wiki clone (created or fast-forwarded)
if [ -d "$CLONE/.git" ]; then
    git -C "$CLONE" pull -q --ff-only || { echo "wiki_sync: the wiki clone at $CLONE did not fast-forward — resolve by hand (or rm -rf it)"; exit 1; }
elif ! git clone -q "$URL" "$CLONE" 2>/dev/null; then
    echo "wiki_sync: $URL is not clonable yet — the wiki exists only after Wikis is enabled in Settings (private is fine) AND after the first page is created"
    echo "           in the GitHub UI (Wiki → Create the first page). Rendered $n pages into $RENDER:"
    ls "$RENDER" | sed 's/^/             /'
    [ $PUSH = 1 ] && { echo "wiki_sync: --push refused (no wiki repository)"; exit 2; }
    echo "wiki_sync: dry run OK (nothing to diff against)"; exit 0
fi

# 3. sync: the rendered set REPLACES the wiki's pages (the repo is the source of truth)
find "$CLONE" -maxdepth 1 -name '*.md' -type f -delete
cp "$RENDER"/*.md "$CLONE"/
git -C "$CLONE" add -A
if git -C "$CLONE" diff --cached --quiet; then echo "wiki_sync: the wiki is up to date ($n pages)"; exit 0; fi
echo "wiki_sync: changes staged in $CLONE ($n pages rendered):"
git -C "$CLONE" status --short | sed 's/^/   /'
[ $PUSH = 1 ] || { echo "wiki_sync: dry run — re-run with --push (Drew, R6) to publish"; exit 0; }

# 4. --push (Drew)
msg="wiki: sync from BFM-decomp $(git rev-parse --short HEAD)"
git -C "$CLONE" commit -q -m "$msg" && git -C "$CLONE" push && echo "wiki_sync: pushed — $msg"
