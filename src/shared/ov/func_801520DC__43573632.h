/* func_801520DC — shared body (overlay slot 0x80128158, h_exact 43573632). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_801520DC(s32 arg0)
{
    func_80019064(&guess_g_RumblePatternFade);
    func_80151204(arg0, M2C_FIELD(arg0, s16 *, 0xF2));
    func_80149020(arg0);
    func_801472C8(arg0);
    M2C_FIELD(arg0, s8 *, 0xDE) = 0x10;
    guess_SetMoveVector(arg0, &D_80180FAC);
    guess_SetVertSpeed(arg0, 0x40000);
    guess_ClearStoodOnActor(arg0);
    guess_ClearTiltVectors(arg0);
    guess_SpawnSmallObject(0x10, arg0, M2C_FIELD(arg0, s16 *, 6), M2C_FIELD(arg0, s16 *, 0xA), (s32) M2C_FIELD(arg0, s16 *, 0xE), 0, 0);
    guess_PlaySoundUnlessSkipped(0x441);
    guess_NextStep(arg0);
}
