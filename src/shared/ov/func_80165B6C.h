/* func_80165B6C — shared body (overlay slot 0x80128158, h_exact 50d4aaab). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80161104(void);
extern void func_80165BB4(u8 *a0);
void func_80165B6C(u8 *a0) {
    if (func_80161104()) {
        func_80165BB4(a0);
        *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1;
    }
}
