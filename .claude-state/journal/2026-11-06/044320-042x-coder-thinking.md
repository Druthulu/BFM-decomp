---
ts: 2026-11-06T11:43:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_skBUgiNZnvxgrpjTF2Uq
---
`cse_rtx_addr_varies_p` returns 0 (doesn't vary) if the address's base reg has a known constant qty. `p` = (s32)a0; a0 is a function parameter — not a constant. So it varies.

BUT: `iVar5` is loaded from p+0x20 — unknown. The store `*(u16*)(iVar5+0x12)` varies.

Hmm. What about the stack pointer? A store to a stack slot: base is the frame pointer (a hard reg with a known constant? In gcc 2.7.2 with a frame pointer, the address is `(plus (reg fp) (const))`. Is fp's qty a known constant? No. Hmm, but at cse time, the stack slots are virtual registers (pseudos) with addresses `(plus (reg pseudo_sp) (const))`? Actually in gcc 2.7.2 at cse1 time, stack slots are pseudos, and their addresses are `(mem (reg pseudo))`? No — the address of a local variable is `(plus (reg virtual_stack_vars_rtx) (const_int))`, and virtual_stack_vars_rtx is a pseudo with a known constant equivalence? Possibly not.

Anyway, empirical: the `sh v1,16(sp)` survived and only invalidated... well, did we get 2 loads? 72 ins with 1 extra store means 71 code insns + 1 store = still 1 load? Let me check: if we had 2 loads, we'd have 71+1 = 72. Actually the target is 71 with 2 loads. Mine 72 with the store. So mine might have 2 loads and the store! Let me check the disassembly.

Let me look at more of the diff — the load region.
