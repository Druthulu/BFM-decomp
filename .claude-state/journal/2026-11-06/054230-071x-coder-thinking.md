---
ts: 2026-11-06T12:42:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_h9d1kwiucC1IVn52Y6ZU
---
Still a0->v0. So ret is still in a0 (the do-while around ret didn't change the sched order enough).

Let me now test the WAR-dependency theory directly: what if `ret` is assigned a value that depends on the call result in a way that's free? For instance:

```
s32 r = call(...);
unkD8 = r;
ret = 7;
```
No.

Hmm, let me check: is the conflict maybe from the *other* arms where ret is live across v0/v1 uses that are NOT about this ordering? Let me test a targeted experiment: take c2 and change ONE arm's order to see if the conflict list changes... too slow.

Better: let me look at the greg dump's conflict for 73 and figure out WHICH insns cause it. There's a `-dG`? Hmm. The `lreg` dump prints live ranges per block: "Register 73 used 9 times across 22 insns". 

Alternative approach: let me test the theory that the conflict comes from the store by simply checking whether a build where the arm's store is NOT a v0 store (e.g. the 0x2D arm has no call) also has the conflict. 

Actually, let me try the most direct lever-free trick for a sched-order problem: the C0535 do-while block split. It splits cse1's EBB, but does it split sched1's basic block? c4 (do-while around both statements) gave 61 (worse) and c5 (around ret only) 53. So it does *something*.

Hmm. Let me reconsider: maybe the issue is not sched1 but the *expander* order. Let me look at the RTL *before* sched1 (.rtl dump) to see the emitted order.
