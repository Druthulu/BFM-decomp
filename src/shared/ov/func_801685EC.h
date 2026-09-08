/* func_801685EC — shared body (overlay slot 0x80128158, h_exact 25f13a15). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80166994(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80166690();
extern void func_80146C3C();
void func_801685EC(s32 a0) {
    func_80166994(a0, 2, 2, 0);
    if ((short)func_80166690(2, 1) == 0) {
        ((void (*)(s32))func_80146C3C)(a0);
    }
}
