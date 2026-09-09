/* func_8012DE2C — shared body (overlay slot 0x80128158, h_exact d811cfb5). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_8012DE2C(s32 a0) {
    extern u8 * D_8018E69C;
    extern u8 * D_8018E698;

    u8 *base;
    u8 *end;
    u8 *p;

    base = D_801202A0;
    end = base + 0x6480;
    D_8018E69C = base;
    D_8018E698 = ((u8 *)a0);

    while (D_8018E69C != end) {
        p = D_8018E69C;
        if (*(u16 *)p != 0 && p != ((u8 *)a0)) {
            D_8018E69C = p + 0x10C;
            return p;
        }
        D_8018E69C += 0x10C;
    }
    D_8018E69C = 0;
    return 0;
}
