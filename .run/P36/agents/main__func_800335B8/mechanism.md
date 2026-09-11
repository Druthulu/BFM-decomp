# func_800335B8 (src/800_b_2.c) — S104 agent e31 — CLOSED at 0, ZERO levers (2 launders -> 0)

## (a) The residual
Score 8 lever-free, COUNT 59 vs 60, two missing copies: (1) the target's `move t0,a1` in the `bne …,<return>` delay slot
(branch 2 then computes `andi a1,t0,0x7f` from the COPY while the two flag tests and branch 1 read `a1`); mine has no
copy and reads `a1` everywhere; (2) loop 1's `move v0,a0` in the `beqz` slot (the stores go through `72/79(v0)`); mine
has a `nop` there and an address giv `addiu a0,a0,751` (`sh a1,-7(a0)`, `sb t0,0(a0)`).

## (b) The passes and the decisions (PROVEN on the `.cse`/`.loop` dumps, scratch/dumps_t0f, dumps_u8, dumps_c1, dumps_a2)
1. cse (first pass). `t0 = a1;` (same-mode SI copy) makes the two pseudos one quantity (`make_regs_eqv`,
   cse.c:826-880); the path from the entry follows the `a1 & 0x1000` jump into branch 2 (`;; Processing block from 2 to
   153`), so branch 2's `a1 = t0 & 0x7F` is canonicalised to the parameter (`.cse` insn 140 `(and (reg 73) 127)`) and
   the copy dies. A `u8`/`u16` copy is not a same-mode copy, but cse still folds `(subreg:SI (reg:QI 85))` through the
   recorded `(subreg:QI (reg 73))` when the read sits on the SAME path (u8 dump, insn 140 again). The target's read of the
   copy is therefore one cse never sees with the equivalence: it is INSIDE loop 2 (the loop head label has two uses, a
   new cse block), and loop.c's invariant motion hoists `val & 0x7F` to the preheader afterwards (`andi a1,t0,0x7f`).
   With `s32 val` the copy is same-mode and outlives the block, so cse makes IT canonical (cse.c:850-855) and rewrites
   the flag tests to `t0` (score 11); with `u16 val` the parameter stays canonical and the copy survives.
2. loop.c `record_giv` (loop.c:4447-4449): a DEST_REG giv is replaceable only if its register's LAST use is inside the
   loop. Loop 1's `rec = p + i * 0x54` with `rec` declared at FUNCTION scope (also set/used in loop 2) has
   `lifetime 46` and no `replaceable` in `.loop` (c1); block-local `rec` prints `replaceable` (a2). A non-replaceable
   reduced giv keeps `(set rec reduced)` (loop.c:3946-3953) — the target's `move v0,a0`, which reorg then steals into the
   `beqz` slot. Also from `.loop`: `giv of insn 76 not worth while, 0 vs 19` — the `e + i` giv is not reduced, which is
   why the target recomputes `addu v0,a3,v1` every iteration; write it `(e + i)[0xE]` (operand order: `e[i + 0xE]` gives
   `addu v0,v1,a3`, score 2).

## (c) The moves (all PROVEN on bytes; c1.c = body.c)
1. `u16 val = flags;` at the top (declaration initialiser; `val = flags;` placed after the `!= 1` test lands in the
   wrong delay slot, score 3) and branch 2's store written `rec[0x53] = val & 0x7F;` INSIDE the loop (the tree's
   `a1 = t0 & 0x7F;` before the loop deleted). Branch 1 stores `flags & 0x7F` and `1` in the loop (loop.c hoists both;
   the tree's `t0 = 1` was the hoisted constant).
2. Loop 1 written like loop 2: `p` invariant, `rec = p + i * 0x54;` (the tree walked `p` and laundered `rec = p`), with
   ONE function-scope `u8 *rec;` shared by both loops.
3. Readability: `for (i = 0; …)`, names `flags`/`n`/`i`/`val`, both stale copy-fence comments dropped.
Ablations on body.c: `s32 val` 11; `u8 val` 4; loop 2 storing `flags & 0x7F` 4; block-local `rec` 3.

## (d) GENERATOR PROPOSAL
When a `move` of a PARAMETER survives in the target (read only in a later branch) and the tree launders a copy of it:
declare the copy at the store's narrower width (`u16 val = param;`) and move the expression that reads it INTO the loop
whose preheader holds it (a use behind a loop label escapes the entry cse path); and when a loop keeps a `move vX,aY`
copy of its reduced pointer, declare the loop's pointer local ONCE at function scope and reuse it in a later loop
(loop.c:4447 non-replaceable giv).

## (e) What did not work (bytes)
- Goto loops (e16's func_80031B7C shape): 25 — this function's target IS loop-optimised (the `p + i*0x54` pointer is
  loop.c's reduced giv; the unreduced `e + i` is "not worth while", not a missing loop).
- Width of `t0` alone with the tree's `a1 = t0 & 0x7F` before the loop: u8/s8/u16/s16 all 4 (cse folds it).
- Loop 1 walking `p` (tree shape) with the launders removed: 4.

## (f) Where the method fell short
The residual's `move t0,a1` looked like S103 c4 (width), and width alone was byte-dead — the position of the READ
(inside vs before the loop) decides whether cse sees the equivalence. `.cse`'s "Processing block from 2 to 153" line
(the followed jump) was the fact that explained it.

## (g) Structs
No. The record walk (`D_800A46E8 + 0x2A0` stride 0x54, fields @0x35/0x48/0x4F/0x53) as a struct would re-spell the
same `(mem (plus rec K))` addresses; the decisions are cse's quantity canonicalisation and loop.c's replaceability.
