# ov_SC04_011 / func_80141874 — score 0 (MATCH), lever-free

Pack: `.run/P36/agents/ov_SC04_011__func_80141874`
TU: `src/ov_SC04_011/ov_SC04_011_jr_80140608.c`   FN: `func_80141874`
Lever removed: the one NEEDED site — `register void (*fp)(void) __asm__("$2")` (pin $2, line 1353).
Final body: `PACK/body.c` — `--try` score **0**, and the whole `.text` section of the scratch object hashes
identical to the baseline object's (`sha1 79da8a30…`; the 60-byte whole-object delta is the scratch source
path, reproduced by the tree's own body as a negative control — the instrument, not the candidate).

## (a) The residual in one sentence

The store of the second call's result (`sh v0, D_8011511C`) was scheduled **after** the function-pointer load
instead of before it, which kept hard reg `$v0` live across that load, so the pointer was allocated `$v1`
(`lw v1` / `jalr v1`) and the two load-delay `nop`s landed on the other side of the block — 6 by edit distance,
same 33 instructions.

## (b) The pass and the decision, read from the compiler's own source

`sched.c` — **sched1, the pre-reload scheduler** (`schedule_block`, backward list scheduling).

* `tools/reference/gcc-2.7.2/sched.c:817` `true_dependence (mem, x)` — "X is read after store in MEM takes place".
  Its last clause is an alias *exception*:

  ```c
  && ! (MEM_IN_STRUCT_P (x) && rtx_addr_varies_p (x)
        && GET_MODE (x) != QImode
        && ! MEM_IN_STRUCT_P (mem) && ! rtx_addr_varies_p (mem))
  ```
  (`sched.c:837-839`, and the comment that states the rule at `sched.c:897-901`:
  *"A MEM_IN_STRUCT reference at a non-QImode varying address can never conflict with a non-MEM_IN_STRUCT
  reference at a fixed address."*)

  Here `x` = the fp load `(mem/s:SI (plus (reg 79) (symbol_ref "D_8019182C")))` — `MEM_IN_STRUCT_P` set (array
  ref), address varies, SImode. `mem` = the store `(mem:HI (symbol_ref "D_8011511C"))` — plain scalar global, so
  `MEM_IN_STRUCT_P` clear and the address is fixed. Every conjunct holds, so `true_dependence` returns 0 and the
  load is free to move above the store — **even though `memrefs_conflict_p` itself says they conflict**
  (`sched.c:711-721`: `x` is not a PLUS, `y` is `(plus reg symbol_ref)` whose second operand is not a
  `CONST_INT`, so it `return 1`). The exception is the whole of it.

* With no dependence, sched1's backward walk puts the store in the fp load's delay slot. From the `-dS` dump of
  the lever-free body:

  ```
  ;; ready list at T-7: 27 (1), now 27          <- the store, the only ready insn, goes right before the jalr
  ;; launching 40 before 27 with no stalls at T-8
  ;; register 2 life extended from 2 to 8
  ```
  (`sched.c:3681` prints `launching …`.) `$v0`'s life stretched from 2 insns to 8, spanning insn 40, so
  `local-alloc.c` could not give reg 72 (the fp pseudo) `$2` — hence `lw v1` / `jalr v1`.

* Everything downstream is a consequence, not a separate decision: with fp in `$v1` there is no WAR edge from
  the store to the load, sched2/maspsx fill the `lw`'s delay slot with the store and leave the `lhu`'s empty
  (`nop` at index 12); the target does the reverse.

## (c) The source move that closed it

One move, one line pair:

* declare the store's destination as an array and store through element 0 —
  `extern u16 D_8011511C;` → `extern u16 D_8011511C[];`, `D_8011511C = func_80015018(0);` → `D_8011511C[0] = func_80015018(0);`

That makes the store `(mem/s:HI (symbol_ref "D_8011511C"))` — `MEM_IN_STRUCT_P` now set on the *store* — so the
`! MEM_IN_STRUCT_P (mem)` conjunct of the exception fails, `true_dependence` falls through to
`memrefs_conflict_p` (which returns 1), and the store is pinned before the fp load. Proven on the `-dS` dump of
the matching body:

```
(insn 33 23 29 (set (reg:SI 76) (zero_extend (mem:HI (symbol_ref "D_80115112")))))
(insn 29 33 38 (set (mem/s:HI (symbol_ref "D_8011511C")) (reg:HI 2 v0)))     <- /s, and now before the load
(insn 38 29 42 (set (reg:SI 79) (ashift (reg 76) 2)))
(insn 42 38 44 (set (reg:SI 81) (mem/s:SI (plus (reg 79) (symbol_ref "D_8019182C")))))
;; launching 42 before 44 with 1 stalls at T-7      <- the nop the target has between lw and jalr
;; register 2 life extended from 2 to 6             <- was 8; no longer spans the load
```

The `lhu D_80115112` still hoists above the store (two distinct fixed symbols → `memrefs_conflict_p` returns 0
at `sched.c:775-781`), which is exactly the target's `lhu / sh / sll / lw` order.

Because the lever is gone the `fp` temp is no longer load-bearing, so the body is also spelled the way its
sibling `func_80141788` in the same TU spells the identical construct — `D_8019182C[D_80115112]();` — which is
the readability win: the delevered body is *shorter* than the levered one.

```c
void func_80141874(void) {

    extern u16 D_8011511C[];
    extern u16 D_80115116;
    extern void (*D_8019182C[])(void);
    func_801754A8();
    D_8011511E = func_80014ED4(0);
    D_8011511C[0] = func_80015018(0);
    D_8019182C[D_80115112]();
    func_80141C04();
    D_80115116 += 1;
}
```

Three other spellings also reach **score 0** (all byte-verified) — the coordinator can pick on taste:

| spelling | score |
|---|---|
| `extern u16 D_8011511C[];` + `D_8011511C[0] = …` + inline call (**shipped**) | 0 |
| same, keeping the `void (*fp)(void)` temp | 0 |
| `extern struct { u16 unk0; } D_8011511C;` + `D_8011511C.unk0 = …` | 0 |
| externs untouched; the *load* routed through a pointer: `void (**pp)(void); pp = D_8019182C + D_80115112; (*pp)();` | 0 |

The last one is the dual of the same clause — it clears `MEM_IN_STRUCT_P` on the **load** instead of setting it
on the store (an `INDIRECT_REF` of a non-aggregate type is not in-struct), and blocks the same sink.

## (d) GENERATOR PROPOSAL

**When the residual is COUNT/ORDER with the same instruction multiset and a store to a plain scalar global has
sunk past a later array/struct load whose destination register is bumped off the store's register (typically
`$v0`), retype that store's destination as a one-element array and store through `[0]` — `extern T X[];` +
`X[0] = …` — to set `MEM_IN_STRUCT_P` on the store MEM and restore sched.c's `true_dependence`; the dual
rewrite, for when the store must instead be free to sink, is to route the *load* through a pointer variable
(`T *p = A + i; … *p …`), which clears `MEM_IN_STRUCT_P` on the load.**

