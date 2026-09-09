/* func_8016B114 — shared body (overlay slot 0x80128158, h_exact 2f685822). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8016B234();
extern void func_800D22E4(s32 a0);
extern void func_80146C3C();
void func_8016B114(void *arg0)
{
    s32 s1;
    u32 state;
    s32 cv;
    s1 = *(s32 *)((u8 *)arg0 + 0x20);
    if ((u32)*(s32 *)((u8 *)arg0 + 0x2C) < 6U) {
        func_8016B234();
    }
    state = *(u32 *)((u8 *)arg0 + 0x2C);
    switch (state) {
    case 6:
    case 7:
        cv = *(u8 *)((u8 *)s1 + 0x26) - 0x10;
        *(u8 *)((u8 *)s1 + 0x26) = cv;
        *(u8 *)((u8 *)s1 + 0x25) = cv;
        *(u8 *)((u8 *)s1 + 0x24) = cv;
        *(u16 *)((u8 *)arg0 + 0xA) = *(u16 *)((u8 *)arg0 + 0xA) - 2;
        break;
    case 1:
    case 5:
    {
        s32 r26;
        s32 r14;
        s32 r24;
        func_800D22E4((s32)arg0);
        r26 = *(u16 *)((u8 *)arg0 + 0x26);
        r14 = *(s32 *)((u8 *)arg0 + 0x14);
        r24 = *(u16 *)((u8 *)arg0 + 0x24);
        r26 += 1;
        r14 += 0x18000;
        r24 -= 0x10;
        *(s32 *)((u8 *)arg0 + 0x14) = r14;
        *(u16 *)((u8 *)arg0 + 0x26) = r26;
        *(u16 *)((u8 *)arg0 + 0x24) = r24;
        break;
    }
    default:
    {
        s32 d26;
        s32 dA;
        s32 d24;
        d26 = *(u16 *)((u8 *)arg0 + 0x26);
        dA  = *(u16 *)((u8 *)arg0 + 0xA);
        d24 = *(u16 *)((u8 *)arg0 + 0x24);
        d26 += 1;
        dA  -= 2;
        d24 -= 0x10;
        *(u16 *)((u8 *)arg0 + 0xA) = dA;
        *(u16 *)((u8 *)arg0 + 0x26) = d26;
        *(u16 *)((u8 *)arg0 + 0x24) = d24;
        break;
    }
    }
    cv = *(s32 *)((u8 *)arg0 + 0x1C) - 1;
    *(s32 *)((u8 *)arg0 + 0x1C) = cv;
    if (cv == 0) {
        ((void (*)(s32))func_80146C3C)((s32)arg0);
    }
}
