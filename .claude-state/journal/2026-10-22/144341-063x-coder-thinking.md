---
ts: 2026-10-22T20:43:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_416aEZ7giGFdTq0GnNqD
---
Now score 2: mine `addu a1,a1,v1` where target has `addiu a1,v1,25996`. So `off` was NOT folded into the add (it became a register add: a1 = it + off), and `off` holds 0x658C in a1? Let's see: mine has `addu a1,a1,v1` — a1 = a1 + v1. Hmm, the register roles: mine a1->v1 and v1->a1 swapped. So mine: off in v1? and it in a1? Then `addu a1,a1,v1` = it + off. The target: `addiu a1,v1,0x658C` = it(v1) + K.

So `off` is a variable holding the constant 0x658C; gcc kept it in a register and used addu. To match, `off` must be a *constant* known at the add, giving `addiu`. But if off is constant-folded, we're back to the symbol fold (score 4).

Hmm, but n2 = 2: the fold of `it + off` didn't happen (because off is a variable?), yet off itself is a constant in a register → addu. We want `addiu` with the immediate 0x658C.

Can I make gcc use addiu with the constant but not fold the symbol? The target's add is `addiu a1,v1,25996` — an add of the symbol-based register with an immediate. So gcc must know the addend is a constant (immediate) but not fold the whole thing into a symbol+const address.

Why does gcc not fold `(reg it) + 0x658C` into symbol+const when it's live? Because cse's fold of a constant+const requires substituting the register with its constant, which it does only when... hmm, in n2, `off` is a variable with a known constant; gcc did NOT substitute off into the add, but used a register. Interesting: so gcc 2.7's cse doesn't substitute a constant for a pseudo in an add if the pseudo is... hmm, but mine (gen_base) DID fold `it + 0x658C`.

Difference: in gen_base, `it`'s constant is a *symbol_ref* and the add is folded into a symbol+const address (lui/addiu). In n2, `off` = 0x658C (a plain const) and the add `it + off` → if cse substituted off, it'd be `it + 0x658C` → then it substitutes it → symbol+0x658C. It didn't.

So cse's constant substitution is limited: maybe it only substitutes constants into *insns* when the result folds to something cheaper (a symbol address). In gen_base, the fold was of the whole expression into an address (symbol + const) — gcc's `simplify_plus_minus`/cse combining a symbol_ref with a const.

Hmm, in n2, `off` was probably kept in a register because gcc's cse didn't propagate a plain int constant into an add? That contradicts normal cse behavior.

Anyway, n2 = 2 with `addu`. To get `addiu`, the addend must be an immediate. What if `off` is a *constant expression* but the compiler doesn't fold the whole address: e.g. `p = it + (0x658C & 0xFFFF);`? Folds to 0x658C → same as gen_base.

What if the add is `p = it + 0x658C` where `it` is *live*? Then gcc keeps it in a register and uses addiu with the immediate — exactly the target! So the question is again how to make `it` live... but wait: in n2, gcc used `addu` with `off` in a register, not `addiu` — because `off`'s value came from a pseudo. If `off` were an immediate, gcc would emit addiu. So the target's add has an immediate → the source likely had a literal constant.

And gcc didn't fold `it + K` into a symbol address because `it` was live (not substituted). So the target's `it` IS live at the add!

But the target's copy path uses the reassigned it... Let me re-examine: maybe the target's source has TWO variables: `it` (the base, live) and another for the scan. Let's map the target registers:
- v1 = D_80120194 at 4614-461c (if branch: base), then at 464c (else: it), then reassigned at 4664 to D_801202A0, then incremented in the loop.
- a1 = p.

In the if branch, v1 = base and is live through the loop (beq a1,v1). At 464c (else), v1 = it. So v1 serves both. In the else branch, v1 = D_80120194, then a1 = v1 + K, then j test, and at test v1 = D_801202A0.

So the else branch's `it` (v1) is dead after the add (reassigned at test). Unless the source uses the *same* variable and gcc decided not to fold because... 

Hmm, wait: maybe the fold in mine is not a cse fold but a *combine/expand* fold: `p = it + K` where `it` is a pseudo with a known constant. In mine, the fold produced `lui a1; addiu a1,lo+K` — that's a direct symbol address, likely from cse1.

In the target, `it` is dead too (reassigned). So why no fold? Because of the launder in the src def — which means this item is a genuine launder wall... BUT n2 = 2 shows we're close: the only diff is addu vs addiu.

Can I get `addiu` with the constant while keeping the non-fold? What if `off` is declared `const s32 off = 0x658C;`? gcc would fold off into the add → `it + 0x658C` → then fold the symbol → 4. Hmm, or maybe not: `const` locals are folded at expand.

What if `off` is `s32 off = 0x658C;` and I use `p = it + (off & 0xFFFF);`? Same as off.

What if I use a *short* constant: `p = it + (s16)0x658C;` → folds.

The addu vs addiu difference: the compiler needs to know the addend is a compile-time constant at the point of the add. If it does, it may also fold the symbol. Unless `it` is live.

