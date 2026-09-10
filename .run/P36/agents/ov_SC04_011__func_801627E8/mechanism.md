# func_801627E8 (src/ov_SC04_011/ov_SC04_011_jr_8015C32C.c) — score 0, lever-free

**Final: score 0 (MATCH, 19/19 ins), both levers removed** (`register u8 *p __asm__("$4")` and the
`__asm__ __volatile__("" : "=r"(p) : "0"(p))` re-tie barrier). Best text = `PACK/body.c`.
Verified with `.venv/bin/python tools/delever_search.py --try src/ov_SC04_011/ov_SC04_011_jr_8015C32C.c
func_801627E8 PACK/body.c --body` → `score 0 (OTHER; mine 19 ins, target 19) — MATCH`.

## (a) The residual in one sentence

The lever-free text folded the symbol straight into the load (`lui v0,%hi; lbu v0,%lo(D_8011F750)(v0)`, 17 ins)
where the target holds the address in a register first (`la a0,D_8011F750; lbu v0,0(a0)` + a load-delay `nop`,
19 ins) — a COUNT residual of 7 whose whole content is "the address stayed in a register, and it is `$a0`".

## (b) The pass and the decision, read from the compiler's own source

Two passes, both confirmed on RTL dumps (`cc1 -dc -dl -dg` on a micro TU, in `PACK/dumps/`), not from memory:

1. **cse does NOT fold it.** `find_best_addr` (`cse.c:2694-2712`) picks the equivalent with the lowest
   `ADDRESS_COST`; `mips.h:2895` gives `REG` = 1 and `mips_address_cost` (`mips.c:1630-1631`) gives a plain
   `SYMBOL_REF` = 2 under `-G0` (`SYMBOL_REF_FLAG` unset). So cse actively *keeps* `(mem:QI (reg 72))` —
   the `.cse` dump shows `(set (reg/v:SI 72) (symbol_ref "D_8011F750"))` alive in **both** the folding and the
   non-folding variant. The old lever's premise ("defeat the %lo-fold of the lbu" with a cse barrier) was aimed
   at the wrong pass.
2. **combine is the folder, and its gate is `added_sets_2`.** `try_combine` computes
   `added_sets_2 = ! dead_or_set_p (i3, i2dest)` (**`combine.c:1458`**). With the pointer used only by the load,
   `reg 72` is dead at i3, `added_sets_2 == 0`, the substitution yields
   `(set (reg 73) (zero_extend:SI (mem:QI (symbol_ref "D_8011F750"))))` — a legal MIPS address, `CONSTANT_ADDRESS_P` —
   it recognizes as `zero_extendqisi2`, i2 is deleted, and out comes the one-insn `lbu $2,D_8011F750` macro.
   Give `reg 72` **one more use after the load** and `added_sets_2 == 1`: combine must carry i2's set along in a
   PARALLEL, nothing on MIPS recognizes "set a reg to a symbol *and* zero-extend a load", the combination is
   rejected, and the standalone `la` survives into the output. The `.combine` dumps show exactly this: insn 8
   gone / `(mem:QI (symbol_ref))` in the folding variant, insn 8 alive / `(mem:QI (reg 72))` in the matching one.
3. **`$a0` is not a coincidence and needs no pin.** The extra use is the call's argument copy
   `(set (reg:SI 4 a0) (reg/v:SI 72))`; `set_preference` (`global.c:1348` → `:1535`) makes `$4` the preference of
   reg 72, global-alloc grants it (`.greg` shows `(set (reg/v:SI 4 a0) (symbol_ref …))`), and jump2's noop-move
   pass deletes the now-self copy. That single fact replaces **both** levers: the barrier that created the `la`
   and the `__asm__("$4")` pin that chose the register.

## (c) The move that closed it

**One move, two characters of real change: give the dispatch entry the pointer as its argument.**

- `extern void (*D_80192FD0[])(void);` → `extern void (*D_80192FD0[])(u8 *);`  (block-scope extern, inside the body)
- `D_80192FD0[idx]();` → `D_80192FD0[idx](p);`

