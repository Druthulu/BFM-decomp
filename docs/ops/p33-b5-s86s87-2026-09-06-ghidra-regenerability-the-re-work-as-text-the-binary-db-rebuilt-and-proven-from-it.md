### P33 B5 (S86–S87, 2026-09-06) — Ghidra regenerability: the RE work as text, the binary DB rebuilt and PROVEN from it
- **Why.** The Ghidra project embeds the game's bytes (verified under the page XOR mask) and leaves git at C3. What R20
  backed up as `ghidra/` is now **`config/ghidra/<program>.jsonl`** — the hand-authored rows only — plus the proof that the
  program regenerates from the disc + the symbol files + that file. Roster: `config/ghidra/ROSTER.md` (6 programs: the
  retail EXE, the resident, `ov_SC01_077`, `ov_SC06_018`, the two prototypes); the other 123 live programs carry no
  hand-authored rows and regenerate on demand (`tools/prefetch_fleet.py`).
- **The delta model.** `ExportAnnotations` dumps EVERYTHING; the hand-authored part is what a fresh rebuild does NOT
  reproduce (baseline subtraction), minus three measured analysis-drift classes (see the `ghidra_annotations_delta.py` row).
  Measured (S87): resident / both overlays → container rows only (their names all come from the symbol files); the retail
  EXE → **38 hand-authored rows** (13 annotated functions incl. 3 the ELF does not define — `SaveLoadRoutine`, `SPU_OBJ_B44`,
  `SYS_OBJ_25B0` — 22 plate/EOL comments, 3 labels) after dropping 29 set-drift functions in the LINKED regions and 1 Error
  bookmark; the two prototypes → 0 after dropping 10 + 5 name-lag rows (their DBs were never re-mirrored from the curated
  proto symbol files). **The DB held no hand-authored types at all** (`types=0` in every program).
- **Controls (R39, S87, resident):** negative — one `block` row's end address mutated in the committed file → `PROOF FAIL`
  (rc 1); positive round-trip — a synthetic EOL comment, `Note` bookmark, user label and retyped signature appended → run 1
  `BFMANN funcs=1 comments=1 bookmarks=1 labels=1 failed=0`, the re-exported delta contains them, `PROOF PASS`; run 2 with
  that delta as the file → `PROOF PASS` (idempotent). The delta filter's own controls: the synthetic rows survive it; a
  hand-renamed name-only diff is KEPT (only auto names count as lag).
- **Gotchas that cost the S86 session:** (1) the OSGi bundle — one uncompilable script disables the whole directory and
  the headless log names every script, never the error; the fix was a hand `javac` (3 errors: `Long`→`int` unboxing ×2,
  and no `LocalVariableImpl(String,int,DataType,int,Program)` ctor — use `VariableStorage(program, off, size)`);
  (2) Ghidra refuses a project path with a `.`-prefixed component — the scratch project lives under `build/`;
  (3) `-process` without a name processes every program in the folder (one `-readOnly` run exports all 129);
  (4) `/undefined` is `DataType.DEFAULT`, in NEITHER type manager — main's first proof "passed" the cmp while 13 of 13
  func rows had failed to import (the plate-comment rows had set the same function comments); the resolver maps it
  explicitly and `ghidra_rebuild.sh` now dies unless the import printed `failed=0` (R49; fake `failed=2` refused,
  the passing population re-proven); (5) the live EXE's RAM tail block (0x800c7f08+) is `init:true` from the Phase-1
  import and `init:false` rebuilt — no hand-authored row lives there (7 auto functions + 1 Error bookmark), the
  committed row takes the rebuild's value.
- **Proofs (S87, all `PROOF PASS`, `failed=0`):** resident 65 s · ov_SC01_077 169 s · ov_SC06_018 173 s · SLUS_007.26
  210 s (`BFMANN funcs=11 comments=11 unchanged=16 rows=70`) · sep8 202 s · aug31 206 s. `tools/ghidra_roster.py --check`
  is in `tools-health` (ignores the per-machine proof column; controls: proof marker removed → OK, census edited → STALE).
- **Same change:** `ExportSymbols.java` R15 fix (output-path arg, refuses to overwrite, refuses `config/`); every
  `tools/ghidra_*.sh` and `Makefile` `GHIDRA_PROJ` repo-relative (`BFM_GHIDRA_PROJ` override); `DefineFunctions.java`
  takes its list path as arg 1; `ImportPsyqGdt.java` finds the gdt under the install dir; `make print-<VAR>`; the
  `.claude/settings.json` hooks `$CLAUDE_PROJECT_DIR`-relative with the silent no-op (§2.8).

