# func_801345F8 (src/ov_SC04_011/ov_SC04_011_jr_8012ACE0.c) — MATCH, score 0

Start 39 (lever-free), mechanical best 7, **final 0 (OTHER; mine 106 ins, target 106) — byte-identical.**
Three NEEDED pins removed: `$5` (param_1), `$4` (cc), `$0` (`zr`). No pin, no `asm`, no added `volatile`,
no `__builtin_*` in `body.c`.

## (a) The residual, in one sentence

At score 7 the lever-free text differed from the target in exactly two places, both of which are the SAME
gcc-2.7.2 decision seen twice: **the target keeps a copy of a value that my text let cse fold away** — once as
a register choice (`andi v0,a0` where the target reads the un-copied `andi v0,v0`), once as a whole missing
instruction (`andi v0,s1,0xffff` where the target has `move v0,s1` + `andi v0,v0,0xffff`, the −1 that made the
class COUNT). Both are the `$0`-add residual class (RC-12) — the `$0` pin's job in this function was never to
supply a zero, it was to be an *opaque operand* so that `x + zr` expanded as a real `addu` that cse could not
dissolve.

**The `$0` site here is NOT the R16 constant-holder shape.** `zr` is `register int __asm__("$0")` with **no
initializer** — gcc does not know it is zero, so `cnt-- + zr`, `c1 + zr`, `hi + zr` are genuine additions of an
unknown value. Deleting the holder and writing the constant `0` at each use (what `body_free.c` does) is
semantically right but *byte-destructive*: `+ 0` folds at tree level and the insn disappears. R16's "delete the
holder, write the constant" rule must therefore refuse an **uninitialized** `register …__asm__` declaration; the
right rewrite for that shape is the width lever below, not the literal.

## (b) The pass and the decision

Both defects are decided in cse, with local-alloc as the second gate. Read in `tools/reference/gcc-2.7.2/`:

* `cse.c:846-858` `make_regs_eqv` — a `(set c a)` reg-reg copy joins `c` into `a`'s equivalence class;
  `cse.c:2532-2575` `canon_reg` then rewrites the later uses to the class head, and the copy dies
  (`delete_dead_from_cse`, `toplev.c:2867`). This is why a plain `c = a` never survives as a `move`.
* `cse.c:7250-7262` (`cse_insn` tail) — a SET of `a` **invalidates** it, so a copy taken *before* `a` is
  re-set cannot be folded at a use *after* it. This is the row-1c-2 lever.
* `cse.c:1017-1019` `insert_regs` mode test — a set whose dest has a **narrower mode** than the source is not
  joined to the SImode class at all; `local-alloc.c:1287-1295` (`may_save_copy`) then cannot tie the two
  quantities either (the source does not die at the copy), so the set reaches reload and emits `addu d,s,$zero`.
  This is the row-1c-1 lever (`residual_moves.md` §1c) and the pin-free way to KEEP a copy.
* `expr.c` `expand_increment` / `enqueue_insn` / `emit_queue` — a **post**-decrement inside an expression is
  *queued*: `cnt--` does not emit `cnt = cnt - 1` where it is written, it emits it at the next **sequence
  point**. That is the missing half of the story and the reason the mechanical search never found this: inside
  `while ((… cnt-- …) != 0)` there is no sequence point before the test, so the queue is still pending, the mask
  reads `cnt` itself, and there is no copy to keep.
* `reorg.c` `fill_simple_delay_slots` then hoists the flushed `addiu s1,s1,-1` into the `bnez` delay slot —
  which is exactly where the target has it (`9a8c`).

## (c) The moves that closed it (one line each)

1. **`u32 uVar2` → `u16 uVar2`** — the 2nd range check's persist copy: narrowing the copy's dest stops cse
   substituting it for `c2` in `(c2 & 0xffff)`. Closed the register defect at `999c`. *(score 7 → 6)*
2. **`while (((cnt-- + 0) & 0xffff) != 0) {` → `for (;;) { rem = cnt--; if (rem == 0) break;` with a new
   `u16 rem;`** — the statement break is a **sequence point** that flushes the queued decrement between the copy
   and the test (so cse's `{rem,cnt}` class is invalidated), and `rem` being **16-bit** stops `insert_regs`/
   `combine_regs` from dissolving the copy. Together they emit the target's `move v0,s1` + `andi v0,v0,0xffff`.
   *(score 6 → **0**)*
3. Cosmetic, each re-verified at 0: `int c8000 = 0x8000` inlined as the literal; every leftover `+ 0` dropped
   (`uVar6 = c1;`, `uVar2 = c2;`, `harg = hi;`); the declaration run merged back to three lines. The prior
   mechanical path's two moves are retained and still load-bearing (`R2 decl-order cc,param_1`;
   `R12 uVar6 u32→u16`, `R12 harg int→u16`).

