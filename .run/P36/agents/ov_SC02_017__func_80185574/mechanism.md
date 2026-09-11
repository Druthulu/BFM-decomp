# func_80185574 — e13 (P36 T7 S104) — score 16 (sweep best 4) -> 0, ZERO levers (was: NEEDED pins `$0`, `$2`, `$3`)

(a) Residual: two defects, 22/22 insns. (1) The else arm reads the object through `a0` (the incoming parameter) while
the target reads it through `a1` in both arms (`move a1,a0` in the prologue, `a0` reused for the `-129` mask).
(2) A v0/v1 permutation in each arm: target then-arm `lw v1,0x20 / lw v0,0xDC / lhu v1 / and v0,v0,a0`, else-arm
`lw v0,0x20 / lw v1,0xDC / lhu v0 / ori v1`; lever-free text the opposite in both.

(b) Pass/decision (dump-verified: `scratch/dumps_b1` (param copy deleted, decompiler temps) vs `scratch/dumps_c3` (body.c)):
  1. `self = arg0 + 0;` makes two pseudos (param r72-equivalent + the copy); cse's canonical-register choice
     (`make_regs_eqv`, cse.c:826-862) leaves the else arm reading the parameter pseudo, which global puts in `a0`.
     One pseudo (use the parameter directly, METHOD d24) lives across the then arm where local-alloc has put the
     mask in `a0`, so it conflicts with `a0` and lands in `a1` in both arms (b1: the `a0` reads are gone, 16 -> REG-only).
     c4/c5 (body.c + `s32 arg0 = a + 0;` / `= a;`): 4 — the copy is part of the joint close.
  2. The decompiler REUSES one variable for the pointer and the halfword read through it (`p = *(s32 *)(self+0x20);
     p = *(u16 *)(p + 0x18);`) and `g` for the flag word and its `|= 0x80` result — each has `reg_n_sets == 2`, so
     sched1's `birthing_insn_p` (sched.c:2469-2490) is false for those loads and `adjust_priority` (sched.c:2507-2547)
     gives them no boost. b1 `.sched` block 1: `ready list at T-5: 40 (2) 30 (7f000001), now 30 40` — the mask `li`
     (insn 30) is launched late, the pointer load (33) first. With one pseudo per value every load is birthing
     (c3 `.sched`: `T-5: 36 (7f000001) 29 (7f000001) … 29 has a greater potential hazard`) and the mask `li` ends up
     FIRST in the block.
     That changes the quantity NUMBERING (birth order) of the block's three local-alloc quantities, and a block with
     exactly three quantities is ordered by the hand-written sort at local-alloc.c:1486-1500, which compares quantity
     NUMBERS 0/1/2, not positions in `qty_order`: b1 {q0 pointer/value (4 refs), q1 flag+and, q2 mask} ends [q0,q1,q2]
     -> pointer `v0`, flag `v1`, mask `a0` (`.lreg`: "Register 77 in 2 / 78 in 3 / 73 in 4"); c3 {q0 mask, q1 pointer
     tied to the u16 value, q2 flag tied to the and result} ends [q2,q1,q0] -> flag `v0`, pointer `v1`, mask `a0`
     (`.lreg`: "78 in 2 / 76 in 3 / 80 in 4") = the target. Same for the else arm (c3: pointer/value r81/r82 in 2,
     flag r83/r84 in 3).
  3. The halfword copy must be written BEFORE the read-modify-write of `+0xDC`: the target does the `lhu` before the
     `sw 220`, and a scalar store through the object vs a load through `*(obj+0x20)` may alias (`true_dependence`,
     sched.c:817-841), so a source order with the RMW first keeps the load after the store (enum `AB__*` 6, `*__AB` 7 COUNT).

(c) Moves (joint):
  - delete `self = arg0 + 0;` and use the parameter directly (d24);
  - one value per name: the pointer, its halfword, the flag word each its own value — body.c inlines them all
    (`*(s16 *)(arg0 + 0x100) = *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x18); *(s32 *)(arg0 + 0xDC) &= ~0x80;`), the spelling
    the neighbour func_80185494 uses for the same `+0x20 -> +0x18` halfword; the `mask`/`flag` locals are gone and the
    test reads `*(s16 *)(arg0 + 0xAA)` inline (c3 = 0);
  - the halfword store first, the `+0xDC` RMW second, in both arms.
  Enumeration (`scratch/gen.py` -> `scratch/enum/`, 143 bodies, `scratch/enum_scores.txt`): every arm spelling that
  reads the halfword into its own value before the RMW scores 0 in combination (42 of 143: `BA`, `vu16A`, `vs32A`,
  `tmpPVF` (decompiler temps with the pointer and value split), `fB`, `pfB`, `mBA`); every spelling that keeps the RMW
  first or reuses `p` does not. Kept a `s32 flag` local: c1 = 0; declared `s16 flag = …` (c2): 1.

(d) GENERATOR PROPOSAL: when a local is assigned twice in a straight-line block (`p = *(T *)(x + K); p = *(U *)(p + J);`
or `g = load; g |= C; store g`) and the residual is a register permutation in that block, give each assignment its own
value (inline or a fresh name) — both sets become sched1-birthing (sched.c:2469-2490), which reorders the block and
therefore local-alloc's quantity NUMBERS, which is all a three-quantity block's order depends on (local-alloc.c:1486-1500).

(e) Did not work: b1 (param copy deleted only) 16; c4/c5 (body.c with the param copy kept) 4 REG; every `AB`/`pA`/
`fpA`/`tmpPF`/`tmpPF2`/`mAB` arm (store order or reused pointer) 6/7/13. The sweep's R7/R8/R5/R9/R10/R18 reached 4.

(f) Method: METHOD c1/c8/d15 ("a local REUSED … split it") was the row; the new fact is that here the split acts through
sched1's birthing boost and the three-quantity sort's use of quantity numbers, not through death counts — the
allocation table (global) is blind to it; the `.sched` ready-list lines and `.lreg` "Register N in R" lines settled it.
An enumeration over arm spellings (143 bodies, ~1 min) found it before any reading.

(g) Structs: no. The decisions are sched1's birthing test (a register's set count) and local-alloc's quantity numbering;
the object (`s16 +0x5C/+0x98/+0xAA/+0x100/+0x104`, `s32 +0x1C/+0xDC`, `+0x20` pointer to a record with `u16 +0x18`)
as a struct would change spelling only. (The `+0x18` load vs the `+0xDC` store ordering is already what the source
order gives; an in-struct marking would only matter if the store came first.)
