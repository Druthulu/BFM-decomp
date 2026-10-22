---
ts: 2026-10-22T09:31:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_AdHhJlcONtqj4aKDqAOi
---
This is `simplify_rtx`. Let me find the PLUS case in simplify_rtx and look for the code that handles a SYMBOL_REF + MULT.

Search for "case PLUS:" within simplify_rtx and look for "make_compound_operation" / "plus_constant".

Actually! Line 3189's comment: "Ensure that our address has any ASHIFTs converted to MULT in case address-recognizing predicates are called later." — `make_compound_operation (XEXP (x, 0), MEM)`. Hmm.

Let me find in combine.c where a PLUS with SYMBOL_REF gets reordered. Search for "make_compound_operation" definition — that's in expr.c probably. Let me look at it: it handles the "plus (reg) (mult x c)" → compound operation for addresses.

Actually, the key function might be `simplify_binary_operation` in combine.c. Let me look at the PLUS handling in `simplify_binary_operation`, particularly the code that swaps operands when one is a constant.

Let me grep for "plus_constant" and "make_compound_operation" in expr.c (fold-const.c?).
