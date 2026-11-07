---
ts: 2026-11-06T21:04:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_gunYDKdssutwhvVwQuS4
---
The lreg dump shows the function after local-alloc maybe. "Register 72 used 2 times across 22 insns; crosses 1 call; GR_REGS or none." So pseudo 72 (ang) is assigned... need the allocation table. Let me use tools/alloc_table.py on the dump.

Actually alloc_table.py needs a specific format. Let me run it.

But wait: the important question is what happened to `a` (reg/v:SI 4). In the final asm, the andi writes $16 (s0) and there's no move. So pseudo 85 (the andi result) got $16, and pseudo 72 (ang) also $16 (coalesced), and the copy insn 42 was deleted.

Why did pseudo 85 get s0 instead of a0? And the `a` user-variable pseudo 4?

Let me look at the local-alloc dump's register allocation decisions. Search for "Register 4" and "Register 85".
