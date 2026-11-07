---
ts: 2026-11-06T18:34:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hTT5xq3rYMJq5HHlgx3Q
---
All score 4 (order). w3/w4/w5/w6 same as w1 presumably (a1 late).

Let me check what w3 does: it moved a2/a3 before the v0 chain; score 4 — maybe the same a1 residual, or a different order issue. Let me see the diff for w3.

Actually, let me think about the real mechanism more: the target's a1 materialization is early because of the asm. With real C, we need another way to make the a1 symbol_ref insn scheduled early.

What if we make the a1 value *not* foldable into the call arg by giving it a second real use, and the second use is scheduled early — e.g., use a1 in the first store? no.

Hmm, what about making a1's value used as the *condition* of the call? no.

Alternatively: make the call's a1 arg not a direct copy: e.g., pass `a1` where a1 was assigned from another variable `t`:
```
s32 t;
t = (s32)&D_801A15AC;
a1 = t;
...
func_8012D5E4(a0, a1, a2, a3)
```
Combine would propagate t → a1 → call arg. But maybe not all: combine's `try_combine` folds one level. cse would propagate t's value into a1 (copy) and into the call arg. So same.

What if a1 is used in a *comparison* before the call that combine folds? e.g., `if (a1 != 0) { ... }` — adds a branch.

What about the "pointer reuse" idea: use a1 as the base of the unk58 store? No.

Hmm, let me look at the sched trace for the ORIG (with keepalive) to see exactly what the asm did to the schedule. If the asm forced 55 early, the real-C equivalent would need a similar barrier. A *store* is a barrier for memory ops but not for a constant load.

What about a *call*? The keepalive asm was between the a1 assignment and the v0 chain. A real call there? No.

Wait — maybe a different trick: make the a1 materialization a *dependency of the call-arg copy* that sched1 must schedule early because the call arg insn 94 has a dependency on an early insn. Hmm, 94 IS the materialization.

What if we split the a1 value: `a1 = (s32)&D_801A15AC;` and then use a1 in a context that forces the insn early: the ready-list order. Since all priorities are 1, sched1 picks... the "potential hazard" and the list order. The list order is the order insns become ready. Insn 94 (the call arg) becomes ready when its deps are satisfied: it depends on nothing (symbol_ref), so it's ready at the start. Hmm, but sched1's `ready` list insertion: insns are added in a specific order (reverse RTL order?). The RTL order: 94 is late in the block, so it may be added to the ready list late (the scheduler scans backward from the block end, adding insns as their successors are scheduled?).

sched1 schedules backward: it starts from the block's last insn and works backward, building the ready list. So insns later in the RTL become ready earlier in the process. The final schedule is built in reverse. The trace shows T-1 = last scheduled.

Hmm, the exact tie-breaking is hard to control from C.

BUT: the target's schedule has 94 early. With the asm, the RTL had an extra insn (the asm) whose position forced things.

Let me look at the orig's sched trace to understand. Let me dump orig.c.

Actually, maybe simpler: let me test whether a *second use* of a1 that is later (e.g., after the call, dead?) keeps combine from folding and forces the early placement. A use after the call would be dead code (removed).

Hmm, what about using a1 in the call TWICE? `func_8012D5E4(a0, a1, a2, a3)` — no.

What about `func_8012D5E4(a0, a1, a2, a1)`? changes the call args.

OK, let me look at the orig dump to see the target's schedule mechanism.
