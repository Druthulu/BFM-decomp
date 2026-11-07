---
ts: 2026-11-06T16:37:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_jqun2POsM7nJB0QNssBO
---
No rtl.c. The semantics: rtx_renumbered_equal_p compares registers by "renumbered" equality: REGNO is ignored? In GCC 2.7.2, rtx_renumbered_equal_p compares regs by their "renumbered" value — I recall it treats REG as equal if both are registers and their "renumbered" versions match (it uses REGNO for hard regs and maybe the same). Let me check the actual source in the tree: it's in rtlanal.c? not present. Hmm, only a subset of files.

In GCC 2.7.2, rtx_renumbered_equal_p is defined in rtl.c:
```
int
rtx_renumbered_equal_p (x, y)
...
case REG:
  return ((REGNO (x) == REGNO (y) || ...) && ...)
```
Actually I recall:
```
    case REG:
      /* If the register numbers are different, ... */
      return (REGNO (x) == REGNO (y)
	      && (REGNO (x) >= FIRST_PSEUDO_REGISTER ...));
```
Hmm. Let me search the reference tree more broadly.
