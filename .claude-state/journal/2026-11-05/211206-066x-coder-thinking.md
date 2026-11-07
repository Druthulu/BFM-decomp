---
ts: 2026-11-06T04:12:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_BorIGCrnh8uQDBGgqTWI
---
Item 3: func_801854B8, kinds barrier, 32 lines. It has two `register ... __asm__` pins (pin kind) plus one barrier. Since kinds = barrier only, the pins may stay. But let me re-read the constraints: "MATCH = the kinds in <dir>/kinds gone; levers of other kinds the def already had (pins under other causes) may stay, never added". So for D3, we may keep the pins but must remove the barrier. Hmm, but the goal of the shard is "lever-free body". The brief says "Lever-free = none of the row kinds in <dir>/kinds remain". kinds=barrier. So removing the barrier suffices; pins may stay.

But wait, D3's `orig.c` had 2 `!FAKE` lines (pins) and one barrier removed. Let me re-read the orig body:

```
void func_801854B8(s32 arg_in)
{
    s32 arg0;
    register s32 t __asm__("$4");  // !FAKE: pin $4
    register s32 var __asm__("$2");  // !FAKE: pin $2
    s32 p;
    s32 i;

    arg0 = arg_in;
    var = ((Unkstruct_801854B8 *)arg0)->unk1C;
    if (var == 0) {
        var = ((Unkstruct_801854B8 *)arg0)->unkFE - 1;
        ((Unkstruct_801854B8 *)arg0)->unkFE = var;
        if ((s16)var != 0) {
            for (i = 0; i < 4; i++) {
                if ((s16)D_80126B5E < D_801924DC[i]) {
                    break;
                }
            }
            p = D_801C7E38[i];
            t = D_801C7E78;
            *(u16 *)(p + 0x10A) = 1;
            __asm__ __volatile__("");  // barrier
            var = 60 - t * 15;
        } else {
            ...
        }
    } else {
        var = var - 1;
    }
    ((Unkstruct_801854B8 *)arg0)->unk1C = var;
}
```

Baseline (nopin.c) scored? The output earlier for D3 didn't show the score line (grep missed). Let me get it.

Note: `var` is pinned to $2 and `t` to $4. The barrier is between the store and `var = 60 - t*15`. What does the barrier do? Probably sched1 ordering: the `sw`/`sh` store then the computation. Let me get the target disassembly and the baseline diff.

Let me run dt.sh on nopin with full tail.
