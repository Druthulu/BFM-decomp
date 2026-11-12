/* func_80160244 — shared body (overlay slot 0x80128158, h_exact 5bfdb1c9). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void guess_SetAnim(s32 a0, s32 a1);
extern void guess_SetTexAnim(s32 a0, s32 a1);
extern void guess_NextStep(void *a0);
extern s32 func_80161208();
void func_80160244(s32 *a0) {
    if (*(u16 *)((u8 *)a0 + 0xB8) == 0x8000) {
        guess_SetAnim((s32)a0, 0x23);
        guess_SetTexAnim((s32)a0, 0x1B);
        guess_NextStep(a0);
    } else {
        ((s32 (*)(s32 *))func_80161208)(a0);
    }
}
