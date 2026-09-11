# func_8017E2CC (ov_SC04_015_jr_8017AE2C.c) — e33, P36 T7 S104 — SCORE 0, ZERO levers (was 2 pins)

(a) Residual (score 14, same 134 ins, REG + one moved copy, in BOTH copies of the volume block): the hand-expanded
`v0 = 0x300 - v1; v1 = (v0 << 7) - v0; … v1 / 512` put the difference in `$a1` and the product in `$v1`/`$v0`, and in
the first copy the signed-division copy became `move a1,v1` instead of adjusting the product in place
(`addiu v1,v1,511; sra a1,v1,9`). The tree pinned `v0`/`v1` to `$2`/`$3` to fake the target's assignment.

(b) Pass: the text is decompiler output of an expander idiom. `x * 127` is synthesised by expand_mult (synth_mult,
expmed.c) into a shift/subtract with its OWN single-use temps, and a signed `/ 512` is expanded by expand_divmod
(expmed.c:2979-2995: `t1 = copy_to_mode_reg(op0); if (t1 >= 0) goto L; t1 += 511; L: t1 >> 9`). When op0 is a
single-use expander temp that dies at that copy, local-alloc ties t1 to it (combine_regs, local-alloc.c:1722) → the
in-place `addiu v1,v1,511`; when op0 is a user variable (the tree's re-assigned `v1`, or a named product variable,
variant B/C = 4) the tie is lost and the copy survives. (The tie claim is read from the source, not dumped; the bytes
prove the spelling.)

(c) Move (proven, --try 0): write the arithmetic as the programmer did —
`func_8002D4C8(0x76C, (((0x300 - t) * 127) / 512 & 0x7F) | 0x1000);` in both copies; `v0` deleted; the remaining
temp `v1` renamed `t` (it only holds D_801C8B78). Both pins gone.

(d) GENERATOR PROPOSAL: when the text has `b = a0 - x; c = (b << k) - b;` (or `(b << k) + b`) feeding a signed
`/ 2^n`, collapse it to `(a0 - x) * (2^k ∓ 1) / 2^n` inline in its single use (R-family "un-synthesise a multiply"):
a hand-expanded synth_mult sequence is never the original, and its named temps break the expander's copy ties.

(e) Did not work: keeping a named product `v0 = (0x300 - v1) * 127;` (4) or reusing `v1` for it (4); the sweep's
inline/decl moves (best 13).

(f) Method: nothing in METHOD covered "a hand-expanded multiply"; step 16's `if (v < 0) v += 2^k-1; v >>= k` is
`v / 2^k` is the sibling rule — extend it to "`(b << k) - b` is `b * (2^k - 1)`".

(g) Structs: not relevant — no memory access involved in the residual (pure arithmetic on a loaded global).

Copies in other TUs: none (`grep -rn 'func_8002D4C8(0x76C, (' src/` → this TU only).
Files: body.c (0), scratch/v/{A,B,C,D}.c.
