/* func_801564B0 — shared body (overlay slot 0x80128158, h_exact bb99dfa8). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 rand(void);
extern s32 func_8002A1B4(void);
extern s32 func_8002A400(void);
extern s32 func_8002A670(void);
extern s32 func_8002A8E0(void);
extern u8 D_80078E78[];
s32 func_801564B0(s32 a0) {
    s32 s0 = (s32)D_80078E78;
    s32 v1;
    if (*(s32 *)(a0 + 0x44) & 0x200) {
        if (rand() & 0x1) {
            return 0x8000;
        }
    }
    if (func_8002A1B4() || func_8002A400() || func_8002A670() || func_8002A8E0()) {
        if ((rand() & 0x3) == 0) {
            return 0x8000;
        }
    }
    if ((rand() & 0x3) != 0) {
        return 0;
    }
    v1 = rand() % 160 & 0xFFFF;
    if ((u32)v1 < 0x51) {
        return 0;
    }
    if (v1 >= *(s16 *)(s0 + 0x2E)) {
        /* LOAD-BEARING: empty volatile asm blocks gcc's noce store-flag
           if-conversion (it would fold "cond ? 0x8000 : 0" to (slt)<<15);
           the original kept the slt+branch form. */
        __asm__ __volatile__("");
        return 0;
    }
    return 0x8000;
}
