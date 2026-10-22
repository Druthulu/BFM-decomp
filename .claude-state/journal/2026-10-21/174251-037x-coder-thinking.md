---
ts: 2026-10-21T23:42:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_noRfH5Ye1Wjerd1BU0rv
---
d1 also 29. So the "second set" of the pointer variable didn't help — gcc still unified the two address expressions (because the VALUE of p1 in both cases is the same rtx (plus (symbol_ref)(const 8)), and cse substitutes the value).

Right: cse works on the *expression*, not on the variable's set count. The variable p1 is a copy; the address expression is shared.

So cse unifies the two ADDRESS expressions. To break it, the expressions must be structurally different.

Hmm. So how did the asm break it? Because the asm's output is a hard REG, and cse cannot rewrite an asm's input operand. So the first use's value comes from the asm (a reg), and the second use is the plain expression → not unified.

So in real C, we need one of the two uses to be "opaque" to cse but still compile to `addiu aN,sp,24`.

What is opaque to cse but compiles to an addiu from sp?
- A value loaded from memory: `lw` — no.
- A value produced by an asm — banned.
- A value from a *function call* — no.
- A **volatile** load — no.
- A value computed from an unknown-but-equal expression: e.g. `p1 = sp10 + 4;` where sp10 is a *pointer to a pointer*? no.

Hmm... What about the SECOND use being `&sp10[4]` where `sp10` is accessed via a **pointer-to-array**? e.g.:

```
u16 (*pa)[6] = &sp10;
func_800D20C0(sp10, sp10 + 4, 1);
func_800D23D0(&(*pa)[4]);
```
Now `(*pa)[4]` = *(pa + 8) → the address = (plus (pseudo_pa) (const 8)) where pseudo_pa holds &sp10 = (plus (reg sp)(const 16)). Different rtx from (plus (symbol_ref)(const 8))! So cse won't unify.

But then gcc needs pseudo_pa in a register (or folds it). If it folds via lookup_reg → (plus (reg sp)(const 16)) then &(*pa)[4] → (plus (plus (reg sp)(const 16))(const 8)) → simplify → (plus (reg sp)(const 24)) → `addiu a0,sp,24`! And that expression is used once → no pseudo → direct addiu.

And for the first use, `sp10 + 4` → (plus (symbol_ref sp10)(const 8)) → after reload, symbol_ref sp10 becomes (plus (reg sp)(const 16))... hmm, then it'd be the same as the other. But the point is they're computed at different RTL stages so cse may not unify.

Hmm, but the risk: gcc will fold `pa` (a local pointer var = &sp10) back to the symbol_ref, making them identical again.

Honestly, this is a lot of speculation. Let me consider a totally different, more promising direction:

**What if the fix is to make the address used ONCE in the C, and get the second `addiu a0,sp,24` from something else entirely?**

Look at the target again:
```
12 jal func_800D20C0
13 sh zero,16(sp)      (delay slot)
14 jal func_800D23D0
15 addiu a0,sp,24       (delay slot)
```
Both calls. call1 args: a0=sp+16, a1=sp+24, a2=1. call2 arg: a0=sp+24.

Hmm what if the original source was:
```
u16 *p = sp10 + 4;
func_800D20C0(sp10, p, 1);
func_800D23D0(p);
```
and the original compiler (not gcc) just didn't CSE and recomputed. Our gcc does CSE. The decompiler added the launder to force gcc. We need a C spelling that makes gcc recompute.

**IDEA: use a `union` to make the two addresses different rtx but the same value!**

```
union { u16 a[6]; } u;   // no
```

Hmm, what about:
```
struct { u16 a[6]; } s;
```
`s.a` address = (plus (symbol_ref s)(const 0)). `&s.a[4]` = (plus (symbol_ref s)(const 8)). Same as array.

**IDEA: make the two accesses have different MEM_IN_STRUCT_P flags.** cse's `find_best_addr`... Hmm, cse has a special case: two MEMs with different flags are NOT unified? Actually cse's `equiv` handling: `cse.c` `cse_record` → for MEMs, it checks `flags_1 == flags_2`? I believe cse does distinguish MEM_IN_STRUCT_P (via `data_ref`?). Hmm, but we're dealing with addresses, not MEMs.

