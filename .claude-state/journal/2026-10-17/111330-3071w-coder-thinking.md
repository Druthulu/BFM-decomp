---
ts: 2026-10-17T17:13:30.365Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: acf1e900976d98019
model: claude-opus-5-5[1m]
effort: medium
turnId: 82d9c87a-028e-4c83-b14d-9d07f43471e2
---
I'm looking at why the target still has a loop with the pointer strength-reduced by 268 bytes and a 512 literal left inside, instead of hoisting that constant out like in b.c — possibly because the comparison against the u16 field isn't structured as a separate invariant set there.

I'm trying to recall gcc 2.7's loop.c heuristics for moving invariants: `move_movables` only hoists a computation if `threshold * savings * lifetime >= insn_count`, where threshold depends on whether the loop contains a call and how many non-fixed registers are available. A call inside the loop lowers the threshold, and a larger instruction count in the loop body can tip that inequality against hoisting, which might explain why a bigger loop keeps the constant load in place while a smaller one hoists it — though I'm not fully certain this is the mechanism at play here, and I'm also wondering if the comparison type (u16 vs SI materialization for 0x200) factors in.

I'm also considering whether a reg being set more than once inside the loop, or being a "user var" tied to a tag field, would block loop.c from treating it as invariant — if `tag` gets assigned both at loop entry and again along a different return path, that could prevent the move entirely.

I'm also wondering if the comparison originated from a switch statement with a single case, since switch expansion can generate an equivalent compare-against-constant pattern, and whether loop.c's scan_loop would still hoist that constant the same way based on its rtx_cost check for CONST_INT sources.

Another possibility is that the loop just isn't recognized as a strict loop by GCC's analysis, since exits through return statements inside the body can confuse the loop detection and block the usual invariant-hoisting pass entirely.

Since the target shows strength reduction with pointer increments, maybe the original C uses explicit pointer arithmetic (`e++`) rather than indexing, combined with a goto-based loop structure instead of a for-loop.
