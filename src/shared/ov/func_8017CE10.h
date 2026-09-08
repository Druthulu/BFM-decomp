/* func_8017CE10 — shared body (overlay slot 0x80128158, h_exact 320105d7). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
void func_8017CE10(void *a0, s32 a1, s32 a2) {
    s16 t0 = *(s16 *)(a0 + 0x6);
    s16 t1 = *(s16 *)(a0 + 0xA);
    s16 t2 = *(s16 *)(a0 + 0xE);
    func_80146A6C(0x2D, a0, t0, t1, t2, a1, a2);
}
