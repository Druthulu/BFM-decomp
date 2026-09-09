/* func_8013C0F8 — shared body (overlay slot 0x80128158, h_exact 6e43c7c8). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8013C0F8(int param_1) {
    int iVar1;
    int iVar2;
    unsigned int local_18;
    unsigned int local_14;
    Bar *local_10;
    Foo *local_c;

    iVar1 = param_1 + 0x14;
    if (*(char *)(param_1 + 4) == '\0') {
        iVar2 = iVar1 + *(int *)(param_1 + 0xc);
        *(int *)(param_1 + 0xc) = iVar2;
        *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + iVar1;
        local_c = (Foo *)iVar1;
        for (local_18 = 0; local_18 < *(unsigned int *)(param_1 + 8); local_18++, local_c++) {
            local_c->field10 = local_c->field10 + iVar1;
            local_10 = (Bar *)local_c->field10;
            for (local_14 = 0; local_14 < local_c->count; local_14++, local_10++) {
                switch (local_10->tag) {
                case 0x24:
                case 0x2c:
                case 0x34:
                case 0x3c:
                    *(unsigned int *)local_10 = (*(unsigned int *)local_10 & 0xffffff) + iVar2;
                    break;
                case 0x26:
                case 0x2e:
                case 0x36:
                case 0x3e:
                    *(unsigned int *)local_10 = (*(unsigned int *)local_10 & 0xffffff) + iVar2;
                    break;
                }
            }
        }
        *(unsigned char *)(param_1 + 4) = 1;
    }
}
