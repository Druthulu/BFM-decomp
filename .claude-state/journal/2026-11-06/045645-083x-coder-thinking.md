---
ts: 2026-11-06T11:56:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_DEReTSgXMBDHxPPXOOTe
---
Baseline 0, 44 ins. Let me create the lever-free body: remove the `two` pin and the barrier.

Lever-free:
```c
void func_80180F68(s32 a0)
{
    {
        s32 *p;

        p = (s32 *)(CAST_SIGN(u32, (u8 *)a0, 0x20));
        ((Unkstruct_800B5CB8 *)a0)->unk2 = 2;
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
            if (v != 0) { v = 0x40000; } else { v = 0x30000; }
        } else {
            v = ((Unkstruct_800B5CB8 *)a0)->unk70;
            if (v != 0) { v = -0x40000; } else { v = -0x30000; }
        }
        CAST_WIDTH(s32, (u8 *)a0, 0x10) = v;
    }

    ((Unkstruct_800B5CB8 *)a0)->unk14 = 0x200000;
    CAST_WIDTH(s32, (u8 *)a0, 0x18) = 0;
    ((Unkstruct_800B5CB8 *)a0)->unk48 = 0x20000;
    ((Unkstruct_800B5CB8 *)a0)->unk1C = 0;
    func_8002D4C8(0x980, 0);
}
```

Let me write and score.

Note: the `two` pin forces the value 2 into $3. Without it, `a0->unk2 = 2` uses some reg. And the barrier at the end of the middle block. Let me test.

Let me write nopin.c.
