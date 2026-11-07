---
ts: 2026-11-06T04:03:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_VwjUWqlfMtWIrQxa2Oup
---
No notes. Let me think about the cse mechanism more concretely by reading cse_insn's handling of loads and dest records. Key question: what invalidates a load entry? A SET of the destination register (the load's value register) invalidates the entry. If we reassign the SAME C variable, the pseudo is re-set → invalidates. But in c4 the second load was still forwarded, meaning cse replaced the second load's MEM with the first's value before processing the dest invalidation? Actually if it forwarded, it replaced the MEM with (reg x), giving `x = x` (self set) which is deleted, leaving one load. That's what happened (58 ins). So the lookup happened before invalidation.

Hmm, cse_insn's `lookup` validation checks `reg_in_table[regno] == reg_tick[regno]` for registers in the expression being looked up (the MEM address). The VALUE register isn't part of the expression. So forwarding is valid.

To make cse NOT forward, the entry must be removed from the table. Removal happens on:
- a store that may alias (invalidate_memory)
- invalidate_for_call (call)
- a SET of a register that is the entry's "reg" (the value): when x is set by a non-equivalent expression, the entry for the load is invalidated? Let's see: when cse processes `(set (reg x) something_else)`, it calls `invalidate (x, ...)`? Let me look at the code path for recording a SET dest: in cse_insn, at the end, for each set it does:
```
      /* ... */
      if (sets[i].rtl != 0 && GET_CODE (sets[i].rtl) == SET)
        ...
      /* Record this expression's value in the table */
      ...
```
and there's `invalidate (x, ...)` for the destination? Let me read around line 6900-7100.
