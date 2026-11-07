---
ts: 2026-11-06T09:55:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_PlpycrC9Kc5Ekf67WcbC
---
Interesting: --explain says score 1 for the current body? But dt.sh with orig.c scored 0. Hmm — maybe --explain reads the src body but... wait. Actually the src body has the levers; the explain says score 1 and insert move v0,s0. That's odd — it says the src body (with levers) is missing the move? But dt.sh with orig.c (same text) scored 0.

Hmm, maybe --explain reads the body from src and then *removes* levers first (that's the point of the tool: residual after delevering). Yes: "site pin ... NEEDED", "site keepalive ... NEEDED" — it explains what's needed to fix the delevered residual. So the explain is the delevered version. Consistent with my win.c: score 1, missing `move v0,s0`.

So I need real C producing `move v0,s0` at position 46.

Let me get the full target and mine disassembly to see context. Let me use --try with --keep to get the candidate object, then objdump both. Actually the tool may have a way to print assembly. Let me check --try output more; dt.sh tail only showed 2 lines by default. My tail 60 showed the insert. There's more? It showed only that. Maybe the diff is just that one insert.

Let me get the target disassembly. Where's the build? `build/` has the object. Let me find the object for this TU. Let me check how delever_search finds target. Maybe I can use --keep and then compare.

Alternative: use tools/cc1_dumps_tu.sh? That dumps our compile, not the target.

Hmm, the target asm: this is a decomp project; there must be a reference disassembly somewhere, maybe in the build dir or a .s file. Let me search for the function name in build or config.

Actually, let's think about `move v0,s0`. In the function, a0 is a pointer arg (s32 *a0), passed in $a0, saved to s0. The last statements:
```
func_8012B77C((s32)&sp20, a1 + 4, (s32)sp10);
rv = sp20;
*a0 = rv;
rv = (s32)a0;   // move v0,s0
keepalive
```

So the real code likely did something that made a0 live into v0. Hmm.

Could `move v0,s0` be the *delay slot* of the final `jr ra`? A `move v0,s0` in the return delay slot? That's typical for a function returning a value: `return a0;` would put a0 into v0 before jr.

But the function returns void per our decl. Yet the target has move v0,s0 before the return. That suggests the actual function returned a pointer — i.e., the original source's return type might be `void*` or `s32*`. But changing the return type = signature change, forbidden.

Hmm, but wait: maybe the move is NOT in the return delay slot. Position 46 of 52. Let me get the target asm to see.

Let me find the target disassembly. In this project, the target asm likely comes from the bank / config. Let me look at how delever_search obtains the target: maybe from `build/` objects. Let me grep the tool.
