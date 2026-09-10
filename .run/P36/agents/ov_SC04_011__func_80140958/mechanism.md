# func_80140958 (src/ov_SC04_011/ov_SC04_011_jr_80140608.c), T7 agent c29, S103 — DRAFT (being updated)

c13's files are preserved in `scratch/prev_body.c` and `scratch/prev_mechanism.md`. All my scratch is in `scratch/c29/`.

**Status: score 4 (260/260, class ORDER), same as c13, but the dead initializer is gone.**

## Move for the loop constant 8 (replaces c13's dead `s16 size = 0;`)
`size` becomes a function-scope `s16`. It is assigned 8 and passed as the fourth argument of the third
`func_80140D68` call (`size = 8; ot = func_80140D68(ot, p, 2, size, ...);`, where the tree has a literal 8). The loop
assigns `size = 8;` again before the two stores. Both assignments are read, so neither is dead in the source.

Mechanism (proven on bytes and dumps, `scratch/c29/s0.c` = 26, `s1.c` = 4):
- At loop.c time `regno_first_uid[size]` is the outer `size = 8`. So `reg_in_basic_block_p` (loop.c:1068) fails for the
  in-loop set. `size` is a user variable, so case (2) fails too. The in-loop set sits after the `j == 0` branch
  (`maybe_never`), so case (3) fails. Result: the set is not movable (loop.c:681-690) and stays in the loop
  (`.loop` dump: no movable for it).
- cse1 propagates the constant into the call argument (`li a3,8`). That leaves the outer set dead, and flow deletes it.
  At flow time `size` is referenced in one block only and dies once. It is therefore a local-alloc qty
  (local-alloc.c:472) and gets `$v0`, as in the target.
- Without the outer use (`s0.c`), the in-loop set is a single-block user variable. loop.c hoists it
  (`threshold*savings*lifetime = 58*1*2 >= 74`, loop.c:1631), and the score is 26.
