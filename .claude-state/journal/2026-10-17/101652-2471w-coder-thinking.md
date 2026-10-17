---
ts: 2026-10-17T16:16:52.341Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac899e71a72e1a646
model: claude-opus-5-5[1m]
effort: medium
turnId: 7b755c42-d9e9-446c-8f08-faa68444d116
---
I'm noticing the shared address register gets reused across loads instead of folding into separate memory operands, and wondering whether the issue traces back to how the compiler expands a COMPONENT_REF through a pointer cast and INDIRECT_REF chain.

The two struct-cast loads would share the same address pseudo via cse, so reusing that register blocks combine from folding the symbol into the memory operand; if instead only one load is struct-spelled it gets folded into a `lui;lw` sequence, but then the plain load at a different point in the sequence risks matching the wrong earlier load and reusing the wrong register. Tracing through the load/store order (L0 plain, store, L1, store, L2), I'm trying different combinations of which loads are struct-spelled versus plain to see which pattern avoids the bad register reuse, and considering whether making all three loads struct-spelled so they all share one address register might match the desired scoring.

I'm now exploring whether the array-indexing trick `(&D)[0]` — which folds to a direct indirect reference — could help, and whether using a variable index instead of a constant zero would prevent that early folding and change how the memory operand gets expanded and flagged.

I'm concluding this path leads into "identity address spellings" that don't really count as genuine levers, so I'm stopping that line of exploration. The best lever-free option seems to be around option 6, where the volatile cast on a read is arguably ordinary C usage per an earlier decision.
