/* func_80168B70 — shared body (overlay slot 0x80128158, h_exact 93d5fccd). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80168B70(s32 a0) {
    s32 *p = (s32 *)a0;
    if (--p[0x1C / 4] != -1) {
        func_80168BDC(a0, 9, 3, 1);
    } else {
        func_80168BDC(a0, 9, 2, 1);
        ((void (*)(s32))func_80146C3C)(a0);
    }
}
