# func_80175AB8 (ov_SC04_011) — T7 agent c11 — WORK IN PROGRESS

Start: lever-free score 41 (mine 191 / target 188). Three independent residuals:
(A) &D_8011F7F0 held in $s2 all function (target) vs folded to absolute addresses (mine) — the launder lever.
(B) (s16)(r1 + r2) computed in $a1 (target) vs in $s0 (mine) — the $4/$5 pins.
(C) D_80193B4C[idx] load hoisted by sched1 above the `D_8011F83A = idx` store (mine) — the memory barrier.

(C) CLOSED (score 41 -> 33 on the lever-free body; with launder kept, 11 -> 3):
  `func_80024054(*(u8 **)((u8 *)D_80193B4C + idx * 4), local);`
  expr.c:4568-4575 (expand_expr INDIRECT_REF) sets MEM_IN_STRUCT_P when the INDIRECT_REF operand is a PLUS_EXPR;
  `p[i]` is *(p+i) so the table load is /s with a varying address, the scalar store is not /s with a fixed address,
  and sched.c true_dependence's in-struct exclusion declares them independent -> sched1 hoists the load over the store.
  Wrapping the pointer arithmetic in a cast makes the operand a NOP_EXPR, the load is not /s, memrefs_conflict_p
  answers "conflict" for (plus reg sym) vs sym, and the load stays after the store.
