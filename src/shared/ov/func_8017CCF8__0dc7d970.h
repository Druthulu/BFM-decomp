/* func_8017CCF8 — shared body (overlay slot 0x80128158, h_exact 0dc7d970). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s16 func_80128CFC(u16 a0);
void func_8017CCF8(void *a0) {
    void *v1 = *(void **)(a0 + 0xDC);
    s16 v0;
    if (*(u8 *)(v1 + 1) == 0) {
        v0 = 1;
    } else {
        v0 = *(s16 *)(a0 + 0x108);
        if (v0 == 0) {
            u16 arg = *(u16 *)(v1 + 2);
            v0 = func_80128CFC(arg);
            *(s16 *)(a0 + 0x108) = v0;
        }
        v0 = *(s16 *)(a0 + 0x108);
    }
    if (v0 != 0) {
        *(u16 *)(a0 + 0x2) += 1;
    }
}
