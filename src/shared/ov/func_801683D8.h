/* func_801683D8 — shared body (overlay slot 0x80128158, h_exact 597ff7e7). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80146C3C();
void func_801683D8(s32 a0) {
    func_80166994(a0, 2, *(short *)(a0 + 0x2c), 0);
    if ((short)func_80166690(*(short *)(a0 + 0x2c), *(short *)(a0 + 0x28)) == 0) {
        ((void (*)(s32))func_80146C3C)(a0);
    }
}
