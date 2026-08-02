s32 func_80184D00(void) {
    s32 v1 = func_80029504();

    if (v1 < 0x14) {
        return 0;
    }
    if (v1 < 0x46) {
        return 1;
    }
    if (v1 < 0x64) {
        return 2;
    }
    if (v1 < 0x82) {
        return 3;
    }
    return 4;
}
