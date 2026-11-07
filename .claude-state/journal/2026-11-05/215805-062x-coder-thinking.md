---
ts: 2026-11-06T04:58:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_SilJ2Gsv81zDwdDnctgk
---
flow_analysis with `final` flag deletes dead stores. The flow pass after cse2 (final=1?) deletes dead stores. So a dead store inserted to defeat cse1/cse2 might be removed by flow_analysis after cse2 — but cse2 already ran and would have seen it. 

Wait, but the forwarding happened in cse1 (need to confirm). If it happened in cse1, a dead store inserted anywhere before the load would block cse1's forwarding, and then flow (after cse2) could delete the dead store, leaving the target code. But careful: if cse2 runs after and the dead store is still there (flow hasn't run yet), cse2 sees it too. Flow deletes dead stores in the final flow pass after cse2 → good.

But a dead store must not be deleted by cse's delete_dead_from_cse or combine. Hmm, combine runs after flow, so if flow deletes it, fine.

So the plan: insert a dead store that cse's note_mem_written treats as invalidating all scalar memory, and which flow later removes as a dead store. What dead store? A store to a local variable (stack slot) is scalar and fixed; that wouldn't invalidate the global scalar D_80127524. We need a store whose address is "varying" in cse's sense (cse_rtx_addr_varies_p) and not a PLUS-with-non-QImode. For example, a store through a pointer variable whose value is unknown: `*q = 0;` where q is a pointer whose value cse can't determine. But a dead store to *q where q points to unknown memory isn't provably dead to flow (it might be a live global). flow deletes dead stores only for stack slots? `insn_dead_p` checks if the store is to a dead stack slot (reg + const offset) or a dead register. A store to an arbitrary pointer can't be deleted.

Alternatively, a store to a *local* variable via a varying address that flow can prove dead? E.g., `s32 arr[2]; arr[i] = 0;` where i is a variable? cse sees a varying address (PLUS with reg) and mode SI → PLUS && mode != QI → does NOT set all=1 (it's "array element", nonscalar). That invalidates only nonscalar entries, not our scalar. Not enough.

We need all=1: varying address that is NOT a PLUS, or QImode with PLUS. A QImode store through a varying address (PLUS) sets all=1 (because mode == QImode fails the exemption). So: a *char* store through a variable address! E.g., `*(char *)q = 0;` where q is a pointer with a varying address. That would invalidate all scalar memory in cse. And if it's a store to a dead local array via a char pointer with a variable address, flow might delete it.

Concretely, add a dead store: `u8 tmp[4]; u8 *t = tmp; t[k] = 0;`? Address is tmp (a stack slot) + k → PLUS with reg, QImode → all=1. flow's insn_dead_p for a QImode store to a stack slot with a varying address: it checks if the destination is a stack slot that's dead — with a variable address it probably can't prove it. Hmm.

What about a direct QImode store to a *known dead local*: `u8 t; t = 0;` — address is a fixed stack slot (not varying), so cse treats it as fixed; does it invalidate the global scalar? A store to a fixed stack slot invalidates only that slot (and scalar entries at the same address). Not our global.

We need cse to invalidate the D_80127524 entry. cse invalidates memory entries by address: entries whose address matches or may alias. For a *scalar* entry (symbol D_80127524), a store through a varying address that isn't known to be disjoint invalidates it if writes.all=1.

So a QImode store through a varying address does it. Then flow must delete the store. flow's dead store deletion: `insn_dead_p(PATTERN(insn), old, 0)` — let me read insn_dead_p to see when a store is dead.
