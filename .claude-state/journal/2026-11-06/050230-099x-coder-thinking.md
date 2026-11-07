---
ts: 2026-11-06T12:02:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_qvvnx8P6lGfjhPqyduql
---
Item 4: func_800CB3BC in src/md_MAIN_041/md_MAIN_041.c:238-330. Kinds barrier,launder. 2 barriers, 2 launders (lines 264, 266, 269 in the source shown).

Let me extract orig.c (238-330) and calibrate.

From the earlier read:
```
void func_800CB3BC(s32 arg0, s16 arg1, s16 arg2, s16 arg3) {   <- line 238
...
    cv = ((Unkstruct_800CB3BC *)ent)->unk12;
    f.cx = arg1;
    BARRIER (264)
    va = (u8 *)&f.cx;
    LAUNDER va (266)
    f.cy = arg2;
    vb = va;
    LAUNDER vb (269)
    p = D_800CB820;
    ...
}   <- line 330
```
Let me extract and test.
