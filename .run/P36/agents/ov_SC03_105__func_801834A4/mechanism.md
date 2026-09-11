# func_801834A4 — e32 (P36 S104) — at 0 with NO pin and NO asm; two marked dead statements remain

`body.c` (= `body_minlever.c` = `scratch/n1.c` + marks): `--try` score 0 (106/106).
Levers before: 3 marked (`tmp` pin `$2`, `hh` pin `$2`, a launder on `tmp`) + 2 UNMARKED dead statements
(`s32 sign = 0;`, `sign = half >> 31;`). After: 0 pins/asm; the same 2 dead statements, now marked `// !FAKE:`.
Strictly by the brief this is a minimum-lever body (the dead store steers cse), not a plain-C close — see (e).

(a) Residual (lever-free 41): two independent defects.
 1. The base copy: target `addiu v0,v0,8192; move s6,v0; sll v0,v0,16; sra s2,v0,18` (the modulus reads the PRE-copy
    sum); mine computed `base` straight into `$s3` and shifted from it.
 2. The inner-loop `/3`: target keeps `lui/ori 0x55555556; mult s4,v0; mfhi; subu` INSIDE the loop and hoists only the
    sign correction `sra s5,s4,31`; mine hoists all of it (K, B, C, D) and, with the outer loop now 58 insns instead of
    62, loop.c also hoists `&D_8018E894` (`29*1*2 = 58 >= 58`) and strength-reduces the table walk into a pointer.

(b) Passes:
 1. `mod = (s16)base >> 2` is the same fact as func_80183DA0's level: `base` is only ever used through a 16-bit
    truncation (`(s16)(base + rand() % mod)`), so it IS `s16`. An `s16 base = u * 0x600 + 0x2000;` is a HImode pseudo:
    expand computes the SImode sum in a temp and stores its low part — a SUBREG move cse cannot fold
    (`cse.c:7440-7474` folds only same-mode REG copies, S103 c4) — and `base >> 2` extends from the temp. PROVEN:
    this one declaration replaces the `tmp` pin AND the launder (tree 3 levers → 1, `scratch/k1.c`, score 0).
 2. loop.c `scan_loop` (`loop.c:696-706` movable criteria; `move_movables` desirability `loop.c:1640-1650`,
    `threshold*savings*lifetime >= insn_count`, 29*…; `force_movables` links the constant K to the mult B and doubles its
    savings). K stays only if B is NOT a movable. B is not a movable when its dividend is a USER VARIABLE assigned inside
    the loop after the first conditional jump (`maybe_never`), used outside that block — criteria (1)/(2)/(3) all fail.
    `step = half; pos[0] -= step / 3;` does that: `step` is also set in the outer body, so `reg_in_basic_block_p` fails,
    and cse keeps `step` (not `half`) as the quantity head because `step` lives longer and beyond the block
    (`cse.c:846-862`) — so B reads `step`. The `.loop` dump (`scratch/dumps_n1/fn.loop`) shows
    `Insn 164: possible biv, reg 78, const = (reg/v:SI 80)` (the copy) and no B movable; K is "not desirable" (life 1).
    The sign correction C `(ashiftrt step 31)` hashes into the same quantity as `half` and is replaced by the register of
    an earlier `sign = half >> 31` (cse), which IS a movable (top of the body, maybe_never==0) and is hoisted
    (`Insn 105 … moved`). PROVEN on bytes and in the dumps (n1: 0; without `sign`: 23; without `= 0`: 23).
    This replaces the tree's `hh` `$2` pin: a hard-register dividend was the lever's way of making B non-invariant
    (`invariant_p` returns 0 for a call-used hard reg in a loop with calls); a re-assigned user variable does the same.

(c) Moves:
 1. `s32 base; tmp = …; base = tmp; launder(tmp); mod = (tmp << 16) >> 18;` → `s16 base; base = u * 0x600 + 0x2000;
    mod = base >> 2;` (drops the `tmp` pin + launder). 41-class → k1 at 0 with only the `hh` pin left.
 2. `register s32 hh __asm__("$2"); hh = half; pos[0] -= hh / 3;` → `step = half; pos[0] -= step / 3;` (the variable
    `step` REUSED; `hh` deleted). 0 with no pin.
 3. `sign` kept exactly as the tree had it (`= 0` initialiser + the unread `sign = half >> 31;` at the top of the inner
    body), now marked. No `tmp`, no `hh`.

(d) GENERATOR PROPOSAL: (1) when a local is used ONLY through `(s16)`/`<< 16 >> N` truncations and the residual shows a
missing `move sK,vN` after its definition, retype it `s16` and drop the casts (a SUBREG store survives cse);
(2) when the target keeps a loop-invariant constant division's `lui/ori/mult/mfhi` inside a loop but mine hoists it, and
the tree pins the dividend to a hard register, replace the pinned copy with a re-assignment of an EXISTING outer-scope
variable (`v = inv; … v / K`) placed after the loop's first conditional — loop.c then has no movable to link the
constant to.

(e) Refused / did not work (bytes):
 - Every natural spelling of the `/3` hoists the whole division (h1/h2 and v1–v7, w1–w2: for/while/do, division in
   the for-increment or the exit test, `step * 2 / 3` inline, counting down): 40–41.
 - `sign` is the remaining fake: the target hoists ONLY the sra, which needs an `(ashiftrt half 31)` computed before
   the division in the same cse block, and no live C expression has that value without emitting code. `sign` in the
   outer body (n6), block-local `s32 sign = half >> 31;` (n4), no initialiser (n3), the store into `obj` (n5): 23;
   into the dead-by-then `u` (n7): 19 (register class). A manual `(s64)` high-part multiply would be hoisted too.
   So: 0 pins/asm, 2 dead statements. Report, not a plain-C claim.
 - `(i << 2) + (s32)D_8018E894` cast table read (g1): 39 — it lets strength reduction turn `i` into `i*4`; the
   outer-loop defects are a CONSEQUENCE of the inner hoist (insn_count 58 vs 62), not their own lever.

(f) Method: the header's own analysis (`hh`/`sign`) was right about the pass; what it missed is that "B's dividend must
be non-invariant" has a plain-C spelling (a re-assigned user variable) — the S104 d14 "the original REUSED variables"
note, applied to loop.c instead of local-alloc. The `.loop` dump (`-dL`) settled it; the allocation table was not needed.

(g) Structs: no. Both defects are about pseudo registers (a HImode store; a loop-invariant dividend), not memory
accesses. `pos` as a struct would not change loop.c's movable analysis of registers.
