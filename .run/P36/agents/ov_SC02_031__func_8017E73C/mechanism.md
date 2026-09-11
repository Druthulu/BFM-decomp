# func_8017E73C (ov_SC02_031, 11 copies) — T7 agent c41 (S103)

**Result: score 0, lever-free.** No register pin, no asm, no added volatile, no do-while, no invented term, no dead
assignment. Whole-object check on the `--try --keep` object of `body.c`: `objdump -drz` of the ENTIRE `.o` is identical
to `.run/P36/delever/baseline/src/ov_SC02_031/ov_SC02_031_jr_8017AE2C.o`; `.text`/`.data`/`.rodata` compare equal (`cmp`).
Candidates in `scratch/v/` (a1-a4, b2-b5, c1-c4, d1, e1); dumps `scratch/dumps_{c1,d1,e1}/`; `scratch/splice.py` splices a
body into the TU, `scratch/try.sh` scores several candidates in parallel.

Two declaration widths, both needed (the same author habit c34 found in func_8017BF88 of this TU):

```c
    u16 flags;       /* was: s32 flags; s32 raw;  raw = call(); flags = raw;  + launder on flags */
    s16 ret;         /* was: s32 ret;  { s32 fire = ret; launder(ret); if (fire) ... }            */
    ...
    flags = ((s32 (*)(s32))func_8012CBA4)(a0);
    if ((flags & 0x6000) != 0x2000) { ... }
    ...
    if (ret != 0) { func_80146A6C(2, (void *)a0, 0, 0, 0, 2, 0); }
```

## (a) The residual in one sentence

COUNT 251 vs 253, two independent defects: (1) the entry test read the saved copy (`andi v1,s1,0x6000`) where the
target reads the raw call result (`move s1,v0; andi v0,v0,0x6000`, and the `li 8192` constant flips to `$v1`);
(2) the final `ret` test read `$s2` directly (`beqz s2`) where the target copies it to a local first (`move v0,s2`,
three copies after reorg fills two delay slots: the two MISSING instructions).

## (b) The passes and the decisions (PROVEN on dumps + bytes)

1. **cse's `(set REG0 REG1)` swap (cse.c:7440-7476, gate `GET_CODE (SET_SRC) == REG` at cse.c:7455).** With
   `s32 raw, flags; flags = raw;` the copy is REG->REG, `flags` (live across calls) becomes the canonical register, the
   swap retargets the call-result copy to it, and the entry test reads `flags` = `$s1`. With `u16 flags` expand emits
   `(set (reg:SI 78) (reg:SI v0))` then `(set (reg/v:HI 73) (subreg:HI (reg:SI 78) 0))` (`dumps_e1/e1.i.rtl` insns
   18/20): the source is a SUBREG, the gate fails, both pseudos survive. cse substitutes r78 for `(subreg:SI r73)` in the
   same block, so after combine the test is `(and:SI (reg:SI 78) 0x6000)` with `REG_DEAD r78` (`e1.i.combine` insn 23):
   r78 is a local that dies there -> `$v0`, r73 lives across the calls -> `$s1`. The target, and the `li 8192` goes to
   `$v1` because `$v0` is now occupied. The later `flags & 0x8000` / `& 0x6000` read r73 (`andi v0,s1,0x8000`).
2. **combine's shift-pair reduction (combine.c:7932-7942, `num_sign_bit_copies > first_count`).** With `s16 ret`, the
   final `if (ret != 0)` expands to `sll 16; sra 16` of the HImode pseudo (`e1.i.rtl` insns 659/660). `ret` is only ever
   set to 0 and 1, so num_sign_bit_copies proves the pair is an identity and combine rewrites it as
   `(set (reg:SI 207) (subreg:SI (reg/v:HI 75) 0))` (`e1.i.combine` insn 660) — a plain copy into a local pseudo, which
   survives (cse has already run) and becomes `move v0,s2`; reorg duplicates it into the two branch delay slots that jump
   to the test (the target's three copies). This is the METHOD's c18 row exactly ("declare the flag s16").

The tree's two launders were faking exactly these two copies (its own comments say so: "gcc-2.7.2 kept TWO pseudos" and
"the target evaluates the flag through a LOCAL copy").

## (c) The source moves that closed it

1. `u16 flags` (the call result assigned directly to it; the `raw` temporary is not needed): alone 14 -> 11 (`a1.c`).
2. `s16 ret` (the `fire` temporary and its block are not needed): alone 14 -> 3 (`a3.c`).
3. Both: 0 (`a4.c`). Readability, all still 0: `fire` block removed (`b2.c`), `raw` removed (`c1.c`), the `s0 = a0`
   copy removed and the parameter used directly (`e1.c` = `body.c`), comments rewritten to the real mechanism.

## (d) GENERATOR PROPOSAL

When a launder re-ties a variable right after `x = y` / `x = call()` and the residual says the target reads the SOURCE
register (or tests a copy of a flag), re-declare the laundered variable as `u16`/`s16` when all its uses are masked to
16 bits or it only holds 0/1 — a HImode destination makes the copy a SUBREG move that cse's swap cannot fold
(cse.c:7455), and a 0/1 short's test sign extension is reduced by combine to a surviving copy (combine.c:7932) — then
delete the now-redundant temporaries.

## (e) What did not work (byte evidence)

* `s16 flags` (`a2.c`): 11, same as `u16` alone — the width is what matters, not the signedness (only the ret move was
  missing).
* Removing `m` (`b3.c`, `c3.c` with `if ((flags & 0x8000) || ...)`): 15, 250 ins — fold_truthop merges the two masks
  into one `andi 0xe000` test, as the tree's comment says. `m` stays (a plain named subexpression, not a lever);
  `u16 m` is also 0 (`c4.c`).
* Removing `s32 dead[4]` (`b5.c` 25, `c2.c` 10 on the matched text): the frame drops 80 -> 64 (`vars= 16` instead of
  32). NOT A LEVER in the tool's sense (it was in `body_free.c`, no `!FAKE` mark) but it is an unused declaration, so
  report it: the 16 bytes that remain are two phantom reload slots — `.lreg` "Register 110/162 used 2 times ... ST_REGS
  or none", the `(ashift (subreg HI) 16)` halves of the `lh 262` (0x106, reused as `a1`) and `t` (0x104) sign
  extensions, deleted by combine's split with stale `reg_n_refs` (combine.c:2306; reload1.c:2331) and each rounded to 8
  bytes. The original needed 16 more bytes; I did not find a natural spelling that makes two more phantom slots and did
  not grind on it.

## (f) Where the method fell short

* It did not: METHOD rows c4/c34 (u16 destination) and c18 (s16 flag -> kept copy) predicted both moves from the
  residual's two shapes, and the neighbouring pack's mechanism (c34, same TU, same author) pointed at the width habit.
  4 compiles to the close. The only lesson: when a body has TWO launders, test the joint move early — each alone scored
  11 and 3, not 0.
* The `dead[4]` frame pad is a separate, unresolved question (see (e)); a frame-only residual tool note ("vars= N")
  would make the check instant.
