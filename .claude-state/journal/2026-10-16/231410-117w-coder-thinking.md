---
ts: 2026-10-17T05:14:10.450Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7f214c1b8ceabcd8
model: claude-opus-5-5[1m]
effort: medium
turnId: edd2b196-9038-4e7d-9ca7-b103d9ac818f
---
These are huge numbers of declarations scattered across TU preambles and function-local blocks, but fleet-wide sed changes are mechanically feasible since it's just text substitution. For an extern whose return is unused, changing void to s32 shouldn't alter codegen in IDO or GCC, since callers ignoring the result produce identical object code either way.

Looking at func_80161208 specifically, the callers already agree it returns s32, so the void definition is the actual liar here — I need to fix the definition to match, casting through the real callee to get the correct return value. I'm noting that param mismatches (void vs single arg) are a separate arity issue outside the scope of this return-type-only fix, so I'll leave those alone unless trivial.

Before changing anything, I want to verify from the compiled object code whether $v0 actually gets set on return — checking if func_8016130C itself produces a meaningful value that propagates through, since callers clearly expect to consume a real result.

For func_801376E8, I'm realizing the declaration mismatch is messier: most call sites declare it void, some declare s32, only one gets it right as a pointer. Since these are block-scope extern declarations inside each translation unit, I need to check whether GCC actually treats conflicting block-scope externs as hard errors, which affects how I can safely unify the signature across all those call sites.

I think s32 is actually the cleaner consistent type here, since the function's local variable `obj` is already s32 and just returned directly, so I'll change the declaration from void to s32 and verify callers casting the function pointer still work fine. Now I'm checking whether func_8012BD14, declared void, has any callers that actually consume its return value or just use it as a void call.

I'm uncertain whether function-pointer casts count as raw casts in the census, which makes that approach risky. Since the caller must consume $v0 to match the decompiled bytes, the function definition can't be void, so I need to check func_80013350's actual return type and count how many of its 136 declarations would need updating to s32 for consistency.
