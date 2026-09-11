void func_800314DC(Obj *p) {
    Slot *e;
    s32 *r;
    u16 h;
    u32 t;
    u32 d;
    u32 q;

    if (!(p->unk37 & 1)) {
        return;
    }

    if (p->unk30 != 0) {
        p->unk30--;
        return;
    }

    if (p->unk2C < 0) {
        p->unk24 += p->unk2C;
        if (p->unk24 <= p->unk28) {
            p->unk24 = p->unk28;
            p->unk37 &= 0xFE;
        }
    } else {
        p->unk24 += p->unk2C;
        if (p->unk24 >= p->unk28) {
            p->unk24 = p->unk28;
            p->unk37 &= 0xFE;
        }
    }

    if (!(p->unk37 & 1) && p->unk38 != 0) {
        if (p->unk24 != p->unk3C) {
            p->unk28 = p->unk3C;
            if (p->unk3C < p->unk24) {
                p->unk2C = -p->unk3A;
            } else {
                p->unk2C = p->unk3A;
            }
        }
        p->unk38 = 0;
        p->unk37 |= 1;
    }

    e = &D_800A4C28[p->unk51];
    /* two statements: the pointer's uses all fold into one address, but reload still gives it the
       8-byte stack slot the target's frame carries (S103 c35 / S104 d25, reload1.c:2331-2352) */
    r = D_80073140;
    r += p->unk0A;
    e->unk00 = *r;
    h = D_8006A970[p->unk10][p->unk0C].unk04;
    t = h;
    t = (t & 0xFF00) + ((s8)t * 2);
    e->unk18 = h;
    t -= 0x3C00;
    d = p->unk24;
    d -= t;
    if (d >= 0x5300) {
        e->unk14 = 0x3FFF;
    } else {
        q = D_8006AB30[d >> 8] * (0x100 - (d & 0xFF));
        q += D_8006AB32[d >> 8] * (d & 0xFF);
        e->unk14 = q >> 8;
    }
    e->unk40 = p->unk0A;
    if (e->unk44 != 0) {
        e->unk04 |= 0x10;
    } else {
        e->unk44 = 1;
        e->unk04 = 0x10;
    }
}
