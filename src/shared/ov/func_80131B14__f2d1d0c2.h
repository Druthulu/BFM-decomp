/* func_80131B14 — shared body (overlay slot 0x80128158, h_exact f2d1d0c2). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80131B14() {
    extern void func_8002A520(void *);
    extern void func_8002A790(void *);
    extern u8 D_8017F738;

    register u8 *a0v __asm__("$4");
    u8 *p = a0v;


    s32 e = *(u8 *)(p + 0x5E);

    if (*(s16 *)(p + 0x60) != 0) {
        if (e == 0x1D) {
            *(s16 *)(p + 0x82) = 0;
            *(s16 *)(p + 0x7C) = *(u16 *)(p + 0x06);
            *(s16 *)(p + 0x7E) = *(u16 *)(p + 0x0A);
            *(s16 *)(p + 0x80) = *(u16 *)(p + 0x0E);
        }
        {
            s32 dec;
            s32 q = *(s32 *)(p + 0x78);
            if (q != 0) {
                dec = ((s32)*(s16 *)(p + 0x60) * (s32)*(s16 *)(q + 0x30)) >> 12;
                if (dec <= 0) dec = 1;
            }
            *(u16 *)(p + 0x76) = *(u16 *)(p + 0x76) - dec;
        }
        ((void (*)(void *))func_8016AA50)(p);
        if (*(u16 *)(p + 0x82) & 1) {
            ((void (*)(void *))func_8016B428)(p);
            ((void(*)(void *))func_80019064)(&D_8017F738);
        }
    }

    *(u16 *)(p + 0x5C) = *(u16 *)(p + 0x5C) & 0xFFFE;

    if (e != 0x1D) {
        if (*(u8 *)(p + 0xC8)) func_8002A520(p);
        if (*(u8 *)(p + 0xC9)) func_8002A790(p);
    }

    if (*(s16 *)(p + 0x76) <= 0) *(s16 *)(p + 0x5C) = 0;

    {
        s32 r = *(s32 *)(p + 0x20);
        *(s16 *)(r + 0x12) = (*(u16 *)(p + 0x62) + 0x800) & 0xFFF;
        {
            s32 r2 = *(s32 *)(p + 0x20);
            *(s16 *)(r2 + 0x14) = 0;
            *(s16 *)(r2 + 0x10) = 0;
        }
    }

    ((void (*)(void *))func_8012B2CC)(p);
    ((void (*)(void *))func_8012B23C)(p);
}
