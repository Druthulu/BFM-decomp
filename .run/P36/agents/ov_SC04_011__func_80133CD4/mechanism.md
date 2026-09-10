# ov_SC04_011 / func_80133CD4 — the `lh` instruction site (line 2705)

Status: best score **11** (from 28); the instruction count is exact (399/399) and instructions 0..233 and
291..398 are byte-identical. The residual is a three-way register permutation in ONE basic block.

## (a) The residual in one sentence
The lever-free body was missing an instruction (398 vs 399): the hand-placed `lh %0, 2(%2)` reload of
`pb0[1]` had no C spelling because gcc's CSE forwards the value just stored to `pb0[1]` into the later
signed-halfword read, and the whole 28-point residual (seven branch displacements + one register
permutation) was that one absent load.

## (b) The passes and the decisions, read from the pinned cc1's own source

1. **cse.c — store-to-load forwarding, and what invalidates it.** After `pb0[1] += …` emits
   `sh <val>,2(pb0)`, CSE records the value of `(mem:HI (plus pb0 2))`, so a following
   `(sign_extend (mem:HI (plus pb0 2)))` is replaced by the stored pseudo and combine folds
   `sign_extend(subreg:HI r) << 16` into `r << 16` — no `lh` at all. The read of `pb0[0]` survives as a
   real `lh` only because the *later* store to `2(pb0)` invalidated the `0(pb0)` entry.
   **The move:** put the `pb0[2] += …` store LAST before the reads. Its store to `4(pb0)` invalidates
   both `0(pb0)` and `2(pb0)`, so BOTH halfword reads become real `lh`s, and `s2a`'s read of `pb0[2]`
   is the one CSE now forwards — which is exactly what the target does (`sll s2,<stored>,0x10`).
   PROVEN: 398 → 399 instructions, the second `lh` appears.

2. **sched.c — the load-delay slot.** With two separate temps the two `lh`s are independent and sched2
   hoists the second into the first's delay slot (399 → 398, the target's `nop` at [282] disappears).
   Writing both loads into ONE reused local `h` creates the anti-dependence that forces the `nop`.
   PROVEN: score 29 → 21, count exact.

3. **local-alloc.c `qty_compare` (`local-alloc.c:1578-1595`) + `find_free_reg` (`local-alloc.c:2073`,
   no `REG_ALLOC_ORDER` on MIPS so the lowest-numbered free hard reg wins) + flow.c's loop-depth
   weighting of `REG_N_REFS`.** The `pb0` pointer is a block-local quantity; its priority
   `floor_log2(refs)*refs*size/(death-birth)` was 13500 (refs 9, live 20), the highest allocatable one
   in the block, so it took the lowest free register `v1` — while the target holds it in `a0`.
   Wrapping the MIDDLE update in `do { … } while (0)` raises the loop depth of that statement, so flow
   counts its references twice: the quantities of the wrapped statement go 2→4 refs (priority ×2) and
   `pb0` goes 9→11 refs (16500). Three quantities now outrank `pb0` and take `v0`/`v1` first, and
   `pb0` falls to **a0** — the target's register.
   PROVEN: score 21 → 11, instructions [234..278] now byte-identical.
   Measured with the `.lreg` dump (`local-alloc`'s own "Register N used M times across L insns" lines,
   `PACK/qty.py`): before, `r203 pri=13500 refs=9 live=20 -> v1`; after, `r203 pri=16500 refs=11 live=20 -> a0`.

## (c) The source moves that closed it (each one line)
1. `pb0[2] += s1var * pc0[2] / s0var;` moved BEFORE the halfword reads (the `q3v` temp deleted) — the
   third store invalidates CSE's entries for `0(pb0)` and `2(pb0)`. 28 → 29→21.
2. The two halfword reads share ONE reused local `s32 h` — the anti-dependence keeps the load-delay `nop`. → 21.
3. The middle update wrapped in `do { … } while (0)` — the loop-depth ref weight reorders local-alloc. 21 → **11**.

## (d) GENERATOR PROPOSAL
**When the residual is COUNT with one missing load and a store to the same object at a nearby constant
offset precedes it, move the statement that stores the HIGHEST offset of that object to just before the
reads (and inline its temp): CSE's `invalidate` then kills the lower-offset entries and the reads become
real loads.**  Companion rule for the register half: **when the residual is REG-caller and the `.lreg`
priority table shows one long-lived pointer quantity outranking every short one, wrap ONE statement that
references it in `do { … } while (0)` — flow's loop-depth weight doubles that statement's `REG_N_REFS`
and demotes the pointer in `qty_compare`.**  (A tool can compute this without compiling: parse the
`.lreg` "used N times across M insns" lines, rank by `floor_log2(N)*N/M`, and try the wrap on each
statement that references the top-ranked pointer.)

## (e) What did NOT work, with byte evidence
- `s1var = ((s16*)pb0)[0] << 16; s0var = ((s16*)pb0)[1] << 16;` (no shared temp): 398 ins, the `nop` is
  filled by the hoisted second `lh`. Score 29.
- Reading through an `s16 *hp = (s16 *)pb0;` alias: score 21, identical residual — CSE copy-propagates
  `hp` away, so no second pseudo is created (`combine_regs` never sees a copy).
