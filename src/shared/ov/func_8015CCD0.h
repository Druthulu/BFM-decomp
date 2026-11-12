/* func_8015CCD0 — shared body (overlay slot 0x80128158, h_exact b57fcdbb). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void guess_SetAnim(s32 a0, s32 a1);
extern s32 func_801725E0(u8 *a0);
extern void func_80147324(s32 arg0);
extern void guess_NextStep(void *a0);
s32 func_8015CCD0(s32 param_1)
{
    guess_SetAnim(param_1, 0x14);
    *(s16 *)(param_1 + 0xB8) = 0;
    func_801725E0((u8 *)param_1);
    *(s32 *)(param_1 + 0x234) = 0xF;
    func_80147324(0x6A7);
    guess_NextStep((void *)param_1);
}
