/* func_8014BB24 — shared body (overlay slot 0x80128158, h_exact 79d6924b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80029178(s32 a0);
extern u8 D_80078E78[];
extern s16 D_80078EB4;
void func_8014BB24(s32 a0, s32 a1, s32 a2)
{
    u8 *base = D_80078E78;
    u16 cur;
    if (a2 != 0) {
        D_80078EB4 = (u16)D_80078EB4 + a1;
    } else {
        if ((func_80029178(0x1B) & 0xFF) != 0) {
            cur = D_80078EB4;
            if (cur < 0x3E7) {
                D_80078EB4 = cur + a1;
                if ((u16)(cur + a1) >= 0x3E8) {
                    D_80078EB4 = 0x3E7;
                }
            }
        } else {
            cur = D_80078EB4;
            if (cur < 0x1F4) {
                D_80078EB4 = cur + a1;
                if ((u16)(cur + a1) >= 0x1F5) {
                    D_80078EB4 = 0x1F4;
                }
            }
        }
    }
    if (*(u16 *)(base + 0x3A) < *(u16 *)(base + 0x3C)) {
        *(u16 *)(base + 0x3C) = *(u16 *)(base + 0x3A);
    }
}
