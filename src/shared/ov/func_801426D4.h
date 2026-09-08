/* func_801426D4 — shared body (overlay slot 0x80128158, h_exact 1e2afbed). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8012AD50(void *a0);
void func_801426D4(s32 a0) {
    s32 s0 = *(s32 *)(a0 + 0x20);
    s16 fc = *(s16 *)(a0 + 0xFC);
    if (fc != 0) {
        *(s16 *)(a0 + 0xFC) = fc - 0x10;
        *(u16 *)(s0 + 0x18) += 0x800;
        *(u16 *)(s0 + 0x1A) += 0x800;
    } else {
        *(s32 *)(a0 + 0x1C) = 0xC;
        func_8012AD50((void *)a0);
        *(u16 *)(s0 + 0x1A) = 0x1800;
        *(u16 *)(s0 + 0x18) = 0x1800;
    }
}
