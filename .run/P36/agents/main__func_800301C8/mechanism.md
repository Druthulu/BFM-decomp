# func_800301C8 (src/800_b_2.c) — S104 agent e23 — at 0 with ONE marked lever (2 levers -> 1); zero-lever close PARKED (identical only after linking)

## (a) The residual
Score 25, COUNT 168 vs 170, two independent defects:
1. (the tree's launder on `e`) the target copies `entry` out of `$s2` (`move v0,s2`) and stores the copy
   (`sh v0,0(s0)` to D_800A46D0, `sh v0` to D_800A4640+k2), reusing `$s2` for the constant 1; mine stores straight from
   `$s2` — one `move` missing.
2. (the tree's barrier) in the `h != D_80064D4A[…]` arm the target keeps the source order `lh n; nop; sll; sh -1 ->
   D_800C532A[n]; sh 0 -> D_800A4644[k]; sh 0 -> D_800A4648[k]` with the load-delay `nop` unfilled; mine fills it with
   the two zero stores and sinks the D_800C532A store to the end.

## (b) The passes and the decisions
1. PROVEN on bytes: the S103 c4 width rule. `s32 e = entry;` is an SImode reg-reg copy that cse's `(set REG0 REG1)`
   case folds away (cse.c:7440-7474); with `s16 e` the copy is a HImode SUBREG move (no PROMOTE_MODE on MIPS) and
   survives — the target's `move v0,s2`.
2. PROVEN on the `.sched` dump (scratch/n1.sched.fn) and on bytes: sched1 dependence analysis + priority.
   - `memrefs_conflict_p` (sched.c) disambiguates `(plus (reg) (symbol_ref A))` from `(plus (reg') (symbol_ref B))` by
     `find_symbolic_term` (distinct symbols -> no conflict), so the three stores are mutually INDEPENDENT.
   - `priority()` (sched.c, the LOG_LINKS path from the block start): the D_800C532A store sits behind the load (cost 2)
     and the `sll`, priority 2; the zero stores have priority 1 (`;; insn[115]: priority = 2`, `[120]`/`[125]` = 1). The
     backward list scheduler places the highest-priority ready insn LAST (`rank_for_schedule`), so the D_800C532A store
     sinks below both zero stores.
   - The target's order means the zero stores DID depend on the D_800C532A store: `find_symbolic_term` returns 0 for a
     `CONST` operand (`GET_RTX_CLASS (CONST) == 'o'`), so an address `(plus (reg) (const (plus (symbol_ref) 4)))` — a
     struct FIELD at a nonzero offset — conflicts with everything; the output dependence gives the zero stores priority
     2 and the LUID tie-break keeps source order. The lever-free sibling func_8003750C (src/800_c.c:1934) writes exactly
     this sequence as `D_800C532A[D_800A4640[k].unk08 * 2] = -1; D_800A4640[k].unk04 = 0; D_800A4640[k].unk08 = 0;` and
     its object keeps the same order with the same unfilled `nop`.

## (c) The moves
- `s32 e;` -> `s16 e;` — closes defect 1 alone (with the tree's barrier kept: 0; scratch/e_s16.c). Launder deleted.
- Defect 2, ZERO levers, PARKED: `D_800A4640[b].unk04 = 0; D_800A4640[b].unk08 = 0;` (the TU's `Rsc24` type; `b` is the
  index the body already has) — score 4, and the ONLY differences are the relocation addends (`sh zero,4(at)` against
  D_800A4640 vs `sh zero,0(at)` against D_800A4644; same for +8/D_800A4648): identical only after LINKING
  (scratch/parked_link_n8.c). This is most likely the original text.
- Defect 2, pre-link, delivered in body.c: the two zero stores wrapped in a marked `do { … } while (0);`
  (`// !FAKE: do-while`, sched.c:2058-2074: a LOOP note in mid-block makes the next insn depend on every earlier set/use
  and flushes the pending memory lists, so nothing crosses it). Wrapping the D_800C532A store instead: 5.
Lever count 2 (barrier + launder) -> 1 marked do-while (0 once the struct spelling is allowed to change relocations).

## (d) GENERATOR PROPOSAL
When a residual is a store sunk below independent stores to OTHER globals (a load-delay slot filled in mine, a `nop` in
the target) and the tree carries a barrier between them: rewrite the later stores' `*(T *)((u8 *)D_X + k)` as fields of
the enclosing struct array (`D_BASE[i].fieldK`, D_X = D_BASE + K, K != 0) — a CONST address defeats
`find_symbolic_term` and restores the output dependence; score it with relocations normalised (it is identical only
after linking). A separate one-line rule: a launder on a copy `e = param;` whose stores are all 16-bit -> declare `e`
`s16` (R12 width on the COPY's destination, not on the parameter).

## (e) What did not work (bytes; all with `s16 e`)
- Barrier simply removed: 17. The D_800C532A index inline, `s16 n`, `*(s16 *)((u8 *)D_800C532A + n * 4)`, the D_800A4644
  zero store moved before the D_800C532A store, array-index spellings `D_800A4644[b * 12]`: 17 / 17 / 17 / 17 / 20 — all
  still `(plus reg symbol_ref)` addresses, all independent.
- Only the first zero store as a struct field: 14 (the D_800A4648 store is then still free to move).
- The sweep's best (R14 `entry` -> u16 + R8 base-shared): 17 — width on the PARAMETER, not on the copy.

## (f) Where the method fell short
The residual printed defect 2 as a register swap (`v0->v1`) plus shifted blocks; only the `.sched` priorities and
reading `memrefs_conflict_p` explained it. The decisive hint was `related.txt`'s func_8003750C (800_c.c), which spells
the same three stores lever-free with struct fields — METHOD step 3's "read lever-free bodies that share your globals
anywhere" is what found it. The byte oracle cannot credit a close that differs only in relocation addends; a
reloc-normalised score mode would let such struct closes bank.

## (g) Structs
YES — defect 2 IS a struct question, through the scheduler's alias channel rather than `expr.c:4568`'s
MEM_IN_STRUCT_P: typing the D_800A4640 records as `Rsc24` (unk04 = D_800A4644, unk08 = D_800A4648, unk10 = D_800A4650,
unk00 = D_800A4640, unk02 = D_800A4642, 0x18 stride) gives field addresses `symbol + const`, which `memrefs_conflict_p`
cannot disambiguate, which orders the stores as the target does. It removes the last lever but changes every such
access's relocation to D_800A4640+K — adopt it in the STRUCTS phase when the per-field symbols D_800A4644/D_800A4648 are
retired, for the whole D_800A4640 family (func_8002FF0C's identical barrier, src/800_b_2.c:2958, is the same case).
