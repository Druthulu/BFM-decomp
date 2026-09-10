# func_80178970 (ov_SC04_011_jr_801734BC.c): T7 agent c31 (re-draw after S103's new information)

**Final score: 2, NOT closed.** `PACK/body.c` is the S102 agent's early-return body. I re-scored it (score 2, 14 vs 15
instructions) and found nothing better. The earlier agent's files are kept in `scratch/prev_body.c` and
`scratch/prev_mechanism.md`. My probes, dumps and the corpus scan are in `scratch/c31/`.

**Verdict: the `$2` pin is irreducible in plain C on this compiler. There are two independent walls, and each one alone
deletes the copy.** S102 named only the first wall (combine). The second wall (local-alloc) is the one that makes every
"keep the copy alive" idea from today's closes useless here. I proved it on bytes (the E_s16/D1 probes below). A
whole-binary scan backs it up: every function in the binary with this byte shape is levered.

## (a) The residual

The target keeps the call-result copy `move v1,v0`, tests `$v1`, and loads the result's zero into `$v0` in the branch
delay slot:

    jal func_801789AC / nop / move v1,v0 / beqz v1,L / move v0,zero / lui+lh v0,D / nop / sltiu v0,v0,1 / L: epilogue

Mine (early return) is identical except that the copy is missing and the branch reads `$v0` (14 vs 15). Counted first:
one instruction is MISSING, and nothing else is wrong. reorg already fills the delay slot with `move v0,zero` from the
taken path.

## (b) Mechanism: two walls, both read in the source and both shown in this function's own dumps

For `move v1,v0` to exist in the bytes, the RTL needs a pseudo P (the tested value) that is set from the dying `$v0`
and read only by the branch, and P must end up in a register other than `$v0`.

**Wall 1: combine deletes the copy** (`scratch/c31/dumps_free/free.i.combine`: insn 11 is gone and the branch reads
`(reg:SI 2 v0)`). `can_combine_p` refuses a copy only in these cases:
- a set of `$v0` between the copy and its use: `use_crosses_set_p`, combine.c:914-917 and :10107-10130;
- a CALL between them, combine.c:929;
- a volatile insn (asm or unspec) between them, combine.c:985-989;
- the copy's destination still live after the use: `added_sets_2`, combine.c:1458, whose PARALLEL is then not
  recognised;
- the copy and the use in different basic blocks, because LOG_LINKs are only made inside a block, flow.c:2087.

In plain C, the only things that write `$v0` are a `jal` and a `return` (expand_value_return). `expand_return`
always evaluates into a pseudo first, because `cleanups = 1` (stmt.c:2634, :2853-2859), so the `$v0` write is always at
the end of the return arm. jump.c's "x = b; if (...) x = a" hoist (jump.c:698-790) could move a `$v0 = 0` above the
branch. It requires the then-arm to be ONE insn directly before the simplejump (jump.c:727-748). A return arm ends
`$v0 = val; (use $v0); jump`, and `D_801F1638 == 0` needs a load plus an scc. So no plain-C body puts a `$v0` write in
the window. A second live reader of P either shows up in the bytes or, on the taken path, is folded to 0 by cse's
jump equivalence before combine runs (S102 measured this).

**Wall 2: local-alloc gives the copy's destination `$v0` even when the copy survives.** P has one use in block 0,
so it is local (local-alloc.c:472: `reg_basic_block >= 0 && reg_n_deaths == 1`). block_alloc offers every operand
pair to `combine_regs`. When the used register is a hard register, `combine_regs` records it as a copy suggestion for
the pseudo's qty (local-alloc.c:1798-1818). The suggested-register pass (local-alloc.c:1469-1476) then gives P `$v0`,
because `$v0` dies at P's birth and nothing else holds it in P's range. The global pseudo `r` is allocated later and
cannot evict it. The copy becomes `move v0,v0` and is deleted.
- **Proved on bytes:** when an instruction DOES survive between the call and the test, its result still lands in
  `$v0`. With `s16`/`u16`/`u8`/`s8` return casts (E_*.c) and with `u16 v` (D1.c), the output is
  `sll v0,v0,16` / `andi v0,v0,0xffff` followed by `beqz v0`. `dumps_es16/es16.i.lreg` shows local pseudo 74, which
  holds the surviving shift, placed in hard reg 2.
- The pin breaks BOTH walls with one hard write. `dumps_tree`: insn 14 `(set (reg/v:SI 2 v0) 0)` sits between the
  copy and the branch. `.combine` keeps insn 11 (use_crosses_set_p), and `.lreg` places the copy's pseudo 73
  "in 3" (`$v1`), because `$v0` is live across its range.

