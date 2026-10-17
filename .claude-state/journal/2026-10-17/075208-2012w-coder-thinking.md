---
ts: 2026-10-17T13:52:08.010Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a91f36121b5043b6a
model: claude-opus-5-5[1m]
effort: medium
turnId: 2eee350e-3a84-4d56-9c95-e752be0f81a2
---
I'm looking at how the two calls computing the same base-plus-offset expression could get folded by common subexpression elimination, since the compiler might treat the symbol-plus-0x18 arithmetic as redundant across both function calls on each face.

I'm trying different ways to break that equivalence—rephrasing the pointer arithmetic, using different struct member accesses—but they all still reduce to the same constant offset computation that cse would unify. The real fix seems to be whether the first add result lands in a hard register that gets clobbered by the call, forcing cse to invalidate its equivalence table and recompute the offset fresh for the second use.

I'm wondering if preventing pseudo reuse requires making mb non-constant to cse, like loading it from memory via a static pointer or param — but that changes the generated code shape. I'm also considering whether the second call could use a differently-typed pointer offset, like casting mb to a MATRIX pointer with a non-multiple offset, to avoid matching the same constant expression.

Then I think about how cse tracks a pseudo's equivalence to a constant across calls, since calls don't invalidate pseudos, so later computations of the same offset just reuse that pseudo — unless the argument is forced directly into a hard register rather than precomputed into a pseudo during expand_call.

I'm trying to figure out if the source computed the pointer expression twice using a variable base rather than a known constant, which would explain why the target keeps the base in a register instead of folding into one canonical pseudo.

Maybe the original source had `mb` as a pointer variable assigned once and reused across both calls with an offset, which would explain why GCC keeps the base address in one register (s0) and only computes the offset (+24) separately for each call rather than reloading the full address twice.

Trying variant spellings of the mb pointer arithmetic across both calls, testing different casts and declarations to see which reproduces the exact compiled output.

I'm checking whether cse invalidates constants across the call boundary — it only clears call-clobbered hard regs and memory, not pseudos. Then I'm looking at whether a label or branch sits between the two calls in the original assembly, since that would flush the cse block table; checking around lines 115-120, the two jal instructions appear adjacent with no intervening code, though an empty-if branch could still leave a stray label if jump optimization didn't fully remove it.

Another angle: maybe the base pseudo mb is assigned to the constant in a separate cse block from where the calls occur, so cse never establishes mb equals that constant value when computing the pointer-plus-24 argument for the second call.

But if both calls fall within the same expression-hashing block, cse would still unify the repeated "mb + 24" expression regardless. Maybe the repeated vertex/face code wasn't actually a loop in the original source, since GCC won't unroll loops without explicit unrolling flags — so it's more likely a macro expansion, and the matrix struct might be getting passed in a way that differs subtly between calls.

I'm reconsidering whether register argument handling in GCC's expand_call always produces a pseudo for the PLUS expression, meaning P would exist regardless and its equivalence class should include both the register and the constant in CSE—so the second mb+24 reference should still resolve the same way.

But maybe mb isn't treated as constant to CSE if it's assigned across a branch or label boundary, putting it in a different CSE block than the first reference—that could explain why the two accesses to mb+24 and mb+0x18 don't get unified despite structurally resembling the same constant class.

I'm trying to figure out if there's some invalidation happening when mb itself gets modified, but since P=(plus mb 24) doesn't depend on anything else being changed, that doesn't seem to be the breaking factor. Another angle: maybe mb stays live across the second call because it's reused afterward in subsequent operations, which could explain why the compiler prefers keeping it in s0.

I'm also wondering if the second argument expression differs structurally even though it has the same value -- maybe it's cast differently or references a different struct member offset that coincidentally equals the same address. I should check the cookbook for similar "launder" patterns and how prior fixes handled these redundant move eliminations.

The target keeps `mb` live across the first call and recomputes `mb + 0x18` afterward rather than reusing the pseudo. I'll check the cookbook for launder-removal moves before trying specific rewrites.
