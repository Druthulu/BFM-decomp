# func_801287B8 (src/ov_SC04_011/ov_SC04_011.c) — score 0, byte-identical, lever-free

Levers removed: the one NEEDED site, `register volatile s32 *p __asm__("$4")` (line 222) — the `$4` pin AND the
`volatile` are both gone. No `asm`, no pin, no added `volatile`, no `__builtin_*`.

## (a) The residual in one sentence

`v0 -> a0 x4`, 62 ins vs 62, one 3-instruction block: mine materialised the address of `D_801F1640` into `$v0`
(`lui v0; addiu v0; lw v0,0(v0)`), the target into `$a0` (`lui a0; addiu a0; lw v0,0(a0)`) — i.e. the target's address
pseudo carries an **argument-register copy preference**, which only exists if that address is passed to a call.

## (b) The reading: it is a DECLARATION artefact, and the pass says so

The prompt asked which of the two it is. **It is the declaration** — but not in the way a2's case was, and it is
fixable body-only.

`ov_SC04_011.c:197` declares `extern void func_8013BC7C(void);`. The function's real, byte-verified definition is
`src/shared/ov/func_8013BC7C__8042ae05.h:3`:

```c
void func_8013BC7C(void *arg0) {
    extern void (*D_8017F230[])(void *);
    D_8017F230[((S_8013BC7C_8013BC7C *)arg0)->f68](arg0);
}
```

It takes a pointer and dispatches on it. The local extern had been truncated to `(void)`, so no C written against
*this TU's* declaration could produce the `$a0` instruction — exactly a2's shape. The difference from a2's case is
that the truncation is in a **local `extern` in this TU**, not a shared header, so a cast at the call site restores
the argument without touching any declaration: the bank stays body-only.

Two decisions, both in `tools/reference/gcc-2.7.2/local-alloc.c`, and both are needed:

1. **Why the address stays in a register instead of folding into the `lw`.**
   `update_equiv_regs` (`local-alloc.c:947`) attaches a `REG_EQUIV` note carrying the `SYMBOL_REF` to the address
   pseudo, and only substitutes it back into its use when the register **"is referenced exactly twice, meaning it is
   set once and used once"** (`local-alloc.c:1066`; the replacement itself is the `REG_DEAD` scan at
   `local-alloc.c:1085-1112`, `validate_replace_rtx` + `reg_n_refs[regno] = 0`). One use folds to `lui;lw %lo`
   (2 insns). **Two** uses — the load base and the call argument — defeat that test, the pseudo survives, and the
   MIPS mover emits `lui;addiu` + `lw 0(reg)` (3 insns). This is what the old `volatile` was faking.

2. **Why the surviving pseudo lands in `$a0` and the `move` disappears.**
   The `move $4, pseudo` that sets up the call makes `combine_regs` (`local-alloc.c:1722`) take the
   "UREG is a hard reg and SREG is a pseudo" path at `local-alloc.c:1797-1818`: it does *not* tie them, it records
   `$4` in `qty_phys_copy_sugg[]` and returns 0 so the two lifetimes stay disjoint. `find_free_reg`
   (`local-alloc.c:2073`) then runs its `just_try_suggested` pass and restricts the candidate set to exactly those
   copy suggestions — `local-alloc.c:2145-2150`, `if (qty_phys_num_copy_sugg[qty] != 0) IOR_COMPL_HARD_REG_SET
   (first_used, qty_phys_copy_sugg[qty]);` — so the quantity is coloured `$4`, the copy is coalesced away, and the
   `lui/addiu` write `a0` directly. This is what the old `__asm__("$4")` pin was faking.

Both claims are **proved on bytes** by the controls in (e).

## (c) The move

- One move: give the block a plain `s32 *p = &D_801F1640;`, test `*p`, and pass `p` to `func_8013BC7C` through a
  function-pointer cast — `((void (*)(void *))func_8013BC7C)(p);` — the same idiom this TU already uses three lines
  up for `func_8014FDF4` / `func_801505FC`. The second reference to `p` supplies both the two-use count of (b1) and
  the `$4` copy suggestion of (b2); the pin and the `volatile` become redundant and are deleted.

`PACK/body.c` — score 0, first spelling tried.

## (d) GENERATOR PROPOSAL (new — not R15/R16/R17/R18)

**R19 "argument restore":** when the residual is REG-only and the mapping `mine -> target` sends one pseudo to an
argument register `$4..$7`, look for a call in that block whose local `extern` prototype takes fewer parameters than
the callee's real definition (the shared body under `src/shared/ov/<fn>__*.h`, or its declaration in any other TU —
`tools/match_protos.py` / `tools/fix_arity_callers.py` already own that oracle), and offer the candidate that routes
the nearby value into that call through a function-pointer cast `((R (*)(T))f)(v)`, hoisting the value into a local
if it is currently spelled inline.

Generalised in one sentence: *when the diff is "a pseudo wants an argument register", the missing argument is real —
recover the callee's true arity from the other TUs and pass the value.*

Two things make this cheap and safe to run fleet-wide: the arity mismatch is a **static, zero-compile filter** (a
call spelled with fewer args than the callee's real definition is a defect regardless of bytes), and the fix is
**body-only** whenever the truncated prototype is a local `extern` in the same TU. A scan of every function still
holding a NEEDED `$4`/`$5`/`$6`/`$7` pin against the arity oracle should be run before any further search on them —
this residual class is not an allocator puzzle at all.

## (e) What did NOT work, with byte evidence

- **Read the global directly and pass `&D_801F1640`** (`if (D_801F1640 == 0) ((void (*)(void *))func_8013BC7C)
  (&D_801F1640);`): **score 9 (COUNT), 63 ins vs 62**. The address then has one use each side of the branch, so
  `update_equiv_regs` folds the load to `lui v0; lw 0(v0)` and the argument is materialised separately — one insn
  too many. This is the control that proves decision (b1): the shared *local* is what creates the two references.
- **The pointer declared at the top of the function** instead of in the inner block: **score 4 (MIXED), `s0 -> a0
  x4`**, with an extra `move a0,s0` where the target has a `nop`. Live across fifteen calls, the pseudo becomes a
  *global* allocno and takes a callee-saved `$s0`, so `find_free_reg`'s copy-suggestion pass never sees it. This is
  the control that proves decision (b2): the `$4` colour comes from a *block-local* quantity carrying the copy
  suggestion.
- The mechanical search's 4,000+ compiles across seven runs (`history.txt`, best 3 every time) could not reach this:
  every generator it has rewrites statements that are already there, and this move had to **add an argument that the
  TU's own declaration says does not exist**. No amount of R6/R7/R9/R12 reshuffling can produce it.

## (f) Where the method fell short

Step 1 of the brief sends you to the compiler sources first. Here the compiler was innocent: the fastest possible
first move was `grep -rn func_8013BC7C --include=*.h src/ include/`, which shows the real signature in one line.
**The method should put a callee-arity check before the pass reading whenever the residual's differing register is an
argument register** — `$4..$7` in the `register pairs` line is a strong prior for "a call is missing an argument",
and it costs one grep. The pass reading was still worth doing afterwards, because it is what turned the fix into
R19's applicability test (block-local, two references) rather than a lucky spelling.

Also worth recording for the coordinator: the more readable end state is to repair `ov_SC04_011.c:197` to
`extern void func_8013BC7C(void *a0);` and drop the cast. That is a declaration change, outside the body-only bank,
and it is **not** byte-proven here (`--try` substitutes only the body), though it compiles to the same RTL.
