# func_8017F0EC (ov_SC04_015_jr_8017AE2C.c) — e33, P36 T7 S104 — plain C 56; MINIMUM-LEVER body at 0 (1 lever → 1, a declaration alias instead of an asm launder)

(a) Residual (score 56, 200 vs 199 ins, one extra saved register): the address `&D_801C8B64` computed for
`VectorNormalSS(&D_801C8B64, &D_801C8B64)` is REUSED for `func_8012F568(…, (s32)&D_801C8B64)` after the call, so it
lives across the call in `$s0` and shifts every callee-saved register (a0 copy `$s1`, q `$s2`). The target keeps it in
`$a0` only up to the call (`move a1,a0` in the delay slot) and RE-MATERIALISES it (`lui v0/addiu v0; sw v0,20(sp)`)
for the 6th argument.

(b) Pass: cse. The arguments are precomputed into pseudos (calls.c:1655-1666: `rtx_cost(symbol_ref) = 6 > 2` and
`preserve_subexpressions_p` is 1 at -O2, stmt.c:2439); the later `(set r102 (symbol_ref D_801C8B64))` finds r100 in the
symbol's class and takes it (pseudo cost 1 < symbol cost 12, cse.c:481-486 / 6776-6803). Proven with dumps: a
`do { … } while (0)` around the stores + call makes CSE1 keep r102 separate (cse stops at NOTE_INSN_LOOP_END,
cse.c:8054-8056) but CSE2 (after_loop, loop notes ignored) re-merges it (scratch/dumps_B: `.cse` has insn 142 = symbol,
`.cse2` has it = r100) — score 57. Nothing invalidates r100 (a pseudo) at the call (invalidate_for_call removes only
call-clobbered hard regs and memory entries). SYMBOL_REF equality is by NAME POINTER (exp_equiv_p), and every
declaration of an identifier shares IDENTIFIER_POINTER (varasm.c make_decl_rtl, :477) — so no plain-C spelling of
the same symbol can be kept apart; only a different name string (an `__asm__("D_801C8B64")` declaration label,
varasm.c:482-485 builds `"*D_801C8B64"` in a fresh string) or a different address rtx (`(const (plus sym_other K))`,
another symbol at the same address = identical only after linking) reaches the target.
The caller-save / spill alternatives were checked and refuted: caller-saves needs `4*calls < refs` (regs.h:165, r100 has
4 refs, 1 call) and a spilled REG_EQUIV constant would reload `la a1,sym` (2 ins), not the target's `move a1,a0`.

(c) Closest moves:
- plain C (body.c, 56): the tree's `_m` block dropped, `VectorNormalSS(&D_801C8B64, &D_801C8B64);` — same score as
  body_free (the residual is exactly the shared pseudo).
- MINIMUM LEVER (body_minlever.c, 0): the tree's `__asm__ __volatile__` launder replaced by ONE block-scope declaration
  `extern u16 D_801C8B64_arg __asm__("D_801C8B64");` used only for func_8012F568's 6th argument, marked `// !FAKE:`.
  Zero bytes, the relocation names D_801C8B64 as before. Lever count 1 → 1, but a declaration instead of an asm
  statement. (It is the METHOD step-3 "declaration alias" form; the brief's rule against aliases that dodge cse means
  it stays a marked lever, not a close.)

(d) GENERATOR PROPOSAL: when the residual is one extra callee-saved register holding a global's ADDRESS that the
target re-materialises after a call (target: `lui/addiu` of the same symbol after the `jal`, the pre-call copy in
`$a0`), stop searching C spellings (cse2 re-merges any same-symbol constant) and emit the one-line declaration alias
for the post-call use as the minimum lever; flag the class for the structs/symbols phase (a second real symbol or a
struct member at that address would make it plain C).

(e) Did not work: do-while(0) around stores+call (57) or around the call only (63) — cse2 re-merges; dropping the
`_m` temp (56). The sweep's width/temp moves all 56 (none touches the shared constant).

(f) Method: counting first showed the one extra register was not a priority question (every allocno would get a
callee-saved reg); reading the `.cse` vs `.cse2` dumps proved which pass re-merges. The METHOD has no entry for
"target re-materialises a constant address after a call" — add one: "the original had a DIFFERENT address rtx; alias or
park".

(g) Structs: typing `D_801C8B64` as an SVECTOR (or making it `g.dir` of an overlay state struct starting at
0x801C8B60 — D_801C8B60/64/6C/70/74/78 look like one struct) does NOT change the decision by itself: cse compares the
address constants, not the types, so both call sites spelled `&g.dir` still share one pseudo. It WOULD help if the
original spelled the two sites differently (e.g. `&g.dir` for VectorNormalSS and a separate symbol/array for the
effect call) — that is the symbols/structs phase's question, testable only with the real layout.

Copies in other TUs: none (`grep -rln '12288) / 100' src/` → this TU only).
Files: body.c (plain C, 56), body_minlever.c (1 marked declaration alias, 0), scratch/v/{A,B,C,D}.c, scratch/dumps_B/.
