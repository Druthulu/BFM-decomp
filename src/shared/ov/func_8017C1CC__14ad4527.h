/* func_8017C1CC — shared body (overlay slot 0x80128158, h_exact 14ad4527). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8017C218(int);
extern void func_80146C3C();
void func_8017C1CC(int param_1)
{
    unsigned short uVar1;
    uVar1 = *(unsigned short *)(param_1 + 0x12) - 0x100;
    *(unsigned short *)(param_1 + 0x12) = uVar1;
    if ((short)uVar1 > 0) {
        func_8017C218(param_1);
    } else {
        ((void (*)(int))func_80146C3C)(param_1);
    }
}
