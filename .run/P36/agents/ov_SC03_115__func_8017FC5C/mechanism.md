# func_8017FC5C (ov_SC03_115, 9 copies): the `$2` pin + keepalive were faking a RETURN VALUE (agent c32, S103)

**Result: score 0, lever-free, whole object byte-identical** — but it is NOT a `--body`-only change: the function has to
return its first argument, so the TU's three file-scope declarations of it change too (`void` -> `s32 *`). Neither
the pin nor the keepalive is needed.

## (a) The residual
Lever-free: 42 vs 43, the missing instruction is the last one, `move v0,s0`. The target returns `a0` in `$v0`. A
`void` function can't do that — flow deletes the tree's `rv = (s32)a0;` because `$2` is dead at the end of a void
function. The keepalive asm existed only to stop that delete, and the pin existed only to pick the register.
Once the function returns a value the missing instruction is back, but there is a SECOND defect hidden behind it:
with a plain `return a0;` sched1 hoists the return copy above the result store (`lw v1 / move v0,s0 / sw v1,0(v0)`,
42 ins, score 4). The tree header's note (4) saw this and blamed sched2 — it is sched1.

## (b) The pass and the decision (proved on bytes)
- The copy emitter: `expand_return` -> `expand_value_return` (stmt.c) for `s32 *`, or `expand_function_end`
  function.c:5406-5427 for a struct-return function. Both emit `(set (reg 2) (reg a0'))` + `(use (reg 2))` in the
  same basic block as the store.
- The ordering: sched1 schedules backwards. At T-2 the ready list is {store 95 (priority 5), return copy 104
  (priority 4)} — the store sits one above because of the load's 2-cycle latency (`priority`, sched.c:1425ff). The
  store wins, gets placed last, the copy lands above it, and local-alloc can't give the loaded temp `$v0`.
- What flips it: `adjust_priority` sched.c:2539-2544 lifts a ready insn to the running max when
  `birthing_insn_p` is true, and sched.c:2490 requires `reg_n_sets[$2] == 1`. The call to `func_8012B77C` is the
  deciding factor. Declared `s32` (as the TU has it), the call is a `call_value` that SETS `$2` (REG_UNUSED), so
  `reg_n_sets[$2] == 2` and there's no boost. Declared `void` (or struct-returning — calls.c:1604-1613 gives
  `valreg = 0` for both), it's a plain `call`, the return copy is `$2`'s only set, it gets boosted
  (`104 (7f000001)` in the `.sched` dump), it's placed last, the store stays above it, and the loaded temp takes
  `$v0` → target.
- Proof, same TU, same body: the callee declared `s32` gives score 4 (hoisted, `scratch/tu_p0.c`); declared `void`
  gives score 0 (`scratch/tu_p1.c`). Dumps: `scratch/dumps_b1` (hoisted) vs `scratch/dumps_v1` (boosted).

## (c) The moves (all four together; each is necessary)
1. `s32 *func_8017FC5C(s32 *a0, s32 a1, s32 a2)` ending in `*a0 = sp20; return a0;` (the return value).
2. The TU's three `extern void func_8017FC5C(s32 *a0, s32 a1, s32 a2);` become `extern s32 *...` (a `void`
   declaration conflicts with the definition — a hard cc1 error, which is why the tree used a pin).
   The callers ignore the result. Their calls become `call_value`s that set `$2` unused (calls.c:1604), and I
   checked on bytes that this changes nothing in any of the three.
3. `func_8012B77C` is called through a body-local declaration alias
   `extern void fV(s32 out, s32 from, s32 to) __asm__("func_8012B77C");` so the call doesn't set `$2`.
   Changing the TU's own file-scope `s32` declaration instead would also touch `func_8017F5B4`'s call.
4. Nothing else changes — same locals, same statement order as `body_free.c`.