**IDEA: the address expression from a global symbol instead of the frame.** E.g., what if sp10 is not a local array but the code uses a *pointer* to a local array...

Hmm hold on. What about the address of a local *scalar* vs the address of an *array element*? For `u16 w;` at sp+16, `&w` is (plus (reg sp) (const 16))? or (symbol_ref w) with frame offset? In gcc RTL, after reload, the address of a local is computed as (plus (reg sp) (const N)) or as a symbol_ref with a frame offset that reload converts to (reg sp) + offset.

For an array `u16 sp10[6]`, `sp10 + 4` = (symbol_ref sp10) + 8 → after reload → (plus (reg sp) (const 24))!

Hmm interesting — for a local ARRAY, gcc's address is (symbol_ref) with a frame offset, and reload converts it to (plus (reg sp) (const 16)). For `sp10 + 4` → the offset is 16+8 = 24 → (plus (reg sp)(const 24)).

Now, the CSE happens BEFORE reload (cse is in the RTL optimization pipeline, reload is later). At cse time, `sp10 + 4` is (plus (symbol_ref sp10) (const 8)) and `sp10` is (symbol_ref sp10). And the other use `sp10 + 4` is the same → unified.

But if one use were `&sp10[4]` — hmm same.

What if one use is the address of a *scalar* variable at sp+24 and the other is `sp10+4`? Then their cse-time rtx: (symbol_ref w) vs (plus (symbol_ref sp10)(const 8)) → DIFFERENT! → cse doesn't unify → two separate computations → after reload both become (plus (reg sp)(const 24)) → both emit `addiu aN,sp,24`!!!

THAT'S IT! The trick: have the array AND a separate scalar variable at the same address. Hmm, but how do you have two objects at the same address? You can't in C without a union.

UNION! 
```
union { u16 a[6]; u16 b[6]; } u;   // b[0] and a[0] at the same address
```
u.b[4] and u.a[4] → both (plus (symbol_ref u)(const 8))? The union member b has offset 0, so &u.b[4] = (plus (symbol_ref u)(const 8)) and &u.a[4] = same. Identical. ✗.

Hmm. But with a struct containing a union? Still the same.

What if we use a **pointer cast** to give a different base? e.g.
```
u16 sp10[6];
...
func_800D20C0(sp10, sp10 + 4, 1);
func_800D23D0((u16 *)((u8 *)sp10 + 8));
```
Both → (plus (symbol_ref sp10)(const 8)). Same.

Hmm. So we need two DIFFERENT cse-time rtx that reload turns into the same address.

What about: one use is the address of a local array element, the other is the address of a local *scalar variable* — and we make the scalar variable an ALIAS of the array element via a union with a struct:

```
union {
    u16 a[6];
    struct { u16 x[4]; u16 y[2]; } s;
} u;
```
u.s.y[0] is at offset 8 = same as u.a[4]. cse-time rtx: &u.s.y[0] = (plus (symbol_ref u) (const 8))? For a struct member inside a union, the address is (plus (symbol_ref u) (const 8)) — the same as &u.a[4]. Hmm, both fold to (plus (symbol_ref u)(const 8)).

Because cse-time rtx for any address = base symbol + constant offset. Same base, same offset → same rtx. The only way to differ is a different base symbol or a different offset.

A different base symbol at the same address: impossible in C... 

...UNLESS the two bases are a *global* and a *local*? no.

OK so cse-time rtx equality is unavoidable for the same address. Therefore cse WILL unify. The asm breaks it because cse can't touch the asm.

CONCLUSION: To break the unification in real C, we need the value to reach the use through something cse can't fold — and the only C-level "opaque" mechanisms are: memory loads, volatile, function calls, and **asm**.

MEMORY LOAD! What if the second use reads the pointer from a stack slot? Then it's `lw a0, N(sp)` — doesn't match `addiu a0,sp,24`.

Hmm... but what if the load is of a *constant* that gcc folds? No.

So... is this function actually crackable in real C?!

