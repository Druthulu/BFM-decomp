/* func_80186FDC — shared body (overlay slot 0x80128158, h_exact edd8502e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012CBCC(s32 a0);
extern s32 func_80143B6C(s32 a0, s32 a1);
s32 func_80186FDC(s32 param_1) {
    s32 p;
    p = *(s32 *)(param_1 + 0x20);
    *(s16 *)(p + 0x12) = *(u16 *)(p + 0x12) + 0x100;
    if (((s32 (*)(void))func_8012CBCC)() != 0) {
        *(s32 *)(param_1 + 0x18) = 0xFFE80000;
        *(s32 *)(param_1 + 0x14) = 0xFFC80000;
        *(s32 *)(param_1 + 0x44) = 0;
        *(s32 *)(param_1 + 0x48) = 0x80000;
        *(s32 *)(param_1 + 0x4C) = 0;
        func_80143B6C(param_1, 0);
        *(s16 *)(param_1 + 0xFC) = 0x40;
        *(s16 *)(param_1 + 0x2) = *(u16 *)(param_1 + 0x2) + 1;
    }
}
