# func_80168828 (ov_SC04_011_jr_8015C32C.c) — T7 agent report

**Outcome: score 0 (MATCH, 108/108 ins) with the `$3` pin AND its variable `c40` deleted.
The `$4` pin remains and is argued below to be semantically irreducible in a body-local rewrite.
Sites: 2 -> 1.** The fully lever-free text bottoms out at **score 1** (proof below).

`PACK/body.c` is the score-0 text. Verified with
`.venv/bin/python tools/delever_search.py --try src/ov_SC04_011/ov_SC04_011_jr_8015C32C.c func_80168828 PACK/body.c --body`.

---

## (a) The residual in one sentence

Two independent residuals were tangled in the lever-free start (score 35, `COUNT`, 107 vs 108 ins):

1. **the constant residual (closed).** The target holds the CSE'd `0x40` in **`$v1`** across a run of unrelated
   byte stores (`li v1,64` at idx15, its four `sb v1,…` at idx36-40); the lever-free text puts the same constant
   in **`$v0`** and emits `li v0,64` immediately in front of its own four stores. Same instructions, different
   register and therefore a different schedule.
2. **the argument residual (open).** The target's idx2 is `move s1,a0` — it *reads the incoming `$a0`*. The
   function is defined `void func_80168828()` because `src/shared/ov/func_801687CC.h` (spliced into this TU by
   `#include "../shared/ov/func_801687CC.h"` at line 5636) declares `extern void func_80168828(void);`. With no
   parameter there is no C expression for `$a0`, so no lever-free spelling emits that instruction; the whole
   107-vs-108 count gap and the callee-saved bank rotation (`s2->s3, s4->s1, s3->s4, s1->s2`) are downstream of it.

## (b) The pass and the decision — read from `tools/reference/gcc-2.7.2/`, confirmed in the cc1 dumps

The constant residual is decided in **local-alloc**, not in sched and not in cse. Dumps taken with
`cc1 … -dr -ds -dj -dl -dg -df -dc -dS -dL` on the *spliced real TU* for both orderings:

* `cse` / `combine` / `flow` are identical up to insn ORDER: the `0x40` is one pseudo `(reg/v:SI 76)` set by
  `insn 12 (set (reg 76) (const_int 64))` with a `REG_EQUAL`, consumed by four `(subreg:QI (reg 76) 0)` stores;
  the `0x10` is a second pseudo `(reg:QI 82)`.
* `*.lreg` header, the one line that changes:
  `Register 76 used 5 times across 10 insns in block 0` (unswapped) -> `across 14 insns` (swapped),
  and the assignment line `;; Register 76 in 2.` -> `;; Register 76 in 3.` — i.e. **$v0 -> $v1, chosen by
  local-alloc**. `*.greg` only records it (`;; Hard regs used: 2 4 5 …` -> `2 3 4 5 …`).
* the decision: `local-alloc.c:2073 find_free_reg`, the live-range scan at **`local-alloc.c:2109-2110`**
  `for (ins = born_index; ins < dead_index; ins++) IOR_HARD_REG_SET (used, regs_live_at[ins]);`.
  Unswapped, qty(76) *dies at insn 61* and qty(82) is *born at insn 64* — disjoint intervals, so the second
  quantity allocated finds `$v0` free and both land in `$v0`. Swapped, insn 61 becomes the `li 16` and the last
  `sb …,46(sp)` moves to insn 66, so **qty(76) is still live across the whole of qty(82)** — the intervals now
  overlap, `used` already contains `$v0` when qty(76) is allocated, and it takes the next free `$v1`.
  Which quantity is allocated first is `qty_compare` at **`local-alloc.c:1579-1595`**
  (`floor_log2(n_refs)*n_refs*qty_size / (death-birth)`, densest first) applied through the unrolled
  `switch (next_qty)` at `local-alloc.c:1485-1512`; the dumps show the short, dense qty(82) taking `$v0`.
* the schedule then follows for free: with the constant in `$v1` it no longer collides with the stream of
  `li v0,…` constants, so `sched` hoists `li v1,64` to idx15 and sinks its four stores to idx36-40, exactly the
  target's order. **Proved: the local-alloc register change (dumps + bytes). Read, not separately proved: the
  sched attribution — the byte match is the only evidence for that step.**

## (c) The moves that closed it (each one line)

1. Delete `register s32 c40 __asm__("$3");` and `c40 = 0x40;`, and write the literal `0x40` at its four uses (`thing.f18/f19/f22/f1e`) — byte-neutral by itself; the pin and the variable were never doing the work.
2. Swap the two adjacent statements `thing.f1e = 0x40;` and `thing.f1a = 0x10;` so the `0x10` store splits the run of `0x40` stores — this is the whole move, and it is what closes residual 1.

Robustness of move 2, measured (each one `--try` compile, all score 0 unless noted):
`f1a` after `f18` (1+3 split) = 0 · after `f19` (2+2) = 0 · after `f22` (3+1, the chosen text) = 0 ·
`f1e` moved past the whole `0xff/0xc0` group to last = 0. Any split of the `0x40` run works.
Splitting a *different* constant's run breaks it: moving `f21=0xc0` between `f20=0xff` and `f1c=0xff` = **12**;
sorting the whole block by field offset = **9**.

## (d) GENERATOR PROPOSAL — R16, "split the constant run" (a residual-DIRECTED swap)

