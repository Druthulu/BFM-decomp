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
and on a row whose name no longer exists in any symbol file. The ledger started empty on purpose, so that no evidence
was invented for the 1,083 names inherited from earlier phases. In 3.43 each of them got a row citing its real source,
and `--gate-citations` now fails on any curated name that has no citation.

## Naming conventions

*Written at 3.43 T7 with the first naming batch; every later batch follows them.*

**Style.** The baseline is [`docs/gen3-standards.md`](../gen3-standards.md) section 2: functions and types are
`PascalCase` (`UpdateCamera`), globals are `g_PascalCase` (`g_PlayerHp`), and data private to one source file are
`s_PascalCase`. Clear is better than short. A name says what the thing does or holds. It never says how sure we are,
because confidence lives in the ledger.

**`guess_` comes first.** A best guess is the name it would have if confirmed, with `guess_` in front:
`guess_UpdateCamera`, `guess_g_ActiveCamera`, `guess_s_<Name>`. Removing `guess_` gives the confirmed name, so
confirming a guess is a rename that drops exactly that prefix and turns its ledger row from guess to cited. The tools
depend on this position: the ledger check and the worklist check read the tier from a leading `guess_`. The `s_`
prefix is only for a datum that is defined in, and used by, one source file (a C `static`). Every datum named so far is
global: it sits in a symbol file and many binaries read it.

**When a name is cited.** A name is cited (no prefix) only when its meaning comes from a recorded source outside our
own reading of the code. The sources that count are a library symbol (a linked or byte-matched SDK object), a string the
game prints, a debug-menu entry, a live-RAM observation that meets the project's bar (at least three consistent
datapoints or a controlled before/after), and a community label verified to that same bar. The citation points at the
record, for example `docs/memory-map.md:365`. A name we choose from reading the code is a guess whatever its
confidence, even when the body leaves no doubt: a dot product is `guess_Vec3sDotAdd`. This is the standards' rule that a
model may propose a name but never assert one. A community label that is reported but not verified also gives a guess,
with evidence `community label`.

**What a basis quotes.** The basis is the fact the name rests on, quoted with where it is, so that a reader can check it
without trusting us. It can be the operation the code performs (the offsets, constants or expression), a callee's
name together with where that name comes from (the linker map, for a library function reached through a `func_`
alias), or a memory-map row with its datapoints. A basis never restates the name in other words. When a guess leans on
another guess it says so, for example `"player" rests on guess_g_PlayerActor (low)`, so that new evidence about one
can be carried to the other. Confidence is `high` when the body alone determines the name, `medium` when the role is
inferred from callers, callees or neighbouring data, and `low` when the name rests on one unverified source or on another
low guess. The evidence kind is the strongest one the basis actually uses: `xref chain` when it rests on a named
neighbour, which it then quotes, and `code inference` when it rests only on the body.

**The header comment.** Every named function has a comment directly above each definition of it: in the shared header
for a class (the header is its one source), in each private copy for a family kept as copies (ledgered in
`config/dedup_exceptions.tsv`), and in the `.c` file for a single instance. The template:

```c
/* guess_SetState: sets a state machine's state (s16 at +0x0) to a1 and resets its step counter (s16 at +0x2).
 * Confidence medium, code inference: 95 callers pass constant states; one saves the old +0x0 value first.
 * Names ledger: config/names.tsv guess_SetState */
```

The first line is the name and what the function does. The second gives the confidence, the evidence kind and a
shortened basis. The third points at the ledger row, which holds the full basis with its line references. A cited
name's comment ends with `Citation: <the ledger citation>` instead. Data get no comment: their ledger row is the record.

**A class at several addresses.** A naming unit is one body, identified by its hash, and it can sit at several
addresses. Each address is a different function in the original program, and only the body is shared. One name covers
every instance only when it describes the body itself, which is byte-identical at every address (`guess_Vec3sDotAdd` at
3 addresses). A binary holding several copies names them `Name`, `Name_2` and so on, with the copy in the shared
overlay base first. When the body is too trivial to say what any copy was for, the class is not named as one. The empty
function `func_80014554`, at 726 unrelated addresses, stays unnamed until each group can be named from what its callers
use it for.

A placeholder is derived from an address, so the same `func_`/`D_` token can name unrelated functions in two binaries
that load at the same address. The rename tool rewrites a token in every file, whichever binary the file belongs to. A
copy whose placeholder also names a different function elsewhere therefore waits until the rename can be limited to the
binaries the copy is in. Module files (`md_*`) that call an overlay function through its placeholder get the new name in
their own symbol file, because at run time the call reaches the same function.

**No evidence.** A unit we cannot name honestly keeps its `func_`/`D_` placeholder. Its row in
`config/names_worklist.tsv` says `no-evidence` and gives the reason. Every row of that worklist ends as `cited`,
`guess` or `no-evidence`.

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
