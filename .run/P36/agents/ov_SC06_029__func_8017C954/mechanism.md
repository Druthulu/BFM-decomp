# func_8017C954 (ov_SC06_029) — agent e22, P36 S104

**Result: score 0, ZERO levers (the `__asm__ __volatile__ ("" ::: "$3")` "L1 dial" is gone). Levers 1 -> 0.**
Two plain-C edits to body_free.c (1194 = 1194 ins):
1. the box's second use of `wy` (`wy = wz >> 16;`, the high z half) becomes its own local `s16 wq;`;
2. in arm B (case 6/7, PolyFT3) `g.opz = za;` is written inside BOTH branches of the za max-of-3 instead of once after
   the if/else (the spelling the lever-free family members ov_SC03_014 func_8017DF84 :4812 and func_8017FA5C :3410
   already use in the same FT3 arm).
The function's file-level header (L1 dial, L6 "zero sliders") describes the old levers and should be rewritten when
this banks (I did not edit it — outside the body).

## (a) The residual
Lever-free: 632 (COUNT, 1182 vs 1194). The header's diagnosis was right about the symptom: the s16 quad
my/mny/mx/mn slides one slot down reg_alloc_order (v1,a2,a3,t0 instead of a2,a3,t0,t1), which renames ~40% of every
switch arm and changes the spill count (frame 656 vs 664, -12 ins).

## (b) The passes and decisions (all proven on bytes/dumps)
Step 1 — why my/mny take $v1:
- `wy` holds TWO values (`part->yy`, later `wz >> 16`) -> dies in 2 places -> refused by local-alloc
  (`reg_n_deaths == 1`, local-alloc.c:472) -> a GLOBAL allocno. So no LOCAL pseudo in $v1 is live while my/mny are:
  my/mny have no hard conflict with $v1 (`;; 103 conflicts: ... 2 12 29`) and keep a $v1 preference, which
  `prune_preferences` (global.c:834-874) only deletes for a conflicting register; my takes $v1 (find_reg's preference
  pass, global.c:1037-1071) and, via `regs_someone_prefers`, every earlier per-arm HI temp (r277, r360, ...) is pushed
  from $v1 to $a0 — the cascade (r277 identical conflicts in both compiles, different register: a0 vs v1).
- With `wq` its own variable, `wy` is single-value -> local ($v1), and `wq` is local too. Its WIDTH is what matters:
  as `s16` the shift is `(set (subreg:SI (reg:HI wq) 0) (lshiftrt ...))` — a SUBREG destination, so
  `birthing_insn_p` (sched.c:2469-2490) fails and sched1 keeps the shift early (right after `my = wy >> 16`), while
  the `box[].vz = wz` stores still follow: `wz` stays live, `wq` cannot tie to it, local-alloc gives `wq` $v1 for a
  stretch where all four of my/mny/mx/mn are live -> each gets a HARD conflict with $v1 (`;; 104..107 conflicts:
  2 3 12 29`) -> the quad lands on a2/a3/t0/t1, exactly the tree's asm clobber, but for a real reason.
  As `u32 wq` the set is a REG, gets the birthing boost, is scheduled after the wz stores, ties to wz's $v0 and the
  conflict never appears (gen_box.py: 459; s16/u16: 28).
Step 2 — the last 28 (header L6: the 3-cycle {vtx, &g.flag, 0x7F85E000} and the {&g.sz1, &g.sz2} swap):
- Every loop-invariant allocno's live length (recomputed by sched1, sched.c:4911-4947) was exactly ONE insn shorter
  than with the tree's zero-byte asm: &g.sz{1,2,3} 967/968/969 -> `allocno_compare` (global.c:594-607)
  floor(640000/L) = 661/661/660 — a TIE, broken by allocno number the wrong way (tree: 968/969/970 -> 661/660/659);
  same for &g.flag vs the constant (390000/L).
- A diagnostic `__asm__("")` probe (not delivered) at each of 267 statement positions gave 0 at 138 of them: ANY
  one zero-byte insn inside the outer loop is the whole residual.
