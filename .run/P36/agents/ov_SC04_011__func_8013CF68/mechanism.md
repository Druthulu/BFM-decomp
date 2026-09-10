# func_8013CF68 (ov_SC04_011_jr_8013C98C.c): mechanism (T7 agent c27, P36 S103; re-draw after c9)

**Result: NOT closed.** The best score is still **10** (ORDER, 63/63). `PACK/body.c` is c9's `h2.c`, unchanged,
because nothing I tried beat it. Its `do { } while (0)` is a steering construct: it splits cse1's extended basic
block, and as a side effect it acts as a sched barrier. So the honest numbers are:
- **10** with that do-while;
- **35** with no steering construct at all (c9's `g1.c`/`g2.c`, re-scored today);
- **5** only with c9's refused do-nothing second `base =` (`scratch/c27/f2.c`, re-scored).

c9's copies are in `scratch/prev_body.c` and `scratch/prev_mechanism.md`. My probes are in `scratch/c27/`.

This run tested the coordinator's new idea: that re-spelling the stores or the `D_801F155x` loads (as a struct
member, an array element, a derived pointer, a struct through a cast) could restore the dependence edges the target
keeps. It cannot. The reason is below, with evidence from both the bytes and the dumps.

## (a) The residual in one sentence
c9's reading holds. With count and addressing exact (63/63), the one remaining defect is that sched1 hoists the
`lbu D_801F155x` loads above the `k($s0)` stores in blocks 2 and 3, where the target keeps the stores first. On top
of that, the do-while's two loop notes put `move a0,zero` and `sw zero,4(s0)` in the wrong places.

## (b) Why no address spelling can create the edge (sched.c, read and checked on dumps)
- The dependence tests are `true_dependence`/`anti_dependence` (`sched.c:817-864`). Their first conjunct is
  `memrefs_conflict_p` (`sched.c:614`). The `MEM_IN_STRUCT_P`/`rtx_addr_varies_p` clauses (`:830-835`, `:858-863`)
  are `&& !(...)` terms: they can only **remove** an edge that `memrefs_conflict_p` already allowed, never add one.
  c1's and c15's closes (the `/s` grant) worked because their store addresses VARIED (pointer bases), so
  `memrefs_conflict_p` returned 1 and the `/s` bit decided the edge. c11's worked for the same reason.
- Here `base` (reg 75) has one set, `(set (reg 75) (symbol_ref D_800A5E94))`, with a REG_EQUAL note
  (`cse.c:6919-6934` always writes it for a constant source). `init_alias_analysis` (`sched.c:419-438`) therefore
  records `reg_known_value[75] = D_800A5E94`. `canon_rtx` (`:371-392`) rewrites every store address
  `(plus 75 k)` as `(const (plus D_800A5E94 k))`, and `memrefs_conflict_p` reaches its CONSTANT_P arm
  (`:775-778`): two different SYMBOL_REFs never conflict, so it returns 0. Any other single-set pseudo address
  (a derived pointer, a record pointer, an array base) is canonicalised to its constant in the same way. Loads must
  stay `(mem (symbol_ref D_801F155x))`, because both the reloc names and the lui+lbu byte count require it.
