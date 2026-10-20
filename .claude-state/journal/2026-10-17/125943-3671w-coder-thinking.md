---
ts: 2026-10-17T18:59:43.510Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6ee12ed7d3da1789
model: claude-opus-5-5[1m]
effort: medium
turnId: c73a5082-25b2-49a4-a028-dd1d5ff9dd77
---
I'm tracing how GCC's CSE pass handles the pseudo for the `rot` stack address, noting it assigns to s0 across the call, and wondering how the target version avoids that by laundering the value differently after the function call returns into q1.

The asm code explicitly kills q1 after setting it, so later lookups for the sp+24 address have no live register holding that value and must recompute it rather than reuse a stale pseudo. I'm questioning whether CSE's cost model, which favors registers over computed addresses, is what triggers substitution across calls in my version but not in the original.

For pseudo registers holding frame-pointer-plus-offset, CSE would favor the cheaper plain register over recomputing the address, so the question is whether distinct offsets or distinct call sites produce different cache entries that prevent this reuse from happening in the original code.

Actually I'm realizing this is about expand_call and how arguments like simple address expressions get moved into hard registers directly — when the expression is just a plus of frame pointer and constant, it may bypass a pseudo and emit the move straight into the argument register, which would explain `addiu a1,sp,24` appearing without any intervening pseudo.

Right, this matches `precompute_register_parameters` in expand_call — when optimizing, non-constant non-register argument values get forced into pseudos so CSE can later recognize and reuse them, which explains why repeated address-of-local expressions collapse into a shared pseudo register.

Now I'm tracing the asm version: the q1 pseudo is already a register, so no new pseudo is created — its value gets copied straight into argument register a1. If a variable holding sp+24 is reused across several calls without being reassigned between them, CSE will keep substituting that same pseudo register for subsequent occurrences, so I'm walking through the call sequence to see exactly when q gets killed versus when it stays live and gets reused as `rot`.

I'm also considering a riskier trick: reusing `q` as a pointer for the sv loads/stores between calls, letting it point at sp+16 temporarily instead of sp+24, though I worry CSE might fold that pointer back into fixed base-relative addresses anyway. I'm also noting that passing `rot` with different types across calls shouldn't matter for this purpose.

Since m1 gets reassigned after RotMatrixYXZ and later used by func_80048D9C at a different stack offset, I'm sketching a plan where a single generic pointer variable gets reassigned between calls (first to rot, then needing to be killed and reused), but I can't yet see how to force that kill reliably -- it might come down to how CSE treats frame-pointer-relative equivalences when a register just happens to hold one.

Trying alternate approaches: wrapping the rot argument differently (explicit indexing, pointer arithmetic, a new struct) still folds to the same frame offset, so none of these break the equivalence. I'm wondering whether using two separate pseudo-variables for consecutive calls would help, but CSE seems to just treat the second as a copy of the first and still collapses them -- it's past 1pm now, about four minutes into this specific experiment, and I want to check whether the target's sv address also gets recomputed somewhere.
