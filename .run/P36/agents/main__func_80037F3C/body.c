void func_80037F3C(void)
{
    /* TU-absent names, block scope */
    extern u8 D_800C6DD0[];
    extern void func_8003B250(s32, void *);

    u8 *p;
    u8 *base;
    s32 i;

    base = D_800C6DD0;
    for (i = 0; i < 0x10; i++, base += 0x60) {
        if (base[0x5A] != 0 && base[0x5D] != 0) {
            func_8003B250(i, base + 0x10);
            *(u32 *)(base + 0x14) = 0;
            base[0x5D] = 0;
            base[0x5E] = 0;
        }
    }
}
