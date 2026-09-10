# func_801651B8 (src/ov_SC04_011/ov_SC04_011_jr_8015C32C.c) — score 0, MATCH, no levers

Start 29 (COUNT; mine 38 ins, target 34); mechanical best 8; **final 0** on the 1st `--try`.

## (a) The residual in one sentence

The lever-free body walked the table pointer by hand (`puVar1 = puVar1 + 4`), which made the
pointer a **second basic induction variable**; loop.c then strength-reduced the three
`puVar1[3]` address givs into a **third walking register** (`addu $16,$17,12` + `addu $16,$16,16`)
whose extra live range forced a **fourth callee-saved register** (`sw $19` / `lw $19`) — +4
instructions and the whole `s0/s1/s2/s3` colouring shifted by one (`s1->s0`, `s3->s2`).

## (b) The pass and the decision, read from the compiler's own source

Pass: **loop** (`tools/reference/gcc-2.7.2/loop.c`), `strength_reduce`.

Proven on the real-TU dumps (`PACK/scratch/dumps/dumps_free/free.i.loop` vs `dumps_mine/mine.i.loop`,
made with `tools/cc1_dumps_tu.sh` on a spliced copy of the TU in `PACK/scratch/wk_free|wk_mine`):

lever-free body — **two** bivs:

```
Insn 67: possible biv, reg 74, const = 1        <- the counter i
Insn 70: possible biv, reg 73, const = 16       <- the hand-walked pointer
Cannot eliminate biv 73: biv used in insn 50.   <- loop.c:5976 (maybe_eliminate_biv)
Insn 37/57/61: dest address src reg 73 ... add 12
giv at 57 combined with giv at 61               <- combine_givs, loop.c:5527 (fn at :5494)
giv at 37 combined with giv at 61
giv at 61 reduced to (reg:SI 85)                <- passes loop.c:3822 `v->lifetime*threshold*benefit < insn_count`
```

my body — **one** biv:

```
Insn 75: possible biv, reg 75, const = 1        <- the counter, the ONLY biv
Insn 41: giv reg 74 src reg 75 ... mult 16 add (reg/v:SI 73)   <- p = base + i*16 is a giv
giv of insn 39 not worth while, 0 vs 15.        <- loop.c:3828, the bare i*16 giv dropped
giv at 41 reduced to (reg:SI 88)
biv 75 can be eliminated.
```

The `+12` field access never becomes a giv at all in my body: it rides the single reduced giv as
an immediate, which is exactly the target's `lw v0,12(s0)` / `sw v0,12(s0)` / `addiu a2,s0,8`.

The decision sites, verbatim from `tools/reference/gcc-2.7.2/loop.c`:
* `loop.c:3822-3828` — `if (v->lifetime * threshold * benefit < insn_count && ! bl->reversed)` -> `v->ignore = 1`
  (the "not worth while" gate; the combined add-12 giv clears it in the free body and is reduced).
* `loop.c:5494` / `:5527` — `combine_givs`, `"giv at %d combined with giv at %d"` (the three add-12 uses merged
  into one, which is what raises the benefit above that gate).
* `loop.c:5976` — `"Cannot eliminate biv %d: biv used in insn %d."` — the hand-walked pointer cannot be
  eliminated because its *value* is an argument to the call, so it must both live and increment.

This is row 10 of `.run/P36/engine/residual_moves.md` ("Two walked pointers vs one base + offsets",
`basic_induction_var` :4819, `combine_givs` :5494) — the row named the reading; this is the byte proof
and the source move.

The already-matched sibling directly above in the same file, `func_80165140`, carries the same finding as a
hand comment (`src/ov_SC04_011/ov_SC04_011_jr_8015C32C.c:4505-4511`): "recompute `p = &D_801EDCA8[i]` each
iteration (NOT p++) so gcc reduces base+i*0x10 into a SINGLE pointer IV with immediate offsets 0/8/0xC".
**Reading the neighbouring matched function's comment would have produced this answer in one minute.**

## (c) The move(s) that closed it

