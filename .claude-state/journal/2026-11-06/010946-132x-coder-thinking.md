---
ts: 2026-11-06T08:09:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vKYiodIa8HsPfQ8yxft3
---
Look at the callers! Lines 157, 215, 254: `if (((s32 (*)(void *))func_800CD494)(arg0) != 0) {` — the callers cast the function to `s32 (*)(void *)` and test the return value! So func_800CD494 DOES return a value (s32) — the callers use it. The declaration `extern void func_800CD494(void *a0);` at line 145/196/237 is the FAKE/lever (declared void but called through a cast to get the return). 

So the natural C: `s32 func_800CD494(void *a0) { ... return rv; }`. But the brief says "no signature or decl change outside the body (callers stay as they are)". Changing the function's return type from void to s32 IS a signature change outside the body. Hmm. But the callers already cast to s32(*), so changing the definition's return type would... The definition is in the same TU (line 408). The callers have `extern void func_800CD494(void *a0);` declarations (local, inside their bodies?) and cast. If we change the definition to s32, the extern decls (void) would conflict? The extern decls are inside other functions (local block scope), and the definition is at line 408 after them. GCC 2.7 might complain about conflicting types.

Wait, the local externs at 145/196/237 declare `void func_800CD494(void*)`, then cast to `s32(*)(void*)`. If the definition later is `s32 func_800CD494(void*)`, the local declarations (void) conflict with the definition's type. In GCC 2.7, a block-scope declaration then a file-scope definition with a different type → error.

So changing the signature breaks the TU. That's why the banked source declares it void and uses the keepalive. The lever-free MATCH may require a signature change, which the brief forbids. So item4 is likely a WALL — specifically the "expand-void-return" wall tag: "void def (caller TU K&R void decl); target li v0,0/1 on exits; expand drops void return values". That's in walls.txt! `expand-void-return` from moves.md line 19 and 40.

The moves.md line: "keepalive,pin | func_800D2A24 | WALL expand-void-return — void def (caller TU K&R void decl); target li v0,0/1 on exits; expand drops void return values (W03)". And "keepalive,pin | func_80184FB0 | PARTIAL:keepalive,pin expand-void-return — void fn, target returns call ptr in v0 (else move v0,zero); u8 c = a1 dropped $16/$3 pins; win.c keeps $2 pin+keepalive".

Our case: the function is declared void but the callers use the return value via a cast. The target has `move v0,zero` and `li v0,1`. So the natural function returns rv.

Can we express the return without changing the signature? What if we keep the void signature but add a real use of rv that produces `move v0,zero`/`li v0,1`? E.g., assign to a global? No, that'd be a store.

What if we use `return;` but the compiler still sets v0? No.

Hmm, the brief says no signature change. So item4 is a WALL with the known tag `expand-void-return`. Best lever-free = 3.

But wait — the constraint says "no signature or decl change outside the body (callers stay as they are)". The function's definition signature is the body's first line — is it "outside the body"? The body is the function definition; the signature is part of it. "no signature or decl change outside the body" — arguably the signature of THIS function is inside its definition, but the callers' decls are outside. Changing the definition's return type would conflict with the callers' `extern void` decls (outside the body). So no.

Could we change the function to return rv WITHOUT changing the declared type, using a cast trick inside? E.g., `return;` won't. Or use a `register s32 rv __asm__("$2")` pin? That's a lever (forbidden).

What if the source uses `rv` in a real way that the compiler must materialize: e.g., the if/else assigns rv and then `if (rv) ...`? That would add a branch.

The target's structure: 
```
if (unk246 == 0) {
    func(...); func(...);
    li v0,1
} else {
    move v0,zero  (in delay slot)
}
```
So rv=1 in the if branch, rv=0 in the else, and the values are in v0. For a void function, this is a dead computation that flow would remove. The target keeps it because the function actually returns it.

So the natural C is `s32 func_800CD494(...) { ... return rv; }`. The callers cast to s32(*). But the callers also have `extern void func_800CD494(void*)` local decls. If we change the definition to s32, the local decls conflict.

Let me test whether changing the definition's return type to s32 compiles and scores 0. If it does, is it allowed? The brief explicitly forbids signature changes. But maybe the callers' decls are the lever (fake) and the brief's "callers stay as they are" means don't touch the call sites. Changing the DEFINITION's return type is a signature change of the function, which is arguably "the body". Hmm, risky. The constraint: "no signature or decl change outside the body (callers stay as they are)". The definition's signature is not "outside the body" in the sense that it's the function we're editing; but it IS a signature change. The intent is likely: don't change the function's signature because it would affect callers. Here the callers already expect s32 (they cast). So changing the definition to s32 makes the callers' casts redundant but correct.

However, the local extern decls `extern void func_800CD494(void*)` would conflict. Let me test if it even compiles. If it compiles and scores 0, I'd have to decide. The safer interpretation: WALL expand-void-return (known wall). The moves.md has WALL entries for exactly this. Given the brief's explicit constraint, I'll treat signature change as forbidden and mark WALL.

But let me at least test whether the s32 definition compiles (to document it) — actually, testing it is fine (scratch). Let me test a candidate with `s32 func_800CD494(void *a0)` and `return rv;` plus removing the keepalive. If it scores 0, I'll note that the only close is a signature change (forbidden) → WALL.

Let me test.
