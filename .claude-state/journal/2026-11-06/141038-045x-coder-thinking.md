---
ts: 2026-11-06T21:10:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ja9yOHI5Fwu8KqKD0DU3
---
Still missing the move. So `return (s32)a0;` in a void function was ignored (GCC dropped the value) or the return expr was discarded. Let me check the actual asm of w3. Let me dump it. Actually let me check if it compiled at all — score 1 means it compiled (else COMPILE-ERROR). So `return (s32)a0;` compiled but the value was dropped by expand (void function ignores the return value).

Hmm. So GCC 2.7.2's expand_return for a void function ignores the value. That's the "expand-void-return" wall.

But maybe there's a way: assign to the return-value register directly? No.

What if we use a nested function or a `__builtin_return`? No.

Let me reconsider. The target's move v0,s0 could come from something else. Let me look at the full target again:

```
329c: lw v0,32(sp)      # rv = sp20
32a0: nop
32a4: sw v0,0(s0)       # *a0 = rv
32a8: move v0,s0        # ??? 
32ac: lw ra,44(sp)
32b0: lw s0,40(sp)
32b4: addiu sp,sp,48
32b8: jr ra
32bc: nop
```

The `move v0,s0` is right after the store. It could be:
(a) rv = (s32)a0 (dead) — the pin's purpose.
(b) The return of a value that the caller ignores — but void.
(c) A setup for something? No.

Since it's dead, flow would remove it unless it's kept. With the keepalive asm it's kept. Without, flow deletes.

Is there a real C construct where a value is computed and "used" in a way that flow considers live but emits no code? 

What about an `if` whose condition uses the value and whose body is empty, where the condition is not provably constant? E.g.:
```
if ((s32)a0) { }
```
That would emit a branch (bne) — extra insns, not target.

What about using the value as a function argument to a call that doesn't happen? No.

What about `rv` being used in the address computation of the store? E.g., `*(s32 *)((s32)rv + 0) = sp20;`? That's identity address (launder) and would change the base to v0 not s0.

What about making the store's value be rv AND rv used as the base: `*a0 = rv;` where rv=sp20... 

Hmm, what if we reorder to make the move not dead by making it the *store's* value or base? Target: store value v0 = sp20; base s0 = a0. The move v0,s0 after the store overwrites v0 with a0. If C were `*a0 = sp20;` then `a0` is used as base (s0), and the move is separate.

What if the C is: `*a0 = rv;` where rv is a pointer? no.

Let me look at this from the "expand-void-return" wall: it says expand drops void return values. The only way is to make the function non-void, which conflicts with the extern void decls. So WALL.

But wait — is the extern void decl in the same TU? Yes, at file scope 3x. Could we make the definition's return type a *different* type that's compatible with void? No.

What about a K&R-style definition? `func_8017F0D0(a0, a1, a2) s32 *a0; ...`? No, still conflicts.

Hmm, what if we don't change the signature but use a *macro* or an `asm` label to define the function with a different name? No.

Let me consider: maybe the move can be produced by a real use in the *call* to func_8012B77C. The target:
```
327c: lhu v0,4(a0)      # p[2]
3280: addiu a0,sp,32    # &sp20
3284: addiu a1,a1,4     # a1+4
3288: lhu v1,4(a2)
328c: addiu a2,sp,16    # sp10
3290: addu v0,v0,v1
3294: jal func_8012B77C
3298: sh v0,26(sp)      # sp10[?]=...
```
Note a0 = sp+32 (sp20) is set for the call. After the call, sp20 has the result. Then `lw v0,32(sp)` loads it. And `move v0,s0` at the end.

Hmm, what if the C passes `a0` to a subsequent call? No.

Let me look at the wall list for a matching tag. `expand-void-return` seems right. But before declaring a WALL, the brief requires ≥20 min and ≥30 scored tries. That's a lot. Let me first try more variants.

