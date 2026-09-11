s32 func_80035210(s32 a0, s32 a1)
{
    s32 ret;

    func_8003C498(D_80076218);
    ret = ((s32 (*)(s32, s32))SpuWrite)(a0, a1);
    D_80076218 += a1;
    return ret;
}
