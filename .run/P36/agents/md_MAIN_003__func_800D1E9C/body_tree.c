void func_800D1E9C(void *arg0) {
    s32 sp18[30];
    s16 sp90[4];
    s16 sp98[8];
    s32 *p;
    s32 i;
    register s32 v0r __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus9)

    p = (s32 *) arg0;
    D_800EC9F0 = 1;
    ((void (*)()) func_800D2394)(D_800EC9A4,
                                 p[1] ? (p[4] * 3) / 2 : p[4],
                                 p[5],
                                 p[1] ? (p[4] * 3) / 2 : p[4],
                                 p[5] + p[7],
                                 p);
    if (((s32 (*)()) func_800D2454)(D_800EC9FC, func_800D24D0, p) != 0) {
        func_800D2D44(0);
        func_800468FC();
        func_8002D8D4();
        func_800D2AA0(0);
        __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus9)
        goto ret;
    }
    if (func_800D2704(D_800EC9A4, p) != 0) {
        func_800D2D44(0);
        func_800468FC();
        func_8002D8D4();
        func_800D2AA0(0);
        goto ret;
    }
    D_800EC9F4 = 0;
    D_800EC9F8 = 0;
    func_80059658(0);
    VSync(0);
    sp90[0] = 0;
    sp90[1] = 0;
    sp90[2] = p[1] ? (p[6] * 3) / 2 : p[6];
    sp90[3] = p[7] * 2;
    if (p[1] != 0) {
        func_80059888(sp90, 0, 0, 0);
        sp98[0] = 0x1E0;
        sp98[1] = 0;
        sp98[2] = 0xA0;
        sp98[3] = 0x1E0;
        func_80059888(sp98, 0xFF, 0xFF, 0xFF);
    } else {
        func_80059888(sp90, 0, 0, 0);
        sp98[0] = 0x140;
        sp98[1] = 0;
        sp98[2] = 0x140;
        sp98[3] = 0x1E0;
        func_80059888(sp98, 0xFF, 0xFF, 0xFF);
    }
    for (;;) {
        func_800D2C0C(D_800EC9A4[D_800EC9AC], p[1] ? 3 : 2);
        ((void (*)()) func_800D2C88)((&D_800EC9A4[3])[D_800EC9B8],
                                     ((*(s16 *) ((u8 *) D_800EC9A4 + 0x30) << 4) *
                                      ((*(s16 *) ((u8 *) D_800EC9A4 + 0x32) - 1) / 16 + 1)) >> 1);
        if (func_800D2704(D_800EC9A4, p) != 0) {
            func_800D2D44(0);
            func_800468FC();
            func_8002D8D4();
            goto after;
        }
        func_800D298C(D_800EC9A4, 0);
        VSync(0);
        i = (D_800EC9CC == 0);
        SetDefDispEnv(sp18,
                      D_800EC9BC[i * 4] -
                          (p[1] ? (p[4] * 3) / 2 : p[4]),
                      D_800EC9BE[i * 4] - p[5],
                      p[1] ? (p[6] * 3) / 2 : p[6],
                      p[7]);
        if (p[1] != 0) {
            *((u8 *) sp18 + 0x11) = p[1];
            *(s16 *) ((u8 *) sp18 + 4) = (*(s16 *) ((u8 *) sp18 + 4) * 2) / 3;
        }
        func_80059FC0((u8 *) sp18);
        func_80059658(1);
        if (D_800EC9F4 == 1) {
            goto done;
        }
        func_800189A8();
        if (D_800EC9F8 == 0) {
            if (D_800EC9E0 == 0) {
                if (func_80014CAC(0, 0x800) != 0) {
                    D_800EC9E0 = 1;
                    D_800EC9E4 = 0x10;
                    func_8002D8A8();
                }
            } else {
                D_800EC9E4 -= 1;
                if (D_800EC9E4 == 0) {
                    goto done;
                }
            }
        }
        func_8002D034();
    }
done:
    func_800D2D44(0);
    func_800468FC();
    func_8002D8D4();
    func_80043830(9, 0, 0);
after:
    func_800D2AA0(0);
    func_80059658(1);
ret:
    func_80010A98();
    v0r = 1;
    __asm__ __volatile__("" : : "r"(v0r));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B tus9)
}
