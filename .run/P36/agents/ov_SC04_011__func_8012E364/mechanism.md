# func_8012E364 (src/ov_SC04_011/ov_SC04_011_jr_8012ACE0.c) — T7 agent c51, MINIMUM-LEVER pass

**Final: score 0 (MATCH, 67/67) with TWO levers.** They are two of the tree's three pins, `flags` $2 and `d` $2. The
tree's third pin (`prev` $5) is replaced by one plain-C spelling: the entity-pointer field read as `((s32 *)arg0)[8]`
instead of `*(s32 *)(arg0 + 0x20)`.
- `PACK/body.c` holds it. Proven on bytes with the official `--try`.
- No single lever reaches 0 from any plain body tried, and (c) proves why.
- My first result, the tree's three pins on the tree's order (0, three levers), is kept as
  `scratch/c51/body_pfd_final.c`.
- The earlier agents' files are kept: `scratch/c22_body.c` (the score-4 ORDER body), `scratch/c22_mechanism.md`,
  `scratch/prev_mechanism.md`.
- All my probes and searches are under `scratch/c51/`.

(The tree's fourth marked site, the `arg0` $6 pin, was already REMOVED by the byte oracle — `sites.txt` — and it does
nothing on any base; see the table.)

## (a) Single-lever table (official `--try`, 67/67 ins unless noted)

Bases:
- F = `body_free.c`, the tree's order, 25.
- O = the c22 ORDER body, 4.
- T = F with the three `arg0 + 0x20` reads spelled `((s32 *)arg0)[8]`, 25 (`scratch/c51/t1/N.c`).

| lever (one only) | F | O | T |
|---|---|---|---|
| none | 25 | 4 | 25 |
| pin `prev` $5 (tree) | **13** | 4 | 15 |
| pin `flags` $2 (tree) | 19 | 4 | 20 |
| pin `d` $2 (tree) | 25 | 4 | 25 |
| pin `arg0` $6 (tree, oracle-REMOVED) | 19 | 4 | 21 |
| pin `v` $3 | 19 | 4 (fast) | 20 |
| pin `e1` $4 | 25 | 4 (fast) | 25 |
| pin `e2` $4 / `spd` $7 / `a` $4 / `diff` $2 | 23 / 23 / 26 / 25 | 4 (fast) | — |
| keepalive `v` after the second entity `sh` (`__asm__ __volatile__("" : : "r"(v))`) | 26 (the abs `move` arm appears; the rest permuted) | 4 (fast) | 26 |
| keepalive `v`, non-volatile | 25 (sched1 hoists it above the abs; no effect) | — | — |
| keepalive `v` at the function end | 17, 68 ins (reorg cannot fill the `jr` slot across a volatile asm) | — | — |
| keepalive `prev` / `e1` / `flags` | 22 / 25 / 27 (68 ins) | — | — |

- Every single lever, crossed with 3 flags spellings × 2 widths × 3 `v` spellings × 16 MEM_IN_STRUCT masks × 4 load
  orders (`scratch/c51/search8.py`, fast): the best is 5.
- **No single lever reaches 0.** On the ORDER body no lever of any kind moves the score. Its one defect is the position
  of the `D_801ED9D8` store X, and a register lever cannot move a memory op (see (c)).

## (b) Lever sets that reach 0 (all official `--try` = 0)

| levers | plain-C spelling needed | file |
|---|---|---|
| **flags $2 + d $2** | the `e1` read as `((s32 *)arg0)[8]`. Any subset of the other `arg0 + 0x20` / entity reads may be typed too; 8 masks tested, all 0 | **`body.c`** (= `scratch/c51/t1/FD.c`) |
| d $2 + v $3 | `e1` typed + `s32 flags` + `flags |= 0x10;` on its own line | `scratch/c51/alt_DV.c` |
| keepalive v + d $2 | same as the line above | `alt_KD.c` |
| keepalive v + flags $2 | `e1` typed + `flags |= 0x10;` on its own line | `alt_KF.c` |
| keepalive v + v $3 | `e1` typed + `s32 flags` + `flags |= 0x10;` | `alt_KV.c` |
| prev $5 + flags $2 + d $2 (the tree) | none | `scratch/c51/body_pfd_final.c` |
| keepalive v + prev + {d, flags, v $3} | none | `w/a18_PD.c`, `w/a18_PF.c`, `w/a18_PV.c` |

