/* func_8013DBE4 — shared body (overlay slot 0x80128158, h_exact 036a62a6). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8013DBE4(int param_1)
{
    int *p;
    int x, y, z;
    int flag;

    if (D_8018E774 != 0) {
        D_8018E784 = 0;
        p = (int *)(param_1 * 12 + (int)D_8018E770);
        x = p[0];
        y = p[1];
        z = p[2];
        flag = 0;
        if (D_8018E7A4 != x) {
            flag = 1;
            if (D_8018E7A4 < x) {
                if (x - D_8018E7A4 < 5) {
                    D_8018E7A4 = x;
                } else {
                    D_8018E7A4 = D_8018E7A4 + 4;
                }
            } else {
                if (D_8018E7A4 - x < 5) {
                    D_8018E7A4 = x;
                } else {
                    D_8018E7A4 = D_8018E7A4 - 4;
                }
            }
        }
        if (D_8018E7A8 != y) {
            flag = 1;
            if (D_8018E7A8 < y) {
                if (y - D_8018E7A8 < 5) {
                    D_8018E7A8 = y;
                } else {
                    D_8018E7A8 = D_8018E7A8 + 4;
                }
            } else {
                if (D_8018E7A8 - y < 5) {
                    D_8018E7A8 = y;
                } else {
                    D_8018E7A8 = D_8018E7A8 - 4;
                }
            }
        }
        if (D_8018E7AC != z) {
            flag = 1;
            if (D_8018E7AC < z) {
                if (z - D_8018E7AC < 5) {
                    D_8018E7AC = z;
                } else {
                    D_8018E7AC = D_8018E7AC + 4;
                }
            } else {
                if (D_8018E7AC - z < 5) {
                    D_8018E7AC = z;
                } else {
                    D_8018E7AC = D_8018E7AC - 4;
                }
            }
        }
        if (flag != 0) {
            func_8013DD68();
        }
        D_8018E784 = flag;
    }
}
