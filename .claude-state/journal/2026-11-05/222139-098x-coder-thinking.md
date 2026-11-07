---
ts: 2026-11-06T05:21:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_a1A809PzDFw9mgGn2T4h
---
This deletes only register-set dead insns, not memory stores. So the memory-store deletion must be elsewhere: probably in `cse_insn`'s "invalidate" logic or in `flow.c`'s `insn_dead_p` where a store to memory is dead if... Let me look at flow.c:947-1010.

Actually, in flow.c's `insn_dead_p`, for a SET to a MEM: "A store into memory is dead if the memory is not needed and the address is dead". For stack slots, the address (sp) is live, so not dead.

Hmm, but the stores ARE removed somewhere. Let me find out empirically: compare the RTL dumps. Let me extract the `sh` store insns from the .flow and .cse dumps.

The dump format: `(insn NNN ... (set (mem:HI (plus (reg 29) (const_int 24))) ...))`. Let me grep for `mem:HI (plus (reg:SI 29)` or similar. Let me look at one instance in the flow dump.
