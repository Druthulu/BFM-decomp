---
ts: 2026-11-06T04:46:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4bPBI2XfiqbMpMMLiD6L
---
Difference in the prologue ordering:
- Target: mask (~0xF000) in v1; loads currentLocationId into v0 first, then computes and; the `D_800A2E20` address setup (v0) is deferred until after the D_800D34AE load; the store to D_800C7C64 (at reg) after.
- Mine: mask in a0; D_800A2E20 address in v1 early; ... store to D_800C7C64 early at 0x160; mask in a0.

The barrier in orig prevented the store `D_800C7C64 = &D_800A2E20;` and `*p = val;` from moving up. Without barrier, the compiler hoists the address computation of D_800A2E20 and the store earlier. Target (with barrier) has the store late.

So we need a real-C construct that keeps those two stores after the loads. Options: make the store value depend on the loads (val, raw). `*p = val;` already depends on val. `D_800C7C64 = &D_800A2E20;` doesn't depend. Target's store of D_800C7C64 comes after the D_800D34AE load — but sched1 reorders independent insns; to keep it there, we need... Hmm.

Actually the key difference may be cse/flow ordering. Let me think about what the barrier does exactly: `__asm__("" ::: "memory")` is placed after all declarations and before the two stores. It's an asm with memory clobber, so it blocks reordering of memory ops across it. Removing it lets sched1 move the D_800A2E20 address computation and store up.

Approaches in real C:
1. Make the two stores depend on `val`/`raw` computations (they can't be hoisted above the loads). `D_800C7C64 = &D_800A2E20;` could be written so the value depends on a load, e.g., `D_800C7C64 = (s32 *)((u32)&D_800A2E20 + (val & 0));`? That's an identity launder — not allowed.
2. Reorder the C statements so that the stores come after the loads naturally... they already do (source order: loads, then stores). But sched1 reorders. To stop sched1, we need dependencies.
3. Use a `do{}while(0)` around the stores? That creates an EBB boundary for cse, but sched1 may still move within the block? Actually sched1 operates on basic blocks; a do-while creates a new basic block boundary only if there's a label/branch. do{}while(0) is a loop construct: gcc generates a NOTE_INSN_LOOP_BEG and maybe a branch at the end (to itself, then optimized?). If flow removes the branch, the block may merge. Hmm. In item1, the do-while did change the schedule — it prevented the load hoist. So it acts as a scheduling barrier even at do-while(0)! Interesting: in item1 b7, the do-while around the store prevented the next load from being hoisted above the store.

Wait actually in item1 b7, the result matched exactly, meaning the store and load stayed in order. So do-while(0) does act as a barrier for sched1 here. But does that make do-while(0) a "launder/barrier" lever? The brief explicitly allows `do{}while(0)` with the `// !FAKE: do-while` comment, and C0535 documents it as a move that cracked a sched1-birth-order item. So it's a legitimate real-C move.

But careful: the "kind" to remove is `barrier` (the asm memory barrier). If I replace the asm barrier with do-while and it works, that's a crack.

Let's try: wrap the two stores in do-while(0). Or place a do-while around... The orig structure:

```
s32 mask = ~0xF000;
s32 idx = currentLocationId & mask;
s32 raw = D_800D34AC[idx];
s32 val = D_800D34AE[idx * 2];
s32 *p = &D_800C7C60;
s32 id;

<barrier>
D_800C7C64 = &D_800A2E20;
*p = val;
```

Try b1: do { D_800C7C64 = &D_800A2E20; *p = val; } while(0);
Also b2: separate do-while per store.
Also b3: reorder: move the two stores after `id = raw & 0xFFF;`? No, source order should match target? Target has the D_800C7C64 store after the lh (val load), i.e., after all loads. Since `*p = val` depends on val, it's naturally after. `D_800C7C64 = &D_800A2E20` is hoisted up in mine.

Alternatively make D_800C7C64 store use a pointer variable: `s32 *q = &D_800A2E20; D_800C7C64 = q;` — could change scheduling.

Let me try do-while variants and a few others.
