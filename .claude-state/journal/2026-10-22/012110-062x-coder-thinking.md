---
ts: 2026-10-22T07:21:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_VDLXcoDmHncDcGKrgv1M
---
Now I can read the launch order for the tree's case-0 block:

T-30: "451 (1) 266 (7f000001), now 266 451" → the boosted 266 (the ×127 product) wins → launched 266.
T-31: 264 (boosted) → launched 264
T-32: 261 (boosted) → launched 261
T-33: 259 (boosted) → launched 259 (the `li v0,160`)
T-34: 451 → launched 451 (the ori)
T-35: 450 → launched 450 (the lui)

So the launch order is: 266, 264, 261, 259, 451, 450 — i.e., the magic materialization (450, 451) was launched LAST.

And the chain (final order) = [450, 451, 259, 261, 264, 266] — the REVERSE of the launch order ✓✓. Confirmed: chain = reverse of launch order.

So: the magic's birth (450) was launched LAST → it's FIRST in the chain. Why launched last? Because it was the lowest priority (1) and the others were boosted (7f000001). The boosted ones (266, 264, 261, 259) launched first → they land LATER in the chain.

Wait, that's inverted from the intuition: the BOOSTED insns (266 etc.) launched first → they land at the END of the chain. And the unboosted 450/451 launched last → they land at the START of the chain.

Hmm! So the boost pushes an insn to the END of the chain (later in the final order).

Hmm, that seems backwards but let's accept it: the ready list picks the highest priority first; the chain is built in reverse.

Hmm, hold on. That's really weird for a scheduler: the insn with the highest priority should be scheduled FIRST (executed first). Unless the chain is built by prepending (gcc's sched1 emits the block in reverse and then reverses it).

Whatever. Empirically: chain position = reverse of launch order = the LOWEST priority insns land FIRST.

Hmm, wait, that can't be right either: in the tree's case-0 block, the chain starts with the magic materialization and the boosted ones are later in the chain. And the assembly shows the magic first ✓.

OK so now, in C2, why is the magic materialized later in the chain? Let me look at C2's trace for the same block.

If in C2 the magic's birth (451) was launched EARLY (i.e., it had a boost or won a tie), it lands later.

Let me look at C2's trace.
