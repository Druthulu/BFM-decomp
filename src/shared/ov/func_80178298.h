/* func_80178298 — shared body (overlay slot 0x80128158, h_exact d8d556f5). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
u32 *func_80178298(u32 *param_1, u8 *param_2, short param_3, short param_4) {
    u8 bVar1;
    short sVar2;
    if (*param_2 < 0x80) {
        do {
            sVar2 = *(short *)param_2;
            switch (sVar2) {
            case 0x1850:
            case 0x1858:
                *(short *)((u8 *)param_1 + 8) = param_3 + 4;
                *(short *)((u8 *)param_1 + 0xA) = param_4 + -7;
                break;
            case 0x3870:
                param_3 = param_3 + 8;
                param_2 = param_2 + 2;
                continue;
            case 0x3871:
                param_3 = param_3 + 4;
                param_2 = param_2 + 2;
                continue;
            case 0x3872:
                param_3 = param_3 + 2;
                param_2 = param_2 + 2;
                continue;
            default:
                *(short *)((u8 *)param_1 + 8) = param_3;
                *(short *)((u8 *)param_1 + 0xA) = param_4;
                if (*(short *)param_2 >= 0x861) {
                    param_3 = param_3 + 8;
                } else {
                    param_3 = param_3 + 7;
                }
                break;
            }
            *param_1 = (u32)(param_1 + -5) & 0xffffff | 0x4000000;
            *(u32 *)((u8 *)param_1 + 4) = 0x64808080;
            ((u8 *)param_1)[0xC] = *param_2;
            param_2 = param_2 + 1;
            bVar1 = *param_2;
            param_2 = param_2 + 1;
            *(short *)((u8 *)param_1 + 0xE) = 0x4056;
            ((u8 *)param_1)[0xD] = bVar1;
            *(short *)((u8 *)param_1 + 0x10) = 8;
            *(short *)((u8 *)param_1 + 0x12) = 8;
            param_1 = param_1 + 5;
        } while (*param_2 < 0x80);
    }
    return param_1;
}