The only way around wall 2 is to make P a global allocno with a lower priority than `r`. That needs P to be read in a
second basic block, and such a read would appear in the target's bytes. The target's other blocks never read `$v1`.
The lever-free functions below show this route working when the second read is real.

**Corpus evidence** (`scratch/c31/scan2.py` over all 4,284 baseline objects; shape `jal; nop; move rX,v0; beqz/bnez rX;
move v0,zero`): 9 function families.
- The 3 lever-free families (func_801823B8, func_80138DE0, func_8014CD80) all read the call result again in a later
  block, so it is a GLOBAL pseudo.
- Every family whose call result is read only by the test is levered: func_80178970 (133 pinned copies), and
  func_80180CC0 / 80181D1C / 80183790 / 80187250 (a `$2`/`$3` pin plus keepalives).
- func_8002FF0C (166 instructions, `src/800_b_2.c`) also carries a lever. I did not read its body, so it is not
  classified here.

In short, this compiler never produces this shape from plain C anywhere in the binary.

## (c) The move that got closest (6 -> 2, S102's, re-verified)

The early return: `if (v != 0) return D_801F1638 == 0; return 0;`. It deletes `r`, and with it the register swap and
the trailing `move v0,v1`. The one missing copy is the irreducible part.

## (d) Generator proposal (one sentence)

When a COUNT residual's only missing instruction is `move rX,$v0` right after a `jal`, and `rX` is read only by the
next branch, apply R-early-return. Then classify the pin as IRREDUCIBLE unless the call result also has a real reader
in another basic block; if it does, make that reader explicit so the pseudo goes global.

## (e) Today's hypotheses, tested on bytes (`scratch/c31/*.c`, each scored alone)

| hypothesis | spelling | score | why |
|---|---|---|---|
| lever-free baseline | body_free.c | 6 | both walls |
| early return (best) | A1/B2/A5/prev_body | **2** | wall 1 folds the copy |
| narrow result `r` (c4/c18) | `s16`/`u8`/`u16 r` (C1-C3), `s16` function return (C4) | 6 | `r` is not the problem; P still takes `$v0` |
| narrow test value (c4) | `u16 v` + early return (D1) | 2 MIXED | `andi v0,v0,0xffff` replaces the move, and the result stays in `$v0` (wall 2) |
| narrow callee return type | `s16/u16/u8/s8 (*)(void)` (E_*) | 2 MIXED | an extension, not a copy (combine.c:7932 needs sign-bit copies it cannot know for a call value); the result is in `$v0` |
| real callee arity (argcheck) | `func_80178970(s32 arg0)` passing `arg0` (B1/B2) | 6 / 2 | the arg pseudo is tied to `$a0` and changes nothing near the call result |
| `&&` / `?:` into the return | T1, T2, A2, A3, T4 | 5 / 6 / 5 / 5 / 10 | `expand_return` computes into a pseudo (stmt.c:2859), so there is no early `$v0` write |
| second user (c25 `added_sets_2`) | `else r = v` (F1), `v = D==0; else v = 0` (F2), `r = v` (M2), merged (M1) | 6 / 3 / 3 / 3 | cse folds the taken-path reader to 0, or merges `r`/`v` into one pseudo that takes `$v0` |
| make_regs_eqv "mentioned last" (c3/c12) | n/a | n/a | the copy's source is a hard register, and cse.c:840-842 already makes the pseudo canonical; there is no second pseudo in the class to reorder |

None of these used a pin, asm, volatile, a zero term, a dead assignment or a do-while.

## (f) Where the method fell short

1. The METHOD's closing idioms (c4, c18, c25) all keep an instruction alive past cse or combine. None of them says
   what happens NEXT: an instruction that survives still loses its register to local-alloc's hard-register copy
   suggestion (local-alloc.c:1798). A check such as "does the surviving value's pseudo stay out of the source's hard
   register?" belongs next to them. The S102 reading stopped at combine and so missed wall 2.
2. The fastest settling step was a whole-binary byte-shape scan with a lever-free/levered split: 30 lines of Python and
   about 2 minutes. It turns "no spelling found" into "the compiler never emits this without a lever". It should be a
   tool (`tools/shape_census.py <regex over mnemonics>` -> families x {free, levered}) and a standard pack field.
3. The scan's NODEF rows were bodies inside `src/shared/ov/*.h`. A census has to resolve `#include`d shared bodies.
