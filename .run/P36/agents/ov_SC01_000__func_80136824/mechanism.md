# func_80136824 (ov_SC01_000 exemplar, 125 copies) — T7 agent c50, P36 S103

**Result: score 0, BODY-ONLY, ZERO levers** (no pin, no asm, no volatile, no builtin, no zero term; the prototype
`s32 func_80136824(s32 arg0, s32 arg1, s32 arg2)` and every line outside the definition untouched).
Also 0 on the ov_SC04_011 copy (symbols remapped D_8017F198/19C/1A0/1A4 -> D_801909BC/C0/C4/C8:
`scratch/c50/clean_sc04.c`). The tree has 10 marked levers per copy (4 pins already judged REMOVED, plus pin $12,
pin $5, launder, 2 barriers, keepalive); none is needed.

**This REFUTES S102's reading** ("a real crack needs its prototype widened, types phase"). The prototype crack is real
(re-measured: `s16 arg1` on the definition + the file prototype + the call-site casts, with the same body moves,
scores 0 and the caller func_80135EB0 stays 0 — `scratch/c50/tu_p16.c`), but it is not the ONLY crack. The s16 parameter
only works because it gives the function a HImode copy of arg1 next to a block-local SI copy of `$a1`; a body-local `u16`
copy of arg1 gives the compiler exactly the same two pseudos. The sibling in the same TU, func_801365B8 (lever-free),
is already spelled this way (`a1c = arg1; if (!(arg1 & 1)) … if (a1c & 0x8000) … if ((a1c & 1) != 0)`).

## (a) The residual in one sentence
Lever-free (score 21, COUNT 154 vs 156): arg1 and its copy were ONE pseudo (t4), so the first test read the
long-lived copy instead of `$a1` and wrote `$v0` (target: `move t3,a1; andi a1,a1,1`); the same for arg2/pos
(`move t3,a2; sll v0,t3` vs target `move t4,a2; sll v0,a2`); and the tail computed `pos±2` into one cross-block `$a0`
hoisted into the branch delay slot, with the store at the join (target: `addiu v0,t4,±2` last in each arm, one merged
`sh v0,2(v1)`).

## (b) The passes and decisions
1. **Same-mode copy absorbed by cse** — `a1v = arg1` / `pos = arg2` with `s32` destinations: the copy joins arg1's
   equivalence class, `canon_reg` rewrites the use onto the class's first register and the copy dies
   (`cse.c:7440-7474` special `(set REG0 REG1)` handling; METHOD R20/c4). Dumps (`scratch/c50/b2.lreg.fn`): reg 73
   (arg1) "used 4 times across 65 insns" → global → t3, and the first `andi` reads it.
2. **HImode copy survives** — with `u16 a1v`, the copy is `(set (reg/v:HI 80) (subreg:HI (reg/v:SI 73) 0))`, a
   different-mode value cse cannot fold onto the SI register. When EVERY later use reads the HI copy, arg1's SI pseudo
   is used only in block 0 ("Register 73 used 3 times across 3 insns in block 0", `scratch/c50/clean.lreg.fn`) so
   local-alloc owns it: `block_alloc` (`local-alloc.c:1281-1295` → `combine_regs` `:1722`) takes the hard-register
   preference from `(set (reg 73) (reg:SI 5 a1))` where `$a1` dies → ";; Register 73 in 5", and the `andi` result
   ties into the dying 73 → `andi a1,a1,0x1`. HI 80 is the long-lived copy → t3. Identical allocation to the
   s16-parameter dumps (`scratch/c50/p16.lreg.fn`: SI reg 74 in block 0 in $5, HI 73 long-lived). pos: `u16 pos` gives
   HI 79 = subreg of arg2's SI 74, which keeps `$a2` (read by both `(s16) arg2` extensions) while 79 → t4.
3. **The tail** — the arm-scoped store (`b4b[1] = pos ± 2;` in each arm, not a `var_v0_3` set in both arms and stored
   at the join) keeps `pos±2` an arm-local value computed after the D_801152AA store; the post-reload jump pass
   (`toplev.c:3142`, cross-jump) then merges the two identical `sh v0,2(v1)` tails into the join: `.sched2` has 3
   `mem+2` HI stores, `.jump2` has 2 (`scratch/c50/dumps_clean/`). This is METHOD's c6 use of cross-jump (per-site
   statements merged after allocation).

