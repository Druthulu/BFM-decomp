# tools/

Everything under `tools/` that this project wrote — the extractor, the byte gate, the matching harness, the campaign
machinery, the audits, the Ghidra scripts, the public-flip rewrite package — is licensed under the **GNU Affero General
Public License v3.0** (the repository's `LICENSE`). There are no per-file license headers; this statement covers them.

Third-party pieces under `tools/` keep their own licenses and are listed in the top-level `THIRD_PARTY.md`:
`tools/brave-CUE/` (GPL-3.0, vendored source), the pinned submodules `tools/maspsx` (MIT), `tools/decomp-permuter`
(MIT), `tools/asm-differ` (Unlicense) and `tools/m2c` (GPL-3.0), and the gcc-2.7.2 compiler tarballs under `tools/bin/`
(GCC, GPL). The Sony SDK directory `tools/psyq/` is never part of the repository — it is user-supplied and gitignored.

Where each tool fits and how to run it: `docs/SETUP.md` ("Tooling inventory"), `docs/wave-playbook.md` (the matching
procedure) and `docs/public-flip-runbook.md` (the publication procedure).
