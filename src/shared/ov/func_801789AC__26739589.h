/* func_801789AC — shared body (overlay slot 0x80128158, h_exact 26739589). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_801789AC(s32 arg0)
{
    s32 ret;

    func_8017BC38(arg0);
    func_8017A4AC();
    func_8017AE2C(arg0);

    switch ((s16)(D_8018FB24 - 1)) {
    case 0:
        ret = func_801399F0(D_8018F918);
        D_8018F9CC = ret;
        if (ret == 0) {
            break;
        }
        func_80178CBC(arg0, D_8018F500);
        break;
    case 1:
        ret = func_801399F0(D_8018F918);
        D_8018F9CC = ret;
        if (ret == 0) {
            break;
        }
        func_80178CBC(arg0, D_8018F500);
        break;
    case 2:
        func_80178CBC(arg0, D_8018F500);
        break;
    case 3:
        if (--D_8018F504 > 0) {
            break;
        }
        func_80178CBC(arg0, D_8018F500);
        break;
    case 4:
        ret = ((s32 (*)(s32))D_8018F944)(arg0);
        if (ret == 0) {
            break;
        }
        func_80178CBC(arg0, D_8018F500);
        break;
    case 5:
        switch (D_8018F9CC) {
        case -1:
        case 1:
            return 1;
        case 2:
            return 2;
        case 3:
            return 3;
        }
        break;
    }
    return 0;
}
