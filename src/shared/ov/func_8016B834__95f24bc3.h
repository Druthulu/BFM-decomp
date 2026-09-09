/* func_8016B834 — shared body (overlay slot 0x80128158, h_exact 95f24bc3). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
int func_8016B834(int param_1, int param_2) {
    int *puVar3;
    int *puVar2;
    int iVar1;

    puVar2 = (int *)(D_8018EC88 + param_2 * 0x40);
    puVar3 = D_80182498[*(int *)(param_1 + 0x2c)];
    iVar1 = ((int (*)(void))func_801465C0)();
    if (iVar1 != 0) {
        func_8001CD9C(iVar1, puVar2);
        func_800233CC(puVar2, D_801824A0[param_2]);
        puVar2[0] = *(int *)((int)puVar3 + param_2 * 8);
        puVar2[1] = *(int *)((int)puVar3 + param_2 * 8 + 4);
        *(unsigned int *)(iVar1 + 4) = *(unsigned int *)(iVar1 + 4) | 0x50040000;
        *(short *)(iVar1 + 0x1e) = D_801824A8[param_2];
    }
    return iVar1;
}
