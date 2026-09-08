/* func_80130088 — shared body (overlay slot 0x80128158, h_exact 33795432). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8012BCCC(s32 a0);
extern s32 func_80131AC8(void *a0);
void func_80130088(void *a0) {
    s32 v0 = func_8012BCCC((s32)a0);
    if (v0 <= 0x8FFF) {
        if (((s32 (*)(void *, s32))func_80131AC8)(a0, 0x32)) {
            return;
        }
        ((s32 (*)(void *, s32))func_80131AC8)(a0, 0x33);
    } else {
        if (((s32 (*)(void *, s32))func_80131AC8)(a0, 0x33)) {
            return;
        }
        ((s32 (*)(void *, s32))func_80131AC8)(a0, 0x32);
    }
}
