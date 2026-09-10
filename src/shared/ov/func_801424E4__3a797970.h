/* func_801424E4 — shared body (overlay slot 0x80128158, h_exact 3a797970). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_801424E4(short *param_1) {

    extern void (*D_8018069C[])(void);
    short sVar1;
    int iVar2;
    unsigned short t;

    (*D_8018069C[(unsigned short)param_1[1]])();
    if (*(unsigned short *)param_1 != 0) {
        if (param_1[0x38] != 0) {
            iVar2 = *(int *)(param_1 + 0x32);
            if (iVar2 == 0) {
                return;
            }
            *(int *)(param_1 + 2) = *(int *)(iVar2 + 4);
            t = (unsigned short)param_1[0x7e];
            sVar1 = *(unsigned short *)(iVar2 + 10) + t;
            param_1[5] = sVar1;
            *(int *)(param_1 + 6) = *(int *)(iVar2 + 0xc);
        } else {
            unsigned short a;
            iVar2 = *(int *)(param_1 + 0x32);
            if ((iVar2 != 0) && (*(short *)(iVar2 + 0x36) == param_1[0x7f])) {
                *(int *)(param_1 + 2) = *(int *)(iVar2 + 4);
                a = *(unsigned short *)(*(int *)(param_1 + 0x32) + 10);
                param_1[5] = (a + ((unsigned short)param_1[0x7e]));
                iVar2 = *(int *)(param_1 + 0x32);
                *(int *)(param_1 + 6) = *(int *)(iVar2 + 0xc);
                return;
            }
            ((void (*)(short *))func_8012C218)(param_1);
        }
    }
    return;
}
