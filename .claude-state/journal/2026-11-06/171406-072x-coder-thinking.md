---
ts: 2026-11-07T00:14:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_lv4rjlZsqXeYCD6ALagL
---
The .lreg dump DOES have the final register assignments:
- r72 → 16 (s0)
- r73 → 17 (s1)
- r74 → 20 (s4)
- r75 → 16 (s0)
- r76 → 19 (s3)
- r77 → 18 (s2)
- r78 → 21 (s5)
- r79 → 17 (s1)

Hmm, r72→s0 and r75→s0 — they don't conflict (different live ranges, both in block 0, reused). Same for r73/r79 → s1.

So: r74=s4, r75=s0, r76=s3, r77=s2, r78=s5, r79=s1.

And from the assembly mapping: x1=r74 (s4), x0=r75 (s0), y0=r78 (s5), y1=r79 (s1), white=r77 (s2), base=r76 (s3).

Hmm wait, that contradicts what I said. Let me redo: mine's assembly has x0=s0, y1=s1, white=s2, base=s3, x1=s4, y0=s5. So x0=r75 (s0), y1=r79 (s1), white=r77 (s2), base=r76 (s3), x1=r74 (s4), y0=r78 (s5). Yes.

Now, the allocation order: r75 (s0), r79 (s1), r77 (s2), r76 (s3), r74 (s4), r78 (s5).

By pri: r74=1034, r75=1034, r78=967, r79=967, r77=750, r76=714.

Hmm, the order r75, r79, r77, r76, r74, r78 doesn't match pri order at all.

Unless find_free_reg's *preferences* reorder. local-alloc assigns each qty a register, trying "preferred" regs first. A qty's preference comes from copies (`x = y` suggests the same reg) and from `qty_phys_sugg`.

Hmm, in this function, the copies are `x0 = a0 - 3` etc. (adds, not copies). But there are `move s1,a0` in the target — the compiler chose to copy a0.

Hmm, wait. Actually, the *allocno order* in local-alloc is by qty_compare, but the tie-break is qty number (birth). The pri values: r74 1034 (live 29), r75 1034 (live 29) — tie. r78 967 (live 31), r79 967 (live 31) — tie.

If the allocation order were r74, r75, r78, r79, r77, r76 → regs s0,s1,s2,s3,s4,s5 (assuming first-fit with no prefs) → x1=s0, x0=s1, y0=s2, y1=s3, white=s4, base=s5.

Target: x1=s0, x0=s1, y1=s2, base=s3, white=s4, y0=s5.

Hmm! Target has x1=s0, x0=s1 (matches the pri order), but then y1=s2, base=s3, white=s4, y0=s5 instead of y0=s2, y1=s3, white=s4, base=s5.

So the target's order is x1, x0, y1, base, white, y0.
The pri-based order is x1, x0, y0, y1, white, base.

Differences: y1 before y0; base before white.

base has live 42 (pri 714, lowest) but target allocates it 4th. y0 has live 31 (pri 967) but target allocates it last.

Hmm, so in the target, base's priority must be higher and y0's lower. That depends on the *live lengths in the target's RTL*. Since the target was compiled from the same C (minus levers), the live lengths should be the same... unless the lever removal changes them!

Wait — the pin on x1 (`register s16 x1 __asm__("$16")`) and the launder affect the RTL. With the pins, the live lengths are computed differently? No, the pins don't change refs/live.

Hmm, but the launder `__asm__("" : "=r"(x1) : "0"(x1))` creates an extra set of x1 and an extra insn. That changes x1's live length and refs! In the lever-free body, x1's live is 29. With the launder, x1 has an extra reference (the asm) and the asm is an insn.

But x1 is pinned in the target, so its allocno doesn't exist.

Hmm, the launder removal changes x1's RTL. But x1 in the target is a hard reg, so its allocation doesn't matter.

OK so the question remains: how do I get the target's order x1, x0, y1, base, white, y0?

In the target (pinned), x1=s0 (pin), x0=s1 (r?), white=s4 (pin $20), base=s3.

Hmm wait — white is pinned to $20=s4 in the target. So white's natural allocation doesn't matter. And x1 pinned s0. So the target's *natural* allocation order only matters for x0, y0, y1, base: they got s1, s5, s2, s3.

So in the target: x0=s1, y0=s5, y1=s2, base=s3.
The available regs after the pins (s0 for x1, s4 for white): s1,s2,s3,s5 (s6,s7 maybe).

Natural order for x0, y0, y1, base: x0→s1, y1→s2, base→s3, y0→s5.

Their priorities (in the pinned body's RTL — same as lever-free except x1's launder): x0 1034, y0 967, y1 967, base 714.

Order by pri: x0, y0/y1 (tie), base. First-fit to s1,s2,s3,s5 → x0=s1, y0=s2, y1=s3, base=s5. But target has y1=s2, base=s3, y0=s5.

Hmm, so again y0 is allocated last in the target despite pri 967.

So the tie between y0 and y1: y0 born before y1 (qty lower) → y0 should allocate first. But target allocates y1 first.

Unless y0's live is longer in the target's RTL, lowering its pri below y1's. In the lever-free body both are 31.

Hmm, wait: y0 is used at `line.y0 = y0` and y1 at `line.y1 = y1`. Also y0/y1 are used in the second GsSortLine block. Hmm.

Actually hold on — maybe the difference is the *death* of y0 vs y1. y0 = a1-3, y1 = a1+3. Both used in the struct stores.

Hmm, the live lengths are 31 and 31 in mine.

In the target (pinned), the launder on x1 adds an insn, shifting things but not y0/y1's live.

Hmm. Let me check the pinned body's lreg table for comparison. Let me dump orig.c and look.

That will tell me the target's natural priorities for x0, y0, y1, base.

Let me do it.
