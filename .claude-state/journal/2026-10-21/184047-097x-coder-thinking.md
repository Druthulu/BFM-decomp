---
ts: 2026-10-22T00:40:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_bBQG6Z7ZUZpfHm4t7GBH
---
The target:
```
3924: lw a0,100(s0)      ; unk64
3928: jal func_80188E1C  ; func_8012BD14
392c: nop
3930: slti v0,v0,4097
3934: beqz v0,3958       ; if !(v0 <= 0x1000) goto 3958
3938: li v0,2            ; delay: v0 = 2
393c: lw v1,100(s0)      ; unk64 again
3940: jal func_80188E1C  ; func_80178BF8
3944: sh v0,2(v1)        ; delay: store v0 (=2) to unk64+2
3948: lui v0,0x0         ; v0 = func_80172710 (the function address)
394c: addiu v0,v0,0
3950: j 395c
3954: nop
3958: move v0,zero       ; v0 = 0
395c: epilogue
```

So the target materializes:
- in the "then" branch: v0 = &func_80172710 (lui+addiu) — that's the asm's constant input.
- in the "else" branch: v0 = 0 (move v0,zero).

So `ret` is a *return value* — but the function is `void`! The target's v0 at the end holds &func_80172710 or 0. The function is declared void, so v0 is just a leftover register.

So the lever forces the *constants* to be materialized in v0. Plain C: how? The function returns void; the value is discarded. GCC would remove the dead constant materialization.

Hmm! In plain C, if the source were:
```
ret = (s32)func_80172710;
return;
```
GCC would remove it (dead). So the asm is needed to *keep* the constant materialization.

How to keep a dead constant materialization in plain C? You can't — unless the value is *used* somewhere. But the target's v0 is not used (the function returns void)...

Hmm, wait: is it possible the original source was NOT void? The function is `void func_8018C730(s32 a0r)`. The original game asm returns v0 = something. Hmm, the original might have been a function returning a pointer (e.g. `s32 func_8018C730(s32)`) where the returned value is &func_80172710 or 0! But the constraint says "no signature or decl change outside the body" — the signature is fixed as void.

Hmm, so in plain C, how do we get "lui v0; addiu v0,v0" in the then-branch and "move v0,zero" in the else?

Option: make the function *return* the value — but the signature is void. Hmm, in C, `void f() { ... return expr; }` is an error ("return with a value in function returning void") — actually GCC 2.7.2 gives a warning, not an error? Hmm, in old GCC it's a warning ("return with a value, in function returning void") — the code would still compile! And the value would be materialized in v0. Hmm! But that's a signature/semantic change... The constraint says "no signature or decl change outside the body (callers stay as they are)" — a `return expr;` inside a void function is inside the body. It's a warning-level hack; would the build tolerate warnings? The TU is compiled with -Wall maybe -Werror? Risky.

Alternative: use the value in a way that produces the same instructions but is not dead. E.g.:

```
if (cond) {
    *(s16 *)(unk64 + 2) = 2;
    func_80178BF8();
    ret = (s32)func_80172710;
    return;
}
ret = 0;
```
GCC would remove `ret = ...` (dead) → no lui/addiu. Hmm.

Unless the value is *used* in a way that leaves v0 holding it: e.g. `ret = (s32)func_80172710;` and then... nothing. Dead.

Hmm, what if the *asm* is replaced by a real *call* whose result is discarded? no.

What about `ret = (s32)func_80172710;` and then a *use* of ret that has no code effect? Hmm, e.g. `if (ret == 0) {}`? That adds a compare.

Hmm! What about making the function *not* void in the body sense: the target's asm leaves the function address in v0 at the return. The only way to get that in C with a void signature is the asm.

