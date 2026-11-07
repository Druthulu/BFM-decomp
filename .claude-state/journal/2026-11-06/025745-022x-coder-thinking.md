---
ts: 2026-11-06T09:57:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_MArldgyY4KPIfSMYbnFT
---
Confirmed: for a void function, `return expr;` expands expr with NULL target (side effects only) and then null return. So `return a0;` produces nothing. That's why it failed.

So `move v0,s0` cannot come from a return in a void function.

Now, what else? Let's think about how gcc could produce `move v0,s0` before the epilogue in a void function.

Possibility: the target's move v0,s0 could come from a *different source statement ordering* — e.g., the value sp20 loaded into v0, stored, and then... no, v0=s0 is specifically a0.

Hmm, wait. Let me reconsider: maybe s0 is not a0 at that point? `move s0,a0` at 2a3c (delay slot of bnez). s0 is never reassigned. So yes s0=a0.

What about a `set` to the return-value pseudo? In gcc, even void functions have DECL_RESULT but it's not used.

Alternative: maybe the original source declared the function returning a value but the *project* declares it void... no, one definition.

OK, different angle: perhaps we don't need `move v0,s0` from the end of the function. Maybe we can restructure so that the register allocation naturally produces it. But the instruction is literally `move v0,s0` at that position; the diff is purely count (one missing ins). Any body that yields 52 instructions identical bytes works.

What real C gives `move v0,s0` (a copy of an arg pointer into $v0) in a void function? 

Idea: passing a0 as an argument to a call. If a call's first arg is a0, the move would be `move a0,s0` (a0 reg), not v0. Unless the call's arg register is v0 — that happens for... no, args go to a0-a3.

Idea: A `switch` on (s32)a0? jump table? No.

Idea: An assignment `s32 dummy = (s32)a0;` where dummy is then... dead. Deleted.

Idea: The value is used in a comparison at the end: `if (a0) ...` would emit a branch, not a move.

Idea: A function call where a0 is passed as an argument via a variable that happens to be v0? no.

Hmm, what about a volatile? `*(volatile s32*)&something = (s32)a0;` would store, not move v0.

Hmm. What about `return` being at a point where... 

Wait. Actually — maybe the original source is a function returning void, but it has a `return;` after a call whose return type is a pointer, and gcc's "return value in void" ... no.

Let me reconsider: maybe the original body isn't what I think. Let me look at whether there's an original source or a decomp note for func_8017E8D8. The comment says "P36 rung B t8_tus2". This is an "jr" function (jr_8017BEBC) — maybe there's a corresponding function in the "main" TU and the ov version is a jump-table relocation stub. Hmm.

Actually — hold on. Let's reconsider the problem. Maybe the target's `move v0,s0` is a leftover from the *previous* function in the TU? No, objdump shows it within the function.

Let me look for how similar functions were cracked. Search moves.md for "v0,s0" or for a returned pointer in void. Or search cookbook.

