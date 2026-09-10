# func_8016B234 (ov_SC04_011) — T7 residue exemplar, CLOSED

**Final score: 0 — MATCH** (`mine 112 ins, target 112`), from a lever-free start of 13 and a mechanical best of 3.
Body: `PACK/body.c`. No `register` pin, no `__asm__`, no `volatile` added, no `__builtin_*`.

Two `NEEDED` pins are gone: `sy` pinned to `$16` (line 2040) and `sxy` pinned to `$3` (line 2042).

---

## (a) The residual in one sentence

The lever-free body puts the projected screen-Y in a **caller-saved** register (`v1`) where the original keeps it in a
**callee-saved** one (`s0`), which pushes both `sxy` loads onto `a0` and forces the `lhu …,90(sp)` down past the
`prim.bx/dx` stores, so mine spends a `nop` in the `lw`'s load-delay slot that the target fills
(`score 13 COUNT; a0->v1 x3, v1->s0 x1, a0->s0 x1`).

## (b) The passes and the decisions (`file:line`, read in `tools/reference/gcc-2.7.2/`)

**Decision 1 — a callee-saved register is only reachable by crossing a call.**
`global.c:922-927`, `find_reg`:

```c
  if (accept_call_clobbered)      COPY_HARD_REG_SET (used1, call_fixed_reg_set);
  else if (allocno_calls_crossed[allocno] == 0)
                                  COPY_HARD_REG_SET (used1, fixed_reg_set);
  else                            COPY_HARD_REG_SET (used1, call_used_reg_set);
```

For an allocno that crosses a call, *every* caller-saved register is excluded up-front, so the first-fit scan at
`global.c:962-985` (MIPS declares no `REG_ALLOC_ORDER`, so it is ascending regno) lands on the lowest free
callee-saved register — `s0`. An allocno that crosses **no** call never gets there: `regs_used_so_far`
(`global.c:350-355` = `regs_ever_live | call_used_regs`) already contains `v0,v1,a0..a3,t0..t9`, so pass 0 hands it
`a0`. **Proved by refutation:** hoisting `sy = (u16)out.xy[1];` above the `if` makes it a genuine cross-block global
allocno — and it comes out in `a0`, score 9, not `s0`. Being global is not enough; crossing a call is the whole rule.

Whether a pseudo is even offered to `global.c` is `local-alloc.c:472`:
`if (reg_basic_block[i] >= 0 && reg_n_deaths[i] == 1 …) reg_qty[i] = -2; else reg_qty[i] = -1;`
— one block **and** one death, or it goes to global. Block-local singles are coloured by `find_free_reg`
(`local-alloc.c:2157-2172`), ascending regno, which is why the lever-free `sy` gets `v1`.

**Decision 2 — the destination of the final `addu` inherits a dying operand's register only through `combine_regs`.**
`block_alloc` tries to tie operand 0 to an operand that dies in the insn (`local-alloc.c:1199-1290`), calling
`combine_regs` (`local-alloc.c:1722`). Its first guard, `local-alloc.c:1763-1766`:

```c
  /* If UREG is a pseudo-register that hasn't already been assigned a
     quantity number, it means that it is not local to this block or dies
     more than once.  In either event, we can't do anything with it.  */
  if ((ureg >= FIRST_PSEUDO_REGISTER && reg_qty[ureg] < 0) …) return 0;
```

`sxy` is assigned twice in the body (`*(s32 *)out.xy`, then `*(u16 *)(param_1 + 0x26)`), so `reg_n_deaths == 2`,
`reg_qty < 0` at `local-alloc.c:472`, the tie is refused, the add's destination gets a fresh quantity and
`find_free_reg` gives it the lowest free register, `v0`. The target reuses `v1`.

## (c) The source moves that closed it

1. **Merge `sy` into `uVar1`** — one scratch variable holds the projected screen-Y and then the UV column index, so its
   pseudo is live from the projection into the `do…while` and **crosses `func_80016ED4`**. `s32 sy;` is deleted; the three
   `sy` references become `uVar1`. Score 13 → **3** (`REG-mixed`, count now 112 = 112: the `nop` and the store exchange
   both vanish with the register).
2. **Split `sxy` in two** — `s32 sh2;` (renamed `hh` in the shipped body) takes the second assignment
   `*(u16 *)(param_1 + 0x26)`, so each variable is assigned once, is block-local and dies once. `combine_regs` now ties the
   `addu`'s destination to the dying `hh` and the result lands in `v1`. Score 3 → **0**.
3. Cosmetic, byte-neutral: `sxy = uVar1 + hh; prim.cy = prim.dy = sxy;` collapses to
   `prim.cy = prim.dy = uVar1 + hh;` (the `sxy` variable no longer carries the sum).

Dump evidence for both moves (`cc1 -dl -dg` on the spliced real TU):

| | lever-free | shipped body |
|---|---|---|
| the `sxy` pseudo | `used 6 times across 13 insns in block 1; **dies in 2 places**` → global, `in 4` (`a0`) | `used 2 times across 8 insns in block 1` → local, `in 3` (`v1`), and the sum's pseudo tied to it, also `in 3` |
| the `sy`/`uVar1` pseudo | two pseudos: `81` local `in 3` (`v1`) and `74` `crosses 1 call` `in 16` | one pseudo `74`, `used 10 times across 50 insns; dies in 2 places; **crosses 1 call**` → `in 16` (`s0`) |
| `;; N regs to allocate` | `4: 83 74 72 75` | `3: 74 72 75` |

