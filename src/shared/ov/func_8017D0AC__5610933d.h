/* func_8017D0AC — shared body (overlay slot 0x80128158, h_exact 5610933d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8017D0AC(int param_1)
{
    unsigned short uVar1;
    uVar1 = *(unsigned short *)(param_1 + 0x12) - 0x100;
    *(unsigned short *)(param_1 + 0x12) = uVar1;
    if ((short)uVar1 > 0) {
        func_8017D0F8(param_1);
    } else {
        ((void (*)(int))func_80146C3C)(param_1);
    }
}
