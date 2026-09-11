s32 func_80181294(s32 arg0) {
    s32 e;      /* *(s32 *)(arg0 + 0x20) -- the owned effect/entity */
    s16 *rot;   /* (s16 *)(e + 0x10) : rot[0]=0x10 rot[1]=0x12 rot[2]=0x14 */
    s32 i;
    s32 t;
    s32 t2;
    s32 base1;
    s32 base2;
    u16 sp10[3];

    e = *(s32 *)(arg0 + 0x20);
    rot = (s16 *)(e + 0x10);

    if (rand() & 1) {
        *(u16 *)(e + 0x14) += *(s16 *)(arg0 + 0xFC) * (rand() % 8 + 1);
    }

    if (rot[2] > 0x38) {
        *(s16 *)(arg0 + 0xFC) = -1;
        rot[2] = 0x38;
    } else if (rot[2] < -0x38) {
        *(s16 *)(arg0 + 0xFC) = 1;
        rot[2] = -0x38;
    }

    if (*(s32 *)(arg0 + 0x1C) % 10 == 0) {
        sp10[1] = D_8018E40A;
        for (i = 0; i < 5; i++) {
            t = rand() % 80;
            sp10[0] = ((rand() & 1) == 0) ? -t : t;
            t2 = rand() % 16;
            sp10[2] = ((rand() & 1) == 0) ? -t2 + 0x40 : t2 + 0x40;
            ((void (*)(s32, void *, s32))func_8017DC70)(arg0, sp10, 1);
        }
        func_8002D4C8(0xBA0, 0);
        if (*(s32 *)(arg0 + 0x1C) % 10 == 0) {
            sp10[0] = *(u16 *)(arg0 + 0x6);
            sp10[1] = *(u16 *)(arg0 + 0xA);
            sp10[2] = *(u16 *)(arg0 + 0xE) + 0x50;
            for (i = 0; i < 10; i++) {
                s32 v;
                t = rand() % 80;
                base1 = *(s16 *)(arg0 + 0x6);
                if ((rand() & 1) == 0) {
                    v = base1 - t;
                } else {
                    v = base1 + t;
                }
                sp10[0] = v;
                t = rand() % 56;
                base2 = *(s16 *)(arg0 + 0xA);
                if ((rand() & 1) == 0) {
                    v = base2 - t;
                } else {
                    v = base2 + t;
                }
                sp10[1] = v;
                func_80143BDC(sp10);
            }
        }
    }

    if (func_8012BEE8(arg0)) {
        rot[2] = 0;
        func_8012B23C(arg0);
        return 1;
    }
    return 0;
}
