---
ts: 2026-11-06T09:09:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_W2mC2C3vg6ShsOYDm7Mh
---
Conflicting types, as expected. So s32 return is not available without touching line 146.

Alternative: keep void signature but make `found` genuinely live through a real C use. Options that produce no extra instruction at the end:

- `if (found == 0) return;` → test + branch.
- Make found the loop bound? no.

What about making `found` a `s16 buf[4]` element? No.

Hmm — think differently. The target's code: found in s2, initialized to zero at the very start (`move s2,zero` at entry). If instead the value were used in a real way that produces exactly `move v0,s2` at the end... only return does.

Wait, maybe the function's void return could be `return (void)found;`? No, that's a cast to void — drops it.

What about `return found;` in a void function? GCC error: "return with a value, in function returning void" — warning? In C89 it's an error? GCC 2.7.2: warning by default ("return with a value, in function returning void"), and codegen: does it emit the move v0,s2? It might! Let's test: `void f(){ ...; return found; }` — GCC 2.7.2 warns but compiles. Codegen may still emit the return value move since the value is computed. Actually in the tree, `return_expr` for void function... GCC's expand_return for void may ignore the value. Let me test.

Actually, a cleaner real-C trick: make the function return int implicitly? No.

Another idea: use the value in a call that the compiler cannot remove but which the target also has? No.

Alternatively, change the TU declaration... forbidden. But wait — is line 146's extern a "decl outside the body"? The brief says no signature or decl change outside the body (callers stay as they are). So no.

Hmm, but the moves.md line 43 shows a MATCH that changed call sites (`call-site return-type casts`) — but that was a different task's constraints.

Let me test the `return found;` in a void function.
