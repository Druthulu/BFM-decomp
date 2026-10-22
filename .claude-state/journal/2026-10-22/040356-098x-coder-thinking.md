---
ts: 2026-10-22T10:03:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_oDvE7tUl8juK94kx8Pw7
---
In the .rtl dump (post-expand) there's only ONE insn with D_800B99DC: `(set (reg/v:SI 81) (symbol_ref D_800B99DC))` — so the copy `p = pb` was ALREADY folded at expand time! The pseudo 81 is p itself (the set's dest).

So expand folded the copy: the front end/expand assigned the constant directly to p.

So the "pb temp + p = pb" never existed in the RTL. Interesting: so the front end (or expand) merged the two variables.

Hmm! So the fold is at the front-end/expand level: `u16 *pb = &D_800B99DC; p = pb;` → expand sees pb's value is a constant and substitutes.

Now: how do we get a REAL copy in the RTL? We need the RTL to be `(set (reg a) (symbol_ref))` + `(set (reg b) (reg a))`.

That requires the front end to NOT substitute. When does gcc's front end/expand substitute a variable's constant value into a use? This is gcc's "expand_expr: VAR_DECL with a constant initializer" — hmm.

AH WAIT. I bet it's this: gcc's front end (c-decl.c / c-typeck.c) creates the local variable pb with DECL_INITIAL = &D_800B99DC. Then `expand_start_stmt`/the assignment `p = pb` → expand_expr(pb) → the front end's expand_expr for a VAR_DECL with a constant initializer returns the CONSTANT tree (not a variable reference) — that's the front end's "expand_expr" in c-type.c:

```c
    case VAR_DECL:
      ...
      /* If the variable is a local variable with a constant initializer and
	 it is not modified, use the constant directly.  */
```
Hmm, in gcc 2.7's c-type.c there IS such code:

```c
    case VAR_DECL:
      ...
      if (TREE_CODE (decl) == VAR_DECL && TREE_CODE (decl) != ... )
```

Let me grep the papermario c-decl.c / c-typeck.c for this. Actually, the relevant front-end code is in c-type.c which we lack. But c-decl.c might have it. Let me grep c-decl.c for "DECL_INITIAL" + "constant".

Hmm, but the papermario tree is a different gcc version. Let's check c-typeck.c or c-decl.c for a "fold a variable initialized with a constant" rule.

Actually! I recall in gcc's c-decl.c, function `expand_start_stmt`... no. Hmm, in gcc 2.7's c-type.c:

```c
    case VAR_DECL:
      ...
      /* Handle the case of a variable that is not initialized... */
      ...
      /* If the variable is const and the initializer is a constant, 
	 use the constant.  */
      if (TREE_CODE (decl) == VAR_DECL
	  && TREE_READONLY (decl) ...
```
Hmm, that requires `const`.

But our test v64_const_p (item 80184828) had a const pointer and it still folded.

Hmm! Let me look at this from a different angle: what if the fold is done by gcc's *front end* "c-decl.c: expand_decl → the variable is put in the DECL_RTL as a constant"? Hmm.

Actually — I remember now! It's in gcc 2.7's c-type.c `expand_expr` case VAR_DECL:

```c
    case VAR_DECL:
      ...
      /* Handle the case of a variable that is a "constant" ... */
      ...
      if (DECL_RTL (decl) == 0) ...
```

Hmm.

Let me try the practical route: find a C spelling where the copy survives. The copy survives if the source expression is NOT a compile-time constant from the front end's perspective. E.g.:

- If the address is obtained via a *cast through an integer*: `p = (u16 *)(s32)&D_800B99DC;` → the front end's tree is (CAST (ADDR_CONST ...)) → hmm, the front end would fold the cast of an ADDR_CONST to an ADDR_CONST? v12 tried it → 5 (folded).

- If the address is the result of `+ 0`: folded.

- If the address is loaded from a *const global pointer*: no such global.

- If the address comes from a *function parameter*: the signature is fixed (a0 is s32).

- If the pointer is *assigned in a loop*? no.

- What if p is assigned the address and the assignment is *conditional*: `if (cond) p = &D_800B99DC;` → the front end emits a branch and the set is in a block; the value would still be a constant → folded into the reg_equiv.

Hmm, so the front end's constant folding of the initializer is the wall.

