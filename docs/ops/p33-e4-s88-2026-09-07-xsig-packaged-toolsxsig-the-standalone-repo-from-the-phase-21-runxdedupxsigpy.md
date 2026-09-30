### P33 E4 (S88, 2026-09-07) — xsig packaged: `tools/xsig/` + the standalone repo, from the Phase-21 `.run/xdedup/xsig.py`
- **What it is.** The Phase-21 cross-project dedup probe's signature library (`.run/xdedup/xsig.py`, 2026-06-25) plus the
  driver scripts around it (`sign_bfm.py`, `sign_xeno.py`, `cross.py`, `analyze.py`) folded into ONE stdlib file with a CLI
  (`sign-s | sign-objdump | cross | verify | selftest`), a README that carries the recorded worked example (BFM × Xenogears +
  Vagrant Story: 103 hits, all PsyQ library/BIOS — libapi 34, libcd 14, libetc 14, libspu 11, libcard 7 …, the largest
  `_spu_setReverbAttr` 307 ins; BFM × Tomba: 126 hits, 124 library, one 19-ins non-library HIGH — the decision log's "clean
  negative: zero engine code"), an MIT `LICENSE`, and `tests/`.
- **The fixture (no game bytes, R-candidate (a)):** `tests/fixture.c` (two functions of our own) compiled with the pinned
  triple by `tests/make_fixtures.sh` and linked TWICE (`ld -q` = `--emit-relocs`, `-Ttext` 0x80010000 vs 0x80200000,
  `--defsym` helper/table at different addresses). Gotcha: `objdump -dr` interleaves relocation records only for OBJECT
  files; for a linked ELF they are listed separately (`-r`, section-relative offsets) — the generator merges them into the
  listing in the object-listing format (`\t\t\t<vma>: R_MIPS_HI16\ttable`), which is what the front-end reads. A second gotcha:
  a linked listing puts the address at column 0 (an object listing indents it) — the instruction regex is `^\s*` now.
  `tests/test_xsig.py` (8 checks): same function at two link addresses signs identically while the raw words differ; the
  relocated fields are present and the only masked ones (`verify`: IDENTICAL up to relocation, 3 fields); a different
  function differs; a register flip changes the sig and is classified `register`; the `.s` and objdump front-ends agree;
  `sign-objdump` + `cross` find exactly the two true pairs; `verify` accepts the pair and rejects the mismatch; `selftest`.
- **Wiring (R21):** the tests in `make tools-health` and the CI `audits` job; `tools/xsig/README.md` in `doc_links`' default
  set; this row/section. The standalone repo: `.run/P33/xsig-repo/` = the same files, `git init`, the repo-local NOREPLY
  identity (never the global one), one initial commit; Drew creates `Druthulu/xsig` on GitHub (empty) and pushes.


