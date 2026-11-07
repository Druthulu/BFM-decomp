---
ts: 2026-11-06T11:45:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ldx8aFNeLVMykytGM22G
---
exp_equiv_p uses rtx_equal_p for MEM (falls through to the generic loop that compares elements and flags?). The generic code compares `GET_MODE`, then for each operand, and also checks `MEM_VOLATILE_P`? Actually the generic loop in exp_equiv_p compares subexpressions but not rtx flags. So MEM_IN_STRUCT isn't compared → the struct-member load and the plain load ARE equivalent.

Hmm, but wait: `rtx_equal_p` for MEM does compare... in gcc 2.7.2's rtl.c:
```
case MEM:
  return (rtx_equal_p (XEXP (x, 0), XEXP (y, 0))
          && (MEM_ALIAS_SET...))  // no alias sets in 2.7.2
```
Probably just the address. So same.

OK so the struct trick doesn't split the loads by equality. But it does matter for invalidation.

Hmm. Let me reconsider.

What about the pin `$3` on bb? The target's first load is into v1 = $3. After the load, the value is in a hard reg. The second read is in a1. If cse forwards, it would use v1.

Wait — maybe the target's structure is different: maybe the *second* read is not a reload of `bb` but of a *different expression*: the C could be
```
sVar4 = ratan2((bb & 0xFF) - 0x80, 0x80 - (bb >> 8));
```
which would reuse bb (v1) → 1 load. The target reloads, so the original C had `*(u16*)(p+0xAE)` again.

Hmm OK. Let me look at this from the perspective: what C produces a memory clobber without emitting code? 

IDEA: A call to a function that the compiler turns into nothing? No.

IDEA: An assignment to a *global* that flow deletes? flow doesn't delete global stores.

IDEA: An assignment to a local that cse deletes because... hmm.

Wait, actually, let me reconsider: does cse delete a store whose value is already in memory? Let me search cse.c for the store-elimination code. Search for "SET_DEST (sets[i].rtl)" near the deletion decision, or "this is a store to a memory location whose value is already known".

Let me grep for "already" or "delete_insn" in cse.c.
