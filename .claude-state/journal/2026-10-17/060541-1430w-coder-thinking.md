---
ts: 2026-10-17T12:05:41.402Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a8e969c8cbf9244d6
model: claude-opus-5-5[1m]
effort: medium
turnId: 150f717e-3914-450b-b185-2137b70bb2af
---
I'm noticing the target reloads both pb0[0] and pb0[1] from memory with signed halfword loads after the store, using a memory clobber to block CSE reuse — but in my version only [0] gets reloaded while [1] is reused from the already-computed value. I'm trying to figure out why CSE would forward one but not the other.

One idea is to force a reload by reading through a differently-typed pointer to the same global, so CSE can't prove the stored value and the reloaded value are identical, since the store's type might not alias cleanly with the global's declared pointer type.

I'm short an instruction compared to target (398 vs 399) so that reload would overshoot. Let me instead check if reordering the read of h to happen before the `pb0[1] +=` store matches the target's actual instruction sequence around lines 225-295.
