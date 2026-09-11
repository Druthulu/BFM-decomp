void func_8018230C(s32 arg0) {
    u16 base[3];
    struct { s16 vx, vy, vz, pad; } v[16];
    s32 buf[2];
    u16 *bp;
    s32 i;
    s32 j;
    s32 d;
    s32 c;
    s32 acc;
    s32 w;
    s32 ang;

    c = *(s32 *)(arg0 + 0x1C);
    acc = 0;
    for (; c >= 0; c--, acc += D_8018A308) {
        if (c < *(s32 *)(arg0 + 0x1C) - 0x10) {
            break;
        }
        w = D_8018A304 + D_8018A306 * c;
        bp = base;
        {
            u16 z;
            base[0] = *(u16 *)(arg0 + 6);
            base[1] = *(u16 *)(arg0 + 0xA);
            z = *(u16 *)(arg0 + 0xE);
            base[2] = z;
            base[1] = base[1] - D_8018A302 * c;
        }
        for (i = 0, ang = 0; i < 16; i++, ang += 0x100) {
            func_8012B0B4((unsigned int *)buf, ang, w);
            d = buf[0];
            v[i].vx = bp[0] + d;
            v[i].vy = bp[1];
            v[i].vz = bp[2] + (d >> 16);
        }
        i = 0;
        do {
            j = i + 1;
            func_8012D3B4((s32)&v[i], (s32)&v[j & 0xF], acc);
            i = j;
        } while (i < 16);
    }
    if (*(s32 *)(arg0 + 0x1C) == 0x10) {
        *(u32 *)(*(s32 *)(arg0 + 0x20) + 4) &= 0x7FFFFFFF;
    }
    if (func_8012BEE8(arg0) != 0) {
        func_801824D0(arg0);
    }
}