## (d) GENERATOR PROPOSAL — one sentence

**R19 "flush-and-narrow":** when a `$0`/opaque-add pin sits on a value read out of a variable that is
**modified in the same expression** (a `p++`/`p--`/compound-assign inside a loop condition or a call argument),
hoist that read into its own statement as a **new 16-bit local** (`u16 t; … t = cnt--; if (t == 0) break;`,
turning `while (COND)` into `for (;;) { …; if (!COND) break; …}`), because the statement boundary flushes gcc's
queued post-increment (`expr.c` `emit_queue`) so cse invalidates the class at the modification
(`cse.c:7250-7262`) and the narrow dest keeps the copy alive as `addu t,src,$zero` (`cse.c:1017-1019`).

Sub-rule worth wiring separately (it is cheap and it scored twice here): **when the residual is a single
`REG-caller` swap on an `andi`/mask whose operand is a persist copy, narrow the persist variable to `u16`** —
this is `residual_moves.md` row 1c-1 applied to a masked value, and it fixed defect A in one compile.

Also a **refusal** for the existing R16: never rewrite a `register T v __asm__("$N");` that has **no
initializer** into a constant — it is an opaque operand, not a constant holder.

## (e) What did NOT work, with byte evidence

| try | score | why |
|---|---|---|
| `while (((cnt--) & 0xffff) != 0)` (drop the `+ 0`) | 6, 105 ins | no sequence point → queue pending → mask reads `s1`, no copy |
| `while ((u32)(u16)cnt-- != 0)` | 12, 107 ins | the cast adds an insn and changes the loop shape |
| `for (; (cnt & 0xffff) != 0; cnt--)` | 11, 105 ins | decrement lands *before* the test; still no copy |
| `while ((cnt & 0xffff) != 0) { cnt--; …}` | 11, 104 ins | −2: both the copy and the mask fold |
| `u16 rem; while (((rem = cnt--) & 0xffff) != 0)` | 12, 107 ins | **width lever alone** — no sequence point, so the copy folds and gcc adds an entry guard |
| `u32 rem; while (((rem = cnt--) & 0xffff) != 0)` | 6, 105 ins | neither lever fires |
| `u32 rem; for (;;) { rem = cnt--; …}` | 9, 108 ins | **sequence point alone** — copy still dissolved (same mode) |
| `u32 rem; while (1) { rem = cnt--; …}` | 29, 106 ins | ditto, plus `while(1)` costs the register flow |
| final body with `u32 rem` (control) | 5, **105** ins | −1: proves the `u16` width is what carries the copy |
| final body with `s16 rem` (control) | 1 | `s16` is **not** interchangeable with `u16` here — refines `residual_moves.md` row 1c-1's "u16 and s16 equivalent" |
| final body with `while (1)` for `for (;;)` (control) | 29 | `for(;;)` is load-bearing; `while(1)` keeps a real loop-continuation test |
| final body with `u32 uVar2` (control) | 1 (REG-caller) | proves move 1 |

**A second spelling that also reaches 0** (kept out of the deliverable only on readability): 
`while (rem = cnt--, rem != 0) { … }` — the **comma operator is the sequence point**, which is the cleanest
possible proof of the `emit_queue` mechanism: the identical expression *without* the comma
(`while ((rem = cnt--) != 0)`) scores 12.

## (f) Where the method fell short

* **The mechanical search cannot cross a sequence point.** Every generator it has (R2/R3/R6/R9/R12/R18) edits a
  declaration or permutes existing statements; none *splits an expression into two statements*. That is the one
  move this function needed, and it is why 4,000+ compiles across seven runs all stalled at 7. R19 above is
  exactly that missing generator.
* `residual_moves.md` §1c is excellent and got me here in one read, but its row 1c-1 states the bound as
  "≥2 surviving consumers" and calls `u16`/`s16` equivalent. Here the copy had **one** consumer and still
  survived, and `s16` scored 1 while `u16` scored 0 — the real bound is the *mode change plus a live source*,
  and signedness matters when the consumer is a mask. Worth amending the row.
* §1c's opening note ("the `$0`-add exists because a plain copy never survives as a `move`") never mentions the
  **queued post-increment**, which is half of every `$0`-add that sits on a `x++`/`x--`. Adding one line about
  `emit_queue` to §1c would have made this a one-shot.
* **Instrument noise:** two `--try` runs returned a spurious `COMPILE-ERROR` / a python traceback pointing at an
  unrelated header (`../shared/ov/func_8012D3B4.h`) and re-ran clean immediately. With ~20 agents sharing the
  scratch build, a `--try` failure that is not about your own text should be **retried once before it is
  believed** (R40, exonerate the instrument).