Proven on bytes: every score in the tables below. Read-only (consistent with the dumps, not separately ablated): the
exact cse site that deletes the SI copy and the combine_regs hard-reg preference path.

## (c) The source moves (all three needed jointly)
1. `s32 a1v` → `u16 a1v`, and the reader swap: the FIRST test reads `arg1`, the two LATER tests read `a1v`
   (lever-free had it the other way round).
2. `s32 pos` → `u16 pos`.
3. Sink the store: `b4b[1] = pos + 2;` / `b4b[1] = pos - 2;` in the arms; `var_v0_3` deleted.

| candidate (scratch/c50/) | score |
|---|---|
| free.c (lever-free start) | 21 COUNT |
| sink.c (3 alone) | 11 REG |
| posu16.c (2 alone) | 14 COUNT |
| j_rev.c (1 alone) | 19 COUNT |
| j_rev_posu16.c (1+2) | 12 COUNT |
| j_rev_sink.c (1+3) | 9 REG |
| sink_posu16.c (2+3) = the engine's R15+R12 best | 2 REG (`andi v0,t3,1` vs `andi a1,a1,1`) |
| sink_posu16_a1u16.c (2+3, u16 a1v but readers NOT swapped) | 2 REG |
| j_clean_poss32.c (1+3) | 9 REG |
| **clean.c = body.c (1+2+3)** | **0** |
| rev_a1s16.c (1 with `s16 a1v`) +2+3 | 0 |

Single-lever table (levers added to the 2-point body sink_posu16.c, i.e. the minimum-lever answer if move 1 were not
known):

| lever set | score |
|---|---|
| pin `a1v` to `$5` only (plain `a1v = arg1`) | 2 (pin alone does nothing: the copy is still folded) |
| launder `a1v` from `arg1` only (unpinned) | 5 COUNT (157 ins) |
| pin `$5` + launder | 0 (two levers) |
| none, move 1 in plain C | **0** |

So the smallest lever set is EMPTY. No lever stands in for the missing parameter: the `u16` local IS the narrow value
the s16 prototype would have carried, written in plain C.

## (d) GENERATOR PROPOSAL
When the target shows `move sK/tK,$aN` at entry and the FIRST use of that argument reads `$aN` itself (with its result
written back into `$aN`) while the candidate reads the copy: introduce `u16 c = argN;` (or re-type an existing copy to
`u16`/`s16`), point the FIRST use at `argN` and every LATER use at `c` — the first use must be the SI parameter's last,
so it is block-local and local-alloc keeps it in `$aN`. Apply to each argument showing the shape (here arg1 and arg2)
jointly, plus R15's sink when the tail diff is a join-point store. R12 (width) + R15 (sink) alone stop at 2 because
neither re-points the readers; the missing generator is "narrow copy + reader split" (first reader = parameter, later
readers = copy).

## (e) What did not work (bytes)
- u16 a1v with the readers left as lever-free had them (first test on a1v, later on arg1): 2 — the SI parameter stays
  long-lived, so the t3 copy is the parameter and the test reads it.
- Pin `$5` alone: 2. Launder alone: 5.
- Any subset of the three moves: 2–19 (table above).

## (f) Where the method fell short
- The pack's `related.txt` carried the answer (func_801365B8's `a1c = arg1; if (!(arg1 & 1))`, func_80136334's
  `u16 a1v`) but S102 read the engine's BANK-REFUSED score 0 via R14 (param width) as "a prototype change is required".
  A score-0 through an out-of-body move proves a crack exists, not that it is the only one; the body-local
  equivalent of a narrowed parameter is a narrowed COPY with the readers split. R14's OUT-OF-BODY verdict should
  trigger this body-local rewrite as its fallback.
- The engine's R12 width move re-types a declaration but never re-routes WHICH name a use reads; here that was the
  whole remaining 2 points.
