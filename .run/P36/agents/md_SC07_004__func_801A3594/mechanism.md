# func_801A3594 (md_SC07_004) — P36 S104 agent e35 — score 11 (lever-free; sweep best 7) -> 0, ZERO levers (was 2 pins: `$3` on b, `$2` on tw)

(a) Residual: 35 vs 36 ins. Lever-free, the SI->HI copy `t16 = tw` vanishes (the `xor` reads `tw` itself, which therefore
lands in `$a0`, the target's `move a0,v0` in the `beqz` delay slot is missing), and under it `a`/`b` are swapped
(`lhu v1/v0; subu v1,v1,v0` vs the target's `lhu v0/v1; subu v1,v0,v1`).

(b) Pass and decision — the SAME class agent e30 closed in ov_SC04_011 (`func_801836D4`, its mechanism.md), re-read on this
body's free dump (`scratch/dumps_free/`):
- The copy `(set (reg/v:HI 78) (subreg:HI (reg/v:SI 77) 0))` (free.i.rtl insn 85) and the `xor`'s read
  `(subreg:SI (reg:HI 78))` sit in ONE cse block (label 76 .. jump 102). `fold_rtx`'s SUBREG case (`cse.c:4836-4870`,
  "these SUBREGs just say how to treat the register") finds 78 equivalent to `(subreg:HI 77)` whose inner mode is SI and
  returns 77: free.i.cse insn 95 is `(xor:SI (subreg:SI (reg/v:HI 75) 0) (reg/v:SI 77))`, 78 is dead, `tw` lives to the
  xor. (`make_regs_eqv`, `cse.c:846-862`, is the same-mode-copy version of this; an `s32 t16` scores 11 too.)
- With the copy AND the `tw == 0` test moved INTO each case (a case-local `s32 tw`), the copy is in the case block and the
  `xor` in the join block — a new cse block, so no equivalence is available and the copy stays. The three-quantity
  block (a, b, tw local to the case, `local-alloc.c:1486-1500`, hand-written order, compares 0/1, 1/2, 0/1) puts `a` in
  `v0` and `b` in `v1`; the two case tails (`beqz v0; move a0,v0`) are merged by the post-reload cross-jump
  (`jump.c:2371`) into the one the target has. Proven on bytes (`--try` 0, 36/36); the cse fold proven on the free dump.

(c) Moves (joint; body.c = scratch/p/p1.c, score 0):
1. `s32 tw` declared inside each `case N: { ... }` block; `t16 = tw; if (tw == 0) return 1;` sunk into the case (copy
   BEFORE the test, as e30 found); the join keeps `if (diff == 0) goto ret1; xr = diff ^ t16; if (xr >= 0) goto default_case;`
2. `a`, `b` inlined into the subtraction (`diff = *(u16 *)(a0 + 0xE8) - *(u16 *)(a0 + 0x6);`) — the pins deleted.
   Named case-local `u16 a; u16 b;` also scores 0 (scratch/p/p2.c).
3. `s16 buf[12]` kept: the frame is exactly the array (buf[2] -> frame 8, buf[8] -> 16, both score 2 on the two `addiu sp`
   only); no orphan pseudo pads it (`.lreg`: every temp holds a hard register). 24 bytes = the tree's declaration.

(d) GENERATOR PROPOSAL: e30's rule, now confirmed on a second body: when a `switch` whose cases each load a value that is
tested after the join leaves a `move aK,vN` copy missing (`lh vN; ... join: beqz vN; move aK,vN`), sink the join test and the
narrowing copy INTO every case on a case-local variable (`{ s32 v = LOAD; keep = v; if (v == 0) return 1; } break;`) —
the copy leaves cse's block, cross-jump re-merges the tails after reload, and the extra case quantity flips local-alloc's
3-quantity order. Before any of that: grep `src/` for the same statement shape in other overlays (`xr = diff ^ t16`) —
the answer was banked in `.run/P36/agents/ov_SC04_011__func_801836D4/`.

(e) Did NOT work: a/b load order swapped (v1: 9, count still wrong), a/b per-case or inlined with the tail unchanged
(v4/v5: 9), `s16 tw` (cI: 11 — `lhu` + a direct HI test, `combine.c:simplify_comparison` strips the sign_extend, no `lh`),
`s32 t16`/`u16 t16`/`s32 xr`/the copy before the test/`(s16)(diff ^ tw)` (cA-cH: 11, the fold or `make_regs_eqv` every
time), `s16 tw` + `s32 t16` (cD: 17). The free sweep's best 7 (R2/R4 decl moves, R7 do-while) never moved the copy out
of the cse block.

(f) Method gap: METHOD step 12's "grep the WHOLE src/ for the shape" found the close in one `--try` — but only after I had
read the compiler for an hour (combine.c:1882's load+copy split was a plausible but wrong route: it needs a single-set HI
reg, and a two-case `switch` sets it twice). The residual-first order is right; "grep the shape across overlays" should be
step 0b, before the dumps. Also: the pack's `related.txt` was EMPTY for this function although a same-shape sibling with a
closed mechanism existed in another overlay — related.txt should search by statement shape, not by name.

(g) Structs: NO for the lever — the decision is cse's SUBREG fold over scalar locals and block layout; no memory-ordering
question. `a0` is an actor with a target position at 0xE8/0xEA, a direction at 0xEC/0xEE, an axis selector at 0x106 and a
position at 0x6/0xE (same layout e30 described for ov_SC04_011); with arrays (`o->tgt[axis]`, `o->dir[axis]`) the switch
could collapse to one indexed body, but the target has a real 2-way switch. Not tested (nothing left to close).

(h) Joint check (e35): all four e35 body.c files spliced into one copy of the tree TU with the four `extern void func_801A395C`
turned into `extern s32` (`md_SC07_004__func_801A3594/scratch/joint.py` -> `scratch/joint_tu.c`, object `scratch/joint.o`):
each of the four scores 0 through `--try` (whole-TU), and the object's `.text` (sha1 ad583f4dfb0c), `.rodata`, `.data`/`.sdata`/
`.bss`, relocations and symbol table are identical to the baseline snapshot; the only difference is the source-path string.
Gotcha for the next agent: a splice regex `^[^\n;]*\bfn\([^;{]*\)\s*\{` also matches a CALL line ending in `{`
(`if (func_801A3594(...)) {` at :2061) — anchor the definition at column 0 (`^[A-Za-z_]`).
