---
ts: 2026-11-06T09:56:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Rgqkjl4uKdV5UHJOU3XY
---
The target function returns a value in v0 and jr ra. So the source must produce v0 values. But declared void. With plain C, if rv is dead, flow deletes all the rv assignments, leaving only the branches. So we need a way for rv to be live.

Key insight: The function returns via `jr ra` with v0 computed. In C, a void function whose last statement computes into a variable that's dead will be eliminated. But if the function has a `return` statement with a value... that's an error in void function (warning, but GCC might allow? In C, `return expr;` in a void function is a constraint violation; GCC 2.7.2 gives a warning and... maybe discards). Hmm.

Alternative: make the function's return type implicit? No.

What about using a real C construct that makes the value observable: e.g., passing it to another function? That changes codegen (adds a call).

Hmm — maybe the target source actually wasn't void. But callers declare extern void. In C, calling an unprototyped function returning s32 and ignoring the result is fine. The definition in the TU could be s32 while callers declare void? In the same TU, there's `extern void func_8017F1F0(s32 arg0, s32 arg1);` after the definition. Conflicting types would be an error/warning.

Wait — is the definition in a different TU than the callers? The callers are in the same file (lines 5460+). GCC 2.7.2 with old-style... it would warn "conflicting types".

But hold on: the pin/keepalive approach is precisely the "fake" way to keep the value. The task says to remove the levers and find real C that produces the same code. Maybe the answer is that rv must be live because it's stored... Hmm.

Actually, wait. Let me reconsider: does `rv` need to be live? flow deletes dead sets. The `goto done` jumps to a label; flow sees rv assigned in several branches and never used → deletes the assignments, and the `goto done` becomes... The branches would still exist if they have side effects? `if (a0 >= x) { rv = -1; goto done; }` → without rv, becomes `if (a0 >= x) goto done;`. So the branch structure remains; only v0 sets vanish.

So to keep v0 sets, rv must be live at function exit. In a void function, a live variable at exit... only via asm or return. Unless the function has a `return rv;` — that's the sig change.

Hmm, but maybe the target is what the *original* binary has, and the matching source uses something. Let me check other similar cases in moves.md: line 28 `keepalive | func_80184D28 | MATCH — keepalive replaced by return v0; (s32 fn returned nothing; flow kept v0 sets only via asm use)`. That means the function was declared s32 (not void) and `return rv;` — but here it's void. Wait "s32 fn returned nothing" = the function is declared s32 and the original returned nothing. So they changed the return type. That would be a signature change, which the brief forbids ("no signature or decl change outside the body").

Hmm, but is changing the return type from void to s32 "outside the body"? The function definition's first line is not the body. The brief says no signature or decl change outside the body (callers stay as they are). So changing void→s32 changes the definition's type but not callers (callers stay as they are). Ambiguous. "callers stay as they are" suggests callers aren't edited; the definition's return type change might be allowed? But "no signature ... change" seems explicit.

Wait, but maybe there's another route. Let me look at what the original source (before levers were added) was — maybe git history has it. Let me check git log for this function/file.

Actually, the pin/keepalive were added to make a "fake" match; the real answer is a lever-free body. The target was likely compiled from the original game source which had... hmm, the function returns a value in v0. Actually maybe the real source had a *global* variable or the function had a different structure.

Let me think differently: maybe the value in v0 is not a "return value" but the result of an expression that flow can't eliminate because it's stored somewhere. E.g.:

done:
    D_801EEAEC[0] = rv;   // no, target doesn't store.

The target's v0 sets: `li v0,-1`, `sll v0,a0,1`, `li v0,31`. And jr ra. No store. So v0 is the return value register. In a void function, GCC doesn't care about v0.

So the only real-C way: the function returns a value. Since callers are `extern void`, and the TU compiles with old GCC 2.7.2... Let's test whether GCC 2.7.2 accepts `s32 func(...)` definition followed by `extern void func(...)` declaration and calls. It would give "conflicting types for `func_8017F1F0`" warning? In K&R-era GCC, conflicting declarations produce an error? Actually GCC 2.x: "warning: conflicting types for ...". With -Werror? The build uses the project's flags. Risky.

Alternatively, maybe the original source used a return value and the *current src* declaration was made void by the decomp author. The brief says callers stay as they are. Changing the definition to return s32 while callers keep `extern void` declarations → conflict within the TU.

Hmm, wait: are the callers in the same TU? Line 5460 is within the same file. Yes.

Let me check if there's a header declaring it. `extern void func_8017F1F0(s32 arg0, s32 arg1);` inside a function? Lines 5460, 5470... each call site has its own extern declaration, probably inside functions.

Let me look at the context.
