---
ts: 2026-11-06T21:15:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7ImxGbmmOMbXjZP1hGpY
---
Item 2 win.c has no asm/keepalive/register. Good (lever-free, score 1).

Time: item 2 started around 14:08 (after item1 at 14:08). Now 14:15 — only 7 minutes! The WALL requires ≥20 min. Hmm. I need to spend at least 20 min on this item before declaring a wall. Let me continue searching more seriously. The brief: "past 30 min stop and record a wall; a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)."

I have 34 tries but only ~7 min. I need ≥20 min. So I should keep working on item 2 for at least another ~13 min. Let me use the time productively: try more creative real-C ideas, maybe examine the GCC expand/flow source for a loophole.

Let me think about the loophole. The dead set is `rv = (s32)a0` where rv is a pseudo. flow deletes it because rv is dead. To keep it, rv must be live at the end. In a void function, only callee-saved regs are live-out (for restore). 

Idea: what if rv is assigned to a *callee-saved* register variable? No, the target wants v0 ($2). But if rv were live at exit and allocated to a callee-saved reg, the move would be to that reg, not v0. Target is v0.

The only reason it's v0 is the $2 pin. So even if we make rv live, without the pin it'd go elsewhere. So MATCH requires the pin. Hence impossible.

BUT — what if we make the value live via a *return* and the function's return type is void? expand ignores. What if we trick expand by using a nested block with `return` and a *cast*? No.

What if we define the function as `void` but the return statement is `return (void *)a0;`? Still a value in a void function → ignored.

Hmm, what about `return *a0 = (s32)a0;`? The store's value... in void, ignored but the store happens: `*a0 = a0` (stores a0 to *a0). Target stores sp20. No.

What if the C is `return *a0 = sp20, (s32)a0;`? Comma in a void return. Ignored.

OK here's a different thought: maybe the target's move v0,s0 is not from a dead assignment but from the *call setup* for a function that returns void but the compiler places a0's value in v0 for... no.

Let me look at the GCC expand code for void returns. Maybe there's a construct like `return (s32)a0;` in a K&R function without a prototype — GCC 2.7.2 might not know the function is void at the point of the return if the extern decl comes AFTER the definition. Wait — the extern void decls: where are they relative to the definition? Earlier grep showed:
- 3454: extern void func_8017F0D0(...)
- 3603: extern void ...
- 3636: extern void ...
- 3803: definition

So the extern void decls come BEFORE the definition. If the definition is parsed after, the return type is void. What if we move the definition BEFORE all extern void decls? We can't reorder the TU (no edits outside the body). But the body is spliced into the TU at its location. The extern decls at 3454/3603/3636 are before 3803. So the definition always sees the void decl.

Hmm, but what if the *definition* itself has a return type that GCC uses for expand? The definition is `void func_8017F0D0(...)`. So void.

Could we define the function with a *different* type that's compatible with the extern void? No.

What if we add a *local* declaration inside the body? E.g., `extern s32 func_8017F0D0();` inside the body? That would conflict with the outer void decl (same identifier). Error.

OK. Another angle: maybe the target's move is not dead but is the return value of a *different* function. Let me re-examine the target bytes: `02001021 move v0,s0`. In the source TU, the function is void. But what if the C's last statement is a call to `func_8012B77C` that returns a value stored... no.

Let me try: `rv = func_8012B77C(...); *a0 = sp20;` — then rv = call return (v0), and the move v0,s0 wouldn't appear.

What if `func_8012B77C` returns s32 and the C does `rv = sp20; *a0 = rv; rv = func_8012B77C(...)`? No.

I'm confident it's a wall. To satisfy the 20-min requirement, let me spend the time examining more and trying more variants (maybe restructurings, not just tails). Let me also check the possibility of using a `union` or `struct` copy that produces a move.

Idea: `struct { s32 v; } s; s.v = sp20; *a0 = s.v; s.v = (s32)a0;` — extra.

Idea: The store `*a0 = rv` and then `rv = a0`; what if `rv` is used by the *next* function in the TU? No, functions are separate.

Idea: Make `rv` a global? no.

Idea: Use `setjmp`? no.

Let me try a few "restructuring" variants where the whole body is reorganized:
R1: compute p into a temp, store sp20 first, etc.
R2: use `s32 *ap = a0;` and `*ap = ...`.
R3: return the store value.

Actually, maybe the answer is a *different* mechanism entirely: the target's `move v0,s0` might be produced if the function's last statement is a call to a function whose argument is a0, and the call is to `func_8012B77C`... no.

Hmm, let me look at the actual sibling function in the TU that has a similar "return a0" pattern and is MATCHed. The comment says "Family of 10". Let me find other functions in the TU ending with a move v0,s0. Let me grep the TU for `(s32)a0` patterns.

Actually, let me look at the family in moves.md: search for "func_8017F0D0" — none. Search for "expand-void-return" MATCH — none.

Given the constraints (void signature locked), this is a documented wall family. I'll use the remaining time to run a few more real-C attempts (restructurings) and then record the wall at ≥20 min.

Let me check the time budget: item2 start ~14:08. Need until ~14:28. That's 13 more minutes. That's a lot of idle-ish work. Let me be productive: try 10 more variants (restructurings), examine the GCC expand source for a loophole, and prepare the notes.

Let me look at expand_return in stmt.c to confirm void behavior and look for any GNU extension.
