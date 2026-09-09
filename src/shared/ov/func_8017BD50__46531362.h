/* func_8017BD50 — shared body (overlay slot 0x80128158, h_exact 46531362). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8017BD50(int param_1)
{
    func_8017B0E4(param_1, 6);
    D_8018F914 = D_8018F914 + 1;
    if (D_8018F914 >= 0x19) {
        if (D_8018F958 != 0) {
            (*D_8018F958)();
        } else {
            D_80114F30 = D_80114F30 + D_8018F99C;
            D_80114F34 = D_80114F34 + D_8018F99E;
            D_80114F38 = D_80114F38 + D_8018F9A0;
            D_80114F24 = D_80114F24 + D_8018F99C;
            D_80114F28 = D_80114F28 + D_8018F99E;
            D_80114F2C = D_80114F2C + D_8018F9A0;
            func_8012A4BC();
        }
        D_8018FAB0 = 0;
    }
}
