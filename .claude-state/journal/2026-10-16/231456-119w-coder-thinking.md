---
ts: 2026-10-17T05:14:56.556Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7f214c1b8ceabcd8
model: claude-opus-5-5[1m]
effort: medium
turnId: edd2b196-9038-4e7d-9ca7-b103d9ac818f
---
Since all three callees return s32, the real return type of these functions is s32 passed through rather than void. For func_8012CBF4 I can simply make it return the call result directly, and since its header already declares s32, I just need to mechanically update the void declarations across the codebase—around 2160 lines—wherever this function is declared in translation units that include the header.

For func_80013350, I need the extern declaration in the header to change from void to s32, then propagate that same change to roughly 1345 other void declarations elsewhere; since callers currently ignore the return value, flipping void to s32 has no codegen impact, and it actually corrects another inaccurate signature.

For the 80161208 case, the fix means making the function return the result of calling func_8016130C with its arguments, keeping the existing cast that already treats the return as s32, since the underlying function signature uses a different parameter type that the cast works around.

I'm reasoning that returning a value through a jal call compiles identically whether the function is declared void or s32 under IDO/GCC — same instruction sequence — so this should be a safe, invisible change to verify with make check. Then checking func_80161208's callers: most already declare the return as s32 or compatible int types, so only the definition itself needs updating; moving on now to look at func_801376E8, whose definition returns a void pointer but has a mix of caller declarations — 1442 void, 21 s32, and 1 void pointer.

So s32 it is for that case. Now checking func_80150480 — def and all decls are s32, but I need to check if the body actually returns a value or just falls through without setting v0. Similarly func_8017E3F0 and func_801843E0 appear as different functions across overlays at the same address, so each copy's def and callers should agree independently. Let me look at func_80150480's body next.
