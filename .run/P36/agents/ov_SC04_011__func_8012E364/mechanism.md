# func_8012E364 (src/ov_SC04_011/ov_SC04_011_jr_8012ACE0.c) — T7 agent c51, MINIMUM-LEVER pass

**Final score 0 (MATCH, 67/67) with THREE levers** — the tree's own three pins (`prev` $5, `flags` $2, `d` $2) on the
tree's statement order (`body_free.c`). No single lever and no pair of levers reaches 0; the reading below proves why
for every pair that gets close. The earlier agents' files are kept: `scratch/c22_body.c` (the score-4 ORDER body),
`scratch/c22_mechanism.md`, `scratch/prev_mechanism.md`. All my probes are under `scratch/c51/`.

(The tree's fourth marked site, the `arg0` $6 pin, was already REMOVED by the byte oracle — `sites.txt` — and it
changes nothing on either base; see the table.)

## (a) Single-lever table (official `--try`, 67/67 ins unless noted)

| lever (one only) | on `body_free.c` (tree order, 25) | on the c22 ORDER body (4) |
|---|---|---|
| none | 25 | 4 |
| pin `prev` $5 (tree) | **13** | 4 |
| pin `flags` $2 (tree) | 19 | 4 |
| pin `d` $2 (tree) | 25 | 4 |
| pin `arg0` $6 (tree, oracle-REMOVED) | 19 | 4 |
| pin `v` $3 | 19 | 4 (fast) |
| pin `e1` $4 | 25 | 4 (fast) |
| pin `e2` $4 | 23 | 4 (fast) |
| pin `spd` $7 | 23 | 4 (fast) |
| pin `a` $4 | 26 | — |
| pin `diff` $2 | 25 | 4 (fast) |
| keepalive `v` after the second entity `sh` (`__asm__ __volatile__("" : : "r"(v))`) | 26 (the abs `move` arm appears; every other register permuted) | 4 (fast) |
| keepalive `v`, non-volatile | 25 (sched1 hoists it above the abs; no effect) | — |
| keepalive `v` at the function end | 17, 68 ins (reorg cannot fill the `jr` slot across a volatile asm) | — |
| keepalive `prev` after the `v =` line | 22 | — |
| keepalive `e1` after the second entity `sh` | 25 | — |
| keepalive `flags` after its load | 27, 68 ins | — |

**No single lever reaches 0 from either plain body.** On the ORDER body no lever of any kind moves the score. Its one
defect is where the `D_801ED9D8` store X sits, and a register lever cannot move a memory op (see (c)).

## (b) Pairs and triples (official `--try` unless marked fast)

| levers | score | what is left |
|---|---|---|
| prev + flags + d (the tree) | **0** | — |
| keepalive v + prev + d | **0** | — |
| keepalive v + prev + flags | **0** | — |
| keepalive v + prev + pin v $3 | **0** | — |
| prev + flags | 5 | d tied into v: abssi2 `nop` arm |
| flags + d | 6 | prev/e1 swap $a0/$a1 |
| keepalive v + prev | 13; **2** with `v =` moved above `e1 =` (`scratch/c51/s2_b.c`, ORDER); **2** with the keepalive after a split-out last pointer load (`w/e3_P.c`) | 13: flags and the chain swap $v0/$v1. s2_b: registers all right, but the `e1` load lands after the D load. e3_P: the last pointer takes $a0, because v is still live in $v1 |
| keepalive v + flags | 15; 6 with `flags |= 0x10;` on its own line (`kf_or2.c`) | 15: prev takes $v0. 6: the prev/e1 swap $a0/$a1 |
| keepalive v + d | 15 | prev takes $v0 |
| prev + d | 13 | the chain takes d's $2 through a suggestion |
| every pair of {pins of arg0/prev/flags/v/d/e1/e2/spd/a/diff, keepalive v/prev/e1/flags}, on both bases (`search5.py`, 364 fast compiles) | best 5 | — |
| 14 lever pairs × 3 flags spellings × 2 widths × 3 `v` spellings × 16 MEM_IN_STRUCT masks × 4 load orders (`search7.py`, 11,200 fast compiles) | see (e) | — |

## (c) The mechanism: three independent defects, and each lever fixes exactly one

Plain C in the tree's order (`body_free.c`, 25) has three separate local-alloc defects in block 8, the tail.

1. **The abs tie.** At `(set d (abs:SI v))`, `combine_regs` (`local-alloc.c:1722`) ties d into v's quantity because v
   dies there (`:1854` needs a `REG_DEAD`). abssi2 (`mips.md:1526`) then emits the dest==src arm (`nop`) where the
   target has `move $v0,$v1`. **The tie cannot be broken in plain C here, by a two-pass argument:**
   - X and the flags `sh` are ordered by a memory dependence (a symbol against a register-based address,
     `memrefs_conflict_p`, `sched.c:614`). Both schedulers keep that order, so the target's X-before-flags-`sh` holds in
     sched1 as well as in sched2.
   - flags and d share $v0 in the target. As local quantities their lives must not overlap, so in sched1 the flags `sh`
     comes before the abs.
   - So in sched1, X comes before the abs, and the abs is v's last use. Something must keep v alive past the abs (a
     keepalive), or make one of v/d a hard register (a pin), or make one of them block-global. Block-global would take
     a reused variable, which the brief forbids.
   - The earlier agents' score-4 body breaks the tie by putting X last. That is exactly the X position the dependence
     argument rules out, which is why no lever moves that body off 4.
