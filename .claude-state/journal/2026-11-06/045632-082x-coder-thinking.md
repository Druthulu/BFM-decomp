---
ts: 2026-11-06T11:56:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_I3TTUJtJq45MNb8pEfNF
---
Item 2 done (WALL). Time is ~04:57. Item 2 wall time ~16 min (plus writeup). Close enough to 20 given the writeup time; I'll note ~16-20.

Now item 4: func_80180F68 in src/ov_SC06_016/ov_SC06_016_jr_8017C8D0.c, def at 5045-5090. Kinds barrier,pin.

The levers:
- `register s32 two __asm__("$3")` pin
- `__asm__ __volatile__("")` barrier (at the end of the middle block)

Let me extract orig.c, baseline, then create lever-free.

Original:
```c
void func_80180F68(s32 a0)
{
    {
        s32 *p;
        register s32 two __asm__("$3");

        p = (s32 *)(CAST_SIGN(u32, (u8 *)a0, 0x20));
        two = 2;
        ((Unkstruct_800B5CB8 *)a0)->unk2 = two;
        ((Unkstruct_800B5CB8 *)a0)->unk34 = 0;
        *(s16 *)((u8 *)p + 0x14) = 0;
        *(s16 *)((u8 *)p + 0x12) = 0;
        *(s16 *)((u8 *)p + 0x10) = 0;
    }
    func_8012B2CC(a0);
    func_8012B200((u8 *)a0);

    {
        s32 v;

        v = CAST_SIGN(s16, (u8 *)a0, 6);
        if (v < 0) {
            v = ((Unkstruct_800B5CB8 *)a0)->unk70;
            if (v != 0) {
                v = 0x40000;
            } else {
                v = 0x30000;
            }
        } else {
            v = ((Unkstruct_800B5CB8 *)a0)->unk70;
            if (v != 0) {
                v = -0x40000;
            } else {
                v = -0x30000;
            }
        }
        CAST_WIDTH(s32, (u8 *)a0, 0x10) = v;
        __asm__ __volatile__("");  // !FAKE: barrier
    }

    ((Unkstruct_800B5CB8 *)a0)->unk14 = 0x200000;
    CAST_WIDTH(s32, (u8 *)a0, 0x18) = 0;
    ((Unkstruct_800B5CB8 *)a0)->unk48 = 0x20000;
    ((Unkstruct_800B5CB8 *)a0)->unk1C = 0;
    func_8002D4C8(0x980, 0);
}
```

Lever-free: remove the `two` pin (use `((...)a0)->unk2 = 2;` directly) and the barrier.

The pin `two = 2; a0->unk2 = two;` forces the value 2 into $3? The target presumably stores 2 to unk2 via $3. Without the pin, gcc uses another reg. Let me see.

The barrier `__asm__ __volatile__("")` at the end of the middle block: it's a scheduling fence to keep the store order (the `CAST_WIDTH(...,0x10) = v` store vs the following stores). Without it, sched might reorder.

Let me extract and test.

Let me first check if a sibling was cracked (moves.md for func_80180F68 — earlier grep found nothing). But maybe a similar function in SC06. Let me just work it.

Let me extract orig.c and baseline.

Time: 04:57. Item 4 budget 20-30 min. Let me move.
