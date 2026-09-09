/* func_80164530 — shared body (overlay slot 0x80128158, h_exact 9aa82e98). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_80012A60(s32 a0, s32 a1);
extern s32 func_80012DBC(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80047D3C(s32 a0);
extern s32 ratan2(s32 a0, s32 a1);
extern u8 D_801202A0[];
extern u8 D_800AF630[];
void func_80164530(s32 arg0) {
    u8 *p;
    s32 s0;
    u8 *unaff_s5;
    s32 unaff_s6;
    u8 *base;
    s32 iVar9;
    s16 sVar4;
    s32 ix, iy, dist;
    sVar4 = 0x1000;
    base = D_800AF630;
    p = D_801202A0;
    iVar9 = *(s32 *)(arg0 + 0x20);
    for (; p < D_801202A0 + 0x6480; p += 0x10C) {
        if ((*(u16 *)(p + 0x5C) & 0x2000) != 0) {
            s32 r2;
            s0 = func_8014C59C((void *)arg0, (void *)p);
            r2 = func_80012A60((s32)(s16)s0, (s32)*(s16 *)(iVar9 + 0x12));
            if (((s16)r2 < 0x200) && ((s16)r2 < sVar4)) {
                unaff_s6 = s0;
                sVar4 = r2;
                unaff_s5 = p;
            }
        }
    }
    if (sVar4 != 0x1000) {
        *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12) =
            (s16)func_80012DBC((s32)*(s16 *)(iVar9 + 0x12), (s32)(s16)unaff_s6, 10, 1);
        if (*(s16 *)(base + 0xA3D8) == 0x30A0) {
            u32 uVar7 = *(u32 *)(unaff_s5 + 0x58) & 0xFFFFFFF;
            if (uVar7 != 0) {
                iy = (s32)((((u32)*(u16 *)(unaff_s5 + 0xE) +
                             ((s32)*(s16 *)(uVar7 + 0xC) + (s32)*(s16 *)(uVar7 + 0xE)) / 2) -
                            (u32)*(u16 *)(arg0 + 0xE)) << 16) >> 16;
                ix = (s32)((((u32)*(u16 *)(unaff_s5 + 0x6) +
                             ((s32)*(s16 *)(uVar7 + 0x4) + (s32)*(s16 *)(uVar7 + 0x6)) / 2) -
                            (u32)*(u16 *)(arg0 + 0x6)) << 16) >> 16;
                dist = func_80047D3C(iy * iy + ix * ix);
                s0 = ratan2(((s32)*(s16 *)(unaff_s5 + 0xA) +
                             ((s32)*(s16 *)(uVar7 + 0x8) + (s32)*(s16 *)(uVar7 + 0xA)) / 2) -
                            (s32)*(s16 *)(arg0 + 0xA),
                            (s32)(s16)dist) & 0xFFF;
                *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x10) = (u16)s0;
            }
        }
    }
}