Verified: `func_8017FC5C` and its three callers (`func_8017F2B0`, `func_8017F808`, `func_8017F914`) all score 0.
The WHOLE object compiled from `scratch/tu_p1.c` is identical to the baseline — `.text/.data/.rodata/.sdata/.bss`,
every relocation, every symbol. Only the FILE symbol's path differs (it's a scratch path).
Transfer checked on a sibling: the same 4-line edit on `ov_SC03_099` `func_80180200` scores 0 for it and its three
callers (`scratch/sib_099.c`). Patch against the tree: `scratch/tu_p1.diff`. The tree's comment header above the
function (notes 3-5) is now wrong and should be replaced by this reading.

**The faithful alternative (also proven, whole object identical — `scratch/tu_d5.c`, `scratch/tu_d5.diff`):** these
are pcc-struct-return functions. The toolchain has `flag_pcc_struct_return = 1` (toplev.c:328-334,
aggregate_value_p function.c:3132), so every struct result goes through a hidden first-argument pointer that comes
back in `$v0`. `func_8012B77C` (`sw s4,0(v0)` after `move v0,s3`) and `func_8012B0B4` have exactly that tail.
Written as `AngM func_8017FC5C(s32 a1, s32 a2) { ...; return fS(a1 + 4, (s32)sp10); }` with
`typedef struct { u32 lo : 16; s32 hi : 16; } AngM;` and callers `v = func_8017FC5C(a0, a0 + 0x102);`, it
reproduces even `func_8017F808`'s shared `sp+24` slot, which gcc's temp-slot reuse gives two struct returns
(that also needs `fB` = struct view of `func_8012B0B4`). Byte-proven type constraints: `lo` MUST be unsigned (a
signed `lo` adds a frame slot: 32->40, 48->56), and `hi` MUST be signed (an unsigned `hi` stores via `srl`, the
target uses `sra`). It touches 3 callers + a new typedef, so I recommend the `s32 *` form for the bank. The struct
form is the better story for a later fleet pass that retypes the whole `func_8012B77C` / `func_8012B0B4` family.

## (d) GENERATOR PROPOSAL
When the target ends `sw/sh X,0(sN)` … `move v0,sN` and the tree fakes the `move` with a `$2` pin plus a keepalive
in a `void` function whose first parameter is the stored-through pointer: retype the function (definition + every
TU declaration) to return that pointer, and `return a0;`. If the copy then hoists above the store, redeclare every
value-returning call in the function whose result is unused as `void` through a body-local `__asm__` name alias,
so `$2` is set only once (`birthing_insn_p`, sched.c:2490). General rule for the "return copy hoisted into a load
delay" class: count the `$2` sets in the function — every unused `call_value` is one too many.

## (e) Tried and rejected (bytes)
- struct return, callee left `s32`: score 4 (hoist) — `scratch/tu_b1.c`.
- duplicated tails per arm (to leave a label between the store and the return copy): score 44 — cse folds `q-3`
  into absolute addresses per arm.
- `*(T *)sp10 = f()` in the callers (struct form): a temp plus a copy — `expand_expr` drops a MEM target for
  a non-BLKmode result when cse is expected (expr.c, the top of `expand_expr`), so the caller has to assign
  to a register-able local.
- Signed `lo` / unsigned `hi` in the struct form: see the type constraints above.

## (f) Where the method fell short
- The brief's scoring loop is `--body`, and this close needs a TU declaration change. Scoring the whole TU without
  `--body`, plus a hand-rolled object comparison (objdump -drs / nm / readelf diff against the baseline), did the job.
  `--try` could take a `--also FN...` flag that scores the named callers from the same compile, plus a whole-object
  compare mode.
- The "COUNT: one instruction missing" framing points toward emitters in the BODY. Here the emitter is the
  function's TYPE (`void` vs value-returning). METHOD §3 should gain: "a missing trailing `move v0,sN` in a void
  function = the function returns sN; check the TU declarations, which may be wrong, not the body."
- A scan of all 7,428 baseline objects for `sw X,0(sN) ; move v0,sN` at a function end (`scratch/scan.py`) found
  only this family, the `func_8012F40C` family (whose return copy sits after a join label) and libgpu `ClearOTag`.
  That's a cheap way to size a class.
