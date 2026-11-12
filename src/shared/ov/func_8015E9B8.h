/* func_8015E9B8 — shared body (overlay slot 0x80128158, h_exact c7ba891b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_80078EC0;
extern s16 guess_g_CameraRelativeYaw;
extern void func_80160818(s32 *a0);
extern void guess_SetAnim(s32 a0, s32 a1);
extern void func_80149034(s32 *a0);
extern void func_801553A8(s32 *a0);
extern s32 guess_GetCameraRelativeYaw(s32 a0);
extern void guess_NextStep(void *a0);
void func_8015E9B8(s32 *a0) {
    if (D_80078EC0 & 0x80) {
        func_80160818(a0);
    } else {
        guess_SetAnim((s32)a0, 0x1D);
        a0[0x44 / 4] |= 1;
        func_80149034(a0);
        func_801553A8(a0);
        guess_g_CameraRelativeYaw = guess_GetCameraRelativeYaw((s32)a0);
        guess_NextStep(a0);
    }
}
