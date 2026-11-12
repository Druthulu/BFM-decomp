/* func_80183930 — shared body (overlay slot 0x80128158, h_exact 20a4f42e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void guess_ReturnPlayerToStandingState(s32 a0, s32 a1, s32 a2);
extern M2C_UNK D_8018F830;
void func_80183930(void) {
    ((void (*)(void *, s32))guess_ReturnPlayerToStandingState)(&D_8018F830, 0x1000000);
}