Hmm, hold on: what about the "and the function is void" — maybe the *original* function was NOT void, and the decompiler changed the signature (which is a "no signature change" constraint → I can't change it back). Hmm, but the *caller* uses it as void. Hmm.

Wait — what if I make the *return value* used via a comma expression or a cast to void: `(void)((s32)func_80172710);` — GCC would fold it (the value is unused) → dead.

Hmm, what about assigning to a *global*? e.g. `D_something = (s32)func_80172710;` — that would add a store (not in the target).

Hmm, what about the *asm-free* way to keep a constant alive: the constant is used as a *function pointer* in a call! E.g. `((void (*)())(s32)func_80172710)();` — no, that adds a call.

OK, so what about: the *value* must be in v0 at the return point. Hmm.

Interesting thought: what if the source is:
```
ret = (s32)func_80172710;
return;
```
and GCC *does* keep it because... it's a *volatile* asm? no.

Hmm, what if the variable `ret` is a *global*? Then the store would be visible (adds instructions).

What about `ret` being declared as `volatile s32`? Then `ret = (s32)func_80172710;` → a store to the stack (a sw instruction) → the target has no such store. And volatile is a barrier lever.

Hmm. So this item is likely a WALL: the lever materializes a dead constant in v0.

Hmm, but hold on! What about the "call-site return-type cast" move from moves.md? "pin | func_80157BC8 | MATCH: both $2 result pins -> call-site return-type casts ((s32 (*)(s32))f)(a0); 140/141 0" — that's for pins, and it changes the *caller*, which is outside the body. Not allowed here ("no signature or decl change outside the body").

Hmm, but for THIS function: the caller calls func_8018C730(...) as void. If the function returned a value, the caller would ignore it. But we can't change the signature.

So: the target's v0 = &func_80172710 in the then-branch. In plain C with a void function, GCC won't materialize a dead constant.

Hmm, unless... the constant is materialized as part of a *different* expression that GCC keeps: e.g. `func_80178BF8();` — hmm, what if the source called the function *through* the pointer: `((void(*)())func_80172710)();`? That would emit a call (jalr) — the target has `jal func_80188E1C` (func_80178BF8) — hmm, and then the lui/addiu of func_80172710.

WAIT. Look at the target's then-branch:
```
393c: lw v1,100(s0)
3940: jal func_80188E1C      ; func_80178BF8()
3944: sh v0,2(v1)             ; delay slot
3948: lui v0,0x0              ; &func_80172710
394c: addiu v0,v0,0
3950: j 395c
```
Hmm, the `lui v0; addiu v0,v0` = loading the address of func_80172710 — as a *value*, not a call.

Hmm, so the original game code probably was:
```
void func_8018C730(s32 a0r) {
    ...
    if (cond) {
        *(s16 *)(unk64+2) = 2;
        func_80178BF8();
        ??? = func_80172710;   /* the address as a value */
        return;
    }
    ??? = 0;
}
```
Hmm, and the compiler kept the dead assignment because the *original* function returned a value (e.g. `s32 func_8018C730(...)`) — the return value is &func_80172710 or 0. So the original signature was probably NOT void!

And the decompiler made it void (because the caller ignores the result) — and then needed the asm to reproduce the register state.

So the crack would be: make the *body* return the value. In C, a void function can't return a value... but GCC 2.7.2 allows `return expr;` in a void function with a warning? Let me test! If GCC 2.7.2 accepts it (warning only) and generates the same code (materializing the value in v0), that would be a MATCH... but it's a *semantic* hack (the function still returns void per its declaration; the value in v0 is ignored by the caller).

Hmm, is that a "lever"? No lever — it's plain C. But it's a warning-generating construct. The build might use -Werror. Let me test if it compiles.

Actually hmm, in GCC 2.7.2, `return expr;` in a void function: "warning: return with a value, in function returning void". It compiles. And the RTL would materialize the value into v0 (the return register) → matching the target!

Hmm, but is that "cheating"? The constraint is "no signature or decl change outside the body (callers stay as they are)" — a `return expr;` inside the body doesn't change the signature. The callers stay as they are. The generated code matches the target exactly. I'd say it's a legitimate plain-C move (the "return type" trick), though it produces a warning. Hmm, the project might have -Werror in the build... but the score is computed by delever_search's own compile (which uses the project's flags). If it compiles with a warning, the score could be 0.

Hmm, but a warning in the shipped source is bad practice. Hmm. But wait: is it even *semantically* OK? The function is void; returning a value from a void function is undefined behavior in C (if the caller uses the value). The caller ignores it. The generated asm matches the target. Hmm, it's a "fake" but it matches the game's behavior exactly.

Hmm, this feels like it could be considered a "launder in disguise" — it's materializing a value for the register's sake. But it's a *return value*, which is a legitimate mechanism. And the target's asm literally returns that value in v0.

Hmm, hold on. Let me reconsider: maybe the *right* fix is to change the *declaration* of the function to return s32 — but that's "outside the body" (not allowed).

OK, let me test the `return expr;` variant. Let me write it:
```
void func_8018C730(s32 a0r)
{
    s32 base;
    s32 ret;

    base = (s32)a0r;
    if (func_8012BD14(((Unkstruct_8018C730 *)base)->unk64) <= 0x1000) {
        *(s16 *)(((Unkstruct_8018C730 *)base)->unk64 + 0x2) = 2;
        func_80178BF8();
        return (s32)func_80172710;
    }
    return 0;
}
```
Let me test this (it should produce lui/addiu + move v0,zero).

Let me try it after the background batch finishes (to avoid CPU contention). Actually, let me just run it now — the background job is using CPU but there's room.

Let me write the file and score it.
