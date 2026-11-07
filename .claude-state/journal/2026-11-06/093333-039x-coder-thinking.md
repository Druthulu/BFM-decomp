---
ts: 2026-11-06T16:33:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mS8CAQSKJCFFliE3fYmb
---
The lreg dump shows the RTL after local-alloc. Register 72 = self (10 uses). Let's see the insns to see which regs: register 74 in 4? Hmm "Register 74 in 4" means reg 74 got hard reg 4 (a0). Reg 75 in 2 (v0), 78 in 2 (v0), 79 in 3 (v1), 81 in 3 (v1), 82 in 3 (v1), 83 in 2 (v0).

Block 1 = then block, block 2 = else block. Register 73 live at block 2 start is a pointer (self, 5 uses? no, 72 is self with 10 uses across 13 insns).

Let's print the whole function RTL.
