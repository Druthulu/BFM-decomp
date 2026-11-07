---
ts: 2026-11-06T05:28:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_DUCURv1ULlwdV6j3i1UM
---
Even an intermediate store to a different location doesn't change the count (42). So the deletion isn't "the second store is redundant because the memory value is unchanged" — because an intermediate store to b[1] would change b[1]'s memory, not b[0]'s.

Hmm, e1 inserts `b[1] = (s16)u88;` — that doesn't touch b[0]. So b[0]'s value is still t; the second b[0]=t is still redundant.

e4 inserts a global store — should invalidate all memory (different symbol, but cse's alias...). Still 42.

Hmm, so the deletion of the duplicate store isn't prevented by a memory store. Then how did the barrier prevent it? The barrier is an asm memory clobber, which cse treats specially (invalidate everything).

Hmm, wait — maybe the deletion is not by cse but by **combine** or the **dbr/reorg**. Or maybe it's `loop.c`? No loops.

Let me check: maybe the deletion is at the **RTL expansion** stage: the compiler sees `b[0] = t; ... b[0] = t;` and the *front-end* (or `expand_expr`) ... no.

Hold on — maybe it's **cse2** (after loop). Or **flow** (the second flow pass after cse). flow's dead-store: for sp stores, last_mem_set is not set. Hmm.

Wait, let me re-read line 1964-1974:

```c
if (GET_CODE (reg) == MEM
    || (GET_CODE (reg) == REG && last_mem_set != 0 && reg_overlap_mentioned_p (reg, last_mem_set)))
  last_mem_set = 0;

if (GET_CODE (reg) == MEM && ! side_effects_p (reg)
    && ! reg_mentioned_p (stack_pointer_rtx, reg))
  last_mem_set = reg;
```

For a store to `(mem (plus (reg sp) 24))`: line 1964 clears last_mem_set; line 1969 fails (mentions sp) → not set. So last_mem_set = 0.

Then `insn_dead_p` line 1726: `GET_CODE(r)==MEM && last_mem_set && ...` → last_mem_set is 0 → not dead. So flow doesn't delete sp stores.

Unless the b array is accessed through a *frame pointer* register (not sp)! In the target's code, the stores are `sh X,24(sp)` — using sp. So reg_mentioned_p(sp) is true → not deleted by flow.

Hmm, so who deletes them? Let me check `combine`: it can combine two stores? No.

Maybe **`cse`** deletes a store when it's redundant: in cse_insn, after processing the sets, there's logic:

```
/* If this is a store into memory and the value stored is the same as
   the value already there, delete the store. */
```

Let me grep for "delete" near "dest" in cse_insn... Let me look at cse.c line 7113 area.

Actually, let me test empirically which pass: compile v1 with a flag to disable cse? Can't change flags.

Alternative: look at the dump files. Let me count the number of `(set (mem:HI ... (const_int 24)` insns in the flow and cse dumps for our function. The dump format: I need to find our function's region. Let me search for the insn pattern `(mem:HI (plus:SI (reg:SI` and `const_int 24` together.

Hmm, the dumps have multiple functions. Let me extract the function's dump section by searching for a unique marker. The dump lines for our function would reference the header file. 

Let me try: grep -n "const_int 24" in the .flow dump and look at the context. Earlier the grep found 299 occurrences (all functions). Let me narrow by searching for `(insn` lines with `(mem:HI (plus:SI (reg:SI 29)` — the register might be 29 (sp) or a pseudo.

Actually, at the flow pass, the stack address is `(plus:SI (reg:SI 29) (const_int 24))` where 29 = sp. Let me grep for that exact pattern.
