---
ts: 2026-11-06T21:47:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_DAvXULeZSjY9jpIhsIn3
---
So combine_regs is called with may_save_copy = 1 only for true moves. For an ashift, may_save_copy=0, but combine_regs can still set *normal* suggestions (qty_phys_sugg) when the input dies. Let's look at combine_regs to see: it sets `qty_phys_sugg[reg]` maybe. Actually qty_phys_sugg = "all possible hard registers" for the qty; qty_phys_copy_sugg = tied by a simple copy.

For the ashift r84 = r181<<2, r181 dies. combine_regs(r1=r181, r0=r84, may_save_copy=0,...) → it may record that r84 can be in r181's reg? Let's read combine_regs.

Actually, the key phase: qty_sugg_compare sorts qtys with suggestions. If r84 has a "normal" suggestion (qty_phys_sugg) to r181's eventual reg, that's circular.

Let me read combine_regs around where it sets qty_phys_sugg.
