---
ts: 2026-11-06T05:26:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_eoCFkv6zN54KnDOqrmwi
---
Key line 1969-1974:

```c
if (GET_CODE (reg) == MEM && ! side_effects_p (reg)
    && ! reg_mentioned_p (stack_pointer_rtx, reg))
  last_mem_set = reg;
```

So `last_mem_set` is NOT set for stores through the stack pointer (`reg_mentioned_p (stack_pointer_rtx, reg)`)! The b array is at `(plus (reg sp) 24)` — it mentions the stack pointer → last_mem_set is NOT set. And at line 1964: `if (GET_CODE (reg) == MEM ...) last_mem_set = 0;` — every memory store clears last_mem_set, then the stack-pointer store doesn't set it.

So for stack slots, last_mem_set stays 0 → `insn_dead_p` line 1726 returns false → the store is NOT deleted by flow!

Hmm! So the deletion isn't in flow either. Then where?

Wait, but this explains why the stores are deleted: maybe they're deleted by **`reorg`** or **`dbr`**? No.

Let me reconsider. Maybe the deletion is in the *initial* expand: the front-end/expand may remove redundant stores? No.

Hmm, maybe the stores aren't deleted at all — maybe they're **merged by cse into a single store**? No, different values.

Let me look at the actual candidate disassembly again for item 3 and count the sh stores. Let me dump the candidate object and compare with the target in detail. Maybe the 3-insn difference is something else entirely (not dead stores).

Earlier diff:
```
replace mine[21:26] target[21:29]
   21  subu a1,a1,v1   | subu a0,a0,v1
   22  sh a1,24(sp)    | sh v1,24(sp)
   23  subu v0,v0,a0   | sh a0,24(sp)
   24  subu a0,a0,v0   | sh v0,28(sp)
   25  sh a0,28(sp)    | subu v0,v0,a1
   26  --              | subu a1,a1,v0
   27  --              | sh v0,28(sp)
   28  --              | sh a1,28(sp)
```
Mine has 2 stores in this region (sh a1,24 and sh a0,28), target has 4 stores (sh v1,24; sh a0,24; sh v0,28; sh v0,28; sh a1,28 — actually 5). Hmm.

Wait, mine's `sh a1,24` corresponds to b[0]=u88 (a1=u88 after the subu? confusing). Let me look at the full candidate listing to identify which stores are present.

Let me dump the candidate and target side by side for the whole function.

Actually, let me reconsider: maybe the missing stores are eliminated by **`cse2`** (the second cse after loop). cse2 runs after loop; the dead-store elimination for memory might be in cse's `cse_insn`: when a store to memory is encountered and a previous store to the same memory is in the table, the previous store's *value* is invalidated... but deletion?

Hmm, wait. Let me look at cse.c around line 6983 (`if (GET_CODE (dest) == MEM)`).
