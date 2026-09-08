/* func_8015F948 — shared body (overlay slot 0x80128158, h_exact 299a7ca5). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8015F948(s32 *param_1) {
    extern void func_80146C98(s32 *a0, s16 a1);
    extern void func_80147078(s32 *a0, s16 a1);
    extern void func_80154150(s32 a0, s32 a1);
    extern void func_80154A74(s32 a0, s32 a1);
    extern s32 func_80161104(void);
    func_80147078(param_1, 0x15);
    if (((s32 (*)(s32 *))func_80161104)(param_1) != 0) {
        func_80154150((s32)param_1, 0x22);
        func_80154A74((s32)param_1, 0x1A);
        func_80146C98(param_1, 2);
    }
}
