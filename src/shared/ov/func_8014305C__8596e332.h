/* func_8014305C — shared body (overlay slot 0x80128158, h_exact 8596e332). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8014305C(int param_1)
{
    int s0_param = param_1;
    int s1_copy;
    int iVar2;
    short sVar1;

    do { iVar2 = ((int (*)(void))func_8012C1B8)(); } while (0);
    s1_copy = iVar2;
    *(int *)(s0_param + 0x20) = iVar2;
    if (iVar2 == 0) {
        ((void (*)(int))func_8012CAE4)(s0_param);
    } else {
        ((void (*)(int, void *))func_8001CA1C)(s1_copy, D_80180108);
        sVar1 = (*(unsigned short *)(s0_param + 0x70) & 0xf) * 0x600 + 0xc00;
        *(short *)(s1_copy + 0x1a) = sVar1;
        *(short *)(s1_copy + 0x18) = sVar1;
        *(short *)(s0_param + 0xfc) = 0;
        func_8012A828(s0_param, D_80180168);
        ((void (*)(int))func_80142B2C)(s0_param);
    }
}