Hold on. Let me reconsider. Maybe the answer is that gcc CAN be made to not unify, by giving the pseudo 2 sets via a different mechanism. §145(b) says: "ANY second SET of a pseudo in the address's equivalence chain (in-place `p += K`, §145(b)'s `p = r;` copy, or an asm re-tie) kills the fold; the pass is cse and the gate is invalidate's reg_tick++".

"the address's equivalence chain" — this is about an ADDRESS (a MEM's address), not a pointer value. In our case: the address of the local `sp10` is used in `sp10 + 4`. Hmm.

But d1 (`p1 = &sp10[4]` as a second set of p1) didn't work. Because the cse-unified thing is the *value expression* (plus (symbol_ref sp10)(const 8)), and cse unified the two uses of that expression, creating a pseudo with 1 set. The two "sets" of p1 don't matter.

To give the EXPRESSION pseudo two sets, we'd need the expression to be re-computed: i.e., two different rtx that cse considers "the same equivalence chain" but with a reg_tick bump in between. §145(b): "in-place `p += K`" — the pointer-bump addiu is saved by cse unless there's a second set of the pseudo `p`.

Hmm, so the mechanism: cse tracks equivalence via reg_tick. If between the two uses, some pseudo's reg_tick is bumped (invalidated), the equivalence chain breaks and the second use re-derives the expression.

So we need to invalidate the equivalence of the ADDRESS pseudo between the two uses. The asm does it (asm has a memory clobber? no, but asm operands cause... hmm, `__asm__("" : "=r"(p1) : "0"(p1))` has no memory clobber, so no reg_tick bump. But the asm creates a new pseudo for the output, so p1's value = the asm output reg → different.

So: the asm gives p1 a value that is a HARD REG, breaking the chain.

In real C, what breaks the chain? A second SET of the *same pseudo*. d1 did that for p1, but the chain that matters is for the address expression.

Hmm, so what if we assign the address to a variable in a way that the address expression itself is re-derived? E.g.:

```
u16 *p1;
p1 = sp10 + 4;    // set 1: p1 = (plus (symbol_ref sp10) (const 8))
...
p1 = sp10 + 4;    // set 2
```
The two assignments create two sets of p1, each with the same value expression. At cse time, cse processes the first assignment: p1's reg_equiv = the expression → creates a pseudo for the expression? Then the second assignment re-derives it. cse would see the expression twice and unify them into one pseudo (with 2 sets? no, one pseudo with the expression computed once).

Hmm. In cse.c, when a common subexpression is found a second time, cse creates a new pseudo for it and replaces the earlier occurrence with the pseudo. The pseudo has ONE set (the computation). So the value lives in the pseudo → live across the call → s0.

UNLESS the pseudo's reg_equiv is a constant/rematerializable.

AH WAIT. Here's the thing: gcc's `cse.c` `record_cse` only creates a pseudo for the expression if the expression is "worth" it. And there's a rule in cse: if the expression is a "constant" it isn't CSE'd. But (plus (symbol_ref) (const 8)) is not a constant.

Hmm, but gcc's cse has `cse->equiv` and the "cse_class" mechanism. And there's a special case: cse does NOT create a pseudo for an expression that is "cheap to recompute" and used in a context where recomputation is fine? I don't think gcc has that.

Hmm, BUT: gcc's local-alloc has the "address GIV" concept: a pseudo holding an address that is used to compute other addresses gets special treatment — it can be "rematerialized" as a base for address computations. §349 says: making n_times_set > 1 kills the ADDRESS GIV and reproduces a REMATERIALISED addiu.

So: the address pseudo (holding sp+24) IS an address GIV. To kill it, give it 2 sets.

How do we give the *address expression's pseudo* two sets? By making the expression appear twice in a way that cse treats as two separate sets. Hmm — cse creates the pseudo at the FIRST occurrence and replaces it; the second occurrence uses the pseudo (1 set).

UNLESS the second occurrence is a re-derivation after a reg_tick bump.

What bumps reg_tick? `invalidate()` is called by: asm with memory clobber? Actually reg_tick is bumped by `update_stmt` (any statement that writes a pseudo) — "the gate is invalidate's reg_tick++". update_stmt bumps reg_tick for the statement's modified pseudos. So ANY re-assignment of a pseudo bumps reg_tick and invalidates the equivalence chain.

So: if between the two uses, we re-assign a pseudo that is part of the address's equivalence chain, the chain breaks. d1 re-assigned p1 — but p1's value was substituted, so the chain...

Hmm, in d1: `p1 = sp10 + 4;` (set1) ... `p1 = &sp10[4];` (set2). At cse time: set1 gives p1 = expr. Then use1 (call1) uses p1 → cse substitutes p1's value = expr → creates a pseudo for expr. Then set2: p1 = expr again → update_stmt(p1) bumps reg_tick → the expr pseudo's equivalence is invalidated? Then use2 → cse re-derives expr → new pseudo or direct computation.

But the result was still 29 (same as before). So d1 didn't change anything. Maybe because the second assignment `p1 = &sp10[4]` was optimized away by the frontend (gcc sees p1 already equals that value? no, gcc doesn't know). Or cse's chain wasn't broken.

Hmm, OR: the whole thing is in the frontend: gimple → the "expr" is computed by a gimple stmt `p1 = sp10 + 4`. The address expression `sp10 + 4` is a gimple ADDR_EXPR. In RTL, the local's address is a symbol_ref; the +4 is folded into the symbol's offset. So `sp10 + 4` at RTL = (symbol_ref sp10) with offset 8? In gcc RTL, `symbol_ref` has a frame offset attribute, and pointer arithmetic on a frame address creates (plus (symbol_ref) (const 8)) — but actually for a frame symbol, gcc's `force_const_mem` etc... In modern gcc, the address of a local array element is (plus (symbol_ref arr) (const 8)) where symbol_ref has the frame offset.

Hmm, so at RTL: (plus (symbol_ref sp10) (const 8)). cse: this expression used twice → cse creates a pseudo P. P's value = (plus (symbol_ref sp10)(const 8)). P is an ADDRESS → local-alloc makes it an address GIV, allocated to a callee-saved reg (s0) because it's live across the call.

To get `addiu a0,sp,24` twice, we need P to be rematerialized. §349's trick: make n_times_set > 1 for the *base pointer* pseudo.

Hmm, in our case, the "base" is the frame address — there's no base pseudo.

Hmm, so what if we ADD a base pointer pseudo?
```
u16 *base = sp10;         // base = (symbol_ref sp10)  → 1 set
u16 *p1 = base + 4;       // p1 = (plus (reg base) (const 8)) → base has 1 set...
```
base would be a pseudo holding (symbol_ref sp10) — but since it's a local variable with a constant value, gcc's local-alloc would likely fold base into the constant and use (symbol_ref) directly, or allocate base to a reg.

If base is allocated to a reg r, then p1 = r+8 → the address = (plus (reg r)(const 8)) → reload: r is callee-saved (live across the call) → `addiu a1,r,8` — wrong insn.

Unless base is NOT live across the call: base is used at call1 (a0) and (via p1) at call2 → live across. Hmm.

OK OK. Let me now consider: maybe the real answer involves the fact that the address sp+24 is used in TWO DIFFERENT FUNCTIONS-CALL ARGUMENT POSITIONS, and gcc's "argcopy" / call-clobber logic. Hmm.

Let me try yet another empirical approach: let me look at what OTHER function in the codebase has the same shape and was cracked. E.g., func_801815D4 (the twin) has the same issue.

Hmm, what about searching the repo for an existing lever-free spelling of a similar pattern? Let me look at the T10 shard's `func_80181F4C` example: "pin removed; +1 loop-weighted ref on p via `do { r = p + i; } while (0);`".

Interesting! A `do { } while (0)` trick to add a ref to a pointer! `do { r = p + i; } while (0);` — that adds a use of p.

Hmm! What if adding an extra use of the address expression changes the allocation? Like `do { p1 = sp10 + 4; } while (0);`? no.

Hmm, what about this: the "loop-weighted ref" trick adds a use of `p` in a do-while(0) which makes the ref count higher, changing the birth priority.

Let me think about what would make gcc NOT create a shared pseudo: if the two uses are in DIFFERENT basic blocks with a call between them, cse still unifies.

Hmm, hold on! Let me reconsider: does cse unify across a CALL? YES, cse is global.

OK, let me look at the problem from the "what does the number 120 vs 119 and the diff say" angle and consider: maybe the fix isn't about the address at all — maybe it's about the register allocation choice. What if the address pseudo P is allocated to s0 because s0 is the only free callee-saved reg at that point? In the target, s0 = param_1, s1 = counter, s2 = 25, s3 = 1023. In mine: s1 = param_1, s0 = address P, and the counter reuses s0 later (after P dies).

So in mine, P (the address) took s0 and param_1 took s1. In the target, P doesn't exist, param_1 takes s0 and the counter takes s1.

So if P were eliminated, gcc's allocation would likely be: param_1 → s0, counter → s1. Matching the target.

So the ONE thing to fix: eliminate P (the shared pseudo for sp+24).

Hmm, what if we make the second use of the address NOT a pointer at all — e.g., the second call could take a different but equivalent expression that gcc compiles to `addiu a0,sp,24`?

What compiles to `addiu a0,sp,24`? An address of sp+24. The ways: (a) &array[4], (b) &scalar, (c) pointer arithmetic.

Since (a) and (b) both give the same rtx...

Hmm, WAIT. What about (b) with a **scalar**? Let's reconsider: for a local scalar `u16 w;` at sp+24, `&w` at RTL is (symbol_ref w) with a frame offset. Now, `(symbol_ref w)` and `(plus (symbol_ref sp10) (const 8))` are DIFFERENT rtx! cse won't unify them!

But how do we get a scalar at sp+24 AND the array at sp+16 with the right layout? gcc's stack layout: locals are allocated in some order. We need:
- sp+16: the array's first element (sp10[0])
- sp+18, sp+20: sp10[1], sp10[2]
- sp+24: sp10[4] (a u16)
- sp+26: sp10[5] (a u16)
And the target reads `lhu v0,26(sp)` (sp10[5]) and writes `sh zero,20(sp)`, `sh zero,18(sp)`, `sh zero,16(sp)`.

If instead the C had SIX separate u16 scalars w0..w5 at sp+16..sp+26, then:
- call1: func_800D20C0(&w0, &w4, 1) → a0 = &w0 = (symbol_ref w0) → reload → (plus (reg sp)(const 16)) → `addiu a0,sp,16` ✓; a1 = &w4 = (symbol_ref w4) → `addiu a1,sp,24` ✓
- call2: func_800D23D0(&w4) → &w4 again — SAME rtx → cse unifies → same problem!!

Unless call2 uses a DIFFERENT scalar at the same address — impossible.

Hmm, but WAIT: what if call1's second arg is `&w4` (a scalar) and call2's arg is `sp10 + 4` (an array element)? Then:
- a1 = (symbol_ref w4) → `addiu a1,sp,24`
- a0 = (plus (symbol_ref sp10)(const 8)) → `addiu a0,sp,24`
Different rtx → cse doesn't unify → two separate computations → EXACTLY the target!

But we need both a scalar w4 AND the array sp10[4] at the same address sp+24. In C that's a union:

```
union { u16 a[6]; struct { u16 pad[4]; u16 w4; u16 w5; } s; } u;
```
Hmm, but then &u.s.w4 = (plus (symbol_ref u)(const 8)) and &u.a[4] = (plus (symbol_ref u)(const 8)) — SAME rtx. Because the union member's offset is 0 and the struct field offset is 8. Damn.

To get a different base symbol_ref, we'd need two separate OBJECTS at the same address — impossible in C.

Hmm, hmm. But WAIT: is it really the same rtx? (symbol_ref u) + 8 vs (symbol_ref u) + 8. Yes identical.

What about `&u.s.w4` vs `&u.a[4]` — the difference is only in the *type* (u16 vs u16) and MEM flags. Since we take addresses, the MEM flags don't appear in the address rtx.

OK, so the base symbol must differ. Impossible.

THEREFORE: cse will always unify the two address computations... UNLESS the two uses have different cse-time rtx due to a *pointer variable* in between. E.g.:

```
u16 *base = sp10;         // base = (symbol_ref sp10)
func_800D20C0(sp10, base + 4, 1);   // a1 = (plus (pseudo_base)(const 8))
func_800D23D0(sp10 + 4);            // a0 = (plus (symbol_ref sp10)(const 8))
```
Different rtx! (plus (pseudo_base)(const 8)) vs (plus (symbol_ref sp10)(const 8)). cse won't unify.

But now base must live in a register across the call → base in s0 (callee-saved) → `addiu a1, s0, 8`?? Unless base is rematerialized as (plus (reg sp)(const 16)) and then base+4 folds to (plus (reg sp)(const 24)).

Hmm! Does gcc fold (plus (pseudo_base) (const 8)) where pseudo_base's reg_equiv = (symbol_ref sp10)? At cse time, `lookup_reg(base)` gives (symbol_ref sp10) and simplify_rtx would fold (plus (symbol_ref sp10)(const 8)) → (plus (symbol_ref sp10)(const 8)). Hmm, but the folding happens at RTL generation (expand) time: the gimple `base + 4` where base is a local whose value is a known constant address → gcc's expand would generate a "plus" of the base's RTL. Since base is a local variable (a pseudo), expand generates: base = (symbol_ref sp10) [set], then p = base + 4 → (plus (reg base)(const 8)).

Then cse: `lookup_reg(base)` = (symbol_ref sp10) → but simplify_rtx on (plus (reg base)(const 8)) with base's reg_equiv known → gcc's simplify_rtx does look up reg_equiv for a REG in a plus? I believe `simplify_rtx` calls `lookup_reg` for a REG in some contexts. Actually gcc's simplify_rtx does: for a plus, it tries to fold constants: `simplify_plus` → if one operand is a REG with a known constant value (CONSTANT_P (lookup_reg (reg))), it folds. Yes! `simplify_rtx` for PLUS: "fold_const_initializer... " and there's a step: `if (CONSTANT_P (lookup_reg (reg0)) ...)`. I'm fairly confident gcc folds `plus(reg,const)` when the reg has a constant reg_equiv.

If so, base+4 → (plus (symbol_ref sp10)(const 8)) → and then it becomes IDENTICAL to the second use → cse unifies them → back to square one.

Argh.

BUT: it might not fold if base is not a "constant" pseudo but an ordinary variable. The distinction: gcc tracks "local variables with a constant initializer" as pseudo with reg_equiv CONSTANT. Here base = &sp10, a frame address — that's not a CONSTANT (it's a symbol_ref with a frame offset), but it IS "rematerializable".

