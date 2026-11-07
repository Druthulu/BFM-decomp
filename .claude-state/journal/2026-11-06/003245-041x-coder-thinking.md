---
ts: 2026-11-06T07:32:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_BNHom7eCYgrTI3rdzH5v
---
The sibling func_800CB158 has the same copy pattern using `arg0` directly, no s0. And note `func_800CAF84(arg0)` — but our extern decl says `void func_800CAF84(void)`. Wait, the sibling calls func_800CAF84(arg0) with an argument! So the real signature of func_800CAF84 takes an argument. In our function, the call is `func_800CAF84();` with no args, but the extern declaration is local `extern void func_800CAF84(void);`. Hmm, maybe the real function takes an arg and the call in our function passes... Let me look at func_800CB228 and the file's other uses.

Actually this sibling is very informative: it uses `arg0` directly (no s0) and the copies use `(arg0+0x38)`. Let me check its bytes? It may show how a0 is handled. But our function has a call and the if-block uses s0.

Key insight: func_800CAF84 might take arg0 as parameter! In our function, `func_800CAF84();` — maybe the original is `func_800CAF84(arg0);` and the extern decl is wrong (declared void). But the call target relocates to func_800CAE0C (target shows `jal func_800CAE0C`). Let me check what func_800CAE0C is. Maybe func_800CAF84 is an alias.

Actually, the target's jal at insn 26 goes to 0 <func_800CAE0C> (relocation label). The source calls func_800CAF84. If we pass arg0 to it, the call would need `move a0,?` before jal. Target has `jal` with `nop` delay slot — no move a0. So func_800CAF84 is called with no meaningful arg (or arg already in a0?). Hmm! If the original called `func_800CAF84(arg0)` and arg0 were still live in a0 at that point, the call would need no move! That's it! 

Look at target: `jal func_800CAE0C; nop`. If the source were `func_800CAF84(arg0);` and arg0 were live in a0 (not yet copied to s0), the compiler would pass arg0 directly — but then s0 must be a separate copy. Wait, target has `move s0,a0` at insn 2, so arg0 IS copied to s0 early. If arg0 is still needed for the call, it would be live in a0 across the copies! And a0 would be reserved → copies use a1-a3! And the jal needs no move because arg0 is already in a0. THAT explains everything!

So the natural C is likely:
```
void func_800CB458(s32 arg0) {
    extern s32 func_80146A6C(...);
    s32 s0 = arg0;
    ...
    *(Struct16 *)(s0 + 0x38) = ...;
    *(Struct16 *)(s0 + 0x48) = ...;

    func_800CAF84(arg0);   // passes arg0 in a0
    ...
}
```
And the extern declaration in the source `extern void func_800CAF84(void);` would need to be `extern void func_800CAF84(s32);` — but the brief says "no signature or decl change outside the body (callers stay as they are)". Declarations INSIDE the body (the extern lines are inside the function body!) — hmm, they are inside the body. "no signature or decl change outside the body" means we can change decls inside the body. So we can change the extern declaration inside the function.

Wait, but does func_800CAF84 take an arg? Sibling calls `func_800CAF84(arg0)`. Let me check the file's declaration at top and the actual function. Let me grep.
