---
ts: 2026-10-17T11:54:29.886Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a8e969c8cbf9244d6
model: claude-opus-5-5[1m]
effort: medium
turnId: 150f717e-3914-450b-b185-2137b70bb2af
---
I'm noticing the load instruction appears scheduled before the prologue setup, while in my version it shows up later, after the lhu instruction, suggesting the scheduler is reordering things differently than expected.

Looking more carefully at the instruction ordering, I'm comparing my full listing against the target position by position: mine has addiu, sw, move, sw, sw, lhu, then the lui/lw pair, followed by another lui/lw pair and a store. The question is why the pb0 load lands first in the target even before the parameter copy — likely because the asm volatile keepalive acts as a scheduling barrier, forcing the load to precede it while everything else gets pushed after.

Thinking through the bottom-up list scheduler's priority calculation, the key is memory aliasing: since all these stores go through s16-type pointers, the scheduler probably treats them as potentially aliasing, creating a dependency chain where the store to pb0's memory must happen before a subsequent load, which in turn ties the load of pb0 and the load of t1 together — and the tie-break apparently favors scheduling the t1 load first.

Comparing register allocations between the target and my current output: pb0 maps to t1 vs v1, pac to a2 vs likely different, pb8 to t0 vs a3, and b to v1 vs t0. I'm considering several angles to try next — using local variable copies for p2, re-declaring the extern pointer differently, changing declaration order since pseudo-numbering affects local allocation ordering, or restructuring statement order so all three pointer loads (pb0, pac, pb8) are grouped at the top of the function. Let me check what approaches history has already tried.
