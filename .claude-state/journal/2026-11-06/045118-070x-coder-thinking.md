---
ts: 2026-11-06T11:51:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_x2CH9qXraP2QXS0ngmZR
---
Item 2: func_80016224 in src/800.c:2911-2966. Kinds barrier,launder. Let me extract and calibrate.

The body:
```
void func_80016224(s32 a0, s32 a1)
{
    extern struct { s32 a; s32 b[4]; } D_800A651C[];
    extern struct { s32 a; s32 b[4]; } D_800AE7BC[];
    extern u8 D_800AE7B8[];

    void *p;
    s16 xl, xr, yl, yr;
    s32 idx;

    p = func_80010A08(0x18);
    *(u8 *)((u8 *)p + 3) = 5;
    *(u8 *)((u8 *)p + 7) = 0x2A;
    *(u8 *)((u8 *)p + 6) = a0;
    *(u8 *)((u8 *)p + 5) = a0;
    *(u8 *)((u8 *)p + 4) = a0;
    xl = -(s32)D_800AF7BC / 2;
    *(s16 *)((u8 *)p + 0x10) = xl;
    *(s16 *)((u8 *)p + 0x08) = xl;
    BARRIER
    xr = D_800AF7BC / 2;
    *(s16 *)((u8 *)p + 0x14) = xr;
    *(s16 *)((u8 *)p + 0x0C) = xr;
    yl = -(s32)D_800AF7BE / 2;
    *(s16 *)((u8 *)p + 0x0E) = yl;
    *(s16 *)((u8 *)p + 0x0A) = yl;
    BARRIER
    yr = D_800AF7BE / 2;
    idx = a1 & 0xFFFF;
    *(s16 *)((u8 *)p + 0x16) = yr;
    *(s16 *)((u8 *)p + 0x12) = yr;
    if (idx != 0) {
        u32 m24 = 0x00FFFFFF;
        u32 mFF = 0xFF000000;
        register s32 i4 __asm__("$6") = idx * 4;
        register u32 pv __asm__("$4");
        pv = *(u32 *)p;
        *(u32 *)p = (pv & mFF) | (*(u32 *)(i4 + D_800A651C[D_800B9A02].a) & m24);
        i4 += D_800A651C[D_800B9A02].a;
        *(u32 *)i4 = (*(u32 *)i4 & mFF) | ((u32)p & m24);
        func_80016638(&D_800A6518[D_800B9A02 * 20], idx, 2);
    } else {
        u32 m24 = 0x00FFFFFF;
        register u32 pv __asm__("$3");
        u32 *ot;
        pv = *(u32 *)p;
        *(u32 *)p = (pv & 0xFF000000) | (*(u32 *)D_800AE7BC[D_800B9A02].a & m24);
        __asm__ __volatile__("" : "=r"(pv));
        ot = (u32 *)D_800AE7BC[D_800B9A02].a;
        *ot = (*ot & 0xFF000000) | ((u32)p & m24);
        func_80016638(&D_800AE7B8[D_800B9A02 * 20], 0, 2);
    }
}
```
Levers: 2 barriers (memory), 1 launder (out-only pv in the else branch). Pins: $6 i4, $4 pv, $3 pv — pins may stay.

So the target: remove the 2 barriers and the 1 launder; keep pins.

Let me extract orig.c (lines 2911-2966), calibrate, then v0 = remove barriers+launder, score.

Note: this function's decls are file-scope externs at 2904-2909; body starts at 2911.

Let me do it.
