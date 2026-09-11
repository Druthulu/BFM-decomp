void func_8018BAC4(void) {
    u8 *pa;
    s32 t;
    s32 r;
    s32 x;

    pa = &D_801EFEA0[0];
    x = *(u8 *)pa;
    if (x != 0) {
        t = x - 0x18;
        r = t;
        if (t < 0) {
            r = 0;
        }
        *pa = r;
    }

    pa = &D_801EFEA1;
    x = *(u8 *)pa;
    if (x != 0) {
        t = x - 0x18;
        r = t;
        if (t < 0) {
            r = 0;
        }
        *pa = r;
    }

    pa = &D_801EFEA2;
    x = *(u8 *)pa;
    if (x != 0) {
        t = x - 0xD;
        r = t;
        if (t < 0) {
            r = 0;
        }
        *pa = r;
    }
}
