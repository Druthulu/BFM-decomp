/* func_8015FDCC — shared body (overlay slot 0x80128158, h_exact 77b42930). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 guess_GetTextWindowResult(s32 a0);
extern void guess_PlaySoundUnlessSkipped(s32 a0);
extern void guess_CloseTextWindow(s32 a0);
extern s32 func_80028DE0(void);
extern u8 func_80165700(s32 a0, s32 a1);
extern void guess_SpawnObject(s32 a0, s32 a1, s32 a2, s32 a3, s32 sp5, s32 sp6, s32 sp7, s32 sp8);
extern void guess_NextStep(void *a0);
void func_8015FDCC(s32 a0) {
    s32 s0 = a0;
    if (guess_GetTextWindowResult(*(s32 *)(s0 + 0x198)) != 0) {
        guess_PlaySoundUnlessSkipped(0x19);
        guess_CloseTextWindow(*(s32 *)(s0 + 0x198));
        *(s32 *)(s0 + 0x198) = 0;
        if (func_80028DE0() == 0) {
            if ((func_80165700(s0, *(u8 *)(s0 + 0x1A0)) & 0xFF) != 0) {
                guess_SpawnObject(0x24, s0, 0, 0, 0, 0, 0, 0);
                guess_PlaySoundUnlessSkipped(0x989);
            }
        }
        guess_NextStep((void *)s0);
    }
}
