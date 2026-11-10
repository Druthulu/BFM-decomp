# Names and renames

*Written at Phase 3.42 (2026-11-10), when the naming machinery was built and no name had landed yet. The names come in
3.43.*

A rename does not change a byte, so the byte gate cannot tell a finished rename from a half-finished one. The machinery
below exists to close that gap: a ledger that records why each name is believed, a scanner that proves every mention was
rewritten, a tool that performs the rename, and a ranking that says which names to choose first.

## The names ledger and the `guess_` tier

[`config/names.tsv`](../../config/names.tsv) holds one row per name that needs its evidence on record. The 11 fields are
the ones rule 1 of [`docs/gen3-standards.md`](../gen3-standards.md) asks for: name, kind, scope, addr, tier, basis,
confidence, evidence, conflict, history and citation.

- A **cited** name points at its source, for example a PsyQ library symbol or a string in the game.
- A **`guess_`** name is a name inferred from the code without proof, such as `guess_ClearTbl40` for a function that
  clears a 0x40-byte table. It may sit in the tree, but only with a ledger row that records its basis, its confidence and
  the kind of evidence. So a reader can always tell a guess from a proof by the name alone.

`tools/rename_scan.py --ledger` runs in `make tools-health`. It fails on a `guess_` name that has no row with a basis,
and on a row whose name no longer exists in any symbol file. The ledger started empty on purpose: the 1,083 curated
names from earlier phases have no citation row yet, and writing one for them would invent evidence. The check prints
that count, and `--gate-citations` turns it into a failure when the project is ready to require citations.

## The scanner: assert your coverage (R32)

[`tools/rename_scan.py`](../../tools/rename_scan.py) takes a rename (`--spec` file, or `--range A..B` to read the
renames from a commit range's symbol-file diff). It collects every spelling of the old name and of its address across
all tracked files, then makes each hit account for itself:

| class | meaning |
|---|---|
| history | a record that is never rewritten (phase-ends, cookbook, the decision log, raw logs) |
| rewritten | the line now carries the new name |
| address-key | a file keyed by address, not by name (share headers, the closed `ADDRESS_KEYED` list) |
| stale-build-input | the old name is still in something the build reads |
| stale-invisible | the old name is still somewhere the build does not read |
| unclassified | a bare address the scanner cannot place |

A rename lands only at 0 stale and 0 unclassified. The scanner asserts its coverage twice: for each rename, the
candidates equal the classified hits, and every grep hit belongs to some rename. Names that a generator derives from
the address (`func_<ADDR>` in `docs/duplicates.md`) pass only through the closed `NAMES_FROM_VRAM` list. Both closed
lists grow only by a reviewed edit, never at rename time.

## Applying a rename

[`tools/rename_sym.py`](../../tools/rename_sym.py) `--spec <tsv> [--dry-run]` writes the symbol line in each binary's
symbol file, rewrites every live mention, adds the names-ledger row, and prints the binaries to gate, the Ghidra
programs to re-apply and the generated files to regenerate. It never edits a generated file itself. Share headers are
keyed by address or class hash, so a function rename touches only the `#define SHARED_FN` lines that name it and the
registry's member names ([The dedup engine](The-dedup-engine.md)).

The tool was proven on the fixture [`config/rename_known.tsv`](../../config/rename_known.tsv), in a scratch worktree
that was then thrown away:

- **Positive control.** `func_80037004 -> guess_ClearTbl40` stayed byte-identical, and the scanner found 0 stale. An
  independent grep found the same 89 candidates, line for line.
- **Negative control.** One mention in `config/dedup.us.yaml` was left unrewritten. The byte gate stayed green and the
  scanner failed on exactly that line. This is the case the scanner exists for.

## Which names first: the leverage ranking

[`tools/leverage_rank.py`](../../tools/leverage_rank.py) ranks every function class and data address by how many places
in the de-duplicated source its name would appear. References come from the relocations of our own build, counted once
per unique body, so the ranking stays put as copies move into shared headers. Units also get credit for the struct
types they anchor and a damped bonus for bodies shared across many binaries. Its outputs are
[`docs/leverage.md`](../leverage.md) (method, weights, controls, top 50) and `docs/leverage.tsv` (every unit). The first
500 unnamed units cover about 35% of all references, and they are 3.43's naming list.
