/* func_8016DEE0 — shared body (overlay slot 0x80128158, h_exact 5d5ada92). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_80146C3C();
void func_8016DEE0(s32 a0) {
    if (func_80128ED8((void *)*(s32 *)(a0 + 0x20), (void *)(a0 + 0x24)) != 0) {
        ((void (*)(s32))func_80146C3C)(a0);
    }
}
