---
ts: 2026-11-06T03:00:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_R4ThEYaMMlRJ6cgfkEM2
---
j1 (pseudo local z = 0) → 105 (didn't break cse). j2 (s0=0) → 105 (didn't break). j6/j7 → 111 (stores kept). j8 → 105.

So the only cse-breaker that worked was `flag = 0;` (memory store to an address-taken local) → 108 ins but one extra store.

We need to eliminate that extra store. Ideas:
- Make the store's value the same as the memory's known value so cse removes it as redundant. E.g., `flag = flag;` didn't break cse (j8 → 105). Hmm, `flag = flag` is a load+store; cse might delete the store as redundant but then doesn't invalidate.
- What about `flag = -1;` vs `flag = 0;`? Same store.
- Make the store a `sh` (u16) to flag's address? Still an insn.
- Use a store to a location that flow/combine removes: e.g., a store to a stack slot that is then overwritten by another store before any read. Flow doesn't DSE memory.
- What if the dead reset is a store to `unk1C` of a value that cse then proves dead because the next store overwrites it? cse's "dead store" elimination: gcc's cse has `delete_dead_from_cse`? Hmm, cse.c has code to delete redundant stores of the same value ("record_jump_equiv"?) and there's a "cse2" pass. In the .combine dump for nopin, the first store (insn 178) was DELETED by cse/flow. That means the compiler DID delete a dead store to memory (unk1C)! So gcc 2.7.2 does delete dead memory stores in some cases (cse's store-to-store forwarding: the store at 178 followed by the store at 185 to the same address → the first is dead and cse deletes it). So cse can delete a store that is overwritten by a later store to the same address.

So if we insert a store to `flag` and later a store to `flag` again... hmm.

What if the dead reset is a store to a location that is *later stored again* (so the reset store is dead and removed)? E.g.:
```
unk1C = unkDC;
flag = 0;        // breaks cse, then...
unk1C -= 1;
flag = 1;        // overwrites flag → the first flag store is dead, cse removes it?
```
cse might remove the first flag store if it sees the second store to the same address. But the second store is an extra instruction (flag=1). Unless flag is used later? flag is dead after the condition. Adding `flag = 1;` after the decrement adds an insn.

Hmm. What about a store to a stack slot that is overwritten by the *existing* code? The existing code doesn't touch flag again.

What if we use `sp10` (the stack array)? It's used before (gte_ldv0(sp10)) but not after. A store to sp10[0] after the store would survive (no later overwrite).

What if we reset a location that the function's epilogue/other code overwrites? No.

Alternative: make the cse-breaker store a *dead store to a pseudo* but ALSO make cse's memory table invalidated. Does cse invalidate the memory table on any SET? Let me look at cse.c's `cse_insn`: when processing a store to memory, it calls `invalidate_memory`? The memory entries are in the same table; a store to a different address may invalidate entries via `exp_equiv_p`? Hmm.

Actually, why did `flag = 0` break the forwarding? Because the store to 24(sp) invalidated the memory entry for 28(s1) (alias unknown). And a store to a *pseudo* (z=0) doesn't touch memory → no invalidation. Confirmed by j1.

