/* func_8015C0C4 — shared body (overlay slot 0x80128158, h_exact 50441ee1). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void guess_SetAnim(s32 a0, s32 a1);
extern void func_801553A8(s32 *a0);
extern void guess_NextStep(void *a0);
extern s16 D_801152B0;
extern s16 D_801152B4;
void func_8015C0C4(s32 a0) {
    s32 t = D_801152B0 << 6;
    *(s32 *)(a0 + 0x238) = 0x80000;
    *(s32 *)(a0 + 0x234) = t;
    *(s32 *)(a0 + 0x23C) = D_801152B4 << 6;
    guess_SetAnim(a0, 0x11);
    func_801553A8((s32 *)a0);
    guess_NextStep((void *)a0);
}
