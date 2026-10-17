---
ts: 2026-10-17T11:18:05.683Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7979eba5885c3edf
model: claude-opus-5-5[1m]
effort: medium
turnId: 921e828f-1fac-424f-94a0-d040638a6158
---
Tracing the fallthrough case, I find the jump's next instruction resolves to the same code label, giving both branches value 0, so the equality check predicts not-taken by default.

I'm considering whether the second branch could instead use NE, but since the jump targets "cont" via EQ regardless of source phrasing, that path seems ruled out. More promising is that stealing the delay-slot instruction (v0=0) into a branch that itself reads v0 is still valid on MIPS, so I need to check whether the first return value could be something other than a simple zero assignment that still satisfies the stealing constraints.

I'm also exploring whether ordering effects explain the asymmetry — maybe the target thread's jump got its delay slot filled first due to branch-prediction heuristics like mostly_true_jump or rare-label detection, or possibly because the continuation label is preceded by a loop-begin note (e.g., from a `do {} while(0)` construct), which could bias gcc to fill the target branch before the fallthrough one.