Pairs that do NOT reach 0:
- prev + flags: 5 on F, 7 on T.
- flags + d on F: 6 (prev/e1 swap).
- keepalive + prev: 13; 2 at best over 11,200 spellings. The flags/chain tie in (c)2 is exact.
- prev + d: 13 on F, 15 on T.

## (c) The mechanism: three local-alloc defects in block 8 (the tail)

1. **The abs tie. It needs a lever.** At `(set d (abs:SI v))`, `combine_regs` (`local-alloc.c:1722`) ties d into
   v's quantity because v dies there (`:1854`). abssi2 (`mips.md:1526`) then emits the dest==src arm, a `nop` where the
   target has `move $v0,$v1`. Plain C cannot break it:
   - X and the flags `sh` are ordered by a memory dependence (symbol against register-based,
     `sched.c:817-890`), and both schedulers keep that order.
   - flags and d share $v0, so as local quantities their lives are disjoint and the flags `sh` precedes the abs in
     sched1.
   - So X precedes the abs in sched1, and the abs is v's last use. Only a keepalive, a pin on d or v, or a reused
     (block-global) variable breaks the tie, and the brief forbids the reuse.
   - The c22 ORDER body broke the tie by putting X last. That is an X position the dependence rules out, which is why
     it stops at 4.
   - A pin on d or v breaks the tie but hands the other one a SUGGESTION for the same register (`local-alloc.c:1822`,
     the "SREG a hard register" arm). The suggested-register pass (`:1472`) honours it unless that register is busy
     for the whole life. So pin d alone (25) puts the chain in $2 as well.
   - The flags $2 pin (or a second pin on v) is what makes $2 busy across the chain.
2. **The chain/flags order, when the tie-breaker is a keepalive.** The keepalive adds an 8th ref to the
   `D_801ED9D8` chain (`r105`, `r106`, `v`). In `qty_compare_1` (`local-alloc.c:1598`) the chain then scores
   24/Lc, against 8/Lf for flags.
   - The three leading loads have no predecessors in sched2 (priority 1 each, then the LUID tie-break at
     `sched.c:2427`), so they keep sched1's order. That forces the D load third.
   - The last `lw $v1` needs $v1 free, so the keepalive can sit no later than the second entity `sh`. Lc ≤ 24.
   - The lhu→ior latency forces Lf ≥ 8.
   - 10000 = 10000, and the lower quantity number (the chain, born first) wins. That is why keepalive + prev stops at
     2-13.
   - With a pin as the tie-breaker the chain keeps 7 refs (14/Lc), and flags wins by a wide margin.
3. **prev. This is the one that plain C fixes.** prev (2 refs, `D_801ED9DC` load → `subu`) is the weakest quantity.
   It gets $a1 only if $v0, $v1 and $a0 are all taken during its life, and e1 must outrank it for $a0
   (3/Le > 2/Lp).
   - $v0 is busy when the flags lhu is placed before the `subu` in sched1. That happens when the lhu's destination has
     two sets, because the lhu then loses the birthing boost (`sched.c:2469`, `reg_n_sets == 1`). Two ways:
     - flags pinned to $2, which d's pin also sets;
     - `flags |= 0x10;` on its own line.

     sched2 then restores the target's `subu`, `lhu` order ("insn 120 has a greater potential hazard").
   - **The typed read `e1 = ((s32 *)arg0)[8];`** makes the e1 load `mem/s` (MEM_IN_STRUCT, `expr.c:4568-4577`). The
     anti-dependence on the `D_801ED9DC` store is then dropped: an in-struct varying address against a fixed scalar
     symbol, `sched.c:858-863`.
   - The boosted e1 load is scheduled after that store in sched1. That shortens Le from 16 to 14: 3/14 = **2142**
     against prev's 2/10 = **2000**. e1 takes $a0 and prev takes $a1.
   - Measured in `scratch/c51/dumps_fdt/` (`localalloc_sim.py`, 0 mismatches). sched2 puts the load back before the
     store, because the loads have no predecessors and the store has one.

