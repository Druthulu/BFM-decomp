---
ts: 2026-10-17T11:40:47.724Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7979eba5885c3edf
model: claude-opus-5-5[1m]
effort: medium
turnId: 921e828f-1fac-424f-94a0-d040638a6158
---
I only did 4 tries against the "stop after 15 consecutive no-gain attempts" rule, so I should keep going rather than stop early. Let me dig into why CSE folds things on MIPS gcc 2.7.2 — specifically what happens when a pseudo register is assigned a SYMBOL_REF and then used inside a memory reference with an offset.

Looking at `find_best_addr` in cse.c: it skips addresses that are already simple registers (unless frame pointer, etc.), but for non-register addresses it tries folding the address and compares ADDRESS_COST and rtx_cost between the original and folded forms, replacing the address if the folded version is cheaper or equally-costed but structurally better. So whether the compiler picks the folded `(const (plus sym -52))` form comes down to how MIPS's `mips_address_cost` scores CONST/SYMBOL_REF addresses, particularly around the small-data (-G0) threshold.
