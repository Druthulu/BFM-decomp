# func_8002AAB4 (src/800.c) — e29, P36 S104 — SCORE 0, zero levers

(a) Residual (lever-free 18 / sweep best 17, COUNT): (1) the prefix — the hand-expanded rounding division put the sum in
s0/s2 and reordered the call-result copies (the tree pinned s1/s2/v0); (2) the table walk's threshold/pointer registers
swapped (a0<->v1, the tree pinned v0/v1).

(b) Two mechanisms, both proven on bytes:
  1. `x / 4` is expanded by expmed.c:2979-2995 (`abs_d != 2 && BRANCH_COST < 3`): `t1 = copy_to_mode_reg(op0)`, a
     `bge` around `t1 += 3`, then `expand_shift(t1, 2, tquotient)`. The copy `t1` is a fresh pseudo that ties to the sum's
     register (v0, d's register) while the quotient goes to its own pseudo (s0). The hand-rolled `if (v<0) v+=3; s0=v>>2`
     with the tree's reused names gives the allocator a different pseudo web. The same-TU sibling func_80029FE4
     (`return (a + b + c + d) / 4;`) has the identical first 19 instructions — the prefix is that function inlined by hand.
  2. The walk's two stepped registers (v1 = &tbl[i].thr, a1 = &tbl[i].val, both +8 per trip, the exit test on the
     loaded threshold) are loop.c strength reduction of an INDEXED access: `i` is a biv used only in addresses, two givs
     `D + 8i` and `D + 8i + 4` (record_giv loop.c:4341; not combined, different add_val), and the biv is eliminated.
     The threshold must be read ONCE into a named temp (`thr`) — reading `D[i*2]` twice (c2) keeps a second load (46 ins).

(c) Moves: prefix → four call results in four locals + `avg = (a + b + c + d) / 4;` (the sibling's text); walk →
    `for (i = 0; (thr = D_800638A0[i * 2]) != 0; i++) { if (avg >= thr) return D_800638A0[i * 2 + 1]; } return D_800638EC;`
    The `while` spelling and a `thr` read before the loop and at the bottom both also score 0 (scratch/d2.c, d3.c).

(d) GENERATOR PROPOSAL: when a body contains `if (v < 0) v += 2^k-1; x = v >> k;` rewrite it as `x = v / 2^k` (and, when
the operand is a sum of call results, one local per call); when a loop steps two pointers into one table by the same
stride (`p += 2; q += 2;` with `q = p + 1`), rewrite as an index `i` with `tbl[i*S]` / `tbl[i*S+K]` and the loop-test load
kept in one named temp.

(e) Did not work: pointer walk `for (p = D; p[0]; p += 2) … p[1]` (22: p[1] folds into `lw 4(p)`, one biv, and p[0] is
re-read); index without the `thr` temp (15: second load); tree names + `/4` (15: the call-copy order still wrong because
`s0` is reused for the first result and the quotient); a body-local struct-pointer view `tbl[i].thr` (26 / 15 with `thr`).

(f) Method gap: the "hand-rolled division = `/ 2^k`" line in METHOD step 16 was the right start but not sufficient — the
sibling that shares all four callees (related.txt's first hit) gave the whole prefix; the loop needed the idea "two
stepped pointers into one table = two givs of one index", which S103 c2 states only in the opposite direction.

(g) Structs: D_800638A0 is plausibly `struct { s32 thr; s32 val; } D_800638A0[10]` (0x48 = 9 entries + a 0 terminator,
and D_800638EC = D_800638A0 + 0x4C is the TERMINATOR's `val`). TESTED on bytes with a body-local struct-typed alias
(`extern Rank D_800638A0_rank[] __asm__("D_800638A0");`, scratch/d6.c, d8.c): WORSE — 22 / 20. With the struct array the
field reads are emitted as `lui at; addu at,at,i*8; lw 4(at)` (symbol + scaled index, no pointer givs), while the
`s32 D[]` + `i * 2` spelling gets two strength-reduced pointer givs like the target. A body-local struct POINTER view
(`tbl = (void *)D_800638A0`, d4/d5) was also worse (26 / 15). So for this function a struct type would NOT help; the
original indexed a flat s32 array (or the struct phase must keep this global flat).
