# func_80182F8C (ov_SC03_111, 7 copies): closed lever-free — the sign-bit copy written as a bit test (agent c43, S103)

**Result: score 0 with `--body` only.** No pin, no asm, no volatile, and no pad: the `{ s32 pad[2]; }` "LEVER 1 frame
pad" at the end is REMOVED (the real construct supplies those 8 bytes, see (b3)). Body: `PACK/body.c`
(= `scratch/s7.c`). The only change is the flag copy:

```c
    if (*(u32 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 4) & 0x80000000) {
        *(u32 *)(*(s32 *)(a0 + 0x20) + 4) |= 0x80000000;
    } else {
        *(u32 *)(*(s32 *)(a0 + 0x20) + 4) &= ~0x80000000;
    }
```
(it copies the parent's bit 31 into our own flag word), plus deleting the trailing `{ s32 pad[2]; }`.

**Transfer: all 14 copies of the family score 0 with the same edit** (`scratch/xfer.py`, which applies it and runs
`--try` on each). That's both classes in 7 overlays (SC03_107/111/112/113/117/118, SC05_004): this function
(145 ins) and its sibling func_80182490 / func_80186B78 / func_8017F9BC / ... (386 ins), which has the same pin +
barrier + pad trio.

## (a) The residual
Same count (145/145). The lever-free `if (x < 0)` fills the `bgez` delay slot with the ELSE arm's `lui v1,0x7fff`
and leaves a `nop` in that arm's load-delay slot. The target fills it with `lui a0,0x8000`, and the then-arm uses
`v1` for the pointer and `v0` for the value, where mine has them the other way round. So it's one delay-slot choice
plus the register swap that goes with it. The pin fixed the swap (score 3 alone) and the barrier fixed the slot
(score 4 alone).

## (b) The passes (proved on dumps, `scratch/dumps_s5/`, `scratch/dumps_free/`)
1. **cse1 shares the constant across the branch.** `x & 0x80000000` can't take an immediate on MIPS, so the
   expander loads the constant into a pseudo (`.cse` insn 84: `(set (reg 97) (const_int 0x80000000))`), and then
   insn 85 `and`s it with the flag word. The then-arm is the jump's fall-through, so it's in the same extended basic
   block, and cse replaces the arm's own `0x80000000` with `reg 97` (`.cse` insn 98: `(ior (reg 100) (reg 97))`).
2. **combine turns the bit test into a sign test** (`and` + `eq 0` becomes `(ge (reg 95) 0)`, the same `bgez` the
   target has). The constant load stays alive because the then-arm still reads reg 97. So the constant is set
   BEFORE the branch (`.lreg` insn 85).
3. **reorg's backward fill takes it.** `fill_simple_delay_slots` runs before `fill_eager_delay_slots`
   (reorg.c:4331 area), and it moves `li $4,0x80000000` from before the branch into the `bgez` slot. The eager fill,
   which in the lever-free build stole the else arm's `lui` (`mostly_true_jump` says GE-against-0 is taken,
   reorg.c:1335-1420, so the target thread is tried first), never runs, because the slot is already full. With
   `$4` busy across the branch, the then-arm's local allocation lands the pointer in `$3`, as in the target.
4. **The 8-byte "frame pad" is this construct's fingerprint.** When combine deletes the `and`, the REG_DEAD note
   for its result (reg 96) has no insn left to go on, so `distribute_notes` emits a `(use (reg 96))` at the block's
   code label (combine.c:10830-10840; `.combine`: `(insn 283 (use (reg:SI 96)))` after `code_label 504`). Reg 96 is
   never set, so global allocation gives it no hard register (`.greg`: "5 regs to allocate: 72 74 96 97 150", and
   96 is the only pseudo with no disposition; the lever-free build has none). Reload then gives it a stack slot, and
   the frame grows by 8 after rounding (with the pad kept: 80 vs 72; with it removed: 72 = target). This is the
   METHOD c35 frame-only mechanism, and it's why a previous agent needed an invented dead `pad[2]` local: the pad
   was standing in for the phantom slot of the real `&` test. The same holds for the 386-ins sibling, whose pad
   comment said "INNER-BLOCK + LAST is load-bearing".

What's proved on bytes: the score-0 compiles (this function and all 14 copies), the frame arithmetic (s1 = with pad
= 80, s5/s7 = without = 72), and pin-alone = 3 / barrier-alone = 4. What's proved on dumps: points 1, 2, the USE
insn and the missing disposition. What I read but did not trace in a dump (there's no dbr dump): that
`fill_simple` is the pass that fills the slot. It's consistent with the `.s`, where the slot holds the pre-branch
insn.

## (c) The move
Rewrite `if (x < 0) set bit31; else clear bit31;` as `if (x & 0x80000000) x' |= 0x80000000; else x' &= ~0x80000000;`
(u32 view), and delete the trailing `{ s32 pad[2]; }`. It's one edit: the pad has to go BECAUSE the test now
supplies the phantom slot.

## (d) GENERATOR PROPOSAL
When a `< 0` / `>= 0` test on a word guards `|= 0x80000000` (or any constant that can't be an immediate), and the
target fills the branch delay slot with that constant's `lui` while the lever-free build fills it from the other arm
(or the tree carries a pin + barrier there and/or a dead trailing `pad[]` local), rewrite the test as
`x & CONST` with the same constant and drop any frame pad. cse shares the constant with the arm, combine turns the
`&` back into a sign test, and the USE of the dead `&` result gives back the pad's stack slot.
Family sizing grep: `grep -rn -B1 "0x80000000; }" src | grep "FAKE: pin"` = 14 hits, and all 14 scored 0. Another
possible family for the same idea (not tested): `uVar1 = val | 0x80000000;` under lever-carrying `< 0` tests in
ov_SC06_008/010/032.

## (e) Tried and did not work (bytes)
- `pin.c` (pin only) = 3 [ORDER], `bar.c` (barrier only) = 4 [REG]. Lever-free = 18.
- `t1`-`t5`: every spelling of the then/else arms (`|=` vs `= x |`, s32 vs u32, a local `q`) with the `< 0` test
  kept = 18. With the `< 0` test the constant is only ever loaded inside the arm, so arm spellings can't help.
- `s1`-`s4` (the `&` test with the pad kept) = 8, frame only (80 vs 72). That's what revealed the pad as a stand-in.
- Removing the unused `s16 pos[4]` as well = 9. `pos` is a real frame member (the sibling uses it), so it stays.

## (f) Where the method fell short
- METHOD's list has no row for "the delay slot is filled from the wrong arm". The fix wasn't about the arms at all:
  the test has to create a value that's live BEFORE the branch, so the backward fill wins. residual_moves.md needs
  a row for it: *delay slot holds the other arm's constant → make the test compute that constant (bit test instead
  of sign test)*.
- The tree's "frame pad" levers are worth auditing as a class. A dead `pad[N]` local that some earlier agent
  "byte-verified" may be standing in for a combine-emitted USE slot (c35 again) from a test spelled the wrong way.
  When one of those pads comes out, look at the tests near it.
