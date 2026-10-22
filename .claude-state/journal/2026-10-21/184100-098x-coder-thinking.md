---
ts: 2026-10-22T00:41:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_6avPNMcwDydaxrQACpco
---
Still 18 ins — so GCC 2.7.2 *removed* the return value in a void function (as expected: the "return with a value in a void function" is treated as a plain return).

So that doesn't work. Hmm.

So the constant materialization requires the value to be *live* at the return. In a void function, the return value register v0 is dead → GCC removes it.

Hmm! But hold on: what if the *value* is used in the *other* branch? E.g.:
```
if (cond) {
    ...
    ret = (s32)func_80172710;
} else {
    ret = 0;
}
```
and then... the value is dead at the end. GCC removes both.

Hmm, but the target HAS them. So the target's compiler kept dead constant materializations. That happens with the asm.

Hmm, what if the *value* is used in a way that's *not* dead but produces no code? E.g. `ret = (s32)func_80172710;` then `if (ret) { }`? That adds a branch.

What if the value is passed to a function that GCC knows is a no-op? no.

Hmm, what if the "return" is done through a *pointer* to a function...

What if the source calls a function *through* the pointer: `((void (*)(void))func_80172710)();` → that emits `jalr` (a call) — the target has no such call. Hmm, but wait: what if the *call* is to func_80172710 and the *lui/addiu* is the address setup? The target's then-branch: `jal func_80188E1C` (that's func_80178BF8) then `lui v0; addiu v0,v0` (the address of func_80172710) then `j 395c` (the epilogue). So no jalr.

OK so the target materializes the address as a *value* in v0 and returns it. The only way in plain C: the function must *return* it. Since the signature is void, GCC drops it.

Hmm, what if the *body* declares a *nested* function? Not C89.

What if the *value* is stored to a *global* that the target also stores? The target has no such store.

Hmm, what if the value is assigned to a *volatile* global? Adds a store.

So: item 10 (func_8018C730) = WALL. The mechanism: the asm materializes a dead constant (the address of func_80172710 / 0) into v0 at the return; a void function's return value is dead, so plain C removes it (18 vs 23 ins).

Tag: new, e.g. `flow-unused-result` (exists in walls.txt!): "flow: flow deletes results the target computes but never uses (T10 S20, func_80188C04 family)". That's EXACTLY this mechanism! Great: tag = flow-unused-result.

And the fix would be a signature change (return type), which is not allowed.

OK. Now let me check the background batch results.
