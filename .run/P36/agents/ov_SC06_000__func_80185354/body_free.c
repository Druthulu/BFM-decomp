void func_80185354(void *param_1)
{
    s32 i;
    u8 *e;
    u32 vA, vB;

    i = 0;
    e = D_801AED08;
    do {
        ((void (*)(void *, s32))func_80185520)(e, i);
        i = i + 1;
        vA = rand() & 0x1F;
        *(u32 *)(e + 0x18) = (vA << 2) | ((vA << 0x12) | (vA << 10));
        vB = rand() & 7;
        *(u32 *)(e + 0x20) = vB;
        e = e + 0x2C;
    } while (i < 200);
    func_8012BF4C((s32 *)param_1, 4);
    func_8012AD50(param_1);
}
