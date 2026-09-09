/* func_8014B7A4 — shared body (overlay slot 0x80128158, h_exact 1193dabf). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8016F1C4(void);
extern s32 func_80029178(s32 arg);
extern void func_8014B944(s32 a0, s32 a1, s32 a2);
extern u8 D_800AF630[];
extern u8 D_80078E78[];
extern s16 currentLocationId;
extern s32 D_80078EA4;
void func_8014B7A4(s16 *param_1) {
    s32 s0 = (s32)param_1;
    u8 *s2 = D_800AF630;
    s32 s1 = (s32)D_80078E78;
    s32 v0;
    s32 v1;
    if (func_8016F1C4() != 0) {
        return;
    }
    if (*(u16 *)s0 == 0x1E) {
        return;
    }
    if (*(u16 *)s0 == 0x1A) {
        return;
    }
    if (*(s32 *)(s0 + 0x44) & 0x10) {
        return;
    }
    if (*(s32 *)(s0 + 0x44) & 0x80) {
        if ((func_80029178(0x1B) & 0xFF) != 0) {
            func_8014B944(s0, 0x2D80, 0);
        } else {
            func_8014B944(s0, 0x16C0, 0);
        }
    } else {
        v1 = currentLocationId;
        if (v1 == 0x3024) goto check_end;
        if (v1 == 0x3042) goto check_end;
        if (v1 == 0x3067) goto check_end;
        if (v1 == 0x3075) goto check_end;
        if ((func_80029178(0x21) & 0xFF) != 0) {
            D_80078EA4 = D_80078EA4 - 0xF2;
        } else {
            D_80078EA4 = D_80078EA4 - 0x16C;
        }
    }
check_end:
    if (*(s32 *)(s1 + 0x2C) < 0) {
        *(s32 *)(s1 + 0x2C) = 0;
        if (*(s32 *)(s0 + 0x44) & 0x80) {
            v1 = 0xAAA8;
            v0 = *(s32 *)(s1 + 0x30) + v1;
        } else {
            v0 = *(s32 *)(s1 + 0x30) + 0x1555;
        }
        *(s32 *)(s1 + 0x30) = v0;
        if (*(s16 *)(s1 + 0x32) >= 0x3C) {
            *(s32 *)(s1 + 0x30) = 0;
            if (*(s16 *)(s2 + 0xA3D8) != 0x3051) {
                *(s32 *)(s0 + 0x44) = *(s32 *)(s0 + 0x44) | 0x100;
            }
        }
    }
    return;
}
