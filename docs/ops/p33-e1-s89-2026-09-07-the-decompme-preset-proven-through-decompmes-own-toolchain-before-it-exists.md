### P33 E1 (S89, 2026-09-07) — the decomp.me preset, proven through decomp.me's own toolchain before it exists
- `docs/decompme-preset.md` (NEW; in `doc_links`' default set). The preset: platform `ps1`, `gcc2.7.2-psx`,
  `-O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker -Wa,--aspsx-version=2.56,--expand-div`, name
  `Brave Fencer Musashi (SLUS-00726)`; **no create-preset UI exists** (the frontend only reads presets) — decomp.me's
  maintainers create them from the `create-or-update-a-compiler-preset.md` issue template; `name`/`platform` immutable and no
  owner delete (`views/preset.py`: 405) → proven before it is requested.
- **Measured (R14) — the stale claim "decomp.me bundles maspsx at the same pinned commit we use" (§6.5, rows for maspsx)
  was wrong:** decomp.me's image (`decompme/compilers` `platforms/ps1/gcc2.7.2-psx/Dockerfile` + `values.yaml`) is old-gcc
  **0.13** (sha256 `aca64479…ffbc`) + maspsx **`86ccd7d8`** (2026-08-29) with `as` = `python3 maspsx.py --run-assembler
  -I${COMPILER_DIR} "$@"`; the backend (`coreapp/compilers.py` `PS1_GCC`) runs `/usr/bin/cpp -nostdinc | sed` then
  `gcc ${FLAGS} -c -pipe -B${COMPILER_DIR}/`. Our pin `874855c5` is 4 commits behind; the two behavioural commits (lw,lw and
  lwl/lwr nop handling) are gated on aspsx < 2.30. old-gcc 0.13→0.17 changed build scripts and the cdk patches only
  (`compare/0.13...0.17`). The three §6.5/maspsx rows were corrected in place.
- **`tools/decompme_replica.sh`** (NEW): the replica + control + attribution matrix described in its inventory row. Recorded run
  (`.run/P33/e1/decompme_replica.log`): **decomp.me replica BYTE-IDENTICAL on all 26 words of `func_80018F20`** (+2 trailing
  zero words = gas padding, reported not counted) · our pipeline BYTE-IDENTICAL (control) · C1 cc1 0.13 vs 0.17 identical
  text · C2 maspsx 86ccd7d8 vs 874855c5 identical text · `PASS`. Controls (R39): `-O1` flags → FAIL listing the words (rc 1);
  an empty-body TU → the CONTROL fails first (rc 3, R56). `--upstream` 2026-09-07: `pins UNCHANGED`. Instrument lesson (R40):
  the first comparison read the padded `.text` and called the identical object DIFFERS.
- `.gitignore`: `.run/P33/e1/` allowlisted for the verdict log only (the regenerated target `.s` is game disassembly — H1).
- **Done 2026-09-08 (P34 task 2, Drew):** scratch <https://decomp.me/scratch/mIu4d> at 100% / score 0; the preset-request issue
  <https://github.com/decompme/decomp.me/issues/2106>; the manual search recorded in ledger row 14 (closed). The first attempt failed on
  the target's form — the §5 doc and the tools were fixed and proven before the retry (`verbatim_target_s.py --gas`, replica step D).
  **Still pending:** the maintainers creating the preset (its id goes into §6.5 when it exists).

