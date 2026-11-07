---
ts: 2026-11-06T09:58:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4Vz77UEf8BzsaCpuk2AN
---
Confirmed: `extern void func_8017E8D8(s32 *a0, s32 a1, s32 a2);` appears twice at file scope before the definition. So the definition must be void to compile.

So how to get `move v0,s0` in a void function...

Hmm, hold on. Let me reconsider. The target's `move v0,s0` — maybe it's not from a return at all. In GCC, a void function can still set v0 if the source contains a call whose return value is used in a `?:` or an expression where the value lands in v0 and is then... no, must be used.

WAIT. What about the function *signature*? The target was compiled from the ORIGINAL source which may have had `s32 func_8017E8D8(...)`. But our TU's extern decls (void) are our own reconstruction. The target bytes don't care about our decls. So the original returned a value. The project's constraint is that our src decls are void. So we literally cannot produce the target bytes with void... unless the bank compares only the function's instructions, and the *definition* could return a value if the extern decls were compatible. They aren't.

Hmm, but actually: does the tool compare only the function's instructions (not the whole object)? The score line says "the bank judges the whole object" — score 0 = whole object identical. But --try compares "the function's instructions". dt.sh shows score. For MATCH we need score 0 which is whole-object.

OK so what if we could make the extern declarations compatible by... we can't touch them.

So this looks like a genuine WALL: `void-return-value` or similar. But the task requires ≥30 scored tries and 20 min. Let me not give up yet; think of C constructs.

Idea: `goto`-based epilogue where the return value... no.

Idea: What if the function's return type is void but we call `func_8017E8D8` recursively? no.

Idea: What if the last statement is `*(s32 *)a0 = sp20;` and then `a0 = a0;`? dead.

Idea: The `move v0,s0` could be produced if we assign a0 to a variable and then *pass it as the return value via a nested function*? no.

Idea: `return (void)a0;`? void cast → expand_expr with NULL target, no move.

Hmm, what about making the compiler believe the function returns a value by using `#pragma`? no.

What about declaring a local `s32 (*fp)(s32*)` and calling `fp(a0)` — the call sets v0 from the call, not from a0.

What if we use `__builtin_apply`? no.

OK here's a thought: the move v0,s0 might come from a *conditional expression as the last statement*: e.g. `x ? a0 : a0;`? dead.

What about `return;` inside `if (0) { return a0; }`? void → ignored.

Hmm.

Let me look at whether the original function might return a value through an *unused* result where gcc still emits the move because it's a "return value" register. In gcc 2.7.2, for a void function, `expand_null_return` → `expand_null_return_1` which emits a `return`. No v0.

Alternatively, maybe the target `move v0,s0` comes from the source having `a0 = ...` no.

Let me question the assumption that s0==a0 at that point. `move s0,a0` at 2a3c is in the bnez delay slot. But if `*q == 0` branch: after the bnez (not taken), s0=a0. Yes.

Hmm, what if there's a `set` of a pseudo to a0 that gcc keeps because it's used as the return of a *tail call*? no.

New angle: maybe the function could be written to have the same instructions with a *different* final move: instead of `move v0,s0`, what if the target's v0 at that point... it's exactly move v0,s0, no alternative.

Could we produce `move v0,s0` via an assignment to a variable that's in v0 and then is "used" by the epilogue? The epilogue uses ra, s0, sp. Not v0.

Unless... the value in v0 is live-out because the function is declared to return something? For a void function, no.

Hmm, let me check: is there any chance the delever tool considers the function's declared type from the TU (void)? Yes.

OK, let me consider the possibility that the intended solution IS to change the return type in the definition and the extern decls are only two, both in the same file... The brief says "no signature or decl change outside the body". Changing the extern decls would be outside the body → forbidden. So no.

Hmm, but wait: what if the definition's return type is `void` and we add a *local* function pointer typedef... no.

Let me look at this from the "what did the original source look like" angle by checking the sibling main TU (ov_SC02_035_jr_8017BEBC.c mentioned in the comment) — maybe it has the same function with a real return. Actually the comment says declarations were conformed to ov_SC02_035. Let me check if func_8017E8D8 exists elsewhere with a non-void return.

Actually — this is an overlay "jr" TU: functions are duplicated across overlays. Let me search src for func_8017E8D8 definitions.
