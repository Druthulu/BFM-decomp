---
ts: 2026-11-06T09:00:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_JKK5Fgy0Uczj5rj0XieW
---
buf[5] at sp+68 is read at insn 85 (the product) and later at 216/224 (the uv computations). No store to 68(sp) in the function? The buf is filled by func_8017E410(mode1, buf) via the pointer (sp+48). So no explicit stores.

Idea: what if the original source was:
```c
buf[5] = (a[2] - z) * buf[5];
```
This is a store to buf[5]! The target would have a `sw t1,68(sp)`. Is there one? No store to 68(sp) in the listing. So no.

Hmm.

Wait, actually, let me look at line 100-108: after gte_rtpt, `swc2 $12,0(a0)` etc. Then lwc2 $0..$1 and `swc2 $14,0(v0)` for gte_stsxy.

OK. Let me now consider a totally different possibility: maybe the original C *did* use the product, and the use is the `gte_stsxy3(&p->x0, &p->x1, &p->x2)` call? No.

Let me look at what `t1` ($9) could be in the original source: maybe the original declared a variable `s32 t1` used as... no, the register name is incidental.

OK, decision time: this looks like a wall of class `flow-unused-result`. But let me do due diligence with a batch of ~30 candidates. Actually, wait — before mass-producing, let me think about one more clever route: **the value could be used by a `(use)` insn created by combine's REG_DEAD handling** (like item 2). If the product is used in a *copy* that combine then removes but leaves a USE... Hmm.

In item 2, combine created a USE for a REG_DEAD at a code label. That USE kept the register alive at that point, but flow removed it later (it wasn't in cse2/flow dumps). Not a reliable route.

Another thought: what if the product is used in a **conditional expression that gcc turns into a `slt`+... ** no.

What if the product is used as the **count of a memcpy-like builtin**? no.

Hmm, what about **`func_8017E410` being called with the product as an argument in a *dead* argument position**? It takes 2 args. No.

What if the original code was:
```c
s32 tt = (a[2] - z) * buf[5];
...
func_8017E410(mode1, buf);
```
and tt is used much later in a place where the decompiled body uses a *recomputation*? Let me look for a spot where the same expression could be used: e.g., the else branch `if (hi != 0) ... unk48 = unk48 * (rand() % 3 + 3)`. No.

Let me look at the uv computations: `p->uv0 = buf[1] | (buf[3] << 8) | buf[2];` etc. buf[5] is used in uv2/uv3: `((buf[3] + buf[5]) << 8)`. Not the product.

I'll now test a batch of plausible uses. But many will add instructions. Let me think about which could be zero-cost:

1. `if (tt) ;` — empty if removed at tree level.
2. `tt;` — dropped.
3. `tt = tt;` — dropped.
4. `switch(tt){}` — removed.
5. `do { tt = ...; } while (0);` — dropped.
6. `while (0) { tt = ...; }` — dropped.
7. `if (0) { tt = ...; }` — dropped.
8. `goto L; L: tt = ...;` — tt unused → dropped.
9. `tt = (a[2]-z)*buf[5]; z = z + (tt - tt);` — tree folds.
10. `otz = tt; gte_stszotz(&otz);` — extra store.
11. `v[0].vx = tt;` — changes code.
12. `p->tag = tt;` — changes.
13. `if (tt == 0) {} else {}` — removed.
14. `return tt;` — changes.
15. `buf[5] = tt;` — extra store.
16. `*(volatile s32*)&otz = tt;` — extra store.

None zero-cost.

Hmm, what about making the product's *result* be the value of `z` in a dead assignment: `z = tt;` right before the loop where z is recomputed? The target's if-block ends with `if (a[7]==0) a[7]=1; else if (a[7]==1) a[7]=2;` then the else block `z = top`. After the if, the loop starts with `mode = 0; top2 = a[0]; ...` and `z` is used in the loop. So `z = tt` would change the loop's behavior. No.

What about assigning to `idx`/`otp` (the pinned $4 vars)? They're assigned later in the if-block (`idx = otz;`). If we assign `idx = tt;` *before* `idx = otz`, the first is dead → deleted (unless $4 pin makes it live? the pin is a register-asm variable; flow might keep the set because the pseudo is a hard reg? Hmm! A register-asm variable's set could be considered live? No, flow deletes dead sets to hard regs too... but maybe not! If the variable is pinned to $4, the set `idx = tt` would be `(set (reg:SI 4) tt)` and flow's insn_dead_p might consider hard registers... Actually flow deletes dead sets to hard registers only if they're not live; $4 might be live at the end (caller-saved, dead). It would be deleted.

But the target's insns write t1, not $4. So no.

OK, what if we make the product feed a **second assignment to a pinned variable that the target already has**? The target has `otp = (u32 *)(idx + ot)` using $4. If we compute the product and assign it to `idx` before `idx = otz`... the result would be `idx = otz` overwriting; the product's set dead. Deleted.

Hmm.

What if we *replace* the computation of something with the product? E.g. `idx = otz;` → `idx = otz + 0*(a[2]-z)*buf[5];` — the product would be computed and multiplied by 0, folded. Adds.

Let me now look at the actual original code style: maybe the original had:
```c
if ((a[2] - z) * buf[5] > 0x4000) { ... }
```
No branch in target.

I'm now ~15 min in. Let me consider the wall route seriously. But 30 scored tries is a lot of work for a wall. Hmm, but the brief is explicit. Let me do a batch of ~20 additional candidates in one sc.sh call (each is a full compile ~2-5s, so 20 = ~60-100s). That's cheap. I'll generate diverse real-C uses.

Actually, wait! One more idea that could be zero-cost: **make the product the operand of a `?:` that feeds the `buf` pointer to gte_ldv3c?** no.

Another: **use the product as the value stored into `otz` AFTER gte_stszotz but before the `if (otz > 0...)`** — that changes the condition.

Another: **use the product in a `if (otz > 0 && cull == 0)` extended condition with `&&` folding**: e.g. `if (otz > 0 && cull == 0 && ((a[2]-z)*buf[5] || 1))` — `x || 1` folds to 1 at tree level.

`((a[2]-z)*buf[5], 1)` comma → left operand has no side effects → dropped at tree level. BUT does gcc 2.7.2's tree optimizer drop a comma expression with a non-trivial left operand? The left operand `(a[2]-z)*buf[5]` has no side effects; gcc's `save_expr`/`expand_expr` for a comma evaluates both operands... Actually in GCC, `(a, b)` is a COMPOUND_EXPR; expand evaluates the left operand for side effects, and if it's not TREE_SIDE_EFFECTS, it's discarded at the tree level. Yes, dropped.

What about an expression with a *volatile* left operand? A volatile load adds an instruction.

Hmm what about `sizeof((a[2]-z)*buf[5])`? Compile-time, no code.

What about an array dimension? no.

OK here's yet another idea: the product could be used in a **function call argument to a function that is declared but whose call is optimized away**? Calls aren't removed.

What about a **builtin** like `__builtin_return_address`? no.

Let me just do the batch and record the wall if nothing works. Actually, hold on — let me reconsider the target's mflo t1 one final time. t1 is $9. Is $9 special? In the pinned declarations, `idx` and `otp` are pinned to $4. No $9 pin. 

Hmm, one thing I notice: `mflo t1` — the target's multiply result is in t1, a *caller-saved* reg. If the product were assigned to a C variable used later, the RA would put it elsewhere. So it's dead.

Let me check GCC 2.7.2 flow.c's dead-code elimination to see whether there's a class of dead sets it keeps. grep flow.c for "delete_dead" or "insn_dead_p".
