### P33 C1 (S87, 2026-09-07) — the history-rewrite tooling, measured before the irreversible run
- **Design points.** The scrub replaces a hex token only when the WHOLE token is a prefix (≥ 7) of an old commit hash —
  so a 16-char sig hash can never be mistaken for a commit; only 7–8-char tokens carry any false-positive risk (≈1.6e-5
  per 7-char token) and the sample prints every 7-char replacement in context to be READ (R63). Tokens that are also
  prefixes of a cited CONTENT hash (1,480: the manifest, `check.*.sha`, the dumps, the sha256 checksum files, the redump
  CRC32) are excluded — measured 0 collisions. `rom_blob_ids.txt` is content/signature hits ∪ every blob that ever sat
  under a purge path, so `--strip-blobs-with-ids` kills a renamed copy that a path rule would miss. Bare session UUIDs in
  checkpoint prose (68 at HEAD) are NOT scrubbed (out of scope; no `claude.ai` URL exists in any HEAD blob) — reported
  as INFO by `absent_scan`. The mailmap and the dictionary are scratch: no personal address and no old hash is a
  literal in the package.
- **Measured (S87):** dictionary 4,420 commit objects (4,030 main, 339 twins, 51 orphans), 150,280 prefixes, **0
  ambiguous, 0 content-hash collisions**, 2 personal identities → noreply, 4 s. Sample over HEAD: 397 MB of text in
  7.9 s (50 MB/s), 1,238 replacements in 98 files, 731 distinct tokens (7-char 186 · 8-char 326 · 9-char 721 · 40-char
  5), 6 address replacements; **git's own lookup resolves exactly the same 731 tokens** (only-git 0, only-ours 0).
  `gate_scan --all --expect-fail`: 112,390 reachable blobs / 16.79 GB in 2 m 25 s; every purge rule named (ghidra/ 42
  paths ever, tools/psyq/ 190, dumps 28, archive 3, zips 2, brave.exe 1, the EXE 1+1), 0 stray content offenders, 52
  content/signature ids + 269 blobs ever under a purge path. `absent_scan` on the current repo → FAIL with 82,362
  offenders in 7 m 24 s (its positive control). `scrub --test` 12/12.
- **Trial rewrite #1 (S87, on a scratch bare clone — the reason a trial exists):** filter 274 s (72,500 hash replacements
  over every historical blob version, 60 trailers, 81 address replacements, 192 binary blobs untouched); the purge is
  real (archive/ghidra/dump blobs absent from the store; 0 purge paths reachable) but it found TWO defects that would have
  corrupted the real run: (1) the EMPTY blob was in `rom_blob_ids.txt` (an empty file once sat under a purge path) and
  `--strip-blobs-with-ids` dropped every "file emptied" change in history — 7 files silently kept their previous content
  and a restore commit became empty and was pruned (a second zero row); fixed: a blob shared with a non-purge path is
  never stripped by id (content/signature hits always are), and `verify_rewrite` now asserts no purge path survives and
  that the pruned set equals the derived purge-only set; (2) a commit the rewrite leaves byte-identical keeps its hash
  (the noreply-authored "Initial commit") and tripped the map's old-hash assertion — unchanged commits are recorded and
  exempted in the map, `absent_scan` and the probe. Also: the post-rewrite `gate_scan` must accept 0 blobs under purge
  paths (the guard now fires only when path offenders exist), and filter-repo's own gc leaves a ≈500 MB pack (re-deltaing
  16 GB of scrubbed text) — the purged binaries are gone regardless; C9 repacks aggressively.
- **Gotchas:** `git log --raw` abbreviates blob ids — `--no-abbrev` or the id filter drops everything (caught by the
  count "0 ever under a purge path"; the function refuses that result when path offenders exist, R43). git-filter-repo gc's the OLD objects
  out of the clone after the run, so `verify_rewrite` reads the old side from the working repo (`--old`) and the new
  side from the clone (`--new`). The clone stops being a "fresh clone" once the tag is deleted → `--force` is passed by
  `run_filter.py` (the only deviation from filter-repo's defaults). `--prune-empty auto`, never `always`.

