---
ts: 2026-11-06T04:48:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QBhhhqDkH71EvJdzga8X
---
Same residual as b1. Both: ori delayed to pos 5, and a3 setup late at 15 instead of 6.

Interesting: target has a3 (p=&D_800C7C60) setup at insn 6-7, i.e., very early (right after lh currentLocationId). Mine has it at 15-16 (after the two indexed loads). Why? In target, `p = &D_800C7C60` is a global-alloc/local-alloc choice; sched1 placement. 

Wait: maybe the difference is which pseudo gets v1/a0 etc. Let me reconsider. In b1/b10, mask in v1, idx in v0. In target mask in v1, idx v0. Good. a3 = p. In target a3 setup early. In mine late.

In a1 (no do-while), a3 setup was early (150). So do-while moved it late. Hmm. So maybe the do-while isn't the right approach; instead we need to only stop the D_800A2E20 hoist. In a1, what's wrong is: D_800A2E20 address in v1 and mask in a0; store to D_800C7C64 early at 0x160.

Target: mask in v1, D_800A2E20 address in v0 late at 174, store at 180.

So in a1, register assignment differs: a0=mask, v1=D_800A2E20 addr. In target, v1=mask, v0=D_800A2E20 addr (after currentLocationId's v0 dies).

The do-while fixed the register assignment (mask v1) and D_800A2E20 late, but moved a3 late.

Maybe try: do-while around only D_800C7C64 store, but move `s32 *p = &D_800C7C60;` declaration/assignment to just before the store, or after the do-while? p is used in *p = val after. Currently p is initialized in the declaration list before the barrier. If we initialize p later, after the loads: e.g., remove `= &D_800C7C60` from decl and add `p = &D_800C7C60;` just before `*p = val;`. Then a3 setup would be later, not earlier. Target has it early though.

Hmm target: a3 setup at 6-7 (early), and *p = val store at 18c in the delay slot. So the address is computed early and the store late.

In mine b10: a3 setup late (15-16) and store at... let me see full b10 asm. Let me dump.
