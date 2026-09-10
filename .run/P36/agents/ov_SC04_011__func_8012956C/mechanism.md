# func_8012956C (ov_SC04_011) — T7 residue exemplar

Levers in the tree: `register` pins `$7` (temp_a3), `$4` (arg0), `$3` (s2) and one `__asm__("")`
barrier at the head of the `do_default:` block. Starting text `body_free.c` scores **11**.
Best lever-free text found: **score 4** (`PACK/body.c`).

## (a) The residual in one sentence

Everything in the function matches except the `do_default:` block, where (i) the four `lhu`
field loads come out in a different order — `base->f38` is emitted before `base->f40` instead of
after it — and (ii) the `j` that enters the block copies the block's first instruction
(`sll a1,a1,0x10`) into its own delay slot and jumps one instruction further in, where the target
leaves a `nop` and jumps to the label.

Score-4 diff (the whole of it):

```
  replace mine[33:35] target[33:35]
       33  j  <do_default+4>   | j  <do_default>
       34  sll a1,a1,0x10      | nop
  ... mine  lhu a3,4(s0) ; lhu v0,12(s0)
      target lhu v0,12(s0) ; lhu a3,4(s0)
```

## (b) The passes and the decisions, read from `tools/reference/gcc-2.7.2/`

### The pins are a *scheduling* lever, not a register lever (proved)

`register u32 arg0 __asm__("$4")` does not primarily choose a register — the allocator already
picks `$4`/`$7`/`$3` without it. What it changes is the **insn count entering `sched1`**. With the
pin the variable *is* the hard register, so `combine` folds the load straight into the argument
register: `.i.sched` for the tree has one insn

```
(insn 377 (set (reg/v:SI 4 a0) (zero_extend:SI (mem:QI (symbol_ref "D_801F1620")))))
(insn 387 (set (reg/v:SI 7 a3) (zero_extend:SI (mem/s:HI (plus (reg 233) (const_int 4))))))
```

while the lever-free text has *two* insns for each: the load into a pseudo plus a
`(set (reg:SI 4 a0) (reg/v:SI 79))` copy emitted at the call. `local-alloc` coalesces the copy
away again, so the final instruction **count** is equal — but `sched1` saw a different dependency
graph and ordered the block differently. This is the whole of the 11.

* `gcc-2.7.2/combine.c:can_combine_p` / `try_combine` — the fold puts the merged insn at **i3**'s
  position (the later insn), which is why inlining `D_801F1620` into the call argument folds the
  load but drops it to the *end* of the block's LUID order.
* `gcc-2.7.2/sched.c:rank_for_schedule` (the whole function, ~line 2385): priority first, then the
  data/anti/independent class against `last_scheduled_insn`, then `INSN_LUID (tmp) - INSN_LUID (tmp2)`.
  The block is scheduled **backwards** (`sched.c:1208` "The scheduler is operating in reverse"), so
  the *first* insn picked is emitted *last*; among priority ties the larger LUID is picked first and
  therefore emitted last, i.e. **ties come out in source order**. Both remaining `lhu`s are a
  priority tie (`2 + P(add)` either way); the tie is broken against `last_scheduled_insn`, and the
  extra `a3 = pseudo` copy that the lever-free text still has is what flips it.

### `do { X } while (0);` is a hard scheduling barrier (proved on bytes)

`sched.c` collects `NOTE_INSN_LOOP_BEG` / `NOTE_INSN_LOOP_END` into `loop_notes` and
`sched_analyze_insn` makes the insn that carries them depend on *everything* before it and
everything after depend on *it* — a two-sided barrier pinned at that source position. A plain
`{ X }` emits only `NOTE_INSN_BLOCK_BEG/END`, which are **not** in that set and change nothing.
Measured here: `{ arg0 = D_801F1620; }` → 11 (no change), `do { arg0 = D_801F1620; } while (0);`
plus one statement swap → **6** (this is the path the mechanical search `g5` found).
That spelling is a dead end for a full match: the barrier can only pin the load *first* in the
block, and the target wants it fourth, after `sll/sra/move a2` (which are generated at the call,
i.e. last in RTL, and float to the head because they have the lowest priority).

