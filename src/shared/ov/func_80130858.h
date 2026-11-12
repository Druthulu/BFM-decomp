/* func_80130858 — shared body (overlay slot 0x80128158, h_exact 684dec78). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void guess_ApplyAccelAndVelocity(s32 a0);
extern s32 guess_TickWaitTimer(s32 a0);
extern void func_801319E0(s32 a0);
void func_80130858(s32 a0) {
    guess_ApplyAccelAndVelocity(a0);
    if (guess_TickWaitTimer(a0)) {
        func_801319E0(a0);
    }
}
