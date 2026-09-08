/* func_80188990 — shared body (overlay slot 0x80128158, h_exact c539b69f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012B030(u8 *a0);
extern void func_8012CBCC(s32);
extern void func_80131C78(s32 a0);
extern s32 func_80143B6C(s32 a0, s32 a1);
extern void func_800291C8(s32, s32);
extern s32 D_801D46D8;
extern s32 D_801D46DC;
void func_80188990(s32 a0) {
    s32 pad[4];
    switch (*(u8 *)(a0 + 0xC2)) {
    case 0:
        D_801D46D8 = ((s32 (*)(s32))func_8012CBCC)(a0);
        if (D_801D46D8 & 0x6000) {
            if (D_801D46D8 & 0x1000) {
                *(s16 *)(a0 + 0x2) = 2;
                *(u8 *)(a0 + 0xC1) = 0;
                *(s16 *)(a0 + 0x5E) = 0;
                *(s32 *)(a0 + 0x1C) = 0x30;
                func_8002D4C8(0x7DF, 0);
                func_800291C8(0xA, *(s16 *)(a0 + 0xFE));
                return;
            }
            func_8002D4C8(0x754, 0);
            func_80143B6C(a0, 1);
            *(u8 *)(a0 + 0xC2) = 1;
            *(s32 *)(a0 + 0x14) = 0xFFF30000;
            *(s32 *)(a0 + 0x1C) = 0;
            *(s32 *)(a0 + 0x10) = *(s32 *)(a0 + 0x10) >> 2;
            *(s32 *)(a0 + 0x18) = *(s32 *)(a0 + 0x18) >> 2;
        }
        *(s32 *)(a0 + 0x1C) += 1;
        if (*(s32 *)(a0 + 0x1C) >= 0x78) {
            func_80131C78(a0);
            *(s16 *)(a0 + 0x2) = 2;
            *(s32 *)(a0 + 0x1C) = 1;
        }
        break;
    case 1:
        D_801D46DC = *(s32 *)(a0 + 0x14);
        D_801D46D8 = ((s32 (*)(s32))func_8012CBCC)(a0);
        if (D_801D46D8 & 0x6000) {
            if (D_801D46D8 & 0x1000) {
                *(s16 *)(a0 + 0x2) = 2;
                *(u8 *)(a0 + 0xC1) = 0;
                *(s16 *)(a0 + 0x5E) = 0;
                *(s32 *)(a0 + 0x1C) = 0x30;
                func_8002D4C8(0x7DF, 0);
                func_800291C8(0xA, *(s16 *)(a0 + 0xFE));
                return;
            }
            {
                s32 t;
                func_8002D4C8(0x754, 0);
                func_80143B6C(a0, 1);
                t = D_801D46DC;
                *(u8 *)(a0 + 0xC2) = 2;
                *(s32 *)(a0 + 0x1C) = 0;
                *(s32 *)(a0 + 0x14) = -t;
            }
        }
        *(s32 *)(a0 + 0x1C) += 1;
        if (*(s32 *)(a0 + 0x1C) >= 0x28) {
            func_80131C78(a0);
            *(s16 *)(a0 + 0x2) = 2;
            *(s32 *)(a0 + 0x1C) = 1;
        }
        break;
    case 2:
        *(s32 *)(a0 + 0x10) = (*(s32 *)(a0 + 0x10) * 15) >> 4;
        *(s32 *)(a0 + 0x18) = (*(s32 *)(a0 + 0x18) * 15) >> 4;
        D_801D46D8 = ((s32 (*)(s32))func_8012CBCC)(a0);
        if (D_801D46D8 & 0x6000) {
            *(s32 *)(a0 + 0x14) = 0;
            if (D_801D46D8 & 0x1000) {
                *(s16 *)(a0 + 0x2) = 2;
                *(u8 *)(a0 + 0xC1) = 0;
                *(s16 *)(a0 + 0x5E) = 0;
                *(s32 *)(a0 + 0x1C) = 0x30;
                func_8002D4C8(0x7DF, 0);
                func_800291C8(0xA, *(s16 *)(a0 + 0xFE));
                return;
            }
            if (!(*(u16 *)(a0 + 0x84) & 1)) {
                *(u16 *)(a0 + 0x84) |= 1;
                func_8002D4C8(0x754, 0);
            }
            if ((*(s32 *)(a0 + 0x1C) & 3) == 3) {
                func_80143B6C(a0, 1);
            }
            *(s32 *)(a0 + 0x1C) += 1;
            if (*(s32 *)(a0 + 0x1C) >= 0x11) {
                func_80131C78(a0);
                func_8012B030((u8 *)a0);
                *(s16 *)(a0 + 0x2) = 1;
                *(u16 *)(a0 + 0x84) &= 0xFFFE;
            }
        }
        break;
    }
    *(s16 *)(a0 + 0x108) = *(u16 *)(a0 + 0x108) - 1;
    if (*(s16 *)(a0 + 0x108) == 0) {
        func_800291C8(0xA, *(s16 *)(a0 + 0xFE));
    }
}