## (d) GENERATOR PROPOSAL

**R19 `death_splits` (primary, purely mechanical):** when the residual is `REG` and the only differing instruction is the
*destination* of a commutative binary op whose two source registers already match the target, split every local that the
body assigns more than once into one variable per assignment (each then satisfies `reg_n_deaths == 1` at
`local-alloc.c:472`, so `combine_regs` at `:1765` can tie the op's destination to its dying operand) and re-score.
Applicability is a textual census — a local with N simple whole-variable assignments and no use that reads a value written
before the split point — and the bytes stay the proof.

*Companion, R20 `call_crossing_merges`:* when a residual's register pairs map a caller-saved register of mine onto a
callee-saved register of the target for a value whose live range ends **before** a call, merge that local with another
local of compatible type whose live range begins after it and **crosses a call** (delete the declaration, rename the
references) — `global.c:922-927` then excludes every caller-saved register and first-fit yields `s0`. The enumeration is
cheap: all ordered pairs of locals with disjoint live ranges where the later one is written before a call and read after
it. This is the one that supplies the *reason* a decompiled body has a spurious extra local at all — the original reused a
scratch variable, and the decompiler split it.

Neither is R15 `sink_merges` (a statement sunk into arms), R16 `constant_holders` (a literal-only local deleted),
R17 `constant_run_splits` (a *statement* run split), nor R18 `bystander_moves` (an independent statement relocated);
both operate on the **variable→pseudo mapping** (how many pseudos, and over what span) rather than on statement position.

## (e) What did NOT work — byte evidence

All scored with `delever_search.py --try … --body`; lever-free start = 13.

* **Statement order of the `sy` load** — moved above `sxy`, between `sxy` and `prim.a04`, and after it: **13, 13, 13**
  (no change at all). `sched1`/`sched2` re-derive the order from the dependence graph, so R9/R18-shaped moves cannot
  touch this residual. This is the measurement that ruled scheduling out as a *cause*.
* **Declaration width of `sy`** — `s16 short u32 int long` → **13**; `u16 u8` → **14**. Width of `sxy` — `u32 int` → 13,
  `u16` → 15, `s16`/`short` → **7** (this one produces the target's *order*, `lhu a0,90(sp)` in the delay slot, but pays
  two `sll/sra` sign-extend insns and still puts the value in `a0`). Instructive, not usable.
* **Declaration order** — `sy`/`sxy` merged into the `s32 X, Y0, …` list at the front/back, split apart, moved to the top
  of the block, exchanged: **13** in all eight spellings.
* **Inlining** — `sy` inlined at both uses → 13; the first `sxy` load inlined into `X` → 14.
* **Hoisting the `sy` load above the `if`** (the "make it a global allocno" hypothesis) → **9**, and the dump shows it
  *is* global — allocated to `a0`. A strong prediction refuted; it is what identified `global.c:922-927`.
* **Splitting `sxy` without the merge** → **11**; the merge without the split → **3**. Both moves are required.
* **After the merge, every spelling of the final add** — operand order swapped, `sxy += uVar1`, fully inlined, a named
  temp in six widths, `Y1`/`ni` reused as the temp, `prim.dy` assigned first, the two stores split into two statements,
  the `prim.v0/v1` and `prim.v2/v3` constant pairs moved before/after/around the add: **3 in all fourteen**, always with
  destination `v0`. The destination is not reachable from statement text; only removing `sxy`'s second death moved it.
* `*(u16 *)(param_1 + 0x26)` folded directly into the add (no `hh` variable) → **13**: the second load must stay its own
  statement, because it is the *variable* that the tie needs, not the value.

## (f) Where the method fell short

1. **The pack's `residual.txt` hides the decisive fact.** Its class was `COUNT` and its headline was an extra `nop`,
   which reads as a scheduling defect; the cause was entirely allocation, and the `nop` was a *consequence* three steps
   downstream. The two lines that made the diagnosis mechanical are in the `-dl`/`-dg` dumps and nowhere in the pack:
   `Register N used K times across M insns [in block B]; dies in D places; crosses C calls` and `;; N regs to allocate`.
   **Ask:** have the engine emit those two lines for every pseudo of the body next to the diff (it already compiles the
   TU; `-dl -dg` costs one extra flag), or add `delever_search.py --try --dump` writing `t.i.lreg`/`t.i.greg` plus a full
   side-by-side listing into the score scratch dir. I spent roughly the first third of this task rebuilding that
   invocation from `recipes.json`'s `pipeline` field and `objdump`-ing `.run/P36/engine/score/<alias>__<fn>/cand.o` by
   hand; every agent will pay that again.
2. **`history.txt` cannot say "the generator does not contain the answer".** Its `best-scoring single candidates` list
   showed twelve moves all landing on 5, which reads as "close" — but no single move in R2/R5–R12 improves on 3, because
   the answer is a *variable-count* change (one merge, one split) and no generator changes the number of locals. A
   "no single move improves **and** the residual class is REG" flag would route bodies like this to an agent immediately
   instead of after 2,304 compiles (run `g5`).
3. **`.run/P36/engine/residual_moves.md` has no row for "mine caller-saved → target callee-saved".** That pair
   (`v1->s0`, `a0->s0`) is the single most diagnostic thing in the summary and it has exactly one cause in this compiler
   — the allocno crosses a call. Worth a row of its own, with `global.c:922-927` and the refutation above.
4. The `--try` loop itself was excellent: 0.75 s per compile, ~70 spellings scored, zero tree writes.
