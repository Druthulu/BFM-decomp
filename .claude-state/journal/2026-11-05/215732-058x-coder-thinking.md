---
ts: 2026-11-06T04:57:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_lrE4zjnZNxEPdkXlLmAB
---
For the store `(mem:HI (plus (reg 84) (const_int 26)))`: addr is PLUS, mode HI (not QImode) → writes_ptr->all stays 0, nonscalar=1, var=1. So it invalidates only *nonscalar* memory entries (struct/array). The D_80127524 entry is a *scalar* (symbol ref, not MEM_IN_STRUCT_P), so it survives! That's why cse forwards the later load.

In orig, the asm clobber (mem:BLK scratch) invalidates everything → no forward.

So to invalidate the scalar entry via real C, we need a store that cse considers potentially aliasing a scalar: either a QImode store through a varying address (char aliasing) or a store with a varying address whose mode isn't HI-with-PLUS... Let's see: the condition for `all=1` is: varying address AND NOT (MEM_IN_STRUCT or addr is PLUS) && mode != QImode → all=1. So a varying address that is NOT a PLUS (e.g., a bare register `(mem:SI (reg X))`), with any mode → all=1! Or a QImode store through a PLUS → all=1.

Interesting. So if the intermediate store's address were a bare register (not plus), cse would invalidate all scalar memory. But our store is `*(s16 *)(D_80127524 + 0x1A)` = plus reg 26. Hmm.

Can we make the intermediate store's address a bare register without changing the instruction? Target insn is `sh v0,26(v1)` — offset 26 must be in the instruction. So the address is plus reg 26.

Alternatively, a QImode store with a varying address would also set all=1. But target has an HI store.

Hmm, but wait — the cse pass here might be cse1 vs cse2. The forwarding happened in cse1 or cse2? In the cse2 dump (a1) insn 64 is already forwarded. Let me check a1.i.cse (cse1) to see if it was already forwarded there.

If the forward happened in cse1, maybe we can add a construct that makes cse1 not forward but is eliminated later. E.g., a store that's dead and removed by flow/combine after cse.

Idea: insert a *real* store to a varying address between the sh and the call, which cse sees and invalidates, but which is dead and gets deleted later. For example, a store to a local variable through a pointer with a varying address? A dead store to a local would be removed by flow (dead store elimination) after cse. But cse1 runs before flow? Order in gcc 2.7.2 -O2: cse1, then flow? Let me check toplev/pass order. In gcc 2.7.2: 
- cse (cse1)
- ... loop ...
- cse2
- flow2? 

Let me look at toplev.c pass order. Actually the standard order for -O2 in 2.7.2: 
```
if (optimize) { ... }
...
if (optimize) { cse_insns... }
```
Let me grep toplev.c.
