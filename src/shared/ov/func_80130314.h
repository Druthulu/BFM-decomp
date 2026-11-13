/* func_80130314 — shared body (overlay slot 0x80128158, h_exact ae2c8dec). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80131340(s32 a0);
extern s32 guess_CallActorEventHandler(int);
void func_80130314(s32 a0) {
    if (*(s32 *)(a0 + 0xB4) & 0x800) {
        func_80131340(a0);
    }
    KR_AS(s32, guess_CallActorEventHandler)(a0, 0x2D);
}
