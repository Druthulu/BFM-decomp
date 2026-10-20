---
ts: 2026-10-17T17:23:36.806Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab7c1b2050f875aa7
model: claude-opus-5-5[1m]
effort: medium
turnId: e9067380-d3b2-4c4e-97d8-f140a92e4fcf
---
I'm close on b5 - the first part matches now since separating the ret assignment broke the crossjump. I'm reworking the overshot branch to directly generate the comparison and conditional store sequence instead of using the generic ret/overshot pattern.

Still, the question is why the first branch's `li v0,1` and `j end` don't crossjump into the second path's `li v0,1` in the target — that difference must come from what precedes it at jump-pass time, likely the asm statement versus the store comparing differently before the crossjump tail-merge runs.

I'm still trying to figure out why the barrier version blocks the merge while mine doesn't—maybe it's about where ret=1 sits relative to the asm keepalive, or differing hard-reg assignments at jump2 time. I'm sketching out more variant test cases (b6, b7) to isolate what structural difference triggers the cross-jump optimization.

Trying variant b2: setting ret = 1 upfront then conditionally resetting it inside the branch when cur differs from t, which gives a different instruction count. Then testing b7, the swapped version where overshot being false triggers the store-and-set-to-1 path instead.
