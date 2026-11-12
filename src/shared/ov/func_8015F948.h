/* func_8015F948 — shared body (overlay slot 0x80128158, h_exact 299a7ca5). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8015F948(s32 *param_1) {
    extern void guess_SetStep(s32 *a0, s16 a1);
    extern void guess_SetState(s32 *a0, s16 a1);
    extern void guess_SetAnim(s32 a0, s32 a1);
    extern void guess_SetTexAnim(s32 a0, s32 a1);
    extern s32 func_80161104(void);
    guess_SetState(param_1, 0x15);
    if (((s32 (*)(s32 *))func_80161104)(param_1) != 0) {
        guess_SetAnim((s32)param_1, 0x22);
        guess_SetTexAnim((s32)param_1, 0x1A);
        guess_SetStep(param_1, 2);
    }
}
