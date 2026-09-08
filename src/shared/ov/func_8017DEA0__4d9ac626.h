/* func_8017DEA0 — shared body (overlay slot 0x80128158, h_exact 4d9ac626). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
    extern void func_800D1E28(void);
    extern void func_8002D4C8(s32, s32);
    extern void func_8001BFD0(void);
    extern s32 func_800291B4(s32);
    extern s32 func_80029524(void);
    extern void func_800D0C48(s32);
    s32 func_8017DEA0(s32 param_1) {
        if ((*(s32 *)(param_1 + 0x28) = *(s32 *)(param_1 + 0x28) - 1) == -1) {
            ((s32 (*)(void))func_800D1E28)();
            ((s32 (*)(s32, s32))func_8002D4C8)(0x1C, 0);
            ((s32 (*)(void))func_8001BFD0)();
            if ((func_800291B4(0xCE) & 0xFF) == 0 && func_80029524() == 0) {
                ((s32 (*)(s32))func_800D0C48)(1);
            }
            *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
        }
        return 0;
    }
