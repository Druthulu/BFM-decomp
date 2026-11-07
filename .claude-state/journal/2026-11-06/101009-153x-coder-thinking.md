---
ts: 2026-11-06T17:10:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xt2xcjG2QDboeLTzJQvF
---
The disposition list is sorted by pseudo number, not allocation order.

Let me directly compute the priorities from the lreg data. Actually, maybe the allocation order is: 87 (mask) allocated BEFORE 117 (constant) since 87 < 117 in the list and priorities... but 87 got t7 while 117 got t6. If 87 were allocated first, it would take the lowest free reg. At that moment, which regs are free? All the pointers 74-79 are in s-regs (6-11); 72/73 in a0/a1; etc. The mask is live over a huge range, so it conflicts with everything live; the free regs at its birth might be {t6, t7, ...} and it took t7 — meaning t6 was NOT free at the mask's birth.

Who holds t6 at the mask's birth? Possibly a pseudo that is live then and was allocated t6: e.g., 117 (constant, live 5..76) — if 117 was allocated BEFORE 87, it took t6, and 87 then took t7.

So the allocation order had 117 before 87. That means pri(117) > pri(87). Let me recompute with the actual birth/death from the lreg dump for 117 and 87.

Let me find their qty_birth/death in the lreg dump: the "used N times across M insns" line gives the span. 117: "used 10 times across 12 insns; dies in 5 places" — wait, that was the lreg line for 117? Let me re-read the lreg list: 

"Register 117 used 10 times across 12 insns; dies in 5 places; GR_REGS or none."

Hmm, 10 times, not 2! So pseudo 117 is NOT the constant? But the flow dump showed insn 168 `(set (reg:SI 117) (const_int -520093554))` — a 2-ref use. The lreg line says 10 uses across 12 insns.

Ah — the lreg is AFTER local-alloc, which may have merged/renumbered. Actually the pseudo numbers in the lreg dump are the original ones. Hmm, but 117 with 10 refs across 12 insns doesn't match.

Hold on, the flow dump numbers may differ from the lreg dump because local-alloc merged some pseudos into quantities (reg_qty). The "Register 117" line in lreg might be a *qty* containing several pseudos.

This is getting deep. Let me take the empirical route: try C variants that might swap the constants/mask.

Ideas:
1. Reorder the source so the mask is defined earlier (before the packets). Then the mask's live range is longer (worse priority) but its birth earlier.
2. Move the mask definition to just before the last block (it already is).
3. Increase the mask's refs: e.g., use m24 in the 6 `unk0` expressions AND the 6 `*ot` expressions — it already is (12 uses).
4. Split the mask into two variables (m24a for the first 6, m24b for the last 6)? That would create 2 pseudos with 6 refs each; each might take a different reg. Hmm.
5. Make the 0xE1 constants not use a register: e.g., write `*q2 = 0xE100008E;` — already.
6. Change the order of the six packet stores so a different constant is hoisted.
7. Use the mask inline (`& 0xFFFFFF`) instead of m24: cse would create the constant pseudo at its first use; maybe its priority changes.

Let me try these variants and score:
a1: inline the mask (remove m24, use 0xFFFFFF in all 12 places).
a2: m24 declared/assigned at the top (before the packets).
a3: m24 assigned right after pbase.
a4: split into two masks (first 6 uses m24, last 6 m24b).
a5: mask as `~0xFF000000u`.
a6: mask as `0xFFFFFFu`.

Also try moving the `m24 = 0xFFFFFF;` line after `obase = ...` (currently after ot).

Let me generate and score.
