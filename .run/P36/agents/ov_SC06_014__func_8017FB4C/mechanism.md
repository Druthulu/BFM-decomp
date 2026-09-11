# func_8017FB4C (ov_SC06_014_jr_8017BEBC.c, 4 copies) — P36 S104 agent d3

**Result: score 0 in plain C** (no pin, no asm, no volatile, no do-while, no dead initialiser). Lever count 1 -> 0.
Body: `PACK/body.c` (= `scratch/n11.c`). The same body with body-local struct types (`scratch/n15.c`) also scores 0.

## (a) The residual
Starting text (`body_free.c`, score 22) and the sweep's `free_048.c` (score 4) are goto transliterations. Counting
first: 66 vs 66 instructions every time, so it is a pure register residual at the start, but the goto shape hid three
separate decisions. Once rewritten as structured C they came apart one at a time:

| step | text | score | what still differed |
|---|---|---|---|
| n4b | if/else, one shared `v` temp stored once | 4 | the stored value in `$a0`, the target has `$v0` |
| n5 | one constant store per arm (no shared temp) | 9 | `$s0`/`$s1` swapped between `angle` and `a` |
| n10 | flag computed before `angle = rot & 0xFFF` | 10 | `D_801A14A8`'s value in `$v0`, the target has `$v1` |
| n11 | `p` reused: `p = D; if (p) { … p = p->+0x20; … }` | **0** | — |

Every intermediate score is worse than free_048's 4, and the close is the JOINT of the three moves (METHOD step 5).

## (b) The passes and decisions (read, and proved on bytes)
1. **Stored value `$a0` vs `$v0`: jump.c's if/else hoist + sched1.** `if (c) v = a; else v = b;` becomes
   `v = b; if (c) v = a;` (`jump.c:699-835`, conditions `:727-761`, move at `:811`). sched1 then moves the hoisted
   `v = 0xC00` above the sign-extension of the second call's result, which still occupies the hard `$v0`
   (`.lreg` insn 142 comes before insn 62 in n4b). So `v` conflicts with `$v0` and `find_reg` hands it `$a0`. The target
   never had a shared temp. Each arm stores its own constant, and the post-reload cross-jump pass (`toplev.c:3142`,
   `find_cross_jump` `jump.c:2371`) merges the three identical `sh $v0,18($s2)` tails into the one the bytes show. The
   `sh $zero` arm stays separate because its tail differs. PROVED (n4b -> n5 removed exactly those 4 hunks).
2. **`$s0`/`$s1` swap: sched1's LUID tie-break feeding global.c's priority.** `angle` has 5 refs and `a` has 4. With
   `angle`'s `& 0xFFF` computed BEFORE the flag's `& 0x400`, both are ready at T-2 with equal priority (7f000001) and
   `rank_for_schedule` (`sched.c:2385`, final tie `INSN_LUID`, `:2428`) puts the higher LUID, the flag, next to the
   branch. `angle`'s def moves one insn earlier, so its live length goes from 12 to 13, and sched1's live lengths
   replace flow's (`sched.c:4946-4947`). The priority is then 2*5/13 = 7692 < `a`'s 2*4/10 = 8000
   (`allocno_compare`, `global.c:587-607`, priority first, allocno number only on a tie), so `a` takes `$s0` first. Writing the flag before `angle = rot & 0xFFF`
   puts `angle` next to the branch: live 12, 8333 > 8000, and `angle` gets `$s0`. A separate `rot` temp is needed for the
   `+0x800` value: folding it into `angle` (n9) makes `angle` the addiu's destination (`addiu s0,…`). PROVED: the tables
   of n5 and n11 give the numbers above, identical to the pinned tree's table (20000 / 8333 / 8000).
