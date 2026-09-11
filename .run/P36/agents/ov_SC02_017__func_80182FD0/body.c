void func_80182FD0(int param)
{
    struct {
        s16 v[4];
        s32 flag;
    } w;
    u8 *s0;
    u8 *m = &D_800AF648;
    s32 lim;
    s32 lim2;

    s0 = ((u8 **)D_8018E8DC)[*(s16 *)(param + 0xFC)];

    gte_SetRotMatrix(m);
    gte_SetTransMatrix(m);

    func_80015978(param + 4, (s32 *)w.v);
    gte_ldv0(w.v);
    gte_rtps();
    gte_stsxy(w.v);
    gte_stflg(&w.flag);

    lim = (D_800AF7BC >> 1) + 0x20;
    if (w.v[0] > -lim && w.v[0] < lim) {
        lim2 = (D_800AF7BE >> 1) + 0x20;
        if (w.v[1] > -lim2 && w.v[1] < lim2 && w.flag >= 0) {
            if (*(s32 *)(param + 0x1C) == 0) {
                while (*(s16 *)(s0 + 6) != 0xFF) {
                    func_80183168((u8 *)param, s0);
                    s0 += 8;
                }
                *(s32 *)(param + 0x1C) = *(s32 *)(param + 0xDC);
            }
            *(s32 *)(param + 0x1C) -= 1;
        }
    }
    func_801831FC(param);
}
