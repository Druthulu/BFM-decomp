void func_801841A4(s32 a0) {

    extern u8   D_800AF648;

    struct {
        s16 v[3];    /* sp+0x10 */
        s16 pad1;    /* sp+0x16 */
        u16 sxy[2];  /* sp+0x18 */
        s32 z;       /* sp+0x1C */
        s32 flag;    /* sp+0x20 */
        s32 pad2;    /* sp+0x24 -- dead, sizes the frame */
    } L;

    s16 hp;
    s32 state;
    s32 p;

    hp = *(s16 *)(*(s32 *)(a0 + 0x20) + 0x14);
    if (hp >= 0xD00) {
        goto L_A;
    }
    state = 3;
    if (hp != 0) {
        goto L_B;
    }

L_A:
    {
        s32 count;
        s32 total;

        count = *(u16 *)(a0 + 0xFC);
        total = *(u16 *)(a0 + 0xFE);
        count = count + 1;
        total = total + count;
        *(u16 *)(a0 + 0xFC) = count;
        *(u16 *)(a0 + 0xFE) = total;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) - total;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) & 0xFFF;
    }
    goto L_end;

L_B:
    p = *(s32 *)(a0 + 0xCC);
    *(s16 *)(a0 + 2) = state;
    *(s32 *)(a0 + 0x1C) = 0x1E;
    *(s16 *)(a0 + 0x98) = 0;
    *(s16 *)(p + 2) = state;
    *(s32 *)(p + 0x1C) = 0x1E;
    *(s16 *)(p + 0x98) = 0;

    L.v[0] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48);
    L.v[1] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C);
    L.v[2] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50);
    { void *r4; r4 = &D_800AF648; func_8004914C(r4); }  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus7)
    { void *r4; r4 = &D_800AF648; func_800491AC(r4); }
    RotTransPers((s32)L.v, (s32)L.sxy, &L.z, &L.flag);
    if (L.flag >= 0 && (u32)((L.sxy[0] + 0xEF) & 0xFFFF) < 0x1DF
                    && (u32)((L.sxy[1] + 0xB3) & 0xFFFF) < 0x167) {
        s32 sx = (s16)L.sxy[0];
        s32 av;
        av = sx;
        if (sx < 0) {
            av = -sx;
        }
        av = ((0xF0 - av) * 0x7F) / 0xF0;
        sx = (sx + 0xF0) / 0x1E;
        if (sx == 0x10) {
            sx = 0xF;
        }
        sx = sx << 8;
        func_8002D4C8(0x961, (av | (0x3000 | sx)) & 0xFFFF);
    }

L_end:
    func_8012B370(a0);
}
