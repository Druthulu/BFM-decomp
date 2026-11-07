---
ts: 2026-11-06T10:04:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZXBq4gwCl1hbnY1y0uG9
---
`depth = 1` initially! So outside loops, loop_depth = 1, inside a loop it's 2. So refs outside loops add 1 each; inside add 2.

So:
- f: refs at f=0 (outside loop, depth 1), f=1 (inside loop, depth 2), f!=1 (outside, 1). n_refs = 1+2+1 = 4. Plus maybe the set counts as 2 refs if modified ("counts a register twice if modified" — for SET insns, the reg is counted twice: once as set, once as use? The comment says "This counts a register twice if it is modified"). Let me not over-model.

- i1: i1=0 (depth 1), i1<5 compare (depth 2), i1++ (depth 2, counted as 2 refs since increment), etc. Roughly 1+2+2+2 = 7.

- giv: initialized (depth 1), incremented (depth 2), used (depth 2)...

Priorities: pri = floor_log2(nrefs)*nrefs/live_length*10000.

The keepalive adds a use of i1 inside the loop: +2 refs (and +1 live length maybe).

Hmm, but empirically it flips f and giv. That suggests the effect is on the giv, not i1. Maybe the asm use prevents loop.c from optimizing the giv's init or the giv's refs change.

Let me just experiment. I'll create variants and score.

Variant ideas for item 4:

A. Wrap the loop body in `do { ... } while (0);` (C0535: splits cse1 EBB). This may change register allocation.
B. Move `f = 0;` into the for-init: `for (f = 0, i1 = 0; i1 < 5; i1++)`. 
C. Reorder declarations.
D. Change `f != 1` to `f == 0`.
E. Use `f |= (cond)`.
F. Use a second variable for the condition.
G. Declare f before/after i1.
H. Use `i1` in the loop condition differently: `for (i1 = 0; i1 < 5; i1++)` vs `i1 <= 4`.
I. Add `&& i1 >= 0` — no.

Let me first check: does the keepalive-free body differ ONLY in this swap? Score 7 with 222 ins both. So yes, only the f/giv swap (6+3 = 9 register-pair differences but 7 score).

Let me try variant A (do-while around the body). Note: do{}while(0) needs `// !FAKE: do-while` per constraints. But wait — do-while(0) is a real C construct; the constraint says only with the marker. Fine.

Actually, the keepalive is inside the loop; wrapping the body in do-while(0) is a common ref-boost trick.

Let me also consider: the original keepalive is `"r"(i1)` — it makes i1 live at the END of the loop body (after the if). If I write a real statement using i1 at the same place, e.g. the increment `i1++` — already there. Hmm.

What about `if (*(u16 *)(D_801AECD8[i1] + 2) == 5) { f = 1; }` → move the array access to use i1 directly twice? 

Let me think about what the asm insn does to loop.c: The asm `"r"(i1)` is an insn with a USE of i1. loop.c's strength reduction: it looks for induction variables; the giv is i1*4 + base. The extra use of i1 might make loop.c treat i1 as a biv and... 

Hmm, actually maybe the key is that the asm use makes i1 live until the end of the loop body, so local-alloc gives i1 and the giv different registers... 

Let me just run experiments. Write a generator script.

Actually, let me reconsider the scale of this task. Four items, three likely walls. Item 4 needs cracking. Let me focus effort: try ~20 variants for item 4, and for items 1-3 record PARTIAL/WALL.

But hold on — for items 1-3, if I record PARTIAL:keepalive,pin with win.c = orig, that requires no tries. But is PARTIAL honest? The win.c scores 0 while keeping the levers. Yes. And "best" = lever-free best (15/23/28).

Hmm, but the brief's primary ask is a lever-free body scoring 0. The expert will see PARTIAL rows. The moves.md precedent supports PARTIAL for expand-void-return (func_80184FB0). And WALL for func_800D2A24 (same class). So both are valid outcomes.

Given "a WALL needs ≥20 min and ≥30 scored tries", PARTIAL doesn't have that requirement explicitly. So recording PARTIAL is cheaper and honest. But is PARTIAL the right label? PARTIAL:<kinds still kept> — we keep keepalive and pin (both). win.c = orig scores 0. Yes.

Hmm, but maybe I can do better for items 1-3: a PARTIAL that keeps only *some* levers? The kinds row is keepalive,pin. If win.c keeps only the keepalive and drops the pin (the $2 pin), does it still score 0? The keepalive alone marks rv used; without the pin, rv gets some register, but the target needs v0. Let's test: drop only the pin from item 1's orig (keep keepalive). That would give PARTIAL:keepalive. Let me test quickly — it might still be 0 if global-alloc naturally picks v0 (unlikely for a value used across blocks). Actually rv is set in multiple branches and used at the end; global-alloc would pick a caller-saved reg — v0 is caller-saved and might be chosen (it's the first in order). Let's test!

If dropping the pin keeps score 0, then PARTIAL:keepalive — better (fewer levers). Similarly, dropping the keepalive but keeping the pin? Probably score > 0 (dead).

Let me test for item 1: body with pin removed, keepalive kept.

Also for item 2 and 3.

This is a promising direction: maybe only the keepalive is truly needed, and the pin is redundant (like moves line 15: "pin redundant"). Then the result is PARTIAL:keepalive. But the brief's goal is lever-free... still PARTIAL.

Wait, but hold on! If only the keepalive is needed, then could we replace the keepalive with a *real C* use of rv? The keepalive's purpose is to mark rv live. A real C use would have to be observable... e.g., storing rv to a global — adds a store. Not matching.

Hmm, unless the real use is `return rv` (blocked).

OK let me test pin-dropped variants.

Actually, wait. Let me reconsider the whole thing ONE more time. What if the function's return type could stay `void` while we make the value live via a **`register` variable used in a `goto`-computed... no.

Let me look at whether the callers are really in the same TU for item 1 — yes. What if we declare the definition `s32` and *remove* the callers' conflicting declarations? That's a caller change — forbidden.

Alright, let me proceed with experiments.

First, test items 1-3 with pin dropped (keepalive kept).
