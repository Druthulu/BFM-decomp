# func_801836B0 (ov_SC02_027) — agent e18, P36 T7 S104 — score 0, ZERO levers

(a) Residual: score 2 — the target leaves the `beqz v0,L` delay slot EMPTY (`nop`, branch to `L: move a0,s0`); the lever-free
body lets reorg copy `move a0,s0` from the branch target into the slot and re-target the branch one insn later. The tree
faked the empty slot with `__asm__ __volatile__("")` at the join label (reorg's `stop_search_p` stops at an asm insn,
reorg.c:695-700).

(b) Pass and decision (proved on the dumps, `scratch/dumps_close/`):
- reorg `fill_eager_delay_slots` (reorg.c:3632): `beqz` = EQ → `mostly_true_jump` predicts not-taken (reorg.c:1405); the
  fall-through thread starts with a CALL (not eligible); then the target thread is tried (reorg.c:3723-3728) and
  `fill_slots_from_thread` copies `move a0,s0` unless it SETS a register needed on the opposite (fall-through) thread
  (reorg.c:3374-3376, `opposite_needed` from `mark_target_live_regs`, reorg.c:2441).
- a0 is needed on the fall-through only if the first call READS a0. The original passed the object pointer to
  `func_80178D18` (the TU's `void (void)` prototype is the decompiler's; three siblings already cast it at the use — TU
  line ~6309, ov_SC06_008 func_80185274, ov_SC03_006 func_8017D058). The arg copy `(set a0 (reg s0))` (insn 18) survives
  cse/combine/greg/sched2 and is DELETED by jump2's post-reload redundant-move scan (jump.c:426-458, `find_equiv_reg` sees
  the prologue's `move s0,a0` with no label between) — so the bytes show no `move` before the `jal`, yet the call's
  `(use a0)` keeps a0 live at the fall-through and reorg refuses the steal. Proved: insn 18 is present in `.greg`/`.sched2`
  and absent in `.jump2`/`.dbr`; `--try` = 0.

(c) Move (one line): `func_80178D18();` → `((void (*)(void *))func_80178D18)(arg0);` (cast at the use — the TU keeps its
declaration; the house convention, law 4 / cookbook §181.4).

(d) GENERATOR PROPOSAL: when a residual is ONE delay slot the target leaves empty (`nop`) where mine holds a `move aN,sK`
copied from the branch target, and the fall-through starts with a call whose callee is invoked elsewhere WITH arguments
(or whose `$aN` still holds the parameter the `move` loads), add the parameter as that call's argument N-4 via a cast at
the use — jump2 deletes the copy (0 bytes), the call's `(use aN)` blocks reorg's steal. (A variant of S103 c35's "pass the
argument the caller already holds", R19, but the symptom is in reorg, not in the allocator.)

(e) Not tried/needed: the sweep's R7 block/do-while and R9 swaps all stayed at 2 (history.txt) — none touches a call's arity.

(f) Method note: the `.dbr` dump is not enough alone; the deciding fact was in `.jump2` (the deleted arg copy). Grepping
the callee's other call sites in the TU (`grep -n func_80178D18`) found a sibling comment saying "the original source
passed the object pointer" — step 0/3's "read lever-free bodies that share your callees" was the whole crack.

(g) Structs: no. The lever was a call arity (a wrong prototype), not a memory-access channel; a struct type on `arg0`
would not change reorg's liveness decision.

Copies closed with the same text: src/ov_SC02_028/ov_SC02_028_jr_8017D898.c func_801817B8 (`--try` = 0,
scratch/copy_SC02_028_func_801817B8.c). The ov_SC02_016 `func_801836B0` is a different function (same address only).
