/* func_8013D330 — shared body (overlay slot 0x80128158, h_exact 3ba2802e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8013D330(void) {
    if ((D_8018FAB2 & 0xff) != D_8018FB2C) {
        D_8018FAB2 = ((D_8018FAB2 & 0xff) < D_8018FB2C) ? (D_8018FAB2 + 1) : (D_8018FAB2 - 1);
    }
    if ((D_8018F9DA & 0xff) != D_8018FA94) {
        D_8018F9DA = ((D_8018F9DA & 0xff) < D_8018FA94) ? (D_8018F9DA + 1) : (D_8018F9DA - 1);
    }
    if ((D_8018F9B8 & 0xff) != D_8018F9D9) {
        D_8018F9B8 = ((D_8018F9B8 & 0xff) < D_8018F9D9) ? (D_8018F9B8 + 1) : (D_8018F9B8 - 1);
    }
    D_8018FA98 = 1;
}
