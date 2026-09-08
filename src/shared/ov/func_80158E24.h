/* func_80158E24 — shared body (overlay slot 0x80128158, h_exact a6b2616c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u16 func_801487F4(s32 *a0);
extern s32 func_80159434(s32 a0, s32 a1);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_80146CA0(void *a0);
extern M2C_UNK D_800D5904;
void func_80158E24(s32 *a0) {
    s32 n;
    s32 c;
    c = 0x4C000;
    n = 1;
    if (func_801487F4(a0) & 0xF0) {
        n = 4;
    }
    while (n > 0) {
        func_80159434((s32)a0, c);
        if (*(s16 *)(a0[0x20 / 4] + 0x10) < 0xC00) {
            *(s16 *)(a0[0x20 / 4] + 0x10) = 0xC00;
            func_80154274(a0, (s32)&D_800D5904);
            func_80154A74((s32)a0, 0x20);
            func_8002D4C8(0x2A, 0);
            func_8002D4C8(0x1C, 0);
            func_80146CA0(a0);
            n = 0;
        }
        n--;
    }
}
