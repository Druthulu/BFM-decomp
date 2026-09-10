# func_80157D20 (src/ov_SC04_011/ov_SC04_011_jr_80154C24.c) — T7 agent report

**Final score: 0 (BYTE-IDENTICAL, 21/21 words + relocs) — but NOT body-only.**
The two `!FAKE` pins are genuinely NEEDED *while the file-scope declaration stays `(void)`*.
They are not needed at all once that one declaration line is widened: the function simply **has two
parameters**, and the pins are the project's workaround for a wrong canon.

* `PACK/body.c` — the score-0 text (a plain 2-parameter definition, no pin, no `asm`, no `volatile`, no builtin).
* `PACK/body_bodyonly.c` — the best text that compiles against the *unchanged* canon: **score 4**.
* `PACK/scratch/repro.sh` — one command, writes only inside PACK, prints `IDENTICAL=True`.

---

## (a) The residual in one sentence

The lever-free body is 19 instructions against the target's 21: it is missing exactly the two
instructions that **read the incoming argument registers** — `move s1,a0` in the prologue and
`move s0,a1` in the delay slot of `jal func_80156648` — and, as a knock-on, allocates the two
pseudos to the opposite callee-saved pair (`param_1`→`s0`, `param_2`→`s1`; the target has
`param_1`→`s1`, `param_2`→`s0`).

Target (`build/src/ov_SC04_011/ov_SC04_011_jr_80154C24.o`, 21 ins):

```
addiu sp,sp,-32 ; sw s1,20(sp) ; move s1,a0 ; sw s0,16(sp) ; sw ra,24(sp)
jal func_80156648 ; move s0,a1        <- delay slot
sll s0,s0,0x1 ; lui at,%hi ; addu at,at,s0 ; lhu a1,%lo(at)
jal func_80147078 ; move a0,s1
jal func_80157D74 ; move a0,s1
lw ra ; lw s1 ; lw s0 ; addiu sp,sp,32 ; jr ra ; nop
```

## (b) The pass and the decision, with `file:line`

`move s1,a0` / `move s0,a1` are **parameter home copies**, and nothing but a parameter can emit them.

* `gcc-2.7.2/function.c:assign_parms` walks `DECL_ARGUMENTS` and, for each parm, makes a pseudo
  and emits `emit_move_insn (parmreg, entry_parm)` — the copy out of the incoming hard register
  (`tools/reference/gcc-2.7.2/function.c`, the `if (GET_CODE (entry_parm) == REG …)` /
  `emit_move_insn` arm of `assign_parms`). With `DECL_ARGUMENTS == 0` the arg registers are never
  even entered in the live-in set, so **`$4`/`$5` never appear as a source anywhere downstream**:
  `local-alloc.c:block_alloc`/`combine_regs` and `global.c:find_reg` can only *choose homes for*
  pseudos, they cannot invent a read of a hard register that no RTL mentions.
  Empirically: every lever-free spelling I tried is 19–20 instructions and none contains a
  reference to `a0`/`a1` as a source.
* Why the copies land where they do (proven by the score-0 build, not just read):
  the `move s1,a0` sits *between* `sw s1,20(sp)` and `sw s0,16(sp)` because
  `sched.c:schedule_block` interleaves the prologue stores with the parm copies, and
  `move s0,a1` is pulled into the `jal` delay slot by `reorg.c:fill_slots_from_thread`
  (an insn from *before* the call, still legal there because the delay slot runs before the callee).
  Both fall out for free from the 2-parameter spelling.
* The register pair (`param_1`→`s1`, `param_2`→`s0`) is likewise not something the body-only text
  can steer: with real parms the allocnos are created in `DECL_ARGUMENTS` order and
  `global.c:allocno_compare` orders them by `(live_length, n_refs)`; with two dead uninitialised
  locals the order is the reverse of the target's. Body-only I could flip the pair (see (e)),
  but only by paying an `andi`.

## (c) The move that closed it

**One move: give the function its two real parameters.**

```c
void func_80157D20(void *param_1, s32 param_2)
```

