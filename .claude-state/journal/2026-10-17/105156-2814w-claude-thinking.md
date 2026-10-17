---
ts: 2026-10-17T16:51:56.428Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac33bcc12f95b099e
model: claude-opus-5-5[1m]
effort: medium
turnId: 642fce30-a585-4106-9bf9-735136648dff
---
Each coder handles a shard of roughly 8 functions with a 20-30 minute cap per item—if that's exceeded, I record the wall time and move to the next item, with the coder persisting through the whole shard. I'm grouping round-robin by size rather than by kind or translation unit, so similar functions get spread across different coders; since these are singletons, the exemplar-propagation already happened in T9 for the 38 head classes, so there's nothing left to propagate here.

Still, kind/mechanism similarity could warm up context even without shared propagation, so I'd recommend re-sharding by lever kind (and TU) instead of round-robin by size—cost is minimal, and T10 already showed walls/moves clustering by kind. Given only 7 of 50 shards are briefed so far, I should flag this now to the developer and ask whether to re-deal the remaining 43 shards by kind, keep roughly 8-12 items per coder, and add a shared "moves that cracked" notes file alongside walls.txt.
