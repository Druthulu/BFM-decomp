---
ts: 2026-10-17T11:37:01.093Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7979eba5885c3edf
model: claude-opus-5-5[1m]
effort: medium
turnId: 921e828f-1fac-424f-94a0-d040638a6158
---
I'm noticing that cross-jumping here reduces the minimum because the block is essentially a jump around itself, so a condjump wrapping each single-instruction block means identical blocks in the ladder merge together.

To stop them merging I need the blocks to differ in RTL, not just syntactically. Adding a volatile memory barrier would insert an extra insn making them distinct, but I'm trying to find a plain C fix — reordering the if/else won't help since every if/else produces that same jump-around pattern, and switch statements with GNU case ranges would compile to a different structure (jump table or compare tree) rather than the ladder I need. I'm also checking whether varying how the pointer is assigned, or how the symbol is referenced, changes the RTL — but these all fold to the same representation, and redeclaring the array elsewhere still refers to the same symbol.

What I actually need is for the RTL patterns to differ while still emitting identical final code — maybe via a REG_EQUAL note mismatch — since cross-jumping merges blocks when patterns are equal, but can be blocked if there's a meaningful pattern difference underneath.

I'm wondering if two different symbols could coincidentally resolve to the same address via linker aliasing, though that seems unlikely. Maybe the blocks weren't actually identical before cross-jumping—perhaps one had an extra dead store that got eliminated earlier, making them match only by coincidence at this late stage.

Let me reconsider the find_cross_jump mechanics directly: if I trace insn=21 with target=65, e1 and e2 line up such that the minimum reduction hinges on where i1's jump label falls relative to e1, so I should check the reverse direction too, starting from insn=65 toward target=21.

I'm also wondering whether the two blocks could differ in the actual RTL pattern emitted for the pointer assignment — maybe cse or a later pass folds a symbol-plus-zero expression into a plain symbol reference, which would make two syntactically different statements collapse into identical insns after jump2. I should check what D_80180BB8 actually refers to and whether a neighboring symbol could explain this.

I'm wondering if the two blocks could call the function with different argument expressions directly—one calling with the address inline and the other via the pointer variable—so cross-jump merging would unify them anyway once both paths converge on the same call. At roughly fifteen minutes into this exercise, I'm considering tweaking how the second block's pointer gets assigned to break that symmetry.

Then I notice the addresses ABC, AE0, B04, B28, B4C, B70, B94, and BB8 are each spaced exactly 0x24 apart, which means they're not separate variables at all but eight consecutive 36-byte entries in a single array starting at 0x80180ABC, indexed 0 through 7. That reframes the whole problem: the original code is almost certainly declaring an array like `u8 D_80180ABC[8][0x24]` and indexing into it rather than referencing distinct symbols.

But I'm stuck on why two blocks resolve to the same index 7 entry — if both used the same index expression, they'd produce identical RTL and merge, so there must be some difference in how the index is computed or symbolically represented that keeps the blocks distinct despite pointing at the same address.

I'll test a couple more variations — one where the array indexing is represented differently (as an array of 36-byte elements) and one using a ternary chain — then move on to other hypotheses.
