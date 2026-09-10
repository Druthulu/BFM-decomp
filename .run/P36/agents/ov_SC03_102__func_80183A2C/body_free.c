void func_80183A2C(s32 a0) {

    extern u8 D_800AF648;
    extern u8 D_80199B64[];
    /* locals start at sp+0x10 (the 16-byte outgoing-arg area).  The first
       16 bytes are unreferenced in this function but are part of the
       frame — vars must be 0x28, i.e. frame 0x48. */
    struct {
        s32 pad0[4];   /* sp+0x10 */
        s16 v[3];      /* sp+0x20 */
        s16 pad1;      /* sp+0x26 */
        u16 sxy[2];    /* sp+0x28 */
        s32 z;         /* sp+0x2C */
        s32 flag;      /* sp+0x30 */
    } L;
    void *p88;

    p88 = (void *)(a0 + 0x88);

    if (((s32 (*)(s32, u16 *))func_8012BE98)(a0, (u16 *)p88) >= 0x1000) {
        s32 r = func_8012B608(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12),
                              func_8012B744((void *)(a0 + 4), p88), 0x20);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + r;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF;
    }

    func_8012B1B4(a0, (s32)D_80199B64);

    if ((((s32 (*)(s32))func_8012CBA4)(a0) & 0x6000) == 0) {
        s32 r2;
        *(s32 *)(a0 + 0x4) = *(s32 *)(a0 + 0x38);
        *(s32 *)(a0 + 0x8) = *(s32 *)(a0 + 0x3C);
        *(s32 *)(a0 + 0xC) = *(s32 *)(a0 + 0x40);
        r2 = func_8012B608(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12),
                           func_8012B744((void *)(a0 + 4), p88), 0x20);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + r2;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF;
    }

    if (func_8012BD3C(a0, 0x200, 0x40000) == 1) {
        *(s16 *)(a0 + 0x2) = 7;
        L.v[0] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48);
        L.v[1] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C);
        L.v[2] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50);
        { void *r4; r4 = &D_800AF648; func_8004914C(r4); }  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus8)
        { void *r4; r4 = &D_800AF648; func_800491AC(r4); }
        RotTransPers((s32)L.v, (s32)L.sxy, &L.z, &L.flag);
        if (L.flag >= 0 && (u32)((L.sxy[0] + 0x9F) & 0xFFFF) < 0x13F
                        && (u32)((L.sxy[1] + 0x77) & 0xFFFF) < 0xEF) {
            s32 x = (s16)L.sxy[0];
            s32 ax;
            s32 vol;
            ax = x;
            if (x < 0) {
                ax = -x;
            }
            vol = ((0xA0 - ax) * 0x7F) / 0xA0;
            x = (x + 0xA0) / 0x14;
            if (x == 0x10) {
                x = 0xF;
            }
            x = x << 8;
            {
                s32 flg = 0x3000;
                func_8002D4C8(0xA9B, ((vol | flg) | x) & 0xFFFF);
            }
        }
    }
}
