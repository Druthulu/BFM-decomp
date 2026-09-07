# xsig — relocation-masked function signatures for cross-project code identification

Two projects that compile the **same source with the same compiler** emit byte-identical machine code except in the
operand fields the linker fills in — `j`/`jal` targets and `%hi`/`%lo` address halves — which differ by link address.
`xsig` hashes a per-function signature that masks exactly those fields and keeps everything else verbatim (opcodes,
registers, real constants, PC-relative branch offsets), so a shared signature means *the same function, linked
somewhere else*. It was written for the [Brave Fencer Musashi decompilation](https://github.com/Druthulu/BFM-decomp)
to ask one question of its unmatched functions: *does any sibling decompilation already have this body?*

MIPS (PlayStation-era) only. Single stdlib Python file, no dependencies. MIT.

## What it answers, and what it found

The question a byte-exact decompilation asks of its neighbours is not "is this code similar?" but "is this code the
same object?" — because if it is, the neighbour's C compiles to your bytes and the function costs nothing. In Phase 21
of BFM-decomp the unmatched functions of every binary were signed and joined against three sibling decompilations built
with the same gcc 2.7.2 toolchain — [Xenogears](https://github.com/ladysilverberg/xenogears-decomp),
[Vagrant Story](https://github.com/ser-pounce/rood-reverse) and [Tomba!](https://github.com/hansbonini/psx_tomba) —
each compiled to objects and listed with `objdump -dr`:

| Join | Hits | What they were |
|---|---|---|
| BFM × Xenogears + Vagrant Story | 103 (57 + 46) | every one a **PsyQ library or BIOS function** — `libapi` 34, `libcd` 14, `libetc` 14, `libspu` 11, `libcard` 7, the rest `libc2`/`libsn`/other SDK units; the largest `_spu_setReverbAttr` at 307 instructions; 37 of the 103 BFM functions were already named as library code |
| BFM × Tomba! | 126 | 124 library (77 high-confidence), **one** high-confidence non-library hit — a 19-instruction function — and one 2-instruction shape shared by 16 locations (a generic epilogue) |

The recorded verdict (BFM's decision log, 2026-07): *a clean negative — shared byte-identical code exists only in the
PsyQ library objects, zero engine code.* That closed a question with byte evidence in an afternoon, and the library
hits fed the project's other lever: link Sony's real objects instead of decompiling them. The tool is published because
the *question* transfers to any decompilation with same-compiler neighbours, even when the answer is "no".

## The signature

```
sig = sha1( little-endian masked word stream, trailing all-zero (nop) words stripped )
```

- `j` / `jal` (opcode 2/3): keep the 6-bit opcode, mask the 26-bit target — by opcode, no relocation record needed.
- An instruction carrying a **HI16/LO16 relocation**: keep opcode + `rs` + `rt`, mask the low 16 bits. The relocation is
  read from the input, never guessed: a splat-style `.s` line whose operands contain `%hi(` / `%lo(`, or an
  `objdump -dr` listing whose next line names `R_MIPS_HI16` / `R_MIPS_LO16`.
- Everything else is kept. **Registers are never masked** (masking them is too loose), a constant `lui` stays a
  constant, a branch offset is position-independent and stays.
- Trailing nops are inter-function alignment; stripping them on both sides removes a boundary-dependent length
  ambiguity and cannot forge a match.

Symmetric, explicit, and tighter than a heuristic that tracks `lui`/`addiu` pairs (which over-masks a genuine constant
`lui`). The price is the input: both sides need relocation information — a splitter's `.s` with `%hi`/`%lo`, or an object
listing — and a linked binary without emitted relocations cannot be signed faithfully.

## Usage

```bash
# sign a splitter's per-function .s files (one function per file), deduplicated by signature with a location list
python3 xsig.py sign-s asm/ --project bfm --dedup -o bfm.jsonl

# sign every function in objdump -dr listings of a sibling's objects
mipsel-linux-gnu-objdump -dr build/libcd.o > libcd.txt
python3 xsig.py sign-objdump libcd.txt other.txt --project sibling -o sibling.jsonl

# join: the same signature on both sides = the same function
python3 xsig.py cross bfm.jsonl sibling.jsonl --min-ins 8

# read the diff before believing any score: instruction-by-instruction comparison of two functions
python3 xsig.py verify asm/func_80044B14.s libcd.txt --name-b CD_flush

# the built-in property checks (no files)
python3 xsig.py selftest
```

Records are JSON Lines: `{project, tu, name, kind, sig, nins, nins_raw, mnem_head, path}` (`--dedup` adds `n_loc`
and `locs`). `cross` prints a TSV of hits sorted by instruction count, preceded by a coverage line (records and unique
signatures on each side — a join without its denominators is a number about an unknown world). `verify` exits 0 only
when the two functions are identical up to relocation and classifies every differing instruction as `opcode`,
`register`, `immediate` or `length`.

Library use: `import xsig` — `signature(pairs)`, `parse_splat_s(path)`, `parse_objdump_dr(text)`,
`compare(pairs_a, pairs_b)`, where `pairs` is a list of `(raw_word, is_address_immediate)`.

## Tests

`python3 tests/test_xsig.py` — eight checks on committed fixtures that contain **no game bytes**: one small function of
our own ([`tests/fixture.c`](tests/fixture.c)) compiled once with the gcc 2.7.2 toolchain and linked at two different
addresses with `--emit-relocs`, listed with `objdump` (the relocation records merged into the listing by
[`tests/make_fixtures.sh`](tests/make_fixtures.sh)), plus a splat-style `.s` rendering of the same function and a second,
different function. The tests prove: the same function at two link addresses signs identically while its raw words
differ; the relocated fields are present and are the only masked ones; a different function signs differently; a
one-bit register flip changes the signature and is classified as `register`; the two front-ends agree; the CLI's
`sign-objdump` + `cross` find exactly the two true pairs; `verify` accepts the pair and rejects the mismatch.

## Limits

- Same compiler, same flags, same conventions on both sides. Xenogears had to be signed under both its faithful `-G8`
  and BFM's `-G0` convention; a different `-G` changes `gp`-relative addressing and the bytes.
- A function is identified, not understood: a hit says the *bytes* are shared. Small generic shapes (a two-instruction
  epilogue) collide across unrelated functions — filter by instruction count, and read `verify`'s diff.
- MIPS I encodings; the relocation kinds handled are `R_MIPS_26`, `R_MIPS_HI16`, `R_MIPS_LO16` (PC16 is kept on purpose).

## Provenance

Written 2026-06-25 (BFM-decomp Phase 21, session "xdedup"), packaged 2026-09-07 (Phase 33). The method, the campaign it
served and the records it cites are in the BFM-decomp repository: the decision log, `docs/how-to-ai-decomp/`, and the
SETUP inventory row for `tools/xsig/`.

## License

MIT — see [`LICENSE`](LICENSE).
