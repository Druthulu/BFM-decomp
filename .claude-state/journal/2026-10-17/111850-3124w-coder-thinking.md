---
ts: 2026-10-17T17:18:50.284Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab7c1b2050f875aa7
model: claude-opus-5-5[1m]
effort: medium
turnId: e9067380-d3b2-4c4e-97d8-f140a92e4fcf
---
I'm wondering whether CSE is folding the constant symbol address into each memory access, which would explain the lui/lw pattern the compiler generates — this looks like the known cse-const-addr wall. Since the target keeps the base in a1/a3 via lui/addiu with offsets, I'm considering whether other shards avoided this by sourcing the pointer from something non-constant, like a function return value or a global, rather than a direct symbol address.

I wonder if the a1 register target comes from an inline function/macro call where the pointer param gets assigned a constant and cse propagates it the same way. Also wondering whether the struct copy actually uses a different mips.c codegen path depending on whether the byte count fits within MAX_MOVE_BYTES for inline sequential moves versus a library call.

For 32-byte copies, expand_block_move likely emits movstrsi_internal with four-register groups, and in b1 the base address stayed in a held register (s4) across both calls because cse combined them into one pseudo, whereas the target recomputes the base into a1/a3 separately -- meaning the base address isn't being held across calls in the target code.

The 3-vs-4 register grouping difference might come from how many scratch registers movstrsi_internal clobbers in this gcc 2.7 version, so I'm checking whether the pattern reserves three or four temporary registers for the block move.

Looking back at diff, it seems b1's first copy actually matches the target with 3-groups and base in a1 — so the second copy differs because its address gets CSE'd and held across calls, needing 4 temps instead, while the first copy's address naturally dies after use.

I'm wondering if calls really break CSE blocks here, or whether there's some way to rewrite the second copy's source expression so cse doesn't recognize it as the same symbol, forcing a fresh address computation instead of reusing the cached one.

I'm trying variable reassignment tricks for the second copy's source pointer, but cse would still unify the pseudos since nothing invalidates them. The key insight is that cse only drops the equivalence if the register holding the symbol address gets clobbered, which only happens for call-clobbered hard regs — so the original pins on hard registers across the call must be what's preventing the merge, not pseudo lifetime games.

I'm reconsidering how cse recognizes equivalent symbol references — when it sees a set assigning a pseudo the same symbolic value as an existing pseudo, it treats the new one as redundant and replaces its uses with the older pseudo, deleting the dead set. There's no basic-block boundary between the two copies to stop this folding, so I'm wondering whether pinning the second copy's pointer to a hard register like the original would block the equivalence.
