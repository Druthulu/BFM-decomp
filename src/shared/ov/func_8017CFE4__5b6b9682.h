/* func_8017CFE4 — shared body (overlay slot 0x80128158, h_exact 5b6b9682). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8017D030(int);
extern void func_80146C3C(void);
void func_8017CFE4(int param_1)
{
    unsigned short uVar1;
    uVar1 = *(unsigned short *)(param_1 + 0x12) - 0x100;
    *(unsigned short *)(param_1 + 0x12) = uVar1;
    if ((short)uVar1 > 0) {
        func_8017D030(param_1);
    } else {
        ((void (*)(int))func_80146C3C)(param_1);
    }
}
