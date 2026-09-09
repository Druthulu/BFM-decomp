/* func_80128AF4 — shared body (overlay slot 0x80128158, h_exact 79334e07). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80128AF4(void) {
    switch (D_800B99F6) {                           /* irregular */
    case 0:
        D_8018E678 = func_8002AF08();
        func_80011C10();
        return;
    case 1:
        D_8017F258();
        func_80011C10();
        return;
    case 2:
        if ((D_8017F25C() << 0x10) != 0) {
            if (D_8018E678 == 1) {
                if (func_800CFBE8() != 0) {
                    func_800CFBBC();
                    func_80011B7C(0x13);
                } else {
                    func_80011B7C(4);
                }
            } else {
                func_80010DE0();
            }
            func_8002AEF8();
        }
        return;
    }
}
