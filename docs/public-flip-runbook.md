# The public-flip runbook — Phase 33 Block C (the history rewrite, the push, the purge gate, the flip)

> **Status:** written at C3 (S87, 2026-09-06). The procedure is the approved Phase-33 plan's Block C, made operational:
> every step names its actor (**Claude** in the WSL clone, **Drew** for every push / GitHub action — rule R6), its exact
> commands, its checks (each an exit code or a count), and what to do if it fails. The tools it names under
> `tools/public_rewrite/` are written in C1; until then only `purge_set.txt` exists. Scratch for the whole block lives
> in `.run/public_rewrite/` (gitignored — it holds old hashes and personal addresses; never commit it).

## 0. The decisions this runbook implements (Drew, 2026-09-06 — binding)

1. **Flip IN PLACE with the full history.** `Druthulu/BFM-decomp` is force-pushed with a rewritten history: every commit,
   date, message and order preserved; hashes change; the one commit that touched only purged paths ("session archive
   update", 2026-08-12) drops as empty. No new repo.
2. **Purge from ALL history** — `tools/public_rewrite/purge_set.txt` is the single source of truth (filter-repo syntax):
   the retail EXE at both historical paths, `dumps/*.bin` (28 RAM images), `ghidra/` (the Ghidra project — its database
   embeds the EXE's bytes under the page XOR mask), `tools/psyq/` (Sony's SDK), `session archive/` (3 parts, ~271 MB, the
   only blobs > 50 MiB, ~260k lines of game disassembly inside), `tools/ghidra-ext/*.zip` (re-downloadable; sha256s in
   `docs/SETUP.md` §2.3/§2.4), `tools/brave-CUE/brave.exe` (a compiled GPL tool; the source stays).
3. **In-history hash scrub.** Every old commit hash cited in any historical blob or commit message becomes an inert token
   `commit:NNNN` (NNNN = the commit's ordinal on `main`); a token→new-hash map is committed (`docs/commit-map.tsv`); one
   tip commit resolves the tokens at HEAD to the new hashes so current docs stay navigable. **Fixed-point rule:** a new
   hash can never be written into a historical blob (it would change every descendant hash) — tokens in history, real
   hashes only at the tip.
4. **Identity:** both personal e-mail identities → `Drew T <50529377+Druthulu@users.noreply.github.com>` (`--mailmap`);
   names and dates untouched. The three tracked files that mention the addresses are literal-replaced in the same pass.
5. **Everything else stays public**, including `phase-ends/` (PhaseEnds AND `logs/`), `CLAUDE.md`, `PROJECT_CONTEXT.md`,
   the decision log, the accelerators and the campaign tooling.
6. **The archive:** `Druthulu/BFM-decomp-archive` (private, created EMPTY — never a fork or an import, those share
   GitHub's object store) receives the current, unrewritten history (all refs + the `S76-pre-scrub-backup` tag) BEFORE
   the rewrite. The tag is dropped from the public history.
7. **The flip is gated** on GitHub no longer serving the old hashes (Support purge, probed by script); delete-and-recreate
   under the same name is the fallback if Support stalls.

**Data-loss hazard, in force from C3 onward:** the purged paths are now *ignored but present* on disk. `git clean -x` /
`git clean -fdx` would delete the Ghidra database, the dumps and the SDK. `make clean` is the only clean. (CLAUDE.md
fail-safe rule; R20 amendment proposed at PhaseEnd_Phase33.)

## 1. Who does what

| Actor | Steps |
|---|---|
| **Claude** (WSL clone `~/bfm-decomp`) | C3 ✓, C1, C2, the bundle (C4a), the bare clone + rewrite (C4c), C5, C6, C7, C8, the C9 gate, C11's local part, every doc |
| **Drew** | creates the archive repo and pushes the mirror (C4b), the force-push + remote tag deletion (C9), the Support ticket, the probe re-runs, the visibility flip (C10), the other clones' resets (C11) |

Claude never runs `git push` (R6). Every Drew step is announced with its exact command and its check, and the session
WAITS for Drew's word that it ran (never inferred from a later `git fetch`).

## 2. C3 — the preparatory commit (DONE, S87)

`git rm --cached` of the purge set (index only; the files stay on disk, already ignored — checked with
`git check-ignore --no-index` on every path BEFORE they became untracked, because a blanket `git add -A` would otherwise
re-add ROM bytes). `tools/psyq/CHECKSUMS.sha256` had already moved to `tools/psyq_CHECKSUMS.sha256` (B4) — nothing
project-authored remained under a purged directory (census: 189 Sony/third-party files under `tools/psyq/`, 27 Ghidra
DB files, 3 archive parts, 2 zips, `brave.exe`, the EXE). Controls: `git ls-files -- <every purge path>` empty;
`tools/audit_public.py` → OK (it FAILED by design until this commit); `make check-env` 0; main byte-identical with
`tools/psyq/` + `.run/obj40` + `.run/obj42` moved aside (the public WITHOUT leg needs none of it). A5's recorded run stays
valid for this tip: a `--cached` removal changes no tracked-content byte.

## 3. C1 — the tooling (Claude; design Max, execution xHigh)

`.venv/bin/pip install git-filter-repo==2.47.0` (SETUP row, R21). `tools/public_rewrite/`:

| Tool | Does | Measured (S87; C2 re-measures on the final tree) |
|---|---|---|
| `purge_set.txt` | the purge paths (exists since B7) | 8 rules |
| `gate_scan.py --all \| --refs <refs> [--worktree] [--expect-fail tools/public_rewrite/expected_offenders.txt]` | the first-push gate over history: scans every blob reachable from the refs (and the worktree) for purge-path prefixes, content SHA1s in the known-ROM set (the EXE, the redump Track 1, every `sha1` in `extracted/retail/manifest.jsonl`, every `config/check.*.sha`), byte signatures (`PS-X EXE` at offset 0; the 2,097,152-byte RAM image with the resident's first words at 0xCEDF8; the EXE entry code; PsyQ `LIB\x01` / `LNK\x02` magics), any blob > 50 MiB; emits `rom_blob_ids.txt`. `--expect-fail FIXTURE` = the R39 negative control: the fixture lists `rule<TAB>min offending paths`; exit 0 only when every rule has at least that many AND no content/signature/size offender sits outside the purge rules; `rom_blob_ids.txt` = content hits ∪ every blob ever under a purge path | measured S87 on the current repo: 112,390 blobs / 16.8 GB in 2 m 25 s; paths ever: ghidra/ 42, tools/psyq/ 190, dumps 28, archive 3, zips 2, brave.exe 1, the EXE 1+1; 0 strays; 52 content/signature ids + 269 blobs ever under a purge path |
| `hash_dict.py [--write-mailmap]` | every commit hash → ordinal (`git rev-list --reverse main`); off-main commits (the tag lineage, 126) → the ordinal of their (tree, author-timestamp, subject) twin, else `orphan-NNN`; all prefixes 7..40; asserts 0 ambiguous prefixes and 0 collisions with the content-hash set | measured S87: 4,420 commit objects (4,030 main, 339 twins incl. the 126 tag-lineage re-authorings, 51 orphans), 150,280 prefixes, 0 ambiguous, 0 content collisions |
| `scrub.py` | THE one scrub function: `\b[0-9a-f]{7,40}\b` → dictionary lookup → `commit:NNNN` (non-hex in the first 7 chars, so it can never re-match; no Markdown side effects); NUL-sniff binary skip; idempotent | at HEAD (S87): 731 distinct resolving tokens, 1,238 replacements in 98 files, git's own lookup agrees exactly; 397 MB in 7.9 s |
| `run_filter.py [--sample]` | composes the `git filter-repo` call (below); refuses to run outside a bare repo under `.run/public_rewrite/`; logs versions + wall time; `--sample` first (R37) = `scrub.py --sample`, the independent-oracle check | the trial run's numbers are in phase-ends/CURRENT_PHASE.md (S87 C1) |
| `build_commit_map.py [--out PATH]` | public `docs/commit-map.tsv` (`ordinal  new_hash  author_date  committer_date  subject`, no old hash anywhere — asserted by running scrub over its own output); private `.run/public_rewrite/old-to-new.tsv` for the probe | 4,0xx rows, exactly one mapped to zeros (the pruned archive-upload commit) |
| `resolve_tokens.py [--check] [--map PATH]` | at HEAD of the adopted checkout: `commit:NNNN` → the unique 9-char new abbreviation (asserted by `git cat-file --batch-check`); `--check` asserts zero resolvable tokens remain and lists the orphan residue | ≥1 orphan: `tools/verify_worktree.py` cites a dropped TEMP commit |
| `verify_rewrite.py --old ~/bfm-decomp --new .run/public_rewrite/repo.git` | the pairwise proof (C5): old commits from the ORIGINAL repo (the clone gc's them away), new from the clone | every pair |
| `absent_scan.py [--repo PATH] [--tree HEAD]` | every text blob + every message + every ref → 0 old-hash prefixes, 0 personal addresses, 0 session URLs, 0 trailer lines, every identity = noreply, no replace/original/tag refs (≈7 min over all objects; INFO: bare UUID count) | 0 offenders (the current repo: FAIL, 82,362 — its positive control) |
| `probe_github.sh` | Drew's post-purge probe (C10) | — |
| `mailmap` (scratch, `.run/public_rewrite/mailmap`, written by `hash_dict.py --write-mailmap` from the log's identities) | the two personal identities → the noreply identity | never committed |

Budget: regex+lookup ≈2.2 CPU-min over 16.8 GB of blobs; the filter-repo stream dominates (10–30 min). Disk: a bare
`--no-local` clone ≈0.6 GB + the bundle ≈0.6 GB; no working-tree copy (the WSL disk is capped at 75 GB, ≈13 GB free).

## 4. C2 — negative control, dictionary, sample (Claude)

1. `gate_scan.py --all --worktree --expect-fail tools/public_rewrite/expected_offenders.txt` on the CURRENT repo → must
   report PASS (= the scan fails exactly as the fixture says; the scan that PASSES with 0 offenders in C5 is this same tool).
2. `hash_dict.py` → prints the counts; assert 0 ambiguous, 0 collisions.
3. `run_filter.py --sample` → the sample numbers above.

## 5. C4 — backups, then the rewrite

**C4a (Claude) — the bundle:** `git bundle create .run/public_rewrite/pre-rewrite.bundle --all --reflog && git bundle
verify .run/public_rewrite/pre-rewrite.bundle` (≈0.6 GB). This is the local restore point for everything below.

**C4b (Drew) — the archive mirror:**
```bash
# on GitHub: New repository → Druthulu/BFM-decomp-archive → Private → EMPTY (no README, no .gitignore, no license;
#            NOT "import" and NOT a fork)
cd ~/bfm-decomp
git remote add archive https://github.com/Druthulu/BFM-decomp-archive.git
git push --mirror archive
```
Check (Claude): `git for-each-ref --format='%(objectname) %(refname)' | sort` equals `git ls-remote archive | sort`
(same ref set, same hashes; the tag included). Only then may the rewrite start.

**C4c (Claude) — the bare clone + the rewrite:**
```bash
git clone --no-local --bare ~/bfm-decomp .run/public_rewrite/repo.git
cd .run/public_rewrite/repo.git
git tag -d S76-pre-scrub-backup            # the archive keeps it (decision 11)
git for-each-ref                          # must be exactly refs/heads/main at the prep commit
git count-objects -v                      # one pack, zero loose objects
.venv/bin/python ../../../tools/public_rewrite/run_filter.py   # composes:
#  git filter-repo --invert-paths --paths-from-file purge_set.txt --strip-blobs-with-ids rom_blob_ids.txt \
#      --blob-callback <scrub every text blob> --message-callback <scrub + drop 'Claude-Session:' trailers> \
#      --prune-empty auto --replace-refs delete-no-add --mailmap .run/public_rewrite/mailmap
```
Why each flag: `--prune-empty auto`, never `always` (main carries one pre-existing empty commit from 2026-08-25 that must
survive); `--replace-refs delete-no-add` (no `refs/replace/<old>` names may be minted — they would leak old hashes);
`--strip-blobs-with-ids` catches the EXE wherever it was renamed; the message callback also strips the 60 remaining
`Claude-Session:` trailer lines the S76 scrub missed.
Checks: exit 0; the commit map has (old main count) rows; the rows mapped to zeros are EXACTLY the commits whose every
change was a purge path (`verify_rewrite` derives that set — 1 on this history: "session archive update"); no
`refs/replace`; one pack. Pack size: filter-repo's own gc leaves ≈500 MB (trial #1: 534 → 520 MB — the 16 GB of scrubbed
text history re-deltas poorly; the purged binaries ARE gone: the archive/ghidra/dump blobs are absent from the store);
C9's local gc uses an aggressive repack — measured on trial #2: `git -c pack.threads=16 repack -adf --window=250
--depth=50` took the 500 MB pack to **80 MB in 166 s**.
**Lesson from trial #1 (S87):** stripping blobs BY ID must never include a blob that also lives under a non-purge path —
the EMPTY blob (an empty file once sat under `ghidra/`) was in the list, and `--strip-blobs-with-ids` then dropped every
"file emptied" change in history: those files silently kept their previous content and a later restore commit became
empty and was pruned. `gate_scan` now excludes shared blobs from `rom_blob_ids.txt` (content/signature hits are always
kept), and `verify_rewrite` asserts both that no purge path survives in any new tree and that the pruned set equals the
derived purge-only set.

## 6. C5 — verification on the rewritten clone (Claude; every check an exit code)

`verify_rewrite.py` — for every (old, new) pair: names/e-mails (post-mailmap) and BOTH timestamps equal; `new.message ==
scrub(old.message)`; new parents = map(old parents) with the pruned commit spliced out; `git diff-tree -r --no-renames old
new`: every `D` is a purge path or a ROM blob id, every `M` satisfies `hash-object(scrub(old_blob)) == new_blob`, any `A`
FAILS; prints the pair count. Then `gate_scan.py --refs --all` → PASS (the same tool that failed in C2); `absent_scan.py`
→ 0/0/0; `git rev-list --count main` = old count − pruned; the `%at %ct` lists match with the pruned commits removed; the
pre-existing empty commit's twin exists; no purge path in any new tree; the pruned set == the purge-only commits.
A commit the rewrite leaves BYTE-IDENTICAL keeps its hash (old == new — the noreply-authored "Initial commit", which cites
no hash and touches no purge path): `build_commit_map` records those in `.run/public_rewrite/unchanged_commits.txt`,
`absent_scan` does not count their prefixes as old hashes, and `probe_github.sh` skips them (they legitimately still
resolve on GitHub). Measured trial #1: filter 274 s, verify 385 s, absent_scan 346 s over 16.2 GB of text.

## 7. C6 — adoption in `~/bfm-decomp` (Claude; NO gc yet)

```bash
git fetch .run/public_rewrite/repo.git +refs/heads/main:refs/heads/main-rewritten
git diff --stat main main-rewritten        # ONLY text files (≈93) and no purge path
git reset --hard main-rewritten            # on main; the purged paths are untracked+ignored since C3 → they stay on disk
git status --porcelain                     # empty
git branch -D main-rewritten; git stash drop (each); git tag -d S76-pre-scrub-backup; git update-ref -d refs/original/... (if any)
```
`git ls-files | wc -l` equals the clone's tree count. No `gc` yet: `origin/main` still pins the old lineage until Drew
pushes, and the old objects are the local safety net until C9's counts pass.

## 8. C7 — commit map + tip resolution (Claude)

`git config user.email 50529377+Druthulu@users.noreply.github.com` (the noreply identity, before the tip commit).
`build_commit_map.py` → `docs/commit-map.tsv`; `resolve_tokens.py`; checks: `git grep -c 'commit:[0-9]' HEAD` = 0; the
orphan residue listed in the commit message; every inserted 9-char hash resolves uniquely; `absent_scan.py --tree HEAD`
= 0. Commit: `docs(phase-33): commit-map + citations resolved to the rewritten history`.

## 9. C8 — R22 on the adopted tree (Claude, ≈15 min here)

`tools/verify_contract.sh` (the A5 script) → `.run/P33/verify/` refreshed; `check-all: 218 passed, 0 failed of 218`;
report still 100.00 / 100.0 / 100.0. Commit the refreshed evidence (a content-preserving rewrite changed no tracked
byte — this run proves it).

## 10. C9 — final gate, force-push, gc

**Claude:** `gate_scan.py --refs main --worktree` → PASS.
**Drew:**
```bash
git ls-remote --tags origin                         # is S76-pre-scrub-backup on origin?
git push --force origin main
git push origin :refs/tags/S76-pre-scrub-backup     # if it was
git fetch --prune origin && git rev-parse origin/main main    # equal
```
**Claude, after Drew's word — measured S87:** (1) `git remote remove archive` (its remote-tracking ref pins the old
lineage; the mirror push is done); (2) **`git worktree list` — every linked worktree's HEAD counts as REACHABLE**: S87 found
12 stale campaign worktrees (`.run/S74/wt_*`, `.run/pgate/wt*`, `.run/S69_fable3/…`, `~/bfm-verify`) at old commits — 12 GB
of old-history checkouts, each holding the SDK/EXE/Ghidra on disk — `git worktree remove --force <path>` each, then `git
worktree prune` (`rev-list --all` went 8,146 → 7,763 after the remote, → 4,034 only after the worktrees); (3) `git reflog
expire --expire=now --all && rm -f .git/objects/info/commit-graph && git -c pack.threads=16 repack -adf --window=250
--depth=50 && git prune --expire=now && git commit-graph write --reachable` (a stale commit-graph names pruned commits and
makes `fsck` fail; 163 s). Checks: `git rev-list --all --count` == `git rev-list --count main` (4,034), objects in store ==
reachable (176,056), `git fsck` clean, `gate_scan.py --all --worktree` PASS, `absent_scan.py --repo ~/bfm-decomp` PASS
(≈7 min), `.git` size (S87: one 80 MB pack, `.git` 93 MB, from 1.5 GB). Then the probe baseline (`probe_github.sh`): every
sampled old hash still ALIVE is expected until the Support purge — that count (S87: 31 of 33) is what the ticket asks
GitHub to make zero.

## 11. C10 — the Support purge, the probe, the flip (Drew; decision Max)

**The ticket** (GitHub Support → "Remove data from a repository" / force-push cleanup), text:

> Repository: `Druthulu/BFM-decomp` (private, no forks, no pull requests from forks). I force-pushed a rewritten history
> that removes proprietary game binaries (a PlayStation executable, memory dumps and a vendor SDK) and personal session
> links from every commit. Please garbage-collect the unreachable objects and purge cached views (commit pages, raw
> blob URLs, API lookups by SHA) so that the old commit SHAs no longer resolve. The repository will be made public only
> after that. Thank you.

**The probe** (`tools/public_rewrite/probe_github.sh`, needs `gh auth login` in Drew's shell): for 30 sampled full old
hashes + the pruned commit + the old tag tip: `gh api repos/Druthulu/BFM-decomp/commits/<sha>` must return 404 and
`git fetch origin <sha>` must fail; positive control: the current `main` sha must succeed. After the flip, also probe
7-char prefixes unauthenticated at `github.com/Druthulu/BFM-decomp/commit/<7>`. While ANY probe returns 200: wait and
re-run daily. **Fallback** if Support stalls: delete the repository and recreate it under the same name, push the same
rewritten history (nothing else exists to lose — the archive repo and the bundle hold the old history).

**The flip:** Settings → General → Danger Zone → Change visibility → Public — ONLY after the probe exits 0 and Blocks D
(README, LICENSE, NOTICE, THIRD_PARTY, badges), E and F have landed on the still-private repo. Then D3's outward actions
(frogress slug, decomp.dev registration), E1 (the decomp.me preset), E2 (the Archipelago message), F3 (the wiki push).

## 12. C11 — aftercare

- **Every other clone of the old history** (the Windows tree, any other machine): `git fetch origin && git reset --hard
  origin/main && git reflog expire --expire=now --all && git gc --prune=now` — or re-clone. **Never `git pull`** (an
  8,000-commit merge of two unrelated lineages).
- `git remote remove archive` — done at C9 (it pinned the old lineage); never re-add it to the working repo.
- `.run/` (38 GB) → prune regenerables; `.run/public_rewrite/` (old hashes, the mailmap, the bundle) → keep until the
  probe has passed, then delete the clone and the dictionary; keep the bundle off-machine if wanted.
- Docs: `phase-ends/DIGEST.md` §1 (H1 in force again; R1/R20 historical), `docs/decision-log.md` (R31), SETUP's posture
  section (D4), `CLAUDE.md` (the `git clean -x` guard — in place since C3).

## 13. Risk register (condensed)

| Risk | Guard |
|---|---|
| A new hash written into a historical doc (changes every descendant hash) | tokens in history, real hashes only in the tip commit (fixed-point rule) |
| `git clean -x` after C3 deletes the RE database | CLAUDE.md fail-safe line; the bundle; the archive repo; the text export `config/ghidra/` + `ghidra_rebuild.sh --proof` |
| GitHub keeps serving force-pushed-away objects | the Support purge + the probe gate; the earlier S76 pre-scrub lineage sits unreachable on GitHub too and is covered by the same purge |
| A fork/import-created archive shares the object store | the archive is created EMPTY and receives a `--mirror` push |
| A scrub false positive (a binary SHA1 abbreviation coinciding with a commit prefix; expected < 1 over 44k tokens) | the content-hash exclusion set; ambiguous prefixes become `commit:amb-N`, never a wrong hash |
| An old clone `git pull`s the new history | the C11 reset recipe; announced before the force-push |
| Disk (13 GB free) / time | clone 0.6 + rewrite 0.2 + bundle 0.6 GB; rewrite 10–30 min; C8 ≈15 min |
| The mailmap is cosmetic unless the 3 tracked files mentioning the addresses are also replaced | they are (the blob callback) — and `absent_scan.py` asserts 0 occurrences everywhere |

## 14. Rollback

- **Before C9's force-push:** nothing on GitHub has changed; `git reset --hard origin/main` (or restore from the bundle:
  `git clone .run/public_rewrite/pre-rewrite.bundle`) returns the clone to the old history.
- **After the force-push:** the archive repo and the bundle hold the complete old history; `git push --mirror` from the
  archive into `BFM-decomp` restores it (it would then need the Support purge again). Old objects on GitHub are
  unreachable, not gone, until the purge — which is why the flip waits for the probe.
