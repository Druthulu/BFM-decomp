/* func_801819EC — shared body (overlay slot 0x80128158, h_exact 68a6381c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void guess_ReturnPlayerToStandingState(s32 a0, s32 a1, s32 a2);
extern M2C_UNK D_8018DDCC;
void func_801819EC(void) {
    ((void (*)(void *, s32))guess_ReturnPlayerToStandingState)(&D_8018DDCC, 0x1000000);
}
