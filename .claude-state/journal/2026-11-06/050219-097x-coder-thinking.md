---
ts: 2026-11-06T12:02:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Mq4hDeGZPGOLl2AEN9dh
---
v_v_init = 2 (no change). v_v_func_init = 20 (worse, 45 ins).

Still the store sink. Let me think about sched1 vs sched2. The wall tag is sched-store-sink. Let me look at what the barrier actually does at the sched level.

The barrier `__asm__ __volatile__("")` is an asm insn. sched1/sched2 treat asm as a barrier (can't move across). So the store before the asm can't be moved after it, and the li after can't move before.

Without the asm, the store and li are in the same EBB and sched reorders.

Real C constructs that act as sched barriers: a function call? A volatile access? A label? sched1 splits at basic block boundaries and at CALL_INSNs? Actually sched1 works on extended basic blocks; calls are barriers? No, calls can be in EBBs.

A do-while(0) creates a loop boundary (NOTE_INSN_LOOP_BEG/END) which sched respects? I tried (v_mid_dw = 2, no change). Hmm.

What if I put the store AFTER a call? The target has the store before the final call. If I move the store to after the final call, wrong order.

What if I create a dependence: make the final call's second arg depend on v? `func_8002D4C8(0x980, v & 0)`? That's an identity (v & 0 = 0) — launder, and folds. Or `func_8002D4C8(0x980, 0)` — the second arg is 0. If I make it depend on v: `func_8002D4C8(0x980, v - v)`? identity, folds to 0. Hmm, but if it doesn't fold... `v - v` folds to 0 at RTL. 

What about making the FIRST arg depend on v? No, it's 0x980.

Hmm. What if the store's value v is used in the final call somehow? No.

Let me try a different approach: the store sink might be fixable by changing the ORDER of the tail statements. Currently:
```
    unk14 = 0x200000;
    CAST_WIDTH(...,0x18) = 0;
    unk48 = 0x20000;
    unk1C = 0;
    func_8002D4C8(0x980, 0);
```
Target sched order: store 0x10, li a0, lui 0x20 (unk14 value), sw unk14, lui 0x2 (unk48 value), move a1, sw 0x18, sw unk48, jal (delay sw unk1C).

Mine: li a0, store 0x10, lui 0x20, sw unk14, lui 0x2, move a1, sw 0x18, sw unk48, jal (delay sw unk1C).

So only the first two swapped. What if I reorder the source tail to put the 0x18 store first, etc.? That would change the target order.

Hmm. What if the `li a0` is for the final call and it's hoisted because the call is at the end. If I move the final call EARLIER in the source (before some stores)? But then the semantics change (the stores must happen before the call? Actually the target does the stores then the call). If I move the call before the stores, the order changes.

Let me look at whether the store sink is really the only issue and whether it's crackable. The score is 2. That's very close. Let me try a few more things:

1. Make the store `volatile`? No (lever).
2. Use a `do-while` around the store AND the tail.
3. Reorder the tail stores.
4. Change the final call to use a variable for 0x980.

Let me try:
- v_tail_reorder: swap unk14 and 0x18 stores, etc.
- v_call_arg_var: `s32 c = 0x980; ... func_8002D4C8(c, 0);`
- v_store_after_call: no.

Actually, let me look at the mine disassembly tail to confirm.

Let me dump v_v_init tail.

Actually, I know the diff. Let me try the call-arg-var idea and tail reorder.

Also, maybe the store sink is because the `li a0` and the store are scheduled by sched2 (not sched1). sched2 runs after reload. The wall tag sched-store-sink is "sched". Let me check if it's sched1 or sched2.

Let me try the "init at decl" trick from moves.md line 241/243 (dead stores move above a load, changing sched2 slot). Maybe declaring something with init changes the birth order.

Hmm. Let me try a batch:
- v_tail_reorder1: move unk48/unk1C before unk14.
- v_call_var: 0x980 in a variable.
- v_store_dw_tail: do-while around store+tail.

Let me test.

Actually, let me reconsider: the target's store at 29 is right after the v computation (lui 0xfffd at 28). The li a0 at 30. In mine, the li a0 is at 29 (before the store). 

What if I make the store's address computation depend on the v computation in a way that ties them? It already does (store uses v0).

What if I insert a dummy that forces the li a0 later? 

Let me try making the final call's first arg a non-constant that's computed after the store. E.g.:
```
    ...
    CAST_WIDTH(...,0x10) = v;
    unk14 = ...;
    ...
    func_8002D4C8(0x980, 0);
```
The li a0=0x980 is a constant. sched hoists it. If I make it `func_8002D4C8(0x980 + (v - v), 0)`? folds.

What if the first arg is a global read? `func_8002D4C8(D_something, 0)` — but the target is 0x980. A global read would add an insn.

Hmm.

Let me try the tail reorder and call-var and see.

Actually, let me look at the sched pass. Let me check if there's a way to see which pass. The wall tag "sched-store-sink sched sinks a store past the target slot (G28)". So it's a known wall from G28. Let me check moves.md for sched-store-sink MATCHes.

Let me grep moves.md for "store-sink" or "sink".

Let me do that.
