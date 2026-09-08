/* func_8014EA4C — shared body (overlay slot 0x80128158, h_exact 3d0eaf2f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_801202A0[];
extern u16 D_800B99DA;
extern s32 D_801150D8;
extern s16 D_801152AA;
extern u8 D_80126720[];
extern s16 D_80126724;
extern s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3);
s32 func_8014EA4C(void * a0, void * a1, void * a2, s32 _arg3)
{
    u8 buf[24];
    s32 acc;
    s16 d5;
    s16 d4;
    s32 mode;
    u8 *p;
    acc = 0;
    __builtin_memcpy(buf + 16, a2, 8);
    d5 = 8;
    mode = (D_800B99DA & 0x60) >> 5;
    d4 = 8;
    switch (mode) {
    case 0:
    case 1:
        d5 = 7;
        break;
    case 2:
        d4 = 7;
        break;
    }
    for (p = D_801202A0; p < D_801202A0 + 0x6480; p += 0x10C) {
        s32 *q = (s32 *)(p + 0x58);
        if (*(u16 *)p == 0) continue;
        if (q[0] == 0) continue;
        if (p == *(u8 **)((u8 *)a0 + 0x178)) continue;
        if (p == *(u8 **)((u8 *)a0 + 0x174)) continue;
        if ((q[1] & 0x1800) == 0) continue;
        D_801150D8 = 0;
        if (func_80135A4C(q[-0xe], ((struct { s32 w; } *)q)->w, (s32 *)a1, (s32)a2) != 0) {
            if ((D_801150D8 & 1) != 0) {
                if ((*(u16 *)(p + 0x5C) & 0x10) == 0) {
                    if ((*(s16 *)&D_80126720) - *(s16 *)((u8 *)a1 + 0x0) >= 0)
                        *(s16 *)((u8 *)a0 + 0x6) = *(u16 *)((u8 *)a2 + 0x0) - d5;
                    else
                        *(s16 *)((u8 *)a0 + 0x6) = *(u16 *)((u8 *)a2 + 0x0) + d5;
                    if (D_80126724 - *(s16 *)((u8 *)a1 + 0x4) >= 0)
                        *(s16 *)((u8 *)a0 + 0xE) = *(u16 *)((u8 *)a2 + 0x4) - d4;
                    else
                        *(s16 *)((u8 *)a0 + 0xE) = *(u16 *)((u8 *)a2 + 0x4) + d4;
                }
                acc |= 2;
            } else {
                *(s16 *)((u8 *)a0 + 0x6) = *(u16 *)((u8 *)a2 + 0x0);
                *(s16 *)((u8 *)a0 + 0xA) = *(u16 *)((u8 *)a2 + 0x2) + 0x10;
                *(s16 *)((u8 *)a0 + 0xE) = *(u16 *)((u8 *)a2 + 0x4);
                acc |= 1;
                if (q[0] < 0) {
                    s32 t = D_801152AA;
                    if (t < 0) t = -t;
                    if (0x800 < (s16)t) {
                        if ((*(s16 *)&D_80126720) - *(s16 *)((u8 *)a2 + 0x0) >= 0)
                            *(s16 *)((u8 *)a0 + 0x6) = *(s16 *)((u8 *)a2 + 0x0) - d5;
                        else
                            *(s16 *)((u8 *)a0 + 0x6) = *(s16 *)((u8 *)a2 + 0x0) + d5;
                        if (D_80126724 - *(s16 *)((u8 *)a2 + 0x4) >= 0)
                            *(s16 *)((u8 *)a0 + 0xE) = *(s16 *)((u8 *)a2 + 0x4) - d4;
                        else
                            *(s16 *)((u8 *)a0 + 0xE) = *(s16 *)((u8 *)a2 + 0x4) + d4;
                    }
                }
            }
        }
    }
    return acc;
}
