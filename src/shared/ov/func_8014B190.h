/* func_8014B190 — shared body (overlay slot 0x80128158, h_exact 4491a46e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8016F1C4(void);
extern u8 D_80078E78[];
extern s16 D_80078E96;
extern s16 D_80078EB8;
extern u16 D_80078EA6;
extern u8 D_80078EC1;
void func_8014B190(s32 s0) {
    s16 *s1 = (s16 *)D_80078E78;
    s32 v0;
    *(s16 *)(s0 + 0x68) = 0x1000;
    *(s16 *)(s0 + 0x6A) = 0x1000;
    *(s16 *)(s0 + 0x6C) = 0x1000;
    v0 = *(s32 *)(s0 + 0x44) & -0x201;
    v0 = v0 & -0x401;
    *(s32 *)(s0 + 0x44) = v0;
    v0 = func_8016F1C4();
    if (v0) {
        return;
    }
    if (*(u16 *)(s0 + 0x0) == 0x1E) {
        return;
    }
    if (*(u16 *)(s0 + 0x0) == 0x1A) {
        return;
    }
    if ((D_80078E96 & 0x8000) ||
        ((u16)D_80078EB8 < 0xB) ||
        ((s16)D_80078EA6 < 0x10) ||
        (D_80078EC1 == 0x1)) {
        *(s32 *)(s0 + 0x44) |= 0x200;
    }
    if (*(s16 *)((s32)s1 + 0x22) & 0x8000) {
        *(s16 *)(s0 + 0x68) = 0x555;
        *(s16 *)(s0 + 0x6A) = 0x555;
        *(s16 *)(s0 + 0x6C) = 0x555;
        *(s32 *)(s0 + 0x44) |= 0x400;
    }
}
