# func_80135168 (src/ov_SC04_011/ov_SC04_011_jr_8012ACE0.c): T7 agent c1, S103

**Result: score 0 (62/62 instructions). Words and relocations are identical to the tree object's function, checked by
`diff` of `objdump -drz`. Stable over repeated `--try` runs. No pin, no asm, no added volatile, no invented term.**
The coordinator still has to run the whole-object gate.

## (a) The residual in one sentence
Nothing is missing: both sides are 62 instructions. What differs is the register permutation of three single-block
pointer locals and one reused temp: target pb0=t0, pac=a2, pb8=a3, b=v1; the start had pb0=v1, pac=a3, pb8=a2, b=t0.
The target also hoists the `D_801909C0` load above the prologue, which is the 2-instruction "insert" at the head.

## (b) The passes and decisions (read in gcc-2.7.2 source, then proven on dumps and bytes)
Three decisions stack. Each one is proven on the `.lreg`/`.sched` dumps (`PACK/scratch/dumps_*`), and the combination
is proven on bytes.

1. **Which pass allocates the temp: local-alloc or global.** `local-alloc.c:472` hands a pseudo to local-alloc only when
   `reg_basic_block >= 0 && reg_n_deaths == 1`. The start text reused one `u16 a, b` across all three x/y/z statement
   groups, so each of them dies 3 times. That makes them GLOBAL allocnos: the start's `.greg` order line is `81 80 75`,
   and alloc_table shows r81=b and r80=a with "dies in 3 places". Global allocation runs only after every local qty
   already has its register, so the local pointer pb0 took v1 before b could get it, and b ended up in t0.
   **Move 1:** give each group its own temps (`ax,bx / ay,by / az,bz`). Each now dies once, so each is a local qty with
   priority 7500 (3 refs over 4 indices). That is higher than the pointers' priority, so the temps are placed first:
   b→v1 and a→v0 inside each group's window. Pointer pb0 then finds v0/v1/a0/a1 busy. Proven: this alone takes the
   score from 25 to 12. pb0=t0 and b=v1 come out right, and the head hoist comes out right too (not traced, see (f)).
2. **The order among the three pointers (local-alloc `qty_compare_1`, `local-alloc.c:1598-1625`).** The priority is
   `floor_log2(refs)*refs / (death-birth)`. Birth and death are `2*insn_number` after sched1 (`reg_is_set` :1970,
   `wipe_dead_reg` :2057). `find_free_reg` (:2073) then gives each qty the lowest free hard reg over its window. After
   move 1: pb8 = 8/30 → 2666, **pac = 12/46 → 2608**, pb0 = 8/32 → 2500. So pb8 was placed before pac and took a2, and
   pac got a3. The target needs pac > pb8 > pb0.
3. **Why pac lived 46 indices: sched1 dropped an anti-dependence (`sched.c:858-863`, `anti_dependence`).**
   `a2v = pac[2]` is `MEM_IN_STRUCT_P` because its address is a top-level PLUS_EXPR (`expr.c:4570-4577`), and its
   address varies. `D_801EDA40 = 0` is a plain scalar at a fixed address. The exception clause drops the
   store-after-load edge, so sched1 sank the `pac[2]` load below the store and below the a0/a1 argument setups
   (`.sched` order: 71, 80, 88, 90, **75**). That pushed pac's death from index 50 out to 56. `pac[0]` is a bare `*pac`,
   has no `/s`, and so keeps its edge.
   **Move 2:** store through the shared `H16` member view, `((H16 *)&D_801EDA40)->h = 0;`. A COMPONENT_REF always sets
   `/s` (`expr.c:4888`). With both sides `/s`, the exception fails, the edge stays, and sched1 keeps the store after
   both loads. Final `.sched` order: 71, 75, 82 (`mem/s` store), 90, 92. pac becomes 12/40 → **3000**, above pb8 2666
   and pb0 2500, which gives pac=a2, pb8=a3, pb0=t0. This is proven on the final dump
   (`PACK/scratch/dumps_final`, `lpri.py`).

The tree's two levers encoded exactly these two decisions:
- The `"memory"` barrier sat between the pac loads and the `D_801EDA40` store. It is the lever form of the missing
  anti edge.
