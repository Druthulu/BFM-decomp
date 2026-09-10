/* func_80156044 — shared body (overlay slot 0x80128158, h_exact 8f5b4545). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80156044(int param_1, int param_2) {
    extern u32 func_8015616C(s32 a0, u16 a1);
    extern void func_80156670(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
    extern void func_801567BC(s32 a0);
    extern void func_80156848(s32 a0, s32 a1, s32 a2);
    extern void func_80156A88(s32 a0, s32 a1);
    extern s32 func_801565C0(s32 a0);
    extern u8 D_80180AEC;
    extern u8 D_80180B00;
    extern u8 D_80180984;

    u8 *puVar4;
    s32 uVar1;

    if (((u32)param_2) & 0x10000) {
        puVar4 = &D_80180AEC + (((u32)param_2) & 0xffff) * 0x14;
    } else if (((u32)param_2) & 0x20000) {
        puVar4 = &D_80180B00 + (((u32)param_2) & 0xffff) * 0x14;
    } else {
        puVar4 = &D_80180984 + (((u32)param_2) & 0xffff) * 0x14;
    }
    uVar1 = func_8015616C(((s32)param_1), *(u16 *)puVar4) & 0xffff;
    if (*(u8 *)(((s32)param_1) + 0x1a8) != 0) {
        func_80156670(((s32)param_1), *(s32 *)puVar4, uVar1, *(s32 *)(puVar4 + 4),
                      *(u8 *)(puVar4 + 0xA), *(u16 *)(puVar4 + 0x12));
        if (*(u8 *)(puVar4 + 0x10) != 0) {
            func_801567BC(((s32)param_1));
        }
        func_80156848(((s32)param_1), (s32)puVar4, uVar1);
        func_80156A88(((s32)param_1), (s32)puVar4);
        if (func_801565C0(((s32)param_1)) != 0) {
            *(u8 *)(((s32)param_1) + 0x1c0) = 1;
        }
    }
}
