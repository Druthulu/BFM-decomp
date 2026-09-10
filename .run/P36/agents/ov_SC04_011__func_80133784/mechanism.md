# func_80133784 (ov_SC04_011) — mechanism (S103 agent c23, a re-draw of S102 b4)

**Final score 0.** `mine 203 ins, target 203`. The result was confirmed by re-running `--try` on `PACK/body.c`.
The body has no pin, no `asm`, no added volatile, no `do {} while (0)` and no invented zero term, and it no longer
has b4's `lim`/`mask` liveness pads. The earlier text is kept at `scratch/prev_body.c` and `scratch/prev_mechanism.md`.
All probes are in `scratch/c23/` (the harness is `h.py`, the runs are `r1.py`–`r7.py`, candidates are in `v/` and pass
dumps are in `dumps/`).

## (a) The residual in one sentence

b4's body left one mismatch, `andi v0,s2,0xffff ; bnez v0` where the target has `nop ; bnez s2`. It came from a
wrong loop shape. b4 used a `goto` loop to stop loop.c from hoisting the call argument's `sll`, but a `goto` loop also
stops loop.c from hoisting the 16-bit flag's test extension. The target hoists the flag's extension and keeps the
argument's `sll` inside the loop.

## (b) The pass and the decision (read in the source, then proven on bytes)

**loop.c `move_movables`, the desirability test at `loop.c:1631`:**
`threshold * savings * m->lifetime >= insn_count`, where `threshold = (loop_has_call ? 1 : 2) * (1 + n_non_fixed_regs)`
(`loop.c:532`). For this target that is 1 × (1 + 28): 25 GPRs plus HI, LO and HILO are non-fixed
(`mips.h:1186` FIXED_REGISTERS, with the soft-float FP registers made fixed by `CONDITIONAL_REGISTER_USAGE`
`mips.h:522`, `regclass.c:380-387`). So the threshold is about 29. `insn_count` counts every real insn between
`NOTE_INSN_LOOP_BEG` and `NOTE_INSN_LOOP_END`, including code that leaves the loop by a `goto`.

Two movables compete:

- The call argument's `(ashift (subreg:SI mode) 16)`: savings 1, life 1, so its score is 29.
- The flag test's `sll`/`sra` pair (s16 flag): savings 2, life 2, so its score is 116.

What the `.loop` dumps show (`-dL` is included in `tools/cc1_dumps_tu.sh`):

| body | `Loop from … N real insns` | argument `sll` | flag extension |
|---|---|---|---|
| `while(1)` with the timeout block after the loop (`dumps_Ws16`) | **28** | `moved` (29 ≥ 28) | moved |
| `while(1)` with the timeout block INSIDE the loop (`dumps_final`) | **38** | **`not desirable`** (29 < 38) | moved |

The timeout block is the code that runs when `tries++ >= 5`: it copies the box, sets `flags = 0x2000` and does
`goto store_out`. With that block written inside the loop body, loop.c counts 10 more insns. The argument `sll` then
stays at the loop top, which is what the target has at `8c58: sll a0,s5,0x10`. The flag's extension still leaves the
loop. In the preheader, combine turns the extension into a paradoxical-subreg copy
`(set rX (subreg:SI (reg:HI same) 0))`. `same` dies at that copy, so the allocator gives the copy and the flag the
same register. The copy becomes `move s2,s2` and is deleted, and the loop test reads `bnez s2` directly.

**Why the flag has to be `s16` (combine.c):**

- **With an s32 flag**, the `sltiu` → `move s2,v0` copy is a same-mode SI copy. cse's `(set REG0 REG1)` swap
  (`cse.c:7440-7474`, `make_regs_eqv` `cse.c:846-862`) or combine folds it, which gives `sltiu s2,…` with the copy
  missing. Score 23 in the final shape.
- **With an HImode flag**, the store is `(set (reg:HI) (subreg:HI (reg:SI seq)))`. That is a SUBREG move, so it
  survives and gives `move s2,v0`.
- **The in-loop test extension cannot be folded into the branch.** simplify_comparison strips the extension and
  widens back (`combine.c:9645-9670`). Then the simplify_rtx `(ne X 0) → X` rewrite for a 0/1 value
  (`combine.c:3711-3730`; nonzero_bits comes from `set_nonzero_bits_and_sign_copies` `combine.c:718`) leaves an
  unrecognisable `if_then_else`, so combine refuses. Proven in `dumps_s16` (combine insn 309 is left as a copy, and
  the goto-loop body gives `move v0,s2 ; bnez v0`) and in `dumps_u16` (insn 308 `zero_extendhisi2` is left, which
  gives `andi`). Only hoisting the extension out of the loop removes it.
- **A `u16` flag is worse:** `zero_extendhisi2` is a single insn with nothing to combine with, so it hoists as an
  `andi` copy and keeps `andi` in the loop. Score 14.

