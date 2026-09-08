/* func_8012FDA8 — shared body (overlay slot 0x80128158, h_exact 703b8336). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8012FDA8(int param_1)
{
    extern void func_8012CBF4(s32 a0);
    extern void func_80131CA8(int a0, int a1);
    extern void func_80131E00(struct S80131E00 *a0, s32 a1);
    int iVar1;
    unsigned int uVar2;
    if ((*(unsigned int *)(param_1 + 0xb4) & 0x100) != 0) {
        iVar1 = *(int *)(param_1 + 0x1c) + 1;
        *(int *)(param_1 + 0x1c) = iVar1;
        if (0x14 < iVar1) {
            ((void (*)(int, int))func_80131E00)(param_1, 0xd);
            return;
        }
        uVar2 = ((int (*)(int))func_8012CBF4)(param_1);
        if ((uVar2 & 0x2000) != 0) {
            if ((uVar2 & 0xff) == 2) {
                ((void (*)(int, int))func_80131E00)(param_1, 0x12);
                return;
            }
            if ((uVar2 & 0xff) == 0x1a) {
                func_801319E0(param_1);
                return;
            }
            func_80131C78(param_1);
        }
    }
    func_80131CA8(param_1, 0x1d);
    return;
}