…and delete the four now-pointless locals (`a0v`, `a1v`, `param_1 = a0v`, `param_2 = a1v`).
That is the *whole* diff. It requires one line **outside the body span** to be widened, in this TU:

```
src/ov_SC04_011/ov_SC04_011_jr_80154C24.c:365
-extern void func_80157D20(void);
+extern void func_80157D20(void *, s32);
```

### The canon is provably wrong, not just inconvenient

The TU header comment above the function (L1331-1355) argues the `(void)` canon is correct because
"the target sets up NO argument registers before `jal func_80156648`". That is a **pass-through**,
not an absence of arguments. Three independent pieces of evidence:

1. **The sole direct caller passes two arguments through.** `src/shared/ov/func_80149CB4.h`
   is `void func_80149CB4(void) { func_80157D20(); }` and compiles to
   `addiu sp,-24 ; sw ra ; jal func_80157D20 ; nop ; …` — **no argument setup and no `s`-register
   saves**, i.e. it forwards its own incoming `$a0`/`$a1`.
2. **`func_80149CB4`'s own callers already cast two arguments in**:
   `src/shared/ov/func_80157F64.h:9` `((void (*)(s32 *, s32))func_80149CB4)(a0, 5);`,
   `src/shared/ov/func_80155A44.h:17,24` `((void (*)(int, int))func_80149CB4)(param_1, 2|3);`.
   `src/ov_SC01_077/ov_SC01_077_jr_80154C24.c:1031` even records the fight:
   `// @stuck: callee-conflict (func_8014BEF8/func_80149CB4 declared void …) — cast at call site`.
3. **The ripple is byte-clean, one level up.** I recompiled `src/ov_SC04_011/ov_SC04_011_after.c`
   in scratch with `func_80149CB4` respelled as
   `void func_80149CB4(void *param_1, s32 param_2) { func_80157D20(param_1, param_2); }`
   and its two decls widened: **`func_80149CB4` is byte-identical, 8/8 ins**. The pass-through
   emits no moves because the parms are already coalesced onto `$a0`/`$a1`.

So the real shape of this chain is `(void *, s32)` at every level; the `(void)` canon is what forces
both the pins here *and* the casts at every call site.

### Fleet scope (measured, not estimated)

* 133 in-tree definitions of `func_80157D20` + 5 `#include`s of the two shared-body headers
  (`src/shared/ov/func_80157D20__99380536.h` ×3, `__d073e622.h` ×2) = the 138 the comment names.
* **131 of the 133** carry their own `extern void func_80157D20(void);`; the other 2 need no edit.
* **0 of the 133** also include `func_80149CB4.h`, so widening cannot self-conflict inside a
  defining TU.
* `func_80157D20` is declared in 2178 `src/` files but **called by name in exactly one place**
  (`src/shared/ov/func_80149CB4.h:5`); everything else is the carried decl layer or a comment.
  Non-defining TUs need no edit at all (C has no cross-TU type checking) — the minimal R22 edit is
  the 131 + 5 decls plus `func_80149CB4`'s.

## (d) GENERATOR PROPOSAL

> **R19 `param_promotion`** — when a NEEDED `$4`/`$5`/`$6`/`$7` pin exists *only* to seed a local that
> is then copied into a plain pseudo, and the residual class is COUNT with the missing instructions
> being exactly `move <callee-saved>,a<N>`, delete the pins and the copy locals, respell the
> definition with those pseudos as parameters in `$a` order, and widen the *defining TU's own*
> `extern <fn>(void);` line to the new signature — accepting the candidate only if the whole-object
> gate passes.

Mechanically checkable preconditions, all computable with no compile:
`sites.txt` has ≥1 NEEDED arg-register pin; the residual is COUNT with `mine == target - k` where the
k missing instructions are all `move <s-reg>,a<n>`; the pinned locals are each read exactly once, into
another local; the defining TU declares the function `(void)` and does not include a header that
re-declares it. The generator is *one* candidate per function, and the byte gate decides — the same
shape as the existing generators, except it edits one declaration line as well as the body.
This is a big family: the pin-to-pseudo idiom is the standard project workaround for a `(void)` canon
on a function that really takes arguments, and the sweep is `grep -l 'NEEDED   pin *\$[4-7]'` over the
residue.

