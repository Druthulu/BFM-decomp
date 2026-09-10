void func_8014305C(int param_1)
{

    extern unsigned char D_8018BA50[];
    extern unsigned char D_8018BAB0[];
    short sVar1;
    int iVar2;

    *(int *)(param_1 + 0x20) = iVar2 = ((int (*)(void))func_8012C1B8)();
    if (iVar2 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        ((void (*)(int, void *))func_8001CA1C)(iVar2, D_8018BA50);
        sVar1 = (*(unsigned short *)(param_1 + 0x70) & 0xf) * 0x600 + 0xc00;
        *(short *)(iVar2 + 0x1a) = sVar1;
        *(short *)(iVar2 + 0x18) = sVar1;
        *(short *)(param_1 + 0xfc) = 0;
        func_8012A828(param_1, D_8018BAB0);
        ((void (*)(int))func_80142B2C)(param_1);
    }
}