3. **`D_801A14A8` in `$v0` vs `$v1`: one pseudo for the walked pointer (the S103 c18 MERGE move).** sched1 puts the
   `lw +0x20` first in block 1. With a separate pseudo for the global's value, that value dies before the
   `lhu 18($s2)` temp (which local-alloc gives `$v0`) is born. So nothing conflicts with `$v0`, and global.c's lowest
   free register is `$v0`. Reusing ONE variable `p` for both the global's value and the loaded child pointer keeps
   the pseudo live up to the `lhu 0x12(p)` (5 refs, live 5, "conflicts v0" in n11's table), so it lands in `$v1`, as
   in the target. The pinned tree body already had this shape. Its `p` was reused the same way, and the `$2` pin only
   stood in for decisions 1 and 2. PROVED (n10 -> n11).

## (c) The source moves that closed it
- Rewrote the goto chain as if/else, with one constant store per arm and no shared `v` temp (cross-jump rebuilds the shared `sh`).
- Kept both call results in `s32` locals `a`, `b` and compared `(s16)a <= (s16)b` (with direct calls, or with `s16` locals, the first result is extended before the second call — n6/n7, score 30).
- `rot = lhu + 0x800; p = p->0x20; flag = … & 0x400; angle = rot & 0xFFF; if (flag)`: this source order is the sched tie-break.
- Reused `p` for the global and the child pointer.

## (d) Generator proposal
When a goto body's `$2`/`$3` pin feeds a temp that only carries constants to ONE store after an if/else join, rewrite
the join as one constant store per arm (cross-jump re-merges the tails after reload). When a `$sN` pair is swapped
between two call-crossing values, reorder the source so the insn defining the higher-ref value has the higher LUID
among the ready-at-branch insns: move independent test computations (flag masks) BEFORE its def. Check it with
`2·refs/live` in `alloc_table.py`.

## (e) What did not work (byte evidence)
- n1 (`s16 a`, `(s16)call < a` inline): score 37. The sign extension moved before the second call.
- n2/n3/n4b (shared `v` temp, either branch sense): scores 13 / 5 / 4. The jump.c hoist, see (b)1.
- n6 (both calls inline in the comparison) and n7 (`s16 a, b` locals): score 30. The extension came before the second call, and the frame and callee-saved set changed.
- n8 (flag line before the whole `angle` expression): score 10. The `lw +0x20` ordering changed in block 1.
- n9 (`angle = lhu+0x800; …; angle &= 0xFFF`): score 5. One pseudo, so `addiu s0`.
- n12 (no `rot`, `angle` after flag): 10. n13 (no `flag`, test inline): 18.
- n14 (natural `(s16)a > (s16)b` with the arms swapped): score 11, 69 insns. jump sense and block layout change, so `<=` with the 0x400 / 0 arm first stays.

## (f) Where the method fell short
- The residual's hunk view reported ONE register class at each step. The real defect was three independent decisions, and
  the goto transliteration (body_free / free_048) hides decision 1 completely: a shared temp is exactly what the goto
  form forces. The generator families all mutate the goto text, so R2-R26 could not reach a per-arm-store spelling.
  A "de-goto to structured if/else with per-arm stores" generator is the missing family.
- alloc_table.py was decisive for (b)2 and (b)3. The live lengths it prints are sched1's, and the tie-break that sets
  them is only visible in the `.sched` ready-list trace ("now 38 36"), so pair the two when priorities are within one insn.

## (g) Structs question
Not needed here. Test on bytes: `scratch/n15.c` gives `a0` a body-local `struct Obj { u8 pad[0x20]; void *xf; }` and
`s2` `struct Xform { u8 pad[0x12]; u16 rot; }` (all 6 field accesses through them), and it also scores 0. None of the
three decisions goes through the aggregate-vs-scalar channel (`expr.c:4568-4577`, `sched.c` true_dependence): the only
stores come after every load, and the decisions are the jump.c hoist, a LUID tie-break and pseudo identity.
One caveat for the STRUCTS phase: decision 3 needs ONE variable for both `D_801A14A8`'s object and its `+0x20` child
(`p = p->xf`). Once those get distinct struct types, the reuse needs a common pointer type or a cast. Splitting them into two
typed locals re-opens the `$v0`/`$v1` residual (n10, score 10).
