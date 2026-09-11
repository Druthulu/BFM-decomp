# func_8018179C (ov_SC06_010_jr_8017A4AC.c) — T7 d21, P36 S104

**Score 0, ZERO levers** (free start 63; regen best free_109 = 7). Tree levers 2 pins -> 0. The same text closes all
seven copies of the class at 0 (scratch/copies/TABLE.md): 14 pins -> 0.

Diff from body_free.c (two independent moves; each alone scores worse, both needed):
```
+    s32 ret;                         /* function scope; the three per-case `s32 ret;` declarations deleted */
-        v1p = *(s32 *)(a0 + 0x20);   /* case 0, last statement group */
-        *(u16 *)(v1p + 0x12) = *(u16 *)(v1p + 0x12) & 0xFFF;
+        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) &= 0xFFF;
```

## (a) The residual
1. (60 of 63) a register permutation: `a0` (the actor) took $s0 and case 0's `s0v = a0+0x88` / case 3's `ret` took $s1;
   the target has a0=$s1, s0v=$s0, ret=$s0, s2v=$s2. Instruction count equal.
2. (3) case 0's `p20 = *(a0+0x20)` in $v1 and the lhu/addu temp in $a0; the target (and case 2's identical code, even
   in the free body) has p20=$a0, temp=$v1.

## (b) The passes and decisions
1. global.c `allocno_compare` (:594-607) + `find_reg` (:945-990). Free body: a0's allocno (r72, 56 refs over 179 insns,
   priority 15642) outranks every other call-crossing pseudo (s0v 2307, case-3 ret 4000, s2v 1875), is allocated first
   and takes $16 in pass 1. **Merged**: the one function-scope `ret` is one allocno whose refs add up (3 sets + 3 uses = 6)
   while its live length is the SUM of three tiny pieces (case 0: copy->compare; case 1: same; case 3: across one call) =
   5 insns -> priority floor_log2(6)*6/5*10000 = **24000 > 15642**, and it crosses a call (case 3). It is allocated FIRST,
   takes $16; a0 (conflicts with it) takes $17; s0v then takes $16 in pass 0 (`regs_used_so_far`, :951-953 — it does not
   conflict with ret: see next line); ret-vs-s2v conflict pushes s2v to $18. The case-0/case-1 pieces of `ret` never show
   in the bytes: combine folds each call-result copy `(set ret v0)` into its single compare (combine.c:914-917), so
   after combine only case 3's `move s0,v0` survives — but flow counted the refs and live length BEFORE combine
   (flow -> combine -> ... -> global), so the priority keeps them. Proven on bytes + dumps: `.greg` order line
   `76 145 72 …` (r76 = ret, before r72 = a0), alloc_table r76 pri 24000, refs 6, live 5 (scratch/dumps_m1).
   Merging only two of the three (cases 0+3 or 1+3) also scores 0 (m3, m4); merging all three plus the rand() and
   BE54 results too (m2) also 0. One per-case `ret` each (free body) = the permutation.
   Side proof of the same channel: regen R9's free_109 reached 7 by moving case 3's `v1p` read above the B744 call —
   v1p becomes block-local + call-crossing, local-alloc gives it $16 (find_free_reg), r72's `.greg` conflict line gains
   `16`, a0 -> $17. Right allocation, wrong reason (the target loads v1p after the call).
2. local-alloc `block_alloc` three-quantity path (local-alloc.c:1486-1500): `qty_compare (0, 1)` / `(1, 2)` are called
   with qty NUMBERS, not `qty_order[]` slots, so a block with exactly three quantities is allocated in BIRTH order. Case
   0's tail block (label 170 .. jump 230) had 3 qtys: p20 (born first, pri 5000) -> $v1 before the lhu/addu pair
   (20000) -> $a0. Case 2's identical code sits in a 5-qty block, takes the real qsort (`qty_compare_1`, :1598) and
   gets p20=$a0. Writing the last read-modify-write as a compound on the re-read pointer (the TU's own spelling in
   func_801825DC) deletes the reused function-level `v1p` second set there, so the block gains a quantity (4) -> qsort
   -> p20=$a0, temp=$v1. Proven: lsim3.py on the .lreg (block 17: `qtys 3`, order q0,q1,q2 -> v1,a0,v0, 0 mismatches
   vs the dump), then bytes 7 -> 3 (v2) and 4 -> 0 with the merge. Inlining the FIRST read instead
   (`snd = *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12);`) closes it equally (v3) — also a quantity-count change.

