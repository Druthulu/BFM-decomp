# CURRENT_PHASE — Phase 9: Binary-Agnostic Toolchain Refactor

**Status:** IN PROGRESS (plan approved 2026-06-15, gate 1 passed) · **Target version:** 1.8.0 → 1.9.0
**Effort:** planning was Max (Tier 1); execution = xHigh (Tier 2; Tier-3 for report scripts).
**Plan of record:** `/home/musashi/.claude/plans/confirmed-max-effort-plan-cryptic-cherny.md` (full design).

## Oracle (the regression gate after EVERY task)
- **Build no-op:** `make clean && make extract && make build` ⇒ `SHA1 143dbb89f34491258bbc27810d0a12ec8b43a8dd` (BYTE-IDENTICAL).
- **Report no-op:** `make report` ⇒ REAL **52** / LINKED **959** / NON_MATCHING **7** / 50.24%.
- **Fresh-clone fallback:** at T1/T5/T10, also verify byte-identical with `.run/obj40/` moved aside (stub path).
- **Negative control:** wrong `--vram-base`/window ⇒ build must FAIL or diverge from 143dbb89 (manual, never committed).
- **R22:** byte checks from a CLEAN rebuild only.

## Baseline established (2026-06-15, before any change)
- ✅ with-SDK build: `143dbb89…` BYTE-IDENTICAL · `make report` 52/959/7/50.24%. `.run/obj40/*` present on this machine.

## Architecture (locked, gate-1 approved)
1. Alias-key Make namespacing: `BINARIES := main` + `main_*` vars; `make build [BINARY=main]`; default = EXE.
2. Preserve the EXE's exact artifact paths as `main`'s values — NO renames. Clean `<bin>` convention documented now, first instantiated by Phase 10.
3. No new config-file format — Make vars + existing splat yaml.
4. Required params, no EXE defaults; threaded leaf-first (psyq_link → identify → link_region → integrate) so misses fail loud.
5. `--vram-base` = single fileoff→vram scalar (EXE 0x8000F800); text window is orthogonal.
6. Scope = de-risked middle. 7. Commits = per-tool checkpoints (I commit in WSL; Drew pushes).

