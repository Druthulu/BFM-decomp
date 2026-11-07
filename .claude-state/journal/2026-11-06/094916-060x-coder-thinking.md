---
ts: 2026-11-06T16:49:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QGzGA6i1QFzhsJdOVRa4
---
`qty_n_refs[sqty] += reg_n_refs[sreg]` — the group's nrefs is the sum of the tied regs' refs. So:
- h group {76,81,82}: nrefs = 4 + 4 + 4 = 12. size 1. life = 39-30 = 9 (×2 = 18? qty_birth/death are in insn_number units ×2, so death-birth = 2*(39-30) = 18).
  pri = floor_log2(12)*12*1/18 = 3*12/18 = 2.
- t group {77,83}: nrefs = 4 + 4 = 8. life = 2*(39-25) = 28.
  pri = floor_log2(8)*8/28 = 3*8/28 = 0.857.

So h group > t group. To flip, I need t's group pri > h's.

Options:
- Increase t's group nrefs (tie more regs to it) or shorten its life.
- Decrease h's group nrefs (fewer tied regs) or lengthen its life.

Interesting: h's group has 3 tied regs (nrefs 12); t's has 2 (8). If I could make the t group have 3 tied regs... e.g., if t were used in a chain: `t = s0 << 1;` then `u = t + ...`? 

Wait, actually: in the target, the t group is {77, 83} = 2 regs, and the h group is {76,81,82} = 3 regs. The target still allocates t first. So the target's priorities must differ from mine... OR the target's allocation isn't by priority alone.

Hmm! Wait. Maybe in the target, the qty lives differ. Let me reconsider: the target's C might be different from ours in a way that changes the RTL.

Actually, maybe the target's h load is `(reg:HI 84)` style (u16) rather than a sign-extended SImode. Let me look at the target's instructions: `lh v1,112(s1)` — sign-extending load into v1. Then `sll v1,v1,0x4`. So h is SImode in a register (lh sign-extends). Same as ours.

Hmm, so why would the target allocate t first? Let me reconsider the priorities. Maybe the qty birth/death aren't what I think. qty_birth/death are in "insn_number" units where each insn increments by 1, but alloc_qty uses `birth = 2 * insn_number`? Let me look at reg_is_set.
