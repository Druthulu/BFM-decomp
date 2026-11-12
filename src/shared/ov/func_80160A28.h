/* func_80160A28 — shared body (overlay slot 0x80128158, h_exact 2120c89f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_801553C0(s32 a0);
extern void guess_SetTexAnim(s32 a0, s32 a1);
void func_80160A28(s32 a0) {
    s32 v0;
    func_801553C0(a0);
    v0 = *(s32 *)(a0 + 0x44);
    v0 &= ~0x40;
    v0 &= ~1;
    *(s32 *)(a0 + 0x44) = v0;
    guess_SetTexAnim(a0, 0x11);
}
