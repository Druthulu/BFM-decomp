# func_8013CF68 (ov_SC04_011_jr_8013C98C.c): mechanism (T7 agent c9, P36 S103)

**Result: NOT closed.** Best clean plain-C spelling scores **10** (ORDER only; 63/63 instructions, every
address mode right). `PACK/body.c` holds it. A spelling at **5** exists (`scratch/f2.c`), but it relies on a no-op
second assignment of `base`, which is a dummy set, so it is refused and not claimed. My reading, argued below and
not exhaustively proven: with the pinned cc1, no straight-line plain C reaches 0. The `la` lever does two jobs, in
two different passes, and no plain-C construct I found does both without leaving a scheduling barrier.

## (a) The residual in one sentence
Starting from the lever-free text: COUNT 76 vs 63. With `base = &D_800A5E94` known constant, cse folds 13
`off(base)` stores into `lui $at` + `sw %lo(D_800A5E94+off)` pairs (rec0.a in block 1, and every field of blocks 2
and 3). Once that is fixed, a second defect is left: ORDER. In the target, blocks 2 and 3 keep their base-relative
stores before the `D_801F155x` byte loads, in source order. With a known base, the loads hoist above them.

## (b) The passes and decisions (all `tools/reference/gcc-2.7.2/`)
1. **The fold (count).** `find_best_addr` (`cse.c:2664`) applies `fold_rtx` to every non-REG address with no cost
   check. The REG arm of `fold_rtx` (`cse.c:5170-5178`) substitutes `qty_const` for `base`, so `(plus base k)` becomes
   `(const (plus D_800A5E94 k))`. That form is legitimate on MIPS, so it is emitted as a `lui $at` macro. Only a bare
   `(mem base)` survives (`base[0]`, which is `sb v1,0(s0)` in both). PROVED in `scratch/d_free/t.i.cse`: the fold is
   already in cse1.
2. **The re-anchor (how I got the count right).** A forced-constant address (array/global spelling such as
   `*(s32*)(D_800A5E94+4)`) is expanded as `(set Yk (const sym+k)) (mem Yk)`. The address is a REG, so the fold at
   `cse.c:2664` never sees a constant. `use_related_value` (`cse.c:1781`, called at `cse.c:6535`) rewrites `Yk` as
   `(plus R d)` against whichever register already holds a member of the same symbol family.
   - If the anchor is `base` in the same EBB, cse2 folds `(plus base k)` again (`scratch/c1.c`, `a.c`).
   - If the first family access sits in a cse1 EBB where `base` is unknown, it becomes a local anchor L. The
     others become `(plus L k)`. In cse2, L is re-related to `base` and `(plus L k)` is canonicalised to
     `(plus base d+k)` **without folding**. PROVED in `scratch/d_c2/t.i.cse2`, insns 65/73: `(plus (reg 79) 4)`
     becomes `(plus (reg 75) 20)`.
   - The only cse1-only EBB splitter is `NOTE_INSN_LOOP_END` (`cse.c:8054-8055`, ignored when `after_loop`, which
     cse2 passes at `toplev.c:2926`). So a `do { } while (0)` gives cse1 two EBBs and cse2 one.
   Result: 63/63 instructions, every addressing mode equal to the target (`scratch/d1.c`, `body.c`).
3. **The alias oracle (order).** `init_alias_analysis` (`sched.c:419-438`) sets `reg_known_value[base] =
   D_800A5E94`, because `base` has one set and cse always adds a REG_EQUAL note for a constant source
   (`cse.c:6919-6934`). `canon_rtx` then turns `(plus base 4)` into `D_800A5E94+4`, and `memrefs_conflict_p`
   (`sched.c:775-778`) proves it disjoint from `D_801F155B`. No anti/true edge is created, and the loads (higher
   priority) go first. The target's order needs the edge, so the original's base was **opaque** to the oracle.
   PROVED on bytes: `scratch/f2.c` gives `base` a second set in a later cse1 EBB. cse2 reduces it to
   `(set (reg 75) (reg 75))` with REG_EQUAL. flow keeps it because of its REG_EQUAL exemption (`flow.c:957-964`), so
   `reg_n_sets = 2` and the oracle is blinded. Block 2 then comes out exactly in target order
   (`scratch/d_f2/t.i.cse2` insn 110; the no-op becomes `(set s0 s0)` in `.greg` and emits nothing).
4. **Why neither fix reaches 0: the loop notes are sched barriers.** `sched_analyze_insn` (`sched.c:2058-2080`)
   makes the first insn after a LOOP note (the "carrier") depend on every earlier insn, and every later insn depend
   on it. The target hoists each call's argument sets to the very top of its block (`move a0,zero` is the function's
   first body insn; `li a0,1/2` plus `addiu a1` come right after the previous `jal`). In source those sets come last.
   So the only consistent carrier position would be the argument set itself, which is impossible. **No LOOP note
   (and no label, which is a sched block boundary) can sit anywhere in this function.** Without an EBB split, a
   single-set constant base is known to both cse passes (fold) and to the oracle (no edge). A second set that
   survives flow without a split is deleted by cse1 as a no-op (`delete_dead_from_cse`, `cse.c:8700-8773`). That is
   the reason the tree needs an opaque `la`: an asm output carries no REG_EQUAL, so both jobs are done at once.