## (c) The moves
- Declare `s32 ret;` once at function scope and use it for all three `func_8012BE98` distance results (delete the
  per-case declarations). Global-alloc priority, global.c:594-607.
- case 0: `*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) &= 0xFFF;` for the two-statement v1p re-read + mask. local-alloc
  3-qty birth order, local-alloc.c:1486-1500.

## (d) GENERATOR PROPOSALS
- **R-merge-callret**: when the residual is a callee-saved permutation in which the high-ref "self" pointer lands one
  register too LOW (target a0=$s1, a short-lived value in $s0), merge every same-typed call-result temp (`ret`, `r`,
  `ret3`, …) that is declared per case/arm into ONE function-scope variable — the combined allocno has many refs over a
  near-zero summed live length (its copies from $v0 are folded into their compares by combine after flow counted
  them), so it outranks the self pointer. Enumerate: all pairs/triples of same-type call-result locals.
- **R-qty3**: when a block-local register pair is swapped (`lw v1 / lhu a0` vs `lw a0 / lhu v1`) and the SAME code
  elsewhere in the function allocates correctly, count the block's quantities in `.lreg` (lsim3.py prints `qtys N`):
  if it is 3 (or 2), add or remove one quantity — inline a re-read into a compound (`*(T *)(*(s32 *)(p + K) + J) op= v;`),
  or split/merge a reused temp — to move the block onto/off the birth-order path.

## (e) What did not work (bytes)
- body_free with only the merge: 4 (the case-0 p20 swap remains). Only the case-0 compound: 60 (permutation remains).
- v4 = case-0 fix + case 3 in its original order, per-case `ret`: 60.
- On the free_109 base: splitting case 0's second `v1p` into `p20` (reuse p20 for the mask): 12 (a2 used, the qty
  ranks shuffle the other way); the compound (v2) or the inlined first read (v3): 3.
- All R2–R34 generator families: best 7 (free_109, R9 swap-stmts, which fixed the permutation by the wrong
  mechanism). No generator merges same-role temps ACROSS switch cases.

## (f) Where the method fell short / what helped
- Step 3's "(S103 c18) MERGE per-block locals into one function-scope variable when the target keeps ONE register for one
  role across several blocks" was the right family, but its trigger ("read the objdump for same register, same role")
  does NOT fire here: two of the three merged pieces are INVISIBLE in the target bytes (combine folded the copies), and
  the visible piece's register ($s0) is shared with an unrelated variable (s0v). The better trigger is arithmetic:
  "the self pointer's priority must be beaten — which merge of short-lived call-crossing/call-result temps sums to
  refs/live above it?" Worth adding to METHOD step 4 next to the 6524-vs-6666 note.
- Starting from the regen best (free_109, 7) and asking WHY its move fixed the permutation (r72 conflict line gained
  `16`) is what pointed at "something must outrank or pre-occupy $16" — then the priority table made the merge obvious.
- lsim3.py settled the case-0 swap in one run (the 3-qty birth path), as step 12 (d5) said it would.

## (g) Structs
No. Neither decision reads memory-access kinds: (1) is global-alloc priority arithmetic over pseudo refs/live lengths
(global.c:594-607) and (2) is local-alloc's quantity count in one block (local-alloc.c:1486-1500). A struct type for
the actor (`a0->f20->f12 &= 0xFFF` instead of the cast) would produce the same RTL for these accesses (MEM_IN_STRUCT_P
changes only sched/cse alias answers, `expr.c:4568-4577`, and no load/store order differs here); the class was never a
struct problem — its two pins were compensating for a declaration SCOPE and a statement SPELLING. (A struct for
`a0+0x88`, likely a target-position vector passed to BE98/B744, would be the readability pass, not a lever.)
Not tested on bytes, since both closes are lever-free without it.
