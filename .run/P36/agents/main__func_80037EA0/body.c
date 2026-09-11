void func_80037EA0(void)
{
    extern void func_8003D3B4(s32, s32);
    u8 *p;
    s32 i;

    for (i = 0; i < 0x10; i++) {
        p = &D_800C6E2E[i * 0x60];
        if (p[-4] != 0 && p[-1] == 0 && p[0] != 0) {
            func_8003D3B4(i, 8);
            *(u32 *)(p - 0x4A) &= ~0x60000;
            p[0] = 0;
        }
    }
}
