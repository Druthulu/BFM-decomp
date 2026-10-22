---
ts: 2026-10-21T23:52:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_OZDfRVLiJ2x3sCgRi8ZB
---
canon_reg just maps a pseudo to its quantity's first reg. Not the forwarding I was thinking of.

The forwarding of a copy is in `cse.c`'s `record_cse` / `cse_basic_block` — the "cse_class" mechanism: `cse->equivs` and the `cse_class` table. The relevant: cse's `record_cse` handles a SET of a pseudo to a value: it records the equivalence so later uses of the pseudo get the value. That's the "forward scan".

Let me look at how cse decides to forward a use: in `cse_basic_block`, for each insn, it calls `cse_record` / `record_cse` on the SET_SRC. And for a USE, `cse.c`'s `record_cse` is called with the use's rtx; if the rtx is a REG that has a recorded equivalence (in `cse->equivs`), it's replaced by the value.

The blocker for forwarding: `cse->equivs` records the equivalence only if the pseudo's "reg_equiv" is valid.

Let me look at cse.c's `record_cse` REG case and `update_stmt`/`invalidate`.

Let me grep for "invalidate" in cse.c and read it.
