/* func_801439C0 — shared body (overlay slot 0x80128158, h_exact 2b1fec6d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80016714(void *a0, s32 a1);
extern void func_8012C218(void *a0);
void func_801439C0(u8 *a0) {
    if (a0 != 0) {
        func_80016714(*(void **)(a0 + 0xCC), 0x38);
        func_8012C218(a0);
    }
}
