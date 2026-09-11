void func_80184A68(void) {
    u8 *a0;
    a0 = &D_801AECC5;
    if (a0[0] < 0xF8U) {
        a0[0] += 4;
        a0[-1] += 6;
        a0[1] += 4;
    }
}