- `D_801909C0[k] += …` with no local pointer: 402 ins — the stores invalidate the global's own memory,
  so the pointer is re-loaded (`lui`/`lw`).
- A second `pb0 = D_801909C0;` before the reads: 402 ins, same reason.
- Declaration-order permutations of `pc0`/`pc4`/`pb0`, a separate divisor local, `h` hoisted to block
  scope, `s2a` spelled `((s16*)pb0)[2] << 16` or read through `h`: all score 21 — the priority table is
  unchanged by any of them.
- Wrapping the FIRST or THIRD update in `do{}while(0)` instead of the middle one: 34 / 35 (count breaks).
- Two separate temps `h0`/`h1` on top of the score-11 body: 398 ins (score 18) — the `nop` is lost again.

## (f) Where the method fell short
The residual text alone could not distinguish "an instruction is missing" from "the registers are wrong":
the seven `bgez/bnez/j` displacement mismatches were downstream of ONE absent `lh`, and the register-pair
histogram (`v1->a0 x8` …) invited a register lever when the real defect was a CSE invalidation. What
closed it was reading the compiler's own allocation table out of the `.lreg` dump (`PACK/qty.py`) —
priority, refs, live length and the assigned hard register per pseudo — and comparing it against the
target's registers. That instrument should be part of the engine: for a REG-class residual it names the
exact quantity to demote and by how much, instead of leaving the search to guess among 254 candidates.

---

## Addendum — the last 11 points, and why the search stopped there

After the three moves the residual is ONE region (instructions 279-290) and one decision: the shared temp
`h` sits in **a1**, the target has it in **v0** (with the `pb0[2]` load in v1 and the third quotient in a1).

**Why `h` cannot be steered from the source, read out of the compiler.** `h` is set twice, so
`reg_n_deaths[h] == 2` and `local-alloc.c:472` (`if (reg_basic_block[i] >= 0 && reg_n_deaths[i] == 1`)
refuses it a local quantity — it is a GLOBAL allocno, allocated in `global.c` only after every local one.
The `.greg` dump states the outcome directly: `;; 244 conflicts: 74 77 83 91 201 244 2 3 4 29` — hard
regs 2 (`v0`), 3 (`v1`) and 4 (`a0`) are already taken over its range by locals (`pb0` in a0, the
`pb0[2]` load in v0, the third quotient in v1), so `find_reg` hands it a1.
For `h` to get v0, the two locals that overlap it (`(reg:HI 241)`, the `lhu 4(pb0)` value, priority 3333;
and `(reg:SI 239)`, the third quotient, 2857) must both avoid v0 — but in the target the ONLY thing
holding v0 across their ranges is `h` itself, which is allocated after them. That is self-referential
unless `h` is LOCAL in the target, i.e. set once.

**And it cannot be set once.** With two temps (`h0`, `h1`) `h` becomes local and the third quotient
already lands on the target's a1 (measured: `r244 pri=10000 -> v0`, `r239 -> a1`) — but sched1 then has
no anti-dependence between the two loads and hoists `lh 2(pb0)` into the first load's delay slot, so the
target's `nop` at [282] disappears and the count drops to 398 (score 18). One temp buys the `nop` and
costs the register; two temps buy the register and cost the `nop`. Both were measured.

So the last 11 points need something that changes which local holds v0 across [the two `lh`s], and no
spelling reachable from this source shape does it. What is still untried and would be the next step: a
change EARLIER in the block (the `pw` store block, the `gte_stlvnl` operand, the `pc4` sum) that alters
the pre-reload SCHEDULE so the `lhu 4(pb0)` is no longer scheduled BETWEEN the two `lh`s — with it out
of `h`'s live range, `h`'s conflict set loses hard reg 2 and `find_reg` gives it v0.

**Search effort behind that verdict:** 1,304 compiles of the engine's own generators (beam depth 2,
width 4, all 16 families) from the score-11 body found nothing below 11, and ~90 hand candidates
(statement interleavings, temp widths `s16`/`u16`/`u32`, `register`, pointer aliases, named quotient and
sum temps, the global used directly, `do{}while(0)` on every other statement) all returned 11 or worse.

## The readability caveat
Move 3 is `do { pb0[1] += …; } while (0);` — ordinary C, and R7 ("a statement wrapped in a block") is one
of the engine's own byte-neutral recipes, but it reads as a macro expansion, and it is asymmetric (only
the MIDDLE of three sibling statements). It is worth 10 points (21 → 11) and it is the only thing that
puts `pb0` in the target's `a0`. `PACK/body_readable_21.c` is the same body WITHOUT it — fully natural C,
score 21, count exact — if the coordinator prefers the readable text over the closer one.

## The files
- `PACK/body.c` — the score-11 body (the three moves).
- `PACK/body_readable_21.c` — the score-21 body (moves 1 and 2 only; no `do{}while(0)`).
- `PACK/qty.py` — the instrument: cc1 pass dumps for a candidate body + local-alloc's quantity table
  (priority, refs, live length, assigned hard register) for the function. This is the piece the engine
  is missing.
- `PACK/beam.py` — a tree-free beam search seeded from a candidate body (never writes `src/`).
- `PACK/dump.sh` — side-by-side mine/target instruction listing.
