/* func_8012F87C — shared body (overlay slot 0x80128158, h_exact f577c356). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80131340(s32 a0);
extern s32 guess_CallActorEventHandler();  // K&R: 2 of 1 args (P37 unalias t4_ua7)
void func_8012F87C(s32 a0) {
    if (*(s32 *)(a0 + 0xB4) & 0x8) {
        func_80131340(a0);
    }
    guess_CallActorEventHandler(a0, 0xA);
}
