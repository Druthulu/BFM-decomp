---
ts: 2026-10-17T12:06:55.128Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a8e969c8cbf9244d6
model: claude-opus-5-5[1m]
effort: medium
turnId: 150f717e-3914-450b-b185-2137b70bb2af
---
My third attempt failed again due to that extra replacement I added. I'm puzzled why the first load/store sequence gets reloaded but the second doesn't - let me trace through the actual instruction sequences for both halfword operations to spot the divergence.

Looking more carefully, I'm wondering if CSE's invalidation logic treats the two memory offsets as non-overlapping ranges, so an equivalence survives for the second store but not the first. The division trap handling sitting between the stores might also be interfering with how CSE tracks the live values across that boundary.

Maybe the store ordering should put q3v before the [1] store instead.

I'm wondering whether original code avoided a cached local pointer and instead reloaded D_8017E914 via the global each time, since without strict aliasing a u16 store could invalidate that cached value and force a reload — that matches m5's extra load, but the target only has a single lw/lui pair. So maybe the read is happening through a different access mode than I assumed.

I'm testing whether reloading pb0 from the global again right before the h block, or changing how the [1] store's address is expressed, could break cse's ability to forward the stored value and produce the right lh pattern.

Alternatively, I'm trying a variant where a fresh pointer `ph` is cast from pb0 and used for both loads, hoping that if the compiler doesn't propagate the copy, it avoids canonicalizing to the pb0 pointer and generates the needed extra load.
