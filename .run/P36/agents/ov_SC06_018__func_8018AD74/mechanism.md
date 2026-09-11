# func_8018AD74 (src/ov_SC06_018/ov_SC06_018_jr_80187AEC.c), e5, P36 T7 S104: MINIMUM-LEVER at 0

**Final: score 0 (60/60 ins, byte-identical).** Lever count 1 → 1, but the kind changes: the tree's `__asm__` launder
on `obj` becomes ONE marked empty `do { } while (0);`, which is ordinary C (step 8). No pin, no asm, no volatile. I found no
lever-free spelling (below). The move against `body_free.c`:

    -    obj = func_8012C658((s16)p2, (s16)p3, p1);
    -    if (obj != 0) {
    -        m = &local_30;
    +    obj = func_8012C658((s16)p2, (s16)p3, p1);
    +    do { } while (0);  // !FAKE: do-while — …
    +    m = &local_30;
    +    if (obj != 0) {

The class's other copy closes with the same text: **func_80185F4C** (src/ov_SC06_032/ov_SC06_032_jr_80182890.c) scores
**0** (`scratch/copy_func_80185F4C.c`).

## (a) The residual
Same count, one instruction in the wrong place. The target is `jal; [move s1,a3]; move s0,v0; beqz s0; [addiu s2,sp,16]`.
The free text is `move s1,a3; jal; [addiu s2,sp,16]; move s0,v0; beqz; [sll a0,s1,16]`. The `m = &local_30` address
(`addiu s2,sp,16`) sits before the call instead of between the call-result copy and the branch.

## (b) The pass and the decision (proved on dumps, `scratch/dumps_free/`, `scratch/dumps_tree/`)
1. **cse1 hoists `m` into block 0.** `local_30 = D_800AE620` expands through `expand_block_move`, which copies the
   destination address into a pseudo (`.rtl` insn 17, `reg 78 = fp+16`). `m = &local_30` in the if-body is the same
   `(plus fp 16)`, so cse finds reg 78 in the table. m's own pseudo is not made the class head (it does not outlive the
   extended block, `make_regs_eqv`, cse.c:846-862), so every use of m becomes reg 78 and m's set is deleted. The
   struct copy's own address is folded back to `fp+16`, so reg 78 now exists only to be m. It is set at insn 17, before the call.
2. **sched1 ranks it before the call.** At T-2 (just before the branch) the ready list is {17 (reg 78), 35 (`obj = v0`)}.
   Both are birthing insns, boosted to `max_priority` (`adjust_priority`, sched.c:2507-2545; `birthing_insn_p` needs
   `reg_n_sets == 1`, :2469-2490). Both are class 3. The tie goes to the higher LUID (`rank_for_schedule`, sched.c:2428),
   which is 35, so 35 is placed last and 17 falls before the `jal`. reorg then fills the `jal` slot with it.
3. **The tree's launder** makes obj's pseudo `reg_n_sets == 2`. 35 is then not a birthing insn (priority 1 against 17's
   boost), and 17 lands between 35 and the branch (`.sched` of the tree: `T-2: 17 (7f000001) 35 (1), now 17`).

## (c) The move (minimum lever)
Assign `m = &local_30;` in block 0 after the call, behind an empty `do { } while (0);`. The loop's `NOTE_INSN_LOOP_END`
ends cse1's extended basic block (`cse_end_of_basic_block`, cse.c:8054). m's `(plus fp 16)` is then never looked up
against reg 78. Reg 78 goes dead once the movstr address is folded, and cse deletes it, so cse2 (which ignores the note)
has nothing to merge. m keeps its own pseudo, set after 35. At T-2 both are boosted and the LUID tie now picks m's set.
It lands between `move s0,v0` and `beqz`, and reorg puts it in the branch delay slot. The note is also a sched barrier
(sched.c:2053-2074), but between 35 and m's set that is harmless.
Placement matters (all `--try`): the empty loop **between the call and `m =`** scores **0**. `do { m = &local_30; } while (0)`
scores 5, because the LOOP_END comes after m and the fold still happens. Wrapping the call scores 7: its LOOP_BEG pins
`move s1,a3` before the argument setup and flips the s1/s2 allocation. Wrapping the struct copy scores 21.

## (d) GENERATOR PROPOSAL
When the only residual is an `addiu sK,sp,N` (a local's address) sitting in a `jal` delay slot where the target has it in
the following branch's slot, and the source takes that local's address inside the if-body after a struct copy into the
same local: hoist `p = &local;` to just before the `if`, behind an empty `do { } while (0);` (marked). The mechanical
test: `.cse` shows the address pseudo created by `expand_block_move` standing in for the pointer variable.

## (e) What did not work (all `--try`)
| spelling | score | why |
|---|---|---|
| body_free (start) | 5 | above |
| `&local_30` direct at both calls, no `m` | 5 | same fold onto reg 78 |
| `m = &local_30;` before / instead of the struct copy (`*m = D_800AE620`) | 5 / 5 | m is set first, LUID lowest |
| `m = &local_30;` between the call and `if`, no loop | 5 | cse1 folds it onto reg 78 again |
| `if (obj == 0) return;` form | 5 | the same extended block |
| `p1 = func(…, p1)` / `p2 = func(…)` to give obj a second set | 5 / 5 | expand puts the call value in a fresh temp; cse deletes the param copy, so the temp still has `n_sets == 1` |
| the sweep's R18/R7 bests | 2 (history) | never below 2 |

## (f) Where the method fell short
- A plausible origin for an EMPTY `do { } while (0)` in 1990s game code is a debug macro compiled out
  (`#define DPRINTF(...) do { } while (0)`). That is an interpretation, not proven. It would make this text the original
  rather than a lever, and it is why I prefer it to the asm. Three distinct effects of a do-while(0) are now on record:
  a sched barrier (d4), a cse1 extended-block end (this one, cse.c:8054), and a loop-depth ref weight (e5's
  func_80187DD0, flow.c:2711). A generator that inserts `do { } while (0);` at each statement boundary and scores all of
  them would have found this in about 20 compiles.
- The method has the birthing boost (S104 d8) but no rule for **cse moving a variable's definition to another block**
  by folding it onto an earlier pseudo that holds the same address. That fold is what put `m` in block 0 in the first place.
  "Read `.cse` for a user variable that vanished" belongs in step 3.
- I looked for a plain-C second set of `obj` (a natural `reg_n_sets == 2`) and did not find one. Every reuse of a
  parameter goes through a call-value temp.

## (g) Structs answer
Struct typing would not remove this lever. The deciding facts are cse's value equivalence of two `(plus fp 16)`
computations and sched1's LUID tie. Neither involves memory aliasing (`expr.c:4568-4577` → `sched.c` true_dependence
is not on the path: the two contenders are register copies). `local_30` is already a struct. What would matter is the
original's **statement placement** (where `&m` is formed) or a second assignment of `obj`, which is information a
struct definition does not supply.

Files: `body.c` (the min-lever text), `scratch/copy_func_80185F4C.c` (SC06_032 copy, 0), `scratch/d/` (do-while
placements), `scratch/dumps_free/`, `scratch/dumps_tree/`, `scratch/dumps_v2/`, `scratch/dumps_v7/`.
