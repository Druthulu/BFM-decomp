# func_801A395C (md_SC07_004) — P36 S104 agent e35 — score 7 (lever-free) -> 0 in plain C, ZERO levers, but a SIGNATURE change (void -> s32): PARKED (d29 class)

(a) Residual: 26 vs 29 ins. The target RETURNS a value: `li v0,1` on the `cur == t` path (its own `j epilogue; li v0,1`),
`move v0,zero` in the `bnez` slot and `li v0,1` after the final `sh` — every caller in the TU already casts the function to
`s32 (*)(s32, s32)` (lines 1122, 1617, 2339) and the tree's `extern` at :1482 says "real sig returns s32". The tree faked
the value with a `"r"(ret)` keepalive plus a barrier that kept the two `ret = 1` apart. Lever-free and `void`, `ret` is dead
and the three value insns vanish.

(b) Pass and decision (dumps `scratch/dumps_C/` = the close, `scratch/dumps_s1/` = the 4):
- With `s32` and early returns, jump1's block swap (`jump.c:1800-1870`, "Look for if (foo) bar; else break;") fires on
  `if (overshot) return 0;`: the condjump's label is used once, range1 (`v0 = 0; j Lend`) ends in a simple jump to
  label2 = Lend, and range2 (`sh; v0 = 1; j Lend`) ends in a jump + barrier, so `invert_jump` and the two ranges are
  exchanged — the `return 1` block now falls through to Lend and the `return 0` block (`move v0,zero`) is the LAST insn
  before the return label (C.i.jump: 87 -> 96, `99 sh; 102 li; 104 j 424; L423: 91 move v0,0; L424`).
- Therefore jump2's cross-jump (`find_cross_jump`, `jump.c:2371`) finds no match for the equality path's `li v0,1; j Lend`
  (i2 = `move v0,zero` != `li v0,1`), the block stays, and reorg fills the `j`'s slot with the block's own preceding
  `li v0,1` (C.i.dbr insn 123: `sequence [jump 29 -> 112, insn 27 v0 = 1]`), and the `return 0` block's `move v0,zero`
  goes into the `bnez` slot — the target's `bnez v0,epilogue; move v0,zero` / `j epilogue; li v0,1`.
- With `return 0` INSIDE each arm (s1, score 4) the swap condition fails (`JUMP_LABEL (range1end) == label2` is false —
  the label after the skipped `return 0` is the arm's join, not Lend), the final block is `sh; li v0,1`, cross-jump merges
  the equality path's `li v0,1` into it and the condjump is inverted to `beq v0,a1,<li>` (mine).
- `move a2,a1` / `sh a2,10(a0)`: the parameter's raw copy is what the final store writes (its low half is `t` anyway);
  `= t` and `= a1` both score 0 (C_p32_t, D_p32_a1). A `(s16)a1` cast at each use instead of the `t` local scores 12/13 —
  the sign-extension is then re-done per use.
All claims proven on bytes (whole-TU `--try` 0, 29/29: `scratch/w/C_p32_t_tu.c`, also `D_p32_t_tu.c`, `D_p32_a1_tu.c`).

(c) Moves (body.c = scratch/w/C_p32_t.c):
1. `void` -> `s32`; `ret` deleted; `return 1;` on `cur == t`, `if (overshot) return 0;`, final `*(s16 *)(a0 + 0xA) = t; return 1;`
   (the tree's `overshot` flag kept — it is what puts the `return 0` in one block after the if/else);
2. the barrier and the keepalive deleted; `t = a1` (the `(s16)` cast on an `s16` local is implicit).
3. A `D` shape (each arm ends `*(s16 *)(a0 + 0xA) = t; return 1;`, no `overshot`) also scores 0 — cross-jump merges the
   duplicated tails back. `body_tu_s32.c` = the whole TU with the four `extern void func_801A395C` turned into `extern s32`
   (the casts at the three call sites can then go) — this is the file that scores 0 with `--try` (no `--body`).

(d) GENERATOR PROPOSAL: when a `void` body ends with a `"r"(ret)` keepalive and the residual's missing insns are
`li v0,K` / `move v0,zero` on return paths, the function RETURNS `ret`: emit the `s32` signature with the TU's `extern`s
changed and `return` at each `ret = K` (the R-d29 rule); then, when the equality path's `li v0,1; j` is still merged, put
the last `return 0` in ONE block AFTER the if/else (a flag tested once) so jump1's range swap (`jump.c:1800-1870`) makes
`return 0` the final block and cross-jump has nothing to merge.

(e) Did NOT work: every `void` spelling (the free sweep's 190 compiles, all 7; a keepalive-only body `ml/m1.c` 4 — the
barrier is needed too, so the tree's two levers are the minimum for `void`: `body_minlever.c` = the tree's body);
`s16 a1` parameter (compile error against the TU's `extern`s — not tried further, the `move a2,a1` says the raw parameter
is kept anyway); `(s16)a1` at each use (12-13); `return 0` inside the arms (A/B/E shapes: 4).

(f) Method gap: none — d29 named the class exactly ("a `void` function whose last statement is a keepalive of `v0` RETURNS
it"). The one new fact is the block-swap rule that decides whether the equality path keeps its own `li v0,1`
(`jump.c:1800`), which no generator can reach because it depends on WHERE the `return 0` sits relative to the if/else.
`--try --body` cannot score a signature change (the file-scope `extern void` conflicts); whole-TU `--try` with the
`extern`s rewritten does (`scratch/splice_sig.py`).

(g) Structs: NO — the decisions are jump1's block swap and jump2's cross-jump over the control flow; no memory access is
involved in the lever. `a0` is an object whose `s16` at 0xA is an angle stepped by 2 toward the target `a1` (a
`step_toward(s16 *field, s16 target)` shape); a struct type would read better (`o->ang`) and would not change the bytes
(same `mem:HI`). Not tested.

(h) Joint check (e35): all four e35 body.c files spliced into one copy of the tree TU with the four `extern void func_801A395C`
turned into `extern s32` (`md_SC07_004__func_801A3594/scratch/joint.py` -> `scratch/joint_tu.c`, object `scratch/joint.o`):
each of the four scores 0 through `--try` (whole-TU), and the object's `.text` (sha1 ad583f4dfb0c), `.rodata`, `.data`/`.sdata`/
`.bss`, relocations and symbol table are identical to the baseline snapshot; the only difference is the source-path string.
Gotcha for the next agent: a splice regex `^[^\n;]*\bfn\([^;{]*\)\s*\{` also matches a CALL line ending in `{`
(`if (func_801A3594(...)) {` at :2061) — anchor the definition at column 0 (`^[A-Za-z_]`).
