# func_8017F024 (ov_SC06_010_jr_8017A4AC.c) — T7 e26, P36 S104

**Score 0, ZERO levers** (free start 5 = regen best 5). Tree levers: 2 (the `$2` pin on `p` + the `self` launder) -> 0.
No copies elsewhere (the `p[1] |= 0x80000000` after a `D_8018AFBC` dispatch is unique; the other `func_8017F024`s
in src/ are different functions of other overlays).

The move (one): the dispatch-table call passes the actor, as its handlers take it (`func_8017EE3C(s32 a0)` is entry 1
of `D_8018AFBC` = {func_801804B0, func_8017EE3C, func_80180598}, asm/ov_SC06_010/data/tail.data.s:8754):
```
-    D_8018AFBC[*(u16 *)(a0 + 2)]();
+    ((void (*)(s32))D_8018AFBC[*(u16 *)(a0 + 2)])(a0);
```
(`self`, the launder and the pin deleted.) body.c uses the cast because the table's `extern` is at file scope
(TU line 5317) and D_8018AFBC has no other user in this TU. **The cleaner spelling, also 0** (scratch/tu_decl.c,
whole-TU `--try`): change the file-scope declaration to `extern void (*D_8018AFBC[])(s32);` and call
`D_8018AFBC[*(u16 *)(a0 + 2)](a0);` — recommended for the bank (a declaration change outside the body, not a
signature change of this function).

## (a) The residual
Count 30 vs 29 (COUNT class, but really a register decision): the mask constant `0x80000000` took `$a0` (`lui a0` in
the beqz slot, then `move a0,s0` before the jal = one extra insn); the target keeps the argument copy `move a0,s0`
first in the block (reorg puts it in the beqz slot) and loads the constant into `$a1`.

## (b) The passes and decisions (dumps: scratch/dumps_free, dumps_l1, dumps_a1)
1. **sched1 `adjust_priority` / `birthing_insn_p` (sched.c:2469-2545).** In the free body the argument copy
   `(set (reg a0) (reg 72))` (insn 47) births `$a0` and `reg_n_sets[4] == 1` (the only set of `$a0` in the function),
   so its priority is raised to the block maximum (`7f000001` in `.sched`) and the reverse list scheduler places it
   immediately before the call — after the constant load (order 36 39 41 42 44 47). local-alloc then sees `$a0` free
   across the constant's life and block 1's three quantities (p, the load/ior pair, the constant — allocated in BIRTH
   order, local-alloc.c:1486-1500) get v0, v1, **a0**.
2. **Passing `a0` to the handler adds a second set of `$a0`** (insn 23, `(set a0 r72)` before the jalr). cse keeps it
   (the `.cse` still has it), flow counts it (`reg_n_sets[4] = 2`, flow.c:2047), so `birthing_insn_p` returns 0
   (sched.c:2489-2490) and the argument copy keeps priority 1: `.sched` "ready list at T-2: 43 (3) 46 (1)" ... it is
   placed LAST in the reverse schedule = first in the block. `$a0` is now live across the constant, which takes the
   next free register after v0/v1: **a1** — the target.
3. **The handler's copy costs zero bytes**: after reload insn 23 is `(set a0 s0)` right after the prologue's
   `(set s0 a0)`; jump2's no-op move scan (`find_equiv_reg`, jump.c:425-462) finds `$a0` still equal to `$s0` and deletes
   it (`.sched2` has insn 23, `.jump2` does not). So the jalr's delay slot stays a nop, as in the target.
The launder was faking (2): an asm output tied to `$a0` at the block top made `$a0` live over the constant; the `$2`
pin then restored the p/v0 assignment the extra asm quantity had disturbed (the launder alone gives p=a1, dumps_l1).
Proven on bytes (5 -> 0) and on dumps (.sched priorities, .sched2 vs .jump2 insn 23).

## (c) The move that closed it
- Pass the actor to the dispatch-table handler (`(a0)`), deleting the launder, `self` and the pin.

## (d) GENERATOR PROPOSAL
**R-dispatch-arg**: for every call through a function-pointer TABLE declared `(void)` whose index is read from a
parameter's struct (`D_x[*(u16 *)(aN + K)]()`), emit the variant that passes that parameter (`(void (*)(s32))` cast or
the widened extern): it is free in bytes when the parameter is still in its incoming register (jump.c:425-462 deletes the
copy) and it demotes every LATER argument copy of that register from sched1's birthing priority (sched.c:2489-2490).
Trigger: a residual where a later `move aK,sN` argument copy sits right before its `jal` in mine but at the top of its
block in the target (or a constant/temp takes `$aK` in mine). Leads with levers still in the tree:
scratch/dispatch_sites_with_levers.txt (func_80180100 ov_SC03_105, func_80180AA0 ov_SC05_010 — not tried).

## (e) What did not work
- body_free: 5. All R2–R38 families: 5 (history.txt: inline/width/param-alias/decl-move of `self`/`p`). No family
  changes a call's ARITY at a different call site from the one that differs.
- The launder alone (no pin), scratch/l1.c: 5 (REG: p=a1, load=v0, const=v1 — four quantities, sorted order).

## (f) Where the method fell short / what helped
- METHOD S103 c3/c12 ("a dispatch-table handler READS `$aN` implicitly — pass it") is exactly this family, but its
  trigger is a MISSING `move sK,$aN`; here nothing is missing at the dispatch site — the effect shows at a DIFFERENT call
  (the second `$a0` set demotes the later copy's sched1 priority). Worth a line: "a later argument copy placed too late
  = its hard register is set only once in the function (birthing priority); pass the parameter to an earlier call".
- Reading `.sched`'s ready list (the `7f000001` priority on a hard-register copy) settled it in one step.

## (g) Structs
No. The decision is a hard-register set count (`reg_n_sets[$a0]`) feeding sched1's birthing priority; typing `a0` as an
actor struct (`a0->state`, `a0->model->flags |= 0x80000000`) changes no set of `$a0` and no quantity count, and the
`expr.c:4568-4577` aggregate channel (memory-access ordering) is not involved. The table's element type (a handler
taking the actor) is the "type" fix here — a function-pointer prototype, not a struct.
