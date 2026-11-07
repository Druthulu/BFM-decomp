---
ts: 2026-11-06T03:05:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_NUxrFsV1x94XPwYuB7r8
---
m2 (flag=0 twice) and m5 (flag=0; ...; flag=flag) both score 1, 108 ins — same as i2: the extra store remains (one of them). So combine removed the redundant one but one remains.

Hmm. What if the dead-reset store is to `flag` and combine deletes it because a *later* store to flag exists in the target? None.

Wait — m5: `flag = 0; ...; flag = flag;` — the second is a load+store; combine/cse might remove the second (store of the same value) and keep the first. Either way one store remains.

We need ZERO extra stores. The only way: the cse-breaker must be a store that is deleted. In this compiler, combine deletes a store to memory when a later store to the same address overwrites it AND the value is unused. So: place TWO stores to the same address, where the SECOND is an existing store... The existing stores are to unk1C. 

Idea: make the cse-breaker a store to unk1C *before* the target's store A, and store A overwrites it. But the breaker must be BETWEEN store A and the load to invalidate. ✗

Idea: make the breaker a store to unk1C *between* A and the load, storing the same value as A: `unk1C = unkDC; unk1C = unkDC;` — cse sees the second store's value = the first; the load forwards to unkDC. ✗

Idea: make the breaker a store to unk1C with a *different* value V, and then the load reads V, and the decrement uses V... that changes the value. Unless V is computed such that the final result is the same? The final store is V-1, but the target's final store is unkDC-1. So V must equal unkDC. ✗

So a same-address breaker is impossible.

What about a store to a *different* address that combine deletes because of a later store to THAT address? We'd need a later store to that address in the target — none.

Hmm, unless the breaker store is to `flag` and there's a later `flag` store hidden in the epilogue? No.

OK, what about the *other* direction: make the load not forwardable by making the store's VALUE not equivalent. cse forwards the stored value if it knows it. What if the stored value is computed in a way cse can't equate to the load's value? E.g., store `unk1C = (s32)(unkDC)` vs the load `unk1C - 1`: the load's forwarding uses the stored value regardless of the expression. The value IS unkDC. So it forwards.

Unless the store's value is a *different pseudo* that cse doesn't know equals the loaded unkDC? The store's source is the loaded unkDC value; cse knows it.

What if we load unkDC twice into two different pseudos: `v1 = unkDC; unk1C = v1; v2 = unkDC; ... unk1C = v2 - 1;`? Then the store's value v1 and the load's... the load of unk1C would still forward to v1. ✗

Hmm, what if the store is not to unk1C but to an *alias* the compiler can't resolve, and then the load reads unk1C? That changes semantics unless the alias is the same location. E.g., store via a `s32*` pointer loaded from a global that points to unk1C — the compiler can't resolve it, so no forwarding! But then the store's address is unknown → codegen needs the pointer (extra load). ✗

I think item 3 is a WALL with best 1 (i2/m2/m5), which is a strong result: 108/108 ins, one wrong instruction (`sw zero,24(sp)` vs nop).

Wait — actually, can we exploit the fact that the target's instruction at that position is a NOP (the load-delay slot)? The extra store is in the load-delay slot. What if we place the dead-reset store somewhere that it *doesn't* fill a delay slot and instead... it would still be an extra instruction (109). The best is 108 with the store replacing the nop. Score 1 = 1 differing instruction.

Could we make the store's instruction identical to the target's nop? No.

Alternatively, make the dead-reset store be a *store that the target also has* at that position. The target has `sw v0,28(s1)` at 20ac (after addiu). What if we reorder so our dead store is the shared final store? No.

Hmm, what if the dead-reset store is `flag = 0` but we can get flow to delete it by making flag *not* address-taken? The address is taken by gte_stflg(&flag) — required.

What if we use a different local for the dead reset whose address is taken but which flow proves dead? A local whose address is taken is memory; flow doesn't DSE memory.

OK. Let me try one more idea: what if the dead-reset store is to `flag` but we make it a *load* of flag that is... no.

Alternatively, use a *volatile-free* store to a local that combine can fold into a nop? no.

Decision: item 3 WALL, best 1. Let me count tries: orig control + nopin + g1-g7 (7) + h1-h7 (7) + i1,i2,i3,i5 (4, i4 compile error) + j1,j2,j6,j7,j8 (5) + k? none + m1-m5 (5) = 29 scored + nopin = 30. Good.

Actually, let me double check m2 vs i2: both score 1. Best 1.

Let me record item 3: WALL, best 1, wall tag `cse-store-forward` (existing: "cse1 forwards the sh value into the reload ... only a barrier/volatile stops it"). Evidence: "cse1 forwards the unkDC store into the unk1C reload and combine drops the dead store; flag=0 dead-reset (C0414) restores 108 ins but leaves sw zero,24(sp) in the load-delay nop."

Wait, the evidence ≤140 chars. Let me craft.

win.c = i2.c (best, score 1).

Let me finalize item 3.
