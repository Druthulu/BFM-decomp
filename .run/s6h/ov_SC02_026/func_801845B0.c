void func_801845B0(s32 a0)
{
    if (*(u16 *)a0 != 0) {
        if (*(s16 *)(a0 + 0x70) == 0x4) {
            s32 res = func_8012C658(0x12C, 0x4, a0);
            if (res != 0) {
                *(u16 *)(res + 0x6) = *(u16 *)(a0 + 0x88);
                *(u16 *)(res + 0x88) = *(u16 *)(a0 + 0x88);
                *(u16 *)(res + 0xE) = *(u16 *)(a0 + 0x8C);
                *(u16 *)(res + 0x8C) = *(u16 *)(a0 + 0x8C);
                *(u16 *)(res + 0xA) = *(u16 *)(a0 + 0x8A) - 0x400;
                *(u16 *)(res + 0x8A) = *(u16 *)(a0 + 0x8A);
                func_8012B2CC(res);
            }
        }
    }
    if (func_80153BD8(a0)) {
        func_80153BF0(a0);
    }
    if (*(s32 *)(a0 + 0x78) != 0) {
        func_8002A04C(a0);
    }
    func_8012C098((void *)a0);
}
