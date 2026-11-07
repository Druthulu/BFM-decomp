---
ts: 2026-11-06T21:04:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_sDGBUnlpVYZGivAT2zq4
---
Now I see:
- reg 95 = off (ashift of idx) — defined insn 54
- reg 79 = e (symbol_ref D_801E8F78) — defined insn 73, with REG_EQUIV
- reg 81 = lim (loaded via reg 95 + sym)

So off=reg95, e=reg79.

Interesting: e (reg 79) has REG_EQUIV (symbol_ref D_801E8F78). This REG_EQUIV means it can be rematerialized at each use! That's why reload/global-alloc can materialize it cheaply.

Let me find the register assignment: search for "reg 95" and "reg 79" after allocation. The .lreg dump shows hard regs? Actually -dl dumps after local-alloc, so pseudos should be renumbered. But here reg 95 and reg 79 remain — maybe local-alloc assigned them to hard regs but the dump still shows pseudo numbers? Hmm, in GCC the local-alloc pass output shows the regs with renumbering applied? Actually -dl = "dump after local-alloc" (lreg). The reg numbers shown are still pseudo but `reg_renumber` applied later? Let me check the .greg (global-alloc) dump or .sched.

Actually in the final asm, off is a0 and e is a1 in mine. The local-alloc assigned them. Let me look at .lreg more: local-alloc output usually shows the same pseudo numbers but the actual assignment is in the register allocation done in the same pass. Hmm.

The key: reg 79 (e) has REG_EQUIV. In global-alloc, a REG_EQUIV pseudo might be allocated differently. But these are block-local, so local-alloc.

Let me compute n_refs: reg 95 (off): def at 54, used at 70 (address) and used at the load in condition. reg 79 (e): def at 73, used in condition. Let me see the condition RTL (insns 85+).
