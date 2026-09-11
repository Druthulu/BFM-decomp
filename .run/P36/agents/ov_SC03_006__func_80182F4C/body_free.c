s32 func_80182F4C(s32 a0, s16 a1)
{
    u8 *base;
    s16 val;
    u16 c0;
    u16 c1;
    u16 outerIdx;
    u16 innerIdx;
    u16 diff;
    s32 prod;
    u16 temp2;
    u16 idx2;
    u16 *tbl;
    s32 p1;
    s32 p2;
    s32 p3;
    u16 dx;
    u16 n;
    u16 sample;
    s32 addr;
    s16 cur;
    u16 v;

    base = D_801AD31C;
    c0 = 0xF800;
    val = (s16)a0;

    do {
        c1 = 0xFA00;
        outerIdx = (c0 + 0x8000) >> 7 & 0x1FF;
        do {
            innerIdx = (c1 + 0x8000) >> 7 & 0x1FF;
            diff = innerIdx - *(u16 *)(base + 2);
            prod = diff * *(u16 *)(base + 4);
            p1 = *(s32 *)(base + 0x14);
            p2 = *(s32 *)(base + 0x18);
            p3 = *(s32 *)(base + 0x1C);
            temp2 = outerIdx - *(u16 *)(base + 0);
            tbl = *(u16 **)(base + 0x8);
            idx2 = (prod + temp2) * 2;
            dx = tbl[idx2];
            n = tbl[idx2 + 1];
            p1 += dx;
            while (n--) {
                sample = *(u16 *)p1;
                if (!(sample & 0x8000)) {
                    addr = p2 + sample * 18;
                } else {
                    v = sample & 0x7FFF;
                    addr = p3 + v * 22;
                }
                cur = *(s16 *)addr;
                if (cur == val) {
                    *(s16 *)addr = a1;
                }
                p1 += 2;
            }
            c1 += 0x80;
        } while (c1 <= 0xFDFF);
        c0 += 0x80;
    } while (c0 <= 0xFBFF);
}
