/* func_801299C8 — shared body (overlay slot 0x80128158, h_exact f9a41b0d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_801299C8(arg0, arg1, arg2)
s16 arg0;
s16 arg1;
u8 *arg2;
{
    u32 r;
    u32 g;
    u32 b;
    s32 i;

    if (arg0 != 0) {
        switch (arg1) {
        case 1:
            r = D_8018FAB2;
            g = D_8018F9DA;
            b = D_8018F9B8;
            D_8018E680[0] = r * 5 >> 3;
            D_8018E681[0] = g << 3;
            D_8018E682[0] = (s32)(b * 255) >> 4;
            D_8018E680[4] = (s32)(r * 143) >> 4;
            D_8018E681[4] = g * 25 >> 1;
            D_8018E682[4] = (s32)(b * 255) >> 4;
            D_8018E680[8] = (s32)(r * 255) >> 4;
            D_8018E681[8] = (s32)(g * 255) >> 4;
            D_8018E682[8] = (s32)(b * 255) >> 4;
            D_8018E680[12] = (s32)(r * 143) >> 4;
            D_8018E681[12] = (s32)(g * 255) >> 4;
            D_8018E682[12] = (s32)(b * 45) >> 2;
            break;
        case 0:
        case 2:
            i = arg1 * 4;
            D_8018E680[i] = arg2[0x44] * D_8018FAB2 >> 4;
            D_8018E681[i] = arg2[0x45] * D_8018F9DA >> 4;
            D_8018E682[i] = arg2[0x46] * D_8018F9B8 >> 4;
            i = (arg1 + 1) * 4;
            D_8018E680[i] = arg2[0x47] * D_8018FAB2 >> 4;
            D_8018E681[i] = arg2[0x48] * D_8018F9DA >> 4;
            D_8018E682[i] = arg2[0x49] * D_8018F9B8 >> 4;
            break;
        case 3:
        case 4:
            arg2[0x20] = D_8018FAB2 << 3;
            arg2[0x21] = D_8018F9DA << 3;
            arg2[0x22] = D_8018F9B8 << 3;
            break;
        }
    }
}
