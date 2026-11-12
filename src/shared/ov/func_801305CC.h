/* func_801305CC — shared body (overlay slot 0x80128158, h_exact 9a49b315). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 guess_StartActorSequenceById(s32, s32);
extern s32 guess_CallActorEventHandler();  // K&R: 2 of 1 args (P37 unalias t4_ua7)
void func_801305CC(u8 *a0) {
    *(u8 *)(a0 + 0xC1) = 0xC;
    if (*(s32 *)(a0 + 0xB4) & 0x1000) {
        *(s32 *)(a0 + 0x1C) = 0x3C;
        *(s32 *)(a0 + 0xC4) = *(s32 *)(a0 + 0xC4) & ~4;
        if (guess_StartActorSequenceById((s32)a0, 0x20)) {
            *(s32 *)(a0 + 0xC4) = *(s32 *)(a0 + 0xC4) | 4;
        } else {
            *(u16 *)(a0 + 0x98) = 0;
        }
    }
    guess_CallActorEventHandler((int)a0, 0x22);
}
