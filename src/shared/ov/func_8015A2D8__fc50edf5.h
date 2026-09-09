/* func_8015A2D8 — shared body (overlay slot 0x80128158, h_exact fc50edf5). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8015A2D8(s32 param_1)
{
    unsigned char bVar1;

    ((void (*)(int, int *))func_80146DB8)(param_1, &D_80181888);
    if ((*(unsigned int *)(param_1 + 0x44) & 0x200) != 0) {
        func_80154150(param_1, 10);
        func_80154A74(param_1, 0x1c);
        *(int *)(param_1 + 0x2c) = 0xfffc0000;
        goto LAB_8015a38c;
    }
    bVar1 = *(unsigned char *)(param_1 + 0xa9);
    switch (bVar1) {
    case 0x41:
        func_80154150(param_1, 7);
        break;
    case 0x53:
    case 0x73:
        func_80154150(param_1, 6);
        break;
    default:
        *(int *)(param_1 + 0x23c) = 0;
        goto LAB_8015a390;
    }
    func_80154A74(param_1, 0x21);
LAB_8015a38c:
    *(int *)(param_1 + 0x23c) = 0;
LAB_8015a390:
    func_8014C010(param_1, 2);
    ((void (*)(int))func_801553A8)(param_1);
    ((void (*)(int))func_80172608)(param_1);
    ((void (*)(int))func_80146CA0)(param_1);
    return;
}
