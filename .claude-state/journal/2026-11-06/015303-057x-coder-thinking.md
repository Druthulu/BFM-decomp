---
ts: 2026-11-06T08:53:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QPFpUO8KbAb2y8euSxK1
---
C0535: do{}while(0) emits 0 bytes and splits cse1's EBB. In our c2, `do { val = nudge; } while (0); val = -val;` — the do-while is around only the copy, so the neg is *after* the loop end. Maybe the block boundary needs both statements inside the do-while: `do { val = nudge; val = -val; } while (0);` — then the loop body is one block, still adjacent... hmm, no split inside.

Wait, the mechanism: `do { A; B; } while (0)` creates a label at the loop top and a branch at the bottom. The branch at the bottom (while(0)) is a conditional branch `beqz`? gcc 2.7.2 with -O2 might turn do-while(0) into a straight-line block with a label at the end... The key is where the boundary lands. If the boundary is *between* the two statements, combine can't merge.

To place the boundary between the copy and the neg, wrap only the copy in the do-while *and* put the neg inside the same block? c2 was `do { val = nudge; } while (0); val = -val;` → the label/branch of the do-while is after the copy, i.e., between the copy and the neg. But score stayed 1, so the boundary didn't survive or combine merged across.

Hmm, maybe gcc's loop optimizer (loop.c runs after combine? no, loop runs after combine) — the do-while(0) at tree level: gcc's `expand` might collapse a do-while with a constant-false condition? The condition is evaluated at runtime (while(0) → constant 0), and gcc's tree optimizer folds `while(0)` into straight-line code? In C, `do { } while (0)` is a statement; gcc's jump optimizer (jump.c) removes the branch to the loop top (since the condition is constant false, it's an unconditional... hmm).

In c2's dump we could check. Let me dump c2 and see whether a label/branch remains at combine time. Actually, C0535's mechanism says the do-while emits 0 bytes — meaning the branch/label get removed eventually, but they survive *cse1* (which runs before jump? no, jump runs before cse).

Pass order in GCC 2.7.2 toplev.c: ... jump_optimize (jump1), ... cse, ... loop, ... cse2, ... combine, ... flow, ... 

Actually C0535 says "splits cse1's EBB" — so the do-while survives until cse1. And combine runs after cse1. Does the do-while boundary survive to combine? Maybe not.

In our case the merge is done by combine, which runs after cse1. So a do-while may not help.

Hmm, but wait: maybe combine's merge could be blocked by cse2 running before combine? Pass order: cse, loop, cse2, combine? Let me check toplev.c order.

Actually in GCC 2.7.2: jump_optimize(1), cse, loop_optimize, cse (again), then combine_regs (combine), then jump_optimize(2), ... Let me check.

Regardless, empirically do-while didn't block it.

Let me think about what else combine can't merge: if i2 (the copy) has a REG_EQUAL/REG_RETVAL note? no.

Alternative approach: make the neg's source a *different pseudo* that is tied to val by a copy that combine can't see. E.g.:
```c
val = nudge;
{ s32 t = val; val = -t; }
```
Here i2 = val=nudge, i3 = t=val, i4 = val=-t. Combine merges t=val into val=-t → val=-val, then merges val=nudge → val=-nudge. Same.

What if t is used later? Then the merge of t=val into val=-t is still possible (t's value used later → t must be set... wait, t = val is a copy; if t is used later, combine can't delete the copy because t is needed! Let's think:

```c
s32 t;
...
} else {
    val = nudge;
    t = val;
    val = -t;
}
... later use of t ...
```
RTL: (set val nudge); (set t val); (set val (neg t)); ... later use of t.
Combine: merge (set t val) into (set val (neg t))? That would give (set val (neg val)) and t would never be set — invalid because t is used later. Combine's merge requires the destination of i2 to be used only in i3 (or the value to be dead after). Here t is used later, so i2 can't be merged into i3? Actually combine can still merge if it keeps i2: hmm, the merge would delete i2. If t is live after, it can't. But combine could still merge i3 and i4? i3's destination t used in i4 only → merge i3 into i4: val = -val; and keep i2? No, i3 sets t = val; merging i3 into i4 gives val = -(val) — wait, that changes t's value? No: i3 (t=val) merged into i4 (val=-t) yields val=-val, but then t is never set while it's live later — invalid. Combine's condition: i2's destination must be dead after i3 (or used only in i3). t is used later → cannot merge i3 into i4.

But combine could merge i2 (val=nudge) into i3 (t=val) → t=nudge. Then i4 = val=-t. That gives: move t,s1; negu v1,t. Two insns + t live later. If the later use of t is... we'd have to add a real use of t later in the function, which would change the code (an extra use, maybe dead → removed).

If the later use of t is dead, flow removes t and the merge is possible again.

What if t is `val` itself? circular.

Hmm. What if we make `t` an *existing* variable whose later use is already in the code? E.g., reuse `nudge`:
```c
val = nudge;
nudge = val;   // self-ish
val = -nudge;
```
nudge is dead after; merge.

What about reusing `r`? `r` is dead after. 

What about making the neg use a variable that's live later for a real reason: `hi` is live later (used in the final if)! 
```c
} else {
    val = nudge;
    hi = val;      // changes hi's value! not allowed semantically
```

We need semantics preserved. Hmm.

What about a *different* variable t that IS used later but whose assignment can be added without changing behavior? E.g., `r` is dead. No.

OK, alternative: prevent the merge at the *first* step: make the copy `val = nudge` have a use between it and the neg. What if the neg statement reads val *twice*? `val = -val + (val - val);` → simplify to -val. Adds.

What if the neg is written so the source is not the destination: `val = -val;` → `val = ~val; val++;`? two insns (not matching).

Hmm, what about `val = -val;` where the *copy* is to a different register first, like `val = nudge;` then `val = -val;` but with a **different type width** so combine can't substitute: e.g. if val is s32 and nudge is s32, fine. What if we introduce a *bitfield*? no.

What about making the copy `val = (s32)(u32)nudge;`? combine treats as same.

Let me reconsider the problem: maybe the target can be reached with a *different* source structure entirely, e.g., the neg computed into a *different variable* and stored:

Target: move v1,s1; negu v1,v1; sw v1,16(s0); sw v1,224(s0).

What if the source is:
```c
} else {
    val = nudge;
    val = -val;
}
```
vs
```c
} else {
    val = nudge;
    val = -nudge;   // dead copy
}
```
no.

What if the source uses a `?:`:
```c
val = (rand() & 1) ? nudge : -nudge;
```
→ likely `negu v1,s1` in the else and `move v1,s1` in the then. Mine.

Hmm what if the original code was:
```c
val = nudge;
if (!(rand() & 1)) val = -val;
```
c5 scored 35. Let me look at c5's diff to see what happened — maybe the move went before the call, but maybe a small tweak (e.g., computing nudge after the call) could fix. Actually the target has the rand() call at 6304 and the move at 6314 in the delay slot. In c5, the move is emitted before the call → 1 extra insn? Score 35 is large.

Let me look at c5's diff.
