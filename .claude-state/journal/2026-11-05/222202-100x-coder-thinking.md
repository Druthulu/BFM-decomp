---
ts: 2026-11-06T05:22:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_phxUpDHGp90FiFKme533
---
The function is inlined at 3 sites (3 includers?). The dumps are per-pass snapshots.

This is taking too long. Let me step back and think about the *mechanism* differently.

The stores are removed because the compiler proves they're dead. In gcc 2.7.2, the pass that removes a dead store to a stack slot: `flow.c`'s `insn_dead_p`:

```
/* Return 1 if the value of the SET in PATTERN is dead... */
static int
insn_dead_p (pattern, regs_live, call_ok)
{
  ...
  if (GET_CODE (x) == SET)
    {
      ...
      if (GET_CODE (SET_DEST (x)) == MEM)
	{
	  /* ... */
	}
    }
}
```

Let me read flow.c around 940-1020.