- The three pins plus the keepalive forced the permutation that the reused temps' global allocation could not reach.

## (c) The moves that closed it (they only work together)
- **Split the reused temps per group:** `u16 a, b` becomes `u16 ax, bx, ay, by, az, bz` (one pair per x/y/z statement
  group). Per-group block-scoped `{ u16 a, b; ... }` temps also score 0 (scratch `vF.c`).
- **Spell the scalar-global store as a member store:** `D_801EDA40 = 0;` becomes `((H16 *)&D_801EDA40)->h = 0;`.
  `H16` is `src/shared/engine_types.h:832` and is already used by 532 cast sites in `src/`. This is the cookbook's
  "/s-DEP LATTICE" idiom (docs/matching-cookbook.md ~L2538) and residual_moves.md row 6 ("grant `/s`").

Each move alone: the split scores 12, the store scores 20 (from 25). Together they score 0.

## (d) Generator proposal
- **Temp split:** when the residual is a register permutation, and the allocation table shows a `.greg` allocno that
  lives in ONE block but dies in N>1 places (a temp reused across repeated statement groups), rename it apart at each
  full redefinition (one temp per group, i.e. one per web). Each copy then dies once and becomes a local-alloc qty
  (`local-alloc.c:472`) that is placed before the long-lived locals.
- **/s grant on a store:** when a pointer load with a constant nonzero offset and a plain fixed scalar global store
  both sit in the block that feeds a call, and the lever text carries a `"memory"` barrier between them, rewrite the
  store as a member store of the width-matched shared struct (`H16` for u16/s16, `struct{s32 w;}` for 32-bit). That
  restores the anti edge at `sched.c:858-863`. Score both moves jointly as well as singly.
- **Likely first family member:** the sibling directly above, `func_80135004`, has the same shape and the same levers
  (pins $9/$6/$8 plus a keepalive, same tail with `D_801EDA40 = 0`). I did not test it, to avoid the shared per-function
  scratch object of another agent.

## (e) What did not work (byte evidence, scratch/*.c)
- `v2`: loading pb8 before `b0` in the source scores 12. sched1 re-sorts to the same order, so the lifetime is
  unchanged.
- `v3`/`v4`: putting the `D_801EDA40` store before the pac loads (or inlining the loads into the call args) scores 28,
  with 60 instructions. The store floats into the third group, and pb0 and pb8 swap.
- `v5`: swapping the `a1v`/`a2v` statements scores 12. sched1 re-sorts them.
- `vB`: a block-scope `extern u16 D_801EDA40[];` is a COMPILE-ERROR ("conflicting types"). The file-scope
  `extern u16 D_801EDA40;` sits just above the function. The a18 array form therefore needs a TU-level declaration
  change and is out of scope for a body edit (types phase).
- `vC`: the /s store alone scores 20.
- `vD`: splitting only b scores 23. `vE`: splitting only a scores 38. Both halves are needed.
- `vG`/`vH`: hoisting all three pointer loads to the top scores 25. It changes the lifetimes the wrong way.

## (f) Where the method fell short
- **The priority that decides here is not in the table.** `tools/alloc_table.py` prints the GLOBAL-formula priority
  from the `.lreg` "used N times across M insns" line. For local qtys the deciding number is local-alloc's
  `qty_compare_1` over the post-sched1 `2*insn_number` birth/death indices. The table showed pac, pb8 and pb0 all tied
  at 5000, which hid the real order 2666 > 2608 > 2500. I wrote `PACK/scratch/lpri.py` (about 40 lines, it parses the
  `.lreg` insn stream) to get the true order. Suggestion: add a local-qty priority column to alloc_table.
- **The key clue was in the table but not called out.** A "dies in N places" pseudo that sits in the `.greg` order line
  while living in one block is exactly the split case. The brief could name it.
- **sites.txt could flag the barrier pattern.** The `barrier memory` NEEDED site placed between a pointer load and a
  scalar-global store is a direct pointer to the /s class; the pack could say so.
- **Not traced:** why sched2 hoists the `D_801909C0` load above the RTL prologue (`mips.md:6029` `define_expand
  "prologue"`) once pb0 is in t0. It came for free with move 1.
