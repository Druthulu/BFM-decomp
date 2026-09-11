# func_80182A2C — agent c53 (S103) — CLOSED, score 0, no lever

## (a) Residual
COUNT 143 vs 145: both matrix-pool allocations load the pool cursor straight into `$s1` where the target loads it into a
caller-saved temp (`lw v0` / `lw v1`) and copies it (`move s1,v0` / `move s1,v1`); the following `+0x20` then reads `$s1`.
Two instructions missing, no register permutation beyond that.

## (b) Mechanism (pass + decision), read from dumps of both spellings
The lever-free text `tmp = D_801A6A2C; puVar2 = tmp;` expands to a load immediately followed by the copy, and cse's
`(set REG0 REG1)` special case (`cse.c:7440-7474`, the swap at `:7454`) retargets the load into `puVar2` and kills the
copy — that is why the tree needed the `$2`/`$3` pins (a hard-register source is excluded from that swap).

The original is a **post-increment of a pool pointer typed as a 32-byte struct** (`MATRIX *`): `m = D_801A6A2C++;`.
- `expand_increment` (`expr.c:8644-8660`) for a post-increment of a MEM that addsi3 cannot take as operand 0: the old
  value is `copy_to_reg`'d (T = load), `expand_binop` computes T+32 into a new pseudo and `emit_move_insn` stores it,
  and only THEN does the assignment emit `m = T` (`.rtl` insns 151/153/155/157). The copy is no longer adjacent to its
  producer, so `cse.c:7454` cannot fire; `m` stays the canonical register of the qty.
- sched1 hoists the copy `m = T` above the add (the `.sched`/`.lreg` order becomes 151, 157, 153, 155).
- local-alloc's `update_equiv_regs` calls `optimize_reg_copy_1` (`local-alloc.c:1007` → `:700-853`): T is not dead at
  the copy and dies in the add, so the add is rewritten to read `m` and T's death note moves to the copy. T is now a
  two-insn local → `$v0`; `m` crosses calls → `$s1`. Result: `lw v0; move s1,v0; addiu v0,s1,32` — the target.
- **The ONE variable `m` for both allocations is required** (proven on bytes: a second variable `m2` for the second
  allocation scores 15). In `.cse2` of the two-variable spelling, pseudo 104 (the load temp) becomes the qty's canonical
  register, every use of `m` is replaced by it and flow deletes the copy (`make_regs_eqv`, `cse.c:840-862`: `m` must
  live beyond the extended block and longer than the temp — a single `m` live into the second allocation's block does;
  a block-1-only `m` does not). The two allocations ARE one role (the freshly taken pool matrix), both in `$s1` in the
  target, so this is not a reuse of one name for unrelated values.

Proven on bytes: the close (score 0), the two-variable failure (15), `D_801A6A2C += 0x20` form (8, the load goes straight
into `m`), a chained `m = *(...) = D_801A6A2C` (6). Proven in dumps: the expansion order, the sched1 hoist, the
`optimize_reg_copy_1` rewrite, the `.cse2` canonical-register flip for two variables. Not proven: exactly which cse path
processing makes `m` canonical (the whole-function path and the `32 to 176` path both cover insn 157).

## (c) The move
```c
extern MATRIX *D_801A6A2C;     /* matrix pool cursor */
extern MATRIX D_801B2AE8[];    /* matrix pool end */
MATRIX *m;
...
m = D_801A6A2C++;
*(MATRIX **)(param_1 + 0xcc) = m;
if (D_801A6A2C > D_801B2AE8) {
    D_801A6A2C = D_801B2AE8 - 9;       /* 9 * 0x20 = 0x120 */
}
```
(same for the second allocation into `+0xd0`, reusing `m`). Both externs are body-local and used by no other function
in the TU (grep), so the retyping is inside the body. An equivalent but uglier spelling also matches:
`puVar2 = (D_801A6A2C += 0x20) - 0x20;` (score 0) — the post-increment is the natural one.

## (d) Generator proposal
When the residual is `lw vN,SYM` + `move sK,vN` missing (mine loads `SYM` straight into `sK`) and the next insn adds a
constant C to the loaded pointer and stores it back to `SYM`, rewrite `p = SYM; SYM = p + C;` as a post-increment
`p = SYM++;` with `SYM` retyped as a pointer to a C-byte struct (or `(SYM += C) - C` if no such type exists), keeping one
variable for every such allocation in the function.

This applies verbatim to the 11 other copies (ov_SC06_008, SC06_018, SC06_024, SC06_032, SC03_121, SC02_000, SC02_016,
SC01_084, ... — `grep -rn ' - 0x120;$' src/`): each has the same pinned `tmp` block with its own pool symbols.

## (e) What did not work
- `puVar2 = D; D += 0x20;` → 8 (cse forwards the re-load of D from `puVar2`; the load goes straight into `$s1`).
- `puVar2 = *(char **)(param_1+0xcc) = D; D = puVar2 + 0x20;` → 6 (the store to 0xcc reads the temp).
- post-increment with a second variable `m2` for the second allocation → 15 (see (b)).

## (f) Method notes
The residual was an idiom question, not an allocation question: the alloc table was never needed. Reading
`expand_increment`'s emission order predicted a non-adjacent copy (the thing the pin fakes); I mispredicted the final
registers from the RTL alone (I missed sched1 + `optimize_reg_copy_1`), and `--try` settled it in one compile. Four
spellings in parallel was the right first step.
