/* func_8014350C — shared body (overlay slot 0x80128158, h_exact f81e8c37). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8014358C(s32 param_1);
extern void guess_AddVelocityToPos(S800D22E4 *a0);
extern s32 guess_StepPairSequence(s32 param_1, s32 *param_2);
extern void func_801292C8(u8 *a0);
void func_8014350C(s32 *a0) {
    if (*(u16 *)((u8 *)a0 + 2) == 0) {
        KR_AS(void, func_8014358C)();
        return;
    }
    guess_AddVelocityToPos((S800D22E4 *)a0);
    if (guess_StepPairSequence((void *)a0[0x20 / 4], (void *)((u8 *)a0 + 0x24)) != 0) {
        func_801292C8((u8 *)a0);
        return;
    }
    *(u8 *)(a0[0x20 / 4] + 0x27) = *(u8 *)((u8 *)a0 + 0x28) - 0x70;
}
