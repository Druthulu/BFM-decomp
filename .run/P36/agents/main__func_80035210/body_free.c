void func_80035210(s32 a0, s32 a1)
{
    s32 v1;

    v1 = D_80076218;
    func_8003C498(v1);
    SpuWrite(a0, a1);
    v1 = D_80076218;
    D_80076218 = v1 + a1;
}
