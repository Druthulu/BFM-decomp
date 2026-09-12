/* func_80130A18 — shared body (overlay slot 0x80128158, h_exact f655639f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80131CA8();  // K&R: 2 of 1 args (P37 unalias t4_ua7)
extern s32 func_80133784(s32 a0, void *a1, s32 a2);
void func_80130A18(u8 *a0) {
    s16 b1[4];
    s16 b2[4];
    *(u16 *)(a0 + 0x5C) = *(u16 *)(a0 + 0x5C) & 0xFFFE;
    if (((s32 (*)(int, int))func_80131CA8)((int)a0, 0x34) != 0) {
        return;
    }
    b1[0] = *(u16 *)(a0 + 6);
    b1[1] = *(u16 *)(a0 + 0xA) - 0x10;
    b1[2] = *(u16 *)(a0 + 0xE);
    b2[0] = *(u16 *)(a0 + 6);
    b2[1] = *(u16 *)(a0 + 0xA) + 8;
    b2[2] = *(u16 *)(a0 + 0xE);
    if ((func_80133784(0x11, b1, (s32)b2) & 0x6000) != 0) {
        *(s8 *)(a0 + 0xC1) = 0x11;
        *(s16 *)(a0 + 0xAC) = 0x78;
    }
}
