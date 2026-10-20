---
ts: 2026-10-17T18:42:45.200Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: aed641f299013cd69
model: claude-opus-5-5[1m]
effort: medium
turnId: a05808f2-3ac4-478a-96ff-4005570aa66e
---
I'm checking whether the store to one symbol and the load from a different symbol could actually alias, since if they're distinct nonvarying symbols there's no dependence and the load can be hoisted above the store.

To match the target ordering, the load needs some dependence forcing it after the store — otherwise the scheduler, seeing a longer load→store chain, will prioritize scheduling the load first, which breaks the expected sequence of the immediate store before the load.

Tracing through memrefs_conflict_p... for constant addresses it checks whether both are equal constants with overlapping size windows based on the offset, otherwise treats them as non-conflicting.

Working through the specific case: load at (sym8747 - 3) versus store at sym8747 — since y is CONST wrapping a PLUS, the comparison recurses with the offset, and the overlap math (store size 1 at offset 0, load size 4 at offset -3) ends up overlapping, so these are flagged as conflicting references to the same symbol. That means encoding the load as a relative access off D_801F8747-3 rather than D_801F8744 produces the same runtime address but a different-looking relocation in the disassembly, which could matter if the scoring compares relocations directly.

I'm also trying the reverse framing, writing the store as `D_801F8744[3] = 1` referencing the array declared earlier, and checking whether its relocation symbol still mismatches the load's target — it does. So both directions give distinct reloc symbols, meaning the original binary's actual code must not depend on this symbol aliasing at all; the scheduler kept the store before the load for some other reason, maybe an unrelated data dependency, higher instruction priority, or because the `li v0,1`/`sb` pair was already sequenced earlier in the block before the load could be hoisted.

Now I want to check where the ApplyRotMatrixLV call sits in the target block versus my version — I should look at my file's tail to compare ordering.
