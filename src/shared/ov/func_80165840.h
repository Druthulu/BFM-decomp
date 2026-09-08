/* func_80165840 — shared body (overlay slot 0x80128158, h_exact f2064f5e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_80078EC3;
extern void func_80165874(void);
void func_80165840(void) {
    if (D_80078EC3 != 0) {
        D_80078EC3 = 0;
        func_80165874();
    }
}
