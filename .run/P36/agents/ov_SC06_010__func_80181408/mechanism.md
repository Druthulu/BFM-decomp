# func_80181408 (ov_SC06_010, def name aF8017EF54) — P36 S104 d34 — CLOSED at 0, zero levers

Score: 26 (body_free.c) -> 2 (declaration alias) -> 6 (structured, frame only) -> **0**. Lever count 2 NEEDED
(pin $4 + `"memory"` barrier) + 3 REMOVED pins + 1 unmarked dead `pad2[2]` -> **0** (no pin, no asm statement, no
volatile, no pad, no do-while). The one non-trivial construct left is the body-local DECLARATION alias
`extern u8 D_800AF648_b __asm__("D_800AF648");` (METHOD step 3's allowed alias — the same spelling this TU's already-banked
siblings use at lines 7029/8041/8579/8686/8783/8980/9187). Copies: all 6 other copies close with the same text
(scratch/copies.md), plus a bonus same-TU sibling func_8017F278.

## (a) The residual in one sentence
Two independent defects: (1) the second `&D_800AF648` call argument was served from a callee-saved register (`s1`
holding the param, `s0` the address: frame 64, two extra saves) where the target re-materialises `lui/addiu a0` per call;
(2) the tail `move a0,s0` was hoisted above `sh v0,132(s0)` and the store then addressed through `a0`.

## (b) The passes and decisions (file:line read; each proven on bytes with dumps under scratch/dumps_a1, dumps_a7n)
1. **cse merges the two address loads.** Both `&D_800AF648` expand to `(set (reg P) (symbol_ref "D_800AF648"))`
   (scratch/dumps_a3 .rtl insns 56/63); cse hashes a SYMBOL_REF by its NAME POINTER (`cse.c:1937-1939`) and
   `exp_equiv_p` compares it by pointer (`cse.c:2107-2108`), so the second load becomes a copy of the first pseudo,
   which lives across the call -> `$s0`. A body-local `extern ... __asm__("D_800AF648")` has a different name string
   pointer, so the two loads never share a class. (Proven: a1 = body_free + alias only: 26 -> 2.) Even a trivial lever-free
   body (func_8012E32C in ov_SC06_008) keeps the address in `$s0`, so no ordinary spelling of the same symbol twice avoids it.
2. **The tail order is a BLOCK boundary, not a scheduling barrier.** In the goto text the join label precedes the
   `0x84` store, so store + tail are one block; sched1 hoists the call-argument copy `(set a0 (reg param))` (insn 246)
   above the store (dumps_a1 .sched), then local-alloc's `optimize_reg_copy_1` (`local-alloc.c:700`, called at `:1007`)
   rewrites every later use of the dying param as `a0` — including the store (dumps_a1 .lreg insn 225). The target's
   order comes from a store written IN EACH ARM of an if/else: the join label then sits between the store and the tail
   (sched cannot cross it), and the post-reload jump pass (`toplev.c:3142`, `jump_optimize(insns,1,1,0)`;
   `find_cross_jump` `jump.c:1941`/`:2371`) merges the two identical `sh v0,132(s0)` into one (dumps_a7n: 2 stores
   in .greg, 1 in .jump2). The `"memory"` barrier was faking that label.
3. **The `move v1,v0` copy and the 8 extra frame bytes both come from `(*(s16 *)(a0 + 0x84))--`.** The test
   `*(s16 *)(a0+0x84) == 0` loads a HImode pseudo r75 and sign-extends it (r77 = r75<<16, r76 = r77>>16); the else-arm
   decrement reads the same lvalue and cse forwards r75 (no store between). combine's 3-insn combine (i1 = the load,
   `added_sets_1` because r75 is still used in the else arm, `combine.c:1460-1462`) yields `lh` into r76 plus the kept
   copy `(set (reg:HI 75) (subreg:HI (reg:SI 76) 0))` — the delay-slot `move v1,v0` (r76 dies at the branch -> v0,
   r75 lives into the arm -> v1). The eliminated shift temp r77's death note finds no insn and combine plants
   `(use (reg:SI 77))` at the label (`combine.c:10831-10845`, dumps_a7n .combine insn 222); r77 then has a reference but
   no set, gets no hard register (.greg: "77 conflicts:" empty, no disposition) and reload gives it a stack slot at
   sp+40 -> frame 56 = the target. The tree's `v1 = old;` copy and its dead `pad2[2]` were faking exactly these two
   artefacts. (Proven: a2n = structured + `old`/`v1` + no pad scores 6, frame 48; a7n = `--` + no pad scores 0.)

