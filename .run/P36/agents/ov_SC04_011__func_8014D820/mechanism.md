# func_8014D820 (src/ov_SC04_011/ov_SC04_011_after.c) — score 0, MATCH, 304/304 ins

Levers removed: the `register u16 *a2 __asm__("$7")` pin (NEEDED) **and** the
`__asm__ __volatile__("" : "=r"(a2) : "0"(a2x))` launder (NEEDED) — both gone, plus the
`a2x`/`a2` copy pair they hung on. No pin, no `asm`, no added `volatile`, no added
`__builtin_*` (the pre-existing `__builtin_memcpy` in `body_free.c` is untouched).

## (a) The residual in one sentence

The target spends one extra instruction, `move a3,a2` at index 3, to copy the third
parameter out of `$6` into `$7` and then reads `a2[0]/a2[1]/a2[2]` through `$7`
(register pairs `a2->a3 x4`, `insert mine[3:3]`, mine 303 vs target 304) — my text let
the parameter stay in its own incoming register `$6`, so the copy was deleted.

## (b) The pass and the decision

`global.c` — global register allocation, hard-register *copy preferences*.

* `set_preference` (`tools/reference/gcc-2.7.2/global.c:1535`, reached from
  `global_conflicts` at `global.c:1348`): for every `(set (hard reg) (pseudo))` or
  `(set (pseudo) (hard reg))` it does `SET_REGBIT (hard_reg_copy_preferences,
  reg_allocno[pseudo], hardreg)` (`global.c:1588` / `global.c:1607`). A *call argument
  setup* insn is exactly such a set — passing a pseudo as argument N records a copy
  preference for that argument register.
* `find_reg` (`global.c:997-1030`): after the two-pass `REG_ALLOC_ORDER` scan it
  overrides `best_reg` with any still-free member of `hard_reg_copy_preferences[allocno]`
  of the same class. Then in `reload1`/`flow` a `(set (reg X) (reg X))` copy is deleted.

So the allocno of the third parameter has **two** copy preferences in the original —
`$6` (the incoming-argument copy emitted by `assign_parms`) and `$7` (the fourth
argument of the `func_80135A4C` call). `$7` wins; the parameter copy at the top of the
function survives as a real `move a3,a2`, and the argument-setup insn at the call site
degenerates to `move $7,$7` and is **deleted**. Net: +1 instruction at index 3, zero
instructions at the call — which is precisely the 303→304 delta and why the call site
*looks* like it only sets `$a0-$a2`.

Proved on bytes: score 0. The `set_preference`/`find_reg` reading is the explanation and
is consistent with the bytes, but I did not dump `.greg` to confirm the preference sets
directly — that part is a (well-supported) hypothesis.

## (c) The source move

**One move.** Call `func_80135A4C` with its real four-argument prototype and pass the
third parameter as the fourth argument, instead of casting the call down to three
arguments:

```c
-  if (((s32 (*)(s32, s32, s32)) func_80135A4C)(ent->f20, ent->f58, (s32) a1) == 0)
+  if (func_80135A4C(ent->f20, ent->f58, (s32 *) a1, (s32) a2) == 0)
```

The TU already carries the canonical declaration at file scope —
`extern s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3);` — so nothing outside the
body changes; the bank stays BODY-ONLY.

**Second (readability, byte-neutral).** With the pin gone, the launder pair collapses:
the parameter is named `a2` directly and `u16 *a2x; ... a2 = a2x;` disappears.

```c
-s32 func_8014D820(s32 a0, u16 *a1, u16 *a2x)
+s32 func_8014D820(s32 a0, u16 *a1, u16 *a2)
-u16 *a2;
-a2 = a2x;
```

Score 0 both with and without this simplification; `PACK/body.c` has it.

