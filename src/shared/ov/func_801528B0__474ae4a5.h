/* func_801528B0 — shared body (overlay slot 0x80128158, h_exact 474ae4a5). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_801528B0(s32 arg0)
{
    func_80019064(&guess_g_RumblePatternFade);
    func_80151204(arg0, M2C_FIELD(arg0, s16 *, 0xF2));
    func_80149020(arg0);
    guess_SetAnimScript(arg0, &D_800D5880);
    guess_PlaySoundUnlessSkipped(0x451);
    M2C_FIELD(arg0, s8 *, 0xDE) = 0x10;
    guess_SetMoveVector(arg0, &D_80180FF4);
    guess_SetVertSpeed(arg0, 0xFFF00000);
    guess_ClearStoodOnActor(arg0);
    guess_ClearTiltVectors(arg0);
    guess_NextStep(arg0);
}