## (c) The source moves (one line each)

1. The timeout block (`if (tries++ >= 5) { …copy box…; flags = 0x2000; goto store_out; }`) goes INSIDE a real
   `while (1)` loop, replacing b4's `goto` loop. loop.c's `insn_count` goes from 28 to 38, so the argument `sll` is
   "not desirable" and stays in the loop.
2. The flag is `s16 same` (b4 had `u16`). The HImode store keeps `move s2,v0`, and the flag's test extension becomes
   a subreg copy that hoists out of the loop and is tied away.
3. b4's `lim = -0xBCB` / `mask = 0xFFFF` pads are deleted. They made up for the loop-depth reference weighting that
   the `goto` loop had lost (`flow.c:2067`). With a real loop the weighting is back, and removing them scores 0.
4. Kept from b4: one variable `r` for both call results. Splitting it scores 7 (b4's `find_reg` reading).
5. Cleanups, each re-scored at 0: `break` for the two `goto after`, `tries++`, and `mode` passed straight to the call
   (the `arg0s` duplicate is gone). Also removed: the redundant `(s16)` casts, the `*(s32*)&D_801EDA30` cast, and the
   argument casts (the prototype converts). Renamed: s1→flags, s2→same, s3→tries, s4→hits, a0v→mode, sx/sy/sz→dx/dy/dz.
   Also `for (;;)` scores the same 0.
6. Rejected: typed `from`/`to` pointer locals for `arg1`/`arg2`, which score 26 because the parameter copies land in
   different registers. The `((Box_80133784 *)argN)` casts stay.

## (d) Generator proposal

**`delever.loop_insn_count`:** when the target keeps an invariant (an argument `sll`, a symbol load) inside a loop
that mine hoists, and the loop has a call, compare loop.c's `threshold*savings*life` with the `.loop` dump's
`N real insns`. Then move a loop-exit block that sits right after the loop (reached by `break`/fall-through, ending
in `goto`/`return`) INTO the loop body as `if (cond) { block; goto L; }`. That raises `insn_count` without changing
the bytes and turns off the low-savings movables first. Check the `.loop` line `Insn N: … not desirable`.
**Before de-looping to a `goto` (b4's move), try this move.** A `goto` loop also stops the hoists the target DOES
have, and it loses flow's loop-depth weighting, which then has to be patched with fake liveness pads.

## (e) What did not work (byte evidence)

- The `goto` loop (b4) with each flag width. u16 scores 2 (`andi`), s16 scores 2 (`move v0,s2`), u8/s8 score 2, and
  s32/int/u32 score 11 (the `move s2,v0` is gone).
- `while(1)` with the timeout block after the loop. s16 scores 14 (the argument `sll` is hoisted into `s3` and the
  s3/s4/s5 roles rotate), u16 scores 9 and s32 scores 18.
- `same = (dx==0 && dy==0 && dz==0)` as one `&&` value, in the goto-loop body. u16/s16 score 22 and s32 scores 16:
  the `&&` value path adds a store on the false edges that the target does not have.

## (f) Where the method fell short

- No entry in METHOD_S103, `residual_moves.md` or b4's reading covers loop.c's *desirability* test. b4 read
  `invariant_p` and said `threshold` is "~60 vs ~15, never fails". Both numbers were wrong: the threshold is about
  29 and the real count is 28. In a small loop with a call the test is decided by a margin of 1. **Recommend a
  row: "invariant hoisted in mine, not in target → read `Loop from … N real insns` and the `Insn …: savings`
  lines in `.loop`".** The dump already prints the decision word for word.
- The hunk view put the residual on the flag's width, and the brief framed it as a width question ("a THIRD
  spelling"). The width was necessary (s16) but not sufficient. What decided it was where the flag's *test* was
  evaluated, in the preheader or in the loop. Reading the one sibling that closes the same shape (c10's
  func_80135A4C: "the loop test's (sign_extend eq) comes out of the loop as a copy") gave the hypothesis, and one
  `--try` proved it.
- The whole close cost about 20 `--try` compiles. The compiler-source reading (combine's comparison rewrite, then
  loop.c:1631) predicted both moves before they were tested.

## Paths

- `PACK/body.c` — the final text (score 0).
- `PACK/mechanism.md` — this file.
- `PACK/scratch/c23/` — the harness, the candidates and the pass dumps (`dumps_final`, `dumps_Ws16`, `dumps_Wctl`,
  `dumps_s16`, `dumps_u16`).
- Note for the coordinator: `src/shared/ov/func_80133784__bcb91966.h` is a twin of this function in another overlay
  (`D_8017F808`/`D_8017F80C`). The same spelling should port to it (R22/twin sweep); it was not tested here.
