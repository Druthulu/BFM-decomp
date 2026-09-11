# func_8017FCFC (ov_SC02_017) — e9 (P36 T7 S104) — score 10 (sweep best 2) -> 0, ZERO levers
(was: NEEDED pins `$3` + `$0` on `u = t + zr`, a NEEDED `launder` on `p`, and a `(void)&frame_pad` dead pad)

(a) Residual: COUNT 79 vs 80, two independent defects. (1) The `+0xFE` countdown: target `lh v0; beqz; move v1,v0;
addiu v0,v1,-1; j; sh v0` — a copy the lever-free text folds (`beqz; addiu v0,v0,-1`). (2) The table base
`&D_8018E204` (held in `$s1` for the `k == 0xC` arm): target `lw a0,0(at); la s1,D_8018E204; jal func_800291B4; nop`,
lever-free `jal …; nop; andi v0,v0,0xff; la s1,…; beqz` (ORDER).

(b) Pass/decision (dump-verified: `scratch/dumps_free`, `dumps_tree`, `dumps_c1`, `dumps_e1`, `.sched` ready-list traces):
  1. The countdown as a memory decrement `*(s16 *)(a0 + 0xFE) -= 1` of the value already tested: the test reads the
     halfword sign-extended into an SImode pseudo (e1 `.lreg` insn 12, `extendhisi2`) and the decrement works on a
     HImode copy of it (insn 13 `(set (reg:HI 74) (subreg:HI (reg:SI 75) 0))`) — a SUBREG move, which cse's
     `(set REG0 REG1)` handling (cse.c:7440-7474, it wants same-mode REGs) does not fold: the target's `move v1,v0`.
     The same text also brings a pseudo with no insns that reload gives a stack slot (e1 `.lreg` r76 "dies in 0
     places", reload1.c:2327-2352), so the 48-byte frame comes out without the tree's `(void)&frame_pad` pad.
  2. sched1's lifetime heuristic `adjust_priority` (sched.c:2507-2547) raises an insn to the block's max priority when
     `birthing_insn_p` (sched.c:2469-2490) holds: a SET of a REG that is live after it with `reg_n_sets == 1`. The base
     pseudo (`rN = D_8018E204`, which expand makes for the array index and cse1 extends into the `k == 0xC` arm) is
     always birthing. The decompiler's `t` holds the call result AND the counter AND 8 AND 0x8C00 (`reg_n_sets > 1`),
     so the call result's `andi` is not: at T-2 the ready list is `base-set (7f000001), andi (3)` (c1 `.sched`) and the
     base set goes last, after the call. With the result tested inline (or in its own variable) the `andi` is
     birthing too: `62 (7f000001) 69 (7f000001), now 69 62` (e1 `.sched`) — the `andi` takes T-2, the base set lands
     before `jal` (as `la` it is two words and cannot fill the delay slot, so the `nop` stays). The tree's launder
     faked exactly this by giving `p` a second set (`reg_n_sets == 2`, not birthing).

(c) Moves (each closes its own defect; together 0):
  - the countdown `t = *(s16 *)(a0+0xFE); if (t != 0) { u = t + 0; t = u - 1; store; }` -> `if (*(s16 *)(a0 + 0xFE) != 0)
    { *(s16 *)(a0 + 0xFE) -= 1; return; }`, and the `frame_pad` local and its `(void)&` statement deleted
    (b2n = 0 with the launder still in; with the pad kept the frame is 56);
  - the call result tested inline: `if ((func_800291B4(D_8018E204[… & 0xF]) & 0xFF) != 0)` — no shared `t`
    (d2 `s32 r` / d3 `u8 r` in their own variable also 0).
  Byte-neutral cleanups (e1 = 0): `p` deleted (the arm indexes `D_8018E204` directly — cse1 makes the shared base
  itself, c1), every `t = 8; store t` -> `store 8`, `t = 0x8C00` -> a direct store; `t`/`u` gone.

(d) GENERATOR PROPOSAL: when a `launder` sits on a pointer/constant local whose only other set is `p = &GLOBAL` before a
call, and the residual is ORDER (the `la` after the call instead of before it), look for a variable REUSED for the
value tested right after that call (`t = f(…) & M; if (t …)` with other `t = …` sets) and give the call result its own
single-set name or test it inline — both insns then carry sched1's birthing boost and the tie goes to the test.
Also (R-new, "countdown"): `t = *(T *)(p+K); if (t) { u = t + 0; t = u - 1; *(T *)(p+K) = t; }` with a `$0` pin ->
`if (*(T *)(p+K) != 0) *(T *)(p+K) -= 1;` for a narrow `T`.

(e) Did not work: counter spellings with the `frame_pad` kept (b2/b3/b6: 8, frame 56 vs 48); `t - 1`, `--t`, `u = t--`,
`u = t` copies (b1/b4/b5/b7: 6); `u16 u` (b8: 2, an `andi 0xffff` instead of the move); every `p` spelling without the
launder while `t` is shared: `p` kept (c0 4), no `p` (c1 4), first call through `p` (c2 4), `p` set after the call (c3 4),
a second `p = D_8018E204;` in the arm (c4/c5/c6 4 — cse removes the redundant set, so `reg_n_sets` stays 1).
`func_80178BF8();` without the `(void (*)(void))` cast: 4 (ORDER) — keep the cast.

(f) Method: METHOD c4 ("a copy into HImode is a SUBREG move and survives") was the counter row. Nothing in METHOD covers
the second defect: `birthing_insn_p` is named only for the width of an incremented local (d8); here the fix was a
variable's SET COUNT on a DIFFERENT insn that competes for the same ready slot. The `.sched` ready-list lines
(`ready list at T-2: … (7f000001) … (3)`) were the deciding evidence; the allocation table was irrelevant (ORDER).
The frame pad was an unlisted lever (not in sites.txt).

(g) Structs: no. Both decisions are about scalar locals (a HImode SUBREG copy; sched1's per-register set count);
the object's `u16 +0x5C/+0x5E/+0x70`, `s16 +0xFE`, `s32 +0x58/+0xDC` fields as a struct would change spelling only.
