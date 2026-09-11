void func_800336A8(Req336A8 *arg)
{
    Chan336A8 *ch;
    Voice336A8 *vo;
    u16 *p;
    const u16 *q;
    u32 m;
    u32 n;
    u32 v;
    s32 i;
    s32 j;

    for (i = 0; i < 8; i++) {
        if (arg->unk3A[i] == 0) {
            continue;
        }
        ch = (Chan336A8 *)(D_800A4988 + i * 0x54);
        vo = (Voice336A8 *)(D_800A4988 + 0x2A0 + i * 0x48);
        vo->unk00 = D_80073140[ch->unk0A];
        m = ch->unk34;
        m = D_8006AA30[m];
        m = m * *(s16 *)(D_800A4988 + 0x572);
        m = m >> 7;
        if (arg->unk16 != 0) {
            m = m * arg->unk18;
            m = m >> 15;
        }
        p = arg->unk1C;
        for (j = 2; j >= 0; j--, p += 4) {
            m = m * *p;
            m = m >> 14;
        }
        n = ch->unk35;
        if (n == 0) {
            v = m;
            vo->unk0A = v;
            vo->unk08 = v;
        } else {
            if (arg->unk38 != 0) {
                n += arg->unk38;
                if (n >= 0x42) {
                    n -= 0x40;
                    if (n >= 0x80) {
                        n = 0x7F;
                    }
                } else {
                    n = 1;
                }
            }
            ch->unk52 = n;
            if (D_800A4F19 != 0) {
                /* zero-byte dbr fence: ASM_INPUT stops reorg's fallthrough trial scan
                 * (stop_search_p), so the beqz above keeps its `nop` delay slot. */
                __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus9)
                v = (m * D_8007319E[n]) >> 14;
                vo->unk0A = v;
                q = D_8007319E + 1;
                v = (m * q[0x7F - n]) >> 14;
                vo->unk08 = v;
            } else {
                v = (m * D_8007321E) >> 14;
                vo->unk0A = v;
                vo->unk08 = v;
            }
        }
        vo->unk40 = ch->unk0A;
        if (vo->unk44 != 0) {
            vo->unk04 |= 3;
        } else {
            vo->unk04 = 3;
            vo->unk44 = 1;
        }
    }
}
