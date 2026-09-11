# func_8012956C (ov_SC07_006) — T7 agent c39 (S103), a PORT of c24's close (R71)

**Score 0, no lever of any kind, on the FIRST `--try`** (`PACK/body.c`). Levers in the tree: pins `$7` temp_a3,
`$4` arg0, `$3` s2 + one `__asm__("")` at the head of `do_default:`. Start `body_free.c` = 11 (same 11 as the sibling).

## (a) The residual in one sentence

Identical to the ov_SC04_011 sibling's residual line for line (`residual.txt` is the same 11-point COUNT diff): the `j` into
the default block steals its first insn (`sll a1`) where the target leaves `nop`, and the `f38` load is scheduled before
`f40` inside the default block.

## (b) The passes and the decisions

Not re-derived — the bytes are the sibling's, so the mechanism is c24's
(`../ov_SC04_011__func_8012956C/mechanism.md`): (1) reorg's two passes (`reorg.c:4326-4332`; pass 2's
`steal_delay_list_from_fallthrough`, `reorg.c:1699`, empties the `j`'s slot) once `i + 3` is computed at the default block's
head instead of in the dispatch, with the dispatch a `switch` whose empty `case 0x7FFF` is FIRST (`stmt.c:5654` +
`jump.c:1725-1757` invert the last test into `bne → default; j end`); (2) the `$7` pin faked a phantom 4th argument to the
3-parameter K&R `func_801299C8` (its definition is in this very TU, `ov_SC07_006.c:692`: `(arg0, arg1, arg2)`), whose
`a3` copy made sched1 put the f38 load first. Proved here only by the bytes (score 0), not by fresh dumps.

## (c) The source moves (11 → 0)

1. `func_801299C8(D_801F62E0, (s16)(i + 3), base);` at the real 3-argument arity, no cast; the two sums written directly
   (`base->f1C = base->f40 + base->f38; base->f1E = base->f42 + base->f3A;`); the `a1`/`arg0`/`temp_a3`/`s`/`s2`/`t6`/`code`
   locals gone.
2. The `goto` dispatch as `switch (base->f34)` with cases `0x7FFF` (empty `break`), `0x7FFD`, `0x7FFE`, `default`.

## What differed from the banked sibling (why propagation refused)

`diff ../ov_SC04_011__func_8012956C/body_tree.c body_tree.c` after the symbol remap
(`D_801ED9C4..CA → D_801F4D5C..62`, `D_801F1620 → D_801F62E0`) leaves exactly ONE extra line: a body-local
`extern s32 D_801F4D5C;` at the top of the function. The sibling's counterpart `D_801ED9C4` is declared at FILE scope
(`src/ov_SC04_011/ov_SC04_011.c:66`), so the sibling's body has no such line. It is a declaration only — no code
difference. The port keeps the variant's body-local extern and otherwise is the banked text with the remap.

## (d) GENERATOR PROPOSAL

> Propagation's "text differs beyond a symbol remap" test should ignore (or normalise) block-scope `extern T SYM;`
> declarations — when the only non-remap delta between a variant and a banked sibling is an `extern` declaration line
> (added/removed/moved between file and block scope), apply the banked text with the remap and KEEP the variant's own
> extern lines. This variant would then have banked with zero tokens.

## (e) What did not work

Nothing else was tried; the ported text matched on the first compile.

## (f) Where the method fell short

Nothing in the method; the tool (propagation) was too strict on a declaration-only difference. The brief's "diff against
the sibling's pre-bank shape" step found it in one command.
