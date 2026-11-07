---
ts: 2026-11-06T22:14:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6yhu1pYX0YhdnzR2OF2w
---
In the target: `lui a1,0xff` at 166, `ori a1,a1,0xffff` at 170 — interleaved with the sxy stores. In mine (i2.txt): `lui a1,0xff` at 163, `ori` at 167. So 3 positions earlier (163 vs 166). The scorer's index said 150 vs 154 (difference 4?).

Anyway, mine places the mask 3-4 instructions earlier. The target places it among the sxy stores (after lhu v0,8(sp) at 165).

This is a sched1 ready-list/priority difference. Since the whole body's schedule matches except this, a small perturbation might fix it.

Idea: the mask constant 0xFFFFFF is used at the `and v0,v0,a1`. In the target, the materialization is scheduled right before its use region. In mine, slightly earlier. The scheduler's tie-break depends on the insn's "priority" (length of the dependency chain). If we add a dependency between the mask and something later, it'd be delayed.

What if we compute the mask from the otp value? E.g., `(*otp & 0xFF000000) | ((u32)pkt & ~(*otp & 0xFF000000))`? That changes semantics.

What if the mask constant is used in a *different* order: `((u32)pkt & 0xFFFFFF) | (*otp & 0xFF000000)` — k_swap = 5 (MIXED). Close but not 3.

Let me try other expression shapes for the final store:
- `*otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);` (current)
- `*otp = (*otp & 0xFF000000) | ((u32)pkt & ~0xFF000000);` (~ same value)
- `*otp = (*otp & 0xFF000000) + ((u32)pkt & 0xFFFFFF);` (+ vs |; values disjoint so same result; the RTL would be plus → `addu`, but the target uses `or`. combine might convert plus of disjoint? No.)

Hmm.

What about the *do-while* placement: i2 wraps `otp = ...; *otp = ...;`. The mask's birth is in the second EBB. What if we wrap a slightly larger/smaller span so the mask's position shifts by one? j1 (only store) = 20, j5 (only otp assignment) = 20, j2 (oidx+otp) = 13.

What if we use a *different* construct that creates an EBB split at the same place but with a different sched1 boundary: e.g., `if (1) { otp = ...; *otp = ...; }`? That's a constant branch, folded. Or a `for (i=0;i<1;i++)`? adds code.

What about C0535's do-while specifically splitting cse1 EBB — the effect we want is on sched1, not cse1. Hmm, the do-while also splits the basic block for sched1? Actually a do-while(0) with no loop is removed by the front end or creates a NOTE_INSN_LOOP? In GCC 2.7.2, `do { } while (0)` produces a `do-while` in the tree which expand handles as a loop with a single iteration? It might create a jump/note that splits EBBs.

Given i2 = 3 (very close), let me try a few more span variants:
- l1: do-while around `otp = ...; *otp = ...;` but with the otp assignment *inside* and the store outside? No.
- l2: do-while around `oidx = ...; otp = ...; *otp = ...;` (j2 = 13).
- l3: do-while around the sxy store lines (before the tail) to shift the schedule boundary.
- l4: do-while around the whole packet-store + otp block (i3 = 23).
- l5: two nested/sequential do-whiles.

Actually, the residual is only the mask materialization position. Let me try moving the mask computation into a variable *declared inside the do-while*:
```
do {
    u32 m = 0xFFFFFF;
    otp = ...;
    *otp = (*otp & 0xFF000000) | ((u32)pkt & m);
} while (0);
```
The variable m might be scheduled differently (a pseudo with a use in the same EBB). Let me try.

Also:
```
do {
    u32 pw = (u32)pkt & 0xFFFFFF;
    otp = ...;
    *otp = (*otp & 0xFF000000) | pw;
} while (0);
```
This creates a temp for the pkt mask, which might tie to the constant.

Let me test these.
