# func_8017A3D8 (ov_SC04_011_jr_80178D40.c) — pin `$4` removed, score 3 → 0

**Final: score 0, MATCH.** `PACK/body.c` is byte-identical and body-only (bankable).
A second, *more readable* spelling also reaches 0 but needs one word changed outside the
definition — see "The two paths" at the end.

## (a) The residual in one sentence

Every instruction and every position agreed; only the case-100 temp's colour differed —
mine `lui/lh/beq v1` (`$3`), the target `lui/lh/beq a0` (`$4`), `v1->a0 x4`, 53 ins both.

## (b) The pass and the decision, read from the compiler's own source

Proved from the `-dl`/`-dg` dumps of the real TU (both variants, `PACK/dumps/`):

* **Lever-free draft** — `.lreg` header: `Register 74 used 2 times across 3 insns **in block 4**`.
  The `in block N` tag is the `local_alloc` gate (`local-alloc.c:472`): one block, one death ⇒ a
  local quantity. Block 4 holds exactly two quantities, `74` (the `lh` of `D_801EEC90`, born insn 35,
  dead insn 39) and `77` (the `li -1`, born 38, dead 39). `qty_compare`'s density
  (`local-alloc.c:1579`, `refs*log2(refs)*size/(death-birth)`) ranks the 2-insn constant above the
  3-insn load, so `77` is coloured first; `find_free_reg` (`local-alloc.c:2158-2175`, and
  `local-alloc.c:2107` `used |= regs_live_at[ins]` over the qty's window) then hands it `$2`, marks
  `$2` live over `[38,39)` — which is *inside* `74`'s window `[35,39)` — and `74` first-fits to the
  next free regno, `$3`. Dump confirms: `;; Register 77 in 2.` / `;; Register 74 in 3.`
  **There is no source move inside block 4 that can reach `$4`**: with only two quantities in the
  block, first-fit can never skip past `$3`. (Byte-proven: five independent block-4 rewrites —
  no temp, `short` temp, inverted `if`, initialiser-at-declaration, function-scope declaration —
  all scored exactly 3.)

* **The target** — the value is *not* a local quantity at all. Passing it to the call in the
  successor block makes it live across the `beq`, so it fails `local-alloc.c:472` (2 blocks) and
  becomes a **global allocno**; `.lreg` then reads `Register 74 used 3 times across 4 insns` with
  **no `in block`** tag, and it is absent from the `;; Register N in R` local list. The argument
  copy `(insn 43 (set (reg:SI 4 a0) (reg/v:SI 74)))` makes `global.c:1348` call `set_preference`,
  which at **`global.c:1589`** sets `hard_reg_copy_preferences[allocno(74)] |= {$4}`;
  `find_reg` applies the copy preference ahead of its first fit at **`global.c:1001-1015`**.
  `.greg`: `74 in 4`, and the copy has become `(set (reg:SI 4 a0) (reg/v:SI 4 a0))`.
  That self-move is then deleted as a noop move by the post-reload
  `jump_optimize (insns, 1, 1, 0)` at **`toplev.c:3142`** → `jump.c:308` — **so the argument costs
  zero instructions**, which is why the count stayed 53 and only the colour moved.

The pin `register int a __asm__("$4")` was a stand-in for that copy preference: it wrote the same
`$4` by hand and left the constant to take `$2`.

## (c) The source move that closed it

The evidence that this *is* the original source, not a trick: `func_8001AAA0` is declared
`extern int func_8001AAA0(void);` in this TU (line 3495) but is **defined** in
`src/800.c:7846` as `void func_8001AAA0(s32 arg0) { func_8001ABBC(1, arg0, 0, 0, 0); }`, and two
other TUs already declare it correctly — `src/ov_SC03_099/ov_SC03_099_jr_801588CC.c:1086`
`extern int func_8001AAA0(int);` with the call `func_8001AAA0(0x83)`. The `(void)` prototype here
is simply wrong, and the original passed the loaded value:

    return func_8001AAA0(a) != 0;

**Move (body-only, what `PACK/body.c` contains):** route the value into `$a0` by making it the
call's argument, spelling the true signature at the call site so no outside declaration changes:

    return ((int (*)(int))func_8001AAA0)(a) != 0;

`((int (*)())func_8001AAA0)(a)` also scores 0 (tested); the explicit `(int)` form is kept because it
documents the callee's real signature.

## (d) GENERATOR PROPOSAL

> When the residual is REG-only, the count matches, and the whole difference is one value that the
> target holds in `$a0..$a3` while the draft holds it in `$v0/$v1`, and that value's last use in the
> draft is immediately before a `jal` whose delay slot is a `nop` and which takes no argument in the
> draft: re-issue the call with that value as argument N (N = the a-register's index), spelling it
> `((RET (*)(T))fn)(v)` so the edit stays inside the body — the argument copy becomes a self-move
> and is deleted at `toplev.c:3142`, so the instruction count cannot change; **and cross-check the
> callee's real definition elsewhere in `src/` first — a `(void)` extern that disagrees with the
> definition is the tell.**

Mechanisable cheaply and worth toolifying beyond the generator: a census of
`extern … fn(void);` declarations whose defining TU gives `fn` parameters. Every such site is a
candidate `$aN` pin that a corrected call can remove. (`grep -rn 'extern .*func_XXXX' src/` against
the definition's arity — the two disagreeing prototypes for `func_8001AAA0` in this tree were found
by one grep.)

## (e) What did NOT work, with byte evidence (each one compile, `--try`)

| candidate | score |
|---|---|
| lever-free draft (baseline) | 3 |
| no temp at all: `if (D_801EEC90 != -1)` | 3 |
| `short a;` instead of `int a;` | 3 |
| inverted `if` (`a == -1` first, arms swapped) | **11** (COUNT — worse) |
| `int a = D_801EEC90;` (initialiser at the declaration) | 3 |
| declaration hoisted to function scope | 3 |
| block-scope `extern int func_8001AAA0(int);` inside the case | **COMPILE-ERROR** — `conflicting types for 'func_8001AAA0'` (gcc 2.7.2 rejects a block-scope redeclaration incompatible with the file-scope one, so the honest spelling cannot be smuggled into the body) |
| `((int (*)(int))func_8001AAA0)(a)` | **0 — MATCH** |
| `((int (*)())func_8001AAA0)(a)` | **0 — MATCH** |
| whole-TU: `extern int func_8001AAA0(int);` + `func_8001AAA0(a)` | **0 — MATCH** |

Both matching variants were also checked for blast radius: `objdump -drz` of the whole candidate
object is identical to `build/src/ov_SC04_011/ov_SC04_011_jr_80178D40.o` (only the scratch source
path in `STT_FILE` differs), so nothing else in the 3,500-line TU moved.

## (f) Where the method fell short

1. The pack's `history.txt` shows four engine runs and ~600 compiles all stuck at 3 with moves
   confined to the function body. The engine's move set cannot reach this residual **in principle**,
   because the fix is a *call site's argument list*, not a statement/declaration rewrite. Reading
   `.lreg` for the `in block N` tag took ~5 minutes and settled it immediately: two quantities in the
   block, first-fit cannot reach `$4`. **Reading `.lreg` for the `in block N` tag should be step 1 of
   every REG-only residual** — it says at once whether the answer is inside the block (local qty:
   density/order moves) or outside it (global allocno: liveness/preference moves).
2. `residual_moves.md` Class 1a has twelve rows, none of which is "make the value a call argument".
   Row 1b-5 ("make or break a call crossing") is the nearest relative but is written for the
   callee-saved bank; the caller-saved `$aN` case — a copy preference from an argument copy that
   reload then deletes — deserves its own row. Suggested text is the generator in (d).
3. The engine treats the extern block above the function as immutable. That block is *decompiler
   output*, not ground truth, and it is demonstrably wrong here. A pre-pass that reconciles each
   TU's `extern` prototypes against the defining TU would have removed this lever with no search at
   all — and, per the two-paths note below, would let the readable spelling be the banked one.

## The two paths

* **Bankable now, body-only (`PACK/body.c`, score 0):**
  `return ((int (*)(int))func_8001AAA0)(a) != 0;` — one line, no lever, no `volatile`, no builtin.
* **Readable, two lines, needs the coordinator (also score 0, whole object verified):**
  line 3495 `extern int func_8001AAA0(void);` → `extern int func_8001AAA0(int);`
  line 3510 `return func_8001AAA0() != 0;` → `return func_8001AAA0(a) != 0;`
  This is the correct prototype (`src/800.c:7846`), it matches what
  `src/ov_SC03_099/ov_SC03_099_jr_801588CC.c:1086` already says, and it removes the cast noise.
  **Recommended** if the bank can take a two-hunk patch; the 118 sibling copies each carry the same
  wrong prototype, so the same two-line edit propagates unchanged.
