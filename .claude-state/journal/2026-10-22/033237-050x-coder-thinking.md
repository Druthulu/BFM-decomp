---
ts: 2026-10-22T09:32:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_ah9Y817mSCWRuok873b1
---
simplify_binary_operation is in cse.c. But cse runs after combine. The swap appeared in the .combine dump, so it's in combine.c.

Let me search combine.c for where a PLUS gets its operands reordered — maybe in the code handling "GET_CODE (x) == MEM" addresses: `plus_constant`?

Let me grep combine.c for "plus_constant" and check fold-const.c's plus_constant for a swap.

Actually — hold on! Maybe the swap is done by the *front end* (c-type.c) or expand: maybe the tree at .rtl was (plus (symbol) (reg 118)) and combine's `simplify_rtx` case MEM → `make_compound_operation (XEXP (x, 0), MEM)` → the ASHIFT case: "Convert shifts by constants into multiplications if inside an address"! So in an address, (ashift x 3) becomes (mult x 8) — and then the address becomes (plus (symbol) (mult x 8))...

But we saw in the combine dump the tree as (plus (reg 118) (symbol_ref)) where 118 is a REG (the shift result), not (mult). Hmm.

OK, let me take yet another approach: rather than reverse-engineering combine, let me use gcc's own source to find the rule by grepping for code that reorders PLUS operands with SYMBOL_REF. Search combine.c for "XEXP (x, 0)) == SYMBOL_REF" or similar.

Let me grep for "SYMBOL_REF" case at 10264 (that's in some switch). Let me look at that context.
