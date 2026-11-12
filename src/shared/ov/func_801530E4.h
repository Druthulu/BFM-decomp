/* func_801530E4 — shared body (overlay slot 0x80128158, h_exact 2ddaebea). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void guess_StartPadVibration(void *a0);
extern void guess_NextStep(void *a0);
extern s32 func_801472C8(struct S *a0);
extern void guess_ClearTiltVectors(s32 *a0);
extern void func_80149020(s32 *a0);
extern void guess_ClearStoodOnActor(void *a0);
extern void func_80155440(s32 *a0);
extern u8 guess_g_RumblePatternFade[]; // Names ledger: config/names.tsv guess_g_RumblePatternFade
void func_801530E4(s32 arg0)
{
    guess_StartPadVibration(&guess_g_RumblePatternFade);
    func_80149020(arg0);
    func_801472C8(arg0);
    M2C_FIELD(arg0, s8 *, 0xDE) = 0x40;
    guess_ClearStoodOnActor(arg0);
    guess_ClearTiltVectors(arg0);
    func_80155440(arg0);
    guess_NextStep(arg0);
}
