---
ts: 2026-11-07T00:29:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8VSfvT6VmuwD744xcPDb
---
This confirms: `(mem (symbol_ref))` varies → true? Let's see the rest: for a MEM whose address is a SYMBOL_REF, neither branch applies → returns 1 (varies)! Wait, then any store would invalidate it... but the invalidate_memory loop only removes p when `all || (nonscalar && in_struct) || cse_rtx_addr_varies_p(p->exp)`.

Hmm, if cse_rtx_addr_varies_p((mem (symbol_ref))) returns 1, then any store (nonscalar or not) would remove it. But my compile shows the load was NOT re-issued... Let me check the rest of the function to see what it returns for a symbol address.
