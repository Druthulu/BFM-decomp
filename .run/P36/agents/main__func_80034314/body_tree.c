s32 func_80034314(u32 arg0, u8 *p, u32 arg2) {
    u32 flags;
    Snd54 *e;
    Rec12 *rec;
    u8 *q;
    s16 *pa;
    register s32 idx __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus9)
    s32 ret;
    s32 i;
    s32 j;
    s32 b1;
    u32 x;
    u32 y;

    y = arg0 >> 16;
    flags = arg2;
    x = arg0;
    b1 = p[1];
    if (b1 == 0) {
        rec = &D_80068A54[p[3]];
    } else {
        if (D_800A4EE8 == 0) {
            return 0;
        }
        if (D_800A4EF0 != b1) {
            return 0;
        }
        rec = *(Rec12 **)((u8 *)D_800A4EE8 + 0x18) + p[3];
    }

    idx = func_800348A8(arg0);
    ret = idx;
    if (idx != 0) {
        idx = ret - 1;
        e = (Snd54 *)((u8 *)D_800A46E8 + idx * 0x54);
        if (flags & 0x1000) {
            e->unk1C[0].unk06 = 1;
            e->unk1C[0].unk02 = 0x100;
            e->unk1C[0].unk04 = ((s32)(flags & 0x7F) * 0x3FFF) >> 7;
            if (flags & 0x2000) {
                e->unk38 = D_8006AED8[(flags >> 8) & 0xF];
            } else {
                e->unk38 = 0;
                e->unk39 = 0;
            }
            return ret;
        }
        if (e->unk08 != 0) {
            return 0;
        }
        func_80034650(e, 0);
    } else {
        idx = func_8003310C(rec->unk04);
        ret = idx;
        if (idx == 0) {
            return 0;
        }
        idx = ret - 1;
        e = (Snd54 *)((u8 *)D_800A46E8 + idx * 0x54);
    }

    /* dbr fence (zero-byte, non-volatile asm -> reorg stop_search_p): keeps the
     * `j .L800344B4` delay slot a nop; without it reorg eagerly steals + duplicates
     * the merge block's first store. */
    e->unk37 = rec->unk08;
    e->unk34 = b1;
    e->unk0C = rec->unk00;
    e->unk02 = rec->unk04;
    e->unk10 = e->unk0C;
    e->unk04 = x;
    e->unk06 = y;
    e->unk14 = 1;
    e->unk17 = p[2];
    e->unk16 = 0;
    e->unk18 = 0x7FFF;
    e->unk08 = rec->unk06;
    e->unk50 = 0;
    e->unk52 = 0;

    if (rec->unk08 & 0x10) {
        e->unk48 = 1;
    } else {
        e->unk48 = 0;
    }

    if (rec->unk08 & 4) {
        e->unk1A = 0x400;
    } else if (rec->unk08 & 8) {
        e->unk1A = 0x200;
    } else {
        e->unk1A = 0x5F;
    }
    e->unk36 = 0;
    /* sched fence: without it the two stores (memory-unit users) sink below the
     * whole loop preheader (potential_hazard beats the LUID tie-break). */

    pa = &e->unk1C[0].unk00;
    for (i = 0; i < 3; i++, pa = (s16 *)((u8 *)pa + 8)) {
        pa[1] = 0x100;
        *((u8 *)pa + 6) = 0;
        if (i != 0) {
            pa[0] = 0x3FFF;
            pa[2] = 0x3FFF;
        } else if (flags & 0x1000) {
            pa[0] = ((flags & 0x7F) * 0x3FFF) >> 7;
            pa[2] = ((flags & 0x7F) * 0x3FFF) >> 7;
            if (flags & 0x2000) {
                u8 tv = D_8006AED8[(flags >> 8) & 0xF];
                e->unk38 = tv;
                e->unk39 = tv;
            }
        } else {
            pa[0] = 0x3FFF;
            pa[2] = 0x3FFF;
            e->unk38 = 0;
            e->unk39 = 0;
        }
    }

    q = e->unk3A;
    for (j = 7; j >= 0; j--) {
        *q++ = 0;
    }

    e->unk00 = 5;
    return ret;
}
