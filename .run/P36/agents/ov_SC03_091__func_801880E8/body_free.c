s32 func_801880E8(s32 param_1, s32 arg1)
{
    s32 hole[4];
    Blk20 m;
    s32 vec[3];
    s16 *spt;

    spt = *(s16 **)(param_1 + 0x2C);
    if (*(u16 *)spt == 0)
        return 0;
    {
        Blk20 *s = &D_800AE620;
        s32 t0, t1, t2;
        t0 = s->w[0]; t1 = s->w[1]; t2 = s->w[2];
        m.w[0] = t0; m.w[1] = t1; m.w[2] = t2;
        t0 = s->w[3]; t1 = s->w[4]; t2 = s->w[5];
        m.w[3] = t0; m.w[4] = t1; m.w[5] = t2;
        t0 = s->w[6]; t1 = s->w[7];
        m.w[6] = t0; m.w[7] = t1;
    }
    RotMatrixY(func_8012B6D4((s16 *)(param_1 + 4), spt + 2), &m);
    vec[1] = 0;
    vec[0] = 0;
    vec[2] = arg1;
    func_800484EC((s32)&m, (s32)vec, param_1 + 0x10);
    return 1;
}
