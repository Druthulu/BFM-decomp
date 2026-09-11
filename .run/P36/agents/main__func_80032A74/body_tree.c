void func_80032A74(Slot54 *arg0, s32 arg1, Rec14 *arg2, s32 flags) {
#define REQ ((Req32A74 *)arg0)
#define REC ((Rec32A74 *)arg2)
    C24 sp10;

    Chan32A74 *ch;
    Voice32A74 *vo;
    A12 *dd;
    B12 *q;
    u8 *cp;
    const u16 *tA;
    const u16 *tB;
    u8 *vB;
    s32 i2;
    u16 v;
    u32 vv;
    s32 idx;
    s32 w;
    s32 n;
    s32 flag;
    s32 h;
    s32 i;
    s32 b;
    s32 sub;
    u8 pan;
    u32 vol;
    u32 mp;
    u32 qq;
    s32 tb;
    u32 d;
    register s32 base __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus9)
    u16 t16;
    s32 t8;
    s32 t32;
    u32 gx;

    tA = D_8007319E;
    tB = D_800731A0;
    vB = (u8 *)D_800A4C28;
    v = REQ->unk02;
    i = 7;
    cp = (u8 *)arg0 + 7;
    do {
        cp[0xE] = 0;
        i--;
        cp--;
    } while (i >= 0);
    REQ->unk0C = 0;

    for (;;) {
        b = REC->unk08;
        flag = 0;
        if ((b & 0x80) == 0) {
            dd = &D_80064D44[b];
            sub = REC->unk09;
            if (dd->unk06 != 0) {
                gx = dd->unk07;
                gx -= 0x100;
                flag = (u32)sub < (u32)(u8)gx;
            }
            n = D_800C5328[b * 2];
            if (n < 0) {
                if (flag == 0) {
                    break;
                }
                n = D_800C532A[b * 2];
                if (n < 0) {
                    break;
                }
                if (sub >= D_800A4646[n * 12]) {
                    break;
                }
            }
        } else {
            n = 4;
        }
        if ((flags & 0x1000) && (flags & 0x7F) < 0x30U) {
            v >>= 1;
            flags = (flags & 0xFF80) | (0x2F - ((0x2F - (flags & 0x7F)) >> 1));
        }
        idx = func_80030CA4(v);
        if (idx != 0) {
            idx--;
            vo = (Voice32A74 *)(idx * 0x48 + (s32)vB);
            if ((b & 0x80) == 0) {
                q = &D_8006A970[n][REC->unk09];
                vo->unk1C = q->unk00;
                vo->unk18 = q->unk04;
                vo->unk3A = q->unk06;
                vo->unk3C = q->unk08;
            } else {
                if (func_8003F144(D_800A46A2, b & 0x7F, REC->unk09, &sp10) != 0) {
                    goto next;
                }
                h = func_8003F380(D_800A46A2, sp10.unk16);
                if (h < 0) {
                    goto next;
                }
                tb = sp10.unk04;
                vo->unk1C = h;
                vo->unk18 = tb << 8;
                vo->unk3A = sp10.unk10;
                vo->unk3C = sp10.unk12;
            }
            w = idx + 0x10;
            vo->unk00 = D_80073140[w];
            ch = (Chan32A74 *)(D_800A4988 + idx * 0x54);
            ch->unk4C = 0;
            ch->unk4A = 0x7FFF;
            if (REQ->unk00 & 0x80) {
                ch->unk4D = 0;
            } else {
                ch->unk4D = 1;
            }
            t16 = REC->unk02;
            ch->unk04 = 0;
            ch->unk08 = v;
            ch->unk0A = w;
            ch->unk00 = t16;
            t8 = REC->unk09;
            ch->unk0E = b;
            ch->unk36 = flag;
            ch->unk10 = n;
            ch->unk12 = 0;
            ch->unk0C = t8;
            t32 = REC->unk10;
            ch->unk4F = 0;
            ch->unk4E = 0x85;
            ch->unk14 = t32;
            __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus9)
            vol = REC->unk06;
            if (D_800A4F1E != 0) {
                vol *= 0x70;
                vol >>= 7;
            }
            if (flags & 0x1000) {
                ch->unk48 = flags & 0x7F;
            } else {
                ch->unk48 = 0x7F;
            }
            ch->unk34 = vol & 0x7F;
            pan = REC->unk07;
            ch->unk35 = pan;
            if (flags & 0x8000) {
                ch->unk24 = REC->unk04 - 0x80;
            } else {
                ch->unk24 = REC->unk04;
            }
            ch->unk40 = (s32)func_80033324;
            ch->unk44 = arg1;
            if ((flags & 0x2000) && pan != 0) {
                if ((flags & 0x3000) == 0x3000) {
                    ch->unk53 = D_8006AED8[(u32)(flags & 0xF00) >> 8];
                } else {
                    ch->unk53 = flags & 0x7F;
                }
            } else {
                ch->unk53 = 0;
            }
            if (REC->unk02 == 0) {
                func_800316F8(ch);
            }
            {
                u16 u18 = vo->unk18;
                base = (u18 & 0xFF00) + (s8)u18 * 2;
            }
            base -= 0x3C00;
            d = ch->unk24;
            d -= base;
            if (d >= 0x5300) {
                vo->unk14 = 0x3FFF;
            } else {
                qq = D_8006AB30[d >> 8];
                qq = qq * (0x100 - (d & 0xFF));
                vo->unk14 = (qq + D_8006AB32[d >> 8] * (d & 0xFF)) >> 8;
            }
            vol = D_8006AA30[ch->unk34];
            mp = vol * D_800A4EFA;
            vol = mp >> 7;
            mp = vol * ch->unk48;
            vol = mp >> 7;
            if (pan != 0) {
                if (ch->unk53 != 0) {
                    pan += ch->unk53;
                    if (pan >= 0x42) {
                        pan -= 0x40;
                        if (pan >= 0x80) {
                            pan = 0x7F;
                        }
                    } else {
                        pan = 1;
                    }
                }
                if (D_800A4F19 != 0) {
                    vv = (vol * tA[pan]) >> 14;
                    vo->unk0A = vv;
                    vv = (vol * tB[0x7F - pan]) >> 14;
                    vo->unk08 = vv;
                } else {
                    vv = (vol * D_8007321E) >> 14;
                    vo->unk0A = vv;
                    vo->unk08 = vv;
                }
            } else {
                vv = vol;
                vo->unk08 = vv;
                vo->unk0A = vv;
            }
            ch->unk52 = pan;
            vo->unk0C = 0;
            vo->unk0E = 0;
            vo->unk04 = 0x6009F;
            __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus9)
            if (D_800A4EF6 > REC->unk0A) {
                func_8002F064(1, vo->unk00);
            } else {
                func_8002F064(0, vo->unk00);
            }
            t16 = ch->unk0A;
            vo->unk45 = 0;
            vo->unk44 = 1;
            vo->unk40 = t16;
            if (REC->unk02 == 0) {
                func_8002EFF8(1, vo->unk00);
            }
            REQ->unk0C++;
            REQ->unk0E[idx] = 1;
        }
    next:
        if (REC->unk0B == 0) {
            break;
        }
        arg2++;
        v = REC->unk00;
    }
    if (REQ->unk0C == 0) {
        REQ->unk00 = 0;
    } else {
        REQ->unk0A = 4;
    }
}
