/* func_801301E8 — shared body (overlay slot 0x80128158, h_exact 48ada76c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 guess_TickWaitTimer(s32 a0);
extern void func_80130D48(s32 a0);
extern void func_801319E0(s32 a0);
extern s32 guess_CallActorEventHandler();  // K&R: 2 of 1 args (P37 unalias t4_ua7)
void func_801301E8(u8 *a0) {
    if (*(s32 *)(a0 + 0xB4) & 0x2000) {
        if (*(u8 *)(a0 + 0xC3) != 0) {
            if (*(u16 *)(a0 + 0x72) & 0x4000) {
                func_80130D48((s32)a0);
                func_801319E0((s32)a0);
            }
        } else if (guess_TickWaitTimer((s32)a0) != 0) {
            func_80130D48((s32)a0);
            func_801319E0((s32)a0);
        }
    }
    guess_CallActorEventHandler((int)a0, 0x26);
}
