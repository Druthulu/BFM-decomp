/* func_8018655C — shared body (overlay slot 0x80128158, h_exact 5fb02634). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012C218(void *a0);
extern s32 func_8012CBCC(s32 a0);
extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 rand(void);
extern s32 func_8012B77C(s32 out, s32 from, s32 to);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B370(int a0);
extern void func_8012B14C(s32 a0, s32 a1);
extern u8  D_80126B5C;
extern s32 D_80126B60;
extern s32 D_80126B64;
extern u8 D_801905C4[];
extern u8 D_801905D4[];
extern u8 D_801905DC[];
void func_8018655C(s32 a0) {
    s32 sp10[4];
    s32 sp20[2];
    register s32 i __asm__("$19");
    register s32 r __asm__("$16");
    register s32 t __asm__("$18");
    s32 v;
    s32 w;
    v = *(s32 *)(a0 + 0x1C) - 1;
    *(s32 *)(a0 + 0x1C) = v;
    if (v <= 0) {
        ((void (*)(void))func_8012C218)();
        return;
    }
    sp10[0] = *(s32 *)&D_80126B5C;
    sp10[1] = D_80126B60 + 0xFFC00000;
    sp10[2] = D_80126B64;
    func_8012B77C((s32)sp20, a0 + 4, (s32)sp10);
    w = sp20[0];
    *(s16 *)(a0 + 0xFC) += func_8012B608(*(s16 *)(a0 + 0xFC), (s16)sp20[0], 0xA);
    *(s16 *)(a0 + 0xFE) += func_8012B608(*(s16 *)(a0 + 0xFE), w >> 16, 0xA);
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = *(u16 *)(a0 + 0xFC);
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = *(u16 *)(a0 + 0xFE);
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x14) = 0;
    func_8012B370(a0);
    func_8012B14C(a0, (s32)D_801905C4);
    if (func_8012CBCC(a0) != 0) {
        for (i = 0x600; i < 0xB00; i += 0x100) {
            t = func_8012C658(0x265, 2, a0);
            if (t != 0) {
                r = rand() & 7;
                *(s32 *)(t + 0x10) =
                    (-func_8004787C(*(s16 *)(a0 + 0xFE) + i) * r) << 4;
                *(s32 *)(t + 0x18) =
                    (-func_80047948(*(s16 *)(a0 + 0xFE) + i) * r) << 4;
            }
        }
        func_8012C218((void *)a0);
    } else if (func_8012D5E4(a0, (s32)D_801905D4, (s32)D_801905DC, 0x20) == 1) {
        for (i = 0x600; i < 0xB00; i += 0x100) {
            t = func_8012C658(0x265, 2, a0);
            if (t != 0) {
                r = rand() & 7;
                *(s32 *)(t + 0x10) =
                    (-func_8004787C(*(s16 *)(a0 + 0xFE) + i) * r) << 4;
                *(s32 *)(t + 0x18) =
                    (-func_80047948(*(s16 *)(a0 + 0xFE) + i) * r) << 4;
            }
        }
        func_8012C218((void *)a0);
    } else {
        if ((*(s32 *)(a0 + 0x1C) & 3) == 0) {
            func_8012C658(0x265, 2, a0);
        }
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = 0;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = 0;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x14) = *(u16 *)(a0 + 0xFE) + 0x200;
    }
}
