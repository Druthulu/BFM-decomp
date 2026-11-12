/* func_80158CD8 — shared body (overlay slot 0x80128158, h_exact a810ff63). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u16 guess_GetPadHeld(s32 *a0);
extern s32 guess_TickWaitTimer_2(s32 a0);
extern void guess_PlaySoundUnlessSkipped(s32 a0);
extern void guess_NextStep(void *a0);
void func_80158CD8(s32 *a0) {
    s32 i = 1;
    if (guess_GetPadHeld(a0) & 0xF0) {
        i = 4;
    }
    while (i > 0) {
        if (guess_TickWaitTimer_2((s32)a0)) {
            guess_PlaySoundUnlessSkipped(0x453);
            *(s32 *)((s32)a0 + 0x238) = 0x5B0000;
            guess_NextStep((void *)a0);
            i = 0;
        }
        i--;
    }
}
