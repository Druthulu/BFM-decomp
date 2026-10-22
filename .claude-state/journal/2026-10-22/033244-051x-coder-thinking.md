---
ts: 2026-10-22T09:32:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_8so2E5SfsmvhERUzBz0d
---
Not it. Time to be pragmatic: the gcc source is available, but finding the exact rule by grep may take a while. Let me instead do a targeted experiment in the REAL body — try spellings and see which yields "addu v0,a1,v0".

Key insight to exploit: the target's tree had the pointer in a REG. So I need to prevent expand from substituting the constant into the address.

How does expand substitute? Let me check expand.c in the reference tree: look for where a pseudo's constant value replaces a use. In gcc 2.7.2's expand.c there's `expand_expr` case REG:

Let me grep expand.c for "reg_constant" or "CONSTANT_P" in the REG case.

Actually — I recall in gcc 2.7 expand.c:

```c
    case REG:
      /* ... */
      if (GET_CODE (x) == REG && REGNO (x) >= FIRST_PSEUDO_REGISTER ...)
	{
	  rtx reg = ...
	  /* If the variable is a constant, substitute it. */
	  ...
	}
```
Hmm, there's `expand_expr`'s handling using `cse`? no.

Let me grep expand.c for "REG_EQUAL" or "reg_equiv".

Actually, in gcc 2.7, expand.c's `expand_expr` REG case has this code:

```c
    case REG:
      /* ...
	 If this is a hard register, ...  */
      ...
      /* If we have a variable that is a constant, ... */
```

Let me just grep expand.c for "constant" near "REG".

Alternatively — the substitution might be done by expand's `expand_assignment` when the pseudo is assigned a constant and used once: gcc 2.7 expand.c has the "expand_const" hmm.

Let me grep expand.c for "SUBST" with "reg_constant".

Actually, I recall in gcc 2.7.2 expand.c there's:

```c
/* Return the reg for the local variable... */
```
and in `expand_expr`:
```c
    case REG:
      ...
#ifdef HAVE_cc0
      ...
#endif
      /* Handle the case of a variable that is not a register... */
```

OK, let me grep for the specific mechanism: `reg_constant` is in cse.c. `expand` doesn't have it. But there's `expand_expr`'s case REG with:

```c
	  /* If this is a pseudo-register that is set to a constant,
	     and the constant is not a valid address... */
```

Let's grep expand.c for "CONSTANT_P".
