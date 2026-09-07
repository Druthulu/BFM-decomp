# CURRENT_PHASE — Phase 33: 100% verification + the public flip + Gen2 exit

> **Gate 1 approved 2026-09-06 (Drew, plan mode, Max, Fable 5.1).** Rules **R65–R73 ratified at gate 1** (binding; full text
> in `phase-ends/DIGEST.md` §3). The approved plan is reproduced VERBATIM at the end of this file (§"Approved plan") — its
> `~/.claude/plans/` copy is not part of the repo. Roadmap: `docs/roadmap-to-100.md` v2 §3 P33 (all six items, Drew's
> "everything as written"); `docs/gen2-roadmap.md` Phase 14's two-repo model is SUPERSEDED by the in-place flip.
> **Baseline HEAD at open: `b5b79b3ac`** (the Phase-32 CLOSE commit; tree clean apart from the R23 `ghidra/` churn).

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
- [x] **A1** Governance commit (R65–R73 in DIGEST §3; this file; the harness list) — xHigh — `73068f39f`
- [x] **A2** Reporting-instrument fixes (pad-tail literal → derived; backlog LINKED-aware prune; `sig-main` build-derived +
      `progress.py` loud-fail) — xHigh, R39 controls — see Log 2026-09-06 A2
- [x] **A3** `NO_SDK` knob + `make sdk-dual` (+ tools-health wiring, `[skip]` without SDK dirs) — Max — see Log 2026-09-06 A3
- [x] **A4** `tools/family_hseq.py` regen — Low (became an instrument fix: the map now carries its own coverage) — see Log
- [x] **B1** `make disc-extract` (extract.py `--expect-manifest` / `--allow-missing-audio`; check-env; `.gitignore`
      re-tightened; the 4 splat preset headers tracked; `clean` fixed) — Max — see Log 2026-09-06 B1
