---
ts: 2026-10-22T00:33:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_PgF64hjAQMm45CoUWGb1
---
Item 3: the launder is `__asm__("" : "=r"(n) : "0"(n));` — on the loop counter `n` (the trip count), placed after the first loop and after the second.

The lever's role: it makes `n` "unknown" after the asm, so the *second* loop's `if (n != 0)` test and the loop's trip count are computed from an opaque value → the compiler must keep n in a register and can't fold `n` (0x14 or 0x10) into the loop's comparison.

Without the lever, GCC would know n is 0x14 or 0x10 → the loop `while (i < n)` with n constant → GCC might unroll or use a constant bound. Hmm, but the *first* loop has no launder before it (n is set at the top). So the first loop compiles with a known n. Then the launder makes n unknown for the second loop.

Interesting: so the target's second and third loops have the trip count in a register (opaque), while the first loop's n is a known constant.

Plain-C way to make n opaque: hmm. n = 0x14 or 0x10 based on a condition. After the first loop, n is still known (0x14 or 0x10) — GCC would keep it in a reg anyway (it's a variable with 2 possible values, so it's not a constant) → the loop bound would be a reg.

So why the lever? Maybe the difference is subtle: maybe without the lever, GCC *unrolls* or *peels* the second loop (since n is 0x14 or 0x10, both multiples of 4, and the loop increments i by 4 → GCC 2.7.2 doesn't unroll anyway).

Hmm, what does the lever change? The asm's output makes n opaque → GCC can't know the trip count → no loop optimizations (e.g. "loop.c" might otherwise do something). Also the asm forces n into a *register* at that point.

Let me look at the target asm to see the difference. Let me first write the orig and a lever-free candidate and compare.

Actually, let me think about what the *first* loop looks like in the target: the first loop has NO preceding launder, so n is known (0x14/0x10) — the target's first loop must have a *constant* bound? Hmm, n is 0x14 or 0x10 depending on a runtime condition, so it's not a compile-time constant, but GCC knows it's one of two values. The loop `i += 4; while (i < n)` → the trip count is 5 or 4 iterations.

With the launder (opaque n), the second loop's bound is unknown → different code shape.

Hmm, so what would the plain-C version produce? Probably the same shape for all three loops (since n is the same variable in all). The target has the 2nd and 3rd loops different from the 1st. So the lever is needed to make loops 2 and 3 "opaque".

Plain-C way: make the trip count a value that GCC can't predict — e.g. recompute n before each loop from a source GCC can't fold:
```
n = 0x14;
if (unk70 >= 2) n = 0x10;
```
This is the same for all loops.

What if the trip count were computed differently for loops 2 and 3, e.g. from a *volatile* read? No.

Hmm! What about: the loops use a *different* counter variable, so that each loop's bound is a separate variable? The lever's effect is opacity; a separate variable is still known.

Hmm. Let me look at the target asm to understand the actual difference. Let me dump the target's asm for func_8017D73C.

Given the size (86 lines of C), the asm will be long. Let me look at the loop structure only.

Let me write the orig + a lever-free candidate first, then compare their asm.

Candidate c1: remove the two asm lines.
Candidate c2: replace the asm with a "real 2nd set" of n: e.g. `n = n;`? identity. Hmm. What about making n's value *recomputed*: e.g. before loop 2, `n = 0x14; if (...) n = 0x10;` (recompute) — that's a "real 2nd set" but the value is still known.

Hmm, what if the trip count for loops 2 and 3 were computed from a source that GCC can't fold, e.g. from the *return value* of a function? no.

Let me look at the asm first. Let me create the orig and c1 and compare their asm.

Actually, to save time: let me just write c1 (lever-free) and score it, then look at the residual.
