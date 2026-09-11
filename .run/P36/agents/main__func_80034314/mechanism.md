# func_80034314 (src/800_b_2.c) — S104 agent e16 — CLOSED at 0, ZERO levers (1 pin -> 0)

## (a) The residual
Score 27 lever-free (sweep best 23), COUNT 205 vs 207: after EACH of the two calls (`func_800348A8`, `func_8003310C`) the
target keeps the result in a first register, tests it, and copies it to the long-lived `ret`
(`move v1,v0; beqz v1,…; move s5,v1; addiu v1,s5,-1`); mine puts the call result straight into `ret`
(`move s3,v0; beqz s3,…; addiu v1,s3,-1`) — one `move` missing per site. The `s3`/`s5` swap of `p` is fallout of the
missing pseudo. (The tree faked the survivor with a `$3` pin on `idx`.)

## (b) The pass and the decision (PROVEN on the `.cse` dumps, scratch/dumps_free vs scratch/dumps_win)
cse's `(set REG0 REG1)` swap, cse.c:7440-7474: the body's `idx = f(); ret = idx;` has the copy IMMEDIATELY after the insn
that set `idx`, and `ret` is the qty's canonical register (it lives longer and beyond the block, `make_regs_eqv`
cse.c:840-856), so cse rewrites the pair as `ret = v0; idx = ret;` and the test to `ret == 0`
(`.cse`: `insn 102 (set (reg 81) v0)`, `insn 105 (set (reg 80) (reg 81))`, `jump_insn 108 … (eq (reg 81) 0)`). `idx`'s
copy is then dead (it is reassigned `ret - 1` before any read), so one register and one move vanish.
With the copy AFTER the test (win), the insn before the copy is the jump, not the setter, so the swap's
`prev … SET_DEST (PATTERN (prev)) == SET_SRC` test (cse.c:7463-7464) fails: `.cse` keeps `(set (reg 80) v0)`,
`jump_insn 105 … (eq (reg 80) 0)`, `(set (reg 81) (reg 80))`. reorg then pulls each `move s5,v1` into its branch's delay
slot (EQ site: from the fall-through head, `fill_eager_delay_slots` reorg.c:3713-3718; NE site: from the target head,
predicted taken, reorg.c:3690-3695), which is why the copy looked like it came before the test.

## (c) The moves that closed it (PROVEN on bytes; JOINT — both sites needed)
1. `idx = func_800348A8(arg0); ret = idx; if (idx != 0) { idx = ret - 1;` ->
   `idx = func_800348A8(arg0); if (idx != 0) { ret = idx; idx--;`
2. `idx = func_8003310C(…); ret = idx; if (idx == 0) return 0; idx = ret - 1;` ->
   `idx = func_8003310C(…); if (idx == 0) return 0; ret = idx; idx--;`
Site 1 alone: 25 (worse than the start — METHOD step 5). `idx = ret - 1;` and `idx--;` both score 0; `idx--` delivered.
Also dropped (byte-neutral): the two orphan comments "dbr fence …" and "sched fence …" — they described launder levers
that sites.txt lists as REMOVED and that are no longer in the body (flagged here so the drop is not silent).

## (d) GENERATOR PROPOSAL
When a COUNT residual is one missing `move` right after a call (target: `move vA,v0; b?? vA; move sK,vA`) and the body
reads `x = call(); y = x; if (x …)`, move the copy `y = x;` past the test into the arm(s) where `y` is needed (after an
early `return`), at every such site at once: the cse.c:7440 swap needs the copy to sit immediately after its source's
setter. (A variant of generator R21 — "separate the copy from its producer" — where the separating statement is the
test itself; R21's reorders stay within straight-line statements and so did not reach it.)

## (e) What did not work (bytes)
- Only the first site changed: 25. `e = D + (idx - 1) * 0x54` with no `idx` reassignment: 25 (idx then dies at the copy
  again; the target needs `idx` reassigned from `ret`).
- The sweep's 325 compiles (width `u16` counter + do-while, decl moves, block/do-while wrappers, param copies): 23.

## (f) Where the method fell short
The residual's "register pairs" line (s5->s3, s3->v1) reads as a register permutation; the fact is a missing pseudo
(COUNT 205 vs 207). METHOD step 2 ("COUNT FIRST") was the right entry; the S103 c-list "a copy cse deleted because the
producer sat immediately before it" named the class — the only new part is that the fix is moving the copy past a branch.

## (g) Structs
No. `Snd54`/`Rec12` are already structs; the decision is cse's register-copy canonicalisation, not an aggregate/scalar
alias question, and no field access is involved in the defect.
