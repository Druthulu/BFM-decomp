### P33 B1 (S86, 2026-09-06) — `make disc-extract`: the rom→decoder step, promoted into the build
- **`make disc-extract`** (`DISC_DIR ?= disks`): the repository ships no ROM bytes (H1 in force). The target (1) probes
  `extracted/retail/` against the committed oracle (`extract.py --verify`, **0.7 s** when up to date → no-op), else (2)
  requires `disks/Brave Fencer Musashi (USA) (Track 1).bin` (exit 2 with the staging instruction), (3) verifies the dump
  is the canonical redump one (`extract_exe.py --verify-disc`: Track-1 SHA1 `b44f0f0a…` + CRC32 `c238191b`; a truncated
  or foreign dump FAILS and nothing is written), (4) extracts everything and COMPARES against the committed
  `extracted/retail/manifest.jsonl` (`extract.py --expect-manifest`: identical → nothing written; different → the actual
  manifest goes to `.run/extract/` with the first 20 differences listed, exit 1), (5) re-verifies the tree. Measured:
  **15.7 s wall** for the full 4-track extraction + manifest compare + verify (1,801 files, 759 MB). `extract`/`extract-all`
  call it when a payload is absent / once up front, so the R22 chain on a fresh clone is `make disc-extract && make
  extract-all && make check-all`. A Track-1-only dump is accepted with an explicit **PARTIAL** verdict (`--allow-missing-
  audio`: the 3 `.DA` audio rows from Tracks 2–4 are excluded from the compare and the verify; without the flag a partial
  extraction FAILS, R43). The committed oracle is never overwritten by a build step; regenerating it is a deliberate plain
  `extract.py` run. `extracted/proto/` (the two prototype EXEs) is NOT produced here — it comes from the prototype discs via
  `tools/bfm_extract/extract_proto_exe.py`.
- `make check-env`: the EXE's absence is now a `[WARN]` with the instruction (present-but-wrong stays `[FAIL]`); new step 7
  asserts the oracle is self-consistent (`manifest.sha1 == sha1(manifest.jsonl)`); `[INFO]` disc presence. `make help`
  rewritten for the live targets. `make clean` no longer deletes the four splat preset headers — `include/include_asm.h`,
  `macro.inc`, `labels.inc`, `gte_macros.inc` are TRACKED (generic splat presets, identical for every binary, ROM-free; the
  compile-only CI needs them; a splat preset change shows as a diff).
- `.gitignore` re-tightened to H1: `/dumps/*.bin`, `/session archive/`, `/tools/ghidra-ext/*.zip`, `/tools/brave-CUE/brave.exe`,
  `/ghidra/` (whole), `/tools/psyq/` (whole; checksums move to `tools/psyq_CHECKSUMS.sha256` in C3), the EXE re-include
  dropped (only the two manifest files stay under `extracted/`), the header rewritten. Tracked files under those paths stay
  tracked until the C3 `git rm --cached` commit (ignore rules bind untracked paths only).

