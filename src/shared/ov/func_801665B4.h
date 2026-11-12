/* func_801665B4 — shared body (overlay slot 0x80128158, h_exact 883ec57a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 guess_StepPairSequence(s32 param_1, s32 *param_2);
extern s32 guess_FreeSmallObject();  // K&R: 1 of 1 args (P37 rung D t6_hD1)
extern void guess_AddVelocityToPos_4(s32 a0);
void func_801665B4(s32 *a0)
{
    if (guess_StepPairSequence((void *)a0[8], (void *)(a0 + 9))) {
        guess_FreeSmallObject((s32)a0);
    } else {
        guess_AddVelocityToPos_4((s32)a0);
        a0[5] -= a0[5] >> 3;
    }
}
