# func_800D1984 (aF800D1984) — e34 (P36 T7 S104) — score 1 -> 0, levers 1 -> 0 (plain C)

Byte-twin of func_800D1B80 (same TU; only the tail callee differs: func_800D19DC vs DsMix). The full reading, with
the dump evidence, is in `../resident__func_800D1B80/mechanism.md`; summary:

(a) Residual: `sb v0,20(s0)` vs the target's `sb v0,20(a0)` — the store base, nothing missing (22 = 22 ins).

(b) Pass: sched1 `adjust_priority` (`sched.c:2507-2545`) boosts func_800D19DC's argument copy `a0 = arg0` to
max priority because `birthing_insn_p` (`sched.c:2469-2491`) sees `reg_n_sets[$a0] == 1` (`:2488-2489`); the
copy lands after the store. With it before the store, `optimize_reg_copy_1` (`local-alloc.c:700`, called at
`:1003-1007`) rewrites the store base from arg0's pseudo to `$a0`. Proven on the .sched/.lreg dumps of the twin.

(c) Move: call the method pointer with its object, `fp(arg0)` (`s32 (*fp)(u8 *)`) — the second set of `$a0`
kills the birth boost. The extra `move a0,s0` before `jalr` is deleted after reload as a no-op-by-history copy
(`jump.c:425-462`), 0 bytes. `arg0[0x14]++` written directly (no `p`).

(d) Generator: when the only residual is a store base `$sN -> $aK` just before a call taking that value as arg K,
pass the same value as argument K to an EARLIER call (the method pointer read off that object) — raises
`reg_n_sets[$aK]` above 1.

(e) Didn't work: every `p = arg0` spelling (cse merges it), `fp()` with the store written via `++` (1).

(f) Method gap: no step names `birthing_insn_p`'s `reg_n_sets == 1` test on a hard argument register.

(g) Structs: no — a struct for arg0 would read better (`arg0->fn(arg0); arg0->f14++;`) but the decision is a set
count of `$a0`, not an aggregate-vs-scalar access question.

Name note: the definition stays `aF800D1984` with the file's `__asm__("func_800D1984")` label (func_800D1938's
`extern void func_800D1984(S800D1938 *)` prototype earlier in the TU conflicts with the `u8 *`/`s32` definition).
