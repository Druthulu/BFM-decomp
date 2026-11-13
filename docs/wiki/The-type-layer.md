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
  row is keyed by callee, definition file and kind, and its cause column records the instruction that moves when the
  lie is removed. Since Phase 3.44 the kind is a signature rule and each row also carries instruction cites that a tool
  re-checks against the game's bytes (next section).

The rules for the macros and the residue are in [`docs/gen3-standards.md`](../gen3-standards.md).

## Function signatures: what the census says

A byte-identical build does not prove a prototype. gcc compiles a call through a wrong declaration without complaint,
and a declaration with empty parentheses `()` checks nothing at all. So in Phase 3.44 every prototype in the tree was
measured against the original machine code, the one source that cannot be wrong about it.
[`tools/sig_evidence.py`](../../tools/sig_evidence.py) reads every function in all 218 binaries and records the calling
contract the shipped code actually used, with the instruction that proves each answer. Functions with identical bytes
are measured once, as a class: 92,716 classes over 363,457 copies. Every function's definition and declarations now
agree with that contract, or the disagreement is ledgered with its cited instructions. The full rules are in
[`docs/ops/sig-evidence.md`](../ops/sig-evidence.md).

**The return verdict.** Each class gets one of three verdicts on whether its return value matters:

- `used` (11,345 classes at the Phase 3.44 close): at least one caller reads the return register `$v0` after the call
  before overwriting it. The row cites that read, for example an `andi $v0,$v0,0xff` or a store of `$v0`. The function
  really returns something, and its prototype must not be `void`.
- `unused` (18,026): every call site is known, and none reads `$v0`. The function may be `void`, but declaring it
  `void` is a byte question too, because a declaration can change register allocation in the caller.
- `unknown` (63,345): the bytes cannot settle it, and the row names the reason. That is not a failure of the tool; it
  is the honest answer. The commonest reasons are `indirect call` (the function is only reached through a pointer, so
  no call site can be credited with the read, 39,473 classes), `no callers` (8,837), `tail position unresolved` (the
  result is passed on as its caller's own return, whose use is itself unknown, 7,098) and `address taken` (direct
  callers ignore it, but a pointer call elsewhere might not, 6,287). For an `unknown` function the prototype follows
  the definition's C, and a modder should not assume the return is dead.

The census also records how many arguments the function reads (from its own reads of `$a0`-`$a3` and of the stack
slots above its frame), how many its callers set, and any width or sign evidence. One caution about width: under this
compiler the calling convention never widens or narrows a value at a call. An `andi 0xff` or an `lbu` next to a call is
a conversion that some C wrote, either in the callee or in the caller, so it supports a byte type but does not prove
one.

**Regenerating it.** The census needs a built tree, as after `make check-all`, and writes to `build/sig_evidence/`,
which is never committed because it holds instruction text from the game:

```
python3 tools/sig_evidence.py -j 16              # the census (about 20 s): census.jsonl, summary.txt
python3 tools/sig_evidence.py --show main:0x80028D9C   # the row for one function
python3 tools/sig_evidence.py --check -j 16      # compare with the C and verify the ledgers (about a minute)
```

`make tools-health` runs all three, so a declaration retyped against its definition, or a ledger cite that no longer
matches the bytes, fails the health check.

**Reading a ledgered exception.** A few places in the C deliberately keep what the shipped game did when the original
code was inconsistent with itself. They live in three files, each row carrying `cites` as
`<binary>:<address> <instruction>`, which `--check` re-decodes from the game's bytes:

- [`config/lying_exceptions.tsv`](../../config/lying_exceptions.tsv): `callee def_file kind cause task cites`. A
  declaration that still disagrees with its definition. `kind` names the rule (`return` for a return type, `DECL-EMPTY`
  for a `()` declaration, `ARG-OVER`, `DECL-ARITY`), and `cause` says why it stays: `SHARED-DECL-SPLIT` means one
  declaration in a shared header serves copies whose definitions disagree, so no single prototype fits;
  `DECL-EMPTY-CONFLICT` means giving the declaration its prototype changed the compiled code.
- [`config/ret_view_casts.tsv`](../../config/ret_view_casts.tsv): one row per `RET_AS(T, fn, params)` view. The
  function keeps its one prototype, but at these calls the shipped caller read the result as another type `T` (for
  example, the whole register after a callee that returns a byte), so the call is written through a marked cast.
- [`config/kr_view_casts.tsv`](../../config/kr_view_casts.tsv): one row per function called through `KR_AS(T, fn)`,
  where the original called it with fewer arguments than it reads.

To check a row by hand, open the game's disassembly at each cited address. The instruction there should be the one
quoted, and the cause should explain it. A call written `RET_AS` or `KR_AS` is not a mistake to tidy up: removing it
changes the bytes.

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
`ghidra_types.py --check`, and then the signature census and its `--check`. The Ghidra proof needs Ghidra and the extracted programs, so it runs on demand rather than
in the health check. See [Verification and progress](Verification-and-progress.md).
