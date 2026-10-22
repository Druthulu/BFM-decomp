---
ts: 2026-10-22T10:08:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_MG7qpHQyCA34VoVoSB9u
---
The loop tail:
```
325c: lhu  v0,0(s0)      ; *p
3260: addiu s1,s1,1      ; i++
3264: addu  v0,v0,v1     ; + D_801E86C0
3268: addiu v1,v1,1      ; c0+1
326c: sh   v0,0(s0)      ; *p = *p + c0
3270: slti v0,s1,4
3274: lui at; 3278: sw v1,0(at)   ; D_801E86C0 = c0+1
327c: bnez v0,3180
```
So the store is through s0 — p is not bumped. Our source matches this (`*p = *p + c0`).

So p has ONE set in the target too. Hmm! Then why does the target have the copy?

Hmm, so the "second set kills the fold" theory doesn't apply (the target has one set).

So in the target, the copy "move s0,v0" comes from a *different* source pseudo. And in the target, that source pseudo (v0) has ONE set (the symbol) and one use (the copy to s0).

In OUR compile, the copy is folded at expand.

Hmm! So the difference is at expand/front-end level. Let me now find where. Since the .rtl dump of x3 (pb temp + p = pb) showed only ONE set insn (to reg 81 = p), the fold happened before/at expand.

In gcc 2.7, the front end's `expand_expr` (c-type.c) for a VAR_DECL: I'm now quite sure there's this code in c-type.c (gcc 2.7):

```c
    case VAR_DECL:
      ...
      /* If the variable is a local variable with a constant value,
	 and the value is not address-taken, then use the constant
	 directly.  */
      if (TREE_CODE (decl) == VAR_DECL
	  && ! DECL_ADDRESS_TAKEN (decl)
	  && DECL_INITIAL (decl)
	  && TREE_CODE (DECL_INITIAL (decl)) == ADDR_CONST)   /* ??? */
```

Hmm, actually I remember a specific gcc 2.x behavior: "a variable initialized with a constant is not kept in memory; the initializer is expanded at each use" — that's the standard.

Hmm, but then the RTL would have TWO sets (one for pb, one for p) — unless expand decided to expand pb's initializer directly into the use (i.e. it didn't create a pseudo for pb at all).

Right: in gcc, a local variable with a constant initializer that's used once: expand creates the set insn for the variable's pseudo... hmm, but the dump shows only one set.

Hmm, unless the front end's expand_expr for the USE of pb returned the constant directly (no pseudo). That's the front end's "fold a variable with a constant initializer into its uses" behavior.

In gcc 2.7's c-type.c, `expand_expr` case VAR_DECL:

```c
    case VAR_DECL:
      ...
      /* If the variable is `const' and its value is a constant, 
	 use the constant. */
```
Hmm, requires const.

OK, let me test the `const` hypothesis for THIS item: `u16 * const pb = &D_800B99DC; p = pb;` — if the front end folds const vars into uses, then a const pb would be folded (same as now), and a NON-const pb would NOT be folded... but our x3 (non-const pb) WAS folded. Hmm, so the fold isn't the const rule.

Hmm!! Wait. Maybe the fold is at the level of gcc's `expand_assign`/`expand_expr` where a *pointer-typed* variable initialized with an ADDR_CONST gets the constant.

Hmm, let me look at the papermario c-decl.c for the front end's handling of initializers... hmm, c-decl.c is the declaration parser.

You know what? There's a much better empirical approach: TEST whether the fold happens for OTHER kinds of initializers. E.g.:
- `u16 *pb = &D_800B99DC;` → folded (x3).
- What if pb's initializer is a *cast*: `u16 *pb = (u16 *)&D_800B99DC;`?
- What if pb is initialized with an *array element address*: `u16 *pb = &D_800B99DC[0];`?
- What if pb's type is `void *`?
- What if pb is initialized with a *function pointer cast*?

Since the front end's ADDR_CONST is the key, all of these fold.

The escape might be: an initializer that is NOT TREE_CONSTANT, e.g. `u16 *pb = (u16 *)(u32)&D_800B99DC;` — if the front end folds (CAST (CAST (ADDR_CONST))) to ADDR_CONST, no escape.

Hmm, what about an initializer that's a *PLUS of an ADDR_CONST and a variable*: `u16 *pb = (u16 *)((u8 *)&D_800B99DC + 0);` — fold → ADDR_CONST.

What about `u16 *pb = (u16 *)((u8 *)&D_800B99DC + (0 & some_var));` — hmm, "0 & x" folds to 0.

What about a genuinely non-constant expression that always yields the same value at runtime? E.g. `u16 *pb = (u16 *)((u8 *)&D_800B99DC + (D_801E86BC - D_801E86BC));` — hmm, the subtraction of a global from itself is not folded by gcc (it's a load-load) → the value is runtime-computed but always 0! But that adds 2 loads → the asm changes ✗.

Hmm, but wait: `D_801E86BC - D_801E86BC` → gcc 2.7 would emit two loads and a subu (or one load if CSE'd) → 2-3 extra insns ✗.

OK so for 8018483C: the copy cannot be produced lever-free. It's a genuine wall. The previous agent's tag: "cse-const-addr-copy".

Hmm, but hold on. Let me reconsider one thing: what if the copy is not needed because the target's pointer p was assigned a value that is NOT the constant but came from a *register* — e.g. the original source had the pointer in a variable that was assigned from a *table lookup*? The asm materializes the constant → no.

Alright: WALL for 8018483C, best 5 (v9 has 115 insns; x1 has 114). Hmm, "best = lowest score of a lever-free body" → 5 (both x1 and v9 are 5).

Hmm, wait. But hold on: the score counts *mismatching instructions*. v9 has 115 insns (matching count) but 5 differ. x1 has 114 and 5 differ. Both 5.

OK. Now let me consider: is there any chance the "copy" could come from the *loop* structure? The notes mention "loop.md L4 preheader-copy". Let me look at loop.c's L4 to see when loop.c copies a value in the preheader. If loop.c copies the pointer into a register for the loop, maybe a different loop shape would produce the copy.

Let me grep loop.c for "preheader" and the copy logic.