**Caveat the generator must respect:** the widen ripples to any *caller that itself passes through*
(here `func_80149CB4`). The generator should therefore refuse (and hand to an agent) when the function
has a by-name caller that supplies fewer arguments than the new signature; when the only callers are
already cast (`((void (*)(…))fn)(…)`), the widen is inert.

## (e) What did NOT work, with byte evidence

| attempt | result |
|---|---|
| `void func_80157D20(void *, s32)` **without** widening L365 | `COMPILE-ERROR` — cc1: `tu.c:1363: number of arguments doesn't match prototype` / `tu.c:365: prototype declaration` |
| K&R definition `void func_80157D20(a0v, a1v) void *a0v; s32 a1v; {…}` | same error, same two lines — gcc 2.7.2 checks an old-style definition against a visible prototype |
| decl-order / init-order swaps of `a0v`,`a1v`,`param_1`,`param_2` (4 spellings) | score **9**, 19 ins — no effect at all; the missing insns are not an ordering artefact |
| inlining `a0v`/`a1v` into the call arguments (drop `param_1`/`param_2`, 3 spellings) | score **9**, 19 ins |
| narrowing `a1v` (or `param_2`) to `u16` / `u8` | score **4**, 20 ins — buys the *register pair* (`param_1`→`s1`, `param_2`→`s0`) but pays a spurious `andi s0,s0,0xffff`, and the two `move`s are still absent. This is the body-only ceiling; the mechanical search hit the same 4 five independent times (g2, g5, s1, s2, s4, s7 — 760 compiles) |
| any body-only text at all | **19 or 20 instructions, never 21** — no lever-free spelling of a `(void)` function references `$a0`/`$a1` as a source |

Not tried, deliberately: `__builtin_next_arg`/`__builtin_apply_args` and any `asm` — the brief bans them
(and a varargs spill would be `sw a0,32(sp)`, a different instruction anyway).

## (f) Where the method fell short

1. **The pack's frame hides the answer.** `sites.txt` says NEEDED, `history.txt` shows six runs
   converging on 4, and the residual is a COUNT class — all of which read as "unmatchable body".
   The answer was one line *outside* the body span. A pack for a body carrying an argument-register
   pin should include the function's file-scope declaration and its by-name callers; I had to grep
   for them. **Cheap fix:** add a `decl.txt` (the TU's own `extern` line + `grep -rn '<fn>' src/`
   minus decl lines) to every pack whose `sites.txt` has a `$4`-`$7` pin.
2. **`--try` cannot express the move.** The scorer splices only the body span, so the *one* candidate
   that reaches 0 is unreachable through the agent's own loop; I had to rebuild the recipe by hand
   (cpp | cc1 | maspsx | jtbl_rodata_pads | as) to prove it. **Cheap fix:** a `--try-decl OLD=NEW`
   flag on `delever_search --try` that also rewrites matching declaration lines in the scratch TU.
3. **`--try` truncates the compile error at 300 chars**, and the truncation cut off exactly the
   `number of arguments doesn't match prototype` line — the diagnostic that names the fix. It took a
   manual cc1 run to see it. **Cheap fix:** print the first non-warning diagnostic line, not the
   first 300 characters.
4. **The scratchpad directory is SHARED between the parallel agents.** A helper script I wrote to
   `…/scratchpad/t.sh` was overwritten twice by other agents mid-session (I scored four candidates
   against `func_8017B238` and then `func_801345F8` before noticing the printed TU name). Everything
   an agent writes must live in its PACK; the brief should say so explicitly, and the harness should
   give each agent its own scratch dir. The only thing that caught it was that `--try` echoes the TU
   and function it scored — keep that echo.
5. The TU's own header comment (L1331-1355) asserts the `(void)` canon is right and the pins are the
   fix. It is a well-argued, wrong, load-bearing comment, and it is the reason six mechanical runs
   never tried the parameter. It must be rewritten with the bank.
