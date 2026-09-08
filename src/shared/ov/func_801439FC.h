/* func_801439FC — shared body (overlay slot 0x80128158, h_exact 8890d24d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80016714(void *a0, s32 a1);
extern void func_8012C218(void *a0);
extern s32 func_80134510(s32 arg);
extern s32 ratan2(s32 a0, s32 a1);
extern s16 D_801152AC;
extern s16 D_801152AA;
extern u8 D_801152A8[];
void func_801439FC(s32 a0) {
    s32 s1 = *(s32 *)(a0 + 0x64);
    s32 s0 = *(s32 *)(a0 + 0xCC);
    s16 sp[3];
    s32 v0;
    if (*(s16 *)(s1 + 0x36) != *(s16 *)(a0 + 0xFC)) {
        if (a0 == 0) {
            return;
        }
        func_80016714((void *)s0, 0x38);
        func_8012C218((void *)a0);
        return;
    }
    sp[0] = *(u16 *)(s1 + 6);
    sp[1] = *(u16 *)(s1 + 0xA) - 0x10;
    sp[2] = *(u16 *)(s1 + 0xE);
    if (func_80134510((s32)&sp[0]) == 0) {
        *(s32 *)(s0 + 4) = *(s32 *)(s0 + 4) | 0x80000000;
        return;
    }
    *(s16 *)(s0 + 8) = sp[0];
    *(s16 *)(s0 + 0xA) = sp[1];
    *(s16 *)(s0 + 0xC) = sp[2];
    *(s32 *)(s0 + 4) = *(s32 *)(s0 + 4) & 0x7FFFFFFF;
    *(s16 *)(s0 + 0x10) = ratan2(D_801152AC, D_801152AA) + 0x400;
    *(s16 *)(s0 + 0x12) = ratan2(*(s16 *)D_801152A8, D_801152AA);
    v0 = *(s32 *)(s1 + 0x20);
    *(s16 *)(s0 + 0x14) = -(*(u16 *)(v0 + 0x12));
}