So we need a memory store that is removed. cse removes a store to the same address that is overwritten by a later store (store-to-store). Could we arrange the dead reset store to be overwritten by an *existing* store? The existing final store is to unk1C (28(s1)). If the dead reset were a store to unk1C... it would be the first store of the pair, and the later store (the decrement's) would overwrite it → the reset store is dead and removed! But the reset store must be *between* the first store and the load, and must not change the semantics. Sequence:
```
unk1C = unkDC;      // store A (kept in target)
???                  // need a memory store that invalidates cse and is removed
unk1C -= 1;          // store C
```
If the dead reset is a store to unk1C with any value, it would be removed as dead (overwritten by store C), BUT it would also make store A dead! Then the target's store A would be removed too. ✗

What if the dead reset is a store to an address that is overwritten by another *existing* store? The only later store is unk1C. Unless we add a store to a stack slot that is overwritten by... the epilogue's `lw`? no.

Hmm. What about a store to a stack slot that flow deletes because it's dead and flow DOES delete dead stack stores? Let me check flow.c in 2.7.2: does it eliminate dead stores to stack slots? The pass `delete_dead_from_cse` is cse's. flow.c's `propagate_block` deletes insns that set dead registers; for memory stores, there's `dead_store` handling only for registers. Hmm, but the first store in nopin WAS deleted — by which pass? Let me check: in the .combine dump it's gone; the .cse dump showed insn 178 store present? Let me check the .cse dump: earlier I saw at line 485 "insn 178 176 183 (set (mem 28) (reg 135))" — present in .cse. And in .combine it's gone. So the pass between cse1 and combine deleted it. Pass order: cse1 → loop → cse2 → jump → combine. The .cse2 dump? Let me check if insn 178 is present there. The cse2 dump earlier showed "485:(insn 178 176 183 (set (mem 28) (reg 135))" — present. Then combine deleted it? Or the jump pass between cse2 and combine? Actually the pass order in toplev: after cse2 there's jump_optimize, then "loop" (again?), then combine? Let me check. Hmm.

The key: some pass removed the dead store. If it's `combine` (store-to-store), maybe it can also remove our flag store if overwritten.

Let me test the "store to flag twice" idea:
```
unk1C = unkDC;
flag = 0;
unk1C -= 1;
flag = 1;    // extra store... would remain
```
✗.

What about storing to flag twice with the SAME value: `flag = 0; ... flag = 0;` — the second store is redundant (same value) and might be removed by cse, and the first too? Both removed → no invalidation. Hmm.

Let me think differently: what if the dead reset is a store to an address that the *target itself* already stores to later — e.g., `sp10[0]`? Target: does it store to sp10 later? gte_stsxy(sp10) stores to sp10 (the GTE writes to sp10 via gte_stsxy). Let me look: gte_stsxy(sp10) is a macro writing to sp10[0]/sp10[1]? The asm macro `swc2 ...` writes 2 words to the sp10 address. So sp10 is written AFTER our region? No — gte_stsxy(sp10) happens before the condition (early in the function). So a store to sp10[0] after would not be overwritten.

Hmm. What about storing to `flag` and then having gte_stflg write it again? No, gte_stflg is before.

OK, alternative: make the dead reset a store to a location whose store is removed by *combine*'s store-to-store elimination with the final unk1C store? Only if the address is the same.

Hmm, what if we insert the dead reset as a store to unk1C with a value that makes the *first* store not dead? E.g.:
```
unk1C = unkDC;      // A
unk1C = flag;        // B (breaks cse; flag is a load from 24(sp))... 
unk1C -= 1;          // C
```
B would make A dead → A removed → target's store A missing. ✗

What if the dead reset is a store to a *different field of the same struct* that is overwritten later? E.g., unk20? The target's code after the decrement: func_801820E4(arg0) — which may write fields. But a store before wouldn't be overwritten within the function necessarily.

Hmm. Let me look at what the actual original C might be. Maybe the original had a *real* store between them that the target's asm shows! Let me re-look at the target asm around 209c-20ac:
```
2094: lw v0,220(s1)
2098: nop
209c: sw v0,28(s1)
20a0: lw v0,28(s1)
20a4: nop
20a8: addiu v0,v0,-1
20ac: sw v0,28(s1)
```
No other store. So the original C had exactly these two memory ops and the compiler didn't optimize. 

Could the original have used a *volatile*? That's a lever, but maybe the original game code used a volatile pointer or an asm. Hmm, the reconstruction uses a barrier because the original was likely compiled with the same gcc and the same C — so the original C must have had something.

WAIT. What if the original C's two statements were in *different basic blocks* because of a `goto`/label that was removed by a pass AFTER cse? cse1 runs early. If a label exists at cse1 between the statements, cse won't forward. The label could be removed later by jump2 (unreferenced labels are removed in the first jump pass, which is BEFORE cse1!). Hmm, the first jump pass is before cse1 and deletes unreferenced labels. So a label at cse1 must be referenced by a branch at that time. The branch could be removed by loop_optimize or cse2 or a later jump pass.

What branch could be between the store and the load and later removed? A `goto` that is a jump-to-next would be removed by the first jump pass (before cse1) → label deleted. A branch that loop_optimize removes... e.g., the loop's back-edge? 

Look at the target: the store at 209c is right after the loop exit label 2094. The loop is before. What if the original had the store INSIDE the loop's exit test block, creating an EBB boundary?

Hmm, let me look at the target's structure around 2054-2094:
```
2054: lw v0,28(s1)     ; unk1C
2058: nop
205c: bnez v0,20ac     ; if (unk1C != 0) goto dec_tail
2060: addiu v0,v0,-1   ; delay slot
2064: lh v1,6(s0)      ; loop: unk6
2068: li v0,255
206c: beq v1,v0,2094
2070: move a0,s1
2074: li s2,255
2078: jal func_80182050
207c: move a1,s0
2080: addiu s0,s0,8
2084: lh v0,6(s0)
2088: nop
208c: bne v0,s2,2078
2090: move a0,s1
2094: lw v0,220(s1)
2098: nop
209c: sw v0,28(s1)
20a0: lw v0,28(s1)
20a4: nop
20a8: addiu v0,v0,-1
20ac: sw v0,28(s1)
```

Note: the `bnez v0,20ac` at 205c jumps to the shared store at 20ac. The else path: loop then 2094 store unkDC; 20a0 reload; addiu; 20ac store (shared).

Now, in the RTL at cse1, the EBB: the label at 2094 is a jump target (from the beq at 206c) → EBB boundary. The store at 209c and load at 20a0 are in the same EBB after 2094.

What if the original's `beq` target label was placed BETWEEN the store and the load? I.e., the guard branch jumped to a label right after the store! Then the store would be before the label (in the previous EBB) and the load after → cse can't forward! And the asm: the beq would target 20a0 (the load) instead of 2094 (the store). But the target's beq at 206c targets 2094, and the store at 209c is after. So no.

Hmm, unless the target's beq at 206c targets 2094, which is where the store is — so the store is the target of the beq. The load is after the store in the same block.

OK so cse1 must have been prevented by something else. 

Let me reconsider: maybe the forwarding in our build happens in cse1 but in the ORIGINAL build the RTL was different: maybe the original's store used a *different pseudo* for the base (e.g., the store's base was a0/arg0, and the load's base was s1). The target asm shows both 28(s1). But at cse1 (pre-regalloc), the bases could be different pseudos: e.g., the store via `arg0` (pseudo) and the load via `s0` (a local pointer = arg0). If cse couldn't equate the two pseudos, no forwarding; then register allocation assigned both to s1. 

In our src, the store is `((Unk*)arg0)->unk1C = ((Unk*)arg0)->unkDC;` and the load is `((Unk*)arg0)->unk1C -= 1;` — both use arg0 → same pseudo → forwarded.

If the original used a different pointer for the second access, e.g., a local `u8 *p = arg0;` and `((Unk*)p)->unk1C -= 1;`, cse might still equate p and arg0 via copy propagation (h3/h4 tested this: 105, forwarded). Hmm, but h3/h4 used a pointer to the FIELD. Let me try a pointer to the BASE: 
```
u8 *p;
p = arg0;
...
unk1C = unkDC (via arg0)
p->unk1C -= 1
```
cse's copy propagation would equate p with arg0 → forwarded. Unless we make p's assignment opaque: `p = arg0 + 0;`? Still.

What if p is loaded from a global that holds arg0? That would add code.

What if the second access uses `(u8*)arg0 + 0` vs arg0? Same.

Hmm, what about using the *array indexing* form: `((s32*)(arg0))[7] -= 1;` — the address is (plus (reg arg0) 28) → same.

What about making the second access use a different *struct type* whose field offset is 0x1C but the base expression is cast: same rtx.

I think the original might have used a *different variable* that holds arg0 but that cse couldn't propagate because it's modified. For example, `s0` is a local pointer that is used for the table and modified (s0 += 8). The target's base for both accesses is s1 (arg0). Hmm.

Actually, WAIT: maybe the original's `arg0` is a parameter and the local `s0` variable... The function's prologue: `move s0,a0`? Let me look at the target prologue: a24 addiu sp; a28 sw s0,16(sp); a2c move s0,a0; a30 sw ra; a34 lhu a0,52(s0). So the parameter arg0 is copied to s0 (a callee-saved reg) because it's used across calls. The base for unk1C accesses is s1 (a different callee-saved reg!). Let me check the target prologue for s1: the asm dump I saw starts at a24; where is s1 saved? Let me look at the full target asm. Maybe s1 = arg0 too (two copies?). Let me check.

Actually, the target's unk1C accesses use s1, but the prologue `move s0,a0` sets s0 = a0. Then where does s1 come from? Let me dump the prologue and find s1's setup.
