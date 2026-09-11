# func_801831FC — e7 (P36 T7 S104) — score 6 (sweep best 6) -> 0, ZERO levers (was: 1 NEEDED `$2` pin)

(a) Residual: REG, 8 insns: the product `(0x800 - d) * 127` (expanded `t = 0x800-d; u = t<<7; r = u - t`) and the
following `+0x7FF` / `>> 11` live in `v1` in the lever-free text, in `v0` in the target. Counts equal (62/62).

(b) Pass/decision (dump-verified, `scratch/dumps_free`, `scratch/dumps_d4`; `tools/alloc_table.py`):
  The decompiler text spells a SIGNED DIVISION BY 0x800 by hand (`if (v0 < 0) v0 += 0x7FF; v0 = v0 >> 11;`) and writes
  the shift back into the same variable, which is ALSO the call-result variable. The dividend pseudo (free r74, global —
  it spans the conditional add) then has one preference only: the minus's first operand `u` (`set_preference`,
  global.c:1535, `src = XEXP (src, 0)` for a non-copy at :1545-1546) = `v1` -> `find_reg` gives it `v1`.
  Written as `q = (0x800 - dist) * 127 / 0x800;`, `expand_divmod` makes the dividend a fresh temp (d4 r109) and the
  QUOTIENT a separate pseudo set by `(ashiftrt r109 11)` (insn 120, REG_EQUAL `div … 2048`). The quotient is
  block-local, local-alloc puts it in `v0`, and `set_preference (r74=v0, (ashiftrt r109 …))` gives r109 a SECOND
  preference, `v0` (d4 table: "r109 prefers v0,v1"). `find_reg`'s preference scan runs from hard reg 0 upward
  (global.c:1043-1044), so `v0` (2) is taken before `v1` (3) — the target.

(c) Moves (joint; each alone scores 6):
  - the hand-expanded division -> `/ 0x800` into a NEW variable `q` (d3: new variable, hand shift: 6);
  - the call result straight into the `s16 dist` (no shared `v0` temp; d1: `/ 0x800` but the quotient still the
    call-result variable: 6).
  body.c also renames (`dist`, `q`, `vol`) and drops the `s0 = arg0` copy (both byte-neutral, d5/d6 = 0).

(d) GENERATOR PROPOSAL: when the text has `if (x < 0) x += 2^k-1; x = x >> k;` (the gcc signed-pow2 division
expansion, `expmed.c` expand_divmod), rewrite it as `y = <x's expression> / 2^k;` into a fresh local and route the
x-producing call result into its own typed local — a decompiler-undone division; the quotient's separate pseudo adds a
`set_preference` that steers the dividend's register.

(e) Did not work: d1 (`/0x800`, quotient = the call-result variable) 6; d3 (fresh `q`, hand-written add/shift) 6; the
sweep's R4/R6/R7/R8/R9 moves all 6 (none undoes the hand-expanded division).

(f) Method: the allocation table's "prefers" column was the whole answer (free r74 "prefers v1" only; d4 r109 "prefers
v0,v1"). No METHOD row covers "a hand-expanded division"; add one: `bgez; addiu 2^k-1; sra k` in the target = write `/`.

(g) Structs: no. The decision is global.c preferences between pseudos of one arithmetic chain; the `D_8018E8EC[idx]`
8-byte record (`s16 +2`, `s16 +6`) as a struct would not change it.

BONUS (other TU, read-only test): the same shape in `src/ov_SC02_011/ov_SC02_011_jr_80183178.c` func_80188034 (also a
NEEDED `$2` pin, "tus9") closes at 0 with the same move plus the clamp as `if (q < 0) a1v = 0; else a1v = q;` and
`a1v` declared `s16`: `scratch/sib3.c` (`--try … func_80188034 scratch/sib3.c --body` -> score 0). sib2 (same but
`s32 a1v` with `(s16)` casts) scores 9.