## Tasks (one commit per task, each gated green by the oracle)
- [x] **T1** — Makefile data block (BINARIES/main_*/aliases; wrapped 9 integrate blocks in `ifeq ($(BINARY),main)`). DONE: aliases resolve byte-identically; `BINARY=bogus` errors; clean build ⇒ `143dbb89` + report 52/959/7/50.24%. **Refinement vs plan:** SDK-region vars (LIB*_ELF…) left un-namespaced — they're already main-only by the ifeq gate; namespacing deferred to when a 2nd binary needs SDK regions (avoids speculative churn, consistent with de-risked scope). `report` target unchanged (tools learn `--binary` in T5/T6).
- [x] **T2** — `psyq_link.py` [A1]: threaded `vram_base`/`exe_path` through recover_sym_addrs/unique_byte_vram/link_object (DEFAULT to kept EXE globals — transitional, removed T8); argparse CLI `--vram-base`/`--exe`. DONE: negative control — TOC.o `--vram-base 0x8000F800`⇒PASS, `0x8000F900`⇒FAIL (.rdata shifted +0x100, proving threading); defaults⇒PASS; clean build ⇒ `143dbb89`.
- [x] **T3** — `psyq_identify.py` [A2]: argparse `--vram-base`/`--exe` (default to kept globals, transitional); window stays optional positional. **Caller argv updates deferred to T4/T8** (one-touch-per-file; psyq_identify's defaults keep them green). DONE: narrow window 0x50000..0x60000 ⇒ 0/25 located (window threaded); default + explicit ⇒ 18/25; clean build ⇒ `143dbb89`.
- [x] **T4** — `psyq_link_region.py` + `psyq_link_lib.py` [A3]: threaded vram_base/exe through build_region/placement/classify (+ link_lib); pass `--vram-base`/`--exe` to psyq_identify argv; argparse mains. **VRAM_BASE import KEPT** as transitional default source (removed T8, not dropped now — lower churn, consistent). DONE: link_lib libcd 18/18; wrong base ⇒ 6/18 (threaded); link_region byte-identical True; clean build ⇒ `143dbb89`.
- [x] **T5** — `psyq_integrate.py` + `progress.py` + Makefile (ONE COMMIT) [A4+B1]: integrate argparse (flags before positionals, `nargs="*"` window) threads vram_base/exe/symbols; 9 Makefile call sites pass `--vram-base/--exe/--symbols $(main_*)`; progress regex `(?:\s+--\S+\s+\S+)*` consumes leading flags + `--binary` selector. DONE: positive `143dbb89`; report 52/**959**/7/50.24% (regex OK); **negative** main_VRAM_BASE=0x8000F804 ⇒ `cae22f7e`≠target; **without-SDK fallback** ⇒ `143dbb89`.
- [x] **T6** — `dup_report.py` + `difficulty.py` [B2+B3]: argparse `--binary` (default main) + BINARIES table; Makefile `report` threads `--binary $(BINARY)`. DONE: progress.md + duplicates.md UNCHANGED (pure no-op); difficulty.md old-code==new-code output (proven) ⇒ its 12/12 diff is the **Phase-8 deferred regen** (9 harvested fns left the queue) — regenerated + committed here (resolves the Phase-8 deferral). Build untouched (report-only).
- [x] **T7** — `ld_interleave.py` [C3]: argparse `--front`/`--tail`/`ld` (EXE defaults, transitional); `extract` recipe gates the call under `ifeq ($(BINARY),main)` + passes `--front 53198.data.o --tail 6324C.data.o`. DONE: positive (extract path) ⇒ `143dbb89` (tail_data=1 from the flag); negative `--tail BOGUS.data.o` ⇒ "tail data object not found" exit=1 (threaded); restore ⇒ `143dbb89`.
- [x] **T8** — DONE (two commits). **T8a** [C1/C2/E1/D]: make_snd_used/make_apicard_used/gen_lib_subsegs (`--vram-base`/`--exe`) + split_src_region (`--symbols`) de-defaulted, thread to pipeline; curated dirs regenerate BYTE-IDENTICAL; gen_lib_subsegs libgte=22 blocks. **T8b** [no-EXE-default end state]: removed transitional EXE/VRAM_BASE globals + all `=VRAM_BASE`/`=EXE` param defaults across psyq_link/identify/link_region/link_lib/integrate → `--vram-base`/`--exe`/`--symbols` REQUIRED. PROOF: `psyq_link.py <obj> <vram>` (no flags) ⇒ argparse "required: --vram-base, --exe" (loud); with-SDK + without-SDK builds ⇒ `143dbb89`; wrong base ⇒ `cae22f7e`; curation regen identical.
- [x] **T9** — `diff_settings.py`: `BFM_BINARY` env-var selector + BINARIES table (asm-differ owns apply() signature; env var is the seam). main = current EXE images. DONE: apply() unit test (main→EXE paths; bogus BFM_BINARY→loud error); `make expected` baseline set; asm-differ `-o func_80018F20 --format json` ⇒ current_score=0 (MATCH).
- [x] **T10** — Docs: SETUP §6.7 (binary-agnostic toolchain + future-binary convention, R21), cookbook §9.7 (the reusable refactor pattern, R16), psyq-worklist recipe (flags), README status (52 REAL / 959 LINKED / 50.24% / Gen2-underway). `make expected` refreshed. **FINAL MILESTONE PROOF (all green):** (1) with-SDK ⇒ `143dbb89`; (2) report 52/959/7/50.24%; (3) without-SDK fallback ⇒ `143dbb89`; (4) negative `main_VRAM_BASE=0x8000F804` ⇒ `cae22f7e`≠target; (5) restore+expected ⇒ `143dbb89`.

## 🎯 MILESTONE ACHIEVED (awaiting Drew gate-2 confirm)
The binary-agnostic toolchain rebuilds `SLUS_007.26` byte-for-byte (`143dbb89…`) through the fully
parameterized path **with AND without** the SDK objects; `make report` reproduces the Phase-8 counts
exactly; every binary-specific value is a REQUIRED param (no EXE default) — proven load-bearing by the
negative control. A pure behavior-preserving no-op; the toolchain is ready for Phase 10's resident blob.
**Next:** Drew confirms gate 2 → PhaseEnd_Phase9 (Tier-1) → v1.9.0.

## Transitional-default technique (T2–T8) — keeps every commit green despite in-process coupling
`psyq_integrate`/`psyq_link_region` import `VRAM_BASE` + `recover_sym_addrs`/`classify`/`placement` from
`psyq_link` IN-PROCESS, so removing the global in T2 alone would break the build. Instead: T2–T7 add
`vram_base`/`exe` params that DEFAULT to the kept EXE globals (build stays byte-identical as callers are
updated one commit at a time); **T8 removes the globals + all defaults → required params (no-EXE-default
end state)** once every caller passes explicitly. Negative control still bites at each gate (it passes an
explicit *wrong* value, which IS used). Defaults are EXE values, never shipped to an overlay (Phase 10
starts post-T8). This is the standard safe-refactor-of-a-shared-global pattern.

## Blockers / notes
- The SessionStart hook started the Ghidra MCP server (:8080); harmless for this phase (build/report tools are Ghidra-free; `sig-refresh` not used). Commit ONLY refactor files explicitly (never `git add -A`) so Ghidra DB churn (db.*.gbf) stays out of refactor commits.
- After each task: update the checkbox + a one-line result here (P3 crash-recovery log).
