---
ts: 2026-10-17T13:59:43.043Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a2ab9a444ea3aa2ca
model: claude-opus-5-5[1m]
effort: medium
turnId: 4fd53509-0294-4563-a878-c510da735377
---
I notice the same pattern again: both arg1 and arg2 use the hard register for short-lived reads while the long-lived copies live in separate temp registers, confirming arg2's short use at line 22 reads a2 directly rather than the pos copy.

Since pos is only ever used as `pos ± 2` stored into a 16-bit field, its high bits genuinely don't matter semantically — but combine can't exploit that because the sign-extension insn and its two uses sit in different branches, outside combine's single-block scope, so this mirrors the S03 problem exactly without an obvious combine-based fix.

Maybe the real explanation is simpler: if arg2 is declared as an s16 parameter in the source, then in 2.7 the callee doesn't trust the caller to have sign-extended it, so it re-extends via sll/sra right where it's used — explaining why the duplicated sll/sra sequences appear separately in both branches rather than once at function entry.

So I need two logically distinct values from the same param without CSE merging them — maybe an opaque identity operation like adding a provably-zero local variable, though multiplication by 1 or memory round-trips either get folded or add unwanted instructions. I need to find an operation that survives as a genuine copy without being optimized away by constant propagation.

Trying more equivalent forms: no-op conversions, self-OR/self-AND identities that fold to the operand itself, and masking with `(u16)arg2` to see how combine handles the resulting subreg patterns.

I'm also considering reordering: placing the `pos = arg2` copy after the initial branch uses so CSE has no equivalence to exploit at that point, meaning the branches read the raw pseudo while later uses of `pos` get canonicalized once the copy exists downstream.

I'm trying to find an opaque reg-to-reg copy that cse won't just fold into an equivalence—considering subreg tricks, mode changes, or pinned registers—but none of these seem to actually break cse's ability to record the two pseudos as identical, since any plain SImode set is treated as an equivalence regardless of type.

Another angle: maybe the two separate registers originate from an inlined helper function, where the parameter gets its own pseudo distinct from the caller's pseudo for arg2. But even then, that's still a reg-reg copy that cse should recognize as equivalent, so I'm not sure that explains why the target ends up needing two live registers instead of one.

I'm questioning whether cse's canonical-choice logic is really the thing I need to fight, or whether the real answer is that the param pseudo gets assigned a hard register directly by global allocation for its short use, while the long-lived value is handled separately as a local allocation.

Also wondering if combine could substitute the hard register into the andi insn if the param pseudo has a single use, since combine typically avoids propagating hard regs but might make an exception here.

Given the multiple-use case though, two pseudos seem necessary, so I'm considering changing arg1's declared type to force different parameter handling through assign_parms and promotion rules — but that risks conflicting with the existing extern declaration in the TU, meaning I'd need the full translation unit to resolve it cleanly.

I'm wondering if the branch target reuses a1 directly rather than via the copy, or if the test is written through a different mode cast that CSE would still canonicalize away. The real question is whether there's any register-to-register copy that CSE simply doesn't record, which would make the copy opaque to the optimizer.

Thinking about mode-crossing copies: converting through a wider signed type and then truncating back could leave a dead sign-extension instruction that flow's dead-code elimination would strip out, leaving just the mode-converted result.

For unsigned types, the high bits become a zero rather than a sign-extend, so I should check whether cse can see through subregs of a DI pseudo there too. I'm also considering whether structs/unions passed in registers would actually force a spill to memory, and planning to test the signed 64-to-32 truncation case directly, isolating variable pos while removing the other pins to see the effect cleanly.
