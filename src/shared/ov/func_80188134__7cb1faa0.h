/* func_80188134 — shared body (overlay slot 0x80128158, h_exact 7cb1faa0). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u16 D_800B99DC;
extern s32 D_8018F48C;
extern u8 D_801A7604;
extern u8 D_801A766C;
extern void func_8012B2CC(s32 a0);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_80142414(s32 a0, s16 a1);
void func_80188134(s32 a0) {
    s32 s0 = a0;
    s32 v0;
    s32 v1;
    v0 = *(s32 *)(s0 + 0xDC) - 1;
    *(s32 *)(s0 + 0xDC) = v0;
    if (v0 == 0 ||
        *(s16 *)(*(s32 *)(s0 + 0x64) + 0xE) < *(s16 *)(s0 + 0xE) + *(s32 *)(s0 + 0xE8)) {
        if (*(s16 *)(s0 + 0x6) < 0) {
            v0 = -(s32)*(u8 *)&D_800B99DC;
            v1 = *(s32 *)(s0 + 0x20);
        } else {
            v1 = *(s32 *)(s0 + 0x20);
            v0 = *(u8 *)&D_800B99DC;
        }
        do { *(s16 *)(v1 + 0x12) = v0; } while (0);
        func_8012B2CC(s0);
        func_8012B14C(s0, (s32)&D_8018F48C);
        if (*(s16 *)(s0 + 0x70) == 0) {
            func_8012A828(s0, &D_801A7604);
        } else {
            func_8012A828(s0, &D_801A766C);
        }
        *(s32 *)(s0 + 0xE4) = 4;
        *(u16 *)(s0 + 0x2) = *(u16 *)(s0 + 0x2) + 1;
    }
    if (*(s32 *)(s0 + 0xE4) == 0) {
        if (*(s16 *)(*(s32 *)(s0 + 0x64) + 0xE) < *(s16 *)(s0 + 0xE) + 0x220) {
            func_80142414(s0, -0x96);
            *(s32 *)(s0 + 0xE4) = 1;
        }
    }
}
