# func_8017CAD4 (ov_SC06_010_jr_8017A4AC.c) — T7 e14, P36 S104

**Score 0, ZERO levers** (free start 6 = regen best 6). Tree levers: 1 (the `m24` launder after the inner loop) -> 0.
Same function family and same move as the twin **func_8017BEBC** in this TU (its mechanism.md has the full reading;
the proof numbers for this body are below).

The move (case 6/7, FT3 depth) — `g.opz = za;` stored at the end of each arm instead of once after the if/else:
```
                 if (g.sz0 > g.sz1) {
                     za = g.sz0;
                     if (za < g.sz2) za = g.sz2;
+                    g.opz = za;
                 } else {
                     za = g.sz1;
                     if (za < g.sz2) za = g.sz2;
+                    g.opz = za;
                 }
-                g.opz = za;
```
and the launder line deleted (body_free.c is the start).

## (a) The residual
755/755 instructions, a pure `$s5`/`$s6` swap of the hoisted `&g.sz0` (sp+236) / `&g.sz1` (sp+240) (3 sites).

## (b) The pass and the decision
global.c `allocno_compare` (global.c:585-607), an int-truncation tie: free `.lreg` r237 (`&g.sz0`) 7 refs / live 573,
r239 (`&g.sz1`) 7 / 572 -> (int)(140000/573) = 244 = (int)(140000/572) -> allocno number -> r237 first -> wrong register.
With the duplicated store the outer loop has one more real insn at flow time (602 -> 603 in `.loop`; flow.c:1660-1684):
live 574/573 -> **243 vs 244** -> r239 first, as in the target. After reload the two identical `sw …,232(sp)` arm tails
are merged by post-reload cross-jump (`jump_optimize(insns,1,1,0)` toplev.c:3142, `find_cross_jump` jump.c:2371), so the
instruction stream is the free body's. Proven on bytes (6 -> 0) and on dumps (scratch/probe/dumps_free, dumps_dup;
BEBC's pack shows the 5 -> 4 store count across `.sched2` -> `.jump2` for the same edit).

## (c) The move
- Store `g.opz = za;` in each arm of the case-6/7 `g.sz0 > g.sz1` if/else (the launder deleted).

## (d) GENERATOR PROPOSAL
R-dup-join (see func_8017BEBC): on an equal-priority allocno pair (int-truncated `allocno_compare` tie) in a callee-saved
swap, move one single-insn statement that follows an if/else join into both arms, one site at a time (+1 flow insn,
removed by jump2's cross-jump).

## (e) What did not work
- body_free: 6. Every R2–R38 family: 6 (history.txt). No generator duplicates a statement into both arms of an if/else.

## (f) Where the method fell short
Same as func_8017BEBC: the alloc table's float priorities hide the int tie; the header's "the tie already falls the
target's way, DO NOT add a slider" is stale for the current text (this body needed the +1 too).

## (g) Structs
No — live-length arithmetic on two hoisted stack addresses; struct typing of `model`/`part`/`prim` does not change the
outer loop's insn count at flow time nor these allocnos' refs; the `expr.c:4568-4577` channel is not involved.
