# xsig

Relocation-masked function signatures for finding shared code across MIPS (PlayStation-era) projects.

Two projects that compile the same source with the same compiler produce byte-identical machine code except in the
operand fields the linker fills in: `j`/`jal` targets and `%hi`/`%lo` address halves. `xsig` hashes a per-function
signature that masks exactly those fields and keeps everything else (opcodes, registers, real constants, branch
offsets). Equal signatures mean the same function, linked at a different address.

It was written for the [Brave Fencer Musashi decompilation](https://github.com/Druthulu/BFM-decomp) to answer one
question about its unmatched functions: does any sibling decompilation already have this body?

Single stdlib Python file, MIPS only, MIT.

## What it found

In BFM-decomp the unmatched functions of every binary were signed and joined against three sibling decompilations
built with the same gcc 2.7.2 toolchain, each compiled to objects and listed with `objdump -dr`:
[Xenogears](https://github.com/ladysilverberg/xenogears-decomp), [Vagrant Story](https://github.com/ser-pounce/rood-reverse)
and [Tomba!](https://github.com/hansbonini/psx_tomba).

| Join | Hits | What they were |
|---|---|---|
| BFM x Xenogears + Vagrant Story | 103 (57 + 46) | all PsyQ library or BIOS functions: `libapi` 34, `libcd` 14, `libetc` 14, `libspu` 11, `libcard` 7, the rest other SDK units. Largest: `_spu_setReverbAttr` at 307 instructions. 37 of the 103 were already named as library code. |
| BFM x Tomba! | 126 | 124 library functions (77 high-confidence), one 19-instruction non-library hit, and one 2-instruction shape shared by 16 locations (a generic epilogue). |

Result: shared byte-identical code existed only in the PsyQ library objects, no engine code. That closed the
question in an afternoon with byte evidence, and the library hits fed the project's other approach of linking Sony's
real objects instead of decompiling them. The question transfers to any decompilation with same-compiler neighbours.

## The signature

```
sig = sha1(little-endian masked word stream, trailing nop words stripped)
```

- `j` / `jal` (opcode 2/3): keep the 6-bit opcode, mask the 26-bit target. Decided by opcode, no relocation record
  needed.
- An instruction with a HI16/LO16 relocation: keep opcode + `rs` + `rt`, mask the low 16 bits. The relocation is read
  from the input: a splat-style `.s` line whose operands contain `%hi(` or `%lo(`, or an `objdump -dr` listing whose
  next line names `R_MIPS_HI16` / `R_MIPS_LO16`.
- Everything else is kept. Registers are never masked (masking them is too loose), a constant `lui` stays a constant,
  branch offsets are position-independent and stay.
- Trailing nops are alignment padding. Stripping them on both sides removes a length ambiguity and cannot create a
  false match.

This is symmetric, explicit, and tighter than tracking `lui`/`addiu` pairs heuristically (which over-masks a genuine
constant `lui`). The cost is the input: both sides need relocation information, so a linked binary without emitted
relocations cannot be signed faithfully.

## Usage

```bash
# sign a splitter's per-function .s files (one function per file), deduplicated by signature
python3 xsig.py sign-s asm/ --project bfm --dedup -o bfm.jsonl

# sign every function in objdump -dr listings of a sibling's objects
mipsel-linux-gnu-objdump -dr build/libcd.o > libcd.txt
python3 xsig.py sign-objdump libcd.txt other.txt --project sibling -o sibling.jsonl

# join: equal signatures on both sides
python3 xsig.py cross bfm.jsonl sibling.jsonl --min-ins 8

# compare two functions instruction by instruction
python3 xsig.py verify asm/func_80044B14.s libcd.txt --name-b CD_flush

# built-in property checks
python3 xsig.py selftest
```

Records are JSON Lines: `{project, tu, name, kind, sig, nins, nins_raw, mnem_head, path}` (`--dedup` adds `n_loc` and
`locs`). `cross` prints a TSV of hits sorted by instruction count after a line giving the record and unique-signature
counts on each side. `verify` exits 0 only when the two functions are identical up to relocation and classifies each
differing instruction as `opcode`, `register`, `immediate` or `length`.

Library use: `import xsig` and call `signature(pairs)`, `parse_splat_s(path)`, `parse_objdump_dr(text)` or
`compare(pairs_a, pairs_b)`, where `pairs` is a list of `(raw_word, is_address_immediate)`.

## Tests

`python3 tests/test_xsig.py` runs eight checks on committed fixtures that contain no game bytes: one small function
([`tests/fixture.c`](tests/fixture.c)) compiled once with the gcc 2.7.2 toolchain and linked at two different addresses
with `--emit-relocs`, listed with objdump (the relocation records are merged into the listing by
[`tests/make_fixtures.sh`](tests/make_fixtures.sh)), plus a splat-style `.s` rendering of the same function and a second,
different function. The tests check that the same function at two link addresses signs identically while its raw words
differ, that the relocated fields are the only masked ones, that a different function signs differently, that a one-bit
register flip changes the signature and is classified as `register`, that the two front-ends agree, that `sign-objdump`
plus `cross` find exactly the two true pairs, and that `verify` accepts the pair and rejects the mismatch.

## Limits

- Same compiler, same flags, same conventions on both sides. Xenogears had to be signed under both its own `-G8` and
  BFM's `-G0` convention, since `-G` changes `gp`-relative addressing and therefore the bytes.
- A hit says the bytes are shared, nothing more. Small generic shapes (a two-instruction epilogue) collide across
  unrelated functions; filter by instruction count and read the `verify` output.
- MIPS I encodings. Relocation kinds handled: `R_MIPS_26`, `R_MIPS_HI16`, `R_MIPS_LO16` (PC16 is kept on purpose).

## Provenance

Written in June 2026 for BFM-decomp's cross-project dedup probe, packaged as a standalone tool in September 2026. The
method and the campaign it served are documented in the BFM-decomp repository.

## License

MIT, see [`LICENSE`](LICENSE).
