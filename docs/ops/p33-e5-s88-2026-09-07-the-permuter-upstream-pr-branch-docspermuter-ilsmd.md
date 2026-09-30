### P33 E5 (S88, 2026-09-07) — the permuter upstream PR branch + `docs/permuter-ils.md`
- **The PR (PR-1).** `RelocMaskedScorer` in `src/reloc_scorer.py` — the in-tree `masked_diff.diff_object_object` rule
  (mask from the TARGET's relocation records: `R_MIPS_26` → opcode only; the 16-bit-immediate relocs → opcode+rs+rt; a `j`
  against `.text` compared relative to the function start; everything else the full word; symbol+addend equality at
  masked slots; `score = mismatches + |Δlength|`, 0 iff link-identical) written for upstream `main` at `41bd0bfc` (39
  commits past our pin `b44b0622`; `Scorer.__init__` gained `ign_branch_targets` + `objdump_command`, which is why
  `tools/permuter/run_masked.py`'s rebind targets the PIN, not HEAD). A `Scorer` subclass (no change to `Permuter` /
  `Candidate`); `--score-mode {mnemonic,reloc-masked}` + `score_mode` in settings.toml (default unchanged); refused with
  `-J` (`src/net/evaluator.py` builds a stock `Scorer`, `net/client.py` reads `scorer.stack_differences/algorithm` — the
  subclass carries both); MIPS only (raises otherwise); USAGE/README/example_settings notes.
- **Verified at the commit:** `test/test_reloc_scorer.py` 10/10 on an embedded `objdump -drz` listing of the xsig
  fixture object (real gcc 2.7.2 output, no game bytes; the end-to-end test feeds the scorer through
  `objdump_command="cat"` with a 20-byte MIPS ELF header in front of the listing — `get_arch` reads ident + e_machine);
  `black --check` clean on the touched files; `mypy` = upstream's baseline (5 pre-existing errors: `toml` stubs,
  `Levenshtein`, `helpers.py` Any — none added; checked by stashing); `./run-tests.sh`: only `test_perm` fails (needs
  `mips-linux-gnu-gcc`, absent here); **the real permuter end to end** on `.run/P33/permuter-e2e/` (our `compile.sh`,
  `settings.toml` `objdump_command = "mipsel-linux-gnu-objdump -drz -m mips:4300"` — upstream looks for
  `mips-linux-gnu-objdump`): base == target → base score 0 → `--stop-on-zero`; a swapped-operand `other()` (5 ins) →
  reloc-masked base 4 → **score 0 at iteration 256** (<40 s, `-j4`) while the DEFAULT scorer read the same base as **3,585**
  (3,420 after 20 iterations) — the floor in miniature. A dev venv (`.venv-dev/`, mypy 2.3.1 + black 26.5.1 +
  toml + pycparser) lives in the scratch clone, never in the project venv.
- **PR-2 / the issue:** the MIPS symbol wildcard `"." in field` (`scorer.py:68/72`) — issue text in `docs/permuter-ils.md`
  §3 (a configurable `symbol_regex`). **The recipe:** §4 of the same doc — the ILS warm restart and its five guards
  (hidden pins re-hidden per cycle, refused-cycle abort, comment strip, flushed stdout, winner ≠ bank).
- **Drew:** fork upstream, `git -C .run/P33/permuter-upstream push -u fork reloc-masked-scorer`, open the PR (the commit
  message is the description), then file the issue. The patch file is the tracked copy (R20); the scratch clone is
  regenerable from it.


