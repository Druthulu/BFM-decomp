/* func_8014B944 — shared body (overlay slot 0x80128158, h_exact 7918269a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80029178(s32 arg);
extern u8 D_80078E78[];
extern s32 D_80078EA4;
extern u16 D_80078EA6;
void func_8014B944(s32 a0, s32 a1, s32 a2)
{
    u8 *base = D_80078E78;
    if (a2 != 0) {
        D_80078EA4 += a1;
        __asm__ __volatile__("" ::: "memory");
        if ((s16)D_80078EA6 >= 0xA1) {
            D_80078EA4 = 0xA00000;
        }
    } else {
        if ((func_80029178(0x1B) & 0xFF) != 0) {
            D_80078EA4 += a1;
            __asm__ __volatile__("" ::: "memory");
            if ((s16)D_80078EA6 >= 0xA1) {
                D_80078EA4 = 0xA00000;
            }
        } else {
            if ((s16)D_80078EA6 < 0x80) {
                D_80078EA4 += a1;
                __asm__ __volatile__("" ::: "memory");
                if ((s16)D_80078EA6 >= 0x81) {
                    D_80078EA4 = 0x800000;
                }
            }
        }
    }
    if (a2 != 0) {
        *(s32 *)(base + 0x60) += a1;
        if (*(s16 *)(base + 0x62) >= 0xA1) {
            *(s32 *)(base + 0x60) = 0xA00000;
        }
    } else {
        if ((func_80029178(0x1B) & 0xFF) != 0) {
            *(s32 *)(base + 0x60) += a1;
            if (*(s16 *)(base + 0x62) >= 0xA1) {
                *(s32 *)(base + 0x60) = 0xA00000;
            }
        } else {
            if (*(s16 *)(base + 0x62) < 0x80) {
                *(s32 *)(base + 0x60) += a1;
                if (*(s16 *)(base + 0x62) >= 0x81) {
                    *(s32 *)(base + 0x60) = 0x800000;
                }
            }
        }
    }
}
