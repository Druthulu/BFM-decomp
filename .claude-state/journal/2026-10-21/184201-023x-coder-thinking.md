---
ts: 2026-10-22T00:42:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_nJFtqY9tSIwPSHOFwT2t
---
Baseline score 0. Now let me write the lever-free candidate: remove the asms.

Candidate A (naive lever-free):
```
void func_8018A180(s32 a0) {
    Prim_8018A180 prim;
    MtxBuf_8018A180 buf;
    s32 iVar1;

    prim.rgb = 0x282828;
    prim.tag = 0x60000000;
    {
        s32 ang = 0xE;
        func_8012EA90(a0, ang, (s32 *)&buf);
    }
    func_8012F14C((s32 *)&buf, (s32)&D_801921E8, (s32)&prim.v[0]);
    ...
```
Wait — but the "ang" launder was also needed for ordering (key 4). Removing it may cause ordering diffs. Let's test.

Note the lever-free version must also not have the pin/other levers. All asms removed.

Let me create cand01.c and score. Then iterate.

I'll keep candidates in the item dir as candNN.c.

Let me write candidate 1.