Actually, a key insight: the target function is *void* in the target build too (it's the same bytes). The `move v0,s0` must have a source. In MIPS, `move v0,s0` = `addu v0,s0,zero`. The compiler emits this when a pseudo in v0 is copied from s0. In a void function, the only way to set v0 is:
- the result of a call is returned in v0 and then used → `move v0,s0` would be a move from s0 to v0, i.e., v0 = a0.
- an explicit variable assigned a0 that ends up in v0 and is live (used).

But nothing after. Unless the value in v0 IS live at the end because... in a void function with `-O2`, a dead set is deleted by dead code elimination (in flow/cse). Unless the variable is a `volatile` or its address is taken... `move v0,s0` is not a store.

Wait, what if there's an `asm` that uses it — that's the keepalive lever, forbidden.

Hmm, so how could the ORIGINAL 1998 compiler emit this? Because the original source probably DID return a value! The original function might return `a0` (a pointer), and the project's C file declared it `void` because callers ignore it. But then the project's src with `void` couldn't match... unless the hack (pin+keepalive) was used. That's exactly what happened: the project couldn't express it with void, so used pin+keepalive.

Hmm, so is a lever-free match impossible? The brief expects some items may be WALL. But let's not give up: maybe the return type CAN be changed within the body file if the tool splices the whole definition including the signature. Let me check how --body splices. If it replaces the whole definition (from `void func_8017E8D8(` to `}`), then changing to `s32 *func_8017E8D8(...)` would leave the `extern void func_8017E8D8(...)` declarations conflicting → compile error. Unless the tool also... Let me check whether the externs matter: two declarations, one `void`, one `s32*` → "conflicting types for func_8017E8D8" error.

But what if we change the definition to return a value and ALSO the externs are in the TU (can't touch). So no.

Alternatively — could the function be declared with a *different* type in a way that doesn't conflict? No.

Hmm, but wait: what if we keep the return type void and use a `return` that's compiled as a value return by tricking gcc? E.g., the function's RESULT_DECL is void. No.

Let me reconsider: maybe `move v0,s0` doesn't require a return. What if it's `a0 = a0;`? No.

What if the last statement is a call `func(a0)` where func takes the arg in v0? No, MIPS args are a0-a3.

What if it's `s32 x; ... x = (s32)a0; func_8012B77C(x, ...)` — then the move would be to a0 (arg reg).

Hmm, what if the compiler, at -O2 with `-fno-...`, keeps v0 because of a `return` in a *conditional* path that's unreachable? no.

Let me look at whether the function is truly declared void everywhere or maybe one caller uses its return. `func_8017E8D8(sp10, a0, a0 + 0x102);` — used as statement. But maybe there's a call site that uses the return value, requiring the declaration to return something. The decls at 3568, 3608 are `extern void`.

OK, let me check: is it possible that the `move v0,s0` is actually the compiler copying a0 into v0 because the function's *callers* expect a return and the source has `return a0;` but the declaration says void... no, the source is one.

New idea: Maybe we can get `move v0,s0` from a *different* source-level construct that legitimately writes a value into the return register: passing a0 as the second/third... no.

Wait — what about `func_8012B77C((s32)&sp20, a1 + 4, (s32)sp10)`? Its return value is in v0. If we wrote `s32 r = func_8012B77C(...)` and then used r... but r would be v0 from the call, and `move v0,s0` is a0 not r.

Hmm, let me look at the actual instruction: `02001021 move v0,s0` = addu v0,s0,zero. s0=a0.

What if a0 were reassigned? No.

Let me reconsider the possibility that this is a WALL, but first let me check the other items and whether this kind of thing has been cracked. Search moves.md for "move v0,s0" or "retval" or "void-return".

Actually the walls.txt might have a relevant tag. Let me grep moves.md for keepalive entries with MATCH where a return value was involved. Line 28: "keepalive | func_80184D28 | MATCH — keepalive replaced by return v0; (s32 fn returned nothing; flow kept v0 sets only via asm use)". Interesting! So there, a function's keepalive was replaced by `return v0` — but that function returned s32 maybe.

Let me look at walls.txt tags for void-return: "expand-void-return" is a wall tag. Our function is void but not expand.

Let me search moves.md more broadly for "v0,s0" and "return a0".

Also maybe there's another approach: a `switch` or a computed goto? no.

Let me reconsider: maybe the original source had the last statement as an assignment to a global/static that's in v0? no.

Hmm, actually! What about the *return type of the function being void* but the function body ends with a call to a function declared to return a pointer, and that call is a tail call? If the call result is used as... no.

Wait, what about this: the target move v0,s0 might be from `return` inside a *nested* construct where gcc treats current_function_decl... no.

Let me look at the broader picture: perhaps the whole last sequence can be re-expressed. What if the original source was:
```c
func_8012B77C(...);
*a0 = sp20;
return a0;   // in a pointer-returning function
```
That gives `lw v0; sw; move v0,s0`. Yes exactly.

So the original function returned `a0`. The project declared it void. This is a WALL unless we can change the return type.

Hmm, but hold on — maybe we can change the return type *in the definition only* if the TU's extern decls are compatible? `void` vs `s32 *` are not compatible.

But what if the definition is `void *func_8017E8D8(...)` and the externs say `void`? Incompatible.

What if we declare it as returning `void` but... no.

OK wait, maybe there's a subtlety: the delever_search --body replaces only the body *inside* the function, keeping the signature line from src? Let me check. If it replaces from the signature line to the closing brace, then I could write `s32 *func_8017E8D8(s32 *a0, s32 a1, s32 a2)` in win.c. But then the extern void declarations conflict. Let me check the tool's splice mechanism to know exactly.

Let me grep delever_search.py for "def splice" or body handling.
