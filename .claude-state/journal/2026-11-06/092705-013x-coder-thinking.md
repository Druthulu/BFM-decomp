---
ts: 2026-11-06T16:27:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_5Jx36ceUhUdr25X9qYtP
---
Baseline orig scores 0. Now remove the pins: three pins $0 zr, $2 f, $3 g. The zr pin is used as `self = arg0 + zr;` — pure identity (launder). Remove.

Goal: lever-free body that scores 0.

Let's write win.c without pins:

```c
void func_8017EAD8(arg0)
s32 arg0;
{
    s32 self;
    s32 mask;
    s32 flag;

    self = arg0;
    flag = ((Unkstruct_8017EAD8_2 *)self)->unkAA;
    ((Unkstruct_8017EAD8_2 *)self)->unk5C = 0;
    ((Unkstruct_8017EAD8_2 *)self)->unk98 = 0;
    ((Unkstruct_8017EAD8_2 *)self)->unk1C = 0;
    if (flag == 0) {
        s32 p;
        s32 f;
        mask = ~0x80;
        p = ((Unkstruct_8017EAD8_2 *)self)->unk20;
        f = ((Unkstruct_8017EAD8_2 *)self)->unkDC;
        p = *(u16 *)(p + 0x18);
        ((Unkstruct_8017EAD8_2 *)self)->unkDC = f & mask;
        ((Unkstruct_8017EAD8_2 *)self)->unk100 = p;
    } else {
        s32 q;
        s32 g;
        q = ((Unkstruct_8017EAD8_2 *)self)->unk20;
        g = ((Unkstruct_8017EAD8_2 *)self)->unkDC;
        q = *(u16 *)(q + 0x18);
        g |= 0x80;
        ((Unkstruct_8017EAD8_2 *)self)->unkDC = g;
        ((Unkstruct_8017EAD8_2 *)self)->unk104 = q;
    }
}
```

Let me test score.
