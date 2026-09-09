/* func_801457A4 — shared body (overlay slot 0x80128158, h_exact b9863ee9). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void *func_801457A4(s32 param_1) {
    switch (param_1) {
    case 0x1010:
    case 0x1052:
    case 0x1077:
    case 0x1094:
    case 0x2013:
    case 0x2015 ... 0x201a:
    case 0x2055 ... 0x205b:
    case 0x207a ... 0x2080:
    case 0x2097 ... 0x209d:
        return (void *)(&D_8017F22C)[param_1 & 0xffff0fff];
    default:
        return (void *)D_8017F22C;
        break;
    }
}
