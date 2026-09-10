/* func_8016C188 — shared body (overlay slot 0x80128158, h_exact 467ccd9e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8016C188(s32 param)
{
    s32 s1;
    s32 s2;
    u8 *s0;
    u16 buf[3];
    s16 *pBCC;
    s16 *pBD4;
    s32 t34;

    extern void func_80015954(s32, s32);
    extern s32 func_8016C374(s32, s32, s32, s32);
    extern void func_80146C3C(void);
    extern void func_8001CD9C(s32, void *);
    extern void func_800233CC(void *, unsigned short);
    extern u8 D_8018ED7C[];
    extern s16 D_8018EDC4;
    extern s16 D_8018EDC6;
    extern s16 D_8018EDC8;
    extern s16 D_8018EDCC;
    extern s16 D_8018EDCE;
    extern s16 D_8018EDD0;
    s32 param2;
    param2 = param;

    s1 = param2;
    s2 = ((s32 (*)(void))func_801465C0)();
    *(s32 *)(s1 + 0x20) = s2;
    if (s2 != 0) {
        *(u16 *)(s1 + 0x12) = *(u16 *)(s1 + 0x6);
        *(u16 *)(s1 + 0x16) = *(u16 *)(s1 + 0xA);
        *(u16 *)(s1 + 0x1A) = *(u16 *)(s1 + 0xE);
        t34 = *(s32 *)(s1 + 0x34);
        buf[0] = *(u16 *)(s1 + 0x12);
        buf[1] = *(u16 *)(s1 + 0x16);
        buf[2] = *(u16 *)(s1 + 0x1A);
        ((void (*)(s32, void *, void *))func_80149350)(t34, buf, buf);
        ((void (*)(void *, s32))func_80015954)(buf, s1 + 4);
        s0 = D_8018ED7C;
        ((void (*)(s32, void *))func_8001CD9C)(s2, s0);
        *(s16 *)(s2 + 0x1E) = 0xCCC;
        *(s32 *)(s2 + 4) = *(s32 *)(s2 + 4) | 0x50000000;
        ((void (*)(void *, s32))func_800233CC)(s0, 0x80);
        *(s16 *)(s2 + 0x1A) = 0;
        *(s16 *)(s2 + 0x18) = 0;
        *(s16 *)(s1 + 0x10) = 0;
        pBCC = &D_8018EDC4;
        pBD4 = &D_8018EDCC;
        *pBCC = 0x20;
        D_8018EDC6 = 0x20;
        D_8018EDC8 = 0;
        *pBD4 = 0xC0;
        D_8018EDCE = 0xC0;
        D_8018EDD0 = 0;
        ((s32 (*)(s32, void *, void *, void *))func_8016C374)(s1, pBCC, pBD4, s0);
        *(u16 *)(s1 + 2) = *(u16 *)(s1 + 2) + 1;
    } else {
        ((void (*)(s32))func_80146C3C)(s1);
    }
}
