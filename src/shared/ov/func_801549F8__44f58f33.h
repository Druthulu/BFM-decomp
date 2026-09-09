/* func_801549F8 — shared body (overlay slot 0x80128158, h_exact 44f58f33). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_801549F8(s32 param_1, s32 _arg1, s32 _arg2)
{
    s32 i, j;
    u8 n;
    u8 count;
    s32 *base;

    count = 0;
    i = 0;
    if (*(u8 *)(param_1 + 0xBC) != 0) {
        base = *(s32 **)(param_1 + 0xB4);
        n = *(u8 *)(param_1 + 0xBC);
        do {
            j = i;
            switch (base[j]) {
            case 0:  case 2:  case 7:  case 8:  case 9:  case 10:
            case 0xd: case 0x10: case 0x11: case 0x12: case 0x13:
            case 0x14: case 0x19: case 0x1a:
                i = j + 1;
                break;
            case 3: case 4: case 5: case 6: case 0xb: case 0xc:
            case 0xe: case 0xf: case 0x15: case 0x16:
                i = j + 2;
                break;
            default:
                i = j + 1;
                count += 1;
                break;
            }
        } while (i != n);
    }
    return count;
}
