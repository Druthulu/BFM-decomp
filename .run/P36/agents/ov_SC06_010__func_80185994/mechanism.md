# func_80185994 (ov_SC06_010_jr_8017A4AC.c) — T7 agent c35 — CLOSED, score 3 -> 0

## (a) The residual in one sentence
Same count (48 vs 48), one register: the pointer loaded from `a0+0x20` (and read/written at `+4` before the
`jal func_8012B370`) is `$a0` in mine and `$a1` in the target — the target keeps `$a0` holding the parameter up to the
`jal`, i.e. `func_8012B370` is passed `a0` implicitly; the lever-free text called it through `(void (*)(void))`, zero args.

## (b) The pass and the decision (read on this function's own dumps, `scratch/dumps_c2/`)
The callee's REAL definition is one-argument: `src/shared/ov/func_8012B370.h:4` `void func_8012B370(int a0)`, and the
TU declares it so right above the function (`extern void func_8012B370(int a0);`). Passing `a0`:
1. expand/combine: the argument copy `insn 34 (set (reg:SI 4 a0) (reg 72))` sits after the `+4` store, and the call
   carries `(use (reg:SI 4 a0))` (`.combine`).
2. sched1 (`toplev.c` first `schedule_insns`, before allocation) hoists insn 34 to directly after the pointer load
   insn 23 (`.sched`: `23 -> 34 -> 26 28 29 31 -> call 36`). So hard reg 4 is live across the pointer's whole life.
   (PROVEN on the dump; WHY rank_for_schedule places it there — a ready insn with no input dependence in a bottom-up
   list — was NOT traced to a line.)
3. local-alloc: the pointer (pseudo 74, local to block 1) now conflicts with hard reg 4, so it takes the next free
   register after `$v0/$v1` — `.lreg` ";; Register 74 in 5". This is exactly what the `$5` pin was faking.
4. jump2 (`toplev.c:3142`, `jump_optimize (insns, 1, 1, 0)`, after sched2): the now-`move $a0,$s0` is deleted by the
   no-op-move scan `jump.c:427-462` — `find_equiv_reg` finds `$a0` still equal to `$s0` from the prologue's
   `move $s0,$a0` (nothing wrote `$a0` since; `find_equiv_reg` call `jump.c:437`) and `delete_insn` at `jump.c:462-463`. `.sched2` still has insn 34,
   `.jump2`/`.dbr` do not. Zero bytes for the argument; its only trace is the pointer's register.
Control (`scratch/c3.c`): the same cleaned text with the call put back to `((void (*)(void))func_8012B370)();`
reproduces the residual exactly (score 3, a0->a1 x3) — the arity is the whole defect. PROVEN.

## (c) The move that closed it
One line: call `func_8012B370(a0);` at its real arity (also `((void (*)(s32))func_8012B370)(a0);`, `scratch/c1.c`,
score 0 — use the cast form when propagating to a copy whose in-scope declaration is `void(void)`).
Readability edits that ride along at zero bytes (score 0, `body.c`): the load/xor/store triple written
`p[1] ^= 0x80000000;` with `u32 *p`; the re-read `t = *(s32 *)(a0 + 0x1C); if ((t & 3) != 0)` inlined into the test;
the register-named locals `a1`/`v0`/`s0` renamed (`p`, gone, `obj`).

## (d) GENERATOR PROPOSAL
When a REG residual maps a pointer/temp live just before a call from `$aN` (mine) to `$a(N+1)` or higher (target) and the
target never writes `$aN` between its last definition and the `jal`, look up the callee's real definition
(argcheck) and pass the argument(s) the caller already holds in `$a0..$aN` at the callee's arity: sched1 hoists the
argument copy, local-alloc steers the temp off `$aN`, and jump2's `find_equiv_reg` no-op scan (`jump.c:427-462`)
deletes the copy, so the argument costs zero bytes.

## (e) What did not work / was not needed
The mechanical search (history.txt: 5 generations, 3,684 compiles) stayed at 3 — none of its move families edits a
call's argument list, the class argcheck exists for. No other move was needed; closed on the first `--try`.

## (f) Where the method fell short
Nothing: the brief's first instruction (check every call's arity against the real definition) was the answer. One note
for argcheck: this call was a cast-to-`void(void)` at the site while an in-scope declaration with the right arity sat
five lines above — a cast call site deserves the same check as a declared one.
