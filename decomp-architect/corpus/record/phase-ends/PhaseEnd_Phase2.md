# PhaseEnd — Phase 2: Deterministic disc & .CD extraction pipeline
**Date:** 2026-06-13 · **Project Version:** 1.2.0 · **Phase Status:** Complete

## Build Log

**Files created/changed and complete — do not recreate:**
- `tools/bfm_extract/extract.py` — unified full-disc CLI. Walks the ISO root (over the frozen `iso9660.Iso9660Image`), writes every file, splits `.CD`→PAC→type-4, writes the manifest; `--list` / `--verify`. Composes `cd_archive` + `pac` + `lzss` + `manifest`; reuses `extract_exe` EXE constants. Also contains the multi-track `AudioTrack` reader for the 3 `.DA` files.
- `tools/bfm_extract/cd_archive.py` — `.CD` TOC walker (`parse_toc`, `iter_subfiles`) + `classify_subfile` (pac/sqv/raw). Excludes LIST.CD by caller contract.
- `tools/bfm_extract/pac.py` — PAC chain splitter (`is_pac`, `split_pac`); `{index}.{type}` model with `+0x08` and full-header capture.
- `tools/bfm_extract/lzss.py` — game-semantics LZSS decoder (`pos==0` terminator, −1 bias, length cross-check). Pure function; ring re-zeroed per call.
- `tools/bfm_extract/test_lzss.py` — 5 standalone synthetic unit tests (literals, terminator, −1 bias, overlapping copy, cross-check warnings).
- `tools/bfm_extract/manifest.py` — deterministic JSON-Lines manifest (`build`/`render`/`write`/`verify`); `manifest.jsonl` + `manifest.sha1`.
- `tools/bfm_extract/crosscheck.py` — CUE `brave` oracle harness: builds brave, maps type-only names → `{index}.{type}`, byte-compares, classifies F6/shadowed, writes `_build/divergence.log`.
- `tools/brave-CUE/posix_shim.h` — glibc build shim (`filelength`→`fstat`; 1-arg `mkdir` macro) so the GPL `brave.c`/`common.inc` compile **unmodified**.
- `tools/bfm_extract/extract_exe.py` — added `EXPECTED_EXE_SHA1` constant (round-trip anchor).
- `.gitignore` — `/extracted/*` + `!`-exceptions for `SLUS_007.26`/`manifest.jsonl`/`manifest.sha1`; `/tools/brave-CUE/_build/`.
- `docs/SETUP.md` — §4.4 note: disc staged on ext4 (Phase 2), WSL `--verify-disc` PASS (closes Phase-1 deferral).
- `docs/formats.md` — §2.2 verified US sub-file counts; §3.1 `+0x08` finding; §3.2 type distribution; §4.4 F6 resolution; §5/§7 SQV/.DA; §8 F1/F2/F4/F5/F6/F7 status + Phase-2 summary block.
- `CLAUDE.md` — Reasoning & Model Protocol: corrected the "Ultracode is an effort level" error; added the Effort-map check rule (→ R7); Session Start now states next-task effort.
- `docs/effort-map.md` — **new** evolvable reference: verified effort mechanics, two-axis depth/breadth model, Max-default policy, per-phase Gen1 map.
- `phase-ends/CURRENT_PHASE.md` — **absorbed into this file and deleted** (P8).

**Local artifacts (gitignored / outside the repo — present on this machine, do NOT recreate; a fresh clone must redo them):**
- `disks/Brave Fencer Musashi (USA) (Track 1..4).bin` + `.cue` — all 4 tracks copied once from `/mnt/z` (Track 1 = 364,846,944 B; tracks 2-4 = CD-DA audio). Gitignored.
- `extracted/` bulk — 1801 artifacts (raw `.CD`, `FILE_%03d`, `{index}.{type}`, `.dec`, FMV, `.DA` audio). Regenerable via `extract.py`. **Committed** subset: `manifest.jsonl`, `manifest.sha1`, `SLUS_007.26`.
- `tools/brave-CUE/_build/brave` (+ `divergence.log`) — compiled oracle + scratch (gitignored).

**Tools/packages installed:** gcc 13.3.0 (`Ubuntu 13.3.0-6ubuntu2~24.04.1`) — to build the `brave` cross-validation oracle (user-approved; `build-essential` is a Phase-4 dependency regardless).

**Verification results (literal):**
- LZSS unit tests: **5/5 pass**.
- `extract.py`: 27 files (24 Track-1 verbatim + 3 `.DA` raw CD-DA audio); 447 sub-files, 348 PAC chains, **1189 PAC entries** (138 type-4 decoded, **0 LZSS warnings**), 98 SQV. **EXE round-trip PASS** (SHA1 `143dbb89f34491258bbc27810d0a12ec8b43a8dd`).
- Manifest: **1801 artifacts**; `manifest.sha1 = e5c6019249dec3c71bb2cf40658a78439dddb037`; **identical across re-runs** (deterministic); `--verify` **PASS**.
- `crosscheck.py --sample all` (brave built with gcc): **1484 raw payloads byte-identical** (0 diff); **138/138 type-4 F6** (ours = the game-correct prefix; brave over-decodes exactly 2 B per stream = 276 B total); **0 raw mismatches, 0 decode mismatches — PASS**. 14 "shadowed" entries in MAIN.CD confirm the brave naming collision our `{index}.{type}` fixes.
- `git status`: only tooling/docs/manifest tracked; bulk payloads + `_build/` ignored (**zero ROM-derived files staged**).
- Open-question results: **F5** US counts (MAIN=49, SC01=86, **SC02=43**, SC03=140, SC04=31, SC05=30, SC06=39, SC07=29); **F2** `+0x08`=0 for all type-4 (size-hint refuted; non-zero only type 0=301, type 6=29); **F1** type 7=139 (common), no type 5; **F6** resolved (no within-payload divergence).

