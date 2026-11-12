/* func_80158FA4 — shared body (overlay slot 0x80128158, h_exact 1e7a4e71). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80158FA4(s32 param_1)
{
    s32 v0;
    s16 sVar1;

    v0 = *(s32 *)(param_1 + 0x20);
    *(u16 *)(v0 + 0x12) = (*(u16 *)(v0 + 0x12) + 0x16) & 0xfff;
    if (((s32 (*)(void))guess_GetPadPressed)() & 0xf0) {
        D_8018E860 = 1;
    }
    if (guess_GetTextWindowResult(*(s32 *)(param_1 + 0x198)) != 0) {
        guess_CloseTextWindow(*(s32 *)(param_1 + 0x198));
        *(s32 *)(param_1 + 0x198) = 0;
        sVar1 = ((s32 (*)(s32))func_80159464)(param_1);
        if (sVar1 != 0) {
            func_801594E8(param_1, sVar1);
            ((void (*)(s32, s32))guess_SetStep)(param_1, 0xc);
        } else {
            *(s32 *)(param_1 + 0x198) = ((s32 (*)(u8 *))guess_OpenTextWindow)(&(*(u8 *)&guess_g_StartPromptText));
            ((void (*)(s32))guess_NextStep)(param_1);
        }
    }
}
