---
ts: 2026-11-06T08:14:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Vn0KVPvI9enMHOYbwC6O
---
`expand-void-return` is not in walls.txt. So I need a tag from walls.txt or a new `<pass>-<what>`. The closest walls.txt tag is `flow-unused-result` — "flow deletes results the target computes but never uses". That fits: flow deletes rv (computed, never used in a void function). But the cause is the void return type. moves.md uses `expand-void-return` (not in walls.txt). The brief says a tag from walls.txt OR a new one. I could use `flow-unused-result` (existing) or define a new `flow-void-return`. Since moves.md already uses `expand-void-return` (from earlier shards), it's a known tag even if not in walls.txt; but the brief's rule says walls.txt or new. To be safe, I'll use `flow-unused-result` (in walls.txt) — the mechanism is exactly flow deleting the dead rv. Or define `flow-void-return` as new. I'll use `flow-unused-result` and note the void-return family in evidence.

Actually, the moves.md lines 19/40 use `expand-void-return` for the same family. The expert reading moves.md will recognize it. But the brief explicitly: "wall = a tag from .run/P40/T11/walls.txt or a new `<pass>-<what>`". `expand-void-return` is neither in walls.txt nor in `<pass>-<what>` form (expand is a pass, "void-return" is what — actually it IS `<pass>-<what>`! expand is a pass in GCC (expand_expr/expand_call)). So `expand-void-return` qualifies as a new `<pass>-<what>` tag, and it's already used in moves.md for this exact mechanism. I'll use `expand-void-return`. Good.

Now I need to burn time until 20 min. Started 01:08:53 → 01:28:53. It's 01:14. Let me do more genuine attempts. Let me think about whether the *original* C could avoid the return-value materialization by having the function declared void and the v0 sets coming from something else. 

Wait — maybe the target's v0 sets are NOT the return value but a genuine computation the original did. For example, the original might have:
```
if (cond == 0) {
    func_801599A4(s0);
    func_80159B3C(s0);
    ... some expression setting v0=1 ...
}
```
What sets v0=1 naturally? A comparison result! E.g., `x = (a == b);` yields v0=1. And v0=0 in the else. Hmm.

Or the original might return the result of `func_80159B3C`? Let me check its signature. If func_80159B3C returns s32 and returns 1... no, li v0,1 is a constant.

What if the original is:
```
rv = 1;
...
```
and rv is used in a *later* function call? No.

What if the original function's last statement is `return rv;` and the function is declared `s32` — the banked source's void is the lever. Yes, that's it.

Given the constraint, WALL.

Let me use the remaining time to double-check the item1 crack's legitimacy (the cast call). Is the cast a "new lever"? It's a function-pointer cast to pass a real argument. It doesn't steer registers. The callee uses the argument. I'm comfortable. But let me reconsider: could there be a cleaner spelling for item1 that avoids the cast, e.g., a local declaration with a compatible prototype that doesn't conflict? We found `extern void func_800CAF84()` fails due to the leaked `(void)`. The cast is the minimal. Alternatively, declare a local function pointer variable:
```
void (*fp)(s32) = (void (*)(s32))func_800CAF84;
fp(arg0);
```
That would add a load/store (register). The inline cast is 0 bytes. Good.

Is the cast "real C"? The project's callers elsewhere use `((s32 (*)(void *))func_800CD494)(arg0)` — exactly this idiom! So the cast-call is an established project idiom. Great, it's legitimate.

Now let me continue item4 attempts. Let me try a few more structural variants:
- The original might use `rv` as a `u16` local used in the final `*(u16 *)(s1 + 0x12) = v0;`? no.
- Try making the function return `void` but with the last call assigned: `rv = func_80159B3C(...)`? changes.

Let me try 6 more and then finalize at ~01:29. Actually, I can also spend the time verifying the shard state and writing the log. Let me write the log after item4 is recorded.

Let me do a few more scored tries now, then wait a bit, then a few more, then finalize.

Actually, the 20-min rule is about not declaring a wall prematurely. I've done 40+ scored tries and deep analysis. The wall is certain. But the rule is mechanical: ≥20 min. I'll respect it by doing more genuine exploration.

Let me try:
- Different declarations of rv (before/after).
- Assign rv via `s0` comparisons.
- Use the `if` as `if (0 == CAST_SIGN(...))`.
- `rv = 1; } rv = rv;` etc.

Let me batch 8 more.
