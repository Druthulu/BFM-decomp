# func_801A3B18 (md_SC07_004) — P36 S104 agent e8 — score 23 (lever-free) -> 0 with ZERO levers (was 1 `$0` pin)

(a) Residual: 145 vs 146 ins + a 4th callee-saved register missing (frame 104 vs 112). Lever-free, `ang` (the 12-bit angle
sign-extended to 16) and `mag` (its absolute value) share ONE register (`move s0,v1; ori v1,..; move s0,v1; ...; negu
s0,s0`); the target keeps them apart: `ang` in `$a0` (dies before the call), `mag` in `$s2` (`move s2,a0` in the bgez delay
slot / `negu s2,a0`), which pushes `p` to `$s3`. The tree's `ang = e + zr; mag = ang + zr;` pin faked two non-copies.

(b) Pass and decision (read in `scratch/dumps_good/good.i.rtl` / `.lreg`, and the free dump):
- The tree's `mag = ang; if ((s16)ang < 0) mag = -ang;` with s32 locals: cse records `mag == ang` at the copy and rewrites
  the `-ang` read as `-mag` (`make_regs_eqv`/`canon_reg`, `cse.c:846-862`), so `ang` dies at the copy and the two share a
  register. Free dump: `ang` "used 3 times across 6 insns", `mag` 5 times.
- Written as `if (ang < 0) mag = -ang; else mag = ang;` with s32, jump1 converts it straight back to `x = b; if (...) x = a;`
  (`jump.c:696-760`: the `x = a` arm must be ONE insn right after the condjump — `temp = prev_active_insn (temp3)` must be the
  condjump, `jump.c:750`) and the same cse fold follows (score 23, `Cb_s32_s32_s32`).
- With `s16 mag`, `mag = -ang` expands to TWO insns (`neg:SI` into a temp, then `(set (reg:HI mag) (subreg:HI ...))`,
  good.i.rtl insns 153/155), so the jump1 condition fails, the copy stays in the else arm, `-ang` keeps reading `ang`, and
  `ang` "dies in 2 places" (good .lreg: reg 76 used 5 times, 2 bytes; reg 77 = mag, crosses 2 calls) — two registers, as the
  target. With `s16 ang` too, the 0xF000 sign-extend and the `(s16)` tests are HImode and the extra `move` disappears.

(c) Moves (joint — proven; every single step scores worse than 0):
1. `if (ang < 0) mag = -ang; else mag = ang;` for `mag = ang; if (...) mag = -ang;` (alone with s32: 23; with s32 mag: 6);
2. `ang` and `mag` declared `s16` (the bytes: every test of them is on the sign-extended low half) — both needed
   (`Cb_s16_s32` = 4, `Cb_s32_s16` = 6, `Cb_s16_s16` = 0);
3. readability: `e` deleted (`ang = d & 0xFFF; if (ang >= 0x800) ang |= 0xF000;`), `d` inlined into it, the redundant
   `(s16)` casts on ang/mag dropped. body.c = this, score 0.
A sweep of 648 spellings (scratch/sweep_am.py: 6 ang shapes x 6 mag shapes x widths) found 20 at 0 — every one uses the
if/else mag AND s16/u16 for both ang and mag (or the ternary `Af` with u16/u16).

(d) GENERATOR PROPOSAL: when a `$0` pin feeds `y = x + zr; if (c) y = f(x);`, delete the pin, rewrite as
`if (c) y = f(x); else y = x;` and give x and y the 16-bit width their `(s16)`/`(u16)` uses prove — the narrow destination
makes the then-arm two insns, which blocks jump1's re-merge (`jump.c:750`) and keeps cse from folding x into y.

(e) Did NOT work: the free sweep's best 6 (R9 swap + R12 mag u16) — width alone with the copy-then-if shape stays at 6/20;
the if/else alone at s32 is 23 (jump1 undoes it); `mag = (s16)ang < 0 ? -ang : ang` with s16/s16 is 29.

(f) Method gap: METHOD step 14's "declare y at the proven width" was half of it; the other half was a d1-style if/else (step
12), and d1's rule "the non-simple value in the ELSE arm" is the wrong way round here — what matters is whether the
`x = a` arm is ONE insn (a narrow destination makes it two). Generators R12 (width) and the if/else rewrite were never applied
JOINTLY; a 648-body enumeration (~3 min) found it where reasoning alone would have stopped at the width move.

(g) Structs: NO for this lever — `ang`/`mag` are scalar locals; the decision is jump1's single-insn arm test and cse's
copy equivalence, no memory access is involved. `param_1` as an object struct (0x06/0x0A/0x0E s16 position, 0x20 pointer to a
sub-object with s16/u16 at 0x12) is readability only; not tested on bytes (nothing left to close).

(h) Joint check (e8): all four e8 body.c files spliced into one copy of the tree TU (`md_SC07_004__func_801AB78C/scratch/splice4.py` -> `scratch/tu_all4.c`): each of the four scores 0, and the whole object is sha1-identical to the baseline per section (.text ad583f4dfb0c, .rodata, .data/.sdata/.bss) with .rel.text identical.