2. **The chain/flags order.** Once the tie is broken, the `D_801ED9D8` chain (`r105`, `r106`, `v`) and flags compete
   for $v0 in `qty_compare_1` (`local-alloc.c:1598`; priority = `floor_log2(refs)·refs/(death−birth)`).
   - With a keepalive, the chain has 8 refs: 24/Lc. flags has 4 refs: 8/Lf.
   - The sched1 order is fixed. The three loads have no predecessors in sched2, so they keep sched1's order
     (priority 1 each, then the LUID tie-break at `sched.c:2427`). That forces the D load third, and the keepalive can
     sit no later than the second entity `sh`, because the last `lw $v1` needs $v1 free. So Lc ≤ 24.
   - The lhu→ior latency ("blocking insn 120 for 1 cycles") forces Lf ≥ 8.
   - The best case is therefore 10000 = 10000, and the tie goes to the lower quantity number, the chain (born first).
     The chain takes $v0 (a18_P: 13).
   - Without a keepalive the chain has 7 refs (14/Lc) and flags wins easily. So the keepalive, the only lever-light way
     to break defect 1, is what creates defect 2.
3. **prev.** prev (2 refs, D_801ED9DC load → `subu`) is the lowest-priority quantity. It gets $a1 only if $v0, $v1 and
   $a0 are all taken during its life.
   - With the target's final order, $v0 (flags) is born after prev dies, so prev takes $v0 (a18_F, a18_D: 15).
   - When flags is a hard $2 with two sets, the lhu loses sched1's birthing boost (`sched.c:2469`, `reg_n_sets == 1`).
     Examples: `flags |= 0x10;` spelled on its own line, or d also pinned to $2. sched1 then places the lhu before the
     `subu`, and sched2 restores the target order ("insn 120 has a greater potential hazard"). $v0 is then busy.
   - prev then competes with e1 for $a0: 2/Lp = 2/10 against 3/Le = 3/16. prev wins and takes $a0 (FD, K+F+`|=`: 5-6).
   - e1 would win only with Le ≤ 14. That needs the flags `ori` placed before X in sched1, but `ori` has priority 3
     (after a load) against X's 2, and the backward list scheduler puts it after X. Or it needs the `e1` load after the
     D load, which sched2 keeps (see 2).

Each tree lever removes one defect:

| lever | defect | pass / decision |
|---|---|---|
| `d` $2 | 1 | a hard-reg SREG is never tied; v gets a $2 *suggestion* instead (`local-alloc.c:1822`) |
| `flags` $2 | the suggestion d's pin creates, and 2 | $2 is held across the chain's life, so the suggested-register pass (`:1472`) refuses the chain $2 and it takes $3 |
| `prev` $5 | 3 | prev leaves local-alloc's ranking altogether |

- prev + flags (5) leaves defect 1.
- flags + d (6) leaves defect 3.
- prev + d (13): the chain takes d's $2 through the suggestion.
- The keepalive sets are three levers too: keepalive + prev, plus d, flags or pin v, each 0.

**The floor is three.** No lever covers two of the three defects.
- The keepalive breaks defect 1 but creates defect 2.
- The flags pin needs d's pin to be useful.
- The prev pin touches only prev.

## (d) GENERATOR PROPOSAL (one sentence)

For a MINIMUM-LEVER pass, enumerate lever subsets bottom-up (singles, then pairs, then triples) on BOTH the lever-free
body and the best plain body. For each pair that comes within a handful, run the `localalloc_sim.py` table on its
dump and check whether the leftover is a `qty_compare_1` tie or an inequality that the sched1 order provably cannot
satisfy. If it is, stop: the subset floor is proved. This takes arithmetic, not a search.

## (e) The product search (`scratch/c51/search7.py`)

(filled in below when it finishes)

## (f) Where the method fell short

1. The pack's ORDER body (4) was a dead end for a minimum-lever search. It fixes defect 1 by moving X, which the
   memory dependence then pins, so no lever of any kind moves it. A minimum-lever pass must start from the TREE's
   order, not from the best plain body.
2. `localalloc_sim.py` mis-simulates a block that holds a hard-register pin, reporting 2 mismatches on K+F+`|=`. The
   pinned $2's live range is not modelled as an occupant, so prev appears to get $v0. Trust the dump's
   `;; Register N in M.` lines there.
3. The fast scorer (`scratch/c51/fast51.py`, cpp+cc1 text compare against the tree body) is 2 lower than the official
   score on the ORDER body (2 vs 4). It is fine as a filter, but every claim above is official unless marked "fast".
