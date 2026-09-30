### P33 B4 (S86, 2026-09-06) — `tools/fetch_psyq.sh`: the OPTIONAL PsyQ SDK objects, user-supplied and verified
- **What it is for.** Byte-identity never needs Sony's libraries (without them main links its INCLUDE_ASM tiles — the
  fresh-clone proof in B3 built all 218 that way). `tools/fetch_psyq.sh [--disc <RTL-4.0 Track 1 .bin>] [--from <dir>]
  [--no-build]` is for a developer who wants `make check BINARY=main` to link Sony's REAL objects (the 1,256 LINKED
  functions): it obtains and verifies every piece against `tools/psyq_CHECKSUMS.sha256` (rows relative to `tools/psyq/`,
  which is gitignored — nothing Sony-copyrighted is redistributed), then runs the existing builders and `make sdk-dual`.
- **Pieces and provenance:** `psyq-obj-parser` — decomp.me's release tarball
  `https://github.com/decompme/compilers/releases/download/compilers/psyq-obj-parser.tar.gz` (tarball sha256 `353495f1…`,
  the static x86-64 binary inside `4fba623a…` — identical to the copy this project used since Phase 7); the **Runtime
  Library 4.2** 7z — archive.org `https://archive.org/download/play-station-programmer-tool-runtime-library-version-4.2.7z/
  PlayStation_Programmer_Tool_-_Runtime_Library_Version_4.2.7z` (383,431 B, sha256 `e4f5a678…`) → `tools/psyq/lib421/`
  (the `LIB/42PATCH/J421PD.ZIP` payload: LIBPAD.LIB 4.2.1 + LIBAPI.LIB 4.2, both sha256-rowed); the **20 PsyQ 4.0 libraries
  — NO public download**: they are `PSX/LIB/*.LIB` on the redump disc *PlayStation - Programmer Tools - Run-time Library
  4.0 (USA) (PC-CD ROM Release 2.0)* (DTL-S2002, ISO volume `PROGTOOL`); `tools/psyq_libs_from_disc.py <Track 1 .bin>
  <out>` extracts them with the project's own ISO9660 walker (`tools/bfm_extract/iso9660.py`, the same reader
  `make disc-extract` uses) — every LIB is checked against its recorded sha256 (LIBCD.LIB from the disc == the copy used
  since Phase 7). Without `--disc`/`--from` and without `tools/psyq/lib40/` the script REFUSES and names the disc (R43).
- **Builders it runs (unchanged, all regenerable):** `tools/psyq_build_libs.sh LIBCD LIBETC LIBGPU LIBMCRD LIBC2 LIBGTE
  LIBGS LIBSPU LIBSND LIBCARD` (→ `.run/obj40/<lib>` + `tools/psyq/lib40_elf/*.a`), `tools/make_libgs.sh` (→
  `.run/obj40/libgs_used`), `tools/make_snd_used.py` (→ `.run/obj40/snd_used`), the lib421 ELF step (→
  `.run/obj42/{libpad421,libapi42}`), `tools/make_apicard_used.py` (→ `.run/obj42/apicard_used`); then `make -j$(nproc)
  sdk-dual`. Which region needs which: `.run/obj40/{libcd,libetc,libgpu,libmcrd,libc2,libgte}` + `libgs_used` + `snd_used`
  from the 4.0 LIBs; `.run/obj42/{apicard_used,libapi42,libpad421}` from LIBCARD 4.0 + the 4.2 archive. `Psy-Q_46.zip`,
  `PSYQ_SDevTC_v4.5.zip`, `conv47/` and the 4.0 Win32 tools feed NO linked region (research artifacts; archive repo only).
- **Controls (S86):** no source → refuse (rc 1, the message); `--from` a directory with one corrupted LIB → `sha256 MISMATCH
  for tools/psyq/lib40/LIBTAP.LIB`, rc 1, nothing built; the disc path → see `phase-ends/CURRENT_PHASE.md` B4 for the run.
- `tools/psyq/CHECKSUMS.sha256` → **`tools/psyq_CHECKSUMS.sha256`** (git mv; the directory it lived in leaves git at C3).