Hmm. gcc's `lookup_reg` returns the reg_equiv, and simplify_rtx's plus-folding requires `CONSTANT_P`. A symbol_ref is not CONSTANT_P. So the fold may NOT happen! Then base+4 stays (plus (reg base)(const 8)) → base in a register → `addiu a1,base_reg,8`. That's 1 insn but the wrong form (and base would be sp+16 in a reg).

Hmm, but then reload would need base in a reg → s0 (callee-saved) → conflict again, plus wrong insn.

OK. Time check: I've spent a lot on this. Let me consider the possibility that this item is a WALL and move on, but first let me try a couple of cheap experiments that could crack it:

EXP A: `u16 *p1 = sp10 + 4;` for call1, and for call2 use `&sp10[4]`:
```
p1 = sp10 + 4;
func_800D20C0(sp10, p1, 1);
func_800D23D0(&sp10[4]);
```
Both are the same rtx at RTL → unified. Probably 29. Cheap to test? meh.

EXP B: Make the first call's second arg a *cast pointer*: `(u16 *)((char *)sp10 + 8)`. Same rtx.

EXP C: use `p1` for call2 and `sp10 + 4` for call1 — the ORDER might matter for cse (which occurrence gets the pseudo). If cse creates the pseudo at the FIRST occurrence, then... same.

