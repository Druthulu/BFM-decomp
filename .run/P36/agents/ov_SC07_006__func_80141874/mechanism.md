# func_80141874 (ov_SC07_006_jr_80140608.c) — CLOSED, score 0, no lever

## (a) Residual (lever-free start, score 6, 33 vs 33)
The dispatch-table load `lw fp, D_8018B80C(idx*4)` was scheduled ABOVE the store `sh v0, D_8011511C`
(the second call's result), so `fp` was live across the last use of `$v0` and took `$v1`; the target keeps the
store first and loads `fp` into `$v0` (`lw v0 / nop / jalr v0`). The tree faked this with `register fp __asm__("$2")`.

## (b) Pass and decision (PROVEN on dumps + bytes)
- `fp = D_8018B80C[D_80115112];` is an ARRAY access: expand marks the MEM in-struct (`.rtl`: `(mem/s:SI (reg 80))`,
  `expr.c:4568-4575` aggregate/array ref → MEM_IN_STRUCT_P) with a varying address.
- The store `D_8011511C = ...` is `(mem:HI (symbol_ref "D_8011511C"))`: not in-struct, fixed address.
- `sched.c:837-839` (`true_dependence`): `MEM_IN_STRUCT_P(x) && rtx_addr_varies_p(x) && mode != QImode &&
  !MEM_IN_STRUCT_P(mem) && !rtx_addr_varies_p(mem)` → "no dependence", so **sched1** hoists insn 40 (the load) above
  insn 27 (the store) — visible in `.sched` (order 36, 40, 27). Then `fp` conflicts with the store's `$v0` source and
  global/local alloc give it `$v1`.
- Spelled through a pointer temp, the load is `(mem:SI (reg/v 72))` with NO `/s` flag (`.rtl` of the closed body), so
  the scalar-vs-scalar case applies, `memrefs_conflict_p` cannot separate a register address from a symbol, the load
  stays after the store, and `fp` is born after `$v0` dies → `$v0`.

## (c) The move (R71 — a banked sibling's spelling, first `--try`)
```c
void (**slot)(void);
slot = &D_8018B80C[D_80115112];
fp = *slot;
```
Ported from the lever-free sibling (its `new_var` renamed `slot`, re-verified score 0) `func_8013E5E8` (ov_SC07_006_jr_8013C98C.c:1729, the same prologue calls,
the same globals, table `D_8018B7C0`). Score 6 → 0 on the first compile.

## (d) Generator proposal
When a residual shows a table/array LOAD scheduled above a preceding scalar-global STORE (or a `$v0` pin on a value
loaded by `T x = tbl[i]` right after a `global = call()` store), rewrite `x = tbl[i]` as `p = &tbl[i]; x = *p;`
(drops MEM_IN_STRUCT_P, so `true_dependence` keeps the load after the store) — the same fact as METHOD's c11
"`p[i]` is aggregate, a cast-wrapped byte-offset read is not" entry, in its pointer-temp form.

## (e) What did not work
Not explored further: the first try closed. The mechanical search (history.txt: inline fp, block, do-while at every
line) never touches the access FORM, so it sat at 6 for 1,145 compiles.

## (f) Where the method fell short
`related.txt` had the answer as its first entry (a sibling with 8 shared symbols, spelled lever-free). Nothing else
was needed; the method worked. The engine's move set lacks "array ref → pointer temp deref" (see (d)).
The brief's steer (a `$2` pin = a call-result/return copy, c25/c31) did NOT apply: this `$2` pin was a
scheduling-order lever — the pinned value is a table LOAD, and the pin worked only because it forced the load to be
born after `$v0`'s last reader. Read a `$2` pin's producer first: call result → c25/c31; memory load → true_dependence.
