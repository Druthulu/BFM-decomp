# layout-contract.md — the repository layout the source project's tools assume (a DRAFT for the split phase)

> **Status: a draft measured on 2026-09-07 from five core tools, not yet a contract the installer stamps.** The question it
> answers: if a new project adopted the source project's layout exactly, how close would the verbatim tools in `corpus/tools/`
> be to running unchanged? The probe grepped each tool for the paths, aliases, configuration files, make targets and toolchain
> flags it names; the table is what it found. The decision whether SETUP Step 4 should stamp this layout (making same-compiler
> projects' tools near-drop-in) belongs to the split phase, once the corpus is exercised on a second target. Until then the
> `Adapt` column of the tool dictionary is the list to work from.

## The five tools probed, and what each assumes

| Tool (need) | Directory layout | Configuration files | Make targets | Aliases | Toolchain |
|---|---|---|---|---|---|
| the corpus oracle (is this function open, matched or shared?) | `src/<alias>/<subsegment>.c`, a boot unit, `build/src/` | the curated symbol file under `config/` | the per-binary signature targets, `sig-*` | one alias per binary: the executable, the resident blob, overlays, modules | the per-file optimisation level (`-O0` / `-O2`) |
| the standalone matcher (does this draft's body match, relocations masked?) | `asm/<alias>/nonmatchings/<subsegment>/<function>.s`; scratch under `.run/match/<function>/` and `.run/drafts*/` | — | — | the executable and the resident are special-cased | the pinned compiler, the assembler shim with an explicit compatibility version, the `-G0` and `-O` flags |
| the real-unit matcher (does it match inside its real translation unit?) | `src/<alias>/<split>.c`, `asm/`; scratch under `.run/` | — | `make build` | the executable is special-cased | the same triple and flags |
| the whole-binary byte gate (substitute, build, keep only if identical) | `asm/<alias>/nonmatchings/…`, `src/<alias>/<unit>.c`, `build/<alias>/…`; `.run/drafts/`, `.run/harvest_*` | `config/check.<alias>.sha`, `config/splat.<alias>.yaml`, the per-binary make fragment | `make build`, `make extract`, `-j` | one alias per binary | the compiler and the assembler shim |
| propagation (author once, instantiate at every duplicate site) | `src/shared/` with the shared engine header and the shared types header, `src/<alias>/<alias>.c`, `asm/<alias>/…`, `build/<alias>/`; `.run/sig`, `.run/dpcc` | the dedup registry (`config/dedup.<version>.yaml`), the overlays and modules make fragments | `make build`, `make check`, `make all` | one alias per binary | `-G0`, the optimisation level |

## The contract, as the tools state it

1. **One alias per binary**, used as a path segment everywhere: `asm/<alias>/`, `src/<alias>/`, `build/<alias>/`, `config/splat.<alias>.yaml`,
   `config/check.<alias>.sha`, `make build BINARY=<alias>`. The alias set has a fixed shape: the main executable, a resident blob, a
   family of position-locked overlays and a family of code modules — and two of them (the executable, the resident) are special-cased
   in several tools.
2. **The splitter's layout**: per-function assembly under `asm/<alias>/nonmatchings/<subsegment>/<function>.s`; C under
   `src/<alias>/<subsegment>.c` with a stub macro per unmatched function; the shared engine bodies under `src/shared/` in a generated
   header, with a generated types header beside it.
3. **The per-binary contract**: `config/check.<alias>.sha` holds the target's hash; `make build BINARY=<alias>` checks it; `make extract`
   regenerates the split; per-binary make fragments list the overlays and modules.
4. **The scratch convention**: everything transient under `.run/`, per tool a subdirectory (`.run/match/`, `.run/drafts/`, `.run/sig/`).
5. **The toolchain**: the compiler invoked directly (`cc1`), the assembler shim with an explicit compatibility version, `-G0`, and a
   per-file optimisation level the tools detect from the object.
6. **The registry files**: a curated symbol file, a dedup registry keyed by version, the overlays and modules make fragments.

## What that means for a new project

- A **same-compiler** project that adopts items 1–6 verbatim gets the five core tools running with path edits only; the probe
  found no assumption outside these six classes in them. TODO(platform): a different platform changes item 5 and the alias shape
  of item 1 first.
- A **different-layout** project treats the tool dictionary's `Adapt` column as the work list per tool; the five classes above are
  the vocabulary that column uses.
- The split phase decides whether SETUP Step 4 stamps this layout; the honest prerequisite is a second target on which the corpus
  tools have actually been run.