Hmm, BUT: what if the variable's initializer is NOT a constant *tree* but a *runtime* expression that gcc can't fold, yet yields the same value? For example:

```c
    u16 *pb = (u16 *)((s32)&D_800B99DC + 0);
```
folded.

What about:
```c
    u16 *pb = &D_800B99DC[0];
```
folded.

What about a pointer obtained from a *cast of an int variable*:
```c
    s32 tmp = (s32)&D_800B99DC;   /* the front end folds this to ADDR_CONST */
```
folded.

Hmm, what if the value comes from a *global variable* that holds the address? Let me check: is there a global in the project like `D_800B99DC_ptr`? Unlikely.

Hmm, what about the address of the symbol being computed as `&D_800B99DC` where D_800B99DC is declared as an ARRAY — the front end's ADDR_CONST. Yes.

OK so within this item, the lever-free route seems blocked by the front end's constant folding.

BUT WAIT: what about the *asm-level* copy from a different angle: the target's "move s0,v0" — what if the ORIGINAL source had the pointer value in a variable that was live across a call AND ALSO used in a caller-saved context?

Hmm, hmm. Let me look at the target's asm ONE more time for the region 3138-3160 and think about which source construct yields it:

```
3138: move s1,zero        ; s1 = 0
313c: lui s3 ; addiu s3   ; q = &D_801E87B2  → s3 directly
3144: lui v0 ; addiu v0   ; ??? → v0
314c: move s0,v0           ; p = v0
3150: lui s2 ; addiu s2   ; r = &D_8018F078 → s2 directly
```

Hmm! What if the "lui v0; addiu v0; move s0,v0" is NOT the pointer p but something else, and p is materialized elsewhere? Let's see: the next use is "lhu v0,0(s0)" — so s0 is the pointer ✓ and v0 is a temp.

So the pointer's value was computed into v0 (caller-saved) and copied to s0.

In gcc, when does a *constant* get materialized into a caller-saved reg and then copied to a callee-saved reg? When the RTL is `(set (reg s0) (reg v0))` where v0 holds the constant. As established, the front end must produce two variables.

Since the front end folds `pb` (constant-initialized) into the use, the copy vanishes. UNLESS the front end does NOT fold when the variable is *address-taken* or when the variable's declaration has a *different* type...

Hmm! IDEA: what if pb is declared as `void *pb = (void *)&D_800B99DC;` and then `p = (u16 *)pb;`? The front end's fold of a VAR_DECL use gives the constant (an ADDR_CONST) — the cast then yields the same constant. Folded.

IDEA: what if the intermediate variable is a *global* (static)? `static u16 *pb = &D_800B99DC;` → then pb is in memory → "lw" → different asm ✗.

IDEA: what if the intermediate is an *array element* or a struct field of a local? → memory ✗.

IDEA: what if the *type* of the intermediate is such that the front end keeps it in a reg: e.g. `u32 pb = (u32)&D_800B99DC;`? The front end folds.

Hmm, so it seems the front end ALWAYS folds a constant-initialized local's uses. Let me verify that claim: is that really gcc's behavior? In gcc 2.7, `int x = 5; return x;` → gcc generates "li v0,5" — the value is materialized where used. That's normal. But does it fold the *variable* away (making the copy disappear)? In our case, `p = pb` where pb is a u16* — the copy disappears, meaning the front end substituted the constant into the assignment.

Hmm, actually maybe the copy disappears at EXPAND, not the front end: expand's `expand_expr` for the RHS `pb` — the front end's tree for pb is a VAR_DECL; expand creates a pseudo and a set insn; then the assignment `p = pb` becomes `(set (reg p) (reg pb))`. Then... the .rtl dump shows only ONE set (to reg 81). So either the front end substituted, or expand did.

