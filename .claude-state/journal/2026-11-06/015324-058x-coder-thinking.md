---
ts: 2026-11-06T08:53:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ihVSdLwTx3zTK9MDRiM7
---
c5 changed the register allocation globally (param_1 moved from s0 to s1). So it's a different beast. Not useful.

Let me think about the actual GCC semantics again. The target has `move v1,s1` in the bnez delay slot, which is the *then* branch's copy. The else's negu v1,v1 uses v1 — which was set by that delay-slot move (executes always).

In mine, the same move is in the delay slot, and the else's negu v1,s1 uses s1.

So in the target, the else's neg takes its operand from v1 (val's register) rather than s1 (nudge's). Since the move executes in the delay slot, the value is available.

Wait, could we get `negu v1,v1` without a second copy in the else, by making the neg read `val` (which the RA maps to v1)? That's exactly what the asm does. In mine, combine replaced val with nudge in the neg, so it reads s1.

What if we prevent combine from replacing the *use* of val in the neg by making val's value at that point not provably equal to nudge? E.g., if the copy were `val = nudge;` but between the copy and the neg something *could* modify val (like a call or an aliasing store). If val's address were taken... no.

What if the else's neg is guarded by a condition that could... no.

What if we write the else as:
```c
val = nudge;
val = -val;
```
but make `val` a **volatile**? no.

Hmm, what if we make the copy `val = nudge;` where nudge is `volatile`? That changes nudge's loads everywhere.

What if the copy is `val = (s32)*(volatile s32 *)&nudge;`? adds a load.

New idea: use the fact that combine merges a *copy* into a unary op only if the copy's source is a register. If the copy's source is a **constant expression**? no.

What if the copy is `val = nudge;` but `nudge` is re-assigned right after? no.

Let me look at the problem from the "sched1" angle: maybe we don't need to block combine; maybe we can accept mine's `negu v1,s1` and instead change the RA so s1 is v1? I.e., if `nudge` were allocated to v1 instead of s1... but nudge must be s1 because it's live across the rand() call? No: nudge (s1) is live across the second rand() call (computed before, used after). So nudge must be callee-saved (s1). val is v1. So the register pair difference is inherent.

What if the *copy* `val = nudge` were the only thing... no.

OK here's another thought: what if the else's `val = nudge;` can be made to survive by making it a *conditional* copy that the compiler can't merge:
```c
} else {
    if (nudge) val = nudge; else val = nudge;
    val = -val;
}
```
adds branches.

What about `val = nudge; val = -val;` where the neg is written via a helper *macro* that's pure C, e.g. `val = -(s32)val;` same.

Hmm, let me look at what other T11 shards did with similar `combine-copy-merge` walls. moves.md has `combine-copy-merge` wall (G23) and `cse-copy-merge` (G22x). Let me grep moves.md for those and read the entries.
