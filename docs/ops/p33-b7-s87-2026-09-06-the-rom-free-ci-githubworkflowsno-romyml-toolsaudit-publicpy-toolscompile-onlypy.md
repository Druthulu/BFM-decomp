### P33 B7 (S87, 2026-09-06) — the ROM-free CI: `.github/workflows/no-rom.yml`, `tools/audit_public.py`, `tools/compile_only.py`
- **What CI proves and what it cannot.** The contract (218 binaries byte-identical) needs the disc, never in CI. CI proves
  the tree is public-clean and the C still compiles with the pinned toolchain; the byte proof is the local recorded run
  (`docs/verification.md`, A5). Two jobs, `ubuntu-24.04`, Python 3.12, `actions/checkout@v4` + `setup-python@v5`.
- **`audits` (≈45 s):** `audit_public` → `audit_text_sources` → `verbatim_check --strict` → `cookbook_index --check` →
  `ghidra_roster --check` → `work_evidence --selftest` → `bfm_extract/test_lzss` → `lint_symbol_refs`. Every command was
  run here under the SYSTEM python with only `requirements-python.txt` installed (no venv, no `.run/obj40`) → all rc 0.
  `cdecl.py --audit --gcc` is NOT in CI: the exhaustive form ran > 5 min here (the Makefile's `audit-cdecl` is the
  sampled form and stays in `tools-health`).
- **`compile-only`:** apt `binutils-mipsel-linux-gnu` + **`cpp-mipsel-linux-gnu`** (the MIPS `cpp` is NOT in binutils —
  measured with `dpkg -S`), cc1 from `tools/bin/gcc-2.7.2-psx.tar.gz` (`sha256sum --check --ignore-missing`, the tarball is
  flat: `cc1 cc1plus cpp g++`), submodules recursive (maspsx). PR scope = 4 binaries / 54 eligible TUs (1.6 s here); the
  weekly + dispatch form = `--all`, 4,170 TUs, 123 s at -j32 ≈ 50 CPU-min (≈13 min on a 4-core runner; job timeout 45).
- **`audit_public` controls (R39):** the current private tree FAILS naming exactly the purge set (255 offender rows: 28
  dumps, the EXE ×2 path+content, 28 `ghidra/` files, 190 `tools/psyq/`, the 3 archive parts ×2 path+size, 2 zips,
  `brave.exe`) — it goes GREEN at C3 when `git rm --cached` lands; a clean 4-path subset → OK; a renamed copy of the EXE →
  caught by content. Empty-file gotcha: two zero-length tracked `.run/` files shared the manifest SHA1 of the zero-length
  payloads SC04/SC05 `FILE_029/1.6` — zero-length files are exempt.
- **Until C3 the `audits` job is RED on purpose** (the purge set is still tracked); `compile-only` is green from the
  first push. The README statement (byte-identity verified locally with the disc) is D1's.

