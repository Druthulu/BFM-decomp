/* func_801EF544 — shared body (module slot 0x801EF468, h_exact f054e0c4). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_800D1E28(void);
extern s32 guess_RequestSound(s32, s32);
extern void func_8001BFD0(void);
extern s32 guess_GetGameVarByte(s32);
extern void func_800D0C48(s32);
s32 func_801EF544(s32 param_1) {
    if ((*(s32 *)(param_1 + 0x28) = *(s32 *)(param_1 + 0x28) - 1) == -1) {
        func_800D1E28();
        guess_RequestSound(0x1C, 0);
        func_8001BFD0();
        if ((guess_GetGameVarByte(0xCE) & 0xFF) == 0) {
            guess_RequestSound(0x1D, 0);
            func_800D0C48(1);
        }
        *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    }
    return 0;
}