> **When the residual is ORDER-only and confined to one constant K — the target holds K in a register
> (`li rX,K` scheduled early, its consuming stores late) while yours emits `li v0,K` immediately in front of its
> stores — find the run of consecutive statements that assign the same literal K, and move the nearest
> neighbouring statement that assigns a *different* literal into the run (try each of the run's split points, and
> also try moving the run's last member past the neighbouring group). Extending K's pseudo across the other
> constant's pseudo makes their live ranges overlap, so `find_free_reg` (`local-alloc.c:2109`) must give K a
> second register.**

Two things make this a new move rather than a restatement of what exists:

* it is **directed**, where `R9 adjacent_swaps` is blind. R9 does contain this candidate — g5 found it after
  **2,271 compiles**, and g3/s1 never did. R16 reads K straight out of the `li` in the diff and tries |run|+1
  candidates: **~5 compiles instead of 2,271.** The applicability test is cheap and exact: the diff class is
  ORDER, every differing insn mentions the same immediate K, and the source has >= 2 consecutive statements
  assigning that literal.
* it is a **single-block live-range** move. R15 `sink_merges` is the opposite shape — it removes a *cross-block*
  pseudo from `global.c` by sinking a post-merge statement into if/else arms; R16 *lengthens* a block-local
  quantity so that local-alloc is forced to a second colour. Neither subsumes the other.

**Companion site rule (the family, and the reason this crack is worth generalising).** A NEEDED pin whose
variable is assigned exactly one integer literal and read only as the RHS of stores is not a register lever at
all — it is a *constant-holder pin*. The delever move is: delete the declaration and the assignment, inline the
literal at every use, then run R16. A textual census of `src/` (regex over every `// !FAKE: pin` declaration,
requiring exactly one `name = <literal>;` and every other occurrence matching `= name;`) counts
**284 constant-holder pins out of 10,958 pin sites**, e.g. `c40`/`$3` here, `eight`/`$2` in
`*_jr_80140608.c`, `mask`/`$4` in `ov_SC03_006_jr_8017AE2C.c`. This function is a 134-overlay family exemplar,
so this one crack is ~134 sites by propagation alone.

## (e) What did NOT work, with byte evidence

* **the `$4` pin cannot be removed body-locally.** `s32 a0v; s32 param_1 = a0v;` (an uninitialised read),
  `u8 *a0v; … (s32)a0v`, splitting the declaration from the assignment, and deleting `a0v` outright and simply
  never assigning `param_1` **all give the identical score 25 residual (107 vs 108 ins)** — gcc emits *nothing*
  for reading an uninitialised local, so the target's `move s1,a0` has no source. Byte proof that it is the
  argument and not the allocation: the "no `a0v` at all" spelling reproduces the missing-insn hunk
  `mine[2:4] target[2:6] … -- | move s1,a0` exactly.
* **the K&R escape fails.** `void func_80168828(param_1) s32 param_1; { … }` is
  `…jr_8015C32C.c:5657: number of arguments doesn't match prototype` (cc1 error) against the header's
  `extern void func_80168828(void);`. A prototyped `(s32 param_1)` is the same hard error (already recorded in
  the crack note above the function). Both would need an edit to `src/shared/ov/func_801687CC.h`, which is out
  of a body-local rewrite's reach.
* **score 1 is a coincidence, not a near miss.** The mechanical search's best path
  (`u8 a0v; s16 param_1 = a0v;` + the swap) reaches score 1 with the single diff
  `mine[2] andi s1,s1,0xff | target[2] move s1,a0`. That `andi` is a truncation of *garbage already in `$s1`* —
  it never touches `$a0`. It scores 1 only because it happens to be one instruction in the right slot and to
  restore the register pressure that fixes the callee-saved bank; the value is wrong and the encoding is wrong.
  `char` gives the same 1; `s8`/`signed char` give 19 (a `sll/sra` pair instead of one `andi`);
  `s16`/`u16` give 19; `u8`+`s32`/`u8`+`u16`/`u8`+`u8` give 18; `s32`+`s16` gives 19. **The score-1 text is
  therefore NOT proposed** — it is a wrong-value coincidence, and it is less readable than the pin.
* `s32 c40 = 0x40;` (initialised at the declaration, no swap) scores **10**, identical to `s32 c40;` — proof that
  the variable's shape is irrelevant and only the statement ORDER matters.

## (f) Where the method fell short

* **`history.txt`'s "best single candidates" list is actively misleading.** It came from the shallow `s1` trace
  and ranks `R7 do-while @5673 -> 15` first; the move that actually matters (`R9 swap-stmts @5686`) is listed at
  18 and only as a third-tier tie. The g5 *path* was the useful record. The pack should carry the best path's
  final residual text, not just its score — I had to re-run g5's spelling myself to see what the last
  instruction was.
* **the pack does not say which levers are semantically forced.** `sites.txt` marks both pins `NEEDED DIFFERS`,
  but the `$4` pin is a *declaration-conflict reconcile* (there is no C expression for the value) while the `$3`
  pin was pure scheduling superstition. The crack note directly above the function in the tree says exactly this
  — the pack should include the `// @crack:` comment block that precedes the definition. It would have saved the
  first third of this session.
* **the residual's own text pointed at the wrong pass.** "a constant the target holds in a register while yours
  rematerialises it" reads as a cse/sched problem; it is a local-alloc live-range problem, and only the
  `.lreg` `used N times across M insns` line said so. `residual_moves.md` should carry that line as the
  discriminator for the class: *if the two texts differ in `across M insns` for the constant's pseudo, it is
  `find_free_reg`, and the fix is a source-order move, not a temp or a width.*
