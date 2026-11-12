/* func_80153D7C — shared body (overlay slot 0x80128158, h_exact ab751e1b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80153D7C(s32 param_1)
{
    guess_PlaySoundUnlessSkipped(0x451);
    guess_SetAnimScript((s32 *)param_1, (s32)&D_80181078);
    func_80149020((s32 *)param_1);
    *(u16 *)(param_1 + 0x244) = *(u16 *)(param_1 + 6);
    *(u16 *)(param_1 + 0x246) = *(u16 *)(param_1 + 10);
    *(u16 *)(param_1 + 0x248) = *(u16 *)(param_1 + 0xe);
    if (currentLocationId == 0x3075) *(u8 *)(param_1 + 0xde) = 0x14;
    else *(u8 *)(param_1 + 0xde) = 10;
    *(u8 *)(param_1 + 0xdf) = 0;
    guess_NextStep((void *)param_1);
}
