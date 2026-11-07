---
ts: 2026-11-06T04:57:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xuVNaLwWpTw4EdHLmSBT
---
Worse. The pointer approach changes the code too much (and p1 gives 103 ins).

Let me reconsider. Maybe the hoist is not sched1 but the *RTL generation order*. Actually, let me check the RTL: in GCC, `D_80078EA4 += a1;` generates: load, add, store. Then the next statement's load. The insns are in order: lw, addu, sw, lh, slti. Then sched1 may reorder. The candidate shows lh before addu, so sched1 reordered.

Why doesn't the target reorder? The memory clobber. But wait — the asm is AFTER the store. The memory clobber marks all memory as used/clobbered, so the load can't move above the asm. Yes.

Real-C alternatives to stop sched1's hoist:
- A memory dependency. Since the symbols are distinct, none.
- Make the load's value depend on the store: e.g., compute the compared value from the new EA4 value. Not semantically possible.
- `sched1` uses `-fschedule-insns`. Can't change flags.

Hmm, but hold on: maybe the reordering isn't sched1 but *cse*: cse may replace the second load with a value... no, the insn moved position.

Let me confirm by looking at the cc1 dump (passes). The hdump.sh can dump sched1. Let me run it on the includer TU with the v1 body and look at the sched1 dump around the block. That would confirm.

Actually, a cheaper test: if sched1 is the cause, then a body where the load *must* stay after (due to a real dependency) would keep the order. I can simulate the dependency by making the load's address depend on the stored value — but that changes the address.

Alternatively: make the *store* depend on the load's result? E.g., reorder the C: 
```
s16 x = D_80078EA6;   // load first (before the store)
D_80078EA4 += a1;
if (x >= 0xA1) ...
```
Then the load is before the store in the RTL — but the target has the load AFTER the store. Hmm, but sched1 might reorder it back? No, that's the opposite.

Wait — actually, maybe that's a good idea in reverse: the target's order is store-then-load. If I write the C as load-then-store, sched1 would probably leave it (or reorder to store-then-load? sched1 tends to hoist loads). Hmm.

What about writing the comparison with a *use* of the store's value to create a false dependency? E.g.:

```
s32 v = D_80078EA4 + a1;
D_80078EA4 = v;
if ((s16)D_80078EA6 >= 0xA1) ...
```
No.

What if the condition is written as `if ((s16)D_80078EA6 >= 0xA1)` where D_80078EA6 is accessed through the *same* pointer expression as EA4 but with an offset the compiler knows... we covered that (reloc).

Hmm, let me reconsider the reloc constraint. What if the target's reloc operand comparison is on the *symbol name only*, not addend? Let me check the reloc_op format: it's `rm.group(2)` from objdump's output, e.g., `D_80078EA4`. For `D_80078EA4+2`, objdump prints `D_80078EA4+0x2`? Actually for MIPS HI16/LO16, the addend is in the instruction, and objdump prints `R_MIPS_LO16 D_80078EA4`. The reloc_op would be "D_80078EA4". So `*(s16 *)((u8*)&D_80078EA4 + 2)` gives reloc_op "D_80078EA4" and instruction `lh v0,2(v0)`. The target: reloc_op "D_80078EA6", instruction `lh v0,0(v0)`. Both differ. No.

OK, so we can't express the alias through the same symbol.

Alternative: maybe the *store* can be made to depend on the load instead, so sched1 keeps the order? If the store's value depended on the load of EA6, the order would be load-then-store — wrong order.

Hmm, what if the load is made to appear after the store by using the store's *result*: e.g.

```
D_80078EA4 += a1;
if ((s16)D_80078EA6 >= 0xA1) ...
```
What if we write `if ((s16)(D_80078EA6 + (D_80078EA4 - D_80078EA4)) >= 0xA1)`? The compiler would fold the zero. No.

What if we introduce a real dependency that the target also has? The target's order: lw EA4; addu; sw EA4; lh EA6. No dependency.

So the target relies on the memory clobber for ordering. Without asm, sched1 will hoist. Is there another way to make sched1 not hoist? 

sched1's `true_dependence` for a load vs a store: it checks anti-dependence (store after load) and output dependence. The load EA6 moved above the store EA4. For sched1 to keep it, it needs a dependence edge from the store to the load (true dependence: the load reads what the store writes). Distinct symbols → none.

What if the load is a *volatile* access? Lever.

What if the store is through `base` (a pointer) and the load direct? base = D_80078E78 (a pointer variable). The second half's store is `*(s32 *)(base+0x60)` and the load `*(s16 *)(base+0x62)` — overlapping → dependence → order kept. But the *first half* uses absolute symbols.

Could I access the first half through `base` too? EA4 = base + 0x2C, EA6 = base + 0x2E. But the reloc: target uses D_80078EA4/D_80078EA6, so the generated code would reference D_80078E78+0x2C → reloc_op D_80078E78. Mismatch.

Hmm, unless... `base` is assigned from D_80078E78, and gcc might fold `*(s32*)(base+0x2C)` to the absolute address D_80078EA4? No, it's a pointer variable.

OK, so item 2 may also be a wall: `sched1-load-order` (line 22 in walls.txt: "sched1 orders an addiu/lw pair opposite to the target (G20)"). Or a new tag like `sched1-store-load-order`.

But wait — before concluding, let me check whether the *reordering* is really sched1. If it's sched1, the wall tag would be sched1-load-order. Let me verify with a cc1 dump: run hdump.sh and check the sched1 output.

Actually, maybe there's another approach: what if the whole `if` structure is reorganized so the load comes after the store naturally in the *source order* of the same EBB? E.g., the code is:

```
D_80078EA4 += a1;
if (D_80078EA6 >= 0xA1) ...
```
sched1 hoists the load above the store because it's within the same basic block (the store and the load are adjacent). If we insert a *barrier-like* real-C statement between them that sched1 respects... like a function call? no.

Hmm, what about splitting the basic block with a `do-while(0)` (C0535: splits cse1 EBB)? If the store and the load are in different EBBs, sched1 (which operates within a basic block) can't move the load above the store! That's promising!

C0535: "do{}while(0) splits cse1 EBB; cracked a sched1-birth-order item". So a do-while(0) creates a boundary that sched1 respects (sched1 schedules per basic block). If we wrap the load in a do-while(0), it might stay in a separate block.

But wait, does a do-while(0) survive to sched1? C0535 says it splits the cse1 EBB — and sched1 runs after cse1? The pass order: cse1, loop, cse2, ... sched1 (first scheduling) runs... In GCC 2.7.2: `sched1` runs early? The pass order: jump_opt, cse, ... sched? Let me check. The wall tags mention "sched1" vs "local-alloc" and "sched1-birth-order" — sched1 runs before local-alloc? Actually in gcc 2.7.2 toplev.c: `if (optimize > 0) { ... jump_optimize; ... cse; ... }`. sched1 (`schedule_insns`) runs after cse1 and before local-alloc? Hmm.

Let me check the pass order in toplev.c: `rest_of_compilation`: 
- jump_optimize
- ... cse
- ... schedule_insns (sched1)
- local_alloc
- ...
Yes, sched1 is after cse1 and before local_alloc/global_alloc.

If do-while(0) splits the EBB at cse1 time, the split persists into sched1 (basic block boundaries from the CFG). But do-while(0) with no jump: does it create a basic block boundary? A NOTE_INSN_LOOP_BEG doesn't split a basic block. Hmm, but C0535 claims it splits cse1's EBB. cse1's EBB is split by CODE_LABELs (and jumps). A loop note isn't a label.

Let me read C0535 to understand exactly.
