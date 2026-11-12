/* func_801608C0 — shared body (overlay slot 0x80128158, h_exact dc7d9e49). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_801553A8(s32 *a0);
extern void func_80155440(s32 *a0);
extern void guess_SetAnim(s32 a0, s32 a1);
extern void guess_SetTexAnim(s32 a0, s32 a1);
extern void guess_NextStep(void *a0);
void func_801608C0(s32 *a0) {
    *(s32 *)((s32)a0 + 0x44) |= 0x41;
    func_801553A8(a0);
    func_80155440(a0);
    guess_SetAnim((s32)a0, 0x24);
    guess_SetTexAnim((s32)a0, 0x1D);
    guess_NextStep(a0);
}
