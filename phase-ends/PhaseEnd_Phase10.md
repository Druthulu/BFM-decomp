# PhaseEnd — Phase 10: Resident engine blob — splat config + all-asm byte-match
**Date:** 2026-06-15 · **Project Version:** 1.10.0 · **Phase Status:** Complete · **Generation:** Gen2 (3rd phase)

> Gen2 phase 3 of the arc (8→9→**10**→11→{12,13}→14). The granular per-task trail (the structure
> mapping, the section-order/build_path fights, the Ghidra raw-import diagnostics) is preserved
> on-demand at **`phase-ends/logs/Phase10.md`** (R19 — NOT auto-loaded; consult only when researching
> a mechanism). Owner decisions (2026-06-15): Ghidra = **second program**; **defer** the Q#2 pointer
> table to Phase 11/12; **defer** the PsyQ 4.7 `.LIB`s to Phase 11 start.

## Build Log

**Files created/changed and complete — do not recreate:**

*Config / build (the resident binary):*
- `config/splat.resident.yaml` — **new.** Flat-blob splat config: no `header`, no `gp_value` (-G0),
  single `code` segment @ `vram 0x800CEDF8`, `build_path: build`, per-binary `asm_path: asm/resident`
  / `src_path: src/resident` / `undefined_*_auto_path: build/resident/…`, stacked
  `symbol_addrs_path: [config/symbols.us.txt, config/symbols.resident.txt]`. Subsegments (mapped vs the
  bytes): `[0x0, rodata, hdr]` (the leading data word `0x36`, emitted rodata so section_order places it
  first) + `[0x4, c, resident]` (code, 0x4..0x4610) + `[0x4610, data, tail]` (pointer tables + 78.5 KB
  zero run) + EOF `[0x5935C]` (→ end vram 0x80128154). Consumed by `make extract BINARY=resident`.
- `config/check.resident.sha` — **new, committed.** `8e17e02ff8954d07c979449198f7e1645046b353  resident`
  (the extracted `MAIN.CD/FILE_010/1.1`, 365,404 B). The build-identity gate for `BINARY=resident`.
- `config/symbols.resident.txt` — **new, committed.** R13/R15-tagged, blob-LOCAL, never merged into
  `symbols.us.txt`. Seeded with `DsMix` (the 1 in-range PsyQ-signature hit; R13 candidate — 4.0-sig vs a
  4.7 blob, confirm in Phase 11). count=1.
