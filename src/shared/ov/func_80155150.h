/* func_80155150 — shared body (overlay slot 0x80128158, h_exact 109982dd). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8001D150(s32, s32);
extern void func_8001D130(int, int);
extern u8 func_8014BEF8(void);
void func_80155150(int param_1) {
    int iVar1;
    unsigned int uVar2;
    func_8001D150(*(int *)(*(int *)(param_1 + 0x20) + 0x24), 0x19);
    func_8001D150(*(int *)(*(int *)(param_1 + 0x20) + 0x24), 0x18);
    func_8001D150(*(int *)(*(int *)(param_1 + 0x20) + 0x24), 0x16);
    func_8001D150(*(int *)(*(int *)(param_1 + 0x20) + 0x24), 0x15);
    uVar2 = *(unsigned int *)(param_1 + 0x44);
    if ((uVar2 & 0x400) != 0) {
        return;
    }
    if ((uVar2 & 0x20000) == 0) {
        if ((uVar2 & 0x20000000) != 0) {
            func_8001D130(*(int *)(*(int *)(param_1 + 0x20) + 0x24), 0x19);
        } else {
            iVar1 = ((int (*)(int))func_8014BEF8)(param_1);
            if (iVar1 != 0) {
                func_8001D150(*(int *)(*(int *)(param_1 + 0x20) + 0x24), 0x19);
                func_8001D130(*(int *)(*(int *)(param_1 + 0x20) + 0x24), 0x18);
                goto LAB_80155260;
            }
            func_8001D150(*(int *)(*(int *)(param_1 + 0x20) + 0x24), 0x19);
        }
        func_8001D150(*(int *)(*(int *)(param_1 + 0x20) + 0x24), 0x18);
    }
LAB_80155260:
    if ((*(unsigned int *)(param_1 + 0x44) & 0x10000000) != 0) {
        func_8001D130(*(int *)(*(int *)(param_1 + 0x20) + 0x24), 0x16);
        goto LAB_801552CC;
    }
    func_8001D150(*(int *)(*(int *)(param_1 + 0x20) + 0x24), 0x16);
    func_8001D130(*(int *)(*(int *)(param_1 + 0x20) + 0x24), 0x15);
    if ((*(unsigned int *)(param_1 + 0x44) & 4) == 0) {
        return;
    }
LAB_801552CC:
    func_8001D150(*(int *)(*(int *)(param_1 + 0x20) + 0x24), 0x15);
    return;
}
