/* func_80165BB4 — shared body (overlay slot 0x80128158, h_exact 31b5359a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void guess_SetAnim(s32 a0, s32 a1);
extern void guess_SetTexAnim(s32 a0, s32 a1);
void func_80165BB4(u8 *a0) {
    guess_SetAnim((s32)a0, 0x22);
    guess_SetTexAnim((s32)a0, 0x1A);
    *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1;
}
