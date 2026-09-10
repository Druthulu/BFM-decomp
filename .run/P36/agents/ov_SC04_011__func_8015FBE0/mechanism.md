# ov_SC04_011 `func_8015FBE0` — the barrier was standing in for **argument liveness on the fall-through arm**

FINAL: **score 0 — MATCH** (58 ins vs 58), lever-free, no pin, no `asm`, no `volatile`, no `__builtin_*`.
`PACK/body.c` holds the matching text. One-token move.

---

## (a) The residual in one sentence

The lever-free text puts the else-arm's first instruction — `move a0,s0` — into the **delay slot of the
`bgez`** and deletes it from the else block (`mine 57 ins`, target 58: `[7] move a0,s0 | nop`, `[22] j +0xd0 |
j +0xd4`, target's extra `[24] move a0,s0`); the target leaves that slot a `nop` and keeps the `move` as the
branch target.

## (b) The pass and the decision, read from the pinned cc1 source

Pass: **reorg** (`dbr_schedule` → `fill_eager_delay_slots` → `fill_slots_from_thread`), after
`sched2`/`jump2`. Byte-proven with `-dR -dJ -dd` dumps of the real TU.

* The branch is `bgez v0` — `GE` against `const0` ⇒ `mostly_true_jump` returns 1
  (`reorg.c:1412-1416`), so reorg tries the **taken thread first** (`fill_eager_delay_slots`,
  `reorg.c:3690-3694`).
* `own_thread_p (reorg.c:2151)` is 1 (a BARRIER precedes the label, `LABEL_NUSES == 1`), so a stolen insn is
  *moved*, not copied — hence the missing instruction, not a duplicated one.
* The steal is admitted by exactly one test — **`reorg.c:3374-3376`**:
  `condition == const_true_rtx || (! insn_sets_resource_p (trial, &opposite_needed, 1) && ! may_trap_p (pat))`.
  `trial` is `move a0,s0`; it does not trap and does not touch memory, so the *only* thing that can refuse it
  is **`a0` being live in `opposite_needed`** — the register set of the fall-through (`if`) arm.
  (`-mips1` has no usable annul slot: `mips.md:125-128` gates annul-if-false on `branch_likely == yes`.)
* `opposite_needed` comes from `mark_target_live_regs (reorg.c:2441)`. `a0` *is* live at block 0's start
  (incoming parameter) and the `move s0,a0` only makes it *pending* dead — pending dead regs are applied at a
  CODE_LABEL only, and there is none. It is killed later, in the forward scan **`reorg.c:2741-2746`**:

  ```c
  mark_referenced_resources (insn, &needed, 1);   /* :2741  — FIRST  */
  mark_set_resources       (insn, &set, 0, 1);    /* :2742          */
  scratch = set & ~needed;  res->regs &= ~scratch;/* :2743-2746     */
  ```
  At the fall-through arm's indirect `jalr`, `mark_set_resources` marks every call-clobbered register
  (`a0` included) as *set*; `needed` does not contain `a0`, so `a0` falls in `set & ~needed` and dies. That
  is the whole reason the steal is legal.
* **The lever short-circuits all of this earlier**: `__asm__ __volatile__("")` is an `ASM_INPUT`, and
  `stop_search_p` refuses it at **`reorg.c:697-700`** (`GET_CODE (PATTERN (insn)) == ASM_INPUT ||
  asm_noperands (...) >= 0`), so the thread scan ends on insn 0 and the slot stays empty. The barrier is a
  *search stopper*; it says nothing about the program. The fact it was standing in for is the liveness of
  `a0`.

## (c) The source move that closed it

**One move — give the dispatch-table call its object-pointer argument** (`param_1`), the way every other
call to the same table in this TU is written (`src/ov_SC04_011/ov_SC04_011_jr_8015C32C.c:1253/1262/1303/2781`
— `extern void (*D_80192AC8[])(void *); … D_80192AC8[*(u16 *)arg0](arg0);`):

```c
-        ((void (**)())D_80192AC8)[*(u16 *)param_1]();
+        ((void (**)(s32 *))D_80192AC8)[*(u16 *)param_1](param_1);
```

Why it costs zero instructions and buys the liveness:

1. The argument emits `(set (reg a0) (reg s0))` in front of the `jalr` **and** `(use (reg a0))` in the call's
   `CALL_INSN_FUNCTION_USAGE`.
2. **jump2 deletes the copy**: `jump_optimize(..., noop_moves=1)` — "no-op move instructions resulting from
   smart or fortuitous register allocation", **`jump.c:424-443`**, `find_equiv_reg` — because `a0` still holds
   `param_1` at that point (nothing clobbers it after the prologue's `move s0,a0`). Verified on the dumps:
   insn 29 `(set (reg:SI 4 a0) (reg:SI 16 s0))` is present in `.sched2` and **gone in `.jump2`**.
3. The `(use (reg a0))` survives on the `CALL_INSN`. `mark_referenced_resources`' `CALL_INSN` case walks
   `CALL_INSN_FUNCTION_USAGE` (**`reorg.c:428`**), so at `reorg.c:2741` `a0` enters `needed` **before**
   `:2742` puts it in `set` — `set & ~needed` no longer contains it, `a0` stays live.
4. `reorg.c:3375` therefore rejects `move a0,s0`; the next trial, `sb zero,D_80078EC1`, writes memory and
   `opposite_needed.memory` is unconditionally 1 (`reorg.c:2463`) so `resource_conflicts_p (reorg.c:714-716)`
   refuses it too; the following `jal` is already a `SEQUENCE` from `fill_simple_delay_slots` and
   `stop_search_p` ends the scan. Slot unfilled ⇒ gas emits the `nop`, the `move` stays at `$L309`. 58 ins,
   byte-identical.

Verified in the `.dbr` dump: `jump_insn 13` carries **no** `SEQUENCE` in the matching build, versus
`(insn 143 … (sequence [ (jump_insn 13 …) (insn/s 52 … (set (reg a0) (reg s0))) ]))` in the lever-free build.

This is a readability *win*, not a trick: the decompiled call had lost its argument, and the argument is what
the rest of the file already says the function takes.

## (d) GENERATOR PROPOSAL

> **R19 — "restore the dropped call argument" (delay-slot liveness).** When the residual is `COUNT` with the
> signature *"mine has insn `move aN,rX` in a conditional branch's delay slot where the target has `nop`, and
> the target has that same `move aN,rX` as the first instruction at the branch target"*, do not touch the
> taken arm: find the first call in the **fall-through** arm that is spelled with an empty argument list
> (`f()` / `((void (**)())tbl)[i]()` — an m2c artefact) and give it the argument that its sibling call sites
> to the same callee or table in the TU pass; if that argument register already holds the value, `jump.c:424`
> deletes the copy and the only surviving effect is the `(use)` that keeps `aN` live in `opposite_needed`.

Mechanically checkable and cheap: the candidate set is "zero-argument call sites in the arm the branch falls
into"; the sibling spelling is a grep for the same callee/table symbol in the same TU; the byte gate decides.
125 copies of this function share the class, so one crack remaps to all of them.

## (e) What did NOT work, with byte evidence

| tried | score | why it cannot work |
|---|---|---|
| `body_free.c` as given (control) | 3 | baseline |
| early-`return` spelling (`if (…<0) { … return; } …`) | 3 | identical RTL layout; reorg's decision is unchanged |
| the mechanical trace's `R7 block`/`R7 do-while` @2807-2813, `R8 temp tmp0` @2807 (`history.txt`, 3,373 compiles over 7 runs) | 3 | none of them changes `opposite_needed`; the else-arm head insn stays a slot-eligible `move` |
| cast-only change `((void (**)(s32 *))…)[…]()` — argument NOT passed | COMPILE-ERROR | proves it is the **argument**, not the prototype/cast, that carries the `(use)` |
| `((void (**)(void *))…)(param_1)` (the TU's own `void *` spelling) | **0 — MATCH** | equivalent; kept the `s32 *` form as the smaller textual diff |

Reasoning that was *ruled out on the source* before testing (each would also have to survive the byte gate,
none was needed): making the else-arm head insn ineligible (a memory write / a macro of `length 2`) —
`lose = 1` does not end the scan while `own_thread` is 1, so the `move` two insns later is stolen instead
(`reorg.c:3271`); putting a CODE_LABEL at the head — `own_thread = 0` makes the steal a **copy** and
redirects the branch to `label+4`, which contradicts the target's `bgez → 0x3914`.

## (f) Where the method fell short

* `residual_moves.md` row 11 ("Change the join block's FIRST statement", reorg, `eligible_for_delay` +
  `mark_target_live_regs :2441`) is the nearest row and it points at **eligibility**. This case is the other
  half of the same test — **liveness in the opposite thread** — and there is no row for it, so the row's
  "try" list (make the first statement a store/macro) would have failed here. Row 11 should gain a sibling:
  *"a `nop` in the target's slot where you fill one can also be liveness: the register your candidate insn
  writes is still live down the other arm."*
* Neither `residual_moves.md` nor the cookbook's eager-steal entry (§ around cookbook line 216-228, which
  correctly names `reorg.c:675 stop_search_p` as what the asm barrier exploits) says **what a barrier at a
  join is standing in for**. A barrier stops the scan at insn 0; the plain-C equivalents are exactly the four
  refusals at `reorg.c:3374-3376` + `:714-716` (live register / memory write / volatile / trap). Writing that
  short list next to the barrier entry would have taken this function from ~40 minutes of source reading to a
  single grep.
* The engine's own move menu has no "argument" family at all. Every generator (R7/R8/R10/R12/R14/R15-R18)
  rewrites *statements and declarations*; the closing move here was a change to a **call's argument list**,
  which is invisible to all of them — that is why 3,373 mechanical compiles across 7 runs never moved off 3.
  m2c drops arguments at indirect/unprototyped call sites routinely, so this family is likely large.
* What worked, and would generalise as a procedure: read the residual as *"an instruction crossed a branch"*,
  find the single predicate in the compiler that admits that crossing, and then ask **what fact about the
  program makes that predicate false** — rather than searching for a source shape. One reading, one compile.
