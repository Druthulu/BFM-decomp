# func_80181294 — e7 (P36 T7 S104) — score 10 (sweep best 9) -> 0, ZERO levers (was: 1 NEEDED `$2` pin)

(a) Residual: COUNT 191 vs 192 + v1->v0 on the first loop's jitter value: the target keeps `v = ±t` in `v0`
(`bnez v0,…; move v0,s0` / `negu v0,s0` / `sh v0,16(sp)`), the lever-free text in `v1`; the knock-on moves the second
jitter (`±t2 + 0x40`) into a cross-jumped shape one insn shorter.

(b) Pass/decision (dump-verified: `scratch/dumps_body_free`, `scratch/dumps_e10`, `.lreg`/`.greg`):
  `if ((rand() & 1) == 0) v = -t; else v = t;` is an if/else whose ELSE value is a plain REG, so jump1's
  "`if (...) x = a; else x = b;` -> `x = b; if (...) x = a;`" transform (jump.c:699-760; the REG destination test at
  :731, the REG/SUBREG/constant source test at :739-741) HOISTS `v = t` above the `andi v0,v0,1; beqz` test (free
  `.lreg` insn 479 `(set r121 r76)` sits between the `rand` call_insn 165 and the `and` insn 168). The hoisted copy is
  born while the call result is still live in `v0`, so the variable (free r121, shared by both jitter sites, 12 refs) conflicts
  with hard `v0` (`.greg` ";; 121 conflicts: 72 74 75 76 121 2 29") and global gives it `v1` ("121 in 3").
  Written as `sp10[0] = cond ? -t : t;`, the conversion to the `u16` slot is folded into the arms and the COND_EXPR is
  expanded into a HImode temp (e10 r131, "2 bytes"): the negated arm's destination is `(subreg:SI (reg:HI 131) 0)`, a
  SUBREG, so the transform's `SET_DEST == REG` test (jump.c:731) fails, the copy stays in its arm, the temp never
  conflicts with `v0` (";; 131 conflicts: 72 74 75 131 29"), prefers `v0` and gets it ("131 in 2"). Reorg later fills
  the branch delay slot with the arm's `move v0,s0` — the target's shape.

(c) Move (one): the first jitter as a conditional expression stored straight into its slot:
  `sp10[0] = ((rand() & 1) == 0) ? -t : t;` (scratch/e10.c: this move ALONE scores 0). body.c spells the second
  jitter the same way for uniformity (`sp10[2] = ((rand() & 1) == 0) ? -t2 + 0x40 : t2 + 0x40;`, e5 = 0; also
  `(… ? -t2 : t2) + 0x40`, e9 = 0). The `s32 v` local is gone.

(d) GENERATOR PROPOSAL: when a local is assigned in an if/else whose else arm is a plain register copy
(`if (c) v = -x; else v = x;`) and then only stored to a narrower (u16/s16/u8) memory slot, rewrite the pair as
`slot = c ? -x : x;` — the narrowed COND_EXPR temp is a SUBREG destination that jump.c's if-conversion (:731) refuses,
so the copy is not hoisted above the test (the inverse of S104 d1's "never a ternary", which was for a full-width
value).

(e) Did not work: e1 (two locals `v`/`w`, if/else) 3; e4 (first if/else via `v`, second stores direct) 3; e2/e3
(if/else storing straight to `sp10[0]` in each arm) 9 COUNT — two stores, cross-jump shape differs; e6 (one `t` for
both modulos) 14; e11 (`v = c ? -t : t; sp10[0] = v;` — SImode ternary into the variable) 10: the SImode COND_EXPR
has a REG destination and jump1 hoists it the same way. The sweep's R7/R8/R10/R12 moves best 9.

(f) Method: the header's lever note 1 ("as a plain local it is a global_alloc allocno and lands in $v1") was TRUE but
named the symptom; the cause is jump1's if-conversion hoisting the else copy. METHOD S104 (d1) points the other way
("never a ternary", for a full-width value set before a call); the distinguishing fact is the narrowing store.
The header comment's claim 3 (the `+0x40` must be in both arms) is also refuted on bytes (e9 = 0).

(g) Structs: no. `sp10` is a `u16[3]` local; a struct (x/y/z) would keep the HImode store and the same jump1 decision.
The decision is the if-conversion's destination-code test, not memory aliasing.
