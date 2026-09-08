/* func_8016D848 — shared body (overlay slot 0x80128158, h_exact cc6b91ad). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80146C3C();
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_800D20C0();
void func_8016D848(s32 *a0) {
    s16 sp20[4];
    s16 sp28[4];
    s32 s2;
    s32 cnt;
    s16 i;
    s32 p;
    cnt = *(s32 *)((s32)a0 + 0x1C) - 1;
    *(s32 *)((s32)a0 + 0x1C) = cnt;
    if (cnt == 0) {
        func_80146C3C();
        return;
    }
    if (cnt < 4) {
        s2 = -0xC00;
    } else {
        s2 = 0x800;
        i = 0;
        do {
            func_80146A6C(0x33, a0, 0, 0, 0, 0x8000, 0);
            i = i + 1;
        } while (i < 5);
    }
    p = *(s32 *)((s32)a0 + 0x20);
    if ((s2 << 16) == 0) {
        *(s16 *)(p + 0x18) = *(u16 *)(p + 0x18) ^ 0x400;
        *(s16 *)(p + 0x1A) = *(u16 *)(p + 0x1A) ^ 0x200;
    } else {
        *(s16 *)(p + 0x18) = *(u16 *)(p + 0x18) + s2;
        *(s16 *)(p + 0x1A) = *(u16 *)(p + 0x1A) + s2;
    }
    sp20[0] = *(u16 *)((s32)a0 + 0x12);
    sp20[1] = *(u16 *)((s32)a0 + 0x16);
    sp20[2] = *(u16 *)((s32)a0 + 0x1A);
    func_800D20C0((s32)sp20, (s32)sp28, 0x6);
    *(s16 *)((s32)a0 + 0x6) = sp20[0];
    *(s16 *)((s32)a0 + 0xA) = sp20[1];
    *(s16 *)((s32)a0 + 0xE) = sp20[2];
}
