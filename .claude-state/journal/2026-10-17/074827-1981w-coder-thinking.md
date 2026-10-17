---
ts: 2026-10-17T13:48:27.198Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a715c83225823a44a
model: claude-opus-5-5[1m]
effort: medium
turnId: cb00494e-7b3a-4f28-b3fa-24b3d50bb0ef
---
I'm tracing which pseudo-register corresponds to `my` versus `mny` based on declaration order in the source, since variables declared as `s16 my, mny, mx, mn;` would get sequential register numbers starting around r101.

I need mny to gain one more reference to tip the register priority count above my's. I'm considering whether any redundant assignment elsewhere in the code already computes a value equal to mny that could instead be spelled using mny directly, which would add a ref without changing behavior. I want to scan the lines around the min/max computation for yy coordinates to find such an opportunity.
