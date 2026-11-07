---
ts: 2026-11-06T21:06:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Lp7wjtt63rsY0VG2zUIv
---
qty_birth/qty_death are insn indices, not live length. Priority = floor_log2(n_refs)*n_refs*size / (death - birth).

For off: birth=54, death=81 → 27. n_refs=3 → floor_log2(3)=1 → 1*3*4/27*10000 = 4444.
For e: birth=73, death=81 → 8. n_refs=2 → floor_log2(2)=1 → 1*2*4/8*10000 = 10000.

So e higher → allocated first → a0. But mine gives off a0. Contradiction remains.

Unless qty_birth/qty_death are not the insn numbers but something else, or off's birth is later. Let me check how qty_birth is set. It's from the first and last insn in the block where the qty is live, using `regno` order... Let me look at qty_birth/qty_death assignment.

Actually maybe e (reg 79) has REG_EQUIV and local-alloc treats it differently — REG_EQUIV pseudos might be considered for elimination/rematerialization and their qty not allocated normally.

Wait — maybe the real allocation happens in global-alloc, not local-alloc! These pseudos are in a single basic block, so they'd be local. But reg 79 has REG_EQUIV; global-alloc might handle it.

Hmm. Let me look at the .greg dump (global-alloc) to see the assigned hard regs. -dg = "dump after global-alloc" (greg). Let me grep the function region for the sll/plus.

Actually the .greg dump shows RTL with hard regs? Let me check lines around the ashift in greg.