- The plain-C source of that insn: `g.opz = za;` duplicated into both branches is TWO stores through allocation
  (9 `sw ...,232(sp)` in `.greg`) and ONE in the bytes (8 in `.jump2`/`.dbr`/objdump): the post-reload jump pass's
  cross-jump (`find_cross_jump`, jump.c:2371, run from toplev.c after reload) merges the identical tails, so the bytes
  are unchanged and every live range through arm B is one insn longer. Duplicating it in arms A AND B is +2 -> 115;
  either arm alone -> 0; arm B chosen because the family's lever-free members spell arm B that way.
  (Found by running the R2-R41 recipe families (`tools/delever.py recipe_candidates`, read-only import) over the
  28-body: 1,655 candidates, exactly two at 0 — R39 dup-join in arm A and in arm B.)

## (c) The moves
1. `s16 wq; ... wq = wz >> 16; box[2/3/6/7].vz = wq;` (632 -> 28)
2. arm B: `if (g.sz0 > g.sz1) { za = g.sz0; if (za < g.sz2) za = g.sz2; g.opz = za; } else { ...; g.opz = za; }`
   (28 -> 0)
Both single-step scores are better than the start; neither alone closes.

## (d) Generator proposals
- R-WIDTH-SPLIT: when a local is assigned twice (two unrelated values, "dies in 2 places" in `.lreg`) and one value
  is a narrowing `x >> 16` / truncation stored to 16-bit fields, split that value into its own local AT THE FIELD
  WIDTH (s16/u16): the SUBREG destination removes sched1's birthing boost, keeping the definition where the reused
  variable had it (a u32 split is a different schedule).
- R39 dup-join as a LIVE-LENGTH dial: when a register residual is a permutation among long-lived loop invariants whose
  `alloc_table` priorities TIE (or sit 1 apart), and a zero-byte `asm("")` probe anywhere in the loop closes it, try
  R39 (duplicate a join-point store into both arms) — cross-jump removes the copy post-reload, so it is +1 live length
  at zero bytes. Tooling: an `asm("")` position probe is a cheap oracle for "is the residual a live-length off-by-one".

## (e) Tried and failed (bytes)
- per-arm / per-box scoping of my/mny/mx/mn (64 variants, gen_scope.py): best 503.
- wq as u32 in 36 placements/store orders/assignment orders (gen_box.py): best 459 (my first, `my = wy >> 16;`).
- wq s16/u16: 28 in every placement tried; comparison operand flips on all 84 ifs (gen_flip.py): all 28 (the front
  end canonicalises them).
- dup-join in arms A and B together: 115.
- The earlier `$3` dial and the header's "six natural spellings" are superseded; the header's L2-L5 moves are already
  in body_free and stay.

## (f) Where the method fell short
- The regen sweep (s104_all) was run on the 632 body; its best (581) never met R39 because the dial's residual hid
  behind the big slide. Re-running the generator families AFTER a structural fix found the finisher in one pass —
  the sweep should be re-run on every agent's improved body, not only the free one.
- alloc_table.py prints preferences only after pruning; the $v1 preference that drove the slide was invisible in the
  tree's dump (pruned by the clobber's conflict). A "preferences before prune" column would have shown it.
- Sibling ov_SC06_000 func_8017EF68 (same family, one launder on `wq`): `s16 wq` there scores 14 = its lever-free
  score (scratch/sib/) — a different residual (a sched order), not closed by this text.

Scratch kept (scratch/c/keep/): dupjoin_armB.c (= body.c before the comment clean-up), dupjoin_armA.c (also 0),
dupjoin_AB_115.c, wq_s16_28.c, wq_u32_459.c; generators gen_box.py / gen_box2.py / gen_scope.py / gen_flip.py /
regen.py; dump helpers quick.sh, annot.py (RTL with each pseudo's local/global hard reg), regmap.py, live.py.

## (g) Structs
Not the channel here: the decisions are local-alloc eligibility (a reused variable), sched1's birthing rule (the
declared width of a local), and a post-reload cross-jump. The Part/Prim/POLY_* accesses already go through struct
types; turning `g` into a named struct or `tmpxy` into DVECTOR changes nothing these passes look at.
