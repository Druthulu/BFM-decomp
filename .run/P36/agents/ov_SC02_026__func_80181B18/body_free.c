void func_80181B18(s32 a0) {
    s32 state;   /* $s0 */
    s32 ent;
    s32 sub;
    s32 t;
    s32 v;
    s32 cnt;

    ent = a0;
    state = *(u16 *)(ent + 0x34);

    switch (state) {
    case 0:
        if (0x10000 < ((s32 (*)(s32))func_8012BE54)(ent)) {
            return;
        }
        *(u16 *)(ent + 0x34) = *(u16 *)(ent + 0x34) + 1;
        func_8012E88C((u8 *)ent);
        func_8012B21C((void *)ent);
        return;
    case 1:
        if ((((s32 (*)(s32))func_8012CBCC)(ent) & 0x2000) == 0) {
            return;
        }
        *(s32 *)(ent + 0x1C) = state;
        *(u16 *)(ent + 0x34) = *(u16 *)(ent + 0x34) + 1;
        func_8002D4C8(0x703, 0);
        /* fallthrough */
    case 2:
        sub = *(s32 *)(ent + 0x20);
        t = func_8004787C(*(s32 *)(ent + 0x1C) << 7);
        v = (t * 0x1c00 >> 12) + 0x400;
        *(s16 *)(sub + 0x1C) = v;
        *(s16 *)(sub + 0x18) = v;
        {
            s32 w = 0x3000 - (t * 0x2800 >> 12);
            *(s16 *)(sub + 0x1A) = w;
        }
        cnt = *(s32 *)(ent + 0x1C) + 1;
        *(s32 *)(ent + 0x1C) = cnt;
        if (cnt < 9) {
            return;
        }
        *(s32 *)(ent + 0x1C) = 1;
        *(u16 *)(ent + 0x34) = *(u16 *)(ent + 0x34) + 1;
        return;
    case 3:
        sub = *(s32 *)(ent + 0x20);
        t = func_8004787C(*(s32 *)(ent + 0x1C) << 7);
        {
            s32 lo;
            lo = (t << 12) >> 12;
            v = 0x2000 - lo;
        }
        *(s16 *)(sub + 0x1C) = v;
        *(s16 *)(sub + 0x18) = v;
        {
            s32 w = ((t * 0x800) >> 12) + 0x800;
            *(s16 *)(sub + 0x1A) = w;
        }
        cnt = *(s32 *)(ent + 0x1C) + 1;
        *(s32 *)(ent + 0x1C) = cnt;
        if (8 < cnt) {
            *(u16 *)(ent + 2) = 1;
        }
        return;
    }
}
