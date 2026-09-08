/* func_80187354 — shared body (overlay slot 0x80128158, h_exact de9edbad). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_8018F424[3];
extern s32 D_8018F430[];
extern s16 D_8018F3E4[];
extern void func_80188C0C();
void func_80187354(s32 a0) {
    s16 buf[3];
    s16 vec[3];
    s32 i;
    buf[0] = *(u16 *)(a0 + 0x6) - 0xE1;
    buf[1] = *(u16 *)(a0 + 0xA) + 0x40;
    buf[2] = *(u16 *)(a0 + 0xE) - 0x75;
    for (i = 0; i < 16; i++) {
        vec[1] = buf[1] + D_8018F424[rand() % 3];
        vec[2] = buf[2] + D_8018F430[rand() % 5];
        vec[0] = buf[0] + i * 0x20;
        func_80188C0C(vec, *(s16 *)((s32)D_8018F3E4 + i * 4));
    }
}
