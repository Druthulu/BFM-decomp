/* func_80160B70 — shared body (overlay slot 0x80128158, h_exact 84ea224e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80161104(void);
extern void func_80160BB4(s32 *a0);
void func_80160B70(s32 a0) {
    if (func_80161104()) {
        func_80160BB4(a0);
    } else {
        *(s32 *)(a0 + 0x1AC) = 0;
    }
}
