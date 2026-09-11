void func_8018BAC4(void) {
    u8 *pa;
    u8 x;
    s16 t;

    pa = &D_801EFEA0[0];
    x = *pa;
    if (x != 0) {
        t = x - 0x18;
        x = t;
        if (t < 0) {
            x = 0;
        }
        *pa = x;
    }

    pa = &D_801EFEA1;
    x = *pa;
    if (x != 0) {
        t = x - 0x18;
        x = t;
        if (t < 0) {
            x = 0;
        }
        *pa = x;
    }

    pa = &D_801EFEA2;
    x = *pa;
    if (x != 0) {
        t = x - 0xD;
        x = t;
        if (t < 0) {
            x = 0;
        }
        *pa = x;
    }
}
