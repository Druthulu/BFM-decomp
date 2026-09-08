/* func_801661CC — shared body (overlay slot 0x80128158, h_exact 204babba). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_801661CC(s32 param_1)
{
    extern s32 func_80128ED8(s32 param_1, s32 *param_2);
    extern void func_80146C3C();
    extern void func_800D22E4(s32 a0);
    if (((s32 (*)(s32, s32))func_80128ED8)(*(s32 *)(param_1 + 0x20), param_1 + 0x24) != 0) {
        ((void (*)(s32))func_80146C3C)(param_1);
    } else {
        func_800D22E4(param_1);
        *(s32 *)(param_1 + 0x10) = (*(s32 *)(param_1 + 0x10) >> 1) + (*(s32 *)(param_1 + 0x10) >> 2);
        *(s32 *)(param_1 + 0x18) = (*(s32 *)(param_1 + 0x18) >> 1) + (*(s32 *)(param_1 + 0x18) >> 2);
    }
}
