void func_80030F80(void)
{
    u8 *p;
    u8 *sv;
    u8 *w;
    const u16 *q;
    const u16 *r;
    s32 *tbl;
    s32 vb;
    s32 mask;
    VoiceF80 *e;
    u32 m;
    u32 v;
    s16 n;
    s16 t;
    u8 flag;
    u8 st;
    s32 dsp;
    u16 idx;
    u16 h;
    s32 i;

    sv = D_800A4988 + 0x576;
    p = D_800A4988;
    i = 0;
    tbl = D_80073140;
    w = D_800A4988 + 0x572;
    r = D_8007319E;
    q = D_800731A0;
    for (; i < 8; i++, p += 0x54) {
        flag = 0;
        p[0x4E] &= 0x7F;
        if (p[0x4E] != 0) {
            *(s32 *)(p + 0x4) += 1;
            if (*(s32 *)p != 0) {
                *(s32 *)p -= 1;
                if (*(s32 *)p == 0) {
                    func_8002EFF8(1, tbl[*(u16 *)(p + 0xA)]);
                    func_800316F8((s32)p);
                }
            } else {
                if (p[0x4E] >= 2) {
                    p[0x4E] -= 1;
                } else {
                    idx = *(u16 *)(p + 0xA);
                    dsp = sv[idx];
                    switch (dsp) {
                    case 3:
                        mask = tbl[*(u16 *)(p + 0xA)];
                        p[0x50] = 0;
                        func_8002EFF8(0, mask);
                        /* fallthrough */
                    case 0:
                        p[0x4E] = 0;
                        if (*(s32 *)(p + 0x40) != 0) {
                            (*(void (**)(s32, s32))(p + 0x40))(p[0x51], *(s32 *)(p + 0x44));
                        }
                        *(s32 *)(p + 0x40) = 0;
                        break;
                    case 2:
                        if (p[0x50] != 0) {
                            func_8003D3B4(idx, 1);
                            p[0x50] = 0;
                        }
                        break;
                    }
                }
                if (p[0x4C] != 0) {
                    h = *(u16 *)(p + 0x4A) - 0x220;
                    *(u16 *)(p + 0x4A) = h;
                    flag = 1;
                    if ((s16)h <= 0) {
                        *(u16 *)(p + 0x4A) = 0;
                        p[0x4C] = 0;
                        p[0x50] = 1;
                        D_800A4C6D[i * 0x48] = 1;
                        func_8002EFF8(0, tbl[*(u16 *)(p + 0xA)]);
                    }
                }
                if (p[0x4F] != 0) {
                    flag = 1;
                    p[0x4F] = 0;
                }
                if (p[0x37] & 2) {
                    if (*(s32 *)(p + 0x1C) >= 0) {
                        *(s32 *)(p + 0x18) += *(u16 *)(p + 0x32);
                        if (*(s32 *)(p + 0x18) >= *(s32 *)(p + 0x1C)) {
                            *(s32 *)(p + 0x18) = *(s32 *)(p + 0x1C);
                            p[0x37] &= 0xFD;
                        }
                    } else {
                        *(s32 *)(p + 0x18) -= *(u16 *)(p + 0x32);
                        if (*(s32 *)(p + 0x18) <= *(s32 *)(p + 0x1C)) {
                            *(s32 *)(p + 0x18) = *(s32 *)(p + 0x1C);
                            p[0x37] &= 0xFD;
                        }
                    }
                    flag = 1;
                }
                if ((D_800A4F19 != 0 && p[0x53] != 0) || flag) {
                    n = p[0x35];
                    if (n != 0) {
                        t = n + (*(s32 *)(p + 0x18) >> 8);
                        n = t;
                        if (p[0x53] != 0) {
                            t = p[0x53] + t;
                            if (t < 0x42) {
                                n = 1;
                            } else {
                                t -= 0x40;
                                n = t;
                                if (t >= 0x80) {
                                    n = 0x7F;
                                }
                            }
                        }
                    }
                    if (flag || n != p[0x52]) {
                        m = D_8006AA30[p[0x34]];
                        m = (m * *(s16 *)w) >> 7;
                        m = (m * *(s16 *)(p + 0x48)) >> 7;
                        if (flag) {
                            m = (m * ((s16)*(u16 *)(p + 0x4A) >> 7)) >> 8;
                        }
                        vb = (s32)w - 0x2D2;
                        e = (VoiceF80 *)(i * 0x48 + vb);
                        e->unk00 = tbl[*(u16 *)(p + 0xA)];
                        if (n != 0) {
                            if (w[0x1F] != 0) {
                                v = (m * q[0x7F - n]) >> 14;
                                e->unk08 = v;
                                v = (m * r[n]) >> 14;
                                e->unk0A = v;
                            } else {
                                v = (m * D_8007321E) >> 14;
                                e->unk0A = v;
                                e->unk08 = v;
                            }
                        } else {
                            v = m;
                            e->unk0A = v;
                            e->unk08 = v;
                        }
                        e->unk40 = *(u16 *)(p + 0xA);
                        if (e->unk44 != 0) {
                            e->unk04 |= 3;
                        } else {
                            e->unk44 = 1;
                            e->unk04 = 3;
                        }
                        p[0x52] = n;
                    }
                }
                func_800314DC((struct Obj *)p);
                h = *(u16 *)(p + 0x12);
                if (h != 0) {
                    h -= 1;
                    *(u16 *)(p + 0x12) = h;
                    if (h == 0) {
                        func_80031988((struct Ent30D80 *)p);
                        mask = tbl[*(u16 *)(p + 0xA)];
                        p[0x50] = 0;
                        func_8002EFF8(0, mask);
                        if (*(s32 *)(p + 0x40) != 0) {
                            (*(void (**)(s32, s32))(p + 0x40))(p[0x51], *(s32 *)(p + 0x44));
                        }
                        *(s32 *)(p + 0x40) = 0;
                    }
                }
            }
        } else {
            st = sv[*(u16 *)(p + 0xA)];
            if (st == 0 || st == 3) {
                D_800C7D2C &= ~tbl[*(u16 *)(p + 0xA)];
            }
        }
    }
}
