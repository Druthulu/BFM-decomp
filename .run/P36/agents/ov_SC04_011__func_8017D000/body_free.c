void func_8017D000(void *a0) {

    extern s16 D_80193E7C;
    extern s16 D_80193E88;
    extern s16 D_80193E94;
    extern s16 D_801EED28;
    extern s16 D_801EED30;
    extern s16 D_801EED40;
    extern u8  D_801EED49;
    extern u8  D_801EED4A;
    extern u8  D_801EED4D;
    extern u8  D_801EED4E;
    extern u8  D_801EED51;
    extern u8  D_801EED52;
    extern u8  D_801EED55;
    extern u8  D_801EED56;
    extern s16 D_801EED64;
    extern s16 D_801EED6C;
    extern s16 D_801EED74;
    extern u8  D_801EED7E;
    extern u8  D_801EED80;
    extern u8  D_801EED82;
    extern u8  D_801EED86;
    extern u8  D_801EED88;
    extern u8  D_801EED8A;
    extern s16 D_801EED98;
    extern s16 D_801EEDA8;

    s16 cur = *(s16 *)((s32)a0 + 0x108);
    s32 lo = **(s16 **)((s32)a0 + 0xD4);
    s32 hi = **(s16 **)((s32)a0 + 0xD8);
    s32 hw;
    s16 h;
    s16 c;
    s32 t;

    s16 *p;
    void *w;

    if (cur != lo) {
        if (lo < cur) {
            s32 d;
            s16 *r;
            *(s16 *)((s32)a0 + 0x108) = cur - hi * 3 / *(s16 *)((s32)a0 + 0x70);
            if (*(s16 *)((s32)a0 + 0x108) < lo) {
                *(s16 *)((s32)a0 + 0x108) = lo;
            }
            d = *(s16 *)((s32)a0 + 0x108) * *(s16 *)((s32)a0 + 0x70) / hi;
            r = &D_80193E7C;
            *r = d;
            if (*r == 0) {
                if (lo != 0) {
                    *r = 1;
                }
            }
        } else if (cur < *(s16 *)((s32)a0 + 0x10A)) {
            *(s16 *)((s32)a0 + 0x108) = cur + hi * 3 / *(s16 *)((s32)a0 + 0x70);
            if (lo < *(s16 *)((s32)a0 + 0x108)) {
                *(s16 *)((s32)a0 + 0x108) = hi;
            }
            D_80193E7C = *(s16 *)((s32)a0 + 0x108) * *(s16 *)((s32)a0 + 0x70) / hi;
        } else if (*(s16 *)((s32)a0 + 0x10A) < hi) {
            *(s16 *)((s32)a0 + 0x10A) =
                *(s16 *)((s32)a0 + 0x10A) + hi * 3 / *(s16 *)((s32)a0 + 0x70);
            if (hi < *(s16 *)((s32)a0 + 0x10A)) {
                *(s16 *)((s32)a0 + 0x10A) = hi;
            }
            D_80193E88 = *(s16 *)((s32)a0 + 0x10A) * *(s16 *)((s32)a0 + 0x70) / hi;
            D_80193E94 = D_80193E88 + 2;
        }
    }

    if (*(s16 *)((s32)a0 + 0xFC) == 0xB) {
        s32 f = *(s32 *)((s32)a0 + 0x1C);
        s32 v = -(f & 1) & 0xC0;
        f = f + 1;
        *(s32 *)((s32)a0 + 0x1C) = f;
        D_801EED51 = v;
        D_801EED49 = v;
        D_801EED8A = v;
        D_801EED86 = v;
        D_801EED82 = v;
        D_801EED7E = v;
        D_801EED56 = v;
        D_801EED52 = v;
        D_801EED4E = v;
        D_801EED4A = v;
    }

    hw = (s16) * (u16 *)((s32)a0 + 0x70) >> 1;
    h = hw;
    c = D_80193E7C;
    if (c < h) {
        D_801EED30 = (u16)D_801EED28 + c;
        D_801EED40 = (u16)D_801EED28 + c - 4;
        D_801EED55 = c * 255 / h;
        D_801EED4D = c * 255 / h;
    } else {
        u8 *q;
        u16 bs;
        s32 x;
        s16 y;
        t = (c - h) * 255 / h;
        q = &D_801EED4D;
        bs = (u16)D_801EED28;
        x = bs + hw;
        y = x - 4;
        D_801EED55 = 0xFF;
        *q = 0xFF;
        *(s16 *)(q + 0xF) = x;
        D_801EED64 = bs + c;
        D_801EED30 = x;
        D_801EED6C = y;
        D_801EED40 = y;
        D_801EED74 = bs + c - 4;
        D_801EED88 = -t;
        D_801EED80 = -t;
        func_800176F0(q + 0xF);
    }

    p = &D_801EEDA8;
    D_801EED98 = *(u16 *)((s32)p - 0x18) + (u16)D_80193E88;
    *p = D_801EED98 - 4;
    w = (void *)((s32)p - 0x80);
    p = (s16 *)((s32)p - 0x18);
    func_800176F0(w);
    func_800176F0(p);
}
