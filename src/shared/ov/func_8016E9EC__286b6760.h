/* func_8016E9EC — shared body (overlay slot 0x80128158, h_exact 286b6760). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8016E9EC(u8 *p)
{

    extern u8 *D_80182614[];
    extern u8 D_8018262C[];
    extern u16 D_80182630[];
    s16 i;
    u8 *buf;
    u8 off;
    s32 h;

    i = p[0] - 1;
    off = D_8018262C[i];
    buf = D_80182614[i];
    func_800D2D10((func_800D2CA8(p[3], 0x1C)), 1, buf + off, 0);
    func_80024054(buf, p + 8);
    p[3] = (i + 0);
    *(s16 *)(p + 4) = -0xD7;
    h = D_80182630[i];
    p[2] = 0;
    *(u16 *)(p + 6) = h;
    p[1] = p[1] + 1;
    ((void (*)(u8 *, s32))func_8016EC0C)(p, 0x80);
}
