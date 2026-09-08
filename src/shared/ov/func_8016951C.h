/* func_8016951C — shared body (overlay slot 0x80128158, h_exact 70b8e5ac). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80169584(s32 param_1);
extern void func_800D22E4(s32 a0);
extern void func_80146C3C();
void func_8016951C(int param_1)
{
    int iVar1;
    iVar1 = *(int *)(param_1 + 0x1c);
    *(int *)(param_1 + 0x1c) = iVar1 + 1;
    if (iVar1 < 10) {
        ((void (*)(void))func_80169584)();
        func_800D22E4(param_1);
        *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 0x8000;
    } else {
        ((void (*)(int))func_80146C3C)(param_1);
    }
    return;
}
