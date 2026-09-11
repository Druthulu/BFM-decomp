# func_80183B9C — e4 (P36 T7 S104) — score 4 -> 0, ZERO levers

(a) Residual: COUNT (36 vs 37). Reorg filled the `bnez v0,<else>` delay slot with the else arm's first insn
`li a0,19` (stolen from the branch-target thread); the target keeps `nop` in that slot and `li a0,19` at the else
label. The tree faked the target with a `__asm__ __volatile__("")` barrier at the head of the else arm (an asm insn
is not eligible for a delay slot, so the steal from the target thread fails).

(b) Pass/decision: `reorg.c` `fill_eager_delay_slots` (:3632). The branch is predicted not-taken, so it first tries the
fall-through thread (`:3716-3721` — its first insn is `jal func_80178970`, not eligible), then the TARGET thread
(`:3723-3728`). `fill_slots_from_thread` (:3270) steals a non-owned/owned insn only if it does not set a resource
needed on the OPPOSITE thread: `! insn_sets_resource_p (trial, &opposite_needed, 1)` (:3374-3376), with
`opposite_needed` from `mark_target_live_regs (opposite_thread, …)` (:3293). In the lever-free text the fall-through
`jal func_80178970` takes no argument, so `$a0` is dead there and `li a0,19` is stolen. In the original,
`func_80178970` is CALLED WITH arg0 (as its lever-free siblings func_801833FC:6131 and func_8017D058 do:
`((s32 (*)(s32))func_80178970)(a0)`): the call's CALL_INSN_FUNCTION_USAGE reads `$a0`, `li a0,19` sets it, and the
steal is refused -> `nop`.
The argument costs 0 bytes: `$a0` still holds the incoming arg0 at the call (nothing between the prologue copy and
the jal clobbers it), so the `move a0,s0` is removed as a copy of the value the register already holds —
DUMP-VERIFIED (`PACK/scratch/dumps_b`): insn 23 `(set a0 s0)` survives cse/combine/greg and is deleted by jump2's
"no-op move from fortuitous register allocation" (jump.c:425-462: `find_equiv_reg` finds the prologue `move s0,a0`
with `$a0` unchanged since). Its `(use a0)` on the call is what reorg's `mark_target_live_regs` sees.

(c) Move (one): `func_80178970()` -> `((s32 (*)(u8 *))func_80178970)(arg0)` — pass the argument the callee really
takes (same cast shape as func_801833FC in this TU). Everything else is body_free.c verbatim. `--try` score 0 on
the first attempt.

(d) GENERATOR PROPOSAL: when the residual is a single `nop`-vs-insn in a conditional branch's delay slot with the
insn re-appearing at the branch target (COUNT +1, the tree carries a `barrier` lever at the head of the target
arm), and the arm the branch falls into starts with a call whose declaration/cast passes fewer arguments than
other call sites in the overlay pass (grep `((… (*)(…))<callee>)(` in src/<ov>/), pass the extra argument(s) the
caller already holds in `$a0..$a3` (the incoming parameters) — that makes the register live on the opposite thread
and refuses the steal (R19's "real arity" rule, extended to calls whose only effect is on reorg).

(e) Did not work: the sweep's R7 block/do-while and R9 swaps all stayed at 4 (none changes `$a0`'s liveness on the
fall-through thread).

(f) Method: the fix was a "dropped call argument" (METHOD step 3, first bullet) but it showed as a delay-slot fill,
not a missing instruction — the count gap was an extra `nop`, i.e. a reorg decision. A residual row for
"delay slot stolen from target where the original has nop" -> "check the fall-through call's arity" would have
pointed straight here. related.txt carried the answer (two siblings pass a0 to func_80178970).

(g) Structs: no. The lever controls reorg's resource liveness at a call, not an aggregate-vs-scalar memory
dependence; a struct type for arg0 (field `u16 +0x34`) would not change it.
