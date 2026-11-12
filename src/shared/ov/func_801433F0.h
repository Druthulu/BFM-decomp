/* func_801433F0 — shared body (overlay slot 0x80128158, h_exact 3964cb5f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80143458();  // K&R: 0 of 1 args (P37 rung D t4_HD7)
extern void guess_AddVelocityToPos(struct vec *a0);
extern s32 guess_StepPairSequence(s32 param_1, s32 *param_2);
extern void func_801292C8(u8 *a0);
void func_801433F0(s32 a0) {
    if (*(u16 *)(a0 + 2) == 0) {
        func_80143458();
    } else {
        guess_AddVelocityToPos((struct vec *)a0);
        if (guess_StepPairSequence(*(void **)(a0 + 0x20), (u8 *)a0 + 0x24) != 0) {
            func_801292C8((u8 *)a0);
        }
    }
}
