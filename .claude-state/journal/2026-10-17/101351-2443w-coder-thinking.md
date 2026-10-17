---
ts: 2026-10-17T16:13:51.973Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7f42f9bd4d9f47ca
model: claude-opus-5-5[1m]
effort: medium
turnId: 1d9764d9-f745-4839-857f-1b214f31db78
---
With plenty of time left, I'm digging into the local allocation tie-breaking logic in gcc 2.7, specifically how quantity priority is computed from the number of references, size, and death time in block 2's register allocation.

I'm figuring out that ties are broken by quantity number, which corresponds to birth order within the block, so fld (born earlier via lhu) should win ties over adj. That means I need to engineer the live ranges so fld and adj end up with equal priority, possibly by inserting an instruction between sra and subu to extend adj's live range, though I'm now second-guessing whether the reference counts actually match up the way I assumed.

I'm also reconsidering whether adj is really a separate local variable at all—maybe the original code does the subtraction in-place on fld, like `fld -= adj` then assigning the result to v0, which would change fld's reference count and live range enough to shift priority in the right direction. I want to try restructuring the block so the store writes fld directly and v0 just takes fld's value afterward.
