---
ts: 2026-10-22T09:47:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_ojXK4IFIgRz6IGIwyOEt
---
Interesting: v02 (newval through p) → score 11 (worse). The others stay at 1.

Note v08/v09 ERROR (compile errors) — need fixing (probably the score script's error output; let me check). v08: `u8 *pa = ...` inside a block — maybe "pa" declared after a statement in a block that... it's C89: declarations must come first in a block! The block has statements before → compile error. Right, this project is C89-ish. So I need to declare temps at the top of a block.

v09: `D_80195AF6_t *p;` declared at the top but then `p = D_80195AF6;` — hmm, why an error? Maybe because the decl placement broke something. Let me check the error message.

Anyway: the key finding is that the swap persists across many spellings. The tree at combine time has the symbol as the first operand.

Since combine's simplify_rtx swaps when XEXP(x,0) is a constant, the ONLY way is for the pointer to be a REG in the tree.

Now — why does expand substitute the constant? Let me test the hypothesis that it's expand's "expand_expr REG" case. In gcc 2.7.2's expand.c, I'm now recalling this specific code:

```c
    case REG:
      /* ...
	 If this is a hard register, ...  */
      ...
      /* Handle the case of a variable that is a constant. */
```

Honestly, let me look at the *front end* c-type.c (available in the papermario tree!) — the C front end's expand_expr may substitute constants. Let me grep c-type.c for "TREE_CONSTANT" or "DECL_INITIAL" folding.

Actually! I remember now: gcc 2.7's c-type.c `expand_expr` case VAR_DECL:

```c
    case VAR_DECL:
      ...
      /* Handle the case of a variable that is not initialized... */
      if (TREE_CODE (decl) == VAR_DECL && DECL_INITIAL (decl) && TREE_CONSTANT (decl)) ...
```

Hmm. But there's another classic: gcc's front end "folds" a variable initialized with a constant into its uses when the variable is `const` or when `optimize` is on? I don't think so.

BUT: there IS a known gcc behavior in the front end: `c-type.c`'s `expand_expr` for VAR_DECL:

```c
    case VAR_DECL:
      ...
      /* If the variable is const, and the initializer is a constant,
	 use the constant directly.  */
      if (TREE_CODE (decl) == VAR_DECL
	  && TREE_CODE (DECL_INITIAL (decl)) != ERROR_MARK
	  && ...)
```

Hmm. Let me grep c-type.c for "expand_expr" and the VAR_DECL case.

Actually, better: let me test empirically whether a `const` pointer behaves differently! If gcc substitutes constants for `const` variables, then a non-const variable would stay a reg... but ours is non-const and it WAS substituted.

Hmm, so the substitution isn't from the "const" rule.

Let me look at the front end: grep c-type.c for "ADDR_CONST" / "SYMBOL_REF" folding.

Hmm, time. Let me think about it from the *expand* side instead: maybe the substitution is in expand.c's `expand_expr` case REG, which handles "REG_USERVAR" and the case where the reg is a *pseudo with a constant value*:

In gcc 2.7's expand.c, I DO now clearly recall this block (it's in `expand_expr`, case REG):

```c
    case REG:
      /* ... */
      if (GET_CODE (x) == REG && ...)
```

ARGH.

New idea: let me test whether the substitution depends on the *number of uses* by checking v02's dump (newval through p → p has 2 uses). In v02, the score was 11, meaning the asm differs a lot — but does the final add become pointer-first? Let me check v02's diff! If the final add is now "addu v0,a1,v0" (pointer first), then the 2-uses hypothesis is confirmed, and I can then think about how to get 2 uses without changing the rest.

Let me run dt.sh on v02 tosee the diff.
