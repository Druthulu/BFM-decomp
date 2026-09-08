/* func_80187738 — shared body (overlay slot 0x80128158, h_exact 6f24f1e1). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B200(u8 *a0);
extern u8 D_801E0CBC;
extern u8 D_801E087C;
extern u8 D_801E0B5C;
extern M2C_UNK D_8018AF28;
extern u16 D_800B99DC;
void func_80187738(s32 param_1) {
    s32 v0;
    s16 v1;
    void *a1;
    s32 rng;
    s32 t2;
    s32 t72;
    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)param_1);
        return;
    }
    a1 = &D_801E0CBC;
    v1 = *(s16 *)(param_1 + 0x70);
    if (v1 == 0) {
        a1 = &D_801E087C;
    } else if (v1 == 1) {
        a1 = &D_801E0B5C;
    }
    func_8001C214(*(s32 *)(param_1 + 0x20), (s32)a1);
    func_8001D0E8(*(s32 *)(param_1 + 0x20), 0x140, 0xF0);
    func_8012A828(param_1, &D_8018AF28);
    func_8012B200((u8 *)param_1);
    *(s32 *)(param_1 + 0x18) = 0xFFDBC000;
    *(s32 *)(param_1 + 0x14) = 0xFFF40000;
    rng = D_800B99DC;
    t2  = *(u16 *)(param_1 + 2);
    t72 = *(s16 *)(param_1 + 0x72);
    *(s32 *)(param_1 + 0x44) = 0;
    *(s32 *)(param_1 + 0x48) = 0x80000;
    *(s32 *)(param_1 + 0x4C) = 0;
    t2 = t2 + 1;
    rng = rng & 0x1F;
    *(s16 *)(param_1 + 0x12) = 0xF - rng;
    *(s32 *)(param_1 + 0x48) = t72 + 0x80000;
    *(s16 *)(param_1 + 2) = t2;
}
