/* func_8015B7B4 — shared body (overlay slot 0x80128158, h_exact 0c167617). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80149B54(s32 *a0);
extern void func_80156648(s32 *a0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80147324(s32 a0);
extern void func_80147300(u16 arg0);
extern u8 D_800D4F8C[];
s32 func_8015B7B4(s32 a0) {
    s32 s0 = a0;
    if (func_80149B54((s32 *)s0) != 0) {
        func_80156648((s32 *)s0);
        *(s8 *)(s0 + 0x1AA) = 0xC;
        *(s32 *)(s0 + 0x44) = *(s32 *)(s0 + 0x44) | 0x2;
        *(s32 *)(s0 + 0x23C) = *(s32 *)(s0 + 0xB4);
        *(s8 *)(s0 + 0x244) = *(u8 *)(s0 + 0xBC);
        func_80154274((s32 *)s0, (s32)D_800D4F8C);
        func_80154A74(s0, 0x22);
        *(s8 *)(s0 + 0xDA) = 0;
        func_80146994(5, s0, 5, 0);
        func_80147324(0x455);
        func_80147300(0x5F3);
        return 1;
    }
    return 0;
}
