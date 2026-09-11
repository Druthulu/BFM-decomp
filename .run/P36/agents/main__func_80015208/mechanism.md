# func_80015208 (main, src/800.c) — T7 agent e10 (S104)

**Result: score 0, lever-free** (no pin, no asm, no volatile, no do-while, no invented term). Levers 1 -> 0 (the
tree's one NEEDED launder). Signature unchanged. Whole-object check on the `--try --keep` object: `.text` (101,572
bytes), `.data`, `.rodata` byte-equal to `.run/P36/delever/baseline/src/800.o`.

```c
    {
        s32 mask = 0x800;

        if (D_800B9A13 != 0) {
            return;
        }
        v = *(u16 *)&D_80078DD2 & mask;
        if (v == mask) {
            v = 1;
        } else {
            v = 0;
        }
        if (!v && D_800A5E78 != 0) {
            return;
        }
        base[0xA3E5] = 1;
        func_801281D8();
    }
```

## (a) Residual
COUNT 53 vs 59: the flag `v` vanished — the target computes it with branches (`bne v0,v1,L; move v0,zero; li v0,1;
L: bnez v0,…`) against `0x800` held in `$v1`, mine tested `andi …; bnez` directly — and the late `base[0xA3E5]` store
was folded to an absolute `lui at,%hi(D_800AF630+0x10000)` instead of `addu at,a1,at` off the base in `$a1`.

## (b) Passes and decisions
1. **jump1 if-conversion (PROVEN, `scratch/dumps_free/f.jump`)**: the lever-free `if (c) v = 1; else v = 0;` is
   rewritten by jump.c's first transform (`if (…) x = a; else x = b;` -> `x = b; if (…) x = a;`, jump.c:725-830) and
   then turned into a store-flag (`xor`/`sltu`, jump.c:1012-1210, `reg_set_last` finds the constant `x = b`), after
   which cse/combine fold the flag test away. The transform is refused when the condjump itself references X:
   `! reg_referenced_between_p (temp1, p, NEXT_INSN (temp3))` (jump.c:805). Writing the masked value INTO `v` and
   comparing `v` (`v = pad & mask; if (v == mask)`) makes the jump read `v` — the branchy flag survives (d3, score 4,
   and the `addu at,a1,at` store came back with it: the store now sits after a join label, so the base's constant
   equivalence no longer reaches it — that part is a hypothesis about cse's path end, byte-proven only as "comes back
   with the branchy flag").
2. **combine simplifies a literal compare (PROVEN that combine deletes the `2048` set, `scratch/dumps_d3/f.combine`)**:
   with `v == 0x800` the expander's forced constant register is merged into the jump and the test becomes `bnez`
   (the mechanism is presumably `simplify_comparison` on `nonzero_bits (v) == 0x800` — not traced line by line). A
   named `mask` variable keeps the register compare (`li v1,2048; bne v0,v1`), as the tree already had.
3. **sched1's birth priority (PROVEN, `scratch/dumps_d1/f.sched` vs `scratch/dumps_tree/f.sched`)**: with `mask`
   set in the flag block and `v` set four times, `birthing_insn_p` (sched.c:2465-2490, `reg_n_sets == 1`) boosts only
   the mask insn to the block's max priority (`adjust_priority`, sched.c:2537-2543; ready list `98 (7f000001) 105 (2)`)
   so `li` is scheduled next to the jump, local-alloc gives it `$v0` and `v` loses to `$v1` (d1, 13-18). In the tree
   the and-result was a set-once temp and tied with it. Moving `mask = 0x800` ABOVE the `D_800B9A13` test puts its
   `li` in the previous block, where reorg fills that block's `bnez` delay slot with it — exactly the target's
   `bnez v0,<ret>; li v1,2048`.

## (c) Moves (joint)
1. `v = *(u16 *)&D_80078DD2 & mask; if (v == mask) v = 1; else v = 0;` (the flag variable carries the masked value
   into the compare) — 23 -> 4 with a literal, 13 with the in-block mask.
2. The `{ s32 mask = 0x800;` block opened ABOVE `if (D_800B9A13 != 0) return;` -> **0**.
3. Readability, all still 0: `flag0` inlined into `if (D_800B9A64)`, the nested `if (!v) { if (…) return; }` as
   `if (!v && D_800A5E78 != 0) return;`, the dead `v = 1; base[…] = v;` as `base[0xA3E5] = 1;`.

## (d) Generator proposal
When a lever (launder/asm) sits on one arm of `if (c) x = K1; else x = K2;` and the lever-free text loses the flag to a
store-flag (`COUNT` short by the branch pair), make the condjump read `x` — assign the compared operand into `x` first
(`x = expr; if (x == y) x = K1; else x = K2;`, jump.c:805) — and then, if a set-once constant operand lands next to the
jump (`sched.c` birthing), hoist its declaration/initialiser above the previous early-return test.

## (e) What did not work
90 spellings enumerated (`scratch/e/`, `scratch/e_scores.txt`: flag width s32/u32/s16/u16/u8 x mask in-block/literal x
and-operand x compare orientation x final store): best 4 (literal compare simplified). `u16`/`s16`/`u8` flags put an
extension between `v` and the jump, so the condjump no longer reads `v` and jump1 converts again (17-22).
Function-scope `mask` initialised at the top (f1) = 7 (the `li` lands in the prologue, base takes `$a2`); set above the
`D_800B9A16` test (g2) = 8.

## (f) Where the method fell short
None of steps 12-15 names jump1's if-conversion/store-flag as a COUNT cause; the free sweep cannot reach it (no
generator writes the compared value into the flag or moves a declaration across an early return). Add: "a flag that
is computed with branches in the target but vanished in yours = jump.c's store-flag; make the jump read the flag".

## (g) Structs
No. Nothing here is an aggregate access that a struct would change: the decisions are jump1's operand check, combine's
constant compare and sched1's set-count. `D_80078DD2` is `D_80078D98 + 0x3A` (the pad-state array of 76-byte records
also read by func_80014D94/func_80014C54); typing it as `D_80078D98[0].buttons` would produce the same `lhu`.
