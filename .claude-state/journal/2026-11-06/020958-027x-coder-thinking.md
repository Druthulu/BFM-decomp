---
ts: 2026-11-06T09:09:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_65CNxtdQjq6qdKzqLYea
---
No compile error but score 19 — value dropped (49 ins).

So the found value must be used. What real-C constructs keep a computed value live until function end producing just `move v0,s2`?

Wait... reconsider. Target's `move v0,s2` is the keepalive's `rv = found` where rv is pinned to $2. The pin forces found into s2? No wait — pin makes rv a hard-reg pseudo $2. In target, found is in s2 (a callee-saved!) and then `move v0,s2` at end. So the pin is on rv=$2 and the assignment `rv = found` generates move v0,s2. found itself got s2. So actually the target's register allocation has found in s2 due to... the pin pseudo's interference.

Lever-free, can we get found in s2 and `move v0,s2`? Only if the value ends up in v0.

Hmm, what if we write the function to return void but the final statement is a call that takes found? No, target has no call at end.

What if the code is structured so found is the loop variable/condition? Let's look at the target more carefully: `move s2,zero` at start — found=0. `move s2,s0` at b48 — found=(s32)p. `move v0,s2` at end.

A real C function that returns void but must return the value... Hmm, actually maybe the original source had `return found;` and the function was declared returning something at file scope originally. The port added `extern void` because callers cast. In this task, we can't change decls.

Wait, re-read constraint: "no signature or decl change outside the body (callers stay as they are)". Could changing the definition's return type AND line 146's extern count as "signature change outside the body"? Yes, line 146 is outside the body. So no.

Hmm, is there any other way? What about making `found` used via a pointer to a local that escapes... 

Idea: use a local array and have found stored, then `buf[?]`... no, target has no extra insn.

Idea: `if (found) { }` produced? Let's see what GCC does with an empty if. Probably drops it entirely (flow). Test: `if (found != 0) { }` → dead code, removed, found dead. So no.

Idea: `while (0) { found; }` — no.

Idea: the real C move could be to restructure so `found` is the same variable as something used in the loop condition in a way that matches. E.g., the target loop condition at end is `p < end` only. If found were used, extra test.

Hmm, alternatively the target could be reproduced with a different structure where found's value naturally flows to v0 without a return. E.g., make the function body end with a call `func_800CD6A4`? no.

Wait wait. Let me reconsider: maybe the void-returning function can still produce `move v0,s2` if the last statement is a call returning... no.

What if we make the last expression a `return;` preceded by assigning to a `register s32 rv __asm__("$2")`? That's the pin, forbidden.

OK so maybe this item is a WALL: expand-void-return or a pin/keepalive wall. But before giving up, consider: what does the target actually need? Let's compare: my lever-free candidate is 49 ins vs 54 target. Differences:
1. target saves s2/s4, mine s2/s3 (one fewer callee-saved + one fewer frame word)
2. target has move s2,zero at start (found init kept)
3. target has move s2,s0 and move v0,s2.

If found is dead, it's all dropped.

Could we keep found alive by making it the value of a variable that's passed to a later call... there is no later call.

Hmm, what about making the function's last statement `func_8014C3A4(...)` inside... no.

Actually! Here's an idea: make `found` be read by the loop condition in a way that's a no-op at runtime but real C: `} while (found == 0 && p < D_801202A0 + 0x6480);`? That adds a test of found each iteration — extra insns, not matching.

What about `if (p < p + 0x6480)` outer if — target has that? Let's check target: after the sb, `sltu v0,s0,v1; beqz v0,b5c` — yes the outer if check exists (p < p+0x6480). Interesting: the target computes v1 = s0+25728, and checks sltu(s0, v1). Then inside loop it reuses s4 = v1. So the outer if's `p + 0x6480` and loop's end are common-subexpression'd.

In mine, same structure but s3 instead of s4 and no found.

So the only real difference is found liveness. Since signature change is forbidden, maybe the intended crack is different: perhaps declare `found` as a global? A file-scope variable used elsewhere? No, that'd change other functions.

Hmm — what about `*(s32 *)&...`? no.

Let me reconsider the constraint. "no signature or decl change outside the body (callers stay as they are)". If we change the definition to s32, we MUST also change the extern at line 146 (a decl outside the body). Forbidden.

Unless... we can avoid the conflict by keeping the definition `void` and declaring a second symbol? No.

What if the extern at 146 is `extern void func_800CD5CC(void *a0);` — what if the definition uses a different but compatible type, e.g. `func_800CD5CC()` (K&R, unspecified args, int return)? An old-style definition `func_800CD5CC(arg0) void *arg0; {...}` with implicit int return — that conflicts with void extern too.

Hmm, what about defining it as `void func_800CD5CC(void *arg0)` and adding a *nested* function? No.

OK. So this item likely ends as PARTIAL or WALL. But the brief says PARTIAL is allowed: "PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers)". So we could keep the pin (a row kind) and drop the keepalive? Let's see: with pin but no keepalive: `register s32 rv __asm__("$2"); ... rv = found;` — the pin alone might score 0 (the keepalive may be redundant). Then result PARTIAL:pin. That's a valid row but the goal is MATCH.

But wait: maybe there's a real-C move: make `found` live by returning it through a *pointer*: `s32 found` local, then at the end `if (found) *(u8*)0 = ...` no.

Hmm, think about what the compiler sees. To keep found live and produce exactly `move v0,s2` at the end with no other insn, the only source construct is `return found;` in a non-void function. Since we can't change the signature...

Hold on. What if the return type is changed only in the definition and the extern at line 146 is inside a *function* body (a block-scope extern)? Line 146 is at file scope (after #include at 141). Block-scope extern declarations also conflict. Same thing.

Hmm, but what about the extern at 146 being *before* the definition — GCC errors "conflicting types for func_800CD5CC". Yes.

Let me test whether GCC 2.7.2 actually errors or just warns... The sc.sh said COMPILE-ERROR "conflicting types". So yes.

Alternative: Could we make the definition not conflict by matching the void return but using an *asm label* alias to a different symbol? No.

OK so let me now consider: is there a genuinely different body shape that yields score 0 with no levers? For example, if the function is restructured so found's liveness is inherent: e.g., instead of `found`, write the loop as a function returning the pointer through the loop itself? Hmm.

Think: `found = (s32)p` then after loop `rv = found`. What if we write:

```c
u8 *found = 0;
...
found = p;
...
if (found) ... 
```

Any use adds insns.

What if the last statement is `func_800CD6A4(a0, found);`? Not in target.

So MATCH seems impossible without signature change → WALL. But wait, the brief says budget 20-30 min per item and "a WALL needs ≥20 min and ≥30 scored tries". That's a lot. But before that, maybe check moves.md for prior walls on this exact function — grep for func_800CD5CC.
