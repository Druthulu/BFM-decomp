---
ts: 2026-10-17T12:44:46.857Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: aa713f978f6769f98
model: claude-opus-5-5[1m]
effort: medium
turnId: 29f80c87-241a-492d-b40b-c42d868c661f
---
I'm reconsidering register priority — the score units don't match up, so I'm wondering if hoisting the load of rb earlier, before the flags check, would make it live longer across that test and lower its priority without changing reference counts.

Actually the target shows rb loaded after the branch, which contradicts that. So instead I'm looking at m: maybe if m's live range were shortened by computing it directly inside the then-block rather than before the branch, scheduling could fill the branch delay slot with that computation from the fallthrough path, matching the target's instruction placement.

But then local-alloc in the then-block would normally tie m directly to a0 since it's copied right into the call argument, skipping the move -- yet the target still has a separate move, so something else must be keeping a0 occupied during m's lifetime, which doesn't quite add up given locals only see hard registers. I want to check one of the earlier heuristic variants to see what register m actually received there.
