# The type layer

## What a canonical type is

A struct, union or typedef is **canonical** when it is defined once, in one of two headers:
[`include/struct_types.h`](../../include/struct_types.h) for the struct map's layouts and
[`src/shared/engine_types.h`](../../src/shared/engine_types.h) for the shared engine's types. The scalar typedefs
(`u8`, `s32` and the rest) come from `include/common.h`. Every translation unit that needs a type includes its header.
It never re-declares the type locally. Drafted code started out the other way: each decompiled file invented its own
variant of the same structure, and the Phase 37 census found 7,255 definitions once the ones inside single files were
counted. Phase 38 folded them to one definition per type. At Phase 3.41 the two headers hold 7,151 types (4,131
structs, 3,005 typedefs, 15 unions).

A type is a comprehension lever, not a byte lever, except where the compiler reads the struct spelling (gcc 2.7.2's
`MEM_IN_STRUCT_P`). So every change to the type layer goes through the byte gate like any other edit. The layer is
judged by four tools, which follow.

## The census and its gates

[`tools/type_census.py`](../../tools/type_census.py) reads every struct definition, every raw pointer-cast
dereference and every function declaration in the C. From the access patterns it clusters the cast sites into the
types the tree needs and writes [`docs/struct-map.md`](../struct-map.md). One census run gives three verdicts:

- `--check` asserts what Gen3's done-criteria name. It requires no duplicate struct definitions except the pairs that
  [`docs/struct-twins.md`](../struct-twins.md) lists with their evidence, no definitions outside the canonical headers,
  no dead canonical names, all four known-true controls passing, and no lying declaration that is not ledgered. A
  declaration lies when its argument count or its return type disagrees with the function's definition. The raw cast
  count is printed beside the verdict but does not gate here.
- `--check-structs` is the struct-unification gate: the same duplicate, outside-canon and dead counts, read against
  the same allowlists.
- `--check-casts --residue` is the per-site gate. A raw cast site passes only when a ledger row covers it with its cause,
  and a kept-cast macro passes only when it has a row. Any uncovered site fails it.

Return-type lies are a recent addition. The declaration check used to compare argument counts only, so a function
declared `void` everywhere but defined returning a value went unseen. The census now also compares return types after
resolving the canonical typedefs. Phase 3.41 found 273 such functions and fixed 254 of them, changing each one's
definition, declarations and callers as one unit. The other 19 change the compiled code whichever side is edited
(width and sign mismatches), so they stay ledgered.

## The cast ledger

Not every raw cast can go. Where the byte gate refuses a struct member in place of a cast, the cast stays, and it is
recorded in one of three places:

- **Restructuring ledger rows.** `tools/restruct.py` (rung S) writes one row per site it judged: either `RESIDUAL(<cause>)`
  for a raw cast that waits on something named (a union, a member, a layout), or `KEPT(<class>)` for a cast the bytes
  need.
- **Kept-cast macros** in `include/common.h`. Each one expands to the identical cast and names a single cause class:
  `CAST_ALIAS`, `CAST_SIGN`, `CAST_WIDTH`, `CAST_MISALIGNED`, `CAST_NONSTRUCT`, and the `LOBU/LOH/HIH/LOHU/HIHU/LOW/LOWU`
  family for a value read at another width or sign. A macro site is honest only with its ledger row.
  `M2C_FIELD`, the decompiler's own macro, is a raw form and never a kept spelling.
- **[`config/lying_exceptions.tsv`](../../config/lying_exceptions.tsv)** holds the lying declarations that stay. Each
  row is keyed by callee, definition file and kind (`arity` or `return`), and its cause column records the instruction
  that moves when the lie is removed.

The rules for the macros and the residue are in [`docs/gen3-standards.md`](../gen3-standards.md).

## The Ghidra mirror

Ghidra learns the project's types from the same two headers. [`tools/ghidra_types.py`](../../tools/ghidra_types.py)
writes the canonical types as Ghidra type rows, one file per tracked program under
[`config/ghidra/types/`](../../config/ghidra/types/), with gcc's o32 offsets and sizes. `--check` fails when a header
changed and the rows did not. [`tools/ghidra_rebuild.sh`](../../tools/ghidra_rebuild.sh) `<program> --proof` merges the
rows into the program's committed annotations, imports them into a fresh rebuild and checks that the exported delta
equals the merged file byte for byte. The proof shows that Ghidra reproduces the rows. It does not show that the layouts
are right. That is checked separately: `ghidra_types.py --gcc-compare` compares them with a real compiler's debug
output. The steps are on [Ghidra rebuild from text](Ghidra-rebuild-from-text.md#how-the-types-reach-the-database).

## Where the gates run

`make tools-health` runs `type_census.py --check --check-structs --check-casts --residue` as one call, together with
`ghidra_types.py --check`. The Ghidra proof needs Ghidra and the extracted programs, so it runs on demand rather than
in the health check. See [Verification and progress](Verification-and-progress.md).
