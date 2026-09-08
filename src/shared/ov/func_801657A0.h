/* func_801657A0 — shared body (overlay slot 0x80128158, h_exact 3b9bc719). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_801657D8(void);
extern u8 D_80078EC3;
void func_801657A0(void) {
    if (D_80078EC3 == 0) {
        D_80078EC3 = 1;
        func_801657D8();
    }
}
