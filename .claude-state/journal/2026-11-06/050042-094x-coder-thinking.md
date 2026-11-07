---
ts: 2026-11-06T12:00:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_3lyqACJugJswYxSaZ4pR
---
Only the store sink remains (sw at 30 vs 29). Score 2. This is the sched-store-sink. Let me try to fix it.

The store `CAST_WIDTH(s32, (u8*)a0, 0x10) = v;` is at the end of the middle block. Target has it at 29 (before li a0,2432 at 30). Mine has it at 30 (after li a0,2432).

I need to prevent the scheduler from sinking the store past the li a0. The barrier did this.

Real C options:
1. Add a dependence between the store and the li. The li a0=0x980 is the arg to the final call. If the store's value/address depended on something computed after the li... 
2. Reorder the source so the store is naturally before the li.
3. Use a do-while around the store (tested: v_s8_store_dw = 4, no help).
4. Make the store's address depend on a value that's loaded after... 

Hmm. Let me think about what the barrier does: `__asm__ __volatile__("")` at the end of the middle block (after the store). It's a scheduling barrier. Without it, sched moves the li a0 (from the final call) up before the store.

Actually, wait — the store is INSIDE the middle block, before the barrier. The barrier is after the store. So the barrier prevents insns from moving across it. The li a0 (after the barrier, in the tail) can't move before the barrier. So the store stays before the li.

Without the barrier, the li a0 can move up before the store.

Real C to create a barrier-like boundary without asm: a do-while(0) creates a NOTE_INSN_LOOP boundary? But v_s8_store_dw (do-while around the store) didn't help. Maybe wrapping the WHOLE middle block in a do-while (so the loop boundary is after the store) would prevent the li from moving up.

Let me try: wrap the middle block in do-while(0). The loop end label is after the store, before the tail. sched might not move the li across the loop boundary.

Also try: wrap the TAIL (after the store) in a do-while. Hmm.

Let me try:
- v_s8_dw_two_block: s8 + do-while around the whole middle block.
- v_s8_dw_two_tail: s8 + do-while around the tail.
- v_s8_dw_two_all: s8 + do-while around the whole function.

Let me test.

Actually, the middle block is:
```
    {
        s32 v;
        v = ...;
        ...
        CAST_WIDTH(s32, (u8 *)a0, 0x10) = v;
    }
```
If I wrap it in `do { ... } while (0);`, the loop boundary is after the store. sched1 operates within extended basic blocks; a loop boundary (NOTE_INSN_LOOP_END) might prevent the li from moving up. But the middle block already ends with `}`. Adding a do-while might create a label.

Let me test.

Also, another idea: reorder the tail so the store comes before the li naturally. The tail is:
```
    unk14 = 0x200000;
    CAST_WIDTH(...,0x18) = 0;
    unk48 = 0x20000;
    unk1C = 0;
    func_8002D4C8(0x980, 0);
```
The li a0=0x980 is for the final call. If I move the CAST_WIDTH 0x10 store to AFTER the middle block (into the tail, before the other stores), the scheduler might place it differently. But the target has it at 29 (right after the v computation, before li a0). Hmm.

Let me try moving the store into the tail:
```
    CAST_WIDTH(s32, (u8*)a0, 0x10) = v;   // v is in scope? v is block-local
```
v is declared inside the middle block. If I move the store out, I need v in scope. I could declare v at function scope. But that changes the structure.

Let me first try the do-while wrappers.

Let me generate.