- **PROVED on bytes** (`scratch/c27/sA..sF.c`, block 3 re-spelled over c9's scaffold). The S20 store as a struct
  member `((struct{s32 w;}*)(D_800A5E94+0x14))->w` scores 10. As an array element `((s32*)D_800A5E94)[5]`: 10. The
  whole record through a struct cast: 10. The loads as `(&D_801F155E)[0]`: 10. The loads as struct members through
  a cast: 10. The store via `base` directly: 11 (count +1, it folds).
- **PROVED on the sched1 dumps** (`scratch/c27/d_sA`, `d_sE`, `t.i.sched`). In sA the S20 store is `mem/s:SI`; in
  sE the loads are `mem/s:QI`. In both, the load (insn 113/115) carries **no** LOG_LINK to the store (insn 110).
- The order cannot be steered through priorities either. **PROVED on bytes** (`scratch/c27/perm.py`): all 60
  source orders of block 3 `{S20, S24, S28, loads, sbs}` score 10, and so do all 60 of block 2 (a few score 11-13).
  sched1 re-sorts them all to the same schedule. Within one priority group, `schedule_select` (`sched.c`,
  potential-hazard pick) chooses the store before the loads no matter what order the source gives.
- So the edge needs `reg_known_value[base] = (reg base)`, which means `reg_n_sets[base] != 1` or no REG_EQUAL
  note on its set. In plain C that takes either a second set of `base` (a do-nothing, refused; cse1 deletes it
  within one EBB, §194-K bound 5) or a source cse cannot evaluate (a load, a call, a parameter, or asm, and none of
  those gives a bare `la`). The cookbook's §194-K reached the same bound ("not spellable in plain C").

## (c) The moves (nothing new closes it; best = c9's h2 at 10)
1. (c9) Spell the block-2/3 family accesses as forced-constant addresses off the array (`*(s32 *)(D_800A5E94+4)`)
   and put a cse1-only EBB split (the do-while's LOOP_END) between `base`'s set and those accesses. Count goes 76 → 63.
2. (c9) Write block 1 through `r0 = (s32 *)(base - 0xC)`, used as both the store and the call argument.
3. (c27, new reading of move 2, from the dumps; the exact code path is inferred, not traced line by line) Why
   `-12(s0)` survives cse2 even though `base` is known: `find_best_addr` folds `(plus 75 -12)` to the constant
   (`cse.c:2664`). It then looks that constant up (`:2700-2735`), and its class also holds `r0` (live as the call
   argument) and `(plus 75 -12)`. Both cost 1, below the constant's 2 (`mips.c:1600` `mips_address_cost`), and the
   `(plus …)` form wins the tie on rtx cost. So the fold is undone. In `free.c`, with no `r0`, the same store stays
   `lui $at` + `%lo(D_800A5E94-12)` (compare `d_free/t.i.cse` insn 12 with `d_prev/t.i.cse2` insn 19). The rescue
   therefore reaches only addresses that a LIVE register already holds, which is why blocks 2 and 3 (one live
   call-argument pointer each) cannot be rescued this way.
4. (c27) Do-while placement: wrapping from `base`'s set scores 13 (`x1.c`), wrapping only `base` and `r0` scores
   11 (`x2.c`), and ending the loop before the call scores 10 (`x3.c`). 10 is the floor for this family.

## (d) Generator proposal
When the lever is an opaque `la` base AND the target keeps `k($sN)` stores ahead of loads of OTHER globals in every
block, first compute `reg_known_value` for the lever-free base (one set plus REG_EQUAL means known). If it is known,
**no store or load spelling can restore the order**: `/s`, array, derived-pointer and cast spellings only delete
edges (`sched.c:830-835`). Classify the site as IRREDUCIBLE-ALIAS and stop, instead of permuting statements.
Separately, the COUNT half generalises: "a `(plus base k)` store folded to `lui/%lo` is rescued when some live
register holds exactly base+k". A generator can try routing a folded field address through the call-argument
pointer the body already passes.

## (e) What did not work (byte evidence, `scratch/c27/`)
- `sA`-`sE`: `/s` or array spellings of stores and loads, 10 each (no LOG_LINK in the `.sched` dumps).
- `sF`: the store via `base`, 11 (COUNT 64, the address folds).
- `perm.py` b2/b3: all 120 statement orders, 10-13.
- `x1`/`x2`/`x3`: do-while placements, 13/11/10.
- c9's `g1`/`g2` (no steering construct), 35 (COUNT 73).
- c9's refused `f2` (second set), 5.

## (f) Where the method fell short
- The brief implies that "change how the address is spelled" transfers from c1/c11/c15. It transfers only when the
  base VARIES. The cheap check comes first: if `reg_known_value` of the base is a constant, the `/s` family is dead.
  The alias table in the cookbook (§165-25/§16Z) says this. A pack-builder check ("does the store's base pseudo have
  one set plus REG_EQUAL?") would have told this re-draw at once.
- `delever_search --try` is NOT safe to run in parallel on one function. Its scratch dir and object tag are per
  function (`delever_search.py:738,760`), so my first 8-wide permutation batch returned 999/COMPILE errors on half
  of the candidates. `scratch/c27/score.py` scores with a per-candidate scratch dir and tag, and I validated it
  first: tree = 0, c9 = 10, free = 38, the same as `--try`.
