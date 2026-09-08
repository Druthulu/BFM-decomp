/* func_80130438 — shared body (overlay slot 0x80128158, h_exact 5d57e32b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80131B14();
extern void func_80143CD4(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_800CB0E8(s32 a0);
extern s32 func_80131A34(s32 a0, s32 a1);
extern void func_80131CA8(int a0, int a1);
extern void func_80131E00(struct S80131E00 *a0, s32 a1);
extern s32 *D_80126B78;
void func_80130438(s32 a0) {
    s32 flag;
    flag = 0;
    *(u8 *)(a0 + 0xC1) = 6;
    if ((*(u32 *)(a0 + 0xB4) & 0x40) != 0) {
        flag = 1;
        func_80131B14();
        *(s32 *)(a0 + 0x1C) = 0x78;
        func_80143CD4(a0);
        func_8002D4C8(0x47B, 0);
        func_8002D4C8(0x478, 0);
        func_800CB0E8(a0);
        if (func_80131A34(a0, 0x14) == 0) {
            *(s16 *)(a0 + 0x98) = 0;
        }
    }
    if (((s32 (*)(s32, s32))func_80131CA8)(a0, 0x12) != 0) {
        flag = 1;
    }
    if (flag == 0) {
        *(s16 *)(a0 + 0x5E) = 2;
        *(s16 *)(a0 + 0x60) = 1;
        *(s16 *)(a0 + 0x62) = *(u16 *)((s32)D_80126B78 + 0x12);
        ((void (*)(s32, s32))func_80131E00)(a0, 1);
    }
}