- [x] **B2** 34 absolute includes → `../shared/` + portable-include audit + 15-binary re-gate — xHigh — see Log 2026-09-06 B2
- [x] **B3** `tools/bootstrap.sh` / `make bootstrap` + check-env extensions + fresh-clone proof 218/218 — xHigh — see Log 2026-09-06 B3
- [x] **B4** `tools/fetch_psyq.sh` + CHECKSUMS rows (20 lib40 LIBs, psyq-obj-parser) BEFORE `tools/psyq/` leaves git — xHigh — see Log 2026-09-06 B4
- [x] **B5** Ghidra regenerability (ExportAnnotations/ImportAnnotations/ghidra_rebuild.sh `--proof` on SLUS_007.26 +
      resident; roster; ExportSymbols R15 fix; path hardcodes; hooks) — Max (finished at medium, Drew's call) — see Log 2026-09-06 B5
- [x] **B6** `dumps/CHECKSUMS.sha1` + INDEX.md rewrite + memory-map Source-index row — Low/xHigh — see Log 2026-09-06 B6
- [x] **B7** No-ROM CI (`no-rom.yml`, `audit_public.py`, `compile_only.py`) — xHigh — see Log 2026-09-06 B7
- [x] **B8** SETUP.md rows/sections (R21) + `docs/verification.md` — xHigh — see Log 2026-09-06 B8
- [x] **A5** THE RECORDED RUN (`tools/verify_contract.sh` → `.run/P33/verify/`, SUMMARY all EXIT=0) — run Low, read Max — see Log 2026-09-06 A5
- [x] **B9/C3** The preparatory commit (`git rm --cached` purge set; psyq CHECKSUMS moved; zip sha256s; runbook;
      decision-log entry) — Max (P5c-class) — see Log 2026-09-06 B9/C3
- [x] **C1** filter-repo 2.47.0 + `tools/public_rewrite/` — design Max, execution xHigh — see Log 2026-09-07 C1
- [x] **C2** Negative control + dictionary + sample — xHigh — see Log 2026-09-07 C2
- [x] **C4** Bundle + Drew's archive mirror push + bare clone + the rewrite — xHigh — see Log 2026-09-07 C4
- [x] **C5** Verification suite on the rewritten clone — xHigh — see Log 2026-09-07 C5
- [x] **C6** Adoption in `~/bfm-decomp` (no gc yet) — xHigh — see Log 2026-09-07 C6
- [x] **C7** `docs/commit-map.tsv` + tip resolution commit — design Max, run xHigh — see Log 2026-09-07 C7
- [x] **C8** R22 clean rebuild on the adopted tree — xHigh — see Log 2026-09-07 C8
- [x] **C9** Final gate + Drew's force-push + local gc — xHigh — see Log 2026-09-07 C9
- [ ] **C10** Support purge → probe gate → FLIP (Drew) — decision Max
- [x] **D1** README rewrite — Max — see Log 2026-09-07 D1
- [x] **D2** LICENSE + `src/NOTICE.md` + `THIRD_PARTY.md` — Max wording — see Log 2026-09-07 D2
- [x] **D3** Progress publishing (progress.json, badges, frogress_upload, objdiff_report + progress.yml) — xHigh — see Log 2026-09-07 D3
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
- **2026-09-06 (S86) — A1** `73068f39f`: R65–R73 appended to DIGEST §3; this file opened with the plan verbatim; 41 harness tasks.
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
- **2026-09-06 (S86) — A4 (family map regen → instrument fix, R35).** Regenerating `.run/family_hseq.json` made the
  `audit-binaries` warning WORSE (6 → 217 "missing"): at 100% the map's `families` list is empty and CHECK 4 inferred coverage
  from family members, so a complete map read as empty; the P32-close warning had been a stale pre-onboarding file. Fix:
  `family_hseq.py` writes `"binaries"` (scanned: 217) + `"open_instances"` (0); `audit_binaries.py` CHECK 4 reads that
  denominator and warns "predates the coverage field" on an old-format map. Controls: current map → 0 `[warn]`; the same map
  with the keys removed → the predates warning; restored → 0. No other tool calls `family_hseq.load()` (grep; consumers read
  the json's `families` key, unchanged). `docs/family-hseq.md` regenerated (0 families). SETUP: P33 A4 section (R21).
- **2026-09-06 (S86) — B1 (`make disc-extract`).** `tools/bfm_extract/extract.py`: `--expect-manifest` (compare against the
  committed oracle, never write it; mismatch → `.run/extract/` + the first 20 diffs, exit 1; refuses an internally
  inconsistent oracle) and `--allow-missing-audio` (PARTIAL verdict for Track-1-only dumps, in both extract and `--verify`).
  Makefile: `disc-extract` (probe → disc presence → `--verify-disc` → extract+compare → verify), `extract` runs it when
  `$(EXE)` is absent, `extract-all` runs it once first, `check-env` step 6 WARN-on-absent + step 7 oracle self-consistency +
  disc INFO, `help` rewritten, `clean` keeps the 4 preset headers (now tracked), `.PHONY`. `.gitignore` re-tightened to H1
  (see SETUP P33 B1). **Controls:** no disc → exit 2 + staging text; truncated 100 MB Track 1 → `--verify-disc` FAIL, nothing
  written, `git diff --exit-code` on the oracle clean; the real run with `extracted/` moved aside and only the two manifest
  files restored → `disc-extract: OK` in **15.7 s** (EXIT=0, `.run/P33/b1_disc_extract.log`), `diff -rq` against the previous
  tree IDENTICAL for all 1,801 retail files; second run "up to date" in 0.7 s; `make check-env` OK with the new PASS lines.
  Slip, recorded: the previous tree also held `extracted/proto/` (the two prototype EXEs from the prototype discs, not the
  retail one) and I removed the moved-aside copy in the same command as the diff — regenerated from `disks/` with
  `tools/bfm_extract/extract_proto_exe.py` (sep8 413,696 B sha1 `43006a31…`, aug31 415,744 B sha1 `6150b0f8…`). Commit
  `026571291`.
- **2026-09-06 (S86) — B2 (portable includes).** `tools/audit_text_sources.py` gained the portable-include class (absolute /
  angle-bracket / unresolvable / outside-repo `#include`); positive control BEFORE the fix: 34 offenders in 19 files, all
  ABSOLUTE (4,299 sources scanned); the sed → `../shared/engine_core.h` ×30 + `../shared/engine_types.h` ×4;
  `grep -rn /home/musashi src include` → 0; negative control → OK. Re-gate of the 15 binaries (derived from the diff, 5 in
  parallel): 15/15 `[ OK ]` BYTE-IDENTICAL in 29 s wall (`.run/P33/b2_gate/<bin>.log`). SETUP: P33 B2 section (R21). Commit
  `9be6364a5`.
- **2026-09-06 (S86) — B3 (bootstrap + the fresh-clone proof).** `tools/bootstrap.sh` (apt presence → printed install line;
  venv from `requirements-python.txt`; submodules; cc1 tarballs sha256-checked + extracted into their own dirs; `make
  check-env`), `make bootstrap`; check-env gained 4b (the other three submodules, WARN), 4c (the four tracked preset headers,
  FAIL) and 8 (`[INFO] extracted payloads present: N / 218`). Idempotent run here: 1.4 s, OK. **The proof** (`.run/P33/
  b3_fresh.log`): `git clone --no-local` into `.run/P33/fresh` (the uncommitted Makefile + bootstrap.sh copied in) →
  `tools/bootstrap.sh` created its own `.venv`, extracted both cc1s, fetched the submodules, `check-env: OK` → `disks` symlinked
  → `disc-extract: OK` → `extract-all: 217 extracted, 0 failed of 217` → **`check-all: 218 passed, 0 failed of 218`**, EXIT=0,
  **4 m 18 s wall** (user 45 m 48 s) — with NO SDK objects in the clone (`.run/obj40` absent), i.e. every binary built the way a
  public user builds it. Clone deleted afterwards (3.1 GB). SETUP: P33 B3 section (R21). Commit `89e087f52`.
- **2026-09-06 (S86) — B4 (the optional SDK, user-supplied and verified).** `git mv tools/psyq/CHECKSUMS.sha256
  tools/psyq_CHECKSUMS.sha256` (done here rather than in C3 so the script's path is final) + rows for the parser tarball
  (`353495f1…`, decomp.me's release), the parser binary (`4fba623a…`, identical to our Phase-7 copy) and the 20 PsyQ 4.0
  LIBs; `docs/SETUP.md` + `.gitignore` references repointed. New `tools/psyq_libs_from_disc.py` (the 20 `PSX/LIB/*.LIB` off
  the DTL-S2002 redump disc via our own ISO walker; refuses a disc without `PSX/LIB`; asserts 20) and `tools/fetch_psyq.sh
  [--disc|--from] [--no-build]` (parser → RTL 4.2 7z → lib421 → the 4.0 LIBs, each sha256-verified before use; then
  `psyq_build_libs.sh` ×10, `make_libgs.sh`, `make_snd_used.py`, the lib421 ELF step, `make_apicard_used.py`, `make sdk-dual`).
  **Controls:** no 4.0 source → refuses naming the redump title (rc 1) after verifying the parser + 4.2 pieces; `--from` a dir
  with one corrupted LIB → `sha256 MISMATCH for tools/psyq/lib40/LIBTAP.LIB`, rc 1, nothing built. **The run:** with
  `tools/psyq/lib40/` moved aside, `fetch_psyq.sh --disc "<our Track 1 .bin>"` extracted the 20 LIBs from the disc
  (`diff -rq` against the tracked copies: identical), verified them, rebuilt `.run/obj40/*`, `.run/obj42/*`,
  `tools/psyq/lib40_elf/`, and `sdk-dual: OK` — **36.9 s wall**, EXIT=0 (`.run/P33/b4_fetch.log`). SETUP: P33 B4 (R21). Commit
  `707ec491e`.
- **2026-09-06 (S86) — B5 IN PROGRESS (checkpointed at 87% context; WIP commit).** Done and proven: MCP stopped cleanly;
  `tools/ghidra_scripts/ExportAnnotations.java` + `tools/ghidra_export_annotations.sh` — byte-stable JSONL export of a
  program's container facts, LOCAL types, every function signature (params/locals/storage/sources), defined data, the 5
  comment kinds, bookmarks, equates, and labels the symbol files do not carry; **all 129 programs exported in 18.5 s** →
  `.run/ghidra_export/<prog>.jsonl` (139 MB; resident 2,573 rows in 5.7 s). `tools/ghidra_annotations_delta.py` (live −
  baseline; container rows always kept; `--census`). Makefile `print-%` helper + `GHIDRA_PROJ` repo-relative; the six
  `tools/ghidra_*.sh` wrappers repo-relative (`BFM_GHIDRA_PROJ` override; `ghidra_mcp_verify.sh` takes the program as arg 3
  / `BFM_GHIDRA_PROG`); `DefineFunctions.java` takes the list path as arg 1; `ImportPsyqGdt.java` finds the gdt under
  `Application.getInstallationDirectory()`; `ExportSymbols.java` R15 fix (output path arg, refuses to overwrite, refuses
  `config/`). Written, NOT yet proven: `tools/ghidra_scripts/ImportAnnotations.java`, `tools/ghidra_rebuild.sh` (its import
  step works: the scratch project must live under `build/ghidra_rebuild/proj` — Ghidra refuses a path component starting
  with '.'; `resident_funcs.txt` from the ELF = 1,304 entries). **Blocker found:** in the resident rebuild the runs after the
  import failed with `Failed to get OSGi bundle containing script: …/tools/ghidra_scripts/ApplySymbols.java` (same for
  ExportAnnotations) — Ghidra compiles the script DIRECTORY as one bundle, so ONE file that does not compile breaks every
  script in it; `ExportAnnotations` worked on 129 programs BEFORE `ImportAnnotations.java` existed ⇒ the new file almost
  certainly has a compile error (one known: `new LocalVariableImpl(name, first, dt, stackOffset, program)` — no such ctor;
  the stack form is `(String, DataType, int, Program)` without first-use, or `(String, int, DataType, VariableStorage/Address/
  Register, Program)`). Census of the live exports (heuristic, before baselines): `types=0` in EVERY program (no hand-authored
  structs in the DB at all); the 154/402 "USER_DEFINED" variables per program are the loader's GTEMAC functions
  (analysis-origin, will subtract); real user labels beyond the symbol files: aug31 382, sep8 15, SLUS_007.26 1, overlays 1–2.
- **2026-09-06 (S87) — B6 (dumps).** `dumps/CHECKSUMS.sha1` (28 rows from `sha1sum ram_*.bin`; `sha1sum --check` 28/28 —
  `ls dumps/*.bin | wc -l` = 28, `git ls-files dumps` = 29 incl. INDEX; the `.bin` are still TRACKED until C3, ignored
  for new adds since B1); `dumps/INDEX.md` status bullets rewritten (LOCAL-ONLY from the flip; the archive repo holds the
  committed copy; a re-capture via `tools/ram_probe.py snapshot` is a new state snapshot, never byte-identical — the
  table of 28 states preserved verbatim); `docs/memory-map.md` Source-index row for the corpus. Commit: see below.
- **2026-09-06 (S87) — B7 (the ROM-free CI).** `tools/public_rewrite/purge_set.txt` (THE purge set, filter-repo syntax —
  created here so `audit_public` and C1 share one file); `tools/audit_public.py` (purge paths + a DERIVED ROM-hash set
  [1,801 manifest rows + 218 check.*.sha + redump] + 50 MiB cap; controls: the current tree FAILS with exactly the purge
  set — 255 offender rows — a clean subset OK, a renamed EXE copy caught by content; empty-file SHA1 collision with the
  zero-length SC04/SC05 `FILE_029/1.6` payloads found and exempted); `tools/compile_only.py` (flags parsed from the Makefile,
  TUs from `<alias>_SRC_DIR` with nested pruning, skips DERIVED: 70 LINKED + 47 INCLUDE_ASM, -O0 TUs compiled at -O0;
  measured PR scope 54/54 in 1.6 s, **fleet 4,170/4,170 in 123 s at -j32, failed 0**; unknown alias refused);
  `.github/workflows/no-rom.yml` (jobs `audits` + `compile-only`; every audit command re-run under the SYSTEM python
  without the venv/obj40 → rc 0 ×8; apt needs `cpp-mipsel-linux-gnu` for the MIPS cpp — `dpkg -S` measured; `cdecl --audit
  --gcc` left out: > 5 min exhaustive). The `audits` job is RED until C3 by design (the purge set is still tracked).
  Gotcha, recorded: `pkill -f '<pattern>'` from a shell whose own command line contains the pattern kills that shell
  (exit 144) — match on the child's distinctive argv or use `pgrep -f … | grep -v $$`. SETUP: P33 B7 section + 4
  inventory rows (R21). Commit: see below.
- **2026-09-06 (S87) — B8 (SETUP cross-references + `docs/verification.md`).** Every P33 tool already had its SETUP section +
  inventory row (written with its task, R21); B8 added the as-built pointers the plan named — §4.4 → `make disc-extract`,
  §4.6 → `make bootstrap`, §4.8 → `tools/fetch_psyq.sh`, §6.3 → `make help` + the new targets + the R22 line — and the
  "Backup & private-repo posture" P33 update (R20's new home: `config/ghidra/` + `--proof`, `dumps/CHECKSUMS.sha1`,
  `tools/psyq_CHECKSUMS.sha256`, the archive repo; "never `git clean -x`"). NEW `docs/verification.md`: what you need
  (redump SHA1/CRC, apt, disk/time), the R22 recipe with every expected last line (from `make help`, the P32/B3 logs and the
  current digest: 363,214 / 13,492,113 / 5,820,205 / main 45,150), what is NOT our C (1,256 LINKED + 5 verbatim), the
  last-recorded-run table (placeholder until A5 fills it from `SUMMARY.md`), what CI proves without the disc, the
  regenerable RE artifacts. `tools/verify_contract.sh` is A5's (next). Commit: see below.
- **2026-09-06 (S87) — A5 THE RECORDED RUN: PASS.** `tools/verify_contract.sh` on HEAD `3e0ecfacc` → `.run/P33/verify/`
  (tracked): 00 tree · 01 `check-env: OK` · 02 family_hseq 217 scanned / 0 open · **03 `check-all: 218 passed, 0 failed of
  218` (157 s, clean fleet)** · 04 `sdk-dual: OK — main 143dbb89… WITH and WITHOUT` (28 s) · 05 `tools-health: OK` (356 s;
  `sig-main-oracle: 0 PHANTOM, 0 TRUNCATED, 0 PAD-TAIL`; zero `[warn]`) · 06 audit-frontier (1,258 stubs = all in main's
  LINKED regions, 0 game-code) · 07 `UNCLAIMED code payloads: 0` · 08 report `363214/363214 · 13492113/13492113 ·
  5820205/5820205 · main 45150/45150`, `INCLUDE_ASM stubs : 0`, backlog 0. Every step EXIT=0 with its contract line;
  SUMMARY.md pasted into `docs/verification.md` §2. Total wall 14 min (32 CPUs, JOBS=16). Two false starts recorded: the
  porcelain check tripped on the run's own untracked logs (→ `-uno`), and audit_frontier's derived LINKED count read 0
  twice (the reference view keys addresses, not Stub records) — each fix gated on a control before its commit (R66).
  Gotcha ×2: `pkill -f '<pattern>'` kills the calling shell when its own command line contains the pattern (exit 144) —
  bracket the pattern (`'verify_contrac[t]'`). Commit: see below.
- **2026-09-06 (S87, Max) — B9/C3 the preparatory (purge) commit.** Pre-checks: census of the purge set (1 EXE at
  `extracted/retail/`, 28 dumps, 27 Ghidra DB files, 189 under `tools/psyq/` — all Sony/third-party: 20 LIB, 61 h, 55 o,
  37 a, 10 EXE, 3 zip, psyq.ini, psyq-obj-parser; 3 archive parts; 2 zips; brave.exe = 251 index entries; nothing
  project-authored inside a purged dir — CHECKSUMS had moved in B4); ignore coverage proven with `git check-ignore
  --no-index` on every path (the plain form is BLIND to tracked files — it reported nothing); **control: main byte-identical
  with `tools/psyq/` + `.run/obj40` + `.run/obj42` moved aside** (0 `build/psyq/` map entries = the public WITHOUT leg; B3's
  fresh clone still HAD tools/psyq), WITH state restored (1,288). Then `git rm --cached` ×251 (files stay on disk: 37
  sampled present); `git ls-files` on every purge path → 0; `?? ` purge paths in status → 0; **`tools/audit_public.py` →
  OK, 0 offenders among 6,566 tracked paths (its first green; 255 offenders before)**; `make check-env` → 0. Docs in the
  same commit: `docs/public-flip-runbook.md` (NEW — Block C operational: decisions, actor table, C3…C11 with exact
  commands/checks, the Support-ticket text, the probe, fallback, risk register, rollback; the mailmap is SCRATCH and the
  runbook names no personal address), SETUP §2.3/§2.4 (the two zip sha256s + byte sizes; download-only now),
  `docs/verification.md` (the `--cached` removal changes no tracked-content byte → A5 holds for this tip), `CLAUDE.md`
  fail-safe line **"never `git clean -x`"** (the hazard begins at THIS commit: ignored-but-present dirs), the decision-log
  entry (R31: why the purge leaves the index before the rewrite). Re-measured repo state for C1/C2: main 4,029 commits
  before this commit, `--all` 4,300; refs = main, origin/main, origin/HEAD, 1 stash, the tag (NO `refs/original/`, 1 stash —
  not the S86 block's 3 + refs/original; re-measure in C2); `origin/main` is still the P32 close commit — **Drew has not
  pushed the P33 commits yet (R6)**; `.git` 929 MB. Commit: see below.
- **2026-09-07 (S87, Max) — C1 the rewrite tooling, PROVEN by two trial rewrites on a scratch bare clone.**
  `git-filter-repo==2.47.0` in the venv (+ `requirements-python.txt`); `tools/public_rewrite/`: `common.py`, `hash_dict.py`
  (4,420 commit objects: 4,030 main / 339 twins / 51 orphans; 150,280 prefixes; **0 ambiguous, 0 collisions** with 1,480 cited
  content hashes; the scratch mailmap: 2 personal identities → noreply), `scrub.py` (`--test` 12/12; `--sample` over HEAD:
  397 MB in 7.9 s, 1,238 replacements in 98 files, 731 distinct tokens = EXACTLY the set git's own object lookup resolves;
  the 186 seven-char replacements read — all commit ranges in PhaseEnds/cookbook), `gate_scan.py` (+ the tracked fixture
  `expected_offenders.txt`; negative control PASS: 16.8 GB / 112,390 blobs in 2 m 25 s, every rule named, 0 strays),
  `run_filter.py`, `verify_rewrite.py`, `build_commit_map.py`, `resolve_tokens.py`, `absent_scan.py` (positive control on the
  current repo: FAIL with 82,362 offenders, 7 m 24 s), `probe_github.sh`. **Trial #1** (filter 274 s) exposed two defects
  that would have corrupted the real run — (1) the EMPTY blob was in the strip list (an empty file once sat under a purge
  path) and `--strip-blobs-with-ids` dropped every "file emptied" change in history: 7 files kept their previous content and
  a restore commit was pruned as a second empty; (2) the byte-identical "Initial commit" (noreply-authored, no citations,
  no purge paths) keeps its hash and tripped the map's old-hash assertion — plus the post-rewrite gate's empty-list guard.
  Fixes: shared blobs are never stripped by id (content/signature hits always are); `verify_rewrite` asserts no purge path
  survives and that the pruned set == the DERIVED purge-only set; unchanged commits recorded (`unchanged_commits.txt`) and
  exempted in the map, absent_scan and the probe; the guard fires only with path offenders. **Trial #2: everything PASS** —
  gate fixture PASS (268 ids, the empty blob excluded); filter 269 s, **1 pruned** (exactly "session archive update"), main
  4,030 → 4,029; `verify_rewrite` 4,029 pairs / 0 failures (241,534 changed blobs re-derived, 989,166 removals justified, the
  empty commit survived) in 430 s; map 4,030 rows / 1 pruned / 0 old hashes / 1 unchanged; absent_scan on the clone PASS
  (0/0/0/0/0/0; INFO 370 bare UUIDs) 409 s; gate on the clone PASS (0 offenders, 60 s); resolve_tokens on a trial checkout:
  1,231 tokens in 97 files, residue 7 (`commit:1712` ×3 = the pruned commit's ordinal, orphan-24 ×2, orphan-26, orphan-35 —
  cited commits that exist in no lineage), `--check` 0 remaining; absent_scan --tree HEAD PASS. **Pack size:** filter-repo's
  gc leaves 500 MB; `repack -adf --window=250 --depth=50` → **80 MB in 166 s** (C9). SETUP P33 C1 section + rows; runbook
  §3/§5/§6/§10 updated with the measured facts and the strip-by-id lesson. Trial scratch deleted (C4 re-clones fresh).
  For Drew's decision (not in the plan's scope, reported by absent_scan as INFO): 370 bare session UUIDs across history / 68
  at HEAD in checkpoint prose; no `claude.ai` URL anywhere. Commit: see below.
- **2026-09-07 (S87) — C2 the recorded controls on the final pre-rewrite tree (HEAD `fca383904`, the C1 commit).**
  `hash_dict.py --write-mailmap`: 4,421 commit objects (4,031 main, 339 twins, 51 orphans), 150,314 prefixes, **0 ambiguous,
  0 collisions** with 1,480 cited content hashes, 2 identities → noreply. `scrub.py --test` 12/12; `scrub.py --sample`: 397 MB
  in 7.9 s, 1,239 replacements in 98 files, **732 distinct tokens == the 732 git's own lookup resolves** (only-git 0 /
  only-ours 0), 186 seven-char replacements read (`.run/public_rewrite/c2_sample.log`, scratch — it prints old hashes).
  `gate_scan.py --all --worktree --expect-fail`: 112,405 reachable blobs / 16.79 GB in 3 m 13 s, every rule named with its
  count (ghidra/ 42 paths ever, tools/psyq/ 190, dumps 28, archive 3, zips 2, brave.exe 1, the EXE 1+1), 0 strays, 268 ids
  to strip (the shared EMPTY blob excluded), **`audit_public` OK 0 offenders among 6,578 tracked paths**. One more R43 guard
  added to `run_filter.py`: it refuses a dictionary whose main count/HEAD differ from the clone's (a stale dictionary would
  drop rows from the public map; trial #2 matched by construction). **Sequencing law for C4:** the dictionary + ids are
  rebuilt from the FINAL tree right before the clone (4 s + 3 min) — any commit after that invalidates them (the guard
  enforces it). Commit: see below.
- **2026-09-07 (S87) — C4 the backups and THE REWRITE.** C4a: `.run/public_rewrite/pre-rewrite.bundle` (556 MB, `--all
  --reflog`, `git bundle verify`: complete history, 6 refs) made after the C2 commit. C4b (Drew, R6): WSL had no GitHub
  credentials (password auth refused) → `gh auth login -h github.com -p https -w` (device flow, browser opened by hand — the
  "failed opening a web browser" line is cosmetic, Ctrl-C cancels the login) + `gh auth setup-git`; `Druthulu/BFM-decomp-archive`
  created (Private; it carried GitHub's own `.gitattributes` initial commit — force-updated, harmless) and `git push --mirror
  archive` (176,533 objects, 530 MiB; GH001 large-file warnings for the 3 archive parts, accepted). Verified via `gh api`:
  **private, not a fork, no parent**; `git ls-remote archive` == local refs except **`refs/stash`, which `--mirror` does not
  push** (the bundle holds it; Drew may push it as a branch). C4c: FINAL dictionary on the committed tip (4,422 commit objects,
  4,032 main, 0 ambiguous, 0 collisions) + FINAL ids (`gate_scan --expect-fail` PASS; 268 ids, the shared empty blob
  excluded) → bare `--no-local` clone (1 pack, 0 loose) → tag deleted (its tip recorded in scratch) → **`run_filter.py`:
  311 s, commit-map 4,032 rows, exactly 1 pruned ("session archive update", ordinal 1712), main 4,032 → 4,031, new tip
  `494fbd3c8`, 1 pack / 0 loose / 500 MB, scrub stats: 72,568 hash replacements, 85 address replacements, 60 trailers dropped,
  192 binary blobs untouched.** Logs: `.run/public_rewrite/c4c5.log`, `filter.log` (scratch).
- **2026-09-07 (S87) — C5 the verification suite on the rewritten clone — ALL PASS.** `verify_rewrite.py`: **4,031 pairs / 0
  failures** (identities post-mailmap, both timestamps, message == scrub(old), parents with the pruned commit spliced,
  241,734 changed blobs re-derived as git-hash(scrub(old)), 989,166 path removals justified, no purge path survives in any new
  tree, pruned set == the derived purge-only set, the pre-existing empty commit survived) in 433 s. `build_commit_map` (scratch
  copy): 4,032 rows / 1 pruned / 0 old hashes / 1 unchanged (the noreply-authored "Initial commit", ordinal 1, byte-identical).
  `absent_scan.py` on the clone: **0 offenders** across 112,138 blobs (16.2 GB text) + 4,031 commits + refs (INFO 370 bare
  UUIDs) in 360 s. `gate_scan.py --all --repo <clone>`: **PASS, 0 offenders** over 16.22 GB in 56 s.
- **2026-09-07 (S87) — C6 adoption in `~/bfm-decomp` (NO gc).** `git fetch <clone> +refs/heads/main:refs/heads/main-rewritten`;
  `git diff --name-only main main-rewritten` = **100 files, all text (0 binary), 0 purge paths, 0 added/deleted** (the
  token-scrubbed docs/logs/tool comments at the tip); `git reset --hard main-rewritten` → HEAD `494fbd3c8`; tracked 6,578 ==
  the clone's tree; `main-rewritten`, `refs/original/refs/heads/main`, the tag and the 1 stash dropped (bundle + archive hold
  them); refs now: `main`, `remotes/origin/{HEAD,main}` (the P32 close, pinning the old lineage until Drew's push),
  `remotes/archive/main` (the pre-rewrite tip); `rev-list --all --count` 8,143 (both lineages); the purged paths still on disk.
- **2026-09-07 (S87) — C7 the commit map + the tip resolution.** Repo-local identity → `Drew T
  <50529377+Druthulu@users.noreply.github.com>`. `build_commit_map.py` → **`docs/commit-map.tsv` (4,032 rows, 1 pruned row of
  zeros, 0 old hashes asserted)** + private `old-to-new.tsv` + `unchanged_commits.txt` (1). `resolve_tokens.py`: **1,238 tokens
  → shortest-unique ≥9-char new hashes in 98 files** (phase-ends 24, logs 20, docs 23, tools 14 — comments/docstrings only,
  checked; 2 `src/` files — C comments only, checked; `.run/P33/verify` 3, `.run` notes); `--check` 0 remaining; **residue 8
  in 4 tokens: `commit:1712` ×4 (the pruned commit), `commit:orphan-24` ×2, `commit:orphan-26`, `commit:orphan-35` (cited
  commits that exist in no lineage — one is the dropped TEMP commit in tools/verify_worktree.py)**. Defect caught and fixed
  before the commit: the resolver had rewritten `scrub.py`'s self-test fixtures (`commit:0012` etc. are the grammar's own
  examples) — restored from HEAD, and `tools/public_rewrite/` is now skipped by rule. `absent_scan --tree HEAD` PASS,
  `audit_public` OK. The tip commit (this one) cites NEW hashes only. Commit: see below.
- **2026-09-07 (S87) — C8 R22 on the ADOPTED tree: PASS.** `tools/verify_contract.sh` on HEAD `5bc4a5c0ab` (the rewritten
  history + the C7 tip + one fix): 00 tree · 01 `check-env: OK` · 02 family_hseq 217/0 · **03 `check-all: 218 passed, 0 failed
  of 218` (176 s, clean fleet)** · 04 `sdk-dual: OK` both legs `143dbb89…` (29 s) · 05 `tools-health: OK` (358 s; `0 PHANTOM, 0
  TRUNCATED, 0 PAD-TAIL`, zero warns) · 06 audit-frontier (1,258 stubs = main's LINKED regions, 0 game-code) · 07 `UNCLAIMED code
  payloads: 0` · 08 report `363214/363214 · 13492113/13492113 · 5820205/5820205 · main 45150/45150`, stubs 0, backlog 0. Total
  ≈14 min. **A content-preserving rewrite changed no tracked-content byte — proven.** Two false starts recorded, both my own
  instrument: the A5 logs under `.run/P33/verify/` are TRACKED since A5 (I deleted them before the run → dirty tree), and
  `run_step` writes `00_tree.log` before the porcelain check runs → step 00 failed on its own log; fixed in `5bc4a5c0ab` (the
  check now excludes `.run/P33/verify/`). SUMMARY pasted into `docs/verification.md` §2 (the C8 run is now the recorded one; the
  A5 run is cited by date). Commit: see below.
- **2026-09-07 (S87) — C9 the final gate, THE FORCE-PUSH (Drew) and the local gc.** Gate on the final `main` + worktree:
  `gate_scan --refs main --worktree` PASS (0 offenders over 16.23 GB, 61 s; `audit_public` OK 6,579 paths); `origin` carried no
  tags. **Drew: `git push --force origin main`** (176,052 objects, 491.5 MiB) → `git fetch --prune origin` → `origin/main ==
  main == e821833986`. Local gc, with two discoveries: (1) `refs/remotes/archive/main` pinned the old lineage → `git remote
  remove archive` (done here instead of C11); (2) **12 stale linked worktrees** (`.run/S74/wt_*` ×8, `.run/pgate/wt8-9`,
  `.run/S69_fable3/pgate/wt0`, `~/bfm-verify` — campaign gate scratch from 2026-08-24…09-02, ~12 GB, each a full old-history
  checkout with the SDK/EXE/Ghidra on disk, no process using them) kept 3,729 old commits reachable (a linked worktree's HEAD
  counts) → `git worktree remove --force` ×12 + prune: `rev-list --all` 8,146 → 7,763 (remote) → **4,034 = main**. Then reflog
  expire + `repack -adf --window=250 --depth=50` + prune + a fresh commit-graph (the stale one named pruned commits → fsck
  errors): **one pack, 80 MB; `.git` 1.5 GB → 93 MB; store == reachable (176,056 objects); fsck clean; disk 13 → 24 GB free.**
  Scans on the working repo: `absent_scan` **PASS 0 offenders** (112,251 blobs / 16.2 GB text + 4,034 commits, 438 s; INFO 375
  bare UUIDs), `gate_scan --all --worktree` **PASS** (94 s). **Probe baseline** (`probe_github.sh`, gh-authenticated): 33 old hashes
  sampled → **31 still ALIVE on GitHub, 2 already gone** — the ticket's target is 0; the probe now treats the API's 422 ("no
  commit found") as gone (it had counted the vanished tag tip as alive). The rewritten history is the only one reachable
  locally and the only one reachable on `origin`; the old objects remain SERVABLE on GitHub until Support purges — hence C10.
  Runbook §10/§12 updated with the measured procedure. Commit: see below.
- **2026-09-07 (S87, Max) — D1 the README rewrite.** The old README was Phase-19 era (136 binaries, 52 functions, "about
  half the EXE is stubs") — every number stale, so a full rewrite. **The numbers are GENERATED:** `tools/progress.py --json`
  → `docs/progress.json` (schema 1: the four metrics with numerator/denominator/pct + a one-line "what", the counts — real
  360,737 / shared 255,632 / linked 1,256 / verbatim 5 / stubs 0 / non-matching 0 / matchable 363,214 / dedup 2,220 groups,
  255,708 instances — and 218 per-binary rows; no run date, so it never churns) and `--readme` rewrites the block between
  `<!-- progress:begin/end -->` (refuses a README without the markers — control run; `--check` asserts both are fresh);
  wired into `make report BINARY=main` after `--fleet`. README (144 lines): the claim and the contract · the generated block
  · what is NOT our C (1,256 Sony objects + 5 verbatim) · build from your own disc (the verification.md recipe, redump SHA1/
  CRC32, the EXE SHA1, the pinned triple, the optional SDK) · repository layout · how it was made (ProjectArchitect link,
  the governance files, the knowledge base) · **About the history** (the rewrite, the `commit:NNNN` tokens, `docs/commit-map.tsv`)
  · the license split · contributing + the no-ROM policy · **Special thanks** (the plan's list, sotn-decomp style) · the
  Square trademark line · 3 badges. **Forward references the README makes to files later tasks create** (D5's link checker
  must see them by then): `LICENSE`, `src/NOTICE.md`, `THIRD_PARTY.md` (D2); `docs/badges/fleet_instr.json`,
  `docs/badges/binaries.json` (D3 — these exact names); `docs/story.md` (F1), `docs/retrospective.md` (F2). Commit: see below.
- **2026-09-07 (S87, Max) — D2 LICENSE + NOTICE + THIRD_PARTY.** `LICENSE` = the AGPL-3.0 text fetched verbatim from
  `https://www.gnu.org/licenses/agpl-3.0.txt` (661 lines, 34,523 bytes — never retyped). `src/NOTICE.md`: a reimplementation
  for study/interoperability/preservation, © 1998 Square Co., Ltd. acknowledged, no affiliation, **no license asserted over
  `src/`**, "distributing the compiled output is distributing the game's code — don't", what the repo does not contain; the
  phrase "clean-room" appears nowhere (grep = 0). `THIRD_PARTY.md`: 17 rows, every license read from the upstream source of
  truth — the submodules' on-disk LICENSE files (maspsx MIT, decomp-permuter MIT, asm-differ Unlicense, m2c GPL-3.0),
  brave-CUE's `license.txt` (GPL-3.0; the compiled `brave.exe` purged from history), and the GitHub API's license metadata
  for the rest (splat/spimdisasm/rabbitizer MIT, Ghidra Apache-2.0, GhidrAssistMCP MIT, PCSX-Redux GPL-2.0 — psyq-obj-parser
  is part of it; **old-gcc and ghidra_psx_ldr publish NO license file** → stated as such, download-only; the SDK proprietary and
  never distributed; the AP world cited as facts). `tools/README.md` (new): the one AGPL statement for `tools/`, no per-file
  SPDX headers. **For Drew:** `docs/history/project_architect_v1.3.0.md` is KEPT as the historical record of the framework
  version used (THIRD_PARTY row links the repo) — say if you prefer link-only. Commit: see below.
- **2026-09-07 (S87) — D3 progress publishing.** `progress.py`: `weighted_metrics` now returns per-binary instruction totals
  (`per_bin`, from the existing loop), `--json` rows carry `instr_matched/instr_total` (main 45,150/45,150, resident
  4,483/4,483 — known-true check), and `docs/badges/{fleet_instr,fleet_fn,distinct,binaries}.json` are written in the shields
  endpoint format; `--check` also asserts the badges (control: a mutated badge → STALE). `make audit-digest` runs
  `progress.py --json --readme --check`. `tools/objdiff_report.py`: report.proto v2 (snake_case) — 218 units all complete,
  code 53,968,452/53,968,452 bytes (= 13,492,113 × 4, reconciles), functions 363,214/363,214, categories `game-code` +
  `linked-sony-objects`; **validated with the real `objdiff-cli` 3.8.1** (`report changes a a` parses and reports no change;
  a mutated unit is reported — control) — its `changes` takes POSITIONAL previous/current. `tools/frogress_upload.py`: dry run
  prints the payload (git_hash, timestamp, the measures with denominators); `--push` needs `FROGRESS_API_SECRET`.
  `.github/workflows/progress.yml`: converts the committed JSON, uploads `SLUS_007.26_report` (no rebuild in CI). SETUP: 3
  inventory rows + a P33 D1–D3 section (R21). Outward (Drew, after the flip): decomp.dev registration, frogress slug + key.
  Commit: see below.

## 🛑 SESSION CHECKPOINT — A1–A5 ✓, B1–B9/C3 ✓, C1–C9 ✓, D1–D3 ✓; C10 IN PROGRESS ON DREW'S SIDE (the Support ticket + the daily probe); NEXT = D4 (2026-09-07 ~08:20 UTC, written by session fa49faf3 "S87" after the D3 commit; SUPERSEDES the earlier blocks)

### 0. How to use this block
You are a FRESH SESSION that has read `PROJECT_CONTEXT.md`, `phase-ends/DIGEST.md`, `PhaseEnd_Phase30/31/32.md` and this file,
and nothing else (R64). Replay this block verbatim, state phase / done / NEXT / effort, list the rules from the digest
(R1–R73), then WAIT for Drew. **NEXT = two tracks.** **Drew (C10):** open the GitHub Support ticket (text in `docs/public-flip-runbook.md` §11), then run `tools/public_rewrite/probe_github.sh` daily (gh is authenticated in WSL; 31 of 33 sampled old hashes were alive at S87's baseline) until it prints PASS — only then the visibility flip, and only after Blocks D/E/F have landed. **Claude (NEXT = D4, xHigh): the SETUP.md public-clean pass** — header date; §2.3/§2.4 → download-only wording (drop the "vendored zip" lines the plan cites at 16-17/861-862 — grep `vendored`); §4.4 a generic dump path; §4.7 the tarballs; §4.8 + §5.6 PsyQ = user-supplied; §6.5 → the decomp.me preset (E1); the "Backup & private-repo posture" section → the PUBLIC posture (R1/R20 historical; the archive repo; `config/ghidra/` as R20's home — the P33 paragraph is already there, the private-era prose above it is not); ledger rows 11/14 closed; an R21 row for every P33 tool (audit against `git log --diff-filter=A --name-only <P33 range> -- tools/`); every `gitignored|private|curated public mirror|two-repo` mention reviewed line by line. Then D5 (governing docs + `tools/doc_links.py`) → F1 → F2 → F3 → E3 → E4 → E5 → E6; E1/E2 and D3's outward actions after the flip. **Every commit cites NEW hashes only; `.run/public_rewrite/` (scratch: dict, mailmap, old-to-new, bundle 556 MB, the rewritten bare clone) holds the old ones — keep until the probe passes, then delete (C11).**
one TaskCreate per plan item A1…G2, 40 items, mark A1–A5 + B1–B9/C3 + C1–C9 + D1–D3 completed; R28). The SessionStart hook restarts the headless
MCP server when `ghidra/bfm.rep` exists (it did not stay up in S87 — `ss -tln` showed nothing on :8080; harmless): B6/B7/B8
need no Ghidra; run `tools/ghidra_mcp_stop.sh` before any headless step (R23).

### 1. Where we are
**Phase 33 — 100% verification + the public flip + Gen2 exit.** Gate 1 approved 2026-09-06 (plan mode, Max). R65–R73 ratified.
**Done: A1 (`73068f39f`), A2 (`b23300fc2`), A3 (`4bb29544a`), A4 (`62854caca`), B1 (`026571291`), B2 (`9be6364a5`), B3
(`89e087f52`), B4 (`707ec491e`), B5 (`936d7d741`), B6 (`d37953732`), B7 (`6732771fe`), B8 (`b2fb392ad`), A5 (`1e3ce6c1c` prep + `8845fdd99`/`3e0ecfacc` fixes + `19832e169`), B9/C3 (`2b45081b5` — 251 index entries removed), C1 (`fca383904`), C2 (the S87 `chore(phase-33): C2 …` commit).** The approved plan is
VERBATIM at the end of this file — Blocks A–G give every task's files, commands and verification; "Execution order and why"
is the sequence. Effort: Drew ran S87 at **medium** by explicit choice (the plan says Max for B5); the plan's annotations
still stand for the tasks ahead — restate them, Drew decides (R7/R27).

### 2. Facts measured that every task depends on (do not re-derive; verify if in doubt, R14)
- **History / purge set / citations / identities / build facts / external facts:** unchanged from the S86 block — see the
  Log entries and the Approved plan (C1–C7 carry the numbers: main 4,011 commits, `--all` 4,282, 711 resolving hex
  citations, the purge paths and the two ghidra-ext zip sha256s `983e2add…` / `dc57cf1a…`, `brave.exe` `fdc9f486…`, the
  Gmail identities ×3,816/×162, the empty commit `133c1d45a`, the purge-only commit `commit:1712`).
- **Ghidra (B5, PROVEN S87):** the RE work is text now — `config/ghidra/{SLUS_007.26,resident,ov_SC01_077,ov_SC06_018,
  sep8_SLUS_007.26,aug31_USA_DEMO.EXE}.jsonl` (145 rows; only main carries hand-authored rows: 38) + `ROSTER.md`
  (`tools/ghidra_roster.py`, `--check` in tools-health). `tools/ghidra_rebuild.sh <prog> --proof` rebuilds from disc +
  symbol files + that file and `cmp`s (all six PASS, ≈65 s raw / ≈200 s EXE; needs `~/ghidra_12.1_PUBLIC`, the psyq400.gdt
  in the psx_ldr extension, the built ELF, the extracted payload — protos need `extracted/proto/*` from
  `tools/bfm_extract/extract_proto_exe.py`). The delta filter's three drift classes are documented in SETUP (P33 B5). The
  live `ghidra/` project is untouched and still on disk (leaves git at B9/C3; the archive repo keeps its history).
- **Verification state:** **A5 PASS on `3e0ecfacc`** (`.run/P33/verify/SUMMARY.md`: 218/218 clean fleet, sdk-dual both legs,
  tools-health OK with 0 PHANTOM/TRUNCATED/PAD-TAIL and zero warns, UNCLAIMED 0, report 100.00/100.0/100.0, stubs 0, backlog 0).
  C8 re-runs it on the adopted (rewritten) tree; a `--cached` removal (B9/C3) changes no tracked-content bytes.
- **Environment:** the purge set is IGNORED-BUT-PRESENT on disk since C3 — never `git clean -x`; **`gh` IS authenticated in WSL as Druthulu since C4b (token in `~/.config/gh/hosts.yml`; `gh auth logout` at C11)** and git uses it for github.com; `git-filter-repo` 2.47.0 in the venv; no linked worktrees remain (`git worktree list` = 1); the repo-local identity is the noreply address; disk ≈ 24 GB free of 75 (`.run/` 38 GB —
  `build/ghidra_rebuild/` and `.run/ghidra_rebuild/` are scratch, ~1 GB, safe to delete); no `/tmp` (R12).
  `.run/ghidra_export/` (139 MB, 129 live exports from S86) is the input for any future re-derivation of a candidate.

### 3. NEXT — in order
0. **Preflight:** `git status --short | grep -v ghidra/` (empty) · `git log -1 --format='%h %s'` · `df -h ~`.
1. **C10** (Drew; decision Max): the Support ticket (text in `docs/public-flip-runbook.md` §11), then `tools/public_rewrite/
   probe_github.sh` daily until PASS (gh auth done in S87; `old-to-new.tsv` + `old_tag_tip.txt` in scratch); the flip only
   after the probe passes AND Blocks D/E/F have landed.
2. **D4 — SETUP.md public-clean pass** (xHigh; see the NEXT line above). Then **D5**: CLAUDE.md:61 wording (true again),
   `.gitignore` header, `dumps/INDEX.md:8`, `docs/roadmap-to-100.md` §1 → a dated "status at P33" block, `docs/gen2-roadmap.md`
   Phase-14 → a "SUPERSEDED at P33" banner, `phase-ends/DIGEST.md` §0/§1/§3 (H1 re-tightened, R1/R20 historical, the
   PROJECT_CONTEXT corrections, R65–R73 full text — already there), `docs/backlog.md` (0 rows — done); NEW `tools/doc_links.py`
   (relative link/path checker over README, THIRD_PARTY, SETUP, verification, the runbook, the wiki; in tools-health) + a
   line-by-line grep review for `gitignored|private|curated public mirror|two-repo`.
3. Aftercare reminders (C11): `gh auth logout` in WSL after the flip; `git remote remove archive`; other clones reset, never
   pull; `.run/public_rewrite/` deleted after the probe passes (keep the bundle off-machine if wanted).
### 4. Files S87 touched
D3: `tools/progress.py` (per_bin, badges, --check), `docs/badges/*.json` (4, new), `docs/progress.json`, `tools/objdiff_report.py` (new), `tools/frogress_upload.py` (new), `.github/workflows/progress.yml` (new), `Makefile` (audit-digest), `docs/SETUP.md`. Scratch: `.run/objdiff/` (the objdiff-cli 3.8.1 validator + reports). D2: `LICENSE` (new), `src/NOTICE.md` (new), `THIRD_PARTY.md` (new), `tools/README.md` (new). D1: `README.md` (rewritten), `docs/progress.json` (new, generated), `tools/progress.py` (`--json`/`--readme`/`--check`), `Makefile` (report wiring). C9: `tools/public_rewrite/probe_github.sh` (422 = gone), `docs/public-flip-runbook.md` §10/§12; `.git` (the archive remote removed, 12 worktrees removed, repacked to one 80 MB pack). C8: `.run/P33/verify/*` (the recorded run, tracked), `docs/verification.md` §2, `docs/family-hseq.md`, `tools/verify_contract.sh` (the step-00 fix). C4–C7: `docs/commit-map.tsv` (new), the 98 token-resolved files (see the C7 entry), `tools/public_rewrite/resolve_tokens.py` (the skip rule), `.git/config` (repo-local noreply identity). Scratch `.run/public_rewrite/`: `pre-rewrite.bundle`, `repo.git` (the rewritten bare clone, keep until C9), `c4c5.{sh,log}`, `old-to-new.tsv`, `unchanged_commits.txt`, `old_tag_tip.txt`, `c5_commit-map.tsv`, `ids_after.txt`, `refs_*.txt`. C1: `tools/public_rewrite/{common,hash_dict,scrub,gate_scan,run_filter,verify_rewrite,build_commit_map,resolve_tokens,absent_scan}.py`, `probe_github.sh`, `expected_offenders.txt` (all new), `requirements-python.txt`, `docs/SETUP.md`, `docs/public-flip-runbook.md`. Scratch `.run/public_rewrite/`: `dict.json`, `mailmap`, `rom_blob_ids.txt`, `old_tag_tip.txt`, `trial*.{sh,log}`, `trial_commit-map.tsv`, `trial_old-to-new.tsv`, `unchanged_commits.txt`, `nonpurge_blob_ids.txt`, `filter.log`. B9/C3: 251 index removals (files on disk), `docs/public-flip-runbook.md` (new), `docs/SETUP.md` §2.3/§2.4, `docs/verification.md`, `CLAUDE.md`, `docs/decision-log.md`. A5: `tools/verify_contract.sh` (new), `tools/audit_frontier.py` (derived denominator lines), `.gitignore` (the `.run/P33/verify/` allowlist), `.run/P33/verify/*` (tracked evidence), `docs/verification.md` §2, regenerated `docs/family-hseq.md` + `docs/progress*.md`/`duplicates*.md`. B8: `docs/verification.md` (new), `docs/SETUP.md` (§4.4/§4.6/§4.8/§6.3 pointers, backup posture). B7: `.github/workflows/no-rom.yml`, `tools/audit_public.py`, `tools/compile_only.py`, `tools/public_rewrite/purge_set.txt` (all new), `docs/SETUP.md`. B6: `dumps/CHECKSUMS.sha1` (new), `dumps/INDEX.md`, `docs/memory-map.md`. B5: `tools/ghidra_scripts/ImportAnnotations.java` (3 compile fixes + the `/undefined` resolver), `tools/ghidra_rebuild.sh`
(`.proof` markers; dies unless `failed=0`), `tools/ghidra_annotations_delta.py` (the three drift classes), new
`tools/ghidra_roster.py`, `tools/ghidra_mcp_start.sh` (silent no-op guard), `.claude/settings.json` (relative hooks),
`Makefile` (roster check in tools-health), `docs/SETUP.md` (P33 B5 section, 5 inventory rows, §2.8), `config/ghidra/*`
(new, 7 files), this file. Scratch: `.run/ghidra_rebuild/` (baselines, candidates, `proof_*.log`, `.proof`, the two chain
scripts `b5_controls.sh`/`b5_proofs.sh` + logs), `build/ghidra_rebuild/` (the scratch project, wiped by `make clean`).
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
  main has one pre-existing empty commit `133c1d45a` that must survive; `delete-no-add` so no `refs/replace/<old>`
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