EXP D: **Make the second call's argument a pointer that was DERIVED from the first call's argument via a genuine reassignment that changes the rtx but keeps the address** — e.g., pass the pointer through a *union* member:
```
union { u16 *p; u16 a[6]; } ...
```
meh.

EXP E: **Use a different function-argument spelling that makes gcc compute the address at the call site as a fresh expression: e.g. make the second call's argument `sp10 + 4` but with sp10 declared as `u16 * const`?** no.

EXP F: **Make the array's address not directly usable: e.g. declare the array inside a struct and access via a pointer**:
```
struct { u16 a[6]; } s;
u16 *base = &s.a[0];
func_800D20C0(base, base + 4, 1);
func_800D23D0(base + 4);
```
Same.

Hmm.

EXP G: **Give the second call a pointer that is loaded from a stack slot but where the slot's value is known**... no.

EXP H: What about making the SECOND use's address come from a **different frame offset expression** that reload turns into the same thing? Like the address of the array END minus 4:
`&sp10[6] - 2` = (plus (symbol_ref sp10)(const 12)) + (-4) = (plus (symbol_ref sp10)(const 8)) — folded at RTL. Same.

I'm now fairly convinced: within one function, two C expressions yielding the same frame address have the same RTL rtx, hence cse unifies them.

UNLESS the base is a *pseudo with a non-constant reg_equiv* (a variable) — then the rtx differs, but then the base needs a register.