**Why two is the floor.**
- Defect 1 needs a lever: a keepalive, a pin on d, or a pin on v.
- Pin d alone, or pin v alone, gives the other side a suggestion for the same register. Nothing in plain C holds that
  register across the chain: there is no call or return value in the block to put a hard register live. So the abs
  stays dest==src.
- A keepalive alone creates defect 2, and defect 3 needs flags born before the `subu`: Lf ≥ 10 → 8/10 = 0.8. Beating
  that takes 24/Lc < 0.8, so Lc > 30, i.e. more than 15 instructions between the D load and the keepalive. The block
  has too few.
- So every single lever leaves a defect. Measured: singles best 5 over 5,600 spellings.

## (d) GENERATOR PROPOSAL (one sentence)

When a `qty_compare_1` loss is a pointer load (3 refs) against a short-lived quantity (2 refs) that it outranks only if
its life were 2 shorter, re-spell that pointer load as a typed index (`((T *)base)[k]`). The MEM_IN_STRUCT flag frees
the load from an intervening scalar-global store in sched1 (`sched.c:858`), and the boost births it later. sched2
restores the original order, so the bytes are unchanged and the allocation changes. Pair it with the lever-subset
enumeration: singles → pairs → triples, each crossed with this spelling.

## (e) Measured negatives (fast pre-filter `scratch/c51/fast51.py`; every 0 above re-proven with the official `--try`)

- `search1/2.py`: keepalive + prev × all 85-514 statement orders × 9 spellings. Best 2 (the `e1` load lands after the
  D load).
- `search3.py`: pairs FD, KF, KD, KV, PF, PD × orders × spellings. Best 4-5, all without the typed read.
- `search4.py`: keepalive + prev / keepalive + flags × 64 MEM_IN_STRUCT masks × 4 orders. Best 2 / 14. The typed `e1`
  read does not help keepalive + prev, because its defect is (c)2.
- `search5.py`: every single and pair over 14 levers (10 pins, 4 keepalives) on F and O (364 compiles). Best pair 5.
- `search6.py`: v made block-global by naming block 2's `D_801ED9D8` value `v`, × lever subsets. Best 10.
- `search7.py`: 11,200 compiles = 14 pairs × spellings × masks × orders. 376 zeros, every one with the typed `e1`
  read, over FD, KD, KF, KV and DV. KP best 2, PF 5, PD 12, ED 12, EF 5, EP 7, FV 5, KE 12.
- `search8.py`: every single lever over the same product. Best 5.

## (f) Where the method fell short

1. The pack's ORDER body (4) was a dead end for a minimum-lever search. It fixes defect 1 by moving X, which the
   memory dependence then pins, so no lever of any kind moves it. A minimum-lever pass must start from the TREE's
   order.
2. The winning move was a plain-C spelling that no lever-subset search on the fixed text could find. The MEM_IN_STRUCT
   masks entered only as one axis of a product search, and they are cheap. Lever-minimisation tooling should always
   cross subsets with the typed-index family (generator R-typed-index) before declaring a floor.
3. `localalloc_sim.py` mis-simulates a block that holds a hard-register pin, reporting 2 mismatches on
   keepalive + flags + `|=`. It does not model the pinned $2's live range as an occupant. Trust the dump's
   `;; Register N in M.` lines there.
4. The fast scorer is 2 lower than the official score on the ORDER body (2 vs 4). It is fine as a filter, and every
   claim above is official unless marked "fast".
