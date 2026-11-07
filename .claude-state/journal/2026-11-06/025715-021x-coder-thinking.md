---
ts: 2026-11-06T09:57:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_av5wo4bJuKOHi3jSbBj3
---
So `return a0;` in a void function did NOT emit the move (gcc probably just warned and ignored the value). Hmm.

Let me think differently. The move is `v0 = s0` where s0 = a0. What C makes gcc move a0 into v0?

Option: a function whose return type is pointer, but we can't change the signature. BUT — the brief says "no signature or decl change outside the body (callers stay as they are)". Could we change the return type in the *definition* only? The TU file has `extern void func_8017E8D8(...)` at line 3568, 3608, and the definition at 3740. Callers call it as void. If the definition returns `s32 *` while the extern decl says void, that's a conflicting declaration error. But we're only editing the body (win.c), and the tool substitutes the body into the TU which has `extern void ...` declarations. So we can't change the return type — the TU decl conflicts.

Hmm. Unless the tool's body replacement replaces the definition line including signature? Let me check: --body means "FILE holds the function's definition only". The tool splices it in place of the existing definition. The existing extern decls remain. So the return type must stay void.

OK so we need a void function to emit `move v0,s0`.

Idea: A call to a function returning a value where the result is stored in a variable that gets v0? No — the move is v0 = s0 (a0 value), not a call result.

Idea: `s32 x = (s32)a0;` used later? There's nothing later.

Wait — maybe the move isn't from `rv = a0` at all in the original source. Maybe it's from an entirely different source structure. Let me reconsider the whole function. The last part:
```
lw v0,32(sp)
sw v0,0(s0)
move v0,s0
```
What if the original source is:
```c
*a0 = func_8012B77C(...)  ... 
```
No.

What if the original returns a0 as the value of a `return` in a function declared void — but gcc's behavior depends on -pedantic? Let me check the actual compile flags. Maybe warnings. Actually gcc 2.7.2: "return with a value, in function returning void" — it emits the return expression? Let me check the GCC 2.7.2 source in tools/reference/gcc-2.7.2/. Look at c-typeck.c or stmt.c `expand_return`.

Actually in GCC 2.7.2, `expand_return` in stmt.c:
```
if (TREE_TYPE (TREE_TYPE (current_function_decl)) == void_type_node)
  {
    if (retval != NULL_TREE)
      warning ("return with a value, in function returning void");
    ...
  }
```
Hmm, in old gcc, if function returns void and retval given, it warns and... let me actually check. There might be a path where it evaluates the value. Let me grep the reference source.

Actually, let me step back and think about what other real C could produce `move v0,s0`.

Alternative: `return (s32)a0;` in void — same.

Alternative: What if we make the last statement a function call whose return value is used, e.g. `if (func(...))`? No.

Hmm, what about `return;` but the function's `a0` gets into v0 through... no.

Wait, maybe the source used the return-value idiom differently: perhaps the original had `void` but the compiler keeps v0 because of a `return` statement with an expression that is evaluated for side effects? In C, `return expr;` in a void function — gcc evaluates expr for side effects and might load it into the return register? Let me check gcc 2.7.2 stmt.c.

Let me grep tools/reference/gcc-2.7.2/stmt.c for "returning void".
