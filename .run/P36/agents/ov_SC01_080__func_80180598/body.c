void func_80180598(s32 arg0)
{
    s32 obj;
    s32 ret;
    s32 v;

    ret = ((s32 (*)(void))func_8012C1B8)();
    obj = ret;
    *(s32 *)(arg0 + 0x20) = ret;
    if (ret == 0) {
        ((void (*)(s32))func_8012CAE4)(arg0);
        return;
    }
    {
        extern s32 D_801ACC1C;
        func_8001C810(obj, (s32)&D_801ACC1C);
    }
    func_8001D0E8(obj, 0x800, 0x800);
    func_8012A828(arg0, D_80189D04);
    *(s32 *)(arg0 + 8) = 0;
    v = *(s16 *)(arg0 + 0xA);
    *(s32 *)(arg0 + 0xC) = 0;
    *(s32 *)(arg0 + 4) = 0;
    D_80127190 = v;
    *(u32 *)(*(s32 *)(arg0 + 0x20) + 4) |= 0x40000040;
    *(u16 *)(arg0 + 2) += 1;
}
