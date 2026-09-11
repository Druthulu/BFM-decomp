# func_8018226C (ov_SC02_026_jr_8017C180.c): T7 agent c55

**Result: score 0, byte-identical (43/43 insns). No pin, no asm, no volatile, no zero term.** `body.c` = scratch/d1.c.
Nothing outside the body changed. The four argument-register pins ($3,$4,$5,$6) are gone, and so is the `a3 = arg0` copy.

## (a) The residual in one sentence
There were no missing or extra instructions (43 vs 43, same mnemonics). Every register in the entity block was permuted:
the parameter copy sat in `a1` where the target has `a3`, and the temps were shifted to match (a2->v0, a3->v1, v1->a0, a0->a1, v0->a2).

## (b) The passes and decisions (read, then proved on bytes)
1. **Temps reused inside one block go to global-alloc** (`local-alloc.c:472`: a pseudo gets a local quantity only if
   `reg_n_deaths[i] == 1`). `body_free.c` is an m2c transliteration that reassigns `v0` six times and `v1` twice in block 3,
   so they die several times and reach global-alloc with the parameter copy. Local-alloc hands `v0,v1,a0` to the three
   single-death temps, and `find_reg` (`global.c:904`) then gives the parameter copy r73 the lowest free register, `a1`.
   The other registers cascade from there. Proved: alloc_table `free` lists r73/r75/r74 as globals conflicting with only
   v0,v1,a0.
   Giving every value its own name (c3.c) makes all 11 block temps local. They fill v0..a2, the parameter pseudo
   conflicts with v0..a2, and it gets `a3`. **Score 29 -> 6.**
2. **The last permutation (a0/a1/a2 among the 0x88 halfword, the 0x20 pointer, and the `*(0x78)` halfword) is decided by
   local-alloc's ranking** `qty_compare_1` (`local-alloc.c:1598`): `floor_log2(refs)*refs*size/(death-birth)`. All three
   have 2 refs, so the order depends only on live length, and live length depends on where **sched1** (which runs before
   local-alloc) puts the loads. That placement depends on the source order of the stores.
   - c3 (stores 6, E, A, 76; `*(0x78)` loaded into a temp): x0 is born at 28 and dies at 38, pri 2000. It ranks ahead of
     x88 (1666) and obj20 (1111), so it takes a0. Wrong.
   - d1 (stores **6, A, E**, i.e. x, y, z from 0x88/0x8A/0x8C in ascending order, loads inline, the 0x76 copy next to the
     0x5C copy): sched1 emits the `*(0x78)` load early and its store last. x0 lives 24..38, pri **1428**, below x88 22..32
     (2000) and obj20 30..40 (2000). Ranked last, it gets a2; x88 gets a0 and obj20 gets a1. `tools/localalloc_sim.py
     dumps_d1/d1.i.lreg func_8018226C 25` reproduces all 11 quantities (`mismatches vs dump: 0`).
   The final order is set by sched2 (after reload), which is why the m2c text shows 6, E, A: that is the scheduled order,
   not the source order.
3. **Control flow:** `if ((f & 0x800) && (f & 0x10))` is folded to `(f & 0x810) == 0x810` by `fold_truthop`
   (`fold-const.c:2687`), which emits one `andi`/`bne` where the target has two tests (c2.c, 41 insns). Nested ifs that
   fall through to the single `func_8012C098` call keep the two `beqz`, with no goto or label.

## (c) The source moves
- Delete the parameter copy and every reassigned temp. Each field copy is written as one statement,
  `*(s16 *)(a0 + D) = *(u16 *)(a0 + S);`, leaving one `flags` read of 0x70 (the version with no `flags` variable at all,
  d2.c, also scores 0).
- Store order 0x5C, 0x76 (the two halfwords read through the 0x78 pointer), then 0x6, 0xA, 0xE (x, y, z from
  0x88/0x8A/0x8C). The sibling `func_8017EC78` in the same TU writes 6, A, E in the same order.
- `if (flags & 0x800) { if (flags & 0x10) { ...; func_8012B2CC(a0); return; } } func_8012C098((void *)a0);`

## (d) Generator proposal
When a REG-caller residual is a whole permutation of v0..a3 and the parameter copy lands in a lower argument register
than the target's, check block-local temps with `reg_n_deaths > 1` (a name reassigned inside one block). Split or inline
them (R23) so every temp is a local-alloc quantity. If a permutation among 2-ref locals remains, enumerate the orders of
the independent same-base stores that consume them: sched1's births set `qty_compare_1`'s 2/(death-birth). Try the
ascending-field-offset order (struct-member copy order) first. The search took 3120 compiles (x88/x8C/x8A/x0 temp
subset x load order x store order x 0x78 form) and 100 scored 0. Every winner stored 6 before A before E, and the
simplest winner has no explicit temps at all. An R-rule could enumerate just the permutations of consecutive same-base
stores with their loads inlined.

## (e) What did not work (byte evidence)
- c1: one name per role but `v0`/`v1` still reused inside block 3: 29 -> 26 (still global).
- c2: fully natural with `&&`: fold_truthop merges the two bit tests, COUNT 41.
- c4: natural with store order 6, E, A: 22 (sched1 order and registers both off).
- c5/c6: inlining only obj20, or only x88, into c3: 4 (a two-way swap remains). c7 (both inlined): 4. 0x88 and 0x8C
  trade places because the E store still comes before A.
- g2 sweep: the store order 6 < A < E is necessary but not sufficient. None of the 2600 candidates without it scored 0.
  Of the 520 with it, 100 scored 0; the other 420 failed on where the explicit temps were loaded.

## (f) Where the method fell short
- The brief's hint (four argument-register pins usually mean a wrong-arity call) did not apply. Both callees take one
  argument and are declared correctly. The pins stood in for a transliteration defect, not a call-arity defect.
- The m2c body's statement order is the post-sched2 order, so "keep the body's order" held the source in the wrong
  order. For block-local permutations, the useful unit of search is the order of independent stores, not temps.
- Proved on bytes: every claim above (--try scores; localalloc_sim with 0 mismatches). Not proved: why sched1 puts the
  0x76 store after the xyz stores in d1 (I read the result from the .lreg order, not from `rank_for_schedule`).
