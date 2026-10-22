---
ts: 2026-10-22T11:47:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_Bo6ktEGnw7eJC3Mnhk7i
---
expr.c doesn't have the division-by-constant expansion. It's in `expand_expr` in expr.c for TRUNC_DIV_EXPR. Let me grep for "TRUNC_DIV_EXPR" in expr.c and look at the division case.

Actually, GCC 2.7's `expand_expr` handles TRUNC_DIV_EXPR:
```c
    case TRUNC_DIV_EXPR:
    case TRUNC_MOD_EXPR:
      ...
      /* If we are dividing by a power of two, ... */
      ...
      else if (... constant divisor ...)
	{
	  /* Use the multiply-by-magic algorithm. */
	  ...
	}
```

Let me grep.
