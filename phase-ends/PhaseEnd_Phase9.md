# PhaseEnd — Phase 9: Binary-agnostic toolchain refactor
**Date:** 2026-06-15 · **Project Version:** 1.9.0 · **Phase Status:** Complete · **Generation:** Gen2 (2nd phase)

> Gen2 phase 2 of the arc (8→**9**→10→11→{12,13}→14). The granular per-task trail (per-tool edits,
> exact gates, the transitional-default reasoning) is preserved on-demand at
> **`phase-ends/logs/Phase9.md`** (R19 — NOT auto-loaded; consult only when researching a mechanism).
> Owner decisions (2026-06-15): scope = **de-risked middle**; commits = **per-tool checkpoints**;
> at phase-end **stop the Ghidra MCP + commit the DB** (option a → R23).

## Build Log

**Files created/changed and complete — do not recreate:**

*The refactor pattern (locked, gate-1 approved):* alias-key Makefile namespacing (`BINARIES := main` +
`main_*` vars + `$(BINARY)`-resolved aliases, borrowing `match_protos.py`'s idiom); EXE artifact paths
**preserved verbatim** (no rename churn against the byte oracle); **no new config-file format** (Make vars
+ existing splat yaml); **required params, no EXE default** threaded **leaf-first**; `--vram-base` a single
fileoff→vram scalar (window is orthogonal).

*Makefile (T1, T5, T6, T7):* the data-driven `BINARIES`/`BINARY ?= main` block + `$(filter)` guard + the
`main_*` set (paths/`VRAM_BASE 0x8000F800`/`TEXT_LO/HI` preserved) + selected-binary aliases. The 9 PsyQ
`psyq_integrate` calls gained `--vram-base $(main_VRAM_BASE) --exe $(main_EXE) --symbols $(main_SYMBOLS)`
(flags before positionals) and are wrapped in `ifeq ($(BINARY),main)`; the `extract` `ld_interleave` call
likewise gated + `--front 53198.data.o --tail 6324C.data.o`; the `report` target threads `--binary $(BINARY)`.

*Link pipeline — `--vram-base`/`--exe` REQUIRED, no module globals (T2–T5, T8b):*
- `tools/psyq_link.py` — `recover_sym_addrs`/`unique_byte_vram`/`link_object` take `vram_base` (+
  `link_object` `exe_path`); module `EXE`/`VRAM_BASE` removed; CLI `--vram-base`/`--exe` required (argparse).
- `tools/psyq_identify.py` — argparse; `--vram-base`/`--exe` required; `[lo hi]` window optional positional.
- `tools/psyq_link_region.py` + `tools/psyq_link_lib.py` — thread `vram_base`/`exe` through
  `build_region`/`placement`/`classify`; dropped the `VRAM_BASE` import + `EXE`; pass `--vram-base`/`--exe`
  to the `psyq_identify` subprocess; CLI required.
- `tools/psyq_integrate.py` — `integrate()` `vram_base`/`exe_path`/`symbols_path` keyword-required; argparse
  (`nargs="*"` window) with `--vram-base`/`--exe`/`--symbols` before positionals; dropped `VRAM_BASE` import + `EXE`.

*Report scripts — `--binary` selector (T5, T6):* `tools/progress.py` (the Makefile `psyq_integrate`
stub-list regex updated **in lockstep** to consume leading `--flag value` pairs:
`psyq_integrate\.py(?:\s+--\S+\s+\S+)*\s+\S+\s+\S+\s+\S+\s+\S+\s+(\S+)`), `tools/dup_report.py`,
`tools/difficulty.py` — each gains `--binary <alias>` (default `main`) + a `BINARIES` path table.

*EXE-curation helpers — de-defaulted (T7, T8a):* `tools/ld_interleave.py` (`--front`/`--tail`/`[ld]`),
`tools/make_snd_used.py` + `tools/make_apicard_used.py` (`--exe`/`--vram-base`; region bounds/excludes kept
as EXE data), `tools/gen_lib_subsegs.py` (`--vram-base`/`--exe`; its own `VRAM_BASE` const removed),
`tools/split_src_region.py` (`--symbols`).

*asm-differ (T9):* `diff_settings.py` — `BFM_BINARY` env-var selector + `BINARIES` → `{baseimg,myimg,mapfile}`
(env var because asm-differ owns the `apply()` signature); `main` = the EXE images.

*Docs (T10, R16/R21):* `docs/SETUP.md` **§6.7** (the binary-agnostic toolchain: `make build BINARY=<alias>`,
the required flags, `BFM_BINARY`, and the future-binary path convention `config/splat.<bin>.yaml` /
`build/<bin>/` / `config/check.<bin>.sha` / `config/symbols.<bin>.txt` / `.run/sig.<bin>.jsonl`);
`docs/matching-cookbook.md` **§9.7** (the reusable Gen2 refactor pattern: required-params-no-default, the
transitional-default + leaf-first technique, the negative control, the progress.py regex lockstep gotcha);
`docs/psyq-worklist.md` (per-library recipe updated with the now-required flags); `README.md` (status →
52 REAL / 959 LINKED / ~50% / Gen2-underway); `docs/difficulty.md` regenerated (resolves the Phase-8
deferred regen — 9 harvested fns leaving the unmatched queue, old-code==new-code verified).

- `phase-ends/CURRENT_PHASE.md` → **`phase-ends/logs/Phase9.md`** (R19 archive). `phase-ends/PhaseEnd_Phase9.md` — this file.

**Local artifacts (gitignored / regenerable — a fresh clone redoes them):** `build/`, `expected/`, `asm/`,
the generated `include/` macros, `undefined_*_auto.txt`, `.run/obj40/*` (curated SDK dirs), `build/psyq/*`.

**Tools/packages installed:** None (used the existing Phase-4/6 toolchain entirely).

**Ghidra DB (R23, this phase):** the MCP server ran (SessionStart hook) but Phase 9 made **zero** RE writes
(pure build-tooling). At phase close the MCP was cleanly stopped (`tools/ghidra_mcp_stop.sh` — save + lock
release) and the current `ghidra/` program DB committed to reconcile git with disk (the tracked `db.12` →
the live `db.N`); content unchanged, a one-time ~10 MB reconcile + protocol bank.

**Verification results (literal) — the milestone proof (all green):**
- **(1) with-SDK** `make clean && extract && build` → `build/us/SLUS_007.26` SHA1
  `143dbb89f34491258bbc27810d0a12ec8b43a8dd` (BYTE-IDENTICAL).
- **(2) `make report`** → REAL **52** / LINKED **959** / NON_MATCHING **7** / **50.24%** (exact Phase-8 counts;
  the progress regex still parses all 9 stub lists through the new flags).
- **(3) without-SDK** (`.run/obj40` moved aside, fresh-clone stub fallback) → `143dbb89…` (BYTE-IDENTICAL).
- **(4) NEGATIVE CONTROL** `make build main_VRAM_BASE=0x8000F804` → `cae22f7ee81e534b4af83290750a8c4e7e651b70`
  (≠ target — proves `--vram-base` is load-bearing, not accepted-and-ignored). Per-tool: `psyq_link.py <obj>
  <vram>` with no flags → argparse `error: the following arguments are required: --vram-base, --exe` (loud).
- **(5) restore + `make expected`** → `143dbb89…` baseline refreshed.
- `git status`: only `config/`/`Makefile`/`tools/`/`src`-free docs tracked per commit; Ghidra DB reconciled
  at close; **zero ROM-derived/generated bulk staged** in the source commits.

**Milestone achieved:** The toolchain is **binary-agnostic** — `make build` rebuilds `SLUS_007.26`
**byte-for-byte (`143dbb89…`)** through the fully parameterized path **with AND without** the SDK objects,
`make report` reproduces the Phase-8 counts exactly, and **every binary-specific value is a required
parameter** (no EXE default an overlay could inherit) proven load-bearing by the negative control — a pure
behavior-preserving no-op. Confirmed by Drew (gate 2).

**Next:** **Phase 10 — Resident engine blob (splat config + all-asm byte-match).** Start a fresh session
(effort **Max**, plan mode). First target: the resident engine blob `MAIN.CD/FILE_010/1.1` @ vram
`0x800CEDF8` — author `config/splat.resident.yaml` + the `resident` `BINARIES` instance (clean `<bin>`
convention; its own `resident_VRAM_BASE`, **not** `0x8000F800`), build at 100% INCLUDE_ASM, SHA1-match the
extracted payload. The Phase-9 parameterized tools + the documented convention (SETUP §6.7) feed directly in.

## Deviations
| Item | Plan | Actual | Reason |
|---|---|---|---|
| T8 commit count | one commit | **split T8a + T8b** | in-process coupling: the no-default removal (T8b) can only land after the curation helpers (T8a) pass explicit args — two green commits |
| Default removal | "remove module globals in each tool's commit" | **transitional-default technique** (params default to kept globals T2–T7; removed → required at T8b) | `psyq_integrate`/`link_region` import from `psyq_link` IN-PROCESS — removing a global in isolation breaks the build mid-sequence; defaults keep every per-tool commit green, then a final hardening reaches the no-default end state |
| SDK-region Makefile vars | namespace under `main_` | **left un-namespaced** (LIB*_ELF…) | already main-only by the `ifeq ($(BINARY),main)` gate; namespacing a hypothetical future collision is speculative churn (de-risked scope) — deferred to when a 2nd binary needs SDK regions |
| `psyq_identify` caller argv | "update all callers in T3" | **distributed to each caller's own task** (T4/T8a) | one-touch-per-file; psyq_identify's transitional defaults kept callers green meanwhile |
| `ld_interleave`/curation `--exe`/`--vram-base` | "required" | **CLI-default to EXE values** (entry-point convenience) | these are EXE-curation tools / EXE-gated; they thread EXPLICIT values down to the now-required pipeline — the "no silent default" holds where it matters (the pipeline) |
| `difficulty.md` | not in plan | **regenerated** (committed) | the Phase-8 deferred regen surfaced; old-code==new-code output verified → the diff is the deferral, not a T6 bug |
| Ghidra DB at phase-end | (not anticipated) | **stop MCP + commit DB** (R23) | Drew raised the lock/backup gap: the `.rep` lock holds until MCP closes, and SessionEnd is too late for a mid-session phase-end commit |

## Commit Message
```
(Phase 9 landed as 11 per-tool checkpoint commits commit:0042..commit:0052 + this PhaseEnd.)

feat(phase-9): binary-agnostic toolchain refactor — one pipeline builds any binary (v1.9.0)

- Makefile: data-driven BINARIES (alias keys) + main_* vars + $(BINARY) aliases; EXE
  paths preserved verbatim; 9 psyq_integrate calls + ld_interleave gated ifeq(BINARY,main)
- link pipeline (psyq_link/identify/link_region/link_lib/integrate): --vram-base/--exe
  (+ integrate --symbols) REQUIRED, module EXE/VRAM_BASE removed, threaded leaf-first via a
  transitional-default technique (every per-tool commit byte-identical)
- reports (progress/difficulty/dup_report): --binary selector; progress regex consumes
  the new leading flags in lockstep. diff_settings: BFM_BINARY env selector
- curation helpers (ld_interleave --front/--tail; make_snd/apicard/gen_lib_subsegs
  --vram-base/--exe; split_src_region --symbols) de-defaulted
- docs: SETUP §6.7 + cookbook §9.7 (the reusable Gen2 pattern) + psyq-worklist recipe +
  README; difficulty.md deferred-regen resolved
- MILESTONE: EXE rebuilds 143dbb89 WITH and WITHOUT SDK objects; report 52/959/7/50.24%;
  wrong --vram-base -> cae22f7e (negative control); required params fail loud
- rule R23 (stop Ghidra MCP + commit DB at phase-end/RE-checkpoint); bumps 1.8.0 -> 1.9.0
```

## Rules Added This Phase
| Rule | Reason |
|---|---|
| **R23 — Stop the Ghidra MCP before any phase-end / RE-checkpoint commit; commit the DB if RE work changed it.** The headless MCP server holds the `.rep` lock with an open transaction — the saved program DB only materializes on a clean stop (`tools/ghidra_mcp_stop.sh`, which waits for *"Save succeeded"* + lock release). Phase-end/checkpoint commits happen **mid-session**, so the **SessionEnd** hook is too late — run `ghidra_mcp_stop.sh` explicitly first, then commit the current `ghidra/` DB (the live `db.N.gbf`) when RE work changed it. Between RE checkpoints, the `db.*.gbf` rename-on-save churn in `git status` is noise — don't commit no-op renumbers. Extends R20 (backup) + R9 (verify persistence). | Drew (2026-06-15): the DB is the irreplaceable RE artifact (types/comments/imported overlays beyond `symbols.us.txt`), it's tracked-but-not-actually-saved-when-current, and the lock won't release until MCP closes — so a phase-end commit must stop MCP itself, not wait for session close. |

*(Not elevated to rules — captured in cookbook §9.7: the transitional-default + leaf-first technique for refactoring a shared in-process global without breaking the byte oracle; the negative-control discipline (a no-op can pass for the wrong reason — pass a deliberately wrong value too); the progress.py-regex/Makefile lockstep. SETUP §6.7 documents the future-binary path convention.)*

## PhaseEnd Changelog
**v1.8.0 → v1.9.0 — Phase 9 complete (Gen2 phase 2).** The single-binary toolchain is now
**binary-agnostic**: a data-driven `BINARIES` Makefile (`make build BINARY=<alias>`) + every link-pipeline,
report, curation, and asm-differ tool parameterized by **required** `--vram-base`/`--exe`/`--symbols`/
`--binary`/`BFM_BINARY` — **no EXE default an overlay could silently inherit** (the roadmap's #1 risk,
eliminated by construction; a miss fails loud). Proven a **pure no-op**: the EXE rebuilds `143dbb89…` through
the parameterized path with and without the SDK objects, `make report` reproduces 52 REAL / 959 LINKED /
50.24%, and a deliberately wrong `--vram-base` diverges (`cae22f7e…`, the negative control). Landed as 11
per-tool checkpoint commits (each byte-gated), using a **transitional-default technique** (params default to
kept globals, removed → required once every caller passes explicitly) so the byte-locked EXE never broke
mid-refactor. The EXE's artifact paths are preserved verbatim; the clean `<bin>` convention + the EXE-only
`ifeq ($(BINARY),main)` gates are documented (SETUP §6.7, cookbook §9.7) for Phase 10's resident blob. One
rule (R23, stop-MCP-then-commit-DB at phase-end). No tools installed. The toolchain is ready to point at the
first overlay binary.

## Notes for Future Phases
- **Gen2 candidate (raised Phase 9):** extend `ExportSymbols.java` to also export Ghidra **types + comments**
  to text. Today only function names/addresses are text-exported (`config/symbols.us.txt`, R15); types/
  comments/imported-overlays live only in the binary `db.*.gbf`, which **renames on every save** → committing
  it bloats `.git` ~10 MB/checkpoint (R20 accepts this; clean public mirror later). Text-export would make the
  DB regenerable, eliminate the binary-blob backup + the R23 lock/commit dance, and be public-clean from day one.
- **Phase 10 first step:** `config/splat.resident.yaml` + the `resident` `BINARIES` instance for
  `MAIN.CD/FILE_010/1.1` @ `0x800CEDF8` (its own `resident_VRAM_BASE`); all-asm byte-match vs the extracted
  payload. The Phase-3 overlay map (`docs/memory-map.md §4.3`) + the Phase-9 parameterized tools feed directly in.

## 🛑 Stop Here
PhaseEnd written; `CURRENT_PHASE.md` archived → `phase-ends/logs/Phase9.md` (R19). The Phase-9 work is
committed (11 checkpoints `commit:0042`..`commit:0052` + this PhaseEnd commit, which also reconciles the Ghidra DB per
R23); **Drew pushes** (R6). Gen2 continues — do **NOT** start Phase 10 here. Start a **fresh session**
(effort **Max**, plan mode) for **Phase 10 — Resident engine blob**. Keep this file forever.
