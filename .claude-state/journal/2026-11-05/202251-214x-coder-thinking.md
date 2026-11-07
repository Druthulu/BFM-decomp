---
ts: 2026-11-06T03:22:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_qjCdOgcdonIvJ6dSxcvt
---
The struct store is `mem/s:HI` (in-struct) at insn 18/23 (via reg 69 = obj). Yet cse still forwarded the global (2 refs after cse). So cse's alias analysis did NOT invalidate the fixed scalar D_80126B78 on a varying in-struct store? Let me check cse.c's `fixed_scalar_and_varying_struct_p` semantics:

```
/* Return 1 if X and Y are mems that are fixed scalar / varying struct... */
static int
fixed_scalar_and_varying_struct_p (mem1, mem2, varies)
{
  ...
  return ((MEM_IN_STRUCT_P (mem1) && !MEM_IN_STRUCT_P (mem2)
           && varies (XEXP (mem2, 0)))
          || (MEM_IN_STRUCT_P (mem2) && !MEM_IN_STRUCT_P (mem1)
              && varies (XEXP (mem1, 0))));
}
```
And in cse.c, `invalidate_memory` uses:
```
if (write_dependence_p (mem, x, ...))
```
Hmm. Let me look at cse.c's store handling. Search "invalidate" in cse.c.
