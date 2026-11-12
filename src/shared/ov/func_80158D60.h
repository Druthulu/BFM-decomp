/* func_80158D60 — shared body (overlay slot 0x80128158, h_exact 270e24b5). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u16 guess_GetPadHeld(s32 *a0);
extern s32 func_80159434(s32 a0, s32 a1);
extern void guess_PlaySoundUnlessSkipped(s32 a0);
extern void guess_NextStep(void *a0);
void func_80158D60(s32 a0) {
    s32 count;
    s32 i;
    s32 arg;
    arg = 0x4C000;
    count = 1;
    if (guess_GetPadHeld((s32 *)a0) & 0xF0) {
        count = 4;
    }
    for (i = count; i > 0; i--) {
        func_80159434(a0, arg);
        if (*(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) < 0xC00) {
            guess_PlaySoundUnlessSkipped(0x454);
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = 0xC00;
            *(s32 *)(a0 + 0x238) = 0xFFEA0000;
            guess_NextStep((void *)a0);
            i = 0;
        }
    }
}
