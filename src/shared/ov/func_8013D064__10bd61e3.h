/* func_8013D064 — shared body (overlay slot 0x80128158, h_exact 10bd61e3). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8013D064(void)
{
    if (D_8018E790 != 0) {
        if (D_8018E790 != 2) {
            if (((D_8018E790 < 3) && (D_8018E790 == 1)) &&
                (D_8018E794 = D_8018E794 + 1, 0x23a < D_8018E794)) {
                D_8018E778 = D_8018E790;
                D_8018E790 = 2;
            }
        } else {
            D_8018E778 = D_8018E778 + -1;
            if (D_8018E778 == 0) {
                D_8018E778 = D_8018E790;
                ((void (*)(s32))func_8013D9B0)(2);
                if (D_8018E784 == 0) {
                    D_8018E790 = D_8018E790 + 1;
                }
            }
        }
    }
    return;
}
