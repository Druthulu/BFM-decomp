void func_8017E060(s32 *param_1)
{
    extern s8 D_80191C70;

    *(&D_80191C70 + param_1[0x34 / 4]) = 0;
    func_801292C8((u8 *)param_1);
}
