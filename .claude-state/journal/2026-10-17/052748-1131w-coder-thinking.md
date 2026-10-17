---
ts: 2026-10-17T11:27:48.680Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7979eba5885c3edf
model: claude-opus-5-5[1m]
effort: medium
turnId: 921e828f-1fac-424f-94a0-d040638a6158
---
I'm still hunting for a non-dead-branch route, checking if the unread arithmetic has a consumer removed later in the flow—maybe through a narrowed byte write or a min-based computation feeding into `su`.

Testing various flag-derived comparisons like `tp == 3` or `shift < 0` for provable falseness, but none seem clean enough to be "natural" original code; they all look like compiler-provable dead branches rather than genuine logic. Since unread arithmetic inherently suggests this pattern (or inline asm), I suspect the original code had some flip/flag test the compiler could prove always false, though I can't pin down a convincingly natural example within my budget.

I'm wrapping up this exemplar with the dead-branch lever as the best match, having spent roughly ten minutes on it. Before moving on, I want to try one more legitimate angle: a value consumed only by a comparison that combine folds purely due to the comparison's internal structure, rather than an obviously dead flag check.