1. **Fold the hand-walked pointer back into the index**: `puVar1 = puVar1 + 4` (a second biv) replaced by
   `p = &tbl[i]` recomputed from the loop counter (one biv, one reduced giv). This alone is the whole crack.
2. **Type the table** so the field offsets are immediates rather than `[3]` on an `s32*`:
   `Slot_80165140 *tbl = (Slot_80165140 *)&D_801EDCA8;` — a body-local cast, because the file-scope
   `extern s32 D_801EDCA8;` at line 4537 forbids the sibling's block-scope `extern Slot_80165140 D_801EDCA8[8];`
   redeclaration. Byte-neutral; readability only.
3. **Drop the function-pointer casts on both calls**: `func_80165240(param_1, (u8*)param_1+0x2c, (u8*)param_1+0x50)`
   and `func_80165240(param_1, p, &p->b)` — the file-scope prototype at line 4536 already has the honest arity and
   types, so the `((s32 (*)(s32,s32,s32))...)` cast was decompiler noise. Byte-neutral.
4. The `launder` on `a0v` and the `$16` pin both fall out: the `move a0,s2` the launder was faking is emitted
   anyway, and the `$16` colour is what the single-IV allocation produces on its own.

Final text (15 lines, no `register`, no `asm`, no added `volatile`, no `__builtin_*`): `PACK/body.c`.

## (d) GENERATOR PROPOSAL — R20 `index_the_walked_pointer`

**When a `do`/`for` loop has BOTH a counter incremented by 1 and a pointer local incremented by a constant
inside the same body, and the residual class is COUNT with `mine > target` by 2 or 4, rewrite the pointer's
self-increment away and recompute it from the counter at the top of the body
(`p = p + K;` deleted, `p = base + i*K;` inserted as the first statement), trying the loop's other
`base`-valued locals in turn as `base`.**

Rationale for a mechanical family: the shape is syntactically detectable (two increments in one loop, one of
them by 1), the rewrite is a two-line text edit, and the payoff is the removal of a whole induction variable —
which is why the mechanical search's 127-copy, 1,800-compile budget never found it (R2-R14 only permute
declarations, widths, blocks and adjacent statements; none of them can delete an increment). The inverse
direction ("+2 instructions, target walks two pointers") is the same rule run backwards and should be offered
when `mine < target`.

## (e) What did NOT work, with byte evidence

* `extern Slot_80165140 D_801EDCA8[8];` as a block-scope declaration, copying the sibling `func_80165140`
  verbatim — **COMPILE-ERROR**. The sibling can do it because its block-scope declaration precedes the
  file-scope `extern s32 D_801EDCA8;` at line 4537; mine follows it, so the types conflict. The
  `(Slot_80165140 *)&D_801EDCA8` cast is the body-only substitute and it scores 0.
* The mechanical history (`history.txt`) shows seven runs, 1,816 compiles, all stalled at 8 via
  `R6 inline iVar2 + R7 do-while`. Those two moves reduce the instruction count by shuffling the counter, but
  they never touch the second biv, so 8 is a floor for that family — the search was searching the wrong axis.

## (f) Where the method fell short

The brief's step 1 sends you to `residual_moves.md` and the cookbook, but not to **the same file's neighbours**.
This function's answer was written in English 30 lines above it, in the `// @class: struct` header of the
already-matched `func_80165140`, which shares the table, the stride and the loop shape. Recommendation for the
next brief: **step 0 = read the `// @class:` / `// @stuck:` header comments of the matched functions
immediately before and after your target in the TU, and any function that touches the same global** (here
`grep -n D_801EDCA8 <tu>` returns the answer in four lines). A cheap mechanical version: have the pack ship a
`neighbours.txt` with the header comments of the nearest matched siblings that share a global with the target.

Second, smaller: `--try`'s COMPILE-ERROR text is truncated to the last ~300 characters, which was the tail of a
harmless `#define NULL` redefinition note rather than the real `conflicting types` line. It cost one round of
guessing. Printing the FIRST error line as well as the last would fix it.
