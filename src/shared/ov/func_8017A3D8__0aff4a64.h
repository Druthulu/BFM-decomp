/* func_8017A3D8 — shared body (overlay slot 0x80128158, h_exact 0aff4a64). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
int func_8017A3D8(void)
{
    switch (D_8018F94C) {
    case 0:
        func_800D0CA0(1);
        D_8018F94C = D_8018F94C + 1;
        return 0;
    case 100:
    {
        register int a __asm__("$4");
        a = D_8018F948;
        if (a != -1) {
            return func_8001AAA0() != 0;
        }
        return func_800D0CE0() == 1;
    }
    default:
        D_8018F94C = D_8018F94C + 1;
        if (D_8018F94C < 0x1E) {
            return 0;
        }
        D_8018F94C = 100;
        return 0;
    }
}
