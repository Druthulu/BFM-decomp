/* func_801533A4 — shared body (overlay slot 0x80128158, h_exact 2ddaebea). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_801472C8(struct S *a0);
extern void guess_ClearStoodOnActor(void *a0);
extern void guess_ClearTiltVectors(s32 *a0);
extern void func_80155440(s32 *a0);
extern void guess_NextStep(void *a0);
extern u8 guess_g_RumblePatternFade[];
void func_801533A4(s32 a0)
{
    guess_StartPadVibration(guess_g_RumblePatternFade);
    func_80149020(a0);
    func_801472C8((struct S *)a0);
    *((u8 *)a0 + 0xDE) = 0x40;
    guess_ClearStoodOnActor(a0);
    guess_ClearTiltVectors(a0);
    func_80155440(a0);
    guess_NextStep(a0);
}
