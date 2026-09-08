/* func_801292C8 — shared body (overlay slot 0x80128158, h_exact 05a218ad). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80016714(void *a0, s32 a1);
void func_801292C8(u8 *a0) {
    u16 *p = *(u16 **)(a0 + 0x20);
    if (p != 0) {
        func_80016714(p, (p[0] == 1) ? 0x84 : 0x38);
    }
    *(s16 *)a0 = 0;
}
