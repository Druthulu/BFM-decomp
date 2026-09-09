/* func_8017C0A4 — shared body (overlay slot 0x80128158, h_exact e00a4591). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8017C0A4(param_1)
s32 param_1;
{
    s32 var_v0;

    *(s32 *)(param_1 + 0x14) = *(s32 *)(param_1 + 0x14) + 0xC000;
    ((void (*)(void))func_800D22E4)();
    var_v0 = *(s32 *)(param_1 + 0x1C) - 1;
    *(s32 *)(param_1 + 0x1C) = var_v0;
    if (var_v0 == -1) {
        *(s32 *)(param_1 + 0x2C) = 0;
        *(s32 *)(param_1 + 0x10) = *(s32 *)(param_1 + 4);
        *(s32 *)(param_1 + 0x18) = *(s32 *)(param_1 + 0xC);
        func_80146E90(param_1, 0x14);
        *(u16 *)(param_1 + 2) += 1;
    }
}
