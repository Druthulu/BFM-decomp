---
ts: 2026-11-06T09:57:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_imQ3clndnzElKbgfUTQM
---
The target keeps `rv` in v0 and returns it (jr ra with v0 set). The function's target returns a value in v0. So the real function returns s32. But the source declares `void`. The pin `register s32 rv __asm__("$2")` plus keepalive fakes that.

How to get a lever-free body that returns v0? The declaration is `void func_80182420(a0, a1)`. Changing signature is forbidden ("no signature or decl change outside the body"). Hmm. But wait — maybe we can make the body return a value? In K&R C, the definition `void func_80182420(a0,a1) s32 a0; s32 a1; { ... }` declares void return. We cannot change that.

Options within the body:
1. Add `return;` at the end — doesn't set v0.
2. Use a value that's "used" in a way that forces it into v0 at the end. The target's last instructions: `li v0,31; jr ra` / and in the `d<16` case `sll v0,a0,0x1; ... jr ra`. So v0 = rv at the end.

Hmm, what if the function body's last expression is a call whose return is in v0? No.

Wait — maybe we CAN change the return type as part of the body? The brief says "no signature or decl change outside the body (callers stay as they are)". Changing `void` to `s32` in the definition is a decl change outside the body (the header line). That's forbidden.

But there's a trick: the keepalive asm is a lever. Without it, rv dead. Could we use `return` with the function declared... no.

Hmm, but the task says MATCH = score 0 with the kinds gone. If impossible lever-free, then WALL/PARTIAL. But the brief expects we try.

Wait — maybe the trick is that the callers cast the function pointer and use the return value. But the definition's return type determines codegen. If the definition is `void`, gcc doesn't keep the return value.

Unless... the body contains a `return;` in a function that... no.

Let me reconsider: perhaps there's a C construct that forces a value into v0 at function exit without asm. E.g., a tail call? If the function ended with `return func(...)` it'd be a tail jump, not matching.

Hmm, what about declaring rv as `s32` and adding `if (rv) {}`? No, still dead.

What about making the function `s32`-returning via a nested declaration inside the body? Like:
```c
{
    extern s32 func_80182420();  // wrong
}
```
No, that changes the function's type? A declaration inside its own body of the same name would conflict.

Alternative: gcc 2.7.2 with a void function — does it keep computations whose results are stored to a local that's then... The target has v0 as the destination. If we write `s32 rv; ...; rv = 31;` dead → deleted.

But what if rv is used in a way that forces it to be live at the return? For instance, a `return` statement in a void function with a value is an error in C89? GCC gives warning "return with a value, in function returning void". In gcc 2.7.2, `return rv;` in a void function is a warning, and it DOES generate the return of rv! Let me check. GCC: "warning: `return' with a value, in function returning void". And codegen: it emits the value. That would be a real-C-ish spelling but it's a warning, not a lever. Hmm, but does the decomp project allow warnings? The build uses -W? Probably compiles with warnings but not -Werror.

Actually wait: with `return rv;` in void function, gcc sets v0=rv and returns. That matches the target's structure! And it's not a lever (no asm/register). But is `return <value>` in a void function acceptable? The brief says lever-free = no pin/launder/barrier/keepalive. A `return rv;` in void is a source-level oddity but real C (K&R allowed it; it's a constraint violation warning in C89). Hmm, risky but could work.

But wait: `goto done; ... done: __asm__...` — the gotos all jump to done, then function ends. If instead we write `return rv;` at done and also the early exits `return -1;`... but then the tail. Let's think.

Actually maybe simpler: use `return rv;` at the `done:` label:
```c
done:
    return rv;
```
In a void function, gcc 2.7.2 emits `move v0,rv`? But then the target has v0 = rv directly, no move, because rv was pinned to v0. Lever-free rv would be allocated some register, then `move v0,<reg>` adds an instruction → mismatch (26 vs 27).

Hmm. Unless the value naturally lands in v0 because it's the return value. With `return rv;` in a void function, expand_return sets v0 = rv... Actually gcc might just treat it as the return value and allocate rv into v0? Return value register assignment: the return value is forced into $2 (hard reg). If the function "returns" rv, then gcc's expand for `return rv` in a void function... Let me test.

Actually, let's just test candidates. It's cheap. Let me write nopin.c variants and score.

Variant A (nopin, dead rv):
```c
void func_80182420(a0, a1)
s32 a0;
s32 a1;
{
    extern s32 D_801E1BCC[];
    s32 rv;
    s32 x = D_801E1BCC[0];
    s32 y = a1;
    s32 d;
    ...
done:
}
```
Score? Probably ~10.

Variant B (return rv at done):
```c
done:
    return rv;
```
Let me test both.

Actually wait. Maybe there's a smarter approach: `s32 rv` and the target's `rv` values are in v0. Since the function is void, but the target keeps them, maybe the original C returned them and the TU's `void` is a "wrong" decl that the project keeps because callers are cast. The lever (pin) was needed exactly because the void return type drops it. So a lever-free match may be impossible → WALL expand-void-return. That's a known wall tag (many entries). But let's try `return rv;`.

Hmm, but if `return rv;` works, it changes control flow: the target uses `goto done` then `jr ra`. With `return rv;` at done, same. And early exits currently `rv=-1; goto done;` then `return rv` → gcc may optimize to `return -1` directly, merging. Actually the target has `j 93c; li v0,-1` (the j is to the shared return, v0=-1 in delay). So there is a shared return block at 93c. If we write `return -1;` in each branch, gcc might create separate returns or merge. The current structure with `rv=-1; goto done;` gives the shared exit. With `return rv;`, `rv=-1` then `return rv` → gcc's flow may simplify to `return -1`, still jumping to shared epilogue? Let's just test.

Let me create nopin.c with rv plain and `return rv;` at done, and test. But careful: `return rv;` in void function — the compiler may warn. Let's see if the scorer accepts compile warnings.

Let me write it.

Actually, another thought: maybe write the function body to compute rv and then use it as the argument to a `return` — but the function is void. GCC 2.7.2: `return` with expression in void function. Let me check the gcc source? Not needed; test.

Let me write variant B.
