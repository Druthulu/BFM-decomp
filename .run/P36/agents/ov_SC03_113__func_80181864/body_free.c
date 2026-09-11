void func_80181864(s32 arg0) {
    extern void func_8012C218(void *a0);
    extern s32 func_8012CC64(s32 a0, void *a1);
    extern s32 func_80133784(s32 a0, void *a1, s32 a2);
    extern void func_8012E688(s32 arg0, s32 arg1, s32 arg2);
    extern void func_8012B23C(s32 a0);
    extern void func_8012B1B4(s32 a0, s32 a1);
    extern s32 rand(void);
    extern s32 D_8019F2A8;
    extern s32 D_8019F28C;

    s32 e;
    s32 n;
    s32 dir;

    e = arg0;
    if (--*(s16 *)(e + 0xFC) == 0) {
        n = 0;
        do {
            arg0 = *(s32 *)(arg0 + 0x6C);
            n++;
        } while (arg0 != 0);
        if (n < 7) {
            if (e != 0) {
                arg0 = e;
                for (;;) {
                    e = *(s32 *)(arg0 + 0x6C);
                    func_8012C218((void *)arg0);
                    arg0 = e;
                    if (arg0 == 0) {
                        return;
                    }
                }
            }
            return;
        }
    }

    {
        s32 f;

        *(s16 *)(*(s32 *)(e + 0x20) + 0x14) += 0x40;
        *(s16 *)(*(s32 *)(e + 0x20) + 0x14) &= 0xFFF;
        f = func_8012CC64(e, &D_8019F2A8);

        if (f & 0x1000) {
            *(s16 *)(e + 0x2) = 0x12;
            return;
        }

        n = 0;
        if (f & 0xC000) {
            s16 p1[3];
            s16 p2[3];

            {
                s16 *q = p2;
                s32 x;
                s32 y;
                s32 z;

                *(s16 *)(e + 0x16) = -(rand() & 3) - 8;
                x = *(u16 *)(e + 6);
                p1[0] = x - 0x20;
                y = *(u16 *)(e + 0xA) + 0x10;
                p1[1] = y;
                z = *(u16 *)(e + 0xE) + 0x20;
                p1[2] = z;
                q[0] = x + 0x20;
                q[1] = y;
                q[2] = z;

                if (func_80133784(1, p1, (s32)q) != 0) {
                    n = 1;
                    *(s16 *)(e + 0x12) = -(rand() & 3) - 4;
                } else {
                    q[0] = p1[0] + 0x40;
                    q[1] = p1[1];
                    q[2] = p1[2];
                    if (func_80133784(1, q, (s32)p1) != 0) {
                        n = 2;
                        *(s16 *)(e + 0x12) = (rand() & 3) + 4;
                    }
                }
            }
            {
                s16 *q = p2;
                s32 x;
                s32 y;
                s32 z;

                x = *(u16 *)(e + 6);
                p1[0] = x;
                y = *(u16 *)(e + 0xA) + 0x10;
                p1[1] = y;
                z = *(u16 *)(e + 0xE);
                p1[2] = z;
                q[0] = x;
                q[1] = y;
                q[2] = z + 0x40;

                if (func_80133784(1, p1, (s32)q) != 0) {
                    n += 4;
                    *(s16 *)(e + 0x1A) = -(rand() & 3) - 4;
                } else {
                    q[0] = p1[0];
                    q[1] = p1[1];
                    q[2] = p1[2] + 0x40;
                    if (func_80133784(1, q, (s32)p1) != 0) {
                        n += 8;
                        *(s16 *)(e + 0x1A) = (rand() & 3) + 4;
                    }
                }
            }

            switch (n - 1) {
            case 0:
                dir = 0x800;
                break;
            case 1:
                dir = 0;
                break;
            case 3:
                dir = 0x400;
                break;
            case 4:
                dir = 0x600;
                break;
            case 5:
                dir = 0x200;
                break;
            case 7:
                dir = 0xC00;
                break;
            case 8:
                dir = 0xA00;
                break;
            case 9:
                dir = 0xE00;
                break;
            }
            *(s16 *)(*(s32 *)(e + 0x20) + 0x12) = dir;
        } else if (f & 0x2000) {
            func_8012E688(e, 0x833, 0);
            if ((rand() & 0xF) == 0) {
                s32 t1;
                s32 t2;
                s32 t3;
                s32 p;

                *(s16 *)(*(s32 *)(e + 0x20) + 0x14) = 0;
                t1 = *(u16 *)(e + 6);
                t2 = *(u16 *)(e + 0xA);
                t3 = *(u16 *)(e + 0xE);
                *(s16 *)(e + 0x2) = 1;
                *(s16 *)(e + 0x34) = 1;
                *(s16 *)(e + 0x70) = 0;
                *(s16 *)(e + 0x88) = t1;
                *(s16 *)(e + 0x8A) = t2;
                *(s16 *)(e + 0x8C) = t3;
                func_8012B23C(e);
                func_8012B1B4(e, (s32)&D_8019F28C);
                p = *(s32 *)(e + 0x6C);
                if (p != 0) {
                    do {
                        *(s16 *)(p + 0x2) = 2;
                        *(s16 *)(p + 0x70) -= 0x10;
                        *(s16 *)(*(s32 *)(p + 0x20) + 0x14) = 0;
                        p = *(s32 *)(p + 0x6C);
                    } while (p != 0);
                }
                *(s16 *)(e + 0xFC) = 0;
            } else {
                *(s16 *)(e + 0x16) = -(rand() & 3) - 8;
            }
        }
    }

    if (*(s16 *)(e + 0xA) >= 0x65) {
        func_8012C218((void *)e);
    }
}