Actually, maybe there's a trick: the pin $2 alone (without keepalive) — does the pin keep the value live? In w1 (pin kept, keepalive removed), score 1 (move deleted). So the pin alone doesn't keep it; the asm did. Because `rv = (s32)a0` with rv pinned $2: the set is dead, flow deletes it regardless of the pin.

Hmm, but the src comment says "The pin is load-bearing twice: pinning the POST-CALL temp to $v0 is what stops sched2 hoisting the return copy into the load-delay slot". So the pin affects scheduling even if the move is kept by the asm.

So both are needed. To crack, we need to keep the move with real C.

Idea: What if the last statement is a *second* store that uses rv as a value, and the store is to a location that's... no, target has only one store after the call.

Idea: What if `rv` is used as the argument to `func_8012B77C`? No, that call is before.

Idea: What if we make the function's last statement `return;` but preceded by a store to `*(s32*)a0`... 

Idea: Use `__builtin_return_address`? no.

Idea: The value a0 could be used in a `?:` expression whose result is discarded but not provably dead? Flow would still delete.

Hmm, let me think about what flow keeps. flow (dead code elimination) keeps a set if the register is live-out of the basic block. At the end of the function (before epilogue), the only live regs are the return reg (if non-void) and callee-saved. For void, v0 isn't live. 

What if v0 is live because a subsequent (unreachable) block uses it? E.g., add an unreachable `label:` that uses v0, but no code. Hmm, unreachable code is deleted by jump/flow.

What if we make the function's exit path go through a block that uses v0? Like a loop? No.

OK, what about a completely different structure: the target's `move v0,s0` might come from `*a0 = rv;` where the store's value register is v0 and then v0 is reused as the base for... no.

Let me look at whether the "nop" after lw v0,32(sp) is a load-delay. `lw v0,32(sp); nop; sw v0,0(s0)`. The nop is because sw uses v0 (load delay). Then move v0,s0. If the move were removed, the nop might also disappear? In w1/w2 the diff shows only the move missing, so the nop stays (it's the load-delay filler for the sw).

Let me try a few more real-C variants:
- Declare `rv` as `s32 *rv` and `rv = a0; *a0 = sp20;` — the move would be from a0 to rv (a pointer). Target move v0,s0 — v0 gets a0. If rv is a pointer in a general reg... but the target uses v0. Without pin, rv could be any reg.
- `return;` with `rv` used in `if (rv == 0) return;`? Emits a branch.

Hmm, what about the `&&`/`||` fold: `if (((s32)a0) && 0) { }`? Compiler folds to nothing (0 is false). No move.

What if `rv` is used in an expression that's part of the store address: `*(s32 *)(rv - rv + (s32)a0) = sp20;`? identity address (launder) — not allowed, and emits no move.

Let me reconsider the possibility that the target's move comes from a *return* of a value in a void function via a different mechanism: GCC 2.7.2 expand_return with a void function — does it ignore or emit? w3 showed it ignored. Let me verify by dumping w3's asm. Actually score 1 with only the move missing confirms it's ignored.

What if we use `__asm__` — not allowed.

Hmm. Let me look at the exact src comment again: "(5) `rv = (s32)a0;` alone is DELETED by flow ($2 is dead at the end of a void fn). The empty volatile asm keeps it live and emits zero bytes." This confirms the wall.

But the shard is a "crack shard" — maybe some items are WALLs. Item 2 might be one. But let me try a bit more.

Real C idea: make v0 live by making the function's return value be used through the `sp20` value. E.g., the last statement `*a0 = sp20;` — what if we write it as `*a0 = (s32)(sp20 = ...)`? no.

Another idea: the move v0,s0 could be the *store of a return value* if the store is the last statement and the function returns the stored value: `return *a0 = rv;`? In a void function, still ignored.

What if the function's body ends with `return func_...;`? no.

Let me look at whether other functions in the same family (func_8017F0D0 has siblings in other TUs — the comment says "Family of 10 / 430 templatable ins") cracked this. Let me grep moves.md for func_8017F0D0 or the family.

Also grep src for other definitions of func_8017F0D0 with a lever-free body.
