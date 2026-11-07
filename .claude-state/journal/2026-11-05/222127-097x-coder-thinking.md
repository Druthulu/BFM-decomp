---
ts: 2026-11-06T05:21:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_uyzGpclgv6G21Hjfbno2
---
flow.c's `insn_dead_p` deletes dead stores. Let me look at `insn_dead_p` — it handles stores to dead stack slots.

Line 1002: "A SET that makes space on the stack cannot be dead." Let me read insn_dead_p around line 950-1050.

The key: does flow delete a store to a stack slot that is overwritten later? `insn_dead_p` uses the liveness of the *address* — a store is dead if the destination register (the address) is dead and the memory isn't needed. For a stack slot accessed via sp+24, the address register (sp) is always live, so the store is not dead in flow.

Hmm, so the deletion is in cse. Let me look for where cse deletes a store whose value is overwritten. In cse.c, `cse_insn` maintains a table of available expressions; a store to memory invalidates the equivalences. Dead store elimination: cse.c has the `n_sets == 1` path where a store is deleted if `dest` is a MEM and the previous store to it is dead... 

Let me grep cse.c for "MEM" and "dead".
