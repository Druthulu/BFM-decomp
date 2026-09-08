/* func_8014D2A0 — shared body (overlay slot 0x80128158, h_exact 18749e1a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3);
extern s32 func_8014C918(s32 a0, s32 a1);
s32 func_8014D2A0(s32 arg0, void *a1, void *a2)
{
    extern u8 D_801202A0[];
    extern u8 D_80126720[];
    u16 *arg2 = (u16 *)a2;
    u8 *p;
    s32 t;
    p = D_801202A0;
    if (p < p + 0x6480) {
        do {
            if ((*(u16 *)p != 0) && ((*(u16 *)(p + 0x5C) & 0x400) != 0) &&
                ((t = *(s32 *)(p + 0x58)) != 0) &&
                (p != *(u8 **)(arg0 + 0x178)) && (p != *(u8 **)(arg0 + 0x170)) &&
                (*(s16 *)(p + 0xA) >= *(s16 *)(arg0 + 0xA)) &&
                (func_80135A4C(*(s32 *)(p + 0x20), t, (s32 *)a1, (s32)arg2) != 0)) {
                *(u16 *)(arg0 + 6) = arg2[0];
                *(u16 *)(arg0 + 0xA) = arg2[1];
                *(u16 *)(arg0 + 0xE) = arg2[2];
                *(u16 *)(arg0 + 0x16E) = func_8014C918(arg0, *(u8 *)(p + 0x75)) & 0xFF;
                return 1;
            }
            p += 0x10C;
        } while (p < D_80126720);
    }
    return 0;
}
