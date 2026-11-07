---
ts: 2026-11-06T05:00:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tN0HdtNluZmuIi5ou2rp
---
No luck. The forwarding persists.

Let me think about cse's `do_not_record`: if the stored value's source expression contains a MEM, cse won't record the store→value? Let's check: in cse_insn, when computing the src hash, `do_not_record` is set if the expression contains a volatile MEM (line 1942) or... let me read hash(): `case MEM: if (MEM_VOLATILE_P) do_not_record=1; else if (CONSTANT_P) ...`. Let me read lines 1935-1975.
