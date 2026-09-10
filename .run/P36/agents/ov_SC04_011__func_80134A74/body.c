int func_80134A74(int param_1, s16 param_2, s16 param_3, int param_4)
{
    extern u16 D_801EDA40;
    extern s32 func_80134C20(s32, s32, s32, s32);

    Map_80133AB0 *map = (Map_80133AB0 *)param_4;
    u32 X, Y, cell;
    u16 Xc, Yc;
    u16 k, off, cnt;
    u16 *cp, *lst;
    u16 raw;
    u32 hib;
    u16 harg;
    u8 *s0;
    void *p0C, *p10;
    u8 *p14, *p18, *p1C;

    X = ((((u16)param_2 + 0x8000) >> 7) & 0x1ff) - map->ox;
    Xc = X;
    if (!((X & 0xffff) < map->w))
        return 0;
    Y = ((((u16)param_3 + 0x8000) >> 7) & 0x1ff) - map->oy;
    Yc = Y;
    if (!((Y & 0xffff) < map->h))
        return 0;

    p0C = map->p0C;
    p10 = map->p10;
    p18 = map->p18;
    p1C = map->p1C;
    cell = Yc * map->w + Xc;
    k = cell * 2;
    cp = (u16 *)(k * 2 + (u32)map->cells);
    p14 = map->p14;
    off = cp[0];
    cnt = cp[1];
    lst = (u16 *)(p14 + off + cnt * 2) - 1;

    while (cnt-- != 0) {
        raw = *lst;
        hib = raw & 0x8000;
        harg = hib;
        if (hib == 0) {
            s0 = p18 + raw * 18;
        } else {
            s0 = p1C + (raw & 0x7fff) * 22;
        }
        lst--;
        if (func_80134C20((s16)(harg | param_1), (s32)s0, (s32)p10, (s32)p0C) != 0) {
            D_801EDA40 = *(u16 *)s0;
            return 1;
        }
    }
    return 0;
}