### The delay slot: `reorg.c:fill_slots_from_thread`

`fill_eager_delay_slots` → `fill_slots_from_thread (j, const_true_rtx, next_active_insn(label), …)`
copies the first insn of the jump's target into the delay slot and redirects the jump past it
(`reorg.c:3430` `temp = own_thread ? trial : copy_rtx (trial);`, then the redirect at
`reorg.c:3592-3615`). The gate is `eligible_for_delay`, i.e. mips.md's

```
(define_delay (eq_attr "type" "jump") [(and (eq_attr "dslot" "no") (eq_attr "length" "1")) …])
(define_attr "dslot" "no,yes"
  (if_then_else (eq_attr "type" "branch,jump,call,load,xfer,hilo,fcmp") "yes" "no"))
```

so a **load** at the head of the block (`dslot = yes`) or a two-instruction insn (`length = 2`,
e.g. `la`/`lbu sym` — that is the 9014 `j+nop` sites whose target starts with `lui`) cannot be
stolen, and `stop_search_p` (`reorg.c`) stops outright on an `ASM_INPUT` — which is exactly what
the tree's `__asm__("")` does. Verified three ways on bytes:

* tree (asm at the head) → `j <label>` + `nop`;
* the `do-while` candidate (head = `lbu $4,D_801F1620`, a load) → `j <label>` + `nop`;
* a probe with `s32 a1` (head = `move $6,$18`) → `j <label+4>` + `move $6,$18` — stolen.

