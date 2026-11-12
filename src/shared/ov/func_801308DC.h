/* func_801308DC — shared body (overlay slot 0x80128158, h_exact b789abbd). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void guess_RequestSound(s32 a0, s32 a1);
extern s32 guess_CallActorEventHandler();  // K&R: 2 of 1 args (P37 unalias t4_ua7)
void func_801308DC(s32 a0) {
    *(u8 *)(a0 + 0xC1) = 0xE;
    if ((*(s32 *)(a0 + 0xB4) & 0x8000) != 0) {
        *(s32 *)(a0 + 0x1C) = 0x10;
        *(s16 *)(a0 + 0xAA) = 0;
        *(s16 *)(a0 + 0x5C) = 0;
        *(s16 *)(a0 + 0x98) = 0;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0x400;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1C) = 0x400;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x200;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) |= 0x10;
        guess_RequestSound(0x68A, 0);
    }
    guess_CallActorEventHandler(a0, 0x2A);
}
