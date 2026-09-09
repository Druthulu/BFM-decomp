/* func_8013D3D4 — shared body (overlay slot 0x80128158, h_exact f5857947). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8013D3D4(int param_1, int param_2)
{
    u8 *p = D_80078E78;

    D_8018E798 = param_2;
    D_8018E79C = (param_2 >> 2) & 3;
    D_8018E7A0 = (param_2 >> 4) & 1;
    if (((param_2 >> 2) & 3) == 0) {
        D_8018E768 = D_8017FAB8;
        D_8018E76C = D_8017FB60;
        D_8018E770 = D_8017FA10;
    } else {
        D_8018E768 = D_8017FB0C;
        D_8018E76C = D_8017FB8C;
        D_8018E770 = D_8017FA64;
    }
    func_8013D53C();
    if ((param_2 & 1) != 0) {
        if (D_8018E7A0 != 0) {
            func_8013DD68();
        } else {
            func_8013D8FC();
        }
        func_8013CF68();
        if ((D_8018E798 & 2) != 0) {
            D_8018FA0C[0] = 0x140;
            D_8018FA0C[3] = 0x80;
            if (p[0x37] == 4) {
                D_8018FA0C[0] = 0x140;
                D_8018FA0C[3] = 0;
            }
            if (p[0x37] == 0) {
                D_8018FA0C[0] = 0x140;
                D_8018FA0C[3] = 0x80;
            }
        }
    }
}
