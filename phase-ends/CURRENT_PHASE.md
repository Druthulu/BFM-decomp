# CURRENT_PHASE — Phase 33: 100% verification + the public flip + Gen2 exit

> **Gate 1 approved 2026-09-06 (Drew, plan mode, Max, Fable 5.1).** Rules **R65–R73 ratified at gate 1** (binding; full text
> in `phase-ends/DIGEST.md` §3). The approved plan is reproduced VERBATIM at the end of this file (§"Approved plan") — its
> `~/.claude/plans/` copy is not part of the repo. Roadmap: `docs/roadmap-to-100.md` v2 §3 P33 (all six items, Drew's
> "everything as written"); `docs/gen2-roadmap.md` Phase 14's two-repo model is SUPERSEDED by the in-place flip.
> **Baseline HEAD at open: `commit:4011`** (the Phase-32 CLOSE commit; tree clean apart from the R23 `ghidra/` churn).

## Milestone (gate 2)
1. `.run/P33/verify/SUMMARY.md`: every step EXIT=0 (218/218 clean fleet; `sdk-dual` both legs; oracles green incl. `0 PAD-TAIL`;
   disc residue 0; report 100.00 / 100.0 / 100.0 with `INCLUDE_ASM 0`, backlog 0) — and the C8 re-run on the adopted tree.
2. `gh api repos/Druthulu/BFM-decomp --jq .private` → `false`; `tools/public_rewrite/probe_github.sh` exit 0 (old hashes 404);
   root `LICENSE`, `src/NOTICE.md`, `THIRD_PARTY.md`, the rewritten README (badges, Special thanks, the ProjectArchitect link);
   `.github/workflows/no-rom.yml` green on the public repo; the fresh-clone criterion met with the disc.