In gcc 2.7's expand.c, there IS this in expand_expr (case VAR_DECL / REG): "if the variable's value is a constant (as known by the front end's DECL_INITIAL), use the constant directly". I'm fairly confident gcc 2.7's expand.c has:

```c
    case VAR_DECL:
      ...
      /* If the variable is a local variable with a constant value and
	 the value is not address-taken, use the constant.  */
```

Hmm, alternatively it's in the front end's c-type.c `expand_expr` case VAR_DECL:

```c
    case VAR_DECL:
      ...
      /* If the variable's initializer is a constant and the variable
	 is not address-taken, use the constant value. */
      if (TREE_CODE (decl) == VAR_DECL && DECL_INITIAL(decl) && TREE_CONSTANT (DECL_INITIAL(decl)) && ! DECL_ADDRESS_TAKEN(decl))
	  return DECL_INITIAL (decl) ...
```

That's plausible for gcc 2.7! And the escape: make the variable's address taken? Then it'd be in memory ✗.

Hmm, what about a variable whose initializer is a constant but whose *type* forces a conversion? e.g. `u16 *pb = (u16 *)&D_800B99DC;` — the initializer is a CAST tree, not TREE_CONSTANT → maybe not folded!! Then expand would create a pseudo pb, set it to the cast... and the cast of an ADDR_CONST is folded by the front end into an ADDR_CONST? Hmm, in the front end, `fold` would simplify (CAST (ADDR_CONST x)) → (ADDR_CONST x) since the types are pointers. Yes, fold does that.

But what about a cast that is NOT foldable, e.g. casting to a different-sized integer then back? E.g. `u16 *pb = (u16 *)(s32)&D_800B99DC;` — fold: (CAST (CAST (ADDR_CONST))) → hmm, in gcc 2.7, casting a pointer to an integer gives (CAST (ADDR_CONST)) with the integer type; folding that to an integer constant is not allowed (the address isn't a compile-time integer in gcc 2.7's constant folding — ADDR_CONST can only be folded to an integer in some contexts... gcc 2.7's fold does fold ADDR_CONST to an INTEGER_CST when the type is an integer! (That's how `(s32)&x` works.) So (CAST (ADDR_CONST)) → INTEGER_CST (the address as a number!) — then `(u16 *)(INTEGER_CST)` → the constant address again.

Hmm, but the notes' v12 tried exactly that and it was "folded" ✓ consistent.

OK. So what C construct makes the front end NOT fold the initializer into a use, while gcc still materializes the constant address?

What if the initializer is a constant but the variable is *modified* somewhere (so the front end can't assume its value)? E.g.:
```c
    u16 *pb = &D_800B99DC;
    ...
    p = pb;
```
with pb modified in between? That changes semantics.

What if pb's declaration has an initializer that is a constant but the variable is a *parameter-like*...

Hmm, what about `volatile`? Not allowed (lever).

What if the copy source is a *function call result*? no.

Hmm, what about the *order*: `p = pb;` where pb is declared LATER (C89 requires declaration before use) — no.

What if pb is declared with the initializer in a *different scope* than the use? E.g.:
```c
    {
        u16 *pb = &D_800B99DC;
        p = pb;
    }
```
That's the orig's structure (x3) → folded.

Hmm, what if the assignment is inside a nested block and the use of p is outside? Same.

OK, radical: maybe the copy can be produced by a *different* mechanism: what if p is assigned the address and ALSO the address is used somewhere else (so the constant is materialized once into a caller-saved reg and copied)? Hmm: if the address is used in two places, gcc materializes it... hmm, no: each use would materialize its own copy (or the same reg if live).

Wait! That's an idea: what if the *load* `*p` uses the address directly (not through p)? Hmm, v09 did that: `D_801E86BC = (*(u16 *)&D_800B99DC & 1) + 3;` → the load's base was v0 and the count matched (115). In v09, the materialization was "lui s0; addiu s0" (into s0) and the load "lhu v0,0(v0)".

Hmm, so in v09 the address was materialized into s0 (because p = the address, and p is live across calls) and the direct load used a separate copy in v0.

What if we swap: the load uses p (s0) and the *other* use is direct? That's the base version.

Hmm, so what we want is: the address materialized into v0 (a temp) and copied to s0, with the loads using s0.

That means: the pseudo holding the constant is a *caller-saved* temp (v0) with a copy to s0. For gcc to do this, the pseudo holding the constant must be short-lived (not live across calls) — i.e. the *variable* pb is used only before the calls, and p (the copy) is what's live across calls.

But in our source, the copy `p = pb` is folded, so pb's pseudo disappears.

Hmm, what if pb is used ONCE but the copy is NOT folded because the copy is to a DIFFERENT MODE? E.g. `p = (u16 *)pb;` where pb is `void *`? Hmm, the modes are all 32-bit.

Hmm, what if the copy is to a *hard register* — e.g. if p were declared `register u16 *p;` — not allowed.

OK — what about this: the front end folds the initializer only when the variable's DECL_INITIAL is TREE_CONSTANT. What if the initializer is a constant *expression* involving a cast that fold can't simplify — e.g. `(u16 *)((u32)&D_800B99DC)`: fold would simplify the double cast → ADDR_CONST. Hmm.

What about a *pointer difference* or an *offset*: `(u16 *)((u8 *)&D_800B99DC + 0)` → fold → ADDR_CONST.

What about `&D_800B99DC[0]`? → ADDR_CONST.

What about a *conditional expression*: `1 ? &D_800B99DC : &D_800B99DC` → fold → ADDR_CONST.

Hmm, what about `(u16 *)(u32)(u32)&D_800B99DC`? same.

What about a *volatile* read of a constant global pointer — no.

Hmm, what about `&D_800B99DC` where D_800B99DC is declared as `extern u16 D_800B99DC[]` — the ADDR_CONST.

So the front end will always produce ADDR_CONST → folded.

CONCLUSION for item 8018483C: the copy "move s0,v0" cannot be produced lever-free, because the front end folds any constant-address initializer into its use. The only way to keep the intermediate pseudo is a lever (asm) or an identity statement (not allowed).

Hmm, wait. Actually — hold on! What about the possibility that the intermediate variable is *not* a pointer but the address is computed by an expression that yields a REG at runtime: e.g. the address of a *local variable*? No, it must be &D_800B99DC.

Hmm, what about `p = (u16 *)&D_800B99DC;` where the cast makes the front end NOT fold but expand materializes it? Let me test a few cast variants to see if any produces the copy:
- `p = (u16 *)(s32)&D_800B99DC;` (v12 → folded)
- `p = (u16 *)&((u16 *)&D_800B99DC)[0];`
- `p = (u16 *)(u32)(void *)&D_800B99DC;`
- `p = (u16 *)((s32)&D_800B99DC + 0);`
- `p = *(u16 **)&D_800B99DC;`?? — WRONG semantics (reads the memory at that address) ✗.

Hmm, what about the reverse: make p's *use* the folded one and the *variable* the copy? I.e., what if the source is:
```c
    u16 *pb = &D_800B99DC;
    p = pb;
```
where pb's use is folded. What if instead:
```c
    p = &D_800B99DC;
    u16 *pb = p;      /* copy the other way */
```
Then pb = p is folded too.

What if the copy is between two variables where the SOURCE is not constant but the DEST is used in the loads? E.g.:
```c
    u16 *pb;          /* uninitialized */
    pb = &D_800B99DC; /* folded */
```

Hmm.

What if the value is copied through a *struct* (local struct field)? → memory ✗.

What about copying through a *pointer dereference*: `*(u16 **)&p = &D_800B99DC;`? That stores to the stack → extra insns ✗.

Hmm, what about the trick where the value is in a *register* because of an arithmetic op: `p = (u16 *)((u32)&D_800B99DC + 0)` → the front end folds the +0.

What about `p = (u16 *)((u32)&D_800B99DC | 0)` → folds.

What about a *non-constant* mask: `p = (u16 *)((u32)&D_800B99DC & 0xFFFFFFFF)` → folds.

Hmm.

What about the possibility that the copy is not of the pointer but of something else entirely, and p is materialized directly into s0? Let's compare the target and our asm around there:
target: lui v0; addiu v0; move s0,v0; lui s2; addiu s2; lhu v0,0(s0)
ours:  lui s0; addiu s0; ... (and the "lui v0" for the direct load in v09)

Hmm, in the target, is there any OTHER lui/addiu pair that we're missing? The score is 5: the diff showed mine[17:19] vs target[17:20] (the extra move) and mine[21:23] vs target[22:23] (the load base). So the target has 115 insns and ours 115 — the counts match! So the target's extra "move s0,v0" is compensated by something else in ours.

Interesting: in the target, the materialization of &D_800B99DC is "lui v0; addiu v0; move s0,v0" (3 insns) vs ours "lui s0; addiu s0" (2 insns) — but the counts match, so elsewhere ours has an extra insn (e.g. ours has "lui v0; addiu v0" for the direct load — in the base version, p is used for the load, so no).

Let me look at the actual diff of the base candidate (x1 = `p = &D_800B99DC;`) to see all 5 differences.

Let me run the detailed diff on x1.
