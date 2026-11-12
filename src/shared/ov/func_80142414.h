/* func_80142414 — shared body (overlay slot 0x80128158, h_exact 433656cc). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 guess_SpawnActorNoArg(s32 a0, s32 a1);
void func_80142414(s32 a0, s16 a1) {
    s32 v0;
    v0 = guess_SpawnActorNoArg(0x13, a0);
    if (v0 != 0) {
        *(s16*)(v0 + 0x52) = a1;
    }
}
