# func_80183A2C (ov_SC03_102_jr_8017BEBC.c) — T7 agent c45, S103

**Result: score 0** (154/154 ins). Checked three ways: `--try … --body` gives MATCH; the candidate object's
`objdump -drz` of the function, relocations included, is identical to the baseline
(`.run/P36/delever/baseline/…jr_8017BEBC.o`); and the candidate's whole `.text` is byte-identical to the baseline's
(cmp). The body has no register pin, no asm statement, no added volatile, no do-while and no invented term. The one
non-plain construct is the body-local **declaration alias** for `D_800AF648` (METHOD_S103 allows it as a declaration
alias). A pure-C alternative that needs a change outside the body is in
`../ov_SC03_102__func_80183E3C/mechanism.md` (c2), proved for this function too.
Two defects, each fixed by one move. A third move only improves readability.

## (a) The residual
Start: score 30, COUNT 151 vs 154.
1. **Three missing instructions**, all from `&D_800AF648`. The target has 2 × `lui/addiu $a0` and no `$s2`. The build
   has one `la $s0` + 2 × `move $a0,$s0`. The build had `$s0` free here, so the stack frame did not change.
2. **Tail schedule + registers.** The target issues the VOLUME magic-multiply first (`mult v1,a0 ; mfhi t1`, then
   `addiu v0,a2,160 ; nop ; mult v0,a0`), with `|x|` and `vol` both in `$a1` and the 0x66666667 constant in `$a0`.
   The build issues the PAN multiply first, keeps `|x|` in `$v1` and the constant in `$a1`, and loses the mfhi->mult
   hazard `nop` (the 154th instruction).

## (b) Pass and decision (read in the source; each one proved on bytes and dumps)
1. Same mechanism as func_80183E3C. `calls.c:1654-1664` puts the constant argument in a pseudo. cse unifies the two
   pseudos because SYMBOL_REFs hash and compare by string POINTER (`cse.c:1937-1939`, `cse.c:2107-2108`). An
   asm-label declaration gets a fresh `"*SYM"` string (`varasm.c:479-486`), so its SYMBOL_REF is a different cse
   value, while the emitted relocation is unchanged. After this move alone the score is 23, count 153/154.
2. **sched1's birthing-insn boost.** `adjust_priority` (`sched.c:2538-2545`) raises a predecessor to `max_priority`
   (LAUNCH_PRIORITY 0x7f000001, `sched.c:187`, set at `sched.c:3902`) when `birthing_insn_p` holds. For a SET of a
   REG, `birthing_insn_p` requires the register to be live after the insn AND `reg_n_sets == 1`
   (`sched.c:2489-2490`). With a separate `ax` temp, `vol` is set once: pseudo 144, "used 2 times" in `.lreg`. So its
   final `subu` (insn 299) is boosted. In the `.sched` dump, at T-2 the ready list is `299 (7f000001) 309 (c)`: 299
   is picked ahead of pan's 309 in the backward scheduler, which places the volume chain LAST and the pan multiply
   first. When `|x|` is computed in `vol` itself, `vol` has 3 sets (pseudo 143, "used 5 times"), so insn 301 is not
   boosted: the ready list reads `301 (c) 311 (c)` and the tie goes to `INSN_LUID` (`sched.c:2428`). Pan's insn 311
   is scheduled at T-3, the volume chain is placed first, and the hazard `nop` comes back. One pseudo for
   `|x|`→`vol` also gives both values `$a1`, which was the old `$5` pin's job.
   The tree's launder `__asm__("" : "=r"(vol) : "0"(vol))` was a second SET of `vol`: it worked only because it made
   `reg_n_sets(vol) = 2` and so switched off the birthing boost. The TU note at func_80183438, lever 3 ("sched1 always
   hoisted the PAN multiply… only the re-tie moves it"), names the right pass. The mechanism behind it is this one.
3. Readability only: `(vol | (0x3000 | x))` replaces the block-local `s32 flg = 0x3000;`. It is the association
   fold wants (TU note at func_80183438). Score stays 0.

## (c) The moves that closed it
```c
func_8004914C(&D_800AF648);
{ extern u8 D_800AF648_b __asm__("D_800AF648"); func_800491AC(&D_800AF648_b); }   /* was: $a0 pin */
...
s32 x = (s16)L.sxy[0];
s32 vol = x;                 /* was: s32 ax = x;  (pinned $5) */
if (vol < 0) { vol = -vol; }
vol = ((0xA0 - vol) * 0x7F) / 0xA0;      /* launder deleted */
x = (x + 0xA0) / 0x14; if (x == 0x10) { x = 0xF; } x = x << 8;
func_8002D4C8(0xA9B, (vol | (0x3000 | x)) & 0xFFFF);
```
The `|x|`→`vol` chain is ONE value refined in place (the absolute position becomes the volume), which is the same
shape the tree already uses in func_80183E3C. It is not an unrelated reuse. `x`→pan is likewise the value derived in
place, as in `body_free.c`.

## (d) Generator proposals
- (R-launder-birth) When a `"=r"(v) : "0"(v)` launder sits after the last SET of `v`, and its removal flips the order
  of two independent chains in one block (a COUNT/ORDER residual in a tail of multiplies/divides), rewrite the
  single-set temp that feeds `v` as `v` itself (`t = e; if (…) t = -t; v = f(t);` → `v = e; if (…) v = -v;
  v = f(v);`). This gives `v` more than one SET, which switches off `birthing_insn_p` (`sched.c:2490`). The 24
  `((0xA0 - ax) * 0x7F) / 0xA0` copies in 8 overlays (`git grep -n "0x7F) / 0xA0"`) are the obvious first family.
- (R-la-alias) As in func_80183E3C: `la $sN,SYM` + N × `move $aK,$sN` where the target has N × `la $aK,SYM` → give
  each later site its own body-local asm-label declaration alias, or use one `static inline` helper at TU level.

## (e) What did not work (byte evidence)
- A plain direct `func_8004914C(&D_800AF648)` pair: 30, unchanged (cse merges).
- A separate `pan` local instead of reusing `x`: 10 (REG-caller).
- `(vol | 0x3000 | x)` and `((vol | 0x3000) | x)`: 12 each (MIXED). `x << 8` folded into the OR: 11 (COUNT, 153).
- The mechanical search (history.txt) best was 25 (R6/R7/R8 moves). None of them changed the set count of `vol` or
  the cse class of the address.

## (f) Where the method / census fell short
- **Census arity claim refuted.** Every `func_8012B608` call in this body passes 3 arguments, the definition
  (`src/shared/ov/func_8012B608.h:3`) takes 3, and the target sets only `$a0`-`$a2` (`lh a0` / `move a1,v0` /
  `li a2,32`) before each `jal`. The census most likely counted the comma of the nested `func_8012B744(a, b)`
  argument. I checked the other calls against the bytes and found no arity gap.
- **Count first mattered.** Residual 1 is a missing-instruction defect. Residual 2 looks like a register defect
  (`v1`/`a1`/`a0` renames) but is driven by a scheduling ORDER decision plus one missing `nop`. The ready-list
  priorities in `.sched` (the value printed after each insn) settled it. `alloc_table.py` would not have.
- Neither the METHOD nor residual_moves.md lists `birthing_insn_p`/`reg_n_sets` as a mechanism for re-tie launders.
  It belongs next to §21's "zero-byte re-tie" in the cookbook, as the explanation of why a re-tie reorders sched1.