- `src/resident/resident.c` — **new, committed.** splat's 143 INCLUDE_ASM stubs (the C record; `DsMix`
  named, the rest `func_*`). `asm/resident/**` is regenerated (gitignored, like main's).
- `Makefile` — **modified.** `BINARIES := main resident`; the `resident_*` block; per-binary
  `<bin>_ASM_DIR`/`SRC_DIR` + a `$(BINARIES)`-derived **OBJS prune-list** (keeps main's and resident's
  object sets disjoint); per-binary `UNDEF_SYMS`/`UNDEF_FUNCS` + `GHIDRA_PROG` aliases; `sig-refresh` →
  `-process $(GHIDRA_PROG)`; `expected` made **per-binary-safe** (merge-copy, no `rm -rf expected/build`
  sibling clobber). The EXE-only library `ifeq ($(BINARY),main)` blocks are untouched (skipped for resident).

*Reusable tooling (new, committed):*
- `tools/ghidra_import_raw.sh` — raw flat-blob importer (`BinaryLoader` + `--loader-baseAddr <vram>` +
  `PSX:LE:32:default` + PsyQ `.gdt` + DumpProgramInfo). The Gen2 counterpart to `ghidra_import.sh`
  (PS-X-EXE only); **reusable for Phase-13 location overlays.** Precondition: MCP stopped.
- `tools/ghidra_scripts/DefineFunctions.java` — disassemble + `createFunction` at each address in
  `.run/<prog>_funcs.txt` (splat's validated entry points) — completes a raw-blob program's function set
  (raw-binary auto-analysis only finds the reachable subset). Saves on clean exit.

*Reports / asm-differ (per-binary):*
- `diff_settings.py` — **modified.** `resident` entry in the `BFM_BINARY` map (`baseimg`/`myimg`/`mapfile`
  under `build/resident/`).
- `tools/progress.py` / `tools/difficulty.py` / `tools/dup_report.py` — **modified.** `resident` BINARIES
  entry each. progress.py: `linked_subsegs()` scoped to `BINARY==main` (PsyQ library linking is the EXE's
  layout — a 2nd binary has 0 LINKED). dup_report.py: degrades gracefully when the Ghidra sig is absent
  (writes a placeholder, exit 0) instead of crashing `make report`.

*Docs:*
- `docs/SETUP.md` — **§6.7** extended with the `resident` first-instantiation + the reusable **flat-blob
  recipe** (per-binary OBJS prune, `build_path: build`, flat config, rodata-before-code, per-binary
  GHIDRA_PROG/expected); the 2 new scripts added to the tooling inventory (R21).
- `docs/{progress,difficulty,duplicates}.resident.md` — **new, committed** per-binary digests
  (resident = 0 REAL / 143 stubs / 100% INCLUDE_ASM; 6 byte-identical intra-resident dup groups).

*Ghidra DB (R23, committed — MCP stopped first):*
- The `bfm` project's **4th program `resident`** (`ghidra/…/00000003.*`) — raw-import @0x800CEDF8,
  PsyQ 4.0 types, **PsyQ 4.7.0 detected**, all 143 splat boundaries defined, `DsMix` named. R9-verified.
  (Main's incidental `db.15→db.16` no-op renumber rode along with this real RE checkpoint.)

- `phase-ends/CURRENT_PHASE.md` → **`phase-ends/logs/Phase10.md`** (R19 archive). `phase-ends/PhaseEnd_Phase10.md` — this file.

**Local artifacts (gitignored / regenerable — a fresh clone redoes them):** `asm/resident/**`, `build/`,
`expected/`, `.run/sig.resident.jsonl`, `.run/resident_funcs.txt`. The resident **Ghidra program is itself
reproducible** from committed tooling: `tools/ghidra_import_raw.sh … 0x800CEDF8 resident` then
`DefineFunctions.java` over splat's `func_*` list.

**Tools/packages installed:** None (used the existing Phase-1/4/6 toolchain entirely).

**Verification results (literal) — the milestone proof (clean rebuild, all green):**
- **(1) resident** `make clean && make extract BINARY=resident && make build BINARY=resident` →
  `build/resident/resident` SHA1 `8e17e02ff8954d07c979449198f7e1645046b353` == the extracted
  `MAIN.CD/FILE_010/1.1` (365,404 B, end vram 0x80128154) — **BYTE-IDENTICAL**.
- **(2) main (no-regression)** `make extract && make build` → `143dbb89f34491258bbc27810d0a12ec8b43a8dd`
  — **BYTE-IDENTICAL** (the per-binary OBJS/UNDEF refactor is a proven no-op on the byte-locked EXE).
- **(3) composition** `make report BINARY=resident` → **0 REAL / 143 INCLUDE_ASM stubs / 145 matchable
  (100% INCLUDE_ASM)**; main report UNCHANGED (52 REAL / 959 LINKED / 50.24%).
- **(4) -G0** confirmed — 0 `($gp)`/`%gp_rel` in the resident disasm.
- **(5) isolation** main `OBJS` stays 81 objects (excludes resident) even with `asm/resident`+`src/resident`
  on disk; `make build BINARY=main` after a resident extract stays `143dbb89…`.
- **(6) Ghidra** resident program: 143 funcs defined (created=120/existed=23/failed=0), **R9-verified
  persisted** via read-only `sig-refresh`; PsyQ **4.7.0** detected; `DsMix` (libsnd) the lone sig hit.
- `git status`: zero ROM-derived/generated bulk staged across all 4 task commits.

**Milestone achieved:** `make build BINARY=resident && make check` rebuilds the always-resident engine blob
**byte-for-byte (SHA1 `8e17e02f…` == the extracted disc payload)** from disassembly alone at 100%
INCLUDE_ASM, with the EXE still `143dbb89…` (no regression) — the parameterized toolchain proven on a real
second binary. Confirmed by Drew (gate 2).

**Next:** **Phase 11 — Cross-binary dedup pipeline.** Start a fresh session (effort **Max**, plan mode).
**First, fetch + sha-verify the PsyQ 4.7 `.LIB`s** (archive.org; R20 — deferred from Phase 10) since the
resident is 4.7; then build the cross-binary duplicate-detection + share pipeline and prove it on the
byte-verified EXE↔resident pair (the Phase-9 sigs + this phase's `.run/sig.resident.jsonl` feed in directly;
6 byte-identical intra-resident groups already visible).

## Deviations
| Item | Plan | Actual | Reason |
|---|---|---|---|
| Code/data boundary | iterate from a splat estimate | mapped empirically vs the bytes (code 0x4..0x4610; data tail; 78.5 KB zeros) | the blob isn't a PS-X EXE → no psxexeinfo estimate; the Phase-3 "18,788-byte prefix" was the runtime-stable slice, not the section boundary |
| Leading data word | (not anticipated) | emit as **`rodata`** (section_order places .rodata first) — no `ld_interleave` | a 1-word data-before-code island; rodata-first is the clean fix the Plan-agent validation flagged |
| `build_path` | `build/<bin>` (intuitive) | **`build`** (splat writes `.ld` object paths under build_path; must match the Makefile's `build/asm/**` rules) | the only way the `.ld` and the pattern rules agree; only elf/ld/output go under `build/<bin>/` |
| Ghidra analysis depth | "auto-analysis" (light) | auto-analysis found 23/143 → **defined all 143** via DefineFunctions.java | raw-binary auto-analysis is conservative (no entry points); "properly analyze" needs splat's boundaries — mechanical, not manual RE |
| PsyQ version | (assumed EXE's 4.0) | resident detects **4.7.0** (DsMix=libsnd) | a real finding; the resident's PsyQ library linking (Phase 11) is 4.7, not 4.0 → R24 |
| `expected` / report tools | "one-line additions" | also fixed a clobber (`rm -rf expected/build`) + a dup_report crash (absent sig) + progress LINKED leak | genuine multi-binary parameterization gaps Phase 9 hadn't exercised (main was the only binary) |
| 4.7 `.LIB`s | (open) | **deferred to Phase 11 start** (Drew) | Phase 10 needs nothing from them (100% INCLUDE_ASM); staged when Phase 11 links the resident's PsyQ code |

## Commit Message
```
(Phase 10 landed as 4 per-task checkpoint commits commit:0054..commit:0057 + this PhaseEnd.)

feat(phase-10): resident engine blob — 2nd binary byte-identical from source (v1.10.0)

- T1 (commit:0054): scaffold the `resident` binary — Makefile BINARIES+=resident, resident_* block,
  per-binary OBJS prune-list ($(BINARIES)-derived) + UNDEF aliases; config/splat.resident.yaml
  (flat: no header/gp_value, vram 0x800CEDF8, stacked symbols); proven a no-op on main (143dbb89)
- T2 (commit:0055): split iterated to byte-identical — [0x0,rodata,hdr]+[0x4,c]+[0x4610,data];
  leading data word emitted rodata (section_order first, no ld_interleave); build_path=build;
  make build BINARY=resident -> 8e17e02f BYTE-IDENTICAL (365,404 B), -G0, R22 clean-rebuild
- T3 (commit:0056): per-binary reports + diff_settings + per-binary-safe expected (no clobber);
  dup_report degrades on absent sig; progress linked_subsegs scoped to main; main reports unchanged
- T4 (commit:0057): tools/ghidra_import_raw.sh (raw-blob importer) + DefineFunctions.java; resident
  imported as the bfm project's 2nd binary @0x800CEDF8 (PsyQ 4.7.0 detected, DsMix=libsnd);
  143 boundaries defined + R9-verified; config/symbols.resident.txt seeded; sig-refresh per-binary;
  Ghidra DB committed (R23)
- docs/SETUP.md §6.7: the resident instantiation + the reusable flat-blob recipe (R21)
- MILESTONE: resident 8e17e02f == extracted MAIN.CD/FILE_010/1.1 at 100% INCLUDE_ASM; main 143dbb89
- rule R24 (per-binary compiler/SDK provenance); bumps 1.9.0 -> 1.10.0
```

## Rules Added This Phase
| Rule | Reason |
|---|---|
| **R24 — Per-binary compiler/SDK provenance.** Record each binary's detected toolchain (PsyQ/SDK version, and the compiler triple once pinned) as provenance, tagged per binary; **never assume one binary's toolchain applies to another.** Verify before linking that binary's library code or pinning its triple. Extends G8 (expect per-module compiler variation) and G5 (provenance) to the Gen2 multi-binary reality. | The resident detects as **PsyQ 4.7.0** while the EXE is **4.0.0** (DetectPsyQ + the `DsMix`/libsnd hit + the auto-associated `psyq470` archive). Assuming 4.0 would mis-link the resident's PsyQ library code (sound/GTE) in Phase 11. The byte-match is unaffected (100% INCLUDE_ASM), but the matching/linking phase must use the right version. |

*(Not elevated to a rule — captured in SETUP §6.7: the reusable **flat-blob `<bin>` recipe** — per-binary nested `asm/<bin>`+`src/<bin>` with a `$(BINARIES)`-derived OBJS prune, `build_path: build`, flat config with no header/gp_value, and the **leading-data-word-as-rodata** trick that avoids `ld_interleave`. R22 clean-rebuild discipline was exercised throughout. The resident Ghidra program is reproducible from committed tooling, so its DB commit is a convenience baseline, not the irreplaceable artifact — Phase 11/12's manual RE on top of it will be.)*

## PhaseEnd Changelog
**v1.9.0 → v1.10.0 — Phase 10 complete (Gen2 phase 3).** The project now rebuilds a **second binary**
byte-for-byte from source: the always-resident engine blob (`MAIN.CD/FILE_010/1.1`, vram `0x800CEDF8`,
365,404 B) → SHA1 `8e17e02f…` at 100% INCLUDE_ASM, with the EXE still `143dbb89…` (the Phase-9
binary-agnostic toolchain proven on a real overlay-class target). The reusable **flat-blob recipe** is
established and documented (SETUP §6.7): per-binary nested `asm/<bin>`+`src/<bin>` with a
`$(BINARIES)`-derived OBJS prune, `build_path: build`, a flat splat config (no header, no gp_value, -G0),
and the **leading-data-word-as-rodata** trick (places a pre-code data word first via section_order, no
`ld_interleave`). Two reusable Ghidra tools were added — `ghidra_import_raw.sh` (raw flat-blob import,
for Gen2 overlays) and `DefineFunctions.java` (seed splat's validated boundaries) — and the resident is
now the `bfm` project's second analyzed program (143 functions, R9-verified). Reports/asm-differ/`expected`
are fully per-binary (fixing a clobber + a crash + a LINKED-leak the single-binary era hid). **Key finding:**
the resident was built with **PsyQ 4.7** (the EXE is 4.0) — `DsMix`/libsnd corroborates; the 4.7 `.LIB`s
are deferred to Phase 11 (the resident's library linking will need them). One rule (R24, per-binary
SDK provenance). No tools installed.

## Notes for Future Phases
- **Phase 11 opener (carried, Drew):** fetch + sha-verify the **PsyQ 4.7 `.LIB`s** (archive.org) into
  `tools/psyq/` (R20 — hard-to-source backup) before linking the resident's embedded PsyQ code. The
  resident holds the **sound driver** (libsnd — `DsMix`) and likely libgte/libspu; these collapse to
  real linked 4.7 objects (the Phase-7/8 technique), not hand-decomp. The EXE's 4.0 `.LIB`s won't match.
- **Cross-binary dedup (Phase 11):** `.run/sig.resident.jsonl` is generated; `make report BINARY=resident`
  already shows **6 byte-identical intra-resident dup groups**. The EXE↔resident pair is the byte-verified
  proving ground for the new dedup pipeline (per the roadmap's de-risk invariant).
- **Q#2 — EXE→resident pointer table** (JP ~0x62620, US to re-derive): **deferred** (roadmap-optional). It
  maps the resident's sub-sections; fits Phase 11/12 when the engine layout is being RE'd.
- **Engine RE (Phase 12):** the resident's 143 functions are auto-named `func_*` (only `DsMix` real). The
  script VM + actor system live here — name + match them in Phase 12; `config/symbols.resident.txt` grows then.
- **DB-bloat note (still open from Phase 9):** the resident program adds ~13 MB/commit to `ghidra/`. Since
  it's script-reproducible, extending `ExportSymbols.java` to text-export types+comments (so the DB is
  regenerable + public-clean) remains the right Gen2 cleanup — revisit before the public flip.

## 🛑 Stop Here
PhaseEnd written; `CURRENT_PHASE.md` archived → `phase-ends/logs/Phase10.md` (R19). The Phase-10 work is
committed (4 checkpoints `commit:0054`..`commit:0057` + this PhaseEnd commit, which also lands the SETUP §6.7 update);
**Drew pushes** (R6). Gen2 continues — do **NOT** start Phase 11 here. Start a **fresh session** (effort
**Max**, plan mode) for **Phase 11 — Cross-binary dedup pipeline** (opening with the PsyQ 4.7 `.LIB` fetch).
Keep this file forever.
