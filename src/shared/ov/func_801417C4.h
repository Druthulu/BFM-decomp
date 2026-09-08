/* func_801417C4 — shared body (overlay slot 0x80128158, h_exact a2e16cc8). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8001903C(void);
extern u16 D_80115112;
void func_801417C4(void) {
    u16 *p = &D_80115112;
    func_8001903C();
    *p = *p + 1;
}
