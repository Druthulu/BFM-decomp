# func_80133784 (ov_MAIN_012) — T7 agent c39 (S103), a PORT of c23's close (R71)

**Score 0 (`mine 203 ins, target 203`), no lever of any kind, on the FIRST `--try`** (`PACK/body.c`). Levers in the tree:
pins `$19` s3, `$20` s4, `$21` arg0s, `$3` retc, two `addu` asm instructions and one keepalive. Start `body_free.c` = 21,
mechanical best 18.

## (a) The residual in one sentence

The same residual as the ov_SC04_011 sibling: the flag lands in `$s5` instead of `$s2` (its `sltiu → move s2,v0` copy is
folded), the call argument's `sll` is hoisted out of the loop into a callee-saved register, and the call result's
`move v1,v0` copy is missing (201 vs 203 ins).

## (b) The passes and the decisions

Not re-derived — the bytes are the sibling's, so the mechanism is c23's (`../ov_SC04_011__func_80133784/mechanism.md`):
loop.c `move_movables`' desirability test (`loop.c:1631`, threshold ≈ 29 with a call, `loop.c:532`) refuses to hoist the
argument `sll` once the timeout block sits INSIDE a real `while (1)` (insn_count 28 → 38), while the flag's test
extension still hoists; the flag must be `s16` so its store is a HImode SUBREG move that survives cse's `(set REG0 REG1)`
fold (`cse.c:7440-7474`) and combine (`combine.c:9645-9670`, `:3711-3730`). Proved here only by the bytes (score 0), not by
fresh dumps.

## (c) The source moves (21 → 0) — c23's text with the symbol remap

1. The timeout block (`if (tries++ >= 5) { copy box; flags = 0x2000; goto store_out; }`) INSIDE a real `while (1)`.
2. The flag as `s16 same`.
3. One variable `r` for both call results; the call `func_80133AB0(mode, D_8017E910->f0, D_8017E910->f4, D_80184120)`
   with `mode` (s16 copy of `arg0`) passed straight — no `arg0s`, `ret0`, `retc`, `oldc`; `break` for the two `goto after`.
4. Remap: `D_801909BC → D_8017E910`, `D_801909C0 → D_8017E914`, `D_801EDA3C → D_8018412C`, `D_801EDA40 → D_80184130`,
   `D_801EDA30 → D_80184120`.

## What differed from the banked sibling (why propagation refused)

`diff ../ov_SC04_011__func_80133784/body_tree.c body_tree.c` after the remap leaves exactly ONE extra line: a body-local
`extern s32 D_80184120;` (plus a blank line). The sibling's `D_801EDA30` is declared at FILE scope
(`src/ov_SC04_011/ov_SC04_011_jr_8012ACE0.c:2130`), so its body has no such line. In the variant TU the same global is
declared body-locally in each function that uses it (`tu_free.c:1372/1391/1408`). Declaration only — no code
difference. The port keeps the variant's body-local extern and drops the sibling tree's `*(s32*)&` cast exactly as c23 did
(the declaration is already `s32`).

## (d) GENERATOR PROPOSAL

> Same as pack A (`../ov_SC07_006__func_8012956C/mechanism.md`): propagation's "differs beyond a symbol remap" test
> should normalise away block-scope `extern T SYM;` lines (a global declared in the body in one overlay and at file scope
> in the other). Apply the banked text with the remap and KEEP the variant's own extern lines; both of this agent's
> functions would have banked with zero tokens.

## (e) What did not work

Nothing else was tried; the ported text matched on the first compile.

## (f) Where the method fell short

Nothing in the method; the propagation tool was too strict on a declaration-only difference.