**The trap this function was built on.** The block comment above the function in the TU
(`ov_SC04_011_after.c`, the "one deliberate divergence (§27 step 2 / rule 3)" paragraph)
records the wrong conclusion in writing: *"func_80135A4C's canonical extern is 4-arg but
this call site sets only $a0-$a2, so the canonical decl is kept verbatim and the ARITY is
cast at the call site."* The call site sets `$7` — 20 instructions earlier, as the
parameter copy, because the allocator merged the two. Reading argument setup off the
instruction immediately preceding a `jal` is unsound under `-O2`: an argument whose value
is available at function entry and crosses no call can be placed by the allocator
anywhere in the dominating block, and its setup insn then vanishes.

## (d) Generator proposal

> When the residual is `COUNT` with `mine N` / `target N+1`, the inserted instruction is a
> `move` between two argument registers `$4-$7` near the top of the function, and the
> register pairs are `aX->aY` on a *parameter*: for every call in the body whose local or
> file-scope declaration has **fewer** parameters than the callee's real definition
> (`src/shared/ov/<callee>__<hash>.h`, or a wider `extern` already present in the TU) —
> or that is cast down to a narrower function-pointer type at the call site — re-emit the
> call at the full declared arity, trying each in-scope pointer/integer local and
> parameter as the missing argument, one candidate per compile.

The join is cheap and fully mechanical: the candidate set is (calls in the body) ×
(arity gap) × (locals live at the call), and the arity gap is a one-line grep join of the
TU's `extern` list against `src/shared/ov/*.h`. Two extra signals make it nearly
deterministic here: (1) the *deleted* argument-setup insn means the missing argument is
whichever value already occupies the target register `$Y` at the call, and the residual
names `$Y`; (2) an explicit function-pointer cast at a call site
(`((T (*)(...)) f)(...)`) that narrows the canonical prototype is a direct flag — it is
someone having previously "explained away" this exact residual.

## (e) What did not work, with byte evidence

* Everything the mechanical search had already tried: `g3/g4s/g5/s1/s2/s4/s7` — 4,674
  compiles across R5/R6/R7/R8/R18 (block, do-while, hoist, inline, bystander moves), all
  stuck at **8**. Correct, and diagnostic: *every mechanical generator rewrites statements
  that exist*; this residual needs a call's arity to change, which no generator can reach.
* Dropping the `a0v` temp (`s32 a0v; a0v = a0;` → use `a0` directly) after the match:
  score **6** (`COUNT`, mine 306 vs target 304 — `lhu a0,4(s3)` / `nop` / `subu s1,v0,a0`
  inserted, `move v1,s0` vs `move a0,s0`). `a0v` is load-bearing; it stays.
* I did not need to try any register-order or declaration-order perturbation — the arity
  hypothesis was the first thing tested and scored 0 on the first compile.

## (f) Where the method fell short

1. **The residual's own vocabulary hid the answer.** `insert ... move a3,a2` at index 3 in
   a prologue reads unambiguously as "parameter copy / register allocation", and it sent
   me into `local-alloc.c` `block_alloc` and `global.c` `find_reg` looking for a *conflict*
   that would make `$6` unavailable. The instruction is a parameter copy; the *reason* is a
   call 40 instructions later. Nothing in `residual.txt` links the two. A residual line
   that also reported "target register `$7` is an argument register whose setup insn is
   absent before the next `jal`" would have pointed straight at it.
2. **The engine has no read of the TU's own prose.** The answer was written, in English,
   30 lines above the function in the same file — and written as a *dismissal*. Neither
   `tu.txt` (two lines: path and name) nor the pack surfaces the TU's comment block. Packs
   should include the comment block immediately preceding the function; a previous
   session's "deliberate divergence" note is the highest-yield lead in the pack, because it
   marks the exact spot where someone chose a lever over an explanation.
3. **`sites.txt` mislabels causes as locations.** It reported a `$7` pin plus a launder as
   two NEEDED sites — two levers, one cause, and neither at the causal statement. A site
   list that clustered levers by the residual they suppress would have said "one cause,
   located elsewhere".

## Files

* `PACK/body.c` — final text, score 0.
* `PACK/mechanism.md` — this file.
