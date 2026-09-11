s32 func_801880E8(s32 param_1, s32 arg1)
{
    s32 hole[4];
    Blk20 m;
    s32 vec[3];
    s16 *spt;

    spt = *(s16 **)(param_1 + 0x2C);
    if (*(u16 *)spt == 0) {
        return 0;
    }
    m = D_800AE620;
    RotMatrixY(func_8012B6D4((s16 *)(param_1 + 4), spt + 2), &m);
    vec[1] = 0;
    vec[0] = 0;
    vec[2] = arg1;
    func_800484EC((s32)&m, (s32)vec, param_1 + 0x10);
    return 1;
}
