---
ts: 2026-10-22T09:41:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_GE7YlaEhBaAcZEdzJuSy
---
So the substitution I hypothesized (qty_const) is in `set_nonvarying_address_components`, used by refers_to_mem_p — not the actual tree rewrite. So the symbol_ref substitution into the address tree came from elsewhere.

Where else? cse's `fold_rtx` / `simplify_rtx`? Or the front end?

Since the .rtl dump (post-expand) already had the symbol_ref in the plus, the substitution happened at EXPAND time (or in the front end). So expand substituted p's constant value into the address.

In gcc 2.7's expand.c, `expand_expr` case REG:
```c
    case REG:
      ...
      /* If this is a pseudo-register that has a constant value, use it */
```
Hmm, but I recall expand.c has this specific code:

```c
    case REG:
      ...
#ifdef HAVE_cc0
      ...
#endif
      /* Handle the case of a variable that is a constant: this is
	 done by the front end? */
```

Actually! I remember now: gcc's expand.c has a function `expand_expr` with the REG case:

```c
    case REG:
      /* ... */
      if (GET_CODE (x) == REG && ...)
```
and there's `expand_const`? Hmm.

The front end (c-type.c) does the substitution! In c-type.c's `expand_expr` (the C front end's tree expander), a VAR_DECL with a constant initializer might be... no.

Hmm, but our dump's insn 176 `(set (reg/v:SI 112) (symbol_ref D_80195AF6))` shows the assignment was emitted as an insn, so expand DID create the set. And the use at insn 190 used the symbol_ref directly. So expand substituted the constant into the use while still emitting the set (dead code later removed).

In gcc 2.7's expand.c, function `expand_expr`:
```c
    case REG:
      ...
      /* If the variable is a constant, we can use the constant. */
      ...
```
I recall gcc 2.7 expand.c has this in the REG case:

```c
      /* Handle the case of a variable that is a constant: 
	 cse will fold it later, but expand does it now for address arithmetic. */
```

Hmm, actually! I remember: gcc's expand.c has a table `reg_constant`? No, that's cse.

Wait — maybe the substitution is done by the C front end (c-type.c): when a local variable is initialized with a constant and used in an address expression, the front end's `expand_expr` (in c-type.c) may do "fold" the variable → but the front end doesn't do that.

Alternatively, expand.c's `expand_expr` REG case:
```c
    case REG:
      ...
      /* If this is a pseudo reg that is set to a constant, and the
	 constant is used in an address, ... */
```

OK OK. Let me look at the gcc 2.7.2 source for expand.c — we don't have it in tools/reference. Hmm! But we have other gcc copies? tools/reference/gcc-papermario/ — let me check if it has expand.c.
