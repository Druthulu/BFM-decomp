---
ts: 2026-11-06T09:56:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_btz6JfiMkHaqbb5D5mO2
---
The target has at 2ad4: `move v0,s0` right after `sw v0,0(s0)`, and then the epilogue. So the move v0,s0 is NOT in the return delay slot (delay slot is nop). It's just before epilogue.

This looks exactly like `return a0;` in a function that returns a value! The classic pattern: return a pointer → move v0,s0. But our function returns void.

Hmm. But wait — the target was presumably compiled from the original source which is `void`. Yet it has `move v0,s0`. That's weird for void. Unless the original C had something.

Hold on. The last statement is `rv = (s32)a0;` with rv pinned to $2 and kept alive. Without the pin/keepalive, dead code.

What real C yields `move v0,s0` (v0 = a0)? A value assigned to a variable that gets v0 and is used... but it's not used after. Unless it IS the return value: `return a0;` in a function whose return type is a pointer.

Hmm, but "no signature or decl change outside the body" — changing the return type of the function definition is a signature change. Forbidden.

Alternative: Can we produce a dead-but-kept assignment to a pseudo that lands in v0? Assignments to dead variables are deleted. But if the value is used... The instruction is `move v0,s0`, then epilogue. There's nothing after. So v0 is dead unless it's the return value.

Unless... the function's declared return type is void, and there's a `return;` — no move.

Hmm. Wait, maybe the src function's actual signature is different from what I think. Let me re-read: `void func_8017E8D8(s32 *a0, s32 a1, s32 a2)`. And callers: `func_8017E8D8(sp10, a0, a0 + 0x102);` ignoring result. And there's `extern void func_8017E8D8(...)`.

So the target compiled a `move v0,s0`. How did the original game's compiler produce it from a void function? Possibly the original function returned a value (e.g., `return a0;`) but the project declared it void for matching callers. But then the target bytes wouldn't match... yet they do match our src with the pin+keepalive hack. So the hack was needed precisely because the real source can't express it under void.

Hmm wait. Maybe there's another way: a `return` of a value in a void function? That's a warning/error in C. GCC 2.7.2 might allow `return a0;` in a void function with a warning? Actually in K&R/C89, returning a value from a void function is a constraint violation; gcc warns "`return' with a value, in function returning void". But does it still emit the move? Possibly yes, gcc emits the return value code then warns. Hmm, but would that change the signature? No, the function stays void.

But wait, we're not allowed to change signature/decl outside the body. Adding `return a0;` inside a void function is inside the body. That might be the trick! But is that "real C"? It's C, albeit a warning.

But hold on: the delever tool probably compiles with warnings not errors. Let me test: replace the last lines with `return a0;`? But `return a0;` where a0 is `s32 *` and function returns void. Hmm.

Actually wait, let me reconsider. Maybe there's a cleaner path: What if we don't need v0 at all because... no, we need the move.

Let me think about what C naturally emits `move v0,s0` where s0 holds a0:
1. `return a0;` (pointer return) — but void.
2. Assign a0 to a variable whose last use is... no.

Actually, there's another classic: the function's return type could be void, but the caller... no.

Hmm, but consider: maybe the src decl could be `void func_8017E8D8(...)` but the *definition* in the TU... it's the same.

Let's test `return a0;`. But that would be `return` with value in void. GCC 2.7.2: in `c-common`/`c-decl`, "return with a value, in function returning void" is a warning (pedwarn), and it does `expand_return`. Let me just test.

Actually, wait. Another possibility: `*(s32**)a0 = ...` no.

Let me test candidate: end with
```c
    func_8012B77C((s32)&sp20, a1 + 4, (s32)sp10);
    *a0 = sp20;
    return a0;
```
Hmm, `*a0 = sp20;` vs `rv = sp20; *a0 = rv;`. In orig, rv=sp20 then *a0=rv, compiled to `lw v0,32(sp); sw v0,0(s0)`. If I write `*a0 = sp20;` directly, combine may merge. Let me test.

Actually careful: `return a0;` in a void function may be a compile error in this build (if -Werror). Let's test.

Let me make candidate win.c v2.