Hmm, hold on!! What if the base variable is used ONLY ONCE in each place such that the base itself is rematerialized? Like:

```
u16 *base = sp10;         // base used twice → needs a reg
```

What if we use TWO different base variables?
```
u16 *b1 = sp10;
u16 *b2 = sp10;
func_800D20C0(b1, b1 + 4, 1);
func_800D23D0(b2 + 4);
```
Now b1+4 = (plus (reg b1)(const 8)) and b2+4 = (plus (reg b2)(const 8)) → different rtx → not unified! But b1 and b2 both hold (symbol_ref sp10) and each needs a register live across the call (b1 live at call1, b2 live at call2 — b1 dies at call1! b2 is live across the call at 12? b2 is used at call2 which is after call1 → b2 live across call1 → needs a callee-saved reg → s0 → wrong).

Unless gcc rematerializes b2 = sp+16 as `addiu a2,sp,16`... hmm, that's an extra insn.

Hmm, but actually, wait! What if b1 and b2 are assigned the SAME value and cse unifies THEM (b1 and b2 both = (symbol_ref sp10)) → then b1 and b2 become the same pseudo → then b1+4 and b2+4 are the same rtx → unified. Yeah.

OK. What if b1 and b2 are assigned DIFFERENTLY: b1 = sp10, b2 = &sp10[0]? Same rtx.

