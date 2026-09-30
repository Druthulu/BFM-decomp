### P33 B5 (S86, 2026-09-06) — Ghidra regenerability (IN PROGRESS at the S86 pause; see `phase-ends/CURRENT_PHASE.md`)
- **Model:** the Ghidra database embeds the program bytes, so it leaves git; what it holds beyond the splat symbol files is
  exported to text and the project is rebuilt from the disc + that text. `tools/ghidra_scripts/ExportAnnotations.java`
  (read-only; byte-stable JSONL: container facts, LOCAL types, every function signature, defined data, the 5 comment kinds,
  bookmarks, equates, labels the symbol files lack) via `tools/ghidra_export_annotations.sh [PROG…]` (no PROG = every
  program; **129 programs in 18.5 s** → `.run/ghidra_export/`). The committed file `config/ghidra/<prog>.jsonl` is the
  DELTA (`tools/ghidra_annotations_delta.py live baseline out`) between the live export and a FRESH rebuild's export, so
  analysis-origin rows subtract themselves out. `tools/ghidra_rebuild.sh <prog> [--proof] [--keep]`: import (PSX loader for
  the EXEs, BinaryLoader at `make -s print-VRAM_BASE BINARY=<alias>` for the rest) → `DefineFunctions.java` from the built
  ELF → `ApplySymbols.java` → baseline export → `ImportAnnotations.java config/ghidra/<prog>.jsonl` → export → delta → `cmp`.
  Scratch project under `build/ghidra_rebuild/proj` (**Ghidra refuses a project path with a component starting with '.'**,
  so never `.run/`). `make print-<VAR> BINARY=<alias>` echoes any per-binary Makefile variable (R33).
- **Gotcha (S86):** Ghidra compiles a `-scriptPath` directory as ONE OSGi bundle — a single script that fails to compile
  makes EVERY script in the directory fail with `Failed to get OSGi bundle containing script`. Diagnose by invoking the
  suspect script directly and reading the javac lines.
- Also in this change: `ExportSymbols.java` R15 fix (output path arg, refuses to overwrite, refuses `config/`);
  `DefineFunctions.java` list path = arg 1; `ImportPsyqGdt.java` default gdt from the Ghidra install dir; the six
  `tools/ghidra_*.sh` are repo-relative (`BFM_GHIDRA_PROJ` overrides the project dir; `ghidra_mcp_verify.sh <addr> <name>
  [PROG]`); Makefile `GHIDRA_PROJ := $(or $(BFM_GHIDRA_PROJ),$(CURDIR)/ghidra)`.