Mechanically detectable and cheap: the trigger is "a `sh/sw/sb SYMBOL` block that appears at a different index
in mine vs target, with an `lw/lhu` of a *different* symbol at a varying address on the other side of it, and a
register-field difference on that load's destination". The rewrite touches exactly one declaration and one
assignment, and there are only two candidate ends to try, so a generator can emit both and let the byte gate
choose. This is a **new** class: `sink_merges` (R15) merges two stores into one sink, `constant_holders` (R16)
hoists a constant into a named local, `constant_run_splits` (R17) splits a run of constant stores, and
`bystander_moves` (R18) relocates an unrelated statement across a barrier — none of them changes the *alias
flags* of a MEM, which is the only knob that moves this residual. Suggested name: **`mem_in_struct_flips`
(R19)**.

## (e) What did NOT work, with byte evidence

* every mechanical generator move in `history.txt` — `R6 inline fp`, `R7 block`/`do-while` at lines 1354-1360,
  7 runs, 1,413 compiles total — **all stayed at exactly 6**. None of them touches a MEM's alias flags, so none
  of them can move this residual. This is the "search reached 6 and then no single move improved it" the pack
  reports, and the reading explains it rather than contradicting it.
* `fp = *(D_8019182C + D_80115112);` → **6**. gcc folds pointer arithmetic on an array name straight back to an
  `ARRAY_REF`, so the MEM is still `mem/s` and the exception still fires. Only a *pointer variable* breaks it.
* `(&D_8011511C)[0] = func_80015018(0);` → **6**. The `ARRAY_REF` on a non-aggregate pointer folds away before
  `expand_expr` sets `MEM_IN_STRUCT_P`, so the store MEM stays flag-clear — an array subscript is not by itself
  enough; the *declared type* has to be the aggregate.
* not tried, deliberately: `volatile` on either object. It would work (the `MEM_VOLATILE_P (x) && MEM_VOLATILE_P (mem)`
  arm at `sched.c:830`) but the phase forbids adding one, and it is a heavier semantic claim than the array.

## (f) Where the method fell short

* **The residual print is misleading about the class.** It reads `COUNT (mine 33 ins, target 33)` because
  difflib scores an interleaved reorder as insert+delete; the true class is ORDER-plus-REG. The `--try` output
  alone would have sent me hunting an instruction-count move. What actually opened the problem was dumping mine
  and the target *side by side, all 33 lines, with the reloc operand printed* — the diff only showed 9 lines and
  hid that the store and the load had simply traded places. A `--try --full` (or a `--side-by-side`) flag that
  prints the whole function with reloc operands would have saved the first 20 minutes; I had to write it myself.
* **The dump script in the brief does not work on this TU as written.** `tools/cc1_dumps_tu.sh` runs cpp with
  `-Iinclude -Isrc`, but this TU's includes are relative (`#include "../shared/ov/…"`), so a copy compiled
  outside `src/ov_SC04_011/` preprocesses to 44 lines and every dump comes out empty — silently, exit 0. The
  fix is the `-I<the TU's own directory>` that `delever_search.score_file` already adds
  (`tools/delever_search.py:732`); `cc1_dumps_tu.sh` should add it too. Also `-dR` (sched2) is missing from its
  flag list.
* `residual_moves.md` has no row for this class. The 58 rows are register-preference, width, and scheduling-
  priority moves; none of them is "change the alias flags of a MEM". Row 59 is the generator proposal above.
* What *did* work, and is the transferable part of the method: read the `-dS` dump's `;; ready list at T-n` /
  `;; launching X before Y` / `;; register N life extended from A to B` lines **first**. The line
  `;; register 2 life extended from 2 to 8` names the defect (a hard reg's life stretched over the load) in one
  token, and from there the only question is which dependence edge is missing — which is a single predicate,
  `true_dependence`, with exactly two exception clauses. Time from that line to the byte-verified match: one
  compile.
