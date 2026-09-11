s32 func_80181DAC(s32 arg0) {
    extern u8 D_801202A0[];
    u8 *pe;
    u8 *ps;
    s16 *ca;
    s16 *cb;
    u16 state;
    u16 t;
    s32 count;

    pe = D_801202A0;
    count = 0;
    ps = pe + 4;
    do {
        if ((s32)pe == arg0) {
            goto next;
        }
        state = *(u16 *)pe;
        ca = (s16 *)((s32)arg0 + 0);
        if (state == 0x1FC) {
            goto b1fc;
        }
        cb = (s16 *)((s32)ps + 0);
        if (state == 0x239) {
            goto b239;
        }
        goto next;

    b1fc:
        cb = (s16 *)((s32)ps + 0);
        t = (*(s16 *)(*(s32 *)(arg0 + 0x20) + 0x18) * 9u) >> 9;
        goto call;

    b239:
        t = (u32)(*(s16 *)(*(s32 *)(arg0 + 0x20) + 0x18) + *(s16 *)(*(s32 *)(ps + 0x1C) + 0x18)) >> 6;
        /* fall through */
    call:
        if (func_80181E90(ca, cb, t) == 0) {
            goto next;
        }
        return (s32)pe;

    next:
        count++;
        ps += 0x10C;
        pe += 0x10C;
    } while (count < 0x60);
    return 0;
}
