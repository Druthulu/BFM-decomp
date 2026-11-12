/* func_8012F7B4 — shared body (overlay slot 0x80128158, h_exact f2c10f62). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 guess_TickWaitTimer(s32);
extern s32 guess_StartActorSequenceById(s32, s32);
extern s32 guess_CallActorEventHandler();  // K&R: 2 of 1 args (P37 unalias t4_ua7)
void func_8012F7B4(s32 a0) {
    if (*(s32 *)(a0 + 0xB4) & 4) {
        guess_TickWaitTimer(a0);
        if (*(s32 *)(a0 + 0x1C) == 1) {
            if (guess_StartActorSequenceById(a0, 8) == 0) {
                guess_StartActorSequenceById(a0, 0x20);
            }
        }
    }
    guess_CallActorEventHandler(a0, 7);
}
