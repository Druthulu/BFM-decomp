---
ts: 2026-11-06T09:03:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_esAWL1P5oCs3G2dkSDmW
---
v22 produces `mflo s3` (z = product, so the result goes into z's register s3) whereas the target has `mflo t1` (a separate temp). The 5 insns are all there; only the destination register differs: s3 vs t1.

So the target computes the product into a *temp* (t1), then... the value is dead. In v22 the value goes to z (s3). So the target's product result is a temp that's dead.

Now: how to get the product into a dead temp t1 but keep the insns? We need a use that keeps the insns but with the destination being a temp that's dead. 

v18 (otz = product) gave 513 insns: the product kept (mflo into otz's reg?) + an extra store. Let me check v18's diff — maybe it's `mflo t1; sw t1,72(sp)` (product kept + store). Score 20.

What we need: the product computed into a temp, and the use is... nothing. Contradiction — unless the use is a *copy that gets deleted but leaves the multiply*. 

Hmm! What about assigning the product to a temp and then using the temp in a way that flow deletes the *copy* but keeps the multiply? E.g.:
```c
tt = (a[2]-z)*buf[5];
otz = tt;   // later overwritten by gte_stszotz
```
flow would delete `otz = tt` (dead) and then `tt = product` (dead) → all gone.

What if the temp's value is used in a *store that flow keeps* (address-taken) but the store is to a slot that... no, the target has no store.

Wait — what about the mult/mflo split? In v22, `z = product` gives `mult v0,v1; mflo s3`. The target has `mult; mflo t1`. The difference is just the destination register. So if we can make the destination a *new temp* that is dead but the insns kept... 

What if the temp is used in a *dead* store to a global? flow keeps global stores? A store to a global MEM is not deleted by flow (flow only deletes register sets; stores to memory are kept unless it's a redundant store to the same MEM). So:
```c
D_something = product;
```
would give `mult; mflo t1; sw t1,0(global)` — an extra store (not in target).

Hmm.

But WAIT: what about a store to a **stack slot that is later overwritten**? flow's `last_mem_set` deletes a store if it's followed by another store to the same MEM with no intervening uses. In v18 (otz = product, then gte_stszotz stores to the same slot), we got 513 insns = the extra store was KEPT. Hmm, why? Because between them there are memory ops (lwc2) that reset last_mem_set? Possibly.

What if the store immediately precedes the overwriting store? E.g., put `otz = product;` right before `gte_stszotz(&otz);` (adjacent). Then flow might delete the first store as a redundant store to the same MEM! Let me test: move the assignment to just before gte_stszotz.

In the source, the asm is before gte_ldv3c; gte_stszotz is later (after the cull computations). If we place `otz = product;` right before `gte_stszotz(&otz);`, the intervening code includes GTE loads and stores... The last_mem_set logic: `if (GET_CODE (r) == MEM && last_mem_set && !MEM_VOLATILE_P (r) && rtx_equal_p (r, last_mem_set)) return 1;` — but `last_mem_set` is updated per block; intervening memory ops may reset it. Let me look at how last_mem_set is maintained in flow.c. Actually, the flow pass that deletes dead stores is `propagate_block` with `last_mem_set`: it tracks the last memory set in the block and clears it on calls/labels. If the two stores are adjacent (same block, no intervening memory set), the first is dead.

But we can't place the product assignment adjacent to gte_stszotz without moving it far from its target position (the target has the product right after the call). The product's 5 insns must be at target[84-88]. If we place `otz = product;` just before gte_stszotz (insn ~160), the multiply would be at the wrong place.

Hmm. Unless we compute the product early into a temp and assign to otz later:
```c
tt = (a[2]-z)*buf[5];      // at the right place
...
otz = tt;                   // right before gte_stszotz
gte_stszotz(&otz);
```
Then: the multiply is computed into t1 (temp, since tt is used later!) — matching target[84-88]! And then `otz = tt` is a store right before gte_stszotz which overwrites otz → flow deletes the store as redundant (if adjacent in the same block with no intervening memory set). Then the multiply remains (its result tt is used by the deleted store? no — if the store is deleted, tt becomes dead, and flow would delete the multiply too... but flow's dead-code pass processes insns in order and computes `needed` from liveness: if the store is deleted, the multiply's destination tt is dead → deleted too.

Hmm. Unless the deletion order leaves the multiply. flow's `propagate_block` computes liveness backward and deletes dead insns; a redundant store is deleted by `last_mem_set` logic but the *value* tt is still "needed" at the store point because the store is examined... Actually the store is deleted for being redundant, but the register needed set includes tt at the store? The deletion happens in `propagate_block`: for each insn, if `insn_dead_p(PATTERN(insn), needed)` → delete. For a MEM store, `insn_dead_p` returns 1 only if it equals last_mem_set. Then the insn is deleted. But the register tt used by the store was added to `needed` when processing the store? The code marks the store's source registers as needed only if the insn isn't dead. Hmm, the order: `propagate_block` walks backward; for each insn it computes the registers used and sets needed, then checks deadness. If the store is dead (redundant), it's deleted and its source regs might not be marked needed. So the multiply would then be dead → deleted.

Too speculative. Let me just TEST the variant:
v27: `tt = product;` at the asm position, and `otz = tt;` inserted right before `gte_stszotz(&otz);`.

Also v28: `tt = product;` and use tt in the *else* branch's dead computation? no.

Let me look at v18's diff to see exactly what extra insn appears (it might be the store to otz kept because the GTE asm has a "memory" clobber, which resets last_mem_set!). Indeed, gte_stszotz has `"memory"` clobber → flow treats an asm as a memory barrier and resets last_mem_set. But between the store and gte_stszotz there are many insns anyway.

Let me look at v18's diff.