Everything else in `body_free.c` is unchanged (the separate `idx = idx - 1;` statement still has to stay — see (e)).
This is also the *reading* the bytes support: `$a0` holds `&D_8011F750` at the `jalr`, i.e. each handler in the table
is called with the control block it dispatches on. The old source comment above the function ("force the full-address
materialization with the §21 re-tie barrier … and pin the pointer to $a0") is now wrong and should be replaced when
this is banked.

BODY-ONLY, so bankable: both edited declarations are block-scope `extern`s inside the function; nothing outside the
definition changes. `grep -rn D_80192FD0 src include` finds no file-scope declaration to conflict with (the only other
hit is an unrelated `Blk8 D_80192FD0` block-extern in `src/ov_SC06_015/`), so the same body text propagates to the
132 copies untouched.

## (d) GENERATOR PROPOSAL

> **R19 "argument-fed address" — when the residual is COUNT and the target holds a global's address in an
> argument register `$aN` (`la $aN,SYM` + a 0-offset load from `$aN`) where the lever-free text folds it into the
> load (`lui;lbu/lhu/lw %lo(SYM)`), and the block ends in a call, append that pointer as the call's N-th argument
> (widening the callee's block-scope `extern` prototype by one pointer parameter) instead of adding a barrier or a
> register pin.**

Mechanically decidable from the diff alone: the target block contains `la $aN,SYM`, the extra instruction count is
exactly +1 `addiu` (+ any load-delay `nop`), the register is an argument register, and a `jal`/`jalr` follows in the
same or a dominated block. The generator writes `(…, p)` at the call and appends `T *` to that callee's prototype;
`N` is read off the target's register. It is the natural companion to R18 (bystander-move) and subsumes the whole
"register-pin + re-tie barrier" pair that this family currently spends two levers on — the search cannot find it
because it only rewrites statements, never a call's *arity*.

Cheap pre-filter for the fleet: any body whose NEEDED sites are exactly `{pin $aN, launder}` on a pointer to a global,
where the target's `$aN` is live from the `la` to a `jalr`/`jal` and is never re-loaded — that is this class.

## (e) What did NOT work, with byte evidence

- **A second dereference of the same pointer** (`idx = *p; … idx = *p - 1;`, `PACK/c1.c`): **score 7, unchanged
  (17 ins)**. cse merges the two loads back into one, so `reg 72` is dead at the load again and combine folds as before.
- **A second, non-load use of the pointer** (`p[1] = 0;` after the call — micro `v1`): still `lbu $2,D_8011F750`
  *and* `sb $0,D_8011F750+1`. The extra use is in a different basic block, so cse's per-EBB constant propagation
  folds each reference independently and combine never sees a live reg. **The extra use must be in the same
  extended basic block as the load** — the argument copy is.
- **Struct-typed global read by field** (micro `v3`), **pointer-to-pointer copy** (`v2`), **index by a zero variable**
  (`v4`), **`extern u8 x[]` + `x[0]`** (`v6`): all emit the folded `lbu $2,D_8011F750`. §48-C1's "a struct global
  materializes a base" needs **2+** struct MEMs in the block; with one MEM the scalar and struct forms are identical.
- **An offset second load** (`idx = p[idx] - 1;`, micro `v5`) *does* produce the target's exact prologue/`la`/`lbu 0($3)`
  shape — proof that "keep the pointer live past the load" is the right mechanism — but it costs a second `lbu`
  and lands in `$3`, not `$4`. It is the diagnostic, not the fix.
- **Inlining the decrement** (`D_80192FD0[idx - 1](p)`, `PACK/c2`-style, micro `w2`): the `-1` const-folds into the
  table load (`lw $2,T-4($2)`), one instruction short. The tree comment's second idiom is still load-bearing; keep
  `idx = idx - 1;` as its own statement.
- `s32 idx = *p;` as a declaration-with-initializer instead of a separate assignment also scores **0** — either
  spelling matches; `body.c` keeps the separate statement because it is the smaller diff from `body_free.c`.

## (f) Where the method fell short

- **The residual is printed as a diff of *my* stream against the target's, but nothing prints the target's own
  instructions.** The whole crack came from reading the target's 19 instructions in one piece (`mipsel-linux-gnu-objdump
  -drz -j .text build/src/<tu>.o`, then `awk '/<fn>:/,/^$/'`) and noticing `$a0` — an *argument* register — held live
  from the `la` to the `jalr` with nothing in between. `--try`/`--explain` should print the target block with
  relocations, or at least mark argument registers; a "live from … to a call" annotation would have named this class
  in one line. **Worth adding to `--explain`.**
- **The pack's `history.txt` records only the mechanical search's moves, all of which rewrite statements *inside*
  the body.** The answer here changes the *interface* of a call (its arity). No generator in `tools/delever.py`
  (`sink_merges` R15, `constant_holders` R16, `constant_run_splits` R17, `bystander_moves` R18) can express that,
  so the 400+ compiles of runs g1/g2/g5/s1/s2/s4/s7 could never have reached score 0 — and a plateau at 3 read as
  "hard" rather than "out of the move set". **The engine should classify a plateau by whether the residual's
  register is an argument register, and hand that class to an agent immediately.**
- **The tree's own source comment asserted the wrong pass** ("defeat the %lo-fold of the lbu" — a cse claim) and I
  nearly spent the budget building cse barriers. The `.cse` dump refuted it in one look. Recommend: when a lever's
  rationale names a pass, dump that pass before trusting it (§454's "exonerate the instrument", applied to prose).
- `residual_moves.md` row 6 (address materialization via `find_best_addr`) points at cse and requires "≥2 uses in one
  EBB"; that is the *right* shape but the *wrong* pass and the wrong count. Row 6 should be corrected to: cse never
  folds a symbol into a mem on MIPS (REG is cheaper); **combine** does, gated by `added_sets_2` (`combine.c:1458`),
  so **one** extra same-EBB use of the pointer is enough — and a call argument is the cheapest such use.
