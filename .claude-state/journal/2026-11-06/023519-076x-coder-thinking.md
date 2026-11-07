---
ts: 2026-11-06T09:35:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4HRBm8gRPzbgXuP36dSA
---
Same diff — so the compiler reordered the source back (sched1 put the store after the copy anyway).

Let me examine the .lreg dump. Find the store insn in lreg for both and see the regs. Let me grep for "392" (0x188) in the lreg dumps near the function.

Actually the .lreg dump prints hard regs? The .lreg dump is after local-alloc; insns show pseudo numbers with hard regs in the "reg" annotations? Let me look at a window.

Let me find the function in o.i.lreg and look at the block with the store.
