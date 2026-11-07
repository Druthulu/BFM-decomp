---
ts: 2026-11-06T13:40:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_TmzQWKfTukjMIZpdqoUl
---
w_b1 (B1 removed): score 20, and the ONLY real difference is at index 118-125 (the rest are address shifts from the 1-ins drift).

Target:
```
118: bne v1,v0,30cc
119: li v0,2
120: sh v0,52(s0)      ← unk34 = 2
121: lw v0,32(s0)      ← unk20 load
122: nop
123: beqz v0,30c4
...
125: sh v1,24(v0)      ← *(unk20+0x18)=var? Actually sh v1,24(v0)
```
Mine:
```
118: bne v1,v0,30c8
119: (delay: ?)
120: lw a0,32(s0)
121: li v0,2
122: beqz a0,30c0
123: sh v0,52(s0)
124: sh v1,24(a0)
```
So mine sinks the `li v0,2; sh v0,52(s0)` (unk34=2) BELOW the unk20 load, and uses a0 for the pointer. Target has li/sh before the load.

The barrier was between `unk34 = 2;` and `k = 0x1000; if (unk20 != 0)`. Removing it lets sched1 sink the store.

Real-C fix: keep the store `unk34 = 2;` before the load. C0535 do-while around the store? Or around the if? Let me try:
- v1: do { unk34 = 2; } while (0)
- v2: do { unk34 = 2; k = 0x1000; } while (0)
- v3: do { k = 0x1000; } while (0)  (split before the if)
- v4: do { if (unk20 != 0) {...} } while (0)
- v5: reorder.

The source block (case 1):
```
        if (((Unkstruct_800B5CB8 *)param_1)->unk1C == 4) {
            ((Unkstruct_800B5CB8 *)param_1)->unk34 = 2;
            __asm__ __volatile__("" ::: "memory");
            k = 0x1000;
            if (((Unkstruct_800B5CB8 *)param_1)->unk20 != 0) {
                ((Unkstruct_800B5CB8 *)*(s32 *)(param_1 + 0x20))->unk18 = k;
                ((Unkstruct_800B5CB8 *)*(s32 *)(param_1 + 0x20))->unk1A = k;
                *(u16 *)(((Unkstruct_800B5CB8 *)param_1)->unk20 + 0x1C) = k;
            }
            func_8012E88C((u8 *)param_1);
        }
```
Target: li v0,2; sh v0,52(s0); lw v0,32(s0); nop; beqz v0,...; then sh v1,24(v0)...

Hmm wait, the target's sh v1,24(v0) is at 125, after the branch. And the `unk18 = k; unk1A = k;` stores — where are they? The target's store at 24(v0) is one of them (unk18 = k where k=0x1000=v1?). Hmm, v1 = 0x1000 presumably.

Let me look at the actual target listing around there to understand. Let me get the addresses 0x30b0-0x30e0.