So the real fix is to make `it` live. Let me revisit: is there a C structure where the first `it` is live at the add but the copy path still uses the current scan pointer? YES: if the copy path uses a *different variable* for the scan, and the first `it` is live at the copy... no wait, if the copy path uses a different variable, the target's copy would use that variable's register. The target's copy uses v1 which is the scan pointer (reassigned at test). Hmm.

Alternatively: make `it` live at the add via a use *after* the add in the else block that doesn't affect the codegen. E.g.:
```
it = (s32)D_80120194;
p = it + 0x658C;
if (it != (s32)D_80120194) goto zero;   // always false; gcc folds it away
goto test;
```
gcc folds the comparison (it is known constant) → removed, and it dies → fold again.

What if the use is a *store* that's dead? `q = it;` where q is unused → flow deletes → it dead at cse time? cse runs before flow; cse sees q = it (a use) and would keep it live in its table, but the add still folds? gen_use2_dead = 4, so no.

What if the use is a *real* use that produces the same code? Hmm.

What if `p = it + 0x658C` is computed *after* the test block reassigns it? No.

Let me look at this from the register-pair angle: n2's diff is `addu a1,a1,v1` vs `addiu a1,v1,25996` plus the beq operand order (a consequence). If I could make `off` an immediate... 

What about using a *constant expression that gcc can't fold into the address but can fold into an immediate*: e.g. `p = it + (s32)0x658C` (a cast of an int constant)? Folds.

What if the addend comes from a `u16` variable? `u16 off = 0x658C; p = it + off;` — gcc would zero-extend off; maybe it keeps off in a register too.

What about `p = it + 0x658C` with `it` declared `volatile`? no.

Hmm, what if `it` is assigned from `(s32)D_80120194` but through a *pointer indirection that gcc can't fold*: e.g. `it = *(s32 *)&it2;`? garbage.

OK, let me try: make `it` live by giving it a use in a *later block that is reachable without the reassignment*, but with semantics that match: e.g., the `copy:` path uses `it`, and I make the reassignment happen *only on the test path*... The C already: `goto test` → test reassigns. What if instead the copy path is reached *from the else block* before the goto test? No.

Alternative: change the loop so the scan pointer is a *different* variable `q`, and at copy: `p = q;`. Then `it` (first) is live only if used elsewhere; not.

What if at copy we use `it` but the compiler's CFG has a path from the add to copy that doesn't reassign it? We could restructure:
```
it = (s32)D_80120194;
p = it + 0x658C;
goto test;
copy:
    p = it;      // uses it (first or current?)
```
For the copy to use the *current scan pointer*, `it` must be reassigned by then. If the scan pointer is a separate variable q, and copy does `p = q`, then `it` is dead.

Hmm, unless the target's copy path actually uses the *first* it! Let me re-check the target's copy block: `465c: j 4694; 4660: move a1,v1`. What is v1 at that point? The path to 465c is from 467c `beqz v0, 465c`, inside the loop, where v1 = the scan pointer. But wait — could v1 still be D_80120194 at that point? No: at 4664 v1 = D_801202A0, and the loop increments it.

Hmm, unless the copy block is reached with v1 = D_80120194 through some other path... The only branch to 465c is 467c. So v1 = scan pointer.

OK so `it` (first) is dead in the target too. Then why no fold? The launder (the src def has it). So the target source had the launder (or equivalent). This item is a launder wall, and the prior coder's 35 variants confirm.

BUT: n2 = 2. That's a lever-free body at 2. Can I get 0 by making the add use an immediate? The target's add is `addiu a1,v1,0x658C`. In n2, gcc used `addu a1,a1,v1` because `off` was in a register. If `off` were the immediate, it'd be `addiu`. But with the immediate, gcc folds the symbol (score 4). Unless...

Wait! Maybe I can keep `off` as a variable but make gcc's *reload* turn `addu a1,a1,v1` into `addiu a1,a1,0x658C`? That happens if `off`'s pseudo gets a constant REG_EQUAL and combine turns addu with a constant-operand pseudo into addiu. Hmm, gcc's combine does that: `(plus reg reg)` where one reg has a constant REG_EQUAL → addiu. But it didn't (it kept addu with off in a register).

What if `off` is assigned 0x658C and *used only here*, so it's a single-use constant pseudo → gcc would substitute it into the add → addiu with the immediate → then cse folds the symbol? Let's see: n2's off is used once. gcc kept it in a register and used addu — surprising.

Hmm, maybe `off` was NOT assigned in my n2! I declared `s32 off;` but never assigned it! Look at mk: I added the decl `s32 off;` and the body uses `p = it + off;` — off is uninitialized! That's a bug: undefined behavior, and gcc used an uninitialized register (a1). Score 2 by accident!

Oops. So n2 is invalid C (reads uninitialized off). Not a real candidate. Must discard.

Let me redo: `s32 off = 0x658C; p = it + off;`. Test that.

Also, with off initialized to 0x658C, gcc will likely fold → 4.

Let me also try `p = it + (off = 0x658C)`? no.

Let me test off initialized.
