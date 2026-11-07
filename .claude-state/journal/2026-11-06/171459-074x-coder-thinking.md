---
ts: 2026-11-07T00:14:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_acEfqKeCKpqNFRk04aTF
---
In the pinned body:
- r76 (base) → s3 (19)
- r78 → s5 (21)
- r79 → s1 (18)
- r72 → s1 (17)... wait r72 in 17 (s1) and r79 in 18 (s2)? Let me recheck the numbering: 16=s0, 17=s1, 18=s2, 19=s3, 20=s4, 21=s5.

So: r72→17 (s1), r73→18 (s2), r76→19 (s3), r78→21 (s5), r79→18 (s2), r89→2 (v0).

Hmm, r73 and r79 both in 18 (s2) — different live ranges.

So the target's s1 = r72, s2 = r73/r79, s3 = r76 (base), s5 = r78.

Which pseudo is x0? x0 must be r72 (s1) — the target's x0=s1! And r73 (s2) = ? and r79 (s2) = y1.

Hmm: target regs x1=s0 (pinned, no allocno), x0=s1 (r72), y1=s2 (r73 or r79), base=s3 (r76), white=s4 (pinned), y0=s5 (r78).

r72 has live 12, refs 3. r73 live 4. r79 live 31.

Hmm, x0 live 12? That's short. And y1 live 31 (r79) or 4 (r73)?

Hmm, this is confusing. Let me reconsider: maybe r72 = y0? No, y0=r78 (live 32, s5).

Let me think: x0 is used in the struct stores (line.x0 = x0) and born at `x0 = a0-3` (late, last statement). So x0's live is short (12) → r72 (live 12) = x0 → s1. ✓

y0 = a1-3 (born first) → live 32 → r78 → s5. ✓
y1 = a1+3 → live 31 → r79 → s2. ✓
base → live 42 → r76 → s3. ✓
white pinned s4. x1 pinned s0.

So the natural order among {x0, y0, y1, base}: the regs are s1(x0), s2(y1), s3(base), s5(y0).

Available after pins: s1,s2,s3,s5 (s4 pinned, s0 pinned).

Allocation order by reg: x0→s1, y1→s2, base→s3, y0→s5.

pri: x0 (live 12, refs 3): floor_log2(3)*3/12 = 1*3/12 = 2500. y1 (31): 967. base (42): 714. y0 (32): 937.

Order by pri: x0 2500 > y1 967 > y0 937 > base 714.

Expected first-fit to s1,s2,s3,s5: x0→s1, y1→s2, y0→s3, base→s5.
Actual: x0→s1, y1→s2, base→s3, y0→s5.

So base (pri 714) got s3 while y0 (937) got s5. That's the only anomaly. Why?

Because find_free_reg has preferences: base is a pointer used in `&base[...]`; maybe it prefers s3? Or the register *class* for base differs (it's a pointer with GR_REGS).

Hmm, or `qty_phys_sugg`: base might have a copy preference.

Hmm, actually! The second GsSortLine call: `&base[(u16)D_800B9A02 * 20]` — base is used to compute the address. Both calls use it. Hmm.

Hmm, let me look at find_free_reg: it tries the "preferred" registers first (from qty_phys_sugg). If base has a suggestion for s3...

Hmm.

Alternatively, maybe the qty ORDER isn't by pri but by `qty_sugg_compare` (the first loop) — registers with suggestions get allocated first. Then the main loop by pri.

Ugh.

Let me take yet another step back. Given time (item 3 ~15 min in), let me consider: is this crackable within budget? The 120-permutation search hit 22. The remaining issue is a local-alloc ordering anomaly (base vs y0).

Hmm, wait. Let me reconsider: in my LEVER-FREE body, the pri values are: x1 1034 (live 29), x0 1034 (29), y0 967 (31), y1 967 (31), white 750 (40), base 714 (42).

But in the TARGET (pinned), x0's live is 12! Why? Because in the pinned body, x0's birth is later? In my lever-free body x0 live 29.

Hmm, the live lengths differ between the pinned and lever-free bodies for x0 (12 vs 29), y0 (32 vs 31), y1 (31 vs 31), base (42 vs 42).

x0 live 12 vs 29 — big difference! Why? In the lever-free body, x0 is assigned at `x0 = a0 - 3;` (5th statement) and used in `line.x0 = x0`. Its live should be short (~12). But the table says 29. Hmm, maybe I misidentified x0.

Let me re-derive: in my lever-free body, r74=s4 and r75=s0 are the live-29 pair. The assembly has x1=s4 and x0=s0. So x0=r75 (live 29) and x1=r74 (live 29).

Hmm, but x1 is born at `x1 = a0+3` (2nd) and used in `line.x1 = x1` — live should be ~25. And x0 born 5th, live ~12.

So why are both 29? Unless the "live" includes... hmm.

Wait, maybe r74/r75 aren't x0/x1. Let me check which pseudo is which by looking at the .lreg references. Ugh.

OK. I'm spending too long. Let me make a decision: this item is a hard local-alloc ordering puzzle. I've done 1 (baseline) + 120 (permutations) + 2 (nopin/nolau not done for item 3) = 121 tries. Plenty.

But wait — before walling, let me try one thing: the launder replacement. Maybe keeping a *real* 2nd set of x1 (like the store-before-copy trick) would restore the live-length difference. But we need it lever-free.

Actually — hmm, what if I make x1's assignment happen in two steps: `x1 = a0 + 3;` and later `line.x1 = x1;` — no.

Let me try the "statement order" search but INCLUDING an extra real statement that adds an insn in y0's live range without changing the code... impossible.

OK, let me also try: what if I permute AND vary the white assignment type/position? The search covered positions.

Let me look at the best 22 body's remaining diff to see if it's close.

Let me score perm (2,0,1,3,4) = y1, y0, x1, white, x0 and see the pairs.
