void func_80037F3C(void)
{
    /* TU-absent names, block scope */
    extern u8 D_800C6DD0[];
    extern void func_8003B250(s32, void *);

    u8 *p;
    s32 i;
    u8 *base;

    base = D_800C6DD0;
    i = 0;
    p = base + 0x5E;
    do {
        if (p[-4] != 0 && p[-1] != 0) {
            func_8003B250(i, base + 0x10);
            *(u32 *)(p - 0x4A) = 0;
            p[-1] = 0;
            p[0] = 0;
        }
        i++;
        p += 0x60;
        base += 0x60;
    } while (i < 0x10);
}
