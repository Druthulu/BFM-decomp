# func_8018594C (ov_SC03_006_jr_8017AE2C.c) — d15, P36 T7 S104

**Result: score 0, ZERO levers** (3 levers before → 0 after: pin $18, pin $3, the hand-placed `move`).
Body: `PACK/body.c` (`u8 *func_8018594C(s16 a0, u8 *a1, s32 a2)`, direct constant stores, `|=` on the flags word).

## (a) The residual, in one sentence
Two independent defects in the lever-free text (16, COUNT): (1) the prologue param copies came out `s2=a0` before
`s0=a2` (target: `s0=a2` first), and (2) the tail's constants/flags word sat in `$a0` with the `0x40000000` in `$v1`
(target: `$v1` / `$a0`), with `move v0,s1` sunk below the first stores instead of right after the call.

## (b) The passes and decisions (all proven on bytes and in the dumps under PACK/scratch/dumps_{free,c1,c5}/)
1. **Tail registers = local-alloc refusal of a reused temp.** The free body's one `v1` variable carried 0xC00, 0x1000
   and the `lw`'d flags word: one pseudo (reg 79) that "dies in 3 places" (`.lreg`), so `local-alloc.c:472`
   (`reg_n_deaths[i] == 1` required) sends it to global-alloc, where it conflicts with `$v0` (the return copy) and `$v1`
   (the lui temp, already local-allocated) and takes `$a0`. Written as direct stores
   (`*(u16 *)(sub + 0x1E) = 0xC00; …; *(s32 *)(sub + 4) |= 0x40000000;`) every value is its own single-death pseudo
   (regs 81/82/84/85 in c5's `.lreg`, all `in 3`), local-alloc hands them `$v1` first and the lui temp (86) `$a0`.
   The `move v0,s1` placement followed for free: with no output/anti chain through one reused pseudo, sched1's
   ready list keeps the return copy (priority 2) behind the LAUNCH_PRIORITY/"potential hazard" stores and it lands at
   the top of the block, right after `jal func_8001CD50` (c5 `.sched`, T-12). This alone scores 4 (`scratch/c1.c`).
2. **Prologue order = assign_parms' deferred conversion insn.** With `a0` declared `s16`, `assign_parms` copies the
   incoming `$a0` to an SImode temp at its turn but queues the HImode narrowing in `conversion_insns`, emitted only
   after ALL parameters are copied (`function.c:3664-3676`, emitted `:3909`). Combine folds the temp copy into it
   (`(set (reg:HI 72) (subreg:HI (reg:SI 4 a0) 0))` at the conversion's position), so the RTL order becomes
   `s0=a2` (insn 10), then `s2=a0` (insn 6), then `a0=23` (c5 `.combine`). sched1 does not move either: the
   function-start loop keeps every leading `SET` from a hard register (SUBREG stripped) out of scheduling
   (`sched.c:3189-3212`). With `s32 a0` the a1 copy is deleted by combine, the resulting NOTE stops that loop after the
   a0 copy, and sched1 moves the a2 copy below `li a0,23` (c1 `.sched`). sched2 then breaks the all-priority-1 tie by
   LUID (`sched.c:2428`), reproducing whichever order sched1 left: target order only with the deferred conversion.
   The callers already pass `*(s16 *)(… + 0x12)` for a0, and a0's only use is the halfword store at +0x12, so `s16`
   is the type the bytes and the call sites both assert. `a2` must stay `s32` (as `s16` the callee re-extends:
   `sll/sra`, score 7 — `scratch/c3.c`).

## (c) The moves (joint — neither alone closes)
- `v1 = K; *(u16 *)(s0 + off) = v1; …` → direct stores `*(u16 *)(sub + off) = K;` and `|= 0x40000000` (→ 4 alone).
- parameter `s32 a0` → `s16 a0` (→ 17 alone on the free body; 0 together).
- Readability only (byte-neutral): `a1` typed `u8 *`, `s0` → `u8 *sub = *(u8 **)(obj + 0x20)`, `ret`/pins/asm dropped.

## Other copies of the class (all proven 0 with --try)
- `src/ov_SC02_011/ov_SC02_011_jr_80188E3C.c` `func_8018D820` — the same s16-param text closes it:
  `scratch/SC02_011_func_8018D820.c` (0). No prototype precedes it in that TU.
- `src/ov_SC03_029/ov_SC03_029_jr_8017FF7C.c` `func_80183F70` and `src/ov_SC03_007/ov_SC03_007_jr_8017AE2C.c`
  `func_8017FD6C` (0x1d variant): the s16-param text is a COMPILE ERROR there because a file-scope
  `extern u8 *func_…(s32 a0, s32 a1, s32 a2);` precedes the definition (029:5677, 007:5632; also declared in
  `ov_SC03_029_jr_80186A34.c:3046/3049` and `ov_SC03_007_jr_80181F94.c:2886`). Two ways:
  (i) keep the signature and narrow in the body — `s16 val = a0;` as the first declaration, store `val` at +0x12 —
  proven 0 on all four: `scratch/SC03_029_func_80183F70_local.c`, `scratch/SC03_007_func_8017FD6C_local.c`,
  `scratch/SC02_011_func_8018D820_local.c`, `scratch/c6.c` (this TU). Same mechanism: the HImode local's
  initialiser is a conversion from the a0 pseudo; combine folds the entry copy into it at the later position.
  (ii) change those externs to `(s16 a0, u8 *a1, s32 a2)` and use the body.c text — NOT tested (changes the callers'
  declarations; must go through the whole-object gate). A plain `(s16)a0` cast in the store does NOT work (4,
  `scratch/c7.c`): the narrowing must be an insn of its own placed after the parameter copies.

## (d) GENERATOR PROPOSALS
- **R-new "reused-temp split to direct stores":** when a lever pins a temp that is assigned ≥2 constants/loads, each
  stored once (`t = K1; *p = t; t = K2; *q = t; …`) and `.lreg` says it "dies in N>1 places", rewrite every
  `t = E; *m = t;` pair as `*m = E;` (and `t = *m; t |= K; *m = t;` as `*m |= K;`) — one single-death pseudo per value
  so `local-alloc.c:472` accepts them.
- **R14 extension "param narrowed at a call site → declare it narrow":** when the prologue's `move sN,aK` pairs are
  in the wrong order (ORDER residual in the first block) and a parameter is only used at a narrower width (stored as
  halfword/byte) and callers pass it from an `*(s16 *)` / `*(u8 *)` load, try that parameter at the narrow width; if a
  file-scope prototype forbids it, a first-declared `s16 v = aK;` local does the same. It must be combined with the
  other moves the sweep finds (R14 alone scored 6/17 here because the tail defect was still open).

## (e) What did not work
- `(s16)a0` cast at the store: 4 (no separate conversion insn).
- `s16 a2` too: 7 (re-extension of the index).
- s16 a0 on the free body without the store rewrite: 17.
- The free sweep's best was 9 (`free_025.c`), history 6 (R12 width v1/s2 u16): width moves on the reused temp do not
  change its death count, so local-alloc still refuses it.

## (f) Where the method fell short
- Nothing in steps 8–12 names the *reused multi-value temp* (a pinned `v1` carrying three values) as the defect —
  S103 c1/c8 covers "split a reused local" for register permutations, but the sweep's R23 apparently never produced
  the store-folded form. The `.lreg` "dies in 3 places" line plus `local-alloc.c:472` settled it in one read.
- ORDER residuals in the PROLOGUE are not covered anywhere: the answer is assign_parms' conversion order plus
  sched1's function-start protection loop (`sched.c:3189-3212`) plus sched2's LUID tie. Worth a row in
  `.run/P36/engine/residual_moves.md`: "prologue param-copy order differs → a parameter's width (deferred conversion,
  `function.c:3664`)".

## (g) Structs answer
Not needed and not the channel here: both levers were an allocation refusal (multi-death temp) and a parameter's
entry-copy order, neither of which reads aliasing. Tested on bytes: a body-local
`struct Sub_8018594C { u8 pad0[4]; s32 flags; u8 pad8[0xA]; s16 f12; u8 pad14[4]; s16 f18, f1A; u8 pad1C[2]; s16 f1E; } *sub;`
with `sub->f1E = 0xC00; … sub->flags |= 0x40000000;` scores 0 with `s16 a0` (`scratch/c8_struct.c`) and 4 with
`s32 a0` (`scratch/c9_struct_s32.c`) — byte-neutral. A struct would have made the natural spelling (direct field
stores) the obvious one, which removes defect 1 as a side effect of style, but defect 2 is a parameter type only.