3. Every deliverable file present (verification.md, commit-map.tsv, config/ghidra/*.jsonl + ROSTER.md, dumps/CHECKSUMS.sha1,
   decompme-preset.md, outreach/archipelago.md, gcc-2.7.2-map/README.md, tools/xsig/, the permuter PR branch +
   permuter-ils.md, matching-drafter-pipeline.md, story.md + timeline, retrospective.md, docs/wiki/ + how-to-ai-decomp/,
   gen3-handoff.md); outward actions done by Drew or explicitly recorded as pending (P9 — never claimed).
4. `PhaseEnd_Phase33.md` v2.0.0 + DIGEST append + `v2.0.0` tag pushed.

## Effort / model (R7/R26/R27 — every transition is PROMPTED, never assumed)
- **Max** is the session default. Max-mandatory tasks: A3 (link recipe), B1 (build input), B5 (Ghidra export design),
  B9/C3 (P5c-class), C1 design, C7 design, C10 decision, D1/D2 wording, E5, E6, F1 narrative, F2, F3, G1, G2 (Tier 1 —
  prompt and WAIT for gate 2). Everything else is xHigh-class execution — drop only for faster turns.
- **No Ultracode / Workflow** in this phase: no breadth stretch warrants it. Agents only for isolated research (read-only).
- **Drew-only actions (R6):** every `git push`, the archive repo creation + mirror push, the force-push + remote tag
  deletion, the GitHub Support ticket, the visibility flip, the wiki push, the decomp.me preset save, the Archipelago
  message, the frogress key / decomp.dev registration, the permuter issue/PR, the `v2.0.0` tag push.

## Owner decisions (binding; the full list with rationale is in the Approved plan §"Owner decisions")
1. Scope = all six roadmap items. 2. Flip IN PLACE with the full rewritten history (every commit/date/message kept; hashes
change; `commit:1712` drops as empty). 3+11. Purge set: the EXE (both historical paths), `dumps/*.bin`, `ghidra/`,
`tools/psyq/`, `session archive/`, `tools/ghidra-ext/*.zip`, `tools/brave-CUE/brave.exe`; drop the `S76-pre-scrub-backup`
tag. 4. In-history hash scrub → `commit:NNNN` tokens + `docs/commit-map.tsv` + a tip resolution commit; the flip is gated
on old hashes returning 404. 5. Everything else stays public (PhaseEnds AND logs, CLAUDE.md, PROJECT_CONTEXT.md, decision
log, accelerators, campaign tooling); README links https://github.com/Druthulu/ProjectArchitect and carries a Special-thanks
section. 6. License split: AGPL-3.0 for tools/ + docs/ (brave-CUE GPL-3.0, submodules theirs); `src/NOTICE.md` no license
asserted. 7. R65–R73 ratified. 8. A project GitHub wiki authored in `docs/wiki/` + `docs/how-to-ai-decomp/`, synced by
script. 9. `--mailmap` both Gmail identities → `Drew T <50529377+Druthulu@users.noreply.github.com>`. 10. Archive repo
`Druthulu/BFM-decomp-archive` (private, created EMPTY, receives the unrewritten history before the rewrite).
Defaults (from the rewrite design's measurements): strip all 60 remaining `Claude-Session:` trailer lines; literal-replace
the Gmail strings in the 3 tracked files that mention them; drop `refs/stash` + `refs/original/` after the archive push;
R20's new home = the Ghidra text export (`config/ghidra/*.jsonl`) + `ghidra_rebuild.sh --proof`, the archive as the
one-time snapshot, `CLAUDE.md` gains "never `git clean -x`" (R20 amendment proposed at the PhaseEnd).

## Tasks (strict order; one commit per task after this file is updated; harness task list = the same 41 items, R28)
- [x] **A1** Governance commit (R65–R73 in DIGEST §3; this file; the harness list) — xHigh — `commit:4012`
- [x] **A2** Reporting-instrument fixes (pad-tail literal → derived; backlog LINKED-aware prune; `sig-main` build-derived +
      `progress.py` loud-fail) — xHigh, R39 controls — see Log 2026-09-06 A2
- [x] **A3** `NO_SDK` knob + `make sdk-dual` (+ tools-health wiring, `[skip]` without SDK dirs) — Max — see Log 2026-09-06 A3
- [ ] **A4** `tools/family_hseq.py` regen — Low
- [ ] **B1** `make disc-extract` (extract.py `--expect-manifest` / `--allow-missing-audio`; check-env; `.gitignore`
      re-tightened; the 4 splat preset headers tracked; `clean` fixed) — Max
- [ ] **B2** 34 absolute includes → `../shared/` + portable-include audit + 15-binary re-gate — xHigh
- [ ] **B3** `tools/bootstrap.sh` / `make bootstrap` + check-env extensions + fresh-clone proof 218/218 — xHigh
- [ ] **B4** `tools/fetch_psyq.sh` + CHECKSUMS rows (20 lib40 LIBs, psyq-obj-parser) BEFORE `tools/psyq/` leaves git — xHigh
- [ ] **B5** Ghidra regenerability (ExportAnnotations/ImportAnnotations/ghidra_rebuild.sh `--proof` on SLUS_007.26 +
      resident; roster; ExportSymbols R15 fix; path hardcodes; hooks) — Max, MCP stopped
- [ ] **B6** `dumps/CHECKSUMS.sha1` + INDEX.md rewrite + memory-map Source-index row — Low/xHigh
- [ ] **B7** No-ROM CI (`no-rom.yml`, `audit_public.py`, `compile_only.py`) — xHigh
- [ ] **B8** SETUP.md rows/sections (R21) + `docs/verification.md` — xHigh
- [ ] **A5** THE RECORDED RUN (`tools/verify_contract.sh` → `.run/P33/verify/`, SUMMARY all EXIT=0) — run Low, read Max
- [ ] **B9/C3** The preparatory commit (`git rm --cached` purge set; psyq CHECKSUMS moved; zip sha256s; runbook;
      decision-log entry) — Max (P5c-class)
- [ ] **C1** filter-repo 2.47.0 + `tools/public_rewrite/` — design Max, execution xHigh
- [ ] **C2** Negative control + dictionary + sample — xHigh
- [ ] **C4** Bundle + Drew's archive mirror push + bare clone + the rewrite — xHigh
- [ ] **C5** Verification suite on the rewritten clone — xHigh
- [ ] **C6** Adoption in `~/bfm-decomp` (no gc yet) — xHigh
- [ ] **C7** `docs/commit-map.tsv` + tip resolution commit — design Max, run xHigh
- [ ] **C8** R22 clean rebuild on the adopted tree — xHigh
- [ ] **C9** Final gate + Drew's force-push + local gc — xHigh
- [ ] **C10** Support purge → probe gate → FLIP (Drew) — decision Max
- [ ] **D1** README rewrite — Max
- [ ] **D2** LICENSE + `src/NOTICE.md` + `THIRD_PARTY.md` — Max wording
- [ ] **D3** Progress publishing (progress.json, badges, frogress_upload, objdiff_report + progress.yml) — xHigh
- [ ] **D4** SETUP.md public-clean pass — xHigh
- [ ] **D5** Governing-docs consistency pass + `tools/doc_links.py` — xHigh
- [ ] **F1** timeline.py + story — xHigh tool / Max narrative
- [ ] **F2** retrospective — Max
- [ ] **F3** wiki + how-to-ai-decomp + `wiki_sync.sh` — Max
- [ ] **E3** gcc-2.7.2 map README + `gccmap_cites.py` — xHigh
- [ ] **E4** xsig packaging — xHigh
- [ ] **E5** permuter upstream PR branch — Max
- [ ] **E6** drafter write-up — Max
- [ ] **E1** decomp.me preset (after the flip) — xHigh
- [ ] **E2** Archipelago outreach (after the flip) — xHigh
- [ ] **C11** Aftercare (other clones, archive remote removed, `.run/` pruned, DIGEST/decision-log) — xHigh
- [ ] **G1** `docs/gen3-handoff.md` — Max
- [ ] **G2** PhaseEnd v2.0.0 + DIGEST + archive this file + tag — Max, Tier 1, WAIT for gate 2

Mid-phase rules check after every 4 completed tasks (P6). Commit banked artifacts immediately (R42); count from the SOURCE.

## Log
- **2026-09-06 (S86, session bd19e14a, Max, Fable 5.1) — gate 1.** Session-start protocol (R64 digest); the history audit
  (every blob on every ref; the Ghidra DB proven to embed the EXE bytes under the page XOR mask; 28/28 RAM dumps carry the
  EXE's code; no secrets in tree, history diffs or the 1.27 GB transcript archive); Drew's decisions 1–11 (above); three
  read-only exploration agents + three design agents; the plan approved via plan mode. No repo change before A1.
- **2026-09-06 (S86) — A1** `commit:4012`: R65–R73 appended to DIGEST §3; this file opened with the plan verbatim; 41 harness tasks.
- **2026-09-06 (S86) — A2 (reporting instruments).** `make sig-main` REWRITTEN: `tools/main_seed_ends.py` derives main's
  game-code function boundaries from the build (link-map `.text` sections × each object's `nm` symbols; tiling asserted) and
  `sig_image` hashes the original EXE bytes at them → `.run/sig.main.jsonl` (809 fns / 45,150 ins); wired into `tools-health`
  and `report BINARY=main`; `progress.py` prefers it, falls back to the legacy Ghidra sig, and EXITS 1 with no sig (control:
  both hidden → rc=1 + the message); the digest's oracle clause is derived live (`main_oracle_line`: "0 phantom, 0 truncated,
  0 pad-tail"); `backlog.linked_closed` retires main addresses inside LINKED ranges (controls 4/4; `backlog prune: 1 rows ->
  0`; `docs/backlog.md` 0 open); `dup_report` main sig → `.run/sig.main.jsonl`. **Measured correction (R14/R41):** the derived
  sig tiles the 15 game-code objects' text EXACTLY (45,150 words, no overlaps, never shorter than Ghidra's), while the Ghidra
  sig covered 41,522 words and left **3,628 words of real game code owned by no function** (switch tails after unresolved
  jump tables, 52 two-to-four-ins thunks, and `SaveLoadRoutine` = the `case 0:` body inside `func_8002b0b4`) — so **MAIN
  game-code weighted is 45,150 / 45,150**, not 41,534 (P31 S79's +22 was one instance of this class); fleet instr
  13,488,497 → **13,492,113**, distinct 5,816,589 → **5,820,205**, all still 100%. `make report BINARY=main` EXIT=0
  (`.run/P33/a2_report.log`: lint OK, dedup-check 2220/0); `make audit-digest` OK; `docs/duplicates*.md` regenerated
  (main's table now game-code-only). SETUP §6.8 + a P33 A2 section (R21).
- **2026-09-06 (S86) — A3 (the with/without-SDK dual).** Makefile: `NO_SDK ?=` knob — under `NO_SDK=1` the eleven
  `psyq_integrate` rewrites are skipped (nested `ifeq`) AND the `-T` externals fragments are not collected (a stale
  `build/psyq/*_externals.ld` from a WITH build must not leak into the WITHOUT link); `sdk-dual` target (refuses unless all 11
  SDK object dirs exist; leg 1 WITH → extract → `rm -rf build/psyq` → leg 2 `NO_SDK=1` → extract → leg 3 WITH restore; map
  assertions each leg; both legs against `config/check.us.sha`); wired into `tools-health` after `sig-main` with a `[skip]`
  when the SDK dirs are absent; `.PHONY` += `sig-main sdk-dual`. **Run:** `make -j$(nproc) sdk-dual` → `sdk-dual: OK — main
  143dbb89… byte-identical WITH and WITHOUT the PsyQ objects`, EXIT=0, 28 s wall (`.run/P33/a3_sdk_dual.log`); maps
  `.run/P33/verify/main_with_sdk.map` (1,288 `build/psyq/` entries, 0 `libcd1` stub) and `main_no_sdk.map` (0 / 12); the live
  tree is back in the WITH state (map has 1,288 psyq entries; `build/us/SLUS_007.26` sha == check.us.sha). Control for A2's
  tool: `main_seed_ends.py` on both maps → identical seed files (the NO-SDK map exercises the LINKED-subseg skip: 70 objects
  skipped by name, vs 268 `build/psyq/` objects by path). Dry-run controls: `make -n check BINARY=main NO_SDK=1` shows 0
  `psyq_integrate` lines and `if [ -z "1" ]` around the externals. SETUP: P33 A3 section (R21).

## 🛑 SESSION CHECKPOINT — A1 ✓ A2 ✓ A3 ✓; NEXT = A4 (family_hseq regen, Low) then the P6 rules check, then B1 (Max) (2026-09-06, written by session bd19e14a "S86"; SUPERSEDES the earlier blocks)

### 0. How to use this block
You are a FRESH SESSION that has read `PROJECT_CONTEXT.md`, `phase-ends/DIGEST.md`, `PhaseEnd_Phase30/31/32.md` and this file,
and nothing else (R64). Replay this block verbatim, state phase / done / NEXT / effort, list the rules from the digest
(R1–R73), then WAIT for Drew. **NEXT = A4** (`.venv/bin/python tools/family_hseq.py`, Low; then the P6 mid-phase rules
check — 4 tasks done — then **B1**, Max). If `git log -1 --format=%s` does not start with `feat(phase-33): A3`, A3's commit
did not land: re-run `make -j$(nproc) sdk-dual` (28 s) and check `.run/P33/a3_sdk_dual.log` ends `sdk-dual: OK` before committing.

### 1. Where we are
**Phase 33 — 100% verification + the public flip + Gen2 exit.** Gate 1 approved 2026-09-06 (plan mode, Max). R65–R73 ratified at
gate 1 (DIGEST §3). **Done: A1 (`commit:4012`), A2 (`commit:4013` — the corrected main denominator 45,150 is now the published
number; `.run/sig.main.jsonl` is the sig main is weighed by; `tools/main_seed_ends.py` is new), A3 (the `NO_SDK` knob +
`make sdk-dual`, proven 28 s: both legs `143dbb89…`).** The approved plan is VERBATIM
at the end of this file — read its Blocks A–G for every task's files, commands and verification; the "Execution order and
why" section is the sequence; the "Honest scale" table is the budget (≈17–21 sessions; the flip precedes the writing so later
items can be cut). Harness tasks: #1 A1 done, #2 A2 done, #3 A3 next … #41 G2.

### 2. Facts measured this session that every task depends on (do not re-derive; verify if in doubt, R14)
- **History:** `main` = 4,011 commits (HEAD `commit:4011`); `git rev-list --all` = 4,282 because the `S76-pre-scrub-backup` tag
  points at a PARALLEL 126-commit lineage (the Phase-31 S76 trailer scrub's pre-image; NOT an ancestor of main; it still
  carries 58 `Claude-Session:` URL trailers and WAS pushed to GitHub — it sits there as unreachable objects), plus
  `refs/original/refs/heads/main` (a filter-branch leftover) and 3 stashes; the object store holds 4,401 commit objects.
  main still carries 60 `Claude-Session:` trailer lines (20 URL-form in `commit:3901..commit:3920`, 40 bare-UUID). One
  pre-existing EMPTY commit on main: `commit:2782` (2026-08-25) — must survive (`--prune-empty auto`, never `always`).
  Exactly one commit touches only purge paths: `commit:1712` "session archive update" (2026-08-12).
- **Purge set in history:** the EXE at `extracted/SLUS_007.26` (added `commit:0005`, 2026-06-10) AND `extracted/retail/SLUS_007.26`
  (`commit:0017`), same blob; `dumps/*.bin` (28, `commit:0016`); `ghidra/` (15 commits since `commit:0057`; 41 unique blobs; 6 programs
  tracked: SLUS_007.26, sep8_SLUS_007.26, aug31_USA_DEMO.EXE, resident, ov_SC01_077, ov_SC06_018; 129 programs on disk, 1,015 MB);
  `tools/psyq/` (5 commits since `commit:0029`; 190 files at HEAD); `session archive/` (3 parts 101,711,872 / 101,711,872 /
  67,419,506 bytes — the only blobs > 50 MiB); `tools/ghidra-ext/*.zip` (sha256 GhidrAssistMCP_2.8.0.zip
  `983e2add88d70552596dc3160c1ece52ca6ba8ac006c6c61446a780696815dc1`, ghidra_psx_ldr_2026.06.04.zip
  `dc57cf1ad126c717f69be63f777d747c9cc0af3b2f833af83eeeac644f8e7c11` — NOT recorded anywhere yet); `tools/brave-CUE/brave.exe`
  (`fdc9f48627e8294105350b36e0a857fe878c027221d9e7e28fedb7b219f036d9`). Never committed: the disc, asm/, assets/, expected/, build/.
- **Citations:** 711 hex tokens at HEAD resolve to commits (699 on main: 408×9-char, 181×8, 110×7; 12 off-main, 10 of them in
  `phase-ends/logs/Phase31.md`), across phase-ends 979 / docs 183 / tools 19 / .run 17 / src 4 occurrences; 160 distinct hashes
  inside commit messages. `\b[0-9a-f]{7,40}\b` is validated (0 word-embedded false hits; `func_800D128C`/`0x800d128c` do not
  match). Regex+dict measured 125 MB/s (HEAD's 395 MB text in 3.2 s, 1,202 prefix hits in 93 files).
- **Identities:** author == committer on every commit; `50529377+Druthulu@users.noreply.github.com` ×3,816, `50529377+Druthulu@users.noreply.github.com` ×162, noreply ×33;
  the two Gmail strings also appear as text in `phase-ends/PhaseEnd_Phase1.md`, `tools/gater_lane.py`, `tools/parallel_gate.py`;
  `git config user.email` is the primary Gmail (switch to the noreply before C7's tip commit).
- **Build facts:** `make extract` never calls `tools/bfm_extract/` (the Makefile's only disc reference is a comment at line 214);
  `extract.py:379-381` OVERWRITES the manifest on every run; the committed manifest (1,801 rows) includes the 3 `.DA` audio files
  from Tracks 2–4 (a Track-1-only dump gives 1,798 rows); `disks/` here holds Tracks 1–4 + cue. The 11 psyq_integrate calls are
  `if [ -d … ]`-guarded (Makefile:864-918); the LINKED count is parsed from the Makefile (`tools/progress.py:485-529`).
  `tools/progress.py:944-947` silently drops main when `.run/sig.SLUS_007.26.jsonl` (Ghidra-derived, gitignored) is absent;
  `tools/progress.py:1032` hardcodes "1 explained pad-tail". 34 absolute `#include "/home/musashi/bfm-decomp/src/shared/…"`
  lines in 19 `src/ov_*/…_jr_*.c` files across 15 binaries. 74 TUs contain `INCLUDE_ASM(` (70 LINKED-region stubs + 4 comment
  mentions), 47 use `INCLUDE_RODATA(`; `src/apicard1.c` IS built (fallback tiles). The 4 gitignored `include/*.inc` +
  `include_asm.h` are splat's generic presets (identical for every binary). `include/` tracks only `common.h` + `psyq/libcd.h`;
  `src/` has zero `#include <…>`. PsyQ 4.0 LIBs (`tools/psyq/lib40/`) have NO recorded public URL (they came from the DTL-S2002
  disc); the RTL 4.2 7z (archive.org) + psyq-obj-parser (decomp.me compilers release) are the only recorded downloads.
- **Verification state at open:** `.run/P32/t4e/tools_health.log` EXIT=0 with one `[warn]` (family_hseq.json missing 6 md_
  binaries) and `sig-main-oracle … 0 PAD-TAIL`; `r22_check.log` 218/218 EXIT=0 at 16:13:17 MDT; report 100.00/100.0/100.0;
  `docs/backlog.md` 1 stale row (`func_80062144` inside LINKED `apicard5`); `config/wave_exclude.txt` 0; verbatim 5 == 5.
- **Ghidra tooling:** export exists for symbols only (`ExportSymbols.java`, hardcoded output, blind overwrite — violates R15,
  wired to nothing); import path (`ApplySymbols.java` + `ghidra_apply_symbols.sh`) is proven; `ghidra_import.sh` /
  `ghidra_import_raw.sh` / `DefineFunctions.java` / `ImportPsyqGdt.java` exist; `prefetch_fleet.py` composes raw imports on demand;
  `.run/<prog>_funcs.txt` exists for 125 programs. Hardcodes: Makefile:165, all six `tools/ghidra_*.sh`, `DefineFunctions.java:21`,
  `ImportPsyqGdt.java:20`, `ghidra_mcp_verify.sh:19`, `.claude/settings.json:11,20`.
- **Environment:** the SessionStart hook's headless Ghidra MCP server is RUNNING (holds the project lock) — run
  `tools/ghidra_mcp_stop.sh` before any headless Ghidra step (B5); MCP tools are not connected in this session (connection
  failure, not absence). `gh` 2.45.0 on PATH but NOT authenticated (Drew's shell has credentials); `git filter-repo` NOT
  installed; **disk: 13 GB free on the 75 GB WSL cap (`.run/` = 38 GB, worktree 44 GB, `.git` 925 MB)**. No `/tmp` (R12).
  `~/bfm-decomp/.run/public_audit/` holds this session's blob inventory (`blobs.txt`, 22 MB; gitignored).
- **External facts (from the design agents' web research; treat as data, X2):** frogress projects are admin-created (slug + API
  key from the maintainers; POST `progress.deco.mp/data/{project}/{version}/`); decomp.dev reads a GitHub Actions artifact
  `<VERSION>_report` in the objdiff report format, registered at `decomp.dev/manage/new`; shields endpoint badges =
  `{"schemaVersion":1,"label","message","color"}`; decomp.me presets are created in-browser by any logged-in user (POST
  `/api/preset/`), compiler id `gcc2.7.2-psx`, maspsx args via `-Wa,--aspsx-version=2.56,--expand-div`; the BFM Archipelago world
  is `github.com/AegeusEvander/Brave-Fencer-Musashi-AP-World`; upstream decomp-permuter's `Scorer.__init__` gained
  `ign_branch_targets, objdump_command` after our pin and its MIPS symbol wildcard is `"." in field` (`scorer.py:66-67`).

### 3. NEXT — in order
0. **Preflight:** `git status --short | grep -v ghidra/` (empty) · `git log -1 --format='%h %s'` · `df -h ~` (≈13 GB free) ·
   `.venv/bin/python -c 'import splat'` · `ls build/us/SLUS_007.26.map` (main is built; `make check BINARY=main` if not).
1. **A4** `.venv/bin/python tools/family_hseq.py` (clears the audit-binaries `[warn] .run/family_hseq.json is missing 6
   onboarded overlay(s)`); confirm with `.venv/bin/python tools/audit_binaries.py 2>&1 | grep -c '\[warn\]'` → 0; commit
   "chore(phase-33): A4 …" (the json is gitignored — the commit is the Log line + this block). Then the **P6 rules check**
   (re-read CLAUDE.md's rules section; state "Rules check — re-read complete. Continuing with B1").
2. **B1** (Max) per the plan's Block B: `tools/bfm_extract/extract.py` gains `--expect-manifest` + `--allow-missing-audio`;
   `make disc-extract`; `extract`/`extract-all`/`check-env`/`help`/`clean` changes; `.gitignore` re-tightened; the 4 splat
   preset headers tracked. Gotchas: `extract.py:379-381` overwrites the manifest on every run (compare, never write); the
   committed manifest has 1,801 rows incl. 3 `.DA` audio files from Tracks 2–4; `disks/` here holds all 4 tracks + cue; the
   verification moves `extracted/` aside (`mv extracted .run/extracted.off`) — put it back if anything fails.
3. After every task: tick the box, add a Log line, refresh this checkpoint block (the 🛑 block is the ONLY in-phase context
   the next session inherits), commit.

### 4. Files this session touched
A1: `phase-ends/DIGEST.md`, `phase-ends/CURRENT_PHASE.md`. A2: `tools/main_seed_ends.py` (new), `Makefile` (`sig-main`
rewritten; `tools-health` + `report` wiring), `tools/progress.py` (sig selection + SystemExit + `main_oracle_line` + the MAIN
header line), `tools/backlog.py` (`linked_closed`), `tools/dup_report.py` (main sig path), `docs/SETUP.md` (§6.8 + P33 A2
section), regenerated `docs/progress.fleet.md`, `docs/duplicates.md`, `docs/duplicates.cross.md`, `docs/backlog.md`,
`.run/backlog.jsonl`. A3: `Makefile` (`NO_SDK`, `sdk-dual`, tools-health wiring, `.PHONY`), `docs/SETUP.md` (P33 A3 section).
Scratch: `.run/public_audit/` (the history inventory), `.run/P33/a2_report.log`, `.run/P33/a3_sdk_dual.log`,
`.run/P33/verify/main_{with_sdk,no_sdk}.map` (to be allowlisted by A5).
The plan file: `~/.claude/plans/max-effort-set-plan-twinkling-moonbeam.md` (copied below).

---

# Approved plan (gate 1, 2026-09-06) — VERBATIM copy of `~/.claude/plans/max-effort-set-plan-twinkling-moonbeam.md`

# Phase 33 — 100% Verification + the Public Flip + Gen2 Exit (plan, gate 1)

> Planning effort: **Max** (confirmed set). Governing inputs: `docs/roadmap-to-100.md` §3 P33 (lines 199–231),
> `docs/gen2-roadmap.md` Phase 14 (lines 150–166, the two-repo model — SUPERSEDED by the decisions below),
> `phase-ends/PhaseEnd_Phase32.md` "Roadmap delta", and this session's history audit + three exploration reports.

## Context

Phase 32 emptied the frontier: 218 binaries rebuild byte-identical from C from a clean tree (218/218, exits 0/0/0),
fleet 100.00 / 100.0 / 100.0, main 2,091 / 2,091 (789 REAL C · 1,256 LINKED Sony PsyQ objects · 3 verbatim asm; 5
verbatim fleet-wide). What remains is not matching: it is proving the contract once more as one recorded run, making
the repository publishable, publishing it with its full history, releasing the reusable tooling, writing the story /
retrospective / how-to, and declaring Gen2 EXIT at v2.0.0.

**The history audit (this session, every blob on every ref — `main` = 4,011 commits; `--all` = 4,282 because the
`S76-pre-scrub-backup` tag points at a PARALLEL 126-commit lineage left by the Phase-31 S76 trailer scrub, plus a
`refs/original/` filter-branch leftover and 3 stashes; the object store holds 4,401 commit objects; 112,253 unique
blobs, ≈16.8 GB content, `.git` 925 MB):** ROM-derived or proprietary content in history = `extracted/retail/SLUS_007.26` (the EXE, 413 KB,
1 commit), `dumps/*.bin` (28 × 2 MB RAM images, 1 commit), `ghidra/` (the Ghidra project — verified to embed the EXE's
bytes under Ghidra's page XOR mask; 174 MB across 15 commits; 6 programs tracked), `tools/psyq/` (Sony PsyQ SDK,
40 MB, 5 commits), `session archive/` (271 MB of session transcripts, 1 commit; ~260k lines of game disassembly inside).
Never committed: the disc, `asm/`, `assets/`, `expected/`, `build/`. No secrets in tree, history diffs or transcripts.
Tracked `.run/`, `docs/`, `phase-ends/` carry no original-game disassembly blocks (0 objdump-style lines; 6 illustrative
lines in the cookbook). 700 old commit hashes are cited in `docs/` + `phase-ends/` (1,167 backticked citations at HEAD).
Author identities: `50529377+Druthulu@users.noreply.github.com` ×3,816, `50529377+Druthulu@users.noreply.github.com` ×162, noreply ×33. One tag
`S76-pre-scrub-backup`. `git filter-repo` is not installed.

## Owner decisions (Drew, 2026-09-06 — binding for this plan)

1. **Scope = everything in roadmap v2 §3 P33** (all six items), not a trimmed subset.
2. **Flip IN PLACE with the full history**: `Druthulu/BFM-decomp` is force-pushed with a rewritten history (every
   commit, date, message and order preserved; hashes change; one all-purged commit `commit:1712` may drop as empty).
   No new repo. Before that, the current unrewritten history is pushed by Drew to a **new private archive repo**.
3. **Purge from all history:** the EXE, `dumps/*.bin`, `ghidra/`, `tools/psyq/`, `session archive/` — plus the two
   additions confirmed in decision 11 (`tools/ghidra-ext/*.zip`: 25.6 MB, one carries no license text, both
   re-downloadable with recorded sha256; `tools/brave-CUE/brave.exe`: a 7.6 KB compiled GPL tool binary).
4. **In-history hash scrub:** every old commit hash in every historical blob and commit message is replaced by an inert
   token; a token→new-hash map is committed; a tip commit resolves tokens at HEAD to the new hashes so current docs stay
   navigable. The visibility flip is gated on old hashes no longer resolving on GitHub (Support purge / GC).
5. **What stays public:** everything else, explicitly including `phase-ends/` (PhaseEnds AND `logs/`), `CLAUDE.md`,
   `PROJECT_CONTEXT.md`, `docs/decision-log.md`, `docs/accelerators.md`, the campaign tooling (no keys in tree). The
   README links **https://github.com/Druthulu/ProjectArchitect** as the guidance system used, and carries a
   **Special thanks** section (sotn-decomp style) crediting every tool/project we built on.
6. **License split:** `tools/` + `docs/` under AGPL-3.0 (`tools/brave-CUE/` keeps GPL-3.0; submodules keep theirs);
   `src/` ships a NOTICE — a reimplementation of copyrighted game code provided for study/preservation, no license
   asserted (sm64/oot convention).
7. **Rules R65–R73 ratified** (PhaseEnd_Phase32 candidates (i)–(ix)) — recorded in `phase-ends/DIGEST.md` §3 as the
   first governance commit of the phase.
8. **A GitHub wiki shaped to this project** (sotn-decomp precedent): Home · Build from your own disc · Toolchain setup ·
   Repository layout · The matching workflow (draft → gate → bank) · The dedup engine · Overlays & modules (the 218
   binaries, the disc map) · Ghidra rebuild from text · Verification & progress · Contributing / no-ROM policy · the
   "how to AI-decomp" chapters. Authored in-repo under `docs/wiki/` (versioned, CI-linted, covered by the rewrite) and
   pushed to `BFM-decomp.wiki.git` by a sync script (Drew pushes, R6).

9. **Author identity:** both Gmail identities are mapped to `Drew T <50529377+Druthulu@users.noreply.github.com>` in
   the same rewrite pass (`--mailmap`); names and dates untouched.
10. **Archive repo:** `Druthulu/BFM-decomp-archive` (private) receives the current unrewritten history (all refs + the
    tag) before the rewrite. Drew creates it empty and pushes (R6).
11. **Purge set is final:** the five confirmed path sets PLUS `tools/ghidra-ext/*.zip` and `tools/brave-CUE/brave.exe`;
    the `S76-pre-scrub-backup` tag is dropped from the public history (the archive keeps it).

## Task blocks (effort per task: **Max** = design / irreversible / synthesis; **xHigh** = mechanical execution)

**Defaults set by this plan from the rewrite design's measurements (change them at approval if you disagree):**
- The EXE is purged at BOTH historical paths (`extracted/SLUS_007.26`, then `extracted/retail/SLUS_007.26`) and by blob
  id, so no renamed copy survives.
- All 60 remaining `Claude-Session:` trailer lines in main's commit messages (the S76 scrub missed them) are stripped
  in the same pass; the Gmail addresses are also literal-replaced inside the 3 tracked files that mention them.
- `refs/stash` (3 Phase-26 WIP entries) and the `refs/original/` leftover are dropped locally after the archive push.
- The archive repo is created EMPTY (never a fork or import — those share GitHub's object store).
- **R20's new home after the flip:** the Ghidra text export (`config/ghidra/*.jsonl`, B5) becomes the tracked backup of
  the RE work and `tools/ghidra_rebuild.sh --proof` its check; the archive repo is the one-time snapshot of the
  binary DB, dumps, PsyQ and transcripts; `CLAUDE.md` gains "never `git clean -x`" (the purged paths become ignored,
  so `git clean -fdx` would delete the RE database). Proposed as an R20 amendment at PhaseEnd_Phase33.

### Block A — Tool fixes the contract run depends on, then THE recorded verification run
- **A1 Governance commit** (xHigh): `phase-ends/DIGEST.md` §3 gains R65–R73 in full text (from PhaseEnd_Phase32 "Rules
  Added"); `phase-ends/CURRENT_PHASE.md` created with the approved plan + the harness task list (R28).
- **A2 Reporting-instrument fixes** (xHigh; each with a known-true control, R39): `tools/progress.py:1032` — the
  fleet digest's "0 phantom, 0 truncated, 1 explained pad-tail" is a HARDCODED f-string literal; derive it from
  `corpus.audit('main')` at render time (print "(run make sig-main-oracle)" when the oracle sig is absent — never a
  stale literal). `tools/backlog.py prune` — an address inside a LINKED range counts as closed (derive the ranges from
  `progress._main_linked_ranges()`, R33) so the legacy `func_80062144` row (inside `apicard5`) retires honestly;
  control: a synthetic near-miss at a game-code address must survive. **R32 hole:** `tools/progress.py:944-947`
  silently drops main (`0/0`, "217 binaries") when the Ghidra-derived `.run/sig.SLUS_007.26.jsonl` is absent — a public
  clone has no Ghidra DB. Fix: `make sig-main` becomes ELF-seeded (`nm` T symbols in main's text range minus the LINKED
  ranges — the `sig-resident` recipe, Makefile:360-374; `tools/sig_image.py` writes the identical schema) and
  `progress.py` reads `sig.SLUS_007.26.jsonl` else `sig.main.jsonl` else **exits non-zero**; control: hide the Ghidra sig,
  `make sig-main && make report BINARY=main` must print `41534 / 41534` and 218 binaries.
- **A3 `NO_SDK` knob + `make sdk-dual`** (Max — touches the link recipe; a wrong knob is a false green): `NO_SDK=1`
  skips the 11 guarded `psyq_integrate.py` calls AND the `-T` externals fragments (Makefile:861-920); `sdk-dual`
  refuses to run unless every SDK ELF dir exists (R32 — never run one leg twice and call it a dual), runs
  `extract BINARY=main` between legs (psyq_integrate rewrites the `.ld` in place), asserts WITH map contains
  `build/psyq/libcd/` and NO-SDK map contains `build/src/libcd1.o` and no `build/psyq/`, both legs == `config/check.us.sha`.
  Added to `tools-health` after `sig-main-oracle`, `[skip]` with a message when no SDK dirs exist (a public clone's
  every check IS the WITHOUT leg). This turns the once-regressed hand-only fallback (`config/symbols.us.txt:248`,
  `docs/accelerators.md:654-656`) into a first-class assertion.
- **A4 `tools/family_hseq.py` regen** (Low): clears the `[warn] .run/family_hseq.json is missing 6 onboarded
  overlay(s)` line in the P32 tools-health log.
- **A5 THE RECORDED RUN** (Low to run, Max to read honestly; runs on the committed final tree AFTER Block B, since R22
  means the verified tree is the published tree): `tools/verify_contract.sh` → `.run/P33/verify/NN_<step>.log` (each
  ending `EXIT=<rc>` + timestamp, the P32 `r22_check.log` shape; aborts on the first non-zero EXIT, R53) + `SUMMARY.md`:
  00 `git rev-parse HEAD` + porcelain (only R23 ghidra churn) · 01 `make check-env` · 02 family_hseq · 03 `make clean &&
  make extract-all JOBS=16 && make check-all JOBS=16` (expect `217 extracted, 0 failed (+ main)` and `check-all: 218
  passed, 0 failed of 218`) · 04 `make sdk-dual` (+ both `.map` files kept) · 05 `make tools-health` (must contain
  `sig-main-oracle: … 0 PHANTOM, 0 TRUNCATED, 0 PAD-TAIL`, corpus(+resident) green, zero `[warn]`) · 06 `make
  audit-frontier` · 07 `make audit-disc` (needs the 4-track disc; residue 0) · 08 `make report` (three 100 lines,
  `INCLUDE_ASM stubs : 0`, backlog `Open near-misses: 0`) · 09 SUMMARY. `.gitignore` allowlists `.run/P33/verify/`
  (`*.log *.map *.md *.txt`) exactly like `.run/P32/t4e/`. The evidence is cited by `docs/verification.md` (a public
  "verify it yourself" page: the commands + expected last lines + this run's SUMMARY table) and by the PhaseEnd.

### Block B — The public build path and the regenerability of everything that leaves git
- **B1 `make disc-extract`** (Max — a build-input step; wrong = a green build on the wrong bytes): promotes
  `tools/bfm_extract/extract.py` into the Makefile. Facts that shape it: `extract.py:379-381` OVERWRITES the manifest
  on every run, so the wiring must COMPARE, never write; the committed `extracted/retail/manifest.jsonl` (1,801 rows)
  includes the 3 `.DA` audio files from Tracks 2–4, so the oracle needs the **4-track redump BIN/CUE** (a Track-1-only
  dump gives 1,798 rows). New flags: `--expect-manifest PATH` (compute, compare to the committed `manifest.sha1`, write
  nothing on match, print the first 20 differing rows and exit 1 on mismatch) and `--allow-missing-audio` (Track 2
  absent → compare minus the 3 `.DA` rows, print `PARTIAL: 1,798/1,798 code+data verified; 3 .DA unverified`; without
  the flag a partial dump FAILS, R43). Target: idempotent probe via `extract.py --verify` (≈5 s) → else require
  `disks/…(Track 1).bin` (exit 2 with the staging instruction) → `extract_exe.py --verify-disc` (redump SHA1
  `b44f0f0a…`/CRC32 `c238191b`; refuses a non-canonical dump) → `extract.py --expect-manifest` → `--verify`.
  `extract-all` runs it once serially first; `extract` runs it only when `$(EXE)` is missing; `check-env` step 6 → WARN
  "run make disc-extract" when the EXE is absent, plus `sha1(manifest.jsonl) == manifest.sha1`; `help` text refreshed.
  `.gitignore`: delete the `!/extracted/retail/SLUS_007.26` re-include; new `/dumps/*.bin`, `/ghidra/`, `/tools/psyq/`,
  `/session archive/`, `/tools/ghidra-ext/*.zip`; header rewritten (H1 in force). `make clean` stops deleting the four
  splat preset headers, which become TRACKED (`include/include_asm.h`, `macro.inc`, `labels.inc`, `gte_macros.inc` are
  generic splat presets, identical for every binary — the ROM-free input CI needs). Verification: `mv extracted
  .run/extracted.off && make disc-extract` → exit 0, `cmp` of the manifests, EXE sha1 `143dbb89…`; second run prints
  "up to date"; negative controls: `DISC_DIR=/nonexistent` → exit 2; a truncated Track-1 copy → `--verify-disc` FAIL
  with `git diff --exit-code extracted/retail/manifest.*` clean; the run time recorded in SETUP §4.4.
- **B2 Absolute includes** (xHigh): 34 lines in 19 `src/ov_*/…_jr_*.c` files across 15 binaries (30 `engine_core.h`, 4
  `engine_types.h`) → `sed 's|#include "/home/musashi/bfm-decomp/src/shared/|#include "../shared/|'` (the tree's own
  form, 3,978 uses; byte-neutral by construction — same header text — but still re-gated: `make extract BINARY=<b> &&
  make check BINARY=<b>` for each of the 15; the fleet R22 in A5 is the recorded proof). `tools/audit_text_sources.py`
  (already in tools-health) gains a portability class: absolute, angle-bracket, or outside-repo `#include`s are
  offenders; controls: 34 offenders before the sed, 0 after.
- **B3 `tools/bootstrap.sh` / `make bootstrap`** (xHigh): idempotent — apt presence check (prints the install line,
  no sudo) → venv + `requirements-python.txt` → `git submodule update --init` → `sha256sum --check
  tools/bin/CHECKSUMS.sha256` + untar each cc1 tarball into its own subdir → `make check-env`. `check-env` gains:
  submodule state, the 4 tracked headers, disc/extracted state. Verification = the "stranger with their own dump"
  criterion: `git clone --no-local` into `.run/P33/fresh/` → `tools/bootstrap.sh` (single WARN: run disc-extract) →
  disc symlinked in → `make disc-extract && make extract-all && make check-all` → 218/218.
- **B4 `tools/fetch_psyq.sh`** (xHigh; OPTIONAL enrichment, never required for byte-identity): what each LINKED region
  needs — `.run/obj40/{libcd,libetc,libgpu,libmcrd,libc2,libgte}` + `libgs_used` + `snd_used` from PsyQ **4.0** LIBs
  (`tools/psyq/lib40/`, sourced from the DTL-S2002 disc — **no public URL is recorded anywhere** → the script REFUSES
  and accepts `--from DIR`, naming the redump title); `.run/obj42/{apicard_used,libapi42,libpad421}` from the RTL 4.2 7z
  (archive.org, sha256 recorded) via `psyq_lib_split.py`; `psyq-obj-parser` from the decomp.me compilers release (sha256
  to be ADDED). `Psy-Q_46.zip`, `PSYQ_SDevTC_v4.5.zip`, `conv47/`, the 4.0 Win32 tools feed NO region. **Before
  `tools/psyq/` leaves git:** add sha256 rows for the 20 `lib40/*.LIB` and the `psyq-obj-parser` tarball to
  `tools/psyq/CHECKSUMS.sha256` (kept tracked) so a user-supplied copy is verifiable. The script ends with `make sdk-dual`.
- **B5 Ghidra regenerability** (Max; runs with the MCP STOPPED — the SessionStart hook's server holds the lock; the
  hook restarts it next session): `tools/ghidra_scripts/ExportAnnotations.java <out.jsonl> [symbols…]` (read-only;
  byte-stable JSON-Lines, fixed key order, sorted sections, `0x%08x` addresses; rows `program`, `block`, `archive`,
  `type` (only LOCAL-archive user types — the 2,599 psyq400 types re-import via `ImportPsyqGdt`), `func` (USER_DEFINED
  signature/params/locals/custom storage), `data`, `comment` ×5 kinds, `bookmark` (not `Analysis`), `equate`, `label`
  (USER_DEFINED, not already in the symbols files)); `ImportAnnotations.java <in.jsonl>` (idempotent compare-before-
  write, two-pass types for self-references via `DataTypeParser`, prints `BFMANN … failed=0`, refuses unknown row kinds
  / schema drift, R43); `tools/ghidra_rebuild.sh <program> [--proof|--into-live]` composing: stop MCP → import
  (`ghidra_import.sh` for PS-X EXEs incl. the two protos from `extracted/proto/`, `ghidra_import_raw.sh <blob> <vram>`
  for raw programs with blob/vram DERIVED from `config/overlays.mk`/`modules.mk`/the Makefile's resident block, R33) →
  `DefineFunctions` from the built ELF's `nm` T symbols → `ApplySymbols` in the yaml's `symbol_addrs_path` order →
  `ImportAnnotations` → `--proof`: re-export and `cmp` against `config/ghidra/<program>.jsonl` (exit 0 = regenerable) +
  an R9 read-only re-open. **Analysis-noise trap:** export a BASELINE from the rebuilt program BEFORE importing; every
  row present in the baseline is analysis-origin (PsyQ-signature plate comments, `Analysis` bookmarks) → tighten the
  filter until `cmp` passes; keep `.run/P33/ghidra/<prog>.baseline.diff`; negative control: mutate one field in a copy
  → the proof must FAIL. Roster: export ALL 129 on-disk programs once, keep in `config/ghidra/` only those with
  hand-authored rows (`config/ghidra/ROSTER.md` generated), proof REQUIRED on `SLUS_007.26` + `resident`, recommended
  on `ov_SC01_077`; protos exported (cheap RE preservation) but marked "rebuild needs the prototype disc". Same change:
  `ExportSymbols.java` R15 fix (output-path arg, refuses to overwrite, never `config/`), and the path hardcodes:
  Makefile:165 `GHIDRA_PROJ := $(or $(BFM_GHIDRA_PROJ),$(CURDIR)/ghidra)`, the six `tools/ghidra_*.sh` `PROJ_DIR`,
  `DefineFunctions.java:21`, `ImportPsyqGdt.java:20` (→ `Application.getInstallationDirectory()`),
  `ghidra_mcp_verify.sh:19` PROG arg; `.claude/settings.json` hooks → `$CLAUDE_PROJECT_DIR`-relative and the start
  script a silent no-op when Ghidra is not installed (a contributor's session must not try to launch Ghidra).
- **B6 Dumps** (Low; wording xHigh): `sha1sum dumps/ram_*.bin > dumps/CHECKSUMS.sha1` (28 rows, committed BEFORE the
  `.bin` leave git); `dumps/INDEX.md` rewritten (local-only from P33; hashes; re-capture recipe `tools/ram_probe.py
  snapshot <name>` → `.run/ram/`, with the honest caveat that a re-capture is a new state snapshot, never byte-identical
  to the original); `docs/memory-map.md` Source-index row for the corpus. Verify: `git ls-files dumps` = INDEX +
  CHECKSUMS; `sha1sum --check` 28/28.
- **B7 No-ROM CI** (xHigh): `.github/workflows/no-rom.yml`, pinned actions, `ubuntu-24.04`, python 3.12, submodules.
  Job `audits` (~1 min, ROM-free by measurement: `audit_text_sources.py`, `verbatim_check.py`, `cookbook_index.py
  --check`, `work_evidence.py --selftest`, `bfm_extract/test_lzss.py`, `lint_symbol_refs.py`, and the first-push gate
  reused as CI — `tools/audit_public.py`: no tracked file's SHA1 appears in `extracted/retail/manifest.jsonl` (the
  manifest IS the list of ROM-derived hashes, R33), none equals the EXE SHA1, none > 50 MB, none under the purged
  paths). Job `compile-only`: cc1 from the tracked tarballs + maspsx + `as` on every eligible TU via new
  `tools/compile_only.py` whose skip list is DERIVED (the 70 LINKED TUs from `progress._main_linked_segs_from_makefile()`
  + the 47 TUs with line-start `INCLUDE_ASM(`/`INCLUDE_RODATA(`; -O0 TUs from `corpus.o0_sources()`), coverage line
  `compiled N of M; skipped …` (R32); PR scope `main resident ov_SC01_077 md_MAIN_013` (sized to ≤10 min — time one
  TU first, each includes the 8.8 MB engine_core.h), `--all` on `workflow_dispatch` + weekly; `cdecl.py --audit --gcc`
  rides along. Excluded on purpose (need the ROM): audit-binaries, split_indicator, audit-digest, progress --audit,
  dedup check. The workflow header and README state that byte-identity is verified locally with the disc.
- **B8 `docs/SETUP.md` (R21) + `docs/verification.md`** (xHigh): §4.4 disc-extract, §4.6 bootstrap, §4.8 fetch_psyq,
  §6.3 the new targets, tooling rows for every new tool; `docs/verification.md` as in A5.
- **B9 The `git rm --cached` commit** (Max, P5c-class): after B4/B5/B6 are committed — `git rm --cached
  extracted/retail/SLUS_007.26 dumps/*.bin tools/brave-CUE/brave.exe tools/ghidra-ext/*.zip && git rm -r --cached
  ghidra tools/psyq "session archive"`; files stay on disk, now ignored by B1's `.gitignore`. A5's R22 logs remain
  valid (a `--cached` removal changes no tracked-content bytes — stated in `docs/verification.md`).

Ordering inside A+B: A1 → A2/A3/A4 → B1 → B2 → B3 → B4 → B5 (parallel with B1–B4 once the MCP is stopped) → B6 →
B7 → B8 → **A5 (the recorded run on the final tree)** → B9 → Block C.

### Block C — The history rewrite, the push, the purge gate, the flip
- **C1 Install + tooling** (design Max, execution xHigh): `.venv/bin/pip install git-filter-repo==2.47.0` (SETUP row,
  R21). New `tools/public_rewrite/`: `purge_set.txt` (the single source of truth, filter-repo `--paths-from-file`
  syntax), `gate_scan.py` (the first-push gate — scans the working tree AND every blob reachable from the given refs for
  purge-path prefixes, content SHA1s in the known-ROM set (EXE, redump Track-1, every `sha1` in
  `extracted/retail/manifest.jsonl`, every `config/check.*.sha`), byte signatures (`PS-X EXE` at 0; the 2,097,152-byte RAM
  image with the resident's first words at 0xCEDF8; the EXE entry code; PsyQ `LIB\x01`/`LNK\x02` magics), any blob
  > 50 MiB; `--expect-fail EXPECTED.txt` = the R39 NEGATIVE CONTROL, exit 0 only when the scan fails naming exactly the
  expected offender set; also emits `rom_blob_ids.txt`), `hash_dict.py` (all 4,401 commit hashes → ordinal by
  `git rev-list --reverse main`; off-main commits → the ordinal of their (tree, author-timestamp, subject) twin — measured
  126/126 for the tag lineage — else `orphan-NNN`; prefixes 7..40 = 149,634 entries; asserts 0 ambiguous prefixes and
  0 collisions with the known content-hash set), `scrub.py` (the ONE scrub function: `\b[0-9a-f]{7,40}\b` — validated
  at HEAD: 711 resolving citations, 0 word-embedded false hits, `func_800D128C`/`0x800d128c` do not match — replaced
  via dict lookup by the token **`commit:NNNN`** (non-hex inside the first 7 chars so it can never re-match; no
  Markdown/GitHub side effects; `git grep -c 'commit:[0-9]'` is 0 today); NUL-sniff binary skip; idempotent),
  `run_filter.py` (composes the filter-repo call, refuses to run outside a bare repo under `.run/public_rewrite/`,
  logs versions + wall time; `--sample` first, R37: must reproduce ≈1,202 hits / 93 files / ≈3 s over HEAD's 395 MB and
  the replaced-token set must equal the 711 citations that `git cat-file -e` resolves), `build_commit_map.py`
  (→ public `docs/commit-map.tsv`: `ordinal  new_hash  author_date  committer_date  subject`, no old hash anywhere —
  asserted by running scrub over its own output; private `.run/public_rewrite/old-to-new.tsv` for the probe only),
  `resolve_tokens.py` (at HEAD of the adopted checkout: `commit:NNNN` → the unique 9-char new abbreviation, asserted
  by `git cat-file --batch-check`; `--check` asserts zero resolvable tokens remain and lists the orphan residue),
  `verify_rewrite.py` (the pairwise proof, C5), `absent_scan.py` (every blob incl. binaries + every message → 0
  dictionary prefixes, 0 `Claude-Session:`, 0 Gmail strings), `probe_github.sh` (Drew's post-purge probe). All scratch
  under `.run/public_rewrite/` (never committed; it holds old hashes). Measured budget: regex+lookup 125 MB/s → ≈2.2
  CPU-min over 16.8 GB; the filter-repo stream dominates (10–30 min). Disk: 13 GB free → bare `--no-local` clone
  (≈0.6 GB) + bundle (≈0.6 GB), no working-tree copy.
- **C2 Negative control + dictionary + sample** (xHigh): `gate_scan.py --refs --all --worktree --expect-fail` on the
  CURRENT repo must FAIL naming exactly: the EXE at both paths, 28 dumps, all `ghidra/**` (41 blobs), all
  `tools/psyq/**` (190 files at HEAD), the 3 `session archive/*` parts (the only >50 MiB blobs), the 2 ghidra-ext zips,
  `brave.exe`; signature hits = EXE blob(s) + 28 RAM images. Then `hash_dict.py` (expected: 4,401 commits, 149,634
  prefixes, 126 twins, 0 ambiguous, 0 collisions) and `run_filter.py --sample`.
- **C3 Preparatory commit in `~/bfm-decomp`** (content Max, mechanics xHigh) = Block B's B9 plus: `git mv
  tools/psyq/CHECKSUMS.sha256 tools/psyq_CHECKSUMS.sha256` BEFORE the rm (B4's added rows go there; SETUP's three
  references follow); record the ghidra-ext zip sha256s in SETUP §2.3/§2.4 (`GhidrAssistMCP_2.8.0.zip`
  `983e2add…`, `ghidra_psx_ldr_2026.06.04.zip` `dc57cf1a…`); `docs/public-flip-runbook.md` + `tools/public_rewrite/`;
  a forward-only decision-log entry (R31). Checks: `git ls-files -- <purge paths>` empty; every purge path
  `git check-ignore -q`; the files still on disk; `make check-env` exit 0. Commit immediately (R42).
- **C4 Backups, then the rewrite** (xHigh; Drew pushes): `git bundle create .run/public_rewrite/pre-rewrite.bundle
  --all --reflog` + `git bundle verify`. **Drew:** create `Druthulu/BFM-decomp-archive` EMPTY + private, `git remote add
  archive …`, `git push --mirror archive`; check: `git for-each-ref` vs `git ls-remote archive` identical. Then
  `git clone --no-local --bare ~/bfm-decomp .run/public_rewrite/repo.git`; delete the tag in the clone; assert the clone
  holds only `refs/heads/main` at the prep commit, one pack, zero loose objects; `run_filter.py` = `git filter-repo
  --invert-paths --paths-from-file purge_set.txt --strip-blobs-with-ids rom_blob_ids.txt --blob-callback …
  --message-callback … --prune-empty auto --replace-refs delete-no-add --mailmap …` (never `--prune-empty always`:
  main has one pre-existing empty commit `commit:2782` that must survive; `delete-no-add` so no `refs/replace/<old>`
  names are minted). Checks: exit 0; commit-map has 4,012 rows (4,011 + prep) with exactly one mapped to zeros (the
  pruned archive upload); no `refs/replace`; one pack; size recorded (expect 150–250 MB).
- **C5 Verification suite on the rewritten clone** (xHigh; every check an exit code): `verify_rewrite.py` — for every
  (old,new) pair: names/emails (post-mailmap) and BOTH timestamps equal; `new.message == scrub(old.message)`; new
  parents = map(old parents) with the pruned commit spliced out; `git diff-tree -r --no-renames old new`: every `D` is a
  purge path or a ROM blob id, every `M` satisfies `hash-object(scrub(old_blob)) == new_blob`, any `A` fails; prints
  4,011 pairs checked. `gate_scan.py --refs --all` → PASS (the same tool that failed in C2). `absent_scan.py` → 0/0/0.
  `git rev-list --count main` = 4,011 and the `%at %ct` lists match with the pruned commit removed. The pre-existing
  empty commit's twin exists.
- **C6 Adoption in `~/bfm-decomp`** (xHigh): `git fetch .run/public_rewrite/repo.git +refs/heads/main:refs/heads/
  main-rewritten`; `git diff --stat main main-rewritten` lists ONLY text files (≈93) and no purge path; `git reset
  --hard main-rewritten` on `main` (the purged paths are untracked+ignored since C3, so they stay on disk); `git status
  --porcelain` empty; `git ls-files | wc -l` equals the clone's tree count; delete `main-rewritten`, `refs/original/…`,
  the tag, the stashes. NO gc yet (origin/main still pins the old lineage until Drew pushes).
- **C7 Commit map + tip resolution** (design Max, run xHigh): `git config user.email` → the noreply identity;
  `build_commit_map.py` → `docs/commit-map.tsv`; `resolve_tokens.py`; checks: `git grep -c 'commit:[0-9]' HEAD` = 0;
  the orphan residue (≥1: `tools/verify_worktree.py:214` cites a dropped TEMP commit) listed in the commit message;
  every inserted 9-char hash resolves uniquely; `absent_scan.py --tree HEAD` = 0. Commit `docs(phase-33): commit-map +
  citations resolved to the rewritten history`.
- **C8 R22 clean rebuild on the adopted tree** (xHigh, ~1 h): `make clean && make disc-extract && make extract-all &&
  make check-all` → 218/218, exit codes 0 (R53); `make report` still 100.00 / 100.0 / 100.0. (Content-preserving
  rewrite ⇒ A5's evidence still describes this tree; this run proves it.)
- **C9 Final gate + force-push + gc** (xHigh; Drew pushes): `gate_scan.py --refs main --worktree` PASS. **Drew:**
  `git push --force origin main`; `git push origin :refs/tags/S76-pre-scrub-backup` if the tag is on origin (`git
  ls-remote --tags origin`); `git fetch --prune origin`; `origin/main == main`. Then locally `git reflog expire
  --expire=now --all && git gc --prune=now`; checks: `git rev-list --all --count` = **4,012** (old main 4,011 + the prep
  commit − the pruned archive upload + the TIP commit; the script prints the expected number from the map),
  `gate_scan.py --refs --all` PASS, `absent_scan.py` PASS, `.git` size recorded (expect < 400 MB).
- **C10 Support purge → probe gate → the flip** (Drew; decision Max): open the GitHub Support ticket (text in the
  runbook: private repo, no forks, force-pushed to remove proprietary game binaries and personal session links; please
  GC unreachable objects and purge cached views; the repo goes public only after the old SHAs return 404). Probe:
  `tools/public_rewrite/probe_github.sh` — for 30 sampled full old hashes + the pruned commit + the old tag tip:
  `gh api repos/Druthulu/BFM-decomp/commits/<sha>` must 404 and `git fetch origin <sha>` must fail; positive control:
  the current `main` sha must succeed; after the flip also probe 7-char prefixes unauthenticated at
  `github.com/Druthulu/BFM-decomp/commit/<7>`. While any probe returns 200: wait and re-run daily; fallback if Support
  stalls = delete + recreate under the same name and push the same rewritten history (nothing else exists to lose).
  Flip = Settings → Change visibility → Public, only after the probe exits 0. During the wait: Blocks D, E, F land on
  the still-private repo.
- **C11 Aftercare** (xHigh): every other clone of the old history (the Windows tree, other machines) must `git fetch
  origin && git reset --hard origin/main && git reflog expire --expire=now --all && git gc --prune=now` or re-clone —
  never `git pull` (an 8,000-commit merge); `git remote remove archive` from the working repo (habit guard);
  `.run/` at 38 GB → prune regenerables (the WSL disk is capped at 75 GB, 13 GB free); PhaseEnd/DIGEST entries.

### Block D — Publishing surface (after the rewrite, during the GitHub-purge wait, BEFORE the visibility flip)
- **D1 README rewrite** (Max): what/why · the numbers table WITH denominators, generated (`tools/progress.py --readme`
  writes a `<!-- progress:begin/end -->` block from `docs/progress.json`; `make audit-digest` asserts it) · "what is
  not our C" (1,256 LINKED Sony objects; 5 PERMANENT verbatim bodies; the 74 `src/lib*.c`/`apicard*.c` INCLUDE_ASM
  fallback tiles for the linked regions) · build-from-your-own-disc in N commands (uses Block B's `make extract`) ·
  verification evidence (R22 log path, EXE SHA1 `143dbb89…`, redump Track-1 SHA1) · method (ProjectArchitect link,
  CLAUDE.md, phase-ends, decision-log, accelerators) · story/retrospective/wiki links · license split · contributing /
  no-ROM policy · **Special thanks** (sotn-decomp style): sotn-decomp (method precedent), splat/spimdisasm/rabbitizer,
  maspsx (mkst), asm-differ + decomp-permuter (simonlindholm), m2c (matt-kempster), old-gcc (decompals), Ghidra,
  ghidra_psx_ldr (lab313ru), GhidrAssistMCP, psyq-obj-parser (decomp.me), PCSX-Redux, brave-CUE (CUE), the
  xenogears/vagrant-story/tomba decomps (sibling idioms), redump, TCRF, gamehacking.org, the BFM Archipelago world
  (AegeusEvander), ProjectArchitect, Claude Code. Badges at top (D3).
- **D2 LICENSE + NOTICE + THIRD_PARTY** (Max for wording, xHigh to place): root `LICENSE` = AGPL-3.0 verbatim;
  `src/NOTICE.md` = reimplementation-for-study wording, no license asserted, © Square 1998 acknowledged, **never the
  word "clean-room"** (the source was derived from the binary); `THIRD_PARTY.md` rows: brave-CUE GPL-3.0 (source only —
  `brave.exe` purged), submodules (maspsx MIT, decomp-permuter MIT, asm-differ Unlicense, m2c GPL-3.0), old-gcc 0.17
  (GCC = GPL; download + sha256), GhidrAssistMCP MIT (download), ghidra_psx_ldr (no license detected upstream — download
  only, never redistributed), Ghidra Apache-2.0, binutils, splat/spimdisasm/rabbitizer (pip), PsyQ SDK (Sony; user-
  supplied, optional, never distributed; `tools/psyq/CHECKSUMS.sha256` stays so a user can verify their copy), gcc-2.7.2
  source (GPL-2.0; `ftp.gnu.org/old-gnu/gcc/gcc-2.7.2.tar.gz`, sha256 `7cd8bce5…`), the gitignored reference clones,
  ProjectArchitect (Drew's; `docs/history/project_architect_v1.3.0.md` — keep or link: **Drew decides at approval**).
  No per-file SPDX headers (sotn precedent); one statement in `tools/README.md`.
- **D3 Progress publishing** (xHigh + one Max pass on the metric→schema map): `tools/progress.py --json` →
  `docs/progress.json` (fleet fn/instr/distinct + main REAL/LINKED/VERBATIM/empties + per-binary rows, every number
  with its denominator, R41) + `docs/badges/*.json` in shields.io endpoint format (`{"schemaVersion":1,"label","message",
  "color"}`; README uses `img.shields.io/endpoint?url=raw.githubusercontent.com/…/docs/badges/fleet_instr.json`) —
  written by `make report`, asserted by `make audit-digest` (extended). `tools/frogress_upload.py` (stdlib, `--dry-run`
  default, `FROGRESS_API_SECRET` env; frogress projects are admin-created — Drew requests slug `bfm` + key from the
  frogress maintainers). `tools/objdiff_report.py` converts `docs/progress.json` → objdiff `report.json` (categories
  `game-code` vs `linked-sony-objects`; metadata says "from a local clean rebuild; CI does not rebuild") +
  `.github/workflows/progress.yml` uploading artifact `SLUS_007.26_report` for decomp.dev (Drew registers at
  `decomp.dev/manage/new` once public; verify the JSON parses with a downloaded `objdiff-cli` first).
- **D4 SETUP.md public-clean pass** (xHigh): header date; §2.3/§2.4 → download-only for the Ghidra extensions (drop the
  "vendored zip" lines 16-17/861-862); §4.4 generic dump path; §4.7 tarballs; §4.8 + §5.6 PsyQ = user-supplied; §6.5 →
  the decomp.me preset; the "Backup & private-repo posture" section → the public posture; ledger rows 11/14 closed;
  R21 rows for every P33 tool.
- **D5 Governing-docs consistency pass** (xHigh): `CLAUDE.md:61` (Ghidra project + PsyQ SDK stay out of git — true
  again post-flip); `.gitignore` header (H1 in force; drop the `!/extracted/retail/SLUS_007.26` re-include);
  `dumps/INDEX.md:8`; `tools/progress.py`'s pad-tail wording (fix the generator, never the file); `docs/roadmap-to-100.md`
  §1 → a dated "status at P33" block (218 / 0 / second oracle closed); `docs/gen2-roadmap.md:150-166` → a "SUPERSEDED at
  P33" banner (delete nothing); `phase-ends/DIGEST.md` §0/§1/§3 (H1 re-tightened, R1/R20 historical, PROJECT_CONTEXT
  corrections, **R65–R73 full text**); `docs/backlog.md` legacy row retired via `tools/backlog.py`. Verification for
  D1–D5: new `tools/doc_links.py` (relative-link/path checker over README, THIRD_PARTY, SETUP, wiki; in tools-health) +
  `make audit-digest` + a line-by-line grep review for `gitignored|private|curated public mirror|two-repo`.

### Block E — Releases (after the rewrite; each is a directory in-repo first, standalone repo only where stated)
- **E1 decomp.me preset** (xHigh, 0.25 session): `docs/decompme-preset.md` — platform `ps1`, compiler `gcc2.7.2-psx`,
  flags `-O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker -Wa,--aspsx-version=2.56,--expand-div` (decomp.me's
  image wraps `as` with maspsx and forwards `-Wa,` args; its cc1 is old-gcc 0.13 + maspsx `86ccd7d8` vs our 0.17 +
  `874855c5` — prove on `func_80018F20` before saving). Presets are created in-browser by any logged-in user (`POST
  /api/preset/`) — Drew creates it, runs the outstanding manual scratch search, and we close SETUP ledger row 14.
- **E2 Archipelago outreach** (xHigh, 0.25): `docs/outreach/archipelago.md` — the world is
  `github.com/AegeusEvander/Brave-Fencer-Musashi-AP-World` (their `client.py` addresses are already cited in
  memory-map §3.4; one live discrepancy to offer: day-of-week `0x078eba` vs our verified `0x80078EAC`). Drew sends
  (GitHub issue or Discord); on reply, a G5 provenance row in `docs/memory-map.md`.
- **E3 gcc-2.7.2 codegen map** (xHigh, 1): `docs/gcc-2.7.2-map/README.md` (cookbook §31's triage table + per-file scope
  + provenance legend + the gcc-source fetch note + the byte-proof method + the 2.8.1-line-number caveat) and
  `tools/gccmap_cites.py` tagging every `file.c:NNN` cite `[2.7.2]` or `[2.8.1 pm]` against `tools/reference/gcc-2.7.2`
  (`--check` exits 0 when every cite is tagged). Not a standalone repo now (it cites in-repo proofs).
- **E4 xsig** (xHigh, 0.5): move `.run/xdedup/xsig.py` → `tools/xsig/` (library + CLI `sign-s | sign-objdump | cross |
  verify`, MIT `LICENSE`, README with the Xenogears/Vagrant Story/Tomba PsyQ-body hits as the worked example,
  `tests/` with a fixture built from one 10-line C function compiled at two link addresses — no game bytes, no `asm/`
  dependency). Standalone repo `Druthulu/xsig` prepared under `.run/P33/xsig-repo/`; Drew creates and pushes.
- **E5 permuter upstream** (Max, 1): upstream's `Scorer.__init__` gained `ign_branch_targets, objdump_command` after
  our pin, so `tools/permuter/run_masked.py`'s rebind breaks on HEAD; the MIPS symbol wildcard is `"." in field`
  (`scorer.py:66-67`) — the root cause of the nonzero floor for dotless `func_8…` symbols. PR-1: a `RelocMaskedScorer`
  behind a `--score-mode reloc-masked` / settings key (objdump `-drz` words + reloc records; MIPS-only; bottoms at 0 iff
  link-identical; decoupled from our `cdecl`; fixture tests, `mypy`, `black`, `./run-tests.sh`). PR-2 (or an issue):
  configurable `symbol_regex`. The ILS warm-restart stays ours (`docs/permuter-ils.md` + script) and is offered as a
  USAGE recipe. Drew opens the issue, then the PR from his fork.
- **E6 drafter write-up** (Max, 0.5–1): `docs/matching-drafter-pipeline.md` from `docs/community-matching-model-plan.md`,
  `docs/gen2-mips-matching-model.md`, cookbook §12/§500, `docs/wave-playbook.md` — the pipeline and the measured
  results; the ROM-derived pair dataset is NOT published.

### Block F — Endgame writing (after the rewrite, during the GitHub-purge wait)
- **F1 timeline + story** (xHigh tool / Max narrative, 1.5): `tools/timeline.py` (stdlib; walks every commit touching
  `docs/progress.fleet.md` — 449 commits over 70 dates since 2026-06-16 — and `docs/progress.md`, parses both the
  June single-metric and the post-07-11 three-metric formats, joins PhaseEnd dates/versions and commits-per-day;
  **keyed by date, never hash**; self-check: last row == `docs/progress.json`) → `docs/story-timeline.md` + a
  hand-written `docs/story-timeline.svg` (three polylines, phase ticks, the 07-22 denominator step annotated).
  `docs/story.md`: the brief and the lost first month (reconstructed from `docs/history/`, P1–P7), Gen1 exit, the
  fleet + dedup, the pivots (P16/P17/P18/P23), the tooling-integrity audit (P26-A), the family campaign (P29), the
  atlas + wide-tolerance waves (P31), the last 21 (P32), the flip — each section citing its PhaseEnd and decision-log
  entries by path.
- **F2 retrospective** (Max, 1.5–2): `tools/mine_hindsight.py` pulls every decision-log `Hindsight` field, the
  PhaseEnds' "What we believed…" sections and all 32 Deviations tables into `.run/P33/hindsight.md` with `file:line`
  anchors; `docs/retrospective.md` folds in the existing `docs/hindsight-study.md` (294 lines) and
  `docs/generic-decomp-package.md` rather than redoing them: what we believed at each turn · what failed and why it
  looked right · what it cost (with denominators) · what we would do sooner · what stayed genuinely hard. R31: cite,
  never backfill the log.
- **F3 wiki + how-to-AI-decomp** (Max, 2–3): `docs/wiki/` = the project wiki pages (decision 8) and
  `docs/how-to-ai-decomp/` = `00-README` · `01-governance` (ProjectArchitect: constitution, two gates, PhaseEnds,
  R-rules, the digest, replayable checkpoints) · `02-byte-gate` · `03-bootstrap-order` · `04-oracles-and-instruments` ·
  `05-cards-lanes-waves` · `06-knowledge-base` · `07-compiler-source` · `08-models-and-budgets` · `09-economics` ·
  `10-integration-and-propagation` · `11-publishing` · `12-failure-museum`; drawn from `docs/portable-decomp-workflow.md`
  §0–§11, `docs/accelerators.md`, `docs/hindsight-study.md` §3, `docs/effort-map.md`. `tools/wiki_sync.sh` pushes
  `docs/wiki/` to `BFM-decomp.wiki.git` (Drew runs the push). All pages link-checked by `tools/doc_links.py`.

### Block G — Gen2 EXIT (Max, 0.5)
- **G1** `docs/gen3-handoff.md`: Drew's next intent (readability / shiftability prep: casts → structs, pins off,
  names) with the starter census (143 raw `*)0x80xxxxxx` casts, 61,898 distinct `D_80xxxxxx`, 16,335 distinct
  `func_80xxxxxx` in `src/`; 1,092 named symbols), the byte-gate invariant, and the existing levers
  (`tools/lift_types.py`, `tools/cast_call_sites.py`, `tools/canon_sig_reconcile.py`, `docs/struct-core-pivot.md`,
  `docs/gen3-parking-lot.md`).
- **G2** `phase-ends/PhaseEnd_Phase33.md` (PROJECT_CONTEXT format + R25 recap + "what we believed" + Roadmap delta =
  Gen2 EXIT), `CURRENT_PHASE.md` → `phase-ends/logs/Phase33.md` (R19), DIGEST §0/§2/§3 appended, version
  **1.31.0 → 2.0.0**; P33 rule candidates recorded (e.g. "no ROM-derived bytes in any published artifact, test fixtures
  and JSON included"; "published numbers are generated, never typed"). Annotated tag `v2.0.0` created locally after
  Drew's milestone-close commit; **Drew pushes `main --tags`** (R6).

## Execution order and why

```
A1 governance ─► A2/A3/A4 instrument fixes ─► B1 disc-extract ─► B2 includes ─► B3 bootstrap ─► B4 fetch_psyq
   ─► B5 Ghidra text export + rebuild proof (MCP stopped; may overlap B1–B4) ─► B6 dumps ─► B7 CI ─► B8 SETUP/verification.md
   ─► A5 THE RECORDED RUN (final tree) ─► B9/C3 prep commit ─► C1/C2 tooling + negative control (can precede C3)
   ─► C4 archive push (Drew) + rewrite ─► C5 verify ─► C6 adopt ─► C7 map + tip ─► C8 R22 ─► C9 force-push (Drew) + gc
   ─► [Support purge wait: D1–D5 docs/license/README, F1–F3 story/retrospective/wiki, E3/E4/E5/E6 releases land on the
       still-private repo] ─► C10 probe gate → FLIP (Drew) ─► D3 outward (badges/frogress/decomp.dev), E1 preset,
       E2 Archipelago (Drew) ─► C11 aftercare ─► G1/G2 PhaseEnd v2.0.0 + tag (Drew pushes)
```
- The rewrite comes AFTER every build-facing change and the recorded run so that the published tree is the verified
  tree (R22) and no later commit needs rewriting; everything written afterwards cites new hashes only.
- The purge wait is used for the writing and the releases, so the flip is not delayed by them and the repo goes
  public with LICENSE, NOTICE, README, story, retrospective and wiki already in place.
- Mid-phase rules check after every 4 completed tasks (P6). One commit per task after `CURRENT_PHASE.md` is updated;
  banks/artifacts committed immediately (R42). Effort per task as annotated (Max = design/irreversible/synthesis, xHigh =
  execution); no breadth stretch in this phase warrants Ultracode.

## Milestone (gate 2 — what Drew confirms)
1. `.run/P33/verify/SUMMARY.md`: every step EXIT=0 (218/218 clean fleet; `sdk-dual` both legs; oracles green incl.
   `0 PAD-TAIL`; disc residue 0; report 100.00 / 100.0 / 100.0 with `INCLUDE_ASM 0`, backlog 0) — and C8's re-run on
   the adopted tree.
2. `gh api repos/Druthulu/BFM-decomp --jq .private` → `false`; `probe_github.sh` exit 0 (old hashes 404); root
   `LICENSE`, `src/NOTICE.md`, `THIRD_PARTY.md`, the rewritten README with badges + Special thanks + the ProjectArchitect
   link; `.github/workflows/no-rom.yml` green on the public repo; the fresh-clone criterion (B3) met with the disc.
3. Deliverables present: `docs/verification.md`, `docs/commit-map.tsv`, `config/ghidra/*.jsonl` + `ROSTER.md`,
   `dumps/CHECKSUMS.sha1`, `docs/decompme-preset.md`, `docs/outreach/archipelago.md`, `docs/gcc-2.7.2-map/README.md`,
   `tools/xsig/`, the permuter PR branch + `docs/permuter-ils.md`, `docs/matching-drafter-pipeline.md`,
   `docs/story.md` + timeline, `docs/retrospective.md`, `docs/wiki/` + `docs/how-to-ai-decomp/`, `docs/gen3-handoff.md`;
   outward actions (preset saved, Archipelago message sent, frogress/decomp.dev registered, wiki pushed, PR opened)
   done by Drew or explicitly recorded as pending in the PhaseEnd (P9 — never claimed).
4. `PhaseEnd_Phase33.md` v2.0.0 + DIGEST append + `v2.0.0` tag pushed.

## Verification summary (machine-checkable, by block)
A: `tools/verify_contract.sh` logs + SUMMARY; the three instrument fixes each with a positive and a negative control.
B: `make disc-extract` idempotence + two negative controls; include audit 34→0; fresh-clone 218/218; `sdk-dual`;
`ghidra_rebuild.sh --proof` `cmp` exit 0 on SLUS_007.26 + resident and a mutated-copy FAIL; `sha1sum --check` 28/28;
CI green. C: the R39 negative control of `gate_scan.py`; the sample check (711/711 tokens); `verify_rewrite.py` 4,011
pairs; `absent_scan.py` 0/0/0; timestamps identical; `git rev-list --count` arithmetic; C8's R22; the probe gate.
D–G: `tools/doc_links.py` in tools-health; `make audit-digest` over README/progress.json/badges; `timeline.py`
self-check (last row == progress.json); `mine_hindsight.py` anchors resolve; markdown lint on the wiki.

## Risk register (condensed; the full text is in the runbook)
- **Fixed point:** new hashes can never be written into historical docs (each insertion changes every descendant hash);
  hence inert tokens in history, live hashes only in the tip commit. A forward-order fast-import driver with `get-mark`
  could do it in one pass but is an unsafe hand-written importer — rejected.
- **Data-loss hazard after the flip:** the purged paths become ignored; `git clean -fdx` would delete the RE database
  → the bundle, the archive repo, the text export, and the CLAUDE.md fail-safe line.
- **GitHub retention:** force-pushed-away objects stay servable until GC/Support; the earlier S76 pre-scrub lineage
  is ALREADY sitting unreachable on GitHub — the same purge covers it. A fork/import-created archive would share the
  object store — the archive is created empty.
- **Other clones:** `git pull` on an old clone = an 8,000-commit merge; reset or re-clone (runbook).
- **Scrub false positives:** a binary-SHA1 abbreviation coinciding with a commit prefix (expected < 1 over 44k tokens)
  is guarded by the content-hash exclusion set; ambiguous prefixes become `commit:amb-N`, never a wrong hash.
- **Disk/time:** 13 GB free suffices (clone 0.6 + rewrite 0.2 + bundle 0.6 GB); rewrite 10–30 min; R22 ≈ 1 h.
- **Mailmap:** cosmetic unless the 3 tracked files mentioning the addresses are also replaced (they are).
- **The 4-track requirement:** the committed manifest includes Tracks 2–4 audio; a Track-1-only user gets an explicit
  PARTIAL verdict, never a silent pass.

## Honest scale (P9, R41)
| Block | Sessions |
|---|---|
| A verification + instrument fixes | 0.5–1 |
| B build path, Ghidra export/rebuild proof, dumps, CI, SETUP | 3–4 (B5 alone 1–1.5) |
| C rewrite, verification, push, gc | 3 + 1 calendar-gated on GitHub Support |
| D publishing surface | 1.5–2 |
| E releases (preset 0.25, Archipelago 0.25, gcc map 1, xsig 0.5, permuter PR 1, drafter write-up 0.5–1) | 3.5–4 |
| F story 1.5, retrospective 1.5–2, wiki + how-to 2–3 | 5–6.5 |
| G exit | 0.5 |
| **Total** | **≈17–21 sessions** (roadmap v2 priced the narrow verify+flip P33 at 2–4; the difference is items 3–5) |
Cut points that cost nothing later because the flip precedes them: F3 (wiki, 2–3), E5 (permuter PR, 1), E3 (gcc map, 1).

## After approval (R28)
Build the harness task list: one task per plan item A1–A5, B1–B9, C1–C11, D1–D5, E1–E6, F1–F3, G1–G2, in the order
above; create `phase-ends/CURRENT_PHASE.md` with the plan, the effort annotations and the first 🛑 checkpoint block;
commit as the A1 governance commit. Then one task at a time.