## (c) The moves that closed it (each one line)
- the second call takes `&D_800AF648_b`, a body-local `extern u8 D_800AF648_b __asm__("D_800AF648");` (26 -> 2);
- the goto chain -> structured `if (*(s16 *)(a0 + 0x84) == 0) { ...; store 0xA; } else { decrement; }` with the flag/X/Y
  gates as one `&&` condition, the store written in each arm (removes the barrier);
- the decrement written as `(*(s16 *)(a0 + 0x84))--;` directly on the lvalue (removes `old`, `v1`, `cool` and the pad);
- readability only (all still 0): `+= 0x280` / `-= 0x280`, `(sx < 0) ? -sx : sx`, `(u16)(L.sxy[0] + 0xEF) < 0x1DF`,
  the tail through `a0` (no `p` copy). One tidy that did NOT hold: folding `sx << 8` into the call argument (18).

## (d) GENERATOR PROPOSAL
When a body reads `old = *(s16 *)(P + K); v1 = old; if (old != 0) goto L_dec; ... cool = C; goto L_join; L_dec: cool =
v1 - 1; L_join: *(s16 *)(P + K) = cool; [barrier]` — emit the structured
`if (*(s16 *)(P + K) == 0) { ...; *(s16 *)(P + K) = C; } else { (*(s16 *)(P + K))--; }`, deleting the copy variable,
the barrier AND any dead `pad` array (then re-add a pad only if the frame is still short — the `--` spelling brings its
own 8-byte dead slot); and whenever the same `&SYM` is passed to two calls and the target re-materialises it, add the
`SYM_b __asm__("SYM")` alias to the second.

## (e) What did not work (byte evidence)
- the structured body keeping `old`/`v1` AND the dead `pad2[2]` (a2): 0 — but that keeps two fakes (the decompiler's copy
  variable and a dead array sizing the frame); with the pad removed it scores 6 (frame 48): the copy then comes from `v1`
  but the dead slot does not. Conversely the `--` form WITH the pad scores 6 (frame 64);
- the structured body with a plain `old` (s32) and no `v1`: 7 (COUNT; reorg steals `addiu v0,v0,-1` into the bnez slot —
  the header's lever-1 observation, still true for an SImode `old`);
- `s16 old` + no pad: 0 as well (a5n) — equivalent to the `--` form (the HImode copy is the point); the `--` form is kept as
  the most natural;
- `old--; store old;` (a8): 7;
- the goto body with the alias only (a1): 2 — the tail order needs the block boundary.

## (f) Where the method fell short / what helped
- METHOD 14's "try the structured spelling EARLY" was the whole close; the generators could not reach it (every R-family
  mutates the goto text). The second half (the `--` spelling) is a WIDTH move in disguise (METHOD 3 S103 c4: a HImode
  destination keeps a copy) — it is reached only by deleting the decompiler's SImode `old`.
- `residual.txt` classed it COUNT/"s1->s0 x3"; the real defect was a register-held constant address (a missing
  instruction pair + an extra callee-saved register), visible only in the whole objdump.
- The header's MATCH-lever notes (lever 1 = `v1` pin, lever 3 = `pad2`) were CLAIMS about the goto shape; both are
  artefacts of one decrement spelling. A dead pad sizing the frame should be re-checked against `.greg` for a
  no-disposition pseudo whenever the body text changes.

## (g) Structs answer
No struct was needed to close this body. The one remaining non-plain construct is the name alias for the second address;
a struct type on D_800AF648 (MATRIX-like) cannot remove it, since cse keys on the symbol NAME (`cse.c:1937`, `:2107`), not
the type. A structs-phase lead: D_800AF630 (6019 refs), D_800AF634, D_800AF638 and D_800AF648 cluster within 0x18 bytes, so
the original may have passed `&view.matrix` (a `(const (plus (symbol_ref D_800AF630) 0x18))`) to one call and the bare
symbol to the other — two different rtx that cse keeps apart. That would reproduce the linked bytes but NOT this object's
relocations (`addiu a0,a0,24` against D_800AF630 vs `addiu a0,a0,0` against D_800AF648), so it is untestable under the
object-level scorer; the alias is the object-exact spelling. Giving `a0` an entity struct (fields 0x0 u16 active, 0x20
parent ptr, 0x84 s16 cooldown, 0xFC/0xFE u16 accumulators) is pure readability here — the decisions above do not depend on
aggregate-vs-scalar marking (no `expr.c:4568` channel involved). No signature change.
