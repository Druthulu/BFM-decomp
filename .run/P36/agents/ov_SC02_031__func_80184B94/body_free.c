s32 func_80184B94(s32 param_1)
{
    s32 iVar1;
    s32 uVar2;

    if (*(u16 *) (param_1 + 6) == 0x31 || *(u16 *) (param_1 + 6) == 0x32) {
        return 1;
    }
    if (*(u16 *) (param_1 + 6) == 0x33 || *(u16 *) (param_1 + 6) == 0x27B) {
        return 1;
    }
    iVar1 = func_800132BC((s32)&D_80126CAC, param_1);
    uVar2 = 0;
    if (D_801274D8 < iVar1) {
        uVar2 = (iVar1 < D_801274DC);
    }
    return uVar2;
}
