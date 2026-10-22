---
ts: 2026-10-21T23:52:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_Fdhg2BwQmgcL9PjWN8ci
---
The gcc source is available. Let me look at local-alloc.c for the copy coalescing / "reg_equiv" handling. The key question: what prevents a copy `p = pb` from being coalesced.

In gcc 2.7.2's local-alloc.c, `coalesce_cost` and the "global-alloc" `set_preference`. But more relevant: in local-alloc, the copy elimination happens because `p`'s reg_equiv is set to the source's value.

Let me grep for "reg_equiv" in local-alloc.c and for the copy handling in cse.c (canon_reg).

Actually, the important one: in cse.c, `canon_reg` (or `get_cse_reg`) forwards the value. The blocker for forwarding: `REGNO_SET_P` / multiple sets.

Let me grep cse.c for "canon_reg" and the condition where it refuses.

Let me be surgical: grep -n "canon_reg" cse.c and look at the function.
