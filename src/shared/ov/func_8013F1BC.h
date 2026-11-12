/* func_8013F1BC — shared body (overlay slot 0x80128158, h_exact 4bfd5f8f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_800D2624(void);
extern short guess_g_DoubleBufferIndex;
extern unsigned short D_80115114;
extern unsigned short guess_g_MenuStep;
extern unsigned short guess_g_MenuTransitionTimer;
void func_8013F1BC(void) {
    unsigned short *p = &guess_g_MenuTransitionTimer;
    if (*p != 0) {
        *p -= 0x10;
        __asm__ __volatile__("" ::: "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B headers1) wall:cse-value-forward
        if (*p != 0) {
            return;
        }
    }
    if (D_80115114 == ((unsigned short)guess_g_DoubleBufferIndex ^ 1)) {
        func_800D2624();
    } else {
        guess_g_MenuStep += 1;
    }
}
