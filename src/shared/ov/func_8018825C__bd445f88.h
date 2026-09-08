/* func_8018825C — shared body (overlay slot 0x80128158, h_exact bd445f88). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8012C588(s32 a0, s32 a1);
extern s32 func_8012B030(u8 *a0);
extern s32 func_80143B6C(s32 a0, s32 a1);
extern void func_8012B23C(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012CBCC(s32 a0);
extern s32 func_801884FC();
extern void func_8002D4C8(s32 a0, s32 a1);
extern u8 D_8018F498[];
extern u8 D_8018F47C[];
extern u8 D_801A68A4[];
void func_8018825C(s32 param_1) {
    s32 deadLocals[4];
    s32 v0;
    s32 entity;
    s32 other;
    s32 r;
    v0 = *(s32 *)(param_1 + 0xE0) - 1;
    *(s32 *)(param_1 + 0xE0) = v0;
    if (v0 == 0) {
        *(s32 *)(param_1 + 0x4C) = 0x4000;
    }
    if (*(s16 *)(param_1 + 0xFC) != 0) {
        entity = func_8012C588(0x3F, param_1);
        if (entity != 0) {
            *(s16 *)(param_1 + 0xFC) = 0;
            *(u16 *)(entity + 0xE) -= 0x300;
            *(s32 *)(entity + 0xDC) += 0x1E;
            *(s16 *)(entity + 0xFC) = 0;
            *(s32 *)(entity + 0x64) = *(s32 *)(param_1 + 0x64);
            func_8012B030((u8 *)entity);
        }
    }
    v0 = *(s32 *)(param_1 + 0xE4) - 1;
    *(s32 *)(param_1 + 0xE4) = v0;
    if (v0 == 0) {
        func_80143B6C(param_1, 0);
        *(s32 *)(param_1 + 0xE4) = 4;
    }
    other = *(s32 *)(param_1 + 0x64);
    if (*(s16 *)(other + 0xE) - 0x80 < *(s16 *)(param_1 + 0xE)) {
        *(s16 *)(param_1 + 0x2) = 5;
        func_8012B23C(param_1);
        func_8012A828(param_1, &D_8018F498);
        *(s32 *)(param_1 + 0x18) = 0xFFE30000;
        *(s32 *)(param_1 + 0x14) = 0xFFE50000;
        *(s32 *)(param_1 + 0xDC) = 1;
        func_8002D4C8(0x6AA, 0);
        return;
    }
    func_8012CBCC(param_1);
    r = func_801884FC(param_1);
    if (r == 1) {
        *(s32 *)(param_1 + 0x14) = 0xFFE00000;
        *(s32 *)(param_1 + 0x44) = 0;
        *(s32 *)(param_1 + 0x48) = 0x40000;
        *(s32 *)(param_1 + 0x4C) = 0;
        *(u16 *)(param_1 + 0x2) += 1;
        func_8012A828(param_1, &D_8018F47C);
        return;
    }
    if (r == 2) {
        *(s32 *)(param_1 + 0x14) = 0xFFE00000;
        *(s32 *)(param_1 + 0x44) = 0;
        *(s32 *)(param_1 + 0x48) = 0x40000;
        *(s32 *)(param_1 + 0x4C) = 0;
        func_8012A828(param_1, &D_801A68A4);
        *(s16 *)(param_1 + 0x2) = 5;
        *(s32 *)(param_1 + 0xDC) = 0x20;
    }
}
