/* func_80139220 — shared body (overlay slot 0x80128158, h_exact 2a5159e3). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80139DC8(void);
extern void func_801392C8(void *a0);
s32 func_80139220(s32 a0) {
    s32 v1;
    *(s16 *)(a0 + 0x14) = 0;
    *(s16 *)(a0 + 0x12) = (*(u16 *)(a0 + 0x12) + 1) % (*(s16 *)(a0 + 0x2E) + 1);
    func_80139DC8();
    v1 = *(u16 *)(a0 + 0x12) - *(u16 *)(a0 + 0x16);
    if (v1 != -1) {
        if (v1 < *(s16 *)(a0 + 0x2E)) {
            return 0;
        }
    }
    func_801392C8((void *)a0);
    return 1;
}
