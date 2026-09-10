void func_8017DBE4(s32 *param_1)
{
    extern u8 D_801B2028[];

    D_801B2028[param_1[0x2c / 4]] = 0;
    ((void (*)(s32 *))func_80146C3C)(param_1);
}
