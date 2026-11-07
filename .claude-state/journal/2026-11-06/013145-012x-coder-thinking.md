---
ts: 2026-11-06T08:31:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tk12FavVOGsiY6R4LWO8
---
Baselines score 0 (as expected; bodies identical to src). Now lever-free attempts: strip the keepalive asm lines and see the score.

Item order in list.tsv: func_8017F6B0 first. Let me start with it.

Item 1: func_8017F6B0:
```
void func_8017F6B0(void *a0, s32 a1) {
    s32 t0, t1, t2, t3, t4;
    s32 sp10[5];
    u16 *h;
    s32 off;

    off = a1 * 20;
    t0 = *(s32 *)((char *)&D_801A5460 + off);
    t1 = *(s32 *)((char *)&D_801A5464 + off);
    t2 = *(s32 *)((char *)&D_801A5468 + off);
    t3 = *(s32 *)((char *)&D_801A546C + off);
    sp10[0] = t0;
    sp10[1] = t1;
    sp10[2] = t2;
    sp10[3] = t3;
    t4 = *(s32 *)((char *)&D_801A5470 + off);
    sp10[4] = t4;
    __asm__ __volatile__("" :: "r"(off));  // keepalive
    h = (u16 *)sp10;
    h[0] = h[0] + ((Unkstruct_800B5CB8 *)a0)->unk6;
    h[1] = h[1] + CAST_ALIAS(u16, (s32)a0, 0xA);
    __asm__ __volatile__("" :: "r"(t3));  // keepalive
    h[2] = h[2] + ((Unkstruct_800B5CB8 *)a0)->unkE;
    func_8012C51C(sp10, (s32)a0);
}
```

The keepalives keep `off` and `t3` live (prevent their death). Real C alternatives: make `off` and `t3` genuinely live later. For `off`: after the sp10 fills, use off... but the code doesn't need it. Hmm, the target presumably has the loads scheduled such that off dies later. Options: use `off` in a dead-ish way that gcc can't delete, e.g. compute something and store to stack? No new lever allowed, but real C moves allowed (temps, decl order/scope, statement order...). A real C use that is observable: e.g., `sp10[0] = ...` later using off? That would change code.

Let me first see what happens with the keepalives simply removed — the score and diff. Then examine the target asm and dumps.

Let me create a working candidate file w1.c.
