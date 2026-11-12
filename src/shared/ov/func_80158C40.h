/* func_80158C40 — shared body (overlay slot 0x80128158, h_exact 734b84eb). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u16 guess_GetPadHeld(s32 *a0);
extern s32 func_80159404(s32 a0, s32 a1);
extern void guess_SetWaitTimer_2(s32 *a0, s32 a1);
extern void func_80146CA0(void *a0);
void func_80158C40(s32 *a0) {
    s32 n;
    s32 c;
    c = 0x3C000;
    n = 1;
    if (guess_GetPadHeld(a0) & 0xF0) {
        n = 4;
    }
    while (n > 0) {
        func_80159404((s32)a0, c);
        if (a0[0x234 / 4] < 0) {
            guess_SetWaitTimer_2(a0, 4);
            func_80146CA0(a0);
            n = 0;
        }
        n--;
    }
}
