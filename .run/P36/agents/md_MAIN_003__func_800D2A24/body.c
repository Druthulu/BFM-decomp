s32 func_800D2A24(s32 a0) {
    u8 *p;
    s32 r;

retry:
    p = D_800EC9E8;
    for (;;) {
        r = func_800435CC(2, (void *)a0, p);
        if (*p & 0x10) {
            return 1;
        }
        if (r != 0) {
            break;
        }
    }
    if (CdRead2(0x1C0) == 0) {
        goto retry;
    }
    return 0;
}
