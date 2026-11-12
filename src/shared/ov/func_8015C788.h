/* func_8015C788 — shared body (overlay slot 0x80128158, h_exact 837d3071). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void guess_SetAnim(s32 a0, s32 a1);
extern void guess_SetTexAnim(s32 a0, s32 a1);
extern void func_801553A8(s32 *a0);
extern void func_80155440(s32 *a0);
extern void guess_SetWaitTimer_2(s32 *a0, s32 a1);
extern void guess_NextStep(void *a0);
void func_8015C788(s32 a0) {
    guess_SetAnim(a0, 0x12);
    guess_SetTexAnim(a0, 0x17);
    func_801553A8((s32 *)a0);
    func_80155440((s32 *)a0);
    guess_SetWaitTimer_2((s32 *)a0, 0xA);
    guess_NextStep((void *)a0);
}
