/* func_80154F9C — shared body (overlay slot 0x80128158, h_exact 9fb7a0c8). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_80078E78[];
extern s16 D_80078E96;
extern s16 D_80078E9E;
extern u16 D_80078EA6;
extern u8 D_800D8D10[];
extern s32 func_8016F1AC(void);
extern void func_801550FC(s32 a0);
void func_80154F9C(s32 a0) {
    u8 *base = D_80078E78;
    if (*(s32 *)(a0 + 0xC8) & 0x1000000) {
        if ((D_80078E96 & 0x8000) || D_80078E9E < 0x10 || (s16)D_80078EA6 < 0x10) {
            if (func_8016F1AC() == 0) {
                return;
            }
        }
        *(s32 *)(a0 + 0xC8) = *(s32 *)(a0 + 0xC8) & 0xC0FFFFFF;
        func_801550FC(*(s32 *)(a0 + 0xC8));
    } else {
        if ((D_80078E96 & 0x8000) && func_8016F1AC() == 0) {
            *(s32 *)(a0 + 0xC8) = *(s32 *)(a0 + 0xC8) | 0x1000000;
            func_801550FC((s32)D_800D8D10);
            return;
        }
        if (!(*(s16 *)(base + 0x26) < 0x10) && !(*(s16 *)(base + 0x2E) < 0x10)) {
            return;
        }
        if (*(s32 *)(a0 + 0x44) & 0xC0) {
            return;
        }
        if (func_8016F1AC() != 0) {
            return;
        }
        *(s32 *)(a0 + 0xC8) = *(s32 *)(a0 + 0xC8) | 0x1000000;
        func_801550FC(0x40000002);
    }
}
