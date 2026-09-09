/* func_8015D01C — shared body (overlay slot 0x80128158, h_exact e5d73af4). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8015D01C(int param_1)
{
    extern s32 func_801725F4(u8 *a0);
    extern int D_800D550C;
    short new_var2;
    unsigned short new_var;
    extern int D_80181AD8;
    short sVar2;
    int iVar4;
    unsigned short uVar1;
    unsigned short uVar5;
    short sVar3;
    ((void (*)(int, void *)) func_80154274)(param_1, &D_800D550C);
    *((short *) ((*((int *) (param_1 + 0x20))) + 0x10)) = 0;
    iVar4 = *((short *) ((*((int *) (param_1 + 0x20))) + 0x12));
    uVar1 = *((unsigned short *) ((*((int *) ((*((int *) (param_1 + 0x180))) + 0x20))) + 0x12));
    uVar5 = (uVar1 + 0x800) & 0xfff;
    new_var = uVar5;
    new_var2 = new_var;
    sVar2 = func_80012A60(iVar4, (short) uVar1);
    sVar3 = func_80012A60(iVar4, new_var2);
    if (sVar2 < sVar3)
    {
        *((short *) ((*((int *) (param_1 + 0x20))) + 0x12)) = uVar1;
    }
    else
    {
        *((unsigned short *) ((*((int *) (param_1 + 0x20))) + 0x12)) = new_var;
    }
    *((int *) (param_1 + 0x38)) = ((int) (&D_80181AD8)) | 0x40000000;
    ((void (*)(int)) func_801725F4)(param_1);
    ((void (*)(int)) func_80146CA0)(param_1);
}
