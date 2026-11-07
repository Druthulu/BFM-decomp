---
ts: 2026-11-06T04:25:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_IuNiWGWHWwJYIFprsK1p
---
w6's p load is still at 4934, before the sll. So the do-while around the multiply did NOT create a barrier for sched1 (maybe because the do-while body executes once and jump.c removes the branch, leaving a NOTE that sched ignores?).

Hmm.

Let me reconsider. Perhaps the real issue is not the schedule but that the p reload's pseudo is born before the multiply in the RTL. Wait, in x1 the source has the p load AFTER the add. But the emitted order still has p before the sll. So sched1 moved it. 

Unless... the reload isn't from the C p assignment but from the *shared tail store* `((Unk*)p)->unk18 = v;` which uses p. The p assignment is at source after the add, but sched1 hoisted the load.

What if we make the p value *depend on the multiply result* through a real expression that the compiler can't fold? For example, the store value is v, and the store address is p. If we wrote `((Unk*)p)->unk18 = v;` where p is computed as `(Unk*)((s32)((Unk*)a0)->unk20 + (v - v))`... folds.

What about making the model load address depend on the multiply: `p = *(Unk**)((s32)a0 + 0x20 + (v & 0));` — folds to a0+0x20.

What about `p = *(Unk**)((s32)a0 + 0x20 + (v << 0 & 0));` no.

Any identity folds.

Hmm, what if the model pointer load is done through a *different* expression that cse can't fold but that produces the same address? E.g., `((s32*)((s32)a0 + 0x1C))[1]` — address a0+0x1C+4 = a0+0x20. cse folds PLUS constants. Same.

What if we use a variable offset that is provably 4? no.

OK, different tactic: maybe accept that the p reload hoist is a sched1 priority issue and try to influence priority by adding a *real* dependency to the multiply chain: make the multiply's input `*(s32*)(obj+0x1C)` also be used by the p address? no.

What if the p load's use is the store, and we make the store ALSO depend on the multiply's last result via the value — it already does (v). So the store depends on both p and v. The scheduler schedules p's load early to be ready. In target it didn't. 

Hmm, maybe the target's p load is NOT hoisted because in the target's RTL, the p load is in a *different basic block*. Look at the target: the `<0x11` arm falls through to the shared tail at 494c. The block boundary: the arm starts at 4924 (after the bnez delay slot at 4908). The shared tail 494c is reached by multiple jumps — it's a separate basic block! The `sh v0,24(v1)` at 494c is the target of jumps from other arms, so 494c is a branch target → a basic block boundary. The p load at 4944 is BEFORE 494c, so it's in the arm's block. Hmm.

But wait — the shared tail statement `((Unk*)p)->unk18 = v;` is at 494c, which is a different block (label). So the p LOAD could be in either block. In target, the p load (4944) is in the arm's block (before the label). In mine, also.

The scheduler in the target put the p load after the chain within the same block. In mine, before. Priority differences.

Let me look at sched1's priority more: it's the max over dependents of (priority + 1), and loads have latency 2 (SCHED_LOAD?). Let me read the rest of the priority function and how it's used (ready list ordering: `schedule_insn` picks the highest priority; ties by birth?).