## (c) The moves, one line each (best clean = 10, `body.c` = `scratch/h2.c`)
1. Spell the family accesses of blocks 2 and 3 as constant addresses off the array symbol (`*(s32 *)(D_800A5E94 + 4)`,
   `D_800A5E94[0x10]`), not as `base`-relative arithmetic. This gives forced-constant REG addresses, so no cse fold.
2. Put a LOOP_END between `base`'s set and those accesses. Here that is `do { record 0 } while (0);`: 38 → 10/11,
   count 76 → 63.
3. Block 1 through a record pointer `r0 = (s32 *)(base - 0xC)`, used for the store and as the call argument. This
   keeps `sw zero,-12(s0)` and `addiu a1,s0,-12` with no loop at the top. It also fixes the prologue order
   (`sw s0; la; sw ra`), 11 → 10. PROVED: `scratch/g1.c` block 1 is byte-exact, and blocks 2/3 fold there because
   there is no split.
4. (Refused, 5) A second `base = D_800A5E94;` in a later cse1 EBB (`scratch/f2.c`) blinds the alias oracle, and
   block 2 goes exact. It is a dummy set and still carries loop-note barriers.

## (d) Generator proposal
When the tree lever is an opaque `la` (asm) base, and the lever-free residual is COUNT made of `lui $at`/`%lo(SYM+k)`
pairs where the target has `k($sN)`, try this: (1) re-spell the base-relative accesses as forced-constant
array-element addresses of SYM, and (2) put a `do{}while(0)` boundary between the base's set and them. This is the
cse1-only EBB split: it fixes the count. Then **check the order before spending more**: if the target keeps
`k($sN)` stores ahead of loads of OTHER symbols in source order, the base must be opaque to `init_alias_analysis`
as well. No loop note can be placed there when the target also hoists call-argument sets to block tops, so mark the
lever IRREDUCIBLE and stop. A structural detector: "`la $sN,SYM` held across calls; stores `k($sN)` precede
`lbu %lo(OTHER)` in source order in every block; `li $a0` at each block top" means the lever is irreducible.

## (e) What did not work (byte evidence, all in `scratch/`)
- `free.c` 38: known base, 13 folded `lui/%lo` stores. `lab1.c` (unused user label after the base) 38: jump deletes
  it before cse1.
- `a.c` 48 (GsF_LIGHT-shaped `struct {s32 a,b,c; u8 r,g,b,pad;} D_800A5E88[]`): the anchor becomes rec0 (sym88) and
  the reloc symbols are wrong (the scorer compares reloc names, so the struct is also unusable for that reason).
- `c1.c` 38 (array spelling, no split): the anchor is the first family access, sym-12. `c2/c4.c` 27: blocks 2/3
  become relative, but the anchor is still sym-12 and col[0] is a `lui` pair (64 instructions).
- `d1.c` 11, `d2.c` 11 (`do{ base = … }while(0)` at the top): count exact. The top carrier pins `sw zero,-12`
  before `move a0,zero`, and the loads hoist in blocks 2/3 (alias).
- `d3.c` 39: col[0] written through the array instead of `base`. `base` is then dead, so there is no anchor.
- `e1.c` 63: a plain second `base =` in the same cse1 EBB. The re-anchors break and `base` splits into $3/$16.
- `f1.c` 5 / `f2.c` 5: the refused second set. Block 2 exact in f2, block 3 pinned by its carrier.
- `g1/g2.c` 35: record pointers r0/r1/r2 with no split. Block 1 exact, but in cse1 `r1` gets `qty_const`, so
  `(plus r1 k)` folds.
- `h1.c` 40: a `static inline` helper taking `u8 *base`. integrate.c substitutes the constant, so it folds like
  the free version.
- `h3/h4.c` 10: more per-record do-whiles do not change the score. `h5/h6.c` 10: a second set before the last call
  is dead and flow deletes it. `h7/h8.c` 30: a second set in the same EBB as later family accesses re-anchors them
  on `base`, and cse2 folds.

## (f) Where the method fell short
- COUNT FIRST was right. The count gap was not a register issue: it was cse folding, and fixing it exposed an
  ORDER defect in a different pass (the alias oracle). The brief's pass list does not name
  `init_alias_analysis`/`reg_known_value`. The cookbook does, in §194-K (`sched.c:399-438`), and its bound 5 ("not
  spellable in plain C") holds here too. The flow.c:957 REG_EQUAL exemption is a new wrinkle: a no-op second set
  CAN survive, but only after a cse1 split.
- The scorer compares reloc SYMBOL names (`masked_diff.py:286`). Any "natural" record-struct spelling
  (GsF_LIGHT at D_800A5E88; func_80028620 looks like `GsSetFlatLight(id, &lt[id])`) is therefore scored wrong even
  where the linked bytes would be equal. This limits which faithful spellings can be tested.
- Useful tool: `scratch/cc.sh` (splice + `-dL -dr -ds -dt` dumps; `-dt` = `.cse2`, which was essential).
