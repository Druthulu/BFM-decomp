void func_80031B7C(void) {
    s32 i = 0;
    s32 one = 1;
    s32 full = 0x7FFF;
    u8 *p = D_800A49D2;

loop:
    if (p[4] && !p[2] && p[3]) {
        p[2] = one;
        *(u16 *)p = full;
    }
    p += 0x54;
    i++;
    if (i < 8) goto loop;
}