I'm stuck on theory. Let me try the empirical route with a few more exotic but cheap candidates, and simultaneously consider that this might be a WALL.

Actually hold on, let me reconsider something! What about the ORDER of the two calls and the fact that `func_800D23D0(sp10 + 4)` is a call whose argument is at sp+24 — while `func_800D20C0(sp10, sp10+4, 1)` is the first call. What if we could make gcc's CSE not apply because the second use is in a different **basic block** after a call, and gcc's cse has a rule that it doesn't create a pseudo for an expression whose uses are separated by a call, when the expression is cheap to recompute?

Actually YES! There IS such a rule in cse! gcc's cse.c has:

```
/* If we are not in a basic block, ... */
...
  /* Don't create a pseudo for an expression that is "cheap" ... */
```
Hmm, I recall in cse.c:
```
	      /* If the expression is a constant, ... */
	      if ( ... CONSTANT_P (newval) ...)
```
and
```
	      /* If this is a constant, ... don't bother creating a reg */
```
And there's `cse->const_cse` and `cse->reg_cse`. Hmm.

But actually the key mechanism might be in local-alloc, not cse: the "address GIV". §349: "RE-ASSIGN A BASE POINTER AT THE END OF THE LOOP BODY to make n_times_set > 1 — that kills both loop.c's INVARIANT HOIST and the ADDRESS GIV, reproducing a REMATERIALISED addiu $aN,$sp,K".

"the ADDRESS GIV": a GIV in local-alloc is a pseudo with a "giv" type (IV of a loop) OR a "address" GIV. Hmm, local-alloc's address GIV: a pseudo whose value is an address and which is used as a base for other address computations.

Hmm OK. Let me look at C0390 (§349) to understand the exact mechanism and adapt it.