**Milestone achieved:** `python3 tools/bfm_extract/extract.py` extracts the full disc in one command, MAIN.CD yields its 49 sub-files, the decompressed type-4 payloads are byte-identical to CUE's `brave` up to the game `pos==0` terminator (138/138), the SHA1 manifest is deterministic, and `git status` shows zero ROM-derived files staged.

**Next:** Phase 3 — File-loader & overlay-map RE (+ PCSX-Redux harness). Start with Ghidra seeded with the provenance-tagged ledger from `docs/memory-map.md`. (Phase 3 is RE work — MCP precondition G2 applies; and per `docs/effort-map.md` the US address derivation + RAM-dump proof are **Max** tasks.)

## Deviations
| Item | Plan | Actual | Reason |
|---|---|---|---|
| Disc staging | Track 1 only | All 4 tracks + `.cue` staged on ext4 | User directed extracting the `.DA` files, whose data lives in tracks 2-4 |
| `.DA` files | Out of scope / skip | Extracted as raw 2352-B/sector CD-DA audio (tracks 2-4) | User "extract every byte"; `.DA` ISO entries point past Track 1 into the audio tracks |
| Cross-val tool | brave.exe (Windows) via wibo/wine | Build `brave.c` from source via `posix_shim.h` (gcc) | Cleaner than Wine; GPL upstream untouched; gcc is a Phase-4 dep anyway (user-approved early install) |
| Commit cadence | One commit per task (P4/R6) | One commit at phase end | User directive 2026-06-13 (→ rule R8) |
| Effort-map work | (not in the phase plan) | Added `docs/effort-map.md` + R7 + CLAUDE.md correction at session start | User requested before planning the phase |
| F4 (LIST.CD regen) | Resolve during the run | Deferred (extractor excludes LIST.CD; regen+diff is a cheap follow-up) | Optional; not a milestone item |
| Output tree | (raw split only) | Keep raw `.CD` + raw sub-files + `{index}.{type}` + `.dec` (all gitignored bulk) | Faithful "every byte" + diffable-against-brave structure |

## Commit Message
```
feat(phase-2): deterministic disc/.CD/PAC/LZSS extraction pipeline

- extract.py: one-command full-disc extraction (27 files: 24 Track-1 verbatim
  + 3 .DA as raw CD-DA audio from tracks 2-4) over the frozen iso9660.py
- cd_archive.py + pac.py: .CD TOC walker + PAC splitter, {index}.{type} naming
  (no collisions; 447 sub-files, 1189 entries), SQV detection (98)
- lzss.py: game-semantics decoder (pos==0 terminator, -1 bias) + 5 unit tests;
  138 type-4 decoded clean (0 warnings)
- manifest.py: deterministic JSON-Lines manifest (1801 artifacts) + --verify
- crosscheck.py + tools/brave-CUE/posix_shim.h: build CUE's brave from source
  (GPL untouched), byte-compare; 1484 raw identical, 138/138 type-4 F6
- docs/formats.md: F5 counts (SC02=43), F2 refuted, F6 resolved, F1 type-7=139
- docs/effort-map.md + CLAUDE.md: Effort-map check rule (R7), Ultracode fix
- .gitignore: /extracted/* + !manifest/EXE exceptions; brave _build/
- install gcc 13.3.0 for the oracle
- milestone: one command extracts the full disc; MAIN.CD=49 sub-files; decoder
  agrees byte-for-byte with CUE up to the game pos==0 terminator; zero ROM
  staged; project version 1.1.0 -> 1.2.0
```

## Rules Added This Phase
| Rule | Reason |
|---|---|
| **R7 — Effort-map check.** Before each Phase Start, state the recommended effort for planning that phase per `docs/effort-map.md` and confirm the developer has it set; annotate every task in the plan with its effort; restate the recommended effort whenever presenting the NEXT task. `docs/effort-map.md` is the evolvable source of truth (it also records the verified harness mechanics: effort ladder `low..xHigh/Max`; Max & Ultracode are session-only; Ultracode = xHigh + multi-agent orchestration, not a deeper level). | User requested a persistent effort guide and noticed Ultracode "reverting to xHigh"; corrects CLAUDE.md's mislabeling of Ultracode as an effort level. |
| **R8 — One commit at phase end (supersedes the per-task-commit part of P4/R6).** Work accumulates UNCOMMITTED during a phase; `CURRENT_PHASE.md` is the per-task crash-recovery log; a single commit lands at phase close. The user commits AND pushes it (R6 phase-boundary exception, extended to the whole phase). | User directive 2026-06-13 — fewer commits to manage with the WSL-commit / GitHub-Desktop-push workflow. |

## PhaseEnd Changelog
**v1.1.0 → v1.2.0** — Phase 2 complete. The deterministic disc/.CD/PAC/LZSS extraction pipeline is live (pure-stdlib Python over the frozen `iso9660.py`): one command extracts the full disc into 1801 manifest-tracked artifacts; the game-semantics LZSS decoder decodes all 138 type-4 overlays cleanly and is byte-validated against CUE's `brave` (built from source). Open questions resolved: F5 (US sub-file counts, SC02=43), F2 (`+0x08` is not a size hint), F6 (no within-payload game/tool divergence); F1 partially (type 7 common). Two rules added (R7 effort-map check, R8 one-commit-at-phase-end). gcc 13.3.0 installed. Deviations: all 4 tracks staged + `.DA` extracted as raw audio (user scope change).

## 🛑 Stop Here
Start a fresh session for the next phase. Keep this file forever.
