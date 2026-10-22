---
ts: 2026-10-22T10:29:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_sM8wwIKY4uzrPOmAsWnA
---
The var dirs were overwritten each round so the mtimes only show the last write. Let me use the known sequence of my work with approximate timestamps:

- Session start ≈ 03:15
- 80184828: 03:16 → 03:53 (37 min) [dump at 03:22]
- 8018483C: 03:53 → 04:01+ (the dump at 04:01) → until ~04:10 (the first variant batch) then more variants at 04:26. So 03:53 → 04:26 = 33 min (with a gap).
- 8017DA30: ~04:10 → 04:26 = 16 min. Hmm! That's < 20 min ✗.

Hmm. The wall requires ≥20 min per item. Let me check: my 8017DA30 work: I read the def and notes at ~04:10, ran the batches (14 + 10 + 9 = 33 tries) at 04:12-04:26. That's ~16 min of wall time. Hmm, marginally under 20.

- 8018389C: ~04:26 → 04:27 (1 min!) ✗✗ Way under 20 min.
- 8017D81C: ~04:27 → 04:27 ✗

Hmm! I blew through the last two items too fast. The brief: "Budget 20-30 min wall per item (date at start/end); past 30 min stop and record a wall; a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)."

Hmm. "Budget 20-30 min wall per item" — the budget is the planned effort; "a WALL needs ≥ 20 min AND ≥ 30 scored tries". So my last two items have 30+ tries but < 20 min wall.

I should spend more time on them to honor the wall requirement. Since the tries are cheap, let me use the time productively: run MORE tries (a wider search) on 8018389C and 8017D81C, and 8017DA30, until each has ≥20 min of wall time.

Hmm, but that means ~15+ more minutes for 8018389C, ~15 for 8017D81C, ~5 for 8017DA30. That's 35 more minutes. Acceptable — and the extra tries could even find a crack.

Let me do that: run several more batches of variants on those three items, with genuine exploration. Let me think about what else to try for each:

8018389C (the division magic):
- The magic's placement: try making the vol division's magic a *shared* temp used by both divisions explicitly: e.g. compute the division as `vol = num * 0x66666667 >> 38`? That's hand-optimized (not "real C" — it's writing the magic by hand; the brief says "real C moves only (C0505 catalog: temps, decl order/scope, s16/u8 widths, loop shape, statement order, init at decl, &&/|| folds, pointer reuse)". Writing the magic by hand is NOT in the catalog → not allowed.
- Try the division as a *helper* variable: `s32 magic = ...` no.
- Try `vol = num / 0xA0;` where num is `u32` (unsigned division → a different magic 0xCCCCCCCD ✗).
- Try different statement orders around the divisions.
- Try moving the vol computation into the enclosing scope.
- Try the `x = (x + 0xA0) / 0x14` as `x = (x + 160) / 20`.
- Try `ax` as u32/s16.
- Try the L.flag check's spelling (which affects the block structure).
- Try the RotTransPers call's args.
- Try the whole inner block's structure (e.g. the `if (L.flag >= 0 && ...)` condition spelling: &&/|| folds are in the catalog!).

Hmm! The catalog mentions "&&/|| folds" — the condition `if (L.flag >= 0 && (u32)((L.sxy[0] + 0x9F) & 0xFFFF) < 0x13F && (u32)((L.sxy[1] + 0x77) & 0xFFFF) < 0xEF)` — folding the && chain into nested ifs changes the block structure and the scheduling! That's a promising move for this item (the residual is about scheduling within the block).

Let me try:
- fold the && into nested ifs
- reorder the && operands
- use `& 0xFFFF` variants

Similarly for 8017D81C: hmm, its residual is the constants' birth. What else could I try?
- the do-while → for/while (tried)
- the store order (tried)
- the constant's spelling (tried)
- Hmm: what if the constants were assigned to variables that are *declared* as `s16`? (the values don't fit)
- What if the three constants were stored via a *loop*? e.g. a loop storing the constants? That changes the asm ✗.
- What if the assignments were moved before the `func_8001C2C4(v)` call? Let me try that (the values don't depend on the call — semantically it's fine as long as the call doesn't... hmm, the call could modify globals but not x/y/z). Actually the decompiler placed them after the call, but semantically they could be before. Then the constants' pseudos would be live across the call → callee-saved regs ✗ (probably a big mismatch). Let me test it anyway.
- What if the constants were assigned at the top of the function (before `v = func_8012C1B8()`)? Same issue.
- What if `x`, `y`, `z` were assigned in a different block (e.g. inside the `if (v == 0)` block)? no.

Hmm, let me also try for 8017D81C: what if the *stores* of x/y/z came first but the other stores were reordered by the scheduler? (w17 = 12: the li's early ✓ but the store order wrong.) Hmm! What if I put only "D_80192CE0 = x" first (w28 = 12) and then let the scheduler reorder the stores? It gave 12 — the stores stayed in the source order.

Hmm, what if the scheduler could reorder? gcc's sched2 generally doesn't reorder stores (it prefers to keep memory ops in order to avoid aliasing issues) ✗.

Hmm. OK, for 8017D81C let me try a few more things:
- The three x/y/z stores moved first but with the other stores reordered to match the target — impossible.
- What if x/y/z were assigned inside the *do-while loop*? no.

Hmm, let me think about 8017D81C differently: the target's li's are at 19-21 in $v1/$a1/$a0. Hmm, $a1 for y! Interesting: why would y be in a1 (an argument register)? Because the launder's asm had 2 outputs (y and z) and gcc allocated them to a1 and a0.

Hmm, hmm. What if y and z were *call arguments* somewhere? Hmm, the call `func_8012C1B8()` has no args; `func_8001C2C4(v)` has one (v in a0).

Hmm! What if the constants were passed as arguments to a call? Then they'd be in a0/a1/a2 — but the target's x is in v1 (not an arg reg).

Hmm, what if x/y/z were *declared* in the reverse order (z, y, x)? The allocation order might change: the target's order of materialization is x(v1), y(a1), z(a0) — hmm, if the allocation gave them v1, a1, a0 in that order...

Hmm, since the li's placement is the core issue, let me try: what if the constants' *uses* were in a different order so that the first uses are all early? E.g. if the three stores CE0/CE4/CE8 came first (w27 = 15) — hmm.

Let me try yet another approach for 8017D81C: make the constants' first uses early WITHOUT changing the store order — by using the constants in the *loop* or in a *dead* computation... no (levers).

OK: for the extra ~15 min on 8017D81C, let me run a broader batch of legitimate variants (types, spellings, orders, loop shapes, declaration scopes) — maybe 25 more tries.

Similarly for 8018389C: broader batches including && folds.

And for 8017DA30: a few more batches.

Let me do these now, in 2-3 bash calls, with enough variants to fillthe time.
