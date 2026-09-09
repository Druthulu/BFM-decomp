/* func_8014E5B4 — shared body (overlay slot 0x80128158, h_exact 4ed201dc). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 aF8014E5B4(s32 a0, void *a1, void *a2) __asm__("func_8014E5B4");
s32 aF8014E5B4(s32 a0, void *a1, void *a2)
{
    extern u8 D_801202A0[];
    u8 *p;
    register u8 *q __asm__("$16");  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B headers1)
    u8 *e;
    s32 t;
    p = D_801202A0;
    if (p < p + 0x6480) {
        e = p + 0x6480;
        q = p + 0xE;
    loop:
        if (*(u16 *)p != 0) {
            if ((*(u16 *)(q + 0x4E) & 0x40) != 0) {
                t = *(s32 *)(q + 0x4A);
                if (t != 0) {
                    if (func_80135888(*(s32 *)(q + 0x12), t, (s32)a1, (s32)a2) != 0) {
                        *(u8 **)(a0 + 0x17C) = p;
                        *(u16 *)(a0 + 6) = *(u16 *)(q - 8);
                        *(u16 *)(a0 + 0xE) = *(u16 *)q;
                        return 1;
                    }
                }
            }
        }
        p += 0x10C;
        q += 0x10C;
        if (p < e) {
            goto loop;
        }
    }
    return 0;
}
