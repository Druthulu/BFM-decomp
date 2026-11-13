/* func_80130360 — shared body (overlay slot 0x80128158, h_exact 24a27bf0). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 guess_CallActorEventHandler(int);
void func_80130360(s32 a0) {
    *(u8*)(a0 + 0xC1) = 2;
    if (*(s32*)(a0 + 0xB4) & 2) {
        *(s16*)(a0 + 0x5C) = 0;
        *(s16*)(a0 + 0x98) = 0;
        *(s32*)(a0 + 0x1C) = 0;
    }
    KR_AS(s32, guess_CallActorEventHandler)(a0, 1);
}
