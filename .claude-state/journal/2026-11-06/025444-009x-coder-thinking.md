---
ts: 2026-11-06T09:54:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2GOqQ72k7vjDeyLKCBDe
---
So the function body is from line 3740 to ~3770. Let me get the exact end. Let me see line numbers.

The body:
```c
void func_8017E8D8(s32 *a0, s32 a1, s32 a2) {
    s32 sp10[4];
    s32 sp20;
    s16 *q;
    u16 *p;
    s16 t;
    register s32 rv __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B t8_tus2)

    q = &D_80126CBA;
    if (*q == 0) {
        s16 lim = CAST_SIGN(s16, a1, 0x8A);
        s16 y = ((Unkstruct_80126B58 *)a1)->unkA;
        if (y <= lim + 0x40 && y >= lim - 0x80) {
            p = (u16 *)(q - 3);
            CAST_WIDTH(s32, a1, 0xE0) = 0;
        } else {
            p = (u16 *)(a1 + 0x88);
            CAST_WIDTH(s32, a1, 0xE0) = 1;
        }
    } else {
        p = (u16 *)(a1 + 0x88);
        CAST_WIDTH(s32, a1, 0xE0) = 1;
    }
    *(s16 *)((s32)sp10 + 0x2) = p[0] + *(u16 *)a2;
    t = p[1] + *(u16 *)(a2 + 2);
    *(s16 *)((s32)sp10 + 0x6) = t;
    ((Unkstruct_80126B58 *)a1)->unk100 = t;
    *(s16 *)((s32)sp10 + 0xA) = p[2] + *(u16 *)(a2 + 4);
    func_8012B77C((s32)&sp20, a1 + 4, (s32)sp10);
    rv = sp20;
    *a0 = rv;
    rv = (s32)a0;
    __asm__ __volatile__("" : : "r" (rv));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B t8_tus2)
}
```

Two levers: `register s32 rv __asm__("$2")` pin and the keepalive asm at the end.

The keepalive makes `rv` live at end — rv = (s32)a0. So rv gets a0. And then rv = sp20; *a0 = rv; rv = a0; keepalive. Hmm.

Without pin and keepalive, we need the same codegen. This is the hard part: what does the target asm look like? I need to understand why the pin and keepalive were there.

Actually the task is: produce a body scoring 0 (match) without those levers. So I need to find real C that produces the same asm.

Let me look at what the current orig scores. First, let me set up: copy src def to orig.c and test with dt.sh.

Let me look at dt.sh usage.
