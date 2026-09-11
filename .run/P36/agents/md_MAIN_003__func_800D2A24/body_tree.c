void func_800D2A24(s32 a0) {
    u8 *p;
    s32 r;
    register s32 v0 __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus9)

retry:
    p = D_800EC9E8;
    for (;;) {
        r = func_800435CC(2, (void *)a0, p);
        if (*p & 0x10) {
            goto ret1;
        }
        if (r != 0) {
            break;
        }
    }
    if (CdRead2(0x1C0) == 0) {
        goto retry;
    }
    v0 = 0;
    __asm__ __volatile__("" : : "r"(v0));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B tus9)
    return;

ret1:
    v0 = 1;
    __asm__ __volatile__("" : : "r"(v0));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B tus9)
    return;
}
