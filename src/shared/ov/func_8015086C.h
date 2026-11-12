/* func_8015086C — shared body (overlay slot 0x80128158, h_exact 6d9aa956). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 guess_SpawnSmallObjectAtOrigin(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8014B2F8(void);
extern void guess_PlaySoundUnlessSkipped(s32 arg0);
void func_8015086C(int param_1)
{
    ((void (*)(int, int, int, int))guess_SpawnSmallObjectAtOrigin)(0x48, param_1, 0, 0);
    ((void (*)(int))func_8014B2F8)(param_1);
    guess_PlaySoundUnlessSkipped(0xA1B);
    return;
}