A whole-build scan (`build/src/**/*.o`, 4284 objects) finds 32092 target-steal sites, and of the
`j`+`nop` sites the target's first mnemonic is overwhelmingly `lui` (9014, the length-2 `la`),
`move` (2932, almost all epilogue `move sp,s8`), or a load — consistent with the rule above.
**This is the part I could not close.** The target's block starts with `sll a1,a1,0x10`
(`ashlsi3`, `dslot=no`, `length=1` — mips.md's `extendhisi2` is an *expander* that always emits two
separate `ashlsi3`/`ashrsi3` insns for a register operand, so the `sll` stands alone and the rule
above says it must be stealable) — yet the original leaves a `nop`. I probed the two lever-free
counter-examples in the tree, `func_801800C0` (`ov_SC03_100_jr_8017D898.c:3583`, `j`+`nop` onto
`sra a0,v0,0x10`) and `func_80166994` (`ov_SC03_099_jr_8015C32C.c:4997`, `j`+`nop` onto
`sra v0,v0,0x10`): in **both**, the steal *did* happen — the jump is redirected PAST the block's
first insn — and the copy was then deleted again by `relax_delay_slots`
(`reorg.c`, "See if the first insn in the delay slot is redundant with some previous insn. Remove
it from the delay slot if so"), because the same insn already executes in the delay slot of the
conditional branch that falls into the jump. That leaves `j <label+4>` + `nop`. Our target is
`j <label>` + `nop`, i.e. **no redirect at all**, so `fill_slots_from_thread` declined at the very
first trial and I could not determine which of its guards fired. The only lever-free way I found to
get the `nop` is to make the block start with a load, which contradicts the target's own first
instruction.

## (c) The source move(s)

From `body_free.c` to `PACK/body.c` (11 → 4), two moves, both readability-positive:

1. **Sink the accumulate into its initializer**: `s = base->f40; temp_a3 = base->f38; s += temp_a3;`
   → `temp_a3 = base->f38; s = base->f40 + temp_a3;` (11 → 11 alone).
2. **Merge the second pair into one expression, dropping the temp**:
   `s2 = base->f42; t6 = base->f3A; s2 += t6;` → `s2 = base->f42 + base->f3A;` and delete the now
   unused `u32 t6;` declaration. Together with (1): **11 → 4**.

Both moves delete a `+=` accumulation whose left-hand side had just been initialised, i.e. they
turn `x = A; x += B;` into `x = A + B;`. That single rewrite is what removes the two intermediate
pseudos whose copies were confusing `sched1`.

## (d) GENERATOR PROPOSAL

> **R19 `accum_folds`** — when the residual is a pure ORDER/COUNT residual confined to a run of
> loads and adds (mine and target hold the same instruction multiset but a straight-line block
> comes out permuted), rewrite every `x = A;` … `x += B;` pair in the body — where `x` is a local
> whose only intervening use is none — as the single statement `x = A + B;` (and drop the now-dead
> temp's declaration), trying each pair alone and then all pairs together.

It is the exact inverse of the existing `R17 constant_run_splits` / `R15 sink_merges` family
(`tools/delever.py:2141` `sink_merges`, `:2237` `constant_holders`, `:2286` `constant_run_splits`,
`:2344` `bystander_moves`) — those *split* statements or *move* bystanders; none of them **fuses a
two-statement accumulation into one initializer**, which is why the 2241-compile `g5` search and
my own 2800-candidate exhaustive statement-permutation sweep both stalled at 11/6: the winning
move is not in the generator set at all. A cheap second rung of the same rule is the reverse
direction (`x = A + B;` → `x = A; x += B;`) for bodies where the tree already has the fused form.

## (e) What did NOT work (byte evidence)

| tried | result |
|---|---|
| all 2800 legal permutations of the 9 `do_default` statements × 10 positions for `arg0` (incl. inlined into the call) | **every one 11** — statement order alone cannot leave the plateau |
| declaration order: all 120 permutations of the five locals | 11 |
| declaration width: `s`/`s2`/`t6`/`temp_a3`/`arg0` as `s32/u32/s16/u16/u8/int/short/unsigned char` | 11 |
| `{ … }` plain block around any single statement | 11 (block notes are not `loop_notes`) |
| `do { … } while (0);` around the whole `do_default` body, or around each statement individually | 11–25, except `arg0` + one swap → 6 |
| inlining `D_801F1620` into the call (folds the load into `a0` — confirmed in `.i.sched`) | 11: the folded insn lands at the call's LUID, so it is emitted *after* the four `lhu`s instead of before them |
| `base->f1C = base->f40 + base->f38;` with `base->f38` passed to the call (no `temp_a3` at all) | ≥11 — CSE re-creates the single pseudo with two uses |
| every S-form × T-form × `arg0` position (1201 candidates) | the score-4 plateau: *every* variant that reaches 4 has the identical residual, so the last `lhu` swap is not reachable by statement spelling |
| `s32 a1` (kills the `sll/sra`) | probe only — confirms a `move` at the block head *is* stolen |

## (f) Where the method fell short

* **The residual class was mislabelled.** `residual.txt` says `COUNT` with `mine 226 ins,
  target 226` — the counts are equal; the class picked the temp-move generators (`R4`, `R6`,
  `R18`) and never the expression-fusion family that actually mattered. A class that compared the
  instruction *multisets* first would have said ORDER and pointed at scheduling.
* **`sites.txt` is not a map of the mechanism.** Three sites are marked NEEDED (`$7`, `$4`, `$3`)
  and one REMOVED (`$2`), which reads as "three registers must be forced". In fact the two argument
  pins ($4, $7) matter only because they let `combine` fold a copy, and `$3` (`s2`) fell out for
  free once the `s2 = A + B` fusion removed its copy. The a2-agent finding quoted in the brief
  generalises: **a pin's byte effect can be a scheduling effect, and it disappears when the
  statement that created the extra copy is rewritten** — here, deleting `t6` deleted the need for
  the `$3` pin.
* **`residual_moves.md` has no row for "the same instructions in a different order inside one basic
  block, caused by an extra register copy that `local-alloc` will coalesce away".** That is the
  row this exemplar should add, with the `.i.sched` insn-count comparison as its test.
* The `--try` loop is excellent (0.15 s/compile in-process; I ran ~4500 candidates in a few
  minutes with a private-scratch parallel wrapper). What is missing is a `--try` mode that prints
  the *pre-sched RTL* insn count for the function, which is the quantity that actually predicts
  whether a pin is removable.
