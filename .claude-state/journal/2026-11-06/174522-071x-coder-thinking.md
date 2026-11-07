---
ts: 2026-11-07T00:45:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_UptF10xS5vYH63ZKSvtg
---
Excellent! w16 (do-while(0) around the three stores) FIXES THE ORDER: mine[32:34] = lui v1; lw v1 (the val load is now at position 32, same as the target). 

Remaining differences:
1. Register: mine val→v1, target val→v0 (and the const 1: mine v0, target v1). "register pairs: v1->v0 x1".
2. `li v0,1` placement: mine has it at 41 (after the stores?), target at 34 (right after the load). And the addiu placement differs: mine has addiu at 42 (before the sw v0) vs target at 45 (after sw v1).

Let me see the full mine listing for w16 to understand. Actually the diff hunks:
- mine[32:34] lui v1; lw v1 vs target[32:35] lui v0; lw v0; li v1,1 — so mine's `li v0,1` is NOT at 34.
- mine[41:43] li v0,1; addiu v1,v1,1 vs target[42:42] nothing.
- mine[44:45] sw v0,0(at) vs target[43:45] sw v1,0(at); addiu v0,v0,1
- mine[46:47] sw v1,0(at) vs target[46:47] sw v0,0(at)

So mine: ... li v0,1; addiu v1,v1,1; ...; sw v0,0(at) [D_801B7988=1]; sw v1,0(at) [D_801B7A84].
Target: li v1,1; ...; sw v1,0(at) [D_801B7988]; addiu v0,v0,1; sw v0,0(at) [D_801B7A84].

So two issues: the register assignment (val v1 vs v0) and the addiu's position (mine before the sw of D_801B7988, target after).

The addiu position: mine has addiu at 42 right after li, i.e., before the D_801B7988 store. Target has the addiu after that store. Both are in the same block? Hmm.

The register swap and the addiu placement are related: with val in v0 and the const in v1, the addiu (v0+1) must come after... hmm.

Let me think about what controls the register choice here: local-alloc's qty priority. val (reg 76) and the const-1 pseudo (reg 78). Both are local to the block.

local-alloc assigns registers in order of qty priority: `qty_compare_1` sorts by `qty_n_refs[q] / qty_size[q]`? Let me read local-alloc.c qty_compare_1.

Actually, maybe I can influence it by *declaration order* of the locals or by using a different temp for the constant. The constant 1's pseudo comes from `D_801B7988 = 1;` — the immediate is loaded into a register (li v0/v1) because the store needs a register operand? On MIPS, `sw reg,0(at)` — the store needs the value in a register (no immediate store form? Actually MIPS has no `sw imm` instruction, so yes, a register).

So the constant 1 gets a pseudo (reg 78).

In the target, val→v0 and const→v1. In mine (w16), val→v1 and const→v0.

local-alloc gives the *first* available hard reg to the highest-priority qty. v0 is "preferred" for... The order is by qty_compare: n_refs / (death - birth)?

val: reg 76, refs: 1 def + 1 use = 2 refs? The dump said "insn[53]: priority 1, ref_count 2" — that's the scheduler's ref_count, not local-alloc's.

Let me look at local-alloc's qty_compare_1.
